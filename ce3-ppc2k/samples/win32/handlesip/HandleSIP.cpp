// HandleSIP.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HandleSIP.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100
#define ID_EDIT1 5000
#define ID_EDIT2 5001
#define ID_EDIT3 5002
#define ID_EDIT4 5003


// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HWND				hwndEdit1, hwndEdit2;
HWND				hwndEdit3, hwndEdit4;

TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

BOOL fSHFORCERESIZE = FALSE;
BOOL fENFOCUS = FALSE;

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
	
	/// InitInstance
	LoadString(hInstance, IDC_HANDLESIP, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	
	// Look for running instance of application
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
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HANDLESIP));
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
	SIPINFO si = {0};
	
	hInst = hInstance;		// Store instance handle in our global variable
	// Initialize global strings
	MyRegisterClass(hInstance, szWindowClass);
	
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
	SHACTIVATEINFO sai;
	
	
	/////////////////////////	
	switch (message) 
	{
		case WM_SETTINGCHANGE:
			if (SPI_SETSIPINFO == wParam){
				memset(&sai, 0, sizeof(SHACTIVATEINFO));
				SHHandleWMSettingChange(hWnd, (fSHFORCERESIZE ? -1 : wParam), (fSHFORCERESIZE ? 0 : lParam), &sai);
				Edit_SetText(GetDlgItem(hWnd, ID_EDIT3), (sai.fSipUp ? L"SipUP" : L"SipDOWN"));
				Edit_SetText(GetDlgItem(hWnd, ID_EDIT4), L"WM_SETTINGCHANGE");
			}
			break;
			
		case WM_ACTIVATE:
			if (SPI_SETSIPINFO == wParam){
				memset(&sai, 0, sizeof(SHACTIVATEINFO));
				SHHandleWMActivate(hWnd, wParam, lParam, &sai, 0);
				Edit_SetText(GetDlgItem(hWnd, ID_EDIT4), L"WM_ACTIVATE");
			}
			break;
						
		case WM_SIZE:
			Edit_SetText(GetDlgItem(hWnd, ID_EDIT4), L"WM_SIZE");
			break;
			
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_EDIT1:
				switch(wmEvent){
				case EN_SETFOCUS:
					if (fENFOCUS) SHSipPreference(hWnd, SIP_UP);
					Edit_SetText(GetDlgItem(hWnd, ID_EDIT1), L"EN_SETFOCUS");
					break;
				case EN_KILLFOCUS:
					if (fENFOCUS) SHSipPreference(hWnd, SIP_DOWN);
					Edit_SetText(GetDlgItem(hWnd, ID_EDIT1), L"EN_KILLFOCUS");
					break;
				}
				break;
				
				case ID_EDIT2:
					switch(wmEvent){
					case EN_SETFOCUS:
						Edit_SetText(GetDlgItem(hWnd, ID_EDIT2), L"EN_SETFOCUS");
						break;
					case EN_KILLFOCUS:
						Edit_SetText(GetDlgItem(hWnd, ID_EDIT2), L"EN_KILLFOCUS");
						break;
					}
					break;
					
				
			case ID_SHOW_SHSIPPREFRENCE_SIPUP:
				SHSipPreference(hWnd, SIP_UP);
				break;
			case ID_SHOW_SHSIPPREFRENCE_SIPDOWN:
				SHSipPreference(hWnd, SIP_DOWN);
				break;
			case ID_SHOW_SHSIPPREFRENCE_SIPFORCEDOWN:
				SHSipPreference(hWnd, SIP_FORCEDOWN);
				break;
			case ID_SHOW_SHSIPPREFRENCE_SIPUNCHANGED:
				SHSipPreference(hWnd, SIP_UNCHANGED);
				break;
				
			case ID_SHOW_SHFORCERESIZE:
				{
					fSHFORCERESIZE = (fSHFORCERESIZE ? FALSE : TRUE); 
					HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
					CheckMenuItem(hm, ID_SHOW_SHFORCERESIZE, (fSHFORCERESIZE ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
				}
				break;
				
			case ID_SHOW_ONENFOCUS:
				{
					fENFOCUS = (fENFOCUS ? FALSE : TRUE); 
					HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
					CheckMenuItem(hm, ID_SHOW_ONENFOCUS, (fENFOCUS ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
				}
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
				
				//Create two edit controls
				hwndEdit1 = CreateWindow(L"edit",L"Edit Number 1",WS_CHILD | WS_BORDER,10,25,100,25,hWnd,(HMENU)ID_EDIT1,hInst, NULL);
				hwndEdit2 = CreateWindow(L"edit",L"Edit Number 2",WS_CHILD | WS_BORDER,130,25,100,25,hWnd,(HMENU)ID_EDIT2,hInst, NULL);
				hwndEdit3 = CreateWindow(L"edit",L"Edit Number 1",WS_CHILD | WS_BORDER,10,50,100,25,hWnd,(HMENU)ID_EDIT3,hInst, NULL);
				hwndEdit4 = CreateWindow(L"edit",L"Edit Number 2",WS_CHILD | WS_BORDER,130,50,100,25,hWnd,(HMENU)ID_EDIT4,hInst, NULL);
				ShowWindow(hwndEdit1, SW_SHOW);
				ShowWindow(hwndEdit2, SW_SHOW);
				ShowWindow(hwndEdit3, SW_SHOW);
				ShowWindow(hwndEdit4, SW_SHOW);
				
				break;//WM_CREATE
				
			case WM_PAINT:
				RECT rt;
				hdc = BeginPaint(hWnd, &ps);
				GetClientRect(hWnd, &rt);
				
				Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
				InflateRect(&rt, -2, -2);
				Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
				InflateRect(&rt, -2, -2);
				Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
				
				DrawText(hdc, L"Center Of Window", _tcslen(L"Center Of Window"), &rt, 
					DT_SINGLELINE | DT_VCENTER | DT_CENTER);
				EndPaint(hWnd, &ps);
				break;//WM_DESTROY
				
			case WM_DESTROY:
				PostQuitMessage(0);
				break;//WM_DESTROY
				
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
		{
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
    }
		
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
