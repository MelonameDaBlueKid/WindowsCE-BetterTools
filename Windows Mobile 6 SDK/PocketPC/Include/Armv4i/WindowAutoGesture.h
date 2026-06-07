//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft
// premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license
// agreement, you are not authorized to use this source code.
// For the terms of the license, please see the license agreement
// signed by you and Microsoft.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//

#ifndef _WINDOWAUTOGESTURE_H_
#define _WINDOWAUTOGESTURE_H_

#if (_MSC_VER >= 1000)
#pragma once
#endif

#include <windows.h>

#ifdef __cplusplus
extern "C"  {
#endif

//
//  WindowAutoGesture
//

// General flags
#define WAGIF_OWNERANIMATE                  0x0001
#define WAGIF_VSCROLLABLE                   0x0002
#define WAGIF_HSCROLLABLE                   0x0004
#define WAGIF_LOCKAXES                      0x0008
#define WAGIF_IGNOREPAN                     0x0010
#define WAGIF_IGNORESCROLL                  0x0020

// Used for validation
#define WAGIF_LASTFLAG                      WAGIF_IGNORESCROLL

// Auto gestures animation types
// Only one auto scroll animation is available now
#define AMI_ANIMATION_SCROLL                0

// Status messages
#define WAG_STATUS_ANIMATION_START          0
#define WAG_STATUS_ANIMATION_END            1
#define WAG_STATUS_ANIMATION_CHANGE         2

// Status extra info
#define WAG_STATUS_EXTRAINFO_FINISHED       0
#define WAG_STATUS_EXTRAINFO_CONTINUOUS     1         
#define WAG_STATUS_EXTRAINFO_DISCRETE       2
#define WAG_STATUS_EXTRAINFO_INTERRUPTED    3

//
//  WindowAutoGesture structures
//

typedef struct tagWAGI {
    size_t cbSize;
    DWORD dwFlags;
    UINT nOwnerAnimateMessage;
    UINT nAnimateStatusMessage;
    HBRUSH hExtentBrush;
    UINT nItemHeight;
    UINT nItemWidth;
    BYTE bHorizontalExtent;
    BYTE bVerticalExtent;
} WAGINFO, *LPWAGINFO;

typedef struct tagANIMATEMESSAGEINFO {
    size_t cbSize;
    DWORD dwAnimationID;
    int nVPixelPosition;
    int nHPixelPosition;
} ANIMATEMESSAGEINFO, *LPANIMATEMESSAGEINFO;

typedef const WAGINFO *   LPCWAGINFO;
typedef const ANIMATEMESSAGEINFO * LPCANIMATEMESSAGEINFO;

//
//  APIs
//
WINUSERAPI
BOOL 
WINAPI 
TKGetWindowAutoGesture(
    __in HWND hWnd, 
    __out LPWAGINFO lpAutoGestureInfo
    );

WINUSERAPI
BOOL 
WINAPI 
TKSetWindowAutoGesture(
    __in HWND hWnd, 
    __in LPCWAGINFO lpAutoGestureInfo);

WINUSERAPI
BOOL
WINAPI 
TKGetAnimateMessageInfo(
    __in HWND hWnd, 
    __in WPARAM wParam, 
    __in LPARAM lParam, 
    __out LPANIMATEMESSAGEINFO pAnimateMessageInfo
    );

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _WINDOWAUTOGESTURE_H_ */
