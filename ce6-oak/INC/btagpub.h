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

#ifndef __BTAGPUB_H__
#define __BTAGPUB_H__

#include <windows.h>

#include <winsock2.h>
#include <ws2bth.h>


#define IOCTL_AG_OPEN_AUDIO         0x01
#define IOCTL_AG_CLOSE_AUDIO        0x02
#define IOCTL_AG_CLOSE_CONTROL      0x03
#define IOCTL_AG_SET_SPEAKER_VOL    0x04
#define IOCTL_AG_SET_MIC_VOL        0x05
#define IOCTL_AG_GET_SPEAKER_VOL    0x06
#define IOCTL_AG_GET_MIC_VOL        0x07
#define IOCTL_AG_GET_POWER_MODE     0x08
#define IOCTL_AG_SET_POWER_MODE     0x09
#define IOCTL_AG_OPEN_CONTROL       0x0A
#define IOCTL_AG_SET_USE_HF_AUDIO   0x0B
#define IOCTL_AG_SET_INBAND_RING    0x0C

#define MAX_SEND_BUF                256
#define MAX_PHONE_NUMBER            128
#define MAX_DISPLAY_NAME            128

#define RK_AUDIO_GATEWAY            _T("SOFTWARE\\Microsoft\\Bluetooth\\AudioGateway")
#define RK_AUDIO_GATEWAY_DEVICES    (RK_AUDIO_GATEWAY TEXT("\\Devices"))
#define RK_AG_SERVICE               _T("Services\\BTAGSVC")

#define NETWORK_FLAGS_DROP_ACTIVE   0x01
#define NETWORK_FLAGS_DROP_HOLD     0x02
#define NETWORK_FLAGS_DROP_OFFERING 0x04
#define NETWORK_FLAGS_DROP_OUTGOING 0x08
#define NETWORK_FLAGS_DROP_ALL      0x0f

#define NETWORK_FLAGS_STATE_ACTIVE      0x01
#define NETWORK_FLAGS_STATE_HOLD        0x02
#define NETWORK_FLAGS_STATE_OFFERING    0x04
#define NETWORK_FLAGS_STATE_OUTGOING    0x08

#define AG_PHONE_EVENT_VOICE_RECOG		0x01
#define AG_PHONE_EVENT_SPEAKER_VOLUME	0x02
#define AG_PHONE_EVENT_MIC_VOLUME		0x03
#define AG_PHONE_EVENT_BT_CTRL			0x04
#define AG_PHONE_EVENT_BT_AUDIO			0x05


typedef void (*PFN_PhoneExtServiceCallback) (BOOL fHaveService);
typedef DWORD (*PFN_SendATCommand) (LPSTR szCommand, DWORD cbCommand);
typedef DWORD (*PFN_BthAGOnVoiceTag) (BOOL fOn);

#define MAX_PAIRINGS    4

typedef struct _AG_DEVICE {
    BT_ADDR bta;
    GUID service;
} AG_DEVICE, *PAG_DEVICE;

// Gets the list of devices from the registry
DWORD GetBTAddrList(PAG_DEVICE pDevices, USHORT usNumDevices);

// Functions implemented by Network component   
DWORD BthAGNetworkInit(HINSTANCE hInstance);
void BthAGNetworkDeinit(void);
DWORD BthAGNetworkDialNumber(LPWSTR pwszNumber);
DWORD BthAGNetworkDropCall(DWORD dwFlags);
DWORD BthAGNetworkAnswerCall(void);
DWORD BthAGNetworkTransmitDTMF(LPWSTR pwszDTMF);
DWORD BthAGNetworkHoldCall(void);
DWORD BthAGNetworkUnholdCall(void);
DWORD BthAGNetworkSwapCall(void);
DWORD BthAGNetworkDropSwapCall(void);
DWORD BthAGNetworkGetCallState(PDWORD pdwFlags);

// Functions implemented by PhoneExt component
DWORD BthAGPhoneExtInit(void);
void BthAGPhoneExtDeinit(void);
BOOL BthAGOverrideCallIn(BOOL fHandsfree);
BOOL BthAGOverrideCallOut(BOOL fHandsfree);
void BthAGPhoneExtEvent(DWORD dwEvent, DWORD dwParam, VOID* pvParam2);
BOOL BthAGGetNameByPhoneNumber(LPCWSTR pwszNumber, LPWSTR pwszName);
BOOL BthAGGetSpeedDial(unsigned short usIndex, LPWSTR pwszNumber);
BOOL BthAGGetLastDialed(LPWSTR pwszNumber);
DWORD BthAGSetServiceCallback(PFN_PhoneExtServiceCallback pfn);


// Network & PhoneExt libs may use these debug zones
#define ZONE_NETWORK        DEBUGZONE(5)
#define ZONE_PHONEUI        DEBUGZONE(6)
#define ZONE_BOND           DEBUGZONE(7)
#define ZONE_WARN           DEBUGZONE(14)
#define ZONE_ERROR          DEBUGZONE(15)



#endif // __BTAGPUB_H__

