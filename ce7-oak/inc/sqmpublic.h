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
#pragma once

// default upload server
#define DEFAULT_UPLOAD_SERVER                          L"sqm.microsoft.com"
#define DEFAULT_UPLOAD_SZREQS                          "/sqm/wince/sqmserver.dll"
#define DEFAULT_UPLOAD_VERB                            "POST"

// SQM Registry settings for Report Upload
#define SQM_REGKEY_UPLOAD_SETTINGS                     L"System\\SQM\\UploadSettings"
#define SQM_REGVALUE_UPLOAD_FOLDER_NAME                L"UploadFolder"
#define SQM_REGVALUE_UPLOAD_NOTIFY_EVENT_NAME          L"UploadEvent"
#define SQM_REGVALUE_UPLOAD_RETRY_INTERVAL             L"UploadRetryInterval"
#define SQM_REGVALUE_UPLOAD_THROTTLE_INTERVAL          L"ThrottleInterval"
#define SQM_REGVALUE_CUSTOM_CONNECTION_LIBRARY         L"ConnectionDll"

// SQM registry settings (main used by control panel applet to enable/disable sqm)
#define SQM_REGKEY_SETTINGS                            L"System\\SQM"
#define SQM_REGVALUE_CONTROL_STATUS                    L"Enabled" // could be 1 for enabled or 0 for disabled

#define SQM_MAX_STRING_LENGTH	64   // Max size of string datapoint or stream entry value
#define SQM_UNIQUE_ID_LENGTH		33   // 32 for ID + 1 for NULL

static const WCHAR c_szConnectionFlags[] = L"ConnectionFlags";
static const DWORD c_dwFreeConnectionsOnly = 0;

// Device specific datapoints
typedef struct _SqmDeviceInfo 
{
    BOOL  fInitialized;
    DWORD dwOSMajorVersion;
    DWORD dwOSMinorVersion;
    DWORD dwOSBuildNumber;
    DWORD dwPlatformBuildNumber;
    DWORD dwSku;
    DWORD dwDefaultLCID;
    DWORD dwDefaultLangID;
    DWORD dwRadioInfo;    
    DWORD dwMOCodes;
    WCHAR *wszOEMInfo;
    WCHAR *wszPlatformManufacturer;
    WCHAR *wszPlatformName;
    WCHAR wszUniqueID[SQM_UNIQUE_ID_LENGTH];
} SqmDeviceInfo;

// This structure is a raw SQM data file header.
typedef struct SQM_HEADER
{
    DWORD       dwSignature;                    // File signature = 'MSQM'
    DWORD       cbHeader;                       // sizeof(SQMHEADER)
    DWORD       dwFlags;                        // Flags (e.g. Testing)
    DWORD       dwChecksum;                     // Checksum
    DWORD       cSections;                      // Number of sections following the header
    DWORD       cbData;                         // Total number of bytes in file (not including header)
    DWORD       dwAppId;                        // Application Id
    DWORD       dwAppVersionHigh;               // Application Version (high DWORD)
    DWORD       dwAppVersionLow;                // Application Version (low DWORD)
    DWORD       dwIP;                           // IP address of client uploading the file (filled in by server)
    FILETIME    ftClientUploadUTC;              // UTC time when client uploads this file
    FILETIME    ftServerUploadUTC;              // UTC time when the server receives this file (filled in by server)
    FILETIME    ftClientSessionStartUTC;        // UTC time when this session starts
    FILETIME    ftClientSessionEndUTC;          // UTC time when this session ends
    GUID        guidMachine;                    // Unique machine identifier
    GUID        guidUser;                       // Unique user identifier
    DWORD       dwStudyId;                      // Study ID
    DWORD       dwInternalFlags;                // Internal Flags
    DWORD       cbRawData;                      // Total number of bytes before compression (not including header)
    DWORD       dwRawChecksum;                  // Checksum of file before compression
} SQM_HEADER, *LPSQM_HEADER;
