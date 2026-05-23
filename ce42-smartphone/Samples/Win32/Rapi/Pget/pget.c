/*****************************************************************************
  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.

  Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

  PROGRAM: pdblist.c

  ABSTRACT:
    This sample copies a file from the WinCE device and copies it to the
 Host Computer.


******************************************************************************/
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <rapi.h>

TCHAR wszSrcFile[MAX_PATH];
WCHAR tszDestFile[MAX_PATH];
BYTE  Buffer[4096];


int main( int argc, char *argv[])
{
    HANDLE hSrc, hDest, hFind;
    CE_FIND_DATA wfd;
    HRESULT hRapiResult;
    DWORD dwAttr, dwNumRead, dwNumWritten;

    if (3 != argc)
    {
        _tprintf( TEXT("Syntax: pget <wce file> <host/destination file>\n"));
        return 1;
    }
    else

    MultiByteToWideChar(
                CP_ACP,    
                MB_PRECOMPOSED,
                argv[1],
                strlen(argv[1])+1,
                wszSrcFile,
                sizeof(wszSrcFile));

#ifdef UNICODE
    MultiByteToWideChar(
                CP_ACP,    
                MB_PRECOMPOSED,
                argv[2],
                strlen(argv[2])+1,
                tszDestFile,
                sizeof(tszDestFile));
#else
    _tcscpy( tszSrcFile, argv[2]);
#endif

    _tprintf( TEXT("Connecting to Windows CE..."));
    
    hRapiResult = CeRapiInit();

    if (FAILED(hRapiResult))
    {
        _tprintf( TEXT("Failed\n"));
        return 1;
    }

    _tprintf( TEXT("Success\n"));


    hFind = CeFindFirstFile( wszSrcFile, &wfd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        _tprintf( TEXT("Windows CE file does not exist\n"));
        return 1;
    }    
    CeFindClose( hFind);

    if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        _tprintf( TEXT("Windows CE file specifies a directory\n"));
        return 1;
    }

    dwAttr = GetFileAttributes( tszDestFile);
    
    if (0xFFFFFFFF  != dwAttr)
    {
        if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
        {
            //Just a directory was specified so we will have to get the filename from the src spec.
            wcscat( tszDestFile, TEXT("\\"));
#ifdef UNICODE
            wcscpy( tszDestFile+wcslen(tszDestFile), wfd.cFileName);
#else
            WideCharToMultiByte(
                        CP_ACP,    
                        0,
                        wfd.cFileName,
                        wcslen(wfd.cFileName)+1,
                        wszDestFile+strlen(wszDestFile),
                        sizeof(wszDestFile)-strlen(wszDestFile),
                        NULL,
                        FALSE);
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

    hSrc = CeCreateFile(
                wszSrcFile,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (INVALID_HANDLE_VALUE == hSrc)
    {
        _tprintf( TEXT("Unable to open Windows CE file"));
        return 1;
    }

    hDest = CreateFile(
                tszDestFile,
                GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);

    if (INVALID_HANDLE_VALUE == hDest)
    {
        _tprintf( TEXT("Unable to open host/destination file"));
        return 1;
    }
#ifdef UNICODE
    wprintf( TEXT("Copying WCE:%s to %s\n"), wszSrcFile, tszDestFile);
#else
    printf( TEXT("Copying WCE:%S to %s\n"), tszSrcFile, tszDestFile);
#endif
    
    do
    {
        if (CeReadFile(
                hSrc,
                &Buffer,
                sizeof(Buffer),
                &dwNumRead,
                NULL))
        {
            if (!WriteFile(
                    hDest,
                    &Buffer,
                    dwNumRead,
                    &dwNumWritten,
                    NULL))
            {
                _tprintf( TEXT("Error !!! Writing hostfile"));
                goto FatalError;
            }
        }
        else
        {
            _tprintf( TEXT("Error !!! Reading Windows CE file"));
            goto FatalError;
        }
        _tprintf( TEXT("."));                                        
    } while (dwNumRead);
    _tprintf( TEXT("\n"));    
FatalError:
    CeCloseHandle( hSrc);
    CloseHandle (hDest);
CloseConnection:
    _tprintf( TEXT("Closing connection ..."));
    CeRapiUninit();
    _tprintf( TEXT("Done\n"));

    return 0;
}




        
