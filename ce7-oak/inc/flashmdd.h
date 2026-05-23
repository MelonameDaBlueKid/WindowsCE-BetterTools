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
#ifndef _FLASHMDD_H_
#define _FLASHMDD_H_ 

#include <FlashMddCommon.h>
#include <FlashPdd.h>

#if __cplusplus
extern "C" {
#endif

// New IOControlCode values

#define IOCTL_FLASH_BASE                0
#define IOCTL_FLASH_OPTIONAL_BASE       0x20

// ---------------------------------------------------------------------------
// 
// Required Flash MDD IOCTLs
//
// The following IOCTLs are required to be implemented.  Any IOCTL parameters
// not specified in the description are not used and should be set to NULL/0.
//
// ---------------------------------------------------------------------------

//
// IOCTL_FLASH_READ_LOGICAL_SECTORS
//
// Read a set of sector range/sector data pairs from the storage media in a 
// single transfer. Similar to IOCTL_DISK_READ_SECTOR, but sectors ranges are 
// NOT required to be contiguous.
// 
// lpInBuffer
// 
//     [in] Pointer to a FLASH_TRANSFER_REQUEST structure.
//
// nInBufferSize
// 
//     [in] Set to sizeof(FLASH_TRANSFER_REQUEST) plus an additional 
//     sizeof(FLASH_SECTOR_TRANSFER) for each FLASH_SECTOR_TRANSFER in 
//     BufferList beyond 1.
//     
#define IOCTL_FLASH_READ_LOGICAL_SECTORS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x1, METHOD_BUFFERED, FILE_READ_ACCESS)


//
// IOCTL_FLASH_WRITE_LOGICAL_SECTORS
//
// Write a set of sector range/sector data pairs to the storage media in a 
// single transfer. Similar to IOCTL_DISK_WRITE_SECTOR, but sectors ranges are 
// NOT required to be contiguous.
// 
// lpInBuffer
// 
//     [in] Pointer to a FLASH_TRANSFER_REQUEST structure.
//
// nInBufferSize
// 
//     [in] Set to sizeof(FLASH_TRANSFER_REQUEST) plus an additional 
//     sizeof(FLASH_SECTOR_TRANSFER) for each FLASH_SECTOR_TRANSFER in 
//     BufferList beyond 1.
//     
#define IOCTL_FLASH_WRITE_LOGICAL_SECTORS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x2, METHOD_BUFFERED, FILE_WRITE_ACCESS)


//
// IOCTL_FLASH_DELETE_LOGICAL_SECTORS
//
// Delete a set of sector ranges from the storage media in a single operation.
// Similar to IOCTL_DISK_DELETE_SECTORS, except it allows for multiple
// discontiguous sector ranges to be specified in a single request.
// 
// lpInBuffer
// 
//     [in] Pointer to a FLASH_SECTOR_DELETE structure.
//
// nInBufferSize
// 
//     [in] Set to sizeof(FLASH_SECTOR_DELETE) plus an additional 
//     sizeof(SECTOR_RUN) for each SECTOR_RUN in 
//     SectorRunList beyond 1.
//     
#define IOCTL_FLASH_DELETE_LOGICAL_SECTORS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x3, METHOD_BUFFERED, FILE_WRITE_ACCESS)



//
// IOCTL_FLASH_FORMAT_STORE
//
// Erase all the blocks in the flash region and reinitialize partition table.
// 
// lpInBuffer
// 
//     [in] Pointer to a DWORD containing the region index to format.
//     Pass NULL to format all regions.
//
// nInBufferSize
// 
//     [in] Set to sizeof(DWORD) if formatting single region.  
//     Set to 0 if formatting entire store.
//     
#define IOCTL_FLASH_FORMAT_STORE \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x4, METHOD_BUFFERED, FILE_WRITE_ACCESS)

//
// IOCTL_FLASH_FORMAT_PARTITION
//
// Erase all the blocks in a single partition.
// 
// lpInBuffer
// 
//     [in] Pointer to a PARTITION_ID containing the partition id to format.
//
// nInBufferSize
// 
//     [in] Set to sizeof(PARTITION_ID)
//     
#define IOCTL_FLASH_FORMAT_PARTITION \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x5, METHOD_BUFFERED, FILE_WRITE_ACCESS)

//
// IOCTL_FLASH_SET_SECURE_WIPE
//
// Secure wipe a single partition.
// 
// lpInBuffer
// 
//     [in] Pointer to a PARTITION_ID containing the partition id to secure wipe.
//
// nInBufferSize
// 
//     [in] Set to sizeof(PARTITION_ID)
//     
#define IOCTL_FLASH_SECURE_WIPE \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x6, METHOD_BUFFERED, FILE_WRITE_ACCESS)

//
// IOCTL_FLASH_SET_SECURE_WIPE_FLAG
//
// Sets the secure wipe flash in the flash partition, which will trigger
// a secure wipe upon the next reboot
// 
// lpInBuffer
// 
//     [in] Pointer to a PARTITION_ID containing the partition id to set flag.
//
// nInBufferSize
// 
//     [in] Set to sizeof(PARTITION_ID)
//     
#define IOCTL_FLASH_SET_SECURE_WIPE_FLAG \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x7, METHOD_BUFFERED, FILE_WRITE_ACCESS)


//
// IOCTL_FLASH_GET_PARTITION_TABLE
//
// Get the entire partition table across all flash regions.  
// This returns an array of FLASH_PARTITION_INFO structures with 
// the number of elements equal to the number of partitions on flash.
// 
// lpOutBuffer
//
//     [out] Receives the partition table.  Pass NULL to query the
//     size of the partition table.
//
// nOutBufferSize
// 
//     [in] Size in bytes of the partition table buffer passed in.
//     
// pBytesReturned
//
//     [out] Size of the partition table in bytes.  Used to 
//     query the size of the partition table before calling again
//     with the actual buffer for the table.
//
//
#define IOCTL_FLASH_GET_PARTITION_TABLE \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x8, METHOD_BUFFERED, FILE_READ_ACCESS)


//
// IOCTL_FLASH_GET_REGION_FREE_SPACE
//
// Get the number of free blocks in a particular region
// that can be used for creating new partitions.  The block
// count accounts for bad blocks.
// 
// lpInBuffer
//
//     [in] Pointer to a DWORD containing region index to
//     get free space from.
//
// nInBufferSize
// 
//     [in] Set to sizeof(DWORD)
//     
// lpOutBuffer
//
//     [out] Receives the number of free blocks available.
//
// nOutBufferSize
// 
//     [in] Set to sizeof(DWORD)
//     
//
#define IOCTL_FLASH_GET_REGION_FREE_SPACE \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0x9, METHOD_BUFFERED, FILE_WRITE_ACCESS)


//
// IOCTL_FLASH_CREATE_PARTITION
//
// Creates one or more new partition.  The partition is located at the end of
// the existing partitions.
// 
// lpInBuffer
//
//     [in] Pointer to an array of FLASH_PARTITION_CREATE_INFO structures, 
//     which contains the parameters for the request.
//
// nInBufferSize
// 
//     [in] Set to sizeof(FLASH_PARTITION_CREATE_INFO) * number of elements
//     
// lpOutBuffer
//
//     [in] Pointer to an array of FLASH_PARTITION_INFO structures, which
//     contains the info for the created partition(s).  Pass in 
//     NULL if this is not needed.
//
// nOutBufferSize
// 
//     [in] Set to sizeof(FLASH_PARTITION_INFO) * number of elements.
//     0 if not needed.
//
#define IOCTL_FLASH_CREATE_PARTITION \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0xA, METHOD_BUFFERED, FILE_WRITE_ACCESS)

//
// IOCTL_FLASH_SECURE_DELETE
//
// Force all deleted sectors to be securely erased from flash.
// 
// lpInBuffer
// 
//     [in] Pointer to a PARTITION_ID containing the partition id to secure delete.
//
// nInBufferSize
// 
//     [in] Set to sizeof(PARTITION_ID)
//     
#define IOCTL_FLASH_SECURE_DELETE \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0xB, METHOD_BUFFERED, FILE_WRITE_ACCESS)

//
// IOCTL_FLASH_DELETE_PARTITION
//
// Deletes one or more partitions.  Partitions should be deleted to the end
// of flash first before creating new partitions.
// 
// lpInBuffer
//
//     [in] Pointer to a FLASH_PARTITION_DELETE_INFO structure, 
//     which contains the parameters for the request.
//
// nInBufferSize
// 
//     [in] Set to sizeof(FLASH_PARTITION_DELETE_INFO)
//     
#define IOCTL_FLASH_DELETE_PARTITION \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_BASE + 0xC, METHOD_BUFFERED, FILE_WRITE_ACCESS)


// ---------------------------------------------------------------------------
//
// Optional Flash MDD IOCTLs
//
// The following IOCTLs are optional.  If a particular IOCTL is not 
// implemented, then return FALSE and SetLastError to ERROR_NOT_SUPPORTED.
//
// ---------------------------------------------------------------------------

//
// IOCTL_FLASH_GET_SECTOR_ADDRESS
//
// For each logical sector address provided in the list, this retrieves the 
// corresponding statically mapped virtual address of the physical sector.
// 
// lpInBuffer
// 
//     [in] Pointer to a FLASH_GET_SECTOR_ADDRESS structure
//
// nInBufferSize
// 
//     [in] Set to sizeof(FLASH_GET_SECTOR_ADDRESS) plus an additional 
//     sizeof(ULONG) for each logical sector beyond 1.
//     
// lpOutBuffer
//
//     [out] Receives the array of physical sector addresses.
//
// nOutBufferSize
// 
//     [in] Size of the physical sector address array.
//     
#define IOCTL_FLASH_GET_SECTOR_ADDRESS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_OPTIONAL_BASE + 0x1, METHOD_BUFFERED, FILE_READ_ACCESS)

//
// IOCTL_FLASH_LOCK_PARTITIONS
//
// Lock one or more partitions, such that blocks cannot be unlocked without
// a power reset.  All other partitions on store will be unlocked.
// The IOCTL allows for discontiguous regions to be locked, but the flash
// part may not support this, so caller needs to know limitations of the part.
// 
// lpInBuffer
// 
//     [in] Pointer to an array of PARTITION_ID structures, where each entry
//     specifies a partition identifier to lock.
//
// nInBufferSize
// 
//     [in] Set to sizeof(PARTITION_ID) * number of elements in array.
//     
#define IOCTL_FLASH_LOCK_PARTITIONS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_OPTIONAL_BASE + 0x2, METHOD_BUFFERED, FILE_WRITE_ACCESS)

//
// IOCTL_FLASH_GET_CONFIGURATION_SETTINGS
//
// Gets the configuration settings of a particular flash partition.  
// 
// lpInBuffer
// 
//     [in] Pointer to a PARTITION_ID containing the partition id to get settings for.
//
// nInBufferSize
// 
//     [in] Set to sizeof(PARTITION_ID)
//
// lpOutBuffer
// 
//     [out] Pointer to a FLASH_CONFIGURATION_SETTINGS structure.
//
// nOutBufferSize
// 
//     [in] Set to sizeof(FLASH_CONFIGURATION_SETTINGS).
//     
#define IOCTL_FLASH_GET_CONFIGURATION_SETTINGS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_OPTIONAL_BASE + 0x3, METHOD_BUFFERED, FILE_READ_ACCESS)


//
// IOCTL_FLASH_SET_CONFIGURATION_SETTINGS
//
// Sets the configuration settings of a particular flash partition.  The flags
// field in FLASH_CONFIGURATION_SETTINGS specifies which particular settings
// to actually apply.
// 
// lpInBuffer
// 
//     [in] Pointer to a FLASH_CONFIGURATION_SETTINGS structure.
//
// nInBufferSize
// 
//     [in] Set to sizeof(FLASH_CONFIGURATION_SETTINGS).
//     
#define IOCTL_FLASH_SET_CONFIGURATION_SETTINGS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_OPTIONAL_BASE + 0x4, METHOD_BUFFERED, FILE_WRITE_ACCESS)


//
// IOCTL_FLASH_PERFORM_CHECKPOINT
//
// Persist the flash driver state to flash.  Called automatically
// on Deinit.
// 
// lpInBuffer
// 
//     [in] Pointer to a PARTITION_ID structure, specifying partition to perform a 
//          checkpoint on.  Specify NULL to checkpoint all partitions in all regions.
//
// nInBufferSize
// 
//     [in] Set to sizeof(PARTITION_ID) if checkpointing one partition or 
//          0 if checkpointing all partitions.
//     
#define IOCTL_FLASH_PERFORM_CHECKPOINT \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_OPTIONAL_BASE + 0x5, METHOD_BUFFERED, FILE_WRITE_ACCESS)


//------------------------------------------------------------------------------

#if __cplusplus
}
#endif

#endif // #define _FLASHMDD_H_ 
