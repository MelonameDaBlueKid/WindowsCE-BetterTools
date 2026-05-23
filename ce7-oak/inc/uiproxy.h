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

#ifndef _UIPROXY_H
#define _UIPROXY_H

#define UIPROXY_IOCTL_DISPLAY 1
#define UIPROXY_DRIVER_KEY L"uiproxy"
#define UIPROXY_DRIVER_PREFIX L"UIP1:"

typedef BOOL (*PFN_UIENTRYPOINT)
    (
    LPVOID lpInBuffer, 
    DWORD nInBufferSize, 
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    PDWORD pBytesReturned 
    );

typedef struct {
    DWORD ccbDllName;
    DWORD ccbFuncName;
    DWORD ccbDriverData;
    // DLL name (variable length, size ccbDllName)
    // func name (variable length, size ccbFuncName)
    // [some padding] to make 8 byte alignment for driver data
    // driver data (variable length, 8 bytes aligned, size ccbDriverData)
} DRIVERUIINFO, *PDRIVERUIINFO;

#define MAKEQUADALIGN(p) (((DWORD)(p) + 7) & ~0x7)
 
#endif
