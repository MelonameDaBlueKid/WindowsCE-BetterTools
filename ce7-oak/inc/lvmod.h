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
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//

// This file documents the DLL entry points exposed by a file verification
// module. These functions are used by the implementation of the LVMod
//
// Each function entry specifies:
// -- function prototype exported by the loader verification module dll
// -- typedef to be used when getting the function entry point from dll
// -- name of the function to be used when getting function entry point
//

#ifndef _LVMOD_H_
#define _LVMOD_H_

#if (_MSC_VER >= 1000)
#pragma once
#endif

#include "windows.h"
#include <wincrypt.h> // for ALG_ID definition

DECLARE_HANDLE(HLVMODAUTHENTICATIONDATA);


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


/// <summary>
///     Initializes the verification module. 
/// </summary>
/// <returns>
///     Returns S_OK if the module initializes successfully. 
/// </returns>
/// <remarks>
///     This function will be called by the kernel to initialize the verifier
///     module. 
/// </remarks>

HRESULT LVModInitialize (void);
typedef HRESULT (*PFNLVModInitialize) (void);
#define LVMOD_INITIALIZE L"LVModInitialize"

    
/// <summary>
///     Uninitializes the verification module, in preparation to unload it. 
/// </summary>    
/// <returns>
///     Returns S_OK if the module uninitialized successfully. 
/// </returns>
    
HRESULT LVModUninitialize (void);
typedef HRESULT (*PFNLVModUninitialize) (void);    
#define LVMOD_UNINITIALIZE L"LVModUninitialize"


/// <summary>
///     Obtains authentication information for a file. 
/// </summary>
/// <param name="guidAuthClass">
///     Indicates the type of file that should be authenticated. 
/// </param>
/// <param name="hFile">
///     Handle to the file to be authenticated. This may be NULL for some file
///     types (e.g. SL_AUTHENTICATIONCLASS_ROMMODULE). 
/// </param>
/// <param name="szFilePath">
///     Full pathname of the file that is to be authenticated.
/// </param>
/// <param name="szHashHint">
///     The caller can specify a CNG algorithm identifier here to request that
///     the Loader Verifier calculate the hash of the file using this algorithm
///     (typically because the caller is going to subsequently caller
///     LoaderVerifierGetHash). If the caller doesn't need a specific hash,
///     then pass in NULL.
/// </param>
/// <param name="hauthnCatalog">
///     Handle to the authentication information returned for the
///     catalog file that references the file being authenticated. For
///     example, the installer would pass in the authentication handle for the
///     CAB file when verifying the files within the CAB. If there's no
///     catalog file associated with the file, then this parameter should be
///     NULL. 
/// </param>
/// <param name="phslauthnFile">
///     Pointer to a variable that receives a handle to the authentication
///     information for the file. 
/// </param>
/// <returns>
///     If the function successfully obtained the authentication information 
///     for the file, the return value is S_OK. 
/// </returns>

HRESULT LVModAuthenticateFile(
             const GUID*                guidAuthClass,
    __in_opt HANDLE                     hFile,
             LPCWSTR                    szFilePath,
             LPCWSTR                    szHashHint,
    __in_opt HANDLE                     hauthnCatalog,
    __out    HLVMODAUTHENTICATIONDATA*  phlvauthnFile
);
typedef HRESULT (*PFNLVModAuthenticateFile) (
    const GUID*,
    HANDLE,
    LPCWSTR,
    LPCWSTR,
    HANDLE,
    HLVMODAUTHENTICATIONDATA*
);
#define LVMOD_AUTHENTICATE_FILE L"LVModAuthenticateFile"


/// <summary>
///     Determines if a file is allowed to be loaded by the system.  
/// </summary>
/// <param name="hslauthnFile">
///     Handle to the authentication information (obtained by previously 
///     calling LVModAuthenticateFile).
/// </param>
/// <param name="pslauthz">
///     Pointer to a variable that receives the result of the authorization 
///     check. Caller's must check this variable to determine whether or not 
///     they should load the file. 
/// </param>
/// <returns>
///     If the function successfully determined the authorization result for 
///     the file, the return value is S_OK.
/// </returns>

HRESULT LVModAuthorize(
    __in HLVMODAUTHENTICATIONDATA   hlvauthnFile,
    __out enum LV_AUTHORIZATION*    plvauthz
);
typedef HRESULT (*PFNLVModAuthorize) (
    HLVMODAUTHENTICATIONDATA,
    enum LV_AUTHORIZATION*
);
#define LVMOD_AUTHORIZE L"LVModAuthorize"


/// <summary>
///     Closes an authentication handle obtained by a call to
///     LVModAuthenticateFile. 
/// </summary>
/// <param name="hslauthnFile">
///     Handle to the authentication information.
/// </param>

void LVModCloseAuthenticationHandle(
    __in HLVMODAUTHENTICATIONDATA hlvauthnFile
);
typedef void (*PFNLVModCloseAuthenticationHandle) (
    HLVMODAUTHENTICATIONDATA
);
#define LVMOD_CLOSE_AUTHENTICATION_HANDLE L"LVModCloseAuthenticationHandle"


/// <summary>
///     Returns a hash value for the file.
/// </summary>
/// <param name="hslauthnFile">
///     Handle to the authentication information (obtained by previously 
///     calling LVModAuthenticateFile).
/// </param>
/// </param>
/// <param name="pszHashAlgorithm">
///     Specifies the CNG algorithm identifier of the hash algorithm that 
///     the caller would like to be used. If this is NULL, then the Loader  
///     Verifier will use a default algorithm. Callers who wish to retrieve 
///     hash calculated with a specific algorithm should indicate that when
///     they call LoaderVerifierAuthenticate.
/// </param>
/// <param name="pbHash">
///     Pointer to a variable that receives the hash value for the file. This
///     parameter may be NULL.
/// </param>
/// <param name="cbHash">
///     Specifies the size in bytes of the buffer that pbHash points to. This
///     parameter is ignored if pbHash is NULL.
/// </param>
/// <param name="pcbHash">
///     On exit, this parameter will contain the required size of the pbHash
///     buffer in bytes. This parameter may be NULL if pbHash is not NULL.
/// </param>
/// <param name="ppszHashAlgorithm">
///     Pointer to a CNG algorithm identifier that receives the hash algorithm 
///     used to calculate the hash. This parameter may be NULL.
///     NOTE: If this parameter is non-NULL, the algorithm identifier it points to 
///     must be freed by the caller by calling LocalFree.
/// </param>
/// <returns>
///     If the function succeeds, the return value is S_OK.
///     If hslauthFile is NULL, the return value is E_HANDLE.
///     If aiHashAlgorithm contains an invalid value, the return value is
///     E_INVALIDARG.
///     If both pbHash and pcbHash are NULL the return value is E_POINTER.
///     If the function fails because pbHash is too small, the return value is
///     E_INSUFFICIENTBUFFER. 
/// </returns>

HRESULT LVModGetHash(
    __in                    HLVMODAUTHENTICATIONDATA    hlvauthnFile,
    __in                    LPCWSTR                     pszHashAlgorithm,
    __in_bcount_opt(cbHash) LPBYTE                      pbHash,
                            DWORD                       cbHash,
    __out_opt               LPDWORD                     pcbHash,
    __deref_opt_out         LPWSTR*                     ppszHashAlgorithm
);
typedef HRESULT (*PFNLVModGetHash) (
    HLVMODAUTHENTICATIONDATA,
    LPCWSTR,
    LPBYTE,
    DWORD,
    LPDWORD,
    LPWSTR*
);
#define LVMOD_GET_HASH L"LVModGetHash"


/// <summary>
///     Adds an item to one of the Loader Verifier lists of blocked items
/// </summary>
/// <param name="slBlockList">
///     Type of block list to add the item to. Currently the only supported
///     block list type is LV_BLOCKLIST_CERTHASH and pbItem should point
///     to the hash of a certificate to be blocked.
/// </param>
/// <param name="pbItem">
///     Pointer to a variable that contains the item to be added.
/// </param>
/// <param name="cbItem">
///     Specifies the size in bytes of the buffer that pbItem points to.
/// </param>
/// <returns>
///     If the function succeeds in adding the item, the return value is S_OK.
///     If the item already exists in the block list, the function returns the
///     HRESULT corresponding to win32 error code ERROR_ALREADY_EXISTS
///     If slBlockList contains an invalid value, the return value is
///     E_INVALIDARG.
///     If pbItem is NULL the return value is E_POINTER. 
///     If cbItem is zero or greater than max item size, the return value is 
///     E_INVALIDARG. 
/// </returns>

HRESULT LVModAddToBlockList(
    __in                enum LV_BLOCKLIST   slBlockList,
    __in_bcount(cbItem) const BYTE*         pbItem,
    __in                DWORD               cbItem
);

typedef HRESULT (*PFNLVModAddToBlockList) (
    enum LV_BLOCKLIST,
    const BYTE*,
    DWORD
);
#define LVMOD_ADD_TO_BLOCKLIST L"LVModAddToBlockList"


/// <summary>
///     Removes an item from one of the Loader Verifier lists of blocked items
/// </summary>
/// <param name="slBlockList">
///     Type of block list to add the hash to. Currently the only supported
///     block list type is LV_BLOCKLIST_CERTHASH and pbItem should point
///     to the hash of a certificate that is blocked.
/// </param>
/// <param name="pbItem">
///     Pointer to a variable that contains the item.
/// </param>
/// <param name="cbItem">
///     Specifies the size in bytes of the buffer that pbItem points to.
/// </param>
/// <returns>
///     If the function succeeds in removing the item, the return value is S_OK.
///     If slBlockList contains an invalid value, the return value is
///     E_INVALIDARG.
///     If pbItem is NULL the return value is E_POINTER. 
///     If cbItem is zero or greater than max item size, the return value is 
///     E_INVALIDARG. 
/// </returns>

HRESULT LVModRemoveFromBlockList(
    __in                enum LV_BLOCKLIST   slBlockList,
    __in_bcount(cbItem) const BYTE*         pbItem,
    __in                DWORD               cbItem
);

typedef HRESULT (*PFNLVModRemoveFromBlockList) (
    enum LV_BLOCKLIST,
    const BYTE*,
    DWORD
);
#define LVMOD_REMOVE_FROM_BLOCKLIST L"LVModRemoveFromBlockList"


/// <summary>
///     Checks if the given item is in one of the Loader Verifier lists of 
///     blocked items
/// </summary>
/// <param name="slBlockList">
///     Type of block list to add the hash to. Currently the only supported
///     block list type is LV_BLOCKLIST_CERTHASH
/// </param>
/// <param name="pbItem">
///     Pointer to a variable that contains the item to be checked.
/// </param>
/// <param name="cbItem">
///     Specifies the size in bytes of the buffer that pbItem points to.
/// </param>
/// <param name="pfInBlockList">
///     Pointer to a boolean variable that will contain the result on return.
/// </param>
/// <returns>
///     The funtion returns S_OK if there was no error encountered during the
///     search.
///     The boolean variable pointed to by the parameter pfInBlockList will
///     be set to TRUE or FALSE depending on whether the item was found in
///     the specified block list.
///     If slBlockList contains an invalid value, the return value is
///     E_INVALIDARG.
///     If pbItem is NULL the return value is E_POINTER. 
///     If pfInBlockList is NULL the return value is E_POINTER.
///     If cbItem is zero or greater than max item size, the return value is 
///     E_INVALIDARG. 
/// </returns>

HRESULT LVModIsInBlockList(
    __in                enum LV_BLOCKLIST   slBlockList,
    __in_bcount(cbItem) const BYTE*         pbItem,
    __in                DWORD               cbItem,
    __out               BOOL*               pfInBlockList
);

typedef HRESULT (*PFNLVModIsInBlockList) (
    enum LV_BLOCKLIST,
    const BYTE*,
    DWORD,
    BOOL*
);
#define LVMOD_IS_IN_BLOCKLIST L"LVModIsInBlockList"


/// <summary>
///     Enumerates the items in one of the Loader Verifier lists of blocked 
///     items
/// </summary>
/// <param name="slBlockList">
///     Type of block list to enumerate from. Currently the only supported
///     block list type is LV_BLOCKLIST_CERTHASH.
/// </param>
/// <param name="iEntry">
///     Current enumeration index. This parameter should be zero on the first
///     call to this function and incremented by 1 on every subsequent call
///     to retrieve the next item.
/// <param name="pbItem">
///     Pointer to a variable that receives the blocked item. This parameter 
///     may be NULL, if the caller wants to determine the size needed for this
///     buffer
/// </param>
/// <param name="cbItem">
///     Specifies the size in bytes of the buffer that pbItem points to. This
///     parameter is ignored if pbItem is NULL.
/// </param>
/// <param name="pcbItem">
///     On exit, this parameter will contain the required size of the pbItem
///     buffer in bytes. This parameter may be NULL if pbItem is not NULL.
/// </param>
/// <returns>
///     If the function succeeds in enumerating the item at iEntry location, 
///     the return value is S_OK.
///     If there are no more items to enumerate, the function returns the
///     HRESULT corresponding to win32 error code ERROR_NO_MORE_ITEMS
///     If slBlockList contains an invalid value, the return value is
///     E_INVALIDARG.
///     If pbItem and pCbItem is both NULL, the return value is E_POINTER. 
///     If cbItem is less that the returned item size, the return value is 
///     HRESULT corresponding to win32 error code ERROR_INSUFFICIENT_BUFFER. 
/// </returns>

HRESULT LVModEnumBlockList(
    __in                     enum LV_BLOCKLIST  slBlockList,
    __in                     DWORD              iEntry,
    __out_bcount_opt(cbItem) BYTE*              pbItem,
    __in                     DWORD              cbItem,
    __out_opt                DWORD*             pcbItem
);

typedef HRESULT (*PFNLVModEnumBlockList) (
    enum LV_BLOCKLIST,
    DWORD,
    LPBYTE,
    DWORD,
    DWORD*
);
#define LVMOD_ENUM_BLOCKLIST L"LVModEnumBlockList"


#ifdef __cplusplus
}
#endif // __cplusplus
    
#endif // _LVMOD_H_

