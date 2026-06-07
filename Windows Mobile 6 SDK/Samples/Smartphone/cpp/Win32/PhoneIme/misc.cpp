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
#include <windows.h>
#include "misc.h"

BOOL SupportIntlPlus(void)
{
    return TRUE;
}


BOOL UseBoldFont(void)
{
    return TRUE;
}


HWND 
CreateFullScreenWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, 
                   HWND hWndParent, HMENU hMenu, HANDLE hInstance, LPVOID lpParam)
{
    RECT rc;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

    return CreateWindow(lpClassName, lpWindowName, dwStyle, 
                        rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 
                        hWndParent, hMenu, (HINSTANCE)hInstance, lpParam);
}