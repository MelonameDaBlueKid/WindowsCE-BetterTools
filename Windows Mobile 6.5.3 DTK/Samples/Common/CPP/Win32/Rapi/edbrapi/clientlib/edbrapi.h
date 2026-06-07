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
//     edbrapi.h
//
// Purpose:
//
//    EDB structures & constants included in windbase.h, windbase_edb.h, 
//    but not included in rapi.h
//    
// --------------------------------------------------------------------------

#ifndef EDB
#define EDB
#endif

#if !defined(CCH_MAX_PASSWORD)
#define CCH_MAX_PASSWORD             40
#endif

#ifdef CEDB_MAXDBASENAMELEN 
#undef CEDB_MAXDBASENAMELEN 
#endif

#ifdef CEDB_MAXSORTORDER
#undef CEDB_MAXSORTORDER
#endif

//copy from windbase.h
//--------------------------------------------------------------------------
// New for EDB
#define DB_CEOID_CREATED            (WM_USER + 0x1)
#define DB_CEOID_DATABASE_DELETED   (WM_USER + 0x2)
#define DB_CEOID_RECORD_DELETED     (WM_USER + 0x3)
#define DB_CEOID_FILE_DELETED       (WM_USER + 0x4)
#define DB_CEOID_DIRECTORY_DELETED  (WM_USER + 0x5)
#define DB_CEOID_CHANGED            (WM_USER + 0x6)

#ifdef EDB
#define DB_NOTIFY_VOLUME_CHANGED               (WM_USER+0x8)
#define DB_NOTIFY_RECORD_CREATED               (DB_CEOID_CREATED)
#define DB_NOTIFY_RECORD_CHANGED               (DB_CEOID_CHANGED)
#define DB_NOTIFY_RECORD_DELETED               (DB_CEOID_RECORD_DELETED)
#endif

#define CEDB_SORT_IGNORENONSPACE    0x00000010  //CEDB
#define CEDB_SORT_IGNORESYMBOLS     0x00000020  //CEDB
#define CEDB_SORT_IGNOREKANATYPE    0x00000040  //CEDB
#define CEDB_SORT_IGNOREWIDTH       0x00000080  //CEDB
#define CEDB_SORT_STRINGSORT        0x00000100
#define CEDB_SORT_UNIQUE            0x00000200 
#define CEDB_SORT_NONNULL           0x00000400  


#ifdef EDB
#define CEDB_SORT_NO_POSITIONAL     (0x00000800)
#define CEDB_SORT_PRIMARYKEY        ((0x00001000) | CEDB_SORT_UNIQUE)
#endif

#ifndef EDB
#define CEDB_MAXSORTPROP 3
#else
#define CEDB_MAXSORTPROP 16
#endif

#ifndef EDB
#define SORTORDERSPECEX_VERSION 1
#else
#define SORTORDERSPECEX_VERSION 2
#endif

#ifndef EDB
#define CEDB_MAXDBASENAMELEN                32
#else
#define CEDB_MAXDBASENAMELEN                 128
#endif

#ifndef EDB
#define CEDB_MAXSORTORDER    4
#else
#define CEDB_MAXSORTORDER    16
#endif

typedef struct _SORTORDERSPECEX {
    WORD      wVersion;    
    WORD      wNumProps;   
    WORD      wKeyFlags;   
    WORD      wReserved;   
    CEPROPID  rgPropID[CEDB_MAXSORTPROP]; 
    DWORD     rgdwFlags[CEDB_MAXSORTPROP]; 
} SORTORDERSPECEX, *PSORTORDERSPECEX;

#ifndef EDB
#define CEDBASEINFOEX_VERSION 1
#else
#define CEDBASEINFOEX_VERSION 2
#endif

#define CEDB_SYSTEMDB      0x00020000  //only CEDB

typedef struct _CEDBASEINFOEX {
    WORD     wVersion;          
    WORD     wNumSortOrder;     
    DWORD    dwFlags;           
    WCHAR    szDbaseName[CEDB_MAXDBASENAMELEN]; 
    DWORD    dwDbaseType;       
    DWORD    dwNumRecords;      
    DWORD    dwSize;            
    FILETIME ftLastModified;    
    SORTORDERSPECEX rgSortSpecs[CEDB_MAXSORTORDER];  
} CEDBASEINFOEX, *PCEDBASEINFOEX;

#ifndef EDB
#define BY_HANDLE_DB_INFORMATION_VERSION 1
#else
#define BY_HANDLE_DB_INFORMATION_VERSION 2
#endif

typedef struct _BY_HANDLE_DB_INFORMATION {
    WORD     wVersion;          
    WORD     wReserved;         
    CEGUID   guidVol;           
    CEOID    oidDbase;          
    CEDBASEINFOEX infDatabase; 
} BY_HANDLE_DB_INFORMATION, *LPBY_HANDLE_DB_INFORMATION;


#ifdef EDB

#define CEDB_SEEK_PREFIX                        0x00000100
#define CEDB_SEEK_VALUEGREATEROREQUAL           0x00000200
#define CEDB_SEEK_VALUESMALLEROREQUAL           0x00000400

#define CEVT_STREAM                 (100)
#define CEVT_RECID                  (101)
#define CEVT_AUTO_I4                (102)
#define CEVT_AUTO_I8                (103)

#define CREATE_INVALIDEDBGUID(pguid)  memset((pguid), 0, sizeof(CEGUID)); *((LPBYTE)(pguid)) = 0xff

#endif

#define OBJTYPE_EDB         5

#ifndef EDB
#define CEOIDINFOEX_VERSION 1
#else
#define CEOIDINFOEX_VERSION 2
#endif

typedef struct _CEOIDINFOEX {
    WORD  wVersion;    
    WORD  wObjType;    
    union {
        CEFILEINFO    infFile;       
        CEDIRINFO     infDirectory;  
        CEDBASEINFOEX infDatabase;   
        CERECORDINFO  infRecord;     
    };
} CEOIDINFOEX,  *PCEOIDINFOEX;


//end of copy from windbase.h

//copy from windbase_edb.h

#define EDB_MOUNT_FLAG 0x80000000

#define DB_PROP_NOTNULL                         (0x00000001)
#define DB_PROP_COMPRESSED                      (0x00000002)


#define DBOPT_SESSION_MAX_CHANGES              (0x01)
#define DBOPT_SESSION_LOCK_TIMEOUT             (0x02)


typedef int CEDBISOLATIONLEVEL;

#define CEDB_ISOLEVEL_DEFAULT            1
#define CEDB_ISOLEVEL_READCOMMITTED      1
#define CEDB_ISOLEVEL_REPEATABLEREAD     2
#define CEDB_ISOLEVEL_SERIALIZABLE       3
#define CEDB_ISOLEVEL_LAST   CEDB_ISOLEVEL_SERIALIZABLE

#define CEDB_CB_MIN_BUFFER_POOL         0x00040000
#define CEDB_CB_MAX_BUFFER_POOL         0x10000000
#define CEDB_AUTO_SHRINK_OFF            0x0
#define CEDB_AUTO_SHRINK_THRESHOLD_MAX  100
#define CEDB_FLUSH_INTERVAL_MIN         1
#define CEDB_FLUSH_INTERVAL_MAX         1000
#define CEDB_C_MIN_MAX_NOTIFY_CHANGES   0
#define CEDB_C_MAX_MAX_NOTIFY_CHANGES   0xFFFFFFFF


#if !defined(CCH_MAX_PASSWORD)
#define CCH_MAX_PASSWORD             40
#endif

#define CEVOLUMEOPTIONS_VERSION 1

typedef struct _CEVOLUMEOPTIONS {
    WORD                wVersion;    
    DWORD               cbBufferPool;
    DWORD               dwAutoShrinkPercent;
    DWORD               dwFlushInterval;
    DWORD               cMaxNotifyChanges;
    DWORD               dwDefaultTimeout;
    WCHAR               wszPassword[CCH_MAX_PASSWORD + 1];
    DWORD               dwFlags;
} CEVOLUMEOPTIONS, *PCEVOLUMEOPTIONS;

#define CEDB_BUFFERPOOL         0x00000001

#define CEDB_AUTOSHRINKPERCENT  0x00000002

#define CEDB_FLUSHINTERVAL      0x00000004

#define CEDB_MAXNOTIFYCHANGES   0x00000008

#define CEDB_DEFAULTTIMEOUT     0x00000010

#define CEDB_PASSWORD           0x00000020

#define CEPROPSPEC_VERSION 1
typedef struct _CEPROPSPEC {
   WORD     wVersion;
   CEPROPID propid;
   DWORD    dwFlags;
   LPWSTR   pwszPropName;
   DWORD    cchPropName;
} CEPROPSPEC, *PCEPROPSPEC;

//end of copy from windbase_edb.h

