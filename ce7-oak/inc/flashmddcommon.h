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
#ifndef _FLASHMDDCOMMON_H_
#define _FLASHMDDCOMMON_H_ 

#include <storeMgr.h>
#include <FlashPddCommon.h>

#if __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
//
// PARTITION_ID
//
// Unique identifier for a partition
//
typedef struct PARTITION_ID
{
    WORD RegionIndex;
    WORD PartitionIndex;

} PARTITION_ID;


//------------------------------------------------------------------------------
//
// FLASH_SECTOR_TRANSFER 
//
// Sub-structure of FLASH_TRANSFER_REQUEST. Describes a sector range to
// transfer, and contains I/O buffers for the transfer.
//
typedef struct FLASH_SECTOR_TRANSFER
{    
    // Logical sector range to transfer.
    SECTOR_RUN SectorRun;

    // Virtual address of the I/O buffer for the transfer. Must be DWORD 
    // aligned, and must be at least (SectorCount * sector size).
    BYTE* pBuffer;

    // Physical address of the I/O buffer.  This field is optional.
    void* pPhysicalAddress;
   
} FLASH_SECTOR_TRANSFER;

//------------------------------------------------------------------------------
//
// FLASH_TRANSFER_REQUEST
//
// Input structure for IOCTL_FLASH_READ_LOGICAL_SECTORS and 
// IOCTL_FLASH_WRITE_LOGICAL_SECTORS. Describes a set of discontiguous sector 
// data/sector run pairs to be read from or written to disk in a single 
// operation.
// 
typedef struct FLASH_TRANSFER_REQUEST
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


//------------------------------------------------------------------------------
//
// FLASH_SECTOR_DELETE 
//
// Input structure for IOCTL_FLASH_DELETE_LOGICAL_SECTORS. Describes a set of
// discontiguous sector ranges to be deleted in a single operation.
//
typedef struct FLASH_SECTOR_DELETE
{
    // Identifier of the flash partition to delete
    PARTITION_ID PartitionId;
    
    // Number of SECTOR_RUN items in DeleteSectorList.
    DWORD SectorRunCount;

    // List of SECTOR_RUN structures. There must be SectorRunCount
    // items in the list.
    SECTOR_RUN SectorRunList[1];
    
} FLASH_SECTOR_DELETE;


//------------------------------------------------------------------------------
//
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


//------------------------------------------------------------------------------
//
// FLASH_PARTITION_CREATE_INFO 
//
// Input structure for IOCTL_FLASH_CREATE_PARTITION.
//

static const DWORD FLASH_PARTITION_NAME_LENGTH = PARTITIONNAMESIZE;

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

typedef struct __FLASH_PARTITION_DELETE_INFO 
{
    // The starting partition to delete
    PARTITION_ID StartPartitionId;

    // The number of consecutive partitions to delete following the starting 
    // partition within the same region.
    ULONG PartitionCount;

} FLASH_PARTITION_DELETE_INFO;

static const DWORD DEFAULT_EXTRA_BLOCK_COUNT = 2;

// For LogicalBlockCount, indicating flash region extends to end of flash
static const DWORD END_OF_FLASH = (DWORD)-1;


//------------------------------------------------------------------------------
//
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


//------------------------------------------------------------------------------
//
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

    // Percentage of dirty to free sectors when idle compaction finishes.
    DWORD IdleCompletionPercent;  

    // Percent of log blocks to total blocks when idle compaction of log occurs.
    DWORD IdleLogSizePercent;     

    // Percentage of free blocks to total blocks when critical compaction occurs.
    DWORD CriticalCompactPercent; 

    // Percent of log blocks to total blocks when critical compaction of log occurs.
    DWORD CriticalLogSizePercent;   

    // TRUE checkpointing of flash state is disabled on shutdown.
    BOOL IsCheckpointOnShutdownDisabled;

    // The threshold for when to perform a checkpoint.  Specified by the number 
    // of blocks written since the last checkpoint.
    DWORD IdleWriteCheckpointThreshold;
    
    // Reserved for future use.
    DWORD Reserved1;
    DWORD Reserved2;
    DWORD Reserved3;

} FLASH_CONFIGURATION_SETTINGS;

enum FLASH_CONFIGURATION_FLAGS
{
    FLASH_CONFIGURATION_IS_IDLE_COMPACTION_DISABLED =           0x00000001,
    FLASH_CONFIGURATION_IDLE_COMPACTION_PERCENT =               0x00000002,
    FLASH_CONFIGURATION_IDLE_COMPLETION_PERCENT =               0x00000004,
    FLASH_CONFIGURATION_IDLE_LOG_SIZE_PERCENT =                 0x00000008,
    FLASH_CONFIGURATION_CRITICAL_COMPACT_PERCENT =              0x00000010,
    FLASH_CONFIGURATION_CRITICAL_LOG_SIZE_PERCENT =             0x00000020,
    FLASH_CONFIGURATION_IS_CHECKPOINT_ON_SHUTDOWN_DISABLED =    0x00000040,
    FLASH_CONFIGURATION_IDLE_WRITE_CHECKPOINT_THRESHOLD =       0x00000080    
};

//------------------------------------------------------------------------------

#if __cplusplus
}
#endif

#endif // #define _FLASHMDDCOMMON_H_ 
