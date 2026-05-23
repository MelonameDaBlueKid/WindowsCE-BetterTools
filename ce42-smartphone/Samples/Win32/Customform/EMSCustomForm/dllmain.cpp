/******************************************************************************

    File: DllMain.cpp

    Purpose: DLL entry point

    Author: Matthew S. Baker (mbaker)

    Modified: 11/6/2002

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



