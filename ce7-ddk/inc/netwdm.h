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

#include <ntcompat.h>

#define LOOKASIDE_ALIGN

//
// Define alignment macros to align structure sizes and pointers up and down.
//

#define ALIGN_DOWN(length, type) \
    ((ULONG)(length) & ~(sizeof(type) - 1))

#define ALIGN_UP(length, type) \
    (ALIGN_DOWN(((ULONG)(length) + sizeof(type) - 1), type))

#define ALIGN_DOWN_POINTER(address, type) \
    ((PVOID)((ULONG_PTR)(address) & ~((ULONG_PTR)sizeof(type) - 1)))

#define ALIGN_UP_POINTER(address, type) \
    (ALIGN_DOWN_POINTER(((ULONG_PTR)(address) + sizeof(type) - 1), type))

#ifdef UNDER_CE
typedef enum {
    UNSPECIFIED_COMPARTMENT_ID = 0,
    DEFAULT_COMPARTMENT_ID
} COMPARTMENT_ID, *PCOMPARTMENT_ID;
#endif

//
// Define types that are not exported.
//

typedef struct _ACCESS_STATE *PACCESS_STATE;
typedef struct _CALLBACK_OBJECT *PCALLBACK_OBJECT;
#if defined(_NTHAL_INCLUDED_)
typedef struct _KPROCESS *PEPROCESS;
typedef struct _ETHREAD *PETHREAD;
#elif defined(_NTIFS_INCLUDED_)
typedef struct _KPROCESS *PEPROCESS;
typedef struct _KTHREAD *PETHREAD;
#else
typedef struct _EPROCESS *PEPROCESS;
//typedef struct _ETHREAD *PETHREAD;
#endif
typedef struct _IO_TIMER *PIO_TIMER;
//typedef struct _KINTERRUPT *PKINTERRUPT;
typedef struct _KTHREAD *PKTHREAD, *PRKTHREAD;
typedef struct _OBJECT_TYPE *POBJECT_TYPE;
typedef struct _SECURITY_QUALITY_OF_SERVICE *PSECURITY_QUALITY_OF_SERVICE;


//
// Declare empty structure definitions so that they may be referenced by
// routines before they are defined
//
typedef struct _CONTEXT *PCONTEXT;
typedef struct _IO_STACK_LOCATION *PIO_STACK_LOCATION;
typedef struct _VPB *PVPB;
typedef struct _FILE_GET_QUOTA_INFORMATION *PFILE_GET_QUOTA_INFORMATION;

//
// Define I/O Driver error log packet structure.  This structure is filled in
// by the driver.
//

typedef struct _IO_ERROR_LOG_PACKET {
    UCHAR MajorFunctionCode;
    UCHAR RetryCount;
    USHORT DumpDataSize;
    USHORT NumberOfStrings;
    USHORT StringOffset;
    USHORT EventCategory;
    NTSTATUS ErrorCode;
    ULONG UniqueErrorValue;
    NTSTATUS FinalStatus;
    ULONG SequenceNumber;
    ULONG IoControlCode;
    LARGE_INTEGER DeviceOffset;
    ULONG DumpData[1];
}IO_ERROR_LOG_PACKET, *PIO_ERROR_LOG_PACKET;


//
// Define Mca POS data block for slot
//

typedef struct _CM_MCA_POS_DATA {
    USHORT AdapterId;
    UCHAR PosData1;
    UCHAR PosData2;
    UCHAR PosData3;
    UCHAR PosData4;
} CM_MCA_POS_DATA, *PCM_MCA_POS_DATA;

#pragma warning(push)
#pragma warning(disable:4214) 

//
// Memory configuration of eisa data block structure
//

typedef struct _EISA_MEMORY_TYPE {
    UCHAR ReadWrite: 1;
    UCHAR Cached : 1;
    UCHAR Reserved0 :1;
    UCHAR Type:2;
    UCHAR Shared:1;
    UCHAR Reserved1 :1;
    UCHAR MoreEntries : 1;
} EISA_MEMORY_TYPE, *PEISA_MEMORY_TYPE;

typedef struct _EISA_MEMORY_CONFIGURATION {
    EISA_MEMORY_TYPE ConfigurationByte;
    UCHAR DataSize;
    USHORT AddressLowWord;
    UCHAR AddressHighByte;
    USHORT MemorySize;
} EISA_MEMORY_CONFIGURATION, *PEISA_MEMORY_CONFIGURATION;


//
// Interrupt configurationn of eisa data block structure
//

typedef struct _EISA_IRQ_DESCRIPTOR {
    UCHAR Interrupt : 4;
    UCHAR Reserved :1;
    UCHAR LevelTriggered :1;
    UCHAR Shared : 1;
    UCHAR MoreEntries : 1;
} EISA_IRQ_DESCRIPTOR, *PEISA_IRQ_DESCRIPTOR;

typedef struct _EISA_IRQ_CONFIGURATION {
    EISA_IRQ_DESCRIPTOR ConfigurationByte;
    UCHAR Reserved;
} EISA_IRQ_CONFIGURATION, *PEISA_IRQ_CONFIGURATION;


//
// DMA description of eisa data block structure
//

typedef struct _DMA_CONFIGURATION_BYTE0 {
    UCHAR Channel : 3;
    UCHAR Reserved : 3;
    UCHAR Shared :1;
    UCHAR MoreEntries :1;
} DMA_CONFIGURATION_BYTE0;

typedef struct _DMA_CONFIGURATION_BYTE1 {
    UCHAR Reserved0 : 2;
    UCHAR TransferSize : 2;
    UCHAR Timing : 2;
    UCHAR Reserved1 : 2;
} DMA_CONFIGURATION_BYTE1;

typedef struct _EISA_DMA_CONFIGURATION {
    DMA_CONFIGURATION_BYTE0 ConfigurationByte0;
    DMA_CONFIGURATION_BYTE1 ConfigurationByte1;
} EISA_DMA_CONFIGURATION, *PEISA_DMA_CONFIGURATION;


//
// Port description of eisa data block structure
//

typedef struct _EISA_PORT_DESCRIPTOR {
    UCHAR NumberPorts : 5;
    UCHAR Reserved :1;
    UCHAR Shared :1;
    UCHAR MoreEntries : 1;
} EISA_PORT_DESCRIPTOR, *PEISA_PORT_DESCRIPTOR;

#pragma warning(pop)

typedef struct _EISA_PORT_CONFIGURATION {
    EISA_PORT_DESCRIPTOR Configuration;
    USHORT PortAddress;
} EISA_PORT_CONFIGURATION, *PEISA_PORT_CONFIGURATION;


//
// Eisa slot information definition
// N.B. This structure is different from the one defined
//      in ARC eisa addendum.
//

typedef struct _CM_EISA_SLOT_INFORMATION {
    UCHAR ReturnCode;
    UCHAR ReturnFlags;
    UCHAR MajorRevision;
    UCHAR MinorRevision;
    USHORT Checksum;
    UCHAR NumberFunctions;
    UCHAR FunctionInformation;
    ULONG CompressedId;
} CM_EISA_SLOT_INFORMATION, *PCM_EISA_SLOT_INFORMATION;


//
// Eisa function information definition
//

typedef struct _CM_EISA_FUNCTION_INFORMATION {
    ULONG CompressedId;
    UCHAR IdSlotFlags1;
    UCHAR IdSlotFlags2;
    UCHAR MinorRevision;
    UCHAR MajorRevision;
    UCHAR Selections[26];
    UCHAR FunctionFlags;
    UCHAR TypeString[80];
    EISA_MEMORY_CONFIGURATION EisaMemory[9];
    EISA_IRQ_CONFIGURATION EisaIrq[7];
    EISA_DMA_CONFIGURATION EisaDma[4];
    EISA_PORT_CONFIGURATION EisaPort[20];
    UCHAR InitializationData[60];
} CM_EISA_FUNCTION_INFORMATION, *PCM_EISA_FUNCTION_INFORMATION;

// line 4615
//
// ClientId
//
/* lpc.h already defines this!

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;
*/
typedef enum _POOL_TYPE POOL_TYPE;

typedef
PVOID
(*PALLOCATE_FUNCTION) (
    __in POOL_TYPE PoolType,
    __in SIZE_T NumberOfBytes,
    __in ULONG Tag
    );

typedef
VOID
(*PFREE_FUNCTION) (
    __in PVOID Buffer
    );

typedef struct _LOOKASIDE_LIST_EX *PLOOKASIDE_LIST_EX;

typedef
PVOID
(*PALLOCATE_FUNCTION_EX) (
    __in POOL_TYPE PoolType,
    __in SIZE_T NumberOfBytes,
    __in ULONG Tag,
    __inout PLOOKASIDE_LIST_EX Lookaside
    );

typedef
VOID
(*PFREE_FUNCTION_EX) (
    __in PVOID Buffer,
    __inout PLOOKASIDE_LIST_EX Lookaside
    );


#ifndef _SLIST_HEADER_
#define _SLIST_HEADER_


#define SLIST_ENTRY SINGLE_LIST_ENTRY
#define _SLIST_ENTRY _SINGLE_LIST_ENTRY
#define PSLIST_ENTRY PSINGLE_LIST_ENTRY


#pragma warning(push)
#pragma warning(disable:4201) 

typedef union _SLIST_HEADER {
    ULONGLONG Alignment;
    struct {
        SLIST_ENTRY Next;
        USHORT Depth;
        USHORT Sequence;
    };
} SLIST_HEADER, *PSLIST_HEADER;


#endif // _SLIST_HEADER_



//
// The goal here is to end up with two structure types that are identical except
// for the fact that one (GENERAL_LOOKASIDE) is cache aligned, and the other
// (GENERAL_LOOKASIDE_POOL) is merely naturally aligned.
//
// An anonymous structure element would do the trick except that C++ can't handle
// such complex syntax, so we're stuck with this macro technique.
// 

#define GENERAL_LOOKASIDE_LAYOUT                \
    union {                                     \
        SLIST_HEADER ListHead;                  \
        SINGLE_LIST_ENTRY SingleListHead;       \
    };                                          \
    USHORT Depth;                               \
    USHORT MaximumDepth;                        \
    ULONG TotalAllocates;                       \
    union {                                     \
        ULONG AllocateMisses;                   \
        ULONG AllocateHits;                     \
    };                                          \
                                                \
    ULONG TotalFrees;                           \
    union {                                     \
        ULONG FreeMisses;                       \
        ULONG FreeHits;                         \
    };                                          \
                                                \
    POOL_TYPE Type;                             \
    ULONG Tag;                                  \
    ULONG Size;                                 \
    union {                                     \
        PALLOCATE_FUNCTION_EX AllocateEx;       \
        PALLOCATE_FUNCTION Allocate;            \
    };                                          \
                                                \
    union {                                     \
        PFREE_FUNCTION_EX FreeEx;               \
        PFREE_FUNCTION Free;                    \
    };                                          \
                                                \
    LIST_ENTRY ListEntry;                       \
    ULONG LastTotalAllocates;                   \
    union {                                     \
        ULONG LastAllocateMisses;               \
        ULONG LastAllocateHits;                 \
    };                                          \
    ULONG Future[2];

//
// GENERAL_LOOKASIDE is a cache aligned type, typically shared between
// multiple processors
// 
/*
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4324) // structure was padded due to __declspec(align())
#endif
*/

typedef struct LOOKASIDE_ALIGN _GENERAL_LOOKASIDE {
    GENERAL_LOOKASIDE_LAYOUT
} GENERAL_LOOKASIDE, *PGENERAL_LOOKASIDE;


//
// GENERAL_LOOKASIDE_POOL is the same layout as GENERAL_LOOKASIDE but is
// not cacheblock aligned, for use in cases where access is limited to a
// single processor
// 

typedef struct _GENERAL_LOOKASIDE_POOL {
    GENERAL_LOOKASIDE_LAYOUT
} GENERAL_LOOKASIDE_POOL, *PGENERAL_LOOKASIDE_POOL;

#pragma warning(pop)

typedef struct _LOOKASIDE_LIST_EX {
    GENERAL_LOOKASIDE_POOL L;
} LOOKASIDE_LIST_EX, *PLOOKASIDE_LIST_EX;


PVOID
FORCEINLINE
ExAllocateFromLookasideListEx (
    __inout PLOOKASIDE_LIST_EX Lookaside
    )

/*++

Routine Description:

    This function removes (pops) the first entry from the specified
    lookaside list.

Arguments:

    Lookaside - Supplies a pointer to a LOOKASIDE_LIST_EX structure.

Return Value:

    If an entry is removed from the specified lookaside list, then the
    address of the entry is returned as the function value. Otherwise,
    NULL is returned.

--*/

{
    UNREFERENCED_PARAMETER(Lookaside);
    return NULL;
    
}

VOID
FORCEINLINE
ExFreeToLookasideListEx (
    __inout PLOOKASIDE_LIST_EX Lookaside,
    __in PVOID Entry
    )

/*++

Routine Description:

    This function inserts (pushes) the specified entry into the specified
    lookaside list.

Arguments:

    Lookaside - Supplies a pointer to a LOOKASIDE_LIST_EX structure.

    Entry - Supples a pointer to the entry that is inserted in the
        lookaside list.

Return Value:

    None.

--*/

{
    UNREFERENCED_PARAMETER(Lookaside);
    UNREFERENCED_PARAMETER(Entry);
    return;
}


//
// _EX_POOL_PRIORITY_ provides a method for the system to handle requests
// intelligently in low resource conditions.
//
// LowPoolPriority should be used when it is acceptable to the driver for the
// mapping request to fail if the system is low on resources.  An example of
// this could be for a non-critical network connection where the driver can
// handle the failure case when system resources are close to being depleted.
//
// NormalPoolPriority should be used when it is acceptable to the driver for the
// mapping request to fail if the system is very low on resources.  An example
// of this could be for a non-critical local filesystem request.
//
// HighPoolPriority should be used when it is unacceptable to the driver for the
// mapping request to fail unless the system is completely out of resources.
// An example of this would be the paging file path in a driver.
//
// SpecialPool can be specified to bound the allocation at a page end (or
// beginning).  This should only be done on systems being debugged as the
// memory cost is expensive.
//
// N.B.  These values are very carefully chosen so that the pool allocation
//       code can quickly crack the priority request.
//

typedef enum _EX_POOL_PRIORITY {
    LowPoolPriority,
    LowPoolPrioritySpecialPoolOverrun = 8,
    LowPoolPrioritySpecialPoolUnderrun = 9,
    NormalPoolPriority = 16,
    NormalPoolPrioritySpecialPoolOverrun = 24,
    NormalPoolPrioritySpecialPoolUnderrun = 25,
    HighPoolPriority = 32,
    HighPoolPrioritySpecialPoolOverrun = 40,
    HighPoolPrioritySpecialPoolUnderrun = 41

    } EX_POOL_PRIORITY;


//
// Interrupt modes.
//
/*
typedef enum _KINTERRUPT_MODE {
    LevelSensitive,
    Latched
} KINTERRUPT_MODE;
*/

//  wdm.h
typedef ULONG_PTR KAFFINITY;
typedef KAFFINITY *PKAFFINITY;

typedef enum _KINTERRUPT_POLARITY {
    InterruptPolarityUnknown,
    InterruptActiveHigh,
    InterruptActiveLow
} KINTERRUPT_POLARITY, *PKINTERRUPT_POLARITY;



//
// Interrupt message information table entry definition
//

typedef struct _IO_INTERRUPT_MESSAGE_INFO_ENTRY {

    //
    // Message address - indicates the address the device should use to
    // generate this message signaled interrupt.
    //

    PHYSICAL_ADDRESS MessageAddress;

    //
    // Target processor set - indicates the set of processors that this
    // message in allowed to interrupt.
    //

    KAFFINITY TargetProcessorSet;

    //
    // Interrupt object - holds a pointer to the interrupt object associated
    // with this interrupt message.  This structure is opaque to drivers.
    //

    PKINTERRUPT InterruptObject;

    //
    // Message data - supplies the value that the device should write to the
    // message address in order to generate this interrupt message.
    //

    ULONG MessageData;

    //
    // The remaining fields indicate the system interrupt vector, IRQL,
    // trigger mode, and interrupt polarity associated with this interrupt
    // message.  These first three values are suitable for use in a fully
    // specified connection parameter structure in a call to
    // IoConnectInterruptEx.
    //

    ULONG Vector;
    KIRQL Irql;
    KINTERRUPT_MODE Mode;
    KINTERRUPT_POLARITY Polarity;

} IO_INTERRUPT_MESSAGE_INFO_ENTRY, *PIO_INTERRUPT_MESSAGE_INFO_ENTRY;

//
// Interrupt message information table definition
//

typedef struct _IO_INTERRUPT_MESSAGE_INFO {

    //
    // Unified IRQL - indicates the IRQL that will be used when calling a
    // message service routine associated with any of the interrupt messages
    // in this table.  Such a unified IRQL will only exist in cases where 1) a
    // driver provides a spinlock to IoConnectInterruptEx with the intent of
    // serializing delivery of all of the messages listed in this table or 2)
    // the driver provides a synchronization IRQL, and no spinlock, with the
    // intent of blocking any message service routine associated with this
    // table from directly preempting another one.  If neither of these cases
    // applies, then the different messages in this table are allowed to be
    // delivered in parallel and at different IRQLs.  In this case this field
    // will be set to zero.
    //

    KIRQL UnifiedIrql;

    //
    // Message count - indicates the number of entries contained in this
    // message information table.
    //

    ULONG MessageCount;

    //
    // Message info - lies at the start of a variable size array of
    // information table entries, with the size of the array dictated by the
    // message count associated with this table.  Each entry describes a
    // different interrupt message that has been allocated to this device.
    //

    IO_INTERRUPT_MESSAGE_INFO_ENTRY MessageInfo[1];

} IO_INTERRUPT_MESSAGE_INFO, *PIO_INTERRUPT_MESSAGE_INFO;

typedef enum _WORK_QUEUE_TYPE {
    CriticalWorkQueue,
    DelayedWorkQueue,
    HyperCriticalWorkQueue,
    MaximumWorkQueue
} WORK_QUEUE_TYPE;

NTKERNELAPI
SIZE_T
MmSizeOfMdl (
    __in_bcount_opt (Length) PVOID Base,
    __in SIZE_T Length
    );

#include <io.h>


LARGE_INTEGER
KeQueryPerformanceCounter (
   __out_opt PLARGE_INTEGER PerformanceFrequency
   );


//
// Since the following function will be compiled inline for user code, the
// initialization changes for IA64 will only take effect if the user code
// is recompiled with this new header. For those binaries that are recompiled
// with this new code, it will not have to go through an extra step of header
// initialization on its first push or pop operation. Note that the SLIST code
// will still work perfectly even without the changes in this initialization
// function.
//

__inline
VOID
InitializeSListHead (
    __out PSLIST_HEADER SListHead
    )

{

    //
    // Slist headers must be 16 byte aligned.
    //

    RtlZeroMemory(SListHead, sizeof(SLIST_HEADER));

    return;
}

#define ExInitializeSListHead InitializeSListHead

#define InterlockedPopEntrySList(Head) \
    ExpInterlockedPopEntrySList(Head)

#define InterlockedPushEntrySList(Head, Entry) \
    ExpInterlockedPushEntrySList(Head, Entry)

#define InterlockedFlushSList(Head) \
    ExpInterlockedFlushSList(Head)

#define QueryDepthSList(Head) \
    ExQueryDepthSList(Head)

#define ExQueryDepthSList(_listhead_) (_listhead_)->Depth

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedPopEntrySList (
    __inout PSLIST_HEADER ListHead
    );

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedPushEntrySList (
    __inout PSLIST_HEADER ListHead,
    __inout PSLIST_ENTRY ListEntry
    );

typedef enum _MEMORY_CACHING_TYPE_ORIG {
    MmFrameBufferCached = 2
} MEMORY_CACHING_TYPE_ORIG;

typedef enum _MEMORY_CACHING_TYPE {
    MmNonCached = FALSE,
    MmCached = TRUE,
    MmWriteCombined = MmFrameBufferCached,
    MmHardwareCoherentCached,
    MmNonCachedUnordered,       // IA64
    MmUSWCCached,
    MmMaximumCacheType
} MEMORY_CACHING_TYPE;

#define MM_DONT_ZERO_ALLOCATION             0x00000001
#define MM_ALLOCATE_FROM_LOCAL_NODE_ONLY    0x00000002

typedef __inexpressible_readableTo(polymorphism) MDL *PMDLX;


#if 0
NTKERNELAPI
PVOID
MmMapLockedPagesWithReservedMapping (
    __in PVOID MappingAddress,
    __in ULONG PoolTag,
    __in PMDLX MemoryDescriptorList,
    __in MEMORY_CACHING_TYPE CacheType
    );
#endif


NTKERNELAPI
PMDL
MmAllocatePagesForMdlEx (
    __in PHYSICAL_ADDRESS LowAddress,
    __in PHYSICAL_ADDRESS HighAddress,
    __in PHYSICAL_ADDRESS SkipBytes,
    __in SIZE_T TotalBytes,
    __in MEMORY_CACHING_TYPE CacheType,
    __in ULONG Flags
    );

NTKERNELAPI
VOID
MmFreePagesFromMdl (
    __in PMDLX MemoryDescriptorList
    );

//
// Types to use to contain PFNs and their counts.
//

typedef ULONG PFN_COUNT;

typedef LONG SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG PFN_NUMBER, *PPFN_NUMBER;


//++
// PPFN_NUMBER
// MmGetMdlPfnArray (
//     __in PMDL Mdl
//     )
//
// Routine Description:
//
//     The MmGetMdlPfnArray routine returns the virtual address of the
//     first element of the array of physical page numbers associated with
//     the MDL.
//
// Arguments:
//
//     Mdl - Pointer to an MDL.
//
// Return Value:
//
//     Returns the virtual address of the first element of the array of
//     physical page numbers associated with the MDL.
//
//--

#define MmGetMdlPfnArray(Mdl) ((PPFN_NUMBER)(Mdl + 1))


//
// Kernel dispatcher object functions
//


typedef KDPC *PRKDPC;

VOID
KeInitializeDpc (
    __out PRKDPC Dpc,
    __in PKDEFERRED_ROUTINE DeferredRoutine,
    __in_opt PVOID DeferredContext
    );


// from ntdef.h
typedef enum _TIMER_TYPE {
    NotificationTimer,
    SynchronizationTimer
} TIMER_TYPE;


NTKERNELAPI
VOID
KeInitializeTimerEx (
    __out PKTIMER Timer,
    __in TIMER_TYPE Type
    );

#ifdef UNDER_CE
#undef NTSYSAPI
#define NTSYSAPI
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateSecurityDescriptor (
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    ULONG Revision
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateAcl (
    PACL Acl,
    ULONG AclLength,
    ULONG AclRevision
    );


NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessAllowedAceEx (
    PACL Acl,
    ULONG AceRevision,
    ULONG AceFlags,
    ACCESS_MASK AccessMask,
    PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetDaclSecurityDescriptor (
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    BOOLEAN DaclPresent,
    PACL Dacl,
    BOOLEAN DaclDefaulted
    );


//
// Pool Allocation routines (in pool.c)
//

typedef enum _POOL_TYPE {
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS,
    MaxPoolType,
    //
    // Note these per session types are carefully chosen so that the appropriate
    // masking still applies as well as MaxPoolType above.
    //

    NonPagedPoolSession = 32,
    PagedPoolSession = NonPagedPoolSession + 1,
    NonPagedPoolMustSucceedSession = PagedPoolSession + 1,
    DontUseThisTypeSession = NonPagedPoolMustSucceedSession + 1,
    NonPagedPoolCacheAlignedSession = DontUseThisTypeSession + 1,
    PagedPoolCacheAlignedSession = NonPagedPoolCacheAlignedSession + 1,
    NonPagedPoolCacheAlignedMustSSession = PagedPoolCacheAlignedSession + 1,

    } POOL_TYPE;

//
// GENERAL_LOOKASIDE is a cache aligned type, typically shared between
// multiple processors
// 

typedef struct _NPAGED_LOOKASIDE_LIST 
{
    GENERAL_LOOKASIDE L;
#ifdef UNDER_CE
    CRITICAL_SECTION    Lock;
#else  //  UNDER_CE
    KSPIN_LOCK Lock__ObsoleteButDoNotDelete;
#endif  //  UNDER_CE
} NPAGED_LOOKASIDE_LIST, *PNPAGED_LOOKASIDE_LIST;



#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
ExInitializeNPagedLookasideList (
    __out PNPAGED_LOOKASIDE_LIST Lookaside,
    __in_opt PALLOCATE_FUNCTION Allocate,
    __in_opt PFREE_FUNCTION Free,
    __in ULONG Flags,
    __in SIZE_T Size,
    __in ULONG Tag,
    __in USHORT Depth
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
ExDeleteNPagedLookasideList (
    __inout PNPAGED_LOOKASIDE_LIST Lookaside
    );
#endif

__inline
PVOID
ExAllocateFromNPagedLookasideList (
    IN PNPAGED_LOOKASIDE_LIST Lookaside
    )

/*++

Routine Description:

    This function removes (pops) the first entry from the specified
    nonpaged lookaside list.

Arguments:

    Lookaside - Supplies a pointer to a nonpaged lookaside list structure.

Return Value:

    If an entry is removed from the specified lookaside list, then the
    address of the entry is returned as the function value. Otherwise,
    NULL is returned.

--*/

{

    PVOID Entry;

    Lookaside->L.TotalAllocates += 1;

#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)

    Entry = ExInterlockedPopEntrySList(&Lookaside->L.ListHead,
                                       &Lookaside->Lock__ObsoleteButDoNotDelete);

#else

    Entry = InterlockedPopEntrySList(&Lookaside->L.ListHead);

#endif

    if (Entry == NULL) {
        Lookaside->L.AllocateMisses += 1;
        Entry = (Lookaside->L.Allocate)(Lookaside->L.Type,
                                        Lookaside->L.Size,
                                        Lookaside->L.Tag);
    }

    return Entry;
}

__inline
VOID
ExFreeToNPagedLookasideList (
    IN PNPAGED_LOOKASIDE_LIST Lookaside,
    IN PVOID Entry
    )

/*++

Routine Description:

    This function inserts (pushes) the specified entry into the specified
    nonpaged lookaside list.

Arguments:

    Lookaside - Supplies a pointer to a nonpaged lookaside list structure.

    Entry - Supples a pointer to the entry that is inserted in the
        lookaside list.

Return Value:

    None.

--*/

{

    Lookaside->L.TotalFrees += 1;
    if (ExQueryDepthSList(&Lookaside->L.ListHead) >= Lookaside->L.Depth) {
        Lookaside->L.FreeMisses += 1;
        (Lookaside->L.Free)(Entry);

    } else {

#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)

        ExInterlockedPushEntrySList(&Lookaside->L.ListHead,
                                    (PSLIST_ENTRY)Entry,
                                    &Lookaside->Lock__ObsoleteButDoNotDelete);

#else

        InterlockedPushEntrySList(&Lookaside->L.ListHead, (PSLIST_ENTRY)Entry);

#endif

    }

    return;
}

//
// Define the I/O error log message.  This message is sent by the error log
// thread over the lpc port.
//

typedef struct _IO_ERROR_LOG_MESSAGE {
    USHORT Type;
    USHORT Size;
    USHORT DriverNameLength;
    LARGE_INTEGER TimeStamp;
    ULONG DriverNameOffset;
    IO_ERROR_LOG_PACKET EntryData;
}IO_ERROR_LOG_MESSAGE, *PIO_ERROR_LOG_MESSAGE;

#define ERROR_LOG_LIMIT_SIZE (256-16)

//
// This limit, exclusive of IO_ERROR_LOG_MESSAGE_HEADER_LENGTH, also applies
// to IO_ERROR_LOG_MESSAGE_LENGTH
//

#define IO_ERROR_LOG_MESSAGE_HEADER_LENGTH (sizeof(IO_ERROR_LOG_MESSAGE) -    \
                                            sizeof(IO_ERROR_LOG_PACKET) +     \
                                            (sizeof(WCHAR) * 40))

#define ERROR_LOG_MESSAGE_LIMIT_SIZE                                          \
    (ERROR_LOG_LIMIT_SIZE + IO_ERROR_LOG_MESSAGE_HEADER_LENGTH)

//
// IO_ERROR_LOG_MESSAGE_LENGTH is
// min(PORT_MAXIMUM_MESSAGE_LENGTH, ERROR_LOG_MESSAGE_LIMIT_SIZE)
//

#define IO_ERROR_LOG_MESSAGE_LENGTH                                           \
    ((PORT_MAXIMUM_MESSAGE_LENGTH > ERROR_LOG_MESSAGE_LIMIT_SIZE) ?           \
        ERROR_LOG_MESSAGE_LIMIT_SIZE :                                        \
        PORT_MAXIMUM_MESSAGE_LENGTH)
//
// Define the maximum packet size a driver can allocate.
//

#define ERROR_LOG_MAXIMUM_SIZE (IO_ERROR_LOG_MESSAGE_LENGTH -                 \
                                IO_ERROR_LOG_MESSAGE_HEADER_LENGTH)

#define PORT_MAXIMUM_MESSAGE_LENGTH 256

//
// Key query structures
//

typedef struct _KEY_BASIC_INFORMATION {
    LARGE_INTEGER LastWriteTime;
    ULONG   TitleIndex;
    ULONG   NameLength;
    WCHAR   Name[1];            // Variable length string
} KEY_BASIC_INFORMATION, *PKEY_BASIC_INFORMATION;

typedef struct _KEY_NODE_INFORMATION {
    LARGE_INTEGER LastWriteTime;
    ULONG   TitleIndex;
    ULONG   ClassOffset;
    ULONG   ClassLength;
    ULONG   NameLength;
    WCHAR   Name[1];            // Variable length string
//          Class[1];           // Variable length string not declared
} KEY_NODE_INFORMATION, *PKEY_NODE_INFORMATION;

typedef struct _KEY_FULL_INFORMATION {
    LARGE_INTEGER LastWriteTime;
    ULONG   TitleIndex;
    ULONG   ClassOffset;
    ULONG   ClassLength;
    ULONG   SubKeys;
    ULONG   MaxNameLen;
    ULONG   MaxClassLen;
    ULONG   Values;
    ULONG   MaxValueNameLen;
    ULONG   MaxValueDataLen;
    WCHAR   Class[1];           // Variable length
} KEY_FULL_INFORMATION, *PKEY_FULL_INFORMATION;

typedef enum _KEY_INFORMATION_CLASS {
    KeyBasicInformation,
    KeyNodeInformation,
    KeyFullInformation,
    KeyNameInformation,
    KeyCachedInformation,
    KeyFlagsInformation,
    KeyVirtualizationInformation,
    MaxKeyInfoClass   // MaxKeyInfoClass shoudl always be teh last enum
} KEY_INFORMATION_CLASS;

//
// Value entry query structures
//

typedef struct _KEY_VALUE_BASIC_INFORMATION {
    ULONG   TitleIndex;
    ULONG   Type;
    ULONG   NameLength;
    WCHAR   Name[1];            // Variable size
} KEY_VALUE_BASIC_INFORMATION, *PKEY_VALUE_BASIC_INFORMATION;

typedef struct _KEY_VALUE_FULL_INFORMATION {
    ULONG   TitleIndex;
    ULONG   Type;
    ULONG   DataOffset;
    ULONG   DataLength;
    ULONG   NameLength;
    WCHAR   Name[1];            // Variable size
//          Data[1];            // Variable size data not declared
} KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;

#define ObReferenceObject(Object) ObfReferenceObject(Object)

NTKERNELAPI
LONG_PTR
FASTCALL
ObfReferenceObject(
    __in PVOID Object
    );

FORCEINLINE
VOID
RtlInitEmptyUnicodeString(
    __out PUNICODE_STRING UnicodeString,
    __in_bcount_opt(BufferSize) PWSTR Buffer,
    __in USHORT BufferSize
    )
{
    UnicodeString->Length = 0;
    UnicodeString->MaximumLength = BufferSize;
    UnicodeString->Buffer = Buffer;
}

FORCEINLINE
VOID
RtlInitEmptyAnsiString(
    __inout PANSI_STRING AnsiString,
    __out_ecount(BufferSize) PCHAR Buffer,
    __in USHORT BufferSize
    )
{
    AnsiString->Length = 0;
    AnsiString->MaximumLength = BufferSize;
    AnsiString->Buffer = Buffer;
}

typedef struct _SECURITY_SUBJECT_CONTEXT {
    PACCESS_TOKEN ClientToken;
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
    PACCESS_TOKEN PrimaryToken;
    PVOID ProcessAuditId;
} SECURITY_SUBJECT_CONTEXT, *PSECURITY_SUBJECT_CONTEXT;


#define ReadTimeStampCounter() __rdtsc()


BOOLEAN
InterlockedBitTestAndSet (
    IN LONG volatile *Base,
    IN LONG Bit
    );


BOOLEAN
InterlockedBitTestAndReset (
    IN LONG volatile *Base,
    IN LONG Bit
    );


LONGLONG
__cdecl
InterlockedExchangeAdd64(
    IN OUT LONGLONG volatile *Addend,
    IN LONGLONG Value);

typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
    ULONG   TitleIndex;
    ULONG   Type;
    ULONG   DataLength;
    UCHAR   Data[1];            // Variable size
} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;


NTKERNELAPI
BOOLEAN
KeInsertQueueDpc (
    __inout PRKDPC Dpc,
    __in_opt PVOID SystemArgument1,
    __in_opt PVOID SystemArgument2
    );


#define InterlockedIncrementSizeT(a) InterlockedIncrement((LONG *)a)



//
// These must be converted to LUIDs before use.
//

#define SE_MIN_WELL_KNOWN_PRIVILEGE         (2L)
#define SE_CREATE_TOKEN_PRIVILEGE           (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE     (3L)
#define SE_LOCK_MEMORY_PRIVILEGE            (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE         (5L)

#define SE_MACHINE_ACCOUNT_PRIVILEGE        (6L)
#define SE_TCB_PRIVILEGE                    (7L)
#define SE_SECURITY_PRIVILEGE               (8L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE         (9L)
#define SE_LOAD_DRIVER_PRIVILEGE            (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE         (11L)
#define SE_SYSTEMTIME_PRIVILEGE             (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE    (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE      (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE        (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE       (16L)
#define SE_BACKUP_PRIVILEGE                 (17L)
#define SE_RESTORE_PRIVILEGE                (18L)
#define SE_SHUTDOWN_PRIVILEGE               (19L)
#define SE_DEBUG_PRIVILEGE                  (20L)
#define SE_AUDIT_PRIVILEGE                  (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE     (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE          (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE        (24L)
#define SE_UNDOCK_PRIVILEGE                 (25L)
#define SE_SYNC_AGENT_PRIVILEGE             (26L)
#define SE_ENABLE_DELEGATION_PRIVILEGE      (27L)
#define SE_MANAGE_VOLUME_PRIVILEGE          (28L)
#define SE_IMPERSONATE_PRIVILEGE            (29L)
#define SE_CREATE_GLOBAL_PRIVILEGE          (30L)
#define SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE (31L)
#define SE_RELABEL_PRIVILEGE                (32L)
#define SE_INC_WORKING_SET_PRIVILEGE        (33L)
#define SE_TIME_ZONE_PRIVILEGE              (34L)
#define SE_CREATE_SYMBOLIC_LINK_PRIVILEGE   (35L)
#define SE_MAX_WELL_KNOWN_PRIVILEGE         (SE_CREATE_SYMBOLIC_LINK_PRIVILEGE)

#define LOOKASIDE_MINIMUM_BLOCK_SIZE  (RTL_SIZEOF_THROUGH_FIELD (SLIST_ENTRY, Next))


//++
//
// PVOID
// MmGetMdlStartVa (
//     __in PMDL Mdl
//     )
//
// Routine Description:
//
//     The MmGetMdlBaseVa returns the virtual address of the buffer
//     described by the Mdl rounded down to the nearest page.
//
// Arguments:
//
//     Mdl - Pointer to an MDL.
//
// Return Value:
//
//     Returns the returns the starting virtual address of the MDL.
//
//
//--


typedef enum _MM_SYSTEM_SIZE {
    MmSmallSystem,
    MmMediumSystem,
    MmLargeSystem
} MM_SYSTEMSIZE;

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
MM_SYSTEMSIZE
MmQuerySystemSize (
    VOID
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WINXP)
NTKERNELAPI
NTSTATUS
MmIsVerifierEnabled (
    __out PULONG VerifierFlags
    );
#endif


typedef
NTSTATUS
(*PPCI_MSIX_SET_ENTRY) (
    __in PVOID Context,
    __in ULONG TableEntry,  
    __in ULONG MessageNumber
    );

typedef
NTSTATUS
(*PPCI_MSIX_MASKUNMASK_ENTRY) (
    __in PVOID Context,
    __in ULONG TableEntry
    );

