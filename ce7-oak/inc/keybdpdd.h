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

// Contains the data structures and function prototypes for a keyboard PDD.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <pm.h>
#include <keybddr.h>

typedef void (*PFN_KEYBD_PDD_POWER_HANDLER)(UINT uiPddId, BOOL fTurnOff);
typedef void (*PFN_KEYBD_PDD_TOGGLE_LIGHTS)(UINT uiPddId, KEY_STATE_FLAGS KeyStateFlags);

typedef struct tagKEYBD_PDD {
    WORD wPddMask; // Matches the keyboard layout with its PDD
    LPCTSTR pszName; // Used to identify PDD to user
    PFN_KEYBD_PDD_POWER_HANDLER pfnPowerHandler;
    PFN_KEYBD_PDD_TOGGLE_LIGHTS pfnToggleLights;
} KEYBD_PDD, *PKEYBD_PDD;

typedef void (*PFN_KEYBD_EVENT)(UINT uiPddId, UINT32 uiScanCode, BOOL fKeyDown);
typedef BOOL (*PFN_KEYBD_PDD_ENTRY)(UINT uiPddId, PFN_KEYBD_EVENT pfnKeybdEvent, PKEYBD_PDD *ppKeybdPdd);

typedef BOOL (*PFN_KEYBD_PDD_EXIT)(UINT uiPddId, PKEYBD_PDD *ppKeybdPdd);
typedef UCHAR (*PFN_KEYBD_PDD_GET_POWER_CAPS)();
typedef void (*PFN_KEYBD_PDD_SET_POWER_STATE)(CEDEVICE_POWER_STATE PowerState);
typedef BOOL (*PFN_KEYBD_PDD_IOCONTROL)(DWORD  dwCode, 
                                        PVOID  pBufIn,
                                        DWORD  dwLenIn, 
                                        PDWORD  pdwBufOut, 
                                        DWORD  dwLenOut,
                                        PDWORD pdwActualOut
                                        );

typedef struct tagKEYBD_CALLBACKS {
    DWORD                         dwSize;
    PFN_KEYBD_PDD_EXIT            pfnPddExits;
    PFN_KEYBD_PDD_GET_POWER_CAPS  pfnPddGetPowerCaps;
    PFN_KEYBD_PDD_SET_POWER_STATE pfnPddSetPowerState;
    PFN_KEYBD_PDD_IOCONTROL       pfnPddIoControl;

    PFN_KEYBD_DRIVER_GET_INFO     pfnPddGetInfo;
    PFN_KEYBD_DRIVER_SET_MODE     pfnPddSetMode;
} KEYBD_CALLBACKS, *PKEYBD_CALLBACKS;


BOOL KeybdMDDRegisterCallbacks(UINT uiPddId, KEYBD_CALLBACKS const * const pKeyBdCallbacks);
BOOL KeybdMDDRegisterGUID(UINT uiPddId, GUID const * const pGUID);

BOOL KeybdShimSetPowerState(__in_bcount(dwLenOut) DWORD * pdwBufOut, DWORD dwLenOut);
void KeybdShimGetPowerState(__out_bcount(dwLenOut) PDWORD pdwBufOut, DWORD dwLenOut, __out PDWORD pdwActualOut);
void KeybdShimGetPowerCaps(__out_bcount(dwLenOut) PDWORD pdwBufOut, DWORD dwLenOut, __out PDWORD pdwActualOut);
HKEY KeybdShimGetDeviceKey();

#ifdef __cplusplus
}
#endif