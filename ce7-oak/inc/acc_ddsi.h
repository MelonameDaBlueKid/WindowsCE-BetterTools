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
//

#pragma once

#include <accapi.h>
#include <ceddk.h>

//------------------------------------------------------------------------------
//  General PDD information
//
const int MAX_PDD_INFO_STRING_LEN = 32;
typedef struct _PDD_INFO
{
    DWORD cbSize;                                   // Size of structure in bytes.
    DWORD dwPDDVersion;                             // Version of the PDD
    DWORD dwInterfaceVersion;                       // Interface version.  If new functions are added then this needs to be updated.
    WCHAR szChipset[MAX_PDD_INFO_STRING_LEN];       // Chipset identification
    WCHAR szManufacturer[MAX_PDD_INFO_STRING_LEN];  // Manufacturer of the part 
} PDD_INFO;

//------------------------------------------------------------------------------
//  The MDD passes a callback information to the PDD, which is driver specific, except the
//  size field which is mandatory.
//
typedef struct _MDD_CALLBACK_INFO
{
    DWORD cbSize;
    // Function pointer table for the MDD callback interface follows.
} MDD_CALLBACK_INFO;

//------------------------------------------------------------------------------
//  The PDD exposes its interface, which is driver specific, except the
//  size field which is mandatory.
//
typedef struct _PDD_INTERFACE
{
    DWORD cbSize;
    // Function pointer table for the PDD interface follows.
} PDD_INTERFACE;


//------------------------------------------------------------------------------
//  The PDD needs to expose a common minimal set of interfaces to allow:
//      - retrieval of basic information
//      - initialization
//      - deinitialization
//      - device specific extensibility
//
const char c_szfnPDDGetInfo[]      = "PDDGetInfo";
const char c_szfnPDDInit[]         = "PDDInit";
const char c_szfnPDDDeInit[]       = "PDDDeInit";
const char c_szfnPDDIoControl[]    = "PDDIoControl";

#define ACC_PDD_VERSION_1 1
#define ACC_PDD_CURRENT_VERSION ACC_PDD_VERSION_1

#define ACC_PDD_CAPABILITIES_HWORIENTATION_DETECT    0x01

typedef struct _ACC_RANGE_RESOLUTION
{
    float fpMinRange;
    float fpMaxRange;
    float fpResolution;
}ACC_RANGE_RESOLUTION;

typedef enum
{
    ACC_HW_MODE_UNKNOWN,
    ACC_HW_MODE_STREAMING,
    ACC_HW_MODE_HWORIENTATION_DETECT,
} ACC_HW_MODE;

// internal sensor power states
typedef enum
{
    PDD_POWER_STATE_L0 = 0, // maximum power state
    PDD_POWER_STATE_L1,
    PDD_POWER_STATE_L2,
    PDD_POWER_STATE_L3,
    PDD_POWER_STATE_L4,     // lowest power state
} PDD_POWER_STATE;
#define SENSOR_MILLIWATTS_UNKNOWN       ((DWORD) (-1))

///=============================================================================
/// PDD functions
///=============================================================================

#if defined(__cplusplus)
extern "C" {
#endif // defined (__cplusplus)

//==============================================================================
// Description: PDD should always implement this function. MDD calls it during
//              initialization to fill up the function table with rest of the
//              DDSI functions.
//
// Arguments:   [IN] pszActiveKey - current active accelerometer driver key.
//              [IN] pMddIfc - MDD interface info
//              [OUT] pPddIfc - PDD interface (the function table to be filled)
//              [IN] hKeyToWatch - HKEY of the key watched by the MDD (e.g.
//                       HKEY_CURRENT_USER). This is configurable in the
//                       accelerometer registry read by the MDD (REG_REGKEY_VALUE).
//              [IN] szSubKey - subkey of hKeyToWatch if applicable. This is 
//                       configurable in the accelerometer registry read by the MDD
//                      (REG_REGSUBKEY_VALUE).
//
// Ret Value:   The PDD context - pddInfo.
//
DWORD
PDDInit(
    DWORD dwPDDContext,
    __in_z WCHAR *szActiveRegistryKey,
    __inout PDD_INTERFACE * pPDDInterface,
    __in MDD_CALLBACK_INFO * pCallBackInfo
);

#if defined (__cplusplus)
}
#endif // defined(__cplusplus)

typedef BOOL  (WINAPI *PFN_PDD_GETINFO) (__out PDD_INFO * pPDDInfo);
typedef DWORD (WINAPI *PFN_PDD_INIT) (
    __in DWORD dwPDDContext,
    __in_z WCHAR *szActiveRegistryKey,
    __inout PDD_INTERFACE * pPDDInterface,
    __in MDD_CALLBACK_INFO * pCallBackInfo
    );
typedef BOOL (WINAPI *PFN_PDD_DEINIT) (__in DWORD dwPDDContext);
typedef BOOL (WINAPI *PFN_PDD_IOCONTROL) (
    __in DWORD dwPDDContext,  // Context information that was returned froM PDDInit
    __in DWORD dwCode,
    __inout PBYTE pBufIn,
    __in DWORD dwLenIn,
    __inout PBYTE pBufOut,
    __in DWORD dwLenOut,
    __inout PDWORD pdwActualOut
    );
typedef DWORD (WINAPI *PFN_ACC_PDD_CAPABILITIES_GET) (DWORD PDDContext, __in PDWORD pdwCaps);
typedef DWORD (WINAPI *PFN_ACC_PDD_POWER_ON) (DWORD PDDContext);
typedef DWORD (WINAPI *PFN_ACC_PDD_POWER_OFF)(DWORD PDDContext);
typedef void (WINAPI *PFN_ACC_MDD_PROCESSSAMPLE)(DWORD hDeviceContext, __in ACC_DATA* pData);
typedef DWORD (WINAPI *PFN_ACC_PDD_MODE_SET) (DWORD PDDContext, ACC_HW_MODE hwMode, DWORD dwIntervalMs);
typedef DWORD (WINAPI *PFN_ACC_PDD_RANGE_GET) (DWORD PDDContext, __out_opt ACC_RANGE_RESOLUTION *paRange, __in DWORD *pcRange);
typedef DWORD (WINAPI *PFN_ACC_PDD_RANGE_SET) (DWORD PDDContext, __in ACC_RANGE_RESOLUTION *pRange);
typedef DWORD  (WINAPI *PFN_ACC_PDD_POWEREVENTINGENABLE)(DWORD PDDContext, BOOL fEnable);
typedef void  (WINAPI *PFN_ACC_MDD_POWER_EVENT)(DWORD hDeviceContext, DWORD dwTimeStamp, PDD_POWER_STATE power, DWORD dwMilliWatts);


typedef struct _ACCELEROMETER_PDD_FUNCTIONS
{
    DWORD cbSize;              // sizeof(ACCELEROMETER_PDD_FUNCTIONS)

    PFN_PDD_GETINFO pfnPDDGetInfo;
    PFN_PDD_DEINIT pfnPDDDeInit;
    PFN_PDD_IOCONTROL pfnPDDIoControl;
    PFN_ACC_PDD_CAPABILITIES_GET pfnPddCapabilitiesGet;
    PFN_ACC_PDD_POWER_ON pfnPddPowerOn;
    PFN_ACC_PDD_POWER_OFF pfnPddPowerOff;
    PFN_ACC_PDD_MODE_SET pfnPddModeSet;
    PFN_ACC_PDD_RANGE_SET pfnPddRangeSet;
    PFN_ACC_PDD_RANGE_GET pfnPddRangeGet;
    PFN_ACC_PDD_POWEREVENTINGENABLE pfnPddPowerEventingEnable;
        
}  ACCELEROMETER_PDD_FUNCTIONS;

typedef struct _ACCELEROMETER_CALLBACK_INFO
{
    DWORD cbSize;              // sizeof(ACCELEROMETER_CALLBACK_INFO)
    PFN_ACC_MDD_PROCESSSAMPLE pfnAccMddProcessSample;
    PFN_ACC_MDD_POWER_EVENT pfnAccMddPowerEvent;
}  ACCELEROMETER_CALLBACK_INFO;

