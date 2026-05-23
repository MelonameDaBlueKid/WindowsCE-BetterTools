// ***************************************************************************
// REGISTRY.CPP
//
// Functions for manipulating the registry
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include "winmine.h"

BOOL InitRegistry(
    LPDWORD dwDisposition
    )
{
	// try to open the registry key
	if (RegCreateKeyEx(REGISTRY_ROOT, REGISTRY_KEY, (DWORD) 0, TEXT(""), 
        (DWORD) 0, (REGSAM) 0, (LPSECURITY_ATTRIBUTES) NULL, 
        &g_hkWinMine, dwDisposition) != ERROR_SUCCESS) 
    {
		return FALSE;
	}

	return TRUE;
}

BOOL GetRegString(
    LPCTSTR c_tszValue, 
    LPTSTR *plptszRetval //pointer to a LPTSTR
    )
{
	int		iResult;
	DWORD	dwSize = 0;

	// regardless of what happens, free plptszRetval and set to NULL
	free(*plptszRetval);
	*plptszRetval = NULL;
	
	// first get the length 
    iResult = RegQueryValueEx(g_hkWinMine, c_tszValue, (LPDWORD)NULL,
        (LPDWORD)NULL, (PBYTE)NULL, &dwSize);

	if (ERROR_SUCCESS == iResult) 
    {
		// now that we have the length, malloc space and get the string
        *plptszRetval = (LPTSTR)malloc(dwSize * sizeof(TCHAR));
		if (NULL == *plptszRetval)
        {
			return FALSE;
		}
        iResult = RegQueryValueEx(g_hkWinMine, c_tszValue, (LPDWORD)NULL, 
            (LPDWORD)NULL, (PBYTE)*plptszRetval, &dwSize);
		if (ERROR_SUCCESS != iResult) {
			free(*plptszRetval);
			*plptszRetval = NULL;
			return FALSE;
		}
	}
    else
    {
		// check iResult to make sure it was just an invalid parameter
		if (ERROR_FILE_NOT_FOUND != iResult) 
        {
		    RETAILMSG(1, (TEXT("GetRegString: Got Error %d\n"), iResult));
			return FALSE;
		}
	} 

	return TRUE;
}

BOOL GetRegDWORD(
    LPCTSTR c_tszValue, 
    LPDWORD dwResult
    )
{
	int		iResult;
	DWORD	dwSize = sizeof(DWORD);
	
	// get the DWORD
	if ((iResult = RegQueryValueEx(g_hkWinMine, c_tszValue, 
								   (LPDWORD) NULL, (LPDWORD) NULL, 
								   (PBYTE) dwResult, &dwSize))
		!= ERROR_SUCCESS) {
		// check iResult to make sure it was just an invalid parameter
		if (iResult != ERROR_FILE_NOT_FOUND) {
		    RETAILMSG(1, (TEXT("GetRegDWORD: Got Error %d\n"), iResult));
			return FALSE;
		}

		// value did not exist, so set it to an impossible time
		*dwResult = 0;
	}

	return TRUE;
}

BOOL GetRegBinary(LPCTSTR c_tszValue, PBYTE lpData, DWORD dwSize)
{
	int		iResult;
	DWORD	dwSizeRec = dwSize;
	
	// get Binary Data
    iResult = RegQueryValueEx(g_hkWinMine, c_tszValue, (LPDWORD)NULL, 
        (LPDWORD)NULL, (PBYTE)lpData, &dwSizeRec);
	if (ERROR_SUCCESS != iResult)
    {
		// check iResult to make sure it was just an invalid parameter
		if (ERROR_FILE_NOT_FOUND != iResult) 
        {
		    RETAILMSG(1, (TEXT("GetRegBinary: Got Error %d\n"), iResult));
			return FALSE;
		}
        else
        {
			// the key doesn't exist, so we didn't receive any data
			dwSizeRec = 0;
		}
	}

	// did we read in the correct number of bytes?
	return (dwSizeRec == dwSize);
}

BOOL SetRegDWORD(
    LPCTSTR c_tszValue, 
    DWORD dwResult
    )
{
	int iResult;
	iResult = RegSetValueEx(g_hkWinMine, c_tszValue, (DWORD)0, REG_DWORD, 
        (PBYTE)&dwResult, sizeof(DWORD));

	return (ERROR_SUCCESS == iResult);
}

BOOL SetRegString(
    LPCTSTR c_tszValue, 
    LPTSTR lptszRetval
    )
{
	int iResult;
	iResult = RegSetValueEx(g_hkWinMine, c_tszValue, (DWORD)0,
        REG_SZ, (PBYTE)lptszRetval, (_tcslen(lptszRetval)+1) * sizeof(TCHAR));
	return (iResult == ERROR_SUCCESS);
}

BOOL SetRegBinary(
    LPCTSTR c_tszValue, 
    PBYTE pData, 
    DWORD dwSize
    )
{
	int iResult;
	iResult = RegSetValueEx(g_hkWinMine, c_tszValue, (DWORD)0, REG_BINARY, 
        pData, dwSize);
	return (ERROR_SUCCESS == iResult);
}
