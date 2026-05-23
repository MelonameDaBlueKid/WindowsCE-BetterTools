// ************************************************************
// cfgclient.cpp
// 
// The meat of the program
//
// Copyright 2003 Microsoft Corporation, All Rights Reserved
//
// ************************************************************

#include "precomp.h"

#include <initguid.h>           // help in defining IID_ConnPrv_IProxyExtension
#include <connmgr_proxy.h>      // PROXY_CONFIG


// **************************************************************************
// Function Name: HandleMessage
// 
// Purpose: process the push message.
//
// Arguments:
//    IN PUSHMSG pPushMsg – contains push message data
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Process push message xml, and send the query results back to the server.
// **************************************************************************
HRESULT HandleMessage(PUSHMSG *pPushMsg)
{
    HRESULT hr          = S_OK;
    LPTSTR  pszResults  = NULL;
    
    hr = ProcessPushXML(pPushMsg, &pszResults);
    CHR(hr);
    
    ASSERT(pszResults);
    
    hr = SendResponse(pPushMsg, pszResults);
    CHR(hr);
    
Error:
    delete[] pszResults;
    
    return hr;
}


// **************************************************************************
// Function Name: PrintXML
// 
// Purpose: print XML to debug output.
//
// Arguments:
//    IN LPTSTR pszResults – XML query results
// **************************************************************************
#ifdef DEBUG
void PrintXML(LPTSTR pszResults)
{
    LPTSTR  pszStart    = pszResults;
    LPTSTR  pszEnd      = NULL;
    TCHAR   szBuffer[MAX_PATH + 1];
    DWORD   dwLen       = 0;

    if (NULL != pszResults)
    {
        while (TEXT('\0') != *pszResults)
        {
            if (TEXT('\n') == szBuffer[dwLen - 1] || MAX_PATH == dwLen)
            {
                // Print buffer so far if we hit the buffer limit or the last 
                // character was a new line.
                szBuffer[dwLen] = TEXT('\0');

                if (TEXT('\n') == szBuffer[dwLen - 1])
                {
                    RETAILMSG(1, (TEXT("%s"), szBuffer));
                }
                else
                {
                    RETAILMSG(1, (TEXT("%s\r\n"), szBuffer));
                }

                dwLen = 0;
            }

            szBuffer[dwLen] = *pszResults;
            dwLen++;
            pszResults++;
        }

        // If there is any output left, print it out.
        if (0 != dwLen)
        {
            szBuffer[dwLen] = TEXT('\0');
            RETAILMSG(1, (TEXT("%s"), szBuffer));
        }
    }
}
#endif 



// **************************************************************************
// Function Name: ProcessPushXML
// 
// Purpose: process the push XML.
//
// Arguments:
//    IN PUSHMSG pPushMsg – contains push message data
//    OUT LPTSTR* ppszResults – XML query results
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Process push message xml with configmanager.
// **************************************************************************
HRESULT ProcessPushXML(PUSHMSG *pPushMsg, LPTSTR *ppszResults)
{
    HRESULT	hr		    = S_OK;
    LPSTR	paszXML     = NULL;
    LPTSTR  pszQuery    = NULL;
    LPTSTR  pszResults  = NULL;
    DWORD	cchLenXML   = 0;
    DWORD	cchLenQuery = 0;
    
    paszXML = (LPSTR)pPushMsg->pbBody;
    cchLenXML = pPushMsg->cbBodyLength;
    
    ASSERT(paszXML);
    
    // Convert to Unicode from UTF-8.  (Provisioning xml should always be 
    // UTF-8 encoded.)
    cchLenQuery = MultiByteToWideChar(CP_UTF8, 0, paszXML, cchLenXML, NULL, 0);
    if (0 == cchLenQuery)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }
    
    // Include space for the NULL terminator.
    cchLenQuery++;
    pszQuery = new TCHAR[cchLenQuery];
    CPR(pszQuery);
    
    cchLenQuery = MultiByteToWideChar(CP_UTF8, 0, paszXML, cchLenXML, pszQuery, cchLenQuery);
    if (0 == cchLenQuery)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }
    
    // Make sure to NULL terminate.  MultiByteToWideChar will not include
    // a NULL if there was not one in the source string.  Since we alloced
    // space for cchLenQuery+1 characters, this will not overflow the buffer.
    pszQuery[cchLenQuery] = TEXT('\0');

#ifdef DEBUG
    // Print out query.
    RETAILMSG(1, (TEXT("CfgClient: Query Document from Server\r\n")));
    PrintXML(pszQuery);
#endif

    hr = DMProcessConfigXML(pszQuery, CFGFLAG_PROCESS|CFGFLAG_METADATA, &pszResults);
    
#ifdef DEBUG
    // Print out results.
    RETAILMSG(1, (TEXT("CfgClient: Result Document from Device\r\n")));
    PrintXML(pszResults);
#endif
    CHR(hr);

    // Make a copy to pass out to the caller.
    *ppszResults = pszResults;
    pszResults = NULL;
    
Error:
    delete[] pszResults;
    delete[] pszQuery;

    return hr;
}


// **************************************************************************
// Function Name: SendResponse
// 
// Purpose: send the query results back to the server.
//
// Arguments:
//    IN PUSHMSG pPushMsg – contains push message data
//    IN LPTSTR pszResults – XML query results
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Send the query results back to the server.  The server's address 
//    is contained in a header.
// **************************************************************************
HRESULT SendResponse(PUSHMSG *pPushMsg, LPTSTR pszResults)
{
    HRESULT                 hr                  = S_OK;
    LPTSTR                  pszSenderAddr       = NULL;
    LPTSTR                  pszSenderAddrType   = NULL;
    LPTSTR                  pszEncodedData      = NULL;
    LPTSTR                  pszProxy            = NULL;
    LPBYTE                  pbData              = NULL;
    DWORD                   cbData              = 0;
    DWORD                   cchEncodedData      = 1; 
    DWORD                   dwAccessType        = 0;
    HANDLE                  hConnHandle         = NULL;
    CONNMGR_CONNECTIONINFO  ConnInfo            = {0};

    // Get the address to which the response is to be sent.
    // Note that in this scheme, the response address is stored as the value of
    // the X-MS-SenderAddr header.
    hr = GetHeader(pPushMsg->szHeaders, c_szSenderAddrHeaderName, &pszSenderAddr);
    CHR(hr);

    if (NULL == pszSenderAddr)
    {
        CHR(E_INVALIDARG);
    }

    // Get the type of response protocol.
    hr = GetHeader(pPushMsg->szHeaders, c_szSenderAddrTypeHeaderName, &pszSenderAddrType);
    CHR(hr);

    if (0 == _tcsicmp(c_szHTTPSenderAddrType, pszSenderAddrType))
    {
        // URL-encode data.
        if (FALSE == InternetCanonicalizeUrl(pszResults, pszResults, &cchEncodedData, ICU_ENCODE_PERCENT))
        {
            if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
            {
                DWORD cchPOSTValueName = _tcslen(c_szPOSTValueName);

                // InternetCanonicalizeUrl includes the NULL-terminator in cchEncodedData
                pszEncodedData = new TCHAR[cchEncodedData + cchPOSTValueName];
                CPR(pszEncodedData);

                _tcscpy(pszEncodedData, c_szPOSTValueName);
                if (FALSE == InternetCanonicalizeUrl(pszResults, pszEncodedData + cchPOSTValueName, &cchEncodedData, ICU_ENCODE_PERCENT))
                {
                    CHR(HRESULT_FROM_WIN32(GetLastError()));
                }
            }
            else
            {
                CHR(HRESULT_FROM_WIN32(GetLastError()));
            }
        }
    }
    else if (0 == _tcsicmp(c_szWSPSenderAddrType, pszSenderAddrType))
    {
        hr = CopyString(pszResults, -1, &pszEncodedData);
        CHR(hr);
    }
    else
    {
        CHR(E_INVALIDARG);
    }

    // Convert to UTF-8.
    // Fake conversion to get buffer size
    cbData = WideCharToMultiByte(CP_UTF8, 0, pszEncodedData, -1, NULL, 0, NULL, NULL);
    if (0 == cbData)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // Allocate needed memory
    pbData = new BYTE[cbData];
    CPR(pbData);

    cbData = WideCharToMultiByte(CP_UTF8, 0, pszEncodedData, -1, (LPSTR)pbData, cbData, NULL, NULL);
    if (0 == cbData)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    if (0 == _tcsicmp(c_szHTTPSenderAddrType, pszSenderAddrType))
    {
        hr = ConnectWithConnMgr(pszSenderAddr, &pszProxy, &dwAccessType, &hConnHandle);
        CHR(hr);
    
        hr = PostHTTPResponse(pbData, cbData, pszSenderAddr, pszProxy, dwAccessType);
        CHR(hr);
    }
    else
    {
        hr = SendWSPResponse(pbData, cbData, pszSenderAddr);
        CHR(hr);
    }

Error:
    delete[] pszSenderAddr;
    delete[] pszSenderAddrType;
    delete[] pszEncodedData;
    delete[] pszProxy;
    delete[] pbData;

    if (hConnHandle)
    {
        ConnMgrReleaseConnection (hConnHandle, TRUE);
    }

    return hr;
}


// **************************************************************************
// Function Name: ConnectWithConnMgr
// 
// Purpose: make a connection with connmgr.
//
// Arguments:
//    IN LPTSTR pszSenderAddr – address to post data to
//    OUT LPTSTR* ppszProxy – proxy to connect to the internet
//    OUT DWORD* pdwAccessType – type of connection to make
//    OUT HANDLE* phConnHandle – handle for connection
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Use connmgr to establish a connection.
// **************************************************************************
HRESULT ConnectWithConnMgr(LPTSTR pszSenderAddr, LPTSTR *ppszProxy, DWORD *pdwAccessType, HANDLE *phConnHandle)
{
    HRESULT                 hr              = S_OK;
    LPTSTR                  pszProxy        = NULL;
    HANDLE                  hConnHandle     = NULL;
    DWORD                   dwWaitStartTick = 0;
    DWORD                   dwIndex         = 0;
    DWORD                   dwResult        = 0;
    DWORD                   dwStatus        = 0;
    LONG                    lWaitInterval   = gc_dwMaxWaitInterval;
    BOOL                    fContinueWait   = TRUE;
    CONNMGR_CONNECTIONINFO  ConnInfo        = {0};
    PROXY_CONFIG            pcProxy         = {0};

    // Register with the connection manager

    ConnInfo.cbSize = sizeof(ConnInfo);
    ConnInfo.dwParams = CONNMGR_PARAM_GUIDDESTNET;
    ConnInfo.dwFlags = CONNMGR_FLAG_PROXY_HTTP;
    ConnInfo.dwPriority = CONNMGR_PRIORITY_USERBACKGROUND;

    // Map the URL to a network, if we can
    CHR(ConnMgrMapURL(pszSenderAddr,
                       &(ConnInfo.guidDestNet),
                       &dwIndex));

    // Try to connect to this network.
    CHR(ConnMgrEstablishConnection(&ConnInfo,
                                    &hConnHandle));

    // Set the timeout
    dwWaitStartTick = GetTickCount();

    // Wait for the connection.
    while (lWaitInterval > 0 && fContinueWait)
    {
        // Wait for some status from connmgr.
        dwResult = WaitForSingleObject (hConnHandle, lWaitInterval);

        if (WAIT_OBJECT_0 == dwResult)
        {
            CHR(ConnMgrConnectionStatus(hConnHandle,&dwStatus));

            switch (dwStatus)
            {
                case CONNMGR_STATUS_CONNECTED:
                case CONNMGR_STATUS_NOPATHTODESTINATION:
                case CONNMGR_STATUS_WAITINGFORPATH:
                case CONNMGR_STATUS_CONNECTIONFAILED:
                case CONNMGR_STATUS_CONNECTIONCANCELED:
                case CONNMGR_STATUS_UNKNOWN:
                case CONNMGR_STATUS_CONNECTIONDISABLED:
                case CONNMGR_STATUS_WAITINGFORNETWORK:
                    fContinueWait = FALSE;
                    break;

                default:
                    break;
            }
        }
        else if (WAIT_FAILED == dwResult) 
        {
            // Error during wait.
            CHR(HRESULT_FROM_WIN32(GetLastError ()));
        }
        else if (WAIT_TIMEOUT == dwResult)
        {
            // Waiting timed out.
            CHR(E_FAIL);
        }
        
        // Calculate the remaining timeout value.
        // Subtract the time that's already elapsed.
        // Time is in milliseconds.
        lWaitInterval = gc_dwMaxWaitInterval - (GetTickCount() - dwWaitStartTick);
    }

    if (CONNMGR_STATUS_CONNECTED != dwStatus)
    {
        CHR(E_FAIL);
    }

    // Get the proxy information for this connection.
    // E_NOINTERFACE means "don't need a proxy".  S_OK means
    // "Yep, we got one, and this is it"
    hr = ConnMgrProviderMessage(hConnHandle,
                                &IID_ConnPrv_IProxyExtension,
                                NULL,
                                0,
                                0,
                                (PBYTE)&pcProxy,
                                sizeof(pcProxy));

    if (S_OK == hr)
    {
        *pdwAccessType = INTERNET_OPEN_TYPE_PROXY;
        pszProxy = pcProxy.szProxyServer;
    }
    else if (E_NOINTERFACE == hr)
    {
        *pdwAccessType = INTERNET_OPEN_TYPE_DIRECT;
        pszProxy = NULL;

        // Reset hr, since it's not really an error here.
        hr = S_OK;
    }
    CHR(hr);

    // Handle off connection handle
    *phConnHandle = hConnHandle;
    hConnHandle = NULL;

    // Handle off memory.
    *ppszProxy = pszProxy;
    pszProxy = NULL;

Error:
    if (hConnHandle)
    {
        ConnMgrReleaseConnection(hConnHandle, TRUE);
    }

    delete[] pszProxy;

    return hr;
}


// **************************************************************************
// Function Name: PostHTTPResponse
// 
// Purpose: post response data to sender.
//
// Arguments:
//    IN LPBYTE pbData – data to post
//    IN DWORD cbData – number of bytes of data to post
//    IN LPTSTR pszSenderAddr – data to post
//    IN LPTSTR pszProxy – proxy to use for connection
//    IN DWORD dwAccessType – type of connection to make
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Post data to the sender with wininet..
// **************************************************************************
HRESULT PostHTTPResponse(const LPBYTE pbData, DWORD cbData, LPCTSTR pszSenderAddr, LPCTSTR pszProxy, DWORD dwAccessType)
{
    HRESULT         hr              = S_OK;
    BSTR            bstrHostName    = NULL;
    BSTR            bstrUrlPath     = NULL;
    DWORD           dwHttpStatus    = 0;
    DWORD           cbHttpStatus    = sizeof(dwHttpStatus);
    HINTERNET       hInternetConn   = NULL;
    HINTERNET       hInternetSess   = NULL;
    HINTERNET       hInternetReq    = NULL;
    URL_COMPONENTS  uc              = {0};

    // Split url into component pieces
    uc.dwStructSize      = sizeof (uc);
    uc.dwSchemeLength    = 1;
    uc.dwHostNameLength  = 1;
    uc.dwUserNameLength  = 1;
    uc.dwPasswordLength  = 1;
    uc.dwUrlPathLength   = 1;
    uc.dwExtraInfoLength = 1;

    if (FALSE == InternetCrackUrl(pszSenderAddr, 0, 0,  &uc))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // Register with the connection manager
    // Get ready to send data to WININET
    //$TODO: Determine agent name to use 
    hInternetConn = InternetOpen(c_szUserAgentName, dwAccessType, pszProxy, NULL, 0);
    if (NULL == hInternetConn)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // The host name member of the url components struct contains not only the host name, but everything 
    // in the url after the host name as well.  We need to null terminate at the end of the host name.
    bstrHostName = SysAllocStringLen(uc.lpszHostName, uc.dwHostNameLength);
    CPR(bstrHostName);

    hInternetSess = InternetConnect(hInternetConn, bstrHostName, uc.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (NULL == hInternetSess)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    bstrUrlPath = SysAllocStringLen(uc.lpszUrlPath, uc.dwUrlPathLength);
    CPR(bstrUrlPath);

    hInternetReq = HttpOpenRequest(hInternetSess, TEXT("POST"), bstrUrlPath, NULL, NULL, NULL, 0, 0);
    if (NULL == hInternetReq)
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    // Note that the content type is application/x-www-form-urlencoded.
    if (FALSE == HttpSendRequest(hInternetReq, c_szAdditionalHeaders, _tcslen(c_szAdditionalHeaders), pbData, cbData))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    if (!HttpQueryInfo(hInternetReq, HTTP_QUERY_FLAG_NUMBER | HTTP_QUERY_STATUS_CODE, &dwHttpStatus, &cbHttpStatus, NULL))
    {
        CHR(HRESULT_FROM_WIN32(GetLastError()));
    }

    DEBUGMSG(1, (TEXT("SendHTTP:  http status code of %d.\r\n"), dwHttpStatus));
                
Error:
    if (hInternetReq)
    {
        InternetCloseHandle(hInternetReq);
    }

    if (hInternetSess)
    {
        InternetCloseHandle(hInternetSess);    
    }

    if (hInternetConn)
    {
        InternetCloseHandle(hInternetConn);
    }

    SysFreeString(bstrHostName);
    SysFreeString(bstrUrlPath);

    return hr;
}


// **************************************************************************
// Function Name: SendWSPResponse
// 
// Purpose: send response data to sender.
//
// Arguments:
//    IN LPBYTE pbData – data to post
//    IN DWORD cbData – number of bytes of data to post
//    IN LPTSTR pszSenderAddr – data to post
//
// Return Values:
//    HRESULT
//    returns an error code indicating success or failure
//
// Description:  
//    Send data to the sender via sms WDP..
// **************************************************************************
HRESULT SendWSPResponse(LPBYTE pbData, DWORD cbData, LPTSTR pszSenderAddr)
{
    HRESULT         hr                  = S_OK;
    WAP_HANDLE      whWAPHandle         = NULL;;
    HANDLE          hevtMsgAvailable    = NULL;
    WDP_UNITDATA    wud;

    memset(&wud, 0, sizeof(WDP_UNITDATA));

    hr = WapOpen(WAP_LAYER_WDP, gc_dwSourcePort, &whWAPHandle, &hevtMsgAvailable);
    CHR(hr);

    // Prepare the WAP Primitive structure
    wud.wpiPrimitiveID     = WAP_PRIMITIVE_ID_T_DUNITDATA;
    wud.wptPrimitiveType   = WAP_PRIMITIVE_TYPE_REQUEST;
    wud.dwValidFields      = WDP_FIELD_DESTINATIONADDRESS | WDP_FIELD_DESTINATIONPORT | WDP_FIELD_USERDATA;
    wud.dwDestinationPort  = gc_dwDestPort;
    wud.pbUserData         = pbData;
    wud.dwUserDataSize     = cbData;

    wud.waDestinationAddress.watAddressType = WAP_ADDRESS_TYPE_GSM_SMS;
    _tcscpy(wud.waDestinationAddress.ptsAddress, pszSenderAddr);

    // Send the primitive to the WAP stack
    hr = WapSend(whWAPHandle, (WAP_PRIMITIVE_BASE* const)&wud);
    CHR(hr);

Error:
    // WapClose closes hevtMsgAvailable as well.
    WapClose(whWAPHandle);

    return hr;

}