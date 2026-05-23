// PolyDrawCE.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PolyDrawCE.h"
#include <commctrl.h>
#include "CEPolyBezier.h"

#define MAX_LOADSTRING 100
//
#define MAXPOINTS  10
#define NONE     -1
#define HITSIZE  15

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HMENU				hMenu;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
COLORREF GetQColor(int );

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
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_POLYDRAWCE);
	
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
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POLYDRAWCE));
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
	LoadString(hInstance, IDC_POLYDRAWCE, szWindowClass, MAX_LOADSTRING);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//   svPoints[] - array that stores the points for the GDI calls.
	//   svTypes[]  - array of bytes to store the type for the PolyDraw() calls.
	//   svIndex    - when tracking, the index of the point we are modifying.
	//   svNumDown  - the number of points currently in the client area.
	//   hPen     - Pens to draw the lines, curves, or erase with.
	static HPEN hPenErase, hPenSpline, hPenpolydraw;
	static POINT svPoints [MAXPOINTS];
	static BYTE  svTypes  [MAXPOINTS];
	static int   svNumDown;
	static int   svIndex;
	
	int wmId, wmEvent;
	
	switch (message) 
	{
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
        
			hMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM3);
			
			svNumDown = NONE;
			svIndex = NONE;
			hPenSpline     = CreatePen (PS_SOLID, 1, (COLORREF) GetQColor(RED));
			hPenpolydraw = CreatePen (PS_SOLID, 1, (COLORREF) GetQColor(BLACK));
			hPenErase     = CreatePen (PS_SOLID, 1, (COLORREF) GetQColor(WHITE));
			CheckMenuRadioItem(hMenu,ID_FLAGS_PTMOVETO,ID_FLAGS_PTBEZIERTO,ID_FLAGS_PTLINETO, MF_BYCOMMAND);
			eDrawAction = LINE_TO;
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_FLAGS_PTMOVETO:
				CheckMenuRadioItem(hMenu,ID_FLAGS_PTMOVETO,ID_FLAGS_PTBEZIERTO,ID_FLAGS_PTMOVETO, MF_BYCOMMAND);
				eDrawAction = MOVE_TO;
				break;
			case ID_FLAGS_PTLINETO:
				CheckMenuRadioItem(hMenu,ID_FLAGS_PTMOVETO,ID_FLAGS_PTBEZIERTO,ID_FLAGS_PTLINETO, MF_BYCOMMAND);
				eDrawAction = LINE_TO;
				break;
			case ID_FLAGS_PTBEZIERTO:
				CheckMenuRadioItem(hMenu,ID_FLAGS_PTMOVETO,ID_FLAGS_PTBEZIERTO,ID_FLAGS_PTBEZIERTO, MF_BYCOMMAND);
				eDrawAction = POLY_TO;
				break;
			case ID_VIEW_ERASE:
				svNumDown = NONE;
				svIndex = NONE;
				memset(svPoints, 0, sizeof(svPoints));

				//Enable the drawing options 
				EnableMenuItem(hMenu,ID_FLAGS_PTMOVETO,MF_ENABLED |MF_BYCOMMAND);
				EnableMenuItem(hMenu,ID_FLAGS_PTLINETO,MF_ENABLED |MF_BYCOMMAND);
				EnableMenuItem(hMenu,ID_FLAGS_PTBEZIERTO,MF_ENABLED |MF_BYCOMMAND);

				InvalidateRect (hWnd, NULL, TRUE);
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

			//Finished tracking.  Release the mouse capture, and force repaint.
			case WM_LBUTTONUP:
				if (GetCapture() == hWnd) {
					SetCapture (NULL);
					InvalidateRect (hWnd, NULL, FALSE);
				}
				break;
				// Hittest to see if the user is selecting an existing point.
				//  If not, check for point overflow.
				//  If o.k. then add a new point to the current list.
			case WM_LBUTTONDOWN: 
				{
					int i;
					RECT rectNear;
					ScreenToClient(hWnd, (LPPOINT)&lParam);

					// Construct a rectangle around the mouse point. 
					rectNear.left   = LOWORD(lParam) - HITSIZE;
					rectNear.right  = LOWORD(lParam) + HITSIZE;
					rectNear.top    = HIWORD(lParam) - HITSIZE;
					rectNear.bottom = HIWORD(lParam) + HITSIZE;
					
					//step through all points so far.  hittest mouse location against
					//each one.  If we hit one, set index, capture mouse .
					
					for (i = 0; i<= svNumDown; i++) {
						if (PtInRect (&rectNear, svPoints[i])) { //demonstrates hit testing near a point
							svIndex = i;
							SetCapture (hWnd);
							break;
						}
					}

					// don't have old point, still room for more.  Put down one more. 
					if (GetCapture() != hWnd && svNumDown < MAXPOINTS - 1) {
						svNumDown++;
						svPoints[svNumDown].x = LOWORD(lParam);
						svPoints[svNumDown].y = HIWORD(lParam);
						// set the type value in the array dependent upon keyboard state. 
						if (eDrawAction == MOVE_TO)        
							svTypes [svNumDown] = PT_MOVETO;
						else if (eDrawAction == POLY_TO) 
							svTypes [svNumDown] = PT_BEZIERTO;
						else                          
							svTypes [svNumDown] = PT_LINETO;
						InvalidateRect (hWnd, NULL, TRUE);
					} else if (GetCapture() != hWnd)
						MessageBox(hWnd, L"Maximum number of points entered. Tap and drag an entered point", L"MaxPoints", MB_OK);
					
					//Disable the drawing options because the maximum number of points has been entered
					if (svNumDown >= MAXPOINTS - 1) {
						EnableMenuItem(hMenu,ID_FLAGS_PTMOVETO,MF_GRAYED | MF_BYCOMMAND);
						EnableMenuItem(hMenu,ID_FLAGS_PTLINETO,MF_GRAYED | MF_BYCOMMAND);
						EnableMenuItem(hMenu,ID_FLAGS_PTBEZIERTO,MF_GRAYED | MF_BYCOMMAND);
					}

				}
				break;
			case WM_MOUSEMOVE: 
				{
					BYTE b = PT_MOVETO;	
					int i;				
					if (GetCapture() == hWnd) {
						HDC hdc;
						
						hdc = GetDC (hWnd);
						CEPolyDraw (hdc, svPoints, &b, 1);//set moveto point
						
						// Erase the old lines and curves. 
						SelectObject(hdc, hPenErase);
						Polyline (hdc, svPoints, svNumDown+1);
						for (i = 0; i < svNumDown + 1; i++)
							Ellipse(hdc,svPoints[i].x - 2, svPoints[i].y - 2,svPoints[i].x + 2,svPoints[i].y + 2);
						CEPolyDraw (hdc, &svPoints[1], &svTypes[1], svNumDown);
						
						// Change the point to match the new mouse position. 
						svPoints[svIndex].x = (int)(short)LOWORD(lParam);
						svPoints[svIndex].y = (int)(short)HIWORD(lParam);
						
						CEPolyDraw (hdc, svPoints, &b, 1); //set moveto point
						SelectObject(hdc, hPenSpline);
						Polyline (hdc, svPoints, svNumDown+1);
						
						SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
						for (i = 0; i < svNumDown + 1; i++)
							Ellipse(hdc,svPoints[i].x - 2, svPoints[i].y - 2,svPoints[i].x + 2,svPoints[i].y + 2);
						SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
						
						SelectObject(hdc, hPenpolydraw);
						CEPolyDraw (hdc, &svPoints[1], &svTypes[1], svNumDown);
						
						ReleaseDC (hWnd, hdc);
					}
				}
				break;
			case WM_PAINT:
				{
					HDC hdc;
					PAINTSTRUCT ps;
					int i;
					BYTE b = PT_MOVETO;
					hdc = BeginPaint(hWnd, &ps);
					CEPolyDraw (hdc, svPoints, &b, 1);
					SelectObject(hdc, hPenSpline);
					Polyline (hdc, svPoints, svNumDown+1);
						SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
						for (i = 0; i < svNumDown + 1; i++)
							Ellipse(hdc,svPoints[i].x - 2, svPoints[i].y - 2,svPoints[i].x + 2,svPoints[i].y + 2);
						SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
					SelectObject(hdc, hPenpolydraw);
					CEPolyDraw (hdc, &svPoints[1], &svTypes[1], svNumDown);
					
					EndPaint (hWnd, &ps);
				}	
				break;	
			case WM_DESTROY:
				DeleteObject (hPenSpline);
				DeleteObject (hPenpolydraw);
				DeleteObject (hPenErase);
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

COLORREF GetQColor(int nColor){
	//COLORREF RGB(
  //BYTE bRed,    // red component of color
  //BYTE bGreen,  // green component of color
  //BYTE bBlue    // blue component of color	
	
	switch (nColor){
		case WHITE: 
			return RGB(255, 255, 255);
		case RED:
			return RGB(255, 0, 0);
		case GREEN:
			return RGB(0, 255, 0);
		case BLUE:
			return RGB(0, 0, 255);
		case YELLOW:
			return RGB(192, 192, 192);
		case MAGENTA:
			return RGB(255, 0, 255);
		case CYAN:
			return RGB(0, 255, 255);
		case GRAY:
			return RGB(128, 128, 128);
		case LIGHTGRAY:
			return RGB(192, 192, 192);
		case DARKRED:
			return RGB(128, 0, 0);
		case DARKGREEN:
			return RGB(0, 128, 0);
		case DARKBLUE:
			return RGB(0, 0, 128);
		case LIGHTBROWN:
			return RGB(128, 128, 0);
		case DARKMAGENTA:
			return RGB(128, 0, 128);
		case DARKCYAN:
			return RGB(0, 128, 128);
		case BLACK://fall through
		default:
			return RGB(0, 0, 0);
	}
}