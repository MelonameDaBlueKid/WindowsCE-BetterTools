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

#include <winioctl.h>
#include "FlashCommon.h"

// New IOControlCode values

#define IOCTL_FLASH_BASE 0
#define IOCTL_FLASH_OPTIONAL_BASE 0x20

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



// ---------------------------------------------------------------------------
//
// Structure definitions for Flash MDD
//
// ---------------------------------------------------------------------------


// FLASH_SECTOR_TRANSFER 
//
// Sub-structure of FLASH_TRANSFER_REQUEST. Describes a sector range to
// transfer, and contains I/O buffers for the transfer.
//
typedef struct __FLASH_SECTOR_TRANSFER
{    
    // Logical sector range to transfer.
    SECTOR_RUN SectorRun;

    // Virtual address of the I/O buffer for the transfer. Must be DWORD 
    // aligned, and must be at least (SectorCount * sector size).
    BYTE* pBuffer;

    // Physical address of the I/O buffer.  This field is optional.
    void* pPhysicalAddress;
    
} FLASH_SECTOR_TRANSFER;

// FLASH_TRANSFER_REQUEST
//
// Input structure for IOCTL_FLASH_READ_LOGICAL_SECTORS and 
// IOCTL_FLASH_WRITE_LOGICAL_SECTORS. Describes a set of discontiguous sector 
// data/sector run pairs to be read from or written to disk in a single 
// operation.
// 
typedef struct __FLASH_TRANSFER_REQUEST
{
    // Identifer of the flash partition to transfer
    PARTITION_ID PartitionId;

    // Flags describing attributes for the transfer operation.  
    // See FLASH_TRANSFER_REQUEST_FLAGS.
    DWORD   RequestFlags;
    
    // Number of FLASH_SECTOR_TRANSFER items in TransferList.
    DWORD   TransferCount;

    // A unique identifier for the "object" this transfer is associated with.
    // Can be ignored or used as an organizational "hint" to the storage device.
    ULONGLONG AssociationId;

    // List of FLASH_SECTOR_TRANSFER range/data structures. There must be 
    // BufferCount items in the list.
    FLASH_SECTOR_TRANSFER TransferList[1];
    
} FLASH_TRANSFER_REQUEST;

// Valid flags for the FLASH_TRANSFER_REQUEST RequestFlags field:
//
enum FLASH_TRANSFER_REQUEST_FLAGS
{
    // Entire request must be atomic.
    FLASH_SECTOR_REQUEST_FLAG_ATOMIC =        0x00000001,

    // Write must be committed synchronously prior to returning.
    FLASH_SECTOR_REQUEST_FLAG_WRITE_THROUGH = 0x00000002, 
};

// FLASH_SECTOR_DELETE 
//
// Input structure for IOCTL_FLASH_DELETE_LOGICAL_SECTORS. Describes a set of
// discontiguous sector ranges to be deleted in a single operation.
//
typedef struct __FLASH_SECTOR_DELETE
{
    // Identifier of the flash partition to delete
    PARTITION_ID PartitionId;
    
    // Number of SECTOR_RUN items in DeleteSectorList.
    DWORD SectorRunCount;

    // List of SECTOR_RUN structures. There must be SectorRunCount
    // items in the list.
    SECTOR_RUN SectorRunList[1];
    
} FLASH_SECTOR_DELETE;

// FLASH_GET_SECTOR_ADDRESS 
//
// Input structure for IOCTL_FLASH_GET_SECTOR_ADDRESS. 
//
typedef struct __FLASH_GET_SECTOR_ADDRESS
{
    // Identifier of the flash partition to query
    PARTITION_ID PartitionId;

    // Number of sectors in the logical sector list
    DWORD SectorCount;

    // Array of logical sectors.  There must be SectorCount items in the list.
    DWORD LogicalSectorList[1];
    
} FLASH_GET_SECTOR_ADDRESS;

static const DWORD FLASH_PARTITION_NAME_LENGTH = PARTITIONNAMESIZE;
static const DWORD DEFAULT_EXTRA_BLOCK_COUNT = 2;

// For LogicalBlockCount, indicating flash region extends to end of flash
static const DWORD END_OF_FLASH = -1;

// FLASH_PARTITION_CREATE_INFO 
//
// Input structure for IOCTL_FLASH_CREATE_PARTITION.
//
typedef struct __FLASH_PARTITION_CREATE_INFO 
{
    // Region index to create new partition in
    ULONG RegionIndex;
    
    // Unique name of the partition.
    WCHAR PartitionName[FLASH_PARTITION_NAME_LENGTH];  
   
    // Number of logical blocks in this partition.
    ULONGLONG LogicalBlockCount;    
    
    // Bitmask describing properties of this region, see FLASH_PARTITION_FLAGS.
    ULONG PartitionFlags;

    // Creation time of partition
    FILETIME CreationTime;

    // The partition type used to determine which file system to mount.
    ULONG PartitionType;

    // Guid used to identify the partition.  Currently not used.
    GUID PartitionGuid;
} FLASH_PARTITION_CREATE_INFO;


// FLASH_PARTITION_INFO 
//
// Output structure for IOCTL_FLASH_GET_PARTITION_TABLE.
//
typedef struct __FLASH_PARTITION_INFO 
{
    // Partition identifier.
    PARTITION_ID PartitionId;
    
    // Unique name of the partition.
    WCHAR PartitionName[FLASH_PARTITION_NAME_LENGTH];  

    // Starting physical block of this partition
    ULONGLONG StartPhysicalBlock;

    // Number of physical blocks in this partition.
    ULONGLONG PhysicalBlockCount;
    
    // Number of logical blocks in this partition.
    ULONGLONG LogicalBlockCount;          

    // Bitmask describing properties of this partition.
    // See FLASH_PARTITION_FLAGS.
    ULONG PartitionFlags;

    // Creation time of partition
    FILETIME CreationTime;

    // The partition type used to determine which file system to mount.
    ULONG PartitionType;

    // Guid used to identify the partition.  Currently not used.
    GUID PartitionGuid;
} FLASH_PARTITION_INFO;

enum FLASH_PARTITION_FLAGS
{
    // Flag indicating that this partition should be accessed with a direct 
    // logical->physical mapping.  This partition will not be wear-leveled and 
    // operations are not transaction safe.
    FLASH_PARTITION_FLAG_DIRECT_MAP =           0x00000001,

    // Flag indicating that this partition should be treated as read-only and 
    // only be written when in update mode.
    FLASH_PARTITION_FLAG_READ_ONLY =            0x00000002,

    // Flag indicating that this partition is reserved, meaning it is not 
    // wear-leveled.
    FLASH_PARTITION_FLAG_RESERVED =             0x00000004,
};

// FLASH_CONFIGURATION_SETTINGS
//
// Input structure for IOCTL_FLASH_SET_CONFIGURATION_SETTINGS.
//
typedef struct __FLASH_CONFIGURATION_SETTINGS
{
    // Partition to apply configuration setting to.
    PARTITION_ID PartitionId;

    // Flags specifying which fields in this structure to set.
    // See FLASH_CONFIGURATION_FLAGS.
    DWORD Flags;

    // TRUE if idle compaction is disabled.
    BOOL IsIdleCompactionDisabled;  

    // Percentage of dirty to free sectors when idle compaction start.
    DWORD IdleCompactionPercent;    

    // Percentage of dirty sectors to total sectors when idle compaction finishes.
    DWORD IdleCompletionPercent;  

    // Percent of log blocks to total blocks when idle compaction of log occurs.
    DWORD IdleLogSizePercent;     

    // Percentage of free blocks to total blocks when critical compaction occurs.
    DWORD CriticalCompactPercent; 

    // Percent of log blocks to total blocks when critical compaction of log occurs.
    DWORD CriticalLogSizePercent;   

    // TRUE checkpointing of flash state is disabled on shutdown.
    BOOL IsCheckpointOnShutdownDisabled;
    
    // Reserved for future use.
    DWORD Reserved1;
    DWORD Reserved2;
    DWORD Reserved3;
    DWORD Reserved4;

} FLASH_CONFIGURATION_SETTINGS;

enum FLASH_CONFIGURATION_FLAGS
{
    FLASH_CONFIGURATION_IS_IDLE_COMPACTION_DISABLED =           0x00000001,
    FLASH_CONFIGURATION_IDLE_COMPACTION_PERCENT =               0x00000002,
    FLASH_CONFIGURATION_IDLE_COMPLETION_PERCENT =               0x00000004,
    FLASH_CONFIGURATION_IDLE_LOG_SIZE_PERCENT =                 0x00000008,
    FLASH_CONFIGURATION_CRITICAL_COMPACT_PERCENT =              0x00000010,
    FLASH_CONFIGURATION_CRITICAL_LOG_SIZE_PERCENT =             0x00000020,
    FLASH_CONFIGURATION_IS_CHECKPOINT_ON_SHUTDOWN_DISABLED =    0x00000040
};

// ---------------------------------------------------------------------------
//
// Structure definitions for Bad Block Table
//
// ---------------------------------------------------------------------------

static const DWORD BAD_BLOCK_TABLE_SIGNITURE = 0x54444142;

// BAD_BLOCK_TABLE_HEADER
//
// The bad block table consists of this header, followed by a list of bad blocks,
// where each bad block takes up a DWORD and the total size of the list is equal
// to BadBlockCount.
//
typedef struct _BAD_BLOCK_TABLE_HEADER
{
    DWORD       Signiture;
    DWORD       BadBlockCount;
    
} BAD_BLOCK_TABLE_HEADER;


// ---------------------------------------------------------------------------
//
// Interface definition for Flash MDD.  Provides same functionality as
// IOCTLs defined above.
//
// ---------------------------------------------------------------------------

class FlashMddInterface
{
public:
    // Pass-through to the Flash PDD GetRegionCount.
    virtual LRESULT GetRegionCount (
        OUT DWORD* pRegionCount) = 0;

    // Pass-through to the Flash PDD GetRegionInfoTable.
    virtual LRESULT GetRegionInfoTable (
        IN DWORD RegionCount,
        OUT FLASH_REGION_INFO RegionInfoList[]) = 0;

    // Reads a range of logical sectors.
    virtual LRESULT ReadLogicalSectors(
        IN FLASH_TRANSFER_REQUEST* pRequest) = 0;

    // Writes to a range of logical sectors.        
    virtual LRESULT WriteLogicalSectors(
        IN FLASH_TRANSFER_REQUEST* pRequest) = 0;

    // Specifies that a range of logical sectors are no longer in use.
    virtual LRESULT DeleteLogicalSectors(
        IN FLASH_SECTOR_DELETE* pDeleteRequest) = 0;

    // Get a list of physical sector address from a corresponding list of logical
    // sector addresses.
    virtual LRESULT GetPhysicalSectorAddress (
        IN FLASH_GET_SECTOR_ADDRESS* pRequest, 
        OUT VOID* pPhysicalAddressList[]) = 0;

    // Lock one or more partitions, such that blocks cannot be unlocked without
    // a power reset.  All other partitions on store will be unlocked.
    virtual LRESULT LockPartitions(
        PARTITION_ID PartitionList[],
        DWORD PartitionCount) = 0;

    // Gets the configuration settings for a partition.
    virtual LRESULT GetConfigurationSettings(
        PARTITION_ID PartitionId,
        FLASH_CONFIGURATION_SETTINGS* pSettings) = 0;

    // Sets the configuration settings for a partition.
    virtual LRESULT SetConfigurationSettings(
        FLASH_CONFIGURATION_SETTINGS* pSettings) = 0;

public:    
    // Erase all the blocks in the flash region and reinitialize partition table.
    virtual LRESULT FormatStore(    
        IN DWORD RegionIndex,
        IN BOOL FormatAllRegions) = 0;

    // Erase all the blocks in a single partition.
    virtual LRESULT FormatPartition(
        IN PARTITION_ID PartitionId) = 0; 

    // Secure wipe a single partition.
    virtual LRESULT SecureWipe(
        IN PARTITION_ID PartitionId) = 0;

    // Set the secure wipe flag in a single partition.
    virtual LRESULT SetSecureWipeFlag(
        IN PARTITION_ID PartitionId) = 0;

    // Get the total number of partitions on the flash media
    // across all regions.
    virtual LRESULT GetPartitionCount (
        OUT LPDWORD pPartitionCount) = 0;

    // Get the entire partition table across all flash regions.  
    // This returns an array of FLASH_PARTITION_INFO structures with 
    // the number of elements equal to the number of partitions on flash.
    virtual LRESULT GetPartitionTable(
        IN DWORD PartitionCount,
        OUT FLASH_PARTITION_INFO PartitionTable[]) = 0;

    // Get the number of free blocks in a particular region
    // that can be used for creating new partitions.  The block
    // count accounts for bad blocks.
    virtual LRESULT GetRegionFreeSpace(
        IN DWORD RegionIndex,
        OUT LPDWORD pFreeBlockCount) = 0;

    // Create a new partition.  The partition is located at the end of the 
    // existing partitions.
    virtual LRESULT CreatePartition(
        IN FLASH_PARTITION_CREATE_INFO* pCreateInfo,
        OUT FLASH_PARTITION_INFO* pActualInfo) = 0;

public:
    virtual LRESULT IoControl(
        DWORD IoControlCode,
        PBYTE pInBuf,
        DWORD InBufSize,
        PBYTE pOutBuf,
        DWORD OutBufSize,
        PDWORD pBytesReturned) = 0;
    
    
};

#endif // #define _FLASHMDD_H_ 

