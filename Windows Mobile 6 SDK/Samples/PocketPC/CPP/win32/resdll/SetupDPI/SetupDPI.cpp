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
// SetupDPI.cpp
//

#include "stdafx.h"
#include <strsafe.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof((x)[0]))

codeINSTALL_INIT Install_Init(
    HWND        hwndParent,
    BOOL        fFirstCall,
    BOOL        fPreviouslyInstalled,
    LPCTSTR     pszInstallDir)
{
    return codeINSTALL_INIT_CONTINUE;
}

//
// This function performs some post-processing after we have installed
// a CAB file which contains some 96 and some 192 DPI resource files.
//
// We have a list of files stored as values under a regkey.  Each file
// should be named \path\to\file_xxx.dll, where "xxx" is the DPI of 
// the resource file (96 or 192).  If the file is correct for our device,
// we rename it to file.dll, otherwise, we delete it.
//
// When done, we delete the list of files.
//
codeINSTALL_EXIT Install_Exit(
    HWND    hwndParent,
    LPCTSTR pszInstallDir,
    WORD    cFailedDirs,
    WORD    cFailedFiles,
    WORD    cFailedRegKeys,
    WORD    cFailedRegVals,
    WORD    cFailedShortcuts)
{
    DWORD nSystemDPI = 96;
    {
        TCHAR szGetRealDPI[MAX_PATH + 40];
        PROCESS_INFORMATION pi;
        
        ::SHGetSpecialFolderPath(hwndParent, szGetRealDPI, CSIDL_WINDOWS, FALSE);
        ::StringCchCat(szGetRealDPI, ARRAYSIZE(szGetRealDPI), _T("\\GetRealDPI.EXE")); 
        ::CreateProcess(szGetRealDPI, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, &pi);
        ::WaitForSingleObject(pi.hProcess, 10000);
        ::GetExitCodeProcess(pi.hProcess, &nSystemDPI);
        ::CloseHandle(pi.hProcess);
        ::DeleteFile(szGetRealDPI);
    }

    HKEY hKey;
    LPCTSTR szRegKey = _T("Software\\Microsoft\\SetupDPI");
    if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegKey, 0, 0, &hKey) != ERROR_SUCCESS)
    {
        return codeINSTALL_EXIT_DONE;
    }
    
    for (INT i = 0;; i++)
    {
        TCHAR szName[256];
        TCHAR szLongName[256];
        DWORD ccName = sizeof(szName) / sizeof(szName[0]) - 1;
        szName[ccName] = '\0';

        if (::RegEnumValue(hKey, i, szName, &ccName, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
        {
            break;
        }

        ::StringCchCopy(szLongName, ARRAYSIZE(szLongName), szName);
        LPTSTR pUnderscore = _tcschr(szName, '_');
        LPTSTR pDot = _tcschr(pUnderscore, '.');
        if (!pUnderscore || !pDot)
        {
            continue;
        }
        DWORD nFileDPI = _ttoi(pUnderscore + 1);
        ::StringCchCopy(pUnderscore, ARRAYSIZE(szName) - (pUnderscore - szName), pDot);

        if (nSystemDPI != nFileDPI)
        {
            ::DeleteFile(szLongName);
        }
        else
        {
            ::MoveFile(szLongName, szName);
        }
    }

    ::RegCloseKey(hKey);
    ::RegDeleteKey(HKEY_LOCAL_MACHINE, szRegKey);
    return codeINSTALL_EXIT_DONE;
}

codeUNINSTALL_INIT Uninstall_Init(
    HWND        hwndParent,
    LPCTSTR     pszInstallDir)
{
    return codeUNINSTALL_INIT_CONTINUE;
}

codeUNINSTALL_EXIT Uninstall_Exit(
    HWND    hwndParent)
{
    return codeUNINSTALL_EXIT_DONE;
}
