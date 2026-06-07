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
// TrayApp.cpp : Defines the entry point for the application.
//
#include "stdafx.h"

#define TRAY_NOTIFYICON WM_USER + 2001
#define WMO_PALMTRAYAPP WM_USER + 2002
#define ID_TRAY	5000

// === Function Prototypes ====================================================

BOOL WINAPI MainDlgProc(
    HWND, 
    UINT, 
    WPARAM, 
    LPARAM
    );

// === Global Variables =======================================================

HINSTANCE g_hInst;

BOOL g_bWinHide = FALSE;
BOOL g_bPalmTrayAppActive = FALSE;

// Tray Icons and Notification ------------------------------

BOOL TrayMessage(
    HWND hwnd, 
    DWORD dwMessage,
    UINT uID, 
    HICON hIcon, 
    PTSTR pszTip
    )
{
  BOOL res = FALSE;
  NOTIFYICONDATA tnd;
  
  tnd.cbSize = sizeof(NOTIFYICONDATA);
  tnd.hWnd = hwnd;
  tnd.uID = uID;
  tnd.uFlags = NIF_MESSAGE|NIF_ICON;
  tnd.uCallbackMessage = TRAY_NOTIFYICON;
  tnd.hIcon = hIcon;
  tnd.szTip[0] = '\0';
  
  res = Shell_NotifyIcon(dwMessage, &tnd);
  return res;
}

void TrayIconDelete(
    HWND hwnd, 
    UINT uID, 
    HICON hIcon, 
    PTSTR pszTip
    )
{
    TrayMessage(hwnd, NIM_DELETE, uID, hIcon, NULL);
}

void TrayIconModify(
    HWND hwnd, 
    UINT uID,
    HICON hIcon, 
    PTSTR pszTip
    ) 
{
    //animate icons
    TrayMessage(hwnd, NIM_MODIFY, uID, hIcon, NULL);
}

void TrayIconAdd(
    HWND hwnd, 
    UINT uID, 
    HICON hIcon, 
    PTSTR pszTip
    )
{
    TrayMessage(hwnd, NIM_ADD, uID,  hIcon, NULL);
}


// === Application Entry Point ================================================

int APIENTRY WinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrev, 
    LPTSTR lpCmdLine, 
    int nShowCmd
    )
{
    int retcode;

    g_hInst = hInstance;   //  Save instance handle in global
    InitCommonControls();

    retcode = DialogBox( g_hInst, MAKEINTRESOURCE(IDD_PALMTRAYAPP), NULL, (DLGPROC)MainDlgProc );

    return(retcode);
}

// === Main Window (dialog) Proc ==============================================
BOOL WINAPI MainDlgProc(
    HWND hDlg, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    )
{
    switch (Msg)
    {

    case WM_CLOSE:
        //Clean up on Close and remove tray icons
        TrayIconDelete(hDlg, ID_TRAY, LoadIcon( g_hInst, MAKEINTRESOURCE(APP_ICON) ), NULL);
        EndDialog(hDlg, TRUE);
        return(TRUE);

    case WM_INITDIALOG:
        //On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
        // with an OK button in the upper corner. 
        SHINITDLGINFO shidi;
        // Create a Done button and size it.
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
        shidi.hDlg = hDlg;
        //initialzes the dialog based on the dwFlags parameter
        SHInitDialog(&shidi);
        //Set Tray Icon
        TrayIconAdd(hDlg, ID_TRAY, LoadIcon(g_hInst, MAKEINTRESOURCE(APP_ICON)), NULL);
        SetForegroundWindow(hDlg);	// make us come to the front
        return(TRUE);
  
    case WM_COMMAND:
        switch (GET_WM_COMMAND_ID(wParam,lParam))
        {

        case IDCANCEL:
            g_bPalmTrayAppActive = FALSE;
            TrayIconDelete(hDlg, ID_TRAY, LoadIcon( g_hInst, MAKEINTRESOURCE(APP_ICON) ), NULL);
            EndDialog( hDlg, TRUE );
            return(TRUE);
            break;

        case IDOK:
            //Hide window 
            if (FALSE == g_bWinHide)
            {
                ShowWindow(hDlg, SW_HIDE);
                g_bWinHide = TRUE;
            }
            //Active state
            PostMessage(hDlg, WM_COMMAND, (WPARAM)WMO_PALMTRAYAPP, 0); 
            return(TRUE);               
            break;
        }

    case TRAY_NOTIFYICON:
        switch (lParam)
        {
        case WM_LBUTTONDOWN:
            if (ID_TRAY == wParam)
            {
                g_bPalmTrayAppActive = FALSE;
                if (TRUE == g_bWinHide)
                {
                    ShowWindow(hDlg, SW_SHOW);
                    SetForegroundWindow(hDlg);	// make us come to the front
                    g_bWinHide = FALSE;
                } 
                else 
                {
                    g_bWinHide = TRUE;
                }
            }
            break;
        }

        break;
  
    }
    return( FALSE );
}

