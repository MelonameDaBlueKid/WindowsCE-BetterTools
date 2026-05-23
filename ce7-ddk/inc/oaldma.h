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
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  
    OALDMA.h

Abstract:  
    Constant definitions for DMA function.

Notes: 

--*/
// Define Structure and prototype for OAL DMA Function.
#ifndef __OALDMA_H_
#define __OALDMA_H_
#include <ceddk.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CE_DMA_Speed_Compatible = 0, 
    CE_DMA_Speed_Slow, 
    CE_DMA_Speed_Medium,
    CE_DMA_Speed_High, 
    CE_DMA_Speed_Highest
} CE_DMA_SPEED;
    
typedef enum {
    CeWidth8Bits = 0, 
    CeWidth16Bits,
    CeWidth32Bits,
    CeWidth64Bits
} CE_REGISTER_ACCESS_WIDTH;

#define DMA_ADAPTER_ANY MAXDWORD
/*
  Size: Size of this structure in bytes.
  DemandMode: Set this to true if Device and DMA hardware has hardware handshaking.
  InterfaceType: Interface type on this device. It could be internal, pci, and etc. it can be found 
      from registry.
  BusNumber:    Bus number that indicates location of this hardware. It can be found from registry.
  RegisterAccessWidth: It indicates whether 8-bit, 16-bit, 32-bit or 64-bits of operation should be 
      perform during DMA Transfer.
  DmaSpeed: DMA Speed is used by this function to determine the DMA Adapter or Channel. The fastest 
      device should allocate highest priority DMA Adaptor and Channel.
  DmaAdapter: This is optional parameter. If this system only has one DMA Adapter or application 
      does not care which DMA adapter it should use, set it to DMA_ADAPTER_ANY.
  This structure is used by function DMAGetAdapter.
*/
typedef struct _DEVICE_DMA_REQUIREMENT_INFO {
  ULONG             Size;
  BOOLEAN           DemandMode;
  BOOLEAN           BusMaster;
  INTERFACE_TYPE    InterfaceType;
  ULONG             BusNumber;   
  ULONG             DeviceLocation; // For PCI, this is PCI_SLOT_NUMBER
  ULONG             DmaAdapter;
  CE_REGISTER_ACCESS_WIDTH  CeDmaWidth;
  CE_DMA_SPEED      DmaSpeed;
  DWORD             dwFlags;    // Transfer Flags that user will used for this 
} DEVICE_DMA_REQUIREMENT_INFO, *PDEVICE_DMA_REQUIREMENT_INFO;



/*
  Size: Size of this structure in bytes.
  DemandMode: Set this to true if Device and DMA hardware has hardware handshaking.
  InterfaceType: Interface type on this device. It could be internal, pci, and etc. it can be found 
    from registry.
  BusNumber:    Bus number that indicates location of this hardware. It can be found from registry.
  NumberOfTransferDescriptor: It indicates how many DMA transfer hardware can queue. Although 
    hardware only can activate one DMA transfer at one time, Multiple Transfer Descriptor support 
    will reduce software turn around time and make the data stream much more consistent.
  MaximumSizeOfEachTransfer: It indicates hardware limitation for each transfer. If any size of 
  issued transfer by OALIssueTransfer is bigger than MaxmimunSizeOfEachTransfer, it will fail.
  DmaAdapter: This system adjusted value which return by OALGetDmaAdapt.
  DmaWidth, DmaSpeed & DemandMode: Copied from DMA_REQUIREMENT_INFO. It should be same.
*/
typedef struct _CE_DMA_ADAPTER {
  ULONG             Size;  
  INTERFACE_TYPE    InterfaceType;
  ULONG             BusNumber;
  ULONG             DeviceLocation; // For PCI, this is PCI_SLOT_NUMBER
  ULONG             DmaAdapter;
  ULONG             MaximumSizeOfMappingRegister;
  ULONG             AddressBoundary;
  ULONG             AddressAlignment;
  PHYSICAL_ADDRESS  DmaSystemMemoryRangeStart;
  ULONG             DmaSystemMemoryRangeLength;
  // Copy From DMA_REQUIREMENT INFO
  CE_REGISTER_ACCESS_WIDTH  CeDmaWidth;
  CE_DMA_SPEED      DmaSpeed;
  BOOLEAN           DemandMode;
  BOOLEAN           BusMaster;
  DWORD             dwFlags;    // Transfer Flags that user will used for this 
  // May be more parameter needed here... Others.
} CE_DMA_ADAPTER, *PCE_DMA_ADAPTER;

typedef HANDLE DMA_CHANNEL_HANDLE ;
typedef HANDLE DMA_TRANSFER_HANDLE,*PDMA_TRANSFER_HANDLE;
typedef HANDLE DMA_BUFFER_HANDLE ;

typedef struct _CE_DMA_BUFFER_BLOCK {
    DWORD dwLength;
    PVOID virtualAddress;
    PHYSICAL_ADDRESS physicalAddress;
} CE_DMA_BUFFER_BLOCK,*PCE_DMA_BUFFER_BLOCK;


// Get DMA Adapter .
/* The DMAGetAdapter routine fill out a pointer to the DMA adapter structure for a physical device.*/
BOOL DMAGetAdapter (
    IN PDEVICE_DMA_REQUIREMENT_INFO pDeviceDmaRequirementInfo, //  Device Description. It descript what is capable Adapt supported.
    IN OUT PCE_DMA_ADAPTER pDmaAdapter
);


/* The AllocateAdapterChannel routine prepares the system for a DMA operation on behalf of the target device 
   and return handle that can be used by DMAAllocateChannel
*/
#define DMA_CHANNEL_ANY MAXDWORD
DMA_CHANNEL_HANDLE DMAAllocateChannel(
    IN PCE_DMA_ADAPTER     pDmaAdapter,
    IN ULONG            ulRequestedChannel,
    IN ULONG            ulAddressSpace,
    IN PHYSICAL_ADDRESS phDeviceIoAddress
);

/* This function frees a DMA Channel buffer allocated by OALAllocateAdapterChannel, along with all resources 
   the DMA Channel uses
*/
BOOL DMAFreeChannel(
   IN DMA_CHANNEL_HANDLE Channel
);


// DMA Transfer.
#define DMA_FLAGS_WRITE_TO_DEVICE       0x00000001
#define DMA_FLAGS_INC_DEVICE_ADDRESS    0x00000002
#define DMA_FLAGS_RESET_DEVICE_ADDRESS  0x00000004
#define DMA_FLAGS_USER_OPTIONAL_DEVICE  0x00000008
#define DMA_FLAGS_NOT_AUTO_START        0x80000000
/* The DMAIssueTransfer routine sets up map descriptor registers for a channel to map a DMA transfer 
   from a locked-down buffer if there is no other DMA transfers queued in the DMA Channel. Otherwise, this 
   transfer should be queued
*/
BOOL DMAIssueTransfer(
  IN HANDLE hDmaChannel,
  IN PDMA_TRANSFER_HANDLE phDmaHandle,
  IN DWORD  dwFlags,
  IN PHYSICAL_ADDRESS  SystemMemoryPhysicalAddress,
  IN PVOID CurrentVa,
  IN ULONG Length,
  IN HANDLE hNotifyHandle,
  IN PVOID Context1, IN PVOID Context2,
  IN PHYSICAL_ADDRESS  phOpDeviceIoAddress
);

/* The DMAIssueMultiBufferTransfer queue up multiple transfer in queue at once. 
*/
BOOL DMAIssueMultiBufferTransfer(
  IN HANDLE hDmaChannel,
  IN PDMA_TRANSFER_HANDLE phDmaHandle,
  IN DWORD  dwFlags,
  IN DWORD dwNumOfTransfer,
  CE_DMA_BUFFER_BLOCK pCeDmaBufferBlock[],
  IN HANDLE hNotifyHandle,
  IN PVOID Context1, IN PVOID Context2,
  IN PHYSICAL_ADDRESS  phOpDeviceIoAddress
);
//This function cancels an active DMA transfer.
BOOL DMACancelTransfer(
    IN DMA_TRANSFER_HANDLE DmaTransferHandle
);
//This function get contexts for a DMA Transfer
BOOL DMAGetContexts(
  IN DMA_TRANSFER_HANDLE hDmaTransferHandle,
  OUT PVOID * pContext1, OUT PVOID * pContext2
  );
// Put this Tranfser to Auto Start Mode
BOOL DMAStartTransfer(
  IN DMA_TRANSFER_HANDLE hDmaTransferHandle
  );    
//This function closes a DMA Transfer and release all related resource.
BOOL DMACloseTransfer(
    IN DMA_TRANSFER_HANDLE DmaTransferHandle
);

//This function get current active or queued DMA transfer status
typedef enum _DMA_STATUS {
    DMA_TRANSFER_COMPLETE = 0 ,
    DMA_TRANSFER_IN_PROGRESS,
    DMA_TRANSFER_IN_QUEUE,
    DMA_TRANSFER_COMPLETE_WITH_ERROR,
    DMA_TRANSFER_COMPLETE_WITH_CANCELED
} DMA_STATUS_CODE, *PDMA_STATUS_CODE ;
BOOL DMAGetStatus (
  IN DMA_TRANSFER_HANDLE hDmaTransferHandle,
  OUT PDWORD lpCompletedLength,
  OUT PDWORD lpCompletionCode
);

// Used to issue DMA transfer directly to hardware.
BOOL DMAIssueRawTransfer(
  IN OUT DMA_TRANSFER_HANDLE * phDmaHandle,
  IN HANDLE hDmaChannel,
  IN PVOID lpInPtr,
  IN DWORD nInLen,
  IN HANDLE hNotifyHandle,
  IN PVOID NotifyContext1,PVOID NotifyContext2
);

// Used to control DMA whose status in DMA_TRANSFER_IN_PROGRESS by hardware.
BOOL DMARawTransferControl(
  IN DMA_TRANSFER_HANDLE hDmaHandle,
  IN DWORD dwIoControl,
  IN PVOID lpInPtr,
  IN DWORD nInLen,
  IN OUT LPVOID lpOutBuffer,
  IN DWORD nOutBufferSize,
  IN LPDWORD lpBytesReturned
);

PVOID 
OALDMAAllocBuffer (
    IN  PCE_DMA_ADAPTER       Adapter,
    IN  ULONG              Length,
    OUT PPHYSICAL_ADDRESS  LogicalAddress,
    IN  BOOLEAN            CacheEnabled
    );
VOID
OALDMAFreeBuffer(
    IN PCE_DMA_ADAPTER      Adapter,
    IN ULONG             Length,
    IN PHYSICAL_ADDRESS  LogicalAddress,
    IN PVOID             VirtualAddress,
    IN BOOLEAN           CacheEnabled
    );

DMA_BUFFER_HANDLE DMAOpenBuffer(
    IN PCE_DMA_ADAPTER pDmaAdapter, 
    IN DWORD dwNumBuffer, 
    IN const PVOID pBufferArray[], 
    IN const DWORD aLength[]
);

DWORD DMAGetBufferPhysAddr (
    IN DMA_BUFFER_HANDLE hBuffer, 
    IN DWORD  NumOfBufferBlock, 
    IN OUT CE_DMA_BUFFER_BLOCK ceDmaBufferBlockArray[]
);

BOOL DMATransferOnBlocks(
    IN DMA_BUFFER_HANDLE hBuffer,
    IN HANDLE hDmaChannel,
    IN OUT PDMA_TRANSFER_HANDLE phDmaHandle,
    IN DWORD  dwFlags,
    IN PVOID  pBufferContext,
    IN HANDLE hNotifyHandle,
    IN PVOID Context1, IN PVOID Context2,
    IN PHYSICAL_ADDRESS  phOpDeviceIoAddress
);

BOOL DMAFlushBlockBuffer(
    IN DMA_BUFFER_HANDLE hBuffer
);

BOOL DMACloseBuffer(
    IN DMA_BUFFER_HANDLE hBuffer
);

#ifdef __cplusplus
};
#endif


#endif


