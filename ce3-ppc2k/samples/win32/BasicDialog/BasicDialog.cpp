/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
// BasicDialog.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BasicDialog.h"
#include <commctrl.h>


#define MAX_LOADSTRING 100
//Menu Bar Height
#define MENU_HEIGHT 26

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HWND			hwndMain; //The main window
HWND			g_hwndBasicDialog; //The basic dialog for the controls
TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	BasicDlgProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
  MSG msg;
  
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_BASICDIALOG, szWindowClass, MAX_LOADSTRING);
  // Look for running instance of application
  if (FindWindow(szWindowClass, szTitle)){
    SetForegroundWindow(FindWindow(szWindowClass, szTitle));
    return FALSE;
  }
  
  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow)) 
  {
    return FALSE;
  }
  
  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
  WNDCLASS	wc;
  
  wc.style			= CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc		= (WNDPROC) WndProc;
  wc.cbClsExtra		= 0;
  wc.cbWndExtra		= 0;
  wc.hInstance		= hInstance;
  wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BASICDIALOG));
  wc.hCursor			= 0;
  wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName		= 0;
  wc.lpszClassName	= szWindowClass;
  
  return RegisterClass(&wc);
}

//
//  FUNCTION: InitInstance(HANDLE, int)
//
//  PURPOSE: Saves instance handle and creates main window
//
//  COMMENTS:
//
//    In this function, we save the instance handle in a global variable and
//    create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance;		// Store instance handle in our global variable
  // Initialize global strings
  MyRegisterClass(hInstance, szWindowClass);
  
  hwndMain = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  
  if (!hwndMain){	
    return FALSE;
  }
  
  //When the main window is created using CW_USEDEFAULT the height of the menubar (if one
  // is created is not taken into account). So we resize the window after creating it
  // if a menubar is present
#if _WIN32_WCE > 211 //Rapier devices
  {
    RECT rc;
    GetWindowRect(hwndMain, &rc);
    rc.bottom -= MENU_HEIGHT;
    if (hwndCB)
      MoveWindow(hwndMain, rc.left, rc.top, rc.right, rc.bottom, FALSE);
  }
#endif
  
  ShowWindow(hwndMain, nCmdShow);
  UpdateWindow(hwndMain);
  
#if _WIN32_WCE < 212//non-Rapier devices
  if (hwndCB)
    CommandBar_Show(hwndCB, TRUE);
#endif
  
  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;
  RECT rect;
  
  switch (message) 
  {
		case WM_COMMAND:
      wmId    = LOWORD(wParam); 
      wmEvent = HIWORD(wParam); 
      // Parse the menu selections:
      switch (wmId)
      {
      case IDM_HELP_ABOUT:
        DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
        break;
      case IDM_FILE_EXIT:
        DestroyWindow(hWnd);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;
      case WM_CREATE:
        
#if _WIN32_WCE > 211 //Rapier devices
        //Create 'Rapier' type MenuBar
        SHMENUBARINFO mbi;
        
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hWnd;
        mbi.nToolBarId = IDM_MAIN_MENU;
        mbi.hInstRes   = hInst;
        mbi.nBmpId     = 0;
        mbi.cBmpImages = 0;	
        
        if (!SHCreateMenuBar(&mbi))
          MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
        hwndCB = mbi.hwndMB;
        
        // Create the DialogWindow and center it under the commandbar
        GetClientRect(hWnd, &rect);
        g_hwndBasicDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_BASICDIALOG), hWnd, (DLGPROC)BasicDlgProc); 
        if ( g_hwndBasicDialog )
        {
          MoveWindow(g_hwndBasicDialog, rect.left, rect.top, 
            rect.right-rect.left,rect.bottom - rect.top, TRUE);
          ShowWindow(g_hwndBasicDialog, SW_SHOW);
          UpdateWindow(g_hwndBasicDialog);
        }
#elif _WIN32_WCE < 212//non-Rapier devices
        
        int nCBrHeight;
        hwndCB = CommandBar_Create(hInst, hWnd, 1);			
        CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);
        CommandBar_AddAdornments(hwndCB, 0, 0);
        nCBrHeight = CommandBar_Height(hwndCB); // returns the height of the commandbars
        
        // Create the DialogWindow and center it under the commandbar
        GetClientRect(hWnd, &rect);
        g_hwndBasicDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_BASICDIALOG), hWnd, (DLGPROC)BasicDlgProc); 
        if ( g_hwndBasicDialog )
        {
          MoveWindow(g_hwndBasicDialog,	0, nCBrHeight, rect.right-rect.left,rect.bottom - (rect.top + nCBrHeight), TRUE);
          ShowWindow(g_hwndBasicDialog, SW_SHOW);
          UpdateWindow(g_hwndBasicDialog);
        }
#endif
        //
        break;
      case WM_DESTROY:
        DestroyWindow(g_hwndBasicDialog);
        
#if _WIN32_WCE > 211 //Rapier devices
        DestroyWindow(hwndCB);
#elif _WIN32_WCE < 212 //non-Rapier devices
        CommandBar_Destroy(hwndCB);
#endif
        
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Mesage handler for the About box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  
  switch (message)
  {
		case WM_INITDIALOG:
#if _WIN32_WCE > 211 //Rapier devices
      //On Rapier devices you normally create all Dialog's as fullscreen dialog's
      // with an OK button in the upper corner. You should get/set any program settings
      // during each modal dialog creation and destruction
      SHINITDLGINFO shidi;
      // Create a Done button and size it.
      shidi.dwMask = SHIDIM_FLAGS;
      shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
      shidi.hDlg = hDlg;
      //initialzes the dialog based on the dwFlags parameter
      SHInitDialog(&shidi);
      
#elif _WIN32_WCE < 212//non-Rapier devices
      RECT rt, rt1;
      int DlgWidth, DlgHeight;	// dialog width and height in pixel units
      int NewPosX, NewPosY;
      // trying to center the About dialog
      if (GetWindowRect(hDlg, &rt1)) {
        GetClientRect(GetParent(hDlg), &rt);
        DlgWidth	= rt1.right - rt1.left;
        DlgHeight	= rt1.bottom - rt1.top ;
        NewPosX		= (rt.right - rt.left - DlgWidth)/2;
        NewPosY		= (rt.bottom - rt.top - DlgHeight)/2;
        
        // if the About box is larger than the physical screen 
        if (NewPosX < 0) NewPosX = 0;
        if (NewPosY < 0) NewPosY = 0;
        SetWindowPos(hDlg, 0, NewPosX, NewPosY,
          0, 0, SWP_NOZORDER | SWP_NOSIZE);
      }
#endif
      return TRUE;
      
    case WM_COMMAND:
      if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
      {
        EndDialog(hDlg, LOWORD(wParam));
        return TRUE;
      }
      break;
  }
  return FALSE;
}

//------------------------------------------------------
// BasicDlgProc
//------------------------------------------------------
LRESULT CALLBACK BasicDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){  
  LRESULT	lResult = TRUE;
  
  switch(msg)
  {
		case WM_COMMAND:
      
    case WM_INITDIALOG:
      {
        ;//Something
      }
      break;
      
    default:
      //return DefWindowProc(hwnd, msg, wp, lp);
      return(FALSE);
      break;
  }
  
  UNREFERENCED_PARAMETER(wp);
  UNREFERENCED_PARAMETER(lp);
  return (lResult);
}
