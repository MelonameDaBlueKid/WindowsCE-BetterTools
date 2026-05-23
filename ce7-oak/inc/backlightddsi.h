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

//=============================================================================
// File Description:
//
// Defines the interface between Backlight stream driver MDD and PDD
//
//=============================================================================

#ifndef __BKLDDSI_H_
#define __BKLDDSI_H_

#define REG_DISPLAY_VALUE TEXT("Display")
#define REG_MINBRIGHTNESS_VALUE TEXT("MinBrightness")
#define REG_MAXBRIGHTNESS_VALUE TEXT("MaxBrightness")
#define REG_REGKEY_VALUE TEXT("RegKey")
#define REG_REGSUBKEY_VALUE TEXT("RegSubKey")
#define REG_DXSUPPORT_VALUE TEXT("SupportedDx")

///=============================================================================
/// Function Pointers
///=============================================================================

//==============================================================================
// Description: MDD calls it during deinitialization. PDD should deinit hardware
//              and deallocate memory etc.
//
// Arguments:   [IN] PddContext. pddInfo returned in PddInit.
//
// Ret Value:   None
//
typedef VOID (WINAPI *PFN_BKL_PDD_DEINIT) (
    DWORD PddContext
    );

//==============================================================================
// Description: IOCTLs passed to PDD.
//
// Arguments:   [IN] PddContext.  pddInfo returned in PddInit.
//
// Ret Value:   TRUE if success else FALSE. SetLastError() if FALSE.
//
typedef BOOL (WINAPI *PFN_BKL_PDD_IOCONTROL) (
    DWORD PddContext,
    DWORD dwIoControlCode,
    LPBYTE lpInBuf,
    DWORD nInBufSize,
    LPBYTE lpOutBuf,
    DWORD nOutBufSize, 
    LPDWORD lpBytesReturned
    );

//==============================================================================
// Description: IOCTLs passed to PDD.
//
// Arguments:   [IN]  pddContext.  pddInfo returned in PddInit.
//              [IN]  powerState - current power state (D0...D4).
//              [IN]  fOnAC - whether the device on external power (TRUE if on
//                       external power else FALSE).
//              [IN]  dwBrightnessToSet - requested brightness to set.
//              [OUT] pdwActualBrightness - brightness of backlight upon return.
//
// Ret Value:   TRUE if success else FALSE.
//
typedef BOOL (WINAPI *PFN_BKL_UPDATE) (
    DWORD pddContext,
    CEDEVICE_POWER_STATE powerState,
    BOOL fOnAC,
    DWORD dwBrightnessToSet,
    DWORD* pdwActualBrightness
    );

///=============================================================================
/// structs
///=============================================================================
// BKL_MDD_INTERFACE_INFO - mdd info passed to PddInit
typedef struct {
    UINT32 version;
} BKL_MDD_INTERFACE_INFO;

// BKL_PDD_INTERFACE_INFO - PddInit must fill out this structure
typedef struct {
    UINT32 version;
    PFN_BKL_PDD_DEINIT pfnDeinit;
    PFN_BKL_PDD_IOCONTROL pfnIoctl;
    PFN_BKL_UPDATE pfnUpdate;
} BKL_PDD_INTERFACE_INFO;

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
// Arguments:   [IN] pszActiveKey - current active backlight driver key.
//              [IN] pMddIfc - MDD interface info
//              [OUT] pPddIfc - PDD interface (the function table to be filled)
//              [IN] hKeyToWatch - HKEY of the key watched by the MDD (e.g.
//                       HKEY_CURRENT_USER). This is configurable in the
//                       backlight registry read by the MDD (REG_REGKEY_VALUE).
//              [IN] szSubKey - subkey of hKeyToWatch if applicable (e.g.
//                       L"ControlPanel\\Backlight"). This is configurable in
//                       the backlight registry read by the MDD
//                      (REG_REGSUBKEY_VALUE).
//
// Ret Value:   The PDD context - pddInfo.
//
DWORD
WINAPI
PddInit(
    const LPCTSTR lpContext,
    const BKL_MDD_INTERFACE_INFO* mddIfc,
    BKL_PDD_INTERFACE_INFO* pddIfc,
    const HKEY hKeyToWatch,
    const LPCTSTR szSubKey
);

#if defined (__cplusplus)
}
#endif // defined(__cplusplus)
///=============================================================================
/// Debug zones (for both DEBUG and RETAIL builds)
///=============================================================================
#ifndef SHIP_BUILD

#define ZONE_ERROR        DEBUGZONE(0)
#define ZONE_WARNING      DEBUGZONE(1)
#define ZONE_FUNCTION    DEBUGZONE(2)

extern DBGPARAM dpCurSettings;

#endif  // (DEBUG || RETAIL)

#endif
