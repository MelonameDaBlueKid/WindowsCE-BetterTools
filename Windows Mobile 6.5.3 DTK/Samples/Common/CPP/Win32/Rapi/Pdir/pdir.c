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
/*****************************************************************************

  PROGRAM: pdblist.c

  ABSTRACT:
    This sample lists all the files in a certain directory.

******************************************************************************/
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <rapi.h>
#include <strsafe.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

WCHAR wszDirectory[MAX_PATH];

TCHAR *tszMonths[12] = {TEXT("Jan"),
                        TEXT("Feb"),
                        TEXT("Mar"),
                        TEXT("Apr"),
                        TEXT("May"),
                        TEXT("Jun"),
                        TEXT("Jul"),
                        TEXT("Aug"),
                        TEXT("Sep"),
                        TEXT("Oct"),
                        TEXT("Nov"),
                        TEXT("Dec")};

int main( int argc, char *argv[])
{
    HANDLE hFind;
    WORD wFatTime, wFatDate;
    CE_FIND_DATA wfd;
    HRESULT hRapiResult;
    HRESULT hr;
    int     nResult;

    if (2 != argc)
    {
        hr = StringCchCopyW(wszDirectory, ARRAYSIZE(wszDirectory),  L"\\*");
        if(FAILED(hr))
        {
            return 1;
        }
    }
    else
    {
#ifdef UNICODE
        nResult = MultiByteToWideChar(
                                      CP_ACP,    
                                      MB_PRECOMPOSED,
                                      argv[1],
                                      strlen(argv[1])+1,
                                      wszDirectory,
                                      ARRAYSIZE(wszDirectory));
        if(0 == nResult)
        {
            _tprintf(TEXT("Failed to convert input arguement\n"));
            return 1;
        }
#else
        hr = StringCchCopy(wszDirectory, ARRAYSIZE(wszDirectory), argv[1]);
        if(FAILED(hr))
        {
            return 1;
        }
#endif
    }

    _tprintf( TEXT("Connecting to Windows CE..."));
    
    hRapiResult = CeRapiInit();

    if (FAILED(hRapiResult))
    {
        _tprintf( TEXT("Failed\n"));
        return 1;
    }

    _tprintf( TEXT("Success\n"));

    _tprintf( wszDirectory);
        
    _tprintf( TEXT("\n"));

    hFind = CeFindFirstFile( wszDirectory, &wfd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        _tprintf( TEXT("Directory file does not exist\n"));
        return 1;
    }    
    do {
        FileTimeToDosDateTime( &(wfd.ftLastWriteTime), &wFatDate, &wFatTime);

        _tprintf( 
            TEXT("%s/%02ld/%02ld %02ld:%02ld\t"),
            tszMonths[(wFatDate >> 5) & 0x000F],
            wFatDate & 0x001F,                    
            (wFatDate >> 9) & 0x007F,
            (wFatTime >> 11) & 0x001F,
            (wFatTime >> 5) & 0x003F);

        if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            wprintf( TEXT("[%s]\n"),wfd.cFileName);
        }
        else
        {
            wprintf( TEXT("%s\n"),wfd.cFileName);
        }
    } while ( CeFindNextFile( hFind, &wfd));

    CeFindClose( hFind);

    _tprintf( TEXT("Closing connection ..."));
    CeRapiUninit();
    _tprintf( TEXT("Done\n"));
    
    return 0;
}

        
