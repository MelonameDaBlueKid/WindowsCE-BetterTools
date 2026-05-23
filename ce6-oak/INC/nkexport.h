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
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

    nkexport.h

Abstract:

This file defines all the functions/variables exports by NK that can be used in OAL/KITL

Notes: 


--*/

#ifndef _NKEXPORTS_H_
#define _NKEXPORTS_H_

#ifndef ASM_ONLY

#include "nkglobal.h"

#ifdef __cplusplus
extern "C" {
#endif

void NKOutputDebugString (LPCWSTR pszStr);
void NKvDbgPrintfW  (LPCWSTR lpszFmt, va_list lpParms);
void WINAPIV NKDbgPrintfW (LPCWSTR lpszFmt, ...);
int NKwvsprintfW  (LPWSTR lpOut, LPCWSTR lpFmt, va_list lpParms, int maxchars);

void NKSetLastError (DWORD dwErr);
DWORD NKGetLastError (void);

void WINAPI EnterCriticalSection (LPCRITICAL_SECTION lpcs);
void WINAPI LeaveCriticalSection (LPCRITICAL_SECTION lpcs);
void WINAPI InitializeCriticalSection (LPCRITICAL_SECTION lpcs);
void WINAPI DeleteCriticalSection (LPCRITICAL_SECTION lpcs);

#ifndef INTERRUPTS_OFF
void INTERRUPTS_OFF (void);
#endif

#ifndef INTERRUPTS_ON
void INTERRUPTS_ON (void);
#endif

BOOL INTERRUPTS_ENABLE (BOOL fEnable);

BOOL HookInterrupt (int irq, FARPROC pfnHandler);
BOOL UnhookInterrupt (int irq, FARPROC pfnHandler);
DWORD NKCallIntChain (BYTE irq);
BOOL NKIsSysIntrValid (DWORD idInt);
BOOL NKSetInterruptEvent (DWORD idInt);

void NKSleep (DWORD cmsec);

BOOL NKVirtualSetAttributes (LPVOID lpvAddress, DWORD cbSize, DWORD dwNewFlags, DWORD dwMask, LPDWORD lpdwOldFlags);
LPVOID NKCreateStaticMapping (DWORD dwPhysBase, DWORD cbSize);

LONG NKRegCloseKey (HKEY hKey);
LONG NKRegCreateKeyExW (HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpsa, PHKEY phkResult, LPDWORD lpdwDisp);
LONG NKRegOpenKeyExW (HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
LONG NKRegQueryValueExW (HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
LONG NKRegSetValueExW (HKEY hKey, LPCWSTR lpValueName, DWORD dwReserved, DWORD dwType, LPBYTE lpData, DWORD cbData);
LONG NKRegFlushKey (HKEY hKey);

// Unicode only
#define NKRegCreateKeyEx    NKRegCreateKeyExW
#define NKRegOpenKeyEx      NKRegOpenKeyExW
#define NKRegQueryValueEx   NKRegQueryValueExW
#define NKRegSetValueEx     NKRegSetValueExW

void NKForceCleanBoot (void);
BOOL NKReboot (BOOL fClean);

//
// NKPhysToVirt - convert a physical address to a static mapped kernel address.
//      return NULL if failed.
//
LPVOID NKPhysToVirt (DWORD dwShiftedPhysAddr, BOOL fCached);

//
// NKVirtToPhys - convert a kernel virtual address to phsyical address.
//      return INVALID_PHYSICAL_ADDRESS if failed.
//
// NOTE: The returned value is the "Shifterd Physical address". i.e. == (actual_physical >> 8)
//
#define INVALID_PHYSICAL_ADDRESS 0xFFFFFFFF

DWORD NKVirtToPhys (LPCVOID pVa);

DWORD NKwcslen (LPCWSTR wcs);
int NKwcscmp (LPCWSTR str1, LPCWSTR str2);
int NKwcsicmp (LPCWSTR str1, LPCWSTR str2);
int NKwcsnicmp (LPCWSTR str1, LPCWSTR str2, int cchLen);
void NKwcscpy (LPWSTR dst, LPCWSTR src);
DWORD NKwcsncpy (LPWSTR dst, LPCWSTR src, DWORD cchLen);
int NKstrcmpiAandW (LPCSTR pascii, LPCWSTR pUnicode);

void NKUnicodeToAscii (LPSTR chptr, LPCWSTR wchptr, int maxlen);
void NKAsciiToUnicode (LPWSTR wchptr, LPCSTR chptr, int maxlen);

BOOL NKSystemTimeToFileTime (const SYSTEMTIME *pst, LPFILETIME pft);
BOOL NKFileTimeToSystemTime (const FILETIME *pft, LPSYSTEMTIME pst);
BOOL NKCompareFileTime (const FILETIME *pft1, const FILETIME *pft2);

void ProfilerHit (UINT addr);
DWORD GetEPC (void);

BOOL KITLIoctl (DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned);

// data exports
#ifndef BUILDING_BOOTLOADER

#ifndef CurMSec
#define CurMSec                             g_pNKGlobal->dwCurMSec
#endif

#ifndef AddrCurMSec
#define AddrCurMSec                         &g_pNKGlobal->dwCurMSec
#endif

#ifndef dwReschedTime
#define dwReschedTime                       g_pNKGlobal->dwNextReschedTime
#endif

#ifndef curridlehigh
#define curridlehigh                        g_pNKGlobal->liIdle.HighPart
#endif

#ifndef curridlelow
#define curridlelow                         g_pNKGlobal->liIdle.LowPart
#endif

#ifndef idleconv
#define idleconv                            g_pNKGlobal->dwIdleConv
#endif

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

#endif  // BUILDING_BOOTLOADER

#ifdef x86

BOOL NKwrmsr (
    DWORD dwAddr,       // Address of MSR being written
    DWORD dwValHigh,    // Upper 32 bits of value being written
    DWORD dwValLow      // Lower 32 bits of value being written
    );

BOOL NKrdmsr (
    DWORD dwAddr,       // Address of MSR being read
    DWORD *lpdwValHigh, // Receives upper 32 bits of value, can be NULL
    DWORD *lpdwValLow   // Receives lower 32 bits of value, can be NULL
    );

#endif

#ifdef __cplusplus
}
#endif

#endif  // ASM_ONLY

#endif  // _NKEXPORTS_H_
