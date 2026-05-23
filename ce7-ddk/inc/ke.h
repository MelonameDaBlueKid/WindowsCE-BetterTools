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


// CE's KeXxx Functions

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <netwdm.h>

#define KeBugCheck(a) ASSERT(0);

typedef CCHAR KPROCESSOR_MODE;

// from usermode.h

__inline
LARGE_INTEGER
KeQueryPerformanceCounter(
    OUT PLARGE_INTEGER PerformanceFrequency  OPTIONAL
    )
{
    LARGE_INTEGER Time = {0};

    if (PerformanceFrequency)
        QueryPerformanceFrequency(PerformanceFrequency);

    QueryPerformanceCounter(&Time);
        
    return Time;
}

typedef struct _KDPC KDPC, *PKDPC, *PRKDPC;

__inline
VOID
KeSetTargetProcessorDpc (
    IN PRKDPC Dpc,
    IN CCHAR Number
    )
{
    //
    // Do not have to do anything really.
    //

    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(Number);
}

VOID
KeInitializeDpc(
    PKDPC                   pKDpc,
    PKDEFERRED_ROUTINE      DeferredRoutine, // pointer to the CustomDpc routine
    PVOID                   DeferredContext); // value to pass as DeferredContext parameter to CustomDpc


typedef HANDLE KEVENT, *PKEVENT, *PRKEVENT;
typedef uint    EVENT_TYPE;
typedef LONG    KPRIORITY;

enum {
    NotificationEvent = 0,
    SynchronizationEvent = 1,
};

__inline void 
KeInitializeEvent(
    IN PRKEVENT     phEvent,
    IN EVENT_TYPE   Type,
    IN BOOLEAN      State)
{
    *phEvent = CreateEvent(NULL, (Type == SynchronizationEvent)? FALSE:TRUE, State, NULL);
    ASSERT(phEvent);
}

__inline LONG 
KeSetEvent(
    IN PRKEVENT     phEvent,
    IN KPRIORITY    Increment,
    IN BOOLEAN      Wait)
{
#ifndef DEBUG
    UNREFERENCED_PARAMETER(Increment);
    UNREFERENCED_PARAMETER(Wait);
#endif
    ASSERT(0 == Increment);
    ASSERT(FALSE == Wait);
    return SetEvent(*phEvent);
}


__inline LONG KeResetEvent(
    IN PRKEVENT  phEvent)
{
    return ResetEvent(*phEvent);

}

__inline NTSTATUS
KeDelayExecutionThread (
    IN KPROCESSOR_MODE WaitMode,
    IN BOOLEAN Alertable,
    IN PLARGE_INTEGER IntervalInHundredsOfNanoseconds
    )
//
//  The KeDelayExecutionThread routine puts the current thread into an alertable
//  or nonalertable wait state for a given interval.
//
//  Interval - Specifies the absolute or relative time, in units of 100 nanoseconds,
//             for which the wait is to occur. A negative value indicates relative time. 
//             Absolute expiration times track any changes in system time;
//             relative expiration times are not affected by system time changes.
{
    UNREFERENCED_PARAMETER(WaitMode);
#ifndef DEBUG
    UNREFERENCED_PARAMETER(Alertable);
#endif
    ASSERT(FALSE == Alertable);
    
    // Relative sleep times are specified with the negative of the interval time.
    // We don't support absolute times, just discard the sign bit.
    if (IntervalInHundredsOfNanoseconds->QuadPart < 0)
        IntervalInHundredsOfNanoseconds->QuadPart = -IntervalInHundredsOfNanoseconds->QuadPart;

    // Sleep takes a time in milliseconds
    Sleep((DWORD)(IntervalInHundredsOfNanoseconds->QuadPart / 10000) + 1);
    
    return STATUS_SUCCESS;
}

//
//  The KeFlushQueuedDpcs routine returns after all queued DPCs on all
//  processors have executed.
//
VOID
KeFlushQueuedDpcs();

typedef HANDLE KMUTEX, *PKMUTEX, *PRKMUTEX;

__inline VOID 
KeInitializeMutex(
    OUT KMUTEX   *Mutex,
    IN  ULONG     Level)
//
//  The KeInitializeMutex routine initializes a mutex object at a given level number,
//  setting it to a signaled state.
//
{
    UNREFERENCED_PARAMETER(Level);
    
    *Mutex = CreateMutex(NULL, FALSE, NULL);
    if (NULL == *Mutex)
    {
        KdPrint(("CreateMutex failed: %d\n", GetLastError())); 
        ASSERT(FALSE);
    }
}

__inline LONG 
KeUninitializeMutex(
    IN OUT KMUTEX *Mutex)
//
//  Free the resources allocated by KeInitializeMutex
//
{
    return !CloseHandle(*Mutex);
}

__inline LONG 
KeReleaseMutex(
    IN OUT KMUTEX *Mutex, 
    IN     BOOLEAN Wait)
//
//  The KeReleaseMutex routine releases a given mutex object,
//  specifying whether the caller is to call one of the KeWaitXxx functions as soon as KeReleaseMutex returns control.
//
//  Returns 0 if successful (the mutex object was released and attained a state of signaled).
//
{
    UNREFERENCED_PARAMETER(Wait);

    if (ReleaseMutex(*Mutex) == 0) {
        KdPrint(("ReleaseMutex failed: %d\n", GetLastError()));
        ASSERT(FALSE);
        return 1;
    }
    return 0;
}

typedef enum _KWAIT_REASON {
    Executive,
    UserRequest        
} KWAIT_REASON;

__inline NTSTATUS
KeWaitForSingleObject( 
    IN PVOID           Object,
    IN KWAIT_REASON    WaitReason,
    IN KPROCESSOR_MODE WaitMode,
    IN BOOLEAN         Alertable,
    IN PLARGE_INTEGER  Timeout OPTIONAL)
{
    HANDLE   Handle = *(PHANDLE)Object;
    DWORD    TimeoutMs = INFINITE;
    NTSTATUS Status = STATUS_SUCCESS;
    
    UNREFERENCED_PARAMETER(WaitReason);
    UNREFERENCED_PARAMETER(WaitMode);
    UNREFERENCED_PARAMETER(Alertable);

    if (NULL != Timeout)
    {        
        if (Timeout->QuadPart <= 0) {
            // relative time (convert to msec)
            TimeoutMs = (DWORD)((1-Timeout->QuadPart) / 10000);

        } else {
            // absolute time (calculate the delta from current system time)
            FILETIME ftNow;
            LARGE_INTEGER llftNow;
            GetCurrentFT (&ftNow);
            llftNow = *((PLARGE_INTEGER)&ftNow);

            if (Timeout->QuadPart <= llftNow.QuadPart) {
                TimeoutMs = 0; // time in past, expire immediately
            } else {
                TimeoutMs = (DWORD)((Timeout->QuadPart - llftNow.QuadPart) / 10000);
            }
        }
    }
    
    Status = WaitForSingleObject(Handle, TimeoutMs);
    // the WAIT_xxx codes are the same as the STATUS_xxx codes, no need to map them
    
    return Status;
    
}

__inline NTSTATUS   
KeWaitForMutexObject(    
    IN PRKMUTEX         Mutex,    
    IN KWAIT_REASON     WaitReason,    
    IN KPROCESSOR_MODE  WaitMode,    
    IN BOOLEAN          Alertable,    
    IN PLARGE_INTEGER   Timeout  OPTIONAL    )
{
    return KeWaitForSingleObject(Mutex, WaitReason, WaitMode, Alertable, Timeout);
}

//
// Semaphore object
//
typedef KMUTEX  KSEMAPHORE, *PKSEMAPHORE, *PRKSEMAPHORE;

__inline VOID
KeInitializeSemaphore(
    IN OUT PRKSEMAPHORE  pSemaphore,    
    IN LONG  Count,    
    IN LONG  Limit)
{
    UNREFERENCED_PARAMETER(Count);
#ifndef DEBUG
    UNREFERENCED_PARAMETER(Limit);
#endif
    // Only support binary semaphores, not counting semaphores
    ASSERT(1 == Limit);
    
    KeInitializeMutex(pSemaphore, 0);
}

__inline LONG 
KeUninitializeSemaphore(
    IN OUT PRKSEMAPHORE  pSemaphore)
{
    return KeUninitializeMutex(pSemaphore);
} 

__inline LONG   
KeReleaseSemaphore(    
    IN PRKSEMAPHORE  pSemaphore,    
    IN KPRIORITY     Increment,    
    IN LONG          Adjustment,    
    IN BOOLEAN  Wait    )
{
    UNREFERENCED_PARAMETER(Increment);
    UNREFERENCED_PARAMETER(Wait);
#ifndef DEBUG
    UNREFERENCED_PARAMETER(Adjustment);
#endif
    // Only support binary semaphores, not counting semaphores
    ASSERT(1 == Adjustment);

    return KeReleaseMutex(pSemaphore, FALSE);
}

__inline VOID   
KeEnterCriticalRegion()
//
//  The KeEnterCriticalRegion routine temporarily disables the delivery of normal kernel APCs;
//  special kernel-mode APCs are still delivered.
//
{
    // Should be a no-op for CE as there are no APCs.
}

__inline VOID   
KeLeaveCriticalRegion()
//
//  The KeLeaveCriticalRegion routine reenables the delivery of normal kernel-mode APCs that
//  were disabled by a preceding call to KeEnterCriticalRegion.
//
{
    // Should be a no-op for CE as there are no APCs.
}


__inline ULONGLONG  
KeQueryInterruptTime()
//
//  The KeQueryInterruptTime routine returns the current value of the system interrupt-time count. 
//
//  Returns the current interrupt-time count in 100-nanosecond units.
//
{
    // This routine must be fast and efficient, so we use GetTickCount() which
    // meets that criteria, but loses on accuracy.
    
    return (ULONGLONG)GetTickCount() * 10000;
}

// Most timer functions are implemented by ntcompat.h

__inline VOID
KeInitializeTimerEx(
    IN PKTIMER     Timer,
    IN TIMER_TYPE  Type)
{
    UNREFERENCED_PARAMETER(Type);

    CeKeInitializeTimer(Timer);
}

__inline BOOLEAN
KeIsExecutingDpc()
{
    return FALSE;
}


//  cf. \sdpublic\ddk\inc\ntddk.h
NTKERNELAPI
ULONG
KeQueryActiveProcessorCount (
    __out_opt PKAFFINITY ActiveProcessors
    );


//  cf. \sdpublic\ddk\inc\ntddk.h
NTKERNELAPI
ULONG
KeQueryMaximumProcessorCount (
    VOID
    );


#ifdef __cplusplus
}
#endif

