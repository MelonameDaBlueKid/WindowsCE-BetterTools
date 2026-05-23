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
#pragma once

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TCHLOG_LEVEL_DEBUG   0
#define TCHLOG_LEVEL_INFO    1
#define TCHLOG_LEVEL_WARNING 2
#define TCHLOG_LEVEL_ERROR   3
#define TCHLOG_LEVEL_FATAL   4

void TchLog_Init();
void TchLog_Deinit();
void TchLog_DoLog(DWORD dwLevel, LPCTSTR szMessage, ...);

#define TCHLOG_NOOP __noop

#define TCHLOG_ENABLE

#ifdef TCHLOG_ENABLE
#define TCHLOG_INIT TchLog_Init
#define TCHLOG_DEINIT TchLog_Deinit
#define TCHLOG TchLog_DoLog
#else // if !defined(TCHLOG_ENABLE)
#define TCHLOG_INIT TCHLOG_NOOP
#define TCHLOG_DEINIT TCHLOG_NOOP
#define TCHLOG TCHLOG_NOOP
#endif

#ifdef __cplusplus
}
#endif