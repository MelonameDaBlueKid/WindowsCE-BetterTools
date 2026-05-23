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

mstoremgr.h

Abstract:

Private version of storemgr.h. This module contains the function prototypes
and constant, type and structure definitions for the WINCE Implementeation
of the storage manager API.

Notes: 


--*/
#ifndef _MACRO_STOREMGR_H_
#define _MACRO_STOREMGR_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

// SDK exports
#ifdef BUILDING_FS_STUBS

#ifdef KCOREDLL

// Kernel mode direct handle calls.
#ifndef _DIRECT_FILE_CALL
#define _DIRECT_FILE_CALL(err, nargs, rt, id, argt, arglist)      _DIRECT_HANDLE_CALL (rt, HT_FILE, id, err, argt, nargs, arglist)
#endif

#ifndef _DIRECT_FIND_CALL
#define _DIRECT_FIND_CALL(err, nargs, rt, id, argt, arglist)      _DIRECT_HANDLE_CALL (rt, HT_FIND, id, err, argt, nargs, arglist)
#endif

// NOTE: ID 11 == DeviceIoControl
#define DismountStore_Trap(hStore) \
    _DIRECT_FILE_CALL(FALSE, 0, BOOL, 2, (HANDLE), (hStore))
    
#define FormatStore_Trap(hStore) \
    _DIRECT_FILE_CALL(FALSE, 0, BOOL, 3, (HANDLE), (hStore))
    
#define OpenPartition_Trap(hStore, szPartitionName) \
    _DIRECT_FILE_CALL((DWORD)-1, 1, HANDLE, 4, (HANDLE, LPCWSTR), (hStore, szPartitionName))

#define FindFirstPartition_Trap(hStore, pInfo) \
    _DIRECT_FILE_CALL((DWORD)-1, 1, HANDLE, 5, (HANDLE, PPARTINFO), (hStore, pInfo))
    
#define CreatePartition_Trap(hStore, szPartitionName, dwPartType, dwHighSec, dwLowSec, bAuto) \
    _DIRECT_FILE_CALL(FALSE, 5, BOOL, 6, (HANDLE, LPCWSTR, DWORD, DWORD, DWORD, BOOL), (hStore, szPartitionName, dwPartType, dwHighSec, dwLowSec, bAuto))

#define MountPartition_Trap(hPartition) \
    _DIRECT_FILE_CALL(FALSE, 0, BOOL, 7, (HANDLE), (hPartition))

#define DismountPartition_Trap(hPartition) \
    _DIRECT_FILE_CALL(FALSE, 0, BOOL, 8, (HANDLE), (hPartition))

#define RenamePartition_Trap(hPartition, szNewName) \
    _DIRECT_FILE_CALL(FALSE, 1, BOOL, 9, (HANDLE, LPCWSTR), (hPartition, szNewName))

#define SetPartitionAttributes_Trap(hPartition, dwAttrs) \
    _DIRECT_FILE_CALL(FALSE, 1, BOOL, 10, (HANDLE, DWORD), (hPartition, dwAttrs))

// NOTE: ID 11 == DeviceIoControl

#define GetPartitionInfo_Trap(hPartition, pInfo) \
    _DIRECT_FILE_CALL(FALSE, 1, BOOL, 12, (HANDLE, PPARTINFO), (hPartition, pInfo))

#define FormatPartition_Trap(hPartition, bPartType, bAuto) \
    _DIRECT_FILE_CALL(FALSE, 2, BOOL, 13, (HANDLE, BYTE, BOOL), (hPartition, bPartType, bAuto))

#define DeletePartition_Trap(hStore, szPartitionName) \
    _DIRECT_FILE_CALL(FALSE, 1, BOOL, 14, (HANDLE, LPCWSTR), (hStore, szPartitionName))

#define GetStoreInfo_Trap(hStore, pInfo) \
    _DIRECT_FILE_CALL(FALSE, 1, BOOL, 15, (HANDLE, PSTOREINFO), (hStore, pInfo))
    
#else // !KCOREDLL

// User mode handle calls.
#define WIN32_FILE_CALL(type, api, args)        (*(type (*) args)IMPLICIT_CALL(HT_FILE, api))
#define WIN32_FIND_CALL(type, api, args)        (*(type (*) args)IMPLICIT_CALL(HT_FIND, api))

// Store APIs are based on a psuedo file API
#define DismountStore_Trap      WIN32_FILE_CALL(BOOL, 2, (HANDLE hStore))
#define FormatStore_Trap        WIN32_FILE_CALL(BOOL, 3, (HANDLE hStore))
// NOTE: IDs 4 & 5 map to GetFileSize and SetFilePointer, both return -1 on failure
// so these will return INVALID_HANDLE_VALUE as appropriate when passed a bad handle.
#define OpenPartition_Trap      WIN32_FILE_CALL(HANDLE, 4, (HANDLE hStore, LPCWSTR szPartitionName))
#define FindFirstPartition_Trap WIN32_FILE_CALL(HANDLE, 5, (HANDLE hStore, PPARTINFO pInfo))
#define CreatePartition_Trap    WIN32_FILE_CALL(BOOL, 6,(HANDLE hStore, LPCWSTR szPartitionName, DWORD dwPartType, DWORD dwHighSec, DWORD dwLowSec, BOOL bAuto))
#define MountPartition_Trap     WIN32_FILE_CALL(BOOL, 7, (HANDLE hPartition))
#define DismountPartition_Trap  WIN32_FILE_CALL(BOOL, 8, (HANDLE hPartition))
#define RenamePartition_Trap    WIN32_FILE_CALL(BOOL, 9, (HANDLE hPartition, LPCWSTR szNewName))
#define SetPartitionAttributes_Trap WIN32_FILE_CALL(BOOL, 10, (HANDLE hStore, DWORD dwAttrs))
// NOTE: ID 11 == DeviceIoControl
#define GetPartitionInfo_Trap   WIN32_FILE_CALL(BOOL, 12, (HANDLE hPartition, PPARTINFO pInfo))
#define FormatPartition_Trap    WIN32_FILE_CALL(BOOL, 13, (HANDLE hPartition, DWORD bPartType, BOOL bAuto))
#define DeletePartition_Trap    WIN32_FILE_CALL(BOOL, 14, (HANDLE hStore, LPCWSTR szPartitionName))
#define GetStoreInfo_Trap       WIN32_FILE_CALL(BOOL, 15, (HANDLE hStore, PSTOREINFO pInfo))

#endif // !KCOREDLL

#define DismountStore           +++ Do Not Use +++
#define FormatStore             +++ Do Not Use +++
#define CreatePartition         +++ Do Not Use +++
#define DeletePartition         +++ Do Not Use +++
#define OpenPartition           +++ Do Not Use +++
#define MountPartition          +++ Do Not Use +++
#define DismountPartition       +++ Do Not Use +++
#define RenamePartition         +++ Do Not Use +++
#define SetPartitionAttributes  +++ Do Not Use +++
#define GetPartitionInfo        +++ Do Not Use +++
#define FormatPartition         +++ Do Not Use +++
#define FindFirstPartition      +++ Do Not Use +++
#define GetStoreInfo            +++ Do Not Use +++
#define FindNextStore           +++ Do Not Use +++
#define FindCloseStore          +++ Do Not Use +++
#define FindNextPartition       +++ Do Not Use +++
#define FindClosePartition      +++ Do Not Use +++

#elif defined(COREDLL)

BOOL xxx_DismountStore(HANDLE hStore);
#define DismountStore xxx_DismountStore

BOOL xxx_FormatStore(HANDLE hStore);
#define FormatStore xxx_FormatStore

BOOL xxx_CreatePartition(HANDLE hStore, LPCTSTR szPartitionName, SECTORNUM snNumSectors);
#define CreatePartition xxx_CreatePartition

BOOL xxx_DeletePartition(HANDLE hStore, LPCTSTR szPartitionName);
#define DeletePartition xxx_DeletePartition

HANDLE xxx_OpenPartition( HANDLE hStore, LPCTSTR szPartitionName);
#define OpenPartition xxx_OpenPartition

BOOL xxx_MountPartition(HANDLE hPartition);
#define MountPartition xxx_MountPartition

BOOL xxx_DismountPartition(HANDLE hPartition);
#define DismountPartition xxx_DismountPartition

BOOL xxx_RenamePartition(HANDLE hPartition, LPCTSTR szNewName);
#define RenamePartition xxx_RenamePartition

BOOL xxx_SetPartitionAttributes(HANDLE hPartition, DWORD dwAttrs);
#define SetPartitionAttributes xxx_SetPartitionAttributes

BOOL xxx_GetPartitionInfo(HANDLE hPartition, PPARTINFO pPartInfo);
#define GetPartitionAttributes xxx_GetPartitionAttributes

BOOL xxx_FormatPartition(HANDLE hPartition);
#define FormatPartition xxx_FormatPartition

BOOL xxx_GetStoreInfo(HANDLE hStore, PSTOREINFO pStoreInfo);
#define FindNextPartition xxx_FindNextPartition

HANDLE xxx_FindFirstStore(PSTOREINFO pStoreInfo);
#define FindFirstStore xxx_FindFirstStore

BOOL xxx_FindNextStore(HANDLE hSearch, PSTOREINFO pStoreInfo);
#define FindNextStore xxx_FindNextStore

BOOL xxx_FindCloseStore(HANDLE hSearch);
#define FindCloseStore xxx_FindCloseStore

HANDLE xxx_FindFirstPartition(HANDLE hStore, PPARTINFO pPartInfo);
#define FindFirstPartition xxx_FindFirstPartition

BOOL xxx_FindNextPartition(HANDLE hSearch, PPARTINFO pPartInfo);
#define FindNextPartition xxx_FindNextPartition

BOOL xxx_FindClosePartition(HANDLE hSearch);
#define FindClosePartition xxx_FindClosePartition

#endif

#ifdef __cplusplus
}
#endif

#endif // _MACRO_WINREG_
