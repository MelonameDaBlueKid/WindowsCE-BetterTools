/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
// HelloWinCE.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HelloWinCE.h"
#include <commctrl.h>

#if _WIN32_WCE < 212//non-Rapier devices
#error 'This sample works on Rapier devices only'
#endif
#include <aygshell.h>

//Menu Bar Height
#define MENU_HEIGHT 26
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
  MSG msg;
  
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_HELLOWINCE, szWindowClass, MAX_LOADSTRING);
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
  wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HELLOWINCE));
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
  HWND	hWnd;
  
  hInst = hInstance;		// Store instance handle in our global variable
  // Initialize global strings
  MyRegisterClass(hInstance, szWindowClass);
  
  hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  
  if (!hWnd)
  {	
    return FALSE;
  }
  //When the main window is created using CW_USEDEFAULT the height of the menubar (if one
  // is created is not taken into account). So we resize the window after creating it
  // if a menubar is present
  {
    RECT rc;
    GetWindowRect(hWnd, &rc);
    rc.bottom -= MENU_HEIGHT;
    if (hwndCB)
      MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
  }
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  
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
  HDC hdc;
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  TCHAR szHello[MAX_LOADSTRING];
  
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
        //Create a MenuBar
        SHMENUBARINFO mbi;
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hWnd;
        mbi.nToolBarId = IDM_MAIN_MENU;
        mbi.hInstRes   = hInst;
        mbi.nBmpId     = 0;
        mbi.cBmpImages = 0;	
        
        SHCreateMenuBar(&mbi);
        if (!SHCreateMenuBar(&mbi))
          MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
        hwndCB = mbi.hwndMB;
        break;
      case WM_PAINT:
        RECT rt;
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rt);
        LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
        DrawText(hdc, szHello, _tcslen(szHello), &rt, 
          DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        EndPaint(hWnd, &ps);
        break;
      case WM_HIBERNATE:
        //Release any large memory resources here
        break;
      case WM_ACTIVATE:
        //Reallocate any large memory resources here when the 
        //MainWindow is reactivated
        if ((LOWORD (wParam) != WA_INACTIVE)) {
          ;
        }
        break;
      case WM_DESTROY:
        //Destroy MenuBar       
        DestroyWindow(hwndCB);
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
      //On Rapier devices you normally create all Dialog's as fullscreen dialog's
      // with an OK button in the upper corner. 
      SHINITDLGINFO shidi;
      // Create a Done button and size it.
      shidi.dwMask = SHIDIM_FLAGS;
      shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
      shidi.hDlg = hDlg;
      //initialzes the dialog based on the dwFlags parameter
      SHInitDialog(&shidi);
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
