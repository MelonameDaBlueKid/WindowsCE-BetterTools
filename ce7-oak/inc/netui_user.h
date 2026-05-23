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

#ifndef __NETUI_USER_H__
#define __NETUI_USER_H__
// @CESYSGEN IF CE_MODULES_NETUI

#include <windows.h>
#include <windev.h>
#include <netui_args.h>

#ifdef __cplusplus
extern "C" {
#endif

//
// ----------------------------------------------------------------
//
// Inline functions
//
// Use these functions to call the dll, will return appropriate
// failure codes if the DLL does not exist.
//
// ----------------------------------------------------------------

#ifndef WaitForAPIReady
DWORD WaitForAPIReady (DWORD dwAPISet, DWORD dwTimeout);
#endif

// Helper function to check whether window manager is present in system, and if so, wait until it
// has initialized.
_inline BOOL
CheckAndWaitForGWE()
{
    if (WAIT_OBJECT_0 == WaitForAPIReady(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
        {
        return TRUE;
        }

    return FALSE;
}


typedef void (WINAPI *PFN_DEFAULTFUNC)();

// Helper function to get the netui function address
_inline PFN_DEFAULTFUNC
GetNetuiFunction(HINSTANCE *phLibInst, const WCHAR * const functionName)
{
    PFN_DEFAULTFUNC pfnReturnAddress = NULL;
    const WCHAR * const dllName = L"netui.dll";

    ASSERT(!(*phLibInst));

    if (!CheckAndWaitForGWE())
        {
        return pfnReturnAddress;
        }

    if ((*phLibInst = LoadLibraryW(dllName)) != NULL)
        {
        pfnReturnAddress = (PFN_DEFAULTFUNC) GetProcAddressW (*phLibInst, functionName);
        if (!pfnReturnAddress)
            {
            RETAILMSG (1, (L"Can't find %S", functionName));
            SetLastError (ERROR_FILE_NOT_FOUND);
            }
        return pfnReturnAddress;
        }
    else
        {
        RETAILMSG (1, (L"Can't load %S", dllName));
        SetLastError (ERROR_PATH_NOT_FOUND);
        return pfnReturnAddress;
    }
}



_inline int
CallUGetNetString (UINT uID, __in_ecount(nBufferMax) LPWSTR lpBuffer, int nBufferMax)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetNetString pfnGetNetString;
    int         retCode = 0;

    pfnGetNetString = (PFN_GetNetString) GetNetuiFunction(&hLibInst, L"GetNetString");
    if (pfnGetNetString)
        {
        retCode = pfnGetNetString(uID, lpBuffer, nBufferMax);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUGetUsernamePassword (HWND hParent, PNETUI_USERPWD pUserPwd)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetUsernamePassword pfnGetUsernamePassword;
    BOOL        retCode = FALSE;

    pfnGetUsernamePassword = (PFN_GetUsernamePassword) GetNetuiFunction(&hLibInst, L"GetUsernamePassword");
    if (pfnGetUsernamePassword)
        {
        retCode = pfnGetUsernamePassword(hParent, pUserPwd);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUGetUsernamePasswordEx(HWND hParent, PNETUI_USERPWD pUserPwd, OUT HWND *phDlg)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetUsernamePasswordEx pfnGetUsernamePasswordEx;
    BOOL        retCode = FALSE;

    pfnGetUsernamePasswordEx = (PFN_GetUsernamePasswordEx) GetNetuiFunction(&hLibInst, L"GetUserPasswordEx");
    if (pfnGetUsernamePasswordEx)
        {
        retCode = pfnGetUsernamePasswordEx(hParent, pUserPwd, phDlg);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUGetNewPassword(IN HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetNewPassword pfnGetNewPassword;
    BOOL        retCode = FALSE;

    pfnGetNewPassword = (PFN_GetNewPassword) GetNetuiFunction(&hLibInst, L"GetNewPassword");
    if (pfnGetNewPassword)
        {
        retCode = pfnGetNewPassword(hParent, pNewPwd);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUGetNewPasswordEx(IN HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd, OUT HWND *phDlg)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetNewPasswordEx pfnGetNewPasswordEx;
    BOOL        retCode = FALSE;

    pfnGetNewPasswordEx = (PFN_GetNewPasswordEx) GetNetuiFunction(&hLibInst, L"GetNewPasswordEx");
    if (pfnGetNewPasswordEx)
        {
        retCode = pfnGetNewPasswordEx(hParent, pNewPwd, phDlg);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUCloseUsernamePasswordDialog(IN HWND hDlg)
{
    HINSTANCE   hLibInst = NULL;
    PFN_CloseUsernamePasswordDialog pfnCloseUsernamePasswordDialog;
    BOOL        retCode = FALSE;

    pfnCloseUsernamePasswordDialog = (PFN_CloseUsernamePasswordDialog) GetNetuiFunction(&hLibInst, L"CloseUsernamePasswordDialog");
    if (pfnCloseUsernamePasswordDialog)
        {
        retCode = pfnCloseUsernamePasswordDialog(hDlg);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUGetResourcePassword (HWND hParent, PNETUI_RESPWD pResPwd)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetResourcePassword pfnGetResourcePassword;
    BOOL        retCode = FALSE;

    pfnGetResourcePassword = (PFN_GetResourcePassword) GetNetuiFunction(&hLibInst, L"GetResourcePassword");
    if (pfnGetResourcePassword)
        {
        retCode = pfnGetResourcePassword(hParent, pResPwd);
        }

    if (hLibInst) 
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline DWORD
CallUGetIPAddress (HWND hParent)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetIPAddress pfnGetIPAddress;
    DWORD       retCode = 0;

    pfnGetIPAddress = (PFN_GetIPAddress) GetNetuiFunction(&hLibInst, L"GetIPAddress");
    if (pfnGetIPAddress)
        {
        retCode = pfnGetIPAddress(hParent);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallULineConfigEdit (HWND hParent, PLINECONFIGDATA pLineConfigData)
{
    HINSTANCE   hLibInst = NULL;
    PFN_LineConfigEdit pfnLineConfigEdit;
    BOOL        fretCode = FALSE;

    pfnLineConfigEdit = (PFN_LineConfigEdit) GetNetuiFunction(&hLibInst, L"LineConfigEdit");
    if (pfnLineConfigEdit)
        {
        fretCode = pfnLineConfigEdit(hParent,pLineConfigData);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return fretCode;
}


_inline BOOL
CallULineTranslateDialog (HWND hParent, HWND *pDialogWnd)
{
    HINSTANCE   hLibInst = NULL;
    PFN_LineTranslateDialog pfnLineTranslateDialog;
    BOOL       retCode = FALSE;

    pfnLineTranslateDialog = (PFN_LineTranslateDialog) GetNetuiFunction(&hLibInst, L"LineTranslateDialog");
    if (pfnLineTranslateDialog)
        {
        pfnLineTranslateDialog(hParent, pDialogWnd);
        retCode = TRUE;
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUConnectionDialog (HWND hParent,PADDCONNECT_DLGPARAMS pDlgParams)
{
    HINSTANCE   hLibInst = NULL;
    PFN_ConnectionDialog pfnConnectionDialog;
    BOOL        retCode = FALSE;

    pfnConnectionDialog = (PFN_ConnectionDialog) GetNetuiFunction(&hLibInst, L"ConnectionDialog");
    if (pfnConnectionDialog)
        {
        retCode = pfnConnectionDialog(hParent, pDlgParams);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUDisconnectDialog (HWND hParent, DWORD dwType)
{
    HINSTANCE   hLibInst = NULL;
    PFN_DisconnectDialog pfnDisconnectDialog;
    BOOL        retCode = FALSE;

    pfnDisconnectDialog = (PFN_DisconnectDialog) GetNetuiFunction(&hLibInst, L"DisconnectDialog");
    if (pfnDisconnectDialog)
        {
        retCode = pfnDisconnectDialog(hParent,dwType);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL WINAPIV
CallUNetMsgBox (HWND hParent, DWORD dwFlags, UINT uStrID, ...)
{
    HINSTANCE   hLibInst = NULL;
    PFN_NetMsgBox pfnNetMsgBox;
    BOOL        retCode=TRUE;
    WCHAR *szStr=NULL;


    pfnNetMsgBox = (PFN_NetMsgBox) GetNetuiFunction(&hLibInst, L"NetMsgBox");
    if (pfnNetMsgBox)
        {
        PWCHAR szFmtStr = NULL;
        UINT   cbFmtStr = 0;
        UINT   ccRead;

        // we don't know how big the string is that needs to be displayed,
        // so we use a loop to keep reading in the string resource until we
        // can be certain we've got it all.

        for(;;) 
            {
            cbFmtStr += 256;
            if (szFmtStr)
                LocalFree(szFmtStr);
            szFmtStr = (PWCHAR)LocalAlloc(LPTR, cbFmtStr * sizeof(WCHAR));
            if (!szFmtStr)
                {
                // Insufficient memory
                retCode = FALSE;
                break;
                }

            ccRead = CallUGetNetString(uStrID, szFmtStr, cbFmtStr / sizeof(WCHAR));

            if (ccRead == 0)
                {
                // String resource doesn't exist
                retCode = FALSE;
                break;
                }

            if (ccRead < (cbFmtStr / sizeof(WCHAR)) - 1)
                {
                // We read the entire string resource into the buffer

                va_list     varglist;
                va_start(varglist, uStrID);

                if (FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_STRING,
                                  szFmtStr,0,0,(LPWSTR)&szStr,ccRead,&varglist) == 0)
                    {
                    RETAILMSG(1,(L"!CallNetMsgBox: Error %u in FormatMessage, ID:%u\r\n", GetLastError(), uStrID));
                    retCode = FALSE;
                    }
                va_end(varglist);

                if (retCode)
                    retCode = pfnNetMsgBox(hParent, dwFlags, szStr);

                break;
                }

            // The string resource filled the entire buffer, so it
            // was probably truncated.  Increase buffer size and try
            // reading it again.
            }

        if (szFmtStr)
            LocalFree(szFmtStr);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    if (szStr)
        {
        LocalFree(szStr);
        }

    return retCode;
}


// Second version of this function that allows the function pointers to be preloaded
// This is necessary for file system drivers (e.g. redirector) which can't wait for LoadLibrary()
_inline BOOL WINAPIV
CallUNetMsgBox2 (PFN_NetMsgBox pfnNetMsgBox, PFN_GetNetString pfnGetNetString, HWND hParent, DWORD dwFlags, UINT uStrID, ...)
{
    BOOL        retCode=TRUE;
    WCHAR       *szStr=NULL;
    PWCHAR      szFmtStr = NULL;
    UINT        cbFmtStr = 0;
    UINT        ccRead;

    // We don't know how big the string is that needs to be displayed,
    // so we use a loop to keep reading in the string resource until we
    // can be certain we've got it all.

    for(;;)
        {
        cbFmtStr += 256;
        if (szFmtStr)
            LocalFree(szFmtStr);
        szFmtStr = (PWCHAR)LocalAlloc(LPTR, cbFmtStr * sizeof(WCHAR));
        if (!szFmtStr)
            {
            // Insufficient memory
            retCode = FALSE;
            break;
            }

        ccRead = pfnGetNetString(uStrID, szFmtStr, cbFmtStr / sizeof(WCHAR));
        if (ccRead == 0)
            {
            // String resource doesn't exist
            retCode = FALSE;
            break;
            }

        if (ccRead < (cbFmtStr / sizeof(WCHAR)) - 1)
            {
            // We read the entire string resource into the buffer
            va_list     varglist;
            va_start(varglist, uStrID);
            if (FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_STRING,
                              szFmtStr,0,0,(LPWSTR)&szStr,ccRead,&varglist) == 0)
                {
                RETAILMSG(1,(L"!CallNetMsgBox2: Error %u in FormatMessage, ID:%u\r\n",
                             GetLastError(),uStrID));
                retCode = FALSE;
                }
            va_end(varglist);

            if (retCode)
                retCode = pfnNetMsgBox(hParent, dwFlags, szStr);

            break;
            }

        // The string resource filled the entire buffer, so it
        // was probably truncated.  Increase buffer size and try
        // reading it again.

        }

    if (szFmtStr)
        LocalFree(szFmtStr);
    if (szStr)
        LocalFree(szStr);

    return retCode;
}


_inline BOOL
CallUAdapterIPProperties (HWND hParent, LPWSTR szAdapterName)
{
    HINSTANCE   hLibInst = NULL;
    PFN_AdapterIPProperties pfnAdapterIPProperties;
    BOOL        retCode = FALSE;

    pfnAdapterIPProperties = (PFN_AdapterIPProperties) GetNetuiFunction(&hLibInst, L"AdapterIPProperties");
    if (pfnAdapterIPProperties)
        {
        retCode = pfnAdapterIPProperties(hParent, szAdapterName);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


_inline BOOL
CallUGetDriverName (HWND hParent, PGETDRIVERNAMEPARMS pDriverParms)
{
    HINSTANCE   hLibInst = NULL;
    PFN_GetDriverName pfnGetDriverName;
    BOOL        retCode = FALSE;

    pfnGetDriverName = (PFN_GetDriverName) GetNetuiFunction(&hLibInst, L"GetDriverName");
    if (pfnGetDriverName)
        {
        retCode = pfnGetDriverName(hParent, pDriverParms);
        }

    if (hLibInst)
        {
        FreeLibrary(hLibInst);
        }

    return retCode;
}


#ifdef __cplusplus
}
#endif


// @CESYSGEN ENDIF
#endif // __NETUI_USER_H__
