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

/**********************************************************************/
/**                        Microsoft Windows                         **/
/**********************************************************************/

//
// ----------------------------------------------------------------
//
// Kernel-Mode UI call methods
//
// ----------------------------------------------------------------

#ifndef __NETUI_KERNEL_H__INCLUDED__
#define __NETUI_KERNEL_H__INCLUDED__

#include <windows.h>
#include <netui_args.h>
#include <safeint.hxx>

// GetSetLastError - SetLastError only if it is currently ERROR_SUCCESS
__inline void GetSetLastError(DWORD newLastError)
{
    DWORD dwLastError = ERROR_SUCCESS;
    dwLastError = GetLastError();
    if(dwLastError == ERROR_SUCCESS)
        dwLastError = newLastError;
    SetLastError(dwLastError);
}


typedef DWORD (WINAPI *PFN_WaitForAPIReady) (DWORD dwAPISet, DWORD dwTimeout);
__inline DWORD WaitForAPIReadyWrapper(DWORD dwAPISet, DWORD dwTimeout)
{
    const WCHAR* dllName = L"k.coredll.dll";
    const WCHAR* funcName = L"WaitForAPIReady";
    HINSTANCE hLibInst = NULL;
    PFN_WaitForAPIReady pfnWaitForAPIReady;
    DWORD retCode = WAIT_FAILED;

    if (NULL != (hLibInst = LoadLibraryW(dllName)))
        {
        pfnWaitForAPIReady = (PFN_WaitForAPIReady) GetProcAddressW (hLibInst, funcName);
        if (!pfnWaitForAPIReady)
            {
            SetLastError(ERROR_FILE_NOT_FOUND);
            return retCode;
            }

        retCode = pfnWaitForAPIReady(dwAPISet, dwTimeout);
        FreeLibrary(hLibInst);
        }
    else
        {
        SetLastError (ERROR_PATH_NOT_FOUND);
        return retCode;
    }

    return retCode;
}


typedef BOOL (WINAPI *PFN_CeCallUserProc)(LPCWSTR pszDllName,
                                          LPCWSTR pszFuncName,
                                          LPVOID lpInBuffer,
                                          DWORD nInBufferSize,
                                          LPVOID lpOutBuffer,
                                          DWORD nOutBufferSize,
                                          LPDWORD lpBytesReturned);
__inline BOOL CeCallUserProcWrapper(LPCWSTR pszDllName,
                                    LPCWSTR pszFuncName,
                                    LPVOID lpInBuffer,
                                    DWORD nInBufferSize,
                                    LPVOID lpOutBuffer,
                                    DWORD nOutBufferSize,
                                    LPDWORD lpBytesReturned)
{
    const WCHAR* dllName = L"k.coredll.dll";
    const WCHAR* funcName = L"CeCallUserProc";
    HINSTANCE hLibInst = NULL;
    PFN_CeCallUserProc pfnCeCallUserProc;
    BOOL retCode = FALSE;

    if (NULL != (hLibInst = LoadLibraryW(dllName)))
        {
        pfnCeCallUserProc = (PFN_CeCallUserProc) GetProcAddressW (hLibInst, funcName);
        if (!pfnCeCallUserProc)
            {
            SetLastError(ERROR_FILE_NOT_FOUND);
            return retCode;
            }

        retCode = pfnCeCallUserProc(pszDllName,
                                    pszFuncName,
                                    lpInBuffer,
                                    nInBufferSize,
                                    lpOutBuffer,
                                    nOutBufferSize,
                                    lpBytesReturned);
        FreeLibrary(hLibInst);
        }
    else
        {
        SetLastError (ERROR_PATH_NOT_FOUND);
        return retCode;
    }

    return retCode;
}


_inline DWORD
CallKMsgWaitForMultipleObjects(DWORD nCount, LPHANDLE pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"MsgWaitForMultipleObjectsExt";
    PMsgWaitForMultipleObjectsArgs pFuncArgs = NULL;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;
    DWORD retCode = 0xffffffff;

    if(FALSE == safeIntUMul(sizeof(HANDLE), nCount, (unsigned int *)(&funcArgsSize)) ||
       FALSE == safeIntUAdd(sizeof(MsgWaitForMultipleObjectsArgs), funcArgsSize, (unsigned int *)(&funcArgsSize))) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return retCode;
    }

    // make sure the arguments are copied into a distinct memory block
    pFuncArgs = (PMsgWaitForMultipleObjectsArgs) LocalAlloc(LPTR, funcArgsSize);
    if(!pFuncArgs)
        return retCode;

    pFuncArgs->retCode = retCode;
    pFuncArgs->lastError = ERROR_SUCCESS;
    pFuncArgs->nCount = nCount;
    pFuncArgs->dwMilliseconds = dwMilliseconds;
    pFuncArgs->dwWakeMask = dwWakeMask;
    pFuncArgs->dwFlags = dwFlags;
    memcpy(&pFuncArgs->handles[0], pHandles, sizeof(HANDLE)*nCount);

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT)) {
        goto Finish;
    }

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) pFuncArgs, funcArgsSize, (LPVOID) pFuncArgs, funcArgsSize, &funcDataOut)) {
        goto Finish;
    }
    else {
        SetLastError(pFuncArgs->lastError);
        retCode = pFuncArgs->retCode;
    }

Finish:

    if(pFuncArgs) {
        LocalFree(pFuncArgs);
    }

    return retCode;
}


_inline BOOL
CallKPeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"PeekMessageWExt";
    PeekMessageArgs funcArgs;
    DWORD funcArgsSize = sizeof(PeekMessageArgs);
    DWORD funcDataOut = 0;
    BOOL retCode = FALSE;

    funcArgs.retCode = FALSE;
    funcArgs.lastError = ERROR_SUCCESS;
    funcArgs.hWnd = hWnd;
    funcArgs.wMsgFilterMin = wMsgFilterMin;
    funcArgs.wMsgFilterMax = wMsgFilterMax;
    funcArgs.wRemoveMsg = wRemoveMsg;
    memcpy(&funcArgs.msg, lpMsg, sizeof(MSG));

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        return FALSE;
    }

    retCode = funcArgs.retCode;
    if(!retCode) {
        SetLastError(funcArgs.lastError);
    }
    else {
        memcpy(lpMsg, &funcArgs.msg, sizeof(MSG));
    }


    return retCode;
}


_inline BOOL
CallKTranslateMessage(CONST MSG *pMsg)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"TranslateMessage";
    TranslateMessageArgs funcArgs;
    DWORD funcArgsSize = sizeof(TranslateMessageArgs);
    DWORD funcDataOut = 0;
    BOOL retCode = FALSE;

    funcArgs.retCode = FALSE;
    funcArgs.lastError = ERROR_SUCCESS;
    memcpy(&funcArgs.msg, pMsg, sizeof(MSG));

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        return FALSE;
    }

    retCode = funcArgs.retCode;
    if(!retCode) {
        SetLastError(funcArgs.lastError);
    }

    return retCode;
}


_inline BOOL
CallKDispatchMessageW(CONST MSG *pMsg)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"DispatchMessageExt";
    DispatchMessageArgs funcArgs;
    DWORD funcArgsSize = sizeof(DispatchMessageArgs);
    DWORD funcDataOut = 0;
    BOOL retCode = FALSE;

    funcArgs.retCode = FALSE;
    funcArgs.lastError = ERROR_SUCCESS;
    memcpy(&funcArgs.msg, pMsg, sizeof(MSG));

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        return FALSE;
    }

    retCode = funcArgs.retCode;
    if(!retCode) {
        SetLastError(funcArgs.lastError);
    }

    return retCode;
}


_inline HINSTANCE
CallKLoadLibrary(LPCWSTR lpLibFileName)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"LoadLibraryExt";
    PLoadLibraryArgs pFuncArgs = NULL;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;
    HINSTANCE retCode = NULL;
    DWORD fileNameSize = 0;

    // make sure the arguments are copied into a distinct memory block
    fileNameSize = (wcslen(lpLibFileName) + 1) * sizeof(WCHAR);
    funcArgsSize = sizeof(LoadLibraryArgs) + fileNameSize;
    pFuncArgs = (PLoadLibraryArgs) LocalAlloc(LPTR, funcArgsSize);
    if(!pFuncArgs)
        return NULL;
    pFuncArgs->retCode = NULL;
    memcpy(pFuncArgs->LibFileName, lpLibFileName, fileNameSize);
    pFuncArgs->lastError = ERROR_SUCCESS;

    if(CeCallUserProcWrapper(dllName, funcName, (LPVOID) pFuncArgs, funcArgsSize, (LPVOID) pFuncArgs, funcArgsSize, &funcDataOut)) {
        retCode = pFuncArgs->retCode;
        if (!retCode) {
            ASSERT(pFuncArgs->lastError == ERROR_SUCCESS);
            SetLastError(pFuncArgs->lastError);
        }
    }

    if(pFuncArgs) {
        LocalFree(pFuncArgs);
    }

    return retCode;
}


_inline BOOL
CallKFreeLibrary(HMODULE hLibModule)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"FreeLibraryExt";
    FreeLibraryArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = FALSE;
    funcArgs.hLibModule = hLibModule;
    funcArgsSize = sizeof(FreeLibraryArgs);
    funcArgs.lastError = ERROR_SUCCESS;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
            return FALSE;
    }

    if(!funcArgs.retCode) {
      ASSERT(funcArgs.lastError == ERROR_SUCCESS);
        SetLastError(funcArgs.lastError);
    }

    return funcArgs.retCode;
}


_inline BOOL
CallKGetUsernamePasswordEx(HWND hParent, PNETUI_USERPWD pUserPwd, OUT HWND *phDlg)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"GetUsernamePasswordExExt";
    GetUsernamePasswordExArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgsSize = sizeof(GetUsernamePasswordExArgs);
    funcArgs.retCode = ERROR_SUCCESS;
    funcArgs.hParent = hParent;
    // !NULL means there is return hDlg back from api
    funcArgs.hDlg = phDlg ?  (HWND)!NULL : NULL;
    memcpy(&funcArgs.userPwd, pUserPwd, sizeof(NETUI_USERPWD));

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT)) {
        GetSetLastError(ERROR_GEN_FAILURE);
        return FALSE;
    }

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        GetSetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    if(funcArgs.retCode != ERROR_SUCCESS) {
        SetLastError(funcArgs.retCode);
        return FALSE;
    }
    else {
      memcpy(pUserPwd, &funcArgs.userPwd, sizeof(NETUI_USERPWD));
      if (phDlg)
         *phDlg = funcArgs.hDlg;
    }

    SetLastError(ERROR_SUCCESS);
    return TRUE;
}


_inline BOOL
CallKGetUsernamePassword(HWND hParent, PNETUI_USERPWD pUserPwd)
{
   return CallKGetUsernamePasswordEx(hParent, pUserPwd, NULL);
}


_inline BOOL
CallKGetNewPasswordEx(
    IN     HWND          hParent,
    IN OUT PNETUI_NEWPWD pNewPwd,
      OUT HWND         *phDlg)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"GetNewPasswordExExt";
    GetNewPasswordExArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgsSize = sizeof(GetNewPasswordExArgs);
    funcArgs.retCode = ERROR_SUCCESS;
    funcArgs.hParent = hParent;
    // !NULL means there is return hDlg back from api
    funcArgs.hDlg = phDlg ?  (HWND)!NULL : NULL;
    memcpy(&funcArgs.newPwd, pNewPwd, sizeof(NETUI_NEWPWD));

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
        return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        return FALSE;
    }

    if(funcArgs.retCode != ERROR_SUCCESS) {
        SetLastError(funcArgs.retCode);
        return FALSE;
    }
    else {
      memcpy(pNewPwd, &funcArgs.newPwd, sizeof(NETUI_NEWPWD));
      if (phDlg)
         *phDlg = funcArgs.hDlg;
    }

    return TRUE;
}

_inline BOOL
CallKGetNewPassword(
    IN     HWND hParent,
    IN OUT PNETUI_NEWPWD pNewPwd)
{
    return CallKGetNewPasswordEx(hParent, pNewPwd, NULL);
}


_inline BOOL
CallKCloseUsernamePasswordDialog(
    IN     HWND          hDlg)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"CloseUsernamePasswordDialogExt";
    CloseUsernamePasswordDialogArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgsSize = sizeof(CloseUsernamePasswordDialogArgs);
    funcArgs.retCode = ERROR_SUCCESS;
    funcArgs.hDlg = hDlg;

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
        return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        return FALSE;
    }

    if(funcArgs.retCode != ERROR_SUCCESS) {
        SetLastError(funcArgs.retCode);
        return FALSE;
    }

    return TRUE;
}


_inline int
CallKGetNetStringSize(UINT uID)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"GetNetStringSizeExt";
    GetNetStringSizeArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgsSize = sizeof(GetNetStringSizeArgs);
    funcArgs.retCode = 0;
    funcArgs.uID = uID;

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            goto Finish;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        goto Finish;
    }

Finish:

    return funcArgs.retCode;
}


_inline int
CallKGetNetString(UINT uID, __in_ecount(nBufferMax) WCHAR* lpBuffer, int nBufferMax)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"GetNetStringExt";
    PGetNetStringArgs pFuncArgs = NULL;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;
    int retCode = 0;

    // make sure the arguments are copied into a distinct memory block
    if(FALSE == safeIntUMul(nBufferMax, sizeof(WCHAR), (unsigned int *)(&funcArgsSize)) ||
       FALSE == safeIntUAdd(sizeof(GetNetStringArgs), funcArgsSize, (unsigned int *)(&funcArgsSize))) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return retCode;
    }

    pFuncArgs = (PGetNetStringArgs) LocalAlloc(LPTR, funcArgsSize);
    if(!pFuncArgs)
        return retCode;

    pFuncArgs->retCode = 0;
    pFuncArgs->uID = uID;
    pFuncArgs->nBufferMax= nBufferMax;

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            goto Finish;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) pFuncArgs, funcArgsSize, (LPVOID) pFuncArgs, funcArgsSize, &funcDataOut)) {
        goto Finish;
    }

    ASSERT(funcDataOut >= (DWORD) (pFuncArgs->nBufferMax * sizeof(WCHAR)));
    memcpy(lpBuffer, pFuncArgs->buffer, pFuncArgs->nBufferMax * sizeof(WCHAR));

Finish:

    retCode = pFuncArgs->retCode;
    if(pFuncArgs) {
        LocalFree(pFuncArgs);
    }

    return retCode;
}


_inline BOOL WINAPIV
CallKVNetMsgBox(HWND hParent, DWORD dwFlags, UINT uStrID, va_list varglist)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"NetMsgBoxExt";
    PNetMsgBoxArgs pFuncArgs = NULL;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;
    BOOL    retCode = TRUE;
    WCHAR *outputString = NULL;
    WCHAR* szFmtStr = NULL;
    UINT cchFmtStr = 0;
    UINT cchRead = 0;
    DWORD outputStringSize = 0;


    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return FALSE;

    // we don't know how big the string is that needs to be displayed,
    // so we first query netui for the size then we query for the resource string
    // then we format the string based on the many parameters we are customizing
    // then we pop up the message box

    cchFmtStr = CallKGetNetStringSize(uStrID);
    if(0 == cchFmtStr) {
        // string resource does not exist
        retCode = FALSE;
        goto Finish;
    }

    cchFmtStr++; // account for null terminator
    szFmtStr = (PWCHAR) LocalAlloc(LPTR, cchFmtStr * sizeof(WCHAR));
    if (!szFmtStr) {
            // insufficient memory
            retCode = FALSE;
            goto Finish;
    }

    cchRead = CallKGetNetString(uStrID, szFmtStr, cchFmtStr);
    ASSERT(cchRead != 0);               // otherwise the above resource query should fail
    ASSERT(cchRead <= cchFmtStr);


    if (FormatMessageW(
                      FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_STRING,
                      szFmtStr,
                      0,
                      0,
                      (LPWSTR) &outputString,
                      cchRead,
                      &varglist) == 0) {
        RETAILMSG(1, (L"%S: Error %u in FormatMessage, ID:%u\r\n", __FUNCTION__, GetLastError(), uStrID));
        retCode = FALSE;
        goto Finish;
    }
    ASSERT(outputString);

    // make sure the arguments are copied into a distinct memory block
    outputStringSize = (wcslen(outputString) + 1) * sizeof(WCHAR);
    funcArgsSize = sizeof(NetMsgBoxArgs) + outputStringSize;
    pFuncArgs = (PNetMsgBoxArgs) LocalAlloc(LPTR, funcArgsSize);
    if(!pFuncArgs) {
        // do not overwrite last error since LocalAlloc sets it on failure
        retCode = FALSE;
        goto Finish;
    }

    pFuncArgs->retCode = FALSE;
    pFuncArgs->hParent = hParent;
    pFuncArgs->dwFlags = dwFlags;
    memcpy(&(pFuncArgs->szStr), outputString, outputStringSize);

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) pFuncArgs, funcArgsSize, (LPVOID) pFuncArgs, funcArgsSize, &funcDataOut)) {
            retCode = FALSE;
            goto Finish;
    }

    retCode = pFuncArgs->retCode;

Finish:

    if (szFmtStr)
            LocalFree(szFmtStr);

    if (outputString)
            LocalFree(outputString);

    if(pFuncArgs)
            LocalFree(pFuncArgs);

    return retCode;
}



_inline BOOL WINAPIV
CallKNetMsgBox(HWND hParent, DWORD dwFlags, UINT uStrID, ...)
{
    BOOL retCode = FALSE;

    va_list varglist;
    va_start(varglist, uStrID);
    
    retCode = CallKVNetMsgBox(hParent, dwFlags, uStrID, varglist);

    va_end(varglist);
    return retCode;
}



_inline BOOL
CallKGetResourcePassword(HWND hParent, PNETUI_RESPWD pResPwd)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"GetResourcePasswordExt";
    GetResourcePasswordArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = FALSE;
    funcArgs.hParent = hParent;
    memcpy(&funcArgs.resPwd, pResPwd, sizeof(NETUI_RESPWD));
    funcArgsSize = sizeof(GetResourcePasswordArgs);

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
            return FALSE;
    }

    return funcArgs.retCode;
}



_inline BOOL
CallKConnectionDialog(HWND hParent, PADDCONNECT_DLGPARAMS pDlgParams)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"ConnectDialogExt";
    ConnectDialogArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = FALSE;
    funcArgs.hParent = hParent;
    memcpy(&funcArgs.dlgParams, pDlgParams, sizeof(ADDCONNECT_DLGPARAMS));
    funcArgsSize = sizeof(ConnectDialogArgs);

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
            return FALSE;
    }

    return funcArgs.retCode;
}


_inline BOOL
CallKDisconnectDialog(HWND hParent, DWORD dwType)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"DisconnectDialogExt";
    DisconnectDialogArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = ERROR_SUCCESS;
    funcArgs.hParent = hParent;
    funcArgs.dwType = dwType;
    funcArgsSize = sizeof(DisconnectDialogArgs);

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
            return FALSE;
    }

    if(funcArgs.retCode != ERROR_SUCCESS) {
        SetLastError(funcArgs.retCode);
        return FALSE;
    }

    return TRUE;
}

_inline DWORD
CallKGetIPAddress (HWND hParent)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"GetIPAddressExt";
    GetIPAddressArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = ERROR_SUCCESS;
    funcArgs.hParent = hParent;
    funcArgsSize = sizeof(GetIPAddressArgs);

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
        return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        return 0;
    }

    if(funcArgs.retCode != ERROR_SUCCESS) {
        SetLastError(funcArgs.retCode);
        return 0;
    }

    return funcArgs.ipAddress;
}


_inline BOOL
CallKLineConfigEdit (HWND hParent, PLINECONFIGDATA pLineConfigData)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"LineConfigEditExt";
    LineConfigEditArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = FALSE;
    funcArgs.hParent = hParent;
    memcpy(&funcArgs.lineCfgData, pLineConfigData, sizeof(LINECONFIGDATA));
    funcArgsSize = sizeof(LineConfigEditArgs);

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
        return FALSE;
    }

    if(funcArgs.retCode != ERROR_SUCCESS) {
        SetLastError(funcArgs.retCode);
        return FALSE;
    }else{
        memcpy(pLineConfigData, &funcArgs.lineCfgData, sizeof(LINECONFIGDATA));
    }

    return TRUE;
}


_inline BOOL
CallKLineTranslateDialog (HWND hParent, HWND *pDialogWnd)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"LineTranslateDialogExt";
    LineTranslateDialogArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = FALSE;
    funcArgs.hParent = hParent;
    funcArgs.hDlg = *pDialogWnd;
    funcArgsSize = sizeof(LineTranslateDialogArgs);

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
         return FALSE;
    }

    if(funcArgs.retCode != ERROR_SUCCESS) {
        SetLastError(funcArgs.retCode);
        return FALSE;
    }

    return TRUE;
}


_inline BOOL
CallKAdapterIPProperties (HWND hParent, LPWSTR szAdapterName)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"AdapterIPPropertiesExt";
    HINSTANCE hLibInst = NULL;
    PAdapterIPPropertiesArgs pFuncArgs = NULL;
    DWORD funcArgsSize = 0;
    DWORD adapterNameSize = 0;
    DWORD funcDataOut = 0;
    BOOL retCode = FALSE;

    // make sure the arguments are copied into a distinct memory block
    if (!szAdapterName) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return retCode;
    }

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return retCode;

    adapterNameSize = wcslen(szAdapterName) * sizeof(WCHAR);
    funcArgsSize = sizeof(LoadLibraryArgs) + adapterNameSize;
    pFuncArgs = (PAdapterIPPropertiesArgs) LocalAlloc(LPTR, funcArgsSize);
    if(!pFuncArgs) {
        // do not overwrite last error since LocalAlloc sets it on failure
        return retCode;
    }

    pFuncArgs->retCode = FALSE;
    pFuncArgs->hParent = hParent;
    memcpy(pFuncArgs->AdapterName, szAdapterName, adapterNameSize);
    pFuncArgs->lastError = ERROR_SUCCESS;

    // for compatible with CallAdapterIPProperties in netui.h
    hLibInst = CallKLoadLibrary(dllName);
    if (!hLibInst) {
      SetLastError(ERROR_PATH_NOT_FOUND);
      goto Finish;
    }
    CallKFreeLibrary(hLibInst);

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) pFuncArgs, funcArgsSize, (LPVOID) pFuncArgs, funcArgsSize, &funcDataOut)) {
        goto Finish;
    }

    retCode = pFuncArgs->retCode;
    if(!retCode) {
       SetLastError(pFuncArgs->lastError);
    }

Finish:

    if(pFuncArgs) {
        LocalFree(pFuncArgs);
    }

    return retCode;
}


_inline BOOL
CallKGetDriverName (HWND hParent, PGETDRIVERNAMEPARMS pDriverParms)
{
    const WCHAR* dllName = L"netui.dll";
    const WCHAR* funcName = L"GetDriverNameExt";
    GetDriverNameArgs funcArgs;
    DWORD funcArgsSize = 0;
    DWORD funcDataOut = 0;

    if(!pDriverParms) return FALSE;

    // make sure the arguments are copied into a distinct memory block
    funcArgs.retCode = FALSE;
    funcArgs.hParent = hParent;
    memcpy(&funcArgs.getDrvNameParms, pDriverParms, sizeof(GETDRIVERNAMEPARMS));
    funcArgsSize = sizeof(GetDriverNameArgs);
    funcArgs.lastError = ERROR_SUCCESS;

    if (WAIT_OBJECT_0 != WaitForAPIReadyWrapper(SH_WMGR, WAIT_FOR_API_MAX_TIMEOUT))
            return FALSE;

    if(!CeCallUserProcWrapper(dllName, funcName, (LPVOID) &funcArgs, funcArgsSize, (LPVOID) &funcArgs, funcArgsSize, &funcDataOut)) {
            return FALSE;
    }

    if(!funcArgs.retCode) {
         SetLastError(funcArgs.lastError);
    } else {
        // copy driver name parameters back to caller structure
        memcpy(pDriverParms, &funcArgs.getDrvNameParms, sizeof(GETDRIVERNAMEPARMS));
    }

    return funcArgs.retCode;
}

#endif
