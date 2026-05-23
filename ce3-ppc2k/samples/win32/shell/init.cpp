// init.cpp : All the initialization functions like creating windows and toolbars
//

#include "stdafx.h"

//////////////////////////////////////
// File specific definitions
//////////////////////////////////////
#define MAX_LOADSTRING 100


//////////////////////////////////////
// Global Variables Set in this file
//////////////////////////////////////
HINSTANCE	g_hinst;								// current instance
INT			g_dyCB;									// height of CommandBar
HWND		g_hwndMain;								// main window
HWND		g_hwndCB;								// toolbar window
TCHAR		g_szHello[256];							// string to print in window
HMENU		g_hmenu;								// menu handle for enable/disable



//////////////////////////////////////
// Foward declarations of functions included in this code module:
//////////////////////////////////////
static ATOM		MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass);


//////////////////////////////////////
// Functions Segment
//////////////////////////////////////


//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
HWND	hwndOther;
TCHAR	szTitle[MAX_LOADSTRING];				// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];			// The window class name


	//
	// Read in from resource file
	//
	LoadString(hInstance, IDC_SHELL,	 szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle,		MAX_LOADSTRING);
	LoadString(g_hinst,	  IDS_HELLO,	 g_szHello,		MAX_LOADSTRING);

    //
	// if there is already an instance of running, exit
    //
	hwndOther = FindWindow(szWindowClass,NULL);
    if (hwndOther) {
		SetForegroundWindow((HWND) ((ULONG) hwndOther | 0x1));
        return FALSE;
    }

	g_hinst = hInstance; // Store instance handle in our global variable

	//
	// initialize other common controls
	//
	INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC  = ICC_BAR_CLASSES | ICC_COOL_CLASSES; 
    InitCommonControlsEx(&icex);

	MyRegisterClass(g_hinst, szWindowClass);
	
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
		
				
	g_hwndMain = CreateWindow(szWindowClass, szTitle, WS_VISIBLE | WS_BORDER,
		x, y, cx, cy, NULL, NULL, hInstance, NULL);

		
	if (!g_hwndMain)
		return FALSE;

	//
	// create control UI on main window
	//
	SendMessage(g_hwndMain, WM_SETTINGCHANGE, SPI_SETSIPINFO, 0);
	g_hwndCB = CreateMenuBar(g_hwndMain);

	
	ShowWindow(g_hwndMain, nCmdShow);
	UpdateWindow(g_hwndMain);

	return TRUE;
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
WNDCLASS wc;

    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= 0;
    wc.hCursor			= 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;

	return RegisterClass(&wc);
}


//
//   FUNCTION: CreateToolbar(HWND hwndParent)
//
//   PURPOSE: Creates and populates commandband
//
//   COMMENTS:
//
//        In this function, we create the commandbands for the menus and toolbar
//
HWND CreateMenuBar(HWND hwndParent)
{
	//Create a MenuBar
	SHMENUBARINFO mbi;
	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hwndParent;
	mbi.nToolBarId = IDM_MAIN_MENU;
	mbi.hInstRes   = g_hinst ;
	mbi.nBmpId     = IDB_BARTAG; //Resource ID of a bitmap to use 
	mbi.cBmpImages = 7;	//Number of images on the bitmap (they are 16 x 16 pixels in size)
	
	if (!SHCreateMenuBar(&mbi))
		MessageBox(hwndParent, L"SHCreateMenuBar Failed", L"Error", MB_OK);
	HWND hWnd = mbi.hwndMB;
	
	
	g_hmenu = SHGetSubMenu(hWnd, IDM_MAIN_MENUITEM1);
	//
	// Disable Properties menu item when g_szFile is NULL
	//
	EnablePropertyItem();
	
	return hWnd;
}


//
// FUNCTION: EnablePropertyItem(BOOL)
//
// PURPOSE:  disable the Properties item from the File menu based on g_szFile
//
void EnablePropertyItem()
{
DWORD fFlags;

	if (g_szFile)
		fFlags = MF_ENABLED;
	else
		fFlags = MF_GRAYED; // MF_DISABLED is not supported in WindowsCE
		
	EnableMenuItem(g_hmenu, IDM_FILEPROPERTIES, MF_BYCOMMAND | fFlags);
}

