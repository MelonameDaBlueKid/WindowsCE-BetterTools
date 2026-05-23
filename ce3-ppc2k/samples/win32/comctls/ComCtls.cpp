/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
// ComCtls.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ComCtls.h"
#include <commctrl.h>

#if _WIN32_WCE < 212//non-Rapier devices
#error 'This sample works on Rapier devices only'
#endif
#include <aygshell.h>

#define MAX_LOADSTRING 100
#define ID_TIMER WM_USER + 300

//Menu Bar Height
#define MENU_HEIGHT 26

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HWND			hwndMain; //The main window
HWND			g_hwndComCtls; //The basic dialog for the controls
TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	BasicDlgProc (HWND, UINT, WPARAM, LPARAM);

void AddToEdit(HWND hwnd, int nCnt);
void AddToListBox(HWND hwnd, int nCnt);
void AddToScrollBars(HWND hwnd, int nCnt);
void AddToProgressBar(HWND hwnd, int nCnt);
void AddToSlider(HWND hwnd, int nCnt);
void AddToComboBox(HWND hwnd, int nCnt);
void AddToButton(HWND hwnd, int nCnt);

int WINAPI WinMain(	HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
  MSG msg;
  
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_COMCTLS, szWindowClass, MAX_LOADSTRING);
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
  wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COMCTLS));
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
  {
    RECT rc;
    GetWindowRect(hwndMain, &rc);
    rc.bottom -= MENU_HEIGHT;
    if (hwndCB)
      MoveWindow(hwndMain, rc.left, rc.top, rc.right, rc.bottom, FALSE);
  }
  
  ShowWindow(hwndMain, nCmdShow);
  UpdateWindow(hwndMain);
  
  
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

      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;
      case WM_CREATE:
        
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
        g_hwndComCtls = CreateDialog(hInst, MAKEINTRESOURCE(IDD_COMCTLS), hWnd, (DLGPROC)BasicDlgProc); 
        if ( g_hwndComCtls )
        {
          MoveWindow(g_hwndComCtls, rect.left, rect.top, 
            rect.right-rect.left,rect.bottom - rect.top, TRUE);
          ShowWindow(g_hwndComCtls, SW_SHOW);
          UpdateWindow(g_hwndComCtls);
        }
        // Set a timer to animate the controls on the dialog window
        SetTimer(g_hwndComCtls, ID_TIMER, 500, NULL);
        //
        break;
      case WM_DESTROY:
        KillTimer(g_hwndComCtls, ID_TIMER);
        DestroyWindow(g_hwndComCtls);
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
      // with an OK button in the upper corner. You should get/set any program settings
      // during each modal dialog creation and destruction
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

int nCnt = 0;
//------------------------------------------------------
// BasicDlgProc
//------------------------------------------------------
LRESULT CALLBACK BasicDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){  
  LRESULT	lResult = TRUE;
  switch(msg)
  {
  case WM_TIMER:
    nCnt > 9 ? nCnt = 0 : nCnt++;
    AddToEdit(hwnd, nCnt);
    AddToListBox(hwnd, nCnt);
    AddToScrollBars( hwnd,  nCnt);
    AddToProgressBar(hwnd, nCnt);
    AddToSlider(hwnd, nCnt);
    AddToComboBox(hwnd, nCnt);
    AddToButton(hwnd, nCnt);
	UpdateWindow(hwnd);
    break;
    
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

void AddToEdit(HWND hwnd, int nCnt){
  //get the control window
  HWND hwEdit = GetDlgItem(hwnd, IDC_EDIT1 ); 
  //set text to show in control
  TCHAR szBufW[16];
  wsprintf(szBufW, L"Edit %d\r\n", nCnt);
  if (nCnt)
    Edit_ReplaceSel(hwEdit, szBufW); 
  else
    Edit_SetText(hwEdit, L""); 
}

void AddToListBox(HWND hwnd, int nCnt){
  //get the control window
  HWND hwListBox = GetDlgItem(hwnd,IDC_LIST1 ); 
  //set text to show in control
  TCHAR szBufW[16];
  wsprintf(szBufW, L"ListBox %d", nCnt);
  if (nCnt)
    ListBox_AddString(hwListBox, szBufW);
  else
    ListBox_ResetContent(hwListBox); 
}

void AddToScrollBars(HWND hwnd, int nCnt){
  //get the control window
  HWND hwScrollBarH = GetDlgItem(hwnd, IDC_SCROLLBAR1);
  HWND hwScrollBarV = GetDlgItem(hwnd, IDC_SCROLLBAR2);
  //set scroll bar range
  ScrollBar_SetRange(hwScrollBarH, 0, 10, FALSE);
  ScrollBar_SetRange(hwScrollBarV, 0, 10, FALSE);
  //set scroll bar position
  ScrollBar_SetPos(hwScrollBarH, nCnt, TRUE);
  ScrollBar_SetPos(hwScrollBarV, nCnt, TRUE);
}

void AddToProgressBar(HWND hwnd, int nCnt){
  //get the control window
  HWND hwProgressBar = GetDlgItem(hwnd, IDC_PROGRESS1);
  //set progress bar position
  SendMessage(hwProgressBar, PBM_SETPOS, (WPARAM)nCnt * 10, 0);
}

void AddToSlider(HWND hwnd, int nCnt){
  //get the control window
  HWND hwSlider = GetDlgItem(hwnd, IDC_SLIDER1);
  //set slider position
  SendMessage(hwSlider, TBM_SETPOS, TRUE, (WPARAM)nCnt * 10);
}
void AddToComboBox(HWND hwnd, int nCnt){
  //get the control window
  HWND hwComboBox = GetDlgItem(hwnd, IDC_COMBO1);
  //set text to show in control
  TCHAR szBufW[16];
  wsprintf(szBufW, L"ComboBox %d", nCnt);
  if (nCnt){
    ComboBox_AddString(hwComboBox, szBufW);
    ComboBox_SetText(hwComboBox, szBufW);
    ComboBox_SetCurSel(hwComboBox, nCnt-1);
  }
  else {
    ComboBox_ResetContent(hwComboBox); 
    ComboBox_ShowDropdown(hwComboBox, FALSE);
  }
}

void AddToButton(HWND hwnd, int nCnt){
  //get the control window
  HWND hwButton = GetDlgItem(hwnd, IDC_BUTTON1);
  //set text to show in control
  TCHAR szBufW[16];
  wsprintf(szBufW, L"Button %d", nCnt);
  Button_SetText(hwButton, szBufW);
  return;
}
