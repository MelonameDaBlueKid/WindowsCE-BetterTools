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
#ifndef _UPDATEAPPUI_H_
#define _UPDATEAPPUI_H_

#include <windows.h>

BOOL InitDisplay(DWORD dwWidth, DWORD dwHeight, DWORD dwBitDepth, DWORD dwOrientation);
BOOL DeinitDisplay();
BOOL BltRect(RECT rc, DWORD dwStride, LPVOID pBuffer);

#define INIT_DISPLAY TEXT("InitDisplay")
#define DEINIT_DISPLAY TEXT("DeinitDisplay")
#define BLTRECT TEXT("BltRect")

// Function pointers to exports from Display DLL
//
typedef BOOL (*PFN_INITDISPLAY)(DWORD dwWidth, DWORD dwHeight, DWORD dwBitDepth, DWORD dwOrientation);
typedef BOOL (*PFN_DEINITDISPLAY)();
typedef BOOL (*PFN_BLTRECT)(RECT rc, DWORD dwStride, LPVOID pBuffer);


#endif //#define _UPDATEAPPUI_H_

