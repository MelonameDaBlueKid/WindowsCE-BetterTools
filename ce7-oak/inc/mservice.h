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
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

mservice.h

Abstract:  

Notes: 


--*/

#if ! defined (__mservice_H__)
#define __mservice_H__		1

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#ifdef WINCEMACRO
// Actual functions to trap into PSLs are declared in mwinbase.h
// MService.h contains the IOCTL rules for those APIs that can
// be simulated usi
#include <mwinbase.h>
#endif

// NOTE: Applications MUST not use IOCTLs defined in this header file.
// These are for services.exe internal use only.  Services.exe will intercept
// these IOCTLs (it never sends them to the service itself) and take appropriate action.

// IOCTL to make a service perform ServiceAddPort 
#define IOCTL_SERVICE_INTERNAL_SERVICE_ADD_PORT CTL_CODE(FILE_DEVICE_SERVICE, 1000, METHOD_BUFFERED, FILE_ANY_ACCESS)

// IOCTL to make a service perform ServiceClosePort 
#define IOCTL_SERVICE_INTERNAL_SERVICE_CLOSE_PORT CTL_CODE(FILE_DEVICE_SERVICE, 1001, METHOD_BUFFERED, FILE_ANY_ACCESS)

// IOCTL to make a service perform ServiceUnbindPorts 
#define IOCTL_SERVICE_INTERNAL_SERVICE_UNBIND_PORTS CTL_CODE(FILE_DEVICE_SERVICE, 1002, METHOD_BUFFERED, FILE_ANY_ACCESS)

// Parameters of ServiceAddPort to be marshalled in IOCTL_SERVICE_INTERNAL_SERVICE_ADD_PORT call
typedef struct _ServicesExeAddPort {
	SOCKADDR *pSockAddr;
	int cbSockAddr;
	int iProtocol;
} ServicesExeAddPort;

// Parameters of ServiceClosePort to be marshalled in IOCTL_SERVICE_INTERNAL_SERVICE_CLOSE_PORT call
typedef struct _ServicesExeClosePort {
	SOCKADDR *pSockAddr;
	int cbSockAddr;
	int iProtocol;
} ServicesExeClosePort;

// IOCTL to implement EnumServices
#define IOCTL_SERVICE_INTERNAL_SERVICE_ENUM CTL_CODE(FILE_DEVICE_SERVICE, 1003, METHOD_BUFFERED, FILE_ANY_ACCESS)

// Paramaters of EnumServices to be marshalled in IOCTL_SERVICE_INTERNAL_SERVICE_ENUM
typedef struct _ServicesExeEnumServicesIntrnl {
	PBYTE pBuffer;
	DWORD *pdwServiceEntries;
	DWORD *pdwBufferLen;
} ServicesExeEnumServicesIntrnl;

#ifdef __cplusplus
}
#endif

#endif	/* __mservice_H__ */

