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
// ************************************************************
// setup.cpp
// 
// Implements Setup DLL that calls DMProcessConfigXML to allow 
// EdbRapiServer.dll to receive CeRapiInvoke calls.
//
// ************************************************************

#include "stdafx.h"
#include "Cfgmgrapi.h"

HINSTANCE g_hinstModule;

LPCWSTR g_wszFavoriteXml = 
L"<wap-provisioningdoc>   <characteristic type=\"Metabase\"> "
L"   <characteristic type=\"RAPI\\Windows\\EdbRapiServer.dll\\*\"> <parm name=\"rw-access\" value=\"3\"/> <parm name=\"access-role\" value=\"152\"/> "
L" <!-- 152 maps to \"CARRIER_TPS | USER_AUTH | MANAGER\" --> </characteristic> </characteristic></wap-provisioningdoc>";

BOOL APIENTRY DllMain(
    HANDLE hModule, 
    DWORD  ul_reason_for_call, 
    LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            g_hinstModule = (HINSTANCE)hModule;
            break;
    }
    return TRUE;
}


// **************************************************************************
// Function Name: Install_Init
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent  handle to the parent window
//    IN BOOL fFirstCall  indicates that this is the first time this function is being called
//    IN BOOL fPreviouslyInstalled  indicates that the current application is already installed
//    IN LPCTSTR pszInstallDir  name of the user-selected install directory of the application
//
// Return Values:
//    codeINSTALL_INIT
//    returns install status
//
// Description:  
//    The Install_Init function is called before installation begins.
//    User will be prompted to confirm installation.
// **************************************************************************
SETUP_API codeINSTALL_INIT Install_Init(
    HWND        hwndParent,
    BOOL        fFirstCall,
    BOOL        fPreviouslyInstalled,
    LPCTSTR     pszInstallDir
    )
{
    HRESULT hr         = E_FAIL;
    
    LPWSTR wszOutput   = NULL;

    // Process the XML.
    hr = DMProcessConfigXML(g_wszFavoriteXml, CFGFLAG_PROCESS, &wszOutput);
    CHR(hr);

Error:
    // The caller must delete the XML returned from DMProcessConfigXML.
    if (wszOutput != NULL)
    {
        delete [] wszOutput;
    }
    if (hr == S_OK)
    {
        return codeINSTALL_INIT_CONTINUE;
    } 
    else
    {
        return codeINSTALL_INIT_CANCEL;
    }
}


// **************************************************************************
// Function Name: Install_Exit
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent        handle to the parent window
//    IN LPCTSTR pszInstallDir  name of the user-selected install directory of 
//                              the application
//
// Return Values:
//    returns install status: codeINSTALL_EXIT
// **************************************************************************
SETUP_API codeINSTALL_EXIT Install_Exit(
    HWND    hwndParent,
    LPCTSTR pszInstallDir,      
    WORD    cFailedDirs,
    WORD    cFailedFiles,
    WORD    cFailedRegKeys,
    WORD    cFailedRegVals,
    WORD    cFailedShortcuts
    )
{
    return codeINSTALL_EXIT_DONE;
}


// **************************************************************************
// Function Name: Uninstall_Init
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent  handle to the parent window
//    IN LPCTSTR pszInstallDir  name of the user-selected install directory of the application
//
// Return Values:
//    returns uninstall status: codeUNINSTALL_INIT
//
// **************************************************************************
SETUP_API codeUNINSTALL_INIT Uninstall_Init(
    HWND        hwndParent,
    LPCTSTR     pszInstallDir
    )
{
   return codeUNINSTALL_INIT_CONTINUE;
}


// **************************************************************************
// Function Name: Uninstall_Exit
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent  handle to the parent window
//
// Return Values:   
//    returns uninstall status: codeUNINSTALL_EXIT
//
// **************************************************************************
SETUP_API codeUNINSTALL_EXIT Uninstall_Exit(
    HWND    hwndParent
    )
{
    return codeUNINSTALL_EXIT_DONE;
}
