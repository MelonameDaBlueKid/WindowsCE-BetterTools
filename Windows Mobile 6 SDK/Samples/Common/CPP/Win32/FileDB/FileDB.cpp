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

#define EDB
#include <windows.h>
#include <windbase.h>

#define MAKEPROP(n,t)    ((n<<16)|CEVT_##t)

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)   (sizeof(a)/sizeof(a[0]))
#endif

#define PROPID_MASK      0x0000FFFF

// Store the volume globaly to make things easy 
CEGUID m_VolGUID;
WCHAR *pszDBVolName = L"MYTEST.EDB";
WCHAR *pszDBName = L"FileDB";

#ifdef EDB
HANDLE hSession;
#endif

#define PROPID_NAME  MAKEPROP(101,LPWSTR)
#define PROPID_SIZE  MAKEPROP(102,UI2)
#define PROPID_TIME  MAKEPROP(103,FILETIME)  
#define PROPID_ATTR  MAKEPROP(104,UI2)


// 
//
// void OutputMsg(WCHAR* format, ...)
//
// Outputs a message to the debug Output in Visual Studio.
//
void OutputMsg(WCHAR* format, ...)
{
    va_list arglist;
    WCHAR   szTemp[MAX_PATH];
    int     nLen;

    // Compose a single string using the input args
    va_start(arglist, format);
    nLen = _vsnwprintf(szTemp, MAX_PATH - 1, format, arglist);

    if (nLen >= 0) 
    {
        szTemp[nLen] = 0;
        OutputDebugString(szTemp);
    }
}


// 
//
// BOOL bPopulateDB(HANDLE hDB, BOOL bRandom)
//
// Put some stuff into our database..
//
BOOL PopulateDB(HANDLE hDB, BOOL bRandom)
{
    CEPROPVAL       props[4];
    DWORD           dwTotalRecords = 0;
    CEOID           oidRec;
    BOOL            fRet = TRUE;

    if(! hDB || INVALID_HANDLE_VALUE == hDB)
    {
        OutputMsg(L"ERROR: Null or invalid database handle\n");
        goto Cleanup;
    }

    WIN32_FIND_DATAW wfd;
    HANDLE hFind = FindFirstFile( L"\\*.*", &wfd);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            props[0].propid = PROPID_NAME;
            props[0].val.lpwstr = wfd.cFileName;
            props[0].wFlags = 0;
            
            props[1].propid = PROPID_SIZE;
            props[1].val.uiVal = (UINT)wfd.nFileSizeLow;
            props[1].wFlags = 0;

            props[2].propid = PROPID_TIME;
            props[2].val.filetime = wfd.ftCreationTime;
            props[2].wFlags = 0;
            
            props[3].propid = PROPID_ATTR;
            props[3].val.uiVal = (UINT)wfd.dwFileAttributes;
            props[3].wFlags = 0;

            OutputMsg( L"Adding record %s\r\n", wfd.cFileName);
            oidRec = CeWriteRecordProps(hDB, 0, 4, props);
            if (!(oidRec))
            {
                OutputMsg(L"CeWriteRecordProps failed error [%u]\n", GetLastError());
                fRet = FALSE;
                goto Cleanup;
            }
            dwTotalRecords++;
            
        } while(FindNextFile(hFind, &wfd));
    }

    OutputMsg(L"DBPlr wrote total: %d records\n", dwTotalRecords);

Cleanup:
    return fRet;
}

BOOL TestOids(PCEGUID pceguid, CEOID oid)
{
    BOOL fRet = TRUE;
    CEOIDINFO oidinfo;
    CEOIDINFOEX oidinfoex;
    
    oidinfoex.wVersion = CEOIDINFOEX_VERSION;
    if (CeOidGetInfoEx2(pceguid, oid, &oidinfoex)) {
        OutputMsg(L"CEOIDINFOEX.wObjType=%s (0x%04x)\n", 
                (OBJTYPE_INVALID == oidinfoex.wObjType) ? L"OBJTYPE_INVALID" : 
                (OBJTYPE_FILE == oidinfoex.wObjType) ? L"OBJTYPE_FILE" : 
                (OBJTYPE_DIRECTORY == oidinfoex.wObjType) ? L"OBJTYPE_DIRECTORY" :
                (OBJTYPE_DATABASE == oidinfoex.wObjType) ? L"OBJTYPE_DATABASE" :
                (OBJTYPE_RECORD == oidinfoex.wObjType) ? L"OBJTYPE_RECORD" : 
                L"????", oidinfoex.wObjType);
        switch(oidinfoex.wObjType)
        {
            case OBJTYPE_DATABASE:
                OutputMsg(L"\tCEDBASEINFOEX.dwFlags=0x%08x\n", oidinfoex.infDatabase.dwFlags);
                OutputMsg(L"\tCEDBASEINFOEX.szDbaseName=\"%s\"\n", oidinfoex.infDatabase.szDbaseName);
                OutputMsg(L"\tCEDBASEINFOEX.dwDbaseType=0x%08x\n", oidinfoex.infDatabase.dwDbaseType);
                OutputMsg(L"\tCEDBASEINFOEX.dwNumRecords=0x%04x\n", oidinfoex.infDatabase.dwNumRecords);
                OutputMsg(L"\tCEDBASEINFOEX.wNumSortOrder=0x%04x\n", oidinfoex.infDatabase.wNumSortOrder);
                OutputMsg(L"\tCEDBASEINFOEX.dwSize=0x%08x\n", oidinfoex.infDatabase.dwSize);
                // don't bother to print the modified time or sortspecs
                break;

            case OBJTYPE_RECORD:
                OutputMsg(L"\tCERECORDINFOEX.oidParent=0x%08x\n", oidinfoex.infRecord.oidParent);
                break;

            case OBJTYPE_INVALID:
            case OBJTYPE_FILE:
            case OBJTYPE_DIRECTORY:
            default:
                break;
        }
        

    } else {
        fRet = FALSE;
    }

    if (CeOidGetInfoEx(pceguid, oid, &oidinfo)) {
        OutputMsg(L"CEOIDINFO.wObjType=%s (0x%04x)\n", 
                (OBJTYPE_INVALID == oidinfo.wObjType) ? L"OBJTYPE_INVALID" : 
                (OBJTYPE_FILE == oidinfo.wObjType) ? L"OBJTYPE_FILE" : 
                (OBJTYPE_DIRECTORY == oidinfo.wObjType) ? L"OBJTYPE_DIRECTORY" :
                (OBJTYPE_DATABASE == oidinfo.wObjType) ? L"OBJTYPE_DATABASE" :
                (OBJTYPE_RECORD == oidinfo.wObjType) ? L"OBJTYPE_RECORD" : 
                L"????", oidinfo.wObjType);
        switch(oidinfo.wObjType)
        {
            case OBJTYPE_DATABASE:
                OutputMsg(L"\tCEDBASEINFO.dwFlags=0x%08x\n", oidinfo.infDatabase.dwFlags);
                OutputMsg(L"\tCEDBASEINFO.szDbaseName=\"%s\"\n", oidinfo.infDatabase.szDbaseName);
                OutputMsg(L"\tCEDBASEINFO.dwDbaseType=0x%08x\n", oidinfo.infDatabase.dwDbaseType);
                OutputMsg(L"\tCEDBASEINFO.wNumRecords=0x%04x\n", oidinfo.infDatabase.wNumRecords);
                OutputMsg(L"\tCEDBASEINFO.wNumSortOrder=0x%04x\n", oidinfo.infDatabase.wNumSortOrder);
                OutputMsg(L"\tCEDBASEINFO.dwSize=0x%08x\n", oidinfo.infDatabase.dwSize);
                // don't bother to print the modified time or sortspecs
                break;

            case OBJTYPE_RECORD:
                OutputMsg(L"\tCERECORDINFO.oidParent=0x%08x\n", oidinfo.infRecord.oidParent);
                break;

            case OBJTYPE_INVALID:
            case OBJTYPE_FILE:
            case OBJTYPE_DIRECTORY:
            default:
                break;
        }
        

    } else {
#ifndef EDB // only expect CeOidGetInfoEx2 to work on EDB
        fRet = FALSE;
#endif        
    }


    return fRet;
}


// 
// Simply create database
//
BOOL CreateDB(HANDLE *phDB, TCHAR *tszDBName)
{
    CEDBASEINFOEX     DBInfo;
    BOOL bRtn = TRUE;
    CEOID           DBOid=0 ;

    //  Fill in the DBInfo structure
    CREATE_SYSTEMGUID(&m_VolGUID);
    memset(&DBInfo, 0, sizeof(CEDBASEINFOEX)) ;
    DBInfo.wVersion = CEDBASEINFOEX_VERSION;
    DBInfo.dwFlags |= CEDB_VALIDDBFLAGS | CEDB_VALIDNAME | CEDB_VALIDSORTSPEC;
    DBInfo.wNumSortOrder = 3;
    DBInfo.rgSortSpecs[0].wVersion = SORTORDERSPECEX_VERSION;
    DBInfo.rgSortSpecs[0].wNumProps = 1;
    DBInfo.rgSortSpecs[0].wKeyFlags = 0;
    DBInfo.rgSortSpecs[0].rgPropID[0] = PROPID_NAME;
    DBInfo.rgSortSpecs[0].rgdwFlags[0] = CEDB_SORT_UNKNOWNFIRST;
    DBInfo.rgSortSpecs[1].wVersion = SORTORDERSPECEX_VERSION;
    DBInfo.rgSortSpecs[1].wNumProps = 1;
    DBInfo.rgSortSpecs[1].wKeyFlags = 0;
    DBInfo.rgSortSpecs[1].rgPropID[0] = PROPID_SIZE;
    DBInfo.rgSortSpecs[1].rgdwFlags[0] = CEDB_SORT_UNKNOWNFIRST;
    DBInfo.rgSortSpecs[2].wVersion = SORTORDERSPECEX_VERSION;
    DBInfo.rgSortSpecs[2].wNumProps = 1;
    DBInfo.rgSortSpecs[2].wKeyFlags = 0;
    DBInfo.rgSortSpecs[2].rgPropID[0] = PROPID_TIME;
    DBInfo.rgSortSpecs[2].rgdwFlags[0] = CEDB_SORT_UNKNOWNFIRST;

    StringCchCopy(DBInfo.szDbaseName, ARRAYSIZE(DBInfo.szDbaseName), tszDBName);


    // Volume might exist, create anyway
#ifdef EDB 
    if (!CeMountDBVol( &m_VolGUID, pszDBVolName, CREATE_ALWAYS | EDB_MOUNT_FLAG))
#else
    if (!CeMountDBVol( &m_VolGUID, pszDBVolName, CREATE_ALWAYS))
#endif // EDB
    {
        OutputMsg(L"ERROR: could not lcreate: %s volume\n", pszDBVolName); 
    }

    // Create the database
#ifdef EDB 
    if(NULL == (DBOid = CeCreateDatabaseWithProps(&m_VolGUID, &DBInfo, 0, NULL)))
#else
    if(NULL == (DBOid = CeCreateDatabaseEx2(&m_VolGUID, &DBInfo)))
#endif
    {
        // DB exists
        if (ERROR_DUP_NAME == GetLastError())
        {
            OutputMsg(L"ERROR: Name already exists!: %s\n", tszDBName);
        }
        else
        {
            OutputMsg(L"ERROR: Failed creating database %s - error = %ld\n", tszDBName, GetLastError());
        }

        goto Cleanup;
        bRtn = FALSE;
    }
    else
    {
        OutputMsg(L"Database created: %s\n", tszDBName);
    }

    TestOids(&m_VolGUID, DBOid);

    // Open the newly created DB
#ifdef EDB 
    hSession = CeCreateSession(&m_VolGUID);
    *phDB = CeOpenDatabaseInSession( hSession,
                            &m_VolGUID, 
                            &DBOid, 
                            tszDBName, 
                            &DBInfo.rgSortSpecs[0], 
                            CEDB_AUTOINCREMENT,
                            NULL) ;

#else
    *phDB = CeOpenDatabaseEx2(&m_VolGUID, 
                            &DBOid, 
                            tszDBName, 
                            &DBInfo.rgSortSpecs[0], 
                            CEDB_AUTOINCREMENT,
                            NULL) ;
#endif
    if (INVALID_HANDLE_VALUE == *phDB)
    {
        OutputMsg(L"ERROR: could not open the created database!: %s\n", tszDBName);
        bRtn = FALSE;
        goto Cleanup;
    }
    else
    {
        OutputMsg(L"OK: opened database: %s\n", tszDBName);
    }
Cleanup:
    return(bRtn);
}


HANDLE OpenByName(WCHAR *szName)
{
    HANDLE hDB = INVALID_HANDLE_VALUE;
    SORTORDERSPECEX rgSortSpecs;
    CEOID DBOid = 0;
    rgSortSpecs.wVersion = SORTORDERSPECEX_VERSION;
    rgSortSpecs.wNumProps = 1;
    rgSortSpecs.wKeyFlags = 0;
    rgSortSpecs.rgPropID[0] = PROPID_NAME;
    rgSortSpecs.rgdwFlags[0] = CEDB_SORT_UNKNOWNFIRST;


#ifdef EDB 
    hDB = CeOpenDatabaseInSession( hSession,
                            &m_VolGUID, 
                            &DBOid, 
                            szName, 
                            &rgSortSpecs, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;

#else
    hDB = CeOpenDatabaseEx2(&m_VolGUID, 
                           &DBOid, 
                           szName, 
                           &rgSortSpecs,
                           CEDB_AUTOINCREMENT,
                           NULL) ;
#endif
    return hDB;
}


HANDLE OpenBySize(WCHAR *szName)
{
    HANDLE hDB = INVALID_HANDLE_VALUE;
    SORTORDERSPECEX rgSortSpecs;
    CEOID DBOid = 0;
    rgSortSpecs.wVersion = SORTORDERSPECEX_VERSION;
    rgSortSpecs.wNumProps = 1;
    rgSortSpecs.wKeyFlags = 0;
    rgSortSpecs.rgPropID[0] = PROPID_SIZE;
    rgSortSpecs.rgdwFlags[0] = CEDB_SORT_UNKNOWNFIRST;

#ifdef EDB 
    hDB = CeOpenDatabaseInSession( hSession,
                            &m_VolGUID, 
                            &DBOid, 
                            szName, 
                            &rgSortSpecs, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;

#else
    hDB = CeOpenDatabaseEx2(&m_VolGUID, 
                           &DBOid, 
                           szName, 
                           &rgSortSpecs,
                           CEDB_AUTOINCREMENT,
                           NULL) ;
#endif
    return hDB;
}

HANDLE OpenByTime(WCHAR *szName)
{
    HANDLE hDB = INVALID_HANDLE_VALUE;
    SORTORDERSPECEX rgSortSpecs;
    CEOID DBOid = 0;
    rgSortSpecs.wVersion = SORTORDERSPECEX_VERSION;
    rgSortSpecs.wNumProps = 1;
    rgSortSpecs.wKeyFlags = 0;
    rgSortSpecs.rgPropID[0] = PROPID_TIME;
    rgSortSpecs.rgdwFlags[0] = CEDB_SORT_UNKNOWNFIRST;
#ifdef EDB 
    hDB = CeOpenDatabaseInSession( hSession,
                            &m_VolGUID, 
                            &DBOid, 
                            szName, 
                            &rgSortSpecs, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;

#else
    hDB = CeOpenDatabaseEx2(&m_VolGUID, 
                           &DBOid, 
                           szName, 
                           &rgSortSpecs,
                           CEDB_AUTOINCREMENT,
                           NULL) ;
#endif
    return hDB;
}
BOOL DumpDB(HANDLE hDB)
{
    CEOID oidRecord;
    CEPROPVAL*pRecord = NULL;
    WORD   wNumProps;
    DWORD  dwBufSize = 0;
    TCHAR szName[MAX_PATH];
    DWORD dwSize = 0;
    DWORD dwAttr = 0;
    FILETIME ft;
    SYSTEMTIME st;
    oidRecord = CeSeekDatabaseEx(hDB, CEDB_SEEK_BEGINNING, 0, 0, 0);
    if (!oidRecord) {
        OutputMsg(L"DumPDB: Couldn't seek to beginning of DB!");
        return FALSE;
    }
    WORD i;
#ifdef EDB 
    while (oidRecord = CeReadRecordPropsEx(hDB, CEDB_ALLOWREALLOC, &wNumProps, NULL, (LPBYTE *)&pRecord, &dwBufSize, NULL)) {
#else
    while (oidRecord = CeReadRecordProps(hDB, CEDB_ALLOWREALLOC, &wNumProps, NULL, (LPBYTE *)&pRecord, &dwBufSize)) {
#endif

        TestOids(&m_VolGUID, oidRecord);
        for (i = 0; i < wNumProps; i++) {
            switch(pRecord[i    ].propid) {
                case PROPID_NAME:
                    wcscpy( szName, pRecord[i].val.lpwstr);
                    break;
                case PROPID_TIME:
                    ft = pRecord[i].val.filetime;
                    break;
                case PROPID_ATTR:
                    dwAttr = pRecord[i].val.uiVal;
                    break;
                case PROPID_SIZE:
                    dwSize = pRecord[i].val.uiVal;
                    break;
                default:
                    OutputMsg(L"Unknown propid !!!!\r\n");
                    DebugBreak();
                    break;
            }
        }
        FileTimeToSystemTime(&ft, &st);
        OutputMsg(L"%30s %10ld %02d/%02d/%02d %02d:%02d %c%c%c\r\n",
            szName,
            dwSize,
            st.wMonth, st.wDay, st.wYear,
            st.wHour, st.wMinute,
            dwAttr & FILE_ATTRIBUTE_DIRECTORY ? L'D' : L' ',
            dwAttr & FILE_ATTRIBUTE_SYSTEM ? L'S' : L' ',
            dwAttr & FILE_ATTRIBUTE_HIDDEN ? L'H' : L' ');
    }

    LocalFree(pRecord);
    return TRUE;
}

//
// Sorts the database using a specific locale.
//
BOOL TestDatabaseSortLCID(LPWSTR lpLocaleString)
{
    LPWSTR pszTmp;
    DWORD dwLCID = wcstoul(lpLocaleString, &pszTmp, 16);
    HANDLE hDB = INVALID_HANDLE_VALUE;

    OutputMsg( L"Setting LCID=%08X\r\n", dwLCID); 

    // has no return value-- assume success
    //
    CeChangeDatabaseLCID(&m_VolGUID, dwLCID);
    
    // string sort
    hDB = OpenByName(pszDBName);

    OutputMsg( L"Sorting by name\r\n");
    OutputMsg( L"--------------------------------------------------------\r\n");

    if (!DumpDB(hDB)) {
        OutputMsg(L"ERROR: could not dump the database!!\n"); 
        goto Cleanup;
    }

    CloseHandle(hDB);

    // dword sort
    hDB = OpenBySize(pszDBName);

    OutputMsg( L"Sorting by size\r\n");
    OutputMsg( L"----------------------------------------------------------\r\n");
    if (!DumpDB(hDB)) {
        OutputMsg(L"ERROR: could not dump the database!!\n"); 
        goto Cleanup;
    }
    CloseHandle(hDB);

    // file time sort
    hDB = OpenByTime(pszDBName);
    OutputMsg( L"Sorting by time\r\n");
    OutputMsg( L"----------------------------------------------------------\r\n");

    if (!DumpDB(hDB)) {
        OutputMsg(L"ERROR: could not dump the database!!\n"); 
        goto Cleanup;
    }

    CloseHandle(hDB);
    hDB = INVALID_HANDLE_VALUE;

    return TRUE;
    
Cleanup:    
    // Close the database if still open
    if(INVALID_HANDLE_VALUE != hDB)
    {
        CloseHandle(hDB);
    }

    return FALSE;
}


//
// Main entry point.
//
BOOL WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR lpCmdLine,
                   int nCmdShow)
{
    HANDLE hDB = INVALID_HANDLE_VALUE;

    //
    // 1. Verify condition of exising Volume - this is where we detect 
    // corruption. CreateDB (or Mount)
    if(! CreateDB(&hDB, pszDBName))
    {
        goto Cleanup;
    }


    //
    // 2. Create Table & Add records
    if(! PopulateDB(hDB, FALSE))
    {
        OutputMsg(L"ERROR: could not populate the database!!\n"); 
        goto Cleanup;
    }


    //
    // 3. Flush baseline Database: schema + data - this must always pass
    if(! CeFlushDBVol(&m_VolGUID))
    {
        OutputMsg(L"ERROR: could not flush baseline database scheema!: %d\n", GetLastError());
        goto Cleanup;
    }

    CloseHandle(hDB);
    hDB = INVALID_HANDLE_VALUE;

    //
    // 4. Call EnumSystemLocales using "0409" LOCALE.
    LPWSTR lpLocale = L"0409\0";
    TestDatabaseSortLCID(lpLocale);

Cleanup:   

#ifdef EDB 
    // Close the session if still open
    if(INVALID_HANDLE_VALUE != hSession)
    {
        CloseHandle(hSession);
    }
#endif

    // Close the database if still open
    if(INVALID_HANDLE_VALUE != hDB)
    {
        CloseHandle(hDB);
    }

    return(FALSE);
}
