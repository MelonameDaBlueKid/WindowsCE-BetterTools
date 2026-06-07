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
#include "verify.h"

HRESULT g_hrPasswordOK;
BOOL    g_fEnabled;
HANDLE  g_hEventComplete;       // Signaled when verification attempt is complete.
HANDLE  g_hEventLockoutDone;
DWORD   g_csecLockout = 0;
HWND    g_hwndPassword = NULL;
BOOL    g_fEmergencyCall;


// Summary:
//   Sets up the dialog for verification attempts.
//
// Parameters:
//  hwndParent -- The handle to the parent window. If this
//  value is NULL, the desktop window will be used.
//  pwszAEDisplayText -- The text that will be displayed 
//  in the verification dialog. If this value is NULL, the default text 
//  will be used
//
// Returns:
//   Returns success if the dialog is set up; otherwise failure.
//
//
// Remarks:
//   
// 
HRESULT DoVerifyUserStart(HWND hwndParent, LPCWSTR pwszAEDisplayText)
{
    // Assume unknown failure.
    HRESULT hr = E_FAIL;

    // Initialize password return value (also read by LockoutUser).
    // Default to generic failure.
    g_hrPasswordOK  = E_FAIL;   

    // LASS should never call VerifyUserStart when the 
    // dialog is already up.
    ASSERT(!ISWINDOWSTORED(LAP_WINDOW_VERIFY));

    // Reserve the verification window exclusively.
    RESERVEWINDOW(LAP_WINDOW_VERIFY); 

    // Create Event: Signals that the verification is complete.
    g_hEventComplete = CreateEvent(NULL, FALSE, FALSE, NULL);
    ASSERT(NULL != g_hEventComplete);

    // Create Event: Signals that lockout wait is 
    // complete (signaled by verify dialog).
    g_hEventLockoutDone = CreateEvent(NULL, FALSE, FALSE, NULL); 
    ASSERT(NULL != g_hEventLockoutDone);

    // Create the dialog.
    HWND hwndVerify = CreateDialogParam(g_hInst, 
        MAKEINTRESOURCE(IDD_VERIFY), hwndParent, 
        VerifyDlgProc, (LPARAM)pwszAEDisplayText);

    // Creating this dialog shouldn't fail.
    if(NULL != hwndVerify)
    {
        // Store the window handle.
        STOREWINDOW(LAP_WINDOW_VERIFY, hwndVerify);

        // Make sure we are in a disabled 
        // state (don't show until we are).
        (void)SendMessage(hwndVerify, WM_APP_DISABLE, 0, 0);

        // Show the window.
        (void)ShowWindow(hwndVerify, SW_SHOWNORMAL);

        // Once the setup is complete, return success.
        hr = S_OK;
    }

    return hr;
}


// Summary:
//   Destroys the dialog for verification attempts.
//
//
// Remarks:
//   
// 
void DoVerifyUserStop()
{
    // Release verification event handle.
    if(NULL != g_hEventComplete)
    {
        CloseHandle(g_hEventComplete);
        g_hEventComplete = NULL;
    }

    // Release lockout event handle.
    if(NULL != g_hEventLockoutDone)
    {
        (void)CloseHandle(g_hEventLockoutDone);
        g_hEventLockoutDone = NULL;
    }

    // Destroy the verification dialog if it still exists.
    if(ISWINDOWSTORED(LAP_WINDOW_VERIFY) && 
        IsWindow(GETSTOREDWINDOW(LAP_WINDOW_VERIFY)))
    {
        (void)DestroyWindow(GETSTOREDWINDOW(LAP_WINDOW_VERIFY));
    }

    // Make sure this window handle is cleared no matter what.
    CLEARSTOREDWINDOW(LAP_WINDOW_VERIFY);
}


// Summary:
//   Enables a single verification attempt for a user. 
//
// Parameters:
//  pwszAEDisplayText -- The text that will be displayed 
//  in the verification dialog. If this value is NULL or an empty string, 
//  the dialog keeps the same text used in 
//  DoVerifyUserStart.
//
// Returns:
//   Returns success if the verification attempt succeeded; otherwise
//   failure. If verification was cancelled, returns E_ABORT.
//
//
// Remarks:
//   
// 
HRESULT DoVerify(LPCWSTR pwszAEDisplayText)
{
    // Reset return value. Default to generic failure.
    g_hrPasswordOK  = E_FAIL;   

    // Ensure that the dialog window exists.
    if(ISWINDOWSTORED(LAP_WINDOW_VERIFY) && 
        IsWindow(GETSTOREDWINDOW(LAP_WINDOW_VERIFY)))
    {
        // Enable the dialog (user can attempt verification once).
        (void)SendMessage(GETSTOREDWINDOW(LAP_WINDOW_VERIFY), 
            WM_APP_ENABLE, (WPARAM)pwszAEDisplayText, 0);

        // Wait for verification attempt.
        (void)MsgBlockOnEvent(g_hEventComplete, 
            GETSTOREDWINDOW(LAP_WINDOW_VERIFY));

        // Disable the dialog.
        (void)SendMessage(GETSTOREDWINDOW(LAP_WINDOW_VERIFY), 
            WM_APP_DISABLE, 0, 0);
    }

    // Return the result set by the dialog.
    return g_hrPasswordOK;
}


// Summary:
//   Dialog proc for the verification dialog. Handles all messages.
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
BOOL VerifyDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL fHandled = FALSE;
    TCHAR szPassword[MAX_PASSWORD + 1];
    LPCTSTR pszDisplayText;
    static HWND       s_hwndMenuBar = NULL;
    static BOOL       s_fIsEmergencyNum;
    static HREGNOTIFY s_hRegNotify;

    // Signal that this dialog is mainly for input purposes.
    SHInputDialog(hwndDlg, uMsg, wParam);

    // Handle specific message.
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            // Initialize static variables.
            s_fIsEmergencyNum = FALSE;
            g_fEmergencyCall  = FALSE;
            s_hRegNotify      = NULL;

            // Set custom display text if 
            // exists (lParam is display text).
            pszDisplayText = (LPCTSTR)lParam;
            if(NULL != pszDisplayText && 
                TEXT('\0') != pszDisplayText[0])
            {
                (void)SetDlgItemText(hwndDlg, IDC_VERIFY, 
                    pszDisplayText);
            }

            // Limit number of characters in password.
            (void)SendDlgItemMessage(hwndDlg, IDC_PASSWORD, 
                EM_LIMITTEXT, (WPARAM)MAX_PASSWORD, 0);

            // Size dialog full-screen.
            SHINITDLGINFO sidi;
            sidi.dwMask = SHIDIM_FLAGS;
            sidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN | 
                SHIDIF_WANTSCROLLBAR;
            sidi.hDlg = hwndDlg;
            (void)SHInitDialog(&sidi);
    
            // Create menubar.
            SHMENUBARINFO smbi;
            memset(&smbi, 0, sizeof(smbi));
            smbi.cbSize = sizeof(smbi);
            smbi.hwndParent = hwndDlg;
            smbi.nToolBarId = IDR_COMMON_MENUBAR;
            smbi.hInstRes = g_hInst;
            (void)SHCreateMenuBar(&smbi);
            s_hwndMenuBar = smbi.hwndMB;

            // Disable the OK softkey.
            EnableSoftkey(s_hwndMenuBar, IDOK, FALSE);

            // Register the back hotkey for the edit controls.
            (void)SendMessage(smbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
                SHMBOF_NODEFAULT | SHMBOF_NOTIFY));
    
            // Register the talk hotkey for emergency calls.
            (void)SendMessage(smbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TTALK, 
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
                SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

            // Keep a copy of the password control for the emergency
            // number subclass handler.
            g_hwndPassword = GetDlgItem(hwndDlg, IDC_PASSWORD);

            // Subclass emergency number control.
            HWND hwndControl = GetDlgItem(hwndDlg, IDC_EMERGENCY);
            if(NULL != hwndControl)
            {
                // Use our own window proc.
                WNDPROC pfnOrigProc = 
                    (WNDPROC)SetWindowLong(hwndControl, 
                    GWL_WNDPROC, (LONG)EmergencySubclassProc);
                // Save the original window proc so it can 
                // be called.
                (void)SetWindowLong(hwndControl, GWL_USERDATA, 
                    (LONG)pfnOrigProc);
            }

            fHandled = TRUE;
            break;
        }
        
        case WM_APP_FOREGROUND:
        {
            // Make sure our window is foreground.
            (void)SetForegroundWindow(hwndDlg);
            fHandled = TRUE;
            break;
        }

        case WM_APP_ENABLE:
        {
            // Update the custom display text (it may have changed).
            LPCTSTR pszDisplayText = (LPCTSTR)wParam;
            if(NULL != pszDisplayText && 
                TEXT('\0') != pszDisplayText[0])
            {
                (void)SetDlgItemText(hwndDlg, IDC_VERIFY, 
                    pszDisplayText);
            }

            // Update info text (retain old text if possible).
            ShowInfo(hwndDlg, s_fIsEmergencyNum, FALSE, 
                FALSE, NULL);

            // Set the global enabled flag.
            g_fEnabled = TRUE;

            // Reset the idle timer.
            ResetIdleTimer(hwndDlg);

            // Make sure we are foreground.
            (void)SetForegroundWindow(hwndDlg);

            // Enable the OK softkey.
            EnableSoftkey(s_hwndMenuBar, IDOK, TRUE);

            fHandled = TRUE;

            break;
        }
        
        case WM_APP_DISABLE:
        {
            // Clear the global enabled flag.
            g_fEnabled = FALSE;

            // Clear the text fields.
            (void)SetDlgItemText(hwndDlg, IDC_PASSWORD,  K_SZRESETTEXT);
            (void)SetDlgItemText(hwndDlg, IDC_EMERGENCY, K_SZRESETTEXT);

            // Stop the idle timer.
            KillIdleTimer(hwndDlg);

            // Disable the OK softkey.
            EnableSoftkey(s_hwndMenuBar, IDOK, FALSE);

            fHandled = TRUE;

            break;
        }

        case WM_HOTKEY:
        {
            switch(HIWORD(lParam))
            {
                case VK_TTALK:
                {
                    // User pressed TALK key. Handle if an emergency 
                    // number is specified and we're not already in 
                    // an emergency call.
                    if(!(LOWORD(lParam) & MOD_KEYUP) && 
                        s_fIsEmergencyNum && !g_fEmergencyCall)
                    {
                        // Read the emergency number from 
                        // the password control.
                        szPassword[0] = TEXT('\0');
                        (void)GetDlgItemText(hwndDlg, IDC_PASSWORD, 
                            szPassword, ARRAYSIZE(szPassword));

                        // Make call.
                        MakeEmergencyCall(szPassword);
                        g_fEmergencyCall = TRUE;
                        
                        // Make sure we are still foreground.
                        (void)SetForegroundWindow(hwndDlg);

                        // Clear the text fields.
                        // This won't change the s_fIsEmergencyNum flag
                        // or the informational text when we're in a call.
                        // That is intentional.
                        (void)SetDlgItemText(hwndDlg, IDC_PASSWORD,  
                            K_SZRESETTEXT);
                        (void)SetDlgItemText(hwndDlg, IDC_EMERGENCY, 
                            K_SZRESETTEXT);

                        // Send a message so the platform-specific 
                        // code can take action.
                        (void)PostMessage(hwndDlg, WM_APP_REGISTERCALLS, 
                            0, 0);
                        fHandled = TRUE;
                    }
                    break;
                }
                    
                case VK_TBACK:
                {
                    // Send back key to controls.
                    SHSendBackToFocusWindow(uMsg, wParam, lParam);
                    fHandled = TRUE;
                    break;
                } 
            }
            break;
        }

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDOK:
                {
                    // Don't handle OK button when in emergency call.
                    // Must be enabled to handle OK.
                    if(!g_fEmergencyCall && g_fEnabled)
                    {
                        // Read user's password.
                        szPassword[0] = TEXT('\0');
                        (void)GetDlgItemText(hwndDlg, IDC_PASSWORD, 
                            szPassword, ARRAYSIZE(szPassword));
                        
                        // Check password
                        if(!LapCheckPassword(szPassword))
                        {
                            // If user tried to enter an empty 
                            // password just treat it like they 
                            // cancelled.
                            if(TEXT('\0') == szPassword[0])
                            {
                                g_hrPasswordOK = E_ABORT;
                            }
                            else
                            {
                                // Display invalid password error 
                                // including failed attempts.
                                LPTSTR pszAttempts = NULL;
                                DWORD dwAttempts = 0;
                                DWORD dwSize = 0;
                                DWORD dwThreshold = 0;

                                // Only continue if threshold exists.
                                if(LASSGetValue(
                                    LASS_VALUE_DEVICE_WIPE_THRESHOLD, 
                                    &dwThreshold, 
                                    sizeof(dwThreshold), 
                                    &dwSize) && 
                                    0 < dwThreshold)
                                {
                                    // Get failed attempts 
                                    // (may return FALSE, then it's 0).
                                    (void)LASSGetValue(
                                        LASS_VALUE_AUTH_FAILURE_COUNT, 
                                        &dwAttempts, 
                                        sizeof(dwAttempts), 
                                        &dwSize);
                                    
                                    // Add 1 to get the current attempt number.
                                    // This should never get up to MAXDWORD.
                                    if(MAXDWORD > dwAttempts) 
                                    {
                                        dwAttempts++;
                                    }

                                    // Load the error string resource.
                                    LPCTSTR pszFormat = 
                                        CELOADSZ(IDS_INCORRECT_ATTEMPTS);
                                    if(NULL != pszFormat)
                                    {
                                        size_t cchAttempts = 0;
                                        size_t cbAttempts = INT_MAX; // Start with max allowed.
                                        // Get the length of the 
                                        // formatting string and 
                                        // make sure we have enough
                                        // room for two numbers.
                                        if(SUCCEEDED(
                                            StringCchLength(pszFormat, 
                                            STRSAFE_MAX_CCH - 
                                            (2 * MAX_INT_LENGTH), 
                                            &cchAttempts)))
                                        {
                                            // Add space for two 
                                            // numbers and NULL terminator.
                                            cchAttempts += (2 * MAX_INT_LENGTH) + 1;

                                            // Check for integer overflow.
                                            if(cchAttempts > (2 * MAX_INT_LENGTH) + 1) 
                                            {
                                                // Convert to bytes.
                                                cbAttempts = 
                                                    cchAttempts * sizeof(TCHAR);
                                                
                                                // Check for integer overflow.
                                                if(cbAttempts < cchAttempts) 
                                                {
                                                    // The string is too long. Use maximum allowed.
                                                    cbAttempts = INT_MAX;
                                                }
                                            }
                                        }

                                        // Allocate memory for
                                        // the final error string.
                                        pszAttempts = (LPTSTR)LocalAlloc(
                                            LMEM_FIXED, cbAttempts);
                                        if(NULL != pszAttempts)
                                        {
                                            // Format the number of 
                                            // attempts (x/y attempts).
                                            if(FAILED(StringCbPrintf(
                                                pszAttempts, 
                                                cbAttempts, 
                                                pszFormat, 
                                                dwAttempts, 
                                                dwThreshold)))
                                            {
                                                (void)LocalFree(pszAttempts);
                                                pszAttempts = NULL;
                                            }
                                        }
                                    }
                                }

                                // If we don't have a device wipe
                                // threshold, show simple error.
                                if(NULL == pszAttempts)
                                {
                                    (void)DisplayMessage(hwndDlg, 
                                        IDS_INCORRECT_TITLE, 
                                        IDS_INCORRECT_PASSWORD);
                                }
                                else
                                {
                                    // Show complex error including
                                    // number of attempts.
                                    (void)DisplayMessageEx(hwndDlg, 
                                        IDS_INCORRECT_TITLE, 
                                        pszAttempts);
                                    (void)LocalFree(pszAttempts);
                                }

                                // Set failure.
                                g_hrPasswordOK = E_FAIL;
                            }
                        }
                        else
                        {
                            // User entered the correct password.
                            g_hrPasswordOK = S_OK;

                            // Make a copy of the password for 
                            // enrollment.
                            SavePasswordForEnrollment(szPassword);

                            // Wipe the password memory for security.
                            for(int i=0; i < MAX_PASSWORD && 
                                TEXT('\0') != szPassword[i]; i++)
                            {
                                *szPassword = TEXT('\0');
                            }
                        }

                        // Signal event that this 
                        // password attempt is complete.
                        (void)SetEvent(g_hEventComplete);

                        fHandled = TRUE;
                    }
                    break;
                }
                    
                case IDCANCEL:
                {
                    // Set cancel value.
                    g_hrPasswordOK = E_ABORT;

                    // Signal event that this 
                    // password attempt is complete.
                    (void)SetEvent(g_hEventComplete);
    
                    // Release the lockout event as well 
                    // if it is waiting.
                    if(NULL != g_hEventLockoutDone)
                    {
                        (void)SetEvent(g_hEventLockoutDone);
                    }                    

                    fHandled = TRUE;
                    break;
                }

                case IDC_PASSWORD:
                {
                    // If the password has changed start the 
                    // edit handler.
                    if(EN_CHANGE == HIWORD(wParam))
                    {                        
                        // Get the entered password.
                        szPassword[0] = TEXT('\0');
                        (void)GetDlgItemText(hwndDlg, IDC_PASSWORD, 
                            szPassword, ARRAYSIZE(szPassword));

                        // Do this synchronously so we don't 
                        // have to worry about allocation.
                        (void)SendMessage(hwndDlg, WM_APP_ONEDIT, 
                            (WPARAM)szPassword, 0);

                        fHandled = TRUE;
                    }
                    break;
                }
            }
            break;
        }

        case WM_APP_ONEDIT:
        {
            // Handle editing of the password.
            // The new edited password is the wParam.
            LPCTSTR pszPassword = (LPCTSTR)wParam;

            if(!g_fEmergencyCall)
            {
                // Only deal with eCalls if the device has a phone.
                if(DeviceHasPhone())
                {
                    // Not in an eCall right now.
                    // See if the user just entered an eNumber.
                    BOOL fOldIsEmergencyNumber = s_fIsEmergencyNum;
                    s_fIsEmergencyNum = PhoneIsEmergencyNumber(FALSE, 
                        pszPassword, NULL);

                    if(fOldIsEmergencyNumber || s_fIsEmergencyNum)
                    {
                        // Do this synchronously so we don't 
                        // have to worry about other messages.
                        (void)SendMessage(hwndDlg, WM_APP_ENUMBER, 
                            MAKEWPARAM(s_fIsEmergencyNum, fOldIsEmergencyNumber), 
                            reinterpret_cast<LPARAM>(pszPassword));
                    }
                }

                // The user edited -- reset the timer.
                ResetIdleTimer(hwndDlg);
            }

            fHandled = TRUE;
            break;
        }

        case WM_APP_ENUMBER:
        {
            // Handle the shift between emergency modes.
            // wParam tells us if we're switching emergency 
            // number on or off.
            BOOL fIsEmergencyNumber = BOOLIFY(LOWORD(wParam));  

            // Check wParam to see if we're switching 
            // emergency number state.
            if(fIsEmergencyNumber != BOOLIFY(HIWORD(wParam)))
            {
                // Show/hide the instructions message.
                ShowInfo(hwndDlg, fIsEmergencyNumber, FALSE, 
                    TRUE, NULL);

                // If not emergency number,
                // restore the reduced power timeout (as if locked).
                // If emergency number,
                // restore the normal power timeout (as if unlocked).
                (void)SHSetPowerTimeoutForLock(!fIsEmergencyNumber);

                // Show/hide edit controls.
                HWND hwndHide = NULL;
                HWND hwndFocus = GetDlgItem(hwndDlg, IDC_EMERGENCY);
                ASSERT(NULL != hwndFocus);

                if(fIsEmergencyNumber)
                {
                    // Emergency number was entered
                    // Copy emergency number to emergency 
                    // control (passed in lParam).
                    (void)SetWindowText(hwndFocus, (LPCTSTR)lParam);

                    // Set the password control to hide.
                    hwndHide = GetDlgItem(hwndDlg, IDC_PASSWORD);
                }
                else
                {
                    // Switch back to normal.
                    hwndHide = hwndFocus;                               
                    hwndFocus = GetDlgItem(hwndDlg, IDC_PASSWORD);
                }
                                        
                // Set focus to the correct control.
                (void)ShowWindow(hwndFocus, SW_SHOW);
                (void)ShowWindow(hwndHide,  SW_HIDE);
                (void)SetFocus(hwndFocus);
                (void)SendMessage(hwndFocus, EM_SETSEL, 
                    MAX_PASSWORD, MAX_PASSWORD);

                fHandled = TRUE;
            }

            break;
        }

        case WM_APP_REGISTERCALLS:
        {
            // Listen for when the call ends.
            s_hRegNotify = RegisterCallNotifications(hwndDlg);

            fHandled = TRUE;
            break;
        }

        case WM_APP_ACTIVECALLS:
        {
            // The number of active calls has changed.
            if(0 == GetActiveCallCount())
            {
                // No active calls. 
                // Assume our emergency call ended.
                g_fEmergencyCall = FALSE;

                // Stop listening for active call number.
                UnregisterCallNotifications(s_hRegNotify);

                // Reset the password text.
                (void)SetDlgItemText(hwndDlg, IDC_PASSWORD, 
                    K_SZRESETTEXT);
                (void)SetDlgItemText(hwndDlg, IDC_EMERGENCY, 
                    K_SZRESETTEXT);

                // Restore focus to this dialog.
                (void)SetForegroundWindow(hwndDlg);

                fHandled = TRUE;
            }
            break;
        }

        case WM_TIMER:
        {
            switch(wParam)
            {
                case IDT_IDLE_TIMEOUT:
                {
                    // The user hasn't pressed a key in a while.
                    // Cancel the dialog.
                    (void)PostMessage(hwndDlg, WM_COMMAND, 
                        MAKEWPARAM(IDCANCEL, 0), 0);   
                    fHandled = TRUE;
                    break;
                }

                case IDT_LOCKOUT:
                {
                    // The user lockout timer fires every second.
                    // Decrement the lockout time.
                    if(g_csecLockout > 0)
                    {
                        g_csecLockout--;
                    }

                    if(0 == g_csecLockout)
                    {
                        // Lockout is finished.
                        (void)KillTimer(hwndDlg, IDT_LOCKOUT);
                        
                        // Go back to the regular informational text.
                        ShowInfo(hwndDlg, s_fIsEmergencyNum, FALSE, 
                            TRUE, NULL);

                        // Set lockout done event to release the 
                        // blocked thread.
                        if(NULL != g_hEventLockoutDone)
                        {
                            (void)SetEvent(g_hEventLockoutDone);
                        }
                    }
                    else
                    {
                        // Show remaining lockout duration.
                        TCHAR szLockout[MAX_LOCKOUT_DISPLAY];
                        TCHAR szTemp   [MAX_LOCKOUT_DISPLAY];
                        
                        // Fill a struct with the time info.
                        SYSTEMTIME st;
                        memset(&st, 0, sizeof(st));
                        st.wSecond = (WORD)(g_csecLockout % 60);        // Seconds in a minute.
                        st.wMinute = (WORD)((g_csecLockout/60) % 60);   // Minutes in an hour.
                        st.wHour   = (WORD)((g_csecLockout/3600) % 24); // Hours in a day.

                        // Format the time to display
                        // using locale info.
                        if(0 == GetLocaleInfo(LOCALE_USER_DEFAULT, 
                            LOCALE_STIMEFORMAT, szLockout, ARRAYSIZE(szLockout)) ||
                            0 == GetTimeFormat(LOCALE_USER_DEFAULT,
                            TIME_FORCE24HOURFORMAT | TIME_NOTIMEMARKER,
                            &st, szLockout, szTemp, ARRAYSIZE(szTemp)) || 
                            FAILED(StringCchPrintf(szLockout, ARRAYSIZE(szLockout),
                            TEXT("%d  %s"), g_csecLockout/86400, szTemp)))  // 86400 = seconds/day.
                        {
                            // We couldn't get a time format so just 
                            // use the seconds.
                            (void)StringCchPrintf(szLockout, 
                                ARRAYSIZE(szLockout), TEXT("%d"),
                                g_csecLockout);
                        }

                        // All other dialogs will see the timeout 
                        // in the info. Use ShowInfo so emergency text 
                        // can override if necessary.
                        ShowInfo(hwndDlg, s_fIsEmergencyNum, 
                            FALSE, TRUE, szLockout);
                    }

                    fHandled = TRUE;
                    break;
                }
            }
            break;
        }

        case WM_DESTROY:
        {
            // Don't keep the password control handle.
            g_hwndPassword = NULL;

            // Cleanup idle timer if it's still going.
            KillIdleTimer(hwndDlg);

            if(s_fIsEmergencyNum)
            {
                // If we were in eMode, restore power timeout.
                (void)SHSetPowerTimeoutForLock(TRUE);
            }

            fHandled = TRUE;
            break;
        }
    }

    return fHandled;
}


// Summary:
//   Window proc for the emergency number control.
//
// Parameters:
//  hwnd -- Handle to the window. 
//  uMsg -- Specifies the message.
//  wParam -- Specifies additional message-specific 
//   information.
//  lParam -- Specifies additional message-specific 
//   information.
//
// Returns:
//   Returns the value from the standard window proc.
//
//
// Remarks:
//   The emergency number control is subclassed here so 
//     that when this control is receiving input all input also
//     goes to the password control All messages are passed 
//     on to the standard edit field window proc.
// 
LRESULT EmergencySubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Used to indicate if we are sending DTMF tones
    static BOOL s_fInDTMF = FALSE;

    // On keydown we send DTMFs.
    // Only if this is changing states from up to down.
    if (g_fEmergencyCall)
    {
        if (   WM_KEYDOWN == uMsg 
            && !(KF_REPEAT & HIWORD(lParam)))
        {
            // Send the virtual key as a DTMF.
            s_fInDTMF = SUCCEEDED (PhoneSendDTMFStart (MapVKeyToChar (LOWORD (wParam))));
        }
        else
        if (s_fInDTMF && WM_KEYUP == uMsg)
        {
            // Stop the DTMF tone
            (void)PhoneSendDTMFStop();
        }
    }

    // Pass on all input to the password control.
    if(WM_KEYDOWN == uMsg || WM_KEYUP == uMsg || (WM_CHAR == uMsg))
    {
        // Send message to password control.
        (void)SendMessage(g_hwndPassword, uMsg, wParam, lParam);
    }

    // Allow normal window proc to handle all messages.
    WNDPROC pfnOrigProc = (WNDPROC)GetWindowLong(hwnd, GWL_USERDATA);
    return CallWindowProc(pfnOrigProc, hwnd, uMsg, wParam, lParam);
}

// Summary:
//   Enable/disable softkey button.
//
// Parameters:
//  hwndMenuBar -- Handle to the menu bar.
//  nID -- Specifies the ID of the button to change.
//  fEnable -- TRUE to enable the button, FALSE to
//   disable.
void EnableSoftkey(HWND hwndMenuBar, int nID, BOOL fEnable)
{
    BOOL fChangeState = FALSE;
    TBBUTTONINFO tbi;
    tbi.cbSize = sizeof(tbi);
    tbi.dwMask = TBIF_STATE;
    
    // Get current button state.
    if(-1 == SendMessage(hwndMenuBar, TB_GETBUTTONINFO, 
        (WPARAM)nID, (LPARAM)&tbi))
    {
        // Failed
        ASSERT(0);
        tbi.fsState = 0;
    }
    
    // Update state flags.
    if(fEnable)
    {
        // Enabling.
        if(!(tbi.fsState & TBSTATE_ENABLED))
        {
            tbi.fsState |= TBSTATE_ENABLED;
            fChangeState = TRUE;
        }
    }
    else 
    {
        // Disabling.
        if(tbi.fsState & TBSTATE_ENABLED)
        {
            tbi.fsState &= ~TBSTATE_ENABLED;
            fChangeState = TRUE;
        }            
    }

    // Set the new state.
    if(fChangeState)
    {
        (void)SendMessage(hwndMenuBar, TB_SETBUTTONINFO, 
            (WPARAM)nID, (LPARAM)&tbi); 
    }
}


