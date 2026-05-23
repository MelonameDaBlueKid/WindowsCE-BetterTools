/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF

  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO

  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A

  PARTICULAR PURPOSE.

  

    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/

// GetUUID.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GetUUID.h"
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
#include <Objbase.h>
#include <uniqueid.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			g_hInst;				// The current instance
HWND				g_hwndCB;					// The command bar handle
GUID				g_Guid;

static SHACTIVATEINFO s_sai;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE, LPTSTR);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
HWND				CreateRpCommandBar(HWND);
BOOL GetDeviceID( GUID* pGuid);

// Purpose: Determine at runtime if the app is running on a pocket pc device
static BOOL IsPocketPC() 
{
    TCHAR tszPlatform[64];

    if (TRUE == SystemParametersInfo(SPI_GETPLATFORMTYPE,
         sizeof(tszPlatform)/sizeof(*tszPlatform),tszPlatform,0))
    {
        if (0 == _tcsicmp(TEXT("PocketPC"), tszPlatform)) 
        {
            return TRUE;
        }
    }
    return FALSE;   
}

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

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_GETUUID);

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
//    It is important to call this function so that the application 
//    will get 'well formed' small icons associated with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
	WNDCLASS	wc;

    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GETUUID));
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
	HWND	hWnd = NULL;
	TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
	TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

	g_hInst = hInstance;		// Store instance handle in our global variable
	// Initialize global strings
	LoadString(hInstance, IDC_GETUUID, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	//If it is already running, then focus on the window
	hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd) 
	{
		SetForegroundWindow (hWnd);    
		return 0;
	} 

	MyRegisterClass(hInstance, szWindowClass);
	
	RECT	rect;
	GetClientRect(hWnd, &rect);
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{	
		return FALSE;
	}
	//When the main window is created using CW_USEDEFAULT the height of the menubar (if one
	// is created is not taken into account). So we resize the window after creating it
	// if a menubar is present
	{
		if (IsPocketPC())
		{
			RECT rc;
			GetWindowRect(hWnd, &rc);
			rc.bottom -= MENU_HEIGHT;
			if (g_hwndCB)
				MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
		}
	}


	// get the device ID this function in implemented at the end of this file
	GetDeviceID(&g_Guid);
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
	WCHAR szData[MAX_LOADSTRING];
	WCHAR * szDataIndex;
	int i;
	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{	
				case IDM_HELP_ABOUT:
					MessageBox(hWnd, _T(" GetUUID Version 1.0\n\nCopyright (C) 2001"), _T("About"), MB_OK);
				    break;
				case IDOK:
					SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
					SendMessage (hWnd, WM_CLOSE, 0, 0);
					break;
				case IDM_QUIT:
					DestroyWindow(hWnd);
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_CREATE:
			g_hwndCB = CreateRpCommandBar(hWnd);
            // Initialize the shell activate info structure
            memset (&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
			break;
		case WM_PAINT:
			RECT rt;
			
			memset(szData, 0, sizeof(WCHAR) * MAX_LOADSTRING);
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);
			
			StringFromGUID2(g_Guid, szData, MAX_LOADSTRING);
			
			rt.bottom = 18;
			//draw the first DWORD including leading '{'
			DrawText(hdc, szData, 10, &rt, 
				DT_CENTER);
			rt.left += 3;
			szDataIndex = szData + 10;
			// draw the 3 middle WORD segments
			for ( i = 0; i < 3; i++)
			{
				rt.top += 18;
				rt.bottom+=18;
				DrawText(hdc, szDataIndex, 5, &rt, 
					DT_CENTER);
				szDataIndex = szDataIndex + 5;
				
			}
			
			rt.top += 18;
			rt.bottom+=18;
			//draw the last WORD,DWORD including trailing '}'
			DrawText(hdc, szDataIndex, 13, &rt, 
				DT_CENTER);

			EndPaint(hWnd, &ps);
			break; 
		case WM_DESTROY:
			CommandBar_Destroy(g_hwndCB);
			PostQuitMessage(0);
			break;
		case WM_ACTIVATE:
            // Notify shell of our activate message
			SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
     		break;
		case WM_SETTINGCHANGE:
			SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
     		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

HWND CreateRpCommandBar(HWND hwnd)
{
	SHMENUBARINFO mbi;

	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hwnd;
	mbi.nToolBarId = IDM_MENU;
	mbi.hInstRes   = g_hInst;
	mbi.nBmpId     = 0;
	mbi.cBmpImages = 0;

	if (!SHCreateMenuBar(&mbi)) 
		return NULL;

	return mbi.hwndMB;
}




BOOL GetDeviceID( GUID* pGuid)
{
	BOOL fRes;
    DWORD dwBytesReturned =0;
	DEVICE_ID* pDevID;
	int wSize;

	if (NULL == pGuid)
		return FALSE;

	memset(pGuid, 0, sizeof(GUID));

	pDevID = (DEVICE_ID*)malloc(sizeof(DEVICE_ID));
	memset(pDevID, 0, sizeof(DEVICE_ID));
	pDevID->dwSize = sizeof(DEVICE_ID);

   fRes = KernelIoControl( IOCTL_HAL_GET_DEVICEID, NULL, 0,
            pDevID, sizeof( DEVICE_ID ), &dwBytesReturned );

	wSize = pDevID->dwSize;
	free(pDevID);
	if( (FALSE != fRes) || (ERROR_INSUFFICIENT_BUFFER != GetLastError()))
		return FALSE;

	pDevID = (DEVICE_ID*)malloc(wSize);
	memset(pDevID, 0, sizeof(wSize));
	pDevID->dwSize = wSize;
    fRes = KernelIoControl( IOCTL_HAL_GET_DEVICEID, NULL, 0,
            pDevID, wSize, &dwBytesReturned );

	if((FALSE == fRes) || (ERROR_INSUFFICIENT_BUFFER == GetLastError()) )
		return FALSE;

	BYTE* pDat = (BYTE*)&pGuid->Data1;
	BYTE* pSrc = (BYTE*)(pDevID) + pDevID->dwPresetIDOffset;
	memcpy(pDat, pSrc, pDevID->dwPresetIDBytes);
	pDat +=  pDevID->dwPresetIDBytes;
	pSrc =  (BYTE*)(pDevID) + pDevID->dwPlatformIDOffset;
	memcpy(pDat, pSrc, pDevID->dwPlatformIDBytes);

	return true;
}
