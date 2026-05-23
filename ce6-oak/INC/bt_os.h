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
//------------------------------------------------------------------------------
// 
//      Bluetooth OS abstraction layer
// 
// 
// Module Name:
// 
//      bt_os.h
// 
// Abstract:
// 
//      This file defines compatibility layer between Windows CE and Windows NT
// 
// 
//------------------------------------------------------------------------------
#if ! defined (__bt_os_H__)
#define __bt_os_H__			1

#define HKEY_BASE				HKEY_LOCAL_MACHINE

inline BOOL GetComputerName (
    __out_ecount(*nSize) LPWSTR lpBuffer,
    LPDWORD nSize
    ) {
	TCHAR szBuffer[_MAX_PATH];
	DWORD dwType = REG_SZ;
	DWORD dwSize = sizeof(szBuffer);
	HKEY hKey = NULL;
	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, TEXT("Ident"), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	if ((RegQueryValueEx (hKey, TEXT("name"), 0, &dwType, (LPBYTE)szBuffer, &dwSize) != ERROR_SUCCESS) ||
		(dwType != REG_SZ) || (dwSize > sizeof(szBuffer))) {
		RegCloseKey (hKey);
		return FALSE;
	}
	RegCloseKey (hKey);

	dwSize = wcslen (szBuffer) + 1;

	if (dwSize > *nSize) {
	    *nSize = dwSize;
	    SetLastError (ERROR_INSUFFICIENT_BUFFER);
	    return FALSE;
	}

    *nSize = dwSize;
	memcpy (lpBuffer, szBuffer, dwSize * sizeof(TCHAR));
	return TRUE;
}

#endif			//	END OS COMPATIBILITY LAYER
