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

bcoemglobal.h

Abstract:

This file defines mappings from the pre Win CE 6.0 OEM Global variables to the Win CE 6.0
fields.

Note! these mappings are only provided to assist in the porting of BSPs to Win CE 6.0, and
      are subject to be removed in a future release. It is recommended that all code using
      this data structure be modified to use the new convension.


--*/

#ifndef _BC_OEM_GLOBAL_H_
#define _BC_OEM_GLOBAL_H_

#define pfnOEMRefreshWatchDog               g_pOemGlobal->pfnRefreshWatchDog
#define dwOEMWatchDogPeriod                 g_pOemGlobal->dwWatchDogPeriod
#define dwdwNKWatchDogThreadPriority        g_pOemGlobal->dwWatchDogThreadPriority
#define dwNKWatchDogThreadPriority          g_pOemGlobal->dwWatchDogThreadPriority
#define pNotifyForceCleanboot               g_pOemGlobal->pfnNotifyForceCleanBoot
#define dwNKAlarmResolutionMSec             g_pOemGlobal->dwAlarmResolution
#define pQueryPerformanceFrequency          g_pOemGlobal->pfnQueryPerfFreq
#define pQueryPerformanceCounter            g_pOemGlobal->pfnQueryPerfCounter
#define pOEMUpdateRescheduleTime            g_pOemGlobal->pfnUpdateReschedTime
#define pOEMIsProcessorFeaturePresent       g_pOemGlobal->pfnIsProcessorFeaturePresent

#define dwNKDrWatsonSize                    g_pOemGlobal->cbErrReportSize
#define pKDIoControl                        g_pOemGlobal->pfnKDIoctl
#define OEMRomChain                         g_pOemGlobal->pROMChain

#define MainMemoryEndAddress                g_pOemGlobal->dwMainMemoryEndAddress

#define pfnOEMSetMemoryAttributes           g_pOemGlobal->pfnSetMemoryAttributes

#endif  // _BC_OEM_GLOBAL_H_
