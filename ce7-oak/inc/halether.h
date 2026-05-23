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

    halether.h

Abstract:


    Defines for the interface to the kernel ethernet services.  Specifies the
    required services by the HAL to allow the debug ethernet (EDBG) services
    (debug messages, kernel debugger, PPSH shell) to operate.

    @doc    EDBG

    @topic  Interfacing a platform to the Windows CE Ethernet debug (EDBG) services |

            In order to use the Ethernet transport for Windows CE debug services
            (dbgmsg, CESH, debugger), the OEM must provide a set of routines to
            control the debug Ethernet hardware specific to the platform (OEMEthxxx
            functions described below), and link ethdbg.lib into the kernel.  Sample
            drivers for NE2000 (ne2kdbg.lib) and SMC9000 (smc9000.lib) compatible
            Ethernet adapters are provided, or an OEM may write a driver for the
            hardware on their particular platform.

            Note that a dedicated debug Ethernet controller must be used, it
            cannot be shared with NDIS drivers in the OS.

            The Ethernet routines may be interrupt driven or may run in polling
            mode.  It is highly recommended to use interrupts for debug Ethernet,
            since polling can result in much greater system delays in the event
            that packets are dropped on the network.  The debug Ethernet ISR is
            much like other driver ISRs - it should be very small and typically
            will just mask the interrupt and return the corresponding SYSINTR
            value to the OS, which will handle the interrupt event internally.
            This means the Interrupt Service Thread (IST) does not need to be
            provided by the OEM - a call will be made to the OEMEthISR() function
            to perform the interrupt handling.

            Even though the model is interrupt driven, there are times when interrupts
            cannot be processed by the system (e.g. very early in boot, or within
            a device driver's power ON/OFF handler).  So, the OEM routines must be
            able to work in polled mode as well. In these situations, the EDBG subsystem
            will repeatedly call OEMEthGetFrame() when waiting for receive data, and
            use OEMEthGetSecs() to implement timeouts.

            All of the debug Ethernet routines (OEMEthxxx) are called in a restricted
            context, and may not make any system calls.  Delays must be accomplished
            by hardware timers, blocking or sleeping is not allowed.

--*/
#ifndef _HALETHER_H_
#define _HALETHER_H_

#include <pkfuncs.h>
#include <ethdbg.h>
#include <kitl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EdbgSend                KITLSend
#define EdbgRecv                KITLRecv
#define EdbgRegisterClient      KITLRegisterClient
#define EdbgDeregisterClient    KITLDeregisterClient
#define EdbgSetDebug            KITLSetDebug
#define OEMEthGetSecs           OEMKitlGetSecs

#ifndef _WINSOCKAPI_    // Don't collide with winsock.h
// These macros are machine dependent.  They convert the little endian representation used on
//  this CPU to the big endian format that is transmitted on the network.
#define htons( value ) ((UINT16)(((0x00FF&((UINT16)value)) << 8) | (((UINT16)((UINT16)value)) >> 8)))
#define ntohs( value ) htons( value )
#define htonl( value ) ((((ULONG)value) << 24) | ((0x0000FF00UL & ((ULONG)value)) << 8) | ((0x00FF0000UL & ((ULONG)value)) >> 8) | (((ULONG)value) >> 24))
#define ntohl( value ) htonl( value )
#endif // ndef _WINSOCKAPI_

//
//  Ethernet Maximum Transfer Unit, the max # of bytes in a single Ethernet frame
//  Max ether packet is 1518 bytes, but bump it up to 1520 to make it DWORD align.
//
//  NOTE: MTU MUST BE MULTIPLE OF 4
//
#define ETHER_MTU 1520

//
// The ethernet debug (EDBG) functions may be called via KernelIoControl if these IOCTLS are
// supported in OEMIoControl. Provide some functions to ease writing apps on top of EDBG.
//
_inline BOOL
CallEdbgRegisterClient(UCHAR *pId, char *ServiceName, UCHAR Flags, UCHAR WindowSize, UCHAR *pBufferPool)
{
    return KernelIoControl(IOCTL_EDBG_REGISTER_CLIENT, pId, Flags, ServiceName, WindowSize, (LPDWORD)pBufferPool);
}
_inline BOOL
CallEdbgDeregisterClient(UCHAR Id)
{
    return KernelIoControl(IOCTL_EDBG_DEREGISTER_CLIENT, NULL,Id,NULL,0,NULL);
}
_inline BOOL
CallEdbgRegisterDfltClient(UCHAR Service, UCHAR Flags, UCHAR **ppTxBuffer, UCHAR **ppRxBuffer)
{
    return KernelIoControl(IOCTL_EDBG_REGISTER_DFLT_CLIENT, (UCHAR *)ppTxBuffer, Service, (UCHAR *)ppRxBuffer, Flags, NULL);
}
_inline BOOL
CallEdbgSend(UCHAR Id, UCHAR *pUserData, DWORD dwUserDataLen)
{
    return KernelIoControl(IOCTL_EDBG_SEND, pUserData, Id, NULL, dwUserDataLen, NULL);
}
_inline BOOL
CallEdbgRecv(UCHAR Id, UCHAR *pRecvBuf, DWORD *pdwLen, DWORD Timeout)
{
    return KernelIoControl(IOCTL_EDBG_RECV, pRecvBuf, Id, pdwLen, Timeout, NULL);
}
_inline BOOL
CallKitlGetCapabilities(KITL_CAPABILITIES * const pkcCapabilities)
{
    BOOL bSuccess = FALSE;
    KITL_GET_CAPABILITIES_OUT kgcoOutParam = { (DWORD)kcUnknown };
    DWORD dwBytesReturned = 0;

    if (pkcCapabilities != NULL)
    {
        bSuccess = KernelIoControl(IOCTL_KITL_GET_CAPABILITIES, NULL, 0, &kgcoOutParam, sizeof(kgcoOutParam), &dwBytesReturned);

        if (bSuccess)
        {
            if (dwBytesReturned == sizeof(kgcoOutParam))
            {
                (*pkcCapabilities) = (KITL_CAPABILITIES) kgcoOutParam.dwCapabilities;
            }
            else
            {
                bSuccess = FALSE;
            }
        }
    }

    if ( (!bSuccess) && (pkcCapabilities != NULL) )
    {
        (*pkcCapabilities) = kcUnknown;
    }

    return bSuccess;
}
_inline BOOL
CallEdbgSetDebug(DWORD ZoneMask)
{
    return KernelIoControl(IOCTL_EDBG_SET_DEBUG, NULL, ZoneMask, NULL, 0, NULL);
}

// get KITL transport information. *pcbRead must hold the size of the buffer when calling.
// If the call return TRUE, *pcbRead will hold the size of data read.
_inline BOOL
CallKITLGetInfo (DWORD dwCode, LPVOID pData, LPDWORD pcbRead)
{
    return KernelIoControl (IOCTL_KITL_GET_INFO, NULL, dwCode, pData, *pcbRead, pcbRead);
}

// pre-defined CONTROL codes
#define KGI_HOSTADDR    0       // host IP address, DWORD
#define KGI_DEVADDR     1       // device IP address, DWORD
#define KGI_BAUDRATE    2       // baudrate, DWORD  (bandwidth if ether)
#define KGI_PORT        3       // port, DWORD (port number if ether, com port if serial)

_inline DWORD __KITLGetDWORD (DWORD dwCode)
{
    DWORD cbRead = sizeof (DWORD), dw;
    return CallKITLGetInfo (dwCode, &dw, &cbRead)? dw : 0;
}

#define KITLGetHostAddr()     __KITLGetDWORD (KGI_HOSTADDR)
#define KITLGetDevAddr()      __KITLGetDWORD (KGI_DEVADDR)
#define KITLGetBaudRate()     __KITLGetDWORD (KGI_BAUDRATE)
#define KITLGetPort()         __KITLGetDWORD (KGI_PORT)


/*
 * @struct EDBG_ADDR | Addressing info for the debug Ethernet subsystem
 *
 * For speed, all values are stored in net byte order (big endian).  Use the
 * htonl/ntohl/htons/ntohs macros to convert to/from local byte order.
 */
typedef struct _EDBG_ADDR {
    DWORD  dwIP;         // @field IP address (net byte order)
    USHORT wMAC[3];      // @field Ethernet address (net byte order)
    USHORT wPort;        // @field UDP port # (net byte order) - only used if appropriate

} EDBG_ADDR;


// Values for EDBG_ADAPTER.EdbgFlags
#define EDBG_FLAGS_STATIC_IP    0x00000001

#define DEFAULT_DHCP_LEASE  259200  // Number of seconds in 3 days.

// The following defs can be used for platforms which support multiple adapter types.
// Identifiers are provided here for drivers which are built in common\oak\drivers\ethdbg.
// Any platform specific adapter types can be identified based off of EDBG_ADAPTER_OEM.
#define EDBG_ADAPTER_SMC9000  0
#define EDBG_ADAPTER_NE2000   1
#define EDBG_ADAPTER_DEFAULT  2
#define EDBG_ADAPTER_DEC21140 3
#define EDBG_ADAPTER_RTL8139  4
#define EDBG_ADAPTER_DP83815  5
#define EDBG_ADAPTER_3C90X    6

#define EDBG_ADAPTER_OEM      16

#define EDBG_USB_RNDIS 'R'

#define EdbgOutputDebugString KITLOutputDebugString

#ifndef _WINSOCKAPI_    // Don't collide with winsock.h
char *inet_ntoa(DWORD dwIP);
DWORD inet_addr( char *pszDottedD );
#endif // ndef _WINSOCKAPI_

// Prototypes for Ethernet controller library functions
typedef BOOL   (*PFN_EDBG_INIT)(BYTE *pbBaseAddress, DWORD dwMultiplier, USHORT MacAddr[3]);
typedef void   (*PFN_EDBG_ENABLE_INTS)(void);
typedef void   (*PFN_EDBG_DISABLE_INTS)(void);
typedef UINT16 (*PFN_EDBG_GET_FRAME)(BYTE *pbData, UINT16 *pwLength );
typedef UINT16 (*PFN_EDBG_SEND_FRAME)(BYTE *pbData, DWORD dwLength );
typedef void   (*PFN_EDBG_CURRENT_PACKET_FILTER)(DWORD dwFilter);
typedef BOOL   (*PFN_EDBG_MULTICAST_LIST)(PUCHAR pucMulticastAddresses, DWORD   dwNoOfAddresses);
typedef BOOL   (*PFN_EDBG_INIT_DMABUFFER)(ULONG StartAddress, ULONG Size);

// Prototypes for the EBOOT.LIB functions
UINT16 EbootInitDHCP( EDBG_ADDR *pMyAddr );
BOOL   EbootSendUDP(BYTE *pFrameBuffer, EDBG_ADDR *pDestAddr, EDBG_ADDR *pSrcAddr, BYTE *pData, UINT16 cwLength);
UINT16 EbootProcessARP( EDBG_ADDR *pMyAddr, BYTE *pFrameBuffer );
// Return codes from EbootProcessARP
#define PROCESS_ARP_IGNORE       0
#define PROCESS_ARP_REQUEST      1
#define PROCESS_ARP_REQUEST_ERR  2 // EbootProcessARP failed to send response
#define PROCESS_ARP_RESPONSE     3 // Some other station has our IP address

UINT16 EbootGratuitousARP( EDBG_ADDR *pMyAddr, BYTE *pFrameBuffer );

UINT16 EbootProcessDHCP( EDBG_ADDR *pMyAddr, DWORD *pSubnetMask, BYTE *pbData, WORD cwLength, DWORD *pLease, BOOL *pfwDHCPComplete );
UINT16 EbootDHCPRetransmit( EDBG_ADDR *pMyAddr, EDBG_ADDR *pSrcAddr, UCHAR *pFrame );
UINT16 EbootCheckUDP(EDBG_ADDR *pMyAddr, BYTE *pFrameBuffer, UINT16 *wDestPort, UINT16 *wSrcPort, UINT16 **pwData, UINT16 *cwLength );
BOOL   EbootProcessEDBG(EDBG_ADDR *pMyAddr, EDBG_ADDR *pEshellHost, BYTE *pFrameBuffer,
                        UINT16 *pwUDPData, UINT16 cwUDPDataLength,BOOL *pfJump, EDBG_OS_CONFIG_DATA **ppCfgData);
void   EbootSendBootme(EDBG_ADDR *pMyAddr, UCHAR VersionMajor, UCHAR VersionMinor, char *szPlatformString, char *szDeviceName, UCHAR CPUId, DWORD dwBootFlags);
BOOL   EbootReadSerialIP( EDBG_ADDR *pMyAddr, DWORD *pSubnetMask);
void EbootInitTFtp( UINT16 wOdoWKSP, UINT16 wHostWKSP );
void   EbootInitTFtpd( void );
// These are the various operations that may be passed to the registered callback function by the
//  server process.  Their descriptions are:
typedef enum {
    TFTPD_OPEN,     // A new link has just been requested
    TFTPD_READ,     // The link is requesting more data
    TFTPD_WRITE,    // The link is delivering data
    TFTPD_DESTROY   // An error occurred which as forced termination of the link
} TFtpdCallBackOps;
typedef UINT16 (*TFtpdCallBackFunc)( char *pszFileName, TFtpdCallBackOps Operation, BYTE *pbData, UINT16 *cwLength, char **ppszErrorMsg );
UINT16 EbootTFtpdServerRegister( char *pszFileName, TFtpdCallBackFunc pfCallBack );
WORD EbootTFtpReceiver( EDBG_ADDR *pMyAddr, BYTE *pFrameBuffer, UINT16 wDestPort, UINT16 wSrcPort, UINT16 *pwUDPData, UINT16 cwUDPDataLength );

// Simplified Eboot routines (single-threaded only)
// The intend is to hide all the ether details behind the scene for bootloader development.
// The bootloader can be reduced to the following using the following routine.
//
//      if (!EbootInitEtherTransport (....)) {
//          while (1);  // spin forever
//      }
//      // main loop of download
//      While (EbootEtherReadData (...)) {
//          // process the data
//          ProcessData (...);
//      }
//      // download complete, wait for host to connect
//      pCfgData = EbootWaitForHostConnect (...);
//
// For real implementation, please refer to sources under platform\ODO\eboot.
//
BOOL EbootInitEtherTransport (EDBG_ADDR *pEdbgAddr, LPDWORD pdwSubnetMask,
                              BOOL *pfJumpImg,         // will be set to TRUE if eshell asked us to jump to existing image
                              DWORD *pdwDHCPLeaseTime, // this parameter is overloaded. pass NULL to indicate static IP
                              UCHAR VersionMajor, UCHAR VersionMinor,
                              char *szPlatformString, char *szDeviceName,
                              UCHAR CPUId, DWORD dwBootFlags);
BOOL EbootEtherReadData (DWORD cbData, LPBYTE pbData);
EDBG_OS_CONFIG_DATA *EbootWaitForHostConnect (EDBG_ADDR *pDevAddr, EDBG_ADDR *pHostAddr);

//
// other simplified routines:
//

// Obtain DHCP address.
BOOL EbootGetDHCPAddr (EDBG_ADDR *pEdbgAddr, DWORD *pdwSubnetMask, DWORD *pdwDHCPLeaseTime);


// Indexes we use to get IP and Mac Addresses (via the KernelIOControl service)
#define IPINFO_ODO              0
#define IPINFO_DOWNLOAD         1
#define IPINFO_DEBUGMSG         2
#define IPINFO_KDEBUG           3
#define IPINFO_ESHELL           4

// Structure returned from IOCTL_HAL_GET_IP_ADDR
typedef struct _IP_INFO {
    UINT32      dwIP;               // The IP Address
    BYTE        MAC[6];             // The MAC address.
} IP_INFO, *PIP_INFO;



// Define some standard ports we use.
// NOTE: The following port is reserved thru the IANA for use
// by the remote replication agent.  They only use it over TCP
// Use only for UDP, 5679 is also available for UDP...
#define ETHER_STAT_PORT         5678

#define  OPT_BROADCAST_FILTERING  0x0001   // Filter out broadcast packets (except ARP packets)

//
// KITL Ether functions (in public\common\oak\drivers\ethdbg\kitl)
//
BOOL KitlEtherInit (EDBG_ADDR *pDevAddr, DWORD dwDHCPLeaseTime);
BOOL KitlEtherEncodeUDP (LPBYTE pbFrame, USHORT cbData);
LPBYTE KitlEtherDecodeUDP (LPBYTE pbFrame, PUSHORT pcbData);
UCHAR KitlEtherGetFrameHdrSize (void);
BOOL KitlEthGetInfo (DWORD dwCode, LPVOID lpData, LPDWORD pcbData);

#ifdef __cplusplus
}
#endif


#endif // _HALETHER_H_
