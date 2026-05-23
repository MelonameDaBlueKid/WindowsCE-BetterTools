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
#ifndef _FLASHCOMMON_H_
#define _FLASHCOMMON_H_ 

// SECTOR_RUN
//
// Describes a single run of sectors
//
typedef struct __SECTOR_RUN {

    ULONGLONG StartSector;
    DWORD SectorCount;
    
} SECTOR_RUN;

// BLOCK_RUN
//
// Describes a single run of blocks
//
typedef struct __BLOCK_RUN
{
    ULONG       RegionIndex;
    ULONGLONG   StartBlock;
    ULONG       BlockCount;
    
} BLOCK_RUN;


// PARTITION_ID
//
// Unique identifier for a partition
//
typedef struct __PARTITION_ID {

    WORD RegionIndex;
    WORD PartitionIndex;
    
} PARTITION_ID;

// FLASH_REGION_INFO
//
// Output structure for the IOCTL_FLASH_PDD_GET_REGION_INFO function. Describes
// standard information for a particular flash region.
// 
typedef struct __FLASH_REGION_INFO 
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

#endif // _FLASHCOMMON_H_
