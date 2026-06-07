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
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
// MultiCab.cpp : 
//   Main file of .exe to install multiple cabs.
//   This sample code works in concert with the 'MCSetup.dll' sample code 
//   and a container cab ('uber-cab') to unpack all the cabs in an uber-cab.  
//   In order to do this the uber-cab file must contain:
//      1. Multiple cab files
//      2. The following registry settings:
//         - HKCU\Software\ChainedCabSample\MultiCab with an "InstallCabName" entry
//           pointing to the subkey that enumerates the cabs installed.  
//             - This registry key will be deleted by this program
//             - This subkey must have the same name as the uber-cab
//
//         - HKCU\Software\ChainedCabSample\UberCabNameHere (this is not the actual 
//           name) with the fully qualified paths of the cabs to be unpacked.
//             - This registry key will be deleted by this program.
//             - the names of the values under this key must 1, 2, 3, etc. as the
//               code assumes this.
//

#include "stdafx.h"
#include "MultiCab.h"
#include <windows.h>
#include <commctrl.h>

// Function to wait for the cab loader to finish.  This is necessary
// because if we try to unpack a cab while the loader is running 
// that second unpack attempt will silently fail to unload.
// No inputs or outputs needed.
void WaitOnLoader ()
{
    const TCHAR c_szWceLoadClass[] = TEXT("MSWCELOAD");  // Loader class name
    const int c_iLoadStartupWait   = 250;                // 250 ms pause
    const int c_iMaxInstallWait    = 600000;             // 10 minutes

    TCHAR  szClass[MAX_PATH];
    HWND   hwnd;
    DWORD  dwProcessID = 0;
    HANDLE hProcess = NULL;
    
    // It's possible that the caller of this function is executing fast
    // enough that this check will be executed before a previously invoked
    // wceload actually starts up, so pause a bit to be sure wceload has 
    // a chance to get going.
    Sleep(c_iLoadStartupWait);

    hwnd = GetWindow(GetDesktopWindow(), GW_HWNDLAST);

    do
    {
        // Look for the loader and if it is running wait for it to finish 
        GetClassName(hwnd, szClass, ARRAYSIZE(szClass));
        if (!_tcscmp(szClass, c_szWceLoadClass))
        {
            GetWindowThreadProcessId(hwnd, &dwProcessID);
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
            WaitForSingleObject(hProcess, c_iMaxInstallWait);
            CloseHandle(hProcess);
        }

        hwnd = GetWindow(hwnd, GW_HWNDPREV);
    } while (hwnd);
}


// Function to delete reg keys.
// Inputs the name of the parent of the subkey to delete and 
// the subkey to delete.  
// No output or return value.
void CleanupAppRegKey(LPCTSTR lpszParentKey, LPCTSTR lpszSubKey)
{
    HKEY hKey;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, 
                                      lpszParentKey,
                                      0,
                                      KEY_ALL_ACCESS,
                                      &hKey))
    {
        RegDeleteKey(hKey, lpszSubKey);
        RegCloseKey(hKey);
    }
}

// Function to ShellExecuteEx files (the multiple cabs to be 
// unpacked, in this case).
// Inputs the path of the file to ShellExecuteEx
// Outputs a handle to the process returned by ShellExecuteEx
// Returns a BOOL indicating if the ShellExecute is successful.
BOOL HostExec(LPCTSTR lpszFilePath, HANDLE *phProcess)
{
    BOOL bRet;
    SHELLEXECUTEINFO sei = {0};

    sei.cbSize = sizeof(sei);
    sei.nShow = SW_SHOWNORMAL;
    sei.lpFile = lpszFilePath;

    bRet = ShellExecuteEx(&sei);

    if (bRet)
    {
        *phProcess = sei.hProcess;
    }

    return bRet;
}


// WinMain
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    const TCHAR c_szAppRegPath[]  = TEXT("Software\\ChainedCabSample");
    const TCHAR c_szAppName[]     = TEXT("MultiCab");
    const TCHAR c_szKeyValue[]    = TEXT("InstallCabName");
    
    TCHAR   szRegKeyName[MAX_PATH];
    TCHAR   szRegKeyValue[MAX_PATH];
    TCHAR   szRegKeyIndex[MAX_PATH];
    TCHAR   szUberCabName[MAX_PATH];
    HKEY    hUberCabKey;
    HKEY    hKey;
    HANDLE  hProcess = NULL;
    DWORD   cKeyValues;
    DWORD   dwType;
    DWORD   dwValueSize;
    DWORD   dwIndexSize;
    DWORD   dwKey = 1;

    szUberCabName[0] = NULL;

    // Wait for wceload to finish.  This code is called by Install_Exit 
    // in the MCSetup dll, so wceload is expected to be shutting down and 
    // shouldn't take long to do so.
    WaitOnLoader();

    // Open the reg key telling us the name of the key that enumerates the 
    // packages to unpack (must be the uber-cab name)
    StringCchPrintf(szRegKeyName,ARRAYSIZE(szRegKeyName), 
                                 TEXT("%s\\%s"), 
                                 c_szAppRegPath,
                                 c_szAppName);
    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, szRegKeyName, 
                                      0, KEY_QUERY_VALUE, &hUberCabKey))
    {
        // Get the name of the uber-cab
        szRegKeyValue[0] = NULL;
        dwValueSize = sizeof(szRegKeyValue);
        if (ERROR_SUCCESS == RegQueryValueEx(hUberCabKey,
                                             c_szKeyValue,
                                             NULL,
                                             &dwType,
                                             (LPBYTE) szRegKeyValue,
                                             &dwValueSize))
        {
            // We now have the name of the key of interest.  Copy this name 
            // so we can delete the key later.
            StringCchCopy(szUberCabName, ARRAYSIZE(szUberCabName), szRegKeyValue);

            // Open the reg key that enumerates the cabs and find out how
            // many values they key has
            StringCchPrintf(szRegKeyName,ARRAYSIZE(szRegKeyName), 
                                 TEXT("%s\\%s"), 
                                 c_szAppRegPath,
                                 szRegKeyValue);
            if ((ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, szRegKeyName,
                                               0, KEY_QUERY_VALUE, &hKey))       &&
                (ERROR_SUCCESS == RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL,
                                                  NULL, &cKeyValues, NULL, NULL, NULL, NULL)))

            {
                szRegKeyIndex[0] = NULL;
                dwValueSize = sizeof(szRegKeyValue);
                dwIndexSize = sizeof(szRegKeyIndex);

                // Iterate through all of the cabs listed in the reg key, which are expected
                // to have sub-keys that increment (ie. 1, 2, 3, 4, ...)
                while(dwKey <= cKeyValues)
                {
                    _itot((int)dwKey, szRegKeyIndex, 10);  // last arg is base
                    szRegKeyValue[0] = NULL;
                    dwValueSize = sizeof(szRegKeyValue);
                    if (ERROR_SUCCESS == RegQueryValueEx(hKey,
                                                         szRegKeyIndex,
                                                         NULL, 
                                                         &dwType,
                                                         (LPBYTE) szRegKeyValue,
                                                         &dwValueSize))
                    {
                        // Execute the cab and wait for it to finish before 
                        // looping to the next cab
                        if (HostExec(szRegKeyValue, &hProcess))
                        {
                             WaitOnLoader();
                        }
                    }

                    dwKey++;
                    szRegKeyIndex[0] = NULL;
                    dwIndexSize = sizeof(szRegKeyIndex);
                }

                RegCloseKey(hKey);
            }
    
            // Clean up the key listing all the cabs to unpack
            CleanupAppRegKey(c_szAppRegPath, szUberCabName);
        }

        // Close the key with the uber-cab name
        RegCloseKey(hUberCabKey);

        // Clean up the key naming the uber-cab
        CleanupAppRegKey(c_szAppRegPath, c_szAppName);
    }
    
    return 0;
}
