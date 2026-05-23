// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include <atlbase.h>

#include "rapi.h"
#include "ceutil.h"

// Check HRESULT
#define CHR(hResult)\
	do {hr = (hResult); if(FAILED(hr)) goto Error;} while (0,0)

// Check pointer result
#define CPR(p)\
    do {if(!(0,(p))) {hr = E_OUTOFMEMORY; goto Error;} } while (0,0)

// Check boolean result
#define CBR(fResult)\
    do {if (!(0,(fResult))) {hr = E_FAIL; goto Error;}} while(0,0);

// Check Windows result
#define CWR(fResult)\
    do {if (!(0,(fResult))) {hr = HRESULT_FROM_WIN32(GetLastError()); goto Error;}} while(0,0);

const TCHAR c_szDeviceFileName[] = _T("\\DevConfig.cpf");
const WCHAR c_szwPPCInstaller[] = L"\\Windows\\wceloadsp.exe";
const WCHAR c_szwSPInstaller[] = L"\\Windows\\wceload.exe";
const TCHAR c_szDeviceTypePPC[] = _T("PocketPC");
const TCHAR c_szDeviceTypeSP[] = _T("SmartPhone");

#define MAX_PROFILE_ENTRY_LEN 100
