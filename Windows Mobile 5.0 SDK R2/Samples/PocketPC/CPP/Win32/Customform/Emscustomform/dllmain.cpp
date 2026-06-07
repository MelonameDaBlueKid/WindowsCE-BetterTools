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
/******************************************************************************

    File: DllMain.cpp

    Purpose: DLL entry point

******************************************************************************/
#include "stdinc.h"
#include "dllmain.h"

HINSTANCE g_hInstance = NULL;

/******************************************************************************

    LibMain - Entry to dll 
    
******************************************************************************/
BOOL WINAPI LibMain(HINSTANCE hinst, DWORD dwReason, LPVOID lpv)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            g_hInstance = hinst;
            break;
        }
    }

    return TRUE;
}



