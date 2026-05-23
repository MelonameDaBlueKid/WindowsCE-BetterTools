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
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

cecertmod.h

Abstract:

Header for certification module APIs and definitions

Notes: 


--*/
#ifndef _CE_CERTMOD_H_
#define _CE_CERTMOD_H_

#ifdef __cplusplus
extern "C"  {
#endif

//
// CERTMOD EXPORT
// This function initializes the certmod module. As part
// of the initialization the code loads evgen library and
// crypto api library. This is called only once when this 
// dll is loaded by filesys for the first time. Returns
// TRUE if the call is successful; FALSE otherwise.
//
DWORD WINAPI CertInit ();

//
// CERTMOD EXPORT
// Given a filename, this function does two things:
// a) Verify that the file is signed with any cert
// b) If the file is signed with a certificate, then find the
// account name associated with the store to which this cert
// belongs to.
//
// Function returns TRUE or FALSE depending on whether API
// call is successful or not. This is called by filesys 
// while loading a dll or exe.
// 
DWORD WINAPI CertVerify
(
	HANDLE hFile, 
	LPCWSTR wszFileName, 
	LPWSTR pUserName, 
	DWORD cchUserName, 
	LPDWORD pdwCertFlags
);

// cert store flags used in "pdwCertFlags" field of CertVerify API
#define CERT_UNKNOWN           0x00000000 // file is not signed with any cert
#define CERT_REVOKED           0x00000001 // file is signed with a cert but the cert is revoked
#define CERT_STORE_UNKNOWN     0x00000002 // file is signed with a cert and the cert doesn't belong to any store on device
#define CERT_STORE_VALID       0x00000004 // file is signed with valid cert which belongs to a store registered on the device

typedef DWORD (* PFN_CertInit) (void);
typedef DWORD (* PFN_CertVerify) 
(
    /*[in]*/HANDLE hFile, 
    /*[in]*/LPCWSTR pszFileName, 
    /*[out]*/LPWSTR pUserName, 
    /*[in]*/DWORD cchUserName, 
    /*[out]*/ LPDWORD pdwCertFlags
);

#define CERTMOD_CERTCHANGE_EVTNAME   L"SYSTEM/CertChange"
#define CERTMOD_REVOKE_LIST_PATH     L"\\Security\\SecurityRevokationList"
#define CERTMOD_REGKEY               L"Security\\CertMod"

#define CERTMODDLL              L"CertMod.dll"              // the DLL implementing module certification
#define FNAME_CERTINIT          L"CertInit"                 // init function
#define FNAME_CERTVERIFY        L"CertVerify"               // the function name for verification of file

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_CE_CERTMOD_H_
