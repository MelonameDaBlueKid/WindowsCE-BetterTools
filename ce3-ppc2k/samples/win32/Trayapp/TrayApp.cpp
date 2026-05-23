// TrayApp.cpp : Defines the entry point for the application.
//
/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <commctrl.h>
#include <aygshell.h>

#define TRAY_NOTIFYICON WM_USER + 2001
#define WMO_PALMTRAYAPP WM_USER + 2002
#define ID_TRAY	5000

// === Function Prototypes ====================================================

BOOL WINAPI MainDlgProc( HWND, UINT, WPARAM, LPARAM );

// === Global Variables =======================================================

HINSTANCE g_hInstance;
HWND g_hMainDlg;

BOOL g_WinHide = FALSE;
BOOL g_PalmTrayAppActive = FALSE;

// Tray Icons and Notification ------------------------------

BOOL TrayMessage(HWND hwnd, DWORD dwMessage, UINT uID, HICON hIcon, PTSTR pszTip)
{
  BOOL res = FALSE;
  NOTIFYICONDATA tnd;
  
  tnd.cbSize		= sizeof(NOTIFYICONDATA);
  tnd.hWnd		= hwnd;
  tnd.uID			= uID;
  tnd.uFlags		= NIF_MESSAGE|NIF_ICON; //|NIF_TIP;
  tnd.uCallbackMessage	= TRAY_NOTIFYICON;
  tnd.hIcon		= hIcon;
  tnd.szTip[0] = '\0';
  
  res = Shell_NotifyIcon(dwMessage, &tnd);
  return res;
}

void TrayIconDelete(HWND hwnd, UINT uID, HICON hIcon, PTSTR pszTip)
{
  TrayMessage(hwnd, NIM_DELETE, uID, hIcon, NULL);
}

void TrayIconModify(HWND hwnd, UINT uID, HICON hIcon, PTSTR pszTip) //animate icons
{
  TrayMessage(hwnd, NIM_MODIFY, uID, hIcon, NULL);
}

void TrayIconAdd(HWND hwnd, UINT uID, HICON hIcon, PTSTR pszTip)
{
  TrayMessage(hwnd, NIM_ADD, uID,  hIcon, NULL);
}


// === Application Entry Point ================================================

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrev, LPTSTR lpCmd, int nShow )
{
  int retcode;
  
  g_hInstance = hInstance;   //  Save instance handle in global
  InitCommonControls();
  
  retcode = DialogBox( g_hInstance, MAKEINTRESOURCE(IDD_PALMTRAYAPP), NULL, (DLGPROC)MainDlgProc );
  
  return( FALSE );
}

// === Main Window (dialog) Proc ==============================================
BOOL WINAPI MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
  switch( msg )
  {
    
	case WM_CLOSE:
			//Clean up on Close and remove tray icons
      TrayIconDelete(hDlg, ID_TRAY, LoadIcon( g_hInstance, MAKEINTRESOURCE(APP_ICON) ), NULL);
      EndDialog( hDlg, TRUE );
      return( TRUE );

	case WM_INITDIALOG:
      g_hMainDlg = hDlg;
      //On Rapier devices you normally create all Dialog's as fullscreen dialog's
      // with an OK button in the upper corner. 
      SHINITDLGINFO shidi;
      // Create a Done button and size it.
      shidi.dwMask = SHIDIM_FLAGS;
      shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
      shidi.hDlg = hDlg;
      //initialzes the dialog based on the dwFlags parameter
      SHInitDialog(&shidi);
      //Set Tray Icon
      TrayIconAdd(hDlg, ID_TRAY, LoadIcon( g_hInstance, MAKEINTRESOURCE(APP_ICON) ), NULL);
      SetForegroundWindow(hDlg);	// make us come to the front
      return( TRUE );
      
    case WM_COMMAND:
      {
        switch (GET_WM_COMMAND_ID(wParam,lParam))
        {
          
        case IDCANCEL:
          {
            g_PalmTrayAppActive = FALSE;
            TrayIconDelete(hDlg, ID_TRAY, LoadIcon( g_hInstance, MAKEINTRESOURCE(APP_ICON) ), NULL);
            EndDialog( hDlg, TRUE );
            return( TRUE );
          }
          break;
          
        case IDOK:
          {
            //Hide window 
            if (!g_WinHide)
            {
              ShowWindow(hDlg, SW_HIDE);
              g_WinHide = TRUE;
            }
            //Active state
            PostMessage(hDlg, WM_COMMAND, (WPARAM)WMO_PALMTRAYAPP, 0); 
            return( TRUE );               
          }
          break;
        }
      }
      
    case TRAY_NOTIFYICON:
      switch (lParam)
      {
      case WM_LBUTTONDOWN:
        if (wParam == ID_TRAY)
        {
          g_PalmTrayAppActive = FALSE;
          if (g_WinHide)
          {
            ShowWindow(hDlg, SW_SHOW);
            SetForegroundWindow(hDlg);	// make us come to the front
            g_WinHide = FALSE;
          } else {
            g_WinHide = TRUE;
          }
        }
      }
      break;
      
      break;
      
  }
  return( FALSE );
}

