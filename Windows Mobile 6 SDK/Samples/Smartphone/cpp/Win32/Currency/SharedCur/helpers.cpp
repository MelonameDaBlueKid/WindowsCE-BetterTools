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


#include "stdafx.h"
#include "helpers.h"

/****************************************************************************

  ****************************************************************************/
HRESULT ActivatePreviousInstance(
    const TCHAR* pszClass,
    const TCHAR* pszTitle,
    BOOL* pfActivated
    )
{
    HRESULT hr = S_OK;
    int cTries;
    HANDLE hMutex = NULL;

    *pfActivated = FALSE;
    cTries = 5;
    while(cTries > 0)
    {
        hMutex = CreateMutex(NULL, FALSE, pszClass); // NOTE: We don't want to own the object.
        if(NULL == hMutex)
        {
            // Something bad happened, fail.
            hr = E_FAIL;
            goto Exit;
        }

        if(GetLastError() == ERROR_ALREADY_EXISTS)
        {
            HWND hwnd;

            CloseHandle(hMutex);
            hMutex = NULL;

            // There is already an instance of this app
            // running.  Try to bring it to the foreground.

            hwnd = FindWindow(pszClass, pszTitle);
            if(NULL == hwnd)
            {
                // It's possible that the other window is in the process of being created...
                Sleep(500);
                hwnd = FindWindow(pszClass, pszTitle);
            }

            if(NULL != hwnd)
            {
                // Set the previous instance as the foreground window

                // The "| 0x01" in the code below activates
                // the correct owned window of the
                // previous instance's main window.
                SetForegroundWindow((HWND) (((ULONG) hwnd) | 0x01));

                // We are done.
                *pfActivated = TRUE;
                break;
            }

            // It's possible that the instance we found isn't coming up,
            // but rather is going down.  Try again.
            cTries--;
        }
        else
        {
            // We were the first one to create the mutex
            // so that makes us the main instance.  'leak'
            // the mutex in this function so it gets cleaned
            // up by the OS when this instance exits.
            break;
        }
    }

    if(cTries <= 0)
    {
        // Someone else owns the mutex but we cannot find
        // their main window to activate.
        hr = E_FAIL;
        goto Exit;
    }

Exit:
    return(hr);
}


/**************************************************************************************

    Variants of printf should be avoided as they don't allow re-ordering of parameters.
    This can be important when an application is required to work in multiple languages
    without code changes.

 **************************************************************************************/
DWORD FormatMessageHelp(
    TCHAR* pszOut,
    UINT cchOut,
    const TCHAR* pszFormat,
    ...
    )
{
    va_list marker;
    DWORD dwRet;

    va_start(marker, pszFormat);
    dwRet = FormatMessage(FORMAT_MESSAGE_FROM_STRING,
            pszFormat, 0, 0, pszOut, cchOut, &marker);
    va_end(marker);
    return dwRet;
}


/**************************************************************************************

 **************************************************************************************/
int FormattedMessageBox(
    HWND hwnd,
    UINT uType,
    HINSTANCE hInst,
    UINT idsCaption,
    UINT idsFormat,
    ...
    )
{
    va_list marker;
    DWORD dwRet;
    // If these buffers are too small, you will get truncation
    TCHAR szCaption[100];
    TCHAR szFormat[200];
    TCHAR szText[ARRAYSIZE(szFormat) + 100];

    if(0 == LoadString(hInst, idsCaption, szCaption, ARRAYSIZE(szCaption)) ||
       0 == LoadString(hInst, idsFormat, szFormat, ARRAYSIZE(szFormat)))
    {
        // Couldn't load a needed string.
        return(0);
    }

    va_start(marker, idsFormat);
    dwRet = FormatMessage(FORMAT_MESSAGE_FROM_STRING,
            szFormat, 0, 0, szText, ARRAYSIZE(szText), &marker);
    va_end(marker);
    if(0 == dwRet)
    {
        // Something bad happened in FormatMessage.
        return(0);
    }

    return(MessageBox(hwnd, szText, szCaption, uType));

}


/**************************************************************************************
    Format strings for errors can use the following replacement strings:
    %1 = Attempt at a user understandable version of the hresult
    %2 = hex version of the hresult


 **************************************************************************************/
void DisplayError(
    HWND hWndOwner,
    HINSTANCE hInst,
    UINT idsCaption,
    UINT idsFormat,
    HRESULT hrDisplay
    )
{
    // If these buffers are too small, you will get truncation
    // (lets hope the error wasn't caused by lack of stack space :-)
    TCHAR szCaption[100];
    TCHAR szFormat[200];
    TCHAR szText[ARRAYSIZE(szFormat) + 200];
    TCHAR szErrorHex[15];
    TCHAR szErrorDescription[15];

    // Attempt to recover instead of bailing on errors...

    if(0 == LoadString(hInst, idsCaption, szCaption, ARRAYSIZE(szCaption)))
        {
        szCaption[0] = 0;
        }

    if(0 == LoadString(hInst, idsFormat, szFormat, ARRAYSIZE(szFormat)))
        {
        szFormat[0] = 0;
        }

    wsprintf(szErrorHex, TEXT("0x%08x"), hrDisplay);
    _tcscpy(szErrorDescription, szErrorHex); // TODO: Implement hresult descriptions...
    
    if(FAILED(FormatMessageHelp(szText, ARRAYSIZE(szText), szFormat, szErrorDescription, szErrorHex)))
        {
        wsprintf(szText, TEXT("Error: 0x%08x"), hrDisplay);
        }

    MessageBox(hWndOwner, szText, szCaption, MB_OK | MB_ICONERROR);

}


/****************************************************************************

  ****************************************************************************/
void GetSystemTimeAsFileTime(FILETIME* pSystemAsFileTime)
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, pSystemAsFileTime);
}


/****************************************************************************

  ****************************************************************************/
HRESULT GetFileTimeForDate(int iYear, int iMonth, int iDay, FILETIME* pft)
{
    HRESULT hr = S_OK;
    SYSTEMTIME st;

    ASSERT(pft);
    
    ZeroMemory(&st, sizeof(st));
    st.wYear = (WORD)iYear;
    st.wMonth = (WORD)iMonth;
    st.wDay = (WORD)iDay;
    if(!SystemTimeToFileTime(&st, pft))
        {
        // This could happen if we were passed
        // a bogus day
        ASSERT(FALSE);
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

Error:
    return(hr);

}

/****************************************************************************
    Used by SubclassEditForKeyTranslation
 ****************************************************************************/
LRESULT EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRet = 0;
    WNDPROC pfn = (WNDPROC)GetWindowLong(hwnd, GWL_USERDATA);
    
    switch(uMsg)
        {
        case WM_CHAR:
            if(TEXT('*') == wParam)
                {
                lRet = CallWindowProc(pfn, hwnd, uMsg, TEXT('.'), lParam);
                }
            else
                {
                goto DoDefault;
                }
            break;

        DoDefault:
        default:
            lRet = CallWindowProc(pfn, hwnd, uMsg, wParam, lParam); 
            break;
        }
    return(lRet);
}

/****************************************************************************
    Helper to make an edit control show a . when * is pressed.
 ****************************************************************************/
HRESULT SubclassEditForKeyTranslation(HWND hwndEdit)
{
    HRESULT hr = S_OK;

    if(GetWindowLong(hwndEdit, GWL_USERDATA))
        {
        ASSERT(FALSE); // Need an empty GWL_USERDATA to save old pointer
        hr = E_FAIL;
        goto Error;
        }

    SetLastError(0);
    SetWindowLong(hwndEdit, GWL_USERDATA, GetWindowLong(hwndEdit, GWL_WNDPROC));
    if(0 != GetLastError())
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    SetWindowLong(hwndEdit, GWL_WNDPROC, (LONG)EditSubclassProc);
    if(0 != GetLastError())
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }
    
Error:
    return hr;
}    


