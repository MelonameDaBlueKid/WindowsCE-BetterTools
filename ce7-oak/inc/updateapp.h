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

#ifndef _UPDATEAPP_H_
#define _UPDATEAPP_H_

#include <windows.h>

// in tools-only builds, including this results in a build-error.
// hence the conditional guard.
#ifndef UA_EXCLUDE_PACKAGEINFOAPI
#include <packageinfoapi.h>
#endif

// in tools-only builds, including this results in a build-error.
// hence the conditional guard.
#ifndef UA_EXCLUDE_STOREMGR
#include <storemgr.h>
#endif

// Registry paths and registry values
#define UA_ROOT_KEY                 HKEY_LOCAL_MACHINE
#define UA_REGKEY_PATH              TEXT("System\\ImageUpdate\\UpdateApp")
#define UV_REGKEY_PATH              TEXT("System\\ImageUpdate\\Updatevalidator")
#define UA_REGVALUE_INPUTFILENAME   TEXT("InputFileName")
#define UA_REGVALUE_OUTPUTFILENAME  TEXT("OutputFileName")
#define UA_REGVALUE_PERSISTTEMPNAME TEXT("PersistentTempName")
#define UA_REGVALUE_RAMTEMPDIR      TEXT("RAMTempDir")
#define UA_REGVALUE_PERSISTENTROOT  TEXT("PersistentRoot")
#define UA_REGVALUE_RETRYLIMIT      TEXT("RetryLimit")
#define UA_REGVALUE_DISPLAYDLL      TEXT("DisplayDLL")
#define UA_REGVALUE_LOGFILEPATH     TEXT("ValidatorLogPath")
#define UV_REGVALUE_LOGFILEPATH     TEXT("ErrorLogFileNamePath")
#define UA_REGVALUE_ERRORLOGFILEPATH     TEXT("UpdateAppErrorLogFileNamePath")
#define UA_REGVALUE_UALOGFILEPATH   TEXT("UpdateAppLogPath")
#define UA_REGVALUE_FSDMOUNTTIMEOUT TEXT("FSDMountTimeout")
#define UA_REGVALUE_INITSLEEP       TEXT("InitSleep")
#define UA_REGVALUE_EXTERNALDIR     TEXT("ExternalStoreDir")
#define UA_REGVALUE_SETTINGSDIR     TEXT("UpdateSettingsDir")
#define UA_REGVALUE_UUITIMEOUT      TEXT("UUITimeout")
#define UA_REGVALUE_ULDRBACKFILE    TEXT("UldrBackupFileFullPath")
#define UA_RESERVEREGION_DRIVERS    TEXT("Drivers\\ReserveRegions")

#define DEFAULT_RETRY_LIMIT         0xFFFFFFFF

// Uldr update mode
#define ULDR_UPDATE_MODE            0x00000002
#define UPDATE_MODE                 0x00000001

// File system paths
#define NK_IMAGE_ROOT                    TEXT("\\NK")
#define NK_IMAGE_PATH                    TEXT("\\NK\\VOL:")
#define ULDR_IMAGE_ROOT                  TEXT("\\ULDR")
#define ULDR_IMAGE_PATH                  TEXT("\\ULDR\\RAW")
#define NK_BACKUP_FILE                   TEXT("NKBackup")
#define RES_BACKUP_FILE                  TEXT("ResBackup")
#define TMP_OUTPUT_FILE                  TEXT("TmpOutputFile")
#define TMP2_OUTPUT_FILE                 TEXT("Tmp2OutputFile")
#define ROM_INFO_PATH                    TEXT("\\IMGFS\\.rom")
#define VM_INFO_PATH                     TEXT("\\IMGFS\\.vm")
#define CIF_PATH                         TEXT("\\IMGFS\\packages.cif")
#define SOF_PATH                         TEXT("\\IMGFS\\packages.sof")
#define IMGFS_ROOT                       TEXT("\\IMGFS")
#define VALIDATOR_TEMP_DIR               TEXT("UVTemp")
#define IMAGE_UPDATE_FOLDER_PATH         TEXT("\\Windows\\System\\ImageUpdate")

#define DSM_TYPEFLAG (TYPEFLAG_FILE | TYPEFLAG_S | TYPEFLAG_H)
#define DSM_ATTRIB   (FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN)

const DWORD cNumMountPoints = 2;
const PCTSTR szMountPoints[] = {NK_IMAGE_ROOT, IMGFS_ROOT};

//Flags for InputFileHdr
#define UA_INPFILEHDR_SRCDWNLDAPP  0x00000001 //Inputfile is created by uldr's download app
#define UA_INPFILEHDR_SYSRESTMODE  0x00000002 //Execute in System Restore Mode
#define UA_INPFILEHDR_DELRSTPOINT  0x00000004 //Discard and disable Restore Point
#define UA_INPFILEHDR_NOCLEARTFAT  0x00000008 //Do not perform Cold Boot - don't clear TFAT
#define UA_INPFILEHDR_DELIFNOTFIT  0x00000010 //Discard restore point when there is not enough space in IMGFS

//Payload Types
#define PT_IMAGEUPDATE              0x00000001
#define PT_FULLFLASHUPDATE          0x00000002

//Transport Types
#define TT_USB_MS                   0x00000001
#define TT_USB_MTP                  0x00000002
#define TT_FILENAME                 0x00000003

//Store Identification Types
#define IT_STORAGEID                0x00000001
#define IT_STOREINFO                0x00000002

// The IClass GUID for ULDRUI used by updateapp, OEMs need to use this IClass GUID in their registry files
// {69F8E46B-CC44-439c-A307-093BDEABCCA5}
static const GUID UUI_DRIVER_GUID = { 0x69F8E46B, 0xCC44, 0x439c, { 0xA3, 0x07, 0x09, 0x3B, 0xDE, 0xAB, 0xCC, 0xA5} };
#define UUI_DRIVER_GUID_STRING TEXT("{69F8E46B-CC44-439c-A307-093BDEABCCA5}")

#define DEFAULT_STORE_ID_SIZE 256

typedef struct _InputFileHdr
{
    DWORD cbSize;
    DWORD dwBitmapPathSize;
    DWORD dwPackageListSize;
    DWORD dwFlags;
} InputFileHdr, *PInputFileHdr;

typedef struct
{
    DWORD cbSize;
    DWORD dwPayloadType;

    union
    {
        struct
        {
            DWORD dwBitmapPathSize;
            DWORD dwPackageListSize;
            DWORD dwFlags;
        } ImageUpdate;

        struct
        {
            DWORD dwTransportType;
            DWORD dwDataSize;
        } FullFlash;
    };

} UpdateInputFileHdr;


// in tools-only builds, using PARTINFO defined in storemgr.h this results 
// in a build-error.hence the conditional guard.
#ifndef UA_EXCLUDE_STOREMGR

//
// This structure is used to initialize the FILENAME transport.  Because the
// path may change between the MainOS and the ULDR, we cannot simply pass
// a file's path to the transport.  This structure breaks the path down into
// pieces that can be used to identify the location of the file to use.
//
// 1. Store
//    The store is identified either through the use of a Storage ID or through
//    the STOREINFO structure.
//
//    When using the Storage ID, set dwStoreIDType to IT_STORAGEID.
//    When using the STOREINFO structure, set it to IT_STOREINFO.
//
//    To get the Storage ID, use IOCTL_DISK_GET_STORAGEID.
//    To use STOREINFO, use GetStoreInfo() and zero out the following fields:
//        ZeroMemory( pStoreInfo->szDeviceName, sizeof(TCHAR) * DEVICENAMESIZE );
//        ZeroMemory( pStoreInfo->szStoreName, sizeof(TCHAR) * STORENAMESIZE );
//        ZeroMemory( &pStoreInfo->snBiggestPartCreatable, sizeof(SECTORNUM) );
//        ZeroMemory( &pStoreInfo->ftLastModified, sizeof(FILETIME) );
//        ZeroMemory( &pStoreInfo->dwMountCount, sizeof(DWORD) );
//
// 2. Partition
//    Use GetPartitionInfo() and then zero out the following fields:
//        ZeroMemory( PartInfo.szPartitionName, sizeof(TCHAR) * PARTITIONNAMESIZE );
//        ZeroMemory( PartInfo.szVolumeName, sizeof(TCHAR) * VOLUMENAMESIZE );
//        ZeroMemory( &PartInfo.ftLastModified, sizeof(FILETIME) );
//
// 3. FilePath
//    This is the path of the file relative to the partition.  Do not include
//    the partition mount name.  For example:
//
//    \Storage Card\BackupPath\Backup.DAT
//
//    would actually become
//
//    \BackupPath\Backup.DAT
//
// Note: The path to the file must exist, even if the file itself is to be
//       created by the transport DLL.
//
// Note: There are two nice StoreMgr APIs that can be useful when populating
//       this structure:
//       1. CeGetCanonicalPathName: Make sure the path is standardized.
//       2. CeGetVolumeInfo: Get the store name and partition name from the path.
//
typedef struct
{
    DWORD dwPathSize;
    DWORD dwStoreIDType;
    DWORD dwStoreIDSize;
    PARTINFO PartInfo;
    BOOL fCreateFile;     // The file should be created by the transport.
    // BYTE Path[dwPathSize];
    // BYTE StoreID[dwStoreIDSize];
} FileNameTransportData;
#endif

typedef struct
{
    BYTE   Signature[12];  // "ImageFlash  "
    UINT16 MajorVersion;
    UINT16 MinorVersion;
    DWORD  ManifestLength;
} ImageHeader;

typedef struct _OutputFileHdr
{
    DWORD cbSize;
    HRESULT hrOverallResult;
    DWORD dwResultTableSize;
} OutputFileHdr, *POutputFileHdr;


typedef PkgUpdateResult PkgResult, *PPkgResult;


typedef struct _HistoryResult
{
    GUID guid;
    VersionInfo version;
    DWORD dwFlags;
} HistoryResult, *PHistoryResult;

typedef struct _HistoryResultHeader
{
    WORD year;
    WORD month;
    WORD day;
    WORD hour;
    WORD minute;
    WORD numPackages;
} HistoryResultHeader, *PHistoryResultHeader;

#endif //#define _UPDATEAPP_H_

