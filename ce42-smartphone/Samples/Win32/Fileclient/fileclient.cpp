// ************************************************************
// fileclient.cpp
// 
// The meat of the program
//
// Copyright 2003 Microsoft Corporation, All Rights Reserved
//
// ************************************************************

#include "precomp.h"


// **************************************************************************
// Function Name: HandleMessage
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN LPPUSHMSG pPushMsg – contains push message data
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Save into a file and execute the file.  The file name is 
//    in the X-MS-FileName header.  By default, the file is saved 
//    in the Windows directory.
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
        
    // Get the X-MS-FileName header value.
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

    if (FALSE == SHGetSpecialFolderPath(NULL, szFilePath, CSIDL_WINDOWS, FALSE))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // +1 for '\'
    ASSERT(_tcslen(szFilePath) + _tcslen(pszFileName) + 1 < MAX_PATH);

    _tcscat(szFilePath, TEXT("\\"));
    _tcscat(szFilePath, pszFileName);

    // Get the X-MS-Params header value.
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
//    IN LPPUSHMSG pPushMsg – contains push message data
//    IN LPTSTR pszFilePath – path of file to be saved
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
// Purpose: save push message body to file.
//
// Arguments:
//    IN LPTSTR pszFileName – name of file to be saved
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
// Purpose: save push message body to file.
//
// Arguments:
//    IN LPTSTR pszFileName – name of file to be saved
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description: 
//    Check to see if the file is allowed to be downloaded onto the device.  
//    The list of allowable extensions is under 
//    HKLM\Security\AllowedExtensions.  Each extension is a name.
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


