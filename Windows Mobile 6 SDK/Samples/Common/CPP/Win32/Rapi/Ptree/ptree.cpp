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
//*******************************************************************************************
//
// Filename : ptree.c
//    
//
//*******************************************************************************************
#include <stdio.h>
#include <tchar.h>
#include <rapi.h>
#include <strsafe.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

void PrintDirectory(LPWSTR Path, UINT Indent)
{
    DWORD          foundCount;
    LPCE_FIND_DATA findDataArray;
    HRESULT        hr;

    WCHAR searchPath[MAX_PATH];

    hr = StringCchCopyW(searchPath, ARRAYSIZE(searchPath), Path);
    if(FAILED(hr))
    {
        return;
    }
    hr = StringCchCatW(searchPath, ARRAYSIZE(searchPath), L"*");
    if(FAILED(hr))
    {
        return;
    }

    if(!CeFindAllFiles(searchPath,
                        FAF_ATTRIBUTES | FAF_NAME,
                        &foundCount,
                        &findDataArray))
    {
        _tprintf( TEXT("*** CeFindAllFiles failed. ***\n"));
        return;
    }

    if(!foundCount)
        return;

    for(UINT i = 0; i < foundCount; i++)
    {
        for(UINT indCount = 0; indCount < Indent; indCount++)
            _tprintf( TEXT("  "));

        if(findDataArray[i].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            _tprintf( TEXT("[%s]\n"),findDataArray[i].cFileName);
            WCHAR newPath[MAX_PATH];
            hr = StringCchCopyW(newPath, ARRAYSIZE(newPath), Path);
            if(FAILED(hr))
            {
                return;            
            }
            hr = StringCchCatW(newPath, ARRAYSIZE(newPath), findDataArray[i].cFileName);
            if(FAILED(hr))
            {
                return;
            }            
            hr = StringCchCatW(newPath, ARRAYSIZE(newPath), L"\\");
            if(FAILED(hr))
            {
                return;
            }
            PrintDirectory(newPath, Indent + 1);
        }
        else
        {
            _tprintf( TEXT("%s\n"),findDataArray[i].cFileName);
        }
    }

    if (findDataArray)
    {
        RapiFreeBuffer(findDataArray);
    }
}

void main()
{
    HRESULT hRapiResult;

    _tprintf( TEXT("Connecting to Windows CE..."));
    
    hRapiResult = CeRapiInit();

    if (FAILED(hRapiResult))
    {
        _tprintf( TEXT("Failed\n"));
        return;
    }

    _tprintf( TEXT("Success\n"));

    PrintDirectory( L"\\", 0);

    CeRapiUninit();
}

