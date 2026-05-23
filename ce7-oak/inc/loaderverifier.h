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

// This file documents the PSL interface to the Loader Verifier.

#ifndef _LOADERVERIFIER_H_
#define _LOADERVERIFIER_H_

#if (_MSC_VER >= 1000)
#pragma once
#endif

#include <windows.h>
#include <bcrypt.h>       // for CNG algorithm identifiers


#if !defined(E_OBJECT_NOT_FOUND)
#define E_OBJECT_NOT_FOUND HRESULT_FROM_WIN32(ERROR_OBJECT_NOT_FOUND)
#endif //E_OBJECT_NOT_FOUND

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


// {003A4F3B-F6F5-41d8-A182-56391DB3CE9A}
EXTERN_C const GUID __declspec(selectany) LV_AUTHENTICATIONGUID_ROMMODULE = { 0x3a4f3b, 0xf6f5, 0x41d8, { 0xa1, 0x82, 0x56, 0x39, 0x1d, 0xb3, 0xce, 0x9a } };

// {73BBBDAA-6CDB-4b55-84E7-448F5BB1F0A3}
EXTERN_C const GUID __declspec(selectany) LV_AUTHENTICATIONGUID_ROM_EXE = { 0x73bbbdaa, 0x6cdb, 0x4b55, { 0x84, 0xe7, 0x44, 0x8f, 0x5b, 0xb1, 0xf0, 0xa3 } };

// {693C5CE7-323F-443f-A2F0-94A59C7A9C65}
EXTERN_C const GUID __declspec(selectany) LV_AUTHENTICATIONGUID_ROM_DLL = { 0x693c5ce7, 0x323f, 0x443f, { 0xa2, 0xf0, 0x94, 0xa5, 0x9c, 0x7a, 0x9c, 0x65 } };

    
// {BC588B1A-D88B-40d4-BD96-12E9820F5BA6}
EXTERN_C const GUID __declspec(selectany) LV_AUTHENTICATIONGUID_PORTABLEEXECUTABLE = { 0xbc588b1a, 0xd88b, 0x40d4, { 0xbd, 0x96, 0x12, 0xe9, 0x82, 0xf, 0x5b, 0xa6 } };

// {39ADA822-9724-400b-872E-66D96644C9C2}
EXTERN_C const GUID __declspec(selectany) LV_AUTHENTICATIONGUID_CAB = { 0x39ada822, 0x9724, 0x400b, { 0x87, 0x2e, 0x66, 0xd9, 0x66, 0x44, 0xc9, 0xc2 } };

// The following GUID is for catalog files, which aren't currently supported
// by the loader verifier.
// {4251968E-7C55-401f-8C22-E5D8DCEC3326}
EXTERN_C const GUID __declspec(selectany) LV_AUTHENTICATIONGUID_CATALOG = { 0x4251968e, 0x7c55, 0x401f, { 0x8c, 0x22, 0xe5, 0xd8, 0xdc, 0xec, 0x33, 0x26 } };

//
// Loader Verifier Authorizations
//
typedef enum LV_AUTHORIZATION
{
    LV_AUTHORIZATION_DENIED                     = 0x0,
    LV_AUTHORIZATION_EXECUTE                    = 0x1
} LV_AUTHORIZATION;

//
// Loader Verifier BlockList Types
//
typedef enum LV_BLOCKLIST
{
    LV_BLOCKLIST_CERTHASH                       = 0x1
} LV_BLOCKLIST;

//
// Loader Verifier Access Mask
//
#define LV_ACCESS_NONE                          0x000
#define LV_ACCESS_ALLOW                         0x001
#define LV_ACCESS_BLOCK                         0x002
#define LV_ACCESS_LOAD                          0x004
#define LV_ACCESS_EXECUTE                       0x008

//
// Error code specific to Loader Verifier
//
#define FACILITY_LV                              (0x400)

// The file is blocked by security policy.
#define LV_E_BLOCKED                             MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0001)

// The file is not digitally signed by trusted authorities.
#define LV_E_NO_SIGNATURE                        MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0002)

// The module has been tampered with.
#define LV_E_TAMPERED                            MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0003)

// The signing certificate or one of the certificates in the trust chain is expired.
#define LV_E_CERTIFICATE_EXPIRED                 MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0004)

// The signing certificate or one of the certificates in the trust chain is not trusted.
#define LV_E_CERTIFICATE_NOT_TRUSTED             MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0005)

// The signing certificate or one of the certificates in the trust chain violated its usage constraint.
#define LV_E_CERTIFICATE_USAGE_VIOLATION         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0006)

// The signing certificate is not chained to a specific certificate
#define LV_E_NOT_CHAINED_TO_REQUIRED_CERTIFICATE MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0007)

// The file has been restricted
#define LV_E_RESTRICTED_TO_LAUNCH                MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x0009)

// One of the certificate chained to the trusted store is revoked
#define LV_E_CERT_REVOKED                        MAKE_HRESULT(SEVERITY_ERROR, FACILITY_LV, 0x000A)


/// <summary>
///     Obtains authentication information for the file.
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
/// <param name="hReserved">
///     this is a reserved handle value for future use. Caller should pass in
///     NULL.
/// </param>
/// <param name="phslauthnFile">
///     Pointer to a variable that receives a handle to the authentication
///     information for the file.
/// </param>
/// <returns>
///     If the function successfully obtained the authentication information
///     for the file, the return value is S_OK. Otherwise, error code will
///     be returned.
/// </returns>

HRESULT LoaderVerifierAuthenticateFile(
    __in        const GUID*    guidAuthClass,
    __in_opt    HANDLE         hFile,
    __in        LPCWSTR        szFilePath,
    __in_opt    LPCWSTR        szHashHint,
    __in_opt    HANDLE         hReserved,
    __out       LPHANDLE       phslauthnFile
);


/// <summary>
///     Determines if the file is authorized to load based on the 
///     authentication information
/// </summary>
/// <param name="hslauthnFile">
///     Handle to the authentication information (obtained by previously
///     calling LoaderVerifierAuthenticateFile).
/// </param>
/// <param name="pslauthz">
///     Pointer to a variable that receives the result of the authorization
///     check. Caller must check this variable to determine whether or not
///     they should load the file. LoaderVerifierAuthorize's return value
///     only indicates if the authorization process itself is successful.
///     If this funtion return S_OK, and pslauthz return LV_AUTHORIZATION_DENIED,
///     the caller can call GetLastError() to determine the reason why
///     LV_AUTHORIZATION_DENIED is returned.
/// </param>
/// <returns>
///     If the function successfully determined the authorization result for
///     the file, the return value is S_OK. Otherwise, error code will be returned.
/// </returns>

HRESULT LoaderVerifierAuthorize(
    __in    HANDLE                 hslauthnFile,
    __out   LV_AUTHORIZATION*      pslauthz
);


/// <summary>
///     Returns a hash value for the file.
/// </summary>
/// <param name="hslauthnFile">
///     Handle to the authentication information (obtained by previously
///     calling LoaderVerifierAuthenticate).
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
///     must be  freed by the caller by calling LocalFree.
/// </param>
/// <returns>
///     If the function succeeds, the return value is S_OK.
///     If hslauthFile is NULL, the return value is E_HANDLE.
///     If pszHashAlgorithm contains an invalid value, the return value is
///     E_INVALIDARG.
///     If both pbHash and pcbHash are NULL the return value is E_POINTER. 
///     If the function fails because pbHash is too small, the return value is
///     E_INSUFFICIENTBUFFER.
/// </returns>

HRESULT LoaderVerifierGetHash(
    __in                    HANDLE      hslauthnFile,
    __in_opt                LPCWSTR     pszHashAlgorithm,
    __in_bcount_opt(cbHash) BYTE*       pbHash,
    __in                    DWORD       cbHash,
    __out_opt               DWORD*      pcbHash,
    __deref_opt_out         LPWSTR*     ppszHashAlgorithm
);


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

HRESULT LoaderVerifierAddToBlockList(
    __in                LV_BLOCKLIST    slBlockList,
    __in_bcount(cbItem) const BYTE*     pbItem,
    __in                DWORD           cbItem
);


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

HRESULT LoaderVerifierRemoveFromBlockList(
    __in                LV_BLOCKLIST    slBlockList,
    __in_bcount(cbItem) const BYTE*     pbItem,
    __in                DWORD           cbItem
);


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


HRESULT LoaderVerifierIsInBlockList(
    __in                LV_BLOCKLIST    slBlockList,
    __in_bcount(cbItem) const BYTE*     pbItem,
    __in                DWORD           cbItem,
    __out               BOOL*           pfInBlockList
);


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


HRESULT LoaderVerifierEnumBlockList(
    __in                    LV_BLOCKLIST    slBlockList,
    __in                    DWORD           iEntry,
    __out_bcount_opt(cbItem)BYTE*           pbItem,
    __in                    DWORD           cbItem,
    __out_opt               DWORD*          pcbItem
);


#ifdef WINCEMACRO
#include <mloaderverifier.h>
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
    
#endif // _LOADERVERIFIER_H_

