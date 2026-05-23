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

    nkglobal.h

Abstract:

This file defines all the functions/variables used by KITL and NK

Notes: 


--*/

#ifndef _NKGLOBAL_H_
#define _NKGLOBAL_H_

#ifndef ASM_ONLY

#include "oemglobal.h"
#include "profiler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _NKGLOBAL {
    DWORD dwVersion;

    // function to output debug sting
    PFN_WriteDebugString pfnWriteDebugString;
    void (* pfnNKvDbgPrintfW) (LPCWSTR lpszFmt, va_list lpParms);
    int (* pfnNKwvsprintfW) (LPWSTR lpOut, LPCWSTR lpFmt, va_list lpParms, int maxchars);

    // last error
    void (* pfnSetLastError) (DWORD dwErr);
    DWORD (* pfnGetLastError) (void);

    // CS related
    void (WINAPI * pfnInitializeCS) (LPCRITICAL_SECTION lpcs);
    void (WINAPI * pfnDeleteCS) (LPCRITICAL_SECTION lpcs);
    void (WINAPI * pfnEnterCS) (LPCRITICAL_SECTION lpcs);
    void (WINAPI * pfnLeaveCS) (LPCRITICAL_SECTION lpcs);

    // interrupt related
    void (* pfnINT_OFF) (void);
    void (* pfnINT_ON) (void);
    BOOL (* pfnINT_ENABLE) (BOOL fEnable);
    BOOL (* pfnHookInterrupt) (int hwInterruptNumber, FARPROC pfnHandler);
    BOOL (* pfnUnhookInterrupt) (int hwInterruptNumber, FARPROC pfnHandler);
    DWORD (* pfnNKCallIntChain) (BYTE irq);
    BOOL (* pfnNKIsSysIntrValid) (DWORD idInt);
    BOOL (* pfnNKSetInterruptEvent) (DWORD idInt);

    // Sleep funciton
    void (* pfnSleep) (DWORD cmsec);

    // VM related
    BOOL (* pfnVMSetAttrib) (LPVOID lpvAddress, DWORD cbSize, DWORD dwNewFlags, DWORD dwMask, LPDWORD lpdwOldFlags);
    LPVOID (* pfnCreateStaticMapping) (DWORD dwPhysBase, DWORD dwSize);
    BOOL (* pfnDeleteStaticMapping) (LPVOID pVirtBase, DWORD dwSize);

    // registry related
    LONG (* pfnRegCreateKeyExW) (HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpsa, PHKEY phkResult, LPDWORD lpdwDisp);
    LONG (* pfnRegOpenKeyExW)  (HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
    LONG (* pfnRegCloseKey) (HKEY hKey);
    LONG (* pfnRegQueryValueExW) (HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
    LONG (* pfnRegSetValueExW) (HKEY hKey, LPCWSTR lpValueName, DWORD dwReserved, DWORD dwType, LPBYTE lpData, DWORD cbData);
    LONG (* pfnRegFlushKey) (HKEY hKey);
    

    // reboot related
    void (* pfnNKForceCleanBoot) (void);
    BOOL (* pfnNKReboot) (BOOL fClean);

    // address translation (physical to virtual and virtual to physical)
    // the dwShiftedPhysAddr parameter is (physicaladdr >> 8), such that we can support 
    // up to 40 bits of physical addresses.
    LPVOID (*pfnPhysToVirt) (DWORD dwShiftedPhysAddr, BOOL fCached);
    DWORD (*pfnVirtToPhys) (LPCVOID pVirtAddr);

    // kitl Ioctl - the only entry point to kitl
    PFN_Ioctl pfnKITLIoctl;

    // utility functions
    DWORD (*pfnNKwcslen) (const wchar_t * wcs);

    int (* pfnNKwcscmp) (const wchar_t * pwc1, const wchar_t * pwc2);
    int (* pfnNKwcsicmp) (LPCWSTR str1, LPCWSTR str2);
    int (* pfnNKwcsnicmp) (LPCWSTR str1, LPCWSTR str2, int cchLen);

    void (* pfnNKwcscpy) (LPWSTR p1, LPCWSTR p2);
    DWORD (*pfnNKwcsncpy) (LPWSTR pDst, LPCWSTR pSrc, DWORD cchLen);

    int (* pfnNKstrcmpiAandW) (LPCSTR lpa, LPCWSTR lpu);

    void (* pfnNKUnicodeToAscii) (LPSTR chptr, LPCWSTR wchptr, int maxlen);
    void (* pfnNKAsciiToUnicode) (LPWSTR wchptr, LPCSTR chptr, int maxlen);

    BOOL (* pfnSystemTimeToFileTime)(const SYSTEMTIME *pst, LPFILETIME pft);
    BOOL (* pfnFileTimeToSystemTime)(const FILETIME *pft, LPSYSTEMTIME pst);
    LONG (* pfnCompareFileTime)(const FILETIME *, const FILETIME *);
    
    // profiler
    void (* pfnProfilerHitEx) (OEMProfilerData* pData);
    DWORD (* pfnGetEPC) (void);

    // compiler /GS runtime
    void (* pfn__report_gsfailure) (void);

    // data
    DWORD dwStartupAddr;
    volatile DWORD dwNextReschedTime;
    volatile DWORD dwCurMSec;
    volatile LARGE_INTEGER liIdle;
    DWORD dwIdleConv;
    DWORD dwMaxThreadPerProc;

    DWORD dwProcessorType;
    WORD  wProcessorLevel;
    WORD  wProcessorRevision;
    DWORD dwInstructionSet;
    
    DBGPARAM *pKITLDbgZone;

    void (*pfnNKSendIPI) (DWORD dwType, DWORD dwTarget, DWORD dwCommand, DWORD dwData);
    void (*pfnAcquireOalSpinLock) (void);
    void (*pfnReleaseOalSpinLock) (void);

    void (*pfnCeLogData) (BOOL, DWORD, VOID*, DWORD, DWORD, DWORD, DWORD, BOOL);
    DWORD dwCntRunnableThreads;
    DWORD unused[31];

#ifdef x86
    // cpu dependent part
    BOOL (* pfnX86wrmsr) (
        DWORD dwAddr,       // Address of MSR being written
        DWORD dwValHigh,    // Upper 32 bits of value being written
        DWORD dwValLow      // Lower 32 bits of value being written
        );
    BOOL (* pfnX86rdmsr) (
        DWORD dwAddr,       // Address of MSR being read
        DWORD *lpdwValHigh, // Receives upper 32 bits of value, can be NULL
        DWORD *lpdwValLow   // Receives lower 32 bits of value, can be NULL
        );    
    DWORD dwKnownUncachedAddress;
#endif

#ifdef SH4
    BYTE* IntrPrio;
    DWORD* InterruptTable;
#endif

#ifdef ARM
    const DWORD *pdwOrigVectors;
    LPDWORD pdwCurrVectors;                 // exception vectors
#endif

}NKGLOBAL, *PNKGLOBAL;

extern PNKGLOBAL g_pNKGlobal;
void NKSendInterProcessorInterrupt (DWORD dwType, DWORD dwTarget, DWORD dwCommand, DWORD dwData);
void NKAcquireOalSpinLock (void);
void NKReleaseOalSpinLock (void);

#ifndef CEProcessorType
#define CEProcessorType                     g_pNKGlobal->dwProcessorType
#endif

#ifndef CEProcessorLevel
#define CEProcessorLevel                    g_pNKGlobal->wProcessorLevel
#endif

#ifndef CEProcessorRevision
#define CEProcessorRevision                 g_pNKGlobal->wProcessorRevision
#endif

#ifndef CEInstructionSet
#define CEInstructionSet                    g_pNKGlobal->dwInstructionSet
#endif

// entry point to OAL
typedef POEMGLOBAL (* PFN_OEMInitGlobals) (PNKGLOBAL pnkglobal);

#ifdef __cplusplus
}
#endif

#endif  // ASM_ONLY

#endif  // _NKGLOBAL_H_
