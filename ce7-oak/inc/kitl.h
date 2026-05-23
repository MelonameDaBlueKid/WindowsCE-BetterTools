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

Module Name:   kitl.h

Abstract:  
    This contains declarations the KITL routines for kitl support.
Functions:


Notes: 

--*/
#ifndef _KITL_H_
#define _KITL_H_

#include "KitlProt.h"

#ifdef __cplusplus
extern "C" {
#endif

// encode: given a frame (pbFrame) and the size of the data, encode the frame to be
//         suitable for the transport. The frame is guaranteed to large enough for
//         transport header and transport tailer, per specified in Kitl.FrmHdrSize
//         and Kitl.FrmTlrSize. And the data layout pointed by pbFrame is always
//          ----------------
//          | Frame Header |
//          |--------------|
//          |     Data     |        // of size cbData
//          |--------------|
//          | Frame Tailer |
//          |--------------|
//   where the encode function is supposed to fill in the Frame Header and Frame Tailer.
typedef BOOL (* PFN_ENCODE) (LPBYTE pbFrame, USHORT cbData);

// decode: given a frame pbFrame, and the frame length in *pcbData, the decode function 
//         check if the frame is valid and put the length of the data in *pcbData 
//         and return the pointer to data. Return NULL if this is not a valid frame.
//         Using the above picture, the return value should be pointer to "Data".
//         *pcbData will contain the size of the whole frame at entrance, and should
//         be updated to the size of "Data" when returned.
typedef LPBYTE (* PFN_DECODE) (LPBYTE pbFrame, PUSHORT pcbData);

// send: send a RAW frame via the transport.
typedef BOOL (* PFN_SENDFRAME) (LPBYTE pbFrame, USHORT cbFrame);
// recv: receive a RAW frame from the transport, *pcbBuffer contains the buffer size
//       at entrance, and should be updated to the size of the frame when returned.
typedef BOOL (* PFN_RECVFRAME) (LPBYTE pbBuffer, PUSHORT pcbBuffer);

// enable/disable transport interrupt
typedef void (* PFN_ENABLEINT) (BOOL fEnable);

// get device transport info
typedef PFN_RECVFRAME   PFN_GETDEVCFG;
typedef PFN_SENDFRAME   PFN_SETHOSTCFG;

// KITL power off / on 
typedef void (* PFN_POWERFUNC)();

// transport: the structure defines a KITL transport. The kernel calls OEMKitlInit
//         and the OEM is responsible of filling the data structure with appropriate
//         function pointers.
typedef struct _KITLTRANSPORT {
    DWORD          dwBootFlags;   // bit fields specify which service to start at boot time
#define KITL_FL_DBGMSG    (1 << 0)  // Debug messages
#define KITL_FL_PPSH      (1 << 1)  // Text shell
#define KITL_FL_KDBG      (1 << 2)  // Kernel debugger
#define KITL_FL_CLEANBOOT (1 << 3)  // Force a clean boot
#define KITL_FL_HAVEZONESET (1 << 4) // Indicates that the host will indicate whether the host key was set or not.
#define KITL_FL_ZONESET(x) (1 << (x + 5))
    char           szName[KITL_MAX_DEV_NAMELEN];    // name of the device
    UCHAR          Interrupt;     // interrupt number
    UCHAR          WindowSize;    // window size for default services
    UCHAR          FrmHdrSize;    // size of the frame header (so we can allocate buffer of the right size)
    UCHAR          FrmTlrSize;    // size of the frame tailer
    DWORD          dwPhysBuffer;  // where the physical buffer is for default kernel services
    DWORD          dwPhysBufLen;  // the size of the physical buffer for default sevices
    PFN_ENCODE     pfnEncode;     // to decode a frame
    PFN_DECODE     pfnDecode;     // to encode a frame
    PFN_SENDFRAME  pfnSend;       // to send a frame
    PFN_RECVFRAME  pfnRecv;       // to receive a frame
    PFN_ENABLEINT  pfnEnableInt;  // to enable/disable transport interrupt
    PFN_GETDEVCFG  pfnGetDevCfg;  // get device transport config data
    PFN_SETHOSTCFG pfnSetHostCfg; // set Host config data
    PFN_POWERFUNC  pfnPowerOn;    // power on  function
    PFN_POWERFUNC  pfnPowerOff;   // power off function
} KITLTRANSPORT, *PKITLTRANSPORT;

//
// OEMKitlStartup (void);
//
// First entry point to OAL when Kitldll is loaded. OEM calls KITLIoctl IOCTL_KITL_STARTUP when 
// it's ready to start kitl. 
//
BOOL OEMKitlStartup (void);

//
// OEMKitlInit:
//      OEM function to perform Initialization for the Kitl module. 
//      OEM is responsible for filling the entries in the KITLTRANSPORT structure.
BOOL OEMKitlInit (PKITLTRANSPORT pTransport);

//
// OEMKitlIoctl - KITL specific IOCTL handling
//
//  All kitl related functionalities (e.g. VMINI) should be handled here. 
//  Ideally, OAL should not contain any KITL code such that kitldll can be dynamically dropped onto
//  retail device for on the field debugging.
//  
//  It handles: IOCTL_VBRIDGE_802_3_MULTICAST_LIST, 
//  IOCTL_VBRIDGE_ADD_MAC, IOCTL_VBRIDGE_CURRENT_PACKET_FILTER, 
//  IOCTL_VBRIDGE_GET_ETHERNET_MAC, IOCTL_VBRIDGE_GET_RX_PACKET,
//  IOCTL_VBRIDGE_GET_RX_PACKET_COMPLETE, IOCTL_VBRIDGE_GET_TX_PACKET,
//  IOCTL_VBRIDGE_GET_TX_PACKET_COMPLETE, IOCTL_VBRIDGE_SHARED_ETHERNET,
//  IOCTL_VBRIDGE_WILD_CARD, IOCTL_VBRIDGE_WILD_CARD_RESET_BUFFER and 
//  IOCTL_VBRIDGE_WILD_CARD_VB_INITIALIZED codes.
//
BOOL OEMKitlIoctl (DWORD code, VOID * pInBuffer, DWORD inSize, VOID * pOutBuffer, DWORD outSize, DWORD * pOutSize);

//
// OEMKitlGetSecs:
//      return the "current time" in seconds
DWORD OEMKitlGetSecs (void);

//
// KitlInit:
//      Kernel Initialization for the Kitl module. This function should be called by 
//      the HAL to initialize the KITL subsystem. As part of the KitlInit processing, 
//      the kernel will call the OEMKitlInit routine to perform hardware initialization.
//      It may be called any time, typically as part of OEMInitDebugSerial or
//      OEMInit processing. KitlInit should also be called in the resume from
//      suspend processing, in OEMPowerOff.
//      
//      The paramenter fStartKitl tells the kernel if it should start the IST at 
//      the time of call. 
//      
//      If fStartKitl is FALSE, KITL behaves in completely passive mode, i.e. there'll 
//      be no KITL acitivity until someone calls KITLRegisterClient. This is mostly
//      used on dogfood devices that uses JIT debuggging.
//
//      If fStartKitl is TRUE, KITL will start talking to desktop and block until
//      connection is made. And we'll start the default services (PPSH, DBGMSG, KDBG) 
//      based on the configuration setting from the desktop.
//
//      Return TRUE if init successful, FALSE if not. 
//
BOOL KitlInit (BOOL fStartKitl);

//
// KitlSendRawData:
//      Essentially it's calling the transport Send Function (pfnSend function in KITLTRANSPORT),
//      with all the necessary protection. OEM MUST call this function if, for any reason, it must 
//      send data via the transport without KITL's knowledge. Note that the data sent will NOT be
//      seen by KITL on the desktop. The purpose of this funciton is to provide a way to safely send 
//      transport specific handshake (e.g. DHCP/ARP if using Ether transport).
//
BOOL KitlSendRawData (LPBYTE pbData, WORD wLength);

//
// KitlSetTimerCallback/KitlStopTimerCallback
//      Since we're inside the kernel and we don't have the luxury to create a thread at will,
//      this provide the transport a way to handle special handshake periodically. Note that 
//      the callback function will only be called once. The transport need to call this function
//      again if it wish to be called again. The timer is ver coarse-grained (in seconds) and 
//      is not intended for very time sensitive functions.
typedef void (* PFN_KITLTIMERCB) (LPVOID lpParam);
BOOL KitlSetTimerCallback (int nSecs, PFN_KITLTIMERCB pfnCB, LPVOID lpParam);
BOOL KitlStopTimerCallback (PFN_KITLTIMERCB pfnCB, LPVOID lpParam);

void KITLOutputDebugString (const char *fmt, ...);

#define KITL_SYSINTR_NOINTR  0xFFFFFFFF

BOOL KITLRegisterClient(UCHAR *pId, char *ServiceName, UCHAR Flags, UCHAR WindowSize, UCHAR *pBufferPool);
BOOL KITLDeregisterClient(UCHAR Id);
BOOL KITLSend(UCHAR Id, UCHAR *pUserData, DWORD dwUserDataLen);
BOOL KITLRecv(UCHAR Id, UCHAR *pRecvBuf, DWORD *pdwLen, DWORD Timeout);
void KITLSetDebug(DWORD DebugZoneMask);

// default services
#define KERNEL_SVC_DBGMSG       0
#define KERNEL_SVC_PPSH         1
#define KERNEL_SVC_KDBG         2

#define DEFAULT_SETTINGS    (ZONE_WARNING|ZONE_INIT|ZONE_ERROR) //|ZONE_FRAMEDUMP|ZONE_RECV|ZONE_SEND|ZONE_RETRANSMIT|ZONE_CMD|ZONE_KITL_OAL|ZONE_KITL_ETHER)
#define DEFAULT_PRECONNECT_SETTINGS (DEFAULT_SETTINGS | ZONE_RECV | ZONE_SEND | ZONE_KITL_OAL | ZONE_KITL_ETHER)

#ifdef __cplusplus
}
#endif


#endif _KITL_H_

