//
// SystemParametersInfo.cpp : Defines the entry point for the application.
//
//

#include "stdafx.h"
#include "SystemParametersInfo.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100
#define ID_EDIT 1000


// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HWND				hwndListBox;		// The Edit control

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
void ShowSystemParameterInfo(HWND hwnd);

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
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SYSTEMPARAMETERSINFO));
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
	LoadString(hInstance, IDC_SYSTEMPARAMETERSINFO, szWindowClass, MAX_LOADSTRING);
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
	RECT rc;
	
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
        
        //SHCreateMenuBar(&mbi);
      //if (!SHCreateMenuBar(&mbi))
        //MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
        //hwndCB = mbi.hwndMB;


				//Create Edit control
				GetClientRect(hWnd, &rc);

				hwndListBox = CreateWindow(_T("listbox") , NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, 
					rc.left, rc.top, rc.right, rc.bottom , 
					hWnd, (HMENU)ID_EDIT, hInst, NULL);
				if (hwndListBox){
				//Do the demonstration code:
					ShowSystemParameterInfo(hwndListBox);
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

//
//
//	Demostration Code Here
//
//
/*
SPI_GETBATTERYIDLETIMEOUT 
Gets the amount of time that Windows CE will stay on with battery power 
before it suspends due to user inaction. The pvParam parameter points 
to a DWORD that returns the time in seconds. 
This flag is ignored if pvParam is zero. 
*/
BOOL spiGETBATTERYIDLETIMEOUT(DWORD *timeout){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	
	fRetStatus = SystemParametersInfo( SPI_GETBATTERYIDLETIMEOUT, uiParam, timeout, 0 );
	return fRetStatus;
} 
/*
SPI_GETEXTERNALIDLETIMEOUT 
Gets the amount of time that Windows CE will stay on with AC power 
before it suspends due to user inaction. The pvParam parameter 
points to a DWORD that returns the time in seconds. 
This flag is ignored if pvParam is zero. 
*/
DWORD spiGETEXTERNALIDLETIMEOUT (DWORD *timeout){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	
	fRetStatus = SystemParametersInfo( SPI_GETEXTERNALIDLETIMEOUT, uiParam, timeout, 0 );
	return fRetStatus;
} 
/*
SPI_GETMOUSE 
Retrieves the two mouse threshold values and the mouse speed. 
*/
DWORD spiGETMOUSE (DWORD *param1, DWORD *param2){
	BOOL fRetStatus = FALSE;
	
	fRetStatus = SystemParametersInfo( SPI_GETMOUSE, (INT)&param1, param2, 0 );
	return fRetStatus;
} 
/*
SPI_GETOEMINFO 
Returns a string containing the model number and manufacturer name. 
The uiParam parameter specifies the length of the buffer in pvParam, 
which on successful return contains the string in Unicode characters.
*/
DWORD spiGETOEMINFO (LPTSTR lpszW, DWORD *count){
	BOOL fRetStatus = FALSE;
	
	fRetStatus = SystemParametersInfo( SPI_GETOEMINFO, (INT)&count, lpszW, 0 );
	return fRetStatus;
}
/*
SPI_GETPLATFORMTYPE 
Returns a string specifying the type of Windows CE device, such as "H/PC". 
The uiParam parameter specifies the length of the buffer in pvParam, 
which on successful return contains the string in Unicode characters. 
This string allows applications like H/PC Explorer to determine the device type. 
*/
DWORD spiGETPLATFORMTYPE (LPTSTR lpszW, DWORD *count){
	BOOL fRetStatus = FALSE;
	
	fRetStatus = SystemParametersInfo( SPI_GETPLATFORMTYPE, (INT)&count, lpszW, 0 );
	return fRetStatus;
} 
/*
SPI_GETWAKEUPIDLETIMEOUT 
Gets the amount of time that Windows CE will stay on after a user notification 
that reactivates a suspended device. The pvParam parameter points to a DWORD 
that returns the time in seconds. This flag is ignored if pvParam is zero. 
*/
DWORD spiGETWAKEUPIDLETIMEOUT (DWORD *timeout){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	
	fRetStatus = SystemParametersInfo( SPI_GETWAKEUPIDLETIMEOUT, uiParam, timeout, 0 );
	return fRetStatus;
} 
/*
SPI_GETWORKAREA 
Retrieves the size of the work area; the portion of the screen not obscured 
by the tray. 
*/
DWORD spiGETWORKAREA (LPRECT lprc){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	
	fRetStatus = SystemParametersInfo( SPI_GETWORKAREA, uiParam, lprc, 0 );
	return fRetStatus;
} 
/*
SPI_SETBATTERYIDLETIMEOUT 
Sets the amount of time that Windows CE will stay on with battery power 
before it suspends due to user inaction. The Windows CE operating system 
will remain on, with battery power, as long as the keyboard or touch screen 
is active. The uiParam parameter specifies the time to set in seconds. 
This flag is ignored if uiParam is set to zero. 
*/
DWORD  spiSETBATTERYIDLETIMEOUT (DWORD *timeout){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	
	fRetStatus = SystemParametersInfo( SPI_SETBATTERYIDLETIMEOUT, uiParam, timeout, 0 );
	return fRetStatus;
} 
/*
SPI_SETEXTERNALIDLETIMEOUT 
Sets the amount of time that Windows CE will stay on with AC power before 
it suspends due to user inaction. The Windows CE operating system will remain on, 
with AC power, as long as the keyboard or touch screen is active. 
The uiParam parameter specifies the time in seconds. This flag is ignored 
if uiParam is set to zero. 
*/
DWORD spiSETEXTERNALIDLETIMEOUT (DWORD *timeout){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  

	fRetStatus = SystemParametersInfo( SPI_SETEXTERNALIDLETIMEOUT, uiParam, timeout, 0 );
	return fRetStatus;
} 
/*
SPI_SETMOUSE 
Sets the two mouse threshold values and the mouse speed. 
*/
DWORD spiSETMOUSE (){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	PVOID pvParam = NULL;
	
	fRetStatus = SystemParametersInfo( SPI_SETMOUSE, uiParam, pvParam, 0 );
	return fRetStatus;
} 
/*
SPI_SETWAKEUPIDLETIMEOUT 
Sets the amount of time that Windows CE will stay on after a user notification 
that reactivates the suspended device. The uiParam parameter specifies the time in seconds. This flag is ignored if uiParam is set to zero. 
*/
DWORD spiSETWAKEUPIDLETIMEOUT (){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	PVOID pvParam = NULL;
	
	fRetStatus = SystemParametersInfo( SPI_SETWAKEUPIDLETIMEOUT, uiParam, pvParam, 0 );
	return fRetStatus;
} 
/*
SPI_SETWORKAREA 
Sets the size of the work area — the portion of the screen not obscured by the taskbar. 
*/
DWORD spiSETWORKAREA (){
	BOOL fRetStatus = FALSE;
	UINT uiParam = 0;  
	PVOID pvParam = NULL;
	
	fRetStatus = SystemParametersInfo( SPI_SETWORKAREA, uiParam, pvParam, 0 );
	return fRetStatus;
} 

void ShowSystemParameterInfo(HWND hwnd){
	TCHAR szbufW[MAX_PATH];
	TCHAR szbuf1W[MAX_PATH];
	RECT rc;
	DWORD dw1;
	DWORD dw2;

	if (spiGETBATTERYIDLETIMEOUT(&dw1)){
		szbufW[0] = '\0';
		wsprintf(szbufW, _T("SPI_GETBATTERYIDLETIMEOUT: %d"), dw1);
		SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM)(LPTSTR)szbufW);
	}
	if (spiGETEXTERNALIDLETIMEOUT(&dw1)){
		szbufW[0] = '\0';
		wsprintf(szbufW, _T("SPI_GETEXTERNALIDLETIMEOUT: %d"), dw1);
		ListBox_AddString(hwnd, szbufW);
	}
	if (spiGETMOUSE(&dw1, &dw2)){
		szbufW[0] = '\0';
		wsprintf(szbufW, _T("SPI_GETMOUSE: %d %d"), dw1, dw2);
		ListBox_AddString(hwnd, szbufW);
	}
	if (spiGETOEMINFO(szbuf1W, &dw1)){
		szbufW[0] = '\0';
		wsprintf(szbufW, _T("SPI_GETOEMINFO:"));
		ListBox_AddString(hwnd, szbufW);
		wsprintf(szbufW, _T(" %s"), szbuf1W);
		ListBox_AddString(hwnd, szbufW);
	}
	if (spiGETPLATFORMTYPE(szbuf1W, &dw1)){
		szbufW[0] = '\0';
		wsprintf(szbufW, _T("SPI_GETPLATFORMTYPE:"));
		ListBox_AddString(hwnd, szbufW);
		wsprintf(szbufW, _T(" %s"), szbuf1W);
		ListBox_AddString(hwnd, szbufW);
	}
	if (spiGETWORKAREA(&rc)){
		szbufW[0] = '\0';
		wsprintf(szbufW, _T("SPI_GETWORKAREA: %d %d %d %d"), rc.top, rc.left, rc.right, rc.bottom);
		ListBox_AddString(hwnd, szbufW);
	}
}
