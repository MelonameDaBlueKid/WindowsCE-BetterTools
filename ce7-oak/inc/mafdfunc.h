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

#if !defined(WINCEMACRO) && !defined(WINCEAFDMACRO) && !defined(WINCEWSPMMACRO)
#error WINCEMACRO not defined __FILE__
#endif

#if !defined(WINCEWSPMMACRO)
#define 	AFDSocket IMPLICIT_DECL (SOCKHAND, SH_COMM, 2,		\
  					(DWORD AddressFamily, 						\
  					 DWORD SocketType, 							\
  					 DWORD Protocol,							\
  					 DWORD CatId,								\
  					 GUID *pProvId))

#define		AFDSelect IMPLICIT_DECL (DWORD, SH_COMM, 10,		\
  					(UINT					ReadCount,			\
  					 LPSOCK_LIST			ReadList,			\
  					 UINT					WriteCount,			\
  					 LPSOCK_LIST			WriteList,			\
  					 UINT					ExceptCount,		\
  					 LPSOCK_LIST			ExceptList,			\
  					 const struct timeval	*timeout))

#endif
  
#define		AFDControl IMPLICIT_DECL (DWORD, SH_COMM, 3,    	\
  					(DWORD Protocol,                        	\
  					 DWORD Action,								\
  					 LPVOID InputBuffer,						\
  					 DWORD cInputBuf,							\
  					 LPVOID OutputBuffer,						\
  					 DWORD cOutputBuf,							\
  					 LPDWORD pcOutputBuf))
  
#define		AFDEnumProtocolsW IMPLICIT_DECL (DWORD, SH_COMM, 4, \
  					 (LPDWORD   lpiProtocols, 					\
  					  LPVOID	lpProtocolBuffer,				\
  					  LPDWORD	lpdwBufferLength))
  
#define		AFDGetHostentByAttr IMPLICIT_DECL (DWORD, SH_COMM, 7,\
  					(LPSOCK_THREAD 			pThread,			\
					 DWORD					cbThread,			\
  					 LPWSTR					Name,				\
  					 LPBYTE					Address,			\
  					 LPVOID					pOptions,			\
  					 DWORD					cOptions))	
  
#define		AFDAddIPHostent IMPLICIT_DECL (DWORD, SH_COMM, 8,	\
  					(LPWSTR		 			Hostname,			\
  					 char					**IpAddr,				\
  					 LPWSTR					Aliases,			\
  					 LPFILETIME				lpFileTime))	
  
#define		RasIOControl IMPLICIT_DECL (DWORD, SH_COMM, 9,		\
  					(LPVOID 				hRasConn,			\
  					 DWORD 					dwCode,				\
  					 PBYTE 					pBufIn,				\
  					 DWORD 					dwLenIn, 			\
  					 PBYTE 				    pBufOut, 			\
  					 DWORD 					dwLenOut,			\
  					 PDWORD					pdwActualOut))
 

#define		AFDAddInterface IMPLICIT_DECL (DWORD, SH_COMM, 19,	\
  					(PTSTR					pAdapter,			\
					 VOID					*Nte,				\
					 DWORD					CONTEXT,			\
					 int					Flags,				\
					 uint					IpAddr,				\
					 uint					SubnetMask,			\
					 int					cDns,				\
					 uint					*pDns,				\
					 int					cWins,				\
					 uint					*pWins))

#define		RasDial IMPLICIT_DECL (DWORD, SH_COMM, 5,			\
					(LPRASDIALEXTENSIONS 	dialExtensions,		\
                     DWORD                  cbDialExtensions,   \
					 LPTSTR		    		phoneBookPath,		\
					 LPRASDIALPARAMS    	rasDialParam,		\
                     DWORD                  cbRasDialParam,     \
					 DWORD		    		NotifierType,		\
					 DWORD		    		notifier,			\
					 LPHRASCONN	    		pRasConn))	


#define		RasHangup IMPLICIT_DECL (DWORD, SH_COMM, 6,			\
					(HRASCONN				Session))	

#define		RasEnumEntries IMPLICIT_DECL (DWORD, SH_COMM, 11,	\
					(LPWSTR					Reserved,			\
					 LPWSTR					lpszPhoneBookPath,	\
					 LPRASENTRYNAME			lprasentryname,		\
                     DWORD                  cbrasentryname,     \
					 LPDWORD				lpcb,				\
					 LPDWORD				lpcEntries))
					 				
#define		RasGetEntryDialParams IMPLICIT_DECL (DWORD, SH_COMM, 12,\
					(LPWSTR					lpszPhoneBook,		\
					 LPRASDIALPARAMS		lpRasDialParams,	\
                     DWORD                  cbRasDialParam,     \
					 LPBOOL					lpfPassword))

#define		RasSetEntryDialParams IMPLICIT_DECL (DWORD, SH_COMM, 13,\
					(LPWSTR					lpszPhoneBook,		\
					 LPRASDIALPARAMS		lpRasDialParams,	\
                     DWORD                  cbRasDialParam,     \
					 BOOL					fRemovePassword))

#define		RasGetEntryProperties IMPLICIT_DECL (DWORD, SH_COMM, 14,\
					(LPWSTR					lpszPhoneBook,		\
					 LPWSTR					szEntry,			\
					 LPBYTE					lpbEntry,			\
					 DWORD					cbEntry,			\
					 LPDWORD				lpdwEntrySize,		\
					 LPBYTE					lpb,				\
					 DWORD					cbDeviceInfo,		\
					 LPDWORD				lpdwSize))
					 				
#define		RasSetEntryProperties IMPLICIT_DECL (DWORD, SH_COMM, 15,\
					(LPWSTR					lpszPhoneBook,		\
					 LPWSTR					szEntry,			\
					 LPBYTE					lpbEntry,			\
					 DWORD					dwEntrySize,		\
					 LPBYTE					lpb,				\
					 DWORD					dwSize))

#define		RasValidateEntryName IMPLICIT_DECL (DWORD, SH_COMM, 16, \
					(LPWSTR					lpszPhonebook,		\
					 LPWSTR					lpszEntry))

#define		RasDeleteEntry IMPLICIT_DECL (DWORD, SH_COMM, 17,	\
					(LPWSTR					lpszPhonebook,		\
					 LPWSTR					lpszEntry))

#define		RasRenameEntry IMPLICIT_DECL (DWORD, SH_COMM, 18,	\
					(LPWSTR					lpszPhonebook,		\
					 LPWSTR					lpszOldEntry,		\
					 LPWSTR					lpszNewEntry))
					 				
#define		RasEnumConnections IMPLICIT_DECL (DWORD, SH_COMM, 20,	\
					(LPRASCONN				lprasconn,				\
					   DWORD				cbRasConn,				\
					 LPDWORD				lpcb,					\
					 LPDWORD				lpcConnections))

#define		RasGetConnectStatus IMPLICIT_DECL (DWORD, SH_COMM, 21,	\
					(HRASCONN				rasconn,				\
					 LPRASCONNSTATUS		lprasconnstatus,        \
					 DWORD            		cbrasconnstatus))

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

#define		NETbios IMPLICIT_DECL (DWORD, SH_COMM, 24,		\
					(DWORD				x1,					\
					 DWORD				dwOpCode,			\
					 PVOID				pNCB,				\
					 DWORD				cBuf1,				\
					 PBYTE				pBuf1,				\
					 DWORD				cBuf2,				\
					 PDWORD				pBuf2))

#define PMInstallProvider IMPLICIT_DECL (DWORD, SH_COMM, 26,		\
					(LPGUID				lpProviderId,				\
					const WCHAR FAR		*lpszProviderDllPath,		\
					const LPWSAPROTOCOL_INFOW	lpProtocolInfoList,	\
					DWORD				cbProtocolInfoList,			\
					DWORD				dwNumberOfEntries,			\
					DWORD				Flags))

#define PMEnumProtocols IMPLICIT_DECL (DWORD, SH_COMM, 27,	\
					(LPINT				lpiProtocols,		\
					LPWSAPROTOCOL_INFOW	lpProtocolBuffer,	\
					DWORD				cbBuffer,	\
					PDWORD				lpdwBufferLength,	\
					PDWORD				lpdwFlags,			\
					LPINT				lpErrno))

#define PMFindProvider IMPLICIT_DECL  (DWORD, SH_COMM, 28,	\
					(int			af,						\
					int				type, 					\
					int				protocol,				\
					DWORD			dwCatalogEntryId,		\
					IN DWORD		dwFlags,				\
					OUT LPWSAPROTOCOL_INFOW lpProtocolInfo, \
					IN DWORD		cbProtocolInfo,			\
					OUT PWSTR		psPath,					\
					IN DWORD		cbPath))

#define PMInstallNameSpace IMPLICIT_DECL (DWORD, SH_COMM, 29,	\
					(LPWSTR				lpszIdentifier,		\
					LPWSTR				lpszPathName,		\
					DWORD				dwNameSpace,		\
					DWORD				dwVersion,			\
					LPGUID				lpProviderId,		\
					PDWORD				pFlags))

#define PMEnumNameSpaceProviders IMPLICIT_DECL  (DWORD, SH_COMM, 30,	\
					(PDWORD					pcBuf,			\
					LPWSANAMESPACE_INFOW	pBuf, 			\
					DWORD					cBuf,			\
					PDWORD					pFlags,			\
					int						*pErr))


#define PMFindNameSpaces IMPLICIT_DECL  (DWORD, SH_COMM, 31,	\
					(WSAQUERYSETW		*pQuery,				\
					void				*pBuf,					\
					int					cBuf,					\
					int					*pcBuf,					\
					int					*pErr))


#define PMAddrConvert IMPLICIT_DECL  (DWORD, SH_COMM, 32,	\
					(DWORD				Op,					\
					DWORD				AddrFamily, 			\
					SOCKADDR			*pSockAddr,			\
					DWORD				cSockAddr,			\
					DWORD				*pcSockAddr,			\
					LPWSAPROTOCOL_INFOW	pProtInfo,		\
					DWORD				cbProtInfo,			\
					PWSTR				psAddr,				\
					DWORD				cAddr,			\
					DWORD				*pcAddr))


#ifdef __cplusplus
}
#endif

#endif // __MAFDFUNC.H
