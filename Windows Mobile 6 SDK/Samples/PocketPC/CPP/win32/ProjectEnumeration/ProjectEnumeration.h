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
/*****************************************************************************


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
