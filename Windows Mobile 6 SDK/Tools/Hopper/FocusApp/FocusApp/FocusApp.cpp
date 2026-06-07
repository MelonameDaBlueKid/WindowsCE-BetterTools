//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

//
// FocusApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////

#define ONE_SECOND      1000
#define TEN_SECONDS     (10 * ONE_SECOND)
#define TWENTY_SECONDS  (2 * TEN_SECONDS)
#define ONE_MINUTE      (3 * TWENTY_SECONDS)
#define FIVE_MINUTES    (5 * ONE_MINUTE)
#define FIFTEEN_MINUTES (3 * FIVE_MINUTES)
 
// Adjust the following to suit your needs
#define SLEEP_TIMEOUT TEN_SECONDS
TCHAR *g_pszAppName = TEXT("\\windows\\wmPlayer.exe");
 
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR tszTmp[MAX_PATH];
    PROCESS_INFORMATION piProcInfo; 
 
    while(TRUE)
    {
        wsprintf(tszTmp, TEXT(" ... Relaunching: %s"), g_pszAppName);
        OutputDebugString(tszTmp);
        if(! CreateProcess(g_pszAppName, NULL, NULL, NULL, FALSE, 0, NULL, 
                NULL, NULL, &piProcInfo))
        {
            goto Error;
        }
 
        // Adjust this value to suit your needs above
        Sleep(SLEEP_TIMEOUT);
    }
Error: 
    // Error condition - should never get here.
    wsprintf(tszTmp, TEXT("ERROR: could not launch %s, last error: %d"), 
        g_pszAppName, GetLastError());
    OutputDebugString(tszTmp);
    return(TRUE);
}
