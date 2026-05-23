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
// Sensor.h
//

#pragma once

#ifndef __SENSOR_H__
#define __SENSOR_H__


#include <windows.h>
#include <initguid.h>


#ifdef __cplusplus
extern "C" {
#endif

// IOCTL's
#define IOCTL_SENSOR_CSMDD_GET_CAPS                 \
    CTL_CODE(FILE_DEVICE_SENSOR_COMMON_MDD, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)

//-----------------------------------------------------------------------------
// Sensor Types - Taken from Desktop Team

//"{C04D2387-7340-4cc2-991E-3B18CB8EF2F4}"
DEFINE_GUID(SENSOR_TYPE_ACCELEROMETER_1D,
    0xC04D2387, 0x7340, 0x4cc2, 0x99, 0x1E, 0x3B, 0x18, 0xCB, 0x8E, 0xF2, 0xF4);

//"{B2C517A8-F6B5-4ba6-A423-5DF560B4CC07}"
DEFINE_GUID(SENSOR_TYPE_ACCELEROMETER_2D,
    0xB2C517A8, 0xF6B5, 0x4ba6, 0xA4, 0x23, 0x5D, 0xF5, 0x60, 0xB4, 0xCC, 0x07);

//"{C2FB0F5F-E2D2-4c78-BCD0-352A9582819D}"
DEFINE_GUID(SENSOR_TYPE_ACCELEROMETER_3D,
    0xC2FB0F5F, 0xE2D2, 0x4c78, 0xBC, 0xD0, 0x35, 0x2A, 0x95, 0x82, 0x81, 0x9D);

typedef enum 
{
    MESSAGE_ACCELEROMETER_3D_STATE,
    MESSAGE_ACCELEROMETER_3D_DATA,
    MESSAGE_ACCELEROMETER_3D_DEVICE_ORIENTATION_CHANGE,
}SENSOR_MESSAGE_TYPE;

typedef enum 
{
    SENSOR_UNKNOWN,
    SENSOR_ACCELEROMETER_3D,
}SENSOR_TYPE;

typedef enum 
{   
    SENSOR_STATE_UNKNOWN = 0,
    SENSOR_STATE_NOT_AVAILABLE,
    SENSOR_STATE_OK,
    SENSOR_STATE_INITIALIZING,
    SENSOR_STATE_UNRESOLVED,
    SENSOR_STATE_ACCESS_DENIED,
    SENSOR_STATE_ERROR,
}   SENSOR_STATE;

//-----------------------------------------------------------------------------

typedef struct _SENSOR_DATA_HEADER
{
    DWORD       cbSize;         // size of SENSOR_DATA_HEADER + the specific
                                    // sensor's SENSOR_DATA
    DWORD       dwTimeStampMs;  // acquisition time in milliseconds
    LUID        sensorLuid;     // Unique ID for resolving which sensor sample
                                    // originated from
    SENSOR_MESSAGE_TYPE msgType;
} SENSOR_DATA_HEADER;

typedef struct _SENSOR_DATA
{
    SENSOR_DATA_HEADER hdr;

    BYTE        value[1];   // Place holder for sensor specific data structure
} SENSOR_DATA, *PSENSOR_DATA;

typedef struct _SENSOR_DEVICE_CAPS
{
    DWORD       cbSize;             // sizeof(SENSOR_DEVICE_CAPS)
    DWORD       dwFlags;            // generic hardware feature flags
    LUID        sensorLuid;         // Unique ID for resolving which sensor
                                        // a sample originated from
    SENSOR_TYPE type;               // type of sensor
    DWORD       dwMinSwIntervalUs;  // This is how fast the sensor can be
                                        //read Sensor - resolution is 1µs
} SENSOR_DEVICE_CAPS, *PSENSOR_DEVICE_CAPS;

typedef struct _SENSOR_NOTIF_OUT
{
    DWORD  dwSourcePID;      //ProcessID of the sensor driver's process
    HANDLE hSourceMsgQueue;  //Message queue handle valid in the sensor driver's process
    HANDLE hDestMsgQueue;    //Message queue handle valid in the caller's process
} SENSOR_NOTIFICATION_OUT, *PSENSOR_NOTIFICATION_OUT;

//-----------------------------------------------------------------------------

DECLARE_HANDLE(HSENSOR);
#define INVALID_HSENSOR_VALUE ((HSENSOR) INVALID_HANDLE_VALUE)

//-----------------------------------------------------------------------------

typedef enum
{
    DEVICE_ORIENTATION_UNKNOWN = 0,
    DEVICE_ORIENTATION_PORTRAIT_UP = 1,
    DEVICE_ORIENTATION_LANDSCAPE_LEFT = 2,
    DEVICE_ORIENTATION_PORTRAIT_DOWN = 4,
    DEVICE_ORIENTATION_LANDSCAPE_RIGHT = 8
}DEVICE_ORIENTATION;

// 
#ifdef __cplusplus
}
#endif

#endif // __SENSOR_H__


