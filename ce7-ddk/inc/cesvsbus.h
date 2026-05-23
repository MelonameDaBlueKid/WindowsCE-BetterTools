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
// Module Name:  
//     CESVSBUS.h
// 
// Abstract: Provides Service Bus Service.
// 
// Notes: 
//
#pragma once
#include <cebus.h>

// Callback.
#define IOCTL_BUS_SVS_ACTIVATE              _BUSACCESS_CTL_CODE(BUS_SERVICES_EXTENTION_FUNCTIONCODE+0)
// pInBuf
typedef struct __BUS_SVS_ACTIVATE_SERVICE {
    DWORD dwStructSize;
    DWORD dwClientInfo;
    TCHAR sRegPath[DEVKEY_LEN];
} BUS_SVS_ACTIVATE_SERVICE, *PBUS_SVS_ACTIVATE_SERVICE;
// pOutBuff
// HANDLE // DeviceHandle
#define IOCTL_BUS_SVS_DEACTIVATE            _BUSACCESS_CTL_CODE(BUS_SERVICES_EXTENTION_FUNCTIONCODE+1)
// pInBuf,
// HANDLE // DeviceHandle
// pOutBuf
// NULL
#define IOCTL_BUS_SVS_DEACTIVATE_BY_NAME    _BUSACCESS_CTL_CODE(BUS_SERVICES_EXTENTION_FUNCTIONCODE+2)
// pInBuf,
// NAME STRING 
// pOutBuf
// NULL
#define IOCTL_BUS_SVS_ENUM_SERVICES         _BUSACCESS_CTL_CODE(BUS_SERVICES_EXTENTION_FUNCTIONCODE+0x10)

