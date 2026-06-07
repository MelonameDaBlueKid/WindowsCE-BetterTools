//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

// ***************************************************************************
// CECamera.cpp
//
// Take pictures and videos using Camera native API.
//

#include <aygshell.h>
#include "Macros.h"
#include "resource.h"

// Macros

#define MAX_INITIAL_DIR                       MAX_PATH
#define MAX_FILE_NAME                         MAX_PATH
#define MAX_TITLE                             64
#define MAX_RESOLUTION_WIDTH                  10
#define MAX_RESOLUTION_HEIGHT                 10
#define MAX_VIDEO_TIME_LIMIT                  10

#define MAX_PLATFORM                          64
#define MAX_CLASSNAME                         64
#define MAX_MESSAGE                           MAX_PATH * 2

#define CECAMERA_DEFAULT_INITIAL_DIR          NULL
#define CECAMERA_DEFAULT_FILE_NAME            NULL
#define CECAMERA_DEFAULT_TITLE                NULL
#define CECAMERA_DEFAULT_STILL_QUALITY        CAMERACAPTURE_STILLQUALITY_DEFAULT
#define CECAMERA_DEFAULT_VIDEO_TYPES          CAMERACAPTURE_VIDEOTYPE_ALL
#define CECAMERA_DEFAULT_RESOLUTION_WIDTH     0
#define CECAMERA_DEFAULT_RESOLUTION_HEIGHT    0
#define CECAMERA_DEFAULT_VIDEO_TIME_LIMIT     0
#define CECAMERA_DEFAULT_MODE                 CAMERACAPTURE_MODE_STILL

#define CECAMERA_MUTEX_NAME                   TEXT("__CECAMERA_MUTEX__")
#define CECAMERA_MAINDLG_CLASSNAME            TEXT("Dialog")


// Global variables

BOOL                       g_bSmartphone  = FALSE;
HINSTANCE                  g_hInstance    = NULL;
HMENU                      g_hMainMenu    = NULL;
LPCTSTR                    g_szCaption;

CAMERACAPTURE_STILLQUALITY g_StillQuality = CECAMERA_DEFAULT_STILL_QUALITY;
CAMERACAPTURE_VIDEOTYPES   g_VideoTypes   = CECAMERA_DEFAULT_VIDEO_TYPES;
CAMERACAPTURE_MODE         g_Mode         = CECAMERA_DEFAULT_MODE;


// Forward declarations of the functions

BOOL IsSmartphone();
BOOL IsFocusOnEditControl();
BOOL InitDialog(HWND hwndDlg);
VOID StartCamera(HWND hwndDlg);
VOID ShowAboutBox(HWND hwndDlg);
VOID ResetOptions(HWND hwndDlg);
VOID ChangeMode(WORD wMode);
VOID ChangeStillQuality(WORD wStillQuality);
VOID ChangeVideoTypes(WORD wVideoTypes);
VOID ChangeOptions(HWND hwndDlg, WORD wOptions);
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


// ***************************************************************************
// Function Name: WinMain
//
// Purpose: Main entry point into the CECamera program
//
// Arguments: Standard WinMain arguments
//
// Return Values: 0
//
// Description:
//   Checks to see if a previous instance of the program is running,
//   and if it is not, it pops up a dialog box allowing the user to
//   specify the parameters for SHCameraCapture() API to launch Camera app.

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    HRESULT hr;
    HWND    hWndPreInstance;
    HANDLE  hMutex = NULL;

    // Load the caption of the main dialog from resource
    g_szCaption = (LPCTSTR)LoadString(hInstance, IDS_CAPTION, NULL, 0);
    CPR(g_szCaption);

    // Use a global named mutex to detect another instance of CECamera
    hMutex = CreateMutex(NULL, FALSE, CECAMERA_MUTEX_NAME);
    CPR(hMutex);

    if (ERROR_ALREADY_EXISTS == GetLastError())
    {
        // Already an instance running - attempt to switch to it and then exit
        hWndPreInstance = FindWindow(CECAMERA_MAINDLG_CLASSNAME, g_szCaption);
        CPR(hWndPreInstance);

        SetForegroundWindow(hWndPreInstance);
    }
    else
    {
        // Store the hInstance
        g_hInstance = hInstance;

        // Determine if platform is Smartphone
        g_bSmartphone = IsSmartphone();

        // Create the dialog box
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDLG), NULL, (DLGPROC)DialogProc);
    }

Error:
    if (NULL != hMutex)
    {
        // Release the global named mutex
        CloseHandle(hMutex);
    }

    return hr;
}

// ***************************************************************************
// Function Name: DialogProc
//
// Purpose: Message Handler for CECamera Dialog Box
//
// Arguments: Standard Dialog Procedure Arguments
//
// Return Values:
//   Returns TRUE if it processed the message, or FALSE if it did not.
//
// Description:
//   Dialog Procedure for the main CECamera Dialog.

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bHandled = TRUE;

    switch (uMsg)
    {
        case WM_INITDIALOG:
            // Make sure the dialog box was created
            if (!InitDialog(hwndDlg))
            {
                PostMessage(hwndDlg, WM_CLOSE, 0, 0);
            }

            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDM_START:
                    StartCamera(hwndDlg);
                    break;

                case IDM_ABOUT:
                    ShowAboutBox(hwndDlg);
                    break;

                case IDM_RESET:
                    ResetOptions(hwndDlg);
                    break;

                case IDM_MODE_STILL:
                    // Fall through

                case IDM_MODE_VIDEOONLY:
                    // Fall through

                case IDM_MODE_VIDEOWITHAUDIO:
                    ChangeMode(LOWORD(wParam));
                    break;

                case IDM_STILLQUALITY_DEFAULT:
                    // Fall through

                case IDM_STILLQUALITY_LOW:
                    // Fall through

                case IDM_STILLQUALITY_NORMAL:
                    // Fall through

                case IDM_STILLQUALITY_HIGH:
                    ChangeStillQuality(LOWORD(wParam));
                    break;

                case IDM_VIDEOTYPES_ALL:
                    // Fall through

                case IDM_VIDEOTYPES_STANDARD:
                    // Fall through

                case IDM_VIDEOTYPES_MESSAGING:
                    ChangeVideoTypes(LOWORD(wParam));
                    break;

                case IDC_CHECK_INITIAL_DIR:
                    // Fall through

                case IDC_CHECK_DEFAULT_FILE_NAME:
                    // Fall through

                case IDC_CHECK_TITLE:
                    // Fall through

                case IDC_CHECK_RESOLUTION:
                    // Fall through

                case IDC_CHECK_VIDEO_TIME_LIMIT:
                    ChangeOptions(hwndDlg, LOWORD(wParam));
                    break;

                case IDCANCEL:
                    // Fall through

                case IDM_EXIT:
                    PostMessage(hwndDlg, WM_CLOSE, 0, 0);
                    break;
            }
            break;

        case WM_CLOSE:
            EndDialog(hwndDlg, IDCANCEL);
            break;

        case WM_ACTIVATE:
            if (WA_ACTIVE == LOWORD(wParam))
            {
                // Set the focus to the main dialog if we are activated
                SetFocus(hwndDlg);
            }
            break;

        case WM_HOTKEY:
            if (g_bSmartphone && VK_TBACK == HIWORD(lParam))
            {
                if (IsFocusOnEditControl())
                {
                    // The current control with focus is an edit control
                    if (MOD_KEYUP & LOWORD(lParam))
                    {
                        // Delete a character on each KEYUP
                        SendMessage(GetFocus(), WM_CHAR, VK_BACK, 0);
                    }
                    else if (MOD_HOLD & LOWORD(lParam))
                    {
                        // Clear content from edit controls while pressing and holding the Back key
                        SetWindowText(GetFocus(), TEXT(""));
                    }
                }
                else if (MOD_KEYUP & LOWORD(lParam))
                {
                    // The current control with focus is not an edit control,
                    // close the dialog and then back to the previous application
                    PostMessage(hwndDlg, WM_CLOSE, 0, 0);
                    SHNavigateBack();
                }
            }
            break;

        default:
            // Specify that we didn't process this message, let the default
            // dialog box window procedure to process this message
            bHandled = FALSE;
            break;
    }

    return bHandled;
}

// **************************************************************************
// Function Name: IsSmartphone
//
// Purpose: Determine if platform is Smartphone
//
// Arguments: none
//
// Return Values:
//   TRUE if the current platform is a Smartphone platform
//   FALSE if the current platform is not a Smartphone platform
//
// Description:
//   This function retrieves the current platforms type and then
//   does a case insensitive string comparison.

BOOL IsSmartphone()
{
    HRESULT hr;
    TCHAR   szPlatform[MAX_PLATFORM] = { 0 };
    BOOL    bResult = FALSE;

    CBR(SystemParametersInfo(SPI_GETPLATFORMTYPE, ARRAYSIZE(szPlatform), szPlatform, 0));

    if (0 == _tcsicmp(szPlatform, TEXT("Smartphone")))
    {
        bResult = TRUE;
    }

Error:
    return bResult;
}

// **************************************************************************
// Function Name: IsFocusOnEditControl
//
// Purpose: Determine if the current control with focus is an edit control
//
// Arguments: none
//
// Return Values:
//   TRUE if the current control with focus is an edit control
//   FALSE if the current control with focus is not an edit control
//
// Description:
//   This function retrieves the window class name of the current control
//   with focus and then does a case insensitive string comparison.

BOOL IsFocusOnEditControl()
{
    HRESULT hr;
    TCHAR   szClassName[MAX_CLASSNAME] = { 0 };
    BOOL    bResult = FALSE;

    CBR(0 != GetClassName(GetFocus(), szClassName, ARRAYSIZE(szClassName)));

    if (0 == _tcsicmp(szClassName, TEXT("Edit")))
    {
        bResult = TRUE;
    }

Error:
    return bResult;
}

// ***************************************************************************
// Function Name: InitDialog
//
// Purpose: UI Initialization
//
// Arguments:
//   HWND hwndDlg - Handle to the main dialog
//
// Return Values:
//   TRUE if initialization was successful
//   FALSE if initialization failed
//
// Description:
//   The purpose of this function is to create a full-screen dialog box with
//   the Cancel button and creates a menu bar at the bottom of the dialog.

BOOL InitDialog(HWND hwndDlg)
{
    SHINITDLGINFO shidi;
    SHMENUBARINFO shmbi;
    BOOL          bSuccess = FALSE;

    // Specify that the dialog box should stretch full screen
    ZeroMemory(&shidi, sizeof(shidi));
    shidi.dwMask  = SHIDIM_FLAGS;
    shidi.hDlg    = hwndDlg;
    shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;

    // Adds the Cancel button to close the dialog with IDCANCEL
    // if the current platform is not a Smartphone platform
    if (!g_bSmartphone)
    {
        shidi.dwFlags |= SHIDIF_CANCELBUTTON;
    }

    if (SHInitDialog(&shidi))
    {
        // Set up the menu bar
        ZeroMemory(&shmbi, sizeof(shmbi));
        shmbi.cbSize     = sizeof(shmbi);
        shmbi.hwndParent = hwndDlg;
        shmbi.nToolBarId = IDR_MENUBAR;
        shmbi.hInstRes   = g_hInstance;

        if (SHCreateMenuBar(&shmbi))
        {
            if (NULL != shmbi.hwndMB)
            {
                // Get the main menu and store it
                g_hMainMenu = (HMENU)SendMessage(shmbi.hwndMB, SHCMBM_GETSUBMENU, 0, IDM_MENU);
                if (NULL != g_hMainMenu)
                {
                    // Set the window caption
                    SetWindowText(hwndDlg, g_szCaption);

                    // Limits the amount of text the user can enter into the edit controls
                    SendDlgItemMessage(hwndDlg, IDC_INITIAL_DIR, EM_LIMITTEXT, MAX_INITIAL_DIR, 0);
                    SendDlgItemMessage(hwndDlg, IDC_DEFAULT_FILE_NAME, EM_LIMITTEXT, MAX_FILE_NAME, 0);
                    SendDlgItemMessage(hwndDlg, IDC_TITLE, EM_LIMITTEXT, MAX_TITLE, 0);
                    SendDlgItemMessage(hwndDlg, IDC_RESOLUTION_WIDTH, EM_LIMITTEXT, MAX_RESOLUTION_WIDTH, 0);
                    SendDlgItemMessage(hwndDlg, IDC_RESOLUTION_HEIGHT, EM_LIMITTEXT, MAX_RESOLUTION_HEIGHT, 0);
                    SendDlgItemMessage(hwndDlg, IDC_VIDEO_TIME_LIMIT, EM_LIMITTEXT, MAX_VIDEO_TIME_LIMIT, 0);

                    // Specify all options as default value
                    ResetOptions(hwndDlg);

                    // In order to make Back work properly, it's necessary to
                    // override it and then call the appropriate SH API
                    if (g_bSmartphone)
                    {
                        SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK,
                                    MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY,
                                               SHMBOF_NODEFAULT | SHMBOF_NOTIFY));
                    }

                    bSuccess = TRUE;
                }
            }
        }
    }

    return bSuccess;
}

// ***************************************************************************
// Function Name: StartCamera
//
// Purpose: Launches Camera using Camera API with specified arguments
//
// Arguments:
//   HWND hwndDlg - Handle to the main dialog
//
// Return Values: none
//
// Description:
//   Calling SHCameraCapture() function to start Camera for
//   taking the pictures or videos.

VOID StartCamera(HWND hwndDlg)
{
    HRESULT         hr;
    HRESULT         hReturn;
    SHCAMERACAPTURE shcc;

    LONG            lCheckStateInitialDir;
    LONG            lCheckStateDefaultFileName;
    LONG            lCheckStateTitle;
    LONG            lCheckStateResolution;
    LONG            lCheckStateVideoTimeLimit;

    TCHAR           szInitialDir[MAX_INITIAL_DIR] = { 0 };
    TCHAR           szDefaultFileName[MAX_FILE_NAME] = { 0 };
    TCHAR           szTitle[MAX_TITLE] = { 0 };
    DWORD           dwResolutionWidth;
    DWORD           dwResolutionHeight;
    DWORD           dwVideoTimeLimit;

    LPCTSTR         szFormat;
    TCHAR           szMessage[MAX_MESSAGE] = { 0 };

    // Get the state of the checkboxs
    lCheckStateInitialDir = SendDlgItemMessage(hwndDlg, IDC_CHECK_INITIAL_DIR, BM_GETCHECK, 0, 0);
    lCheckStateDefaultFileName = SendDlgItemMessage(hwndDlg, IDC_CHECK_DEFAULT_FILE_NAME, BM_GETCHECK, 0, 0);
    lCheckStateTitle = SendDlgItemMessage(hwndDlg, IDC_CHECK_TITLE, BM_GETCHECK, 0, 0);
    lCheckStateResolution = SendDlgItemMessage(hwndDlg, IDC_CHECK_RESOLUTION, BM_GETCHECK, 0, 0);
    lCheckStateVideoTimeLimit = SendDlgItemMessage(hwndDlg, IDC_CHECK_VIDEO_TIME_LIMIT, BM_GETCHECK, 0, 0);

    // Get the user inputs of the edit controls
    GetDlgItemText(hwndDlg, IDC_INITIAL_DIR, szInitialDir, ARRAYSIZE(szInitialDir));
    GetDlgItemText(hwndDlg, IDC_DEFAULT_FILE_NAME, szDefaultFileName, ARRAYSIZE(szDefaultFileName));
    GetDlgItemText(hwndDlg, IDC_TITLE, szTitle, ARRAYSIZE(szTitle));

    dwResolutionWidth = GetDlgItemInt(hwndDlg, IDC_RESOLUTION_WIDTH, NULL, FALSE);
    dwResolutionHeight = GetDlgItemInt(hwndDlg, IDC_RESOLUTION_HEIGHT, NULL, FALSE);
    dwVideoTimeLimit = GetDlgItemInt(hwndDlg, IDC_VIDEO_TIME_LIMIT, NULL, FALSE);

    // Specify the arguments of SHCAMERACAPTURE
    ZeroMemory(&shcc, sizeof(shcc));
    shcc.cbSize             = sizeof(shcc);
    shcc.hwndOwner          = hwndDlg;
    shcc.pszInitialDir      = (BST_UNCHECKED == lCheckStateInitialDir) ? CECAMERA_DEFAULT_INITIAL_DIR : szInitialDir;
    shcc.pszDefaultFileName = (BST_UNCHECKED == lCheckStateDefaultFileName) ? CECAMERA_DEFAULT_FILE_NAME : szDefaultFileName;
    shcc.pszTitle           = (BST_UNCHECKED == lCheckStateTitle) ? CECAMERA_DEFAULT_TITLE : szTitle;
    shcc.StillQuality       = g_StillQuality;
    shcc.VideoTypes         = g_VideoTypes;
    shcc.nResolutionWidth   = (BST_UNCHECKED == lCheckStateResolution) ? CECAMERA_DEFAULT_RESOLUTION_WIDTH : dwResolutionWidth;
    shcc.nResolutionHeight  = (BST_UNCHECKED == lCheckStateResolution) ? CECAMERA_DEFAULT_RESOLUTION_HEIGHT : dwResolutionHeight;
    shcc.nVideoTimeLimit    = (BST_UNCHECKED == lCheckStateVideoTimeLimit) ? CECAMERA_DEFAULT_VIDEO_TIME_LIMIT : dwVideoTimeLimit;
    shcc.Mode               = g_Mode;

    // Call SHCameraCapture() function
    hReturn = SHCameraCapture(&shcc);

    // Check the return codes of the SHCameraCapture() function
    switch (hReturn)
    {
        case S_OK:
            // The method completed successfully.
            szFormat = (LPCTSTR)LoadString(g_hInstance, IDS_NOERROR, NULL, 0);
            CPR(szFormat);
            CHR(StringCchPrintf(szMessage, ARRAYSIZE(szMessage), szFormat, shcc.szFile));
            MessageBox(hwndDlg, szMessage, g_szCaption, MB_OK | MB_ICONINFORMATION);
            break;
        case S_FALSE:
            // The user canceled the Camera Capture dialog box.
            break;
        case E_INVALIDARG:
            // An invalid argument was specified.
            szFormat = (LPCTSTR)LoadString(g_hInstance, IDS_ERROR_INVALIDARG, NULL, 0);
            CPR(szFormat);
            MessageBox(hwndDlg, szFormat, g_szCaption, MB_OK | MB_ICONEXCLAMATION);
            break;
        case E_OUTOFMEMORY:
            // There is not enough memory to save the image or video.
            szFormat = (LPCTSTR)LoadString(g_hInstance, IDS_ERROR_OUTOFMEMORY, NULL, 0);
            CPR(szFormat);
            MessageBox(hwndDlg, szFormat, g_szCaption, MB_OK | MB_ICONSTOP);
            break;
        default:
            // An unknown error occurred.
            szFormat = (LPCTSTR)LoadString(g_hInstance, IDS_ERROR_UNKNOWN, NULL, 0);
            CPR(szFormat);
            CHR(StringCchPrintf(szMessage, ARRAYSIZE(szMessage), szFormat, hReturn));
            MessageBox(hwndDlg, szMessage, g_szCaption, MB_OK | MB_ICONSTOP);
            break;
    }

Error:
    return;
}

// ***************************************************************************
// Function Name: ShowAboutBox
//
// Purpose: Show program information
//
// Arguments:
//   HWND hwndDlg - Handle to the main dialog
//
// Return Values: none
//
// Description:
//   Display a message box for program information.

VOID ShowAboutBox(HWND hwndDlg)
{
    HRESULT hr;
    LPCTSTR szAbout;

    // Load the about string from resource and display it
    szAbout = (LPCTSTR)LoadString(g_hInstance, IDS_ABOUT, NULL, 0);
    CPR(szAbout);

    MessageBox(hwndDlg, szAbout, g_szCaption, MB_OK);

Error:
    return;
}

// ***************************************************************************
// Function Name: ResetOptions
//
// Purpose: Resets all settings as the default value
//
// Arguments:
//   HWND hwndDlg - Handle to the main dialog
//
// Return Values: none
//
// Description:
//   Resets all settings as the default value and updates UI.

VOID ResetOptions(HWND hwndDlg)
{
    HRESULT hr;

    // Uncheck all checkboxs to specify the options using the default value
    SendDlgItemMessage(hwndDlg, IDC_CHECK_INITIAL_DIR, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hwndDlg, IDC_CHECK_DEFAULT_FILE_NAME, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hwndDlg, IDC_CHECK_TITLE, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hwndDlg, IDC_CHECK_RESOLUTION, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hwndDlg, IDC_CHECK_VIDEO_TIME_LIMIT, BM_SETCHECK, BST_UNCHECKED, 0);

    // Set the default value for the options
    CBR(SetDlgItemText(hwndDlg, IDC_INITIAL_DIR, CECAMERA_DEFAULT_INITIAL_DIR));
    CBR(SetDlgItemText(hwndDlg, IDC_DEFAULT_FILE_NAME, CECAMERA_DEFAULT_FILE_NAME));
    CBR(SetDlgItemText(hwndDlg, IDC_TITLE, CECAMERA_DEFAULT_TITLE));
    CBR(SetDlgItemInt(hwndDlg, IDC_RESOLUTION_WIDTH, CECAMERA_DEFAULT_RESOLUTION_WIDTH, 0));
    CBR(SetDlgItemInt(hwndDlg, IDC_RESOLUTION_HEIGHT, CECAMERA_DEFAULT_RESOLUTION_HEIGHT, 0));
    CBR(SetDlgItemInt(hwndDlg, IDC_VIDEO_TIME_LIMIT, CECAMERA_DEFAULT_VIDEO_TIME_LIMIT, 0));

    // Disable the edit controls since specify using default settings
    EnableWindow(GetDlgItem(hwndDlg, IDC_INITIAL_DIR), FALSE);
    EnableWindow(GetDlgItem(hwndDlg, IDC_DEFAULT_FILE_NAME), FALSE);
    EnableWindow(GetDlgItem(hwndDlg, IDC_TITLE), FALSE);
    EnableWindow(GetDlgItem(hwndDlg, IDC_RESOLUTION_WIDTH), FALSE);
    EnableWindow(GetDlgItem(hwndDlg, IDC_RESOLUTION_HEIGHT), FALSE);
    EnableWindow(GetDlgItem(hwndDlg, IDC_VIDEO_TIME_LIMIT), FALSE);

    // Checks the menu item and makes it a radio item
    CBR(CheckMenuRadioItem(GetSubMenu(g_hMainMenu, 0), IDM_MODE_STILL, IDM_MODE_VIDEOWITHAUDIO, IDM_MODE_STILL, MF_BYCOMMAND));
    CBR(CheckMenuRadioItem(GetSubMenu(g_hMainMenu, 1), IDM_STILLQUALITY_DEFAULT, IDM_STILLQUALITY_HIGH, IDM_STILLQUALITY_DEFAULT, MF_BYCOMMAND));
    CBR(CheckMenuRadioItem(GetSubMenu(g_hMainMenu, 2), IDM_VIDEOTYPES_ALL, IDM_VIDEOTYPES_MESSAGING, IDM_VIDEOTYPES_ALL, MF_BYCOMMAND));

    // Set the global variables as default value
    g_StillQuality = CECAMERA_DEFAULT_STILL_QUALITY;
    g_VideoTypes   = CECAMERA_DEFAULT_VIDEO_TYPES;
    g_Mode         = CECAMERA_DEFAULT_MODE;

Error:
    return;
}

// ***************************************************************************
// Function Name: ChangeMode
//
// Purpose: Changes "Mode" parameter of SHCameraCapture()
//
// Arguments:
//   WORD wMode - The identifier of the menu item
//
// Return Values: none
//
// Description:
//   Changes "Mode" parameter of SHCameraCapture(),
//   also checks the specified menu item of "Mode".

VOID ChangeMode(WORD wMode)
{
    HRESULT hr;

    // Update the menu item "Mode"
    CBR(CheckMenuRadioItem(GetSubMenu(g_hMainMenu, 0), IDM_MODE_STILL, IDM_MODE_VIDEOWITHAUDIO, wMode, MF_BYCOMMAND));

    // Set the global variables as user specified value
    switch (wMode)
    {
        case IDM_MODE_STILL:
            g_Mode = CAMERACAPTURE_MODE_STILL;
            break;
        case IDM_MODE_VIDEOONLY:
            g_Mode = CAMERACAPTURE_MODE_VIDEOONLY;
            break;
        case IDM_MODE_VIDEOWITHAUDIO:
            g_Mode = CAMERACAPTURE_MODE_VIDEOWITHAUDIO;
            break;
        default:
            CBR(FALSE);
            break;
    }

Error:
    return;
}

// ***************************************************************************
// Function Name: ChangeStillQuality
//
// Purpose: Changes "StillQuality" parameter of SHCameraCapture()
//
// Arguments:
//   WORD wStillQuality - The identifier of the menu item
//
// Return Values: none
//
// Description:
//   Changes "StillQuality" parameter of SHCameraCapture(),
//   also checks the specified menu item of "StillQuality".

VOID ChangeStillQuality(WORD wStillQuality)
{
    HRESULT hr;

    // Update the menu item "StillQuality"
    CBR(CheckMenuRadioItem(GetSubMenu(g_hMainMenu, 1), IDM_STILLQUALITY_DEFAULT, IDM_STILLQUALITY_HIGH, wStillQuality, MF_BYCOMMAND));

    // Set the global variables as user specified value
    switch (wStillQuality)
    {
        case IDM_STILLQUALITY_DEFAULT:
            g_StillQuality = CAMERACAPTURE_STILLQUALITY_DEFAULT;
            break;
        case IDM_STILLQUALITY_LOW:
            g_StillQuality = CAMERACAPTURE_STILLQUALITY_LOW;
            break;
        case IDM_STILLQUALITY_NORMAL:
            g_StillQuality = CAMERACAPTURE_STILLQUALITY_NORMAL;
            break;
        case IDM_STILLQUALITY_HIGH:
            g_StillQuality = CAMERACAPTURE_STILLQUALITY_HIGH;
            break;
        default:
            CBR(FALSE);
            break;
    }

Error:
    return;
}

// ***************************************************************************
// Function Name: ChangeVideoTypes
//
// Purpose: Changes "VideoTypes" parameter of SHCameraCapture()
//
// Arguments:
//   WORD wVideoTypes - The identifier of the menu item
//
// Return Values: none
//
// Description:
//   Changes "VideoTypes" parameter of SHCameraCapture(),
//   also checks the specified menu item of "VideoTypes".

VOID ChangeVideoTypes(WORD wVideoTypes)
{
    HRESULT hr;

    // Update the menu item "VideoTypes"
    CBR(CheckMenuRadioItem(GetSubMenu(g_hMainMenu, 2), IDM_VIDEOTYPES_ALL, IDM_VIDEOTYPES_MESSAGING, wVideoTypes, MF_BYCOMMAND));

    // Set the global variables as user specified value
    switch (wVideoTypes)
    {
        case IDM_VIDEOTYPES_ALL:
            g_VideoTypes = CAMERACAPTURE_VIDEOTYPE_ALL;
            break;
        case IDM_VIDEOTYPES_STANDARD:
            g_VideoTypes = CAMERACAPTURE_VIDEOTYPE_STANDARD;
            break;
        case IDM_VIDEOTYPES_MESSAGING:
            g_VideoTypes = CAMERACAPTURE_VIDEOTYPE_MESSAGING;
            break;
        default:
            CBR(FALSE);
            break;
    }

Error:
    return;
}

// ***************************************************************************
// Function Name: ChangeOptions
//
// Purpose: Enable/Disable user input of the edit controls
//
// Arguments:
//   HWND hwndDlg  - Handle to the main dialog
//   WORD wOptions - The identifier of the control
//
// Return Values: none
//
// Description:
//   Enable/Disable user input of the edit controls for allowing/disallowing
//   the user to specify the settings of the Camera API.

VOID ChangeOptions(HWND hwndDlg, WORD wOptions)
{
    HRESULT hr;
    LONG    lCheckState;
    BOOL    bEnable;

    // Get the check state of the check box
    lCheckState = SendDlgItemMessage(hwndDlg, wOptions, BM_GETCHECK, 0, 0);
    bEnable = (BST_UNCHECKED == lCheckState) ? FALSE : TRUE;

    // Enable/Disable user input of the edit controls
    switch (wOptions)
    {
        case IDC_CHECK_INITIAL_DIR:
            EnableWindow(GetDlgItem(hwndDlg, IDC_INITIAL_DIR), bEnable);
            break;
        case IDC_CHECK_DEFAULT_FILE_NAME:
            EnableWindow(GetDlgItem(hwndDlg, IDC_DEFAULT_FILE_NAME), bEnable);
            break;
        case IDC_CHECK_TITLE:
            EnableWindow(GetDlgItem(hwndDlg, IDC_TITLE), bEnable);
            break;
        case IDC_CHECK_RESOLUTION:
            EnableWindow(GetDlgItem(hwndDlg, IDC_RESOLUTION_WIDTH), bEnable);
            EnableWindow(GetDlgItem(hwndDlg, IDC_RESOLUTION_HEIGHT), bEnable);
            break;
        case IDC_CHECK_VIDEO_TIME_LIMIT:
            EnableWindow(GetDlgItem(hwndDlg, IDC_VIDEO_TIME_LIMIT), bEnable);
            break;
        default:
            CBR(FALSE);
            break;
    }

Error:
    return;
}
