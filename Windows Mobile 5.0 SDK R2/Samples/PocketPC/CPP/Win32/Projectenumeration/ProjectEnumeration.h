//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
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
