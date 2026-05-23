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
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
// -----------------------------------------------------------------------------
//
// @doc     WDEV_EXT
//
// @module  wavedev.h | Provides the device.exe DeviceIoControl control codes
//          for communicating with both waveapi.dll and wavedev.dll.
//
// -----------------------------------------------------------------------------
#ifndef __WAVEDEV_H__
#define __WAVEDEV_H__

#include "windev.h"

#ifdef __cplusplus
extern "C" {
#endif


//------------------------------------------------------------------------------
//
//  @doc    WDEV_EXT
//
//  @topic  Wave Audio API Manager Device Interface |
//          The COREDLL.DLL Dynamic Link Library gives user applications
//          access to the Waveform Audio functions.
//
//          The Waveform Audio API Manager exports the waveXXX functions via the
//          device manager's IOCTL calls. IOCTL_XXX constants are defined in
//          wavedev.h.
//
//  @ex     Software Layers |
//
// *       ===============    ===============
// *       | Application |    | Application |  Module(s)
// *       ===============    ===============
// *
// *         --------- MMSYSTEM.H ---------    Interface
// *
// *       ==================================
// *       |          COREDLL.DLL           |  Module  (coredll.dll)
// *       ==================================
// *
// *         ---------- WAVEDEV.H ---------    Interface
// *
// *         ------ DeviceIoControl() -----    PSL API
// *
// *       ==================================
// *       |     WAPI (Wave API Manager)    |  Module (waveapi.dll)
// *       ==================================
// *
// *         ---------- WAVEDEV.H ---------    Interface
// *
// *         ------ DeviceIoControl() -----    PSL API
// *
// *       ==================================
// *       |            WAVEMDD             |  Module (wavedev.dll)
// *       ==================================
// *
// *         --------- WAVEDDSI.H ---------    Interface
// *
// *       ==================================
// *       |            WAVEPDD             |  Module (wavedev.dll)
// *       ==================================
//
//------------------------------------------------------------------------------


// For sending messages to the "WAV" device audio driver (wavedev.dll)
#define IOCTL_WAV_MESSAGE                CTL_CODE(FILE_DEVICE_SOUND,    3, METHOD_BUFFERED, FILE_ANY_ACCESS)

// For sending messages to an installed "ACM" device codec
#define IOCTL_ACM_MESSAGE                CTL_CODE(FILE_DEVICE_SOUND,  100, METHOD_BUFFERED, FILE_ANY_ACCESS)

//------------------------------------------------------------------------------
//
//  @doc    WDEV_EXT
//
//  @struct MMDRV_MESSAGE_PARAMS | Structure for parameters passed to
//          the <f WAV_IOControl>() function.
//
//  @field  UINT | uDeviceId |
//          Device identifier (0, 1, 2, and so on) for the target device.
//
//  @field  UINT | uMsg | Specifies one of the <t Wave Input Driver Messages>
//          or <t Wave Output Driver Messages>.
//
//  @field  DWORD | dwUser | Specifies a device instance identifier. For
//          the <m WODM_OPEN> and <m WIDM_OPEN> messages, this is an <p output>
//          parameter. The device creates an instance identifier and
//          returns it in the address specified as the argument. For all
//          other messages, this is an <p input> parameter. The argument
//          is the instance identifier.
//
//  @field  DWORD | dwParam1 | Specifies the first message parameter.
//          Dependent on message type.
//
//  @field  DWORD | dwParam2 | Specifies the second message parameter.
//          Dependent on message type.
//
//  @xref   <t Wave Input Driver Messages> (WIDM_XXX) <nl>
//          <t Wave Output Driver Messages> (WODM_XXX)
//
//------------------------------------------------------------------------------
typedef struct {
    UINT uDeviceId;
    UINT uMsg;
    DWORD dwUser;
    DWORD dwParam1;
    DWORD dwParam2;
} MMDRV_MESSAGE_PARAMS, *PMMDRV_MESSAGE_PARAMS;


//------------------------------------------------------------------------------
//
//  @doc    WACM_EXT
//
//  @struct ACMDRV_MESSAGE_PARAMS | Structure for parameters passed to
//          the <f ACM_IOControl>() function.
//
//  @field  DWORD | dwDriverID |
//          Instance identifier. This value is message-dependent.
//
//  @field  HANDLE | hDriver | Driver handle.
//
//  @field  UINT | uMsg | Specifies one of the <t ACM Driver Messages>.
//
//  @field  LPARAM | lParam1 | Specifies the first message parameter.
//          Dependent on message type.
//
//  @field  LPARAM | lParam2 | Specifies the second message parameter.
//          Dependent on message type.
//
//  @xref   <t ACM Driver Messages> (ACMDM_XXX)
//
//------------------------------------------------------------------------------
typedef struct {
    DWORD  dwDeviceId;
    HANDLE hDriver;
    UINT   uMsg;
    LPARAM lParam1;
    LPARAM lParam2;
} ACMDRV_MESSAGE_PARAMS, *PACMDRV_MESSAGE_PARAMS;

// Possible values for wClickVolume.  Muted must be zero in order for
// default case to work correctly in UpdateFromRegistry
#define WC_CLICKVOL_MUTED 0
#define WC_CLICKVOL_QUIET 1
#define WC_CLICKVOL_LOUD  2

//------------------------------------------------------------------------------
//
// Parameters for the PlaySoundHook functions.  These functions allow a
// project to hook the (snd)PlaySound function before and after the actual
// playing of the sound.
//
//------------------------------------------------------------------------------
typedef BOOL (*PFN_PLAY_SOUND_HOOK_START)(
    LPCWSTR szSoundName,
    DWORD dwSndType
    );

#define SND_APPS            0x01000000
#define SND_EVENTS          0x02000000
#define SND_NOTIFICATIONS   0x04000000
#define SND_TCHCLICK        0x80000000
#define SND_KEYCLICK        0x40000000
#define SND_CLICK           0xC0000000

typedef void (*PFN_PLAY_SOUND_HOOK_STOP)(void);
typedef void (*PFN_PLAY_SOUND_HOOK_UPDATE)(void);

#ifdef __cplusplus
}
#endif


#endif // __WAVEDEV_H__
