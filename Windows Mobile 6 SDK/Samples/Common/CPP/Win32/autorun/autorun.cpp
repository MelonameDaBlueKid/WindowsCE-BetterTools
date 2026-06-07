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

//
// AUTORUN.CPP
//
// Sample Program that demonstrates how to handle autorun notifications
// when an MMC card is inserted/removed from the device. 
//
// The executable must be named autorun.exe and placed in a processor
// specific directory (2577) on the MMC card. 
// When the card is inserted, the application will be launched with
// "install" as its command line. When the card is removed, the application
// will be launched with "uninstall" as its command line.

#include <windows.h>
#include "resource.h"


#define INSTALL_ARGUMENT    TEXT("install")
#define UNINSTALL_ARGUMENT  TEXT("uninstall")

/*===========================================================================
 * Function Prototypes 
*/

static LPCTSTR StringFromResources(
    UINT uStringID
    );


/*===========================================================================
 * Global Variables
*/

HINSTANCE g_hInst = NULL;


static LPCTSTR StringFromResources(
	UINT uStringID
	)
{
    // NOTE: Passing NULL for the 3rd parameter of LoadString causes it to
    // return a pointer to the string in the resource file. It requires that
    // the resource file is compiled with the "/n" switch (see SDK docs).
    return (LPCTSTR) LoadString(g_hInst, uStringID, NULL, 0);
}


int WINAPI WinMain
(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPWSTR      lpCmdLine,
    int         nCmdShow
)
{
    // Save the instance handle for later use
    g_hInst = hInstance;

    // See if we've been launched because an MMC card was inserted or removed
    if (0 == lstrcmp(lpCmdLine, INSTALL_ARGUMENT)) 
    {
        // MMC card inserted
        MessageBox( NULL, StringFromResources(IDS_AUTORUN_INSERT), 
            StringFromResources(IDS_AUTORUN_TITLE), MB_ICONINFORMATION | MB_OK );
    }
    else if (0 == lstrcmp(lpCmdLine, UNINSTALL_ARGUMENT))
    {
        // MMC card removed
        MessageBox( NULL, StringFromResources(IDS_AUTORUN_REMOVE), 
            StringFromResources(IDS_AUTORUN_TITLE), MB_ICONINFORMATION | MB_OK );
    }
    else
    {
        // Unrecognised command-line
        MessageBox( NULL, StringFromResources(IDS_AUTORUN_ERROR), 
            StringFromResources(IDS_ERROR_TITLE), MB_ICONSTOP | MB_OK );        
    }

    return 0;
}
