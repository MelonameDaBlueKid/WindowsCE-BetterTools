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

Module Name:

    ceddk.h

Abstract:

    This module defines the NT types, constants, and functions that are
    exposed to device drivers.

Revision History:

--*/
#pragma once

#ifndef _CEDDK_
#define _CEDDK_

#define NTKERNELAPI
#define NTHALAPI

#ifdef __cplusplus
extern "C" {
#endif

#include <ntstatus.h>
#ifdef _MAC
#include <macwin32.h>
#endif

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS; 

typedef enum _INTERFACE_TYPE {
    InterfaceTypeUndefined = -1,
    Internal,
    Isa,
    Eisa,
    MicroChannel,
    TurboChannel,
    PCIBus,
    VMEBus,
    NuBus,
    PCMCIABus,
    CBus,
    MPIBus,
    MPSABus,
    ProcessorInternal,
    InternalPowerBus,
    PNPISABus,
    PNPBus,
    MaximumInterfaceType
} INTERFACE_TYPE, *PINTERFACE_TYPE;

//
// Define types of bus information.
//

typedef enum _BUS_DATA_TYPE {
    ConfigurationSpaceUndefined = -1,
    Cmos,
    EisaConfiguration,
    Pos,
    CbusConfiguration,
    PCIConfiguration,
    VMEConfiguration,
    NuBusConfiguration,
    PCMCIAConfiguration,
    MPIConfiguration,
    MPSAConfiguration,
    PNPISAConfiguration,
    MaximumBusDataType
} BUS_DATA_TYPE, *PBUS_DATA_TYPE;

//
// A PCI driver can read the complete 256 bytes of configuration
// information for any PCI device by calling:
//
//      ULONG
//      HalGetBusData (
//          __in BUS_DATA_TYPE        PCIConfiguration,
//          __in ULONG                PciBusNumber,
//          __in PCI_SLOT_NUMBER      VirtualSlotNumber,
//          __in PPCI_COMMON_CONFIG   &PCIDeviceConfig,
//          __in ULONG                sizeof (PCIDeviceConfig)
//      );
//
//      A return value of 0 means that the specified PCI bus does not exist.
//
//      A return value of 2, with a VendorID of PCI_INVALID_VENDORID means
//      that the PCI bus does exist, but there is no device at the specified
//      VirtualSlotNumber (PCI Device/Function number).
//
//

// begin_ntminiport begin_ntndis

//
// Disable level 4 warning "C4214: nonstandard extension used : bit field types other than int"
// for PCI_SLOT_NUMBER structure. 
//
#pragma warning( push )
#pragma warning( disable : 4214 )

typedef struct _PCI_SLOT_NUMBER {
    union {
        struct {
            ULONG   DeviceNumber:5;
            ULONG   FunctionNumber:3;
            ULONG   Reserved:24;
        } bits;
        ULONG   AsULONG;
    } u;
} PCI_SLOT_NUMBER, *PPCI_SLOT_NUMBER;

#pragma warning( pop )

#define PCI_TYPE0_ADDRESSES             6
#define PCI_TYPE1_ADDRESSES             2
#define PCI_TYPE2_ADDRESSES             1

typedef struct _PCI_COMMON_CONFIG {
    USHORT  VendorID;                   // (ro)
    USHORT  DeviceID;                   // (ro)
    USHORT  Command;                    // Device control
    USHORT  Status;
    UCHAR   RevisionID;                 // (ro)
    UCHAR   ProgIf;                     // (ro)
    UCHAR   SubClass;                   // (ro)
    UCHAR   BaseClass;                  // (ro)
    UCHAR   CacheLineSize;              // (ro+)
    UCHAR   LatencyTimer;               // (ro+)
    UCHAR   HeaderType;                 // (ro)
    UCHAR   BIST;                       // Built in self test

    union {
        struct _PCI_HEADER_TYPE_0 {
            ULONG   BaseAddresses[PCI_TYPE0_ADDRESSES];
            ULONG   CIS;
            USHORT  SubVendorID;
            USHORT  SubSystemID;
            ULONG   ROMBaseAddress;
            ULONG   Reserved2[2];

            UCHAR   InterruptLine;      //
            UCHAR   InterruptPin;       // (ro)
            UCHAR   MinimumGrant;       // (ro)
            UCHAR   MaximumLatency;     // (ro)
        } type0;

        struct _PCI_HEADER_TYPE_1 {
            ULONG   BaseAddresses[PCI_TYPE1_ADDRESSES];
            UCHAR   PrimaryBusNumber;
            UCHAR   SecondaryBusNumber;
            UCHAR   SubordinateBusNumber;
            UCHAR   SecondaryLatencyTimer;
            UCHAR   IOBase;
            UCHAR   IOLimit;
            USHORT  SecondaryStatus;
            USHORT  MemoryBase;
            USHORT  MemoryLimit;
            USHORT  PrefetchableMemoryBase;
            USHORT  PrefetchableMemoryLimit;
            ULONG   PrefetchableMemoryBaseUpper32;
            ULONG   PrefetchableMemoryLimitUpper32;
            USHORT  IOBaseUpper;
            USHORT  IOLimitUpper;
            ULONG   Reserved2;
            ULONG   ExpansionROMBase;
            UCHAR   InterruptLine;
            UCHAR   InterruptPin;
            USHORT  BridgeControl;
        } type1;

        struct _PCI_HEADER_TYPE_2 {
            ULONG   BaseAddress;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved2;
            USHORT  SecondaryStatus;
            UCHAR   PrimaryBusNumber;
            UCHAR   CardbusBusNumber;
            UCHAR   SubordinateBusNumber;
            UCHAR   CardbusLatencyTimer;
            ULONG   MemoryBase0;
            ULONG   MemoryLimit0;
            ULONG   MemoryBase1;
            ULONG   MemoryLimit1;
            USHORT  IOBase0_LO;
            USHORT  IOBase0_HI;
            USHORT  IOLimit0_LO;
            USHORT  IOLimit0_HI;
            USHORT  IOBase1_LO;
            USHORT  IOBase1_HI;
            USHORT  IOLimit1_LO;
            USHORT  IOLimit1_HI;
            UCHAR   InterruptLine;
            UCHAR   InterruptPin;
            USHORT  BridgeControl;
            USHORT  SubVendorID;
            USHORT  SubSystemID;
            ULONG   LegacyBaseAddress;
            UCHAR   Reserved3[56];
            ULONG   SystemControl;
            UCHAR   MultiMediaControl;
            UCHAR   GeneralStatus;
            UCHAR   Reserved4[2];
            UCHAR   GPIO0Control;
            UCHAR   GPIO1Control;
            UCHAR   GPIO2Control;
            UCHAR   GPIO3Control;
            ULONG   IRQMuxRouting;
            UCHAR   RetryStatus;
            UCHAR   CardControl;
            UCHAR   DeviceControl;
            UCHAR   Diagnostic;
        } type2;

    } u;

    UCHAR   DeviceSpecific[108];

} PCI_COMMON_CONFIG, *PPCI_COMMON_CONFIG;


#define PCI_COMMON_HDR_LENGTH (FIELD_OFFSET (PCI_COMMON_CONFIG, DeviceSpecific))

#define PCI_MAX_BUS                         255
#define PCI_MAX_DEVICES                     32
#define PCI_MAX_FUNCTION                    8

#define PCI_INVALID_VENDORID                0xFFFF
#define PCI_INVALID_DEVICEID                0xFFFF

//
// Bit encodings for  PCI_COMMON_CONFIG.HeaderType
//

#define PCI_MULTIFUNCTION                   0x80
#define PCI_DEVICE_TYPE                     0x00
#define PCI_BRIDGE_TYPE                     0x01
#define PCI_CARDBUS_TYPE                    0x02

//
// Bit encodings for PCI_COMMON_CONFIG.Command
//

#define PCI_ENABLE_IO_SPACE                 0x0001
#define PCI_ENABLE_MEMORY_SPACE             0x0002
#define PCI_ENABLE_BUS_MASTER               0x0004
#define PCI_ENABLE_SPECIAL_CYCLES           0x0008
#define PCI_ENABLE_WRITE_AND_INVALIDATE     0x0010
#define PCI_ENABLE_VGA_COMPATIBLE_PALETTE   0x0020
#define PCI_ENABLE_PARITY                   0x0040  // (ro+)
#define PCI_ENABLE_WAIT_CYCLE               0x0080  // (ro+)
#define PCI_ENABLE_SERR                     0x0100  // (ro+)
#define PCI_ENABLE_FAST_BACK_TO_BACK        0x0200  // (ro)

//
// Bit encodings for PCI_COMMON_CONFIG.Status
//

#define PCI_STATUS_FAST_BACK_TO_BACK        0x0080  // (ro)
#define PCI_STATUS_DATA_PARITY_DETECTED     0x0100
#define PCI_STATUS_DEVSEL                   0x0600  // 2 bits wide
#define PCI_STATUS_SIGNALED_TARGET_ABORT    0x0800
#define PCI_STATUS_RECEIVED_TARGET_ABORT    0x1000
#define PCI_STATUS_RECEIVED_MASTER_ABORT    0x2000
#define PCI_STATUS_SIGNALED_SYSTEM_ERROR    0x4000
#define PCI_STATUS_DETECTED_PARITY_ERROR    0x8000

//
// Base Class Code encodings for Base Class (from PCI spec rev 2.1).
//

#define PCI_CLASS_PRE_20                    0x00
#define PCI_CLASS_MASS_STORAGE_CTLR         0x01
#define PCI_CLASS_NETWORK_CTLR              0x02
#define PCI_CLASS_DISPLAY_CTLR              0x03
#define PCI_CLASS_MULTIMEDIA_DEV            0x04
#define PCI_CLASS_MEMORY_CTLR               0x05
#define PCI_CLASS_BRIDGE_DEV                0x06
#define PCI_CLASS_SIMPLE_COMMS_CTLR         0x07
#define PCI_CLASS_BASE_SYSTEM_DEV           0x08
#define PCI_CLASS_INPUT_DEV                 0x09
#define PCI_CLASS_DOCKING_STATION           0x0a
#define PCI_CLASS_PROCESSOR                 0x0b
#define PCI_CLASS_SERIAL_BUS_CTLR           0x0c

// 0d thru fe reserved

#define PCI_CLASS_NOT_DEFINED               0xff

//
// Sub Class Code encodings (PCI rev 2.1).
//

// Class 00 - PCI_CLASS_PRE_20

#define PCI_SUBCLASS_PRE_20_NON_VGA         0x00
#define PCI_SUBCLASS_PRE_20_VGA             0x01

// Class 01 - PCI_CLASS_MASS_STORAGE_CTLR

#define PCI_SUBCLASS_MSC_SCSI_BUS_CTLR      0x00
#define PCI_SUBCLASS_MSC_IDE_CTLR           0x01
#define PCI_SUBCLASS_MSC_FLOPPY_CTLR        0x02
#define PCI_SUBCLASS_MSC_IPI_CTLR           0x03
#define PCI_SUBCLASS_MSC_RAID_CTLR          0x04
#define PCI_SUBCLASS_MSC_OTHER              0x80

// Class 02 - PCI_CLASS_NETWORK_CTLR

#define PCI_SUBCLASS_NET_ETHERNET_CTLR      0x00
#define PCI_SUBCLASS_NET_TOKEN_RING_CTLR    0x01
#define PCI_SUBCLASS_NET_FDDI_CTLR          0x02
#define PCI_SUBCLASS_NET_ATM_CTLR           0x03
#define PCI_SUBCLASS_NET_OTHER              0x80

// Class 03 - PCI_CLASS_DISPLAY_CTLR

// N.B. Sub Class 00 could be VGA or 8514 depending on Interface byte

#define PCI_SUBCLASS_VID_VGA_CTLR           0x00
#define PCI_SUBCLASS_VID_XGA_CTLR           0x01
#define PCI_SUBCLASS_VID_OTHER              0x80

// Class 04 - PCI_CLASS_MULTIMEDIA_DEV

#define PCI_SUBCLASS_MM_VIDEO_DEV           0x00
#define PCI_SUBCLASS_MM_AUDIO_DEV           0x01
#define PCI_SUBCLASS_MM_OTHER               0x80

// Class 05 - PCI_CLASS_MEMORY_CTLR

#define PCI_SUBCLASS_MEM_RAM                0x00
#define PCI_SUBCLASS_MEM_FLASH              0x01
#define PCI_SUBCLASS_MEM_OTHER              0x80

// Class 06 - PCI_CLASS_BRIDGE_DEV

#define PCI_SUBCLASS_BR_HOST                0x00
#define PCI_SUBCLASS_BR_ISA                 0x01
#define PCI_SUBCLASS_BR_EISA                0x02
#define PCI_SUBCLASS_BR_MCA                 0x03
#define PCI_SUBCLASS_BR_PCI_TO_PCI          0x04
#define PCI_SUBCLASS_BR_PCMCIA              0x05
#define PCI_SUBCLASS_BR_NUBUS               0x06
#define PCI_SUBCLASS_BR_CARDBUS             0x07
#define PCI_SUBCLASS_BR_OTHER               0x80

// Class 07 - PCI_CLASS_SIMPLE_COMMS_CTLR

// N.B. Sub Class 00 and 01 additional info in Interface byte

#define PCI_SUBCLASS_COM_SERIAL             0x00
#define PCI_SUBCLASS_COM_PARALLEL           0x01
#define PCI_SUBCLASS_COM_OTHER              0x80

// Class 08 - PCI_CLASS_BASE_SYSTEM_DEV

// N.B. See Interface byte for additional info.

#define PCI_SUBCLASS_SYS_INTERRUPT_CTLR     0x00
#define PCI_SUBCLASS_SYS_DMA_CTLR           0x01
#define PCI_SUBCLASS_SYS_SYSTEM_TIMER       0x02
#define PCI_SUBCLASS_SYS_REAL_TIME_CLOCK    0x03
#define PCI_SUBCLASS_SYS_OTHER              0x80

// Class 09 - PCI_CLASS_INPUT_DEV

#define PCI_SUBCLASS_INP_KEYBOARD           0x00
#define PCI_SUBCLASS_INP_DIGITIZER          0x01
#define PCI_SUBCLASS_INP_MOUSE              0x02
#define PCI_SUBCLASS_INP_OTHER              0x80

// Class 0a - PCI_CLASS_DOCKING_STATION

#define PCI_SUBCLASS_DOC_GENERIC            0x00
#define PCI_SUBCLASS_DOC_OTHER              0x80

// Class 0b - PCI_CLASS_PROCESSOR

#define PCI_SUBCLASS_PROC_386               0x00
#define PCI_SUBCLASS_PROC_486               0x01
#define PCI_SUBCLASS_PROC_PENTIUM           0x02
#define PCI_SUBCLASS_PROC_ALPHA             0x10
#define PCI_SUBCLASS_PROC_POWERPC           0x20
#define PCI_SUBCLASS_PROC_COPROCESSOR       0x40

// Class 0c - PCI_CLASS_SERIAL_BUS_CTLR

#define PCI_SUBCLASS_SB_IEEE1394            0x00
#define PCI_SUBCLASS_SB_ACCESS              0x01
#define PCI_SUBCLASS_SB_SSA                 0x02
#define PCI_SUBCLASS_SB_USB                 0x03
#define PCI_SUBCLASS_SB_FIBRE_CHANNEL       0x04




//
// Bit encodes for PCI_COMMON_CONFIG.u.type0.BaseAddresses
//

#define PCI_ADDRESS_IO_SPACE                0x00000001  // (ro)
#define PCI_ADDRESS_MEMORY_SPACE            0x00000000
#define PCI_ADDRESS_MEMORY_TYPE_MASK        0x00000006  // (ro)
#define PCI_ADDRESS_MEMORY_PREFETCHABLE     0x00000008  // (ro)

#define PCI_ADDRESS_IO_ADDRESS_MASK         0xfffffffc
#define PCI_ADDRESS_MEMORY_ADDRESS_MASK     0xfffffff0
#define PCI_ADDRESS_ROM_ADDRESS_MASK        0xfffff800

#define PCI_TYPE_32BIT      0
#define PCI_TYPE_20BIT      2
#define PCI_TYPE_64BIT      4

//
// Bit encodes for PCI_COMMON_CONFIG.u.type0.ROMBaseAddresses
//

#define PCI_ROMADDRESS_ENABLED              0x00000001

//
// ISA PnP Structures
//

typedef struct  _ISA_PNP_LOGICAL_DEVICE_INFO
{
    DWORD   LogicalDeviceID;
    DWORD   CompatibleIDs[8];
}   ISA_PNP_LOGICAL_DEVICE_INFO, *PISA_PNP_LOGICAL_DEVICE_INFO;

typedef struct  _ISA_PNP_CONFIG
{
    DWORD                           VendorID;
    DWORD                           SerialNumber;
    DWORD                           NumberLogicalDevices;
    ISA_PNP_LOGICAL_DEVICE_INFO     LogicalDeviceInfo[8];
}   ISA_PNP_CONFIG, *PISA_PNP_CONFIG;

typedef struct  _ISA_PNP_RESOURCES
{
    USHORT                          Flags;
    struct
    {
        USHORT      MemoryBase;
        USHORT      MemoryUpperLimit;
        UCHAR       MemoryControl;
    }                               Memory24Descriptors[4];
    struct
    {
        DWORD       MemoryBase;
        DWORD       MemoryUpperLimit;
        UCHAR       MemoryControl;
    }                               Memory32Descriptors[4];
    USHORT                          IoPortDescriptors[8];
    struct
    {
        UCHAR       IRQLevel;
        UCHAR       IRQType;
    }                               IRQDescriptors[2];
    UCHAR                           DMADescriptors[2];
}   ISA_PNP_RESOURCES, *PISA_PNP_RESOURCES;

#define ISA_PNP_RESOURCE_FLAG_ACTIVE    0x00000001

//++
//
// ULONG
// ROUND_TO_PAGES (
//     __in ULONG Size
//     )
//
// Routine Description:
//
//     The ROUND_TO_PAGES macro takes a size in bytes and rounds it up to a
//     multiple of the page size.
//
//     NOTE: This macro fails for values 0xFFFFFFFF - (PAGE_SIZE - 1).
//
// Arguments:
//
//     Size - Size in bytes to round up to a page multiple.
//
// Return Value:
//
//     Returns the size rounded up to a multiple of the page size.
//
//--

#define ROUND_TO_PAGES(Size)  (((ULONG)(Size) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

//++
//
// ULONG
// BYTES_TO_PAGES (
//     __in ULONG Size
//     )
//
// Routine Description:
//
//     The BYTES_TO_PAGES macro takes the size in bytes and calculates the
//     number of pages required to contain the bytes.
//
// Arguments:
//
//     Size - Size in bytes.
//
// Return Value:
//
//     Returns the number of pages required to contain the specified size.
//
//--

#define BYTES_TO_PAGES(Size)  (((ULONG)(Size) >> PAGE_SHIFT) + \
                               (((ULONG)(Size) & (PAGE_SIZE - 1)) != 0))

//++
//
// ULONG
// BYTE_OFFSET (
//     __in PVOID Va
//     )
//
// Routine Description:
//
//     The BYTE_OFFSET macro takes a virtual address and returns the byte offset
//     of that address within the page.
//
// Arguments:
//
//     Va - Virtual address.
//
// Return Value:
//
//     Returns the byte offset portion of the virtual address.
//
//--

#define BYTE_OFFSET(Va) ((ULONG)(Va) & (PAGE_SIZE - 1))


//++
//
// PVOID
// PAGE_ALIGN (
//     __in PVOID Va
//     )
//
// Routine Description:
//
//     The PAGE_ALIGN macro takes a virtual address and returns a page-aligned
//     virtual address for that page.
//
// Arguments:
//
//     Va - Virtual address.
//
// Return Value:
//
//     Returns the page aligned virtual address.
//
//--

#define PAGE_ALIGN(Va) ((PVOID)((ULONG)(Va) & ~(PAGE_SIZE - 1)))


//++
//
// ULONG
// ADDRESS_AND_SIZE_TO_SPAN_PAGES (
//     __in PVOID Va,
//     __in ULONG Size
//     )
//
// Routine Description:
//
//     The ADDRESS_AND_SIZE_TO_SPAN_PAGES macro takes a virtual address and
//     size and returns the number of pages spanned by the size.
//
// Arguments:
//
//     Va - Virtual address.
//
//     Size - Size in bytes.
//
// Return Value:
//
//     Returns the number of pages spanned by the size.
//
// Notes:
//
//     Do not call with a Size of zero, since it sometimes will return 1
//     instead of 0 for the number of pages.
//
//--

#define COMPUTE_PAGES_SPANNED(Va, Size) \
    ((((ULONG)(Va) & (PAGE_SIZE - 1)) + (Size) + (PAGE_SIZE - 1)) >> PAGE_SHIFT)

#define ADDRESS_AND_SIZE_TO_SPAN_PAGES(Va, Size) \
   COMPUTE_PAGES_SPANNED((Va), (Size))



// OEM IOCTL codes for IOCTL_HAL_DDK_CALL calls.
//
#define IOCTL_HAL_SETBUSDATA    0x01
#define IOCTL_HAL_GETBUSDATA    0x02

// Used by HalSetBusDataByOffset & HalGetBusDataByOffset when calling OAL.
//
typedef struct  __BUSDATA_PARMS
{
    __in  DWORD Function;    // Which function (IOCTL_HAL_GETBUSDATA/SETBUSDATA)
    __out ULONG ReturnCode;  // Return code from the function
    __in  BUS_DATA_TYPE BusDataType;
    __in  ULONG BusNumber;
    __in  ULONG SlotNumber;
    __in  PVOID Buffer;
    __in  ULONG Offset;
    __in  ULONG Length;
} BUSDATA_PARMS, *PBUSDATA_PARMS;


NTKERNELAPI
PVOID
MmMapIoSpace (
    __in PHYSICAL_ADDRESS PhysicalAddress,
    __in ULONG NumberOfBytes,
    __in BOOLEAN CacheEnable
    );

NTKERNELAPI
VOID
MmUnmapIoSpace (
    __in PVOID BaseAddress,
    __in ULONG NumberOfBytes
    );

NTKERNELAPI
BOOL
TransBusAddrToVirtual(
    __in INTERFACE_TYPE InterfaceType,
    __in ULONG BusNumber,
    __in PHYSICAL_ADDRESS BusAddress,
    __in ULONG Length,
    __inout PULONG AddressSpace,
    __out PPVOID MappedAddress
    );

NTKERNELAPI
BOOL
TransBusAddrToStatic(
    __in INTERFACE_TYPE InterfaceType,
    __in ULONG BusNumber,
    __in PHYSICAL_ADDRESS BusAddress,
    __in ULONG Length,
    __inout PULONG AddressSpace,
    __out PPVOID MappedAddress
    );
    
//
// I/O driver configuration functions.
//

NTHALAPI
ULONG
HalGetBusDataByOffset(
    __in BUS_DATA_TYPE BusDataType,
    __in ULONG BusNumber,
    __in ULONG SlotNumber,
    __in PVOID Buffer,
    __in ULONG Offset,
    __in ULONG Length
    );

ULONG __inline
HalGetBusData(
    __in BUS_DATA_TYPE BusDataType,
    __in ULONG BusNumber,
    __in ULONG SlotNumber,
    __in PVOID Buffer,
    __in ULONG Length
    )
{
    return HalGetBusDataByOffset(
        BusDataType, BusNumber, SlotNumber, Buffer, 0, Length);
}

NTHALAPI
ULONG
HalSetBusDataByOffset(
    __in BUS_DATA_TYPE BusDataType,
    __in ULONG BusNumber,
    __in ULONG SlotNumber,
    __in PVOID Buffer,
    __in ULONG Offset,
    __in ULONG Length
    );

ULONG __inline
HalSetBusData(
    __in BUS_DATA_TYPE BusDataType,
    __in ULONG BusNumber,
    __in ULONG SlotNumber,
    __in PVOID Buffer,
    __in ULONG Length
    )
{
    return HalSetBusDataByOffset(
        BusDataType, BusNumber, SlotNumber, Buffer, 0, Length);
}

NTHALAPI
BOOLEAN
HalTranslateBusAddress(
    __in INTERFACE_TYPE  InterfaceType,
    __in ULONG BusNumber,
    __in PHYSICAL_ADDRESS BusAddress,
    __inout PULONG AddressSpace,
    __out PPHYSICAL_ADDRESS TranslatedAddress
    );

NTHALAPI
BOOLEAN
HalTranslateSystemAddress(
    __in  INTERFACE_TYPE    InterfaceType,
    __in  ULONG             BusNumber,
    __in  PHYSICAL_ADDRESS  SystemAddress,
    __out PPHYSICAL_ADDRESS TranslatedAddress
    );


//
// DMA Adapter Description
//
typedef struct _DMA_ADAPTER_OBJECT_
{
    USHORT ObjectSize;                  // Size of structure (versioning).
    INTERFACE_TYPE InterfaceType;       // Adapter bus interface.
    ULONG BusNumber;                    // Adapter bus number.
} DMA_ADAPTER_OBJECT, *PDMA_ADAPTER_OBJECT;

//
// DMA functions.
//
NTHALAPI
PVOID
HalAllocateCommonBuffer(
    __in  PDMA_ADAPTER_OBJECT       Adapter,
    __in  ULONG              Length,
    __out PPHYSICAL_ADDRESS  LogicalAddress,
    __in  BOOLEAN            CacheEnabled
    );

NTHALAPI
VOID
HalFreeCommonBuffer(
    __in_opt PDMA_ADAPTER_OBJECT      Adapter,
    __in ULONG             Length,
    __in PHYSICAL_ADDRESS  LogicalAddress,
    __in PVOID             VirtualAddress,
    __in BOOLEAN           CacheEnabled
    );

//
// I/O space read and write macros.
//
//  These are implemented as functions in ceddk.dll, since only the platform
//  architect knows for sure how the peripherals are mapped to the chip.  An
//  appropriate DLL must then be written for each platform.
//
//  The READ/WRITE_REGISTER_* calls manipulate I/O registers in MEMORY space.
//  (Use x86 move instructions, with LOCK prefix to force correct behavior
//   w.r.t. caches and write buffers.)
//
//  The READ/WRITE_PORT_* calls manipulate I/O registers in PORT space.
//  (Use x86 in/out instructions.)
//

// 
// Use inline/macro versions of these APIs only when (a) performance is critical and
// (b) the underlying platform supports their use.
//

#ifdef CEDDK_USEDDKMACRO

#include <ddkmacro.h>

#else       // CEDDK_USEDDKMACRO

NTKERNELAPI
UCHAR
READ_REGISTER_UCHAR(
    __in volatile const UCHAR * const Register
    );

NTKERNELAPI
USHORT
READ_REGISTER_USHORT(
    __in volatile const USHORT * const Register
    );

NTKERNELAPI
ULONG
READ_REGISTER_ULONG(
    __in volatile const ULONG * const  Register
    );

NTKERNELAPI
VOID
READ_REGISTER_BUFFER_UCHAR(
    __in volatile const UCHAR * const  Register,
    __out_ecount(Count) UCHAR *  Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
READ_REGISTER_BUFFER_USHORT(
    __in volatile const USHORT * const Register,
    __out_ecount(Count) USHORT * Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
READ_REGISTER_BUFFER_ULONG(
    __in volatile const ULONG * const  Register,
    __out_ecount(Count) ULONG *  Buffer,
    __in ULONG   Count
    );


NTKERNELAPI
VOID
WRITE_REGISTER_UCHAR(
    __in volatile UCHAR * const  Register,
    __in UCHAR const Value
    );

NTKERNELAPI
VOID
WRITE_REGISTER_USHORT(
    __in volatile USHORT * const Register,
    __in USHORT  const Value
    );

NTKERNELAPI
VOID
WRITE_REGISTER_ULONG(
    __in volatile ULONG * const  Register,
    __in ULONG   const Value
    );

NTKERNELAPI
VOID
WRITE_REGISTER_BUFFER_UCHAR(
    __in volatile UCHAR * const  Register,
    __in_ecount(Count) const UCHAR *  Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
WRITE_REGISTER_BUFFER_USHORT(
    __in volatile USHORT * const Register,
    __in_ecount(Count) const USHORT * Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
WRITE_REGISTER_BUFFER_ULONG(
    __in volatile ULONG * const  Register,
    __in_ecount(Count) const ULONG *  Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
UCHAR
READ_PORT_UCHAR(
    __in volatile const UCHAR * const  Port
    );

NTKERNELAPI
USHORT
READ_PORT_USHORT(
    __in volatile const USHORT * const Port
    );

NTKERNELAPI
ULONG
READ_PORT_ULONG(
    __in volatile const ULONG * const  Port
    );

NTKERNELAPI
VOID
READ_PORT_BUFFER_UCHAR(
    __in volatile const UCHAR * const  Port,
    __out_ecount(Count) UCHAR *  Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
READ_PORT_BUFFER_USHORT(
    __in volatile const USHORT * const Port,
    __out_ecount(Count) USHORT * Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
READ_PORT_BUFFER_ULONG(
    __in volatile const ULONG * const  Port,
    __out_ecount(Count) ULONG *  Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
WRITE_PORT_UCHAR(
    __in volatile UCHAR * const  Port,
    __in UCHAR   const Value
    );

NTKERNELAPI
VOID
WRITE_PORT_USHORT(
    __in volatile USHORT * const Port,
    __in USHORT  const Value
    );

NTKERNELAPI
VOID
WRITE_PORT_ULONG(
    __in volatile ULONG * const  Port,
    __in ULONG   const Value
    );

NTKERNELAPI
VOID
WRITE_PORT_BUFFER_UCHAR(
    __in volatile UCHAR * const  Port,
    __in_ecount(Count) const UCHAR *  Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
WRITE_PORT_BUFFER_USHORT(
    __in volatile USHORT * const Port,
    __in_ecount(Count) const USHORT * Buffer,
    __in ULONG   Count
    );

NTKERNELAPI
VOID
WRITE_PORT_BUFFER_ULONG(
    __in volatile ULONG * const  Port,
    __in_ecount(Count) const ULONG *  Buffer,
    __in ULONG   Count
    );

#endif      // CEDDK_USEDDKMACRO

//
// Definitions for Stall Execution
//
extern HANDLE g_hCalibrateThread;

typedef  LONG  (*pRegCloseKey) (     HKEY     );
#ifdef UNICODE

typedef 
LONG
(*pRegCreateKeyEx) (
    __in HKEY hKey,
    __in LPCWSTR lpSubKey,
    __in DWORD Reserved,
    __in LPWSTR lpClass,
    __in DWORD dwOptions,
    __in REGSAM samDesired,
    __in LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __out PHKEY phkResult,
    __out LPDWORD lpdwDisposition
    );
#else
typedef 
LONG
(*pRegCreateKeyEx) (
    __in HKEY hKey,
    __in LPCSTR lpSubKey,
    __in DWORD Reserved,
    __in LPSTR lpClass,
    __in DWORD dwOptions,
    __in REGSAM samDesired,
    __in LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __out PHKEY phkResult,
    __out LPDWORD lpdwDisposition
    );
#endif // !UNICODE

#ifdef UNICODE
typedef 
LONG
 (*pRegQueryValueEx) (
    __in HKEY hKey,
    __in LPCWSTR lpValueName,
    __in LPDWORD lpReserved,
    __out LPDWORD lpType,
    __inout LPBYTE lpData,
    __inout LPDWORD lpcbData
    );
#else
typedef 
LONG
(*pRegQueryValueEx) (
    __in HKEY hKey,
    __in LPCSTR lpValueName,
    __in LPDWORD lpReserved,
    __out LPDWORD lpType,
    __inout LPBYTE lpData,
    __inout LPDWORD lpcbData
    );
#endif

#ifdef UNICODE
typedef 
LONG
(*pRegQueryValueEx) (
    __in HKEY hKey,
    __in LPCWSTR lpValueName,
    __in LPDWORD lpReserved,
    __out LPDWORD lpType,
    __inout LPBYTE lpData,
    __inout LPDWORD lpcbData
    );
#else
typedef 
LONG
(*pRegQueryValueEx) (
    __in HKEY hKey,
    __in LPCSTR lpValueName,
    __in LPDWORD lpReserved,
    __out LPDWORD lpType,
    __inout LPBYTE lpData,
    __inout LPDWORD lpcbData
    );
#endif

#ifdef UNICODE
typedef 
LONG
(*pRegSetValueEx) (
    __in HKEY hKey,
    __in LPCWSTR lpValueName,
    __in DWORD Reserved,
    __in DWORD dwType,
    __in CONST BYTE* lpData,
    __in DWORD cbData
    );
#else
typedef 
LONG
(*pRegSetValueEx) (
    __in HKEY hKey,
    __in LPCSTR lpValueName,
    __in DWORD Reserved,
    __in DWORD dwType,
    __in CONST BYTE* lpData,
    __in DWORD cbData
    );
#endif 

void
StallOneMicrosecond(void);

BOOL  
BeginCalibration (HKEY hKey);

void
CalibrateStallCounter(void);

void 
StallExecution (DWORD dwMicroSec);

#ifdef WINCEOEM
//------------------------------------------------------------------------------
// milli-second wait, use Sleep if possible
//
#include <pkfuncs.h>
#define MAX_STALL   (0x3fffffff/1000)
__inline void DDKDriverSleep (DWORD dwMilliSecond)
{
    if (IsInPwrHdlr ()) {
        DWORD dwMs;
        while (dwMilliSecond) {
            dwMs = (dwMilliSecond > MAX_STALL)? MAX_STALL : dwMilliSecond;
            StallExecution (dwMs * 1000);   // stall execution is in micro-second
            dwMilliSecond -= dwMs;
        }
    } else {
        Sleep (dwMilliSecond);
    }
}
#endif

#include <pm.h>
#include <CeBus.h>

#define PAGE_SIZE   VM_PAGE_SIZE
#define PAGE_SHIFT  VM_PAGE_SHIFT

HANDLE  CreateBusAccessHandle(__in LPCTSTR lpActiveRegPath);
VOID    CloseBusAccessHandle(__in_opt HANDLE hBusAccess);
BOOL    SetDevicePowerState(__in_opt HANDLE hBusAccess, __in CEDEVICE_POWER_STATE PowerState,__reserved PVOID pReserved);
BOOL    GetDevicePowerState(__in_opt HANDLE hBusAccess, __out PCEDEVICE_POWER_STATE pPowerState,__reserved PVOID pReserved);
BOOL    TranslateBusAddr(__in_opt HANDLE hBusAccess,
            __in INTERFACE_TYPE  InterfaceType,__in ULONG BusNumber,__in PHYSICAL_ADDRESS BusAddress,__inout PULONG AddressSpace,__out PPHYSICAL_ADDRESS TranslatedAddress );
BOOL    TranslateSystemAddr(__in_opt HANDLE hBusAccess,
            __in INTERFACE_TYPE  InterfaceType,__in ULONG BusNumber,__in PHYSICAL_ADDRESS SystemAddress,__out PPHYSICAL_ADDRESS TranslatedAddress );

ULONG   SetDeviceConfigurationData(__in_opt HANDLE hBusAccess,
            __in DWORD dwSpace,__in DWORD BusNumber,__in  DWORD SlotNumber,__in DWORD dwOffset, __in DWORD dwLength, __in_bcount(dwLength) PVOID pBuffer);
ULONG   GetDeviceConfigurationData(__in_opt HANDLE hBusAccess,
            __in DWORD dwSpace,__in DWORD BusNumber,__in DWORD SlotNumber,__in DWORD dwOffset,__in DWORD dwLength, __out_bcount(dwLength) PVOID pBuffer);
BOOL    GetParentDeviceInfo(__in_opt HANDLE hBusAccess,__out PDEVMGR_DEVICE_INFORMATION pDeviceInfo);
BOOL    GetChildDeviceRemoveState(__in_opt HANDLE hBusAccess, __out PDWORD lpdChildDeviceState);
BOOL    GetBusNamePrefix(__in_opt HANDLE hBusAccess, __out_ecount(dwSizeInCharacters) LPTSTR lpReturnStr,DWORD dwSizeInCharacters);
BOOL    BusTransBusAddrToVirtual( __in_opt HANDLE hBusAccess,__in INTERFACE_TYPE InterfaceType,__in ULONG BusNumber, __in PHYSICAL_ADDRESS BusAddress, __in ULONG Length,__inout PULONG AddressSpace, __out PPVOID MappedAddress);
BOOL    BusTransBusAddrToStatic(__in_opt HANDLE hBusAccess,__in INTERFACE_TYPE InterfaceType, __in ULONG BusNumber,__in PHYSICAL_ADDRESS BusAddress, __in ULONG Length, __inout PULONG AddressSpace, __out PPVOID MappedAddress);
BOOL    BusIoControl(__in_opt HANDLE hBusAccess,__in  DWORD dwIoControlCode, __in_bcount_opt(nInBufferSize) LPVOID lpInBuffer, __in DWORD nInBufferSize, __out_bcount_opt(nOutBufferSize) LPVOID lpOutBuffer,__in DWORD nOutBufferSize, __out_opt LPDWORD lpBytesReturned,__in_opt LPOVERLAPPED lpOverlapped);
BOOL    BusChildIoControl(__in_opt HANDLE hBusAccess,__in DWORD dwIoControlCode, __out_bcount_opt (nBufferSize)LPVOID lpBuffer, __in DWORD  nBufferSize) ;

// Notification Function.
DWORD   CeDriverGetDirectCaller();
HANDLE  CeDriverDuplicateCallerHandle( 
  IN HANDLE DirectCallerHandle, 
  IN DWORD dwDesiredAccess, 
  IN BOOL bInheritHandle, 
  IN DWORD dwOptions
); 


typedef BOOL (WINAPI *LPNOTIFY_CALLBACK_ROUTINE)(
    DWORD dwIoControlCode, __inout_bcount_opt(nInBufSize)LPVOID lpInBuf, DWORD nInBufSize, __inout_bcount_opt(nOutBufSize) LPVOID lpOutBuf, DWORD nOutBufSize, __out_opt LPDWORD lpBytesReturned, __reserved LPOVERLAPPED lpOverlapped
);

HANDLE CeDriverMapCallbackFunction(
 IN LPNOTIFY_CALLBACK_ROUTINE lpCallback
) ;
BOOL CeDriverPerformCallback(
  IN HANDLE hCallback, DWORD dwIoControlCode, __inout_bcount_opt(nInBufSize)LPVOID lpInBuf, DWORD nInBufSize, __inout_bcount_opt(nOutBufSize) LPVOID lpOutBuf, DWORD nOutBufSize, __out_opt LPDWORD lpBytesReturned, __reserved LPOVERLAPPED lpOverlapped
);

///////////////////////////////////////////////////////////////////////////////
// DRIVERHELPER_POWER library
///////////////////////////////////////////////////////////////////////////////

typedef CEDEVICE_POWER_STATE (*PFN_SETPOWERLEVEL)( DWORD, CEDEVICE_POWER_STATE );
typedef void (*PFN_SETPOWERLEVELCALLBACK)( DWORD, CEDEVICE_POWER_STATE );

// lock mechanism initialization/cleanup
HANDLE DDKPwr_Initialize(__in PFN_SETPOWERLEVEL pSetPowerLevelFn,__in DWORD dwContext,__in BOOL fAbortOnPMRequests,__in DWORD dwTimeout );
void   DDKPwr_Deinitialize(__in HANDLE hPowerLock );

// power level lock acquire/release
HANDLE DDKPwr_RequestLevel(__in HANDLE hPowerLock,__in CEDEVICE_POWER_STATE dx );
void   DDKPwr_ReleaseLevel(__in HANDLE hPowerLock,__in HANDLE hLevelLock );

// power level get/set
CEDEVICE_POWER_STATE DDKPwr_GetDeviceLevel(__in HANDLE hPowerLock );
BOOL DDKPwr_SetDeviceLevel(__in HANDLE hPowerLock,__in CEDEVICE_POWER_STATE dx, __in_opt PFN_SETPOWERLEVELCALLBACK pCallbackFn );

#ifdef __cplusplus
}
#endif // __cplusplus
#include <oaldma.h>

#endif // _CEDDK_

