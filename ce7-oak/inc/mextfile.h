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

mextfile.h

Abstract:  

Notes: 


--*/
#ifndef __MEXTFILE_H__
#define __MEXTFILE_H__

#ifdef __cplusplus
extern "C" {
#endif

// Mounted file system api indicies.
#define AFS_API_Unmount 0
#define AFS_API_CreateDirectoryW 2
#define AFS_API_RemoveDirectoryW 3
#define AFS_API_GetFileAttributesW 4
#define AFS_API_SetFileAttributesW 5
#define AFS_API_CreateFileW 6
#define AFS_API_DeleteFileW 7
#define AFS_API_MoveFileW 8
#define AFS_API_FindFirstFileW 9
// 10 was RegisterFileSystemNotification, now obsolete
// 11 was OidGetInfo, now obsolete
#define AFS_API_PrestoChangoFileName 12
#define AFS_API_CloseAllFileHandles 13
#define AFS_API_GetDiskFreeSpace 14
#define AFS_API_NotifyMountedFS 15
#define AFS_API_RegisterFileSystemFunction 16
#define AFS_API_FindFirstChangeNotificationW 17
#define AFS_API_FsIoControlW 21
#define AFS_API_SetFileSecurityW 22
#define AFS_API_GetFileSecurityW 23

#define AFS_Unmount                 +++ Do Not Use +++
#define AFS_CreateDirectoryW        +++ Do Not Use +++
#define AFS_RemoveDirectoryW        +++ Do Not Use +++
#define AFS_GetFileAttributesW      +++ Do Not Use +++
#define AFS_SetFileAttributesW      +++ Do Not Use +++
#define AFS_CreateFileW             +++ Do Not Use +++
#define AFS_DeleteFileW             +++ Do Not Use +++
#define AFS_MoveFileW               +++ Do Not Use +++
#define AFS_FindFirstFileW          +++ Do Not Use +++
#define AFS_PrestoChangoFileName    +++ Do Not Use +++
#define AFS_CloseAllFileHandles     +++ Do Not Use +++
#define AFS_GetDiskFreeSpace        +++ Do Not Use +++
#define AFS_NotifyMountedFS         +++ Do Not Use +++
#define AFS_RegisterFileSystemFunction      +++ Do Not Use +++
#define AFS_FindFirstChangeNotificationW    +++ Do Not Use +++
#define AFS_FsIoControlW            +++ Do Not Use +++
#define AFS_SetFileSecurityW        +++ Do Not Use +++
#define AFS_GetFileSecurityW        +++ Do Not Use +++

#ifdef KCOREDLL
    
// Kernel-mode coredll AFS direct-call PSL Macros.

#define _DIRECT_AFS_CALL(api, rt, err, nargs, argt, arglist) \
    _DIRECT_HANDLE_CALL(rt, HT_AFSVOLUME, AFS_API_ ## api, err, argt, nargs, arglist)
    
#define AFS_Unmount_Trap(hAFS) \
    _DIRECT_AFS_CALL(Unmount, BOOL, FALSE, 0, (HANDLE), (hAFS))

#define AFS_CreateDirectoryW_Trap(hAFS, lpPathName, lpSecurityAttributes, pSecurityDescriptor, SecurityDescriptorSize) \
    _DIRECT_AFS_CALL(CreateDirectoryW, BOOL, FALSE, 4, (HANDLE, LPCWSTR, LPSECURITY_ATTRIBUTES, PSECURITY_DESCRIPTOR, DWORD), \
            (hAFS, lpPathName, lpSecurityAttributes, pSecurityDescriptor, SecurityDescriptorSize))

#define AFS_RemoveDirectoryW_Trap(hAFS, lpPathName) \
    _DIRECT_AFS_CALL(RemoveDirectoryW, BOOL, FALSE, 1, (HANDLE, LPCWSTR), (hAFS, lpPathName))

#define AFS_GetFileAttributesW_Trap(hAFS, lpFileName) \
    _DIRECT_AFS_CALL(GetFileAttributesW, DWORD, INVALID_FILE_ATTRIBUTES, 1, (HANDLE, LPCWSTR), (hAFS,lpFileName))

#define AFS_SetFileAttributesW_Trap(hAFS, lpFileName, dwAttributes) \
    _DIRECT_AFS_CALL(SetFileAttributesW, BOOL, FALSE, 2, (HANDLE, LPCWSTR, DWORD), (hAFS, lpFileName, dwAttributes))

#define AFS_CreateFileW_Trap(hAFS, hProc, lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, \
        dwFlagsAndAttributes, hTemplateFile, pSecurityDescriptor, SecurityDesciptorSize) \
    _DIRECT_AFS_CALL(CreateFileW, HANDLE, (DWORD)-1, 10, (HANDLE, HANDLE, LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE, PSECURITY_DESCRIPTOR, DWORD), \
            (hAFS, hProc, lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile, \
             pSecurityDescriptor, SecurityDescriptorSize))

#define AFS_DeleteFileW_Trap(hAFS, lpFileName) \
    _DIRECT_AFS_CALL(DeleteFileW, BOOL, FALSE, 1, (HANDLE, LPCWSTR), (hAFS, lpFileName))

#define AFS_MoveFileW_Trap(hAFS, lpExistingFileName, lpNewFileName) \
    _DIRECT_AFS_CALL(MoveFileW, BOOL, FALSE, 2, (HANDLE, LPCWSTR, LPCWSTR), (hAFS, lpExistingFileName, lpNewFileName))

#define AFS_FindFirstFileW_Trap(hAFS, hProc, lpFileName, lpFindFileData, SizeOfFindFileData) \
    _DIRECT_AFS_CALL(FindFirstFileW, HANDLE, (DWORD)-1, 4, (HANDLE, HANDLE, LPCWSTR, LPWIN32_FIND_DATAW, DWORD), \
            (hAFS, hProc, lpFileName, lpFindFileData, SizeOfFindFileData))

#define AFS_RegisterFileSystemFunction_Trap(hAFS, pShellFunc) \
    _DIRECT_AFS_CALL(RegisterFileSystemFunction, BOOL, FALSE, 1, (HANDLE, SHELLFILECHANGEFUNC_t), (hAFS, pShellFunc))

#define AFS_PrestoChangoFileName_Trap(hAFS, lpszOldFileName, lpszNewFileName) \
    _DIRECT_AFS_CALL(PrestoChangoFileName, BOOL, FALSE, 2, (HANDLE, LPCWSTR, LPCWSTR), (hAFS, lpszOldFileName, lpszNewFileName))

#define AFS_CloseAllFileHandles_Trap(hAFS, hProc) \
    _DIRECT_AFS_CALL(CloseAllFileHandles, BOOL, FALSE, 1, (HANDLE, HANDLE), (hAFS, hProc))

#define AFS_GetDiskFreeSpace_Trap(hAFS, lpPathName, lpSectorsPerCluster, lpBytesPerSector, lpFreeClusters, lpClusters) \
    _DIRECT_AFS_CALL(GetDiskFreeSpace, BOOL, FALSE, 5, (HANDLE, LPCWSTR, LPDWORD, LPDWORD, LPDWORD, LPDWORD), \
            (hAFS, lpPathName, lpSectorsPerCluster, lpBytesPerSector, lpFreeClusters, lpClusters))

#define AFS_NotifyMountedFS_Trap(hAFS, flags) \
    _DIRECT_AFS_CALL(NotifyMountedFS, void, 0, 1, (HANDLE, DWORD), (hAFS, flags))

#define AFS_FindFirstChangeNotificationW_Trap(hAFS, hProc, lpPath, bSubTree, dwFlags) \
    _DIRECT_AFS_CALL(FindFirstChangeNotificationW, HANDLE, (DWORD)-1, 4, (HANDLE, HANDLE, LPCWSTR, BOOL, DWORD), \
            (hAFS, hProc, lpPath, bSubTree, dwFlags))

#define AFS_FsIoControlW_Trap(hAFS, hProc, dwIoctl, lpInBuf, nInBufSize, lpOutBuf, nOutBufSize, lpBytesReturned, lpOverlapped) \
    _DIRECT_AFS_CALL(FsIoControlW, BOOL, FALSE, 8, (HANDLE, HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPOVERLAPPED), \
            (hAFS, hProc, dwIoctl, lpInBuf, nInBufSize, lpOutBuf, nOutBufSize, lpBytesReturned, lpOverlapped))

#define AFS_SetFileSecurityW_Trap(hAFS, pPathName, SecurityInformation, pSecurityDescriptor, Length) \
    _DIRECT_AFS_CALL(SetFileSecurityW, BOOL, FALSE, 4, (HANDLE, LPCWSTR, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR, DWORD), \
        (hAFS, pPathName, SecurityInformation, pSecurityDescriptor, Length))

#define AFS_GetFileSecurityW_Trap(hAFS, pPathName, RequestedInformation, pSecurityDescriptor, Length, pLengthNeeded) \
    _DIRECT_AFS_CALL(GetFileSecurityW, BOOL, FALSE, 5, (HANDLE, LPCWSTR, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR, DWORD, PDWORD), \
        (hAFS, pPathName, RequestedInformation, pSecurityDescriptor, Length, pLengthNeeded))

#endif // KCOREDLL

// AFS APIs are kernel-mode only, so these macros are defined only in KCOREDLL.

#ifdef __cplusplus
}
#endif

#endif  // __EXTFILE_H__
