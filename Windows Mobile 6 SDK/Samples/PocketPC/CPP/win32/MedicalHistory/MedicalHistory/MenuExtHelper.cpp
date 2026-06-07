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
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

#include "stdafx.h"
#include "MenuExtHelper.h"

// **************************************************************************
// Function Name: CreateMenuExtensionCLSIDRegKey
// 
// Purpose: Sets the CLSID reg keys
//
// Arguments:
//    IN LPTSTR ptszCLSID - Name of the CLSID reg key to be created.
//    IN LPTSTR ptszMenuExtDllName - Name of the dll to be registered
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT CreateMenuExtensionCLSIDRegKey(LPTSTR ptszCLSID, LPTSTR ptszMenuExtDllName)
{
    HRESULT hr = S_OK;
    HKEY    hKeyCLSID = NULL;
    HKEY    hKeyInproc32 = NULL;
    DWORD   dwDisposition = 0;

    CBR(ptszCLSID != NULL);
    //ptszMenuExtDllName can be null

    // Add the CLSID Registry Key
    hr = RegCreateKeyEx(HKEY_CLASSES_ROOT,
                        ptszCLSID, 
                        NULL, TEXT(""), 
                        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
                        &hKeyCLSID, &dwDisposition);
    CHR(hr);

    // Set the default value for the above key with APPNAME
    hr = RegSetValueEx(hKeyCLSID, 
                       TEXT(""), NULL, REG_SZ, 
                       (BYTE*) APPNAME, sizeof(APPNAME));
    CHR(hr);

    // Add the HKCR\CLSID\{ClassGuid}\InprocServer32 key    
    hr = RegCreateKeyEx(hKeyCLSID, TEXT("InprocServer32"), 
                        NULL, TEXT(""), REG_OPTION_NON_VOLATILE, 
                        KEY_ALL_ACCESS, NULL, 
                        &hKeyInproc32, &dwDisposition);

    CHR(hr);

    if(ptszMenuExtDllName)
    {
        // Add the file name as the default value for the 
        // HKCR\CLSID\{ClassGuid}\InprocServer32 key
        hr = RegSetValueEx(hKeyInproc32, TEXT(""), 
                           NULL, REG_SZ, (BYTE*) ptszMenuExtDllName,                    
                           sizeof(TCHAR)*(lstrlen(ptszMenuExtDllName)+1));
        CHR(hr);
    }

Error:
    if(hKeyInproc32)
    {
        RegCloseKey(hKeyInproc32);
    }

    if(hKeyCLSID)
    {
        RegCloseKey(hKeyCLSID);
    }
    
    return hr;
}

// **************************************************************************
// Function Name: CreateMenuExtensionRegKey
// 
// Purpose: Sets the menu extension reg keys
//
// Arguments:
//    IN LPTSTR pszKey - Name of the key to be set
//
// Return Values:
//    HRESULT indicating success or failure
//
HRESULT CreateMenuExtensionRegKey(LPTSTR pszKey)
{
    HKEY    hKeyCLSID = NULL;
    DWORD   dwDisposition;
    HRESULT hr = S_OK;

    // Create the KEY
    hr = RegCreateKeyEx(HKEY_LOCAL_MACHINE, pszKey, NULL, 
                        TEXT(""), REG_OPTION_NON_VOLATILE, 
                        KEY_ALL_ACCESS, NULL, 
                        &hKeyCLSID, &dwDisposition);
    CHR(hr);
    
    // Add a default value string for the Menu Extension
    // THIS IS VERY IMPORTANT... if there is no default value for this key
    // it WILL NOT be used as a menu extension
    hr = RegSetValueEx(hKeyCLSID, TEXT(""), NULL, 
                       REG_SZ, (BYTE*) NULLVAL, sizeof(NULLVAL));
    
    CHR(hr);

    RETAILMSG(TRUE, (L"%s: Created reg keys %s",APPNAME, pszKey));
   
Error:
    if(hKeyCLSID)
    {
         RegCloseKey(hKeyCLSID);
    }
    
    return hr;   
}



