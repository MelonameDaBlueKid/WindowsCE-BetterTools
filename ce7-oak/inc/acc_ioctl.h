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
//

#pragma once

#include <windev.h>

#define FILE_DEVICE_ACCELEROMETER       0x0000011a

#define IOCTL_ACC_STARTSENSOR         \
    CTL_CODE(FILE_DEVICE_ACCELEROMETER, 0x1, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACC_STOPSENSOR         \
    CTL_CODE(FILE_DEVICE_ACCELEROMETER, 0x2, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACC_SETCONFIG_MODE \
    CTL_CODE(FILE_DEVICE_ACCELEROMETER, 0x3, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACC_CALIBRATESENSOR \
        CTL_CODE(FILE_DEVICE_ACCELEROMETER, 0x4, METHOD_BUFFERED, FILE_ANY_ACCESS)    


