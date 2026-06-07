/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

afdfunc.h

Abstract:

Functions exposed from the AFD system process

Notes: 


--*/

// @CESYSGEN IF CE_MODULES_AFD

#ifndef _AFDFUNC_H_
#define _AFDFUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SOCKHAND_DEFINED
DECLARE_HANDLE(SOCKHAND);
typedef SOCKHAND *PSOCKHAND;
#define SOCKHAND_DEFINED
#endif

#include "ras.h"
#include "tapi.h"

//
// Start WINCE API definitions.
//
DWORD WINAPI RasDial (LPRASDIALEXTENSIONS dialExtensions,
	       LPTSTR phoneBookPath,
	       LPRASDIALPARAMS rasDialParam,
	       DWORD NotifierType,
	       LPVOID notifier,
	       LPHRASCONN pRasConn);
DWORD WINAPI RasHangup (HRASCONN Session);	// Kept for historical compatibility
DWORD WINAPI RasHangUp (HRASCONN Session);
DWORD WINAPI RasEnumEntries (LPWSTR Reserved,
		      LPWSTR lpszPhoneBookPath,
		      LPRASENTRYNAME lprasentryname,
		      LPDWORD lpcb,
		      LPDWORD lpcEntries);
DWORD WINAPI RasGetEntryDialParams (LPWSTR lpszPhoneBook,
			     LPRASDIALPARAMS lpRasDialParams,
			     LPBOOL lpfPassword);
DWORD WINAPI RasSetEntryDialParams (LPWSTR lpszPhoneBook,
			     LPRASDIALPARAMS lpRasDialParams,
			     BOOL fRemovePassword);
DWORD WINAPI RasGetEntryProperties (LPWSTR lpszPhoneBook,
			     LPWSTR szEntry,
			     LPBYTE lpbEntry,
			     LPDWORD lpdwEntrySize,
			     LPBYTE lpb,
			     LPDWORD lpdwSize);
DWORD WINAPI RasSetEntryProperties (LPWSTR lpszPhoneBook,
			     LPWSTR szEntry,
			     LPBYTE lpbEntry,
			     DWORD dwEntrySize,
			     LPBYTE lpb,
			     DWORD dwSize);
DWORD WINAPI RasValidateEntryName (LPWSTR lpszPhonebook,
			    LPWSTR lpszEntry);
DWORD WINAPI RasDeleteEntry (LPWSTR lpszPhonebook,
		      LPWSTR lpszEntry);
DWORD WINAPI RasRenameEntry (LPWSTR lpszPhonebook,
		      LPWSTR lpszOldEntry,
		      LPWSTR lpszNewEntry);
DWORD WINAPI RasEnumConnections (LPRASCONN lprasconn,
			  LPDWORD lpcb,
			  LPDWORD lpcConnections);
DWORD WINAPI RasGetConnectStatus (HRASCONN rasconn,
			   LPRASCONNSTATUS lprasconnstatus);
DWORD WINAPI RasGetEntryDevConfig (LPCTSTR szPhonebook,
			    LPCTSTR szEntry,
			    LPDWORD pdwDeviceID,
			    LPDWORD pdwSize,
			    LPVARSTRING pDeviceConfig);
DWORD WINAPI RasSetEntryDevConfig (LPCTSTR szPhonebook,
			    LPCTSTR szEntry,
			    DWORD dwDeviceID,
			    LPVARSTRING lpDeviceConfig);

#ifdef __cplusplus
}
#endif

#ifdef WINCEOEM
#ifdef WINCEMACRO
#include <mafdfunc.h>	// macros
#endif
#endif

#endif  // _AFDFUNC_H_

// @CESYSGEN ENDIF
