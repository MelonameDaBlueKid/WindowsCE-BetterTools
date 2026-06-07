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
#define INITGUID
#include <winsock2.h>
#include <rapi2.h>
#include <strsafe.h>

// **************************************************************************
//	Sample Description:
//		SocClient is a Win32 Desktop component that demontrates the use of
//		sockets to 	communicate with a Windows Mobile device. At first hand,
//		the application uses IRAPI interfaces to get the IP of the 
//		Windows Mobile connected through ActiveSync.  In a second step,
//		it sends a hello string and listen for the device to repond
//		back.
// **************************************************************************

// **************************************************************************
// GetDeviceIP
//  
//  Purpose:
//      Retreive the IP of the first device connected.  This function
//		uses IRAPI interfaces to get the device IP.  Older applications can
//		use IDccManSink2::OnLogIpAddrEx to retreive the device IP address.
//
//	Notes:
//		Add the proxy port under registry 
//		[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows CE Services\ProxyPorts]
//		before device gets connected for serial/IR connections and serial devices.
//
//  Parameters:
//      OUT CHAR* pszDeviceIP
//              
//  Side Effects:
//      None
//
//  Returns:
//		HRESULT: S_OK on Success, an appropriate HR on failure.
//
// **************************************************************************
HRESULT GetDeviceIP(OUT CHAR* pszDeviceIP, IN size_t size)
{
    HRESULT hr = E_FAIL;

    IRAPIDesktop *pIRapiDesktop = NULL;
    IRAPIEnumDevices *pIRapiEnumDevices = NULL;
    IRAPIDevice *pIRapiDevice = NULL;
	RAPI_CONNECTIONINFO connectionInfo = {0};

	SOCKADDR_STORAGE *pIpaddr = NULL;
    sockaddr_in *psoc4 = NULL;

	if (NULL == pszDeviceIP)
	{
		hr = E_INVALIDARG;
		goto Exit;
	}

    // CoCreateInstance assumes that Threading model has already been set
	hr = CoCreateInstance(CLSID_RAPI, NULL, CLSCTX_INPROC_SERVER, 
                    IID_IRAPIDesktop,
                    (void**)&pIRapiDesktop
                    );
    if (FAILED(hr))
    {
        goto Exit;
    }

	// Enumerate the Windows Mobile devices connected
    hr = pIRapiDesktop->EnumDevices(&pIRapiEnumDevices);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
	// Only one device can get connected to AS 4.0 at a time.
	// Get the first device connected
    hr = pIRapiEnumDevices->Next(&pIRapiDevice);
    if (FAILED(hr))
    {
        goto Exit;
    }

    // Get connection information using pIRapiDevice returned previously
	hr = pIRapiDevice->GetConnectionInfo(&connectionInfo);
    if (FAILED(hr))
    {
        goto Exit;
    }
	
	// Convert the ip address received to an ANSI string
	pIpaddr = &(connectionInfo.ipaddr);
    psoc4 = reinterpret_cast<sockaddr_in *> (pIpaddr);
    hr = StringCchPrintfA(pszDeviceIP, size, "%s", inet_ntoa(psoc4->sin_addr));
	if (FAILED(hr))
	{
		goto Exit;
	}

    hr = S_OK;

Exit:
	// Time to free resources
    if (NULL != pIRapiDesktop)
    {
        pIRapiDesktop->Release();
    }

    if (NULL != pIRapiEnumDevices)
    {
        pIRapiEnumDevices->Release();
    }

    if (NULL != pIRapiDevice)
    {
        pIRapiDevice->Release();
    }

    return hr;
}

int main(int argc, char* argv[])
{
	HRESULT hr = E_FAIL;
	HRESULT hrCoinit = E_FAIL;

	WSADATA wsaData = {0};
    SOCKET mySocket;
    sockaddr_in clientService;
	CHAR szDeviceIP[MAX_PATH] = "";

	INT bytesSent = SOCKET_ERROR;
    INT bytesRecv = SOCKET_ERROR;
	INT iRet = 0;

	BOOL fSockInitialized = FALSE;

	CHAR sendbuf[10] = "Hello";
	CHAR recvbuf[10]= "";
   
    // Initialize threading model which is requried to use IRAPI interfaces
    hrCoinit = CoInitialize(NULL);
    if (FAILED(hrCoinit))
    {
        hr = hrCoinit;
        goto Exit;
    }

	// Initialize Winsock.
	iRet = WSAStartup( MAKEWORD(2,2), &wsaData);
    if(iRet != NO_ERROR )
	{
		hr = E_FAIL;
		goto Exit;
	}

	fSockInitialized = TRUE;

	// Create socket
	mySocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(mySocket == INVALID_SOCKET )
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
        goto Exit;
    }

	// use IRAPI intefaces to get the device IP
    hr = GetDeviceIP(szDeviceIP, sizeof(szDeviceIP));
	if (FAILED(hr))
	{
		goto Exit;
	}
    
	clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(szDeviceIP);
    clientService.sin_port = htons( 27020 );

	// Connect to the Server
	iRet = connect(mySocket, (SOCKADDR*) &clientService, sizeof(clientService));
	if(SOCKET_ERROR == iRet)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
    }

	//  Send a 10bytes buffer include the string "Hello"
	bytesSent = send(mySocket, sendbuf, sizeof(sendbuf), 0);
	if(SOCKET_ERROR == bytesSent)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
	}

	// receive a 10bytes buffer including the string "Done"
	bytesRecv = recv(mySocket, recvbuf, sizeof(recvbuf), 0);
	if(SOCKET_ERROR == bytesRecv)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
	}

	wprintf(L"Communication with the Server succeeded\n");

	hr = S_OK;

Exit:
	if (mySocket != NULL)
	{
		closesocket(mySocket);
	}
	
	if (fSockInitialized)
	{
		WSACleanup();
	}
    
	if (SUCCEEDED(hrCoinit))
    {
        ::CoUninitialize();        
    }

	if (FAILED(hr))
	{
		wprintf(L"Communication with the Server has failed\n");
	}

	return SUCCEEDED(hr);
}