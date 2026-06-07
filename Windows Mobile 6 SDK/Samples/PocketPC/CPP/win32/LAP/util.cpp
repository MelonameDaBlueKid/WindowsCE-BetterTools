//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//


#include "lap_priv.h"
#include "scope_guard.h"
#include "intsafe.h"
#include <snapi.h>

// Don't create a message window shorter than this
// because it won't look pretty.
#define MIN_MESSAGE_HEIGHT  106

// Registry keys
const TCHAR* K_SZLAPKEY          = TEXT("Comm\\Security\\LASSD\\LAP\\SampleLap");
const TCHAR* K_SZLAPPOLICYKEY    = TEXT("Comm\\Security\\Policy\\LASSD\\LAP\\SampleLap");
const TCHAR* K_SZAELOCKKEY       = TEXT("Comm\\Security\\LASSD\\AE\\{50C13377-C66D-400C-889E-C316FC4AB374}");
const TCHAR* K_SZAELOCKPOLICYKEY = TEXT("Comm\\Security\\Policy\\LASSD\\AE\\{50C13377-C66D-400C-889E-C316FC4AB374}");

// Registry values
const TCHAR* K_SZHASH            = TEXT("_");
const TCHAR* K_SZMINLENGTH       = TEXT("MinimumPasswordLength");
const TCHAR* K_SZLKGPOLICY       = TEXT("LKGPolicy");
const TCHAR* K_SZCOMPLEXITY      = TEXT("ComplexElements");
const TCHAR* K_SZTIMEOUT         = TEXT("PasswordTimeout");
const TCHAR* K_SZALG             = TEXT("Algorithm");
const TCHAR* K_SZSALT            = TEXT("Salt");
const TCHAR* K_SZHISTORYSIZE     = TEXT("NumberOfPasswords");
const TCHAR* K_SZPROVTYPE        = TEXT("LAPProviderType");
const TCHAR* K_SZPROVNAME        = TEXT("LAPProviderName");
const TCHAR* K_SZHASHALG         = TEXT("LAPHashAlgorithm");

#define DEFAULT_PASSWORD_TIMEOUT    20000 // 20 seconds.
#define MIN_PASSWORD_TIMEOUT        10000 // 10 seconds.
#define CCHMAX_EMERGENCY_CALL_LIST  65

const TCHAR* K_SZRESETTEXT = TEXT("");

TCHAR*  g_pszPreviousPassword    = NULL;
HMODULE g_hInst = NULL;
BOOL    g_fPolicyRequiresUpdate = FALSE;  // Do we have to force updating?

const localalloc_t localalloc;

// Don't allow these hashing algorithms because they 
// don't meet cryptographic standards.
const DWORD c_rgUnsupportedAlgs[] = 
{
    ALG_SID_MD2,
    ALG_SID_MD4,
    ALG_SID_MD5,
    ALG_SID_RIPEMD,
    ALG_SID_RIPEMD160,
    ALG_SID_SSL3SHAMD5,
    ALG_SID_HMAC,
    ALG_SID_TLS1PRF,
    ALG_SID_HASH_REPLACE_OWF,
};

// Summary:
//   Retrieve password settings and policy from registry.
//
// Parameters:
//  ppwi -- Pointer to a PASSWDINFO structure. Upon successful
//   completion, this structure will contain the current password
//   settings and policy.
//
// Returns:
//   Returns success if the password information was filled in,
//   otherwise failure.
//
//
// Remarks:
//   Calls GetPolicy to load the current policy
//     settings.
//   When this structure is used to present options to the
//     user, this call should be followed by a call to 
//     InitPasswordInfo to force the user settings to
//     conform to policy.
// 
HRESULT GetPasswordInfo(PASSWDINFO *ppwi)
{
    HRESULT hr = S_OK;
    DWORD   dwSize = 0;
    HKEY    hKey = NULL;
    DWORD   dwType = 0;
    DWORD   dwTempValue = 0;    // Always put reg values into temp value first.

    if(NULL == ppwi)
    {
        // Parameter is invalid.
        hr = E_INVALIDARG;
    }
    else
    {
        // Initialize the struct (all settings default to 0).
        memset(ppwi, 0, sizeof(PASSWDINFO));

        // USER SETTINGS.
        // Password on/off.
        ppwi->bPasswordOn = LapGetPasswordOn();

        // Open the AE_IDLE key.
        if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_ROOT, K_SZAELOCKKEY, 
            0, 0, &hKey))
        {
            ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

            // Frequency Type.
            dwSize = sizeof(dwTempValue);
            if(ERROR_SUCCESS == RegQueryValueEx(hKey, 
                REG_AE_AUTH_FREQ_TYPE, NULL, &dwType, 
                (LPBYTE)&dwTempValue, &dwSize) && 
                REG_DWORD == dwType)
            {
                ppwi->uFrequencyType = dwTempValue;
            }

            // We only care about the timeout value
            // if the timeout is on (FT_Minutes_Idle)
            if(FT_Minutes_Idle == ppwi->uFrequencyType)
            {
                // Frequency Value
                dwSize = sizeof(dwTempValue);
                if(ERROR_SUCCESS == RegQueryValueEx(hKey, 
                    REG_AE_AUTH_FREQ_VALUE, NULL, &dwType, 
                    (LPBYTE)&dwTempValue, &dwSize) &&
                    REG_DWORD == dwType)
                {
                    // Check for out-of-bounds values
                    if(MAX_FREQUENCY_VALUE < dwTempValue)
                    {
                        ppwi->uFrequencyValue = MAX_FREQUENCY_VALUE;
                    }
                    else
                    {
                        ppwi->uFrequencyValue = dwTempValue;
                    }
                }
            }
        }

        // Retrieve all policy settings.
        hr = GetPolicy(&ppwi->Policy);
    }

    return hr;
}

HRESULT GetPasswordHistorySize (__out UINT *pcHistorySize)
{
    HRESULT hr;
    DWORD   cSize = 0;

    hr = RegistryGetDWORD(HKEY_ROOT, K_SZLAPPOLICYKEY, K_SZHISTORYSIZE, &cSize);
    if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
    {
        cSize = 0;
        hr = S_OK;
    }

    if (cSize > MAX_PASSWORD_HISTORY)
    {
        cSize = MAX_PASSWORD_HISTORY;
    }

    *pcHistorySize = cSize;
    return hr;
}

// Summary:
//   Retrieves components of the master policy.
//
// Parameters:
//  pPolicy -- Pointer to a PASSWDPOLICY structure.
//   Assumes all data are already initialized to 0.
//
// Returns:
//   Returns success if the policy information was filled in;
//   otherwise failure.
//
//
// Remarks:
//   Queries device management policy SECPOLICY_LASS_PWD_REQUIRED
//     to determine if policy is in use. If not, only default values
//     are used.
// 
HRESULT GetPolicy(PASSWDPOLICY* pPolicy)
{
    HRESULT hr          = S_OK;
    DWORD   dwSize      = 0;
    HKEY    hKey        = NULL;
    DWORD   dwType      = 0;
    DWORD   dwTempValue = 0;

    if(NULL == pPolicy)
    {
        // Parameter is invalid.
        hr = E_INVALIDARG;
    }
    else
    {
        // Get the overriding policy from device management.
        DWORD dwPolicy = POLICYVAL_LASS_PWD_REQUIRED;
        (void)QueryPolicy(SECPOLICY_LASS_PWD_REQUIRED, &dwPolicy);
        pPolicy->bPasswordOn = (POLICYVAL_LASS_PWD_REQUIRED == dwPolicy); 

        // Only get rest of policy if password was forced on.
        if(pPolicy->bPasswordOn)
        {
            // Open main LAP policy key.
            if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_ROOT, K_SZLAPPOLICYKEY, 
                0, 0, &hKey))
            {
                ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

                // Complexity.
                dwSize = sizeof(dwTempValue);
                if(ERROR_SUCCESS == RegQueryValueEx(hKey, K_SZCOMPLEXITY, 
                    NULL, &dwType, (LPBYTE)&dwTempValue, &dwSize) &&
                    REG_DWORD == dwType)
                {
                    // Check for out-of-bounds values.
                    if(MAX_COMPLEXITY < dwTempValue)
                    {
                        pPolicy->uComplexity = MAX_COMPLEXITY;
                    }
                    else
                    {
                        pPolicy->uComplexity = dwTempValue;
                    }
                }

                // Min length.
                dwSize = sizeof(dwTempValue);
                if(ERROR_SUCCESS == RegQueryValueEx(hKey, K_SZMINLENGTH, 
                    NULL, &dwType, (LPBYTE)&dwTempValue, &dwSize) && 
                    REG_DWORD == dwType)
                {
                    // Check for out-of-bounds values.
                    if(MAX_PASSWORD < dwTempValue)
                    {
                        pPolicy->uMinLength = MAX_PASSWORD;
                    }
                    else
                    {
                        pPolicy->uMinLength = dwTempValue;
                    }
                }
            }

            // Check for idle timeout policy.
            if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_ROOT, 
                K_SZAELOCKPOLICYKEY, 0, 0, &hKey))
            {
                ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

                // Frequency Type.
                dwSize = sizeof(dwTempValue);
                if(ERROR_SUCCESS == RegQueryValueEx(hKey, 
                    REG_AE_AUTH_FREQ_TYPE, NULL, &dwType, 
                    (LPBYTE)&dwTempValue, &dwSize) &&
                    REG_DWORD == dwType)
                {
                    pPolicy->uFrequencyType = dwTempValue;
                }

                // We only care about the timeout value
                // if the timeout is on (FT_Minutes_Idle)
                if(FT_Minutes_Idle == pPolicy->uFrequencyType)
                {
                    // Frequency Value.
                    dwSize = sizeof(dwTempValue);
                    if(ERROR_SUCCESS == RegQueryValueEx(hKey, 
                        REG_AE_AUTH_FREQ_VALUE, NULL, &dwType, 
                        (LPBYTE)&dwTempValue, &dwSize) && 
                        REG_DWORD == dwType)
                    {
                        // Check for out-of-bounds values.
                        if(MAX_FREQUENCY_VALUE < dwTempValue)
                        {
                            pPolicy->uFrequencyValue = MAX_FREQUENCY_VALUE;
                        }
                        else
                        {
                            pPolicy->uFrequencyValue = dwTempValue;
                        }
                    }
                }
            }
        }
        else
        {
            // Policies are off, so use non-policy defaults.
            pPolicy->uComplexity = 3;   // 3 complex elements.
            pPolicy->uMinLength  = 7;   // 7 characters minimum.
        }

        // We always apply Password policy regardless of password enforcement
        hr = GetPasswordHistorySize(&pPolicy->uNumberOfPasswords);
        if (FAILED(hr))
        {
            hr = S_FALSE;
        }
    }

    return hr;
}


// Summary:
//   Gets the policy in effect at the time of last successful enrollment 
//   (LKG = last known good).
//
// Parameters:
//  pPolicy -- Pointer to a PASSWDPOLICY structure.
//
// Returns:
//   Returns success if the policy information was filled in;
//   otherwise failure.
//
//
// Remarks:
//   If no LKG policy has ever been saved on this device,
//     defaults all values to 0.
// 
HRESULT GetLKGPolicy(PASSWDPOLICY* pPolicy)
{
    HRESULT hr = S_FALSE;
    HKEY    hKey = NULL;
    DWORD   dwSize = 0;
    DWORD   dwType = 0;
    PASSWDPOLICY tmpPolicy;

    // Initialize the structure (defaults are all 0).
    memset(pPolicy, 0, sizeof(PASSWDPOLICY));

    // Open the registry key.
    if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY,
        0, 0, &hKey))
    {
        ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

        // Get the binary structure.
        dwSize = sizeof(PASSWDPOLICY);
        if(ERROR_SUCCESS == RegQueryValueEx(hKey, K_SZLKGPOLICY, 
            0, &dwType, (LPBYTE)&tmpPolicy, &dwSize) &&
            REG_BINARY == dwType && 
            sizeof(PASSWDPOLICY) == dwSize)
        {
            // Only copy this to our return variable after we
            // have confirmed type and size.
            memcpy(pPolicy, &tmpPolicy, sizeof(PASSWDPOLICY));
            hr = S_OK;
        }
    }

    return hr;
}


// Summary:
//   Sets the policy in effect at the time of last successful enrollment 
//   (LKG = last known good).
//
// Parameters:
//  pPolicy -- Pointer to a PASSWDPOLICY structure.
//
// Returns:
//   Returns success if the policy information was saved;
//   otherwise failure.
// 
HRESULT SaveLKGPolicy(PASSWDPOLICY const * pPolicy)
{
    HRESULT hr = E_FAIL;
    HKEY    hKey = NULL;

    // Create the key first.
    if(ERROR_SUCCESS == RegCreateKeyEx(HKEY_ROOT, K_SZLAPKEY, 0, NULL, 0, 
        KEY_WRITE, NULL, &hKey, NULL))
    {
        ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

        // Save the binary structure.
        if(ERROR_SUCCESS == RegSetValueEx(hKey, K_SZLKGPOLICY, 0, 
            REG_BINARY, (LPBYTE)pPolicy, sizeof(PASSWDPOLICY)))
        {
            hr = S_OK;
        }
    }

    return hr;
}


// Summary:
//   Saves password, LKG policy, and other password settings
//   to the registry.
//
// Parameters:
//  ppwi -- Pointer to a PASSWDINFO structure. All data
//   must have been validated before calling this function.
//
// Returns:
//   Returns success if the password information was saved;
//   otherwise failure.
//
//
// Remarks:
//   Turns the password off or on based on the value in
//     ppwi->bPasswordOn.
//   After saving data to registry, flushes the registry and
//     broadcasts a  WM_SETTINGCHANGE message.
// 
HRESULT SavePasswordInfo(PASSWDINFO const * ppwi)
{
    HRESULT hr = E_FAIL;
    HKEY    hKey;

    // Set a cursor because this might take a few seconds.
    HCURSOR hcursor = SetCursor(LoadCursor(0, IDC_WAIT));

    // Frequency Type.
    if(ERROR_SUCCESS == RegCreateKeyEx(HKEY_ROOT, K_SZAELOCKKEY, 0, 
        NULL, 0, KEY_WRITE, NULL, &hKey, NULL))
    {
        ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

        if(ERROR_SUCCESS == RegSetValueEx(hKey, REG_AE_AUTH_FREQ_TYPE, 
            0, REG_DWORD, (LPBYTE)&ppwi->uFrequencyType, 
            sizeof(ppwi->uFrequencyType)))
        {
            // Frequency Value.
            if(ERROR_SUCCESS == RegSetValueEx(hKey, REG_AE_AUTH_FREQ_VALUE, 
                0, REG_DWORD, (LPBYTE)&ppwi->uFrequencyValue, 
                sizeof(ppwi->uFrequencyValue)))
            {
                // Only make changes to password settings if this 
                // flag is set.
                if(!ppwi->bPasswordChanged)
                {
                    hr = S_OK;
                }
                else
                {
                    // Only set password text if password is activated.
                    if(ppwi->bPasswordOn)
                    {
                        // Turn password on or keep it on and 
                        // change it.
                        if(LapSetPasswordOn(g_pszPreviousPassword, 
                            ppwi->szPassword))
                        {
                            hr = S_OK;
                        }
                    }
                    else
                    {
                        // Turn password off.
                        if(LapSetPasswordOff(g_pszPreviousPassword))
                        {
                            hr = S_OK;
                        }
                    }
                }
            }
        }
    }

    // Flush the registry now.
    (void)RegFlushKey(HKEY_ROOT);

    // Let the system know we've made settings changes.
    (void)PostMessage(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, NULL);

    // Restore previous cursor.
    (void)SetCursor(hcursor);

    return hr;
}


// Summary:
//   Saves a copy of the password for enrollment.
//
// Parameters:
//  pszPassword -- NULL-terminated password string.
//   Limited to MAX_PASSWORD characters.
//
// Remarks:
//   Allocates memory in a global variable to store the password
//     string. FreePasswordForEnrollment must be called to free this 
//     memory.
// 
void SavePasswordForEnrollment(LPCTSTR pszPassword)
{
    size_t cchPassword = 0;

    // Free the old password first.
    if(NULL != g_pszPreviousPassword)
    {
        FreePasswordForEnrollment();
    }

    // Get length of password.
    if(SUCCEEDED(StringCchLength(pszPassword, MAX_PASSWORD + 1, 
        &cchPassword)))
    {
        // Allocate the global password buffer for the new password.
        g_pszPreviousPassword = new (localalloc) TCHAR[cchPassword + 1];
        if(NULL != g_pszPreviousPassword)
        {   
            // Copy the password into the buffer.
            (void)StringCchCopy(g_pszPreviousPassword, 
                cchPassword + 1, pszPassword);
        }
    }
}


// Summary:
//   Frees a copy of the password saved using 
//   SavePasswordForEnrollment.
//
//
// Remarks:
//   
// 
void FreePasswordForEnrollment()
{
    if(NULL != g_pszPreviousPassword)
    {
        // First wipe the string for security.
        size_t cchPassword = 0;
        (void)StringCchLength(g_pszPreviousPassword, 
            MAX_PASSWORD + 1, &cchPassword);
        for(UINT i=0; i < cchPassword && 
            TEXT('\0') != g_pszPreviousPassword[i]; i++)
        {
            g_pszPreviousPassword[i] = 0;
        }

        // Free the buffer memory.
        (void)LocalFree(g_pszPreviousPassword);
        g_pszPreviousPassword = NULL;
    }
}


// Summary:
//   Retrieves the password timeout from the registry. This is the
//   timeout used to clear the password or close the password dialog
//   if the user has been idle for too long.
// 
//
// Returns:
//   Returns the timeout value in seconds.
//
//
// Remarks:
//   Reads from the registry location 
//     HKEY_LOCAL_MACHINE\Security\Policies\SampleLap\PasswordTimeout.
//   This function only reads the registry once. Thereafter
//     it returns the already-loaded value. If the password timeout
//     changes, the LAP must be reloaded to use the new value.
//   If the registry value does not exist, uses the default 
//     password timeout of 10 seconds. Minimum timeout is 10 seconds.
// 
DWORD GetPasswordTimeout()
{
    static DWORD s_dwTimeout = 0;

    if(0 == s_dwTimeout)
    {
        // Only get timeout the first time; policy changes
        // are not supported in real-time.
        s_dwTimeout = DEFAULT_PASSWORD_TIMEOUT; // Default = 10 seconds.

        // Try to read in the value from the registry.
        (void)RegistryGetDWORD(HKEY_ROOT, K_SZLAPPOLICYKEY, 
            K_SZTIMEOUT, &s_dwTimeout);

        // Validate registry data.
        if(MIN_PASSWORD_TIMEOUT > s_dwTimeout)
        {
            s_dwTimeout = MIN_PASSWORD_TIMEOUT;
        }
    }

    return s_dwTimeout;
}


// Summary:
//   Shows the specific window if it is owned by the
//   passed-in window.
// 
// Parameters:
//   hwnd -- Handle to the window to show.
//   lParam --  Handle to a window. If hwnd is owned by this
//    window (or is this window), it will be shown. 
//    Otherwise, no action will be taken.
//
// Returns:
//   Always returns TRUE so the enumeration will continue.
//
BOOL ShowOwnedWindowsEnumProc(__in HWND hwnd, __in_opt LPARAM lParam)
{
    HWND hwndMain = reinterpret_cast<HWND>(lParam);
    
    // Run up the owner chain and check if the window 
    // is owned by the specified owner.
    for(HWND hwndOwner = hwnd;
        hwndOwner != NULL;
        hwndOwner = GetWindow(hwndOwner, GW_OWNER))
    {
        // The first check will be the passed-in window itself.
        // If any owner in the chain is the specified main window,
        // show this window.
        if(hwndOwner == hwndMain)
        {
            (void)ShowWindow(hwnd, SW_SHOWNOACTIVATE);
            break;
        }
    }

    return TRUE;
}


// Summary:
//   Brings the specified stored window to the foreground.
//
// Parameters:
//  lw -- LAP_WINDOW value representing the handle of the
//   desired stored window.
//
// Returns:
//   Returns TRUE if the specified window is a valid window and 
//   it was brought to the foreground. Also returns TRUE if
//   the specified window is currently reserved by another function;
//   otherwise, returns FALSE.
//
// Remarks:
//   The specified window must have already been created and
//     stored using the window manager.
// 
BOOL SetWindowToTop(LAP_WINDOW lw)
{
    BOOL fSuccess = FALSE;

    // Get stored window handle.
    HWND hwnd = WndManager()[lw];

    if(WndManager().IsReserved(lw))
    {
        // Return TRUE if someone has reserved this window
        // but it hasn't been created yet.
        fSuccess = TRUE;
    }
    else if(IsWindow(hwnd))
    {
        // Make sure window and all owned 
        // windows are visible first.
        (void)EnumWindows(ShowOwnedWindowsEnumProc, 
            reinterpret_cast<LPARAM>(hwnd)); 

        // Set the window to be foreground.
        // Use the 0x01 flag to make sure that all
        // owned windows are shown as well.
        (void)SetForegroundWindow(reinterpret_cast<HWND>(
            reinterpret_cast<ULONG>(hwnd) | 0x01));

        fSuccess = TRUE;
    }

    return fSuccess;
}


// Summary:
//   Checks if policy requires a password update, and if so
//   forces enrollment.
//
// Parameters:
//  lpParameter -- Ignored.
//
// Returns:
//   Always returns 0.
//
//
// Remarks:
//   Checks the current master policy against the LKG policy.
//     If differences require the password to be updated, calls
//     SHDeviceLockAndPrompt() to force enrollment. Wwaits until the 
//     Shell APIs are loaded before making this call.
// 
DWORD PolicyThreadProc(LPVOID lpParameter)
{
    HRESULT         hr;
    PASSWDINFO      pwi;
    PASSWDPOLICY    lkgPolicy;

    // Get current password settings.
    hr = GetPasswordInfo(&pwi);
    if(SUCCEEDED(hr))
    {
        // Get LKG policy.
        hr = GetLKGPolicy(&lkgPolicy);

        if(SUCCEEDED(hr))
        {
            if(hr != S_FALSE)
            {
                // The LKG policy exists
                // (S_FALSE means no LKG policy).
                if(pwi.Policy.bPasswordOn)
                {
                    // Policy requires password so check against previous 
                    // settings to see if new policy is more strict than 
                    // the current one.
                    g_fPolicyRequiresUpdate = 
                        PolicyRequiresUpdate(&pwi, &lkgPolicy);
                }
            }
            else
            {
                // There was no lkg policy so this was probably an upgrade. 
                // Force enrollment if the current policy requires a 
                // password. Ideally we would only force enrollment if 
                // the password didn't meet the policy requirements 
                // but we don't have that information.
                if(pwi.Policy.bPasswordOn)
                {
                    g_fPolicyRequiresUpdate = TRUE;
                }
            }

            // If we need to re-enroll now, call Lock-And-Prompt.
            if(g_fPolicyRequiresUpdate)
            {
                // Wait for Shell APIs to be ready.
                HANDLE hevt = OpenEvent(EVENT_ALL_ACCESS, FALSE, 
                    TEXT("SYSTEM/ShellAPIReady"));
                ASSERT(NULL != hevt); 
                (void)WaitForSingleObject(hevt, INFINITE);
                (void)CloseHandle(hevt);

                // Lock device and prompt user (forces enrollment).
                (void)SHDeviceLockAndPrompt();
            }
        }
    }

    return 0;
}


// Summary:
//   Checks the master policy against LKG policy to determine if any
//   conditions exist that require re-enrollment.
//
// Parameters:
//  ppwi -- Pointer to a PASSWDINFO structure that is populated
//   with the current password settings, including master policy.
//  pLKGPolicy -- Pointer to a PASSWDPOLICY structure that is 
//   populated with the LKG policy.
//
// Returns:
//   Returns TRUE if re-enrollment is required; otherwise FALSE.
//
//
// Remarks:
//   
//   
//     The master policy requires authentication 
//     but no password has been enrolled.
//   The minimum length set by policy is longer
//     than the minimum length from the last enrollment (LKG).
//   The required complexity level set by policy is 
//     greater than the minimum complexity level from the 
//     last enrollment (LKG).
//     
// 
BOOL PolicyRequiresUpdate(PASSWDINFO* ppwi, PASSWDPOLICY* pLKGPolicy)
{
    // Check for conditions that will force re-enrollment.
    BOOL fRequiresUpdate = !ppwi->bPasswordOn ||            // Password force is changing from off to on.
        ppwi->Policy.uMinLength > pLKGPolicy->uMinLength || // Or minimum length has increased.
        ppwi->Policy.uComplexity > pLKGPolicy->uComplexity; // Or complexity has increased.

    return fRequiresUpdate;
}


typedef BOOL (*PFN_VERIFYUSER)(const GUID *AEKey, LPCWSTR pwszAEDisplayText, HWND hwndParent, DWORD dwOptions, PVOID pExtended);

// Summary:
//   Calls the LASS version of VerifyUser().
//
// Parameters:
//  AEKey --  (Ignored) Authentication event identifier. 
//  The identifier corresponds to the type of authentication required. 
//  pwszAEDisplayText --  The text that will be displayed 
//  in the verification dialog. If this value is NULL or an empty string, 
//  the dialog keeps the same text used in 
//  VerifyUserStart.
//  hwndParent --  The handle to the parent window. If this
//  value is NULL, the desktop window will be used.
//  dwOptions --  Bitmask of possible options are shown 
//  in the following table:
//
//
//
//
//       Start a thread that will determine if policy changes require
//         us to force enrollment -- forces enrollment if required.
//
//
//  pExtended -- Unused. Must be NULL.
//
// Returns:
//   Returns TRUE if the user is verified, and FALSE if the user is not 
//   verified. To get extended error information, call GetLastError.
//
//
// Remarks:
//   This function is required because LAP has the same definition
//     for our own VerifyUser call.
// 
BOOL LASSVerifyUser(const GUID *AEKey, LPCWSTR pwszAEDisplayText, HWND hwndParent, DWORD dwOptions, PVOID pExtended)
{
    HINSTANCE hCoreDll;
    PFN_VERIFYUSER pfnVerifyUser;
    BOOL fVerified = FALSE; // Assume user isn't verified.

    // Need to make sure this calls into LASS instead of locally.
    // CoreDLL already statically linked -- no need to free later.
    hCoreDll = LoadLibrary(TEXT("coredll.dll")); 
    ASSERT(NULL != hCoreDll);
    
    ScopeGuard hCoreDllSc = ScopeProtect(hCoreDll, FreeLibrary);

    // Get point to VerifyUser function in CoreDLL.
    pfnVerifyUser = (PFN_VERIFYUSER)GetProcAddress(hCoreDll, 
        TEXT("VerifyUser"));
    if(NULL != pfnVerifyUser)
    {
        // Call VerifyUser.
        fVerified = pfnVerifyUser(AEKey, pwszAEDisplayText, 
            hwndParent, dwOptions, pExtended);
    }

    return fVerified;
}

// Summary:
//   Places a phone call to the specified number.
//
// Parameters:
//  pszNumber -- NULL-terminated string containing the 
//   phone number to call.
void MakeEmergencyCall(LPCTSTR pszNumber)
{
    // Set up the call with the specified number.
    PHONEMAKECALLINFO pmci;    
    memset(&pmci, 0, sizeof(pmci));
    pmci.cbSize = sizeof(pmci);
    pmci.dwFlags = PMCF_DEFAULT;
    pmci.pszDestAddress = pszNumber;

    // Make the phone call.
    (void)PhoneMakeCall(&pmci);
}

// Summary:
//    Sets the IDC_INFO control to show proper information.
//
// Parameters:
//  hwndDlg -- Dialog window handle. 
//  fIsEmergency -- If TRUE, an emergency number is currently 
//   entered.
//  fIsCodeword -- If TRUE, the dialog is the codeword 
//   dialog.
//  fClear -- If TRUE, clear the existing text before checking 
//   current state.
//  pszOverride -- Text specified here will override all others 
//   except emergency text.
//
// Remarks:
//   Set fClear=TRUE if you always want to update the text, even if 
//     it will be blank.
//
//
//
//
//     
//       3. Otherwise show override text if it exists in 
//         pszOverride.
//     
//     
//       4. Otherwise if this is not the codeword dialog, show 
//         the failure stats if available.
// 
void ShowInfo(HWND hwndDlg, BOOL fIsEmergency, BOOL fIsCodeword, BOOL fClear, LPCTSTR pszOverride)
{
    // Clear the control text first if specified.
    if(fClear)
    {
        (void)SetDlgItemText(hwndDlg, IDC_INFO, K_SZRESETTEXT);
    }

    if(fIsEmergency)
    {
        // We have an emergency phone number, so load emergency text.
        LPCTSTR pszEmergency = CELOADSZ(IDS_EMERGENCY_MODE_INFO);
        ASSERT(NULL != pszEmergency);
        (void)SetDlgItemText(hwndDlg, IDC_INFO, pszEmergency);
    }
    else if(NULL != pszOverride)
    {
        // Show override text if it was passed in.
        // This overrides everything except emergency number.
        (void)SetDlgItemText(hwndDlg, IDC_INFO, pszOverride);
    }
    else if(!fIsCodeword)
    {

        // If this is the password dialog, we show the 
        // number of failed attempts.
        DWORD dwAttempts = 0;
        DWORD dwSize = 0;
        // Only continue if the user has at least 1 failed attempt.
        if(LASSGetValue(LASS_VALUE_AUTH_FAILURE_COUNT, &dwAttempts, 
            sizeof(dwAttempts), &dwSize) && 0 < dwAttempts)
        {
            // Add 1 to get the current attempt number.
            // This should never get up to MAXDWORD.
            if(MAXDWORD > dwAttempts) 
            {
                dwAttempts++;
            }

            // Get device wipe threshold.
            DWORD dwThreshold = 0;
            // Only continue if threshold exists.
            if(LASSGetValue(LASS_VALUE_DEVICE_WIPE_THRESHOLD, &dwThreshold, 
                sizeof(dwThreshold), &dwSize) && 0 < dwThreshold)
            {
                // Calculate the space needed for the string.
                size_t cchAttempts = STRSAFE_MAX_CCH;
                LPCTSTR pszFormat = CELOADSZ(IDS_FAILEDATTEMPTS);
                ASSERT(NULL != pszFormat);

                // Get length of format string.
                 if(SUCCEEDED(StringCchLength(pszFormat, 
                                              STRSAFE_MAX_CCH - (2 * MAX_INT_LENGTH), &cchAttempts)))
                {
                    // Add space for two numbers and NULL terminator.
                    if (!safeIntUAdd (cchAttempts, (2 * MAX_INT_LENGTH) + 1, &cchAttempts)
                        || cchAttempts > STRSAFE_MAX_CCH)
                    {
                        cchAttempts = STRSAFE_MAX_CCH;
                    }
                }

                // Allocate buffer for the info string.
                LPTSTR pszAttempts = new (localalloc) TCHAR[cchAttempts];
                if(NULL != pszAttempts)
                {
                    ScopeGuard scg = ScopeProtect(pszAttempts, LocalFree);

                    // Format the number of attempts (x/y attempts).
                    if(SUCCEEDED(StringCchPrintf(pszAttempts, cchAttempts, 
                        pszFormat, dwAttempts, dwThreshold)))
                    {
                        // Update the control.
                        (void)SetDlgItemText(hwndDlg, IDC_INFO, 
                            pszAttempts);
                    }
                }
            }
        }
    }
}


// Summary:
//    Sets a timer to close/reset dialog if user hasn't made change
//    for a while.
//
// Parameters:
//  hwnd -- Handle to the current dialog.
//
// Remarks:
//   This function should be called whenever the user makes
//     a change to the dialog.
// 
void ResetIdleTimer(HWND hwnd)
{
    // Set a timer useing the password timeout value.
    (void)SetTimer(hwnd, IDT_IDLE_TIMEOUT, GetPasswordTimeout(), NULL);
}


// Summary:
//    Stops the timer from closing/resetting the dialog if user doesn't 
//    make changes for a while.
//
// Parameters:
//  hwnd -- Handle to the current dialog.
void KillIdleTimer(HWND hwnd)
{
    // Stop the timer for this window.
    (void)KillTimer(hwnd, IDT_IDLE_TIMEOUT);
}


// Summary:
//   Blocks the caller, running a message pump until the specified 
//   event is signaled.
//
// Parameters:
//  hEvent -- Handle to the event to wait for.
//  hwndDlg -- [Optional] Window handle of a dialog to handle 
//   messages for.
//
// Returns:
//   Returns the last result of the wait - WAIT_OBJECT_0 in the normal case.
//
//
// Remarks:
//   Waits for an event while dispatching messages for this thread.
//     If a dialog is specified, messages for that dialog are handled
//     specially.
// 
DWORD MsgBlockOnEvent(HANDLE hEvent, HWND hwndDlg)
{
    DWORD dwResult = 0;
    BOOL fBlock = TRUE;

    // Keep waiting until we set fBlock to FALSE.
    while(fBlock)
    {
        // Wait for the specified event or a message to process.
        dwResult = MsgWaitForMultipleObjectsEx(1, &hEvent, INFINITE, 
            QS_ALLINPUT, MWMO_INPUTAVAILABLE);

        switch(dwResult)
        {
            // The event was signalled.
            case WAIT_OBJECT_0:
            {
                // Normal exit
                fBlock = FALSE;
                break;
            }

            // Should not ever get here.
            case WAIT_TIMEOUT:
            case WAIT_FAILED:
            {
                // MsgWaitForMultipleObjectsEx returned an
                // unexpected value. ASSERT and stop blocking.
                ASSERT(FALSE);
                fBlock = FALSE;
                break;
            }

            // A message needs to be processed.
            case WAIT_OBJECT_0 + 1:
            default:
            {
                MSG msg;

                // Get the next message.
                while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    // First check if this message is for the passed-in
                    // dialog. If so, this function will handle 
                    // dispatching the message. If not, or if 
                    // hwndDlg = NULL, this call will fail and 
                    // we'll dispatch the message ourselves.
                    if(!IsDialogMessage(hwndDlg, &msg))
                    {
                        // Dispatch the message.
                        (void)TranslateMessage(&msg);
                        (void)DispatchMessage(&msg);
                    }
                }
                break;
            }
        }
    }

    return dwResult;
}

// Summary:
//   Displays the policy update dialog if necessary.
//
// Parameters:
//  hwndParent -- Parent window for the message. May be 
//   NULL.
//
// Returns:
//   Returns the result of DisplayMessage: S_OK if the 
//   message was displayed; otherwise E_FAIL.
//
//
// Remarks:
//   Displays the policy update message only if enrollment is 
//     required and the message hasn't been displayed yet during this
//     instance of the LAP.
// 
HRESULT DisplayPolicyUpdate(HWND hwndParent)
{
    HRESULT hr = S_OK;
    static BOOL s_fEnrollPromptDisplayed = FALSE;

    // Display a message if we're going to update because of policy
    if(g_fPolicyRequiresUpdate && !s_fEnrollPromptDisplayed)
    {
        hr = DisplayMessage(hwndParent, IDS_POLICYUPDATE_TITLE, 
            IDS_POLICYUPDATE);
        if(SUCCEEDED(hr))
        {
            // Update the static variable so 
            // this is only ever displayed once.
            s_fEnrollPromptDisplayed = TRUE;
        }
    }

    return hr;
}

// Summary:
//   Retrieves the hashing algorithm from the registry.
// 
//
// Returns:
//   An algorithm identifier. See wincrypt.h for supported values.
// 
ALG_ID GetHashAlgorithm()
{
    ALG_ID  calg_Algorithm = CALG_SHA1;  // Default to SHA1.
    HKEY    hKey = NULL;

    // Open the registry key.
    if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY,
        0, 0, &hKey))
    {
        ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

        ALG_ID calg_Temp = ALG_TYPE_ANY; // 0.
        DWORD  dwSize    = sizeof(calg_Temp);
    
        // Read the algorithm setting from the registry.
        if(ERROR_SUCCESS == RegQueryValueEx(hKey, K_SZALG, 
            NULL, NULL, (LPBYTE)&calg_Temp, &dwSize))
        {
            // Only hashing algorithms are supported.
            if(ALG_CLASS_HASH | calg_Temp)
            {
                // Check for unsupported algorithms.
                UINT uAlg = 0;
                for(; uAlg < ARRAYSIZE(c_rgUnsupportedAlgs); uAlg++)
                {
                    // Walk through array of unsupported algorithms.
                    if(c_rgUnsupportedAlgs[uAlg] == calg_Temp)
                    {
                        // This algorithm is unsupported.
                        break;
                    }
                }
                // Continue if we didn't match any of the 
                // unsupported algorithms.
                if(uAlg == ARRAYSIZE(c_rgUnsupportedAlgs))
                {
                    // This algorithm is fine.
                    // Set return value.
                    calg_Algorithm = calg_Temp;
                }
            }
        }
    }

    return calg_Algorithm;
}

BOOL GetSalt (BYTE *pbSalt, DWORD cbSize)
{
    HKEY    hKey = NULL;
    BOOL    fSalted = FALSE;

    // Open the registry key.
    if (RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY, 0, 0, &hKey) == ERROR_SUCCESS)
    {
        ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);

        DWORD dwSize = cbSize;

        // Read the salt from the registry.
        if (   RegQueryValueEx (hKey, K_SZSALT, NULL, NULL, pbSalt, &dwSize) == ERROR_SUCCESS
            && dwSize == cbSize)
        {
            fSalted = TRUE;
        }
    }
    return fSalted;
}


/// <summary>
///   Retrieves the provider type as specified in the registry, or PROV_RSA_FULL if the reg value does not exist.
/// </summary>
/// <returns>
///   Dword specifying a Provider Type as defined in wincrypt.
/// </returns>
DWORD GetProviderType()
{
    DWORD dwProvType = PROV_RSA_FULL; // Default is PROV_RSA_FULL
    DWORD dwRegProvType;

    // Read the provider type setting from the registry.
    if(SUCCEEDED(RegistryGetDWORD(HKEY_ROOT, K_SZLAPKEY, K_SZPROVTYPE, &dwRegProvType)))
    {
        dwProvType = dwRegProvType;
    }

    return dwProvType;
}

/// <summary>
///   Retrieves and stores in ppszName the crypt provider name as specified in the registry, or NULL if the reg value does not exist.
/// </summary>
/// <param name=ppszName>[out] Upon success, poinst to a string containing the provider name.
/// <returns>
/// S_OK if the provider name did not exist in the registry or if the provider name was successfully retrieved.
/// </returns>
HRESULT GetCryptoProviderName(__deref_out LPTSTR *ppszName)
{
    HRESULT hr = S_OK;
    HKEY    hKey = NULL;

    if (!ppszName)
        return E_INVALIDARG;

    *ppszName = NULL; // NULL will specify the default crypt service provider

    // Open the registry key.
    if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY,
        0, 0, &hKey))
    {
        DWORD  dwSize;
        DWORD dwType;
    
        // Read the provider type setting from the registry.
        if(ERROR_SUCCESS == RegQueryValueEx(hKey, K_SZPROVNAME, 
            NULL, &dwType, NULL, &dwSize) && 
            REG_SZ == dwType)
        {
            *ppszName = (LPTSTR) LocalAlloc(LMEM_FIXED, dwSize);
            if (!*ppszName)
            {
                hr = E_OUTOFMEMORY;
                goto Error;
            }

            if(ERROR_SUCCESS != RegQueryValueEx(hKey, K_SZPROVNAME, 
                                                NULL, NULL, (LPBYTE) *ppszName, &dwSize))
            {
                hr = E_FAIL;
                goto Error;
            }
        }
    }

Error:

    if (FAILED(hr) && NULL != *ppszName)
    {
        LocalFree(*ppszName);
        *ppszName = NULL; // avoid a potential double-free in the caller
    }

    if (hKey != NULL)
    {
        (void)RegCloseKey(hKey);
    }

    return hr;
}

/// <summary>
///   Initializes the CSP for use in subsequent calls. 
/// </summary>
/// <param name="dwProvType">[in] Specifies the type of 
///   provider to acquire.</param>
/// <param name="pszProvName">[in] Pointer to a null-terminated
///   string that specifies the name of the CSP to be used. 
///   If this parameter is NULL, the default provider 
///   for the specified type is used.</param>
/// <param name="phCryptProv">[out] Pointer to a handle 
///   to the acquired CSP. The caller must release this
///   CSP by calling CryptReleaseContext().</param>
/// <returns>
///   TRUE iff the provider successfully initializes and phCryptProv points to a valid crypt provider.
/// </returns>
/// <remarks>
///   <para>Attempts to initialize a provider with
///   the specified type and name. To succeed, the
///   provider name must be of the specified type
///   and correspond to an installed provider.</para>
/// </remarks>
BOOL InitProvider(DWORD dwProvType, __in_opt LPCTSTR pszProvName, __out HCRYPTPROV* phCryptProv)
{

    BOOL bInitSuccess = CryptAcquireContext(phCryptProv, NULL, pszProvName, dwProvType, 
        CRYPT_MACHINE_KEYSET | CRYPT_VERIFYCONTEXT | CRYPT_SILENT);

    // Attempt to acquire the context with an existing keyset.
    if(!bInitSuccess)
    {
        // Try again, this time with a new keyset.
        bInitSuccess = CryptAcquireContext(phCryptProv, NULL, pszProvName, dwProvType,
            CRYPT_MACHINE_KEYSET | CRYPT_VERIFYCONTEXT | 
            CRYPT_SILENT | CRYPT_NEWKEYSET);
    }

    return bInitSuccess;
}


HCRYPTPROV CreateCryptProv()
{
    // Get a handle to a CSP key container.
    LPTSTR pszProvName = NULL;
    if (FAILED(GetCryptoProviderName(&pszProvName)))
        return NULL;

    ScopeGuard pszProvNameSc = ScopeProtect(pszProvName, LocalFree);

    HCRYPTPROV hProv;
    if (!InitProvider(GetProviderType(), pszProvName, &hProv))
        return NULL;

    return hProv;
}


BOOL HashStringWorker(HCRYPTPROV hProv,
                      ALG_ID alg,
                      LPCTSTR pszString,
                      LPBYTE pbSalt,
                      DWORD cbSalt, 
                      BYTE ** ppbHash,
                      DWORD * pcbHash)
{
    if (!ppbHash || !pcbHash)
        return FALSE;

    // Get length of string, in bytes.
    size_t cbString = 0;
    if (FAILED(StringCbLength(pszString, (STRSAFE_MAX_CCH * sizeof(TCHAR)), &cbString)))
        return FALSE;

    // Allocate a buffer for salt + string
    DWORD cbPlainText = cbSalt + cbString;
    BYTE* pbPlainText = new (localalloc) BYTE[cbPlainText];
    if (!pbPlainText)
        return FALSE;

    ScopeGuard plainTextSc = ScopeProtect(pbPlainText, LocalFree);

    // Create the hash.
    HCRYPTHASH hHash;
    if(!CryptCreateHash(hProv, alg, 0, 0, &hHash))
        return false;

    ScopeGuard hHashSc = ScopeProtect(hHash, CryptDestroyHash);

    // concatenate the string and the salt
    memcpy(pbPlainText, pbSalt, cbSalt);
    memcpy(pbPlainText + cbSalt, pszString, cbString);

    // Add string to the hash.
    if(!CryptHashData(hHash, pbPlainText, cbPlainText, 0))
        return FALSE;

    // Get length of generated hash.
    DWORD dwHashLen = 0;
    DWORD cbDataSize = sizeof(dwHashLen);
    if(!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*) &dwHashLen, &cbDataSize, 0))
        return FALSE;

    // Allocate a buffer to hold the 
    // resulting hash.
    BYTE * hash = new (localalloc) BYTE[dwHashLen];
    if(!hash)
        return FALSE;

    ScopeGuard hashSc = ScopeProtect(hash, LocalFree);

    // Get the generated hash.
    if(!CryptGetHashParam(hHash, HP_HASHVAL, hash, &dwHashLen, 0))
        return FALSE;

    // success: set output parameters
    *ppbHash = hash;
    *pcbHash = dwHashLen;
    hashSc.release();

    return TRUE;
}


// Summary:
//   Generates a hash of the given string.
//
// Parameters:
//  pszString -- String to hash.
//  ppbHash -- If successful, points to a buffer
//   that contains the hash. Caller must free.
//  pcbHash -- [Optional] If successful, points to 
//   the size of the hash, in bytes.
//  ppbSalt -- [Optional] If NULL, the existing salt 
//   will be used. Otherwise a new salt will be generated for 
//   the hash and returned in this buffer. The allocated buffer
//   must be freed by the caller. The salt is always of 
//   size SALT_LENGTH.
//
// Returns:
//   TRUE if the hash was successfully created, otherwise FALSE.
// 

BOOL HashString (HCRYPTPROV hProv,
                 ALG_ID alg,
                 LPCTSTR pszString,
                 BYTE ** ppbHash,
                 DWORD * pcbHash,
                 LPBYTE * ppbSalt)
{
    // Allocate a buffer to hold the salt
    BYTE * pbTemp = new (localalloc) BYTE[SALT_LENGTH];
    if (!pbTemp)
        return FALSE;
    ScopeGuard pbTempSc = ScopeProtect(pbTemp, LocalFree);

    if (NULL != ppbSalt)  // Caller wants a new salt.
    {
        // Generate a random number for the salt
        if (!CryptGenRandom(hProv, SALT_LENGTH, pbTemp))
            return FALSE;
    }
    else
    {
        if (!GetSalt(pbTemp, SALT_LENGTH))
            return FALSE;
    }

    // Hash the string
    if (!HashStringWorker(hProv, alg, pszString, pbTemp, SALT_LENGTH, ppbHash, pcbHash))
        return FALSE;

    // Check if we created a new salt.
    if (NULL != ppbSalt)
    {
        *ppbSalt = pbTemp;
        pbTempSc.release();
    }

    return TRUE;
}

// Summary:
//   Retrieves the current state of the password.
// 
//
// Returns:
//   TRUE indicates that a password has been enrolled; otherwise, FALSE 
//   is returned.
// 
BOOL LapGetPasswordOn()
{
    // Default to most secure -- assume password exists.
    BOOL fPasswordOn = TRUE;
    HKEY hKey = NULL;
    LONG lResult;

    // Open the registry key.
    lResult = RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY,
        0, 0, &hKey);
    if(ERROR_SUCCESS == lResult)
    {
        // Check if the value exists.
        fPasswordOn = (ERROR_FILE_NOT_FOUND != 
            RegQueryValueEx(hKey, K_SZHASH, NULL, NULL, NULL, NULL));
    
        (void)RegCloseKey(hKey);
    }
    else if(ERROR_FILE_NOT_FOUND == lResult)
    {
        // Our reg key doesn't exist, so there's no password.
        fPasswordOn = FALSE;
    }

    return fPasswordOn;
}


LONG GetEncryptedPasswordHash (DATA_BLOB *pblobData)
{
    LONG            lResult;
    HKEY            hKey;
    DWORD           dwType;
    DATA_BLOB       blobTemp;

    // Open the registry key.
    lResult = RegOpenKeyEx (HKEY_ROOT, K_SZLAPKEY, 0, 0, &hKey);
    if (lResult == ERROR_SUCCESS)
    {
        // Get the data size.
        lResult = RegQueryValueEx (hKey, K_SZHASH, NULL, NULL, NULL, &blobTemp.cbData);
        if (lResult == ERROR_SUCCESS)
        {
            // Allocate a buffer for the data
            blobTemp.pbData = new (localalloc) BYTE[blobTemp.cbData];
            if (blobTemp.pbData)
            {
                // Get the existing password hash from the registry.
                lResult = RegQueryValueEx (hKey, K_SZHASH, NULL, &dwType, 
                                            blobTemp.pbData, &blobTemp.cbData);
                if (lResult == ERROR_SUCCESS && dwType == REG_BINARY)
                {
                    *pblobData = blobTemp;
                }
            }
            else
            {
                lResult = ERROR_OUTOFMEMORY;
            }
        }
        (void)RegCloseKey (hKey);
    }
    return lResult;
}

// Summary:
//   Validates a password by checking a string to determine if it matches 
//   the current password.
//
// Parameters:
//  pszPassword -- Pointer to a null-terminated string 
//   containing the password to verify. If no password has been
//   set, must be NULL or an empty string.
//
// Returns:
//   TRUE indicates a valid password; otherwise, the password is 
//   invalid. Returns TRUE if no password has been set and 
//   pszPasword is NULL or an empty string.
// 
BOOL LapCheckPassword(LPCTSTR pszPassword)
{
    BOOL  fValid = FALSE;
    HKEY  hKey = NULL;
    DWORD dwSize = 0;
    DWORD dwType = REG_NONE;
    BYTE* pbHashOriginal = NULL;
    BYTE* pbHashToCheck  = NULL;
    LONG  lResult;
    DATA_BLOB blobEncrypted = { 0 };
    DATA_BLOB blobHash = { 0 };

    lResult = GetEncryptedPasswordHash (&blobEncrypted);

    if (lResult == ERROR_SUCCESS)
    {
        // Decrypt the hash.
            if(CryptUnprotectData(&blobEncrypted,
                NULL, NULL, NULL, NULL, CRYPTPROTECT_SYSTEM,
                &blobHash))
            {   
                HCRYPTPROV hProv;
                DWORD hashAlg;
                if (GetStoredCryptoSettings(&hProv, &hashAlg))
                {
                    DWORD cbHash;

                    // Now generate a hash for the password to check.
                    if(HashString(hProv, hashAlg, pszPassword, &pbHashToCheck, 
                        &cbHash, NULL))
                    {
                        // The two hashes should ALWAYS be 
                        // the same length.
                        ASSERT(cbHash == blobHash.cbData);

                        // Simply compare the two hashes.
                        fValid = (0 == memcmp(pbHashToCheck, 
                            blobHash.pbData, cbHash));

                        // Clean up the buffer for the new hash.
                        (void)LocalFree(pbHashToCheck);
                    }

                    // Free the blob memory.
                    (void)LocalFree(blobHash.pbData);
                }
                ReleaseProvider(hProv);
            }
        }
        
    // Free the allocated buffer for the existing hash.
    (void)LocalFree(pbHashOriginal);
    
    if(ERROR_FILE_NOT_FOUND == lResult)
    {
        // There was no existing password, so return TRUE
        // if the passed-in string is NULL or empty.
        fValid = (NULL == pszPassword || 
            TEXT('\0') == pszPassword[0]);        
    }

    return fValid;
}


// Summary:
//   Deactivates the current password.
//
// Parameters:
//  pszPassword -- Pointer to a null-terminated string 
//   containing the existing password. If no password has been
//   set, must be NULL or an empty string.
//
// Returns:
//   TRUE indicates that the password has been successfully deactivated; 
//   otherwise, FALSE is returned. Returns TRUE if no password has been
//   set and pszPassword is NULL or an empty string.
//
//
// Remarks:
//   To deactivate the password, pszPassword must match the 
//     existing password.
// 
BOOL LapSetPasswordOff(LPCTSTR pszPassword)
{
    // By default, assume that we can't remove the password.
    BOOL bPasswordOff = FALSE;
    HKEY hKey = NULL;
    LONG lResult = -1;

    // First check this password to make sure it matches the existing.
    if(LapCheckPassword(pszPassword))
    {
        // Open the registry key.
        lResult = RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY, 
            0, 0, &hKey);
        if(ERROR_SUCCESS == lResult)
        {
            // Remove the password value from the registry.
            lResult = RegDeleteValue(hKey, K_SZHASH);
            (void)RegCloseKey(hKey);
        }

        // Consider this successful if the value was removed
        // or didn't exist.
        bPasswordOff = (ERROR_SUCCESS == lResult || 
            ERROR_FILE_NOT_FOUND == lResult);
    }

    return bPasswordOff;
}


// Summary:
//   Changes and/or activates the current password.
//
// Parameters:
//  pszOldPassword -- Pointer to a null-terminated string 
//   containing the existing password. Must be NULL or an empty
//   string if no previous password exists.
//  pszNewPassword -- Pointer to a null-terminated string 
//   containing the new password to activate. Cannot be NULL.
//
// Returns:
//   TRUE indicates that the password has been successfully activated; 
//   otherwise, FALSE is returned.
//
//
// Remarks:
//   To activate the password, pszPassword must match the 
//     existing password.
// 
BOOL LapSetPasswordOn(LPCTSTR pszOldPassword, LPCTSTR pszNewPassword)
{
    // By default, assume that we can't set the password.
    BOOL result = FALSE;
    BYTE* pbHash;
    DWORD cbHash;
    BYTE* pbSalt;
    HKEY hKey = NULL;

    ASSERT(NULL != pszNewPassword);

    // First check the old password to make sure it matches the existing.
    if(LapCheckPassword(pszOldPassword))
    {
        if (HCRYPTPROV hProv = CreateCryptProv())
        {
            ALG_ID hashAlg  = GetHashAlgorithm();

            // Generate a hash of the new password.
            if(HashString(hProv, hashAlg, pszNewPassword, &pbHash, &cbHash, &pbSalt))
            {
                CRYPT_DATA_BLOB blobEncrypted;
                CRYPT_HASH_BLOB blobHash;
                blobHash.cbData = cbHash;
                blobHash.pbData = pbHash;
                ZeroMemory(&blobEncrypted, sizeof(blobEncrypted));
                
                // Encrypt the hash.
                if(CryptProtectData(&blobHash, L"Password", NULL, NULL, 
                    NULL, CRYPTPROTECT_SYSTEM, &blobEncrypted))
                {
                    // Open the registry key.
                    if(ERROR_SUCCESS == RegCreateKeyEx(HKEY_ROOT, 
                        K_SZLAPKEY, 0, NULL, 0, 0, NULL, &hKey, NULL))
                    {
                        // Write the hash to the registry.
                        if(ERROR_SUCCESS == RegSetValueEx(hKey, K_SZHASH, 0, 
                                                          REG_BINARY, blobEncrypted.pbData, 
                                                          blobEncrypted.cbData))
                        {
                            result = SetStoredCryptoSettings(hProv, hashAlg);
                        }

                        // Write the salt to the registry.
                        (void)RegSetValueEx(hKey, K_SZSALT, 0, 
                            REG_BINARY, pbSalt, SALT_LENGTH); 

                        (void)RegCloseKey(hKey);
                    }

                    // Free the blob memory.
                    (void)LocalFree(blobEncrypted.pbData);
                }

                (void)LocalFree(pbHash);
                (void)LocalFree(pbSalt);
            }
            ReleaseProvider(hProv);
        }
    }

    return result;
}


// Summary:
//   Displays a simple MessageBox-like message with an OK button.
//
// Parameters:
//  hwndOwner -- Handle to the owner window of the message 
//   window to be created. If this parameter is NULL, the message window 
//   has no owner window. 
//  uTitle -- Specifies a resource ID usde for the message title.
//   If this parameter is 0 or does not point to a valid resource ID, a
//   blank title is used.
//  uMessage -- Specifies a resource ID that contains the 
//   message to be displayed.
//
// Returns:
//   SUCCESS if the message was displayed; otherwise FAILURE.
// 
HRESULT DisplayMessage(HWND hwndOwner, UINT uTitle, UINT uMessage)
{
    return DisplayMessageEx(hwndOwner, uTitle, 
        SafeCELOADSZ(uMessage));
}


// Summary:
//   Displays a simple MessageBox-like message with an OK button.
//
// Parameters:
//  hwndOwner -- Handle to the owner window of the message 
//   window to be created. If this parameter is NULL, the message window 
//   has no owner window. 
//  uTitle -- Specifies a resource ID usde for the message title.
//   If this parameter is 0 or does not point to a valid resource ID, a
//   blank title is used.
//  pszMessage -- Pointer to a null-terminated string that 
//   contains the message to be displayed. 
//
// Returns:
//   SUCCESS if the message was displayed; otherwise FAILURE.
// 
HRESULT DisplayMessageEx(HWND hwndOwner, UINT uTitle, LPCTSTR pszMessage)
{
    // Set up message info structure.
    MESSAGEINFO msgInfo;
    ZeroMemory(&msgInfo, sizeof(msgInfo));
    msgInfo.pszTitle = CELOADSZ(uTitle);
    msgInfo.pszMessage = pszMessage;
    msgInfo.biButtons = BUTTON_INFO_OK;   // Use one OK button.

    // Show the message.
    int nResult = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_MESSAGE),
        hwndOwner, MessageDlgProc, (LPARAM)&msgInfo);

    return -1 == nResult ? E_FAIL : S_OK;
}


// Summary:
//   Displays a simple MessageBox-like question with YES/NO buttons.
//
// Parameters:
//  hwndOwner -- Handle to the owner window of the message 
//   window to be created. If this parameter is NULL, the message window 
//   has no owner window. 
//  uTitle -- Specifies a resource ID usde for the message title.
//   If this parameter is 0 or does not point to a valid resource ID, a
//   blank title is used.
//  uMessage -- Pointer to a null-terminated string that 
//   contains the message to be displayed. 
//
// Returns:
//   S_OK if the user chose YES; S_FALSE if the user chose NO. FAILURE if
//   the message was not displayed.
// 
HRESULT DisplayQuestion(HWND hwndOwner, UINT uTitle, UINT uMessage)
{
    HRESULT hr = S_OK;
    MESSAGEINFO msgInfo;

    // Set up message info structure.
    ZeroMemory(&msgInfo, sizeof(msgInfo));
    msgInfo.pszTitle = CELOADSZ(uTitle);
    msgInfo.pszMessage = SafeCELOADSZ(uMessage);
    msgInfo.biButtons = BUTTON_INFO_YESNO; // Show yes/no buttons.
    
    // Show the question.
    int nReturn = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_MESSAGE),
        hwndOwner, MessageDlgProc, (LPARAM)&msgInfo);

    if(-1 == nReturn)
    {
        // Unknown failure.
        hr = E_FAIL;
    }
    else if(IDCANCEL == nReturn)
    {
        // User chose No.
        hr = S_FALSE;
    }

    return hr;
}


// Summary:
//   Displays a simple MessageBox-like message.
//
// Parameters:
//  hwndOwner -- Handle to the owner window of the message 
//   window to be created. If this parameter is NULL, the message window 
//   has no owner window. 
//  title   -- Specifies a string for the message title.
//  message -- Specified a string that contains the message to be displayed. 
//  dlgButtons -- Indicates the buttons to display. 
//   Either BUTTON_INFO_OK or BUTTON_INFO_YESNO.
//  heventDisplayed -- Handle to an event to signal
//   when the message box has been displayed. May be NULL.
//
// Returns:
//   -1 on failure, on success the result passed to the EndDialog function by the MessageDlgProc.
// 
int DisplayMessage(HWND owner, LPCTSTR title, LPCTSTR message, BUTTON_INFO dlgButtons, HANDLE heventDisplayed)
{
    MESSAGEINFO msgInfo = {0};
    msgInfo.pszTitle = title;
    msgInfo.pszMessage = message;
    msgInfo.biButtons = dlgButtons;
    msgInfo.heventDisplayed = heventDisplayed;

    return DialogBoxParam(g_hInst
                        , MAKEINTRESOURCE(IDD_MESSAGE)
                        , owner
                        , MessageDlgProc
                        , reinterpret_cast<LPARAM>(&msgInfo));
}


// Summary:
//   Determines if the device has a phone installed.
// 
//
// Returns:
//   TRUE if the device has a phone installed, otherwise FALSE.
//   Only checks once and caches the result.
// 
BOOL DeviceHasPhone()
{
    static BOOL s_fChecked  = FALSE;
    static BOOL s_fHasPhone = FALSE;
    HKEY hKey = NULL;

    // Only check once.
    if(!s_fChecked)
    {
        DWORD dwRadioPresent = 0;

        // Get the phone radio present value.
        (void)RegistryGetDWORD(SN_PHONERADIOPRESENT_ROOT, 
            SN_PHONERADIOPRESENT_PATH, SN_PHONERADIOPRESENT_VALUE, 
            &dwRadioPresent);

        // Compare value to radio present flag.
        s_fHasPhone = BOOLIFY(SN_PHONERADIOPRESENT_BITMASK | dwRadioPresent);

        // Update the static flag so this doesn't check again.
        s_fChecked = TRUE;
    }

    return s_fHasPhone;
}


// Summary:
//   Registers the window for notifications whenever the active call 
//   count changes.
//
// Parameters:
//  hwnd -- The window to notify.
//
// Returns:
//   If the registration succeeds, a handle to the notification request.
//   This handle should be closed using 
//   UnregisterCallNotifications.
//
//
// Remarks:
//   If the registration succeeds, the specified window will receive
//     a WM_APP_ACTIVECALLS message whenever the active call count 
//     changes.
// 
HREGNOTIFY RegisterCallNotifications(HWND hwnd)
{
    HREGNOTIFY hRegNotify = NULL;

    // Set up a notification for the active call count.
    (void)RegistryNotifyWindow(SN_PHONEACTIVECALLCOUNT_ROOT, 
        SN_PHONEACTIVECALLCOUNT_PATH, 
        SN_PHONEACTIVECALLCOUNT_VALUE, hwnd, 
        WM_APP_ACTIVECALLS, 0, NULL, &hRegNotify);            

    // Call the active-call handler at least once.
    // The call count may have already changed.
    (void)PostMessage(hwnd, WM_APP_ACTIVECALLS, 0, 0);

    return hRegNotify;
}


// Summary:
//   Stops notifications for changes to the active call count.
//
// Parameters:
//  hRegNotify -- The notification request returned from 
//   RegisterCallNotifications.
void UnregisterCallNotifications(HREGNOTIFY hRegNotify)
{
    if(NULL != hRegNotify)
    {
        // Cancel notification for the active call count.
        (void)RegistryCloseNotification(hRegNotify);
        hRegNotify = NULL;
    }
}


// Summary:
//   Determines the number of active calls.
// 
//
// Returns:
//   The number of currently-active calls on the device.
// 
DWORD GetActiveCallCount()
{
    // Default to no calls.
    DWORD cCalls = 0;

    // If the registry key doesn't exist, no calls have been recorded.
    (void)RegistryGetDWORD(SN_PHONEACTIVECALLCOUNT_ROOT, 
        SN_PHONEACTIVECALLCOUNT_PATH, 
        SN_PHONEACTIVECALLCOUNT_VALUE, &cCalls);

    return cCalls;
}


// Summary:
//   Perform layout for the message window.
//
// Parameters:
//   hwndDlg - Handle to the message window.
//
// Remarks:
//   This function is called during initialization and 
//   during the handling of the WM_SETTINGCHANGE message.
//   Displays the message text and ensures that all 
//   controls are placed properly in order to display 
//   as much of the message as possible.
//
//   Layout:
//   ____________________________________  (--Width of the dialog is fixed.
//   |  ____________________________    |
//   |  | Wait message text:        |   |  (--Message text fills up as much
//   |  | Lorem ipsum dolor sit     |   |     of the window as necessary.
//   |  | amet, consectetuer        |   |
//   |  | adipiscing elit.          |   |
//   |  |___________________________|   |
//   |                                  |
//   |   __________       __________    |  (--Buttons are YES/NO or a single
//   |   |  YES   |       |   NO   |    |     OK button (centered).
//   |   |________|       |________|    |     
//   |__________________________________|  (--Window has minimum height, and
//                                            expands up to the screen height.
void OnMessageLayout(__in HWND hwndDlg)
{
    RECT rcScreen, rcDialog;
    RECT rcMessage, rcButton;
    HWND hwndMessage = NULL;
    HWND hwndButton;
    int nDelta, nSpacing, nScreenHeight;
    int nOldHeight, nOldWidth;
    HDC hDC = NULL;
    HFONT hfontOld = NULL;
    LPTSTR pszMessage = NULL;
    DWORD  cchMessage;

    // Get size of screen.
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcScreen, NULL);
    nScreenHeight = RECTHEIGHT(rcScreen);

    // Get size of dialog.
    GetWindowRect(hwndDlg, &rcDialog);
    
    // Get current size of message control.
    hwndMessage = GetDlgItem(hwndDlg, IDC_MESSAGE_LABEL);
    GetWindowRect(hwndMessage, &rcMessage);
    MapWindowPoints(HWND_DESKTOP, hwndDlg, 
        reinterpret_cast<LPPOINT>(&rcMessage), 2);

    // We want to maintain the position of controls on
    // the dialog. Only the message text control and 
    // the window expand. Everything else is "anchored".
    // Determine the current spacing so we can maintain it.
    nOldHeight = RECTHEIGHT(rcMessage);
    nOldWidth  = RECTWIDTH(rcMessage);
    nSpacing = RECTHEIGHT(rcDialog) - nOldHeight;

    // Get the message text from the control.
    cchMessage = GetWindowTextLength(hwndMessage);
    DWordAdd(cchMessage, 1, &cchMessage);
    pszMessage = new TCHAR[cchMessage];
    GetWindowText(hwndMessage, pszMessage, cchMessage);

    // Get the font to use for drawing.
    hDC = GetDC(hwndMessage);
    hfontOld = reinterpret_cast<HFONT>(SelectObject(hDC, 
        reinterpret_cast<HGDIOBJ>(SendMessage(hwndMessage, 
        WM_GETFONT, 0, 0))));

    // Calculate size that the message text will take.
    DrawText(hDC, pszMessage, -1, &rcMessage, 
        DT_CALCRECT | DT_LEFT | DT_WORDBREAK | DT_NOCLIP);

    // Resize the message text if it's too long.
    if(nScreenHeight < RECTHEIGHT(rcMessage) + nSpacing)
    {
        rcMessage.bottom = rcMessage.top + nScreenHeight - 
            nSpacing;
    }

    // Resize the message control if it's below the minimum.
    if(MIN_MESSAGE_HEIGHT > RECTHEIGHT(rcMessage) + nSpacing)
    {
       rcMessage.bottom = rcMessage.top + MIN_MESSAGE_HEIGHT - 
            nSpacing;
    }

    // Calculate the delta between the old and new message text
    // height. It may be positive or negative.
    nDelta = RECTHEIGHT(rcMessage) - nOldHeight;

    // Resize the dialog.
    rcDialog.bottom += nDelta;
    SetWindowPos(hwndDlg, NULL, 0, 0, nOldWidth, 
        RECTHEIGHT(rcDialog), SWP_NOMOVE | SWP_NOZORDER);

    // Commit the size of the message text.
    SetWindowPos(hwndMessage, NULL, 0, 0, RECTWIDTH(rcMessage), 
        RECTHEIGHT(rcMessage), SWP_NOMOVE | SWP_NOZORDER);

    // Move the buttons to be at bottom of dialog.
    // Start with first (OK/YES) button.
    hwndButton = GetDlgItem(hwndDlg, IDOK);
    GetWindowRect(hwndButton, &rcButton);
    MapWindowPoints(HWND_DESKTOP, hwndDlg, 
        reinterpret_cast<LPPOINT>(&rcButton), 2);
    rcButton.top += nDelta;
    SetWindowPos(hwndButton, NULL, rcButton.left, rcButton.top, 
        0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // Next move the NO button.
    hwndButton = GetDlgItem(hwndDlg, IDCANCEL);
    GetWindowRect(hwndButton, &rcButton);
    MapWindowPoints(HWND_DESKTOP, hwndDlg, 
        reinterpret_cast<LPPOINT>(&rcButton), 2);
    rcButton.top += nDelta;
    SetWindowPos(hwndButton, NULL, rcButton.left, rcButton.top, 
        0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // Center the window on the screen
    (void)SetWindowPos(hwndDlg, NULL, 
        RECTWIDTH(rcScreen)/2 -  RECTWIDTH(rcDialog)/2,  // Left
        RECTHEIGHT(rcScreen)/2 - RECTHEIGHT(rcDialog)/2, // Top
        0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

    // Free the message string, if allocated.
    if(NULL != pszMessage)
    {
        delete[] pszMessage;
    }

    // Restore previous font selection.
    if(NULL != hfontOld)
    {
        SelectObject(hDC, (HGDIOBJ)hfontOld);
    }

    // Release device context.
    if(NULL != hDC)
    {
        ReleaseDC(hwndMessage, hDC);
    }
}


// Summary:
//   Dialog proc for the message dialog. Handles all messages.
//
// Parameters:
//  hwndDlg -- Handle to the dialog box. 
//  uMsg -- Specifies the message.
//  wParam -- Specifies additional message-specific 
//   information.
//  lParam -- Specifies additional message-specific 
//   information.
//
// Returns:
//   Returns TRUE if the message was handled; otherwise FALSE.
// 
BOOL MessageDlgProc(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam)
{
    BOOL fHandled = FALSE;
    MESSAGEINFO* pMsgInfo;

    // Get message structure.
    pMsgInfo = reinterpret_cast<MESSAGEINFO*>(
        GetWindowLong(hwndDlg, DWL_USER));
    if(WM_INITDIALOG != uMsg && NULL == pMsgInfo)
    {
        return fHandled;
    }

    // Handle specific message.
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            // Get passed-in message structure
            MESSAGEINFO* pMsgInfo = (MESSAGEINFO*)lParam;

            // Get handle to message control
            HWND hwndMessage = GetDlgItem(hwndDlg, IDC_MESSAGE_LABEL);
            ASSERT(NULL != hwndMessage);

            // If there's no message or message control, cancel immediately
            if(NULL == pMsgInfo || NULL == pMsgInfo->pszMessage || 
                TEXT('\0') == pMsgInfo->pszMessage[0] || NULL == hwndMessage)
            {
                EndDialog(hwndDlg, IDCANCEL);
            }
            else
            {
                (void)SetWindowLong(hwndDlg, DWL_USER, 
                    reinterpret_cast<DWORD>(pMsgInfo));

                // Set the prewipe window handle, if it's been reserved.
                // That signals that this message box is for that purpose.
                if(WndManager().IsReserved(LAP_WINDOW_PREWIPE))
                {
                    WndManager()[LAP_WINDOW_PREWIPE] = hwndDlg;

                    // Flag that we don't want to dismiss the pre-wipe
                    // message on deactivation.
                    pMsgInfo->fCloseOnActivationLoss = FALSE;

                }
                else
                {
                    // Make sure the auto-dismiss flag is set.
                    pMsgInfo->fCloseOnActivationLoss = TRUE;
                }

                // Set the title.
                if(NULL != pMsgInfo->pszTitle)
                {
                    (void)SetWindowText(hwndDlg, pMsgInfo->pszTitle);
                }

                // Set the message text
                SetWindowText(hwndMessage, pMsgInfo->pszMessage);

                // Rearrange the buttons if necessary.
                // We do yes/no by default, so shift if there's only one OK button.
                if(pMsgInfo->biButtons == BUTTON_INFO_OK)
                {
                    HWND hwndButton;
                    RECT rcButton, rcDialog;

                    // Get the YES/OK button.
                    hwndButton = GetDlgItem(hwndDlg, IDOK);

                    // Center the YES/OK button.
                    if(GetWindowRect(hwndButton, &rcButton) && 
                        0 != MapWindowPoints(HWND_DESKTOP, hwndDlg, 
                        reinterpret_cast<LPPOINT>(&rcButton), 2))
                    {
                        // Get the dialog client size.
                        GetClientRect(hwndDlg, &rcDialog);

                        rcButton.left = RECTWIDTH(rcDialog)/2 - 
                            RECTWIDTH(rcButton)/2;
                        SetWindowPos(hwndButton, NULL, 
                            rcButton.left, rcButton.top, 0, 0, 
                            SWP_NOSIZE | SWP_NOZORDER);
                    }

                    // Rename the 'yes' button to 'OK'.
                    SetWindowText(hwndButton, CELOADSZ(IDS_OK));

                    // Hide the 'no' button.
                    hwndButton = GetDlgItem(hwndDlg, IDCANCEL);
                    ShowWindow(hwndButton, SW_HIDE);
                }

                // Calculate the layout.
                OnMessageLayout(hwndDlg);

                // Play an exclamation or question beep based on button type.
                // This is the same function that the OS MessageBox API uses.
                // Note that by default these two sounds are the same.
                (void)MessageBeep(BUTTON_INFO_YESNO == pMsgInfo->biButtons ? MB_ICONQUESTION : MB_ICONEXCLAMATION);
                
                // Signal that the message window is ready.
                // If no event was passed in, this is a no-op.
                (void)SetEvent(pMsgInfo->heventDisplayed);
            }

            fHandled = TRUE;
            break;
        }
        
        case WM_COMMAND:
        {
            // Close the dialog as soon as we get any command.
            if(IDOK == LOWORD(wParam) || IDCANCEL == LOWORD(wParam))
            {
                // Clear the auto dismiss flag.
                // This prevents the WM_ACTIVATE handler
                // from overriding the return value.
                pMsgInfo->fCloseOnActivationLoss = FALSE;

                (void)EndDialog(hwndDlg, LOWORD(wParam));
                fHandled = TRUE;
            }

            break;
        }

        case WM_SETTINGCHANGE:
        {
            if(SETTINGCHANGE_RESET == wParam)
            {
                // The screen rotation may be changing.
                // Re-calculate the layout.
                OnMessageLayout(hwndDlg);
            }
            break;
        }

        case WM_ACTIVATE:
        {
            if(WA_INACTIVE == LOWORD(wParam))
            {
                // The dialog is being deactivated.
                // Check the auto-dismiss flag.
                if(pMsgInfo->fCloseOnActivationLoss)
                {
                    // Determine if the device is locked.
                    DWORD dwLockState = 0;
                    (void)RegistryGetDWORD(SN_LOCK_ROOT,
                        SN_LOCK_PATH, SN_LOCK_VALUE, &dwLockState);

                    // If the device is locked in any way, 
                    // close immediately.
                    if(0 != dwLockState)
                    {
                        // Dialog lost focus.
                        // Close with the default button.
                        EndDialog(hwndDlg, IDCANCEL);
                    }
                    else
                    {
                        NOTIFICATIONCONDITION condition;

                        // Register for a notification
                        // when the device locks.
                        condition.ctComparisonType = REG_CT_NOT_EQUAL;
                        condition.dwMask = 0xffffffff;
                        condition.TargetValue.dw = 0;
                        (void)RegistryNotifyWindow(SN_LOCK_ROOT,
                            SN_LOCK_PATH, SN_LOCK_VALUE, hwndDlg,
                            WM_APP_LOCK, 0, &condition, 
                            &(pMsgInfo->hNotify));
                    }
                }
            }
            else
            {
                // The message box is being activated.
                // If we were waiting for a lock notification, stop it.
                if(NULL != pMsgInfo->hNotify)
                {
                    (void)RegistryCloseNotification(pMsgInfo->hNotify);
                    pMsgInfo->hNotify = NULL;
                }

                // Push the SIP down, we don't need it.
                (void)SHSipPreference(hwndDlg, SIP_DOWN);
            }

            break;
        }

        case WM_APP_LOCK:
        {
            // The lock state has changed and the dialog is inactive.
            // Stop the notification.
            (void)RegistryCloseNotification(pMsgInfo->hNotify);
            pMsgInfo->hNotify = NULL;

            // Close with the default button.
            EndDialog(hwndDlg, IDCANCEL);

            break;
        }
    }

    return fHandled;
}


// Summary:
//   Map a virtual key code to a valid phone key if a mapping exists.
//
// Parameters:
//  uvKey -- Virtual key identifier.
//
// Returns:
//   The character represented by uvKey. The only virtual keys that are
//   mapped specially are VK_TSTAR ('*') and VK_TPOUND('#').
// 
TCHAR MapVKeyToChar(UINT uvKey)
{
    TCHAR chDigit = 0;

    switch(uvKey)
    {
        case VK_TSTAR:
        {
            chDigit =  TEXT('*');
            break;
        }
        case VK_TPOUND:
        {
            chDigit =  TEXT('#');
            break;
        }
        default:
        {
            chDigit = uvKey;
            break;
        }
    }

    return chDigit;
}

//  Concatenate two strings.
//  The output string is null-terminated.
//  The space for the output string is automatically allocated.
//  The caller is responsible of releasing it with LocalFree.
//
HRESULT Concat(LPCTSTR str1, LPCTSTR str2, /*out*/ TCHAR ** output)
{
    size_t len1;
    HRESULT hr = StringCchLength(str1, STRSAFE_MAX_CCH, &len1);
    if (FAILED(hr)) return hr;

    size_t len2;
    hr = StringCchLength(str2, STRSAFE_MAX_CCH, &len2);
    if (FAILED(hr)) return hr;

    size_t lenS;
    if (!safeIntUAdd(len1, len2, &lenS))
    {
        return E_OUTOFMEMORY;
    }

    if (!safeIntUAdd(lenS, 1, &lenS)
        || lenS > STRSAFE_MAX_CCH)
    {
        return E_OUTOFMEMORY;
    }

    TCHAR * outputS = new (localalloc) TCHAR[lenS];
    if (!outputS)
    {
        return E_OUTOFMEMORY;
    }

    hr = StringCchCopyN(outputS, lenS, str1, len1);
    if (FAILED(hr)) return hr;

    hr = StringCchCopyN(outputS + len1, lenS - len1, str2, len2);
    if (FAILED(hr)) return hr;

    outputS[lenS - 1] = L'\0';

    // Remove leading carriage return, if necessary.
    if(TEXT('\n') == outputS[0])
    {
        size_t cbLen;
        if(safeIntUMul(lenS, sizeof(TCHAR), &cbLen))
        {
            // Move each character one to the front.
            memmove(outputS, outputS + 1, 
                cbLen - sizeof(TCHAR));
        }
    }

    *output = outputS;

    return S_OK;
}


/// <summary>
///   Retrieves the crypto provider and algorithm
///   used when the current password was stored.
/// </summary>
/// <param name="phCryptProv">[out] Handle to the cryptographic
///   service provider used to hash the current password.
///   Caller must release using CryptReleaseContext().</param>
/// <param name="pdwCryptHashAlg">[out] Algorithm ID of the 
///   hashing algorithm used to hash the current password.</param>
/// <returns>
///   BOOL. TRUE if a handle to the cryptographic provider was 
///   successfully acquired, otherwise FALSE.
/// </returns>
/// <remarks>
///   Determines the settings used when the current password was
///   hashed by reading the stored values from the registry key
///   HKLM\Comm\Security\LASSD\LAP\lap_pw. The algorithm is 
///   populated from the LAPHashAlgorithm registry value. 
///   The CSP is acquired using the provider type and name stored
///   in the LAPProviderType and LAPProviderName registry values.
///   If any of the values are missing, the default values are used.
/// </remarks>
BOOL GetStoredCryptoSettings(__out HCRYPTPROV* phCryptProv, __out DWORD* pdwCryptHashAlg)
{
    HRESULT     hr = S_OK;
    LONG        lResult;
    HKEY        hKey             = NULL;
    DWORD       dwType;
    HCRYPTPROV  hCryptProv       = NULL;
    LPTSTR      pszCryptProvName = NULL;
    DWORD       cbCryptProvName  = 0;
    DWORD       dwCryptProvType  = 0;
    DWORD       dwCryptHashAlg   = 0;

    // Read in the crypto settings from the registry.
    // These were stored along with the password.
    // These settings should exist if a password exists,
    // but if for some reason they're missing, we'll continue
    // anyway and use the current defaults.
    lResult = RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY, 0, 0, &hKey);
    if(ERROR_SUCCESS == lResult)
    {
        // Get the hash algorithm.
        // Ignore the return value. If we don't get a
        // valid value here, it will be filled
        // in with the default later.
        (void)RegistryGetDWORD(hKey, NULL, 
            K_SZHASHALG, &dwCryptHashAlg);

        // Get the crypto provider type.
        (void)RegistryGetDWORD(hKey, NULL, 
            K_SZPROVTYPE, &dwCryptProvType);

        // Get the crypto provider name size.
        lResult = RegQueryValueEx(hKey, K_SZPROVNAME, 
            NULL, NULL, NULL, &cbCryptProvName);
        if(ERROR_SUCCESS == lResult)
        {
            pszCryptProvName = reinterpret_cast<LPTSTR>(
                LocalAlloc(LMEM_FIXED, cbCryptProvName));
        }

        // Get the actual provider name.
        if(NULL != pszCryptProvName)
        {
            lResult = RegQueryValueEx(hKey, K_SZPROVNAME, NULL, 
                &dwType, reinterpret_cast<BYTE*>(pszCryptProvName), 
                &cbCryptProvName);
            if(ERROR_SUCCESS != lResult || REG_SZ != dwType)
            {
                // Failure. Reset the provider name variable.
                (void)LocalFree(pszCryptProvName);
                pszCryptProvName = NULL;
            }
        }
    }
    
    // Check if we need to use defaults 
    // for any of these settings as a fallback.
    if(0 == dwCryptHashAlg)
    {
        dwCryptHashAlg = GetHashAlgorithm();
    }
    if(0 == dwCryptProvType)
    {
        dwCryptProvType = GetProviderType();
    }
    if(NULL == pszCryptProvName)
    {
        hr = GetCryptoProviderName(&pszCryptProvName);
        if (FAILED(hr)) goto Error;
    }

    // Try to initialize a provider with these settings.
    if(!InitProvider(dwCryptProvType, pszCryptProvName, &hCryptProv))
    {
        hr = E_FAIL;
        goto Error;
    }

    // Success. Set output arguments.
    *pdwCryptHashAlg = dwCryptHashAlg;
    *phCryptProv = hCryptProv;
    hCryptProv = NULL;

Error:
    // Close reg key if we opened it.
    if(NULL != hKey)
    {
        (void)RegCloseKey(hKey);
    }

    // Free CSP if function failed.
    if(NULL != hCryptProv)
    {
        (void)CryptReleaseContext(hCryptProv, 0);
    }

    // Free allocated string buffer.
    // No-op if it wasn't allocated.
    (void)LocalFree(pszCryptProvName);

    return SUCCEEDED(hr);
}


/// <summary>
///   Stores the crypto provider and algorithm
///   used to obscure the current password.
/// </summary>
/// <param name="hCryptProv">[in] Handle to the cryptographic
///   service provider used to hash the current password.</param>
/// <param name="dwCryptHashAlg">[in] Algorithm ID of the 
///   hashing algorithm used to hash the current password.</param>
/// <returns>
///   BOOL. TRUE if the cryptographic settings in use were
///   successfully stored in the registry, otherwise FALSE.
/// </returns>
/// <remarks>
///   Stores these values in the registry so they can be retrieved
///   later when checking the password. See 
///   <see cref="GetStoredCryptoSettings" /> for details.
/// </remarks>
BOOL SetStoredCryptoSettings(__in HCRYPTPROV hCryptProv, DWORD dwCryptHashAlg)
{
    HRESULT hr = S_OK;
    DWORD   cbData;
    HKEY    hKey = NULL;
    DWORD   dwCryptProvType;
    LPTSTR  pszCryptProvName = NULL;
    DWORD   cbCryptProvName = 0;

    // Get encryption provider type from the provider handle.
    cbData = sizeof(dwCryptProvType);
    if (!CryptGetProvParam(hCryptProv, PP_PROVTYPE, 
                           reinterpret_cast<BYTE*>(&dwCryptProvType), 
                           &cbData, 0))
    {
        hr = E_FAIL;
        goto Error;
    }

    // Get length of encryption provider name.
    if (!CryptGetProvParam(hCryptProv, PP_NAME, 
        NULL, &cbCryptProvName, 0))
    {
        hr = E_FAIL;
        goto Error;
    }

    // Allocate buffer for encryption provider name.
    pszCryptProvName = static_cast<LPTSTR>(LocalAlloc(LMEM_FIXED, 
        cbCryptProvName));
    if (!pszCryptProvName)
    {
        hr = E_OUTOFMEMORY;
        goto Error;
    }

    // Retrieve encryption provider name.
    if (!CryptGetProvParam(hCryptProv, PP_NAME, 
        reinterpret_cast<BYTE*>(pszCryptProvName), 
        &cbCryptProvName, 0))
    {
        hr = E_FAIL;
        goto Error;
    }

    // Open the reg key where the password is stored.
    if (ERROR_SUCCESS != 
        RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY, 0, 0, &hKey))
    {
        DWORD error = GetLastError();
        hr = HRESULT_FROM_WIN32(error);
        goto Error;
    }

    // Store the hash algorithm.
    hr = RegistrySetDWORD(hKey, NULL, 
        K_SZHASHALG, dwCryptHashAlg);
    if (FAILED(hr))
        goto Error;

    // Store the crypto provider type.
    hr = RegistrySetDWORD(hKey, NULL, 
        K_SZPROVTYPE, dwCryptProvType);
    if (FAILED(hr))
        goto Error;

    // Store the crypto provider name.
    hr = RegistrySetString(hKey, NULL,
        K_SZPROVNAME, pszCryptProvName);
    if (FAILED(hr))
        goto Error;

Error:
    // Close reg key if we opened it.
    if(NULL != hKey)
    {
        (void)RegCloseKey(hKey);
    }

    // Free allocated string buffer.
    // No-op if it wasn't allocated.
    (void)LocalFree(pszCryptProvName);

    return SUCCEEDED(hr);
}
