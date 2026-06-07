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


#pragma once
#include <winsock2.h>
#include <ws2bth.h>
#include <bthapi.h>
#include <bthutil.h>


#define MAX_NAME_SIZE 128
#define MAX_ADDR_SIZE 15
#define MAX_MESSAGE_SIZE 256

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)   (sizeof(a)/sizeof(a[0]))
#endif


struct DeviceList
{ 
	BT_ADDR bthAddress;
	TCHAR bthName[40];
	DeviceList *NextDevice;
};

struct DeviceInfo 
{
	WCHAR szDeviceNameAddr[MAX_NAME_SIZE];

}; 

class BthUtils
{
public:
	BthUtils();
	~BthUtils();
	int DiscoverDevices();
	int GetNumDevices(){return m_iNumDevices;};
	int GetDeviceInfo(DeviceInfo *pPeerDevicesInfo);
	int GetLocalDeviceName(DeviceInfo *pLocalDeviceInfo);
	int GetDeviceInfo(DeviceInfo *pPeerDeviceInfo, int iSelectedItem);
	int OpenServerConnection(BYTE *rgbSdpRecord, int cSdpRecord, int iChannelOffset, void (*funcPtr)( WCHAR*));
	int SendMessageToServer(WCHAR *strGUID, WCHAR *szMessage, int iSelectedDeviceIndex);


private:
	DeviceList *m_pDeviceList, *m_pStart, *m_pEnd, *m_pCurrentDevice;
	int m_iNumDevices;
	void (*pCallBackFunction)( WCHAR* ) ;
	HANDLE m_hReadThread;
	SOCKET m_socketServer, m_socketClient;
	SOCKADDR_BTH m_saClient;
	DWORD m_dwBluetoothMode;

	int RegisterService(BYTE *rgbSdpRecord, int cSdpRecord, int iChannelOffset, UCHAR channel);
	int OpenClientConnection(WCHAR *strGUID, int iSelectedDeviceIndex);
	int GetGUID(WCHAR *psz, GUID *pGUID) ;

	static DWORD WINAPI ReadData(LPVOID voidArg);
};