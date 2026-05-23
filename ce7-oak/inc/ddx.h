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

Module Name:

    ddx.h

Abstract:

    Public header file for Differential Diagnostics (DDx) in CE Watson.

--*/

#ifndef _DDX_H_
#define _DDX_H_


// Exception codes for DDx events

#define STATUS_POSSIBLE_ABONDONED_SYNC            ((NTSTATUS)0xC0008000L)
#define STATUS_POSSIBLE_STARVATION                ((NTSTATUS)0xC0008001L)
#define STATUS_HEAP_CORRUPTION                    ((NTSTATUS)0xC0008002L)
#define STATUS_HANDLED_EX_HOLDING_SYNC_OBJECT     ((NTSTATUS)0x80008000L)
#define STATUS_STACK_OVERFLOW_WARNING             ((NTSTATUS)0x80008001L)

#define HEAP_ITEM_SIGNATURE_CORRUPTION            0x80020001
#define HEAP_ITEM_SIZE_CORRUPTION                 0x80020002
#define HEAP_ITEM_TAIL_CORRUPTION                 0x80020003
#define HEAP_FREE_ITEM_CORRUPTION                 0x80020004
#define HEAP_ITEM_DOUBLE_FREE                     0x80020005

#define DDX_EVENT_DEADLOCK_CHECK                  L"DDxDeadlockCheckEvent"
#define DDX_EVENT_ABANDONED_SYNC_CHECK            L"DDxAbandonedSyncCheckEvent"

#define DDX_ABANDONED_SYNC_THRESHOLD              1000 // Milliseconds.  TODO: Tune to minimize false postives
 
#define IOCTL_DDX_LOAD_PROBE                      1


typedef enum _DDxResult_e
{
   DDxResult_Error              = 0x00,    // Diagnostic tool finds an error that prevents it from running correctly
   DDxResult_Continue           = 0x01,    // [INTERNAL ONLY] Diagnostic tool Result element used for flow control internally in some Diagnose functions
   DDxResult_Positive           = 0x02,    // An error was positively identified
   DDxResult_Negative           = 0x03,    // No errors were found
   DDxResult_Inconclusive       = 0x04,    // Diagnostic tool unable to make a positive diagnosis, but cannot rule out failure
   DDxResult_Duplicate          = 0x05     // DDx has already identified a persistent condition, the diagnosis is a duplicate
}
DDxResult_e;


// Diagnosis Types

typedef enum _DiagnosisType_e
{
   Type_Unknown               = 0x00,       
   Type_Deadlock              = 0x01,       
   Type_Starvation            = 0x02,       
   Type_LowMemory             = 0x03,       
   Type_HeapCorruption        = 0x04,       
   Type_WaitCursor            = 0x05,       
   Type_VirtualMemory         = 0x06,       
   Type_UnrefedObject         = 0x07,       
   Type_AbandonedSync         = 0x08,       
   Type_Stack                 = 0x09,      
   Type_Exception             = 0x10,       
}
DiagnosisType_e;



// Diagnosis Sub Types

typedef enum _DeadlockType_e
{
   Deadlock_Circular          = 0x01,       // Circular contention for critical section or mutex
   Deadlock_AbandonedSyncObj  = 0x02        // A critical section or mutex is indefinitely held by its owner thread
}
DeadlockType_e;


typedef enum _StackIssueType_e
{
   Stack_Overflow          = 0x01,       // Stack has exceeded the system defined size limit
   Stack_Overflow_Warning  = 0x02        // Stack is within one page of exceeding the system defined size limit
}
StackIssueType_e;


typedef enum _ExType_e
{
   Ex_Unknown             = 0x00,        // 
   Ex_AV                  = 0x01,        // Access Violation
   Ex_Null_Deref          = 0x02,        // NULL ptr dereference  
   Ex_FreeModule          = 0x03,        // Calling into an unloaded module
   Ex_Div0                = 0x04,        // Divide by zeroexception
}
ExType_e;


// Scope

typedef enum _Scope_e
{
   Scope_Unknown              = 0x00,       
   Scope_Application          = 0x01,       // Affects faulting app only
   Scope_System               = 0x02,       // System-wide implications
}
Scope_e;


// Depth

typedef enum _Depth_e
{
   Depth_Unknown             = 0x00,       
   Depth_Symptom             = 0x01,       
   Depth_Cause               = 0x02,       
}
Depth_e;


// Severity

typedef enum _Severity_e
{
   Severity_Unknown             = 0x00,    
   Severity_NoEffect            = 0x01,    
   Severity_Recoverable         = 0x02,    
   Severity_Severe              = 0x03,    
   Severity_Fatal               = 0x04     
}
Severity_e;


// Confidence

typedef enum _Confidence_e
{
   Confidence_Unknown             = 0x00,      
   Confidence_Possible            = 0x02,      
   Confidence_Probable            = 0x03,      
   Confidence_Certain             = 0x04       
}
Confidence_e;


// IOCTLs supported by DDXPROBE.DLL

typedef BOOL (*PFN_DDXPROBEIOCTL) (DWORD, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD);

typedef enum 
{
    // lpInBuf:     Ptr to OSAXS_DATA structure
    // nInBufSize:  sizeof(OSAXS_DATA)
    // lpOutBuf:    ignored
    // nOutBufSize: ignored

    IOCTL_DDX_PROBE_INIT             = 1,

    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    ignored
    // nOutBufSize: ignored

    IOCTL_DDX_PROBE_START            = 2,
    
    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    ignored
    // nOutBufSize: ignored

    IOCTL_DDX_PROBE_STOP             = 3,

    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    MODULEHEAPINFO**
    // nOutBufSize: sizeof(MODULEHEAPINFO*)

    IOCTL_DDX_PROBE_GET_NK_HEAP_INFO = 4,

    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    MODULEHEAPINFO**
    // nOutBufSize: sizeof(MODULEHEAPINFO*)

    IOCTL_DDX_PROBE_GET_HEAP_INFO    = 5,

    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    CEL_LOWMEM_DATA*
    // nOutBufSize: sizeof(CEL_LOWMEM_DATA)

    IOCTL_DDX_PROBE_GET_OOM_DATA     = 6,

    // lpInBuf:     DWORD - address of PC 
    // nInBufSize:  ignored
    // lpOutBuf:    UNLOADED_MODULE*
    // nOutBufSize: sizeof(UNLOADED_MODULE)

    IOCTL_DDX_PROBE_IS_FREE_MOD      = 7,

    // lpInBuf:     _WatchdogConfig *
    // nInBufSize:  sizeof(_WatchdogConfig *)
    // lpOutBuf:    ignored
    // nOutBufSize: ignored   
    
    IOCTL_DDX_PROBE_WATCHDOG_INITIALIZE = 8,

    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    ignored
    // nOutBufSize: ignored   
    
    IOCTL_DDX_PROBE_WATCHDOG_UNINITIALIZE = 9,
    
    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    _StarvationReport *
    // nOutBufSize: sizeof(_StarvationReport *)
    
    IOCTL_DDX_PROBE_WATCHDOG_GET_STARVER = 10,
    
    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    DWORD*
    // nOutBufSize: sizeof(DWORD)
    
    IOCTL_DDX_PROBE_IS_ENABLED           = 11,
    
    // lpInBuf:     ignored
    // nInBufSize:  ignored
    // lpOutBuf:    ignored
    // nOutBufSize: ignored
    
    IOCTL_DDX_PROBE_LOCAL_DUMPS          = 12
} 
PROBE_IOCTL_ID;


typedef enum 
{ 
    PAGETYPE_FREE = 0,
    PAGETYPE_RESERVED, 
    PAGETYPE_STACK, 
    PAGETYPE_UNKNOWN, 
    PAGETYPE_CODE_ROM, 
    PAGETYPE_CODE_RAM,  
    PAGETYPE_CODE_DLL_ROM, 
    PAGETYPE_CODE_DLL_RAM, 
    PAGETYPE_CODE_EXE_ROM, 
    PAGETYPE_CODE_EXE_RAM,
    PAGETYPE_WRITABLE, 
    PAGETYPE_RW_DLL,
    PAGETYPE_RW_EXE,
    PAGETYPE_PERIPHERAL,
    PAGETYPE_RO_ROM,
    PAGETYPE_RO_RAM,
    PAGETYPE_HEAP, 
    PAGETYPE_OBJSTORE, 
    PAGETYPE_PAGEPOOL, 
    PAGETYPE_DUPLICATE,
    NUM_PAGETYPES               // <-- this must be the last entry of the enum
}
PageType;

typedef struct _FREE_MOD_DATA
{
    DWORD   dwProcId;
    HANDLE  pMod;
    DWORD   BasePtr;
    DWORD   VMSize;
    DWORD   dwTimeStamp;
    WCHAR   wszName[MAX_PATH];
}
FREE_MOD_DATA, *PFREE_MOD_DATA;

//Name of the event to stop the DDxWatchdog (CPU starvation probe)
#ifndef DDX_WATCHDOG_EXIT_EVENT_NAME
#define DDX_WATCHDOG_EXIT_EVENT_NAME TEXT("DDX_WATCHDOG_EXIT")
#endif

#ifndef DDX_WATCHDOG_STARVING_EVENT_NAME
#define DDX_WATCHDOG_STARVING_EVENT_NAME TEXT("DDX_WATCHDOG_STARVATION")
#endif

//Structures used by the CPU starvation probe
typedef struct _HighCPUThread
{
  DWORD   threadId;
  DWORD   cpuPercent;

} HighCPUThread, *PHighCPUThread;

typedef struct _StarvationReport
{
   DWORD dwSize;
   HighCPUThread highCPUThreads[3];
   BYTE  starvedCEPriority;

} StarvationReport, *PStarvationReport;

typedef struct _WatchdogConfig
{
   DWORD  dwSize;
   BOOL   fEnabled;
   BOOL   fSignalMode;
   DWORD  msecsThresholdForRealtime;
   DWORD  msecsThresholdForAboveNormal;
   DWORD  msecsThresholdForNormal;
   DWORD  msecsThresholdForBelowNormal;
   DWORD  msecsThresholdForUnderBelow;
} WatchdogConfig, *PWatchdogConfig;


#endif // _DDX_H_