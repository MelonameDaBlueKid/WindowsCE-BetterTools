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

#ifndef __BACKLIGHT_H_
#define __BACKLIGHT_H_

#include <windows.h>
#include <pm.h>

///=============================================================================
/// IOCTLs
///=============================================================================
//  IOCTL_BKL_GET_BRIGHTNESS - returns current brightness of backlight
    //  DeviceIoControl:
    //  __in_opt     LPVOID lpInBuffer = NULL,
    //  __in         DWORD nInBufferSize = 0,
    //  __out        LPVOID lpOutBuffer = (LPDWORD) Brightness,
    //  __in         DWORD nOutBufferSize = sizeof(DWORD),
    //  __out        LPDWORD lpBytesReturned = (LPDWORD).
#define IOCTL_BKL_GET_BRIGHTNESS            \
    CTL_CODE(FILE_DEVICE_BACKLIGHT, 0x100, METHOD_BUFFERED, FILE_ANY_ACCESS)

//------------------------------------------------------------------------------
//  IOCTL_BKL_GET_BRIGHTNESS_CAPABILITIES - returns min/max supported brightnesses
    //  DeviceIoControl:
    //  __in_opt     LPVOID lpInBuffer = NULL,
    //  __in         DWORD nInBufferSize = 0,
    //  __out        LPVOID lpOutBuffer = (BKL_CAPABILITIES_INFO*) Support Info,
    //  __in         DWORD nOutBufferSize = sizeof(BKL_CAPABILITIES_INFO),
    //  __out        LPDWORD lpBytesReturned = (LPDWORD).
#define IOCTL_BKL_GET_BRIGHTNESS_CAPABILITIES                \
    CTL_CODE(FILE_DEVICE_BACKLIGHT, 0x101, METHOD_BUFFERED, FILE_ANY_ACCESS)

//------------------------------------------------------------------------------
//  IOCTL_BKL_GET_SETTINGS - gets backlight brightness settings
    //  DeviceIoControl:
    //  __in_opt     LPVOID lpInBuffer = NULL,
    //  __in         DWORD nInBufferSize = 0,
    //  __out        LPVOID lpOutBuffer = (BKL_SETTINGS_INFO*) Settings,
    //  __in         DWORD nOutBufferSize = sizeof(BKL_SETTINGS_INFO),
    //  __out        LPDWORD lpBytesReturned = (LPDWORD).
#define IOCTL_BKL_GET_SETTINGS                \
    CTL_CODE(FILE_DEVICE_BACKLIGHT, 0x102, METHOD_BUFFERED, FILE_ANY_ACCESS)

//------------------------------------------------------------------------------
//  IOCTL_BKL_SET_SETTINGS - sets backlight brightness settings
    //  DeviceIoControl:
    //  __in         LPVOID lpInBuffer = (BKL_SETTINGS_INFO*) Settings,
    //  __in         DWORD nInBufferSize = sizeof(BKL_SETTINGS_INFO),
    //  __out_opt    LPVOID lpOutBuffer = NULL,
    //  __in         DWORD nOutBufferSize = 0,
    //  __out_opt    LPDWORD lpBytesReturned = NULL.
#define IOCTL_BKL_SET_SETTINGS                \
    CTL_CODE(FILE_DEVICE_BACKLIGHT, 0x103, METHOD_BUFFERED, FILE_ANY_ACCESS)

//------------------------------------------------------------------------------
//  IOCTL_BKL_FORCE_UPDATE - forces backlight to update according to settings
    //  DeviceIoControl:
    //  __in_opt     LPVOID lpInBuffer = NULL,
    //  __in         DWORD nInBufferSize = 0,
    //  __out_opt    LPVOID lpOutBuffer = NULL,
    //  __in         DWORD nOutBufferSize = 0,
    //  __out_opt    LPDWORD lpBytesReturned = NULL.
#define IOCTL_BKL_FORCE_UPDATE                \
    CTL_CODE(FILE_DEVICE_BACKLIGHT, 0x104, METHOD_BUFFERED, FILE_ANY_ACCESS)

///=============================================================================
/// structures
///=============================================================================

// BKL_SETTINGS_INFO - backlight Settings. Used in IOCTL_BKL_GET_SETTINGS and
//      IOCTL_BKL_SET_SETTINGS.
//
//      dwBrightness_* - brightness of backlight.
//      fEnable_*      - Enable backlight. If FALSE, backlight would always be
//                       requested to turn off.
//      (*) corresponds to the behavior under different power source:
//          ExPower - on external power.
//          Battery - on battery.
typedef struct {
    DWORD dwBrightness_ExPower;
    BOOL fEnable_ExPower;
    DWORD dwBrightness_Battery;
    BOOL fEnable_Battery;
} BKL_SETTINGS_INFO;

// BKL_CAPABILITIES_INFO - backlight capabilities. Used in 
//      IOCTL_BKL_GET_BRIGHTNESS_CAPABILITIES
//
//      dwMinBrightness - minimum supported brightness supported by the backlight
//                        hardware, usually denotes OFF.
//      dwMaxBrightness - maximum supported brightness supported by the backlight
//                        hardware, usually denotes FULLY ON.
typedef struct {
    DWORD dwMinBrightness;
    DWORD dwMaxBrightness;
} BKL_CAPABILITIES_INFO;

///=============================================================================
/// GUID for Backlight drivers
///=============================================================================
#define BACKLIGHT_DRIVER_CLASS        _T("{F922DDE3-6A6D-4775-B23C-6842DB4BF094}")

#endif