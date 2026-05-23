// ShowFontInfo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ShowFontInfo.h"
#include <windowsx.h>
#include <commctrl.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				g_hwndCB;			// The command bar handle
HWND			g_hwndMain; //The main window
HWND			g_hwndShowFontInfo; //The basic dialog for the controls
//

TCHAR szSampleW[] = _T("The thin red line for the brown fox and lazy dog. 0123456789");

#define MAXNUMFONTS 50

typedef struct{	
	TCHAR  szFontNameW[LF_FACESIZE];
} FONTLIST;

FONTLIST ftList[MAXNUMFONTS];
int nFontCount;  

LOGFONT lf;


// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ShowFontInfoDlgProc (HWND, UINT, WPARAM, LPARAM);

//
void ShowTextMetrics( HWND );
void WindowSetFont(HWND , HFONT );
int CALLBACK EnumFontProc(const LOGFONT *,const TEXTMETRIC *, ULONG , LPARAM);

//
int WINAPI WinMain(	HINSTANCE hInstance,HINSTANCE hPrevInstance,	LPTSTR lpCmdLine,int nCmdShow){
	MSG msg;
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}
	
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) {
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
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHOWFONTINFO));
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
	TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
	TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name
	
	hInst = hInstance;		// Store instance handle in our global variable
	// Initialize global strings
	LoadString(hInstance, IDC_SHOWFONTINFO, szWindowClass, MAX_LOADSTRING);
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
		
				
	g_hwndMain = CreateWindow(szWindowClass, szTitle, WS_VISIBLE ,
		x, y, cx, cy, NULL, NULL, hInstance, NULL);


	if (!g_hwndMain){	
		return FALSE;
	}
	ShowWindow(g_hwndMain, nCmdShow);
	UpdateWindow(g_hwndMain);
	
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
				RECT rect;
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
        g_hwndCB = mbi.hwndMB;

				// Create the DialogWindow and center it under the commandbar
				GetClientRect(hWnd, &rect);
				g_hwndShowFontInfo = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SHOWFONTINFO), hWnd, (DLGPROC)ShowFontInfoDlgProc); 
				if ( g_hwndShowFontInfo )
				{
					MoveWindow(g_hwndShowFontInfo,	rect.left, rect.top, rect.right - rect.left ,rect.bottom - rect.top , TRUE);
					ShowWindow(g_hwndShowFontInfo, SW_SHOW);
					UpdateWindow(g_hwndShowFontInfo);
				}
				//
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

//------------------------------------------------------
// ShowFontInfoDlgProc
//------------------------------------------------------
LRESULT CALLBACK ShowFontInfoDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){  
	LRESULT	lResult = TRUE;
	int i, nSel;
	TCHAR szFontNameW[LF_FACESIZE];
	
	switch(msg)
	{
		case WM_COMMAND:
			switch (GET_WM_COMMAND_ID(wp,lp)){
				case IDD_FONTLIST:
					HFONT hf;
					HWND hwndLBFont;
					hwndLBFont = GetDlgItem(hwnd,IDD_FONTLIST);
					nSel = ListBox_GetCurSel(hwndLBFont);
					ListBox_GetText(hwndLBFont, nSel,(LPTSTR) szFontNameW);
					Static_SetText(GetDlgItem(hwnd,IDD_TM_NAME), (LPTSTR) szFontNameW);
					ShowTextMetrics( hwnd );
					hf = CreateFontIndirect( &lf );
					SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETFONT, (WPARAM) hf, TRUE);
					break;
			}
			break;
			
		case WM_INITDIALOG:
			{
				HDC hdc;
				HWND hwndLBFont;
				hwndLBFont = GetDlgItem(hwnd,IDD_FONTLIST);
				Edit_SetText(GetDlgItem(hwnd, IDC_EDIT1),szSampleW);
				lf.lfEscapement    = 0;
				lf.lfOrientation   = 0;
				lf.lfOutPrecision  = OUT_DEFAULT_PRECIS;
				lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
				
				nFontCount = 0;
				
				hdc = GetDC( GetParent( hwnd ) );
				EnumFonts( hdc, NULL, &EnumFontProc, (LPARAM) &ftList );
				ListBox_ResetContent(hwndLBFont);
				for( i=0; i < nFontCount; i++ ){
					ListBox_AddString(hwndLBFont, (LPTSTR)ftList[i].szFontNameW);
				}
				ReleaseDC( GetParent( hwnd ), hdc );
				ShowTextMetrics( hwnd );  
			}
			break;
				
		default:
			return(FALSE);
			break;
	}
	
  UNREFERENCED_PARAMETER(wp);
  UNREFERENCED_PARAMETER(lp);
	return (lResult);
}

//
void ShowTextMetrics( HWND hWnd ){
	TCHAR  szFontNameW[LF_FACESIZE];
	BOOL   bTrans;
	HFONT  hFont;
	HDC    hdc;
	int    i; 
	static TEXTMETRIC tm;
	struct FONTINFO{
		int  nDlgID;
		long *pTM;   
	};
	static struct FONTINFO FontData[] = {  
		IDD_TM_HEIGHT,   &tm.tmHeight,
		IDD_TM_ASCENT,   &tm.tmAscent,
		IDD_TM_DESCENT,  &tm.tmDescent,
		IDD_TM_LEADINT,  &tm.tmInternalLeading,
		IDD_TM_LEADEXT,  &tm.tmExternalLeading,
		IDD_TM_WIDTHAVG, &tm.tmAveCharWidth,
		IDD_TM_WIDTHMAX, &tm.tmMaxCharWidth,
		IDD_TM_WEIGHT,   &tm.tmWeight,
		IDD_TM_OVER,     &tm.tmOverhang,
		IDD_TM_DIGITX,   &tm.tmDigitizedAspectX,
		IDD_TM_DIGITY,   &tm.tmDigitizedAspectY   
	};
				
	lf.lfHeight = GetDlgItemInt( hWnd, IDD_HEIGHT, &bTrans, TRUE  );
	lf.lfWidth  = GetDlgItemInt( hWnd, IDD_WIDTH,  &bTrans, FALSE );
	lf.lfWeight = GetDlgItemInt( hWnd, IDD_WEIGHT, &bTrans, FALSE );
	GetDlgItemText( hWnd, IDD_TM_NAME, lf.lfFaceName, LF_FACESIZE );
	hdc = GetDC( hWnd );
	hFont = (HFONT)SelectObject( hdc, CreateFontIndirect( &lf ) );
	GetTextMetrics( hdc, &tm );
	SetDlgItemInt( hWnd, IDD_HEIGHT, tm.tmHeight, FALSE );
	SetDlgItemInt( hWnd, IDD_WIDTH,  tm.tmAveCharWidth, FALSE );
	SetDlgItemInt( hWnd, IDD_WEIGHT, tm.tmWeight, FALSE );
	GetTextFace( hdc, sizeof( szFontNameW ), szFontNameW );
	SendDlgItemMessage( hWnd, IDD_TM_NAME, WM_SETTEXT, 0, (DWORD)(LPTSTR) szFontNameW );
	DeleteObject( SelectObject( hdc, hFont ) );
	ReleaseDC( hWnd, hdc );
	for( i = 0; i < sizeof(FontData)/sizeof(FontData[0]); i++ )
		SetDlgItemInt( hWnd, FontData[i].nDlgID, *FontData[i].pTM, TRUE );
	return;
}

int CALLBACK EnumFontProc(const LOGFONT  * lf, const TEXTMETRIC  *tm, ULONG nFontType,  LPARAM ftList )
{
	if (nFontCount == MAXNUMFONTS) return FALSE; //Too many fonts
	FONTLIST *lpft;
	lpft = (FONTLIST *)ftList;
	_tcscpy( lpft[nFontCount].szFontNameW, (LPTSTR) lf->lfFaceName );
	nFontCount++;
	return TRUE;
} 

