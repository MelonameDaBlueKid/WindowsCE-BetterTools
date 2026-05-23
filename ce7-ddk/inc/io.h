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

#include <ntcompat.h>   // For PWORKER_THREAD_ROUTINE, PDEVICE_OBJECT

// IO_WORKITEM is opaque
typedef struct _IO_WORKITEM IO_WORKITEM, *PIO_WORKITEM;

//
//  IO Functions
//

typedef
VOID
IO_WORKITEM_ROUTINE (
    __in PDEVICE_OBJECT DeviceObject,
    __in_opt PVOID Context
    );
    
typedef IO_WORKITEM_ROUTINE *PIO_WORKITEM_ROUTINE;

typedef
VOID
IO_WORKITEM_ROUTINE_EX (
    __in PVOID IoObject,
    __in_opt PVOID Context,
    __in PIO_WORKITEM IoWorkItem
    );

typedef IO_WORKITEM_ROUTINE_EX *PIO_WORKITEM_ROUTINE_EX;

typedef
VOID
(*PIO_WORKITEM_ROUTINE) (
    IN PDEVICE_OBJECT DeviceObject,
    IN PVOID Context
);

ULONG
IoSizeofWorkItem();

VOID  
IoInitializeWorkItem(    
    IN  PVOID         IoObject,    
    OUT PIO_WORKITEM  IoWorkItem);

VOID
IoUninitializeWorkItem(
    __in IN PIO_WORKITEM IoWorkItem
    );
    
PIO_WORKITEM
IoAllocateWorkItem(PDEVICE_OBJECT DeviceObject);

VOID
IoFreeWorkItem(PIO_WORKITEM pIoWorkItem);

VOID
IoQueueWorkItem(
	IN PIO_WORKITEM IoWorkItem,
    IN PIO_WORKITEM_ROUTINE WorkerRoutine,
    IN WORK_QUEUE_TYPE QueueType,
    IN PVOID Context);
    
VOID
IoQueueWorkItemEx(    
    IN PIO_WORKITEM             IoWorkItem,    
    IN PIO_WORKITEM_ROUTINE_EX  WorkerRoutineEx,    
    IN WORK_QUEUE_TYPE          QueueType,    
    IN PVOID                    Context    );

#ifndef DISPATCH_LEVEL
#define DISPATCH_LEVEL 2
#endif
