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
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:

netui.h

Abstract:

Functions:


Notes:
    The netui library cannot be loaded before GWE has initialized (since it
    initializes common controls on DLL entry).  So, check that the WMGR API
    set has been registered before loading netui.dll.

--*/

#ifndef __NETUI_H__
#define __NETUI_H__
// @CESYSGEN IF CE_MODULES_NETUI/

#include <windows.h>
#include <windev.h>
#include <netui_args.h>
#include <netui_user.h>
#include <netui_kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

// determine whether the current function is executing in kernel mode
#define IsKModePtr(ptr) ((0x80000000 & (DWORD) ptr) ? TRUE : FALSE)

/**
 *  This structure is used by "transdlg_wrapper.cpp" to pass data
 *  to a child thread.
 */
typedef struct _LineTranslateParametersStruct_ {
        HWND hParent;
        HWND * phDlg;
        HANDLE LineTranslateEvent;
    } LineTranslateParametersStruct;

/////////////////////////////////////////////////////
//code concerned with the bluetooth management UI

int CreateScanDevice(HINSTANCE, HWND);

_inline BOOL
IsCeCallUserProcAvailable()
{
    HANDLE hKCoreDll = LoadLibraryW(L"k.coredll.dll");

    if (hKCoreDll && GetProcAddressW((HMODULE) hKCoreDll, L"CeCallUserProc")) {
        FreeLibrary((HMODULE) hKCoreDll);
        return TRUE;
    } else {
        return FALSE;
    }
}

_inline int
CallGetNetString(UINT uID, __in_ecount(nBufferMax) LPWSTR lpBuffer, int nBufferMax)
{
    if(TRUE == IsKModePtr(CallGetNetString)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetNetString(uID, lpBuffer, nBufferMax);
        } else {
            return 0;
        }
    } else {
        return CallUGetNetString(uID, lpBuffer, nBufferMax);
    }
}

_inline BOOL
CallGetUsernamePassword(HWND hParent, PNETUI_USERPWD pUserPwd)
{
    if(TRUE == IsKModePtr(CallGetUsernamePassword)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetUsernamePassword(hParent, pUserPwd);
        } else {
            return FALSE;
        }
    } else {
        return CallUGetUsernamePassword(hParent, pUserPwd);
    }
}

_inline BOOL
CallGetUsernamePasswordEx(HWND hParent, PNETUI_USERPWD pUserPwd, OUT HWND *phDlg)
{
    if(TRUE == IsKModePtr(CallGetUsernamePasswordEx)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetUsernamePasswordEx(hParent, pUserPwd, phDlg);
        } else {
            return FALSE;
        }
    } else {
        return CallUGetUsernamePasswordEx(hParent, pUserPwd, phDlg);
    }
}

_inline BOOL
CallGetNewPassword(IN HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd)
{
    if(TRUE == IsKModePtr(CallGetNewPassword)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetNewPassword(hParent, pNewPwd);
        } else {
            return FALSE;
        }
    } else {
        return CallUGetNewPassword(hParent, pNewPwd);
    }
}

_inline BOOL
CallGetNewPasswordEx(IN HWND hParent, IN OUT PNETUI_NEWPWD pNewPwd, OUT HWND *phDlg)
{
    if(TRUE == IsKModePtr(CallGetNewPasswordEx)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetNewPasswordEx(hParent, pNewPwd, phDlg);
        } else {
            return FALSE;
        }
    } else {
        return CallUGetNewPasswordEx(hParent, pNewPwd, phDlg);
    }
}

_inline BOOL
CallCloseUsernamePasswordDialog(IN HWND hDlg)
{
    if(TRUE == IsKModePtr(CallCloseUsernamePasswordDialog)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKCloseUsernamePasswordDialog(hDlg);
        } else {
            return FALSE;
        }
    } else {
        return CallUCloseUsernamePasswordDialog(hDlg);
    }
}

_inline BOOL
CallGetResourcePassword (HWND hParent, PNETUI_RESPWD pResPwd)
{
    if(TRUE == IsKModePtr(CallGetResourcePassword)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetResourcePassword(hParent, pResPwd);
        } else {
            return FALSE;
        }
    } else {
        return CallUGetResourcePassword(hParent, pResPwd);
    }
}

_inline DWORD
CallGetIPAddress (HWND hParent)
{
    if(TRUE == IsKModePtr(CallGetIPAddress)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetIPAddress(hParent);
        } else {
            return 0;
        }
    } else {
        return CallUGetIPAddress(hParent);
    }
}

_inline BOOL
CallLineConfigEdit (HWND hParent, PLINECONFIGDATA pLineConfigData)
{
    if(TRUE == IsKModePtr(CallKLineConfigEdit)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKLineConfigEdit(hParent, pLineConfigData);
        } else {
            return FALSE;
        }
    } else {
        return CallULineConfigEdit(hParent, pLineConfigData);
    }
}

_inline BOOL
CallLineTranslateDialog (HWND hParent, HWND *pDialogWnd)
{
    if(TRUE == IsKModePtr(CallLineTranslateDialog)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKLineTranslateDialog(hParent, pDialogWnd);
        } else {
            return FALSE;
        }
    } else {
        return CallULineTranslateDialog(hParent, pDialogWnd);
    }
}

_inline BOOL
CallConnectionDialog (HWND hParent,PADDCONNECT_DLGPARAMS pDlgParams)
{
    if(TRUE == IsKModePtr(CallConnectionDialog)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKConnectionDialog(hParent, pDlgParams);
        } else {
            return FALSE;
        }
    } else {
        return CallUConnectionDialog(hParent, pDlgParams);
    }
}

_inline BOOL
CallDisconnectDialog (HWND hParent, DWORD dwType)
{
    if(TRUE == IsKModePtr(CallDisconnectDialog)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKDisconnectDialog(hParent, dwType);
        } else {
            return FALSE;
        }
    } else {
        return CallUDisconnectDialog(hParent, dwType);
    }
}

_inline BOOL WINAPIV
CallNetMsgBox (HWND hParent, DWORD dwFlags, UINT uStrID, ...)
{
    BOOL retCode = TRUE;
    va_list va;
    va_start(va, uStrID);

    if(TRUE == IsKModePtr(CallNetMsgBox)) {
        if(IsCeCallUserProcAvailable()) {
            retCode = CallKVNetMsgBox(hParent, dwFlags, uStrID, va);
        } else {
            retCode = FALSE;
        }
    } else {
        retCode = CallUNetMsgBox(hParent, dwFlags, uStrID, va);
    }

    va_end(va);
    return retCode;
}

_inline BOOL WINAPIV
CallNetMsgBox2 (PFN_NetMsgBox pfnNetMsgBox, PFN_GetNetString pfnGetNetString, HWND hParent, DWORD dwFlags, UINT uStrID, ...)
{
    BOOL retCode = TRUE;
    va_list va;
    va_start(va, uStrID);

    if(TRUE == IsKModePtr(CallNetMsgBox2))
        {
        retCode = FALSE;
        }
    else
        {
        retCode = CallUNetMsgBox2(pfnNetMsgBox, pfnGetNetString, hParent, dwFlags, uStrID, va);
        }

    va_end(va);
    return retCode;
}

_inline BOOL
CallAdapterIPProperties (HWND hParent, LPWSTR szAdapterName)
{
    if(TRUE == IsKModePtr(CallAdapterIPProperties)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKAdapterIPProperties(hParent, szAdapterName);
        } else {
            return FALSE;
        }
    } else {
        return CallUAdapterIPProperties(hParent, szAdapterName);
    }
}

_inline BOOL
CallGetDriverName (HWND hParent, PGETDRIVERNAMEPARMS pDriverParms)
{
    if(TRUE == IsKModePtr(CallGetDriverName)) {
        if(IsCeCallUserProcAvailable()) {
            return CallKGetDriverName(hParent, pDriverParms);
        } else {
            return FALSE;
        }
    } else {
        return CallUGetDriverName(hParent, pDriverParms);
    }
}



//////////////////////////////////////////////////////////////////////////////
//
// ShowCertificateFromHash
//
//  Displays a dialog with certificate details, if the cert exists. The dialog
//  is displayed modally if a parent exists, and execution returns to the 
//  caller after the user dismisses the dialog. The cert is looked up in the 
//  registry using config manager, and checks both the "MY" (personal) and 
//  "ROOT" (trusted root) stores for the certificate. 
//
//  Parameters:
//      HWND    hParent - Handle to a window that is the parent of the 
//                        details dialog. If NULL, this dialog has no parent.
//      LPCWSTR pszHash - Hex SHA1 Hash of the certificate to display. 
//                        Example: D23209AD23D314232174E40D7F9D62139786633A
//
//  Return Value:  
//      HRESULT. Typical return values are described below. 
//      S_OK           - The certificate was found and the dialog was displayed 
//                       normally.
//      E_INVALIDARG   - The pszHash parameter is missing or is not a valid
//                       hex string.
//      SEC_E_CERT_UNKNOWN - The specified certificate could not be found on
//                           the device.
//
HRESULT WINAPI ShowCertificateFromHash(__in_opt HWND hParent, __in LPCWSTR pszHash);

// Subkey in HKEY_LOCAL_MACHINE
#define NETUI_REGISTRY_KEY L"Software\\Microsoft\\netui"

// Stores the active WiFi control panel process id at this location
#define NETUI_CURRENT_WIFICPL_MAINWINDOW_KEY L"CurrentWiFiCplMainWindow"

// The active WiFi control panel other than the default NetUI creates the event with this name.
// It will be signaled if Netui receives a UI request from WiFi service but the active wifi control panel is not the default netui
#define NETUI_WIFI_CALLBACK_EVENT_NAME L"WiFiUiRequestEvent"

#ifdef __cplusplus
}
#endif


// @CESYSGEN ENDIF
#endif // __NETUI_H__
