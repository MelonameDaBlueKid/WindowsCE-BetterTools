/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

****************************************************************************/
//
// functions in init.cpp
//
BOOL CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND AreWeRunning(PCTSTR szClassName);
BOOL InitInstance (int CmdShow, LPTSTR szWindowName, LPTSTR szClassName);
ATOM MyRegisterClass(LPTSTR szClassName);

//
// globals in init.cpp
//
extern 	HINSTANCE 		g_hinst;
extern	HWND			g_hwnd;
extern	HWND			g_hwndCB;
extern	BOOL			g_bHibernated;

//
// definitions
//
#define ID_APPBUTTON 0x1234

