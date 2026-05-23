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
#ifndef _FLASHPDD_H_
#define _FLASHPDD_H_

#include <winioctl.h>
#include <FlashPddCommon.h>

#if __cplusplus
extern "C" {
#endif

#define IOCTL_FLASH_PDD_BASE            0x100
#define IOCTL_FLASH_PDD_OPTIONAL_BASE   0x120

//==============================================================================
//
// Required Flash PDD IOCTLs
//
// The following IOCTLs are required to be implemented.  Any IOCTL parameters
// not specified in the description are not used and should be set to NULL/0.
//
//==============================================================================

//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_GET_REGION_COUNT
//
// Query the number of flash hardware regions.
//
// lpOutBuffer
//
//     [out] Number of flash hardware regions.
//
// nOutBufferSize
//
//     [in] Set to sizeof(DWORD).
//
//
#define IOCTL_FLASH_PDD_GET_REGION_COUNT    CTL_CODE(                   \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x1, METHOD_BUFFERED,     \
    FILE_READ_ACCESS)


//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_GET_REGION_INFO
//
// Get region information from the flash PDD.  This IOCTL returns an
// array of FLASH_REGION_INFO structures, where each element corresponds
// to a flash hardware region.  Flash hardware regions have fixed
// physical block boundaries and may have different characteristics,
// such as sector size and block size.
//
// lpOutBuffer
//
//     [out] Array of FLASH_REGION_INFO structures.
//
// nOutBufferSize
//
//     [in] Set to RegionCount * sizeof(FLASH_REGION_INFO).  The
//     RegionCount can be obtained through IOCTL_FLASH_PDD_GET_REGION_COUNT.
//
//
#define IOCTL_FLASH_PDD_GET_REGION_INFO     CTL_CODE(                   \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x2, METHOD_BUFFERED,     \
    FILE_READ_ACCESS)


//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_GET_BLOCK_STATUS
//
// Query the status of a particular block.
//
// lpInBuffer
//
//     [in] Pointer to a FLASH_GET_BLOCK_STATUS_REQUEST structure describing
//     the run of blocks .
//
// nInBufferSize
//
//     [in] Set to sizeof(FLASH_GET_BLOCK_STATUS_REQUEST).
//
// lpOutBuffer
//
//     [out] Array of ULONG, which each ULONG representing the status for the
//      corresponding block.
//
// nOutBufferSize
//
//     [in] Size of the array of ULONGs.  Must equal sizeof(ULONG) * BlockCount
//     specified in the BLOCK_RUN input structure.
//
#define IOCTL_FLASH_PDD_GET_BLOCK_STATUS    CTL_CODE(                   \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x3, METHOD_BUFFERED,     \
    FILE_READ_ACCESS)

// FLASH_GET_BLOCK_STATUS_REQUEST
//
// Input structure for IOCTL_FLASH_PDD_GET_BLOCK_STATUS.
//
typedef struct FLASH_GET_BLOCK_STATUS_REQUEST
{
    BLOCK_RUN BlockRun;
    BOOL IsInitialFlash;
} FLASH_GET_BLOCK_STATUS_REQUEST;


//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_SET_BLOCK_STATUS
//
// Set the status of a particular block to a particular status defined in
// the FLASH_BLOCK_STATUS enumeration, such as bad or reserved.
//
// lpInBuffer
//
//     [in] Pointer to a FLASH_SET_BLOCK_STATUS_REQUEST structure describing
//     the run of blocks and status to set.
//
// nInBufferSize
//
//     [in] Set to sizeof(FLASH_SET_BLOCK_STATUS_REQUEST).
//
//
#define IOCTL_FLASH_PDD_SET_BLOCK_STATUS    CTL_CODE(                   \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x4, METHOD_BUFFERED,     \
    FILE_WRITE_ACCESS)

// FLASH_SET_BLOCK_STATUS_REQUEST
//
// Input structure for IOCTL_FLASH_PDD_SET_BLOCK_STATUS.
//
typedef struct FLASH_SET_BLOCK_STATUS_REQUEST
{
    BLOCK_RUN BlockRun;
    ULONG BlockStatus;
} FLASH_SET_BLOCK_STATUS_REQUEST;


//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_READ_PHYSICAL_SECTORS
//
// Read data and/or spare area from multiple, possibly discontiguous sectors.
//
// lpInBuffer
//
//     [in] Pointer to an array of FLASH_PDD_TRANSFER structures, where each
//     FLASH_PDD_TRANSFER describes a request of contiguous sectors to read.
//
// nInBufferSize
//
//     [in] Set to the size in bytes of the FLASH_PDD_TRANSFER array.
//
// lpOutBuffer
//
//     [out] Pointer to FLASH_READ_STATUS indicating status of the read.
//
// nOutBufferSize
//
//     [in] Set to sizeof(ULONG).
//
#define IOCTL_FLASH_PDD_READ_PHYSICAL_SECTORS   CTL_CODE(               \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x5, METHOD_BUFFERED,     \
    FILE_READ_ACCESS)


//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_WRITE_PHYSICAL_SECTORS
//
// Write data and/or spare area from multiple, possibly discontiguous sectors.
//
// lpInBuffer
//
//     [in] Pointer to an array of FLASH_PDD_TRANSFER structures, where each
//     FLASH_PDD_TRANSFER describes a request of contiguous sectors to write.
//
// nInBufferSize
//
//     [in] Set to the size in bytes of the FLASH_PDD_TRANSFER array.
//
// lpOutBuffer
//
//     [out] Pointer to FLASH_WRITE_STATUS indicating status of the write. 
//     Currently none defined.
//
// nOutBufferSize
//
//     [in] Set to sizeof(ULONG).
//
//
#define IOCTL_FLASH_PDD_WRITE_PHYSICAL_SECTORS  CTL_CODE(               \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x6, METHOD_BUFFERED,     \
    FILE_WRITE_ACCESS)

//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_ERASE_BLOCKS
//
// Erase multiple, possibly discontiguous blocks.
//
// lpInBuffer
//
//     [in] Pointer to an array of BLOCK_RUN structures, where each BLOCK_RUN
//     describes a run of blocks to erase.
//
// nInBufferSize
//
//     [in] Set to the size in bytes of the BLOCK_RUN array.
//
//
#define IOCTL_FLASH_PDD_ERASE_BLOCKS            CTL_CODE(               \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x7, METHOD_BUFFERED,     \
    FILE_WRITE_ACCESS)

//==============================================================================
//
// Optional Flash PDD IOCTLs
//
// The following IOCTLs are optional.  If a particular IOCTL is not
// implemented, then return FALSE and SetLastError to ERROR_NOT_SUPPORTED.
//

//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_COPY_PHYSICAL_SECTORS
//
// Copy data from multiple source sectors to destination sectors.
//
// lpInBuffer
//
//     [in] Pointer to an array of FLASH_PDD_COPY structures, where each
//     FLASH_PDD_COPY describes a request of contiguous sectors to copy.
//
// nInBufferSize
//
//     [in] Set to the size in bytes of the FLASH_PDD_COPY array.
//
//
#define IOCTL_FLASH_PDD_COPY_PHYSICAL_SECTORS   CTL_CODE(               \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x2,             \
    METHOD_BUFFERED, FILE_WRITE_ACCESS)

//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_GET_PHYSICAL_SECTOR_ADDRESS
//
// Retrieve the physical sector address. Must be implemented if XIP is to
// be supported.
//
// lpInBuffer
//
//     [in] Pointer to a FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST structure,
//     which contains a single run of sectors to query.
//
// nInBufferSize
//
//     [in] Set to sizeof(FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST).
//
// lpOutBuffer
//
//     [out] Pointer to an array of void* pointers, where each pointer contains
//     the statically mapped virtual address of the corresponding sector.
//
// nOutBufferSize
//
//     [in] Set to the size in bytes of the output array.  Must equal to the
//     sizeof(void*) * SectorCount in the SECTOR_RUN structure.
//
#define IOCTL_FLASH_PDD_GET_PHYSICAL_SECTOR_ADDRESS     CTL_CODE(       \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x3,             \
    METHOD_BUFFERED, FILE_READ_ACCESS)

// FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST
//
// Input structure for IOCTL_FLASH_PDD_GET_PHYSICAL_SECTOR_ADDRESS
//
typedef struct FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST
{
    DWORD RegionIndex;
    SECTOR_RUN SectorRun;
} FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST;


//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_LOCK_BLOCKS
//
// Hardware lock one or more contiguous range of physical blocks, such that
// blocks cannot be unlocked without a power reset.  Must be implemented if
// block locking is to be supported.  BlockRun specifies the run of blocks
// to lock. All other blocks are assumed to be unlocked.
//
// lpInBuffer
//
//     [in] Pointer to an array of BLOCK_RUN structures, where each element
//     contains a single run of blocks to lock.  All other blocks should
//     be unlocked.
//
// nInBufferSize
//
//     [in] Set to sizeof(BLOCK_RUN) * number of elements.
//
//
#define IOCTL_FLASH_PDD_LOCK_BLOCKS                     CTL_CODE(       \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x4,             \
    METHOD_BUFFERED, FILE_READ_ACCESS)

//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_GET_LIFE_CYCLE_INFO
//
// Get life cycle information for each of the flash regions, such
// as number of typical erases per block.
// This IOCTL returns an array of FLASH_LIFE_CYCLE_INFO structures,
// where each element corresponds to a flash hardware region.
//
// lpOutBuffer
//
//     [out] Array of FLASH_LIFE_CYCLE_INFO structures.
//
// nOutBufferSize
//
//     [in] Set to RegionCount * sizeof(FLASH_LIFE_CYCLE_INFO).  The
//     RegionCount can be obtained through IOCTL_FLASH_PDD_GET_REGION_COUNT.
//
//
#define IOCTL_FLASH_PDD_GET_LIFE_CYCLE_INFO             CTL_CODE(       \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x6,             \
    METHOD_BUFFERED, FILE_READ_ACCESS)

//------------------------------------------------------------------------------
//
// IOCTL_FLASH_PDD_GET_IDENTITY_INFO
//
// Get identity information for the flash part, such
// as the manufacturer id and serial number.
//
// lpOutBuffer
//
//     [out] Pointer to FLASH_IDENTITY_INFO structure.
//
// nOutBufferSize
//
//     [in] Set to sizeof(FLASH_IDENTITY_INFO).
//
//
#define IOCTL_FLASH_PDD_GET_IDENTITY_INFO               CTL_CODE(       \
    FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x7,             \
    METHOD_BUFFERED, FILE_READ_ACCESS)

//------------------------------------------------------------------------------

#if __cplusplus
}
#endif

#endif // #define _FLASHPDD_H_

