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

#ifndef _UUIHID_H_
#define _UUIHID_H_

#include <windows.h>
#include <windev.h>

// Structure defining updateapp UI input
typedef struct _InitUUI
{
    // width of the screen
    DWORD dwWidth;
    // height of the screen
    DWORD dwHeight;
    // bit depth of the screen
    DWORD dwBitDepth;
    // orientation of the screen
    DWORD dwOrientation;
} InitUUI;

// Structure defining the data to be displayed on the screen
typedef struct _Blt
{
    // Rectange defining the data in pBuffer
    RECT rc;
    // Stride for display
    DWORD dwStride;
    // The raw bit info
    LPBYTE pBuffer;
} BltUUI;

#define UUI_FILE_HANDLE_NAME TEXT("UUI1:")

#define IOCTL_UUI_INIT CTL_CODE(FILE_DEVICE_ULDR, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_UUI_BLT_RECTANGLE CTL_CODE(FILE_DEVICE_ULDR, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_UUI_DEINIT CTL_CODE(FILE_DEVICE_ULDR, 3, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif


