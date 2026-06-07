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

#include "common.h"

// Global Count of references to this DLL.
UINT g_cDLLRefCount = 0;

#define EXTENSION_KEY   TEXT("SOFTWARE\\Microsoft\\Shell\\Extensions\\ContextMenus\\Inbox\\")
#define READVIEW_SUBKEY TEXT("Read_View")


/////////////////////////////////////////////////
// DllGetClassObject
//
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void ** ppObject)
{
    HRESULT hr = E_FAIL;
    MyClassFactory * pFactory = NULL;
    
    if(rclsid == CLSID_READVIEW_SK_MENUEXT)
    {
        pFactory = new MyClassFactory();
        CPR(pFactory);

        hr = pFactory->QueryInterface(riid, ppObject);
        CHR(hr);
    }
    else
    {
        hr = CLASS_E_CLASSNOTAVAILABLE;
        goto Error;
    }

Error:

    RELEASE_OBJ(pFactory);
    return hr;
}





/////////////////////////////////////////////////
// DllCanUnloadNow
//
STDAPI DllCanUnloadNow()
{
    return g_cDLLRefCount ? S_FALSE : S_OK;
}





/////////////////////////////////////////////////
// DllRegisterServerHelper
//
HRESULT DllRegisterServerHelper(LPCWSTR szSubKey, LPCTSTR szString)
{
    HRESULT hr = E_FAIL;
    HKEY hKeyCLSID = NULL;
    HKEY hKeyInproc32 = NULL;
    DWORD dwDisposition;
    HMODULE hModule;
    TCHAR szName[MAX_PATH+1];
   
    if (!(ERROR_SUCCESS == RegCreateKeyEx(HKEY_CLASSES_ROOT, szSubKey, NULL, TEXT(""),
                                          REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 
                                          NULL, &hKeyCLSID, &dwDisposition)))
    {
        goto Error;
    }
   
    if (!(ERROR_SUCCESS == RegSetValueEx(hKeyCLSID, TEXT(""), NULL, REG_SZ, (BYTE*) szString,
                                         sizeof(TCHAR) * (lstrlen(szString) + 1))))
    {
        goto Error;
    }

    if (!(ERROR_SUCCESS == RegCreateKeyEx(hKeyCLSID, TEXT("InprocServer32"), NULL, TEXT(""),
                                          REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
                                          &hKeyInproc32, &dwDisposition)))
    {
        goto Error;
    }
 
    hModule = GetModuleHandle(IMAGENAME);
    if (hModule)
    {
        if (GetModuleFileName(hModule, szName, ARRAYSIZE(szName)))
        {
            if (!(ERROR_SUCCESS == RegSetValueEx(hKeyInproc32, TEXT(""), NULL, 
                                                 REG_SZ, (BYTE *) szName,
                                                 sizeof(TCHAR) * (lstrlen(szName) + 1))))
            {
                goto Error;
            }
        }
        else
        {       
            goto Error;
        }            
    }

    hr = S_OK;
   
Error:
    if (hKeyInproc32)
    {
        RegCloseKey(hKeyInproc32);
    }

    if (hKeyCLSID)
    {
        RegCloseKey(hKeyCLSID);
    }

    return hr;    
}


/////////////////////////////////////////////////
// RegisterMenuExtension
//
//  A helper function which creates the entries in 
//      SOFTWARE\\Microsoft\\Shell\\Extensions\\ContextMenus\\Inbox\\
//      allowing this DLL to be used as a Menu Extension
//
HRESULT RegisterMenuExtension(LPCWSTR szKey, LPCTSTR szName)
{
    HRESULT hr = E_FAIL;
    HKEY hKey = NULL;
    DWORD dwDisposition;
   
    if (!(ERROR_SUCCESS == RegCreateKeyEx(HKEY_LOCAL_MACHINE, szKey, NULL, TEXT(""),
                                          REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
                                          &hKey, &dwDisposition)))
    {
        goto Error;
    }

    if (!(ERROR_SUCCESS == RegSetValueEx(hKey, TEXT(""), NULL, REG_SZ, (BYTE*) szName,
                                         sizeof(TCHAR) * (lstrlen(szName) + 1))))
    {
        goto Error;
    }


    hr = S_OK;
Error:
    if (hKey)
    {
        RegCloseKey(hKey);
    }

    return hr;    

}


/////////////////////////////////////////////////
// DllRegisterServer
//
STDAPI DllRegisterServer(void)
{
    HRESULT hr;

    hr = DllRegisterServerHelper(TEXT("CLSID\\{") CLSIDTEXT_READVIEW_SK_MENUEXT TEXT("}"),
                                 TEXT("ReadView Menu Extension"));
    CHR(hr);


    hr = RegisterMenuExtension(EXTENSION_KEY READVIEW_SUBKEY TEXT("\\{") CLSIDTEXT_READVIEW_SK_MENUEXT TEXT("}"),
                               TEXT("ReadView Menu Extension"));
    CHR(hr);

Error:
    return hr;
}



/////////////////////////////////////////////////
// DllUnregisterServer
//
HRESULT DllUnregisterServerHelper(HKEY hkey, LPCWSTR szSubKey)
{
    HRESULT hr = E_FAIL;

    if (!(ERROR_SUCCESS == RegDeleteKey(hkey, szSubKey)))
    {
        goto Error;
    }

    hr = S_OK;
    
Error:
    return hr;
}


/////////////////////////////////////////////////
// DllUnregisterServer
//
STDAPI DllUnregisterServer(void)
{
    HRESULT hr = E_FAIL;
    
    // Delete the CLSID keys
    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, 
            TEXT("CLSID\\{") CLSIDTEXT_READVIEW_SK_MENUEXT TEXT("}\\InprocServer32"));
    CHR(hr);

    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, 
            TEXT("CLSID\\{") CLSIDTEXT_READVIEW_SK_MENUEXT TEXT("}"));
    CHR(hr);
    
    
    // Delete the Menu Extension keys
    hr = DllUnregisterServerHelper(HKEY_LOCAL_MACHINE, 
            EXTENSION_KEY READVIEW_SUBKEY TEXT("\\{") CLSIDTEXT_READVIEW_SK_MENUEXT TEXT("}"));
    CHR(hr);
    
    hr = S_OK;

Error:
    return hr;
}



