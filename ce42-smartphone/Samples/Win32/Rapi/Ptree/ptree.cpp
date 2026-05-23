//*******************************************************************************************
//
// Filename : ptree.c
//    
// Copyright (c) 1997 Microsoft Corporation. All rights reserved
//
//*******************************************************************************************
#include <stdio.h>
#include <tchar.h>
#include <rapi.h>

void PrintDirectory(LPWSTR Path, UINT Indent)
{
    DWORD          foundCount;
    LPCE_FIND_DATA findDataArray;

    WCHAR searchPath[MAX_PATH];
    wcscpy(searchPath, Path);
    wcscat(searchPath, L"*");

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
            wprintf( TEXT("[%s]\n"),findDataArray[i].cFileName);
            WCHAR newPath[MAX_PATH];
            wcscpy(newPath, Path);
            wcscat(newPath, findDataArray[i].cFileName);
            wcscat(newPath, L"\\");
            PrintDirectory(newPath, Indent + 1);
        }
        else
            wprintf( TEXT("%s\n"),findDataArray[i].cFileName);
    }

    if (findDataArray)
        RapiFreeBuffer(findDataArray);
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

