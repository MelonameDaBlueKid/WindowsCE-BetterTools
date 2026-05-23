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
#ifndef _FLASHPDDCOMMON_H_
#define _FLASHPDDCOMMON_H_

#if __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
//
// FLASH_REGION_INFO
//
// Output structure for the GetRegionInfo/IOCTL_FLASH_PDD_GET_REGION_INFO
// function. Describes standard information for a particular flash region.
// 
typedef struct FLASH_REGION_INFO 
{
    // Features supported for this flash part. See FLASH_REGION_INFO_FLAGS.
    ULONG FlashFlags;
    
    // Starting physical block for flash hardware region.
    ULONGLONG StartBlock;

    // Total number of physical blocks in the flash region.
    ULONGLONG BlockCount;
   
    // Number of sectors in a block.                            
    ULONG SectorsPerBlock;      

    // Number of data bytes in a sector.
    ULONG DataBytesPerSector;   
    
    // Number of spare bytes in a sector available for use by MDD.
    ULONG SpareBytesPerSector;  

    // Number of program operations allowed per page (can be 1).
    ULONG PageProgramLimit;     

    // Percentage of blocks that are expected to go bad during lifetime of
    // part.  Expressed as 1/100th of one percent units.  For example,
    // if 1% expected to go bad, this value would be 100.
    ULONG BadBlockHundredthPercent;
} FLASH_REGION_INFO;

static const DWORD MIN_FLASH_SPARE_BYTES = 6;

// FLASH_REGION_INFO_FLAGS
//
// Flag enumeration for FLASH_REGION_INFO_FLAGS.FlashFlags
//
enum FLASH_REGION_INFO_FLAGS
{
    // The flash part is NAND
    FLASH_FLAG_NAND =                       0x00000001,

    // The flash part is NOR
    FLASH_FLAG_NOR =                        0x00000002,
    
    // Flag indicating that this region requires sequential page programming 
    // and does not allow out-of-order sector writes within a block 
    // (e.g. MLC flash).
    FLASH_FLAG_REQUIRE_SEQ_PAGE_PROGRAM =   0x00000004,

    // The flash PDD implements IOCTL_FLASH_PDD_COPY_PHYSICAL_SECTORS
    FLASH_FLAG_SUPPORTS_COPY =              0x00000008,        

    // The flash part supports XIP. The PDD must implement 
    // IOCTL_FLASH_PDD_GET_PHYSICAL_SECTOR_ADDRESS.
    FLASH_FLAG_SUPPORTS_XIP =               0x00000010,

    // The flash part supports block-level locking/unlocking. The PDD must
    // implement IOCTL_FLASH_PDD_LOCK_BLOCKS.
    FLASH_FLAG_SUPPORTS_LOCKING =           0x00000020,

};

//------------------------------------------------------------------------------
//
// BLOCK_RUN
//
// Describes a single run of blocks
//
typedef struct BLOCK_RUN
{
    ULONG       RegionIndex;
    ULONGLONG   StartBlock;
    ULONG       BlockCount;
    
} BLOCK_RUN;

//------------------------------------------------------------------------------
//
// FLASH_BLOCK_STATUS
//
// Possible block status values for GetBlockStatus and SetBlockStatus.
//
typedef enum FLASH_BLOCK_STATUS
{
    FLASH_BLOCK_STATUS_BAD      = 0x1,
    FLASH_BLOCK_STATUS_RESERVED = 0x2
    
} FLASH_BLOCK_STATUS;

//------------------------------------------------------------------------------
//
// SECTOR_RUN
//
// Describes a single run of sectors
//
typedef struct __SECTOR_RUN {

    ULONGLONG StartSector;
    ULONG SectorCount;
    
} SECTOR_RUN;

//------------------------------------------------------------------------------
//
// FLASH_PDD_TRANSFER
//
// Structure describing a run of sectors and containing data and/or spare
// area buffers to be read or written. Input structure for the
// ReadPhysicalSectors/IOCTL_FLASH_PDD_READ_PHYSICAL_SECTORS and
// WritePhysicalSectores/IOCTL_FLASH_PDD_WRITE_PHYSICAL_SECTORS IOCTLs.
//
typedef struct FLASH_PDD_TRANSFER
{
    DWORD RegionIndex;
    SECTOR_RUN SectorRun;
    BYTE* pData;
    BYTE* pSpare;
} FLASH_PDD_TRANSFER;


//------------------------------------------------------------------------------
//
// FLASH_READ_STATUS
//
// Status flags regarding the result of ReadPhysicalSectors/
// IOCTL_FLASH_READ_PHYSICAL_SECTORS
//
typedef enum FLASH_READ_STATUS
{
    // This indicates that there was an ECC failure when reading,
    // but that it was able to be corrected.
    FLASH_READ_STATUS_ECC_CORRECTION_REQUIRED      = 0x1
    
} FLASH_READ_STATUS;

//------------------------------------------------------------------------------
//
// FLASH_PDD_COPY
//
// Structure decribing source and destination of sector to be copied and
// possibly containing new spare area for the destination sector. Input
// structure for the IOCTL_FLASH_PDD_COPY_PHYSICAL_SECTORS function.
//
typedef struct FLASH_PDD_COPY
{
    // Flash region to copy within
    DWORD RegionIndex;

    // Source sector where copy data is to be read from.
    SECTOR_RUN SourceSectorRun;

    // Destination sector where copy data is to be written to.
    SECTOR_RUN DestinationSectorRun;
} FLASH_PDD_COPY;

//------------------------------------------------------------------------------
//
// FLASH_LIFE_CYCLE_INFO
//
// Output structure for the IOCTL_FLASH_PDD_GET_INFO function, when
// info-level is set to FlashLifeCycleInfo.
//
typedef struct FLASH_LIFE_CYCLE_INFO
{
    // Approximate number of erase operations allowed per block over the
    // lifetime of the flash part.
    DWORD ErasePerBlock;
} FLASH_LIFE_CYCLE_INFO;

//------------------------------------------------------------------------------
//
// FLASH_IDENTITY_INFO
//
// Output structure for the IOCTL_FLASH_PDD_GET_INFO function, when
// info-level is set to FlashIdentityInfo.
//

#define MAX_FLASH_MANUFACTURER_ID_CHARS     128
#define MAX_FLASH_SERIAL_NUMBER_CHARS       128

typedef struct FLASH_IDENTITY_INFO
{
    // A NULL-terminated ASCII string describing the manufacter id.
    CHAR ManufacturerId[MAX_FLASH_MANUFACTURER_ID_CHARS];

    // A NULL-terminated ASCII string containing a unique serial number
    // for the storage device.
    CHAR  SerialNumber[MAX_FLASH_SERIAL_NUMBER_CHARS];

} FLASH_IDENTITY_INFO;

//------------------------------------------------------------------------------

#if __cplusplus
};
#endif

#endif // _FLASHPDDCOMMON_H_
