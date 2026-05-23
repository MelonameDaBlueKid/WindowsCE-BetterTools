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

// CE's ExXxx Functions

#pragma once

#include <netwdm.h> // for PSLIST_HEADER, PSLIST_ENTRY

PSLIST_ENTRY
ExpInterlockedFlushSList (
    __inout PSLIST_HEADER ListHead);

PSLIST_ENTRY
ExpInterlockedPopEntrySList (
    __inout PSLIST_HEADER ListHead
    );

PSLIST_ENTRY
ExpInterlockedPushEntrySList (
    __inout PSLIST_HEADER ListHead,
    __inout PSLIST_ENTRY ListEntry
    );
    
    
__inline KPROCESSOR_MODE 
ExGetPreviousMode()
{
    return KernelMode;
}

///////////////////////////////////////////////////////////////////////////////
//  ExInterlockedPushEntrySList()
//
//  Routine Description:
//
//      Push a single SINGLE_LIST_ENTRY to the given SINGLE_LIST_HEADER with
//      lock taken.
//
//  Arguments:
//
//      pListHead   :: Points to SINGLE_LIST_HEADER structure to initialize.
//      pEntry      :: The SINGLE_LIST_ENTRY to be added.
//      pLock       :: Lock to take.
//
//  Return Value:
//
//      None.
//

_inline
VOID
ExInterlockedPushEntrySList(
    PSLIST_HEADER       pListHead,
    PSINGLE_LIST_ENTRY  pEntry,
    PKSPIN_LOCK         pLock)
{
    KeAcquireSpinLockAtDpcLevel(pLock);

    pEntry->Next         = pListHead->Next.Next;
    pListHead->Next.Next = pEntry;
    pListHead->Depth++;

    KeReleaseSpinLockFromDpcLevel(pLock);

}   //  ExInterlockedPushEntryList()



///////////////////////////////////////////////////////////////////////////////
//  ExInterlockedPopEntrySList()
//
//  Routine Description:
//
//      Extract a single SINGLE_LIST_ENTRY from a given SINGLE_LIST_HEADER with 
//      lock taken.
//
//  Arguments:
//
//      pListHead   :: Points to SINGLE_LIST_HEADER structure to initialize.
//      pLock       :: Lock to take.
//
//  Return Value:
//
//      SINGLE_LIST_ENTRY extracted.
//

_inline
PVOID
ExInterlockedPopEntrySList(
    PSLIST_HEADER   pListHead,
    PKSPIN_LOCK     pLock)
{
    PVOID   pvReturn;

    KeAcquireSpinLockAtDpcLevel(pLock);

    pvReturn = pListHead->Next.Next;
    
    if (pListHead->Next.Next)
    {
        pListHead->Next.Next = pListHead->Next.Next->Next;
        pListHead->Depth--;
    }

    KeReleaseSpinLockFromDpcLevel(pLock);
    
    return pvReturn;

}   //  ExInterlockedPopEntrySList()




//
//  Define executive resource data structures.
//

typedef CRITICAL_SECTION ERESOURCE, *PERESOURCE;

__inline NTSTATUS 
ExInitializeResourceLite(
    __out PERESOURCE pResource)
{
    InitializeCriticalSection(pResource);
    return STATUS_SUCCESS;
}

__inline NTSTATUS 
ExDeleteResourceLite(
    __inout PERESOURCE pResource)
{
    DeleteCriticalSection(pResource);
    return STATUS_SUCCESS;
}

__inline BOOLEAN
ExAcquireResourceExclusiveLite (
    __inout PERESOURCE pResource,
    __in BOOLEAN Wait)
//
//  The ExAcquireResourceExclusiveLite routine acquires the given resource for exclusive access by the calling thread.
//
//  ExAcquireResourceExclusiveLite returns TRUE if the resource is acquired. 
//  This routine returns FALSE if the input Wait is FALSE and exclusive access cannot be granted immediately.
//
{
    BOOLEAN ResourceAcquired;
    
    if (Wait)
    {
        EnterCriticalSection(pResource);
        ResourceAcquired = TRUE;
    }
    else
    {
#ifdef UNDER_CE
        ResourceAcquired = TryEnterCriticalSection(pResource) ? TRUE : FALSE;
#else
        ResourceAcquired = TryEnterCriticalSection(pResource);
#endif
    }
    
    return ResourceAcquired;
}

__inline BOOLEAN
ExAcquireResourceSharedLite (
    __inout PERESOURCE pResource,
    __in BOOLEAN Wait)
//
//  The ExAcquireResourceSharedLite routine acquires the given resource for shared access by the calling thread.
//
{
    // For simplification on CE, we just use exclusive access all the time.
    
    return ExAcquireResourceExclusiveLite(pResource, Wait);
}

__inline VOID
ExReleaseResourceLite(
    __inout PERESOURCE pResource
    )
{
    LeaveCriticalSection(pResource);
}

#define ExInitializeResource        ExInitializeResourceLite
#define ExDeleteResource            ExDeleteResourceLite
#define	ExAcquireResourceExclusive	ExAcquireResourceExclusiveLite
#define	ExAcquireResourceShared  	ExAcquireResourceSharedLite
#define	ExReleaseResource           ExReleaseResourceLite

//
//  ExCallback support
//

#ifndef UNDER_CE
#include <lpc.h> // For POBJECT_ATTRIBUTES
#endif

typedef VOID (*PCALLBACK_FUNCTION ) (
    __in_opt PVOID CallbackContext,
    __in_opt PVOID Argument1,
    __in_opt PVOID Argument2
    );

#ifndef UNDER_CE
VOID
ExNotifyCallback (
    __in PVOID CallbackObject,
    __in_opt PVOID Argument1,
    __in_opt PVOID Argument2
    );

NTSTATUS
ExCreateCallback (
    __deref_out PCALLBACK_OBJECT *CallbackObject,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in BOOLEAN Create,
    __in BOOLEAN AllowMultipleCallbacks
    );
#endif

typedef GUID UUID;

#ifdef UNDER_CE
NTSTATUS 
#else
NTSTATUS RPC_ENTRY
#endif
ExUuidCreate (
    OUT UUID  * Uuid
    );

