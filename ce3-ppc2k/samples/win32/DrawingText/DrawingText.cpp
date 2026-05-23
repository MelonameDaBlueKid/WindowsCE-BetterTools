// DrawingText.cpp : Defines the entry point for the application.
//db

#include "stdafx.h"
#include "DrawingText.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100
#define GRAYWIDTH 30
#define PALETTEINDEX2BPP(i)  (((i)==0)?0x00000000:(((i)==1)?0x00808080:(((i)==2)?0x00C0C0C0:0x00FFFFFF)))

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
int					nCmdBarHeight; // Height of the commandbar

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
	HACCEL hAccelTable;
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DRAWINGTEXT);
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWINGTEXT));
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
	LoadString(hInstance, IDC_DRAWINGTEXT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance, szWindowClass);
	
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	
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
		
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE | WS_BORDER,
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
	HDC hdc;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	
	switch (message) 
	{
		//Handle the SIP being put up
		case WM_SETTINGCHANGE:

			SHACTIVATEINFO sai;
			memset(&sai, 0, sizeof(SHACTIVATEINFO));

			//This will force a HWND resize depending on the SIP condition	
			SHHandleWMSettingChange(hWnd, -1, 0, &sai);
		break;

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
				RECT rcString, rcClient;
				POINT ptTrig[4]; 
				INT i, cy;
				
				GetClientRect (hWnd, &rcClient);
				hdc = BeginPaint (hWnd, &ps); 
				ptTrig[0].x = ptTrig[3].x = ptTrig[1].x = rcClient.left;
				ptTrig[0].y = ptTrig[3].y = rcClient.top;
				ptTrig[2].y = ptTrig[1].y = rcClient.bottom;
				ptTrig[2].x = rcClient.right;
				SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
				Polygon(hdc, ptTrig, 4);
				SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
				ptTrig[0].x = ptTrig[3].x = ptTrig[2].x /2; 
				ptTrig[0].y = ptTrig[3].y = ptTrig[2].y /3; 
				Polygon(hdc, ptTrig, 4);
				SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
				
				// DT_CALCRECT fills in &rcString with the height/width of string
				DrawText (hdc, TEXT ("Sample DrawText"), -1, &rcString, 
					DT_CALCRECT | DT_CENTER | DT_SINGLELINE);
				// Text rectangle size plus some padding
				cy = rcString.bottom - rcString.top + 5;
				
				rcClient.bottom = rcClient.top + cy;
				SetBkMode (hdc, TRANSPARENT);
				for (i = 0; i < 8; i++) {
					SetTextColor (hdc, PALETTEINDEX2BPP(i));
					SetBkColor (hdc, PALETTEINDEX2BPP(3 -i));
					DrawText (hdc, TEXT ("Sample DrawText Here"), -1, &rcClient, DT_CENTER | DT_SINGLELINE);
					rcClient.top += cy;
					rcClient.bottom += cy;
				}
				
				SetBkMode (hdc, OPAQUE);
				for (i = 0; i < 4; i++) {
					SetTextColor (hdc, PALETTEINDEX2BPP(i));
					SetBkColor (hdc, PALETTEINDEX2BPP(3 -i));
					DrawText (hdc, TEXT ("Sample DrawText Here"), -1, &rcClient, DT_CENTER | DT_SINGLELINE);
					rcClient.top += cy;
					rcClient.bottom += cy;
				}
				EndPaint(hWnd, &ps);
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
