// ************************************************************
// setup.cpp
// 
// Implementation of DllMain and setup functions
//
// Copyright 2003 Microsoft Corporation, All Rights Reserved
//
// ************************************************************

#include "stdafx.h"

HINSTANCE g_hinstModule;


BOOL APIENTRY DllMain(
    HANDLE hModule, 
    DWORD  ul_reason_for_call, 
    LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            g_hinstModule = (HINSTANCE)hModule;
            break;
    }
    return TRUE;
}


// **************************************************************************
// Function Name: Install_Init
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent – handle to the parent window
//    IN BOOL fFirstCall – indicates that this is the first time this function is being called
//    IN BOOL fPreviouslyInstalled – indicates that the current application is already installed
//    IN LPCTSTR pszInstallDir – name of the user-selected install directory of the application
//
// Return Values:
//    codeINSTALL_INIT
//    returns install status
//
// Description:  
//    The Install_Init function is called before installation begins.
//    User will be prompted to confirm installation.
// **************************************************************************
SETUP_API codeINSTALL_INIT Install_Init(
    HWND        hwndParent,
    BOOL        fFirstCall,     // is this the first time this function is being called?
    BOOL        fPreviouslyInstalled,
    LPCTSTR     pszInstallDir
    )
{
    int iReply = IDYES;

    iReply = MessageBox(hwndParent, 
                        (LPCTSTR)LoadString(g_hinstModule, IDS_INSTALL_PERMISSION, NULL, 0),
                        (LPCTSTR)LoadString(g_hinstModule, IDS_CLIENT_NAME, NULL, 0),
                        MB_YESNO | MB_ICONQUESTION);

    if (IDNO == iReply)
    {
        return codeINSTALL_INIT_CANCEL;
    }

    return codeINSTALL_INIT_CONTINUE;
}


// **************************************************************************
// Function Name: Install_Exit
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent – handle to the parent window
//    IN LPCTSTR pszInstallDir – name of the user-selected install directory of the application
//
// Return Values:
//    codeINSTALL_EXIT
//    returns install status
//
// Description:  
//    Register query client with the PushRouter as part of installation.
//    Only the first two parameters really count.
// **************************************************************************
SETUP_API codeINSTALL_EXIT Install_Exit(
    HWND    hwndParent,
    LPCTSTR pszInstallDir,      // final install directory
    WORD    cFailedDirs,
    WORD    cFailedFiles,
    WORD    cFailedRegKeys,
    WORD    cFailedRegVals,
    WORD    cFailedShortcuts
    )
{
    PROCESS_INFORMATION pi      = {0};
    DWORD               dwRes   = 0;
    codeINSTALL_EXIT    cie     = codeINSTALL_EXIT_UNINSTALL;

    if (FALSE == CreateProcess((LPCTSTR)LoadString(g_hinstModule, IDS_CLIENT_NAME, NULL, 0), TEXT("/register"), NULL, NULL, NULL, 0, NULL, NULL, NULL, &pi))
    {
        goto Error;
    }

    dwRes = WaitForSingleObject(pi.hProcess, REGISTER_WAIT_TIME);
    if (WAIT_OBJECT_0 != dwRes)
    {
        goto Error;
    }

    // Registered...Check result.
    if (FALSE == GetExitCodeProcess(pi.hProcess, &dwRes))
    {
        goto Error;
    }

    ASSERT(STILL_ACTIVE != dwRes);

    if (0 != dwRes)
    {
        goto Error;
    }

    cie = codeINSTALL_EXIT_DONE;

Error:
    return cie;
}


// **************************************************************************
// Function Name: Uninstall_Init
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent – handle to the parent window
//    IN LPCTSTR pszInstallDir – name of the user-selected install directory of the application
//
// Return Values:
//    codeUNINSTALL_INIT
//    returns uninstall status
//
// Description:  
//    Query the device data using the query xml in the push message,
//    and send the query results back to the server.
// **************************************************************************
SETUP_API codeUNINSTALL_INIT Uninstall_Init(
    HWND        hwndParent,
    LPCTSTR     pszInstallDir
    )
{
    int                 iReply  = IDYES;
    PROCESS_INFORMATION pi      = {0};
    DWORD               dwRes   = 0;
    codeUNINSTALL_INIT  cui     = codeUNINSTALL_INIT_CANCEL;


    iReply = MessageBox(hwndParent, 
                        (LPCTSTR)LoadString(g_hinstModule, IDS_UNINSTALL_PERMISSION, NULL, 0),
                        (LPCTSTR)LoadString(g_hinstModule, IDS_CLIENT_NAME, NULL, 0),
                        MB_YESNO | MB_ICONQUESTION);
    if (IDNO == iReply)
    {
        goto Error;
    }

    if (FALSE == CreateProcess((LPCTSTR)LoadString(g_hinstModule, IDS_CLIENT_NAME, NULL, 0), TEXT("/unregister"), NULL, NULL, NULL, 0, NULL, NULL, NULL, &pi))
    {
        goto Error;
    }

    dwRes = WaitForSingleObject(pi.hProcess, REGISTER_WAIT_TIME);
    if (WAIT_OBJECT_0 != dwRes)
    {
        goto Error;
    }

    // Registered...Check result.
    if (FALSE == GetExitCodeProcess(pi.hProcess, &dwRes))
    {
        goto Error;
    }

    ASSERT(STILL_ACTIVE != dwRes);

    if (0 != dwRes)
    {
        goto Error;
    }

    cui = codeUNINSTALL_INIT_CONTINUE;

Error:
    return cui;
}


// **************************************************************************
// Function Name: Uninstall_Exit
// 
// Purpose: processes the push message.
//
// Arguments:
//    IN HWND hwndParent – handle to the parent window
//
// Return Values:
//    codeUNINSTALL_EXIT
//    returns uninstall status
//
// Description:  
//    Query the device data using the query xml in the push message,
//    and send the query results back to the server.
// **************************************************************************
SETUP_API codeUNINSTALL_EXIT Uninstall_Exit(
    HWND    hwndParent
    )
{
    return codeUNINSTALL_EXIT_DONE;
}
