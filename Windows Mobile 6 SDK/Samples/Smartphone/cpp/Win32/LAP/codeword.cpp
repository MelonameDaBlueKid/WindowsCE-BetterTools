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
#include "codeword.h"

BOOL g_fInEmergencyCall;

// Summary:
//   Prompts the user for the specified codeword.
//
// Parameters:
//  hwndParent --  Handle to the parent window.  If NULL, 
//   the desktop window will be used
//  pwszCodeword --  Pointer to the codeword to be entered 
//   for verification. This value can also be NULL or an empty string to 
//   use the default ("a1b2c3"). 
//
// Returns:
//   Returns TRUE if the codeword dialog is displayed and the codeword
//   is entered; otherwise FALSE.
// 
BOOL DoCodeword(HWND hwndParent, LPCWSTR pwszCodeword)
{
    BOOL fRet = BOOLIFY(DialogBoxParam(g_hInst, 
        MAKEINTRESOURCE(IDD_CODEWORD), hwndParent, CodewordDlgProc, 
        (LPARAM)pwszCodeword));

    return fRet;
}


// Summary:
//   Dialog proc for the codeword dialog. Handles all messages.
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
BOOL CodewordDlgProc(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam)
{
    BOOL fHandled = FALSE;
    static TCHAR      s_szCodeword[MAX_CODEWORD + 1];
    static BOOL       s_fIsEmergencyNum;
    static HREGNOTIFY s_hRegNotify;

    // Signal that this dialog is mainly for input purposes.
    SHInputDialog(hwndDlg, uMsg, wParam);
    
    // Handle specific message.
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            // Store the window handle
            STOREWINDOW(LAP_WINDOW_CODEWORD, hwndDlg);

            // Initialize static variables.
            s_hRegNotify       = NULL;
            s_fIsEmergencyNum  = FALSE;
            g_fInEmergencyCall = FALSE;

            // Intialize the dialog with a close button and scroll bar.
            SHINITDLGINFO   shidi;
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_DONEBUTTON | 
                SHIDIF_WANTSCROLLBAR;
            shidi.hDlg = hwndDlg;
            (void)SHInitDialog(&shidi);

            // Create menubar.
            SHMENUBARINFO smbi;
            memset(&smbi, 0, sizeof(smbi));
            smbi.cbSize = sizeof(smbi);
            smbi.hwndParent = hwndDlg;
            smbi.nToolBarId = IDR_SECURE_MENUBAR;
            smbi.hInstRes = g_hInst;
            (void)SHCreateMenuBar(&smbi);

              // Register the back hotkey for the edit controls.
            (void)SendMessage(smbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
                SHMBOF_NODEFAULT | SHMBOF_NOTIFY));
            
            // Register the talk hotkey for emergency calls.
            (void)SendMessage(smbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TTALK, 
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
                SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

            // Limit the codeword field.
            (void)SendDlgItemMessage(hwndDlg, IDC_CODEWORD, EM_LIMITTEXT, 
                MAX_CODEWORD, 0);

            // Allocate a string to keep the actual codeword.
            LPTSTR pszActualCodeword = (LPTSTR)LocalAlloc(LMEM_FIXED, 
                ARRAYSIZE(s_szCodeword) * sizeof(TCHAR));
            (void)SetWindowLong(hwndDlg, DWL_USER, (LONG)pszActualCodeword);
            
            if(NULL == pszActualCodeword)
            {
                // Memory allocation failure. Close the dialog.
                (void)PostMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDOK, 0), 0);
            }
            else
            {
                // Populate the string with the passed-in value or the default.
                // lParam is a UNICODE string, so if this isn't built
                // in UNICODE, it must be converted.
                C_ASSERT(sizeof(TCHAR) == sizeof(WCHAR));
                LPCTSTR pszOriginal = (LPCTSTR)lParam;

                if(NULL == pszOriginal || TEXT('\0') == pszOriginal[0])
                {
                    // Use default codeword.
                    (void)StringCchCopy(pszActualCodeword, 
                        ARRAYSIZE(s_szCodeword), TEXT("a1b2c3"));
                }
                else            
                {
                    (void)StringCchCopy(pszActualCodeword, 
                        ARRAYSIZE(s_szCodeword), pszOriginal);
                }
            }

            // Set info text
            ShowInfo(hwndDlg, FALSE, TRUE, TRUE, NULL);

            // Subclass codeword control (for DTMFs).
            HWND hwndControl = GetDlgItem(hwndDlg, IDC_CODEWORD);
            if(NULL != hwndControl)
            {
                // Use our own window proc.
                WNDPROC pfnOrigProc = (WNDPROC)SetWindowLong(hwndControl, 
                    GWL_WNDPROC, (LONG)CodewordSubclassProc);
                // Save the original window proc so it can be called.
                (void)SetWindowLong(hwndControl, GWL_USERDATA, 
                    (LONG)pfnOrigProc);
            }

            // Set up the codeword label.
            LPCTSTR pszFormat = CELOADSZ(IDS_CODEWORD);
            if(NULL != pszFormat)
            {
                size_t cchCodeword      = 0;
                size_t cchCodewordLabel = 0;
                size_t cbCodewordLabel  = INT_MAX;   // Use max by default.

                // Calculate the size needed for the label + codeword.
                if(SUCCEEDED(StringCchLength(pszActualCodeword, 
                    ARRAYSIZE(s_szCodeword), &cchCodeword)) && 
                    SUCCEEDED(StringCchLength(pszFormat, 
                    STRSAFE_MAX_CCH - cchCodeword, &cchCodewordLabel)))
                {
                    // Add codeword and label size + 1 for 
                    // NULL terminator - 2 for %s.
                    cchCodewordLabel += cchCodeword - 1;
                    // Check for integer overflow.
                    if(cchCodewordLabel > cchCodeword - 1) 
                    {
                        // Convert to bytes
                        cbCodewordLabel = cchCodewordLabel * sizeof(TCHAR);
                        // Check for integer overflow.
                        if(cbCodewordLabel < cchCodewordLabel) 
                        {
                            // Codeword + label was too long.
                            // Use longest allowed.
                            cbCodewordLabel = INT_MAX;
                        }
                    }
                }

                // Alocate a string for the formatted label.
                LPTSTR pszCodewordLabel = (LPTSTR)LocalAlloc(LMEM_FIXED, 
                    cbCodewordLabel);

                // Format the codeword label.
                if(NULL != pszCodewordLabel)
                {
                    // Intialize the label in case the formatting fails.
                    pszCodewordLabel[0] = TEXT('\0');
                    (void)StringCbPrintf(pszCodewordLabel, cbCodewordLabel, 
                        pszFormat, pszActualCodeword);
                    // Set the static control text.
                    (void)SetDlgItemText(hwndDlg, IDC_CODEWORD_LABEL, 
                        pszCodewordLabel);
                    (void)LocalFree(pszCodewordLabel);
                }
            }

            // Start the idle timer now.
            ResetIdleTimer(hwndDlg);

            fHandled = TRUE;
            break;
        }

        case WM_HOTKEY:        
        {
            // User pressed TALK key. Handle if an emergency number is 
            // specified and we're not already in an emergency call.
            if(VK_TTALK == HIWORD(lParam) && 
                0 == (LOWORD(lParam) & MOD_KEYUP) && 
                s_fIsEmergencyNum && !g_fInEmergencyCall)
            {
                // Get the entered codeword.
                s_szCodeword[0] = TEXT('\0');
                GetDlgItemText(hwndDlg, IDC_CODEWORD, s_szCodeword, 
                    ARRAYSIZE(s_szCodeword));

                // Place the call.
                MakeEmergencyCall(s_szCodeword);
                g_fInEmergencyCall = TRUE;

                // We just dialed an emergency call.  
                // Let's clear the original numbers displayed so user 
                // can send DTMF's.
                // This won't change the s_fIsEmergencyNum flag
                // or the informational text when we're in a call.
                // That is intentional.
                (void)SetDlgItemText(hwndDlg, IDC_CODEWORD, K_SZRESETTEXT); 

                // Listen for when the call ends.
                s_hRegNotify = RegisterCallNotifications(hwndDlg);

                fHandled = TRUE;
            }
            else if(VK_TBACK == HIWORD(lParam))
            {
                // User pressed BACK key. Send back key to controls.
                SHSendBackToFocusWindow(uMsg, wParam, lParam);
                fHandled = TRUE;
            }

            break;
        }
        
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDOK:
                {
                    // Get the entered codeword.
                    s_szCodeword[0] = TEXT('\0');
                    (void)GetDlgItemText(hwndDlg, IDC_CODEWORD, 
                        s_szCodeword, ARRAYSIZE(s_szCodeword));

                    // Check the codeword (case insensitive)
                    LPCTSTR pszActualCodeword = 
                        (LPCTSTR)GetWindowLong(hwndDlg, DWL_USER);
                    if(NULL != pszActualCodeword && 
                        0 != _tcsnicmp(pszActualCodeword, s_szCodeword, 
                        ARRAYSIZE(s_szCodeword) - 1))
                    {
                        // Failed. Clear the codeword.
                        (void)SetDlgItemText(hwndDlg, IDC_CODEWORD, 
                            K_SZRESETTEXT);

                        // Alert the user.
                        (void)SetDlgItemText(hwndDlg, IDC_INFO, 
                            SafeCELOADSZ(IDS_INVALID_CODEWORD));

                        // Don't exit the dialog.
                        (void)SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);
                    }
                    else
                    {
                        // Succeeded. Exit the dialog.
                        (void)EndDialog(hwndDlg, 1);
                    }

                    fHandled = TRUE;
                    break;
                }

                case IDC_CODEWORD:
                {
                    // The user has modified the codeword. 
                    // Check for emergency number.
                    if(EN_CHANGE == HIWORD(wParam))
                    {
                        // Get the entered codeword.
                        s_szCodeword[0] = TEXT('\0');
                        GetDlgItemText(hwndDlg, IDC_CODEWORD, s_szCodeword, 
                            ARRAYSIZE(s_szCodeword));

                        if(!g_fInEmergencyCall && DeviceHasPhone())
                        {
                            // Not in an ECall right now.
                            // See if the user just entered an E Number.
                            BOOL fOldIsEmergencyNumber = s_fIsEmergencyNum;
                            s_fIsEmergencyNum = PhoneIsEmergencyNumber(FALSE, 
                                s_szCodeword, NULL);

                            // Take action if we have an emergency number 
                            // or we were in emergency mode.
                            if(fOldIsEmergencyNumber != s_fIsEmergencyNum)
                            {
                                // Show/hide the emergency instructions message.
                                ShowInfo(hwndDlg, s_fIsEmergencyNum, 
                                    TRUE, TRUE, NULL);

                                // If not emergency number, restore the
                                // reduced power timeout (as if locked).
                                // If emergency number, restore the
                                // normal power timeout (as if unlocked).
                                (void)SHSetPowerTimeoutForLock(s_fIsEmergencyNum);
                            }
                        }

                        // Reset the timer.
                        ResetIdleTimer(hwndDlg);
                    }
                    
                    fHandled = TRUE;
                    break;
                }
            }
            break;
        }
        
        case WM_APP_ACTIVECALLS:
        {
            // The number of active calls has changed.
            if(0 == GetActiveCallCount())
            {
                // No active calls. 
                // Assume our emergency call ended.
                g_fInEmergencyCall = FALSE;
                s_fIsEmergencyNum  = FALSE;

                // Stop listening for active call number.
                UnregisterCallNotifications(s_hRegNotify);

                // Restore focus to this dialog.
                (void)SetForegroundWindow(hwndDlg);

                // Clear the codeword field and give it focus.
                HWND hwndCodeword = GetDlgItem(hwndDlg, IDC_CODEWORD);
                (void)SetWindowText(hwndCodeword, K_SZRESETTEXT);
                (void)SetFocus(hwndCodeword);

                // Update the info text.
                ShowInfo(hwndDlg, s_fIsEmergencyNum, TRUE, TRUE, NULL);
            }

            fHandled = TRUE;
            break;
        }        

        case WM_TIMER:
        {
            // The user hasn't pressed a key in a while -- clear the codeword.
            (void)SetDlgItemText(hwndDlg, IDC_CODEWORD, K_SZRESETTEXT);
            fHandled = TRUE;
            break;
        }

        case WM_DESTROY:
        {
            // Cleanup idle timer if it's still going.
            KillIdleTimer(hwndDlg);

            // Free the memory allocated for the codeword.
            (void)LocalFree((HLOCAL)GetWindowLong(hwndDlg, DWL_USER));

            if(s_fIsEmergencyNum)
            {
                // Clean up. If we had an eCall in the codeword field,
                // restore the power timeout.
                (void)SHSetPowerTimeoutForLock(TRUE);
            }

            fHandled = TRUE;
            break;
        }
    }

    return fHandled;
}


// Summary:
//   Window proc for the codeword control.
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
//   The codeword control is subclassed here so that we can 
//     send DTMFs to the phone during an emergency call.
// 
LRESULT CodewordSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Used to indicate if we are sending DTMF tones
    static BOOL s_fInDTMF = FALSE;

    // Use default of 0 to indicate that we handled the message.
    LRESULT lRes = 0;

    // On keydown we send the DTMFs.
    // Only if this is changing states from up to down.
        if (g_fInEmergencyCall)
        {
            if (   WM_KEYDOWN == uMsg 
                && !(KF_REPEAT & HIWORD(lParam)))
            {
                // Start sending the virtual key as a DTMF.
                s_fInDTMF = SUCCEEDED (PhoneSendDTMFStart (MapVKeyToChar (LOWORD (wParam))));
            }
            else
            if (s_fInDTMF && WM_KEYUP == uMsg)
            {
                // Stop the DTMF tone
                (void)PhoneSendDTMFStop();
            }
        }

    // Allow normal window proc to handle all messages.
    WNDPROC pfnOrigProc = (WNDPROC)GetWindowLong(hwnd, GWL_USERDATA);
    lRes = CallWindowProc(pfnOrigProc, hwnd, uMsg, wParam, lParam);

    return lRes;
}
