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

mafdfunc.h

Abstract:  

Notes: 


--*/
  
#ifndef _MAFDFUNC_H_
#define _MAFDFUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(WINCEMACRO)
#error WINCEMACRO not defined __FILE__
#endif


#define     PMSocket IMPLICIT_DECL (SOCKHAND, SH_COMM, 2,       \
                    (DWORD AddressFamily,                       \
                     DWORD SocketType,                          \
                     DWORD Protocol,                            \
                     DWORD CatId,                               \
                     GUID *pProvId,                             \
                     DWORD cProvId))


#define     PMSelect IMPLICIT_DECL (DWORD, SH_COMM, 10,         \
                    (UINT                   ReadCount,          \
                     PPMSOCK_LIST           ReadList,           \
                     UINT                   cbReadList,         \
                     UINT                   WriteCount,         \
                     PPMSOCK_LIST           WriteList,          \
                     UINT                   cbWriteList,        \
                     UINT                   ExceptCount,        \
                     PPMSOCK_LIST           ExceptList,         \
                     UINT                   cbExceptList,       \
                     const struct timeval   *timeout))

  
#define     PMControl IMPLICIT_DECL (DWORD, SH_COMM, 3,         \
                    (DWORD      Protocol,                       \
                     DWORD      Action,                         \
                     LPVOID     pInputBuf,                      \
                     DWORD      cbInputBuf,                     \
                     LPVOID     pOutputBuf,                     \
                     DWORD      cbOutputBuf,                    \
                     LPDWORD    pcOutputBuf))


#define     PMEnumProtocolsW IMPLICIT_DECL (DWORD, SH_COMM, 4,  \
                     (LPDWORD   lpiProtocols,                   \
                      UINT      cbProtocols,                    \
                      LPVOID    lpProtocolBuf,                  \
                      UINT      cbProtocolBuf,                  \
                      LPDWORD   pcbBufferLen))

  
#define     AFDGetHostentByAttr IMPLICIT_DECL (DWORD, SH_COMM, 7,\
                    (LPSOCK_THREAD          pThread,            \
                     DWORD                  cbThread,           \
                     LPWSTR                 Name,               \
                     LPBYTE                 Address,            \
                     LPVOID                 pOptions,           \
                     DWORD                  cOptions))  

  
#define     AFDAddIPHostent IMPLICIT_DECL (DWORD, SH_COMM, 8,   \
                    (LPWSTR                 Hostname,           \
                     char                   **IpAddr,               \
                     LPWSTR                 Aliases,            \
                     LPFILETIME             lpFileTime))    

  
#define     RasIOControl IMPLICIT_DECL (DWORD, SH_COMM, 9,      \
                    (LPVOID                 hRasConn,           \
                     DWORD                  dwCode,             \
                     PBYTE                  pBufIn,             \
                     DWORD                  dwLenIn,            \
                     PBYTE                  pBufOut,            \
                     DWORD                  dwLenOut,           \
                     PDWORD                 pdwActualOut))
 

#define     AFDAddInterface IMPLICIT_DECL (DWORD, SH_COMM, 19,  \
                    (PTSTR                  pAdapter,           \
                     VOID                   *Nte,               \
                     DWORD                  CONTEXT,            \
                     int                    Flags,              \
                     uint                   IpAddr,             \
                     uint                   SubnetMask,         \
                     int                    cDns,               \
                     uint                   *pDns,              \
                     int                    cWins,              \
                     uint                   *pWins))


#define     RasDial IMPLICIT_DECL (DWORD, SH_COMM, 5,           \
                    (LPRASDIALEXTENSIONS    dialExtensions,     \
                     DWORD                  cbDialExtensions,   \
                     LPTSTR                 phoneBookPath,      \
                     LPRASDIALPARAMS        rasDialParam,       \
                     DWORD                  cbRasDialParam,     \
                     DWORD                  NotifierType,       \
                     DWORD                  notifier,           \
                     LPHRASCONN             pRasConn))  

#define     RasHangup IMPLICIT_DECL (DWORD, SH_COMM, 6,         \
                    (HRASCONN               Session))   

#define     RasEnumEntries IMPLICIT_DECL (DWORD, SH_COMM, 11,   \
                    (LPWSTR                 Reserved,           \
                     LPWSTR                 lpszPhoneBookPath,  \
                     LPRASENTRYNAME         lprasentryname,     \
                     DWORD                  cbrasentryname,     \
                     LPDWORD                lpcb,               \
                     LPDWORD                lpcEntries))
                                    
#define     RasGetEntryDialParams IMPLICIT_DECL (DWORD, SH_COMM, 12,\
                    (LPWSTR                 lpszPhoneBook,      \
                     LPRASDIALPARAMS        lpRasDialParams,    \
                     DWORD                  cbRasDialParam,     \
                     LPBOOL                 lpfPassword))

#define     RasSetEntryDialParams IMPLICIT_DECL (DWORD, SH_COMM, 13,\
                    (LPWSTR                 lpszPhoneBook,      \
                     LPRASDIALPARAMS        lpRasDialParams,    \
                     DWORD                  cbRasDialParam,     \
                     BOOL                   fRemovePassword))

#define     RasGetEntryProperties IMPLICIT_DECL (DWORD, SH_COMM, 14,\
                    (LPWSTR                 lpszPhoneBook,      \
                     LPWSTR                 szEntry,            \
                     LPBYTE                 lpbEntry,           \
                     DWORD                  cbEntry,            \
                     LPDWORD                lpdwEntrySize,      \
                     LPBYTE                 lpb,                \
                     DWORD                  cbDeviceInfo,       \
                     LPDWORD                lpdwSize))
                                    
#define     RasSetEntryProperties IMPLICIT_DECL (DWORD, SH_COMM, 15,\
                    (LPWSTR                 lpszPhoneBook,      \
                     LPWSTR                 szEntry,            \
                     LPBYTE                 lpbEntry,           \
                     DWORD                  dwEntrySize,        \
                     LPBYTE                 lpb,                \
                     DWORD                  dwSize))

#define     RasValidateEntryName IMPLICIT_DECL (DWORD, SH_COMM, 16, \
                    (LPWSTR                 lpszPhonebook,      \
                     LPWSTR                 lpszEntry))

#define     RasDeleteEntry IMPLICIT_DECL (DWORD, SH_COMM, 17,   \
                    (LPWSTR                 lpszPhonebook,      \
                     LPWSTR                 lpszEntry))

#define     RasRenameEntry IMPLICIT_DECL (DWORD, SH_COMM, 18,   \
                    (LPWSTR                 lpszPhonebook,      \
                     LPWSTR                 lpszOldEntry,       \
                     LPWSTR                 lpszNewEntry))
                                    
#define     RasEnumConnections IMPLICIT_DECL (DWORD, SH_COMM, 20,   \
                    (LPRASCONN              lprasconn,              \
                       DWORD                cbRasConn,              \
                     LPDWORD                lpcb,                   \
                     LPDWORD                lpcConnections))

#define     RasGetConnectStatus IMPLICIT_DECL (DWORD, SH_COMM, 21,  \
                    (HRASCONN               rasconn,                \
                     LPRASCONNSTATUS        lprasconnstatus,        \
                     DWORD                  cbrasconnstatus))

#define     RasGetEntryDevConfig IMPLICIT_DECL (DWORD, SH_COMM, 22, \
                    (LPCTSTR                szPhonebook,            \
                     LPCTSTR                szEntry,                \
                     LPDWORD                pdwDeviceID,            \
                     LPDWORD                pdwSize,                \
                     LPVARSTRING            pDeviceConfig,          \
                     DWORD                  cbDeviceConfig))

#define     RasSetEntryDevConfig IMPLICIT_DECL (DWORD, SH_COMM, 23, \
                    (LPCTSTR                szPhonebook,            \
                     LPCTSTR                szEntry,                \
                     DWORD                  dwDeviceID,             \
                     LPVARSTRING            lpDeviceConfig,         \
                     DWORD                  cbDeviceConfig))

#define     NETbios IMPLICIT_DECL (DWORD, SH_COMM, 24,      \
                    (DWORD              x1,                 \
                     DWORD              dwOpCode,           \
                     PVOID              pNCB,               \
                     DWORD              cBuf1,              \
                     PBYTE              pBuf1,              \
                     DWORD              cBuf2,              \
                     PDWORD             pBuf2))


#define PROV_OFFSET 25

#define PMInstallProvider IMPLICIT_DECL (DWORD, SH_COMM, PROV_OFFSET + 1,       \
                    (LPGUID             lpProviderId,               \
                    const WCHAR         *lpszProviderDllPath,       \
                    const LPWSAPROTOCOL_INFOW   lpProtocolInfoList, \
                    DWORD               cbProtocolInfoList,         \
                    DWORD               dwNumberOfEntries,          \
                    DWORD               Flags))

#define PMEnumProtocols IMPLICIT_DECL (DWORD, SH_COMM, PROV_OFFSET + 2, \
                    (LPINT              lpiProtocols,       \
                    LPWSAPROTOCOL_INFOW lpProtocolBuffer,   \
                    DWORD               cbBuffer,   \
                    PDWORD              lpdwBufferLength,   \
                    PDWORD              lpdwFlags,          \
                    LPINT               lpErrno))

#define PMFindProvider IMPLICIT_DECL  (DWORD, SH_COMM, PROV_OFFSET + 3, \
                    (int            af,                     \
                    int             type,                   \
                    int             protocol,               \
                    DWORD           dwCatalogEntryId,       \
                    IN DWORD        dwFlags,                \
                    OUT LPWSAPROTOCOL_INFOW lpProtocolInfo, \
                    IN DWORD        cbProtocolInfo,         \
                    OUT PWSTR       psPath,                 \
                    IN DWORD        cbPath))

#define PMInstallNameSpace IMPLICIT_DECL (DWORD, SH_COMM, PROV_OFFSET + 4,  \
                    (LPWSTR             lpszIdentifier,     \
                    LPWSTR              lpszPathName,       \
                    DWORD               dwNameSpace,        \
                    DWORD               dwVersion,          \
                    LPGUID              lpProviderId,       \
                    PDWORD              pFlags))

#define PMEnumNameSpaceProviders IMPLICIT_DECL  (DWORD, SH_COMM, PROV_OFFSET + 5,   \
                    (PDWORD                 pcBuf,          \
                    LPWSANAMESPACE_INFOW    pBuf,           \
                    DWORD                   cBuf,           \
                    PDWORD                  pFlags,         \
                    int                     *pErr))

#define PMFindNameSpaces IMPLICIT_DECL  (DWORD, SH_COMM, PROV_OFFSET + 6,   \
                    (WSAQUERYSETW       *pQuery,                \
                    void                *pBuf,                  \
                    int                 cBuf,                   \
                    int                 *pcBuf,                 \
                    int                 *pErr))

#define PMAddrConvert IMPLICIT_DECL  (DWORD, SH_COMM, 32,   \
                    (DWORD              Op,                 \
                    DWORD               AddrFamily,         \
                    SOCKADDR            *pSockAddr,         \
                    DWORD               cSockAddr,          \
                    DWORD               *pcSockAddr,        \
                    LPWSAPROTOCOL_INFOW pProtInfo,          \
                    DWORD               cbProtInfo,         \
                    PWSTR               psAddr,             \
                    DWORD               cAddr,              \
                    DWORD               *pcAddr))

#define AFDDnsQuery_W IMPLICIT_DECL (DWORD, SH_COMM, 33,    \
                     (PCWSTR            pszName,            \
                      WORD              wType,              \
                      DWORD             Options,            \
                      PIP4_ARRAY        aipServers,         \
                      DWORD             cbServers,          \
                      PDNS_RECORD       *ppQueryResults,    \
                      PVOID             *pReserved))

#define AfdDNSRecordListFree IMPLICIT_DECL (void, SH_COMM, 34, \
                             (PDNS_RECORD pRecordList,         \
                             DNS_FREE_TYPE FreeType))

#define AFD_UpdateOrModifyRecords IMPLICIT_DECL (DWORD, SH_COMM, 35, \
                     (PDNS_RECORD       pAddRecords,        \
                      PDNS_RECORD       pDeleteRecords,     \
                      DWORD             Options,            \
                      HANDLE            hContext,           \
                      PIP4_ARRAY        pServerList,        \
                      DWORD             cbServers,          \
                      PVOID             pReserved,          \
                      BOOL              fReplace))

#define WINSOCK_CALL(type, api, args)   (*(type (*) args)IMPLICIT_CALL(HT_SOCKET, api))




#define PMAccept WINSOCK_CALL (DWORD, 2,        \
           (UINT            ListeningSocket,    \
            UINT            *phAcceptedSock,    \
            PSOCKADDR       pAddr,              \
            DWORD           cbAddr,             \
            DWORD           *pcbAddr,           \
            LPCONDITIONPROC pfnCondition,       \
            DWORD           CallbackData))


#define PMBind WINSOCK_CALL (DWORD, 3,      \
           (UINT            hPmSock,        \
            PSOCKADDR       pAddr,          \
            DWORD           cbAddr))


#define PMConnect WINSOCK_CALL (DWORD, 4,   \
           (UINT            hPmSock,        \
            LPSOCKADDR      pAddr,          \
            DWORD           cbAddr))


#define PMIoctl WINSOCK_CALL (DWORD, 5,     \
           (UINT            hPmSock,        \
            DWORD           Code,           \
            VOID            *pInBuf,        \
            DWORD           cbInBuf,        \
            VOID            *pOutBuf,       \
            DWORD           cbOutBuf,       \
            DWORD           *pcbOutBuf,     \
            WSAOVERLAPPED   *pOv,           \
            DWORD           cbOv,           \
            LPWSAOVERLAPPED_COMPLETION_ROUTINE pCompRtn,   \
            LPWSATHREADID   pThreadId))


#define PMListen WINSOCK_CALL (DWORD, 6,    \
           (UINT            hPmSock,        \
            DWORD           Backlog))


#define PMRecv WINSOCK_CALL (DWORD, 7,      \
           (UINT            hPmSock,        \
            WSABUF          *pWsaBufs,      \
            DWORD           cWsaBufs,       \
            DWORD           *pcbRcvd,       \
            DWORD           *pFlags))


#define PMRecvFrom WINSOCK_CALL (DWORD, 8,  \
           (UINT            hPmSock,        \
            WSABUF          *pWsaBufs,      \
            DWORD           cWsaBufs,       \
            DWORD           *pcbRcvd,       \
            DWORD           *pFlags,        \
            LPSOCKADDR      pAddr,          \
            DWORD           cbAddr,         \
            DWORD           *pcbAddr))


#define PMRecvEx WINSOCK_CALL (DWORD, 9,    \
           (UINT            hPmSock,        \
            WSABUF          *pWsaBufs,      \
            DWORD           cWsaBufs,       \
            DWORD           *pcbRcvd,       \
            DWORD           *pFlags,        \
            PSOCKADDR       pAddr,          \
            DWORD           cbAddr,         \
            DWORD           *pcbAddr,       \
            WSAOVERLAPPED   *pOv,           \
            LPWSAOVERLAPPED_COMPLETION_ROUTINE pCompRtn,    \
            LPWSATHREADID   pThreadId,         \
            WSABUF          *pControl))


#define PMSend WINSOCK_CALL (DWORD, 10,     \
           (UINT            hPmSock,        \
            WSABUF          *pWsaBufs,      \
            DWORD           cWsaBufs,       \
            DWORD           *pcbSent,       \
            DWORD           Flags))


#define PMSendTo WINSOCK_CALL (DWORD, 11,   \
           (UINT            hPmSock,        \
            WSABUF          *pWsaBufs,      \
            DWORD           cWsaBufs,       \
            DWORD           *pcbSent,       \
            DWORD           Flags,          \
            LPSOCKADDR      pAddr,          \
            DWORD           cbAddr))


#define PMSendEx WINSOCK_CALL (DWORD, 12,   \
           (UINT            hPmSock,        \
            WSABUF          *pWsaBufs,      \
            DWORD           cWsaBufs,       \
            DWORD           *pcbSent,       \
            DWORD           Flags,          \
            PSOCKADDR       pAddr,          \
            DWORD           cbAddr,         \
            WSAOVERLAPPED   *pOv,           \
            LPWSAOVERLAPPED_COMPLETION_ROUTINE pCompRtn,    \
            LPWSATHREADID   pThreadId))

         
#define PMShutdown WINSOCK_CALL (DWORD, 13, \
           (UINT            hPmSock,        \
            DWORD           How))


#define PMGetsockname WINSOCK_CALL (DWORD, 14,      \
           (UINT            hPmSock,                \
            LPSOCKADDR      Address,                \
            DWORD           cAddr,                  \
            LPDWORD         pcAddr))


#define PMGetpeername WINSOCK_CALL (DWORD, 15,      \
           (UINT            hPmSock,                \
            LPSOCKADDR      Address,                \
            DWORD           cAddr,                  \
            LPDWORD         pcAddr))


#define PMGetSockOpt WINSOCK_CALL (DWORD, 16,       \
           (UINT            hPmSock,                \
            DWORD          Level,                   \
            DWORD          OptionName,              \
            LPVOID         Buffer,                  \
            DWORD          cBuf,                    \
            LPDWORD        pcBuf))


#define PMSetSockOpt WINSOCK_CALL (DWORD, 17,       \
           (UINT            hPmSock,                \
            DWORD           Level,                  \
            DWORD           OptionName,             \
            LPVOID          Buffer,                 \
            DWORD           BufferLength))


#define PMWakeup WINSOCK_CALL (DWORD, 18,           \
           (UINT            hPmSock,                \
            DWORD           Event,                  \
            DWORD           Status))


#define PMGetOverlappedResult WINSOCK_CALL (DWORD, 19,  \
           (UINT            hPmSock,                \
            WSAOVERLAPPED   *pOv,                   \
            DWORD           *pcTransfer,            \
            DWORD           fWait,                  \
            DWORD           *pFlags,                \
            DWORD           *pErr))


#define PMEventSelect WINSOCK_CALL (DWORD, 20,      \
           (UINT            hPmSock,                \
            WSAEVENT        hEvent,                 \
            long            NetworkEvents))


#define PMEnumNetworkEvents WINSOCK_CALL (DWORD, 21,    \
           (UINT            hPmSock,                \
            WSAEVENT        hEvent,                 \
            LPWSANETWORKEVENTS  pNetworkEvents,     \
            DWORD           cbNetworkEvents))


#define PMCloseSocket WINSOCK_CALL (DWORD, 22,      \
           (UINT            hPmSock))


#define PMSendMsg WINSOCK_CALL (DWORD, 23,      \
           (UINT            hPmSock,            \
            WSAMSG          *pMsg,              \
            DWORD           cbMsg,              \
            DWORD           Flags,              \
            DWORD           *pcbSent,           \
            WSAOVERLAPPED   *pOv,               \
            LPWSAOVERLAPPED_COMPLETION_ROUTINE pCompRtn,    \
            LPWSATHREADID   pThreadId))


#ifdef __cplusplus
}
#endif

#endif // __MAFDFUNC.H
