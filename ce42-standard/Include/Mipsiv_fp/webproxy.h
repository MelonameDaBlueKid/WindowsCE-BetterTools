//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// This source code is licensed under Microsoft Shared Source License
// Version 1.0 for Windows CE.
// For a copy of the license visit http://go.microsoft.com/fwlink/?LinkId=3223.
//

#ifndef __WEBPROXY_H__
#define __WEBPROXY_H__

#include <winsock.h>

#define PROXY_VERSION	1

typedef struct _PROXY_HTTP_REQUEST {
	DWORD dwSize;
	const SOCKADDR_STORAGE* psaClient;
	int cbsaClient;
	const char* szUser;
	int cchUser;
	const char* szURL;
	int cchURL;
	char* szURLOut;
	int cbURLOut;
	const SOCKADDR_STORAGE* psaProxy;
	int cbsaProxy;
} PROXY_HTTP_REQUEST, *PPROXY_HTTP_REQUEST;

typedef struct _PROXY_HTTP_INFORMATION {
	DWORD dwSize;
	DWORD dwProxyVersion;
} PROXY_HTTP_INFORMATION, *PPROXY_HTTP_INFORMATION;

typedef struct _PROXY_ADDRCHANGE_PROPS {
	DWORD dwSize;
	SOCKADDR_STORAGE saPrivateIp;
	int cbsaPrivateIp;
	SOCKADDR_STORAGE saPublicIp;
	int cbsaPublicIp;
} PROXY_ADDRCHANGE_PROPS, *PPROXY_ADDRCHANGE_PROPS;
	

#endif
