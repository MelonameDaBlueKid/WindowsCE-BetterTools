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

ppsyscall.h

Abstract:

Private portion of syscall.h

Notes: 


--*/

#ifndef _PRIV_SYSCALL_H__
#define _PRIV_SYSCALL_H__


#ifdef __cplusplus
extern "C" {
#endif

/* Masks for encoding of implicit handle API calls */
#if defined(MIPS)
#define FIRST_METHOD            0xFFFFBC02              // MIPS need to avoid KData, which is between 0xFFFFC000-0xFFFFE000
#define APICALL_SCALE           4
#elif defined(x86)
#define FIRST_METHOD            0xFFFFFE00
#define APICALL_SCALE           2
#elif defined(ARM)
#define FIRST_METHOD            0xF1020000
#define APICALL_SCALE           4
#elif defined(SHx)
#define FIRST_METHOD            0xFFFFFE01
#define APICALL_SCALE           2
#else
#error "Unknown CPU type"
#endif

#define OFST_PSL_RETURN         0x050
#define OFST_PSL_TRAP_SEED      0x054

#define SYSCALL_RETURN_RAW      (FIRST_METHOD-APICALL_SCALE)

#define PSL_TRAP_SEED           (*(LPDWORD) (PUserKData+OFST_PSL_TRAP_SEED))
#define SYSCALL_RETURN          (*(LPDWORD) (PUserKData+OFST_PSL_RETURN))

#define NUM_API_SETS            128             // must be 2^n

#define APISET_SHIFT            8
#define METHOD_MASK             0x00FF
#define APISET_MASK             (NUM_API_SETS-1)

//
// all the API encoding falls between the following range
//
//  (LAST_METHOD <= api_encoding <= MAX_METHOD_NUM)
//
#define MAX_METHOD_NUM          (FIRST_METHOD + (METHOD_MASK * APICALL_SCALE))
#define LAST_METHOD             (FIRST_METHOD - ((APISET_MASK)<<APISET_SHIFT | (METHOD_MASK))*APICALL_SCALE)

// #define REGAPISET_KPSL       0x40000000  // no supported
#define REGAPISET_TYPEONLY      0x80000000

/* These macros generate the special addresses to call for a given
 * method index for handle based APIs or a handle index and method
 * index pair for an implicit handle API call.
 */
#if defined(WINCEMACRO) || defined(WINCEAFDMACRO) || defined(WINCEWSPMMACRO)
#define METHOD_CALL(mid)        ((FIRST_METHOD + (mid)*APICALL_SCALE) ^ PSL_TRAP_SEED)
#define IMPLICIT_CALL(hid, mid) ((FIRST_METHOD - ((hid)<<APISET_SHIFT | (mid))*APICALL_SCALE) ^ PSL_TRAP_SEED)
#endif
// Private version available even without WINCEMACRO being on
#define PRIV_IMPLICIT_CALL(hid, mid) ((FIRST_METHOD - ((hid)<<APISET_SHIFT | (mid))*APICALL_SCALE) ^ PSL_TRAP_SEED)


#ifdef KCOREDLL

//
// When we're in kernel mode, we call the APIs directly. 
//
extern FARPROC *g_ppfnWin32Calls;               // kernel WIN32 APIs
extern FARPROC *g_ppfnCritCalls;                // Critical Seciton calls
extern FARPROC *g_ppfnWmgrCalls;                // WMGR APIs
extern FARPROC *g_ppfnWgdiCalls;                // GDI APIs
extern FARPROC *g_ppfnFysCalls;                 // FILESYS APIs
extern FARPROC *g_ppfnDevMgrCalls;              // DEVICE manager APIs

#endif

/* These macros will generate a C declaration for psuedo function to
 * invoke a given method.  To define a function:
 *  #define Function METHOD_DECL(return_type, method index,
 *      (type1 arg1, type2 arg2, etc))
 * or
 *  #define Function IMPLICIT_DECL(return type, handle index, method index,
 *      (type1 arg1, type2 arg2, etc))
 */
#define METHOD_DECL(type, mid, args) (*(type (*)args)METHOD_CALL(mid))
#define IMPLICIT_DECL(type, hid, mid, args) (*(type (*)args)IMPLICIT_CALL(hid, mid))
// Private version available even without WINCEMACRO being on
#define PRIV_IMPLICIT_DECL(type, hid, mid, args) (*(type (*)args)PRIV_IMPLICIT_CALL(hid, mid))

// Private version available even without WINCEMACRO being on
#define PRIV_WIN32_CALL(type, api, args) PRIV_IMPLICIT_DECL(type, SH_WIN32, W32_ ## api, args)

#define _THREAD_CALL(type, api, args) IMPLICIT_DECL(type, SH_CURTHREAD, ID_THREAD_ ## api, args)
#define _PROCESS_CALL(type, api, args) IMPLICIT_DECL(type, SH_CURPROC, ID_PROC_ ## api, args)
#define _EVENT_CALL(type, api, args) IMPLICIT_DECL(type, HT_EVENT, ID_EVENT_ ## api, args)
#define _APISET_CALL(type, api, args) IMPLICIT_DECL(type, HT_APISET, ID_APISET_ ## api, args)
#define _FSMAP_CALL(type, api, args) IMPLICIT_DECL(type, HT_FSMAP, ID_FSMAP_ ## api, args)
#define _MUTEX_CALL(type, api, args) IMPLICIT_DECL(type, HT_MUTEX, ID_MUTEX_ ## api, args)
#define _SEMAPHORE_CALL(type, api, args) IMPLICIT_DECL(type, HT_SEMAPHORE, ID_SEMAPHORE_ ## api, args)


#define W32_HandleCall                  0
#define W32_CreateAPISet                2
#define W32_CreateProcess               3
#define W32_OpenProcess                 4
#define W32_CreateThread                5
#define W32_OpenThread                  6
#define W32_CreateEvent                 7
#define W32_OpenEvent                   8
#define W32_CreateMutex                 9
#define W32_OpenMutex                   10
#define W32_CreateSemaphore             11
#define W32_OpenSemaphore               12
#define W32_NKExitThread                13
#define W32_TlsCall                     14
#define W32_IsBadPtr                    15
#define W32_CeVirtualSharedAlloc        16
#define W32_CRITCreate                  17
#define W32_Sleep                       18
#define W32_SetLastError                19
#define W32_GetLastError                20
#define W32_LoadLibraryEx               21
#define W32_FreeLibrary                 22
#define W32_CreateWatchDog              23
#define W32_CeCreateToken               24
#define W32_DuplicateHandle             25
#define W32_WaitForMultiple             26
#define W32_OutputDebugString           27
#define W32_NKvDbgPrintfW               28
#define W32_RaiseException              29
#define W32_PerformCallBack             30
#define W32_GetTickCount                31
#define W32_GetProcessVersion           32     // GetProcessVersion
#define W32_GetRomFileBytes             33
#define W32_CeRevertToSelf              34
#define W32_CeImpersonateCurrProc       35
#define W32_GetRomFileInfo              36
#define W32_GetSystemInfo               37
#define W32_GetFSHeapInfo               38
#define W32_KernelIoControl             39
#define W32_KernelLibIoControl          40
#define W32_NKGetTime                   41
#define W32_GetDirectCallerProcessId    42
#define W32_CeSerializeTokenData        43 // CeSerializeTokenData
#define W32_GetIdleTime                 44
#define W32_CacheRangeFlush             45
#define W32_LoadExistingModule          46  // u-mode only
#define W32_GetCallerResInfo            46  // k-mode only
#define W32_WaitForDebugEvent           47
#define W32_ContinueDebugEvent          48
#define W32_DebugNotify                 49
#define W32_AttachDebugger              50
#define W32_BinaryCompress              51
#define W32_BinaryDecompress            52
#define W32_DecompressBinaryBlock       53
#define W32_StringCompress              54
#define W32_StringDecompress            55
#define W32_CeGetRandomSeed             56
#define W32_SleepTillTick               57
#define W32_QueryPerformanceFrequency   58
#define W32_QueryPerformanceCounter     59
#define W32_GetThreadTimes              60
#define W32_QueryAPISetID               61
#define W32_IsNamedEventSignaled        62
#define W32_CreateLocaleView            63
#define W32_RegisterDbgZones            64
#define W32_SetDbgZone                  65
#define W32_CreateMsgQueue              66
#define W32_WriteDebugLED               67
#define W32_IsProcessorFeaturePresent   68
#define W32_QueryInstructionSet         69
#define W32_SetKernelAlarm              70
#define W32_RefreshKernelAlarm          71
#define W32_SetOOMEventEx               72
#define W32_NKSetTime                   73
#define W32_GetKPhys                    74
#define W32_GiveKPhys                   75
#define W32_InputDebugCharW             76
#define W32_SetLowestScheduledPriority  77
#define W32_UpdateNLSInfoEx             78
#define W32_ReadRegistryFromOEM         79
#define W32_WriteRegistryToOEM          80
#define W32_GetStdioPathW               81
#define W32_SetStdioPathW               82
#define W32_SetHardwareWatch            83
#define W32_PrepareThreadExit           84
#define W32_InterruptInitialize         85
#define W32_InterruptDisable            86
#define W32_InterruptDone               87
#define W32_InterruptMask               88
#define W32_SetPowerHandler             89
#define W32_PowerOffSystem              90
#define W32_LoadIntChainHandler         91
#define W32_FreeIntChainHandler         92
#define W32_GetExitCodeProcess          93
#define W32_GetExitCodeThread           94
#define W32_CreateStaticMapping         95
#define W32_SetDaylightTime             96
#define W32_SetTimeZoneBias             97
#define W32_THCreateSnapshot            98
#define W32_RemoteLocalAlloc            99
#define W32_RemoteLocalReAlloc          100
#define W32_RemoteLocalSize             101
#define W32_RemoteLocalFree             102
#define W32_PSLNotify                   103
#define W32_SystemMemoryLow             104
#define W32_LoadKernelLibrary           105
#define W32_CeLogData                   106
#define W32_CeLogSetZones               107
#define W32_CeLogGetZones               108
#define W32_CeLogReSync                 109
#define W32_WaitForAPIReady             110
#define W32_SetRAMMode                  111
#define W32_SetStoreQueueBase           112
#define W32_GetHandleServerId           113
#define W32_CeAccessCheck               114
#define W32_CePrivilegeCheck            115
#define W32_SetDirectCall               116
#define W32_GetCallerVMProcessId        117
#define W32_ProfileSyscall              118
#define W32_DebugSetProcessKillOnExit   119
#define W32_DebugActiveProcessStop      120
#define W32_DebugActiveProcess          121
#define W32_GetCallerProcess            122     // old behavior GetCallerProcess
#define W32_ReadKPEHeader               123
#define W32_ForcePageout                124
#define W32_DeleteStaticMapping         125
#define W32_CeGetRawTime                126     // CeGetRawTime
#define W32_FileTimeToSystemTime        127     // FileTimeToSystemTime
#define W32_SystemTimeToFileTime        128     // SystemTimeToFileTime
#define W32_NKGetTimeAsFileTime         129     // NKGetTimeAsFileTime
#define W32_NKGetCPUInfo                130     // NKGetCPUInfo (implement CeGetProcessorState, CeGetIdleTimeEx)
#define W32_NKCPUPowerFunc              131     // NKCPUPowerFunc (implement CePowerOnProcessor/CePowerOffProcessor)
#define W32_CeGetAccessMask             132     // CeGetAccessMask
#define W32_CeGetOwnerAccount           133     // CeGetOwnerAccount
#define W32_CeGetGroupAccount           134     // CeGetGroupAccount
#define W32_CeDeserializeTokenData      135     // CeDeserializeTokenData
#define W32_CeResetStack                139     // CeResetStack

/* Common syscalls */

#define ID_HCALLBASE             2

#define ID_HCALL(i)                 (i+ID_HCALLBASE)

/* Process syscalls */

#define ID_PROC_TERMINATE           ID_HCALL(0)
#define ID_PROC_VMSETATTR           ID_HCALL(1)
#define ID_PROC_FLUSHICACHE         ID_HCALL(2)
#define ID_PROC_READMEMORY          ID_HCALL(3)
#define ID_PROC_WRITEMEMORY         ID_HCALL(4)
#define ID_PROC_LOADMODULE          ID_HCALL(5)
#define ID_PROC_GETMODINFO          ID_HCALL(6)
#define ID_PROC_SETVER              ID_HCALL(7)
#define ID_PROC_VMALLOC             ID_HCALL(8)
#define ID_PROC_VMFREE              ID_HCALL(9)
#define ID_PROC_VMQUERY             ID_HCALL(10)
#define ID_PROC_VMPROTECT           ID_HCALL(11)
#define ID_PROC_VMCOPY              ID_HCALL(12)
#define ID_PROC_VMLOCK              ID_HCALL(13)
#define ID_PROC_VMUNLOCK            ID_HCALL(14)
#define ID_PROC_HNDLCLOSE           ID_HCALL(15)
#define ID_PROC_UNMAPVIEW           ID_HCALL(16)
#define ID_PROC_FLUSHVIEW           ID_HCALL(17)
#define ID_PROC_MAPVIEW             ID_HCALL(18)
#define ID_PROC_MAPCREATE           ID_HCALL(19)
#define ID_PROC_GETPROCACCOUNT      ID_HCALL(20)
#define ID_PROC_GETMODNAME          ID_HCALL(21)
#define ID_PROC_GETMODHNDL          ID_HCALL(22)
#define ID_PROC_VMALLOCPHYS         ID_HCALL(23)
#define ID_PROC_READPEHEADER        ID_HCALL(24)
#define ID_PROC_CHECKREMOTEDEBUGGERPRESENT ID_HCALL(25)
#define ID_PROC_OPENMSGQEX          ID_HCALL(26)
#define ID_PROC_GETPROCID           ID_HCALL(27)
#define ID_PROC_VMALLOCCOPY         ID_HCALL(28)
#define ID_PROC_PAGEOUTMODULE       ID_HCALL(29)
#define ID_PROC_GETAFFINITY         ID_HCALL(30)
#define ID_PROC_SETAFFINITY         ID_HCALL(31)
#define ID_PROC_MAPADDRTOVOID       ID_HCALL(32)
#define ID_PROC_GETTIMES            ID_HCALL(33)

/* Thread syscalls */

#define ID_THREAD_SUSPEND           ID_HCALL(0)
#define ID_THREAD_RESUME            ID_HCALL(1)
#define ID_THREAD_SETTHREADPRIO     ID_HCALL(2)
#define ID_THREAD_GETTHREADPRIO     ID_HCALL(3)
#define ID_THREAD_GETCALLSTACK      ID_HCALL(4)
#define ID_THREAD_GETCONTEXT        ID_HCALL(5)
#define ID_THREAD_SETCONTEXT        ID_HCALL(6)
#define ID_THREAD_TERMINATE         ID_HCALL(7)
#define ID_THREAD_CEGETPRIO         ID_HCALL(8)
#define ID_THREAD_CESETPRIO         ID_HCALL(9)
#define ID_THREAD_CEGETQUANT        ID_HCALL(10)
#define ID_THREAD_CESETQUANT        ID_HCALL(11)
#define ID_THREAD_GETID             ID_HCALL(12)
#define ID_THREAD_GETPROCID         ID_HCALL(13)
#define ID_THREAD_GETAFFINITY       ID_HCALL(14)
#define ID_THREAD_SETAFFINITY       ID_HCALL(15)
#define ID_THREAD_GETTHREADACCOUNT  ID_HCALL(16)

/* Token syscalls */
#define ID_TOKEN_IMPERSONATE        ID_HCALL(0)
#define ID_TOKEN_DUPLICATE          ID_HCALL(1)

/* Event syscalls */

#define ID_EVENT_MODIFY             ID_HCALL(0)
#define ID_EVENT_GETDATA            ID_HCALL(1)
#define ID_EVENT_SETDATA            ID_HCALL(2)
#define ID_EVENT_READMSGQ           ID_HCALL(3)
#define ID_EVENT_WRITEMSGQ          ID_HCALL(4)
#define ID_EVENT_GETMSGQINFO        ID_HCALL(5)
#define ID_EVENT_WDSTART            ID_HCALL(6)
#define ID_EVENT_WDSTOP             ID_HCALL(7)
#define ID_EVENT_WDREFRESH          ID_HCALL(8)
#define ID_EVENT_RESUMEMAINTH       ID_HCALL(9)

/* Apiset syscalls */

#define ID_APISET_REGISTER                 ID_HCALL(0)
#define ID_APISET_CREATEHANDLE             ID_HCALL(1)
#define ID_APISET_VERIFY                   ID_HCALL(2)
#define ID_APISET_REGDIRECTMTHD            ID_HCALL(3)
#define ID_APISET_LOCKAPIHANDLE            ID_HCALL(4)
#define ID_APISET_UNLOCKAPIHANDLE          ID_HCALL(5)
#define ID_APISET_SETAPIERRORHANDLER       ID_HCALL(6)
#define ID_APISET_REGACCESSMASK            ID_HCALL(7)
#define ID_APISET_CREATEHANDLEWITHACCESS   ID_HCALL(8)

/* mapped file syscalls */

#define ID_FSMAP_MAPVIEWOFFILE ID_HCALL(0)

/* mutex syscalls */

#define ID_MUTEX_RELEASEMUTEX ID_HCALL(0)

/* semaphore syscalls */

#define ID_SEMAPHORE_RELEASESEMAPHORE ID_HCALL(0)

#ifdef __cplusplus
}
#endif

#endif // _PRIV_SYSCALL_H__

