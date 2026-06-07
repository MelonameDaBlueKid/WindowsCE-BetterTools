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
// MCSetup.cpp : Main file for the 'setup.dll' associated with installing 
//    multiple cab files out of a container or 'uber-cab' file.
//
//    The Install_Exit export of this dll is used to invoke 'MultiCab.exe' 
//    from the install directory of the uber-cab.  MultiCab.exe will then
//    invoke wceload.exe to unpack all cab files contained in the uber-cab.
//    The name of the uber-cab is put in the InstallCabName entry of the
//    HKCU\Software\ChainedCabSample\MultiCab key by the uber-cab.
//

#include "stdafx.h"
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include "ce_setup.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) sizeof(x)/sizeof(x[0])
#endif

codeINSTALL_INIT Install_Init(
    HWND        hwndParent,
    BOOL        fFirstCall,
    BOOL        fPreviouslyInstalled,
    LPCTSTR     pszInstallDir
)
{
    return codeINSTALL_INIT_CONTINUE;
}

codeINSTALL_EXIT Install_Exit(
    HWND    hwndParent,
    LPCTSTR pszInstallDir,
    WORD    cFailedDirs,
    WORD    cFailedFiles,
    WORD    cFailedRegKeys,
    WORD    cFailedRegVals,
    WORD    cFailedShortcuts
)
{
    const TCHAR c_szSWMsft[]         = TEXT("Software\\ChainedCabSample");
    const TCHAR c_szInstallBaseDir[] = TEXT("\\Program Files");
    const TCHAR c_szMultiCabApp[]    = TEXT("MultiCab");
    const TCHAR c_szKeyValue[]       = TEXT("InstallCabName");
    
    TCHAR   szRegKeyName[MAX_PATH];
    TCHAR   szRegKeyValue[MAX_PATH];
    TCHAR   szFullMultiCabPath[MAX_PATH];
    HKEY    hKey;
    DWORD   dwType;
    DWORD   dwValueSize;

    // Open the reg key telling us the name of the uber-cab
    StringCchPrintf(szRegKeyName,ARRAYSIZE(szRegKeyName), 
                                 TEXT("%s\\%s"), 
                                 c_szSWMsft,
                                 c_szMultiCabApp);
    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, szRegKeyName, 
                                      0, KEY_QUERY_VALUE, &hKey))
    {
        // Get the name of the uber-cab
        szRegKeyValue[0] = NULL;
        dwValueSize = sizeof(szRegKeyValue);
        if (ERROR_SUCCESS == RegQueryValueEx(hKey,
                                             c_szKeyValue,
                                             NULL,
                                             &dwType,
                                             (LPBYTE) szRegKeyValue,
                                             &dwValueSize))
        {
            // We now have the name of the uber-cab.  
            // Build up the path of MultiCab.exe and execute it.
            StringCchPrintf(szFullMultiCabPath,ARRAYSIZE(szFullMultiCabPath), 
                                 TEXT("%s\\%s\\%s.exe"), 
                                 c_szInstallBaseDir,
                                 szRegKeyValue,
                                 c_szMultiCabApp);
    
            SHELLEXECUTEINFO sei = {0};
            sei.cbSize = sizeof(sei);
            sei.nShow = SW_SHOWNORMAL;

            sei.lpFile = szFullMultiCabPath;
            ShellExecuteEx(&sei);
        }

        RegCloseKey(hKey);
    }

    return codeINSTALL_EXIT_DONE;
}

codeUNINSTALL_INIT Uninstall_Init(
    HWND        hwndParent,
    LPCTSTR     pszInstallDir
)
{
    return codeUNINSTALL_INIT_CONTINUE;
}

codeUNINSTALL_EXIT Uninstall_Exit(
    HWND    hwndParent
)
{
    return codeUNINSTALL_EXIT_DONE;
}
