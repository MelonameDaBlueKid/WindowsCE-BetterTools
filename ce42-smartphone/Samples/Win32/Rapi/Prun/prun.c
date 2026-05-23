/*****************************************************************************
  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.

  Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

  PROGRAM: pdblist.c

  ABSTRACT:
    This sample executes a program on the WinCE device.

******************************************************************************/
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <rapi.h>

WCHAR wszProgram[MAX_PATH];

int main( int argc, char *argv[])
{
    HRESULT hRapiResult;
    PROCESS_INFORMATION pi;

    if (2 != argc)
    {
        _tprintf( TEXT("Syntax: PRUN <WinCE EXE>"));
        return 1;
    }
    else
#ifdef UNICODE
    MultiByteToWideChar(
            CP_ACP,    
            MB_PRECOMPOSED,
            argv[1],
            strlen(argv[1])+1,
            wszProgram,
            sizeof(wszProgram));
#else
    _tcscpy( wszProgram, argv[1]);
#endif

    _tprintf( TEXT("Connecting to Windows CE..."));
    
    hRapiResult = CeRapiInit();

    if (FAILED(hRapiResult))
    {
        _tprintf( TEXT("Failed\n"));
        return 1;
    }

    _tprintf( TEXT("Success\n"));

    if (!CeCreateProcess(
            wszProgram,
            NULL,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            NULL,
            &pi))
    {
        _tprintf( TEXT("CreateProcess failed with Errorcode = %ld\n"), CeGetLastError());
    }
    else
    {
        CeCloseHandle( pi.hProcess);
        CeCloseHandle( pi.hThread);
    }
        
    _tprintf( TEXT("Closing connection ..."));
    CeRapiUninit();
    _tprintf( TEXT("Done\n"));

    return 0;
}




        
