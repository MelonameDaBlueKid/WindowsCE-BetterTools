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

#include <windows.h>
#include <aygshell.h>
#include <Strsafe.h>
#include "FullScreen.h"
#include "resource.h"

#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

HINSTANCE g_hInstance = NULL;
SHMENUBARINFO g_mbi;
INT g_iMenuHeight = 0; // Height of the softkey bar
BOOL g_bFullScreen = FALSE; // Full screen mode

BOOL InitDialog             ( const HWND hDlg );
BOOL CALLBACK DialogProc    ( const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam );

//
//  FUNCTION: IsSmartphone2003SEOrOlder
//
//  PURPOSE:  Determine whether we're running on a Smartphone 2003 
//            Second Edition (or older) device.
//
BOOL IsSmartphone2003SEOrOlder()
{
    BOOL bRet = FALSE;
    TCHAR szPlatform[64];
    OSVERSIONINFO osvi = {0};
    
    if (TRUE == SystemParametersInfo(SPI_GETPLATFORMTYPE, ARRAYSIZE(szPlatform), szPlatform, 0))
    {
        if (0 == _tcsicmp(TEXT("Smartphone"), szPlatform)) 
        {
            osvi.dwOSVersionInfoSize = sizeof(osvi);
            GetVersionEx(&osvi);
            
            // 2003 Second Edition runs on CE version 4.21
            if (4 >= osvi.dwMajorVersion && 21 >= osvi.dwMinorVersion)
            {
                bRet = TRUE;
            }
        }
    }
    return bRet;
}

//
//  FUNCTION: HideShellUI
//
//  PURPOSE:  Hide Shell UI components
//
void HideShellUI
(
    HWND hWnd,      // In: Window
    BOOL bHide      // In: FALSE to show. TRUE to hide.
)
{
    DWORD dwState;

    dwState = bHide
                ? (SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON)
                : (SHFS_SHOWTASKBAR | SHFS_SHOWSIPBUTTON);

    // Show/Hide Shell UI
    SHFullScreen(hWnd, dwState); 

    // We need to hide the tray manually for 2003 SE 
    // and earlier versions of Smartphone.
    if (IsSmartphone2003SEOrOlder())
    {
        HWND hwndTray = FindWindow(L"Tray", NULL);
        if (hwndTray)
        {
            HWND pos = bHide ? HWND_BOTTOM : HWND_TOP;
            SetWindowPos(hwndTray, pos, 0, 0, 0, 0, 
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
    }                
}

//
//  FUNCTION: SetSoftkeyBarForFullScreen
//
//  PURPOSE:  Setup the softkey for full screen/non full screen mode
//
void SetSoftkeyBarForFullScreen
(
    HWND hwndSoftKeyBar,    // In: Softkeybar
    BOOL bFullScreen        // In: TRUE = set for full screen. FALSE = undo
)
{
    if (bFullScreen)
    {    
        // Move softkey bar off-screen. Don't hide it because
        // a hidden softkey bar will not receive key override
        // messages.   
        SetWindowPos(hwndSoftKeyBar, 
                      NULL,
                      -1, -1,
                      0, 0,
                      SWP_NOZORDER | SWP_NOACTIVATE                    
                      );
    }
    else
    {
        // Move softkey bar on-screen.
        int iSoftkeysHeight = g_iMenuHeight;

        SetWindowPos(hwndSoftKeyBar, 
                      NULL,
                      0, 
                      GetSystemMetrics(SM_CYSCREEN) - iSoftkeysHeight,
                      GetSystemMetrics(SM_CXSCREEN), 
                      iSoftkeysHeight,
                      SWP_NOZORDER | SWP_NOACTIVATE                    
                      );
    }

    // Override/Undo softkeys for key press notifications, so we can
    // display taskbar & softkeys on SK1/SK2 press in full screen.
    DWORD dwBits;
    dwBits = bFullScreen 
                ? SHMBOF_NODEFAULT | SHMBOF_NOTIFY
                : 0;
   
    SendMessage(hwndSoftKeyBar, 
                SHCMBM_OVERRIDEKEY, 
                VK_TSOFT1,
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, dwBits));
    SendMessage(hwndSoftKeyBar, 
                SHCMBM_OVERRIDEKEY, 
                VK_TSOFT2,
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, dwBits));
}

//
//  FUNCTION: SizeFullScreen
//
//  PURPOSE:  Change the specified window size to full screen
//
void SizeFullScreen
(
    HWND hWnd,       // In: Window
    BOOL bFullScreen // In: TRUE = Size to full screen. FALSE = Undo
)
{   
    RECT rc;

    if (bFullScreen)
    {
        // Full screen size
        SetRect(&rc, 
                    0, 0, 
                    GetSystemMetrics(SM_CXSCREEN), 
                    GetSystemMetrics(SM_CYSCREEN));
    }
    else
    {
        // Normal size
        SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, FALSE);
        rc.bottom -= g_iMenuHeight;
    }

    MoveWindow( hWnd, 
        rc.left, rc.top,
        rc.right, rc.bottom,
        FALSE);
}

//
//  FUNCTION: FullScreen
//
//  PURPOSE:  Change the specified window to full screen
//
void FullScreen
(
    HWND hWnd,        // In: Window
    BOOL bFullScreen  // In: TRUE = Size to full screen. FALSE = Undo
)
{
    g_bFullScreen = bFullScreen;
    HideShellUI(hWnd, g_bFullScreen);
    SetSoftkeyBarForFullScreen(g_mbi.hwndMB, g_bFullScreen);
    SizeFullScreen(hWnd, g_bFullScreen);
}

//
//  FUNCTION: DialogProc
//
//  PURPOSE:  Processes mesasges for the main dialog box
//
BOOL CALLBACK DialogProc( const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam ) 
{   
    LRESULT lResult = 1;
    
    switch(msg)
    {
        case WM_ACTIVATE:
            {
                if (g_bFullScreen)
                {
                    FullScreen(hWnd, TRUE);
                }
                lResult = 0;
            }
            break;

        case WM_INITDIALOG:
            if ( !InitDialog( hWnd ) )
            {
                EndDialog ( hWnd, -1);
            }
            break;
    
        case WM_COMMAND:
            lResult = 0;
            switch (wParam)
            {
                case IDM_SK1:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;

                case IDM_SK2_SHFULL:
                    SendMessage(GetDlgItem(hWnd,IDC_EDIT), WM_SETTEXT, 0, (LPARAM)TEXT("Going Full Screen"));
                    // Enter full screen mode 
                    FullScreen(hWnd, TRUE);
                    break;

                case IDCANCEL:
                    if (g_bFullScreen)
                    {
                        SendMessage(GetDlgItem(hWnd,IDC_EDIT), WM_SETTEXT, 0, (LPARAM)L"[IDCANCEL] Exiting Full Screen");
                        // Switch to non full screen so the user has 
                        // a chance to interact with the menu.
                        FullScreen(hWnd, FALSE);
                    }
                    else
                    {
                        // We were not in full screen mode so just exit.
                        EndDialog(hWnd, TRUE);
                    }
                    return TRUE;
            
                default:
                    return DefWindowProc(hWnd, msg, wParam, lParam);
            }
            break;

        case WM_HOTKEY:
            switch(HIWORD(lParam))
            {                            
                case VK_TSOFT1:
                case VK_TSOFT2:
                    {
                        // if we are in full screen mode we want to exit
                        // when the user presses a softkey.
                        if (g_bFullScreen)
                        {    
                            SendMessage(GetDlgItem(hWnd,IDC_EDIT), WM_SETTEXT, 0, (LPARAM)L"[Softkey] Exiting Full Screen");
                            FullScreen(hWnd, FALSE);
                        }
                    }
                    break;
            }
            break;

        case WM_CLOSE:
            EndDialog(hWnd, TRUE);
            lResult = 0;
            break;

        case WM_DESTROY:
            EndDialog(hWnd, TRUE);
            lResult = 0;
            break;

        default:
            lResult = DefWindowProc(hWnd, msg, wParam, lParam);
            break;
          
    }
    return (lResult);
}


//
//  FUNCTION:   InitDialog
// 
//  PURPOSE:    Initialize the proper settings to create the dialog.
//
BOOL InitDialog( const HWND hWnd )
{
    // initialize dialog box, specifying that it should stretch full screen
    SHINITDLGINFO sid;
    RECT rc;
    ZeroMemory( &sid, sizeof( sid ) );
    sid.dwMask  = SHIDIM_FLAGS;
    sid.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
    sid.hDlg    = hWnd;

    // Initialize the dialog
    if ( !SHInitDialog( &sid ) )
    {
        return FALSE;
    }

    memset(&g_mbi, 0, sizeof(SHMENUBARINFO));
    g_mbi.cbSize = sizeof( SHMENUBARINFO );
    g_mbi.hwndParent = hWnd;
    g_mbi.nToolBarId = IDR_MENUBAR;
    g_mbi.hInstRes = g_hInstance;

    if (!SHCreateMenuBar( &g_mbi ))
    {
        return FALSE;
    }

    if (GetWindowRect(g_mbi.hwndMB, &rc))
    {
        g_iMenuHeight = rc.bottom - rc.top;
    }

    SetWindowText(hWnd, TEXT("Full Screen Sample"));
    return TRUE;
}

//
//  FUNCTION: WinMain(HANDLE, HANDLE, LPWSTR, int)
//
//  PURPOSE: Entry point for the application
//
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPWSTR    lpCmdLine,
                   int       nCmdShow)

{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    INT iResult         = 0;

    // store the hInstance in global
    g_hInstance = hInstance;
        
    // create the new dialog box
    iResult = DialogBox( g_hInstance, MAKEINTRESOURCE( IDD_MENU_DIALOG ), 0, (DLGPROC)DialogProc );

    return iResult;
}

