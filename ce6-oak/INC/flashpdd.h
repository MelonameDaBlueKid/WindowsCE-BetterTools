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
#include "FlashCommon.h"

#define IOCTL_FLASH_PDD_BASE 0x100
#define IOCTL_FLASH_PDD_OPTIONAL_BASE 0x120

// ---------------------------------------------------------------------------
// 
// Required Flash PDD IOCTLs
//
// The following IOCTLs are required to be implemented.  Any IOCTL parameters
// not specified in the description are not used and should be set to NULL/0.
//
// ---------------------------------------------------------------------------


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
#define IOCTL_FLASH_PDD_GET_REGION_COUNT \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x1, METHOD_BUFFERED, FILE_READ_ACCESS)


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
#define IOCTL_FLASH_PDD_GET_REGION_INFO \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x2, METHOD_BUFFERED, FILE_READ_ACCESS)


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
 #define IOCTL_FLASH_PDD_GET_BLOCK_STATUS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x3, METHOD_BUFFERED, FILE_READ_ACCESS)


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
#define IOCTL_FLASH_PDD_SET_BLOCK_STATUS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x4, METHOD_BUFFERED, FILE_WRITE_ACCESS)


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
#define IOCTL_FLASH_PDD_READ_PHYSICAL_SECTORS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x5, METHOD_BUFFERED, FILE_READ_ACCESS)


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
//     [out] Pointer to FLASH_WRITE_STATUS indicating status of the write. Currently none defined.
//
// nOutBufferSize
// 
//     [in] Set to sizeof(ULONG).
//     
//     
#define IOCTL_FLASH_PDD_WRITE_PHYSICAL_SECTORS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x6, METHOD_BUFFERED, FILE_WRITE_ACCESS)

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
#define IOCTL_FLASH_PDD_ERASE_BLOCKS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_BASE + 0x7, METHOD_BUFFERED, FILE_WRITE_ACCESS)



// ---------------------------------------------------------------------------
//
// Optional Flash PDD IOCTLs
//
// The following IOCTLs are optional.  If a particular IOCTL is not 
// implemented, then return FALSE and SetLastError to ERROR_NOT_SUPPORTED.
//
// ---------------------------------------------------------------------------

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
#define IOCTL_FLASH_PDD_COPY_PHYSICAL_SECTORS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x2, METHOD_BUFFERED, FILE_WRITE_ACCESS)


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
#define IOCTL_FLASH_PDD_GET_PHYSICAL_SECTOR_ADDRESS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x3, METHOD_BUFFERED, FILE_READ_ACCESS)


//
// IOCTL_FLASH_PDD_LOCK_BLOCKS
//
//?Hardware lock one or more contiguous range of physical blocks, such that    
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
#define IOCTL_FLASH_PDD_LOCK_BLOCKS \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x4, METHOD_BUFFERED, FILE_READ_ACCESS)

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
#define IOCTL_FLASH_PDD_GET_LIFE_CYCLE_INFO \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x6, METHOD_BUFFERED, FILE_READ_ACCESS)


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
#define IOCTL_FLASH_PDD_GET_IDENTITY_INFO \
    CTL_CODE(FILE_DEVICE_FLASH, IOCTL_FLASH_PDD_OPTIONAL_BASE + 0x7, METHOD_BUFFERED, FILE_READ_ACCESS)


// ---------------------------------------------------------------------------
//
// Structure definitions for Flash PDD
//
// ---------------------------------------------------------------------------

// FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST
//
// Input structure for IOCTL_FLASH_PDD_GET_PHYSICAL_SECTOR_ADDRESS
//
typedef struct __FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST
{
    DWORD RegionIndex;
    SECTOR_RUN SectorRun;
    
} FLASH_GET_PHYSICAL_SECTOR_ADDRESS_REQUEST;

// FLASH_BLOCK_STATUS
//
// Possible block status values for GetBlockStatus and SetBlockStatus.
//
enum FLASH_BLOCK_STATUS
{
    FLASH_BLOCK_STATUS_BAD      = 0x1,
    FLASH_BLOCK_STATUS_RESERVED = 0x2
};

// FLASH_GET_BLOCK_STATUS_REQUEST
//
// Input structure for IOCTL_FLASH_PDD_GET_BLOCK_STATUS.
// 
typedef struct __FLASH_GET_BLOCK_STATUS_REQUEST
{
    BLOCK_RUN BlockRun;
    BOOL IsInitialFlash;    
    
} FLASH_GET_BLOCK_STATUS_REQUEST;

// FLASH_SET_BLOCK_STATUS_REQUEST
//
// Input structure for IOCTL_FLASH_PDD_SET_BLOCK_STATUS.
// 
typedef struct __FLASH_SET_BLOCK_STATUS_REQUEST
{
    BLOCK_RUN BlockRun;
    ULONG BlockStatus;    
    
} FLASH_SET_BLOCK_STATUS_REQUEST;

// FLASH_READ_STATUS
//
// Status flags regarding the result of IOCTL_FLASH_READ_PHYSICAL_SECTORS
//
enum FLASH_READ_STATUS
{
    // This indicates that there was an ECC failure when reading,
    // but that it was able to be corrected.
    FLASH_READ_STATUS_ECC_CORRECTION_REQUIRED      = 0x1
};


// FLASH_PERFORMANCE_INFO
// 
// Output structure for the IOCTL_FLASH_PDD_GET_INFO function, when
// info-level is set to FlashPerformanceInfo.
// 
typedef struct __FLASH_PERFORMANCE_INFO 
{    
    DWORD ReadKilobytesPerSecond;
    DWORD WriteKilobytesPerSecond;
    
    DWORD BlockEraseMicroseconds;
    DWORD ReadSetupMicroseconds;
    DWORD WriteSetupMicroseconds;
    
} FLASH_PERFORMANCE_INFO;

// FLASH_LIFE_CYCLE_INFO
//
// Output structure for the IOCTL_FLASH_PDD_GET_INFO function, when
// info-level is set to FlashLifeCycleInfo.
//
typedef struct __FLASH_LIFE_CYCLE_INFO 
{
    // Approximate number of erase operations allowed per block over the
    // lifetime of the flash part.
    DWORD ErasePerBlock;    
                                
} FLASH_LIFE_CYCLE_INFO;


// FLASH_IDENTITY_INFO
//
// Output structure for the IOCTL_FLASH_PDD_GET_INFO function, when
// info-level is set to FlashIdentityInfo.
//

#define MAX_FLASH_MANUFACTURER_ID_CHARS 128
#define MAX_FLASH_SERIAL_NUMBER_CHARS 128

typedef struct __FLASH_IDENTITY_INFO 
{
    // A NULL-terminated ASCII string describing the manufacter id. 
    CHAR ManufacturerId[MAX_FLASH_MANUFACTURER_ID_CHARS];

    // A NULL-terminated ASCII string containing a unique serial number 
    // for the storage device. 
    CHAR  SerialNumber[MAX_FLASH_SERIAL_NUMBER_CHARS];

} FLASH_IDENTITY_INFO;

// FLASH_PDD_TRANSFER
// 
// Structure describing a run of sectors and containing data and/or spare 
// area buffers to be read or written. Input structure for the 
// IOCTL_FLASH_PDD_READ_PHYSICAL_SECTORS and 
// IOCTL_FLASH_PDD_WRITE_PHYSICAL_SECTORS IOCTLs.
// 
typedef struct __FLASH_PDD_TRANSFER 
{
    DWORD RegionIndex;
    SECTOR_RUN SectorRun;
    BYTE* pData;
    BYTE* pSpare;
    
} FLASH_PDD_TRANSFER;


// FLASH_PDD_COPY
// 
// Structure decribing source and destination of sector to be copied and 
// possibly containing new spare area for the destination sector. Input 
// structure for the IOCTL_FLASH_PDD_COPY_PHYSICAL_SECTORS function.
//
typedef struct __FLASH_PDD_COPY 
{    
    // Flash region to copy within
    DWORD RegionIndex;

    // Source sector where copy data is to be read from.
    SECTOR_RUN SourceSectorRun;   

    // Destination sector where copy data is to be written to.
    SECTOR_RUN DestinationSectorRun;     

} FLASH_PDD_COPY;


// ---------------------------------------------------------------------------
//
// FlashPddInterface includes all of the functions that a flash PDD implements
//
// ---------------------------------------------------------------------------

class FlashPddInterface
{
public:
    
    // Query the number of flash hardware regions.
    virtual LRESULT GetRegionCount (
        OUT DWORD* pRegionCount) = 0;

    // Query information about each flash hardware region.
    virtual LRESULT GetRegionInfoTable (
        IN DWORD RegionCount,
        OUT FLASH_REGION_INFO RegionInfoList[]) = 0;

    // Query the status of a particular block.
    virtual LRESULT GetBlockStatus (
        IN BLOCK_RUN BlockRun, 
        IN BOOL IsInitialFlash,
        OUT ULONG BlockStatus[]) = 0;

    // Set the status of a particular block to a combination of bad, read-only, reserved, etc.
    virtual LRESULT SetBlockStatus (
        IN BLOCK_RUN BlockRun, 
        IN ULONG BlockStatus) = 0;

    // Read data and/or spare area from multiple, possibly discontiguous sectors.
    virtual LRESULT ReadPhysicalSectors (
        IN ULONG TransferCount, 
        IN OUT FLASH_PDD_TRANSFER ReadList[],
        OUT ULONG* pReadStatus) = 0;

    // Write data and/or spare area to multiple, possibly discontiguous sectors.
    virtual LRESULT WritePhysicalSectors (
        IN ULONG TransferCount, 
        IN FLASH_PDD_TRANSFER WriteList[],
        OUT ULONG* pWriteStatus) = 0;

    // Erase multiple, possibly discontiguous blocks.
    virtual LRESULT EraseBlocks (
        IN ULONG RunCount, 
        IN BLOCK_RUN BlockRunList[]) = 0;

    // Copy data from multiple source sectors to destination sectors, possibly changing the spare area for the 
    // destination sectors.
    virtual LRESULT CopyPhysicalSectors (
        IN ULONG TransferCount, 
        IN FLASH_PDD_COPY CopyList[]) = 0;

    // For every sector specified by the SectorRun, retrieve a corresponding physical 
    // sector address. Must be implemented if XIP is to be supported.
    virtual LRESULT GetPhysicalSectorAddress (
        IN DWORD RegionIndex,
        IN SECTOR_RUN SectorRun, 
        OUT VOID* pPhysicalAddressList[]) = 0;

    //?Hardware lock a range of physical blocks. Must be implemented if block locking is to be 
    // supported.  BlockRun specifies the run of blocks to lock.  All other blocks are assumed
    // to be unlocked.
    virtual LRESULT LockBlocks (
        IN DWORD BlockRunCount,
        IN BLOCK_RUN BlockRunList[]) = 0;

    // Get life cycle information for each of the flash regions.
    virtual LRESULT GetLifeCycleInfo (
        IN DWORD RegionCount,
        OUT FLASH_LIFE_CYCLE_INFO* pInfo) = 0;

    // Get identity information for the flash part.
    virtual LRESULT GetIdentityInfo (
        OUT FLASH_IDENTITY_INFO* pInfo) = 0;

    // IoControl function for handling additional, part-specific IOCTLs.
    virtual LRESULT IoControl (
        DWORD Ioctl, 
        BYTE* pInBuffer, 
        DWORD InBufferSize, 
        BYTE* pOutBuffer, 
        DWORD OutBufferSize, 
        DWORD* pBytesReturned) = 0;        
};


#endif // #define _FLASHPDD_H_ 

