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
// Module Name:  
//     CESDBUS.h
// 
// Abstract: Provides Liberary for SD Bus Access.
// 
// Notes: 
//

#ifndef __CESDBUS_H_
#define __CESDBUS_H_
#include <cebus.h>
#include <SDCardDDK.h>

// Callback.
#define IOCTL_BUS_SD_REQUEST_CALLBACK               _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+0)
typedef struct _IO_BUS_SD_REQUEST_CALLBACK {
    PSD_BUS_REQUEST_CALLBACK pRequestCallback;
    HANDLE          hDevice;    
    HANDLE          hBusRequest;
    PVOID           pDeviceContext;
    DWORD           dwRequestParam;
} IO_BUS_SD_REQUEST_CALLBACK, *PIO_BUS_SD_REQUEST_CALLBACK ;

#define IOCTL_BUS_SD_SLOT_EVENT_CALLBACK            _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+1)
typedef struct _IO_BUS_SD_SLOT_EVENT_CALLBACK {
    PSD_SLOT_EVENT_CALLBACK pSdSlotEventCallback;
    HANDLE          hDevice;
    PVOID           pDeviceContext;
    SD_SLOT_EVENT_TYPE SdSlotEventType;
    DWORD           dwDataOffset;
    DWORD           dwInSize;
} IO_BUS_SD_SLOT_EVENT_CALLBACK, *PIO_BUS_SD_SLOT_EVENT_CALLBACK;

#define IOCTL_BUS_SD_INTERRUPT_CALLBACK            _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+2)
typedef struct _IO_BUS_SD_INTERRUPT_CALLBACK {
    PSD_INTERRUPT_CALLBACK pSdInterruptCallback;
    HANDLE          hDevice;
    PVOID           pDeviceContext;
} IO_BUS_SD_INTERRUPT_CALLBACK, *PIO_BUS_SD_INTERRUPT_CALLBACK;


// API STATUS get back by GetLastError. the Value is defined in SDCardDDK.h


#define IOCTL_BUS_SD_REGISTER_CLIENT                _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+0)
typedef struct _IO_SD_REGISTERCLIENTDEVICE { // Input
    HANDLE      hDevice;
    PVOID       pDeviceContext;
    HANDLE      hCallbackAPI;
    SDCARD_CLIENT_REGISTRATION_INFO sdClientRegistrationInfo;
} IO_SD_REGISTERCLIENTDEVICE, *PIO_SD_REGISTERCLIENTDEVICE;

#define IOCTL_BUS_SD_SYNCHRONOUS_BUS_REQUEST        _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+1)
typedef struct _IO_SD_SYNCHRONOUS_BUS_REQUEST { // Input.
    HANDLE      hDevice;
    UCHAR       Command;
    DWORD       Argument;
    SD_TRANSFER_CLASS      TransferClass;
    SD_RESPONSE_TYPE       ResponseType;
    ULONG                  NumBlocks;
    ULONG       BlockSize;
    PUCHAR      pBuffer;        // Embedded Buffer.
    DWORD       Flags;
} IO_SD_SYNCHRONOUS_BUS_REQUEST, *PIO_SD_SYNCHRONOUS_BUS_REQUEST;
// Output : PSD_COMMAND_RESPONSE   pResponse;


#define IOCTL_BUS_SD_BUS_REQUEST                    _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+2)
typedef struct _IO_SD_BUS_REQUEST { // Input
    HANDLE      hDevice;
    UCHAR       Command;
    DWORD       Argument;
    SD_TRANSFER_CLASS   TransferClass;
    SD_RESPONSE_TYPE    ResponseType;
    ULONG       NumBlocks;
    ULONG       BlockSize;
    PUCHAR      pBuffer;  // Embedded Buffer.
    IO_BUS_SD_REQUEST_CALLBACK ceDriverCallbackParam;
    DWORD       Flags;
} IO_SD_BUS_REQUEST, *PIO_SD_BUS_REQUEST ;
// Out  HBUS_REQUEST            hRequest;

#define IOCTL_BUS_SD_FREE_BUS_REQUEST               _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+3)
// Input hRequest:
// Output None

#define IOCTL_BUS_SD_CARD_INFO_QUERY                _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+4)
typedef struct _IO_SD_CARD_INFO_QUERY { // Input
    HANDLE          hDevice;
    SD_INFO_TYPE    InfoType;
} IO_SD_CARD_INFO_QUERY, *PIO_SD_CARD_INFO_QUERY ;
// Output Card Info.

#define IOCTL_BUS_SD_READ_WRITE_REGISTERS_DIRECT    _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+5)
typedef struct _SD_READ_WRITE_REGISTERS_DIRECT {
    HANDLE      hDevice;
    SD_IO_TRANSFER_TYPE    ReadWrite;
    UCHAR                  Function;
    DWORD                  Address;
    BOOLEAN                ReadAfterWrite;
    PUCHAR                 pBuffer;     // Embedded pointer.
    ULONG                  Length;
} IO_SD_READ_WRITE_REGISTERS_DIRECT,*PIO_SD_READ_WRITE_REGISTERS_DIRECT ;

#define IOCTL_BUS_SD_CANCEL_BUS_REQUEST             _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+6)
// Input hRequest:
// Output None

#define IOCTL_BUS_SD_GET_TUPLE                      _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+7)
typedef struct _IO_BUS_SD_GET_TUPLE { // INPUT
    HANDLE      hDevice;
    UCHAR       TupleCode;
    BOOL        CommonCIS;
} IO_BUS_SD_GET_TUPLE, *PIO_BUS_SD_GET_TUPLE;
// Output DataBuffer.

#define IOCTL_BUS_SD_IO_CONNECT_INTERRUPT           _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+8)
typedef struct _IO_BUS_SD_IO_CONNECT_INTERRUPT { // Input
    HANDLE      hDevice;    
    IO_BUS_SD_INTERRUPT_CALLBACK sdInterruptCallback;
} IO_SD_IO_CONNECT_INTERRUPT, *PIO_SD_IO_CONNECT_INTERRUPT;
//Ouput : None

#define IOCTL_BUS_SD_IO_DISCONNECT_INTERRUPT        _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+9)
// Input hDevice
// Output NONE;


#define IOCTL_BUS_SD_SET_CARD_FEATURE               _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+0xa)
typedef struct _IO_SD_SET_CARD_FEATURE {
    HANDLE      hDevice;    
    SD_SET_FEATURE_TYPE  CardFeature;
    PVOID       pInBuf;     // embedded point
    DWORD       nInBufSize;
} IO_SD_SET_CARD_FEATURE, *PIO_SD_SET_CARD_FEATURE ;


#define IOCTL_BUS_SD_REQUEST_RESPONSE               _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+0xb)
// INPUT HBUS_REQUEST
// OUTPUT PSD_COMMAND_RESPONSE

#define IOCTL_BUS_SD_GETCLIENT_FUNCTION             _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+0xc)
// INPUT NULL
// OUTPUT PSDCARD_API_FUNCTIONS

#define IOCTL_BUS_SD_SYNCHRONOUS_BUS_REQUEST_EX      _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+0xd)
typedef struct _IO_SD_SYNCHRONOUS_BUS_REQUEST_EX { // Input.
    HANDLE      hDevice;
    UCHAR       Command;
    DWORD       Argument;
    SD_TRANSFER_CLASS      TransferClass;
    SD_RESPONSE_TYPE       ResponseType;
    ULONG                  NumBlocks;
    ULONG       BlockSize;
    PUCHAR      pBuffer;        // Embedded Buffer.
    DWORD       Flags;
    DWORD       cbSize;     // Size inbyte.
    PPHYS_BUFF_LIST pPhysBuffList;
    
} IO_SD_SYNCHRONOUS_BUS_REQUEST_EX, *PIO_SD_SYNCHRONOUS_BUS_REQUEST_EX;
// Output : PSD_COMMAND_RESPONSE   pResponse;


#define IOCTL_BUS_SD_BUS_REQUEST_EX                  _BUSACCESS_CTL_CODE(BUS_SD_EXTENTION_FUNCTIONCODE+0xe)
typedef struct _IO_SD_BUS_REQUEST_EX { // Input
    HANDLE      hDevice;
    UCHAR       Command;
    DWORD       Argument;
    SD_TRANSFER_CLASS   TransferClass;
    SD_RESPONSE_TYPE    ResponseType;
    ULONG       NumBlocks;
    ULONG       BlockSize;
    PUCHAR      pBuffer;  // Embedded Buffer.
    IO_BUS_SD_REQUEST_CALLBACK ceDriverCallbackParam;
    DWORD       Flags;
    DWORD       cbSize;     // Size inbyte.
    PPHYS_BUFF_LIST pPhysBuffList;
} IO_SD_BUS_REQUEST_EX, *PIO_SD_BUS_REQUEST_EX ;
// Out  HBUS_REQUEST            hRequest;
#ifdef __cplusplus
extern "C" {
#endif
HANDLE  GetBusAccessHandle();

#ifdef __cplusplus
};
#endif


#endif


