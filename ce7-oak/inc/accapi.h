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
// ********************************************************
// Accelerometer API
// ********************************************************

#include <windows.h>
#include <sensor.h>

#pragma once

#ifdef __cplusplus
extern "C" 
{
#endif

typedef struct _ACC_DATA
{ 
    SENSOR_DATA_HEADER hdr;
    float  x,y,z;                // signed acceleration in G units (9.8 meters per second squared)
} ACC_DATA, *PACC_DATA;

typedef struct _ACC_ORIENT
{ 
    SENSOR_DATA_HEADER hdr;
    DEVICE_ORIENTATION devOrientation;     // device orientation
} ACC_ORIENT, *PACC_ORIENT;

typedef enum 
{
    ACC_CONFIG_STREAMING_DATA_MODE = 0, //default mode
    ACC_CONFIG_ORIENTATION_MODE,
    ACC_CONFIG_COMPASS_MODE,
    ACC_CONFIG_CALIBRATION_MODE,
    ACC_CONFIG_LAST_MODE = ACC_CONFIG_CALIBRATION_MODE,
}ACC_CONFIG_MODE;

// users of Acc APIs should create a message queue with 
// msgQueueOptions.dwMaxMessages = ACC_MAXQUEUEMESSAGES
#define ACC_MAXQUEUEMESSAGES    16

#define ACC_2GSCALE_MIN (-2.0F)
#define ACC_2GSCALE_MAX (2.0F)

typedef DWORD ACCELEROMETER_CALLBACK(ACC_DATA* pAccData, __in_opt LPVOID plvCallbackParam);
typedef DWORD ACCELEROMETER_MSGCALLBACK(SENSOR_MESSAGE_TYPE msgType, LPVOID pAccData, DWORD cbSizeAccData, __in_opt LPVOID plvCallbackParam);

/// <summary>
/// Open a handle to an instance of the accelerometer device.
/// </summary>
/// <returns>
/// An open handle to the specified device indicates success. 
/// INVALID_HANDLE_VALUE indicates failure. To get extended 
/// error information, call GetLastError.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = __in_z LPCWSTR szDeviceName> Pointer to a null-terminated string that specifies the name of the object </param>
/// <param name = __deref_opt_out PLUID pSensorLuid> Pointer to a LUID containing the Sensor Unique Id </param>
HSENSOR WINAPI AccelerometerOpen(__in_z LPCWSTR szDeviceName, __deref_opt_out PLUID pSensorLuid);

/// <summary>
/// This function sends a start IOCTL to the driver.
/// </summary>
/// <returns>
/// Return error code.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = HSENSOR hAccDevice> Handle of the opened accelerometer device </param>
/// <param name = HANDLE hMsgQueue> Handle of the massage queue to received the accelerometer samples </param>
DWORD WINAPI AccelerometerStart(HSENSOR hAccDevice, HANDLE hMsgQueue);

/// <summary>
/// This function sends a stop IOCTL to the driver.
/// </summary>
/// <returns>
/// Return error code.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = HSENSOR hAccDevice> Handle of the opened accelerometer device </param>
DWORD WINAPI AccelerometerStop(HSENSOR hAccDevice);

/// <summary>
/// This function sets a particular mode for accelerometer instance
/// </summary>
/// <returns>
/// Return error code.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = HSENSOR hAccDevice> Handle of the opened accelerometer device </param>
/// <param name = ACC_CONFIG_MODE configMode> The configuration mode need to be set </param>
/// <param name = LPVOID reserved> Reserved field </param>
DWORD WINAPI AccelerometerSetMode(HSENSOR hAccDevice, ACC_CONFIG_MODE configMode, LPVOID reserved);

/// <summary>
/// This function invokes the accelerometer calibration functionality.
/// </summary>
/// <returns>
/// Return error code.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = HSENSOR hAccDevice> Handle of the opened accelerometer device </param>
DWORD WINAPI AccelerometerCalibrate(HSENSOR hAccDevice);

/// <summary>
/// This function causes a callback function to be called when new accelerometer samples are available.
/// This function creates a message queue which is forwarded to the driver. 
/// A thread is then created to read messages from this queue.
/// </summary>
/// <returns>
/// Return error code.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = HSENSOR hAccDevice> Handle of the opened accelerometer device </param>
/// <param name = __in ACCELEROMETER_CALLBACK* pfnCallback> pointer of the callback function </param>
/// <param name = __in_opt LPVOID plvCallbackParam> Callback function parameters </param>
DWORD WINAPI AccelerometerCreateCallback(HSENSOR hAccDevice, __in ACCELEROMETER_CALLBACK* pfnCallback, __in_opt LPVOID plvCallbackParam);

/// <summary>
/// This function causes a callback function to be called when new accelerometer messages are available.
/// This function creates a message queue which is forwarded to the driver.
/// A thread is then created to read messages from this queue.
/// </summary>
/// <returns>
/// Return error code.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = HSENSOR hAccDevice> Handle of the opened accelerometer device </param>
/// <param name = __in ACCELEROMETER_MSGCALLBACK* pfnCallback> pointer of the callback function with msg type </param>
/// <param name = __in_opt LPVOID plvCallbackParam> Callback function parameters </param>
DWORD WINAPI AccelerometerCreateMsgCallback(HSENSOR hAccDevice, __in ACCELEROMETER_MSGCALLBACK* pfnCallback, __in_opt LPVOID plvCallbackParam);

/// <summary>
/// This function cancels a callback created via AccelerometerCreateCallback
/// </summary>
/// <returns>
/// Return error code.
/// </returns>
/// <exception>
/// N/A
/// </exception>
/// <param name = HSENSOR hAccDevice> Handle of the opened accelerometer device </param>
DWORD WINAPI AccelerometerCancelCallback(HSENSOR hAccDevice);

#ifdef __cplusplus
}
#endif