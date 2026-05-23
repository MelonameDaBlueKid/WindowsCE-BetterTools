// CEGetSys.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CEGetSys.h"
#include <commctrl.h>
#define ID_LB 1000

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB, hwndListBox;			// 
HMENU hm;

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
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CEGETSYS));
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
	TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
	TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name
	
	hInst = hInstance;		// Store instance handle in our global variable
	// Initialize global strings
	LoadString(hInstance, IDC_CEGETSYS, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	MyRegisterClass(hInstance, szWindowClass);
	
	////////// Setting default main window size
	// This technique allows for you to create the main
	// window to allow for the postion of a menubar and/or
	// the SIP button at the bottom of the screen
	
	SIPINFO si = {0};
	//Set default window creation sizd info
	int iDelta, x = CW_USEDEFAULT, y = CW_USEDEFAULT, cx, cy;
	
	si.cbSize = sizeof(si);
	SHSipInfo(SPI_GETSIPINFO, 0, &si, 0);
		
	//Consider the menu at the bottom, please.
	iDelta = (si.fdwFlags & SIPF_ON) ? 0 : MENU_HEIGHT;
	cx = si.rcVisibleDesktop.right - si.rcVisibleDesktop.left;
	cy = si.rcVisibleDesktop.bottom - si.rcVisibleDesktop.top - iDelta;
		
				
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE ,
		x, y, cx, cy, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{	
		return FALSE;
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
	int wmId, wmEvent;
	
	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_SYSCOLORS : 
				CheckMenuRadioItem(hm, ID_SYSCOLORS, ID_VERSIONEX, ID_SYSCOLORS, MF_BYCOMMAND);
				SendMessage (hwndListBox,LB_RESETCONTENT, 0,     0);
				doSysColors (hwndListBox); 
				break;
			case ID_INFO      : 
				CheckMenuRadioItem(hm, ID_SYSCOLORS, ID_VERSIONEX, ID_INFO, MF_BYCOMMAND);
				SendMessage (hwndListBox,LB_RESETCONTENT, 0,     0);
				doInfo      (hwndListBox); 
				break;
			case ID_METRICS   : 
				CheckMenuRadioItem(hm, ID_SYSCOLORS, ID_VERSIONEX, ID_METRICS, MF_BYCOMMAND);
				SendMessage (hwndListBox,LB_RESETCONTENT, 0,     0);
				doMetrics   (hwndListBox); 
				break;
			case ID_PALETTE   : 
				CheckMenuRadioItem(hm, ID_SYSCOLORS, ID_VERSIONEX, ID_PALETTE, MF_BYCOMMAND);
				SendMessage (hwndListBox,LB_RESETCONTENT, 0,     0);
				doPalette   (hwndListBox); 
				break;
			case ID_LOCALTIME : 
				CheckMenuRadioItem(hm, ID_SYSCOLORS, ID_VERSIONEX, ID_LOCALTIME, MF_BYCOMMAND);
				SendMessage (hwndListBox,LB_RESETCONTENT, 0,     0);
				doLocalTime (hwndListBox); 
				break;
			case ID_TIME      : 
				CheckMenuRadioItem(hm, ID_SYSCOLORS, ID_VERSIONEX, ID_TIME, MF_BYCOMMAND);
				SendMessage (hwndListBox,LB_RESETCONTENT, 0,     0);
				doTime      (hwndListBox); 
				break;
			case ID_VERSIONEX : 
				CheckMenuRadioItem(hm, ID_SYSCOLORS, ID_VERSIONEX, ID_VERSIONEX, MF_BYCOMMAND);
				SendMessage (hwndListBox,LB_RESETCONTENT, 0,     0);
				doVersionEx (hwndListBox); 
				break;
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

					RECT rc;
					GetClientRect(hWnd, &rc);
					
					
					hwndListBox = CreateWindow(_T("LISTBOX"), NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL
						|LBS_NOINTEGRALHEIGHT|LBS_USETABSTOPS   , 
						rc.left, rc.top, rc.right, rc.bottom, hWnd, (HMENU)ID_LB, hInst,NULL);
					
				if (hwndListBox){
					//
					ShowWindow(hwndListBox, SW_SHOW);
					UpdateWindow(hwndListBox);
				}
				break;
					
			case WM_DESTROY:
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
//
//

void doSysColors (HWND hwnd)
{
	int i;
	DWORD answer;

  for (i = 0; i<NSYSCOLORS; i++) {
		answer = GetSysColor (SysColors[i].Value);
    wsprintf (szbufW, SysColors[i].String, (int)answer);
    SendMessage (hwndListBox,LB_ADDSTRING, 0, (LPARAM)szbufW);
  }
  return;
}


void doInfo(HWND hwnd)
{
	SYSTEM_INFO  si;
  GetSystemInfo (&si);
  wsprintf (szbufW,_T("wProcessorArchitecture      \t%d"),	(int) si.wProcessorArchitecture    );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wReserved                   \t%d"),	(int) si.wReserved                 );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwPageSize                  \t%d"),  (int) si.dwPageSize                 );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("lpMinimumApplicationAddress \t%08lx"), (LONG)si.lpMinimumApplicationAddress );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("lpMaximumApplicationAddress \t%08lx"), (LONG)si.lpMaximumApplicationAddress );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwActiveProcessorMask       \t%d"),  (int) si.dwActiveProcessorMask      );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwNumberOfProcessors        \t%d"),  (int) si.dwNumberOfProcessors       );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwProcessorType             \t%d"),  (int) si.dwProcessorType            );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwAllocationGranularity     \t%d"),  (int) si.dwAllocationGranularity    );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wProcessorLevel             \t%d"),  (int) si.wProcessorLevel            );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wProcessorRevision          \t%d"),  (int) si.wProcessorRevision         );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
	
  return;
}

void doMetrics   (HWND hwnd){
	int  i;
	int  answer;
	
  for (i = 0; i<sizeof(SystemMetrics)/sizeof(LookupEntry); i++) {
    answer = GetSystemMetrics (SystemMetrics[i].Value);
    wsprintf (szbufW, SystemMetrics[i].String, (int)answer);
    SendMessage (hwndListBox,LB_ADDSTRING, 0, (LPARAM)szbufW);
  }
	
  return;
}

void doPalette(HWND hwnd)
{
	int nEntries;
	HDC hdc;
	int i;
	LPPALETTEENTRY  lpp;
	
  hdc = GetDC (hwnd);
  nEntries = GetSystemPaletteEntries (hdc, 0,0, NULL);

  if (nEntries == 0)
  {
    MessageBox (hwnd, L"There is zero palette entries.", L"Warning", MB_OK);
    return;
  }

  lpp = (LPPALETTEENTRY)LocalAlloc (LPTR,
		(DWORD) (nEntries* sizeof (PALETTEENTRY)));
	
  if (lpp == NULL) {
    MessageBox (hwnd,_T("Memory allocation failed."),_T("Warning"),  MB_OK);
    return;
  }
  nEntries = GetSystemPaletteEntries (hdc, 0,nEntries, lpp);
  ReleaseDC (hwnd, hdc);
  for (i = 0; i<nEntries; i++) {
    wsprintf (szbufW,_T("%d)%02x \t%02x \t%02x \t%02x"), i,
			lpp[i].peRed, lpp[i].peGreen, lpp[i].peBlue, lpp[i].peFlags);
    SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  }
  LocalFree (LocalHandle ((LPSTR)lpp));
  return;
}

void doLocalTime (HWND hwnd)
{
	SYSTEMTIME  st;
  GetLocalTime (&st);
  wsprintf (szbufW,_T("wYear         \t%d"),  (int)st.wYear         );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wMonth        \t%d"),  (int)st.wMonth        );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wDayOfWeek    \t%d"),  (int)st.wDayOfWeek    );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wDay          \t%d"),  (int)st.wDay          );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wHour         \t%d"),  (int)st.wHour         );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wMinute       \t%d"),  (int)st.wMinute       );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wSecond       \t%d"),  (int)st.wSecond       );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wMilliseconds \t%d"),  (int)st.wMilliseconds );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  return;
}

void doTime (HWND hwnd)
{
	SYSTEMTIME  st;
  GetSystemTime (&st);
  wsprintf (szbufW,_T("wYear         \t%d"),  (int)st.wYear         );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wMonth        \t%d"),  (int)st.wMonth        );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wDayOfWeek    \t%d"),  (int)st.wDayOfWeek    );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wDay          \t%d"),  (int)st.wDay          );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wHour         \t%d"),  (int)st.wHour         );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wMinute       \t%d"),  (int)st.wMinute       );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wSecond       \t%d"),  (int)st.wSecond       );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("wMilliseconds \t%d"),  (int)st.wMilliseconds );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  return;
}

void doVersionEx (HWND hwnd)
{
	OSVERSIONINFO osvi;
  osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
  GetVersionEx (&osvi);
	
  wsprintf (szbufW,_T("dwOSVersionInfoSize \t%d"),  (int)osvi.dwOSVersionInfoSize );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwMajorVersion      \t%d"),  (int)osvi.dwMajorVersion );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwMinorVersion      \t%d"),  (int)osvi.dwMinorVersion );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwBuildNumber       \t%d"),  (int)osvi.dwBuildNumber );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("dwPlatformId        \t%d"),  (int)osvi.dwPlatformId );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
  wsprintf (szbufW,_T("szCSDVersion:       \t%s"),  (LPTSTR) osvi.szCSDVersion );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
	
#ifdef GETVERSION
  wsprintf (szbufW,_T("GetVersion(): \t0x%08x"),  GetVersion () );
  SendMessage (hwnd,LB_ADDSTRING, 0, (LPARAM)szbufW);
#endif
	
  return;
}
