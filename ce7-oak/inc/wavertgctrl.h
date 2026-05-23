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

#ifndef _WAVERTGCTRL_H_
#define _WAVERTGCTRL_H_

#if (_MSC_VER >= 1000)
#pragma once
#endif

#include <basetyps.h>

#ifdef __cplusplus
extern "C" {
#endif

//
// Device topology.
//

// {9FEFFBD7-E178-4db3-81A3-1262347C96B3}
DEFINE_GUID(MM_PROPSET_DEVTOPOLOGY, 
    0x9feffbd7, 0xe178, 0x4db3, 0x81, 0xa3, 0x12, 0x62, 0x34, 0x7c, 0x96, 0xb3);

// Prop get only - Returns the device descriptor.
//      pvPropData - Pointer to DTP_DEVICE_DESCRIPTOR.
#define MM_PROP_DEVTOPOLOGY_DEVICE_DESCRIPTOR       1

// Prop get only - Returns the virutal endpoint descriptor.
//      pvPropParams - Pointer to DWORD for the endpoint index.
//      pvPropData - Pointer to DTP_ENDPOINT_DESCRIPTOR.
#define MM_PROP_DEVTOPOLOGY_ENDPOINT_DESCRIPTOR    2

// Prop set only - Registers a message queue to receive device topology messages.
//      pvPropData - Pointer to message queue handle returned from CreateMsgQueue.
#define MM_PROP_DEVTOPOLOGY_EVTMSG_REGISTER         3

// Prop set only - Unregisters a message queue from receiving device topology messages.
//      pvPropData - Pointer to a message queue handle previously registered.
#define MM_PROP_DEVTOPOLOGY_EVTMSG_UNREGISTER       4

// Device descriptor.
typedef struct _DTP_DEVICE_DESCRIPTOR
{
    GUID guidDevClass;                      // Device class GUID.
    DWORD cEndpoints;                       // Number of endpoints on the device.
} DTP_DEVICE_DESCRIPTOR, *PDTP_DEVICE_DESCRIPTOR;

// Endpoint descriptor.
typedef struct _DTP_ENDPOINT_DESCRIPTOR
{
    DWORD dwIndex;                          // Endpoint index starting at zero.
    GUID guidEndpoint;                      // Endpoint GUID.
    BOOL fRemovable;                        // Endpoint is removable.
    DWORD fAttached;                        // Endpoint attached state.
} DTP_ENDPOINT_DESCRIPTOR, *PDTP_ENDPOINT_DESCRIPTOR;

// Device topology event types.
#define DTP_EVT_ENDPOINT_CHANGE         0x00000001  // Endpoint change event.

// Maximum device topology message size.
#define DTP_EVTMSG_SIZE_MAX             128

// Device topology message header.  This structure is located at the 
// beginning of all device topology messages.
typedef struct _DTP_EVTMSGHDR
{
    DWORD dwEvtType;                        // Event type.
    DWORD cbMsg;                            // Size in bytes of the containing message structure.
} DTP_EVTMSGHDR, *PDTP_EVTMSGHDR;

// Endpoint change message.
typedef struct _DTP_EVTMSG_ENDPOINT_CHANGE
{
    DTP_EVTMSGHDR hdr;                      // Message header.
    DWORD dwIndex;                          // Index of the endpoint that changed.
    BOOL fAttached;                         // Endpoint is attached?
} DTP_EVTMSG_ENDPOINT_CHANGE, *PDTP_EVTMSG_ENDPOINT_CHANGE;

// CASSERT(sizeof(DTP_EVTMSG_ENDPOINT_CHANGE) <= DTP_EVTMSG_SIZE_MAX);

//
// Routing control.
//

// {C19F94C4-8448-4c9b-997C-4EAE0B25500C}
DEFINE_GUID(MM_PROPSET_RTGCTRL, 
    0xc19f94c4, 0x8448, 0x4c9b, 0x99, 0x7c, 0x4e, 0xae, 0xb, 0x25, 0x50, 0xc);

// Prop set only - Request for endpoint routing.
//      pvPropData - Pointer to RTGCTRL_ENDPOINT_ROUTING.
#define MM_PROP_RTGCTRL_ENDPOINT_ROUTING    1

// Maximum number of simultaneous selectable endpoints.
#define ENDPOINT_SELECT_MAX                 4

// Endpoints to select for routing.
typedef struct _RTGCTRL_ENDPOINT_SELECT
{
    DWORD cEndpoints;                       // Number of endpoints.
    DWORD rgdwIndex[ENDPOINT_SELECT_MAX];   // Index of endpoints to use for routing.
} RTGCTRL_ENDPOINT_SELECT, *PRTGCTRL_ENDPOINT_SELECT;

// Audio media types to route to endpoints.
typedef enum _RTGCTRL_MEDIATYPE
{
    RTGCTRL_MEDIATYPE_SYSTEM = 0,           // System audio, e.g. wave ouput and wave input
    RTGCTRL_MEDIATYPE_CELLULAR              // Cellular audio
} RTGCTRL_MEDIATYPE;

// Endpoint routing control structure.  Used with MM_PROP_RTGCTRL_ENDPOINT_ROUTING.
typedef struct _RTGCTRL_ENDPOINT_ROUTING
{
    BOOL fEnable;                           // Enables the routing of the media type.
    RTGCTRL_MEDIATYPE MediaType;            // The media type to route.
    RTGCTRL_ENDPOINT_SELECT EndpointSelect; // Endpoints to use for routing.
    DWORD dwReserved;                       // Reserved.
} RTGCTRL_ENDPOINT_ROUTING, *PRTGCTRL_ENDPOINT_ROUTING;

// Endpoint flags.
#define EPFLAGS_MEDIATYPE_CELLULAR_RX       0x00000001  // Endpoint can be used for cellular RX media.
#define EPFLAGS_MEDIATYPE_CELLULAR_TX       0x00000002  // Endpoint can be used for cellular TX media.
#define EPFLAGS_MEDIATYPE_CELLULAR          (EPFLAGS_MEDIATYPE_CELLULAR_RX | EPFLAGS_MEDIATYPE_CELLULAR_TX)
#define EPFLAGS_GENVOICECOMM_RX             0x00001000  // Endpoint can be used for general non-cellular voice comm RX.
#define EPFLAGS_GENVOICECOMM_TX             0x00002000  // Endpoint can be used for general non-cellular voice comm TX.
#define EPFLAGS_GENVOICECOMM                (EPFLAGS_GENVOICECOMM_RX | EPFLAGS_GENVOICECOMM_TX)
#define EPFLAGS_NOAUTOENABLE                0x00010000  // Endpoint should not be auto-enabled when attached.

#define RTGFLAGS_INCALLSTREAM               0x00000001  // Stream uses in-call attenuation and routing behavior.
#define RTGFLAGS_BTHHANDSFREE               0x00000002  // Stream routes to BTH handsfree device.

#ifdef __cplusplus
}
#endif

#endif // _WAVERTGCTRL_H_
