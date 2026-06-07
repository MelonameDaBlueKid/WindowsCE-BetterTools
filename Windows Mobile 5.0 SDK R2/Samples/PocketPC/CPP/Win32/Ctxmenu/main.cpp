//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//


// MAIN.CPP - Main DLL entry points.

#include "common.h"


// Globals

UINT      g_cRefDLL   = 0;        // reference count for this DLL
HINSTANCE g_hinstDLL  = NULL;     // instance handle


BOOL WINAPI DllMain(
	HANDLE hInstDLL, 
	DWORD dwReason, 
	LPVOID lpvReserved
	)
{
    UNREFERENCED_PARAMETER(lpvReserved);

    if (DLL_PROCESS_ATTACH == dwReason)
    {
        DisableThreadLibraryCalls((HMODULE)hInstDLL);
        g_hinstDLL = (HINSTANCE)hInstDLL;
    }

    return 1;
}


STDAPI DllCanUnloadNow()
{
	if (0 == g_cRefDLL) 
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}


STDAPI DllGetClassObject(
	REFCLSID rclsid,
	REFIID riid,
	LPVOID *ppvOut
	)
{
    if (NULL == ppvOut)
	{
        return E_INVALIDARG;
	}

    *ppvOut = NULL;

    if (IsEqualIID(rclsid, CLSID_CContextMenuSample))
    {
        CContextMenuSampleClassFactory *pcf = new CContextMenuSampleClassFactory;

        return pcf->QueryInterface(riid, ppvOut);
    }

    return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllRegisterServer()
{
    LRESULT lr;
    HRESULT hr = E_FAIL;
    HKEY hKey = NULL;
    HKEY hSubKey = NULL;
    DWORD dwDisposition;
    TCHAR wszValue[20];
	TCHAR wszAttrib[20];
    TCHAR wszPath[256];

    StringCchPrintf(wszPath, 256, TEXT("\\CLSID\\%s"), GUID_CContextMenuSample);
    lr = RegCreateKeyEx(HKEY_CLASSES_ROOT, wszPath,
	                              0, NULL, 0, 0, NULL, 
	                              &hKey, &dwDisposition);
    if (lr != ERROR_SUCCESS)
    {
        goto Exit;
    }

	StringCchCopy(wszValue, 20, TEXT("CME Plugin Sample"));
	lr = RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE) wszValue, (lstrlen(wszValue) + 1) * sizeof(TCHAR));
    if (lr != ERROR_SUCCESS)
    {
        goto Exit;
    }
    
	lr = RegCreateKeyEx(hKey, TEXT("InprocServer32"),
	                              0, NULL, 0, 0, NULL, 
	                              &hSubKey, &dwDisposition);
    if (lr != ERROR_SUCCESS)
    {
        goto Exit;
    }

	StringCchCopy(wszValue, 20, TEXT("ctxmenu.dll"));
    lr = RegSetValueEx(hSubKey, NULL, 0, REG_SZ, (LPBYTE) wszValue, (lstrlen(wszValue) + 1) * sizeof(TCHAR));
    if (lr != ERROR_SUCCESS)
    {
        goto Exit;
    }
	
	StringCchCopy(wszValue, 20, TEXT("Free"));
	StringCchCopy(wszAttrib, 20, TEXT("ThreadingModel"));
	lr = RegSetValueEx(hSubKey, wszAttrib, (lstrlen(wszAttrib) + 1) * sizeof(TCHAR), REG_SZ, (LPBYTE) wszValue, (lstrlen(wszValue) + 1) * sizeof(TCHAR));
    if (lr != ERROR_SUCCESS)
    {
        goto Exit;
    }
	
	RegCloseKey(hSubKey);
    hSubKey = NULL;
    RegCloseKey(hKey);
    hKey = NULL;

    StringCchPrintf(wszPath, 256, TEXT("bmpimage\\Shellex\\ContextMenuHandlers\\%s"), GUID_CContextMenuSample);
    lr = RegCreateKeyEx(HKEY_CLASSES_ROOT, wszPath,
	                              0, NULL, 0, 0, NULL, 
	                              &hKey, &dwDisposition);



 
    StringCchCopy(wszValue, 20, TEXT("Sample CME"));
    lr = RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE) wszValue, (lstrlen(wszValue) + 1) * sizeof(TCHAR));
 
	
	if (lr != ERROR_SUCCESS)
    {
        goto Exit;
    }

	hr = S_OK;

Exit:
    if (hSubKey)
    {
        RegCloseKey(hSubKey);
    }
    if (hKey)
    {
        RegCloseKey(hKey);
    }

	return hr;
}