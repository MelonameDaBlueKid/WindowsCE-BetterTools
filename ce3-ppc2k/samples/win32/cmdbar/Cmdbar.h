/*****************************************************************************

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
 ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 PARTICULAR PURPOSE.

 Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

 MODULE:   cmdbar.h

 PURPOSE: Header file for "cmdbar" Windows CE sample application.



 COMMENTS: N/A
*****************************************************************************/

#ifndef __CMDBAR_H__

/////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"    


BOOL InitApplication(HINSTANCE hInstance);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LRESULT CALLBACK  WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

/////////////////////////////////////////////////////////////////////////////
    
#endif /* __CMDBAR_H__ */
