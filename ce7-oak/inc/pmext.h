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
// This module contains power manger extention.
//

// This typedef describes the system activity states.  These are independent of
// factors such as AC power vs. battery, in cradle or not, etc.  OEMs may choose
// to add their own activity states if they customize this module.

// This typedef describes activity events such as user activity or inactivity,
// power status changes, etc.  OEMs may choose to factor other events into their
// system power state transition decisions.

#pragma once
#include <pm.h>

typedef enum {
    NoActivity=0,
    UserActivity,
    UserInactivity,
    SystemActivity,
    SystemInactivity,
    EnterUnattendedModeRequest,
    LeaveUnattendedModeRequest,
    Timeout,
    RestartTimeouts,
    PowerSourceChange,
    Resume,
    SystemPowerStateChange,
    SystemPowerStateAPI,
    PmShutDown,
    PmReloadActivityTimeouts,
    PowerButtonPressed,
    AppButtonPressed, 
    BootPhaseChanged,
    PowerManagerExt = 0x800,
    ExternedEvent = 0x1000
} PLATFORM_ACTIVITY_EVENT, *PPLATFORM_ACTIVITY_EVENT;

typedef DWORD   (WINAPI * PFN_PMExt_Init)(HKEY hKey, LPCTSTR lpRegistryPath); // Must have
typedef VOID    (WINAPI * PFN_PMExt_DeInit) (DWORD dwExtContext );// Must Have
// System Event.
typedef HANDLE (WINAPI * PFN_PMExt_GetNotificationHandle)(DWORD dwExtContext); // Optional
typedef VOID (WINAPI * PFN_PMExt_EventNotification)(DWORD dwExtContext, PLATFORM_ACTIVITY_EVENT platformActivityEvent); // Optional
// System Power State
typedef VOID (WINAPI * PFN_PMExt_PMBeforeNewSystemState)(DWORD dwExtContext, LPCTSTR lpNewStateName, DWORD dwFlags); // Optional
typedef VOID (WINAPI *PFN_PMExt_PMAfterNewSystemState)(DWORD dwExtContext, LPCTSTR lpNewStateName, DWORD dwFlags);  // Optional
// Device Power State
typedef VOID (WINAPI * PFN_PMExt_PMBeforeNewDeviceState)(DWORD dwExtContext,LPCTSTR pszName, CEDEVICE_POWER_STATE curDx, CEDEVICE_POWER_STATE reqDx); // Optional
typedef VOID (WINAPI * PFN_PMExt_PMAfterNewDeviceState)(DWORD dwExtContext, LPCTSTR pszName, CEDEVICE_POWER_STATE reqDx, CEDEVICE_POWER_STATE actualDx); // Optional


#define PMExt_Init_NAME TEXT("PMExt_Init")
#define PMExt_DeInit_NAME TEXT("PMExt_DeInit")
#define PMExt_GetNotificationHandle_NAME TEXT("PMExt_GetNotificationHandle")
#define PMExt_EventNotification_NAME TEXT("PMExt_EventNotification")
#define PMExt_PMBeforeNewSystemState_NAME TEXT("PMExt_PMBeforeNewSystemState")
#define PMExt_PMAfterNewSystemState_NAME TEXT("PMExt_PMAfterNewSystemState")
#define PMExt_PMBeforeNewDeviceState_NAME TEXT("PMExt_PMBeforeNewDeviceState")
#define PMExt_PMAfterNewDeviceState_NAME TEXT("PMExt_PMAfterNewDeviceState")

#define PMExt_Registry_Root TEXT("SYSTEM\\CurrentControlSet\\Control\\Power\\Extension")

