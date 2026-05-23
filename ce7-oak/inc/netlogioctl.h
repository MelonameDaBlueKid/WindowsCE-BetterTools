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

#ifndef _NETLOGIOCTL_H
#define _NETLOGIOCTL_H
typedef struct _NETLOG_GLOBAL_STATE
{
    BOOL        bLogUSB;  //  Not IOCTL Controled.
    BOOL        bStopped; //  Default we are stopped. 
    DWORD       dwMaxPacketSize; // Log Packet upto len - dwMaxPacketSize;
    DWORD       dwCaptureBufferSize; // Size of memory allocated to hold captured packets
    WCHAR       wszCaptureFileName[MAX_PATH+1]; // Name of capture file written when capture is stopped
    DWORD       BluetoothLogMask; // Bitmask of NetlogBTDataType indicating types of BT data to be logged (0=none)
    BOOL        bBluetoothMsgQEnabled; // If TRUE, BT data is written to message queue.
} NETLOG_GLOBAL_STATE;

// Specifies IOCTL interface between netlog and netlogctl.

#define   IOCTL_NETLOG_START                        1
#define   IOCTL_NETLOG_STOP                         2
#define   IOCTL_NETLOG_UNUSED_3                     3
#define   IOCTL_NETLOG_SET_CAPTURE_FILENAME         4
#define   IOCTL_NETLOG_CAPTURE_PACKET_SIZE          5
#define   IOCTL_NETLOG_SET_CAPTURE_BUFFER_SIZE      6
#define   IOCTL_NETLOG_LOG_USB                      7
#define   IOCTL_NETLOG_GET_STATE                    8
#define   IOCTL_NETLOG_SET_BLUETOOTH_LOGGING_STATE  11
#define   IOCTL_NETLOG_SET_BLUETOOTH_VSNIFF_STATE   12
#define   IOCTL_NETLOG_BLUETOOTH_COMMENT_STRING     13 
#define   IOCTL_NETLOG_COMMENT_STRING               14

// Registry Path To ActivateDevice information.
#define NETLOG_DEVICE_KEY L"Comm\\Devices\\Netlog"
// Name used when calling CreateFile
#define NETLOG_LEGACY_NAME L"NLG0:"

#endif 
