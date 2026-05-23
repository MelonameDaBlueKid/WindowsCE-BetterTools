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

mwinreg.h

Abstract:

Private version of winreg.h. This module contains the function prototypes
and constant, type and structure definitions for the WINCE Implementeation
of the Windows 32-Bit Registry API.

Notes: 


--*/
#ifndef _MACRO_WINREG_H_
#define _MACRO_WINREG_H_

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

#ifdef __cplusplus
extern "C" {
#endif

// SDK exports
#ifdef WIN32_FS_CALL
#define RegCloseKey +++ Do Not Use +++ 
#define RegCloseKey_Trap WIN32_FS_CALL(LONG, 17, (HKEY hKey))

#define RegFlushKey +++ Do Not Use +++ 
#define RegFlushKey_Trap WIN32_FS_CALL(LONG, 49, (HKEY hKey))

#define RegCreateKeyExW +++ Do Not Use +++ 
#define RegCreateKeyExW_Trap WIN32_FS_CALL(LONG, 18, (HKEY hKey, LPCWSTR lpSubKey,  \
    DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired,        \
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition))

#define RegDeleteKeyW +++ Do Not Use +++ 
#define RegDeleteKeyW_Trap WIN32_FS_CALL(LONG, 19, (HKEY hKey, LPCWSTR lpSubKey))

#define RegDeleteValueW +++ Do Not Use +++ 
#define RegDeleteValueW_Trap WIN32_FS_CALL(LONG, 20, (HKEY hKey, LPCWSTR lpValueName))

#define RegEnumValueW +++ Do Not Use +++ 
#define RegEnumValueW_Trap WIN32_FS_CALL(LONG, 21, (HKEY hKey, DWORD dwIndex,       \
    LPWSTR lpValueName, DWORD cbValueName, LPDWORD lpcchValueName,                  \
    LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, DWORD cbDataIn,              \
    LPDWORD lpcbDataOut))

#define RegEnumKeuExW +++ Do Not Use +++ 
#define RegEnumKeyExW_Trap WIN32_FS_CALL(LONG, 22, (HKEY hKey, DWORD dwIndex,       \
    LPWSTR lpName, DWORD cbNameIn, LPDWORD lpcchNameOut, LPDWORD lpReserved,        \
    LPWSTR lpClass, DWORD cbClassIn, LPDWORD lpcchClassOut,                         \
    PFILETIME lpftLastWriteTime))

#define RegOpenKeyExW +++ Do Not Use +++ 
#define RegOpenKeyExW_Trap WIN32_FS_CALL(LONG, 23, (HKEY hKey, LPCWSTR lpSubKey,    \
    DWORD ulOptions, REGSAM samDesired, PHKEY phkResult))

#define RegQueryInfoKeyW +++ Do Not Use +++ 
#define RegQueryInfoKeyW_Trap WIN32_FS_CALL(LONG, 24, (HKEY hKey, LPWSTR lpClass,   \
    DWORD cbClassIn, LPDWORD lpcbClassOut, LPDWORD lpReserved, LPDWORD lpcSubKeys,  \
    LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues,      \
    LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, \
    LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime))

#define RegQueryValueExW +++ Do Not Use +++ 
#define RegQueryValueExW_Trap WIN32_FS_CALL(LONG, 25, (HKEY hKey, LPCWSTR lpValueName, \
    LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, DWORD cbDataIn, LPDWORD lpcbDataOut))

#define RegSetValueExW +++ Do Not Use +++ 
#define RegSetValueExW_Trap WIN32_FS_CALL(LONG, 26, (HKEY hKey, LPCWSTR lpValueName, \
    DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData))

#define CeRegTestSetValueW    +++ Do Not Use +++ 
#define CeRegTestSetValueW_Trap WIN32_FS_CALL (LONG, 134, (HKEY hKey, LPCWSTR lpValueName, \
            DWORD dwType, const BYTE *lpOldData, DWORD cbOldData, const BYTE *lpNewData, DWORD cbNewData, DWORD dwFlags))

#define RegSetKeySecurity +++ Do Not Use +++ 
#define RegSetKeySecurity_Trap WIN32_FS_CALL(LONG, 149, (HKEY hKey,    \
    SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor,  \
    DWORD cbSecurityDescriptor))

#define RegGetKeySecurity +++ Do Not Use +++ 
#define RegGetKeySecurity_Trap WIN32_FS_CALL(LONG, 150, (HKEY hKey,    \
    SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor,   \
    DWORD cbSecurityDescriptorIn, LPDWORD lpcbSecurityDescriptorOut))    

#define GetUsetInformation +++ Do Not Use +++ 
#define GetUserInformation_Trap  WIN32_FS_CALL(BOOL, 69, (LPWSTR lpszBuffer,        \
    LPDWORD lpdwSize, DWORD dwFlags))

// This definition is from wincrypt.h
typedef struct _CRYPTOAPI_BLOB
{
    DWORD cbData;
    PBYTE pbData;
} DATA_BLOB;


#define PSLGetDeviceUniqueID WIN32_FS_CALL(HRESULT, 135, (LPBYTE pbApplicationData, DWORD cbApplicationData, DWORD dwDeviceIDVersion, LPBYTE pbDeviceIDOutput, DWORD cbDeviceIDOutput, LPDWORD pcbDeviceIDOutputActual))

#define PSLCryptProtectData WIN32_FS_CALL(BOOL, 85, (PBYTE pbDataIn,            \
                                                     DWORD cbDataIn,            \
                                                     LPCWSTR szDataDescr,       \
                                                     PBYTE pbOptionalEntropy,   \
                                                     DWORD cbOptionalEntropy,   \
                                                     DWORD dwFlags,             \
                                                     PBYTE pbDataOut,           \
                                                     DWORD cbDataOut,           \
                                                     DWORD *pcbDataOutActual))

#define PSLCryptUnprotectData WIN32_FS_CALL(BOOL, 86, (PBYTE pbDataIn,              \
                                                       DWORD cbDataIn,              \
                                                       DWORD *pdwDataDescrPresent,  \
                                                       DWORD *pdwDataDescrOffset,   \
                                                       PBYTE pbOptionalEntropy,     \
                                                       DWORD cbOptionalEntropy,     \
                                                       DWORD dwFlags,               \
                                                       PBYTE pbDataOut,             \
                                                       DWORD cbDataOut,             \
                                                       DWORD *pcbDataOutActual))


// OAK exports
#define RegCopyFile +++ Do Not Use +++ 
#define RegCopyFile_Trap    WIN32_FS_CALL(BOOL, 41, (LPCWSTR lpszFile))
#define RegRestoreFile +++ Do Not Use +++ 
#define RegRestoreFile_Trap WIN32_FS_CALL(BOOL, 44, (LPCWSTR lpszFile))
#define RegSaveKey +++ Do Not Use +++ 
#define RegSaveKey_Trap     WIN32_FS_CALL(LONG, 64, (HKEY hKey, LPCWSTR lpszFile,   \
    LPSECURITY_ATTRIBUTES lpSecurityAttributes))
#define RegReplaceKey +++ Do Not Use +++ 
#define RegReplaceKey_Trap  WIN32_FS_CALL(LONG, 65, (HKEY hKey, LPCWSTR lpszSubKey, \
    LPCWSTR lpszNewFile, LPCWSTR lpszOldFile))
#define SetCurrentUser +++ Do Not Use +++ 
#define SetCurrentUser_Trap WIN32_FS_CALL(BOOL, 67, (LPCWSTR lpszUserName,          \
    LPBYTE lpbUserData, DWORD dwDataSize, BOOL bCreateIfNew))
#define SetUserData +++ Do Not Use +++ 
#define SetUserData_Trap    WIN32_FS_CALL(BOOL, 68, (LPBYTE lpbUserData,            \
    DWORD dwDataSize))
#define PSLGenRandom  WIN32_FS_CALL(BOOL, 87, (LPBYTE pbBuffer, DWORD dwLen))


#define CeFindFirstRegChange    +++ Do Not Use +++ 
#define CeFindFirstRegChange_Trap WIN32_FS_CALL(HANDLE, 104, (HKEY hKey, BOOL bSubTree, DWORD dwFlags))

#define CeFindNextRegChange      +++ Do Not Use +++ 
#define CeFindNextRegChange_Trap  WIN32_FS_CALL(BOOL, 105, (HANDLE hNotify))

#define CeFindCloseRegChange     +++ Do Not Use +++ 
#define CeFindCloseRegChange_Trap WIN32_FS_CALL(BOOL, 106, (HANDLE hNotify))

#elif defined(COREDLL)

LONG xxx_RegCloseKey (HKEY hKey);
#define RegCloseKey xxx_RegCloseKey
LONG xxx_RegFlushKey (HKEY hKey);
#define RegFlushKey xxx_RegFlushKey
LONG xxx_RegCreateKeyExW (HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
#define RegCreateKeyExW xxx_RegCreateKeyExW
LONG xxx_RegDeleteKeyW (HKEY hKey, LPCWSTR lpSubKey);
#define RegDeleteKeyW xxx_RegDeleteKeyW
LONG xxx_RegDeleteValueW (HKEY hKey, LPCWSTR lpValueName);
#define RegDeleteValueW xxx_RegDeleteValueW
LONG xxx_RegEnumValueW (HKEY hKey, DWORD dwIndex, LPWSTR lpValueName, LPDWORD lpcbValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
#define RegEnumValueW xxx_RegEnumValueW
LONG xxx_RegEnumKeyExW (HKEY hKey, DWORD dwIndex, __out_ecount(*lpcbName) LPWSTR lpName, LPDWORD lpcbName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcbClass, PFILETIME lpftLastWriteTime);
#define RegEnumKeyExW xxx_RegEnumKeyExW
LONG xxx_RegOpenKeyExW (HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
#define RegOpenKeyExW xxx_RegOpenKeyExW
LONG xxx_RegQueryInfoKeyW (HKEY hKey, LPWSTR lpClass, LPDWORD lpcbClass, LPDWORD lpReserved, LPDWORD lpcSubKeys, LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime);
#define RegQueryInfoKeyW xxx_RegQueryInfoKeyW
LONG xxx_RegQueryValueExW (HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
#define RegQueryValueExW xxx_RegQueryValueExW
LONG xxx_RegSetValueExW (HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData);
#define RegSetValueExW xxx_RegSetValueExW
LONG xxx_RegSetKeySecurity (HKEY hKey, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor);
#define RegSetKeySecurity xxx_RegSetKeySecurity
LONG xxx_RegGetKeySecurity (HKEY hKey, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, LPDWORD lpcbSecurityDescriptor);
#define RegGetKeySecurity xxx_RegGetKeySecurity

HANDLE  xxx_CeFindFirstRegChange(HKEY hKey, BOOL bWatchSubTree, DWORD dwNotifyFilter);
#define CeFindFirstRegChange   xxx_CeFindFirstRegChange

BOOL    xxx_CeFindNextRegChange(HANDLE hNotify);
#define CeFindNextRegChange      xxx_CeFindNextRegChange

BOOL    xxx_CeFindCloseRegChange(HANDLE hNotify);
#define CeFindCloseRegChange     xxx_CeFindCloseRegChange

LONG    xxx_CeRegGetInfo(HKEY hKey, PCE_REGISTRY_INFO pInfo);
#define CeRegGetInfo     xxx_CeRegGetInfo

// OAK exports
BOOL xxx_RegCopyFile (LPCWSTR lpszFile);
#define RegCopyFile xxx_RegCopyFile
BOOL xxx_RegRestoreFile (LPCWSTR lpszFile);
#define RegRestoreFile xxx_RegRestoreFile
LONG xxx_RegSaveKey(HKEY hKey, LPCWSTR lpszFile, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
#define RegSaveKey xxx_RegSaveKey
LONG xxx_RegReplaceKey (HKEY hKey, LPCWSTR lpszSubKey, LPCWSTR lpszNewFile, LPCWSTR lpszOldFile);
#define RegReplaceKey xxx_RegReplaceKey
BOOL xxx_SetCurrentUser (LPCWSTR lpszUserName, LPBYTE lpbUserData, DWORD dwDataSize, BOOL bCreateIfNew);
#define SetCurrentUser xxx_SetCurrentUser
BOOL xxx_SetUserData (LPBYTE lpbUserData, DWORD dwDataSize);
#define SetUserData xxx_SetUserData
BOOL xxx_GetUserDirectory(LPWSTR lpszBuffer, LPDWORD lpdwSize);
#define GetUserDirectory xxx_GetUserDirectory

#endif

#ifdef __cplusplus
}
#endif

#endif // _MACRO_WINREG_
