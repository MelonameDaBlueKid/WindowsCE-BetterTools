// Bezier.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Bezier.h"
#include "cepolybezier.h"
#include <commctrl.h>
#include <stdlib.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HMENU 			hMenu;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
int rand(int);

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
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BEZIER));
	wc.hCursor			= 0;
	wc.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
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
	LoadString(hInstance, IDC_BEZIER, szWindowClass, MAX_LOADSTRING);
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
	int wmId, wmEvent;
	static POINT pts[10];
	static WORD wDegree = 3;
	static DWORD dwPts = 0;
	static BOOL bShowGuides = TRUE;
	
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
			case IDM_DEGREE2:
			case IDM_DEGREE3:
			case IDM_DEGREE4:
			case IDM_DEGREE5:
			case IDM_DEGREE6:
			case IDM_DEGREE7:
			case IDM_DEGREE8:
				hMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
				CheckMenuRadioItem(hMenu, IDM_DEGREE2, IDM_DEGREE8, wmId, MF_BYCOMMAND);
				wDegree = 2 + (wmId - IDM_DEGREE2);
				dwPts = 0;
				break;
			case IDM_SHOWGUIDES:
				{
				hMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
				bShowGuides = !bShowGuides;
				CheckMenuItem(hMenu, IDM_SHOWGUIDES, bShowGuides ? MF_CHECKED : MF_UNCHECKED);
				// If we have points to show then re-render them
				if (dwPts) 
					InvalidateRect(hWnd, NULL, TRUE);  // Draw via WM_PAINT
				break;
				}
				
			case IDM_QUICKTEST:
				RECT rect;
				/* find out where we can draw */
				GetClientRect(hWnd, &rect);
				/* random initialize our points */
				for (dwPts=0; dwPts<=(DWORD)wDegree; dwPts++) {
					pts[dwPts].x = rand(rect.right);
					pts[dwPts].y = rand(rect.bottom);
				}
				InvalidateRect(hWnd, NULL, TRUE);
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
				
				hMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
				bShowGuides = !bShowGuides;
				CheckMenuItem(hMenu, IDM_SHOWGUIDES, bShowGuides ? MF_CHECKED : MF_UNCHECKED);
				break;
				
			case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC hDC = BeginPaint(hWnd, &ps);
					HPEN hPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
					RECT rect;
					int i;
					
					/* If we have enough points for a curve of the specified degree */
					if (dwPts > wDegree) {
						if (bShowGuides) {
							HPEN hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
							/* Draw outline in red */
							DeleteObject(SelectObject(hDC, hPen));
							Polyline(hDC, (LPPOINT)&pts, wDegree+1);
						}
						/* Draw the curve in white */
						DeleteObject(SelectObject(hDC, GetStockObject(WHITE_PEN)));
						CEPolyBezierDegree(hDC, (LPPOINT)&pts, wDegree+1, wDegree);
					} 
					if (dwPts == 1) {
						GetClientRect(hWnd, &rect);
						PatBlt(hDC, 0, 0, rect.right, rect.bottom, BLACKNESS);
					}
					/* Draw vertices in green */
					DeleteObject(SelectObject(hDC, hPen));
					for (i=0; i<(int)dwPts; i++) 
						Ellipse(hDC, pts[i].x-2, pts[i].y-2, pts[i].x+2, pts[i].y+2);
					DeleteObject(SelectObject(hDC, GetStockObject(WHITE_PEN)));
					EndPaint(hWnd, &ps);
				}
				break;
			case WM_LBUTTONUP:
				if (dwPts > wDegree)
					dwPts = 0;
				
				pts[dwPts].x = LOWORD(lParam);  // horizontal position of cursor 
				pts[dwPts].y = HIWORD(lParam);  // vertical position of cursor 
				dwPts++;
				InvalidateRect(hWnd, NULL, FALSE);
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
// return an integral random number in the range  0  - (1 - n)
int rand(int n)
{
	return (Random() % n);;
}
