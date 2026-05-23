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

rai.h

Abstract:  

Notes: 


--*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//
// Flags for App Registration functions
//

#define RAI_CLASS               0x01
#define RAI_EXE                 0x02
#define RAI_PERF                0x04
#define RAI_FLAGS               0x08
#define RAI_SESSION             0x10
#define RAI_ALL                 0x1F


//
// Perf hint flags
//

#define RAI_PERF_BIGMEM         0x01
#define RAI_PERF_QUICKIE        0x02

//
// App Type Flags
//
// If this flag is set, don't TerminateProcess
// if the app fails to respond to WM_CLOSE
#define RAI_DONT_TERMINATE 0x80000000



//
// App Registration structure
//

typedef struct {
    DWORD  dwInfo;
    LPTSTR ptszWindowClassName;
    LPTSTR ptszExe;
    DWORD  dwPerfHint;
    DWORD  dwAppTypeFlags;
    BOOL   fNewSession;
} REGISTEREDAPPINFO;


//
// App Registration functions
//

BOOL GetRegisteredAppInfo( LPTSTR ptszApp, DWORD dwInfo, REGISTEREDAPPINFO *prai );
BOOL SetRegisteredAppInfo( LPTSTR ptszApp, DWORD dwInfo, REGISTEREDAPPINFO const *prai );
BOOL FreeRegisteredAppInfo( REGISTEREDAPPINFO *prai );

#ifdef __cplusplus
}
#endif

