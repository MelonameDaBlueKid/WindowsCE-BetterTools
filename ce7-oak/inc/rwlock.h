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

    rwlock.h

Abstract:

    The main header for reader writer lock

Notes:

--*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define RWL_XBIT    0x80000000  // exclusive access
#define RWL_WBIT    0x40000000  // wait bit - indicate someone is waiting on this lock

#define RWL_CNTMAX  0x3fffffff

typedef enum _FAST_LOCK_MODE {
    //
    // FAST_LOCK_MODE_SHARED represents shared, or read-only, access
    // to all of the resources covered by the lock, as well as those
    // covered by the lock's descendant locks.
    //
    FAST_LOCK_MODE_SHARED                  = 0,

    //
    // FAST_LOCK_MODE_UPDATE represents shared, or read-only, access
    // to all of the resources covered by the lock, as well as those
    // covered by the lock's descendant locks, with a desire to
    // potentially atomically convert the lock to the exclusive, or
    // read-write, access mode.
    //
    FAST_LOCK_MODE_UPDATE                  = 1,

    //
    // FAST_LOCK_MODE_EXCLUSIVE represents exclusive, or read-write,
    // access to all of the resources covered by the lock, as well as
    // those covered by the lock's descendant locks.
    //
    FAST_LOCK_MODE_EXCLUSIVE               = 2

} FAST_LOCK_MODE, *PFAST_LOCK_MODE, *LPFAST_LOCK_MODE;

typedef struct _FAST_LOCK {
    DWORD            dwLock;    // bit 31 - x
                                // bit 30 - w
                                // bit 29..0 - count
    CRITICAL_SECTION cs;
    HANDLE           hEvt;
} FAST_LOCK, *PFAST_LOCK, *LPFAST_LOCK;

BOOL WINAPI InitializeFastLock (LPFAST_LOCK lpFastLock);
BOOL WINAPI DeleteFastLock (LPFAST_LOCK lpFastLock);
BOOL WINAPI AcquireFastLock (LPFAST_LOCK lpFastLock, FAST_LOCK_MODE dwLockType);
BOOL WINAPI ReleaseFastLock (LPFAST_LOCK lpFastLock, FAST_LOCK_MODE dwLockType);
BOOL WINAPI BoostFastLock(IN OUT LPFAST_LOCK lpFastLock);

#ifdef __cplusplus
}
#endif

