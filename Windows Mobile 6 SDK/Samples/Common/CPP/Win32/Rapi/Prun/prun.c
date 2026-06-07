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
  PROGRAM: pRun.c


******************************************************************************/
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <rapi.h>
#include <strsafe.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

WCHAR wszProgram[MAX_PATH];

int main( int argc, char *argv[])
{
    HRESULT hRapiResult;
    HRESULT hr;
    PROCESS_INFORMATION pi;    

    if (2 != argc)
    {
        _tprintf( TEXT("Syntax: PRUN <WinCE EXE>"));
        return 1;
    }
    else
    {
#ifdef UNICODE
        int nResult = MultiByteToWideChar(
                        CP_ACP,    
                        MB_PRECOMPOSED,
                        argv[1],
                        strlen(argv[1])+1,
                        wszProgram,
                        ARRAYSIZE(wszProgram));
        if(0 == nResult)
        {
            return 1;
        }
#else
        hr = StringCchCopy(wszProgram, ARRAYSIZE(wszProgram), argv[1]);
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




        
