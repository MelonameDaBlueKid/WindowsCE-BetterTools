//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
// ************************************************************
// fileclient.h
// 
// Function declaratinos, constants, etc.
//
//
// ************************************************************

#pragma once

// ************************************************************
//
// Error-handling macros
//
// ************************************************************

// Check HRESULT
#define CHR(hResult)\
    do {hr = (hResult); if(FAILED(hr)) goto Error;} while (0,0)

// Check pointer result
#define CPR(p)\
    do {if (NULL == (p)) {hr = E_OUTOFMEMORY; goto Error;} } while (0,0)


// ************************************************************
//
// Constant string declarations
//
// ************************************************************

extern TCHAR const c_szAppId[];
extern TCHAR const c_szPath[];
extern TCHAR const c_szContentType[];
extern TCHAR const c_szParams[];
extern TCHAR const c_szFileNameHeaderName[];
extern TCHAR const c_szParamsHeaderName[];
extern TCHAR const c_szAllowedExtKey[];


// ************************************************************
//
// Global variable declarations
//
// ************************************************************

extern HINSTANCE g_hInst;


// ************************************************************
//
// Global function prototypes
//
// ************************************************************

HRESULT HandleMessage(LPPUSHMSG pPushMsg);
HRESULT SaveFile(LPPUSHMSG pPushMsg, LPTSTR pszFileName);
HRESULT GetUserPermission(LPTSTR pszFileName);
HRESULT GetHeader(LPCTSTR pszAllHeaders, LPCTSTR pszHeaderName, LPTSTR *ppszHeaderValue);
HRESULT CopyString(LPCTSTR pszSource, DWORD cchSourceLen, LPTSTR* ppszOut);
HRESULT CheckSecurity(LPTSTR pszFileName);


