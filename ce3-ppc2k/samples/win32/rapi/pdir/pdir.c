/*****************************************************************************
  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.

  Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

  PROGRAM: pdblist.c

  ABSTRACT:
    This sample lists all the files in a certain directory.

******************************************************************************/
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <rapi.h>

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

    if (2 != argc)
    {
        wcscpy( wszDirectory , L"\\*");
    }
    else
#ifdef UNICODE
    MultiByteToWideChar(
            CP_ACP,    
            MB_PRECOMPOSED,
            argv[1],
            strlen(argv[1])+1,
            wszDirectory,
            sizeof(wszDirectory));
#else
    _tcscpy( wszDirectory, argv[1]);
#endif

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
            wprintf( TEXT("[%s]\n"),wfd.cFileName);
        else
            wprintf( TEXT("%s\n"),wfd.cFileName);
    } while ( CeFindNextFile( hFind, &wfd));

    CeFindClose( hFind);

    _tprintf( TEXT("Closing connection ..."));
    CeRapiUninit();
    _tprintf( TEXT("Done\n"));

    return 0;
}

        
