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
#include "enroll.h"
#include "verify.h"
#include "codeword.h"
#include <aygshell.h>

HANDLE      g_hPolicyThread = NULL;
HANDLE      g_hAuthResetThread = NULL;
CRITICAL_SECTION g_csAuthResetSetup;


// Summary:
//   Sent to a LAP when it is activated. Performs necessary 
//   initialization. 
//
// Parameters:
//  il -- Pointer to an InitLap structure. Must not be NULL.
//
// Returns:
//   Returns TRUE if initialization succeeded, otherwise FALSE.
//
//
// Remarks:
//   This function initializes a LAP when it is activated by the 
//     LASS. It also enables a LAP to indicate its capabilities.
//   In debug, this function checks the size of the
//     passed-in structure to determine if the LASS version matches up.
//
//
//
//
//     
//     
//       3. Start a thread that will determine if policy changes require
//         us to force enrollment -- forces enrollment if required.
//
//
//
//
//     
//       Sets g_hPolicyThread to the created thread handle. This handle
//         should be closed in DeinitLAP.
//
//
BOOL InitLAP(InitLap* il) 
{

    // Check these in debug, but we don't want to stop
    //  working if these conditions aren't met
    ASSERT(NULL != il && il->size >= sizeof(InitLap));

    // Initialize LAP window handles
    for(uint i=0; i <= LAP_WINDOW_LAST; i++)
    {
        WndManager().Clear(i);
    }

    // Initialize UI control classes that we will need.
    BOOL bInitialized = SHInitExtraControls(); 

    // Initialize critical section.
    InitializeCriticalSection(&g_csAuthResetSetup);

    // Check if policy requires us to force enrollment
    g_hPolicyThread = CreateThread(NULL, 0, PolicyThreadProc, NULL, 0, NULL);
    ASSERT(NULL != g_hPolicyThread);

    return bInitialized;
}


// Summary:
//   Sent to a LAP when it is deactivated. Performs necessary 
//   cleanup.
//
//
// Remarks:
//   This function is called from the LASS when the LAP is being 
//     unloaded.
//   Waits for the policy thread created in InitLAP to 
//     complete.
// 
void DeinitLAP()
{
    // Make sure we're not forcing re-enrollment right now
    // If we allow unload we'll crash if this thread is still running
    if(NULL != g_hPolicyThread)
    {
        (void)WaitForSingleObject(g_hPolicyThread, INFINITE);
        (void)CloseHandle(g_hPolicyThread);
        g_hPolicyThread = NULL;
    }

    // Make sure we're not running AuthReset setup.
    // If we allow unload we'll crash if this thread is still running.
    if(NULL != g_hAuthResetThread)
    {
        (void)WaitForSingleObject(g_hAuthResetThread, INFINITE);
        (void)CloseHandle(g_hAuthResetThread);
        g_hAuthResetThread = NULL;
    }

    // Free the critical section resources.
    DeleteCriticalSection(&g_csAuthResetSetup);
}


// Summary:
//   Represents a single verification attempt for a user. 
//
// Parameters:
//  AEKey --  (Ignored) Authentication event identifier. 
//   The identifier corresponds to the type of authentication required. 
//  pwszAEDisplayText --  The text that will be displayed 
//   in the verification dialog. If this value is NULL or an empty string, 
//   the dialog keeps the same text used in 
//  VerifyUserStart.
//  hwndParent --  (Ignored) The handle to the parent window. 
//  dwOptions --  Bitmask of possible options are shown 
//   in the following table:
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
//   This function authenticates the user to the LASS. May be with
//     or without UI. 
//   If the user cancelled the verification request, GetLastError 
//     will return ERROR_CANCELLED. If the user failed authentication, 
//     GetLastError returns ERROR_NOT_AUTHENTICATED.
//   Must be preceded by VerifyUserStart, and succeeded 
//     by VerifyUserStop.
// 
BOOL VerifyUser(const GUID *AEKey, LPCWSTR pwszAEDisplayText, HWND hwndParent, 
                     DWORD dwOptions, PVOID pExtended)
{
    UNREFERENCED_PARAMETER(hwndParent);

    HRESULT hr = E_ABORT; // E_ABORT means cancel (default)

    // Check here if there's a cancel pending. If so, skip VerifyUser and 
    // return E_ABORT (cancelled). This is used by LAPCancelVerifySequence.
    if(E_ABORT != g_hrPasswordOK)
    {
        // No UI fails if we have to update policy.
        if(!g_fPolicyRequiresUpdate || !(dwOptions & VU_NO_UI))
        {
            // If the password isn't active or is NULL 
            // then we only need to handle forced enrollment.
            if(!LapGetPasswordOn())
            {
                hr = S_OK;
            }
            else
            {
                // If no UI, skip VerifyUser.
                if(!(dwOptions & VU_NO_UI))
                {
                    // Skip checking if VerifyUserStart didn't succeed.
                    if(WndManager().IsStored(LAP_WINDOW_VERIFY))
                    {
                        hr = DoVerify(pwszAEDisplayText);
                    }
                }
            }
        }
    }

    // Handle forced enrollment if password succeeded.
    if(g_fPolicyRequiresUpdate && SUCCEEDED(hr) && 
        !WndManager().IsStored(LAP_WINDOW_ENROLL))
    {
        WndManager().Reserve(LAP_WINDOW_ENROLL);
        
        // Use the verification dialog as the parent.
        if(!DoEnrollment(WndManager()[LAP_WINDOW_VERIFY], TRUE))
        {
            // If forced enrollment fails, consider it a cancel.
            hr = E_ABORT;
        }

        WndManager().Clear(LAP_WINDOW_ENROLL);
    }

    // Make sure the cached password is cleared before we return, 
    // unless we are being called for enrollment
    // which needs it for changing the password
    if(!WndManager().IsStored(LAP_WINDOW_ENROLL))
    {
        FreePasswordForEnrollment();
    }
        
    if(SUCCEEDED(hr))
    {
        SetLastError(0);
    }
    else if(E_ABORT == hr)
    {
        SetLastError(ERROR_CANCELLED);
    }
    else
    {
        SetLastError(ERROR_NOT_AUTHENTICATED);
    }

    return SUCCEEDED(hr);    
}


// Summary:
//   Sets up the dialog for verification attempts.
//
// Parameters:
//  AEKey --  (Ignored) Authentication event identifier. 
//   The identifier corresponds to the type of authentication required. 
//  pwszAEDisplayText --  The text that will be displayed 
//   in the verification dialog. If this value is NULL, the default text will
//   be used.
//  hwndParent --  (Ignored) The handle to the parent window.
//  dwOptions --  Bitmask of possible options are shown 
//   in the following table:
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
// Remarks:
//   Before LASS makes the first VerifyUser call, 
//     it calls VerifyUserStart. May be followed by multiple VerifyUser 
//     calls. Must be followed VerifyUserStop.
//   After creating the dialog, this function displays the 
//     policy update message if necessary.
//   Creates the verify dialog and stores the handle in 
//     for LAP_WINDOW_VERIFY. Since there is no return value, 
//     LAP_WINDOW_VERIFY can be checked in subsequent functions  
//     to determine if the dialog creation succeeded.
// 
void VerifyUserStart(const GUID *AEKey, LPCWSTR pwszAEDisplayText, HWND hwndParent, 
                     DWORD dwOptions, PVOID pExtended)
{
    UNREFERENCED_PARAMETER(hwndParent);

    // The dialog should not have been created yet
    ASSERT(!WndManager().IsStored(LAP_WINDOW_VERIFY));

    // Don't create the dialog if there's no password to check or we're not using UI.
    if(LapGetPasswordOn() && !(dwOptions & VU_NO_UI))
    {
        // Prepare the verification dialog.
        // Always pass NULL as the parent window. This is because 
        // we can have multiple VerifyUser calls come in using the  
        // dialog we are about to create, all from different 
        // applications who may pass their parent windows. 
        // If LASS returns from the first app's call to VerifyUser
        // but we keep this dialog around for a subsequent call that
        // was queued up from another application, this will cause
        // window-ordering issues at best, and a crash at worst.
        if(SUCCEEDED(DoVerifyUserStart(NULL, pwszAEDisplayText)))
        {
            // Show policy update message now if necessary
            (void)DisplayPolicyUpdate(WndManager()[LAP_WINDOW_VERIFY]);

            // Because the verify window has a NULL parent, we have to 
            // make sure it is foreground.
            (void)SetWindowToTop(LAP_WINDOW_VERIFY);
        }
    }
}


// Summary:
//   Destroys the dialog for verification attempts.
//
//
// Remarks:
//   After the LASS makes the last 
//     VerifyUser (LAP) call, it calls VerifyUserStop. 
//     Must be preceded by VerifyUserStart.
// 
void VerifyUserStop()
{
    DoVerifyUserStop();
}


// Summary:
//   Brings the current LAP window to the foreground.
//
// Remarks:
//   This function requests the LAP to bring the verification  
//     dialog to the top of the z order, including any owned 
//     windows. It is called by LASS during multiple simultaneous 
//     application calls to VerifyUser, to prevent the LAP UI from 
//     being displayed under the application UI in the z-order.
//   The WS_EX_ABOVESTARTUP bit must have been set on the dialogs
//     if you want them to be able to be seen when startui is 
//     active (after power suspend, etc).
//
void VerifyUserToTop()
{
    // Set the verify window to top.
    // This will bring up all owned windows, too.
    (void)SetWindowToTop(LAP_WINDOW_VERIFY);
}


// Summary:
//   Displays the password settings.
//
// Parameters:
//  hwndParent --  Handle to the parent window.  If NULL, 
//   the desktop window will be used
//  dwOptions --  (Ignored) Bitmask specifying options for 
//   dialog creation. The only supported value is VU_HANDLE_MASTER_KEY, 
//   which specifies handling for master key encryption and decryption 
//   if master key encryption and decryption are supported.
//
// Returns:
//   Returns TRUE on success; otherwise FALSE.
//
//
// Remarks:
//   LAPCreateEnrollmentConfigDialog is called by the LASS on 
//     behalf of an application calling CreateEnrollmentConfigDialog. 
//   If an enrollment dialog is already displayed, brings that
//     dialog to the foreground and returns FALSE.
//   Calls VerifyUser (in LASS) to authenticate the user
//     before allowing access to the password settings.
// 
BOOL LAPCreateEnrollmentConfigDialog(HWND hwndParent, DWORD dwOptions)
{
    BOOL fRet = FALSE;

    // Try to set the verification window topmost.
    // If we're already enrolling and we're stopped
    // in verification, this will keep us going.
    // If we're not in enrollment and verification is
    // active, this won't hurt us.
    (void)SetWindowToTop(LAP_WINDOW_VERIFY);

    // If we're already enrolling, show that window and exit
    if(SetWindowToTop(LAP_WINDOW_ENROLL))
    {
        return FALSE;
    }

    // Require the user to authenticate
    WndManager().Reserve(LAP_WINDOW_ENROLL); // Reserve this window exclusively
    if(LASSVerifyUser(&AE_EVERY_TIME, CELOADSZ(IDS_AE), hwndParent, 0, NULL))
    {
        fRet = DoEnrollment(hwndParent, FALSE);
    }   
    WndManager().Clear(LAP_WINDOW_ENROLL); // Clear the window handle

    FreePasswordForEnrollment();

    return fRet;
}


// Summary:
//    Prompts the user for the specified codeword.
//
// Parameters:
//  hwndParent --  (Ignored) Handle to the parent window.
//  pwszCodeword --  Pointer to the codeword to be entered 
//   for verification. This value can also be NULL or an empty string. 
//
// Returns:
//   Returns TRUE on success; otherwise FALSE.
//
//
// Remarks:
//   This optional function displays a dialog prompting for 
//     pwszCodeword to be entered. 
//   To ensure that a 'live' user is authenticating with the device, 
//     the user can periodically be prompted to enter a codeword for 
//     verification.
// 
BOOL LAPDisplayCodeword(HWND hwndParent, LPCWSTR pwszCodeword)
{
    UNREFERENCED_PARAMETER(hwndParent);

    BOOL fRet = FALSE;

    // If we're already displaying the codeword, show that window and exit
    if(!SetWindowToTop(LAP_WINDOW_CODEWORD))
    {
        WndManager().Reserve(LAP_WINDOW_CODEWORD); // Reserve this window exclusively
        // Use the verify dialog as the parent.
        fRet = DoCodeword(WndManager()[LAP_WINDOW_VERIFY], pwszCodeword);
        WndManager().Clear(LAP_WINDOW_CODEWORD); // Clear the window handle
    }

    return fRet;
}


// Summary:
//    Displays the pre-wipe message.
//
// Parameters:
//  hwndParent --  (Ignored) Handle to the parent window.
//
// Returns:
//   Returns TRUE on success; otherwise FALSE.
//
//
// Remarks:
//   This optional function displays a dialog informing the user 
//     that the next failed authentication attempt will trigger a device 
//     wipe. 
//   It is important to inform the user that the next failed 
//     verification will cause their device to be wiped. This function 
//     is called by LASS when the user has only one more verification 
//     attempt available.
//   Emergency dialing is not available during this call. The
//     user must dismiss this dialog in order to place emergency calls.
// 
BOOL LAPDisplayPreWipe(HWND hwndParent)
{
    UNREFERENCED_PARAMETER(hwndParent);

    BOOL fRet = FALSE;
        
    // If we're already displaying a message, show that window and exit
    if(!SetWindowToTop(LAP_WINDOW_PREWIPE))
    {
        WndManager().Reserve(LAP_WINDOW_PREWIPE); // Reserve this window exclusively
        // Use the verify dialog as the parent.
        fRet = SUCCEEDED(DisplayMessage(WndManager()[LAP_WINDOW_VERIFY], 
            IDS_PREWIPE_TITLE, IDS_PREWIPE));
        WndManager().Clear(LAP_WINDOW_PREWIPE); // Clear the window handle
    }

    return fRet;
}


// Summary:
//    Locks the user out from the device UI for a specified duration.
//
// Parameters:
//  hwndParent --  (Ignored) Handle to the parent 
//   window.
//  pwszDisplayText --  Pointer to the text for the LAP 
//   to display. If this value is NULL or an empty string, the lockout 
//   keeps the same text used in VerifyUserStart.
//  cSecondsToLockout --  Amount of time, in seconds, to 
//   block the user from continuing.
//
// Returns:
//   Returns TRUE on success; otherwise FALSE.
//
//
// Remarks:
//   This optional function is called when the device needs to block 
//     a user from continuing for a set period of time. Used with exponential 
//     backoff.
//   If an error occurs displaying the UI, this function will
//     perform a simple sleep for the specified number of seconds.
//   
// 
BOOL LAPLockoutUser(HWND hwndParent, LPCWSTR pwszDisplayText, DWORD cSecondsToLockout)
{
    UNREFERENCED_PARAMETER(hwndParent);

    BOOL fRet = TRUE;

    if(WndManager().IsStored(LAP_WINDOW_VERIFY) && IsWindow(WndManager()[LAP_WINDOW_VERIFY]))
    {
        HWND hwnd = WndManager()[LAP_WINDOW_VERIFY];

        // Set the display text if it was passed in
        if(NULL != pwszDisplayText && TEXT('\0') != pwszDisplayText[0])
        {
            (void)SetDlgItemText(hwnd, IDC_VERIFY, pwszDisplayText);
        }   

        // Add one second to the lockout because the first time it hits
        // will be immediate and will deduct one second before displaying.
        if(MAXDWORD == cSecondsToLockout)
        {
            // Can't add 1. Just use as is and don't send
            // an immediate message.
            g_csecLockout = cSecondsToLockout;
        }
        else
        {
            g_csecLockout = cSecondsToLockout + 1;

            // Send the first timer message ourselves so it will start immediately.
            // The first timer will fire after 1 second.
            (void)SendMessage(hwnd, WM_TIMER, IDT_LOCKOUT, 0);
        }
        
        // Set the timer (exponential backoff)
        (void)SetTimer(hwnd, IDT_LOCKOUT, 1000, NULL);

        // Wait for the lockout complete event (signaled by verify dialog)
        if(NULL != g_hEventLockoutDone)
        {
            (void)MsgBlockOnEvent(g_hEventLockoutDone, hwnd);
        }

        // At this point the lockout is complete (success or failure) so make sure
        // that the timer is stopped.
        (void)KillTimer(hwnd, IDT_LOCKOUT);
    }
    else
    {
        DWORD cmsSleep;

        // This API should not be called until VerifyUserStart has been called
        ASSERT(FALSE);
        
        // Fall back to good old Sleep()
        cmsSleep = cSecondsToLockout * 1000;
        if(cmsSleep < cSecondsToLockout)
        {
            // Integer overflow! Use the largest number we can.
            cmsSleep = MAXDWORD;
        }
        Sleep(cmsSleep);
    }

    if(E_ABORT == g_hrPasswordOK)
    {
        fRet = FALSE;
        SetLastError(ERROR_CANCELLED);
    }

    return fRet;
}


// Summary:
//   Attempts to cancel the current verification, removing UI if 
//   possible
// 
//
// Returns:
//   TRUE if we are trying to cancel or FALSE if nothing is available
//   for us to cancel.
//
//
// Remarks:
//   This optional function cancels an existing call to to the 
//     verification sequence. May be called anytime between 
//    VerifyUserStart and VerifyUserStop.
//   
// 
BOOL LAPCancelVerifySequence()
{
    BOOL fCancel = FALSE;

    // NOTE: We don't ever want to cancel forced enrollment.

    // Set the global flag to cancelled
    g_hrPasswordOK = E_ABORT;

    // Cancel standard verification.
    if(NULL != g_hEventComplete)
    {
        // Signal that we've completed verification.
        // This will end the VerifyUser() call.
        (void)SetEvent(g_hEventComplete);
        fCancel = TRUE;
    }

    // Cancel exponential backoff.
    if(NULL != g_hEventLockoutDone)
    {
        // Signal the lockout complete event.
        // If we're in exponential backoff this will cancel.
        (void)SetEvent(g_hEventLockoutDone);
        fCancel = TRUE;
    }

    // Close the codeword dialog, if it exists.
    if(WndManager().IsStored(LAP_WINDOW_CODEWORD))
    {
        (void)EndDialog(WndManager()[LAP_WINDOW_CODEWORD], FALSE);
        fCancel = TRUE;
    }

    // Close the prewipe dialog, if it exists.
    if(WndManager().IsStored(LAP_WINDOW_PREWIPE))
    {
        (void)EndDialog(WndManager()[LAP_WINDOW_PREWIPE], -1);
        fCancel = TRUE;
    }

    return fCancel;
}


// 
// Loads the resource DLL (we need the same resources as CPL).
// Saves the module handle (so we can get our dialog out of the DLL).
// Summary:
//   Main DLL entry point.
//
// Parameters:
//  hinstDLL -- Handle to the DLL. The value is the base 
//   address of the DLL.
//  dwReason -- Specifies a flag indicating why the DLL 
//   entry-point function is being called.
//       Value                  Description
//       -------------------------------------------------
//       DLL_PROCESS_ATTACH     Indicates that the DLL is being loaded into the virtual address space of the current process as a result of the process starting or as a result of a call to LoadLibrary. 
//
//
//       DLL_THREAD_ATTACH      Ignored.
//     
//     
//       DLL_THREAD_DETACH      Ignored.
//     
//     
//       DLL_PROCESS_DETACH     Ignored.
//     
//   
//  lpReserved -- Ignored.
//
// Returns:
//   Always returns TRUE to indicate that initialization succeeded.
//
//
// Remarks:
//   This function is called by the system when processes and threads 
//     are initialized and terminated, or on calls to LoadLibrary and 
//     FreeLibrary.
// 
BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
    switch(dwReason) 
    {
        case DLL_PROCESS_ATTACH:
        {
            g_hInst = (HINSTANCE)hinstDLL;
            
            (void)DisableThreadLibraryCalls(g_hInst);

            break;
        }
    }

    return TRUE;
}


