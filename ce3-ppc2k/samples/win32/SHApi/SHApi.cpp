// shapi.cpp : Defines the entry point for the application.
// Shows some of the shell api's

//
#include "stdafx.h"
#include "shapi.h"
#include <commctrl.h>

#define MAX_LOADSTRING 260

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND          hwndMain;
HWND				hwndCB = NULL;			// The command bar handle
TCHAR      	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	      szWindowClass[MAX_LOADSTRING];		// The window class name
DWORD        m_dwSHInitFlags = 0;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SHInitDialogTestProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//Demo's SHDoneButton
BOOL DoSHDoneButton(HWND hwndRequester);

//Demo's SHSetNavBarText
BOOL DoSHSetNavBarText(HWND hwndRequester, UINT idMenu);

//Demo's SHFullScreen
BOOL DoSHFullScreen(HWND hwndRequester, DWORD dwState);

//Demo's SHInitDialog
BOOL DoSHInitDialogSetFlags(UINT wmId);
BOOL DoSHInitDialog(HWND hDlg, DWORD dwFlags);

//Demo's SHGetAutoRunPath
BOOL DoSHGetAutoRunPath(HWND hwnd);

int WINAPI WinMain(	HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
  MSG msg;
  HWND hwndThis = NULL;
  
  LoadString(hInstance, IDC_SHAPI, szWindowClass, MAX_LOADSTRING);
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  
  // Check if this app. is running
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
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
  WNDCLASS	wc;
  
  wc.style			= CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc		= (WNDPROC) WndProc;
  wc.cbClsExtra		= 0;
  wc.cbWndExtra		= 0;
  wc.hInstance		= hInstance;
  wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHAPI));
  wc.hCursor			= 0;
  wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName		= 0;
  wc.lpszClassName	= szWindowClass;
  
  return RegisterClass(&wc);
}

//
//  FUNCTION: InitInstance(HANDLE, int)
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND	hWnd;
  RECT rc;
  
  hInst = hInstance;		// Store instance handle in our global variable
  // Initialize global strings
  MyRegisterClass(hInstance, szWindowClass);
  
  hwndMain = hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  
  GetWindowRect(hWnd, &rc);
  rc.bottom -= MENU_HEIGHT; 
  if (hwndCB)MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom - rc.top, TRUE); 
  
  if (!hWnd){	
    return FALSE;
  }
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  
  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  int wmId, wmEvent;
  static int cx, cy;
  PAINTSTRUCT ps;
  TCHAR szBufW[MAX_LOADSTRING];
  RECT rc;
  
  SHMENUBARINFO mbi;
  
  switch (message) 
  {
  case WM_COMMAND:
    wmId    = LOWORD(wParam); 
    wmEvent = HIWORD(wParam); 
    // Parse the menu selections:
    switch (wmId)
    {
    case ID_SHAPI_SHINITDIALOG:
      DialogBox(hInst, (LPCTSTR)IDD_TESTDIALOG, hWnd, (DLGPROC)SHInitDialogTestProc);
      break;
      
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON:
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG:
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN:
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN:
    case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR:
      DoSHInitDialogSetFlags(wmId);
      break;
      
    case ID_SHAPI_SHFULLSCREENWINDOW:
      DoSHFullScreen(hWnd, SHFS_HIDETASKBAR);
      DoSHFullScreen(hWnd, SHFS_HIDESIPBUTTON);
      ShowWindow(hwndCB, SW_HIDE);
      rc.left = 0; 
      rc.top = 0;
      rc.right = cx;
      rc.bottom = cy;
      MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
      break;
      
    case ID_SHAPI_SHFULLSCREEN_SHFSSHOWTASKBAR:
      DoSHFullScreen(hWnd, SHFS_SHOWTASKBAR);
      rc.left = 0; 
      rc.top = MENU_HEIGHT;
      rc.right = cx;
      rc.bottom = cy - (2*MENU_HEIGHT);
      MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
      break;
      
    case ID_SHAPI_SHFULLSCREEN_SHFSHIDETASKBAR:
      DoSHFullScreen(hWnd, SHFS_HIDETASKBAR);
      rc.left = 0; 
      rc.top = 0;
      rc.right = cx;
      rc.bottom = cy - MENU_HEIGHT;
      MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
      break;
      
    case ID_SHAPI_SHFULLSCREEN_SHFSSHOWSIPBUTTON:
      DoSHFullScreen(hWnd, SHFS_SHOWSIPBUTTON);
      break;
      
    case ID_SHAPI_SHFULLSCREEN_SHFSHIDESIPBUTTON:
      DoSHFullScreen(hWnd, SHFS_HIDESIPBUTTON);
      break;
      
    case ID_SHAPI_SHFULLSCREEN_SHFSSHOWSTARTICON:
      DoSHFullScreen(hWnd, SHFS_SHOWSTARTICON);
      break;
      
    case ID_SHAPI_SHFULLSCREEN_SHFSHIDESTARTICON:
      DoSHFullScreen(hWnd, SHFS_HIDESTARTICON);
      break;
      
    case ID_SHAPI_SHSETNAVBARTEXT_HERETODAY:
    case ID_SHAPI_SHSETNAVBARTEXT_GONETOMORROW:
      DoSHSetNavBarText(hWnd, wmId);
      break;
      
    case ID_SHAPI_SHDONEBUTTON:
      DoSHDoneButton(hWnd);
      break;
			
    case ID_SHAPI_SHGETAUTORUNPATH:
			DoSHGetAutoRunPath(hWnd);
			break;
			
    case IDM_ABOUT:
      DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
      break;
      
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
    
    case WM_LBUTTONDOWN:
      SHFullScreen(hWnd, SHFS_SHOWTASKBAR );
      ShowWindow(hwndCB, SW_SHOW);
      rc.left = 0; 
      rc.top = MENU_HEIGHT;
      rc.right = cx;
      rc.bottom = cy - (2*MENU_HEIGHT);
      MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, TRUE); 
      break;
      
    case WM_CREATE:
      {
        //set up menu bar structure
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hWnd;
        mbi.nToolBarId = IDM_MAIN_MENU;
        mbi.hInstRes   = hInst;
        mbi.nBmpId     = 0;
        mbi.cBmpImages = 0;	
        
        if (!SHCreateMenuBar(&mbi))
				MessageBox(hWnd, _T("SHCreateMenuBar Failed"), _T("Error"), MB_OK);
        //retain the hwnd to the toolbar to destroy it if necessary
        hwndCB = mbi.hwndMB;
        //get screen size
        HDC hdc = GetDC(hWnd);
        cx = GetDeviceCaps(hdc, HORZRES);
        cy = GetDeviceCaps(hdc, VERTRES);
        ReleaseDC(hWnd, hdc);
        
      }
      break;
      
    case WM_PAINT:
      {
        RECT rt;
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rt);
        LoadString(hInst, IDS_SHAPI_TEXT, szBufW, MAX_LOADSTRING);
        DrawText(hdc, szBufW, _tcslen(szBufW), &rt, 
          DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
        Rectangle(hdc, rt.left, rt.top, rt.left + 50, rt.top+ 50);
        Ellipse(hdc, rt.right-50, rt.top, rt.right, rt.top+ 50);
        Rectangle(hdc, rt.right-50, rt.bottom-50, rt.right, rt.bottom);
        Ellipse(hdc, rt.left, rt.bottom-50, rt.left + 50, rt.bottom);
        SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
        EndPaint(hWnd, &ps);
      }
      break;
      
    case WM_DESTROY:
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



//DoSHDoneButton
// demonstrates how to put an OK button on the task bar
BOOL m_fButtonHide = TRUE;
BOOL DoSHDoneButton(HWND hwndRequester){
  
  //BOOL SHDoneButton(HWND hwndRequester, DWORD dwState);
  //
  // Valid states
  //#define SHDB_SHOW                   0x0001
  //#define SHDB_HIDE                   0x0002
  
  if (m_fButtonHide){
    m_fButtonHide = FALSE;
    HMENU hShowButton = SHMenuBar_GetMenu(hwndCB, IDM_MAIN_SHAPI);
    CheckMenuItem(hShowButton, ID_SHAPI_SHDONEBUTTON, MF_CHECKED | MF_BYCOMMAND);
    return SHDoneButton(hwndRequester, SHDB_SHOW);
  } else {
    m_fButtonHide = TRUE;
    HMENU hShowButton = SHMenuBar_GetMenu(hwndCB, IDM_MAIN_SHAPI);
    CheckMenuItem(hShowButton, ID_SHAPI_SHDONEBUTTON, MF_UNCHECKED | MF_BYCOMMAND);
    return SHDoneButton(hwndRequester, SHDB_HIDE);
  }
  
}

//DoSHDoneButton
// demonstrates how to set text on the navigation bar
BOOL DoSHSetNavBarText(HWND hwndRequester, UINT idMenu){
  TCHAR szText[MAX_LOADSTRING];
  MENUITEMINFO mii;
  
  HMENU hSHMenu = SHMenuBar_GetMenu(hwndCB, IDM_MAIN_SHAPI);
  
  memset((char *)&mii, 0, sizeof(mii));
  mii.cbSize = sizeof(mii); 
  mii.fMask  = MIIM_TYPE;
  mii.dwTypeData = &szText[0];
  mii.cch = MAX_LOADSTRING;
  mii.fType =  MFT_STRING; 
  GetMenuItemInfo(hSHMenu, idMenu, FALSE, &mii);
  
  return SHSetNavBarText(hwndRequester, szText);
}

//DoSHFullScreen
// demonstrates how to show app fullscreen
BOOL DoSHFullScreen(HWND hwndRequester, DWORD dwState){
  // Valid states
  //#define SHFS_SHOWTASKBAR            0x0001
  //#define SHFS_HIDETASKBAR            0x0002
  //#define SHFS_SHOWSIPBUTTON          0x0004
  //#define SHFS_HIDESIPBUTTON          0x0008
  //#define SHFS_SHOWSTARTICON          0x0010
  //#define SHFS_HIDESTARTICON          0x0020
  
  return SHFullScreen(hwndRequester, dwState);
}

////////////////////////////////////////////////////////////////////////////////////
// Demostration of SHInitDialog
//
// Mesage handler for the SHInitDialogTestProc box.
LRESULT CALLBACK SHInitDialogTestProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INITDIALOG:
    DoSHInitDialog(hDlg, m_dwSHInitFlags); 
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

//DoSHInitDialog
// demonstrates how to use SHInitDialog with various flags
BOOL DoSHInitDialog(HWND hDlg, DWORD dwFlags){
  SHINITDLGINFO shidi;
  //
  // Valid mask values
  //#define SHIDIM_FLAGS                0x0001
  
  shidi.hDlg = hDlg;
  shidi.dwMask = SHIDIM_FLAGS;
  shidi.dwFlags = dwFlags;
  
  return SHInitDialog(&shidi);
}


BOOL DoSHInitDialogSetFlags(UINT wmId){
  
  HMENU hMenu = SHMenuBar_GetMenu(hwndCB, IDM_MAIN_SHAPI);
  // Valid flags
  //#define SHIDIF_DONEBUTTON           0x0001
  //#define SHIDIF_SIZEDLG              0x0002
  //#define SHIDIF_SIZEDLGFULLSCREEN    0x0004
  //#define SHIDIF_SIPDOWN              0x0008
  //#define SHIDIF_FULLSCREENNOMENUBAR  0x0010 
  
  //add or remove flag and un/checkmenuitem
  switch (wmId){
	case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON:
		if (m_dwSHInitFlags & SHIDIF_DONEBUTTON){
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON , MF_UNCHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags &= ~SHIDIF_DONEBUTTON; //remove flag 
		} else {
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFDONEBUTTON , MF_CHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags |= SHIDIF_DONEBUTTON;  //add flag
		}
		break;
	case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG:
		if (m_dwSHInitFlags & SHIDIF_SIZEDLG){
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG , MF_UNCHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags &= ~SHIDIF_SIZEDLG; //remove flag 
		} else {
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLG , MF_CHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags |= SHIDIF_SIZEDLG;  //add flag
		}
		break;
	case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN:
		if (m_dwSHInitFlags & SHIDIF_SIZEDLGFULLSCREEN){
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN , MF_UNCHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags &= ~SHIDIF_SIZEDLGFULLSCREEN; //remove flag 
		} else {
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIZEDLGFULLSCREEN , MF_CHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags |= SHIDIF_SIZEDLGFULLSCREEN;  //add flag
		}
		break;
	case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN:
		if (m_dwSHInitFlags & SHIDIF_SIPDOWN){
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN , MF_UNCHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags &= ~SHIDIF_SIPDOWN; //remove flag 
		} else {
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFSIPDOWN , MF_CHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags |= SHIDIF_SIPDOWN;  //add flag
		}
		break;
	case ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR:
		if (m_dwSHInitFlags & SHIDIF_FULLSCREENNOMENUBAR){
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR , MF_UNCHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags &= ~SHIDIF_FULLSCREENNOMENUBAR; //remove flag 
		} else {
			CheckMenuItem(hMenu, ID_SHAPI_SHINITDIALOGFLAGS_SHIDIFFULLSCREENNOMENUBAR , MF_CHECKED | MF_BYCOMMAND);
			m_dwSHInitFlags |= SHIDIF_FULLSCREENNOMENUBAR;  //add flag
		}
		break;
  }
  return TRUE;
}

BOOL DoSHGetAutoRunPath(HWND hwnd){

#ifndef _WIN32_WCE_EMULATION
	TCHAR szBufW[MAX_PATH];
	
	memset(&szBufW, 0, sizeof(szBufW));
	
	SHGetAutoRunPath(&szBufW[0]);
	if (szBufW[0] != '\0')
		MessageBox(hwnd, szBufW, L"AutoRun", MB_OK);
	else
		MessageBox(hwnd, L"AutoRunPath not set.", L"AutoRun", MB_OK);
#else
  MessageBox(hwnd, L"Not applicable for emulation", L"AutoRun", MB_OK);
#endif

	return TRUE;
}
