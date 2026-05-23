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

mkfuncs.h

Abstract:  

Notes: 


--*/
#ifndef __MKFUNCS_H__
#define __MKFUNCS_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

#ifdef WIN32_CALL
#define SetLastError WIN32_CALL(VOID, SetLastError, (DWORD))
#elif !defined(COREDLL)
#define SetLastError PRIV_WIN32_CALL(VOID, SetLastError, (DWORD))
#endif
#define CloseAllHandles PRIV_WIN32_CALL(void, CloseAllHandles, (void))
#define RaiseException PRIV_WIN32_CALL(VOID, RaiseException, (DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD cArgs, CONST DWORD *lpArgs))

#ifndef IN_KERNEL

#include <toolhelp.h>

#define IsBadCodePtr(lpfnProc) IsBadPtr(VERIFY_EXECUTE_FLAG, (LPBYTE)(lpfnProc), 1)
#define IsBadReadPtr(lpvPtr, cbBytes) IsBadPtr(VERIFY_READ_FLAG, (LPBYTE)(lpvPtr), (cbBytes))
#define IsBadWritePtr(lpvPtr, cbBytes) IsBadPtr(VERIFY_WRITE_FLAG, (LPBYTE)(lpvPtr), (cbBytes))

#ifdef WIN32_CALL

// WIN32 calls
#define CreateAPISet        WIN32_CALL(HANDLE, CreateAPISet, \
    (char acName[4], USHORT cFunctions, const PFNVOID *ppfnMethods, const ULONGLONG *pu64Sig))

#define DuplicateHandle     WIN32_CALL(BOOL, DuplicateHandle, (HANDLE hSrcProc, HANDLE hSrcHndl, HANDLE hDstProc, LPHANDLE lpDstHndl, DWORD dwAccess, BOOL bInherit, DWORD dwOptions))

#define OutputDebugStringW  WIN32_CALL(VOID, OutputDebugString, (LPCWSTR str))
#define NKvDbgPrintfW       WIN32_CALL(VOID, NKvDbgPrintfW, (LPCWSTR lpszFmt, va_list param))
#define CreateEventW        WIN32_CALL(HANDLE, CreateEvent, \
    (LPSECURITY_ATTRIBUTES lpsa, BOOL fManual, BOOL fInit, LPCWSTR lpName))
#define OpenEventW          WIN32_CALL(HANDLE, OpenEvent, \
    (DWORD dwDesiredAccess, BOOL fInheritHandle, LPCWSTR lpName))
#define CreateProcessW      WIN32_CALL(BOOL, CreateProcess, \
    (LPCWSTR, LPCWSTR, LPCE_PROCESS_INFORMATION))
#define CreateThread        WIN32_CALL(HANDLE, CreateThread, \
    (LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, LPTHREAD_START_ROUTINE lpStartAddr, \
     LPVOID lpvThreadParm, DWORD fdwCreate, LPDWORD lpIDThread))
#define CreateMutexW        WIN32_CALL(HANDLE, CreateMutex, \
    (LPSECURITY_ATTRIBUTES lpsa, BOOL bInitialOwner, LPCTSTR lpName))
#define GetLastError        WIN32_CALL(DWORD, GetLastError, (void))
#define OpenProcess         WIN32_CALL(HANDLE, OpenProcess, (DWORD fdwAccess, BOOL fInherit, DWORD IDProcess))
#define OpenThread          WIN32_CALL(HANDLE, OpenThread, (DWORD fdwAccess, BOOL fInherit, DWORD IDThread))
#define KernelSleep         WIN32_CALL(VOID, Sleep, (DWORD cMilliseconds))
#define KernelWaitForMultipleObjects WIN32_CALL(BOOL, WaitForMultiple, \
    (DWORD cObjects, CONST HANDLE *lphObjects, BOOL fWaitAll, DWORD dwTimeout, LPDWORD lpRetVal))
#define SleepTillTick       WIN32_CALL(void, SleepTillTick, (void))
#define CreateSemaphoreW    WIN32_CALL(HANDLE, CreateSemaphore, (LPSECURITY_ATTRIBUTES lpsa, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName))
#define GetTickCount        WIN32_CALL(DWORD, GetTickCount, (VOID))

#define GetRomFileBytes     WIN32_CALL(BOOL, GetRomFileBytes, (DWORD type, DWORD count, DWORD pos, LPVOID buffer, DWORD nBytesToRead))
#define GetRomFileInfo      WIN32_CALL(BOOL, GetRomFileInfo, (DWORD type, LPWIN32_FIND_DATA lpfd, DWORD count))

#define GetSystemInfo       WIN32_CALL(VOID, GetSystemInfo, (LPSYSTEM_INFO lpSystemInfo))
#define GetFSHeapInfo       WIN32_CALL(DWORD, GetFSHeapInfo, (void))

#define KernelIoControl     WIN32_CALL(BOOL, KernelIoControl, (DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned))
#define KernelLibIoControl  WIN32_CALL(BOOL, KernelLibIoControl, (HANDLE hLib, DWORD dwIoControlCode, \
    LPVOID lpInBuf, DWORD nInBufSize, \
    LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned))

#define GetDirectCallerProcessId WIN32_CALL (DWORD, GetDirectCallerProcessId, (void))
#define GetCallerVMProcessId     WIN32_CALL (DWORD, GetCallerVMProcessId, (void))
#define GetCallerProcess         WIN32_CALL (DWORD, GetCallerProcess, (void))

#define CreateFileMappingW +++ Do Not Use +++

#define CacheRangeFlush     WIN32_CALL(void, CacheRangeFlush, (LPVOID pAddr, DWORD dwLength, DWORD dwFlags))

#define CeGetRandomSeed     WIN32_CALL(__int64, CeGetRandomSeed, (void))
#define GetIdleTime         WIN32_CALL(DWORD, GetIdleTime, (void))

#define StringCompress      WIN32_CALL(DWORD, StringCompress, (LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD  lenout))
#define StringDecompress    WIN32_CALL(DWORD, StringDecompress, (LPBYTE bufin, DWORD  lenin, LPBYTE bufout, DWORD  lenout))
#define BinaryCompress      WIN32_CALL(DWORD, BinaryCompress, (LPBYTE bufin, DWORD  lenin, LPBYTE bufout, DWORD  lenout))
#define BinaryDecompress    WIN32_CALL(DWORD, BinaryDecompress, (LPBYTE bufin, DWORD  lenin, LPBYTE bufout, DWORD  lenout, DWORD  skip))
#define DecompressBinaryBlock WIN32_CALL(DWORD, DecompressBinaryBlock, (LPBYTE  lpbSrc, DWORD   cbSrc, LPBYTE  lpbDest, DWORD cbDest))

#define TlsCall             WIN32_CALL(DWORD, TlsCall, (DWORD p1, DWORD p2))

#define IsBadPtr            WIN32_CALL(BOOL, IsBadPtr, (DWORD flags, LPBYTE ptr, UINT length))
#define CeVirtualSharedAlloc WIN32_CALL(LPVOID, CeVirtualSharedAlloc, (LPVOID lpvAddr, DWORD cbSize, DWORD fdwAction, PDWORD pdwTag))

#define QueryPerformanceFrequency WIN32_CALL(BOOL, QueryPerformanceFrequency, (LARGE_INTEGER *pli))
#define QueryPerformanceCounter WIN32_CALL(BOOL, QueryPerformanceCounter, (LARGE_INTEGER *pli))

#define GetThreadTimes      WIN32_CALL(BOOL, GetThreadTimes, (HANDLE hth, LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime))
#define QueryAPISetID       WIN32_CALL(BOOL, QueryAPISetID, (char *pName, int* lpRetVal))
#define IsNamedEventSignaled WIN32_CALL(BOOL, IsNamedEventSignaled, (LPCWSTR pszName, DWORD dwFlags))

#define CreateLocaleView    WIN32_CALL(LPBYTE, CreateLocaleView, (LPDWORD pdwSize))

#define WriteDebugLED       WIN32_CALL(void, WriteDebugLED, (WORD idx, DWORD dwVal))
#define IsProcessorFeaturePresent WIN32_CALL(BOOL, IsProcessorFeaturePresent, (DWORD dwFeature))
#define QueryInstructionSet WIN32_CALL(BOOL, QueryInstructionSet, (DWORD dwSet, LPDWORD lpdwCurSet))

#define RefreshKernelAlarm  WIN32_CALL(void, RefreshKernelAlarm, (void))
#define SetKernelAlarm      WIN32_CALL(BOOL, SetKernelAlarm, (HANDLE h, LPSYSTEMTIME pst))

#define SetOOMEventEx       WIN32_CALL(void, SetOOMEventEx, (HANDLE hEvtLowMemoryState, HANDLE hEvtGoodMemoryState, DWORD cpLowMemEvent, DWORD cpLow, DWORD cpCritical, DWORD cpLowBlockSize, DWORD cpCriticalBlockSize))

#define GetKPhys            WIN32_CALL(BOOL, GetKPhys, (LPVOID ptr, ulong length))
#define GiveKPhys           WIN32_CALL(BOOL, GiveKPhys, (LPVOID ptr, ulong length))
#define InputDebugCharW     WIN32_CALL(int, InputDebugCharW, (void))
#define SetLowestScheduledPriority WIN32_CALL(DWORD, SetLowestScheduledPriority, (DWORD dwPrio))

#define UpdateNLSInfoEx     WIN32_CALL(void, UpdateNLSInfoEx, (DWORD ocp, DWORD acp, DWORD sysloc, DWORD userloc))
#define WriteRegistryToOEM  WIN32_CALL(BOOL, WriteRegistryToOEM, (DWORD dwFlags, LPBYTE pBuf, DWORD len))
#define ReadRegistryFromOEM WIN32_CALL(DWORD, ReadRegistryFromOEM, (DWORD dwFlags, LPBYTE pBuf, DWORD len))

#define GetStdioPathW       WIN32_CALL(BOOL, GetStdioPathW, (DWORD id, PWSTR pwszBuf, LPDWORD lpdwLen))
#define SetStdioPathW       WIN32_CALL(BOOL, SetStdioPathW, (DWORD id, LPCWSTR pwszPath))

#define SetHardwareWatch    WIN32_CALL(BOOL, SetHardwareWatch, (LPVOID vAddr, DWORD flags))
#define PrepareThreadExit   WIN32_CALL(void, PrepareThreadExit, (DWORD dwExitCode))

#define InterruptInitialize WIN32_CALL(BOOL, InterruptInitialize, (DWORD idInt, HANDLE hEvent, LPVOID pvData, DWORD cbData))
#define InterruptDisable    WIN32_CALL(void, InterruptDisable, (DWORD idInt))
#define InterruptDone       WIN32_CALL(void, InterruptDone, (DWORD idInt))
#define InterruptMask       WIN32_CALL(void, InterruptMask, (DWORD idInt, BOOL fDisable))

#define SetPowerHandler     WIN32_CALL(BOOL, SetPowerHandler, (FARPROC pfn, DWORD dwHndlerType))
#define PowerOffSystem      WIN32_CALL(void, PowerOffSystem, (void))

#define LoadIntChainHandler WIN32_CALL(HANDLE, LoadIntChainHandler, (LPCWSTR lpszFileName, LPCWSTR lpszFunctionName, BYTE bIRQ))
#define FreeIntChainHandler WIN32_CALL(BOOL, FreeIntChainHandler, (HANDLE hInstance))

#define GetExitCodeThread   WIN32_CALL(BOOL, GetExitCodeThread, (HANDLE hThread, LPDWORD lpretval))
#define GetExitCodeProcess  WIN32_CALL(BOOL, GetExitCodeProcess, (HANDLE hProcess, LPDWORD lpretval))

#define CreateStaticMapping WIN32_CALL(LPVOID, CreateStaticMapping, (DWORD dwPhysBase, DWORD dwSize))
#define DeleteStaticMapping WIN32_CALL(BOOL, DeleteStaticMapping, (LPVOID pVirtBase, DWORD dwSize))

#define SetDaylightTimeEx   WIN32_CALL(BOOL, SetDaylightTime, (DWORD dst, BOOL fUpdate))
#define SetTimeZoneBias     WIN32_CALL(BOOL, SetTimeZoneBias, (DWORD dwBias, DWORD dwDaylightBias))

#define THCreateSnapshot    WIN32_CALL(THSNAP *, THCreateSnapshot, (DWORD dwFlags, DWORD dwProcId))

#define WaitForDebugEvent   WIN32_CALL(BOOL, WaitForDebugEvent, (LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds))
#define ContinueDebugEvent  WIN32_CALL(BOOL, ContinueDebugEvent, (DWORD dwProcId, DWORD dwThreadId, DWORD dwContinueStatus))
#define DebugActiveProcess  WIN32_CALL(BOOL, DebugActiveProcess, (DWORD dwProcId))
#define DebugNotify         WIN32_CALL(void, DebugNotify, (DWORD dwFlags, DWORD data))
#define DebugSetProcessKillOnExit WIN32_CALL(BOOL, DebugSetProcessKillOnExit, (BOOL fKillOnExit))
#define DebugActiveProcessStop WIN32_CALL(BOOL, DebugActiveProcessStop, (DWORD dwProcId))

#define SetDbgZone          WIN32_CALL(BOOL, SetDbgZone, (DWORD pid, LPVOID lpvMod, LPVOID baseptr, DWORD zone, LPDBGPARAM lpdbgTgt))
#define RegisterDbgZones    WIN32_CALL(BOOL, RegisterDbgZones, (HMODULE hMod, LPDBGPARAM lpdbgparam))

#define NKCreateMsgQueue    WIN32_CALL(HANDLE, CreateMsgQueue, (LPCWSTR pQName, PMSGQUEUEOPTIONS lpOptions))

#define RemoteLocalAlloc    WIN32_CALL(HLOCAL, RemoteLocalAlloc, (UINT uFlags, UINT uBytes))
#define RemoteLocalReAlloc  WIN32_CALL(HLOCAL, RemoteLocalReAlloc, (HLOCAL hMem, UINT uBytes, UINT uFlags))
#define RemoteLocalSize     WIN32_CALL(UINT,   RemoteLocalSize, (HLOCAL hMem))
#define RemoteLocalFree     WIN32_CALL(HLOCAL, RemoteLocalFree, (HLOCAL hMem))

#define SystemMemoryLow     WIN32_CALL(void, SystemMemoryLow, (void))
#define PSLNotify           WIN32_CALL(void, PSLNotify, (DWORD dwReason, DWORD dwProcId, DWORD dwThrdId))

#define LoadKernelLibrary   WIN32_CALL(HANDLE, LoadKernelLibrary, (LPCWSTR lpszFileName))

#define CeLogData           WIN32_CALL(VOID, CeLogData, (BOOL fTimeStamp, DWORD dwID, PVOID pData, DWORD dwLen, DWORD dwZoneUser, DWORD dwZoneCE, DWORD dwFlag, BOOL fFlagged))
#define CeLogSetZones       WIN32_CALL(VOID, CeLogSetZones, (DWORD dwZoneUser, DWORD dwZoneCE, DWORD dwZoneProcess))
#define CeLogGetZones       WIN32_CALL(BOOL, CeLogGetZones, (LPDWORD lpdwZoneUser, LPDWORD lpdwZoneCE, LPDWORD lpdwZoneProcess, LPDWORD lpdwAvailableZones))
#define CeLogReSync         WIN32_CALL(BOOL, CeLogReSync, (void))
#define ProfileSyscall      WIN32_CALL(VOID, ProfileSyscall, (LPVOID, DWORD))

#define WaitForAPIReady     WIN32_CALL(DWORD, WaitForAPIReady, (DWORD dwAPISet, DWORD dwTimeout))

#define SetRAMMode          WIN32_CALL(BOOL, SetRAMMode, (BOOL bEnable, LPVOID *lplpvAddress, LPDWORD lpLength))
#define SetStoreQueueBase   WIN32_CALL(LPVOID, SetStoreQueueBase, (DWORD dwPhysPage))

#define NKWDCreate          WIN32_CALL(HANDLE, CreateWatchDog, (LPSECURITY_ATTRIBUTES lpsz, LPCWSTR pszWDName, DWORD dwDfltAct, DWORD dwParam, DWORD dwPeriod, DWORD dwWait, BOOL fCreate))

#define GetHandleServerId   WIN32_CALL(DWORD, GetHandleServerId, (HANDLE h))

#define AttachDebugger_Trap WIN32_CALL(BOOL, AttachDebugger, (LPCWSTR pszDbgrName))
#define ReadKernelPEHeader  WIN32_CALL(BOOL, ReadKPEHeader, (DWORD dwFlags, DWORD dwAddr, LPVOID pBuf, DWORD cbSize))
#define ForcePageout        WIN32_CALL(VOID, ForcePageout, (void))

#define CeSetDirectCall     WIN32_CALL (BOOL, SetDirectCall, (BOOL fKernel))
#define GetProcessVersion   WIN32_CALL (DWORD, GetProcessVersion, (DWORD dwId))

#define NKGetCPUInfo        WIN32_CALL (DWORD, NKGetCPUInfo, (DWORD dwProcessor, DWORD dwInfoType))
#define NKCPUPowerFunc      WIN32_CALL (BOOL, NKCPUPowerFunc, (DWORD dwProcessor, BOOL fOnOff, DWORD dwHint)) 
#define NKResetStack        WIN32_CALL (void, CeResetStack, (void))

#elif defined(COREDLL)

BOOL xxx_VirtualSetPageFlags(LPVOID lpvAddress, DWORD cbSize, DWORD dwFlags, LPDWORD lpdwOldFlags);
BOOL xxx_SetRAMMode(BOOL bEnable, LPVOID *lplpvAddress, LPDWORD lpLength);
#define SetRAMMode xxx_SetRAMMode
LPVOID xxx_SetStoreQueueBase(DWORD dwPhysPage);
#define SetStoreQueueBase xxx_SetStoreQueueBase

#define VirtualSetAttributes xxx_VirtualSetAttributes

void xxx_PrepareThreadExit (DWORD dwExitCode);
#define PrepareThreadExit xxx_PrepareThreadExit

LPBYTE xxx_CreateLocaleView(LPDWORD pdwSize);
#define CreateLocaleView xxx_CreateLocaleView
DWORD xxx_CeModuleJit(LPCWSTR, LPWSTR, HANDLE*);
#define CeModuleJit xxx_ModuleJit
int xxx_QueryAPISetID(char *pName);
#define QueryAPISetID xxx_QueryAPISetID
HANDLE WINAPI xxx_CreateEventW(LPSECURITY_ATTRIBUTES lpsa, BOOL bManualReset,BOOL bInitialState, LPCWSTR lpName);
#define CreateEventW xxx_CreateEventW
HANDLE WINAPI xxx_OpenEventW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName);
BOOL xxx_IsNamedEventSignaled (LPCWSTR pszName, DWORD dwFlags);
#define IsNamedEventSignaled xxx_IsNamedEventSignaled
#define OpenEventW xxx_OpenEventW
VOID WINAPI xxx_Sleep(DWORD dwMilliseconds);
#define Sleep xxx_Sleep
DWORD WINAPI xxx_WaitForMultipleObjects(DWORD cObjects, CONST HANDLE *lphObjects, BOOL fWaitAll, DWORD dwTimeout);
#define WaitForMultipleObjects xxx_WaitForMultipleObjects
DWORD WINAPI xxx_WaitForSingleObject(HANDLE hHandle,  DWORD dwMilliseconds);
#define WaitForSingleObject xxx_WaitForSingleObject
DWORD WINAPI xxx_SuspendThread(HANDLE hThread);
#define SuspendThread xxx_SuspendThread
DWORD WINAPI xxx_GetLastError();
#define GetLastError xxx_GetLastError
VOID WINAPI xxx_SetLastError(DWORD dwError);
#define SetLastError xxx_SetLastError
DWORD xxx_TlsCall(DWORD p1, DWORD p2);
#define TlsCall xxx_TlsCall
LPVOID WINAPI xxx_VirtualAlloc(LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect);
#define VirtualAlloc xxx_VirtualAlloc
BOOL WINAPI xxx_VirtualFree(LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType);
#define VirtualFree xxx_VirtualFree
BOOL WINAPI xxx_VirtualProtect(LPVOID lpAddress, DWORD dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
#define VirtualProtect xxx_VirtualProtect
DWORD WINAPI xxx_VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, DWORD dwLength);
#define VirtualQuery xxx_VirtualQuery
BOOL WINAPI xxx_LockPages(LPVOID lpvAddress, DWORD cbSize, PDWORD pPFNs, int fOptions);
#define LockPages xxx_LockPages
BOOL WINAPI xxx_UnlockPages(LPVOID lpvAddress, DWORD cbSize);
#define UnlockPages xxx_UnlockPages
BOOL xxx_DuplicateHandle(HANDLE hSrcProc, HANDLE hSrcHndl, HANDLE hDstProc, LPHANDLE lpDstHndl, DWORD dwAccess, BOOL bInherit, DWORD dwOptions);
#define DuplicateHandle xxx_DuplicateHandle
DWORD WINAPI xxx_GetTickCount();
#define GetTickCount xxx_GetTickCount
DWORD WINAPI xxx_GetProcessVersion(DWORD dwProcessId);
#define GetProcessVersion xxx_GetProcessVersion
DWORD WINAPI xxx_GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
#define GetModuleFileNameW xxx_GetModuleFileNameW
HMODULE WINAPI xxx_GetModuleHandleW(LPCWSTR lpModuleName);
#define GetModuleHandleW xxx_GetModuleHandleW
BOOL WINAPI xxx_QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
#define QueryPerformanceCounter xxx_QueryPerformanceCounter
BOOL WINAPI xxx_QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
#define QueryPerformanceFrequency xxx_QueryPerformanceFrequency
VOID WINAPI xxx_WriteDebugLED(WORD wIndex, DWORD dwPattern);
#define WriteDebugLED xxx_WriteDebugLED
BOOL WINAPI xxx_GetThreadTimes(HANDLE hThread, LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime);
#define GetThreadTimes xxx_GetThreadTimes
VOID WINAPI xxx_OutputDebugStringW(LPCWSTR lpOutputString);
#define OutputDebugStringW xxx_OutputDebugStringW
VOID WINAPI xxx_GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
#define GetSystemInfo xxx_GetSystemInfo
BOOL WINAPI xxx_QueryInstructionSet(DWORD dwInstructionSet, LPDWORD lpdwCurrentInstructionSet);
#define QueryInstructionSet xxx_QueryInstructionSet
BOOL WINAPI xxx_IsProcessorFeaturePresent(DWORD dwProcessorFeature);
#define IsProcessorFeaturePresent xxx_IsProcessorFeaturePresent
BOOL xxx_RegisterDbgZones(HMODULE hMod, LPDBGPARAM lpdbgparam);
#define RegisterDbgZones xxx_RegisterDbgZones
BOOL xxx_SetDaylightTime(DWORD dst);
#define SetDaylightTime xxx_SetDaylightTime
HANDLE xxx_CreateFileMappingW(HANDLE hFile, LPSECURITY_ATTRIBUTES lpsa, DWORD flProtect, DWORD dwMaxSizeHigh, DWORD dwMaxSizeLow, LPCWSTR lpName);
#define CreateFileMappingW xxx_CreateFileMappingW
HANDLE xxx_CreateFileForMappingW(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
#define CreateFileForMappingW xxx_CreateFileForMappingW
BOOL xxx_UnmapViewOfFile(LPVOID lpvAddr);
#define UnmapViewOfFile xxx_UnmapViewOfFile
BOOL xxx_FlushViewOfFile(LPCVOID lpBaseAddress, DWORD dwNumberOfBytesToFlush);
#define FlushViewOfFile xxx_FlushViewOfFile
BOOL xxx_FlushViewOfFileMaybe(LPCVOID lpBaseAddress, DWORD dwNumberOfBytesToFlush);
#define FlushViewOfFileMaybe xxx_FlushViewOfFileMaybe
BOOL xxx_KernelIoControl(DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned);
#define KernelIoControl xxx_KernelIoControl
HANDLE xxx_CreateMutexW(LPSECURITY_ATTRIBUTES lpsa, BOOL bInitialOwner, LPCTSTR lpName);
#define CreateMutexW xxx_CreateMutexW
HANDLE xxx_CreateSemaphoreW(LPSECURITY_ATTRIBUTES lpsa, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName);
#define CreateSemaphoreW xxx_CreateSemaphoreW
HANDLE xxx_CreateAPISet(char acName[4], USHORT cFunctions, const PFNVOID *ppfnMethods, const ULONGLONG *pu64Sig);
#define CreateAPISet xxx_CreateAPISet
BOOL xxx_VirtualCopy(LPVOID lpvDest, LPVOID lpvSrc, DWORD cbSize, DWORD fdwProtect);
#define VirtualCopy xxx_VirtualCopy

HLOCAL WINAPI xxx_RemoteLocalAlloc( UINT uFlags, UINT uBytes );
HLOCAL WINAPI xxx_RemoteLocalReAlloc( HLOCAL hMem, UINT uBytes, UINT uFlags );
UINT WINAPI xxx_RemoteLocalSize( HLOCAL hMem ); 
HLOCAL WINAPI xxx_RemoteLocalFree( HLOCAL hMem );

#define RemoteLocalAlloc    xxx_RemoteLocalAlloc
#define RemoteLocalReAlloc  xxx_RemoteLocalReAlloc
#define RemoteLocalSize     xxx_RemoteLocalSize
#define RemoteLocalFree     xxx_RemoteLocalFree

void WINAPI xxx_SystemMemoryLow (void);
#define SystemMemoryLow    xxx_SystemMemoryLow
void xxx_PSLNotify (DWORD dwReason, DWORD dwProcId, DWORD dwThrdId);
#define PSLNotify           xxx_PSLNotify

BOOL xxx_GetExitCodeThread (HANDLE hThread, LPDWORD lpExitCode);
#define GetExitCodeThread   xxx_GetExitCodeThread
BOOL xxx_GetExitCodeProcess (HANDLE hProcess, LPDWORD lpExitCode);
#define GetExitCodeProcess  xxx_GetExitCodeProcess

LPVOID xxx_CeVirtualSharedAlloc (LPVOID lpvAddr, DWORD cbSize, DWORD fdwAction);
#define CeVirtualSharedAlloc xxx_CeVirtualSharedAlloc

DWORD xxx_WaitForAPIReady (DWORD dwAPISet, DWORD dwTimeout);
#define WaitForAPIReady   xxx_WaitForAPIReady

int xxx_U_ropen(const WCHAR *fname, UINT mode);
#define U_ropen xxx_U_ropen
int xxx_U_rread(int fh, BYTE *buf, int len);
#define U_rread xxx_U_rread
int xxx_U_rwrite(int fh, BYTE *buf, int len);
#define U_rwrite xxx_U_rwrite
int xxx_U_rlseek(int fh, int pos, int type);
#define U_rlseek xxx_U_rlseek
int xxx_U_rclose(int fh);
#define U_rclose xxx_U_rclose
VOID xxx_NKvDbgPrintfW(LPCWSTR lpszFmt, va_list lpParms);
#define NKvDbgPrintfW xxx_NKvDbgPrintfW
DWORD xxx_GetCallStackSnapshot(ULONG dwMaxFrames, CallSnapshot lpFrames[], DWORD dwFlags, DWORD dwSkip);
#define GetCallStackSnapshot xxx_GetCallStackSnapshot
VOID xxx_CeLogData(BOOL fTimeStamp, WORD wID, PVOID pData, WORD wLen, DWORD dwZoneUser, DWORD dwZoneCE, WORD wFlag, BOOL bFlagged);
#define CeLogData xxx_CeLogData
VOID xxx_CeLogSetZones(DWORD dwZoneUser, DWORD dwZoneCE, DWORD dwZoneProcess);
#define CeLogSetZones xxx_CeLogSetZones
BOOL xxx_CeLogGetZones(LPDWORD lpdwZoneUser, LPDWORD lpdwZoneCE,
                       LPDWORD lpdwZoneProcess, LPDWORD lpdwAvailableZones);
#define CeLogGetZones xxx_CeLogGetZones
BOOL xxx_GetRomFileInfo(DWORD type, LPWIN32_FIND_DATA  lpfd, DWORD count);
#define GetRomFileInfo xxx_GetRomFileInfo
DWORD xxx_GetRomFileBytes(DWORD type, DWORD count, DWORD pos, LPVOID buffer, DWORD nBytesToRead);
#define GetRomFileBytes xxx_GetRomFileBytes
void xxx_CacheSync(int flags);
#define CacheSync xxx_CacheSync
void xxx_CacheRangeFlush (LPVOID pAddr, DWORD dwLength, DWORD dwFlags);
#define CacheRangeFlush xxx_CacheRangeFlush
BOOL xxx_AddTrackedItem(DWORD dwType, HANDLE handle, TRACKER_CALLBACK cb, DWORD dwProc, DWORD dwSize, DWORD dw1, DWORD dw2);
#define AddTrackedItem xxx_AddTrackedItem
BOOL xxx_DeleteTrackedItem(DWORD dwType, HANDLE handle);
#define DeleteTrackedItem xxx_DeleteTrackedItem
BOOL xxx_PrintTrackedItem(DWORD dwFlag, DWORD dwType, DWORD dwProcID, HANDLE handle);
#define PrintTrackedItem xxx_PrintTrackedItem
BOOL xxx_GetKPhys(void *ptr, ULONG length);
#define GetKPhys xxx_GetKPhys
BOOL xxx_GiveKPhys(void *ptr, ULONG length);
#define GiveKPhys xxx_GiveKPhys
DWORD xxx_RegisterTrackedItem(LPWSTR szName);
#define RegisterTrackedItem xxx_RegisterTrackedItem
VOID xxx_FilterTrackedItem(DWORD dwFlags, DWORD dwType, DWORD dwProcID);
#define FilterTrackedItem xxx_FilterTrackedItem
BOOL xxx_SetKernelAlarm(HANDLE hEvent, LPSYSTEMTIME lpst);
#define SetKernelAlarm xxx_SetKernelAlarm
void xxx_RefreshKernelAlarm(void);
#define RefreshKernelAlarm xxx_RefreshKernelAlarm
VOID xxx_SetOOMEvent(HANDLE hEvt, DWORD cpLow, DWORD cpCritical, DWORD cpLowBlockSize, DWORD cpCriticalBlockSize);
#define SetOOMEvent xxx_SetOOMEvent
VOID xxx_SetOOMEventEx(HANDLE hEvtLowMemoryState, HANDLE hEvtGoodMemoryState, DWORD cpLowMemEvent, DWORD cpLow, DWORD cpCritical, DWORD cpLowBlockSize, DWORD cpCriticalBlockSize);
#define SetOOMEventEx xxx_SetOOMEventEx
DWORD xxx_StringCompress(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout);
#define StringCompress xxx_StringCompress
DWORD xxx_StringDecompress(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout);
#define StringDecompress xxx_StringDecompress
DWORD xxx_BinaryCompress(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout);
#define BinaryCompress xxx_BinaryCompress
DWORD xxx_BinaryDecompress(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout, DWORD skip);
#define BinaryDecompress xxx_BinaryDecompress
DWORD xxx_DecompressBinaryBlock(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout);
#define DecompressBinaryBlock xxx_DecompressBinaryBlock
int xxx_InputDebugCharW(VOID);
#define InputDebugCharW xxx_InputDebugCharW
LPVOID xxx_MapPtrToProcess(LPVOID lpv, HANDLE hProc);
#define MapPtrToProcess xxx_MapPtrToProcess
LPVOID xxx_MapPtrUnsecure(LPVOID lpv, HANDLE hProc);
#define MapPtrUnsecure xxx_MapPtrUnsecure
HANDLE xxx_GetProcFromPtr(LPVOID lpv);
#define GetProcFromPtr xxx_GetProcFromPtr
BOOL xxx_IsBadPtr(DWORD flags, LPBYTE ptr, UINT length);
#define IsBadPtr xxx_IsBadPtr
DWORD xxx_GetProcAddrBits(HANDLE hProc);
#define GetProcAddrBits xxx_GetProcAddrBits
DWORD xxx_GetFSHeapInfo(void);
#define GetFSHeapInfo xxx_GetFSHeapInfo
HANDLE xxx_GetOwnerProcess(void);
#define GetOwnerProcess xxx_GetOwnerProcess
DWORD xxx_GetDirectCallerProcessId(void);
#define GetDirectCallerProcessId xxx_GetDirectCallerProcessId
DWORD xxx_GetCallerVMProcessId(void);
#define GetCallerVMProcessId xxx_GetCallerVMProcessId
HANDLE xxx_GetCallerProcess (void);
#define GetCallerProcess xxx_GetCallerProcess
DWORD xxx_GetIdleTime(void);
#define GetIdleTime xxx_GetIdleTime
DWORD xxx_SetLowestScheduledPriority(DWORD maxprio);
#define SetLowestScheduledPriority xxx_SetLowestScheduledPriority
DWORD xxx_SetProcPermissions(DWORD perms);
#define SetProcPermissions xxx_SetProcPermissions
DWORD xxx_GetCurrentPermissions(void);
#define GetCurrentPermissions xxx_GetCurrentPermissions
DWORD xxx_CeGetCurrentTrust(void);
#define CeGetCurrentTrust xxx_CeGetCurrentTrust
DWORD xxx_CeGetCallerTrust(void);
#define CeGetCallerTrust xxx_CeGetCallerTrust
BOOL xxx_SetTimeZoneBias(DWORD dwBias, DWORD dwDaylightBias);
#define SetTimeZoneBias xxx_SetTimeZoneBias
void xxx_SetCleanRebootFlag(void);
#define SetCleanRebootFlag xxx_SetCleanRebootFlag
void xxx_PowerOffSystem(void);
#define PowerOffSystem xxx_PowerOffSystem
BOOL xxx_SetDbgZone(DWORD pid, LPVOID lpvMod, LPVOID baseptr, DWORD zone, LPDBGPARAM lpdbgTgt);
#define SetDbgZone xxx_SetDbgZone
VOID xxx_TurnOnProfiling(HANDLE hThread);
#define TurnOnProfiling xxx_TurnOnProfiling
VOID xxx_TurnOffProfiling(HANDLE hThread);
#define TurnOffProfiling xxx_TurnOffProfiling
#define xxx_SetHandleOwner +++ Do Not Use +++
BOOL xxx_SetHandleOwnerWorkaround (HANDLE *ph, HANDLE hProc);
HANDLE xxx_LoadIntChainHandler(LPCTSTR lpszFileName, LPCTSTR lpszFunctionName, BYTE bIRQ);
#define LoadIntChainHandler xxx_LoadIntChainHandler
BOOL xxx_FreeIntChainHandler(HANDLE hInstance, LPCTSTR lpszFunctionName, BYTE bIRQ);
#define FreeIntChainHandler xxx_FreeIntChainHandler
HANDLE xxx_LoadKernelLibrary(LPCWSTR lpszFileName);
#define LoadKernelLibrary xxx_LoadKernelLibrary
BOOL xxx_InterruptInitialize(DWORD idInt, HANDLE hEvent, LPVOID pvData, DWORD cbData);
#define InterruptInitialize xxx_InterruptInitialize
void xxx_InterruptMask(DWORD idInt, BOOL fDisable);
#define InterruptMask xxx_InterruptMask
void xxx_InterruptDone(DWORD idInt);
#define InterruptDone xxx_InterruptDone
void xxx_InterruptDisable(DWORD idInt);
#define InterruptDisable xxx_InterruptDisable
DWORD xxx_SetKMode(DWORD mode);
#define SetKMode xxx_SetKMode
BOOL xxx_SetPowerOffHandler(FARPROC pfn);
#define SetPowerOffHandler xxx_SetPowerOffHandler
BOOL xxx_SetGwesPowerHandler(FARPROC pfn);
#define SetGwesPowerHandler xxx_SetGwesPowerHandler
BOOL xxx_SetHardwareWatch(LPVOID vAddr, DWORD flags);
#define SetHardwareWatch xxx_SetHardwareWatch
void xxx_PPSHRestart(void);
#define PPSHRestart xxx_PPSHRestart
void xxx_DebugNotify(DWORD dwFlags, DWORD data);
#define DebugNotify xxx_DebugNotify
DWORD xxx_GetCallerProcessIndex(void);
#define GetCallerProcessIndex xxx_GetCallerProcessIndex
BOOL xxx_WaitForDebugEvent(LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds);
#define WaitForDebugEvent xxx_WaitForDebugEvent
BOOL xxx_ContinueDebugEvent(DWORD dwProcessId, DWORD dwThreadId, DWORD dwContinueStatus);
#define ContinueDebugEvent xxx_ContinueDebugEvent
BOOL xxx_DebugActiveProcess(DWORD dwProcessId);
#define DebugActiveProcess xxx_DebugActiveProcess
HANDLE xxx_OpenProcess(DWORD fdwAccess, BOOL fInherit, DWORD IDProcess);
#define OpenProcess xxx_OpenProcess
HANDLE xxx_OpenThread (DWORD fdwAccess, BOOL fInherit, DWORD IDThread);
#define OpenThread xxx_OpenThread
void xxx_DumpKCallProfile(DWORD bReset);
#define DumpKCallProfile xxx_DumpKCallProfile
THSNAP * xxx_THCreateSnapshot(DWORD dwFlags, DWORD dwProcID);
#define THCreateSnapshot xxx_THCreateSnapshot
void xxx_NotifyForceCleanboot(void);
#define NotifyForceCleanboot xxx_NotifyForceCleanboot
BOOL WINAPI xxx_CreateProcessW(LPCWSTR lpszImageName, LPCWSTR lpszCommandLine, LPSECURITY_ATTRIBUTES lpsaProcess, LPSECURITY_ATTRIBUTES lpsaThread, BOOL fInheritHandles, DWORD fdwCreate, LPVOID lpvEnvironment, LPWSTR lpszCurDir, LPSTARTUPINFO lpsiStartInfo, LPPROCESS_INFORMATION lppiProcInfo);
#define CreateProcessW xxx_CreateProcessW
BOOL WINAPI xxx_CeCreateProcessEx(LPCWSTR lpszImageName, LPCWSTR lpszCommandLine, LPCE_PROCESS_INFORMATION lpCeProcInfo);
#define CeCreateProcessEx xxx_CeCreateProcessEx
HANDLE WINAPI xxx_CreateThread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, LPTHREAD_START_ROUTINE lpStartAddr, LPVOID lpvThreadParm, DWORD fdwCreate, LPDWORD lpIDThread);
#define CreateThread xxx_CreateThread
BOOL xxx_TerminateThread(HTHREAD  hThread,DWORD   dwExitcode );
#define TerminateThread xxx_TerminateThread
BOOL xxx_SetStdioPathW(DWORD id, LPCWSTR pwszPath);
#define SetStdioPathW xxx_SetStdioPathW
BOOL xxx_GetStdioPathW(DWORD id, PWSTR pwszBuf, LPDWORD lpdwLen);
#define GetStdioPathW xxx_GetStdioPathW
DWORD xxx_ReadRegistryFromOEM(DWORD dwFlags, LPBYTE pBuf, DWORD len);
#define ReadRegistryFromOEM xxx_ReadRegistryFromOEM
BOOL xxx_WriteRegistryToOEM(DWORD dwFlags, LPBYTE pBuf, DWORD len);
#define WriteRegistryToOEM xxx_WriteRegistryToOEM
__int64 xxx_CeGetRandomSeed(void);
#define CeGetRandomSeed xxx_CeGetRandomSeed
void xxx_UpdateNLSInfo(DWORD ocp, DWORD acp, DWORD locale);
#define UpdateNLSInfo xxx_UpdateNLSInfo
void xxx_UpdateNLSInfoEx(DWORD ocp, DWORD acp, DWORD sysloc, DWORD userloc);
#define UpdateNLSInfoEx xxx_UpdateNLSInfoEx
DWORD xxx_GetProcessIndexFromID(HANDLE hProcess);
#define GetProcessIndexFromID xxx_GetProcessIndexFromID
HANDLE xxx_GetProcessIDFromIndex(DWORD dwIdx);
#define GetProcessIDFromIndex xxx_GetProcessIDFromIndex

/* stubbed out in coredll - not used in CE7 */
HANDLE xxx_CeCreateToken (LPVOID psi, DWORD dwFlags);
BOOL  xxx_CeRevertToSelf (void);
BOOL  xxx_CeImpersonateCurrentProcess (void);
BOOL xxx_CeAccessCheck (LPVOID pSecDesc, HANDLE hTok, DWORD dwDesiredAccess);
BOOL xxx_CeGetAccessMask (LPVOID pSecDesc, HANDLE hTok, LPDWORD pdwMaxAccessMask);
BOOL xxx_CePrivilegeCheck (HANDLE hTok, LPDWORD pPrivs, int nPrivs);
BOOL xxx_CeGetOwnerAccount (HANDLE hTok, PACCTID pAcctId, DWORD ccbAcctId);
BOOL xxx_CeGetGroupAccount (HANDLE hTok, DWORD idx, PACCTID pAcctId, DWORD ccbAcctId, LPDWORD pCountGroups);
BOOL xxx_CeSerializeTokenData (HANDLE hTok, LPVOID lpTokenData, LPDWORD lpcbTokenData);
BOOL xxx_CeDeserializeTokenData (LPVOID lpTokenData, DWORD cbTokenData, LPHANDLE lphToken);

BOOL WINAPI xxx_DebugSetProcessKillOnExit (BOOL fKillOnExit);
#define DebugSetProcessKillOnExit xxx_DebugSetProcessKillOnExit
BOOL WINAPI xxx_DebugActiveProcessStop (DWORD dwProcId);
#define DebugActiveProcessStop xxx_DebugActiveProcessStop

HRESULT xxx_CeOpenCallerBuffer(PVOID* ppDestMarshalled, PVOID pSrcUnmarshalled,
    DWORD cbSrc, DWORD ArgumentDescriptor, BOOL ForceDuplicate);
#define CeOpenCallerBuffer  xxx_CeOpenCallerBuffer

HRESULT xxx_CeCloseCallerBuffer(PVOID pDestMarshalled, PVOID pSrcUnmarshalled,
    DWORD cbSrc, DWORD  ArgumentDescriptor);
#define CeCloseCallerBuffer  xxx_CeCloseCallerBuffer

HRESULT xxx_CeAllocAsynchronousBuffer(PVOID* ppDestAsyncMarshalled,
    PVOID pSrcSyncMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
#define CeAllocAsynchronousBuffer  xxx_CeAllocAsynchronousBuffer

HRESULT xxx_CeFreeAsynchronousBuffer(PVOID pDestAsyncMarshalled,
    PVOID pSrcSyncMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
#define CeFreeAsynchronousBuffer  xxx_CeFreeAsynchronousBuffer

HRESULT xxx_CeAllocDuplicateBuffer(PVOID* ppDestDuplicate, PVOID pSrcMarshalled,
    DWORD cbSrc, DWORD ArgumentDescriptor);
#define CeAllocDuplicateBuffer xxx_CeAllocDuplicateBuffer

HRESULT xxx_CeFreeDuplicateBuffer(PVOID pDestDuplicate, PVOID pSrcMarshalled,
    DWORD cbSrc, DWORD ArgumentDescriptor);
#define CeFreeDuplicateBuffer xxx_CeFreeDuplicateBuffer

BOOL xxx_CeCallUserProc(LPCWSTR pszDllName, LPCWSTR pszFuncName, 
    LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned);
#define CeCallUserProc xxx_CeCallUserProc

#endif // WIN32_CALL

#define ReadProcessMemory       +++ Do Not Use +++
#define WriteProcessMemory       +++ Do Not Use +++

#ifdef KCOREDLL

    
#define _DIRECT_THREAD_CALL(err, nargs, rt, id, argt, arglist)      _DIRECT_HANDLE_CALL (rt, SH_CURTHREAD,  ID_THREAD_##id, err, argt, nargs, arglist)
#define _DIRECT_PROCESS_CALL(err, nargs, rt, id, argt, arglist)     _DIRECT_HANDLE_CALL (rt, SH_CURPROC,    ID_PROC_##id, err, argt, nargs, arglist)
#define _DIRECT_EVENT_CALL(err, nargs, rt, id, argt, arglist)       _DIRECT_HANDLE_CALL (rt, HT_EVENT,      ID_EVENT_##id, err, argt, nargs, arglist)
#define _DIRECT_MUTEX_CALL(err, nargs, rt, id, argt, arglist)       _DIRECT_HANDLE_CALL (rt, HT_MUTEX,      ID_MUTEX_##id, err, argt, nargs, arglist)

#define _DIRECT_APISET_CALL(err, nargs, rt, id, argt, arglist)      _DIRECT_HANDLE_CALL (rt, HT_APISET,     ID_APISET_##id, err, argt, nargs, arglist)
#define _DIRECT_SEMAPHORE_CALL(err, nargs, rt, id, argt, arglist)   _DIRECT_HANDLE_CALL (rt, HT_SEMAPHORE,  ID_SEMAPHORE_##id, err, argt, nargs, arglist)


// kernel mode 'kcoredll'
// handle call direct

// THREAD calls
#define KernelSuspendThread(h, pof)             _DIRECT_THREAD_CALL ((DWORD)-1, 1, BOOL, SUSPEND,         (HANDLE, LPDWORD), (h, pof))
#define ResumeThread(h, pof)                    _DIRECT_THREAD_CALL ((DWORD)-1, 1, BOOL, RESUME,          (HANDLE, LPDWORD), (h, pof))
#define GetThreadPriority(h, pof)               _DIRECT_THREAD_CALL (THREAD_PRIORITY_ERROR_RETURN, 1, BOOL, GETTHREADPRIO, (HANDLE, LPDWORD), (h, pof))
#define SetThreadPriority(h, pri)               _DIRECT_THREAD_CALL (FALSE, 1, BOOL, SETTHREADPRIO, (HANDLE, DWORD),    (h, pri))
#define GetThreadContext(h, pctx)               _DIRECT_THREAD_CALL (FALSE, 1, BOOL, GETCONTEXT,    (HANDLE, PCONTEXT), (h, pctx))
#define SetThreadContext(h, pctx)               _DIRECT_THREAD_CALL (FALSE, 1, BOOL, SETCONTEXT,    (HANDLE, const CONTEXT *), (h, pctx))
#define NKKillThread(h, code, fWait)            _DIRECT_THREAD_CALL (FALSE, 2, BOOL, TERMINATE,     (HANDLE, DWORD, DWORD), (h, code, fWait))

#define CeGetThreadPriority(h, pof)             _DIRECT_THREAD_CALL (THREAD_PRIORITY_ERROR_RETURN, 1, BOOL, CEGETPRIO, (HANDLE, LPDWORD), (h, pof))
#define CeSetThreadPriority(h, pri)             _DIRECT_THREAD_CALL (FALSE, 1, BOOL, CESETPRIO,     (HANDLE, DWORD),    (h, pri))

#define CeGetThreadQuantum(h, pof)              _DIRECT_THREAD_CALL (MAXDWORD, 1, BOOL, CEGETQUANT,(HANDLE, LPDWORD), (h, pof))
#define CeSetThreadQuantum(h, q)                _DIRECT_THREAD_CALL (FALSE, 1, BOOL, CESETQUANT, (HANDLE, DWORD), (h, q))

#define GetThreadId(h)                          _DIRECT_THREAD_CALL (0, 0, DWORD, GETID, (HANDLE), (h))
#define GetProcessIdOfThread(h)                 _DIRECT_THREAD_CALL (0, 0, DWORD, GETPROCID, (HANDLE), (h))


#define GetThreadCallStack(h, n, p,f, s)        _DIRECT_THREAD_CALL (0, 4, DWORD, GETCALLSTACK, (HANDLE, ULONG, LPVOID, DWORD, DWORD), (h, n, p, f, s))
#define NKGetThreadAffinity(h, pa)              _DIRECT_THREAD_CALL (FALSE, 1, BOOL, GETAFFINITY, (HANDLE, LPDWORD), (h, pa))
#define NKSetThreadAffinity(h, a)               _DIRECT_THREAD_CALL (FALSE, 1, BOOL, SETAFFINITY, (HANDLE, DWORD), (h, a))

// PROCESS calls
#define TerminateProcess(h, code)               _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, TERMINATE,    (HANDLE, DWORD), (h, code))
#define FlushInstructionCache(h, p, s)          _DIRECT_PROCESS_CALL (FALSE, 2, BOOL, FLUSHICACHE,  (HANDLE, LPCVOID, DWORD), (h, p, s))
#define CeGetModuleInfo(h, p, t, pb, cb)        _DIRECT_PROCESS_CALL (FALSE, 4, BOOL, GETMODINFO,   (HANDLE, LPCVOID, DWORD, LPVOID, DWORD), (h, p, t, pb, cb))
#define CeSetProcessVersion(h, v)               _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, SETVER,       (HANDLE, DWORD), (h, v))
#define GetModuleName(h, hm, rname, cch)        _DIRECT_PROCESS_CALL (FALSE, 3, BOOL, GETMODNAME,   (HANDLE, HANDLE, LPWSTR, DWORD), (h, hm, rname, cch))
#define GetModHandle(h, name, flags)            _DIRECT_PROCESS_CALL (NULL,  2, HMODULE, GETMODHNDL, (HANDLE, LPCWSTR, DWORD), (h, name, flags))
#define ReadPEHeader(h, f, a, p, cb)            _DIRECT_PROCESS_CALL (RP_RESULT_FAILED, 4, DWORD, READPEHEADER, (HANDLE, DWORD, DWORD, LPVOID, DWORD), (h, f, a, p, cb))
#define CheckRemoteDebuggerPresent(h, p)        _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, CHECKREMOTEDEBUGGERPRESENT, (HANDLE, PBOOL), (h, p))
#define PageOutModule(h, hm, flags)             _DIRECT_PROCESS_CALL (FALSE, 2, BOOL, PAGEOUTMODULE, (HANDLE, HANDLE, DWORD), (h, hm, flags))

#define VirtualAllocEx(h, p, cb, t, f, pt)      _DIRECT_PROCESS_CALL (NULL, 5, LPVOID, VMALLOC, (HANDLE, LPVOID, DWORD, DWORD, DWORD, PDWORD), (h, p, cb, t, f, pt))
#define VirtualFreeEx(h, p, cb, t, u)           _DIRECT_PROCESS_CALL (FALSE, 4, BOOL, VMFREE,  (HANDLE, LPVOID, DWORD, DWORD, DWORD), (h, p, cb, t, u))
#define VirtualQueryEx(h, p, pmi, cb)           _DIRECT_PROCESS_CALL (FALSE, 3, BOOL, VMQUERY, (HANDLE, LPCVOID, PMEMORY_BASIC_INFORMATION, DWORD), (h, p, pmi, cb))
#define VirtualProtectEx(h, p, cb, f, pof)      _DIRECT_PROCESS_CALL (FALSE, 4, BOOL, VMPROTECT, (HANDLE, LPCVOID, DWORD, DWORD, LPDWORD), (h, p, cb, f, pof))
#define VirtualCopyEx(h, p, hs, ps, cb, f)      _DIRECT_PROCESS_CALL (FALSE, 5, BOOL, VMCOPY, (HANDLE, LPVOID, HANDLE, LPVOID, DWORD, DWORD), (h, p, hs,ps, cb, f))
#define VirtualSetAttributesEx(h, p, cb, f, m, pof)  _DIRECT_PROCESS_CALL (FALSE, 5, BOOL, VMSETATTR, (HANDLE, LPVOID, DWORD, DWORD, DWORD, LPDWORD), (h, p, cb, f, m, pof))
#define VirtualAllocCopyEx(h, h2, p, cb, f)     _DIRECT_PROCESS_CALL (NULL,  4, LPVOID, VMALLOCCOPY, (HANDLE, HANDLE, LPVOID, DWORD, DWORD), (h, h2, p, cb, f))
#define LockPagesEx(h, p, cb, pfn, f)           _DIRECT_PROCESS_CALL (FALSE, 4, BOOL, VMLOCK, (HANDLE, LPVOID, DWORD, LPDWORD, DWORD), (h, p, cb, pfn, f))
#define UnlockPagesEx(h, p, cb)                 _DIRECT_PROCESS_CALL (FALSE, 2, BOOL, VMUNLOCK, (HANDLE, LPVOID, DWORD), (h, p, cb))
#define INT_ReadMemory(h, a, p, cb)             _DIRECT_PROCESS_CALL (FALSE, 3, BOOL, READMEMORY, (HANDLE, LPCVOID, LPVOID, DWORD), (h, a, p, cb))
#define INT_WriteMemory(h, a, p, cb)            _DIRECT_PROCESS_CALL (FALSE, 3, BOOL, WRITEMEMORY, (HANDLE, LPCVOID, LPVOID, DWORD), (h, a, p, cb))
#define AllocPhysMemEx(h, cb, fp, aln, f, pfn)  _DIRECT_PROCESS_CALL (NULL, 5, LPVOID, VMALLOCPHYS, (HANDLE, DWORD, DWORD, DWORD, DWORD, LPDWORD), (h, cb, fp, aln, f, pfn))

#define CloseHandleInProc(hproc, h)             _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, HNDLCLOSE, (HANDLE, HANDLE), (hproc, h))

#define UnmapViewInProc(h, v)                   _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, UNMAPVIEW, (HANDLE, LPCVOID), (h, v))
#define MapViewInProc(h, hmap, ac, oh, ol, cb)  _DIRECT_PROCESS_CALL (NULL, 5, LPVOID, MAPVIEW, (HANDLE, HANDLE, DWORD, DWORD, DWORD, DWORD), (h, hmap, ac, oh, ol, cb))
#define FlushViewInProc(h, v, cb)               _DIRECT_PROCESS_CALL (FALSE, 2, BOOL, FLUSHVIEW, (HANDLE, LPCVOID, DWORD), (h, v, cb))
#define CreateFileMappingInProc(h, hf, sa, f, mh, ml, name) _DIRECT_PROCESS_CALL (NULL, 6, HANDLE, MAPCREATE, (HANDLE, HANDLE, LPSECURITY_ATTRIBUTES, DWORD, DWORD, DWORD, LPCWSTR), (h, hf, sa, f, mh, ml, name))

#define NKOpenMsgQueueEx(h, hq, hprcdst, po)    _DIRECT_PROCESS_CALL (NULL, 3, HANDLE, OPENMSGQEX, (HANDLE hSrcPrc, HANDLE, HANDLE, PMSGQUEUEOPTIONS), (h, hq, hprcdst, po))

#define GetProcessId(h)                         _DIRECT_PROCESS_CALL (0, 0, BOOL, GETPROCID,  (HANDLE), (h))

#define NKGetProcessAffinity(h, pa)             _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, GETAFFINITY, (HANDLE, LPDWORD), (h, pa))
#define NKSetProcessAffinity(h, a)              _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, SETAFFINITY, (HANDLE, DWORD), (h, a))
#define CeLoadLibraryInProcess(h, name)         _DIRECT_PROCESS_CALL (FALSE, 1, BOOL, LOADMODULE, (HANDLE, LPCWSTR), (h, name))

#define CeMapUserAddressesToVoid(h, p, cb)      _DIRECT_PROCESS_CALL (FALSE, 2, BOOL, MAPADDRTOVOID, (HANDLE, LPVOID, DWORD), (h, p, cb))

#define GetProcessTimes(h, pt1, pt2, pt3, pt4)  _DIRECT_PROCESS_CALL (FALSE, 4, BOOL, GETTIMES, (HANDLE, LPFILETIME, LPFILETIME, LPFILETIME, LPFILETIME), (h, pt1, pt2, pt3, pt4))

// EVENT calls
#define EventModify(h, fnc)                     _DIRECT_EVENT_CALL (FALSE, 1, BOOL, MODIFY, (HANDLE, DWORD), (h, fnc))
#define EventGetData(h)                         _DIRECT_EVENT_CALL (0,     0, DWORD, GETDATA, (HANDLE), (h))
#define EventSetData(h, d)                      _DIRECT_EVENT_CALL (FALSE, 1, BOOL, SETDATA, (HANDLE, DWORD), (h, d))
#define NKReadMsgQueueEx(h, p, cb, pcbr, t, pf, ph) _DIRECT_EVENT_CALL (FALSE, 6, BOOL, READMSGQ, (HANDLE, LPVOID, DWORD, LPDWORD, DWORD, LPDWORD, PHANDLE), (h, p, cb, pcbr, t, pf, ph))
#define NKWriteMsgQueue(h, p, cb, t, f)         _DIRECT_EVENT_CALL (FALSE, 4, BOOL, WRITEMSGQ, (HANDLE, LPCVOID, DWORD, DWORD, DWORD), (h, p, cb, t, f))
#define NKGetMsgQueueInfo(h, p)                 _DIRECT_EVENT_CALL (FALSE, 1, BOOL, GETMSGQINFO, (HANDLE, PMSGQUEUEINFO), (h, p))
#define NKResumeMainThread(h, p)                _DIRECT_EVENT_CALL (FALSE, 1, BOOL, RESUMEMAINTH, (HANDLE, LPDWORD), (h, p))

#define NKWDStart(h)                            _DIRECT_EVENT_CALL (FALSE, 0, DWORD, WDSTART, (HANDLE), (h))
#define NKWDStop(h)                             _DIRECT_EVENT_CALL (FALSE, 0, DWORD, WDSTOP, (HANDLE), (h))
#define NKWDRefresh(h)                          _DIRECT_EVENT_CALL (FALSE, 0, DWORD, WDREFRESH, (HANDLE), (h))

// APISET calls
#define RegisterAPISet(h, id)                            _DIRECT_APISET_CALL (FALSE, 1, BOOL, REGISTER, (HANDLE, DWORD), (h, id))
#define CreateAPIHandle(h, pobj)                         _DIRECT_APISET_CALL (NULL, 1, HANDLE, CREATEHANDLE, (HANDLE, LPVOID), (h, pobj))
#define CreateAPIHandleWithAccess(h, pobj, acc, htgt)    _DIRECT_APISET_CALL (NULL, 3, HANDLE, CREATEHANDLEWITHACCESS, (HANDLE, LPVOID, DWORD, HANDLE), (h, pobj, acc, htgt))
#define VerifyAPIHandle(h, hapi)                         _DIRECT_APISET_CALL (NULL, 1, LPVOID, VERIFY, (HANDLE, HANDLE), (h, hapi))
#define RegisterDirectMethods(h, ppfn)                   _DIRECT_APISET_CALL (FALSE, 1, BOOL, REGDIRECTMTHD, (HANDLE, const PFNVOID *), (h, ppfn))
#define CeRegisterAccessMask(h, lprg, cnt)               _DIRECT_APISET_CALL (FALSE, 2, BOOL, REGACCESSMASK, (HANDLE, LPDWORD, DWORD), (h, lprg, cnt))
#define LockAPIHandle(hSet, hProc, h, ppobj)             _DIRECT_APISET_CALL (NULL, 3, HANDLE, LOCKAPIHANDLE, (HANDLE, HANDLE, HANDLE, LPVOID *), (hSet, hProc, h, ppobj))
#define UnlockAPIHandle(hSet, hLock)                     _DIRECT_APISET_CALL (FALSE, 1, BOOL, UNLOCKAPIHANDLE, (HANDLE, HANDLE), (hSet, hLock))
#define SetAPIErrorHandler(h, api)                       _DIRECT_APISET_CALL (FALSE, 1, BOOL, SETAPIERRORHANDLER, (HANDLE, PFNAPIERRHANDLER), (h, api))

// MUTEX calls
#define ReleaseMutex(h)                         _DIRECT_MUTEX_CALL (FALSE, 0, BOOL, RELEASEMUTEX, (HANDLE), (h))

// SEMPAHORE calls
#define ReleaseSemaphore(h, cnt, pprev)         _DIRECT_SEMAPHORE_CALL (FALSE, 2, BOOL, RELEASESEMAPHORE, (HANDLE, DWORD, LPLONG), (h, cnt, pprev))


#else

// user-mode coredll

// THREAD calls
#define KernelSuspendThread _THREAD_CALL(BOOL, SUSPEND, (HANDLE hThread, LPDWORD lpRetVal))
#ifdef COREDLL
DWORD WINAPI xxx_SuspendThread(HANDLE hThread);
#define SuspendThread xxx_SuspendThread
#endif

#define ResumeThread        _THREAD_CALL(BOOL, RESUME, (HANDLE hThread, LPDWORD lpRetVal))
#define GetThreadPriority   _THREAD_CALL(BOOL, GETTHREADPRIO, (HANDLE hThread, LPDWORD lpRetVal))
#define SetThreadPriority   _THREAD_CALL(BOOL, SETTHREADPRIO, (HANDLE hThread, int nPriority))
#define GetThreadContext    _THREAD_CALL(BOOL, GETCONTEXT, (HANDLE hThread, LPCONTEXT lpContext))
#define SetThreadContext    _THREAD_CALL(BOOL, SETCONTEXT, (HANDLE hThread, CONST CONTEXT *lpContext))
#define NKKillThread        _THREAD_CALL(BOOL, TERMINATE, (HANDLE hThread, DWORD dwExitCode, BOOL fWait))

#define CeGetThreadPriority _THREAD_CALL(BOOL, CEGETPRIO, (HANDLE hThread, LPDWORD lpRetVal))
#define CeSetThreadPriority _THREAD_CALL(BOOL, CESETPRIO, (HANDLE hThread, int nPriority))
#define CeGetThreadQuantum  _THREAD_CALL(BOOL, CEGETQUANT, (HANDLE hThread, LPDWORD lpRetVal))
#define CeSetThreadQuantum  _THREAD_CALL(BOOL, CESETQUANT, (HANDLE hThread, DWORD dwTime))

#define GetThreadId          _THREAD_CALL(DWORD, GETID, (HANDLE hThread))
#define GetProcessIdOfThread _THREAD_CALL(DWORD, GETPROCID, (HANDLE hThread))

#define GetThreadCallStack  _THREAD_CALL(ULONG, GETCALLSTACK, (HANDLE hThread, ULONG dwMaxFrames, LPVOID lpFrames, DWORD dwFlags, DWORD dwSkip))

#define NKGetThreadAffinity _THREAD_CALL (BOOL, GETAFFINITY, (HANDLE hThread, LPDWORD pdwAffinity))
#define NKSetThreadAffinity _THREAD_CALL (BOOL, SETAFFINITY, (HANDLE hThread, DWORD dwAffinity))

// PROCESS calls
#define TerminateProcess        _PROCESS_CALL(BOOL, TERMINATE, (HANDLE hProc, DWORD dwExitCode))
#define FlushInstructionCache   _PROCESS_CALL(BOOL, FLUSHICACHE, (HANDLE hProc, LPCVOID lpBaseAddress, DWORD dwSize))
#define INT_ReadMemory          _PROCESS_CALL(BOOL, READMEMORY, (HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize))
#define INT_WriteMemory         _PROCESS_CALL(BOOL, WRITEMEMORY, (HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize))
#define CeGetModuleInfo         _PROCESS_CALL(BOOL, GETMODINFO, (HANDLE hProcess, LPCVOID pBaseAddr, DWORD infotype, LPVOID pbuf, DWORD cb))
#define CeSetProcessVersion     _PROCESS_CALL(BOOL, SETVER, (HANDLE hProcess, DWORD dwVersion))
#define VirtualAllocEx          _PROCESS_CALL(LPVOID, VMALLOC, (HANDLE hProcess, LPVOID pAddr, DWORD cbSize, DWORD fAllocType, DWORD fProtect, PDWORD pdwTag))
#define VirtualFreeEx           _PROCESS_CALL(BOOL, VMFREE, (HANDLE hProcess, LPVOID pAddr, DWORD cbSize, DWORD fFreeType, DWORD dwTag))
#define VirtualQueryEx          _PROCESS_CALL(DWORD, VMQUERY, (HANDLE hProcess, LPCVOID lpvaddr, PMEMORY_BASIC_INFORMATION pmi, DWORD dwLength))
#define VirtualProtectEx        _PROCESS_CALL(BOOL, VMPROTECT, (HANDLE hProcess, LPVOID lpvaddr, DWORD cbSize, DWORD fNewProtect, LPDWORD pfOldProtect))
#define VirtualCopyEx           _PROCESS_CALL(BOOL, VMCOPY, (HANDLE hDst, LPVOID pDstAddr, HANDLE hSrc, LPVOID pSrcAddr, DWORD cbSize, DWORD fProtect))
#define LockPagesEx             _PROCESS_CALL(BOOL, VMLOCK, (HANDLE hProc, LPVOID lpvaddr, DWORD cbSize, LPDWORD pPFNs, DWORD fOptions))
#define UnlockPagesEx           _PROCESS_CALL(BOOL, VMUNLOCK, (HANDLE hProc, LPVOID lpvaddr, DWORD cbSize))
#define CloseHandleInProc       _PROCESS_CALL(BOOL, HNDLCLOSE, (HANDLE hProc, HANDLE h))
#define UnmapViewInProc         _PROCESS_CALL(BOOL, UNMAPVIEW, (HANDLE hProc, LPCVOID pAddr))
#define FlushViewInProc         _PROCESS_CALL(BOOL, FLUSHVIEW, (HANDLE hProc, LPCVOID pAddr, DWORD cbSize))
#define MapViewInProc           _PROCESS_CALL(LPVOID, MAPVIEW, (HANDLE hProc, HANDLE hMap, DWORD dwAccess, DWORD dwOfstHigh, DWORD dwOfstLow, DWORD cbSize))
#define CreateFileMappingInProc _PROCESS_CALL(LPVOID, MAPCREATE, (HANDLE hProc, HANDLE hFile, LPSECURITY_ATTRIBUTES lpsa, DWORD flProtect, DWORD dwMaxSizeHigh, DWORD dwMaxSizeLow, LPCWSTR lpName))
#define GetModuleName           _PROCESS_CALL(DWORD, GETMODNAME, (HANDLE hProc, HMODULE hMod, LPWSTR rpName, DWORD cchLen))
#define GetModHandle            _PROCESS_CALL(HMODULE, GETMODHNDL, (HANDLE hProc, LPCWSTR pszModName, DWORD dwFlags))
#define VirtualSetAttributesEx  _PROCESS_CALL(BOOL, VMSETATTR, (HANDLE hProc, LPVOID lpvAddress, DWORD cbSize, DWORD dwNewFlags, DWORD dwMask, LPDWORD lpdwOldFlags))
#define AllocPhysMemEx          _PROCESS_CALL(LPVOID, VMALLOCPHYS, (HANDLE hProc, DWORD cbSize, DWORD fProtect, DWORD dwAlignMask, DWORD dwFlags, PULONG pPhysAddr))
#define ReadPEHeader            _PROCESS_CALL(DWORD, READPEHEADER, (HANDLE hProc, DWORD dwFlags, DWORD dwAddr, LPVOID pBuf, DWORD cbSize))
#define CheckRemoteDebuggerPresent _PROCESS_CALL(BOOL, CHECKREMOTEDEBUGGERPRESENT, (HANDLE hProcess, PBOOL pbDebuggerPresent))
#define PageOutModule           _PROCESS_CALL(BOOL, PAGEOUTMODULE, (HANDLE hProcess, HANDLE hModule, DWORD dwFlags))
#define NKOpenMsgQueueEx        _PROCESS_CALL(HANDLE, OPENMSGQEX, (HANDLE hSrcPrc, HANDLE hMsgQ, HANDLE hDstPrc, PMSGQUEUEOPTIONS lpOptions))

#define GetProcessId            _PROCESS_CALL(DWORD, GETPROCID, (HANDLE hProcess))
#define VirtualAllocCopyEx      _PROCESS_CALL(LPVOID, VMALLOCCOPY, (HANDLE hSrcProc, HANDLE hDstProc, LPVOID pAddr, DWORD cbSize, DWORD fProtect))

#define NKGetProcessAffinity    _PROCESS_CALL (BOOL, GETAFFINITY, (HANDLE hProcess, LPDWORD pdwAffinity))
#define NKSetProcessAffinity    _PROCESS_CALL (BOOL, SETAFFINITY, (HANDLE hProcess, DWORD dwAffinity))
#define CeLoadLibraryInProcess  _PROCESS_CALL (BOOL, LOADMODULE, (HANDLE hProcess, LPCWSTR lpName))

#define CeMapUserAddressesToVoid _PROCESS_CALL (BOOL, MAPADDRTOVOID, (HANDLE hProcess, LPVOID pAddr, DWORD cbSize))

#define GetProcessTimes         _PROCESS_CALL (BOOL, GETTIMES, (HANDLE hProcess, LPFILETIME pt1, LPFILETIME pt2, LPFILETIME pt3, LPFILETIME pt4))

// EVENT calls
#ifdef COREDLL
#ifdef WIN32_CALL
#define EventModify _EVENT_CALL(BOOL, MODIFY, (HANDLE hEvent, DWORD func))
#else
BOOL xxx_EventModify(HANDLE hEvent, DWORD func);
#define EventModify xxx_EventModify
#endif
#endif
#define EventGetData        _EVENT_CALL(DWORD, GETDATA, (HANDLE hEvent))
#define EventSetData        _EVENT_CALL(BOOL, SETDATA, (HANDLE hEvent, DWORD dwData))
#define NKReadMsgQueueEx    _EVENT_CALL(BOOL, READMSGQ, (HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbSize, LPDWORD lpNumberOfBytesRead, DWORD dwTimeout, LPDWORD pdwFlags, PHANDLE phTok))
#define NKWriteMsgQueue     _EVENT_CALL(BOOL, WRITEMSGQ, (HANDLE hMsgQ, LPCVOID lpBuffer, DWORD cbDataSize, DWORD dwTimeout, DWORD dwFlags))
#define NKGetMsgQueueInfo   _EVENT_CALL(BOOL, GETMSGQINFO, (HANDLE hMsgQ,  PMSGQUEUEINFO lpInfo))
#define NKResumeMainThread  _EVENT_CALL(BOOL, RESUMEMAINTH, (HANDLE hProcEvt, LPDWORD pdwRetVal))

#define NKWDStart           _EVENT_CALL(BOOL, WDSTART, (HANDLE hWDog))
#define NKWDStop            _EVENT_CALL(BOOL, WDSTOP, (HANDLE hWDog))
#define NKWDRefresh         _EVENT_CALL(BOOL, WDREFRESH, (HANDLE hWDog))

// APISET calls
#define RegisterAPISet             _APISET_CALL(BOOL, REGISTER, (HANDLE hASet, DWORD dwSetID))
#define RegisterDirectMethods      _APISET_CALL (BOOL, REGDIRECTMTHD, (HANDLE, const PFNVOID *))
#define CreateAPIHandle            _APISET_CALL(HANDLE, CREATEHANDLE, (HANDLE hASet, LPVOID pvData))
#define CreateAPIHandleWithAccess  _APISET_CALL(HANDLE, CREATEHANDLEWITHACCESS, (HANDLE hASet, LPVOID pvData, DWORD dwAccessMask, HANDLE hTargetProcess))
#define VerifyAPIHandle            _APISET_CALL(LPVOID, VERIFY, (HANDLE hASet, HANDLE h))
#define SetAPIErrorHandler         _APISET_CALL(BOOL, SETAPIERRORHANDLER, (HANDLE hASet, PFNAPIERRHANDLER pfnHandler))
#define CeRegisterAccessMask       _APISET_CALL(BOOL, REGACCESSMASK, (HANDLE hASet, LPDWORD lprgAccessMask, DWORD cAccessMask))

// MAPPED FILE calls
#ifdef COREDLL
#ifdef WIN32_CALL
#define MapViewOfFile +++ Do Not Use +++
#else
LPVOID xxx_MapViewOfFile(HANDLE hMap, DWORD fdwAccess, DWORD dwOffsetHigh, DWORD dwOffsetLow, DWORD cbMap);
#define MapViewOfFile xxx_MapViewOfFile
#endif
#endif

// MUTEX calls
#ifdef COREDLL
#ifdef WIN32_CALL
#define ReleaseMutex _MUTEX_CALL(BOOL, RELEASEMUTEX, (HANDLE hMutex))
#else
BOOL xxx_ReleaseMutex(HANDLE hMutex);
#define ReleaseMutex xxx_ReleaseMutex
#endif
#endif

// SEMPAHORE calls

#define ReleaseSemaphore _SEMAPHORE_CALL(BOOL, RELEASESEMAPHORE, (HANDLE hSemaphore, LONG lReleaseCount, LPLONG lpPreviousCount))

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif

