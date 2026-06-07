/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/*++

Copyright (c) 1995 Microsoft Corporation

Module Name:

    stdevs.cpp

Abstract:
    
    Implementation the Stock Portfolio device ActiveSync module for Windows CE Services

--*/
#include <windows.h>
#include <cesync.h>

#include "..\..\common.h"
#include "stdevs.h"

#pragma warning(disable : 4995)

// GUID for the database volume
CEGUID  v_guid;
TCHAR   v_szDBVol[ MAX_PATH ];

BOOL WINAPI DllMain( HANDLE hInstDll, ULONG ulReason, LPVOID lpReserved )
{
    switch( ulReason )
    {
    case DLL_PROCESS_ATTACH :
        break;

    case DLL_PROCESS_DETACH:
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    }
    return TRUE;
}

// Current partner bit (1 or 2)
UINT    v_uPartnerBit;

// OID of the database we synchronize
CEOID   v_oidDb;

/*++
BOOL IsVolMatched
    Return TRUE if the given BLOB matches the GUID we are currently using
--*/
BOOL IsVolMatched( LPBYTE lpbVol, UINT cbVol )
{
    if ( CHECK_SYSTEMGUID( &v_guid ) )
        return lpbVol == NULL || cbVol == sizeof( v_guid ) && CHECK_SYSTEMGUID( (CEGUID *)lpbVol );

    return cbVol == sizeof( v_guid ) && !memcmp( lpbVol, &v_guid, sizeof( v_guid ) );
}

/*++
BOOL Open
    Search/open the database we synchronize
--*/
BOOL Open( HANDLE *phDatabase, CEOID *pOid = NULL )
{
    // search for the database we want to replicate, create one if not found
    HANDLE      hFind;
    CEOID       oid;
    CEOIDINFO   oidInfo;

    oid         = 0;
    hFind       = CeFindFirstDatabaseEx( &v_guid, DBTYPE_STOCKPOR );

    if ( hFind != INVALID_HANDLE_VALUE ) 
    {
        for ( ;; )
        {
            oid = CeFindNextDatabase( hFind );   
            if ( !oid ||
                 CeOidGetInfoEx( &v_guid, oid, &oidInfo ) && oidInfo.wObjType == OBJTYPE_DATABASE &&
                  !wcscmp( oidInfo.infDatabase.szDbaseName, SZ_DEFAULT_PORTFILE ) )
                break;
        }
        CloseHandle( hFind );
    }

    if ( !oid )
    {
        CEDBASEINFO info;

        memset( &info, 0, sizeof( info ) );
        info.dwFlags = CEDB_VALIDNAME | CEDB_VALIDTYPE;
        lstrcpy( info.szDbaseName, SZ_DEFAULT_PORTFILE );
        info.dwDbaseType = DBTYPE_STOCKPOR;
        oid = CeCreateDatabaseEx( &v_guid, &info );
    }

    if ( oid && phDatabase )
        *phDatabase = CeOpenDatabaseEx( &v_guid, &oid, 0,  0, 0, NULL );

    if ( pOid )
        *pOid = oid;

    return oid && ( !phDatabase || *phDatabase != INVALID_HANDLE_VALUE );
}

/*++
EXTERN_C BOOL InitObjType
    Initialize/Un-initialize the moudle. lpszObjType is NULL if un-initializing.
--*/
EXTERN_C BOOL InitObjType( LPWSTR lpszObjType, IReplObjHandler **ppObjHandler, UINT uPartnerBit )
{
    if ( lpszObjType == NULL )
    {
        // terminating the module
        // free up all resources used
        if ( CHECK_SYSTEMGUID( &v_guid ) )
            CeUnmountDBVol( &v_guid );
        return TRUE;
    }

    // find out what database volume we are sync'ing
    HKEY    hKey;
    DWORD   dw, cb;

    v_szDBVol[0] = 0;
    if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE, SZ_REG_ROOT, 0, KEY_READ, &hKey ) == ERROR_SUCCESS )
    {
        cb = sizeof( v_szDBVol );
        RegQueryValueEx( hKey, SZ_REG_DBVOL, NULL, &dw, (LPBYTE)v_szDBVol, &cb );  
        RegCloseKey( hKey );
    }

    if ( v_szDBVol[0] )
        CeMountDBVol( &v_guid, v_szDBVol, OPEN_EXISTING );
    else
    {
        CREATE_SYSTEMGUID( &v_guid );
    }

    *ppObjHandler = new CDataHandler;
    v_uPartnerBit = uPartnerBit;
    return TRUE;
}

/*++
EXTERN_C HRESULT FindObjects
    Enumerate all objects in the database volume currently used
--*/
EXTERN_C HRESULT FindObjects( PFINDOBJINFO pfi )
{
    DWORD       dwIndex, ix, jx, cOid, cbProps;
    CEPROPVAL   *rgProps = NULL;
    WORD        cProps;
    CEOID       oid;
    CEOIDINFO   oidInfo;
    HANDLE      hDatabase;
    int         nChanged = 0, nUnChanged = 0;
    static      CEGUID ceGuid;
     
    if ( pfi->uFlags & FO_DONE_ONE_VOL )
    {
        if ( pfi->poid )
            LocalFree( pfi->poid );
        return NOERROR;
    }

    if ( !CeOidGetInfoEx( &v_guid, v_oidDb, &oidInfo ) || oidInfo.wObjType != OBJTYPE_DATABASE )
        return E_UNEXPECTED;

    // must return the DB GUID as the volume ID, even if there may not be object in the store yet
    if ( !CHECK_SYSTEMGUID( &v_guid ) )
    {
        pfi->cbVolumeID = sizeof( CEGUID );
        pfi->lpbVolumeID = (LPBYTE)&v_guid;
    }

    cOid = oidInfo.infDatabase.wNumRecords;
    if ( cOid == 0 )
        return NOERROR;

    if ( !Open( &hDatabase ) )
        return E_POINTER;

    // NOTE: for sake of simplicity, we are not checking memory allocation error here
    // for real world application, out of memory case must be taken care of.
    pfi->poid = (PUINT)LocalAlloc( LPTR, cOid * sizeof( UINT ) );
       
    oid = CeSeekDatabase( hDatabase, CEDB_SEEK_BEGINNING, 0, &dwIndex );

    for ( ix = 0; ix < cOid && oid != 0; ix++ )
    {
        if ( oid == CeReadRecordProps( hDatabase, CEDB_ALLOWREALLOC, &cProps, NULL, (LPBYTE *)&rgProps, &cbProps ) )
        {
            for ( jx = 0; jx < cProps; jx++ )
                if ( rgProps[jx].propid == HHPR_FLAGS )
                {
                    if ( rgProps[ jx ].val.uiVal & v_uPartnerBit )
                    {
                        // Yes, this one did change -- tack it on to the end of our array
                        pfi->poid[cOid - nChanged - 1] = oid;
                        nChanged++;

                        if ( rgProps[ jx ].val.uiVal & SF_CHG_IN_SYNC )
                        {
                            rgProps[ jx ].val.uiVal &= ~SF_CHG_IN_SYNC;

                            if ( CeSeekDatabase( hDatabase, CEDB_SEEK_CEOID, oid, &dwIndex ) == oid )
                                CeWriteRecordProps( hDatabase, oid, 1, rgProps + jx );
                        }
                    }
                    else
                    {
                        // No, this one did not change -- tack it on to the beginning of our array
                        pfi->poid[nUnChanged] = oid;
                        nUnChanged++;
                    }
                    break;
                }
            LocalFree( rgProps );
        }
        oid = CeSeekDatabase( hDatabase, CEDB_SEEK_CURRENT, 1, &dwIndex );
    }

    pfi->cChg = nChanged;
    pfi->cUnChg = nUnChanged;

    CloseHandle( hDatabase );
    return NOERROR;
}

/*++
EXTERN_C BOOL ObjectNotify
    Respond to change/delete of a file system object
--*/
EXTERN_C BOOL ObjectNotify( POBJNOTIFY pNotify )
{
    CEPROPVAL   *rgProps = NULL;
    HANDLE      hDatabase = INVALID_HANDLE_VALUE;
    UINT        uixFlags = 0, ix;
    BOOL        fRet = FALSE, fSave = FALSE;
    DWORD       dwIndex, cbProps;
    WORD        cProps;

    if ( pNotify->cbStruct < sizeof( OBJNOTIFY ) )
    {
        // stop if strucuture size is smaller
        goto Exit;
    }

    // quick check on ONF_* flags
    // to see if we're interested in this notification
    if ( !( pNotify->uFlags & ( ONF_RECORD | ONF_CLEAR_CHANGE ) ) )
        goto Exit;

    if ( !( pNotify->uFlags & ONF_DELETED ) )
    {
        // make sure we are dealing with the records in our database
        if ( ( pNotify->uFlags & ONF_RECORD ) && 
             ( pNotify->oidInfo.wObjType != OBJTYPE_RECORD || pNotify->oidInfo.infRecord.oidParent != v_oidDb ||
             !IsVolMatched( pNotify->lpbVolumeID, pNotify->cbVolumeID ) ) )
            goto Exit;

        if ( !Open( &hDatabase ) )
            goto Exit;

        CEOID   oid = CeSeekDatabase( hDatabase, CEDB_SEEK_CEOID, pNotify->oidObject, &dwIndex );
        if ( oid != pNotify->oidObject )
            goto Exit;
        
        oid = CeReadRecordProps( hDatabase, CEDB_ALLOWREALLOC, &cProps, NULL, (LPBYTE *)&rgProps, &cbProps );
        if ( oid != pNotify->oidObject )
            goto Exit;

        for ( ix = 0; ix < cProps; ix++ )
            if ( rgProps[ix].propid == HHPR_FLAGS )
            {
                uixFlags = ix;
                break;
            }

        if ( ix >= cProps )
            goto Exit;
    }

    if ( pNotify->uFlags & ONF_CLEAR_CHANGE )
    {
        fSave = TRUE;

        // did object got changed again during sync?
        if ( rgProps[ uixFlags ].val.uiVal & SF_CHG_IN_SYNC ) 
        {
            // clear this bit now but keep the dirty bit
            rgProps[ uixFlags ].val.uiVal &= ~SF_CHG_IN_SYNC;
            fRet = TRUE;
        }
        else
        {
            // clear the dirty bit now
            rgProps[ uixFlags ].val.uiVal &= ~v_uPartnerBit;
            fRet = FALSE;
        }

        goto Exit;
    }

    pNotify->poid = (UINT *)&pNotify->oidObject;

    // determine what object ID to be returned
    // if you store one object per file/record, you simply need to return the file system object ID given
    // otherwise, you need to read the file system object and figure out the list of object ID's that 
    // have changed.

    if ( pNotify->uFlags & ONF_DELETED )
    {
        // object has been deleted
        pNotify->cOidDel = 1;
    }
    else if ( ( rgProps[ uixFlags ].val.uiVal & v_uPartnerBit ) != 0 )
    {
        // object has been deleted
        pNotify->cOidChg = 1;

        if ( rgProps[ uixFlags ].val.uiVal & SF_CHG_IN_SYNC )
        {
            rgProps[ uixFlags ].val.uiVal &= ~SF_CHG_IN_SYNC;
            fSave = TRUE;
        }
    }

    fRet = TRUE;

Exit:  
    if ( fSave && CeSeekDatabase( hDatabase, CEDB_SEEK_CEOID, pNotify->oidObject, &dwIndex ) == pNotify->oidObject )
        CeWriteRecordProps( hDatabase, pNotify->oidObject, cProps, rgProps );
   
    if ( hDatabase != INVALID_HANDLE_VALUE )
        CloseHandle( hDatabase );

    if ( rgProps )
        LocalFree( rgProps );

    return fRet;
}

/*++
EXTERN_C BOOL SyncData
    Allow desktop to send/receive data
--*/
EXTERN_C BOOL SyncData( PSDREQUEST psd )
{
    // do we need to read or write data?
    if ( psd->fSet )
    {
    }
    else
    {
        switch( psd->uCode )
        {
        case 1:
            // set the size of the database volume name we are about to return
            psd->cbData = ( wcslen( v_szDBVol ) + 1 ) * sizeof( WCHAR );

            // Note: ActiveSync manage will call this routine twice, first with lpbData set to NULL
            // after cbData is returned, ActiveSync manager allocates the memory and call this routine again
            if ( psd->lpbData )
                wcscpy( (LPTSTR)psd->lpbData, v_szDBVol );
            break;
        }
    }
    return TRUE;
}


/*++
EXTERN_C BOOL GetObjTypeInfo
    Return object type related information in the given structure
--*/
EXTERN_C BOOL GetObjTypeInfo( POBJTYPEINFO pInfo )
{
    if ( pInfo->cbStruct != sizeof( OBJTYPEINFO ) )
        return FALSE;

    CEOIDINFO   oidInfo;

     if ( !Open( NULL, &v_oidDb ) )
        return FALSE;

    ClearStruct( oidInfo );
    CeOidGetInfoEx( &v_guid, v_oidDb, &oidInfo );

    wcscpy( pInfo->szName, oidInfo.infDatabase.szDbaseName );
    pInfo->cObjects = oidInfo.infDatabase.wNumRecords;
    pInfo->cbAllObj = oidInfo.infDatabase.dwSize;
    pInfo->ftLastModified = oidInfo.infDatabase.ftLastModified;
    return TRUE;
}

/*++
--*/
EXTERN_C BOOL ReportStatus( LPWSTR lpszObjType, UINT uCode, UINT uParam )
{
    HWND    hwnd;

    switch( uCode )
    {
    case RSC_BEGIN_SYNC:
        break;

    case RSC_END_SYNC:
        // post a message to the Stock Portfolio app so it will refresh the display
        hwnd = FindWindow( SZ_WND_CLASS, NULL );
        if ( hwnd )
            PostMessage( hwnd, WM_DATA_CHANGED, 0, 0 );
        break;
    }
    return TRUE;
}

//
// =*=*================== Data Handler ===================================
//

CDataHandler::CDataHandler()
{
    m_cRef  = 1;
}

CDataHandler::~CDataHandler()
{
}

/*++
--*/
STDMETHODIMP_(ULONG) CDataHandler::AddRef()
{
    ULONG urc;
    urc = (ULONG)InterlockedIncrement( &m_cRef );
    return(urc);
}

/*++
--*/
STDMETHODIMP_(ULONG) CDataHandler::Release()
{
    ULONG urc;
    urc = (ULONG)InterlockedDecrement( &m_cRef ); 
    if (urc == 0 ) 
        delete this;

    return urc;
}

/*++
--*/
STDMETHODIMP CDataHandler::QueryInterface( REFIID iid, LPVOID  *ppvObj )
{
    *ppvObj = NULL;
    return E_NOINTERFACE;
}

/*++
--*/
STDMETHODIMP CDataHandler::Reset( PREPLSETUP pSetup )
{                                            
    // we don't have resources to clean up
    return NOERROR;
}

/*++
--*/
STDMETHODIMP CDataHandler::Setup( PREPLSETUP pSetup )
{
    // we could be reading and writing at the same time, so need to save the pointer to setup struct differently
    if ( pSetup->fRead )
        m_pReadSetup = pSetup;
    else
        m_pWriteSetup = pSetup;

    return NOERROR;
}

/*++
--*/
STDMETHODIMP CDataHandler::DeleteObj( PREPLSETUP pSetup )
{
    DWORD   dwIndex;
    HANDLE  hDatabase;
    
    if ( !Open( &hDatabase ) )
        return E_UNEXPECTED;

    if ( CeSeekDatabase( hDatabase, CEDB_SEEK_CEOID, pSetup->oid, &dwIndex ) == pSetup->oid )
    {
        CeDeleteRecord( hDatabase, pSetup->oid );
        CloseHandle( hDatabase );
        return NOERROR;
    }

    CloseHandle( hDatabase );
    return HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND );
}

/*++
--*/
STDMETHODIMP CDataHandler::GetPacket( LPBYTE *lppbPacket, DWORD *pcbPacket, DWORD cbRecommend )
{
    DWORD       dwIndex;
    CEPROPVAL   *rgProps = NULL, *pProp;
    DWORD       cbProps;
    WORD        cProps;
    UINT        ix;
    HRESULT     hr = RWRN_LAST_PACKET;
    HANDLE      hDatabase = INVALID_HANDLE_VALUE;
    
    if ( !Open( &hDatabase ) )
    {
        hr = E_FAIL;
        goto Exit;
    }

    if ( CeSeekDatabase( hDatabase, CEDB_SEEK_CEOID, m_pReadSetup->oid, &dwIndex ) != m_pReadSetup->oid ||
         CeReadRecordProps( hDatabase, CEDB_ALLOWREALLOC, &cProps, NULL, (LPBYTE *)&rgProps, &cbProps ) != m_pReadSetup->oid )
    {
        hr = HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND );
        goto Exit;
    }

    ClearStruct( m_packet );
    for ( ix = 0, pProp = rgProps; ix < cProps; ix++, pProp++ )
    {
        switch( pProp->propid )
        {
        case HHPR_SYMBOL:       wcscpy( m_packet.wszSym, pProp->val.lpwstr ); break;
        case HHPR_COMPANY:      wcscpy( m_packet.wszCompany, pProp->val.lpwstr ); break;
        case HHPR_PRICE:        wcscpy( m_packet.wszLastPrice, pProp->val.lpwstr ); break;
        case HHPR_PUR_DATE:     wcscpy( m_packet.wszPurDate, pProp->val.lpwstr ); break;
        case HHPR_PUR_PRICE:    wcscpy( m_packet.wszPurPrice, pProp->val.lpwstr ); break;
        case HHPR_GAIN_LOSS:    wcscpy( m_packet.wszGain, pProp->val.lpwstr ); break;
        case HHPR_UP_TIME:      m_packet.ftUpdated = pProp->val.filetime; break;
        }
    }

Exit:
    if ( rgProps )
        LocalFree( rgProps );

    if ( hDatabase != INVALID_HANDLE_VALUE )
        CloseHandle( hDatabase );

    *pcbPacket = sizeof( m_packet );
    *lppbPacket = (LPBYTE)&m_packet;

    return hr;
}

/*++
--*/
STDMETHODIMP CDataHandler::SetPacket( LPBYTE lpbPacket, DWORD cbPacket )
{
    CEPROPVAL   rgProps[8];
    CEOID       oid;
    HANDLE      hDatabase = INVALID_HANDLE_VALUE;
    HRESULT     hr = NOERROR;
    PSTPACKET   pPacket = (PSTPACKET)lpbPacket;

    memset( rgProps, 0, sizeof( rgProps ) );

    // write the packet
    if ( cbPacket != sizeof( STPACKET ) )
    {
        hr = E_UNEXPECTED;
        goto Exit;
    }

    if ( !Open( &hDatabase ) )
    {
        hr = E_FAIL;
        goto Exit;
    }

    // must return the DB GUID as the volume ID
    if ( !CHECK_SYSTEMGUID( &v_guid ) )
    {
        m_pWriteSetup->cbVolumeID = sizeof( CEGUID );
        m_pWriteSetup->lpbVolumeID = (LPBYTE)&v_guid;
    }

    rgProps[0].propid       = HHPR_SYMBOL;
    rgProps[0].val.lpwstr   = pPacket->wszSym;

    rgProps[1].propid       = HHPR_COMPANY;
    rgProps[1].val.lpwstr   = pPacket->wszCompany;

    rgProps[2].propid       = HHPR_PRICE;
    rgProps[2].val.lpwstr   = pPacket->wszLastPrice;

    rgProps[3].propid       = HHPR_PUR_DATE;
    rgProps[3].val.lpwstr   = pPacket->wszPurDate;

    rgProps[4].propid       = HHPR_PUR_PRICE;
    rgProps[4].val.lpwstr   = pPacket->wszPurPrice;

    rgProps[5].propid       = HHPR_GAIN_LOSS;
    rgProps[5].val.lpwstr   = pPacket->wszGain;

    rgProps[6].propid       = HHPR_UP_TIME;
    rgProps[6].val.filetime = pPacket->ftUpdated;

    rgProps[7].propid       = HHPR_FLAGS;
    rgProps[7].val.uiVal    = SF_UPDATE_VIEW | ( ( SF_CHANGED1 | SF_CHANGED2 ) & ~v_uPartnerBit );

    // create a new stock record or overwriting the existing record
    if ( m_pWriteSetup->dwFlags & RSF_NEW_OBJECT )
        oid = m_pWriteSetup->oidNew = CeWriteRecordProps( hDatabase, 0, Dim( rgProps ), rgProps );
    else
        oid = CeWriteRecordProps( hDatabase, m_pWriteSetup->oidNew, Dim( rgProps ), rgProps );

    if ( !oid )
    {
        // most likely because we're out of memory 
        hr = E_OUTOFMEMORY;
        goto Exit;
    }

Exit:
    if ( hDatabase != INVALID_HANDLE_VALUE )
        CloseHandle( hDatabase );

    return hr;
}

