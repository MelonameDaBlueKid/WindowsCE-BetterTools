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
#include "classfactory.h"

// Global Count of references to this DLL.
UINT g_cDLLRefCount = 0;
HINSTANCE g_hInstDLL = NULL;

#define EXTENSION_KEY TEXT("SOFTWARE\\Microsoft\\Shell\\Extensions\\ContextMenus\\Contacts\\")
#define SOFTKEY_SUBKEY TEXT("Main_Menu")
#define CONTEXT_SUBKEY TEXT("Main_ContextMenu")

///////////////////////////////////////////////////////////////////////////////
// DllMain
//
BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{    

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            g_hInstDLL = (HINSTANCE)hinstDLL;
            break;           
    }
    return TRUE;  // Success code path
}


///////////////////////////////////////////////////////////////////////////////
// DllGetClassObject  
//
//  This function retrieves the class object from a DLL object handler or object 
//  application. DllGetClassObject is called from within the CoGetClassObject 
//  function when the class context is a DLL.
// 
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void ** ppObject)
{
    HRESULT hr = S_OK;
    MyClassFactory * pFactory = NULL;

    // Figure out which CLSID is being instantiated and then instantiate
    // that class using MyClassFactory
   
    if(rclsid == CLSID_CONTACTS_SK_MENUEXT)
    {
        // The Softkey Menu Extension - Smartfone and PPC
        pFactory = new MyClassFactory(Softkey);
        CPR(pFactory);
        CHR(pFactory->QueryInterface(riid, ppObject));       
    }
    else if(rclsid == CLSID_CONTACTS_CONTEXT_MENUEXT)
    {
        // The Softkey Menu Extension - PPC only
        pFactory = new MyClassFactory(Context);
        CPR(pFactory);
        CHR(pFactory->QueryInterface(riid, ppObject));       
    }
    else
    {
        CHR(CLASS_E_CLASSNOTAVAILABLE);       
    }

Error:
    if (pFactory)
    {
        pFactory->Release();
    }
    
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
    HRESULT hr = S_OK;
    HKEY hKeyCLSID = NULL;
    HKEY hKeyInproc32 = NULL;
    DWORD dwDisposition;
    TCHAR szName[MAX_PATH+1];

    // Add the CLSID Registry Key
    if (!(ERROR_SUCCESS == RegCreateKeyEx(HKEY_CLASSES_ROOT, szSubKey, NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyCLSID, &dwDisposition)))
    {
        CHR(E_FAIL);
    }

    // Set the default value for the above key with the string passed in as szString
    if (!(ERROR_SUCCESS == RegSetValueEx(hKeyCLSID, TEXT(""), NULL, REG_SZ, (BYTE*) szString, sizeof(TCHAR) * (lstrlen(szString) + 1))))
    {
        CHR(E_FAIL);
    }

    // Add the HKCR\CLSID\{ClassGuid}\InprocServer32 key
    if (!(ERROR_SUCCESS == RegCreateKeyEx(hKeyCLSID, TEXT("InprocServer32"), 
        NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
        &hKeyInproc32, &dwDisposition)))
    {
        CHR(E_FAIL);
    }

    if (g_hInstDLL)
    {
        // Get this DLL's file name from the Module handle 
        if (GetModuleFileName(g_hInstDLL, szName, ARRAYSIZE(szName)))
        {
            // Add the file name as the default value for the 
            // HKCR\CLSID\{ClassGuid}\InprocServer32 key
            if (!(ERROR_SUCCESS == RegSetValueEx(hKeyInproc32, TEXT(""), NULL, REG_SZ, (BYTE *) szName, sizeof(TCHAR) * (lstrlen(szName) + 1))))
            {
                CHR(E_FAIL);
            }
        }
        else
        {       
            CHR(E_FAIL);
        }            
    }
    else
    {
        // Should never hit this. By the time this gets called, g_hInstDLL should have been set.
        CHR(E_FAIL);
    }
  
   
Error:
    if (hKeyInproc32)
    {
        RegCloseKey(hKeyInproc32);
    }

    if (hKeyCLSID)
    {
        RegCloseKey(hKeyCLSID);
    }

    DEBUGMSG(1, (TEXT("* * * Contacts MenuExt Sample:  DllRegisterServerHelper returning hr: %X"), hr));
    return hr;    
}


///////////////////////////////////////////////////////////////////////////////
// RegisterMenuExtension
//
//  A helper function called by DLLRegisterServer. It creates the entries in 
//      SOFTWARE\\Microsoft\\Shell\\Extensions\\ContextMenus\\Contacts\\
//      registering this DLL to be used as a Menu Extension
//
//  NOTE: Every Menu Extension must have a string identifier for it. With out
//  a string name - the menu extension will not be instantiated by the Shell
//
HRESULT RegisterMenuExtension(LPCWSTR szKey, LPCTSTR szName)
{
    HRESULT hr = S_OK;
    HKEY hKey = NULL;
    DWORD dwDisposition;

    // Create the KEY
    if (!(ERROR_SUCCESS == RegCreateKeyEx(HKEY_LOCAL_MACHINE, szKey, 
                        NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 
                        NULL, &hKey, &dwDisposition)))
    {
        CHR(E_FAIL);
    }

    // Add a default value string for the Menu Extension
    // THIS IS VERY IMPORTANT... if there is no default value for this key
    // it WILL NOT be used as a menu extension
    if (!(ERROR_SUCCESS == RegSetValueEx(hKey, TEXT(""), NULL, REG_SZ, (BYTE*) szName, sizeof(TCHAR) * (lstrlen(szName) + 1))))
    {
        CHR(E_FAIL);
    }
   
Error:
    if (hKey)
    {
        RegCloseKey(hKey);
    }

    DEBUGMSG(1, (TEXT("* * * Contacts MenuExt Sample:  RegisterMenuExtension returning hr: %X"), hr));
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
    HRESULT hr = S_OK;

    if (!(ERROR_SUCCESS == RegDeleteKey(hkey, szSubKey)))
    {
        CHR(E_FAIL);
    }
    
    
Error:
    DEBUGMSG(1, (TEXT("* * * Contacts MenuExt Sample:  DllUnregisterServerHelper returning hr: %X"), hr));
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer
//
//  This method is called when RegSvrCE /U is called.
//
STDAPI DllUnregisterServer(void)
{
    HRESULT hr = S_OK;
    
    // Delete the CLSID keys
    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_CONTACTS_SK_MENUEXT TEXT("}\\InprocServer32"));
    
    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_CONTACTS_SK_MENUEXT TEXT("}"));

    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_CONTACTS_CONTEXT_MENUEXT TEXT("}\\InprocServer32"));
   
    hr = DllUnregisterServerHelper(HKEY_CLASSES_ROOT, TEXT("CLSID\\{") CLSIDTEXT_CONTACTS_CONTEXT_MENUEXT TEXT("}"));
      
    // Delete the Menu Extension keys
    hr = DllUnregisterServerHelper(HKEY_LOCAL_MACHINE, EXTENSION_KEY SOFTKEY_SUBKEY TEXT("\\{") CLSIDTEXT_CONTACTS_SK_MENUEXT TEXT("}"));
    
    hr = DllUnregisterServerHelper(HKEY_LOCAL_MACHINE, EXTENSION_KEY CONTEXT_SUBKEY TEXT("\\{") CLSIDTEXT_CONTACTS_CONTEXT_MENUEXT TEXT("}"));      

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
    HRESULT hr = S_OK;

    hr = DllRegisterServerHelper(TEXT("CLSID\\{") CLSIDTEXT_CONTACTS_SK_MENUEXT TEXT("}"), TEXT("Contacts Softkey Menu Extension"));
    CHR(hr);


    hr = RegisterMenuExtension(EXTENSION_KEY SOFTKEY_SUBKEY TEXT("\\{") CLSIDTEXT_CONTACTS_SK_MENUEXT TEXT("}"), TEXT("Contacts Softkey Menu Extension"));
    CHR(hr);


    hr = DllRegisterServerHelper(TEXT("CLSID\\{") CLSIDTEXT_CONTACTS_CONTEXT_MENUEXT TEXT("}"), TEXT("Contacts Context Menu Extension"));
    CHR(hr);

    hr = RegisterMenuExtension(EXTENSION_KEY CONTEXT_SUBKEY TEXT("\\{") CLSIDTEXT_CONTACTS_CONTEXT_MENUEXT TEXT("}"), TEXT("Contacts Context Menu Extension"));
    CHR(hr); 

Error:
    if (FAILED(hr))
    {
        DllUnregisterServer();
    }
    return hr;
}









