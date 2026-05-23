// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   init.c
//
//  PURPOSE:  Performs application and instance specific initialization.
//
//  FUNCTIONS:
//    InitApplication() - Initializes window data and registers window.
//
//  COMMENTS:
//

#include <windows.h>            // required for all Windows applications
#include <commctrl.h>
#include "globals.h"            // prototypes specific to this application
#include "resource.h"
#include "procthrd.h"

HINSTANCE hInst;                // current instance

extern TCHAR szAppName[];              // The name of this application
extern TCHAR szTitle[];               // The title bar text


//
//  FUNCTION: InitApplication(HINSTANCE, int)
//
//  PURPOSE: Initializes window data and registers window class.
//
//  PARAMETERS:
//    hInstance - The handle to the instance of this application that
//                is currently being executed.
//    nCmdShow  - Specifies how the main window is to be displayed.
//
//  RETURN VALUE:
//    TRUE  - Success
//    FALSE - Initialization failed
//
//  COMMENTS:
//
//    This function is called at application initialization time.  It
//    performs initialization tasks for the current application instance.
//    Unlike Win16, in Win32, each instance of an application must register
//    window classes.
//
//    In this function, we initialize a window class by filling out a data
//    structure of type WNDCLASS and calling the Windows RegisterClass()
//    function.  Then we create the main window and show it.
//
//

BOOL InitApplication(HINSTANCE hInstance, int nCmdShow)
{
  WNDCLASS wc;
  HWND     hwnd; // Main window handle.
  
  
  if (!InitToolhelp32())
  {
    MessageBox(NULL, 
      L"PViewCE requires toolhelp.dll\nPlease hit OK to exit.",
      szTitle,
      MB_OK);
    return FALSE;
  }
  
  
  // Save the instance handle in static variable, which will be used in
  // many subsequence calls from this application to Windows.
  
  hInst = hInstance; // Store instance handle in our global variable
  
  // Fill in window class structure with parameters that describe the
  // main window.
  
  wc.style         = CS_HREDRAW | CS_VREDRAW; // Class style(s).
  wc.lpfnWndProc   = (WNDPROC)WndProc;        // Window Procedure
  wc.cbClsExtra    = 0;                       // No per-class extra data.
  wc.cbWndExtra    = 0;                       // No per-window extra data.
  wc.hInstance     = hInstance;               // Owner of this class
  wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON)); // Icon name from .RC
  wc.hCursor       = 0; // Cursor
  wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName  = 0;               // Menu name from .RC
  wc.lpszClassName = szAppName;               // Name to register as
  
  // Register the window class and return FALSE if unsuccesful.
  
  if (!RegisterClass(&wc))
  {
    //Assume we are running on NT where RegisterClassEx() is
    //not implemented, so let's try calling RegisterClass().
    
    if (!RegisterClass((LPWNDCLASS)&wc.style))
      return FALSE;
  }
  
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
		
				
	hwnd = CreateWindow(szAppName, szTitle, WS_VISIBLE,
		x, y, cx, cy, NULL, NULL, hInstance, NULL);
  
  // If window could not be created, return "failure"
  if (!hwnd)
    return FALSE;
  
  // Make the window visible; update its client area; and return "success"
  ShowWindow(hwnd, nCmdShow);  // Show the window
  UpdateWindow(hwnd);          // Sends WM_PAINT message
  
#if _WIN32_WCE < 212//non-Rapier devices
  if (hwndCB)
    CommandBar_Show(hwndCB, TRUE);
#endif
  
  return TRUE;                 // We succeeded...
}



