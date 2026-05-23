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
// GPS Intermediate Driver (GPSID) Driver Interface
//
// Defines IOCTLs that GPS device drivers that want 
// closer interaction with GPSID should implement and also
// IOCTLs that GPSID itself supports.
//
// ********************************************************


#include <winioctl.h>

//
//  In a future release, GPSID may support INTERFACE_POLL type for a GPS underlying
//  driver.  If a GPS driver interface is specified as "Poll" (rather "COMM" or "File"),
//  GPSID will periodically call the GPS driver with IOCTL_GPS_DRIVER_GET_LOCATION_V1.
//  GPSID will pass in a buffer in the output argument and the driver is responsible for 
//  filling a GPS_POSITION structure.
//
//  If no data is available but the device is functioning, the GPS driver should still 
//  return TRUE from its IOCTL handeler and just set dwValidFields member of GPS_POSITION=0.
//  If there is a fatal error (GPS hardware has been unplugged for instance), then
//  the IOCTL handeler should return FALSE.
//

#define IOCTL_GPS_DRIVER_GET_LOCATION_V1                CTL_CODE(FILE_DEVICE_GPS,1,METHOD_BUFFERED,FILE_ANY_ACCESS)

//
// The following IOCTLs are defined for reference and compatability across
// GPS devices from different manufactures.  GPSID will pass these through to
// the GPS driver directly.  It is up to the driver to decide whether and how to
// support these IOCTL codes.  If supported, the data blobs that are read and written
// are also left to the OEM to declare.
// 
// Implementors of these IOCTLs should make them run extremely quickly, as GPSID
// will have its global lock held during the call.
//

// Read the almanac settings from the GPS driver
#define IOCTL_GPS_READ_ALMANAC                          CTL_CODE(FILE_DEVICE_GPS,2,METHOD_BUFFERED,FILE_ANY_ACCESS)

// Write the almanac settings to the GPS driver
#define IOCTL_GPS_WRITE_ALMANAC                         CTL_CODE(FILE_DEVICE_GPS,3,METHOD_BUFFERED,FILE_ANY_ACCESS)

// Read assisted GPS informormation from the GPS driver
#define IOCTL_GPS_READ_ASSISTED                         CTL_CODE(FILE_DEVICE_GPS,4,METHOD_BUFFERED,FILE_ANY_ACCESS)

// Write assisted GPS informormation to the GPS driver
#define IOCTL_GPS_WRITE_ASSISTED                        CTL_CODE(FILE_DEVICE_GPS,5,METHOD_BUFFERED,FILE_ANY_ACCESS)



//
// The following IOCTLs are extensions to GPSID that must be supported
// by Poll drivers version 2 or greater.
//

// This is similar to the above IOCTL_GPS_DRIVER_GET_LOCATION_V1 but requires that 
// the driver respond to the location information including the extended (V2) fields of GPS_POSITION structure
#define IOCTL_GPS_DRIVER_GET_LOCATION_V2                CTL_CODE(FILE_DEVICE_GPS,6,METHOD_BUFFERED,FILE_ANY_ACCESS)

// IOCTL sent by GPSID to the GPS driver to get GPS_DEVICE_STATUS as a result of GPSGetDeviceState()
#define IOCTL_GPS_GET_DEVICE_STATUS                     CTL_CODE(FILE_DEVICE_GPS,7,METHOD_BUFFERED,FILE_ANY_ACCESS)

// IOCTL sent by GPSID to the GPS driver as a result of GPSGetDeviceParam()
#define IOCTL_GPS_GET_DEVICE_PARAMETER                  CTL_CODE(FILE_DEVICE_GPS,8,METHOD_BUFFERED,FILE_ANY_ACCESS)

// IOCTL sent by GPSID to the GPS driver as a result of GPSSetDeviceParam()
#define IOCTL_GPS_SET_DEVICE_PARAMETER                  CTL_CODE(FILE_DEVICE_GPS,9,METHOD_BUFFERED,FILE_ANY_ACCESS)

// IOCTL sent by GPSID to the GPS driver when a new GPS client has arrived.
#define IOCTL_GPS_ADD_HANDLE                            CTL_CODE(FILE_DEVICE_GPS,10,METHOD_BUFFERED,FILE_ANY_ACCESS)

// IOCTL sent by GPSID to the GPS driver as a result of a GPS client handle going away
#define IOCTL_GPS_REMOVE_HANDLE                         CTL_CODE(FILE_DEVICE_GPS,11,METHOD_BUFFERED,FILE_ANY_ACCESS)



//
// GPS Drivers will receive the following struct when they are called with
// IOCTL_GPSID_GET_DEVICE_PARAMETER and IOCTL_GPSID_SET_DEVICE_PARAMETER.
//
typedef struct _GPS_CONFIGURATION_PARAM {
    DWORD dwHandle;
    DWORD dwParamName;
    PBYTE pbParamData;
    DWORD dwParamSize;
} GPS_CONFIGURATION_PARAM, *PGPS_CONFIGURATION_PARAM;



#define GPS_POSITION_SIZE_V1 (FIELD_OFFSET (GPS_POSITION, PositionUncertaintyError))
#define GPS_POSITION_SIZE_V2 (sizeof(GPS_POSITION))
