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
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

touchgesture.h

Abstract:  

    Private entry points, defines and types for the Windows Mobile Gesture API.
    
Notes: 


--*/

#ifndef _TOUCHGESTURE_
#define _TOUCHGESTURE_

#ifdef __cplusplus
extern "C"
{
#endif

// Gesture server definitions
#define IOCTL_VERB_PROCESS_GESTURE          1

// Internal Gesture API flags
#define GF_SYNC             8              // Direct synchronous Gesture

typedef HRESULT (*PFN_SETTOUCHRECOGNIZERTIMER)(DWORD* pdwTimerId, DWORD dwElapse, TIMERPROC pfnTimerProc);
typedef HRESULT (*PFN_KILLTOUCHRECOGNIZERTIMER)(DWORD dwTimerId);

typedef struct tagTOUCHRECOGNIZERAPIINIT {
    PFN_SETTOUCHRECOGNIZERTIMER  pfnSetTimer;
    PFN_KILLTOUCHRECOGNIZERTIMER pfnKillTimer;
} TOUCHRECOGNIZERAPIINIT;

WINUSERAPI
BOOL
WINAPI
RegisterGesture(
   __in LPCWSTR pszName,
   __out PDWORD_PTR pdwID);

WINUSERAPI
BOOL
WINAPI
Gesture(
    __in HWND hwnd,
    __in const GESTUREINFO* pGestureInfo,
    __in_bcount_opt(pGestureInfo->cbExtraArguments) const BYTE* pExtraArguments);


WINUSERAPI
BOOL
WINAPI
GestureBeginSession(
    __inout GESTUREINFO* pGestureInfo);

WINUSERAPI
BOOL
WINAPI
GestureEndSession(
    __in const GESTUREINFO* pGestureInfo);


#define CEGESTUREINFO       GESTUREINFO
#define PCEGESTUREINFO      PGESTUREINFO

#ifdef __cplusplus
} // extern "C"
#endif

#endif  //  _TOUCHGESTURE_

