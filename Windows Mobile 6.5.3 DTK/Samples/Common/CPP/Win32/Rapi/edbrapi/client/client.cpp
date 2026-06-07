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
//
// Client.CPP
//
// Test Application for EDB RAPI. 
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
// --------------------------------------------------------------------------


#ifndef EDB
#define EDB
#endif

#include <windows.h>
#include <strsafe.h>
#include "rapi.h"
#include "../Clientlib/edbrapi.h"
#include "../Clientlib/Clientlib.h"

#define MAKEPROP(n,t)    ((n<<16)|CEVT_##t)
#define PROPID_MASK      0x0000FFFF
#define PROPID_NAME  MAKEPROP(101,LPWSTR)
#define PROPID_SIZE  MAKEPROP(102,UI2)
#define PROPID_TIME  MAKEPROP(103,FILETIME)
#define PROPID_ATTR  MAKEPROP(104,UI2)
#define PROPID_STEA  MAKEPROP(105,STREAM)

WCHAR *pszDBName = L"MyDB"; //name of the database

//create the database
CEOID CreateDB(PCEGUID pGuid)
{
    
    CEDBASEINFOEX     DBInfo;
    CEOID             DBOid;

    //  Fill in the DBInfo structure   
    memset(&DBInfo, 0, sizeof(DBInfo)) ;
    DBInfo.wVersion                       = CEDBASEINFOEX_VERSION;
    DBInfo.dwFlags                       |= CEDB_VALIDDBFLAGS | CEDB_VALIDNAME | CEDB_VALIDSORTSPEC;
    DBInfo.wNumSortOrder                  = 3;
    DBInfo.rgSortSpecs[0].wVersion        = SORTORDERSPECEX_VERSION;
    DBInfo.rgSortSpecs[0].wNumProps       = 1;
    DBInfo.rgSortSpecs[0].wKeyFlags       = 0;
    DBInfo.rgSortSpecs[0].rgPropID[0]     = PROPID_NAME;
    DBInfo.rgSortSpecs[0].rgdwFlags[0]    = CEDB_SORT_UNKNOWNFIRST;
    DBInfo.rgSortSpecs[1].wVersion        = SORTORDERSPECEX_VERSION;
    DBInfo.rgSortSpecs[1].wNumProps       = 1;
    DBInfo.rgSortSpecs[1].wKeyFlags       = 0;
    DBInfo.rgSortSpecs[1].rgPropID[0]     = PROPID_SIZE;
    DBInfo.rgSortSpecs[1].rgdwFlags[0]    = CEDB_SORT_UNKNOWNFIRST;
    DBInfo.rgSortSpecs[2].wVersion        = SORTORDERSPECEX_VERSION;
    DBInfo.rgSortSpecs[2].wNumProps       = 1;
    DBInfo.rgSortSpecs[2].wKeyFlags       = 0;
    DBInfo.rgSortSpecs[2].rgPropID[0]     = PROPID_TIME;
    DBInfo.rgSortSpecs[2].rgdwFlags[0]    = CEDB_SORT_UNKNOWNFIRST;
    StringCchCopy(DBInfo.szDbaseName, ARRAYSIZE(DBInfo.szDbaseName), pszDBName);
   
    if (!(DBOid = CeEdbCreateDatabaseEx2( pGuid, &DBInfo )))
    {        
        if(GetLastError() == ERROR_DUP_NAME)
        {
            wprintf(L"Database with the same name already exists\n"); 
        }
        else
        {
            wprintf(L"Database cannot be created\n");
        }
        return NULL;
    }
    else 
    {
        wprintf(L"Database created: %s\n", pszDBName);
        return DBOid;
    }
}

//read the properties in the created database
//hSession is the session handle to this application
//pGuid is the mounted database
//this function return true if the property is read correctly
BOOL ReadProps(HANDLE hSession, PCEGUID pGuid)
{
    HANDLE phDB = INVALID_HANDLE_VALUE;
    CEOID DBOid = 0;
    HRESULT hr;
    CEPROPSPEC* prgProps;
    phDB = CeEdbOpenDatabaseInSession( hSession,
                            pGuid, 
                            &DBOid, 
                            pszDBName, 
                            NULL, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;

    if (INVALID_HANDLE_VALUE == phDB)
    {
        wprintf(L"ERROR: could not open the created database!: %s\n", pszDBName); 
        goto Error;
    }
    else
    {
        wprintf(L"OK: opened database: %s\n", pszDBName);
    }
    
    WORD cPropID =3;
    BOOL fRes;

    prgProps = (CEPROPSPEC*)LocalAlloc(LPTR, cPropID * sizeof(CEPROPSPEC));
    
    fRes = CeEdbGetDatabaseProps(phDB, &cPropID, NULL, prgProps);
    if (fRes)
    {
        wprintf(L"Read the database properties successfully \n");
    }
    else
    {
        wprintf(L"Cannot read the database properties \n");
        CBR(fRes);
    }

    BY_HANDLE_DB_INFORMATION  bhDBInfo;

    fRes = CeEdbGetDBInformationByHandle(phDB, &bhDBInfo);
    if (fRes)
    {
        wprintf(L"Get database information by handle successfully \n");
    }
    else
    {
        wprintf(L"Canot get database information by handle \n");
        CBR(fRes);
    }

    LocalFree(prgProps);
    CeCloseHandle(phDB);
    return TRUE;

Error:
    LocalFree(prgProps);
    CeCloseHandle(phDB);
    return FALSE;

}

//write the files & directories in the root directory of the device into the Database
//every record includes the name, size, data, and type of the file or directory 
BOOL PopulateDB(HANDLE hDB)
{
    CEPROPVAL       props[4];
    DWORD           dwTotalRecords = 0;
    CEOID           oidRec;

    if(! hDB || INVALID_HANDLE_VALUE == hDB)
    {
        wprintf(L"ERROR: Null or invalid database handle\n");
        return FALSE;
    }
    else
    {
        CE_FIND_DATA wfd;
        HANDLE hFind = CeFindFirstFile( L"\\*.*", &wfd);
        
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

                oidRec = CeEdbWriteRecordProps(hDB, 0, 4, props);
                if (!(oidRec))
                {
                    return FALSE;
                }
                dwTotalRecords++;

            } while(CeFindNextFile(hFind, &wfd));
        }
    }

    return TRUE;
}

//add & remove stream property 
BOOL AddRemoveProp(HANDLE hSession, PCEGUID pGuid, CEOID oid)
{
    BOOL fRes;
    CEPROPSPEC addProps;
    addProps.wVersion = 1;
    addProps.propid = PROPID_STEA;
    addProps.pwszPropName = NULL;
    addProps.cchPropName = 0;
    addProps.dwFlags = DB_PROP_NOTNULL;
    if(CeEdbAddDatabaseProps(pGuid, oid, 1, &addProps))
    {
        wprintf(L"A stream property is added successfully\n");
    }
    else
    {
        wprintf(L"A stream property cannot be added\n");
        return FALSE;
    }
    
    //check the number of properties in the database
    HANDLE phDB = INVALID_HANDLE_VALUE;  
    phDB = CeEdbOpenDatabaseInSession( hSession,
                            pGuid, 
                            &oid, 
                            pszDBName, 
                            NULL, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;
    WORD cPropID = 0;
    CEPROPSPEC* prgProps = NULL;
    if(CeEdbGetDatabaseProps( phDB, &cPropID, NULL, prgProps))
    {
        wprintf(L"Now, the number of properties is %d!\n", cPropID);
    }
    else
    {
        wprintf(L"Cannot read the number of properties \n");
        return FALSE;
    }
    CeCloseHandle(phDB);
    phDB = INVALID_HANDLE_VALUE;

    //remove the new property
    CEPROPID rgProps = PROPID_STEA;
    if(CeEdbRemoveDatabaseProps(pGuid, oid, 1, &rgProps))
    {
        wprintf(L"Stream property is removed successfully!\n");
    }
    else
    {
        wprintf(L"Stream property cannot be removed\n");
        return FALSE;
    }

    phDB = INVALID_HANDLE_VALUE;
    phDB = CeEdbOpenDatabaseInSession( hSession,
                            pGuid, 
                            &oid,
                            pszDBName, 
                            NULL, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;
    cPropID = 0;
    prgProps = NULL;
    CeEdbGetDatabaseProps(phDB, &cPropID, NULL, prgProps);
    if(CeEdbGetDatabaseProps(phDB, &cPropID, NULL, prgProps))
    {
        wprintf(L"Now, the number of properties is %d !\n", cPropID);
        fRes = TRUE; 
    }
    else
    {
        wprintf(L"Cannot read the number of properties \n");
        fRes = FALSE;

    }
    CeCloseHandle(phDB);
    return fRes;

}

//sort the database by name and print the record one by one
BOOL SortDB(HANDLE hSession, PCEGUID pGuid)
{
    LPWSTR lpLocaleString = L"0409\0";
    LPWSTR pszTmp;
    DWORD dwLCID = wcstoul(lpLocaleString, &pszTmp, 16);
    CeEdbChangeDatabaseLCID(pGuid, dwLCID);

    SORTORDERSPECEX rgSortSpecs;
    CEOID DBOid = 0;
    rgSortSpecs.wVersion = SORTORDERSPECEX_VERSION;
    rgSortSpecs.wNumProps = 1;
    rgSortSpecs.wKeyFlags = 0;
    rgSortSpecs.rgPropID[0] = PROPID_NAME;
    rgSortSpecs.rgdwFlags[0] = CEDB_SORT_UNKNOWNFIRST;
    
    HANDLE phDB = CeEdbOpenDatabaseInSession( hSession,
                            pGuid, 
                            &DBOid, 
                            pszDBName, 
                            &rgSortSpecs, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;

    CEOID oidRecord = CeEdbSeekDatabaseEx(phDB, CEDB_SEEK_BEGINNING, 0, 0, 0);
    
    wprintf(L"Now we print the records in MyDB sorted by name:\n");

    //print the records one by one
    CEPROPVAL* pRecord = NULL;
    WORD   wNumProps;
    DWORD  dwBufSize = 0;

    while (oidRecord = CeEdbReadRecordPropsEx(phDB, 
                                        CEDB_ALLOWREALLOC, 
                                        &wNumProps, 
                                        NULL, 
                                        (LPBYTE*)&pRecord, 
                                        &dwBufSize, 
                                        NULL)) 
    {
        TCHAR szName[MAX_PATH];
        DWORD dwSize;
        DWORD dwAttr;
        FILETIME ft;
        SYSTEMTIME st;
        //GetDBInfo(pGuid, oidRecord); 
        for ( WORD i = 0; i < wNumProps; i++) 
        {
            switch(pRecord[i].propid) {
                case PROPID_NAME:
                    StringCchCopy( szName, ARRAYSIZE(szName), pRecord[i].val.lpwstr);
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
                    wprintf(L"Unknown propid !!!!\r\n");
                    DebugBreak();
                    break;
            }
        }
        FileTimeToSystemTime(&ft, &st);
        wprintf(L"%50s %15ld %02d/%02d/%02d %02d:%02d %c%c%c\r\n",
            szName,
            dwSize,
            st.wMonth, st.wDay, st.wYear,
            st.wHour, st.wMinute,
            dwAttr & FILE_ATTRIBUTE_DIRECTORY ? L'D' : L' ',
            dwAttr & FILE_ATTRIBUTE_SYSTEM ? L'S' : L' ',
            dwAttr & FILE_ATTRIBUTE_HIDDEN ? L'H' : L' ');
    }
   
    LocalFree(pRecord); 
    CeCloseHandle(phDB);
    return TRUE;
}

  
//main entry
int main( int argc, char *argv[])
{    
    HRESULT    hr = S_OK;;
    CEGUID     m_VolGUID;    
    WCHAR     *pszDBVolName = L"MYTEST.EDB";  
    BOOL       fRes = FALSE;
    CEOID      DBOid = 0;
    CEOID      oidNext = 0;
    HANDLE     hSession = INVALID_HANDLE_VALUE;   //handle for the session
    HANDLE     phDB = INVALID_HANDLE_VALUE;       //handle for the database
    CREATE_SYSTEMGUID(&m_VolGUID);

    CeRapiInit();

    // call EdbRapi function to mount a volume
    fRes = CeEdbMountDBVolEx( &m_VolGUID, pszDBVolName , NULL, OPEN_ALWAYS ); 
    if (!fRes)
    {
        hr = HRESULT_FROM_WIN32(GetLastError()); 
        wprintf(L"ERROR: could not create: %s volume\n", pszDBVolName); 
        CBR(fRes);
    }
    else
    {
        wprintf(L"Create: %s volume successfuly!\n", pszDBVolName);
    }

    //create the database 
    DBOid = CreateDB(&m_VolGUID);

    hSession = CeEdbCreateSession(&m_VolGUID);   

    //read the properties in the created database
    fRes = ReadProps(hSession, &m_VolGUID);
    CBR(fRes);
     
    CEOID oidNULL = 0;
    phDB = CeEdbOpenDatabaseInSession( hSession,
                            &m_VolGUID, 
                            &oidNULL, 
                            pszDBName, 
                            NULL, 
                            CEDB_AUTOINCREMENT,
                            NULL) ;
   
    //add some content to the database
    if (DBOid)
    {
        fRes = PopulateDB(phDB);
        CBR(fRes);
    }
    CeCloseHandle(phDB);

    if (! CeEdbFlushDBVol(&m_VolGUID))
    {
        wprintf(L"ERROR: could not flush baseline database schema!: %d\n", GetLastError());
        return FALSE;
    }

    //get the object ID of the DB
    HANDLE hFirst = CeEdbFindFirstDatabaseEx( &m_VolGUID, 0);
    oidNext = CeEdbFindNextDatabaseEx( hFirst, NULL);

    //add & remove property
    fRes = AddRemoveProp(hSession, &m_VolGUID, oidNext);
    CBR(fRes);

    //sort the database by name and print them one by one
    SortDB(hSession, &m_VolGUID);

Error: 
    if(oidNext)
    {
        if(CeEdbDeleteDatabaseEx(&m_VolGUID, oidNext))
        {
            wprintf(L"Database deleted! \n");
        }
    }
    if(INVALID_HANDLE_VALUE != phDB)
    {
        CeCloseHandle(phDB);
    }
    if (INVALID_HANDLE_VALUE != hSession)
    {
        CeCloseHandle(hSession);
    }
    if (CeEdbUnmountDBVol(&m_VolGUID))
    {
        wprintf(L"Volume unmounted! \n");
            
    }

    CeRapiUninit();
    return 0;  
}