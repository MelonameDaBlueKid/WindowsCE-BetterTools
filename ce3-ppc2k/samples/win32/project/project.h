/*****************************************************************************

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
 ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 PARTICULAR PURPOSE.

 Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

 MODULE:   project.h

 PURPOSE: Header file for "Project" Pocket PC sample application.

 COMMENTS: N/A
*****************************************************************************/

#ifndef _PROJECT_H_
#define _PROJECT_H_

/////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"	

#define ShowInfo(_wnd,_s) MessageBox(_wnd, _s, TEXT("Info"), MB_OK)

BOOL InitApplication(HINSTANCE hInstance);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LRESULT CALLBACK  WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

/////////////////////////////////////////////////////////////////////////////
	
#endif /* _PROJECT_H_ */
