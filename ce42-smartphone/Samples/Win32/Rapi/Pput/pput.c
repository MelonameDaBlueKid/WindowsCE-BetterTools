/*****************************************************************************
  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.

  Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

  PROGRAM: pdblist.c

  ABSTRACT:
    This sample copies a file from the host computer to the Windows CE device.


******************************************************************************/
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <rapi.h>

TCHAR tszSrcFile[MAX_PATH];
WCHAR wszDestFile[MAX_PATH];
BYTE  Buffer[4096];



int main( int argc, char *argv[])
{
    HANDLE hSrc, hDest, hFind;
    WIN32_FIND_DATA wfd;
    HRESULT hRapiResult;
    DWORD dwAttr, dwNumRead, dwNumWritten;

    if (3 != argc)
    {
        _tprintf( TEXT("Syntax: PPUT <host file> <wce file>\n"));
        return 1;
    }
    else

#ifdef UNICODE
    MultiByteToWideChar(
            CP_ACP,    
            MB_PRECOMPOSED,
            argv[1],
            strlen(argv[1])+1,
            tszSrcFile,
            sizeof(tszSrcFile));
#else
    _tcscpy( tszSrcFile, argv[1]);
#endif
    MultiByteToWideChar(
            CP_ACP,    
            MB_PRECOMPOSED,
            argv[2],
            strlen(argv[2])+1,
            wszDestFile,
            sizeof(wszDestFile));

    hFind = FindFirstFile( tszSrcFile, &wfd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        _tprintf( TEXT("Source/host file does not exist\n"));
        return 1;
    }    
    FindClose( hFind);

    if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        _tprintf( TEXT("Source/host file specifies a directory\n"));
        return 1;
    }

    _tprintf( TEXT("Connecting to Windows CE..."));
    
    hRapiResult = CeRapiInit();

    if (FAILED(hRapiResult))
    {
        _tprintf( TEXT("Failed\n"));
        return 1;
    }

    _tprintf( TEXT("Success\n"));

    dwAttr = CeGetFileAttributes( wszDestFile);
    
    if (0xFFFFFFFF  != dwAttr)
    {
        if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
        {
            //Just a directory was specified so we will have to get the filename from the src spec.
            wcscat( wszDestFile, TEXT("\\"));
#ifdef UNICODE
            wcscpy( wszDestFile+wcslen(wszDestFile), wfd.cFileName);
#else
            MultiByteToWideChar(
                    CP_ACP,    
                    MB_PRECOMPOSED,
                    wfd.cFileName,
                    strlen(wfd.cFileName)+1,
                    wszDestFile+wcslen(wszDestFile),
                    sizeof(wszDestFile)-wcslen(wszDestFile));
#endif
        }
        else
        {
            _tprintf( TEXT("File already exists.  Do you want to overwrite ? (Y/N)"));
            if ( 'N' == toupper(getchar()))
            {
                _tprintf( TEXT("File not updateded\n"));
                goto CloseConnection;
            }
        }
    }

    hSrc = CreateFile(
                tszSrcFile,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (INVALID_HANDLE_VALUE == hSrc)
    {
        _tprintf( TEXT("Unable to open source/host file"));
        return 1;
    }

    hDest = CeCreateFile(
                wszDestFile,
                GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);

    if (INVALID_HANDLE_VALUE == hDest )
    {
        _tprintf( TEXT("Unable to open WinCE file"));
        return 1;
    }
#ifdef UNICODE
    wprintf( TEXT("Copying %s to WCE:%s\n"), tszSrcFile, wszDestFile);
#else
    printf( TEXT("Copying %s to WCE:%S\n"), tszSrcFile, wszDestFile);
#endif
    
    do
    {
        if (ReadFile(
                hSrc,
                &Buffer,
                sizeof(Buffer),
                &dwNumRead,
                NULL))
        {
            if (!CeWriteFile(
                    hDest,
                    &Buffer,
                    dwNumRead,
                    &dwNumWritten,
                    NULL))
            {
                _tprintf( TEXT("Error !!! Writing WinCE file"));
                goto FatalError;
            }
        }
        else
        {
            _tprintf( TEXT("Error !!! Reading source file"));
            goto FatalError;
        }
        _tprintf( TEXT("."));                                        
    } while (dwNumRead);
    _tprintf( TEXT("\n"));    
FatalError:
    CeCloseHandle( hDest);
    CloseHandle (hSrc);
CloseConnection:
    _tprintf( TEXT("Closing connection ..."));
    CeRapiUninit();
    _tprintf( TEXT("Done\n"));

    return 0;
}




        
