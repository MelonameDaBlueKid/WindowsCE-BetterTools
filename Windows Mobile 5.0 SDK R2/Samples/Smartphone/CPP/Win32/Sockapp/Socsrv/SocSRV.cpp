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

#include "stdafx.h"
#include "SocSRV.h"
#include <winsock2.h>
#include <ws2tcpip.h>

// **************************************************************************
//	Sample Description:
//		SocSRV is a Windows Mobile application that listens on a specific
//		TCP port.  When it accepts the connection, it expects to receive 
//		a 10 bytes buffer.  It then respond with another 10 bytes buffer 
//		including the string "Done" then releases all its resources and exits.
// **************************************************************************
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    HRESULT hr = E_FAIL;
	WSADATA wsaData;
    SOCKET mySocket;

	INT bytesSent = SOCKET_ERROR;
    INT bytesRecv = SOCKET_ERROR;
	INT iRet = 0;

	CHAR recvbuf[10] = "Dummy";
	CHAR sendBuff[10] = "DONE";

	BOOL fSockInitialized = FALSE;

   // Initialize Winsock.
    iRet = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(NO_ERROR != iRet)
	{
		hr = E_FAIL;
		goto Exit;
	}

	fSockInitialized = TRUE;

	// Create a socket.
    mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(INVALID_SOCKET == mySocket)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
    }

    // Bind the socket.
    sockaddr_in service;
	service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(27020);

	iRet = bind( mySocket, reinterpret_cast<SOCKADDR*> (&service), sizeof(service));
    if(SOCKET_ERROR ==iRet)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
    }
    
    // Listen on the socket.
    iRet = listen(mySocket, 1);
	if (SOCKET_ERROR == iRet)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
        goto Exit;
	} 

    // Accept connections.
    mySocket = accept( mySocket, NULL, NULL );
	if(INVALID_SOCKET == mySocket)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
	}
	
	// Make a blocking recv call
	bytesRecv = recv(mySocket, recvbuf, sizeof(recvbuf), 0 );
	if(SOCKET_ERROR == bytesRecv)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
	}

	bytesSent = send( mySocket, sendBuff, sizeof(sendBuff), 0 );
	if(SOCKET_ERROR == bytesSent)
	{
		iRet = WSAGetLastError();
		hr = HRESULT_FROM_WIN32(iRet);
		goto Exit;
	}

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
	return SUCCEEDED(hr);
}