// DrawingLines.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DrawingLines.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HMENU hMenu;
// 
BOOL fSolid = TRUE; //default solid pen
BOOL fHoriz = TRUE; //default horizontal draw
UINT nROP = ID_ROPCODE_R2_BLACK; //defalut ROPCode

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
//
//void UpdateMenu(HWND hWnd, hMenu hMenu, UINT IDCTL){
void UpdateMenu(HWND , HMENU , UINT );
//void DrawLines(HWND hWnd, HDC hdc, BOOL fHoriz, UINT nRop, BOOL fSolid){
void DrawLines(HWND , HDC , BOOL , UINT , BOOL );
//void DrawSolidLine(HDC hdc, INT width, POINT ptStart, POINT ptEnd, COLORREF cr){
void DrawSolidLine(HDC , INT , POINT , POINT , COLORREF );
//void DrawDashLine(HDC hdc, INT width, , POINT ptStart, POINT ptEnd, COLORREF cr){
void DrawDashLine(HDC , INT ,POINT , POINT , COLORREF );


//

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
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWINGLINES));
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
	LoadString(hInstance, IDC_DRAWINGLINES, szWindowClass, MAX_LOADSTRING);
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
			switch (wmId){
				case IDM_HELP_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_FILE_EXIT:
				   DestroyWindow(hWnd);
				   break;
				//
				case ID_ROPCODE_R2_BLACK:
				case ID_ROPCODE_R2_COPYPEN:
				case ID_ROPCODE_R2_MASKNOTPEN:
				case ID_ROPCODE_R2_MASKPEN:
				case ID_ROPCODE_R2_MASKPENNOT:
				case ID_ROPCODE_R2_MERGENOTPEN:
				case ID_ROPCODE_R2_MERGEPENNOT:
				case ID_ROPCODE_R2_NOT:
				case ID_ROPCODE_R2_NOTCOPYPEN:
				case ID_ROPCODE_R2_NOTMASKPEN:
				case ID_ROPCODE_R2_NOTMERGEPEN:
				case ID_ROPCODE_R2_NOTXORPEN:
				case ID_ROPCODE_R2_WHITE:
				case ID_ROPCODE_R2_XORPEN:
					hMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM3);
					UpdateMenu(hWnd, hMenu, wmId);
					break;
					
				case ID_PEN_PSSOLID:
				case ID_PEN_PSDASH:
				case ID_PEN_HORIZONTAL:
				case ID_PEN_VERTICAL: //fall through
					hMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
					UpdateMenu(hWnd, hMenu, wmId);
					break;
				//
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
			
			CheckMenuRadioItem(hMenu,ID_PEN_PSSOLID, ID_PEN_PSDASH, ID_PEN_PSSOLID, MF_BYCOMMAND);
			CheckMenuRadioItem(hMenu,ID_PEN_HORIZONTAL, ID_PEN_VERTICAL, ID_PEN_HORIZONTAL, MF_BYCOMMAND);

			hMenu = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM3);
			CheckMenuRadioItem(hMenu,ID_ROPCODE_R2_BLACK, ID_ROPCODE_R2_WHITE, ID_ROPCODE_R2_BLACK, MF_BYCOMMAND);
			break;
			
		case WM_PAINT:
			POINT ptTrig[4];
			RECT rc;
			//get some area info
			GetClientRect(hWnd, &rc);

			ptTrig[0].x = ptTrig[3].x = ptTrig[1].x = rc.left;
			ptTrig[0].y = ptTrig[3].y = rc.top;
			ptTrig[2].y = ptTrig[1].y = rc.bottom;
			ptTrig[2].x = rc.right;
			hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			Polygon(hdc, ptTrig, 4);
			SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
			ptTrig[0].x = ptTrig[3].x = ptTrig[2].x /2; 
			ptTrig[0].y = ptTrig[3].y = ptTrig[2].y /3; 
			Polygon(hdc, ptTrig, 4);
			SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
			//
			DrawLines(hWnd, hdc, fHoriz, nROP, fSolid);
			//
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
//
void UpdateMenu(HWND hWnd, HMENU hMenu, UINT IDCTL){
	
	switch(IDCTL){
		case ID_PEN_PSSOLID:
		fSolid = TRUE;
		CheckMenuRadioItem(hMenu,ID_PEN_PSSOLID, ID_PEN_PSDASH, IDCTL, MF_BYCOMMAND);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
		case ID_PEN_PSDASH:
		fSolid = FALSE;
		CheckMenuRadioItem(hMenu,ID_PEN_PSSOLID, ID_PEN_PSDASH, IDCTL, MF_BYCOMMAND);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
		case ID_PEN_HORIZONTAL:
		fHoriz = TRUE;
		CheckMenuRadioItem(hMenu,ID_PEN_HORIZONTAL, ID_PEN_VERTICAL, IDCTL, MF_BYCOMMAND);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
		case ID_PEN_VERTICAL:
		fHoriz = FALSE;
		CheckMenuRadioItem(hMenu,ID_PEN_HORIZONTAL, ID_PEN_VERTICAL, IDCTL, MF_BYCOMMAND);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
		default:
		nROP = IDCTL;
		CheckMenuRadioItem(hMenu,ID_ROPCODE_R2_BLACK, ID_ROPCODE_R2_WHITE, IDCTL, MF_BYCOMMAND);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
}


#define NUMPOINTS 2
#define OFFSET 20
#define MARGIN 10
//
void DrawLines(HWND hWnd, HDC hdc, BOOL fHoriz, UINT nRop, BOOL fSolid){
	RECT rc;
	int i, j = 1;
	POINT pt[NUMPOINTS];
	
	//get some area info
	GetClientRect(hWnd, &rc);
	
	//set ROP codes
	SetROP2(hdc, nRop);
	//
	if (fHoriz){
		pt[0].x = rc.left + MARGIN;
		pt[1].x = rc.right - MARGIN;
		for (i = rc.top + MARGIN; i < rc.bottom - MARGIN; i += OFFSET){
			pt[0].y = i;
			pt[1].y = i;
			fSolid ? DrawSolidLine(hdc, j++, pt[0], pt[1], 0) :
				DrawDashLine(hdc, j++, pt[0], pt[1], 0);
		}
	} else {
		pt[0].y = rc.top + MARGIN;
		pt[1].y = rc.bottom - MARGIN;
		for (i = rc.left + MARGIN; i < rc.right - MARGIN; i += OFFSET){
			pt[0].x = i;
			pt[1].x = i;
			fSolid ? DrawSolidLine(hdc, j++, pt[0], pt[1], 0) :
				DrawDashLine(hdc, j++, pt[0], pt[1], 0);
		}
	}
	
	return;
}

void DrawSolidLine(HDC hdc, INT width, POINT ptStart, POINT ptEnd, COLORREF cr){
	POINT pt[2];
	HPEN hpSolid, hpOld;
	//Create a solid pen
	hpSolid = (HPEN)CreatePen(PS_SOLID, width, cr);
	hpOld = (HPEN)SelectObject(hdc, hpSolid);

	pt[0].x = ptStart.x;
	pt[0].y = ptStart.y;
	pt[1].x = ptEnd.x;
	pt[1].y = ptEnd.y;
	Polyline(hdc, pt, NUMPOINTS);
	SelectObject(hdc, hpOld);
	DeleteObject((HPEN)hpSolid);
} 

void DrawDashLine(HDC hdc, INT width, POINT ptStart, POINT ptEnd, COLORREF cr){
	int i;
	HPEN hpDash,hpOld;
	POINT pt[2];
	//Create a dot pen
	hpDash = (HPEN)CreatePen(PS_DASH, 1, cr);
	hpOld = (HPEN)SelectObject(hdc, hpDash);

	pt[0].x = ptStart.x;
	pt[0].y = ptStart.y;
	pt[1].x = ptEnd.x;
	pt[1].y = ptEnd.y;
	
	//increment on smallest variance
	if(abs(ptStart.x - ptEnd.x) < abs(ptStart.y - ptEnd.y)){
		for (i = 0; i < width; i++){
			pt[0].x += 1;
			pt[1].x += 1;	
			Polyline(hdc, pt, NUMPOINTS);
		}	
	} else {
		for (i = 0; i < width; i++){
			pt[0].y += 1;
			pt[1].y += 1;	
			Polyline(hdc, pt, NUMPOINTS);
		}	
	}

	SelectObject(hdc, hpOld);
	DeleteObject((HPEN)hpDash);

} 