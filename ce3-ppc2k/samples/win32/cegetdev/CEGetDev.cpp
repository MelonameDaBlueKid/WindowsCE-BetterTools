// CEGetDev.cpp : Defines the entry point for the application.
// demostrates a 'Unique' way to get device caps.
// 

#include <windows.h>
#include "CEGetDev.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100
#define ID_LB 1000

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB, hwndListBox;			// 

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);

TCHAR	szTitle[] = L"CEGetDev";			// The title bar text
TCHAR	szWindowClass[] = L"CEGetDev App";		// The window class name
	
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
	wc.hIcon			= NULL;
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
	
	hInst = hInstance;		// Store instance handle in our global variable
	// Initialize global strings
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
	int i;
	int value;
	
	int wmId, wmEvent;
	
	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				
			case IDM_FILE_EXIT:
				DestroyWindow(hWnd);
				break;
				
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
			
			
			case WM_CREATE:
				{

					RECT rc;
					GetClientRect(hWnd, &rc);

					//Create a MenuBar
					SHMENUBARINFO mbi;
					memset(&mbi, 0, sizeof(SHMENUBARINFO));
					mbi.cbSize     = sizeof(SHMENUBARINFO);
					mbi.hwndParent = hWnd;
					mbi.nToolBarId = IDR_MENUBAR1;
					mbi.hInstRes   = hInst;
					mbi.nBmpId     = 0;
					mbi.cBmpImages = 0;	
        
					if (!SHCreateMenuBar(&mbi))
						MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
					
					//
					hwndListBox = CreateWindow(_T("LISTBOX"), NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL
						|LBS_NOINTEGRALHEIGHT|LBS_USETABSTOPS   , 
						rc.left, rc.top, rc.right, rc.bottom, hWnd, (HMENU)ID_LB, hInst,NULL);
					
					
					if (hwndListBox){
						//Iterate through the values to GetDeviceCaps
						hdc = GetDC (hWnd);
						for (i = 0; i < NINDEX ; i++) {
							value = GetDeviceCaps (hdc , DevCaps[i].Value);
							wsprintf (szbufW,_T("%s \t %8d"), DevCaps[i].String, value);
							SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM) szbufW);
							//Expand information returned from GetDeviceCaps if required
							ExpandInfo (hwndListBox, DevCaps[i].Value, value);
						}
						ReleaseDC (hWnd,hdc);
						//
						ShowWindow(hwndListBox, SW_SHOW);
						UpdateWindow(hwndListBox);
					}
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


//function:  ExpandInfo()
//input parameters:
//    hwnd  - parent of the list box with the info.
//    index - the input value which was sent to GetDeviceCaps().
//    value - the return value from calling GetDeviceCaps().
void ExpandInfo (HWND hwnd, int index, int value){
  int i;
  switch (index) {
	case TECHNOLOGY   :
		for (i = 0 ; i< NDevice ; i++) {
			if (value == Device[i].Value) {
				wsprintf (szbufW,space, Device[i].String);
				SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM)szbufW);
			}
		}
    break;
	case CURVECAPS    :
		for (i = 0 ; i< NCurveCaps ; i++) {
			if (value & CurveCaps[i].Value) {
				wsprintf (szbufW,space, CurveCaps[i].String);
				SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM)szbufW);
			}
		}
    break;
	case LINECAPS     :
		for (i = 0 ; i< NLineCaps ; i++) {
			if (value & LineCaps[i].Value) {
				wsprintf (szbufW,space, LineCaps[i].String);
				SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM)szbufW);
			}
		}
    break;
	case POLYGONALCAPS:
		for (i = 0 ; i< NPolygonalCaps ; i++) {
			if (value & PolygonalCaps[i].Value) {
				wsprintf (szbufW,space, PolygonalCaps[i].String);
				SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM)szbufW);
			}
		}
    break;
	case TEXTCAPS     :
		for (i = 0 ; i< NTextCaps ; i++) {
			if (value & TextCaps[i].Value) {
				wsprintf (szbufW,space, TextCaps[i].String);
				SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM)szbufW);
			}
		}
    break;
	case CLIPCAPS     :
		for (i = 0 ; i< NClipCaps ; i++) {
			if (value & ClipCaps[i].Value) {
				wsprintf (szbufW,space, ClipCaps[i].String);
				SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM)szbufW);
			}
		}
    break;
	case RASTERCAPS   :
		for (i = 0 ; i< NRasterCaps ; i++) {
			if (value & RasterCaps[i].Value) {
				wsprintf (szbufW,space, RasterCaps[i].String);
				SendMessage (hwndListBox, LB_ADDSTRING, 0, (LPARAM)szbufW);
			}
		}
    break;
	default:
    break;
  }
}
