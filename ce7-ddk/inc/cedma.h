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
//     CEDMA.h
// 
// Abstract: Provides Liberary for DMA Access.
// 
// Notes: 
//



#ifndef __CEDMA_H_
#define __CEDMA_H_
#include <ceddk.h>
#include <pm.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _CE_DMA_CTL_CODE(_Function)  \
            CTL_CODE(FILE_DEVICE_CE_DMA, _Function, METHOD_BUFFERED, FILE_ANY_ACCESS)

// DMAGetAdapter
#define IOCTL_CE_DMA_OALGETDMAADAPTER _CE_DMA_CTL_CODE(1)
//    IN PDEVICE_DMA_REQUIREMENT_INFO pDeviceDmaRequirementInfo, //  Device Description. It descript what is capable Adapt supported.
//    OUT PCE_DMA_ADAPTER pDmaAdapter


// DMAAllocateChannel
#define IOCTL_CE_DMA_ALLOCATECHANNEL _CE_DMA_CTL_CODE(2)
// IN
typedef struct _CE_DMA_OALALLOCADAPTERCHANNEL {
    IN CE_DMA_ADAPTER       DmaAdapter;
    IN ULONG                ulRequestedChannel;
    IN ULONG                ulAddressSpace;
    IN PHYSICAL_ADDRESS     phDeviceIoAddress;
} CE_DMA_OALALLOCADAPTERCHANNEL,*PCE_DMA_OALALLOCADAPTERCHANNEL;
// OUT  DMA CHANNEL HANDLE

//DMAFreeChannel
#define IOCTL_CE_DMA_FREEDMACHANNEL _CE_DMA_CTL_CODE(3)
// IN DMA CHANNEL HANDLE

//DMAIssueTransfer
#define IOCTL_CE_DMA_ISSUEDMATRANSFER _CE_DMA_CTL_CODE(4)
//IN 
typedef struct _CE_DMA_ISSUEDMATRANSFER {
  IN HANDLE hDmaChannel;
  IN DWORD  dwFlags;
  IN PHYSICAL_ADDRESS  SystemMemoryPhysicalAddress;
  IN PVOID CurrentVa;
  IN ULONG Length;
  IN HANDLE hNotifyHandle;
  IN PVOID NotifyContext1; IN PVOID NotifyContext2;
  IN PHYSICAL_ADDRESS  phOpDeviceIoAddress;
} CE_DMA_ISSUEDMATRANSFER, *PCE_DMA_ISSUEDMATRANSFER;
// OUT
// DMA_TRANSFER_HANDLE hDmaHandle,

//DMACancelTransfer
#define IOCTL_CE_DMA_OALCANCELDMATRANSFER _CE_DMA_CTL_CODE(5)
// IN DMA_TRANSFER_HANDLE

//DMACloseTransfer
#define IOCTL_CE_DMA_OALCLOSEDMATRANSFER _CE_DMA_CTL_CODE(6)
// IN DMA_TRANSFER_HANDLE

//DMAGetStatus
#define IOCTL_CE_DMA_GETDMASTATUS _CE_DMA_CTL_CODE(7)
// IN DMA_TRANSFER_HANDLE
// OUT
typedef struct _CE_DMA_GETDMASTATUS {
  OUT DWORD CompletedLength;
  OUT DWORD CompletionCode;
} CE_DMA_GETDMASTATUS ,*PCE_DMA_GETDMASTATUS ;

//DMAIssueRawTransfer
#define IOCTL_CE_DMA_ISSUERAWDMATRANSFER _CE_DMA_CTL_CODE(8)
typedef struct _CE_DMA_ISSUERAWDMATRANSFER {
  IN HANDLE hDmaChannel;
  IN PVOID lpInPtr;
  IN DWORD nInLen;
  IN HANDLE hNotifyHandle;
  IN PVOID NotifyContext1;PVOID NotifyContext2;
} CE_DMA_ISSUERAWDMATRANSFER, *PCE_DMA_ISSUERAWDMATRANSFER;
// OUT DMA_TRANSFER_HANDLE

//DMARawTransferControl
#define IOCTL_CE_DMA_RAWDMATRANSFERCTRL _CE_DMA_CTL_CODE(9)
typedef struct _CE_DMA_RAWDMATRANSFERCTRL {
  IN DMA_TRANSFER_HANDLE hDmaHandle;
  IN DWORD dwIoControl;
  IN PVOID lpInPtr;
  IN DWORD nInLen;
} CE_DMA_RAWDMATRANSFERCTRL, *PCE_DMA_RAWDMATRANSFERCTRL;
// OUT lpOutPtr with nOutLen

//HalAllocateCommonBuffer
#define IOCTL_CE_DMA_DMAALLOCBUFFER  _CE_DMA_CTL_CODE(0xa)
// IN
typedef struct _CE_DMA_DMAALLOCBUFFER_IN {
    CE_DMA_ADAPTER             Adapter;
    ULONG                   Length;
    IN  BOOLEAN             CacheEnabled;
} CE_DMA_DMAALLOCBUFFER_IN, *PCE_DMA_DMAALLOCBUFFER_IN ;
//
typedef struct _CE_DMA_DMAALLOCBUFFER_OUT {
    OUT PHYSICAL_ADDRESS    PhysicalAddress;
    OUT PVOID               VirtualAddress;
} CE_DMA_DMAALLOCBUFFER_OUT, *PCE_DMA_DMAALLOCBUFFER_OUT ;


//HalFreeCommonBuffer
#define IOCTL_CE_DMA_DMAFREEBUFFER  _CE_DMA_CTL_CODE(0xb)
typedef struct _CE_DMA_DMAFREEBUFFER {
    IN CE_DMA_ADAPTER      Adapter;
    IN ULONG            Length;
    IN PHYSICAL_ADDRESS LogicalAddress;
    IN PVOID            VirtualAddress;
    IN BOOLEAN          CacheEnabled;
} CE_DMA_DMAFREEBUFFER, *PCE_DMA_DMAFREEBUFFER ;


//DMAIssueMultiTransfer
#define IOCTL_CE_DMA_ISSUEMULTIDMATRANSFER _CE_DMA_CTL_CODE(0xc)
//IN 
typedef struct _CE_DMA_ISSUEMULTIDMATRANSFER {
  IN HANDLE hDmaChannel;
  IN DWORD  dwFlags;
  IN DWORD  dwNumOfTransfer;
  IN PCE_DMA_BUFFER_BLOCK pDmaBufferBlock;
  IN HANDLE hNotifyHandle;
  IN PVOID NotifyContext1; IN PVOID NotifyContext2;
  IN PHYSICAL_ADDRESS  phOpDeviceIoAddress;
} CE_DMA_ISSUEMULTIDMATRANSFER, *PCE_DMA_ISSUEMULTIDMATRANSFER;
// OUT
// DMA_TRANSFER_HANDLE hDmaHandle,

//DMAStartTransfer
#define IOCTL_CE_DMA_STARTTRANSFER _CE_DMA_CTL_CODE(0xd)
// IN DMA_TRANSFER_HANDLE

//DMAGetContexts
#define IOCTL_CE_DMA_GETDMACONTEXTS _CE_DMA_CTL_CODE(0xe)
// IN DMA_TRANSFER_HANDLE
// OUT
typedef struct _CE_DMA_GETDMACONTEXTS {
  OUT PVOID dmaContext1;
  OUT PVOID dmaContext2;
} CE_DMA_GETDMACONTEXTS ,*PCE_DMA_GETDMACONTEXTS ;


#define IOCTL_CE_DMA_OEM_IO_CONTROL_START   0x100

#ifdef __cplusplus
};
#endif

#endif

