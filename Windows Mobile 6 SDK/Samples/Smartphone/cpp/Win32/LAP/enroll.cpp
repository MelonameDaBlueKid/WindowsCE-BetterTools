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
#include "password_history.h"

#define DEFAULT_ENROLL_TIMEOUT    120000 // 2 minutes.
#define MIN_ENROLL_TIMEOUT        10000  // 10 seconds.

// Timeout options in minutes.
static const DWORD g_rgTimeout[] = { 1, 5, 15, 30, 60, 90, 120, 12 * 60, 24 * 60 };

static const int c_rgFont[] = 
{
    IDC_CHK_ACTIVE,
    IDC_STATIC_PASSWORD_TYPE,
    IDC_LBL_PASSWORD,
    IDC_LBL_CONFIRM
};

BOOL    g_fEnrolled;   // Flag if we completed enrollment.


// Summary:
//   Creates and displays the enrollment dialog.
//
// Parameters:
//  hwndParent -- Handle to the window that will own the 
//   enrollment dialog.
//  fSecure -- TRUE if enrollment should be forced.
//
// Returns:
//   TRUE if enrollment was completed successfully. If an error occurs 
//   or the user cancels, returns FALSE.
//
//
// Remarks:
//   If enrollment is forced, the user will not be able to cancel
//     or exit the dialog without making changes. Changes are always
//     required to conform to all policies.
// 
BOOL DoEnrollment(HWND hwndParent, BOOL fSecure)
{
    // Reset the global enrollment flag.
    g_fEnrolled = FALSE;

    (void)DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_ENROLL), 
        hwndParent, EnrollDlgProc, (LPARAM)fSecure);

    return g_fEnrolled;
}       


// Summary:
//   Dialog proc for the enrollment dialog. Handles all messages.
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
BOOL EnrollDlgProc(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam)
{
    PASSWDINFO *ppwi;
    BOOL fHandled = FALSE;

    // Get saved password info (if it exists)
    ppwi = (PASSWDINFO*)GetWindowLong(hwndDlg, DWL_USER);
    if(NULL == ppwi && WM_INITDIALOG != uMsg)
    {
        return fHandled;
    }

    // Signal that this dialog is mainly for input purposes.
    SHInputDialog(hwndDlg, uMsg, wParam);

    // Handle specific message.
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            // Store the window handle.
            STOREWINDOW(LAP_WINDOW_ENROLL, hwndDlg);

            // Load password info from registry.
            ppwi = (PASSWDINFO*)LocalAlloc(LMEM_FIXED, sizeof(PASSWDINFO));
            if(NULL == ppwi || FAILED(GetPasswordInfo(ppwi)))
            {
                // We can't access the password information so just end now.
                ASSERT(FALSE);
                (void)LocalFree(ppwi);
                (void)EndDialog(hwndDlg, IDCANCEL);
                return TRUE;
            }

            // Enforce policy settings within the password info.
            InitPasswordInfo(ppwi);

            // Set up the dialog controls.
            InitControls(hwndDlg, ppwi);

            // Set the secure flag if it was passed to the dialog.
            ppwi->bSecure = ppwi->bSecure || BOOLIFY(lParam);

            // Save a pointer to the password info.
            (void)SetWindowLong(hwndDlg, DWL_USER, (LONG)ppwi);

            // Size dialog full-screen.
            SHINITDLGINFO sidi;
            sidi.dwMask = SHIDIM_FLAGS;
            sidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
            sidi.hDlg = hwndDlg;
            (void)SHInitDialog(&sidi);

            // Create a bold font based on the system font.
            ppwi->hFont = (HFONT)GetStockObject(SYSTEM_FONT);
            if(NULL != ppwi->hFont)
            {
                LOGFONT lf;
                GetObject(ppwi->hFont, sizeof(LOGFONT), &lf);
                lf.lfWeight = FW_BOLD;
                ppwi->hFont = CreateFontIndirect(&lf);
            }

            // Bold all label controls.
            if(NULL != ppwi->hFont)
            {
                for(int i=0; i < ARRAYSIZE(c_rgFont); i++)
                {
                    (void)SendDlgItemMessage(hwndDlg, c_rgFont[i], 
                        WM_SETFONT, (WPARAM)ppwi->hFont, FALSE);
                }
            }

            // Create menubar
            SHMENUBARINFO smbi;
            memset(&smbi, 0, sizeof(smbi));
            smbi.cbSize = sizeof(smbi);
            smbi.hwndParent = hwndDlg;
            smbi.nToolBarId = 
                ppwi->bSecure ? IDR_SECURE_MENUBAR : IDR_COMMON_MENUBAR;
            smbi.hInstRes = g_hInst;
            (void)SHCreateMenuBar(&smbi);

            // Register the back hotkey for the edit controls.
            (void)SendMessage(smbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
                SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

            // Change the policy settings if necessary.
            // FrequencyValue can't be 0.
            if(FT_Minutes_Idle == ppwi->Policy.uFrequencyType && 
                0 == ppwi->Policy.uFrequencyValue)
            {
                ppwi->Policy.uFrequencyValue = 1;
            }

            // Queue up a message to handle enabling this 
            // dialog after it's displayed.
            (void)PostMessage(hwndDlg, WM_APP_ENABLE, 0, 0);

            fHandled = TRUE;
            break;
        }

        case WM_APP_ENABLE:
        {
            // The only thing we do when enabling is display the 
            // policy dialog. We want it here because the 
            // enrollment dialog should display behind it.
            if(ppwi->bSecure)
            {
                // Only display this if we're in secure mode.
                (void)DisplayPolicyUpdate(hwndDlg);
            }

            // Start the idle timer.
            ResetIdleTimer(hwndDlg);

            fHandled = TRUE;
            break;
        }

        case WM_ACTIVATE:
        {
            // Our window is being deactivated.
            // We don't want to leave the enrollment dialog up, so
            // we may need to save settings and close the dialog.
            if(WA_INACTIVE == LOWORD(wParam))
            {
                DWORD   dwThreadID;
               
                // Get the process ID for our thread.
                dwThreadID = GetWindowThreadProcessId(hwndDlg, NULL);
                ASSERT(dwThreadID != 0);

                // lParam will be null if another process' window is being 
                // activated but the test still works since 0 won't equal 
                // our thread id.  Any window coming up on our thread 
                // should be something we want to deal with and not exit
                // the CPL.
                if(dwThreadID != GetWindowThreadProcessId((HWND)lParam, 
                    NULL))
                {
                    // Must confirm that this isn't changing property pages.
                    // The PropertySheet code sends this message with 
                    // lParam = 0.
                    if(!IsChild(GetForegroundWindow(), hwndDlg))
                    {                    
                        // Do NOT NOT NOT even think about calling 
                        // MessageBox during WM_ACTIVATE processing.  
                        // We'll post ourselves a message, and take 
                        // care of this momentarily.
                        (void)PostMessage(hwndDlg, WM_APP_DEACTIVATE, 0, 0);
                        fHandled = TRUE;
                    }
                }
            }
            break;
        }
        
        case WM_APP_DEACTIVATE:
        {
            // Our dialog has been deactivated by another thread,
            // so we need to attempt to save settings and exit.
            fHandled = TRUE;

            // Do all the WM_APP_ONOK processing
            if(BOOLIFY(SendMessage(hwndDlg, WM_APP_ONOK, 0, 0)))
            {
                // End the dialog if we saved successfully or we are 
                // giving up.
                // We have to use cancel, otherwise the dialog will 
                // try to call the WM_APP_ONOK handler again.
                (void)EndDialog(hwndDlg, IDCANCEL);
            }

            break;
        }

        case WM_APP_ONOK:
        {
            // Set the result flag to default to failure.
            (void)SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);

            // Make a copy of our existing password settings.
            PASSWDINFO pwiNew;
            memcpy(&pwiNew, ppwi, sizeof(PASSWDINFO));

            // Load the settings from the dialog into our new copy.
            GetDlgPasswordInfo(hwndDlg, &pwiNew);

            // Compare to check if anything has changed.
            if(IsPasswordInfoChanged(ppwi, &pwiNew))
            {
                // Determine if we need to save changes.
                BOOL fSave = TRUE;

                // User only gets to choose if we're not in secure mode.
                if(!ppwi->bSecure)
                {
                    // Prompt user to save or cancel.
                    if(S_FALSE == DisplayQuestion(hwndDlg, IDS_SAVE_TITLE, 
                        IDS_SAVE_TEXT))
                    {
                        // User chose not to save changes.
                        fSave = FALSE;

                        // Set the return value so we can exit.
                        (void)SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
                    }
                }

                // Attempt to save settings.
                if(fSave)
                {
                    // Verify the password info.
                    if(VerifyPasswordInfo(hwndDlg, &pwiNew))
                    {
                        // Save settings to registry.
                        if(SUCCEEDED(SavePasswordInfo(&pwiNew)))
                        {
                            // Set the global enrolled flag.
                            g_fEnrolled = TRUE;

                            // We successfully enrolled so save a copy 
                            // of the policy settings now.
                            (void)SaveLKGPolicy(&ppwi->Policy);

                            // Reset the update flag because we've enrolled.
                            g_fPolicyRequiresUpdate = FALSE;

                            // Save the old password to password history store
                            AddPasswordToHistory (&pwiNew);

                            // Set the return value.
                            (void)SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
                            
                        }
                        else
                        {
                            // An error occurred while saving.
                            (void)DisplayMessage(hwndDlg, IDS_ERROR_TITLE, 
                                IDS_ERROR_SAVE);

                            // Allow the user to exit on error
                            // even if we're in secure mode.
                            (void)SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
                        }
                    }
                }
            }
            else
            {
                // Nothing has changed or the user chose not to
                // save. Act as if the user cancelled.
                (void)SendMessage(hwndDlg, WM_APP_ONCANCEL, 0, 0);
            }

            fHandled = TRUE;
            break;
        }

        case WM_TIMER:
        {
            if(IDT_IDLE_TIMEOUT == wParam)
            {
                // The user hasn't changed anything in 
                // a while so close the dialog.
                // There may be a child dialog so close that first.
                HWND hwndChild = GetActiveWindow();
                if(hwndDlg == GetWindow(hwndChild, GW_OWNER))
                {
                    // Always send cancel to specify 'No' if necessary.
                    (void)PostMessage(hwndChild, WM_COMMAND, 
                        MAKEWPARAM(IDCANCEL, 0), 0);
                }
                (void)EndDialog(hwndDlg, IDCANCEL);

                fHandled = TRUE;
            }
            break;
        }

        case WM_APP_ONCANCEL:
        {
            // Do not allow user cancel in secure mode.
            if(ppwi->bSecure)
            {
                // User is not allowed to cancel -- display message.
                (void)DisplayMessage(hwndDlg, IDS_ERROR_TITLE, 
                    IDS_ERROR_CANCEL);

                // If our thread lost activation during the
                // message display, let the cancel continue.
                if(GetWindowThreadProcessId(hwndDlg, NULL) != 
                    GetWindowThreadProcessId(GetActiveWindow(), NULL))
                {
                    ppwi->bSecure = FALSE;
                }
            }

            // Set the return value.
            (void)SetWindowLong(hwndDlg, DWL_MSGRESULT, !ppwi->bSecure);

            // Set fHandled: FALSE will prevent cancel.
            fHandled = !ppwi->bSecure;
            break;
        }

        case WM_DESTROY:
        {
            // Cleanup the saved password info.
            if(NULL != ppwi)
            {
                // Delete the font we created.
                if(NULL != ppwi->hFont)
                {
                    (void)DeleteObject((HGDIOBJ)(HFONT)(ppwi->hFont));
                }
                (void)LocalFree(ppwi);
            }
            (void)SetWindowLong(hwndDlg, DWL_USER, 0);

            // Cleanup idle timer if it's still going.
            KillIdleTimer(hwndDlg);

            fHandled = TRUE;
            break;
        }

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDOK:
                {
                    // Reset the idle timer.
                    ResetIdleTimer(hwndDlg);

                    // Process WM_APP_ONOK message to see if we can exit.
                    fHandled = BOOLIFY(SendMessage(hwndDlg, WM_APP_ONOK, 
                        0, 0));
                    if(fHandled)
                    {
                        // Exit the dialog.
                        (void)EndDialog(hwndDlg, IDOK);
                    }
                    break;
                }

                case IDCANCEL:
                {
                    // Reset the idle timer.
                    ResetIdleTimer(hwndDlg);

                    // Process WM_APP_ONCANCEL message to see if we can exit.
                    fHandled = BOOLIFY(SendMessage(hwndDlg, 
                        WM_APP_ONCANCEL, 0, 0));
                    if(fHandled)
                    {
                        // Exit the dialog.
                        (void)EndDialog(hwndDlg, IDCANCEL);
                    }
                    break;
                }

                case IDC_CHK_ACTIVE:
                {
                    if(HIWORD(wParam) == BN_CLICKED)
                    {
                        // Password on/off status is changed.
                        // Make sure all other controls are 
                        // enabled/disabled accordingly.
                        EnableControls(hwndDlg, ppwi);

                        // Reset the idle timer.
                        ResetIdleTimer(hwndDlg);

                        fHandled = TRUE;
                    }
                    break;
                }

                case IDC_PASSWORD:
                case IDC_CONFIRM:
                {
                    if(EN_CHANGE == HIWORD(wParam))
                    {
                        // Password text has changed.
                        // If this is the first edit, 
                        // clear the other control.
                        if(!ppwi->bPasswordChanged)
                        {
                            ppwi->bPasswordChanged = TRUE;
                            (void)SetDlgItemText(hwndDlg, 
                                (IDC_PASSWORD == LOWORD(wParam) ? 
                                IDC_CONFIRM : IDC_PASSWORD), 
                                K_SZRESETTEXT);
                        }

                        // Reset the idle timer.
                        ResetIdleTimer(hwndDlg);

                        fHandled = TRUE;
                    }
                    else if(EN_SETFOCUS == HIWORD(wParam))
                    {
                        // If the user is focusing on this item 
                        // for the first time highlight the text.
                        if(!ppwi->bPasswordChanged)
                        {
                            (void)SendDlgItemMessage(hwndDlg, 
                                LOWORD(wParam), EM_SETSEL, 0, -1);
                            fHandled = TRUE;
                        }
                    }
                    break;
                }
            }
            break;
        }

        case WM_HOTKEY:
        {
            // Send back key to controls.
            if(VK_TBACK == HIWORD(lParam))
            {
                SHSendBackToFocusWindow(uMsg, wParam, lParam);
                fHandled = TRUE;
            }                
            break;
        }
    }

    return fHandled;
}


// Summary:
//   Initializes user password settings using policy where necessary.
//
// Parameters:
//  ppwi -- Pointer to a populated PASSWDINFO structure.
//
// Remarks:
//   
//       Element           Initialization
//       ------------------------------------------
//       bPasswordOn       Forced to TRUE if policy requires that a password is set.
//     
//     
//       bSecure           Forced to TRUE if policy requires that enrollment be updated.
//     
//     
//       szPassword        Forced to "********" if a password is already set.
//     
//     
//       uFrequencyType    Forced to FT_Minutes_Idle if policy requires that the timeout is fixed.
//     
//     
//       uFrequencyValue   Forced to the frequency value specified by policy if policy requires that the timeout is fixed.
//
//
void InitPasswordInfo(PASSWDINFO* ppwi)
{
    // Set the secure flag if policy requires updating.
    PASSWDPOLICY lkgPolicy;
    if(ppwi->Policy.bPasswordOn && SUCCEEDED(GetLKGPolicy(&lkgPolicy)))
    {
        ppwi->bSecure = PolicyRequiresUpdate(ppwi, &lkgPolicy);
    }

    // If the password was actually active (and not just forced on by 
    // policy), set the password string for the UI (don't set if we're 
    // forcing a type change).
    if(ppwi->bPasswordOn) 
    {
        (void)StringCchCopy(ppwi->szPassword, ARRAYSIZE(ppwi->szPassword), 
            TEXT("********"));
    }

    // Only check policy if password is forced on.
    if(ppwi->Policy.bPasswordOn)
    {
        // Force password on.
        ppwi->bPasswordOn = TRUE;

        // Idle timeout.
        if(FT_Minutes_Idle == ppwi->Policy.uFrequencyType)
        {
            ppwi->uFrequencyType = FT_Minutes_Idle;
            ppwi->uFrequencyValue = ppwi->Policy.uFrequencyValue;
        }
    }
}


// Summary:
//   Initializes the controls on the enrollment dialog.
//
// Parameters:
//  hwndDlg -- Handle to the enrollment dialog.
//  ppwi -- Pointer to a populated PASSWDINFO structure.
//
// Remarks:
//   
//       Control            Initialization
//       ------------------------------------------------
//     
//       IDC_CHK_ACTIVE     Checked if bPasswordOn is TRUE. Disabled if policy requires that a password is set.
//     
//     
//       IDC_ACTIVEPERIOD   Populated with a default list of timeouts in minutes or hours. Set to the current timeout value. If the current timeout value is not in the default list of timeouts, it is added. Disabled if policy requires that the timeout is fixed.
//     
//     
//       IDC_PASSWORD       Populated with the existing password (we only use "*******". Limited to MAX_PASSWORD characters.
//     
//     
//       IDC_CONFIRM        Populated with the existing password (we only use "*******". Limited to MAX_PASSWORD characters.
//
//
void InitControls(HWND hwndDlg, PASSWDINFO* ppwi)
{
    HWND    hwndCtl;
    UINT    uSel = 0;
    LPCTSTR pszResource, pszFormat;
    int     nIndex;
    
    // ACTIVE CHECKBOX.
    hwndCtl = GetDlgItem(hwndDlg, IDC_CHK_ACTIVE);
    ASSERT(NULL != hwndCtl);
    (void)SendMessage(hwndCtl, BM_SETCHECK, ppwi->bPasswordOn ? BST_CHECKED : BST_UNCHECKED, 0);
    // Disable active checkbox if policy requires a password.
    (void)EnableWindow(hwndCtl, !ppwi->Policy.bPasswordOn);

    // TIMEOUT COMBOBOX.
    hwndCtl = GetDlgItem(hwndDlg, IDC_ACTIVEPERIOD);
    ASSERT(NULL != hwndCtl);
    // Reset all content.
    (void)SendMessage(hwndCtl, LB_RESETCONTENT, 0, 0);
    // Fill with default options.
    // Add the current option if it isn't a default.
    BOOL fAddedCurrent = FALSE;
    for(int i=0; i < ARRAYSIZE(g_rgTimeout) + 1; i++)
    {
        DWORD  dwTimeout;
        UINT   uTimeID;
        UINT   uFormatID = IDS_TIME_WHOLE;
        float  fTimeValue;
        TCHAR  szTimeout[MAX_PATH];

        // If this is the last option, we have to make sure
        // the current value was added.
        if(i == ARRAYSIZE(g_rgTimeout))
        {
            // If the current value has already been added
            // or idle timer isn't turned on, exit the loop now.
            if(fAddedCurrent || 
                (ppwi->uFrequencyValue <= g_rgTimeout[i-1]) || 
                (FT_Minutes_Idle != ppwi->uFrequencyType))
            {
                break;
            }

            // The current value hasn't been added, and it's 
            // greater than all of the default values. 
            // Insert the current value at the end.
            dwTimeout = ppwi->uFrequencyValue;
        }
        else
        {
            dwTimeout = g_rgTimeout[i];
        }

        // If we haven't already added the current value, see if
        // it should go immediately before this value.
        if(!fAddedCurrent && ppwi->uFrequencyValue < dwTimeout && 
            (i == 0 || ppwi->uFrequencyValue > g_rgTimeout[i-1]) && 
            (FT_Minutes_Idle == ppwi->uFrequencyType))
        {
            // Add the current value to the drop-down.
            dwTimeout = ppwi->uFrequencyValue;
            // Decrement counter so next iteration will 
            // continue with the current default value.
            i--; 
        }

        // If the timeout is greater than an hour, express it
        // in terms of hours (1 hour, 1.5 hours, etc).
        if(dwTimeout >= 60)
        {
            // Use hours.
            // We round to the tenth of an hour.
            if(3 < dwTimeout % 60 && 57 > dwTimeout % 60)
            {
                // This is not a round number of hours.
                uFormatID = IDS_TIME_FRACTION;
            }

            // Convert minutes to hours.
            fTimeValue = (float)dwTimeout / 60;

            // If this is exactly 1 hour use "hour", 
            // otherwise use "hours".
            if(dwTimeout == 60)
            {
                uTimeID = IDS_HOUR;
            }
            else
            {
                uTimeID = IDS_HOURS;
            }
        }
        else
        {
            // Use minutes. If this is exactly 1 minute
            // use "minute", otherwise use "minutes".
            fTimeValue = (float)dwTimeout;
            if(dwTimeout == 1)
            {
                uTimeID = IDS_MINUTE;
            }
            else
            {
                uTimeID = IDS_MINUTES;
            }
        }

        // Load the resource strings.
        pszResource = CELOADSZ(uTimeID);
        pszFormat = SafeCELOADSZ(uFormatID);
        ASSERT(NULL != pszResource && NULL != pszFormat);

        // Format the complete time string.
        if(SUCCEEDED(StringCchPrintf(szTimeout, ARRAYSIZE(szTimeout), 
            pszFormat, fTimeValue, pszResource)))
        {
            // Add this string to the drop-down.
            nIndex = SendMessage(hwndCtl, LB_ADDSTRING, 0, 
                (LPARAM)szTimeout);
            if(CB_ERR != nIndex)
            {
                // Add the timeout in muntes as the item data.
                (void)SendMessage(hwndCtl, LB_SETITEMDATA, 
                    nIndex, (LPARAM)dwTimeout);

                // If the timeout we're adding is the current
                // selection, make a note so we can select it later.
                if(ppwi->uFrequencyValue == dwTimeout)
                {
                    // Set the selection
                    fAddedCurrent = TRUE;
                    uSel = nIndex;
                }
            }
        }
    }
    
    // Set currently selected timeout.
    (void)SendMessage(hwndCtl, LB_SETCURSEL, (WPARAM)uSel, 0);
    
    // Disable timeout combobox if policy sets the timeout.
    (void)EnableWindow(hwndCtl, 
        FT_Minutes_Idle != ppwi->Policy.uFrequencyType);

    // Limit text length.
    (void)SendDlgItemMessage(hwndDlg, IDC_PASSWORD, EM_LIMITTEXT, 
        (WPARAM)MAX_PASSWORD, 0);
    (void)SendDlgItemMessage(hwndDlg, IDC_CONFIRM,  EM_LIMITTEXT, 
        (WPARAM)MAX_PASSWORD, 0);

    // Have control values enable/disable other controls.
    EnableControls(hwndDlg, ppwi);

    // PASSWORD/CONFIRM EDIT BOXES.
    if(ppwi->bPasswordOn && NULL != ppwi->szPassword)
    {
        // This will only set "********".
        (void)SetDlgItemText(hwndDlg, IDC_PASSWORD, ppwi->szPassword);
        (void)SetDlgItemText(hwndDlg, IDC_CONFIRM, ppwi->szPassword);
    }

    // Reset the password changed flag.
    ppwi->bPasswordChanged = FALSE;
}


// Summary:
//   Enables and disables dialog controls based on selected values.
//
// Parameters:
//  hwndDlg -- Handle to the enrollment dialog.
//  ppwi -- Pointer to a populated PASSWDINFO structure.
void EnableControls(HWND hwndDlg, PASSWDINFO* ppwi)
{
    HWND hwndCtl;

    // Top-level password activation.
    // All controls depend on this one.
    BOOL fEnable = (BST_CHECKED == 
        SendDlgItemMessage(hwndDlg, IDC_CHK_ACTIVE, BM_GETCHECK, 0, 0));
    

    // Enable timeout drop-down only if policy doesn't set it.
    if(FT_Minutes_Idle != ppwi->Policy.uFrequencyType)
    {
        hwndCtl = GetDlgItem(hwndDlg, IDC_ACTIVEPERIOD);
        ASSERT(NULL != hwndCtl);
        (void)EnableWindow(hwndCtl, fEnable);
    }            

    // Enable password edit box.
    hwndCtl = GetDlgItem(hwndDlg, IDC_PASSWORD);
    ASSERT(NULL != hwndCtl);
    (void)EnableWindow(hwndCtl, fEnable);
    // Also reset the value.
    (void)SetWindowText(hwndCtl, K_SZRESETTEXT);

    // Enable confirm edit box.
    hwndCtl = GetDlgItem(hwndDlg, IDC_CONFIRM);
    ASSERT(NULL != hwndCtl);
    (void)EnableWindow(hwndCtl, fEnable);
    // Also reset the value.
    (void)SetWindowText(hwndCtl, K_SZRESETTEXT);

    // We updated the password text so flag that
    // the password has changed.
    ppwi->bPasswordChanged = TRUE;
}


// Summary:
//   Retrieves the user password settings from the enrollment dialog.
//
// Parameters:
//  hwndDlg -- Handle to the enrollment dialog.
//  ppwi -- Pointer to a populated PASSWDINFO structure.
void GetDlgPasswordInfo(HWND hwndDlg, PASSWDINFO* ppwi)
{
    // Set defaults before loading values (all default to 0).
    ppwi->bPasswordOn = FALSE;          // Password not active.
    ppwi->uFrequencyType = FT_Every_FV; // Timeout is off.
    ppwi->uFrequencyValue = 0;          // Timeout is 0 minutes.
    ppwi->szPassword[0] = TEXT('\0');   // Clear password string.

    // Activation checkbox.
    ppwi->bPasswordOn = (BST_CHECKED == 
        SendDlgItemMessage(hwndDlg, IDC_CHK_ACTIVE, BM_GETCHECK, 0, 0));
    if(ppwi->bPasswordOn)
    {
        // Timeout is on automatically if password is on.
        ppwi->uFrequencyType = FT_Minutes_Idle;

        // Timeout combobox.
        HWND hwndCtl = GetDlgItem(hwndDlg, IDC_ACTIVEPERIOD);
        ASSERT(NULL != hwndCtl);
        int nIndex = SendMessage(hwndCtl, LB_GETCURSEL, 0, 0);
        if(CB_ERR != nIndex)
        {
            // Get and validate timeout setting.
            ppwi->uFrequencyValue = (UINT)SendMessage(hwndCtl, 
                LB_GETITEMDATA, nIndex, 0);
            if(MAX_FREQUENCY_VALUE < ppwi->uFrequencyValue)
            {
                ppwi->uFrequencyValue = MAX_FREQUENCY_VALUE;
            }
        }        

        // Password.
        (void)GetDlgItemText(hwndDlg, IDC_PASSWORD, ppwi->szPassword, 
            ARRAYSIZE(ppwi->szPassword));
    }
}


// Summary:
//   Determines if the user password settings have changed.
//
// Parameters:
//  ppwiOld -- Pointer to a populated PASSWDINFO structure 
//   containing the password settings at the time of initialization.
//   Policy is ignored.
//  ppwiNew -- Pointer to a populated PASSWDINFO structure
//   containing the current password settings. Policy is ignored.
//
// Returns:
//   TRUE if the password settings have changed; otherwise FALSE.
//
//
// Remarks:
//   If we are in secure mode (forced enrollment), this function
//     does not take timeout value into account.
// 
BOOL IsPasswordInfoChanged(PASSWDINFO* ppwiOld, PASSWDINFO* ppwiNew)
{
    return (ppwiOld->bPasswordOn != ppwiNew->bPasswordOn) || 
        (ppwiNew->bPasswordOn && // Password must be on to handle any other changes.
        (ppwiOld->bPasswordChanged ||
        (!ppwiOld->bSecure && // We only care about idle timeout if not in secure mode.
        ((ppwiOld->uFrequencyType != ppwiNew->uFrequencyType) || 
        (ppwiOld->uFrequencyValue != ppwiNew->uFrequencyValue)))));
}


// Summary:
//   Validates all password settings against policy.
//
// Parameters:
//  hwndDlg -- Handle to the dialog box.
//  ppwi -- Pointer to a populated PASSWDINFO structure.
//
// Returns:
//   Returns TRUE if all password data are valid; otherwise FALSE.
//
//
// Remarks:
//   The dialog should not allow users to change the password on/off 
//   or timeout settings in violation of policy. If these settings do not 
//   conform to policy, no error message will be displayed, but the 
//   function will return FALSE.
// 
BOOL VerifyPasswordInfo(HWND hwndDlg, PASSWDINFO* ppwi)
{
    INT nErrorID = 0;
    LPCTSTR pszEmergencyNumber = NULL;

    // Only need to verify if password settings have changed 
    // and we're setting to active.
    if(ppwi->bPasswordChanged && ppwi->bPasswordOn)
    {
        // A password must be present
        // and meet strength requirements.
        if(TEXT('\0') == ppwi->szPassword[0] || !ValidatePassword(ppwi))
        {
            // Use the "invalid password" error message.
            nErrorID = IDS_ERROR_STRENGTH;
        }
        else if(PhoneIsEmergencyNumber(FALSE, ppwi->szPassword, &pszEmergencyNumber))
        {
            // The password may not contain an emergency phone number.
            nErrorID = IDS_ERROR_ENUMBER;
        }
        else if (!PasswordHistoryCheck(ppwi))
        {
            nErrorID = IDS_HISTORY_REQUIREMENT;
        }
        else
        {
            // The password must be confirmed.
            TCHAR pszConfirm[MAX_PASSWORD + 1];
            pszConfirm[0] = TEXT('\0');
            (void)GetDlgItemText(hwndDlg, IDC_CONFIRM, pszConfirm, ARRAYSIZE(pszConfirm));
            if(0 != _tcscmp(ppwi->szPassword, pszConfirm))
            {
                // Use the "confirmation doesn't match" error message.
                nErrorID = IDS_ERROR_CONFIRM;
            }
        }
    }
    
    // All policies must be met.
    if(0 == nErrorID && // Don't overwrite previous specific errors.
        (ppwi->Policy.bPasswordOn && !ppwi->bPasswordOn) ||
        ((FT_Minutes_Idle == ppwi->Policy.uFrequencyType) &&
        ppwi->Policy.uFrequencyValue != ppwi->uFrequencyValue))
    {
        // No specific error message because user should never be 
        // able to circumvent policy.
        nErrorID  = -1; 
    }

    // Show error message if necessary.
    if(nErrorID > 0)
    {
        LPTSTR pszText = NULL;
        BOOL   bAllocated = FALSE;
        size_t cchText = 0;
        size_t cchInsert = 0;
        size_t cbText = STRSAFE_MAX_CCH * sizeof(TCHAR); // Start with maximum size.

        // Load specified error message.
        LPCTSTR pszResource = CELOADSZ(nErrorID);
        if(NULL != pszResource)
        {
            if(IDS_ERROR_ENUMBER == nErrorID)
            {
                // Format with the specific emergency number.
                // Calculate length of this complete message in a safe way.
                if(SUCCEEDED(StringCchLength(pszEmergencyNumber, 
                    STRSAFE_MAX_CCH, &cchInsert)) &&
                    SUCCEEDED(StringCchLength(pszResource, 
                    STRSAFE_MAX_CCH, &cchText)))
                {
                    // Add length of emergency number string and NULL terminator.
                    cchText += cchInsert + 1;

                    // Check for integer overflow.
                    if(cchText > cchInsert) 
                    {
                        // Convert to bytes.
                        cbText = cchText * sizeof(TCHAR);

                        // Check for integer overflow.
                        if(cbText < cchText) 
                        {
                            // String was too long
                            // so use maximum allowed.
                            cbText = STRSAFE_MAX_CCH * sizeof(TCHAR);
                        }
                    }
                }

                // Allocate string for complete error message.
                pszText = (LPTSTR)LocalAlloc(LMEM_FIXED, cbText);
                if(NULL != pszText)
                {
                    // Set flag so we know to free this memory later.
                    bAllocated = TRUE;

                    // Initialize result text.
                    pszText[0] = TEXT('\0');

                    // Format the string to include the emergency number.
                    (void)StringCbPrintfEx(pszText, cbText, NULL, 
                        NULL, STRSAFE_IGNORE_NULLS, pszResource,
                        pszEmergencyNumber);
                }
            }
            else if(IDS_ERROR_STRENGTH == nErrorID)
            {
                // Need to format the strong password error.
                LPCTSTR pszComplexity = SafeCELOADSZ(MAX_COMPLEXITY == 
                    ppwi->Policy.uComplexity ? IDS_ERROR_ALL : IDS_ERROR_ATLEAST);
                // Calculate length of this complete message in a safe way.
                if(SUCCEEDED(StringCchLength(pszComplexity, 
                    STRSAFE_MAX_CCH, &cchInsert)) &&
                    SUCCEEDED(StringCchLength(pszResource, 
                    STRSAFE_MAX_CCH, &cchText)))
                {
                    // Add length of complexity string and NULL terminator.
                    cchText += cchInsert + 1;

                    // Check for integer overflow.
                    if(cchText > cchInsert) 
                    {
                        // Add space for two numbers.
                        cchText += (2 * MAX_INT_LENGTH);

                        // Check for integer overflow.
                        if(cchText > (2 * MAX_INT_LENGTH)) 
                        {
                            // Convert to bytes.
                            cbText = cchText * sizeof(TCHAR);

                            // Check for integer overflow.
                            if(cbText < cchText) 
                            {
                                // String was too long
                                // so use maximum allowed.
                                cbText = 
                                    STRSAFE_MAX_CCH * sizeof(TCHAR);
                            }
                        }
                    }
                }

                // Allocate string for complete error message.
                pszText = (LPTSTR)LocalAlloc(LMEM_FIXED, cbText);
                if(NULL != pszText)
                {
                    // Set flag so we know to free this memory later.
                    bAllocated = TRUE;

                    // Initialize result text.
                    pszText[0] = TEXT('\0');

                    // Format the string one time for min length and 
                    // complexity description.
                    (void)StringCbPrintfEx(pszText, cbText, NULL, 
                        NULL, STRSAFE_IGNORE_NULLS, pszResource,
                        ppwi->Policy.uMinLength, pszComplexity);

                    // If we're not using the maximum complexity,
                    // we have to specify the complexity degree
                    // in the error message.
                    if(MAX_COMPLEXITY != ppwi->Policy.uComplexity)
                    {
                        // Allocate another string to dump the 
                        // resulting formatting into.
                        LPTSTR pszFormat = (LPTSTR)LocalAlloc(LMEM_FIXED, 
                            cbText);
                        if(NULL != pszFormat)
                        {
                            // Initialize the formatting string.
                            pszFormat[0] = TEXT('\0');

                            // Copy the error message to the new
                            // format buffer.
                            (void)StringCchCopy(pszFormat, cbText, pszText);
                            
                            // Format a second time to insert the 
                            // complexity number.
                            (void)StringCchPrintf(pszText, cbText, 
                                pszFormat, ppwi->Policy.uComplexity);
                            (void)LocalFree(pszFormat);
                        }
                    }
                }
            }
            else if (IDS_HISTORY_REQUIREMENT == nErrorID)
            {
                // Format with the password history size
                // Calculate length of this complete message in a safe way.
                if (SUCCEEDED(StringCchLength(pszResource, STRSAFE_MAX_CCH, &cchText)))
                {
                    // Add max number length +1 for NUL terminator
                    if (safeIntUAdd (cchText, MAX_INT_LENGTH +1, &cchText))
                    {
                        // Convert to byte count
                        if (!safeIntUMul (cchText, sizeof (TCHAR), &cbText))
                        {
                            cbText = STRSAFE_MAX_CCH * sizeof(TCHAR);
                        }
                    }
                    else
                    {
                        cbText = STRSAFE_MAX_CCH * sizeof(TCHAR);
                    }
                }

                // Allocate string for complete error message.
                pszText = (LPTSTR)LocalAlloc(LMEM_FIXED, cbText);
                if(NULL != pszText)
                {
                    // Set flag so we know to free this memory later.
                    bAllocated = TRUE;

                    // Initialize result text.
                    pszText[0] = TEXT('\0');

                    // Format the string to include the emergency number.
                    (void)StringCbPrintfEx (pszText, cbText, NULL, 
                        NULL, STRSAFE_IGNORE_NULLS, pszResource,
                        ppwi->Policy.uNumberOfPasswords);
                }
            }

            // Show the error message.
            (void)DisplayMessageEx(hwndDlg, IDS_ERROR_TITLE, 
                bAllocated ? pszText : pszResource);

            // Free the pszText buffer if we had to allocate it.
            if(bAllocated)
            {
                (void)LocalFree(pszText);
            }
        }

        // Clear the password/confirm text.
        HWND hwndPassword = GetDlgItem(hwndDlg, IDC_PASSWORD);
        ASSERT(NULL != hwndPassword);
        (void)SetWindowText(hwndPassword, K_SZRESETTEXT);
        (void)SetDlgItemText(hwndDlg, IDC_CONFIRM, K_SZRESETTEXT);

        // Since we failed, we should have displayed a message.
        // If our thread lost activation during the message display,
        // close the dialog.
        if(GetWindowThreadProcessId(hwndDlg, NULL) != 
            GetWindowThreadProcessId(GetActiveWindow(), NULL))
        {
            (void)PostMessage(hwndDlg, WM_APP_DEACTIVATE, 0, 0);
        }
        else
        {
            // Set focus back to password to re-enter
            (void)SendMessage(hwndDlg, WM_NEXTDLGCTL, 
                (WPARAM)hwndPassword, (LPARAM)TRUE);
        }
    }

    // Return TRUE if no error was encountered.
    return (nErrorID == 0);
}

// Summary:
//   Validates password string for length and complexity.
//
// Parameters:
//  ppwi -- Pointer to a populated PASSWDINFO structure.
//
// Returns:
//   Returns TRUE if the password string is valid; otherwise FALSE.
//
//
// Remarks:
//   The password string must meet the minimum length requirement
//     as supplied by policy or using the default (7). The password must
//     also meet complexity requirements, containing at least the 
//     number of characters of different types specified by policy or
//     using the default (3).
//     types.
// 
BOOL ValidatePassword(PASSWDINFO* ppwi)
{
    BOOL    bValidated = FALSE; // Assume not validated.
    WORD*   pwCharType = NULL;
    DWORD   dwParts = 0;
    WORD    wTypes = 0;

    // Password must meet minimum length requirement.
    size_t cchPassword = 0;
    if(SUCCEEDED(StringCchLength(ppwi->szPassword, 
        ARRAYSIZE(ppwi->szPassword), &cchPassword)) && 
        (cchPassword >= ppwi->Policy.uMinLength))
    {   
        // Get the types of each character in the password.
        pwCharType = (WORD *)LocalAlloc(LMEM_FIXED, 
            cchPassword * sizeof(WORD));
        ASSERT(pwCharType);
        if(GetStringTypeEx(LOCALE_SYSTEM_DEFAULT, CT_CTYPE1, 
            ppwi->szPassword, cchPassword, pwCharType))
        {
            // Walk the password, counting the element types.
            for(UINT i=0; i < cchPassword && 
                dwParts < ppwi->Policy.uComplexity; i++) 
            {
                // Get only the types that haven't been seen before.
                WORD wNewTypes = (pwCharType[i] & ~wTypes);
                if(wNewTypes & C1_UPPER) dwParts++;
                else if(wNewTypes & C1_LOWER) dwParts++;
                else if(wNewTypes & C1_DIGIT) dwParts++;
                else if(wNewTypes & C1_PUNCT) dwParts++;
                wTypes |= pwCharType[i];
            }

            // Number of parts must meet the minimum complexity requirement.
            if(dwParts >= ppwi->Policy.uComplexity)
            {
                // Only set the verified flag to TRUE if we got 
                // past all the checks.
                bValidated = TRUE;
            }
        }
    
        (void)LocalFree(pwCharType);
    }

    return bValidated;
}
