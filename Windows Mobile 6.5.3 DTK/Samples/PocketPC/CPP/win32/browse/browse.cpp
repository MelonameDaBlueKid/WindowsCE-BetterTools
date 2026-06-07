//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//


// ****************************************************************************
// FILE: browse.cpp
// ABTRACT: Browser Control SDK sample program implementation
// ****************************************************************************
// NOTE: start.html, news.html, and supplies.html must be present
//   on the device at the root directory for this sample to function.

#include "stdafx.h"
#include "browse.h"

// forward defines (instead of using string tables)		
#define IDS_APP_TITLE			TEXT("Browse")
#define IDS_START_PAGE			TEXT("file://\\Program Files\\Browse\\start.html")
#define WM_LAUNCHBROWSER		(WM_USER + 1)

// Global Variables:
HINSTANCE			g_hInst;				// The current instance

// Forward declarations of functions 
ATOM MyRegisterClass(
	HINSTANCE,
	LPTSTR
	);
BOOL InitInstance(
	HINSTANCE, 
	int
	);
LRESULT CALLBACK WndProc(
	HWND,
	UINT,
	WPARAM,
	LPARAM
	);


//
//  FUNCTION: WinMain()
//
//  PURPOSE: Entry point for the application and sets up the Msg loop
//
int WINAPI WinMain(	
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow
	)
{
	MSG msg;
	
	
	// Perform application initialization:
	if (FALSE == InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	// Main Msg loop:
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
ATOM MyRegisterClass(
	HINSTANCE hInstance, 
	LPTSTR szWindowClass
	)
{
	WNDCLASS	wc;
	
    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BROWSE));
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
BOOL InitInstance(
	HINSTANCE hInstance, 
	int nCmdShow
	)
{
	HWND hWnd = NULL;
	
	g_hInst = hInstance;		// Store instance handle in our global variable
	
	//If it is already running, then focus on the window
	hWnd = FindWindow(IDS_APP_TITLE, IDS_APP_TITLE);	
	if (NULL != hWnd) 
	{
		SetForegroundWindow (hWnd);
		return FALSE;
	} 
	
	MyRegisterClass(hInstance, IDS_APP_TITLE);
	
	RECT rect;
	GetClientRect(hWnd, &rect);
	
	// create a full-screen window for the browser control
	hWnd = CreateWindow(IDS_APP_TITLE, IDS_APP_TITLE, WS_VISIBLE,
		0,0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 
		NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{	
		return FALSE;
	}
	
	// Hide all the Shell parts and show the window in full screen mode.
	SHFullScreen(hWnd, SHFS_HIDETASKBAR | SHFS_HIDESTARTICON | SHFS_HIDESIPBUTTON);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_NOTIFY		 - Handle specific system notifications
//  WM_CREATE	     - This code runs when the app starts
//	WM_PAINT	     - Paint the main window
//  WM_DESTROY	     - post a quit Msg and return
//  WM_LAUNCHBROWSER - This code starts the browser control and loads a start page
//
//
LRESULT CALLBACK WndProc(
	HWND hWnd, 
	UINT Msg, 
	WPARAM wParam, 
	LPARAM lParam)
{
	WCHAR wszURL[1000];
    HWND hWndHtml;

	switch (Msg) 
	{
	case WM_NOTIFY:
        {
			NM_HTMLVIEW* pnmHTMLView = (NM_HTMLVIEW*)lParam;
			
            switch (pnmHTMLView->hdr.code)
            {
            // this code is processed when a user clicks on a hyperlink
			case NM_HOTSPOT:
                // read the target string
				mbstowcs(wszURL, (const char *)pnmHTMLView->szTarget, 1000);
				
				// if the link is just "exit", then exit
				if(wcscmp(wszURL, L"exit") == 0)
				{
					PostMessage(hWnd, WM_CLOSE, NULL, NULL);
                    // Returning TRUE indicates that we have handled the Msg
                    // and the control will not do its default processing.
                    return TRUE;
				}
				break;
			}			
		}
        // Returning FALSE indicates to the html control that it should do
        // the default processing.
		return FALSE;
		
	case WM_CREATE:
		// launch the browser control on startup
		PostMessage(hWnd, WM_LAUNCHBROWSER, NULL, NULL);						
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	case WM_LAUNCHBROWSER:
		
		// the only function call required to create a browser control instance
		if (TRUE == InitHTMLControl(g_hInst))
		{
			// create the window for the control
			hWndHtml = CreateWindow(TEXT("DISPLAYCLASS"), NULL, WS_VISIBLE, 0, 0, 
				GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 
				hWnd, NULL, g_hInst, NULL);
			ShowWindow(hWndHtml, SW_SHOW);
			UpdateWindow(hWndHtml);
			
			// load the start page into the browser window
			SendMessage(hWndHtml, DTM_NAVIGATE, 0, (LPARAM)(LPTSTR)IDS_START_PAGE);					
		}
		else
		{
			MessageBox(hWnd, TEXT("Unable to Launch Browser"), TEXT("Browser Control Problem:") , NULL);
			DestroyWindow(hWnd);
		}
		break;
		
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}
