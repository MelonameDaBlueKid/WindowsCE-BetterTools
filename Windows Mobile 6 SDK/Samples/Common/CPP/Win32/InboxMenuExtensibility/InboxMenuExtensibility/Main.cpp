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


#define EXTENSION_KEY TEXT("SOFTWARE\\Microsoft\\Shell\\Extensions\\ContextMenus\\Inbox\\")
#define SOFTKEY_SUBKEY TEXT("List_View")
#define CONTEXT_SUBKEY TEXT("List_View_Context")


///////////////////////////////////////////////////////////////////////////////
// DllGetClassObject  
//
//  This function retrieves the class object from a DLL object handler or object 
//  application. DllGetClassObject is called from within the CoGetClassObject 
//  function when the class context is a DLL.
// 
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void ** ppObject)
{
    HRESULT hr = E_FAIL;
    MyClassFactory * pFactory = NULL;

    // Figure out which CLSID is being instantiated and then instantiate
    // that class using MyClassFactory
   
    if(rclsid == CLSID_INBOX_SK_MENUEXT)
    {
        // The Softkey Menu Extension - Smartfone and PPC
        pFactory = new MyClassFactory(Softkey);
        if(!pFactory)
        {
            hr = E_OUTOFMEMORY;
            goto Error;
        }

        if(FAILED(hr = pFactory->QueryInterface(riid, ppObject)))
        {
            goto Error;
        }
    }
    else if(rclsid == CLSID_INBOX_CONTEXT_MENUEXT)
    {
        // The Softkey Menu Extension - PPC only
        pFactory = new MyClassFactory(Context);
        if(!pFactory)
        {
            hr = E_OUTOFMEMORY;
            goto Error;
        }

        if(FAILED(hr = pFactory->QueryInterface(riid, ppObject)))
        {
            goto Error;
        }
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





///////////////////////////////////////////////////////////////////////////////
// DllCanUnloadNow
//
//  Returns true IF and ONLY IF there are no ref counts to this DLL
//
STDAPI DllCanUnloadNow()
{
    return g_cDLLRefCount ? S_FALSE : S_OK;
}





///////////////////////////////////////////////////////////////////////////////
// DllRegisterServerHelper
//
//  A helper function called by DLLRegisterServer
// 
HRESULT DllRegisterServerHelper(LPCWSTR szSubKey, LPCTSTR szString)
{
    HRESULT hr = E_FAIL;
    HKEY hKeyCLSID = NULL;
    HKEY hKeyInproc32 = NULL;
    DWORD dwDisposition;
    HMODULE hModule;
    TCHAR szName[MAX_PATH+1];

    // Add the CLSID Registry Key
    if (!(ERROR_SUCCESS == RegCreateKeyEx(HKEY_CLASSES_ROOT, szSubKey, NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyCLSID, &dwDisposition)))
    {
        goto Error;
    }

    // Set the default value for the above key with the string passed in as szString
    if (!(ERROR_SUCCESS == RegSetValueEx(hKeyCLSID, TEXT(""), NULL, REG_SZ, (BYTE*) szString, sizeof(TCHAR) * (lstrlen(szString) + 1))))
    {
        goto Error;
    }

    // Add the HKCR\CLSID\{ClassGuid}\InprocServer32 key
    if (!(ERROR_SUCCESS == RegCreateKeyEx(hKeyCLSID, TEXT("InprocServer32"), 
        NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
        &hKeyInproc32, &dwDisposition)))
    {
        goto Error;
    }

    // Get this DLL's Module handle
    hModule = GetModuleHandle(IMAGENAME);
    if (hModule)
    {
        // Get this DLL's file name from the Module handle 
        if (GetModuleFileName(hModule, szName, ARRAYSIZE(szName)))
        {
            // Add the file name as the default value for the 
            // HKCR\CLSID\{ClassGuid}\InprocServer32 key
            if (!(ERROR_SUCCESS == RegSetValueEx(hKeyInproc32, TEXT(""), NULL, REG_SZ, (BYTE *) szName, sizeof(TCHAR) * (lstrlen(szName) + 1))))
            {
                goto Error;
            }
        }
        else
        {       
            goto Error;
        }            
    }
    else 
    {
        goto Error;
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


///////////////////////////////////////////////////////////////////////////////
// RegisterMenuExtension
//
//  A helper function called by DLLRegisterServer. It creates the entries in 
//      SOFTWARE\\Microsoft\\Shell\\Extensions\\ContextMenus\\Inbox\\
//      registering this DLL to be used as a Menu Extension
//
//  NOTE: Every Menu Extension must have a string identifier for it. With out
//  a string name - the menu extension will not be instantiated by the Shell
//
HRESULT RegisterMenuExtension(LPCWSTR szKey, LPCTSTR szName)
{
    HRESULT hr = E_FAIL;
    HKEY hKey = NULL;
    DWORD dwDisposition;

    // Create the KEY
    if (!(ERROR_SUCCESS == RegCreateKeyEx(HKEY_LOCAL_MACHINE, szKey, 
                        NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 
                        NULL, &hKey, &dwDisposition)))
    {
        goto Error;
    }

    // Add a default value string for the Menu Extension
    // THIS IS VERY IMPORTANT... if there is no default value for this key
    // it WILL NOT be used as a menu extension
    if (!(ERROR_SUCCESS == RegSetValueEx(hKey, TEXT(""), NULL, REG_SZ, (BYTE*) szName, sizeof(TCHAR) * (lstrlen(szName) + 1))))
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


///////////////////////////////////////////////////////////////////////////////
// DllRegisterServer
//
//  This method is called when RegSvrCE is called.
//  This method will call DllRegisterServerHelper and RegisterMenuExtension
//
STDAPI DllRegisterServer(void)
{
    HRESULT hr;

    hr = DllRegisterServerHelper(TEXT("CLSID\\{") CLSIDTEXT_INBOX_SK_MENUEXT TEXT("}"), TEXT("Inbox Softkey Menu Extension"));
    CHR(hr);


    hr = RegisterMenuExtension(EXTENSION_KEY SOFTKEY_SUBKEY TEXT("\\{") CLSIDTEXT_INBOX_SK_MENUEXT TEXT("}"), TEXT("Inbox Softkey Menu Extension"));
    CHR(hr);


    hr = DllRegisterServerHelper(TEXT("CLSID\\{") CLSIDTEXT_INBOX_CONTEXT_MENUEXT TEXT("}"), TEXT("Inbox Context Menu Extension"));
    CHR(hr);

    hr = RegisterMenuExtension(EXTENSION_KEY CONTEXT_SUBKEY TEXT("\\{") CLSIDTEXT_INBOX_CONTEXT_MENUEXT TEXT("}"), TEXT("Inbox Context Menu Extension"));
    CHR(hr); 

Error:
    return hr;
}



///////////////////////////////////////////////////////////////////////////////
// DllUnregisterServerHelper
//
//  A helper function called by DLLUnregisterServer. 
//  This simply deletes a regkey pointed to hKey\szSubKey
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


///////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer
//
//  This method is called when RegSvrCE /U is called.
//
STDAPI DllUnregisterServer(void)
{
    HRESULT hr = E_FAIL;
    
    // Delete the CLSID keys
    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_INBOX_SK_MENUEXT TEXT("}\\InprocServer32"));
    CHR(hr);

    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_INBOX_SK_MENUEXT TEXT("}"));
    CHR(hr);

    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_INBOX_CONTEXT_MENUEXT TEXT("}\\InprocServer32"));
    CHR(hr);

    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_INBOX_CONTEXT_MENUEXT TEXT("}"));
    CHR(hr);
    
    
    // Delete the Menu Extension keys
    hr = DllUnregisterServerHelper(HKEY_LOCAL_MACHINE, EXTENSION_KEY SOFTKEY_SUBKEY TEXT("\\{") CLSIDTEXT_INBOX_SK_MENUEXT TEXT("}"));
    CHR(hr);

    hr = DllUnregisterServerHelper(HKEY_LOCAL_MACHINE, EXTENSION_KEY CONTEXT_SUBKEY TEXT("\\{") CLSIDTEXT_INBOX_CONTEXT_MENUEXT TEXT("}"));
    CHR(hr);   
    
    hr = S_OK;

Error:
    return hr;
}



