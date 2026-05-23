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


Module Name:

    netlog.h

Abstract:

    retail data logger to allow CE to capture packets.
    Calls out to a helper DLL.

Environment:

    
--*/

#pragma once

// All work is done in the handler API.

typedef enum NetlogBTDataType
{
    NetlogBTTypeUnknown = 0,
    NetlogHCICommand = 1,
    NetlogACLData = 2,
    NetlogSCOData = 3,
    NetlogHCIEvent = 4,
    NetlogL2CAP = 5,
    NetlogText = 6
} NetlogBTDataType;

#ifndef __NETLOG_H
#define  __NETLOG_H

#ifdef __cplusplus 
extern "C" { 
#endif 

#include <windows.h>
#include <lss.h>
#include <ndis.h>
#include <cxport.h>

// Try to load the logging DLL.
// Invoked at startup and given an IOCTL.
BOOL LoadRetailLogger();

// Try to load the logging DLL.
// Invoked if given an IOCTL.
BOOL UnloadRetailLogger();

typedef
VOID (*LP_LOG_NDIS_SEND)(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_PACKET            Packet
    );

typedef
VOID (*LP_LOG_NDIS_SEND_PACKETS)(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    );

typedef
VOID
( *LP_LOG_NDIS_SEND_NET_BUFFER_LIST )(
    IN  PNDIS_HANDLE            MiniportAdapterHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  NDIS_PORT_NUMBER        PortNumber,
    IN  ULONG                   SendFlags,
    IN  NDIS_MEDIUM             MediaType
    );

typedef
VOID (*LP_LOG_NDIS_TX_WAN_PACKET)(
    PWSTR wszProtocolName,
    PWSTR wszStreamName,
    PWSTR wszPacketType,
    struct _NDIS_WAN_PACKET *Packet
    );

typedef
VOID (*LP_LOG_NDIS_RX_CONTIG_PACKET)(
    PWSTR wszProtocolName,
    PWSTR wszStreamName,
    PWSTR wszPacketType,
    PBYTE pPacket,
    DWORD cbPacket
    );

// For the IndicateReceivePackets Case
typedef VOID 
(*LP_LOG_MINIPORT_INDICATE_RECEIVE_PACKETS)(
    IN  PNDIS_MINIPORT_BLOCK    Miniport,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets,
    IN  NDIS_PHYSICAL_MEDIUM    Medium
                                           );
// For IndicateReceive
typedef VOID 
(*LP_LOG_MINIPORT_INDICATE_RECEIVE)(
    IN NDIS_STATUS              Status,
    IN  NDIS_HANDLE             MacReceiveContext,
    IN  PCHAR                   Address,
    IN  PVOID                   HeaderBuffer,
    IN  UINT                    HeaderBufferSize,
    IN  PVOID                   LookaheadBuffer,
    IN  UINT                    LookaheadBufferSize,
    IN  UINT                    PacketSize,
    IN  NDIS_PHYSICAL_MEDIUM    Medium
    );

typedef
VOID
( *LP_LOG_MINIPORT_INDICATE_RECEIVE_NET_BUFFER_LIST )(
    IN  PNDIS_HANDLE            MiniportAdapterHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  NDIS_PORT_NUMBER        PortNumber,
    IN  ULONG                   NumberOfNetBufferLists,
    IN  ULONG                   ReceiveFlags,
    IN  NDIS_MEDIUM             MediaType
    );

typedef VOID 
(*LP_LOG_NDIS_TRANSFER_DATA)(
    OUT PNDIS_PACKET            Packet,
    OUT PUINT                   BytesTransferred,
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HANDLE             MiniportReceiveContext,
    IN  UINT                    ByteOffset,
    IN  UINT                    BytesToTransfer
    );

typedef VOID
(*LP_LOG_EVENT)(
    IN  PSTR  szEvent);

typedef
VOID (*LP_LOG_BT_DATA)(
    IN  PSTR             szDirection,    
    IN  NetlogBTDataType DataType,
    IN  PBYTE            pData,
    IN  DWORD            cbData);

// Declared in cxport.
// Do not use directly use the accessor inline functions instead.


// When we're building   CXPORT  we don't need a declspec.
// When we're building anything else we need it.
#ifdef BUILD_CXPORT
#define  NL_DEC_SPEC  
#else
#define  NL_DEC_SPEC  __declspec(dllimport)
#endif 



NL_DEC_SPEC extern LP_LOG_NDIS_SEND                         g_pLogNdisSend;
NL_DEC_SPEC extern LP_LOG_NDIS_SEND_PACKETS                 g_pLogNdisSendPackets;
NL_DEC_SPEC extern LP_LOG_NDIS_SEND_NET_BUFFER_LIST         g_pLogNdisSendNetBufferLists;
NL_DEC_SPEC extern LP_LOG_NDIS_TRANSFER_DATA                g_pLogNdisTransferData;

NL_DEC_SPEC extern LP_LOG_MINIPORT_INDICATE_RECEIVE         g_pLogMiniportIndicateReceive;
NL_DEC_SPEC extern LP_LOG_MINIPORT_INDICATE_RECEIVE_PACKETS g_pLogMiniportIndicateReceivePackets;
NL_DEC_SPEC extern LP_LOG_MINIPORT_INDICATE_RECEIVE_NET_BUFFER_LIST  g_pLogMiniportIndicateReceiveNetBufferLists;

NL_DEC_SPEC extern LP_LOG_EVENT g_pLogEvent;
NL_DEC_SPEC extern LP_LOG_NDIS_TX_WAN_PACKET                g_pLogTxNdisWanPacket;
NL_DEC_SPEC extern LP_LOG_NDIS_RX_CONTIG_PACKET             g_pLogRxContigPacket;

NL_DEC_SPEC extern LP_LOG_BT_DATA                           g_pLogBTData;

#undef NL_DEC_SPEC

//////////////////////////////////////////////////////
//
// Here are the functions to be used in NDIS and PPP
//
//////////////////////////////////////////////////////

inline void  LogNdisSend(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_PACKET            Packet
    )
{
    if (g_pLogNdisSend)
    {
        g_pLogNdisSend(Status,NdisBindingHandle,Packet);
    }
    return ;
}

inline VOID LogNdisSendPackets(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    )
{
    if (g_pLogNdisSendPackets)
    {
        g_pLogNdisSendPackets(NdisBindingHandle,PacketArray,NumberOfPackets);
    }
}

inline
VOID
LogNdisSendNetBufferLists(
    IN  PNDIS_HANDLE            MiniportAdapterHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  NDIS_PORT_NUMBER        PortNumber,
    IN  ULONG                   SendFlags,
    IN  NDIS_MEDIUM             MediaType
    )
{
    if ( g_pLogNdisSendNetBufferLists )
    {
        g_pLogNdisSendNetBufferLists(
            MiniportAdapterHandle,
            NetBufferLists,
            PortNumber,
            SendFlags,
            MediaType
            );
    }
}  //  LogNdisSendNetBufferLists()

inline void  LogNdisTransferData(
    OUT PNDIS_PACKET            Packet,
    OUT PUINT                   BytesTransferred,
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HANDLE             MiniportReceiveContext,
    IN  UINT                    ByteOffset,
    IN  UINT                    BytesToTransfer
    )

{
    if (g_pLogNdisTransferData)
    {
        g_pLogNdisTransferData(Packet,BytesTransferred,MiniportAdapterContext,MiniportReceiveContext,ByteOffset,BytesToTransfer);
    }
}

inline void  LogMiniportIndicateReceive(
    IN  NDIS_STATUS              Status,
    IN  NDIS_HANDLE             MacReceiveContext,
    IN  PCHAR                   Address,
    IN  PVOID                   HeaderBuffer,
    IN  UINT                    HeaderBufferSize,
    IN  PVOID                   LookaheadBuffer,
    IN  UINT                    LookaheadBufferSize,
    IN  UINT                    PacketSize,
    IN  NDIS_PHYSICAL_MEDIUM    Medium
    )
{
    if (g_pLogMiniportIndicateReceive)
    {
        g_pLogMiniportIndicateReceive(
                Status,
                MacReceiveContext,
                Address,
                HeaderBuffer,
                HeaderBufferSize,
                LookaheadBuffer,
                LookaheadBufferSize,
                PacketSize,
                Medium );

    }
}

inline void  LogMiniportIndicateReceivePackets(
    IN  PNDIS_MINIPORT_BLOCK    Miniport,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets,
    IN  NDIS_PHYSICAL_MEDIUM    Medium)
{
    if (g_pLogMiniportIndicateReceivePackets)
    {
        g_pLogMiniportIndicateReceivePackets (
                Miniport,PacketArray,NumberOfPackets,Medium);

    }
}


inline
VOID
LogMiniportIndicateReceiveNetBufferLists(
    IN  PNDIS_HANDLE            MiniportAdapterHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  NDIS_PORT_NUMBER        PortNumber,
    IN  ULONG                   NumberOfNetBufferLists,
    IN  ULONG                   ReceiveFlags,
    IN  NDIS_MEDIUM             MediaType
    )
{
    if ( g_pLogMiniportIndicateReceiveNetBufferLists )
    {
        g_pLogMiniportIndicateReceiveNetBufferLists(
            MiniportAdapterHandle,
            NetBufferLists,
            PortNumber,
            NumberOfNetBufferLists,
            ReceiveFlags,
            MediaType            
            );
    }
}  //  LogMiniportIndicateReceiveNetBufferLists()


inline void  LogEvent(
    IN  PSTR szEvent)
{
    if (g_pLogEvent)
        g_pLogEvent(szEvent);
}

inline void
LogTxNdisWanPacket(
    PWSTR wszProtocolName,
    PWSTR wszStreamName,
    PWSTR wszPacketType,
    struct _NDIS_WAN_PACKET *Packet)
{
    if (g_pLogTxNdisWanPacket)
    {
        g_pLogTxNdisWanPacket(wszProtocolName, wszStreamName, wszPacketType, Packet);
    }
}

inline void
LogRxContigPacket(
    PWSTR wszProtocolName,
    PWSTR wszStreamName,
    PWSTR wszPacketType,
    PBYTE pPacket,
    DWORD cbPacket)
{
    if (g_pLogRxContigPacket)
    {
        g_pLogRxContigPacket(wszProtocolName, wszStreamName, wszPacketType, pPacket, cbPacket);
    }
}

inline void  LogBTData(
    PSTR             szDirection,    
    NetlogBTDataType PacketType,
    PBYTE            pData,
    DWORD            cbData)
{
    if (g_pLogBTData)
    {
        g_pLogBTData(szDirection, PacketType, pData, cbData);
    }
}

void 
AppendBTHCIFrame(
    PUCHAR              pDstFrame, 
    DWORD*              pcbDstFrame, 
    PUCHAR              pSrcFrame, 
    DWORD               cbSrc,
    NetlogBTDataType    Type,
    BOOL                bTx);


//
//  Define our IOCTL Interface.
//



enum NETLOG_IOCTL 
{
    // Dump all stats to debug out.
    IOCTL_NETLOG_LOAD = CXPORT_IOCTL_NETLOG_BASE ,
    IOCTL_NETLOG_UNLOAD,
    IOCTL_CXLOG_GET_MODULE_INFO,
    IOCTL_CXLOG_SET_FILTER
};

#ifdef __cplusplus 
}
#endif 

#endif // ifdef __NETLOG_H
