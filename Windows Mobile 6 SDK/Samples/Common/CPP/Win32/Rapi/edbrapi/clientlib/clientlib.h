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
// --------------------------------------------------------------------------
// Module:
//
//     Clientlib.h
//
// Purpose:
//
//    include file for Windows CE Remote API, especially for EDB applications
//    It is only included by clientlib project
// --------------------------------------------------------------------------

#define _ErrorLabel Error


#define CHR(hResult) \
    if (FAILED(hResult)) { hr = (hResult); goto _ErrorLabel;}


#define CPR(pPointer) \
    if (NULL == (pPointer)) { hr = (E_OUTOFMEMORY); goto _ErrorLabel;}


#define CBR(fBool) \
    if (!(fBool)) { hr = (E_FAIL); goto _ErrorLabel;}


#define EDB_MOUNTDBVOLEX_FNAME          TEXT("DevCeMountDBVolEx")
#define EDB_CREATEDBWITHPROPS_FNAME     TEXT("DevCeCreateDatabaseWithProps")
#define EDB_OIDGETINFOEX2_FNAME         TEXT("DevCeOidGetInfoEx2")
#define EDB_CREATESESSION_FNAME         TEXT("DevCeCreateSession")
#define EDB_OPENDBINSESSION_FNAME       TEXT("DevCeOpenDatabaseInSession")
#define EDB_GETDBSESSION_FNAME          TEXT("DevCeGetDatabaseSession")
#define EDB_FLUSHVOL_FNAME              TEXT("DevCeFlushDBVol")
#define EDB_WRITERECPROPS_FNAME         TEXT("DevCeWriteRecordProps")
#define EDB_CHANGEDBLCID_FNAME          TEXT("DevCeChangeDatabaseLCID")
#define EDB_SEEKDBEX_FNAME              TEXT("DevCeSeekDatabaseEx")
#define EDB_DELETEDBEX_FNAME            TEXT("DevCeDeleteDatabaseEx")
#define EDB_UNMOUNTDBVOL_FNAME          TEXT("DevCeUnmountDBVol")
#define EDB_ENUMDBVOLUMES_FNAME         TEXT("DevCeEnumDBVolumes")
#define EDB_READRECPROPSEX_FNAME        TEXT("DevCeReadRecordPropsEx")
#define EDB_ADDDBPROPS_FNAME            TEXT("DevCeAddDatabaseProps")
#define EDB_DELETEREC_FNAME             TEXT("DevCeDeleteRecord")
#define EDB_FINDFIRSTDBEX_FNAME         TEXT("DevCeFindFirstDatabaseEx")
#define EDB_FINDNEXTDBEX_FNAME          TEXT("DevCeFindNextDatabaseEx")
#define EDB_GETDBPROPS_FNAME            TEXT("DevCeGetDatabaseProps")
#define EDB_REMOVEDBPROPS_FNAME         TEXT("DevCeRemoveDatabaseProps")
#define EDB_GETDBINFOBYHANDLE_FNAME     TEXT("DevCeGetDBInformationByHandle")
#define EDB_SETDBINFO_FNAME             TEXT("DevCeSetDatabaseInfo")
#define EDB_FREENOTIFICATION_FNAME      TEXT("DevCeFreeNotification")
#define EDB_SETSESSIONOPT_FNAME         TEXT("DevCeSetSessionOption")
#define EDB_BEGINTRANSACTION_FNAME      TEXT("DevCeBeginTransaction")
#define EDB_ENDTRANSACTION_FNAME        TEXT("DevCeEndTransaction")
#define EDB_OPENSTREAM_FNAME            TEXT("DevCeOpenStream")
#define EDB_STREAMREAD_FNAME            TEXT("DevCeStreamRead")
#define EDB_STREAMSAVECHANGE_FNAME      TEXT("DecCeStreamSaveChanges")
#define EDB_STREAMSETSIZE_FNAME         TEXT("DevCeStreamSetSize")
#define EDB_STREAMSEEK_FNAME            TEXT("DevCeStreamSeek")
#define EDB_STREAMWRITE_FNAME           TEXT("DevCeStreamWrite")

BOOL CeEdbMountDBVolEx
(
    PCEGUID pGuid,
    LPWSTR lpwszDBVol,
    CEVOLUMEOPTIONS *pOptions,
    DWORD dwFlags 
);

BOOL CeEdbMountDBVol( PCEGUID pGuid, LPWSTR lpwszDBVol, DWORD dwFlags );

CEOID CeEdbCreateDatabaseWithProps
(
    PCEGUID pGuid,
    CEDBASEINFOEX* pInfo,
    DWORD cProps,
    CEPROPSPEC* prgProps
);

CEOID CeEdbCreateDatabaseEx2(PCEGUID pguid, CEDBASEINFOEX* pInfo);

BOOL CeEdbOidGetInfoEx2(PCEGUID pGuid, CEOID oid, CEOIDINFOEX* poidInfo);

HANDLE CeEdbCreateSession(CEGUID* pGuid);

HANDLE CeEdbOpenDatabaseInSession
(
    HANDLE hSession,
    PCEGUID pGuid, 
    PCEOID poid,
    LPWSTR lpwszName, 
    SORTORDERSPECEX* pSort, 
    DWORD dwFlags,
    CENOTIFYREQUEST* pRequest
);

HANDLE CeEdbGetDatabaseSession(HANDLE hDatabase);

BOOL CeEdbFlushDBVol(PCEGUID pGuid);

CEOID CeEdbWriteRecordProps
(
    HANDLE hDatabase, 
    CEOID oidRecord, 
    WORD cPropID, 
    CEPROPVAL* prgPropVal
);

VOID CeEdbChangeDatabaseLCID(PCEGUID pceguid, DWORD LCID);

CEOID CeEdbSeekDatabaseEx
(
    HANDLE hDatabase,
    DWORD dwSeekType, 
    DWORD dwValue, 
    WORD wNumVals,
    LPDWORD lpdwIndex
);

CEOID CeEdbSeekDatabase
( 
    HANDLE hDatabase, 
    DWORD dwSeekType, 
    DWORD dwValue, 
    LPDWORD lpdwIndex
);

BOOL CeEdbDeleteDatabaseEx(PCEGUID pGuid, CEOID oid);

BOOL CeEdbUnmountDBVol(PCEGUID pGuid);

BOOL CeEdbEnumDBVolumes(PCEGUID pGuid, LPWSTR pwszName, DWORD cchMaxName);

CEOID CeEdbReadRecordPropsEx
(
    HANDLE hDatabase, 
    DWORD dwFlags, 
    LPWORD lpcPropID,
    CEPROPID* prgPropID, 
    LPBYTE *lplpBuffer, 
    LPDWORD lpcbBuffer,
    HANDLE hHeap
);

CEOID CeEdbReadRecordProps
(
    HANDLE hDatabase, 
    DWORD dwFlags, 
    LPWORD lpcPropID,
    CEPROPID* prgPropID, 
    LPBYTE *lplpBuffer, 
    LPDWORD lpcbBuffer
);

BOOL CeEdbAddDatabaseProps
(
    PCEGUID pGuid,
    CEOID oidDb,
    DWORD cProps,
    CEPROPSPEC* prgProps
);

BOOL CeEdbDeleteRecord(HANDLE hDatabase, CEOID oidRecord);

HANDLE CeEdbFindFirstDatabaseEx(PCEGUID pGuid, DWORD dwDbaseType);

CEOID CeEdbFindNextDatabaseEx(HANDLE hEnum, PCEGUID pGuid);

BOOL CeEdbGetDatabaseProps 
(
    HANDLE hDatabase,
    LPWORD lpcPropID,
    CEPROPID* prgPropID,
    CEPROPSPEC* prgProps
);

BOOL CeEdbRemoveDatabaseProps
(
    PCEGUID pGuid,
    CEOID oidDb,
    DWORD cProps,
    CEPROPID* prgProps
);

BOOL CeEdbGetDBInformationByHandle(HANDLE hDbase, BY_HANDLE_DB_INFORMATION * lpDBInfo);

BOOL CeEdbSetDatabaseInfo(CEOID oidDbase, CEDBASEINFOEX* pNewInfo);

BOOL CeEdbFreeNotification(CENOTIFYREQUEST* pRequest, CENOTIFICATION* pNotification);

BOOL CeEdbSetSessionOption
(
    HANDLE hSession,
    ULONG ulOptionId,
    DWORD dwValue
);

BOOL CeEdbBeginTransaction(HANDLE hSession, CEDBISOLATIONLEVEL isoLevel);

BOOL CeEdbEndTransaction(HANDLE hSession, BOOL fCommit);

HANDLE CeEdbOpenStream
(
    HANDLE hDatabase,
    CEPROPID propid,
    DWORD dwMode
);

BOOL CeEdbStreamRead
(
    HANDLE hStream,
    LPBYTE lprgbBuffer,
    DWORD cbRead,
    LPDWORD lpcbRead
);

BOOL CeEdbStreamSaveChanges(HANDLE hStream);

BOOL CeEdbStreamSetSize(HANDLE hStream, DWORD cbSize);

BOOL CeEdbStreamSeek
(
    HANDLE hStream,
    DWORD cbMove,
    DWORD dwOrigin,
    LPDWORD lpcbNewOffset
);

BOOL CeEdbStreamWrite
(
    HANDLE hStream,
    LPBYTE lprgbBuffer,
    DWORD cbWrite,
    LPDWORD lpcbWritten
);

