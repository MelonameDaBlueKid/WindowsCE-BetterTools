// ************************************************************
// utils.cpp
// 
// Utility functions
//
// Copyright 2003 Microsoft Corporation, All Rights Reserved
//
// ************************************************************

#include "precomp.h"


// **************************************************************************
// Function Name: GetHeader
// 
// Purpose: returns the value of a specified header.
//
// Arguments:
//    IN LPCTSTR pszAllHeaders – all headers in http format
//    IN LPCTSTR pszHeaderName – name of header whose value is desired
//    OUT LPTSTR* ppszHeaderValue – value of header
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Parse the headers for a specific one.  Each header is assumed to be 
//    in the following format:
//      field-name ":" [ field-value ]
// **************************************************************************
HRESULT GetHeader(LPCTSTR pszAllHeaders, LPCTSTR pszHeaderName, LPTSTR *ppszHeaderValue)
{
    HRESULT hr                  = S_OK;
    LPCTSTR pszStartHeader      = pszAllHeaders;
    LPCTSTR pszEndHeader        = NULL;
    LPTSTR  pszHeaderValue      = NULL;
    LPTSTR  pszHeaderNameEnd    = NULL;
    DWORD   cchHeaderName       = 0;

    if (NULL == pszAllHeaders)
    {
        return hr;
    }

    cchHeaderName = _tcslen(pszHeaderName);

    while (TEXT('\0') != *pszStartHeader)
    {
        // Skip leading white space.
        while (TEXT('\0') != *pszStartHeader && _istspace(*pszStartHeader))
        {
            pszStartHeader++;
        }

        if (TEXT('\0') == *pszStartHeader)
        {
            break;
        }

        // Find end of header name.
        pszHeaderNameEnd = _tcschr(pszStartHeader, TEXT(':'));
        if (NULL == pszHeaderNameEnd)
        {
            CHR(E_FAIL);
        }

        // Trim end of header name.
        pszHeaderNameEnd--;
        while (pszStartHeader <= pszHeaderNameEnd && _istspace(*pszHeaderNameEnd))
        {
            pszEndHeader--;
        }

        // Find end of header line.
        pszEndHeader = _tcsstr(pszStartHeader, TEXT("\r\n"));
        if (NULL == pszEndHeader)
        {
            pszEndHeader = pszStartHeader + _tcslen(pszStartHeader);
        }

        if (((LONG)cchHeaderName == pszHeaderNameEnd - pszStartHeader + 1) &&
            (0 == _tcsnicmp(pszHeaderName, pszStartHeader, cchHeaderName)))
        {
            // Find start of header value.
            pszStartHeader = _tcschr(pszStartHeader, TEXT(':'));
            if (NULL == pszStartHeader)
            {
                CHR(E_INVALIDARG);
            }

            pszStartHeader++;

            // Skip leading white space.
            while (pszStartHeader < pszEndHeader && _istspace(*pszStartHeader))
            {
                pszStartHeader++;
            }

            // Skip trailing white space.
            while (pszStartHeader < pszEndHeader && _istspace(*pszEndHeader))
            {
                pszEndHeader--;
            }

            if (pszStartHeader >= pszEndHeader)
            {
                // Empty value.
                hr = CopyString(TEXT(""), -1, &pszHeaderValue);
                CPR(hr);
            }
            else
            {
                hr = CopyString(pszStartHeader, pszEndHeader - pszStartHeader + 1, &pszHeaderValue);
                CHR(hr);
            }

            break;
        }
        else
        {
            // Go to next header.
            pszStartHeader = pszEndHeader;
        }
    }

    // Hand off memory.
    *ppszHeaderValue = pszHeaderValue;
    pszHeaderValue = NULL;

Error:
    delete[] pszHeaderValue;

    return hr;
}


// **************************************************************************
// Function Name: CopyString
// 
// Purpose: make a copy of a string.
//
// Arguments:
//    IN LPCTSTR pszSource – source string
//    IN DWORD cchSourceLen – length of source string (without NULL-terminating character)
//    OUT LPTSTR* ppszOut – copy of source string
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    If pszSource has a NULL-terminating character, then cchSourceLen 
//    can be -1.
// **************************************************************************
HRESULT CopyString(LPCTSTR pszSource, DWORD cchSourceLen, LPTSTR* ppszOut)
{
    HRESULT hr = S_OK;

    if (NULL != pszSource)
    {
        if (-1 == cchSourceLen)
        {
            cchSourceLen = _tcslen(pszSource);
        }

        *ppszOut = new TCHAR[cchSourceLen + 1];
        CPR(*ppszOut);

        _tcsncpy(*ppszOut, pszSource, cchSourceLen);

        // Null terminate string.
        (*ppszOut)[cchSourceLen] = TEXT('\0');
    }

Error:
    return hr;
}

