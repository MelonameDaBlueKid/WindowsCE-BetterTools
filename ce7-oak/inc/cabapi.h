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

CABAPI.h

Abstract:  

definitions for the Windows CE CABAPI APIs

Notes: 


--*/

#ifndef _CABAPI_H_
#define _CABAPI_H_

#include <WinCrypt.h>
#include <wintrust.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef VOID*   HCAB;

enum CAB_ExtractEX_Flags
{
    CAB_DEFAULT_FLAGS =         0x0,//flags unset
    CAB_REUSE_DECOMPRESSOR =    0x1,//keep cab decompressor alive to uncab more files
    //
    //Add other flags here
    //
};

/// <summary>
/// - API to open a CAB file. Returns a HANDLE to the opened CAB file in hCab.
/// </summary>
/// <param name="szFileName"></param>
/// <param name="hCab"></param>
/// <returns></returns>
HRESULT CAB_Open(
            __in  LPCTSTR szFileName,
            __out HCAB *hCab
            );

/// <summary>
/// - API to close a CAB file.
/// </summary>
/// <param name="hCab"></param>
/// <returns></returns>
HRESULT CAB_Close(
            __in  HCAB hCab
            );

/// <summary>
/// - Validates the HCAB and then returns the name of the first file in the
/// specified buffer. By passing in NULL for the buffer, the size in bytes will
/// be returned in cbBuffer. If the buffer is not large enough, the function
/// returns SEC_E_BUFFER_TOO_SMALL and places the required number of bytes in
/// cbBuffer. If the function is successful, cbBuffer will contain the number
/// of bytes copied into the buffer.
/// </summary>
/// <param name="hcab"></param>
/// <param name="szBuffer"></param>
/// <param name="cbBuffer"></param>
/// <returns></returns>
HRESULT CAB_FindFirstFile(
            __in  HCAB hCab,
            __out_bcount_opt(*cbBuffer) LPTSTR szBuffer,
            __inout DWORD *cbBuffer
            );

/// <summary>
/// - Validates the HCAB and then returns the name of the next file in the
/// specified buffer. By passing in NULL for the buffer, the size in bytes
/// will be returned in cbBuffer. If the buffer is not large enough, the 
/// function returns SEC_E_BUFFER_TOO_SMALL and places the required number 
/// of bytes in cbBuffer. If the function is successful, cbBuffer will contain
/// the number of bytes copied into the buffer and the return result will be
/// NOERROR. If there are no more files in the CAB, the buffer will not be
/// modified, cbBuffer will be set to zero and S_FALSE will be returned.
/// </summary>
/// <param name="hcab"></param>
/// <param name="szBuffer"></param>
/// <param name="cbBuffer"></param>
/// <returns></returns>
HRESULT CAB_FindNextFile(
            __in  HCAB hCab,
            __out_bcount_opt(*cbBuffer) LPTSTR szBuffer, 
            __inout DWORD* cbBuffer
            );

/// <summary>
/// - API to extract a specific file from the CAB file and store it to the
/// specified path. hCab is verified to be a valid HCAB. If the file is
/// successfully extracted, NOERROR is returned. If the file is not found
/// in the CAB E_FAIL is returned.
/// </summary>
/// <param name="hcab"></param>
/// <param name="szFileName"></param>
/// <param name="szPath"></param>
/// <returns></returns>
HRESULT CAB_Extract(
            __in  HCAB hCab,
            __in  LPCTSTR szFileName,
            __in  LPCTSTR szPath
            );

/// <summary>
/// Extended version of CAB_Extract function
/// - flags are passed to customize the operation
/// </summary>
HRESULT CAB_ExtractEx(
            __in  HCAB hCab,
            __in  LPCTSTR szFileName,
            __in  LPCTSTR szPath,
            __in  DWORD customFlags
            );

/// <summary>
/// - API to extract all of the files from the CAB file and store them at the
/// specified path. hCab is verified to be a valid HCAB. 
/// The files are extracted from the back of the CAB towards the front destructively. 
/// That is as we extract files from the end of the CAB, we delete them from CAB and CAB size gets shrunk. This is to save the space.
/// If the files are successfully extracted, NOERROR is returned. E_FAIL is returned on error.
/// </summary>
/// <param name="hcab"></param>
/// <param name="szPath"></param>
/// <param name="cchPath"></param>
/// <returns></returns>
HRESULT CAB_ExtractAndDeleteAll(
            __in  HCAB hCab,
            __in  LPCTSTR szPath,
            __in  size_t cchPath
            );

/// <summary>
///- Helper function to extract all files in the specified CAB. First
/// validates that hCab is valid and then extracts all files to the specified
/// path. If szPath does not exist, it is created. If the files are
/// successfully extracted NOERROR is returned, failure to extract a file will
/// result in E_FAIL being returned.
/// </summary>
/// <param name="hcab"></param>
/// <param name="szPath"></param>
/// <returns></returns>
HRESULT CAB_ExtractAll(
            __in  HCAB hCab,
            __in  LPCTSTR szPath
            );

/// <summary>
/// Retrieve the certificate data attached to the CAB. Memory will be allocated
/// by this API. CAB_FreeCertificateData should be called to release this memory.
/// </summary>
/// <param name="pFileBlob"></param>
/// <param name="dwCertificateIndex"></param>
/// <param name="pCertificate"></param>
HRESULT CAB_GetCertificateData( 
            __in  HCAB hCAB,
            __in_opt PCRYPT_DATA_BLOB pFileBlob, 
            __in  DWORD dwCertificateIndex, 
            __out LPWIN_CERTIFICATE * pCertificate
            );


/// <summary>
/// Free the memory allocated to hold the certificate data.
/// </summary>
/// <param name="hCab"></param>
/// <param name="pCertificate"></param>
HRESULT CAB_FreeCertificateData(
            __in  HCAB hCab,
            __out LPWIN_CERTIFICATE* pCertificate
            );

/// <summary >
///
/// </summary>
/// <param name="szFileName"></param>
/// <param name="lpCERTData"></param>
/// <param name="cbCERTData"></param>
HRESULT CAB_VerifyFileSignature(
            __in  LPCTSTR szFileName,
            __in  void const * lpCERTData, 
            __in  size_t cbCERTData
            );

#ifdef __cplusplus
}
#endif

#endif // _CABAPI_H_
