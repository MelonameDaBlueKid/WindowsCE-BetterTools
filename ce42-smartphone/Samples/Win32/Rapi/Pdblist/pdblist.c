/*****************************************************************************
  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.

  Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

  PROGRAM: pdblist.c

  ABSTRACT:
    Purpose of this program is to demonstrate the Remote Database API's.
  This sample lists all the database of of a certain type.


******************************************************************************/
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <rapi.h>


void EnumDb( DWORD );

int main( int argc, char *argv[])
{
    HRESULT hRapiResult;

    if ( argc > 2 ) {
        printf( "Syntax: PDBLIST <db type>\n" );
        return 1;
    }

    _tprintf( TEXT("Connecting to Windows CE..."));
    
    hRapiResult = CeRapiInit();

    if (FAILED(hRapiResult))
    {
        _tprintf( TEXT("Failed\n"));
        return 1;
    }

    _tprintf( TEXT("Success\n"));

    if ( argc == 1 )
        EnumDb( 0 );
    if ( argc == 2 )
        EnumDb( atoi(argv[1]) );


    CeRapiUninit();

    return 0;
}

void EnumDb( DWORD DbType )
{
    WORD             cFindData;
    LPCEDB_FIND_DATA pFindData = NULL;

    if ( CeFindAllDatabases( DbType, 0xFF, &cFindData, &pFindData ) )
    {
        WORD  i;
        TCHAR DbName[CEDB_MAXDBASENAMELEN];

        _tprintf( TEXT("Oid         Name                            DbType      Records SrtOrdr\n"));
        _tprintf( TEXT("-----------------------------------------------------------------------\n"));

        for ( i=0 ; i<cFindData ; i++ )
        {
#ifdef UNICODE
                wcscpy( DbName, pFindData[i].DbInfo.szDbaseName );
#else
                wcstombs( DbName, pFindData[i].DbInfo.szDbaseName, CEDB_MAXDBASENAMELEN );
                WideCharToMultiByte(
                            CP_ACP,    
                               0,
                            pFindData[i].DbInfo.szDbaseName,
                            wcslen(pFindData[i].DbInfo.szDbaseName)+1,
                               DbName,
                               sizeof(DbName),
                               NULL,
                               FALSE);
#endif
            _tprintf( TEXT("0x%-8X  %-32s"), pFindData[i].OidDb, DbName);
            _tprintf( TEXT("0x%-8X"), pFindData[i].DbInfo.dwDbaseType);
            _tprintf( TEXT("   %3d"), pFindData[i].DbInfo.wNumRecords);
            _tprintf( TEXT("       %d\n"), pFindData[i].DbInfo.wNumSortOrder);
        }
    } else
    {
        _tprintf( TEXT("Error finding all databases!\n"));
        goto FatalError;
    }

FatalError:
	 if ( pFindData )
		 RapiFreeBuffer(pFindData);
    return;
       
}

