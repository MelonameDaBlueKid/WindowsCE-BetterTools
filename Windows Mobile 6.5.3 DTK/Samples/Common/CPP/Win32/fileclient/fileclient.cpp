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
// fileclient.cpp
// 
// The meat of the program
//
//
// ************************************************************

#include "precomp.h"


// **************************************************************************
// Function Name: HandleMessage
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN LPPUSHMSG pPushMsg  contains push message data
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Save into a file and execute the file.  The file name is 
//    in the X-MyCompany-FileName header.  By default, the file is saved 
//    in the My Documents directory.
// **************************************************************************
HRESULT HandleMessage(LPPUSHMSG pPushMsg)
{
    HRESULT hr                      = S_OK;
    LPTSTR  pszFileName             = NULL;
    LPTSTR  pszParams               = NULL;
    TCHAR   szFilePath[MAX_PATH]    = {0};
    SHELLEXECUTEINFO sei            = {0};

    if (NULL == pPushMsg->pbBody)
    {
        return E_INVALIDARG;;
    }
        
    // Get the X-MyCompany-FileName header value.
    hr = GetHeader(pPushMsg->szHeaders, c_szFileNameHeaderName, &pszFileName);
    CHR(hr);

    if (NULL == pszFileName)
    {
        CHR(E_INVALIDARG);
    }

    // Check the security on this file.
    hr = CheckSecurity(pszFileName);
    CHR(hr);

    // Get the user's permission.
    hr = GetUserPermission(pszFileName);
    CHR(hr);

    // Get the path to the personal documents folder.
    if (FALSE == SHGetSpecialFolderPath(NULL, szFilePath, CSIDL_PERSONAL, FALSE))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // +1 for '\'
    ASSERT(_tcslen(szFilePath) + _tcslen(pszFileName) + 1 < MAX_PATH);

    hr = StringCchCat(szFilePath, MAX_PATH, TEXT("\\"));
    CHR(hr);

    hr = StringCchCat(szFilePath, MAX_PATH, pszFileName);
    CHR(hr);

    // Get the X-MyCompany-Params header value.
    hr = GetHeader(pPushMsg->szHeaders, c_szParamsHeaderName, &pszParams);
    CHR(hr);

    hr = SaveFile(pPushMsg, szFilePath);
    CHR(hr);
    
    // Execute the file.
    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.lpFile = szFilePath;
    sei.lpParameters = pszParams;

    if (FALSE == ShellExecuteEx(&sei))
    {
        RETAILMSG(1, (TEXT("CreateProcess Failed")));
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

Error:
    delete[] pszFileName;
    delete[] pszParams;
    
    return hr;
}



// **************************************************************************
// Function Name: SaveFile
// 
// Purpose: save push message body to file.
//
// Arguments:
//    IN LPPUSHMSG pPushMsg  contains push message data
//    IN LPTSTR pszFilePath  path of file to be saved
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Save the push message body into a file.  
// **************************************************************************
HRESULT SaveFile(LPPUSHMSG pPushMsg, LPTSTR pszFilePath)
{
    HRESULT hr              = S_OK;
    HANDLE  hFile           = INVALID_HANDLE_VALUE;  
    DWORD   cbWritten       = 0;

    hFile = CreateFile(pszFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    if (FALSE == WriteFile(hFile, pPushMsg->pbBody, pPushMsg->cbBodyLength, &cbWritten, NULL))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    ASSERT(pPushMsg->cbBodyLength == cbWritten);

Error:
    CloseHandle(hFile);

    return hr;

}


// **************************************************************************
// Function Name: GetUserPermission
// 
// Purpose: Get a user's permission.
//
// Arguments:
//    IN LPTSTR pszFileName  name of file to be saved
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Save the push message body into a file.  
// **************************************************************************
HRESULT GetUserPermission(LPTSTR pszFileName)
{
    HRESULT hr              = S_OK;
    LPCTSTR pszFormatText   = NULL;
    LPTSTR  pszDisplayText  = NULL;
    int     iReply          = 0;

    pszFormatText = (LPTSTR)LoadString(g_hInst, IDS_INSTALL_PERMISSION, NULL, 0);
    if (NULL == pszFormatText)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    if (0 == FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY, 
                           pszFormatText, 0, 0, reinterpret_cast<TCHAR*>(&pszDisplayText), 
                           256, reinterpret_cast<va_list*>(&pszFileName)))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    ASSERT(pszDisplayText);

    iReply = MessageBox(NULL, pszDisplayText,
                        (LPCTSTR)LoadString(g_hInst, IDS_PERMISSIONTITLE, NULL, 0),
                        MB_YESNO | MB_ICONQUESTION);

    if (IDNO == iReply)
    {
        CHR(E_ACCESSDENIED);
    }

    hr = S_OK;

Error:
    LocalFree(pszDisplayText);

    return hr;
}


// **************************************************************************
// Function Name: CheckSecurity
// 
// Purpose: Check whether a file is allowed to be saved and executed.
//
// Arguments:
//    IN LPTSTR pszFileName  name of file to be saved
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description: 
//    Check to see if the file is allowed to be downloaded onto the device.  
//    The list of allowable extensions is under 
//    HKLM\Security\FileClient\AllowedExtensions.  Each extension is a name.
// **************************************************************************
HRESULT CheckSecurity(LPTSTR pszFileName)
{
    HRESULT hr                  = S_OK;
    HKEY    hKey                = NULL;
    DWORD   dwValueCount        = 0;
    DWORD   cchMaxValueNameLen  = 0;
    DWORD   cchValueNameLen     = 0;
    DWORD   dwType              = 0;
    DWORD   i                   = 0;
    LPTSTR  pszValueName        = NULL;
    LPTSTR  pszExt              = NULL;

    // For security reasons, disallow ".." or '\' in the file name.
    if (NULL != _tcsstr(pszFileName, TEXT("..")) ||
        NULL != _tcschr(pszFileName, TEXT('\\')) ||
        NULL != _tcschr(pszFileName, TEXT('/')))
    {
        CHR(E_INVALIDARG);
    }

    pszExt = _tcsrchr(pszFileName, TEXT('.'));
    if (NULL == pszExt)
    {
        CHR(E_INVALIDARG);
    }

    if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_szAllowedExtKey, 0, 0, &hKey))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // Get information the number of values under this key.
    if (ERROR_SUCCESS != RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &dwValueCount,
                                         &cchMaxValueNameLen, NULL, NULL, NULL))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // Allocate enough space to hold the longest value length.
    cchMaxValueNameLen++;
    pszValueName = new TCHAR[cchMaxValueNameLen];
    CPR(pszValueName);

    // Loop through each value (extension) and see if any match this file's extension.
    hr = E_ACCESSDENIED;
    for (i = 0; i < dwValueCount; i++)
    {
        cchValueNameLen = cchMaxValueNameLen;
        if (ERROR_SUCCESS != RegEnumValue(hKey, i, pszValueName, &cchValueNameLen, NULL, &dwType, NULL, NULL))
        {
            CHR(HRESULT_FROM_WIN32(GetLastError()));
        }

        if (0 == _tcsicmp(pszExt, pszValueName))
        {
            hr = S_OK;
            break;
        }
    }



Error:
    if (NULL != hKey)
    {
        RegCloseKey(hKey);
    }

    delete[] pszValueName;

    return hr;
}


