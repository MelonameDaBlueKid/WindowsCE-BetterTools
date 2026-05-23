// ************************************************************
// cfgclient.h
// 
// Header file for queryclient
//
// Copyright 2003 Microsoft Corporation, All Rights Reserved
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
// Constants
//
// ************************************************************

// Max minutes to wait for a connection (in mS).
const DWORD gc_dwMaxWaitInterval = 12000;

// Source port
const DWORD gc_dwSourcePort = 9031;

// Destination port
const DWORD gc_dwDestPort = 9030;


// ************************************************************
//
// Constant string declarations
//
// ************************************************************

extern TCHAR const c_szAppId[];
extern TCHAR const c_szPath[];
extern TCHAR const c_szContentType[];
extern TCHAR const c_szParams[];
extern TCHAR const c_szPOSTValueName[];
extern TCHAR const c_szUserAgentName[];
extern TCHAR const c_szContentType[];
extern TCHAR const c_szAdditionalHeaders[];
extern TCHAR const c_szSenderAddrHeaderName[];
extern TCHAR const c_szSenderAddrTypeHeaderName[];
extern TCHAR const c_szHTTPSenderAddrType[];
extern TCHAR const c_szWSPSenderAddrType[];


// ************************************************************
//
// Global function prototypes
//
// ************************************************************

HRESULT HandleMessage(PUSHMSG *pPushMsg);
HRESULT ProcessPushXML(PUSHMSG *pPushMsg, LPTSTR *ppszResults);
HRESULT SendResponse(PUSHMSG *pPushMsg, LPTSTR pszResults);
HRESULT GetHeader(LPCTSTR pszAllHeaders, LPCTSTR pszHeaderName, LPTSTR *ppszHeaderValue);
HRESULT CopyString(LPCTSTR pszSource, DWORD cchSourceLen, LPTSTR* ppszOut);
HRESULT ConnectWithConnMgr(LPTSTR pszSenderAddr, LPTSTR *ppszProxy, DWORD *pdwAccessType, HANDLE *phConnHandle);
HRESULT PostHTTPResponse(const LPBYTE pbData, DWORD cbData, LPCTSTR pszSenderAddr, LPCTSTR pszProxy, DWORD dwAccessType);
HRESULT SendWSPResponse(LPBYTE pbData, DWORD cbData, LPTSTR pszSenderAddr);