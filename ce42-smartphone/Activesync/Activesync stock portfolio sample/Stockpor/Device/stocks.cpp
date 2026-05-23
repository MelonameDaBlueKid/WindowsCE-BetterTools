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

Module Name:
    
      stocks.cpp

Abstract:

    Implementation of CStocks class

--*/

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>
#include <commctrl.h>
#include <tchar.h>

#include "..\resource.h"
#include "..\common.h"

// define class CStocks
#include "stocks.h"

typedef struct tagPropMap
{
    UINT    uid;            // id of the control in the dialog for this property
    UINT    uPropId;        // property id
    UINT    cbMax;          // max size of the field
    TCHAR   szText[ 100 ];  // contents of the property
} PROPMAP, *PPROPMAP;

// GUID for the database volume
CEGUID      v_guid;

//
//  List of properties to save in the database
//
static PROPMAP v_rgProps[] =
{
    { IDC_SYMBOL,       HHPR_SYMBOL,    20 },
    { IDC_COMPANY,      HHPR_COMPANY,   80 },
    { IDC_LAST_PRICE,   HHPR_PRICE,     20 },
    { IDC_PUR_DATE,     HHPR_PUR_DATE,  20 },
    { IDC_PUR_PRICE,    HHPR_PUR_PRICE, 20 },
    { IDC_GAIN_LOSS,    HHPR_GAIN_LOSS, 20 },
    { IDC_LAST_UPDATE,  HHPR_UP_TIME,   0 },
};

//
//  List of properties to show in the main view
//
static PROPMAP v_rgPropsView[] =
{
    { IDC_SYMBOL,       HHPR_SYMBOL,    20 },
    { IDC_LAST_PRICE,   HHPR_PRICE,     20 },
    { 0,                HHPR_UP_TIME,   0 },
};

void GetLocalFileTime( FILETIME *pft )
{
    SYSTEMTIME  st;
    GetLocalTime( &st );
    SystemTimeToFileTime( &st, pft );
}

/*++
--*/
LPTSTR FormatTime( FILETIME *pft, LPTSTR lpsz )
{
    TCHAR       szDate[ 40 ], szTime[ 40 ];
    SYSTEMTIME  st;

    FileTimeToSystemTime( pft, &st );
    memset( szDate, 0, sizeof( szDate ) );
    memset( szTime, 0, sizeof( szTime ) );

    GetDateFormat( LOCALE_SYSTEM_DEFAULT, 0, &st, NULL, szDate, sizeof( szDate ) );
    GetTimeFormat( LOCALE_SYSTEM_DEFAULT, 0, &st, NULL, szTime, sizeof( szTime ) );
    wsprintf( lpsz, TEXT( "%s %s" ), szDate, szTime );
    return lpsz;
}

/*++
--*/
void UpdateItem( HWND hDlg, CEPROPVAL *rgProps, UINT cProps, BOOL fReadDlg )
{
    UINT        ix, jx;
    CEPROPVAL   *ppv;
    PPROPMAP    pProp;

    for ( ix = 0, ppv = rgProps; ix < cProps; ix++, ppv++ )
    {
        // search for this property in our map
        for ( jx = 0, pProp = v_rgProps; jx < Dim( v_rgProps ) && pProp->uPropId != ppv->propid; jx++, pProp++ );
        if ( jx >= Dim( v_rgProps ) )
            continue;

        // special case for update time
        if ( pProp->uid == 0 )
        {
            if ( fReadDlg )
                GetLocalFileTime( &ppv->val.filetime );
        }
        else if ( fReadDlg )
        {
            GetDlgItemText( hDlg, pProp->uid, pProp->szText, pProp->cbMax );
            ppv->val.lpwstr = pProp->szText;
        }
        else
            SetDlgItemText( hDlg, pProp->uid, ppv->val.lpwstr );
    }
}

/*++
--*/
CStocks::CStocks( HWND hwndMain, HWND hwndLv )
{
    m_hwndMain      = hwndMain;
    m_hwndLv        = hwndLv;
    m_hwndNotify    = NULL;
    m_oidDatabase   = 0;
    m_hDatabase     = NULL;
}

CStocks::~CStocks()
{
    Close();
}

int CStocks::ShowMsg( LPTSTR lpszText, int iLastErr, UINT uFlags )
{
    TCHAR   szMsg[ 1024 ];

    if ( iLastErr != -1 )
    {
        wsprintf( szMsg, TEXT( "%s Last Error: %d" ), lpszText, iLastErr );
        lpszText = szMsg; 
    }

    if ( uFlags == 0 )
        uFlags = MB_OK | MB_ICONINFORMATION;

    return MessageBox( m_hwndMain, lpszText, TEXT( "Stock Portfolio" ), uFlags );
}

void CStocks::Close( void )
{
    if ( m_hDatabase )
    {
        if ( CHECK_SYSTEMGUID( &v_guid ) )
            CeUnmountDBVol( &v_guid );

        CloseHandle( m_hDatabase );
        m_hDatabase = NULL;
    }
    m_oidDatabase = 0;
}

/*++
--*/
BOOL CStocks::Open( LPTSTR lpszFile, BOOL fFailOnNew )
{
    HANDLE      hFind;
    CEOIDINFO   oidInfo;
    UINT        nCount;

    // must close existing database first
    Close();

    // Mount the external database volume
    CREATE_SYSTEMGUID( &v_guid );
    if ( *v_lpszDBVol )
    {
        if ( !CeMountDBVol( &v_guid, v_lpszDBVol, OPEN_EXISTING ) )
        {
            if ( fFailOnNew )
                return FALSE;
                
            if ( !CeMountDBVol( &v_guid, v_lpszDBVol, CREATE_NEW ) )
            {
                TCHAR   szMsg[ MAX_PATH + 50 ];
                wsprintf( szMsg, TEXT( "Failed to mount the database volume: %s. Error: %d" ), 
                          v_lpszDBVol, GetLastError() );
                ShowMsg( szMsg );
                return FALSE;
            }
        }
    }
   
    // search for the database, create one if not found
    hFind = CeFindFirstDatabaseEx( &v_guid, DBTYPE_STOCKPOR );
    if ( hFind != INVALID_HANDLE_VALUE ) 
    {
        for ( ;; )
        {
            m_oidDatabase = CeFindNextDatabase( hFind );   
            if ( !m_oidDatabase ||
                 CeOidGetInfoEx( &v_guid, m_oidDatabase, &oidInfo ) && oidInfo.wObjType == OBJTYPE_DATABASE &&
                  !wcscmp( oidInfo.infDatabase.szDbaseName, SZ_DEFAULT_PORTFILE ) )
                break;
        }
        CloseHandle( hFind );
    }

    if ( !m_oidDatabase )
    {
        CEDBASEINFO info;

        memset( &info, 0, sizeof( info ) );
        info.dwFlags = CEDB_VALIDNAME | CEDB_VALIDTYPE;
        lstrcpy( info.szDbaseName, SZ_DEFAULT_PORTFILE );
        info.dwDbaseType = DBTYPE_STOCKPOR;
        m_oidDatabase = CeCreateDatabaseEx( &v_guid, &info );
    }

    if ( !m_oidDatabase )
    {
        ShowMsg( TEXT( "Failed to create a new database or find an existing one." ), GetLastError() );
        return FALSE;
    }

    // open the database now
    m_hDatabase = CeOpenDatabaseEx( &v_guid, &m_oidDatabase, 0, 0, CEDB_AUTOINCREMENT, NULL );
    if ( !m_hDatabase )
    {
        ShowMsg( TEXT( "Failed to open the database." ), GetLastError() );
        return FALSE;
    }

    ListView_DeleteAllItems( m_hwndLv );
    UpdateView();

    //
    //  Select the first stock
    //
    nCount = ListView_GetItemCount(m_hwndLv);
    if (nCount > 0)
    {
        ListView_SetItemState(m_hwndLv, 0, LVIS_SELECTED, 0x000F);
    }

    return TRUE;
}

/*++
--*/
BOOL CStocks::BeforeAddChg( void )
{
    return m_hDatabase || Open( NULL, FALSE );
}


/*++
void CStocks::SetViewItemText
--*/
void CStocks::SetViewItemText( UINT ix, CEPROPVAL *pProps, UINT cProps )
{
    UINT        jx;
    PPROPMAP    pMap;
    TCHAR       sz[ 120 ];

    for ( ; cProps; cProps--, pProps++ )
    {
        // search for this property in our map
        for ( jx = 0, pMap = v_rgPropsView; jx < Dim( v_rgPropsView ) && pMap->uPropId != pProps->propid; jx++, pMap++ );
        if ( jx >= Dim( v_rgPropsView ) )
            continue;

        ListView_SetItemText( m_hwndLv, ix, jx, 
                              PROP_TYPE( pProps->propid ) == CEVT_FILETIME? FormatTime( &pProps->val.filetime, sz ) 
                              : pProps->val.lpwstr );
    }
}

/*++
void CStocks::UpdateView
    Update the list view with current list of stocks.
--*/
void CStocks::UpdateView( void )
{
    UINT        ix, jx, cItems, cOid;
    CEOID       oid;
    CEOIDINFO   oidInfo;
    DWORD       dwIndex;
    CEOID       *rgOid = NULL;
    int         *rgIx = NULL;

    if ( !CeOidGetInfoEx( &v_guid, m_oidDatabase, &oidInfo ) || oidInfo.wObjType != OBJTYPE_DATABASE )
        return;

    cItems = ListView_GetItemCount( m_hwndLv );
    if ( oidInfo.infDatabase.wNumRecords == 0 )
    { 
        if ( cItems ) 
        {
            // delete all list view items
            ListView_DeleteAllItems( m_hwndLv );
        }
        return;
    }

    // create a list of OIDs and their item indices from the list view
    if ( cItems )
    {
        rgOid = new CEOID[ cItems ];
        rgIx = new int[ cItems ];
    }

    cOid = 0;
    for ( ix = 0; ix < cItems; ix++ )
    {
        LV_ITEM lvi;
        ClearStruct( lvi );
        lvi.iItem = ix;
        lvi.mask = LVIF_PARAM;
        if ( ListView_GetItem( m_hwndLv, &lvi ) )
        {
            rgOid[ cOid ] = lvi.lParam;
            rgIx[ cOid ] = ix;
            cOid++;
        }
    }

    CeSeekDatabase( m_hDatabase, CEDB_SEEK_BEGINNING, 0, &dwIndex );
    for ( ;; )
    {
        WORD        cProps;
        DWORD       cbProps;
        CEPROPVAL   *rgProps = NULL;

        oid = CeReadRecordProps( m_hDatabase, CEDB_ALLOWREALLOC, &cProps, NULL, (LPBYTE *)&rgProps, &cbProps );
        if ( oid == 0 ) 
            break;

        // search the oid list for this item
        for ( ix = 0; ix < cOid && rgOid[ix] != oid; ix++ );

        // didn't find it in the list view, must be new
        if ( ix >= cOid )
        {
            AddItem( oid, rgProps, cProps );
            cItems++;
        }
        else
        {
            for ( jx = 0; jx < cProps; jx++ )
                if ( rgProps[ jx ].propid == HHPR_FLAGS )
                {
                    if ( rgProps[ jx ].val.uiVal & SF_UPDATE_VIEW )
                    {
                        // update the record
                        SetViewItemText( rgIx[ ix ], rgProps, cProps );
                        rgProps[ jx ].val.uiVal &= ~SF_UPDATE_VIEW;

                        // need to save the record back since SF_UPDATE_VIEW is reset
                        CeWriteRecordProps( m_hDatabase, oid, cProps, rgProps );
                    }
                    break;
                }

            // remove the oid from the list so it won't get deleted later
            cOid--;
            if ( ix != cOid )
            {
                memmove( rgOid + ix, rgOid + ix + 1, ( cOid - ix ) * sizeof( rgOid[0] ) );
                memmove( rgIx + ix, rgIx + ix + 1, ( cOid - ix ) * sizeof( rgIx[0] ) );
            }
        }

        if ( rgProps )
            LocalFree( rgProps );
    }

    // remove deleted stocks from the list view
    if ( cOid )
    {
        for ( ix = 0; ix < cItems; ix++ )
        {
            LV_ITEM lvi;
            ClearStruct( lvi );
            lvi.iItem = ix;
            lvi.mask = LVIF_PARAM;
            if ( ListView_GetItem( m_hwndLv, &lvi ) )
            {
                for ( jx = 0; jx < cOid && rgOid[jx] != (CEOID)lvi.lParam; jx++ );
                if ( jx < cOid )
                {
                    ListView_DeleteItem( m_hwndLv, ix );
                    ix--;
                    cItems--;
                }
            }
        }
    }

    if ( rgOid )
        delete [] rgOid;
}

/*++
--*/
void CStocks::AddItem( CEOID oid, CEPROPVAL *rgProps, UINT cProps )
{
    LV_ITEM     lvi;
    UINT        cItems = ListView_GetItemCount( m_hwndLv );

    ClearStruct( lvi );
    lvi.iItem       = cItems;
    lvi.mask        = LVIF_PARAM;
    lvi.lParam      = (LPARAM)oid;
    ListView_InsertItem( m_hwndLv, &lvi );

    SetViewItemText( cItems, rgProps, cProps ); 
}

/*++
--*/
BOOL CStocks::DoAddChg( HWND hDlg, CEOID oid )
{
    CEPROPVAL       *rgProps = NULL;
    WORD            cProps = Dim( v_rgProps ) + 1;
    DWORD           dwIndex;
    CEOID           oidWrote;
    UINT            ix;

    rgProps = new CEPROPVAL[ cProps ];
    memset( rgProps, 0, cProps * sizeof( CEPROPVAL ) );

    for ( ix = 0; ix < Dim( v_rgProps ); ix++ )
        rgProps[ix].propid = v_rgProps[ix].uPropId;

    UpdateItem( hDlg, rgProps, Dim( v_rgProps ), TRUE );

    rgProps[ cProps - 1 ].propid = HHPR_FLAGS;
    rgProps[ cProps - 1 ].val.uiVal = SF_CHANGED1 | SF_CHANGED2;

    // add/change an extra HHPR_FLAGS
    if ( oid )
    {
        // read the old flags
        CEPROPVAL   *rgPropsRead = NULL;
        DWORD       cbProps;
        WORD        cPropsRead;

        if ( CeSeekDatabase( m_hDatabase, CEDB_SEEK_CEOID, oid, &dwIndex ) == oid &&
             CeReadRecordProps( m_hDatabase, CEDB_ALLOWREALLOC, &cPropsRead, NULL, (LPBYTE *)&rgPropsRead, &cbProps ) == oid )
        {
            for ( ix = 0; ix < cPropsRead; ix++ )
                if ( rgPropsRead[ ix ].propid == HHPR_FLAGS )
                {
                    if ( rgPropsRead[ ix ].val.uiVal & ( SF_CHANGED1 | SF_CHANGED2 ) )
                        rgProps[ cProps - 1 ].val.uiVal |= SF_CHG_IN_SYNC;

                    rgProps[ cProps - 1 ].val.uiVal |= rgPropsRead[ ix ].val.uiVal;
                    break;
                }
        }

        if ( rgPropsRead )
            LocalFree( rgPropsRead );

        rgProps[ cProps - 1 ].val.uiVal |= SF_UPDATE_VIEW;
    }

    oidWrote = CeWriteRecordProps( m_hDatabase, oid, cProps, rgProps );

    if ( !oidWrote || oid && oidWrote != oid )
    {
        ShowMsg( TEXT( "Failed to write a record into the database" ), GetLastError() );
        delete [] rgProps;
        return FALSE;
    }

    if ( oid == 0 )
        AddItem( oidWrote, rgProps, Dim( v_rgProps ) );
    else
        UpdateView();

    delete [] rgProps;
    return TRUE;
}

/*++
BOOL CStocks::FillDetails
    Fills the detail dialog with the data
--*/
void  CStocks::FillDetails(HWND hDlg, CEOID oid)
{
    CEPROPVAL   *pProp = NULL;
    DWORD       cbProps;
    WORD        cPropsRead;
    WORD        jx;
    PPROPMAP    pMap;
    DWORD       dwIndex;
    TCHAR       sz[ 120 ];

    if ( CeSeekDatabase( m_hDatabase, CEDB_SEEK_CEOID, oid, &dwIndex ) == oid &&
         CeReadRecordProps( m_hDatabase, CEDB_ALLOWREALLOC, &cPropsRead, NULL, (LPBYTE *)&pProp, &cbProps ) == oid )
    {
        for (; cPropsRead > 0; pProp++, cPropsRead--)
        {
            // search for this property in our map
            for ( jx = 0, pMap = v_rgProps; jx < Dim( v_rgProps ) && pMap->uPropId != pProp->propid; jx++, pMap++ );
            if ( jx >= Dim( v_rgProps ) )
                continue;

            SetDlgItemText(hDlg, pMap->uid, 
                PROP_TYPE( pProp->propid ) == CEVT_FILETIME ? FormatTime( &pProp->val.filetime, sz ) 
                                  : pProp->val.lpwstr);
            
        }
    }
}


/*++
BOOL CStocks::Add
    Takes input from the dialog and add a new stock 
--*/
BOOL CStocks::Add( HWND hDlg )
{
    return DoAddChg( hDlg, 0 );
}

/*++
--*/
void CStocks::Delete( UINT uParam )
{  
    CeDeleteRecord( m_hDatabase, uParam );
}

/*++
BOOL CStocks::SetupDlg
    Setup the Add/Change dialog with the given uParam of the selected item in list view
--*/
BOOL CStocks::SetupDlg( HWND hDlg, UINT uParam )
{
    DWORD       dwIndex, cbProps;
    WORD        cProps;
    CEPROPVAL   *rgProps = NULL;

    if ( CeSeekDatabase( m_hDatabase, CEDB_SEEK_CEOID, uParam, &dwIndex ) != uParam ||
         CeReadRecordProps( m_hDatabase, CEDB_ALLOWREALLOC, &cProps, NULL, (LPBYTE *)&rgProps, &cbProps ) != uParam )
        return FALSE;

    UpdateItem( hDlg, rgProps, cProps, FALSE );

    if ( rgProps )
        LocalFree( rgProps );

    return TRUE;
}

/*++
BOOL CStocks::Change
    Change the stock using data from the dialog
--*/
BOOL CStocks::Change( HWND hDlg, UINT uParam )
{
    return DoAddChg( hDlg, uParam );
}

/*++
void CStocks::OnDataChange
    Responds to data change notification and update the list view
--*/
void CStocks::OnDataChange( void )
{
    UpdateView();
}

/*++
void CStocks::SyncNow
    As of Windows CE Services ver 2.1, there is no way for the device app to initiate synchronization.
--*/
void CStocks::SyncNow( void )
{
    // NYI
}

