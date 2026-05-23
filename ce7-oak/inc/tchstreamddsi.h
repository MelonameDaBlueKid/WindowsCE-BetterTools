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
// Defines the interface between Touch stream driver MDD and PDD
//
//=============================================================================

#ifndef __TCHSTREAMDDSI_H_
#define __TCHSTREAMDDSI_H_

// tchstream.h for definition of CETOUCHINPUT.
// Not using tchddi.h since it will be deprecated soon
#include <tchstream.h>

///=============================================================================
/// Function Pointers
///=============================================================================

// called by MDD to Deinit PDD
typedef void (WINAPI *PFN_TCH_PDD_DEINIT) (
    DWORD hPddContext
    );

// IOctls passed to PDD
typedef BOOL (WINAPI *PFN_TCH_PDD_IOCONTROL) (
    DWORD hPddContext,
    DWORD dwCode,
    PBYTE pBufIn,
    DWORD dwLenIn,
    PBYTE pBufOut,
    DWORD dwLenOut,
    PDWORD pdwActualOut
    );

// stream interface xxx_powerdown passed to PDD
typedef void (WINAPI *PFN_TCH_PDD_POWERDOWN) (
    DWORD hPddContext
    );

// stream interface xxx_powerup passed to PDD
typedef void (WINAPI *PFN_TCH_PDD_POWERUP) (
    DWORD hPddContext
    );

// PDD calls MDD's function to report the set of simultaneous samples
//
// cInputs is the count of simultaneous samples.
// pTouchInputs is an array of simultaneous samples
// 
// For single-touch drivers, cInputs will always be 1 because there
// will never be more than one simultaneous touch sample.
//
// The PDD must set the following fields in each CETOUCHINPUT structure.
//      x
//      y
//      dwID        - For single touch this can always be 0
//      dwFlags     - TOUCHEVENTF_DOWN | TOUCHEVENTF_INRANGE, etc.
//
// The remaining fields are either optional or are ignored and should 
// be set to 0 if not used.
typedef void (WINAPI *PFN_TCH_MDD_REPORTSAMPLESET) (
    DWORD hMddContext,
    DWORD cInputs,
    __in_ecount(cInputs) const CETOUCHINPUT *pTouchInputs
    );


    
///=============================================================================
/// Structs
///=============================================================================

// mdd info passed to TchPdd_Init
typedef struct {
    UINT32                      version;
    PFN_TCH_MDD_REPORTSAMPLESET pfnMddReportSampleSet;
} TCH_MDD_INTERFACE_INFO;

// TchPdd_Init must fill out this structure
typedef struct {
    UINT32                version;

    PFN_TCH_PDD_DEINIT pfnDeinit;
    PFN_TCH_PDD_IOCONTROL pfnIoctl;
    PFN_TCH_PDD_POWERDOWN pfnPowerDown;
    PFN_TCH_PDD_POWERUP pfnPowerUp;

} TCH_PDD_INTERFACE_INFO;  

///=============================================================================
/// External functions
///=============================================================================

// statically linked function implemented by PDD
#ifdef __cplusplus
extern "C" {
#endif
DWORD WINAPI TchPdd_Init(
    LPCTSTR pszActiveKey,
    TCH_MDD_INTERFACE_INFO* pMddIfc,
    TCH_PDD_INTERFACE_INFO* pPddIfc,
    DWORD hMddContext
    );
#ifdef __cplusplus
}
#endif
    
///=============================================================================
/// Debug zones (for both DEBUG and RETAIL builds)
///=============================================================================
#ifndef SHIP_BUILD

extern DBGPARAM dpCurSettings;

#define ZONE_TOUCH_ERROR        DEBUGZONE(0)
#define ZONE_TOUCH_WARN         DEBUGZONE(1)
#define ZONE_TOUCH_FUNC         DEBUGZONE(2)
#define ZONE_TOUCH_INIT         DEBUGZONE(3)
#define ZONE_TOUCH_INFO         DEBUGZONE(4)
#define ZONE_TOUCH_CIRCBUFFER   DEBUGZONE(5)
#define ZONE_TOUCH_SAMPLES      DEBUGZONE(6)
#define ZONE_TOUCH_IST          DEBUGZONE(7)
#define ZONE_TOUCH_VERBOSE      DEBUGZONE(8)
#define ZONE_TOUCH_TIPSTATE     DEBUGZONE(9)
#define ZONE_TOUCH_PDD          DEBUGZONE(10)

#endif  // (DEBUG || RETAIL)

#endif
