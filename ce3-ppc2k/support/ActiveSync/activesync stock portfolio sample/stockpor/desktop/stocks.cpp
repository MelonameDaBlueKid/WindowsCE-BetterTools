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
#include <commctrl.h>

#include "..\resource.h"
#include "..\common.h"

// define class CStocks
#include "stocks.h"

void GetLocalFileTime( FILETIME *pft )
{
    SYSTEMTIME  st;
    GetLocalTime( &st );
    SystemTimeToFileTime( &st, pft );
}

LPSTR FormatTime( FILETIME *pft, LPSTR lpsz )
{
    char        szDate[ 40 ], szTime[ 40 ];
    SYSTEMTIME  st;

    FileTimeToSystemTime( pft, &st );
    memset( szDate, 0, sizeof( szDate ) );
    memset( szTime, 0, sizeof( szTime ) );

    GetDateFormat( GetUserDefaultLCID(), 0, &st, NULL, szDate, sizeof( szDate ) );
    GetTimeFormat( GetUserDefaultLCID(), 0, &st, NULL, szTime, sizeof( szTime ) );
    wsprintf( lpsz, "%s %s", szDate, szTime );
    return lpsz;
}

void UpdateItem( HWND hDlg, PSTOCK pStock, BOOL fReadDlg )
{
    if ( fReadDlg )
    {
        GetLocalFileTime( &pStock->ftUpdated );
        GetDlgItemText( hDlg, IDC_SYMBOL, pStock->szSym, sizeof( pStock->szSym ) );
        GetDlgItemText( hDlg, IDC_COMPANY, pStock->szCompany, sizeof( pStock->szCompany ) );
        GetDlgItemText( hDlg, IDC_LAST_PRICE, pStock->szLastPrice, sizeof( pStock->szLastPrice ) );
        GetDlgItemText( hDlg, IDC_PUR_DATE, pStock->szPurDate, sizeof( pStock->szPurDate ) );
        GetDlgItemText( hDlg, IDC_PUR_PRICE, pStock->szPurPrice, sizeof( pStock->szPurPrice ) );
        GetDlgItemText( hDlg, IDC_GAIN_LOSS, pStock->szGain, sizeof( pStock->szGain ) );
    }
    else
    {
        SetDlgItemText( hDlg, IDC_SYMBOL, pStock->szSym );
        SetDlgItemText( hDlg, IDC_COMPANY, pStock->szCompany );
        SetDlgItemText( hDlg, IDC_LAST_PRICE, pStock->szLastPrice );
        SetDlgItemText( hDlg, IDC_PUR_DATE, pStock->szPurDate );
        SetDlgItemText( hDlg, IDC_PUR_PRICE, pStock->szPurPrice );
        SetDlgItemText( hDlg, IDC_GAIN_LOSS, pStock->szGain );
    }
}


CStocks::CStocks( HWND hwndMain, HWND hwndLv )
{
    memset( m_szFile, 0, sizeof( m_szFile ) );
    m_hFile         = INVALID_HANDLE_VALUE;
    m_hMapObj       = NULL;
    m_hMutex        = NULL;
    m_pStocks       = NULL;
    m_hwndMain      = hwndMain;
    m_hwndLv        = hwndLv;
    m_hChgEvent     = CreateEvent( NULL, FALSE, FALSE, SZ_CHANGE_EVENT );
}

CStocks::~CStocks()
{
    CloseHandle( m_hChgEvent );
    Close();
}

void CStocks::Close( void )
{
    if ( m_hMutex )
    {
        CloseHandle( m_hMutex );
        m_hMutex = NULL;
    }

    if ( m_pStocks )
    {
        UnmapViewOfFile( m_pStocks );
        m_pStocks = NULL;
    }
    
    if ( m_hMapObj )
    {
        CloseHandle( m_hMapObj );
        m_hMapObj = NULL;
    }
    
    if ( m_hFile != INVALID_HANDLE_VALUE )
    {
        CloseHandle( m_hFile );
        m_hFile = INVALID_HANDLE_VALUE;
    }
    memset( m_szFile, 0, sizeof( m_szFile ) );
}

LPSTR MakeMapObjName( LPSTR lpszFile )
{
static char v_szMapObjName[ MAX_PATH ];
    UINT    ix;
    LPSTR   lpsz;
    
    for ( ix = 0, lpsz = lpszFile; *lpsz; ix++, lpsz++ )
    {
        if ( *lpsz >= 'a' && *lpsz <= 'z' )
            v_szMapObjName[ix] = *lpsz - 'a' + 'A';
        else if ( *lpsz >= 'A' && *lpsz <= 'Z' )
            v_szMapObjName[ix] = *lpsz;
        else
            v_szMapObjName[ix] = 'A';
    }
    v_szMapObjName[ix] = 0;
    return v_szMapObjName;
}

BOOL CStocks::Open( LPSTR lpszFile, BOOL fFailOnNew )
{
    OPENFILENAME    of;
    char            szMsg[ MAX_PATH * 2 ];
    BOOL            fSuccess = FALSE;
    BOOL            fNewFile = TRUE;

    // must close existing file first
    Close();

    memset( &szMsg, 0, sizeof( szMsg ) );

    if ( lpszFile )
        lstrcpy( m_szFile, lpszFile );
    else
    {
        ClearStruct( of );
        of.lStructSize      = sizeof( of );
        of.hwndOwner        = m_hwndMain;
        of.lpstrTitle       = "Open Stock Portfolios";
        of.lpstrFilter      = "Stock Portfolios File (*.por)\0*.por\0";
        of.nFilterIndex     = 1;
        of.lpstrFile        = m_szFile;
        of.nMaxFile         = sizeof( m_szFile );
        of.Flags            = OFN_HIDEREADONLY;
        of.lpstrDefExt      = "por";
        if ( !GetOpenFileName( &of ) ) goto Exit;
    }

    fNewFile = ( GetFileAttributes( m_szFile ) == (DWORD)-1 );
    if ( fNewFile )
    {
        if ( fFailOnNew ) goto Exit;

        wsprintf( szMsg, "%s does not exist. Do you want to create a new file?", m_szFile );    
        if ( MessageBox( m_hwndMain, szMsg, "File does not exist", MB_YESNO | MB_ICONEXCLAMATION ) == IDNO )
        {
            szMsg[ 0 ] = 0;
            goto Exit;
        }
        szMsg[ 0 ] = 0;

        m_hFile = CreateFile( m_szFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                            NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
        if ( m_hFile == INVALID_HANDLE_VALUE )
        {
            wsprintf( szMsg, "Failed to create %s. Error: %d", m_szFile, GetLastError() );  
            goto Exit;
        }
    }
    else
    {
        m_hFile = CreateFile( m_szFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
        if ( m_hFile == INVALID_HANDLE_VALUE )
        {
            wsprintf( szMsg, "Failed to open %s. Error: %d", m_szFile, GetLastError() );    
            goto Exit;
        }
    }

    m_hMapObj = CreateFileMapping( m_hFile, NULL, PAGE_READWRITE, 0, sizeof( PORTFILE ), MakeMapObjName( m_szFile ) );
    if ( m_hMapObj == NULL )
    {
        wsprintf( szMsg, "Failed to create a file mapping using %s. Error: %d", m_szFile, GetLastError() );
        goto Exit;
    }

    // Get a pointer to the file-mapped shared memory:
    m_pStocks = (PPORTFILE)MapViewOfFile( m_hMapObj, FILE_MAP_WRITE, 0, 0, 0 );
    if ( m_pStocks == NULL ) 
    {
        wsprintf( szMsg, "Failed to map a file view on %s. Error: %d", m_szFile, GetLastError() );
        goto Exit;
    }

    // Get the Mutex
    if ( !m_hMutex )
        m_hMutex = CreateMutex( NULL, FALSE, SZ_MUTEX );

    if ( !m_hMutex )
    {
        wsprintf( szMsg, "Failed to create mutex named %s. Error: %d", SZ_MUTEX, GetLastError() );
        goto Exit;
    }
    
    if ( fNewFile )
    {
        WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT );

        ClearStruct( *m_pStocks );
        m_pStocks->uVer1        = PORTFILE_VERSION;
        m_pStocks->uVer2        = PORTFILE_VERSION;
        m_pStocks->uidCurrStock = 1;
        FlushViewOfFile( 0, sizeof( PORTFILE ) );

        ReleaseMutex( m_hMutex );
    }
    else
    {
        WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT );
        if ( m_pStocks->uVer1 != PORTFILE_VERSION || m_pStocks->uVer2 != PORTFILE_VERSION )
        {
            wsprintf( szMsg, "%s is not a valid portfolio file.", m_szFile );   
            ReleaseMutex( m_hMutex );
            goto Exit;
        }

        UpdateView();

        ReleaseMutex( m_hMutex );
    }

    fSuccess = TRUE;

Exit:
    if ( szMsg[0] )
        MessageBox( m_hwndMain, szMsg, "Error", MB_OK | MB_ICONSTOP );

    if ( !fSuccess )
        Close();
    else
    {
        wsprintf( szMsg, "Stock Portfolio - %s", m_szFile );
        SetWindowText( m_hwndMain, szMsg );
    }
    
    return fSuccess;
}

BOOL CStocks::BeforeAddChg( void )
{
    return m_szFile[0] || Open( NULL, FALSE );
}

/*++
PSTOCK CStocks::FindStock
    Find a stock using the stock ID, return NULL if not found.
    m_pStocks must be protected by the mutex before calling this routine and
    before finish using the pointer it returns
--*/
PSTOCK CStocks::FindStock( UINT uidStock, PUINT puix )
{
    UINT    ix;
    for ( ix = 0; ix < m_pStocks->cStocks; ix++  )
        if ( m_pStocks->rgStocks[ix].uidStock == uidStock )
            break;

    if ( puix )
        *puix = ix < m_pStocks->cStocks? ix : (UINT)-1;

    return ix < m_pStocks->cStocks? m_pStocks->rgStocks + ix: NULL;
}

/*++
void CStocks::SetViewItemText
--*/
void CStocks::SetViewItemText( UINT ix, PSTOCK pStock )
{
    char    sz[ 200 ];

    ListView_SetItemText( m_hwndLv, ix, 0, pStock->szSym );
    ListView_SetItemText( m_hwndLv, ix, 1, pStock->szCompany );
    ListView_SetItemText( m_hwndLv, ix, 2, pStock->szLastPrice );
    ListView_SetItemText( m_hwndLv, ix, 3, pStock->szPurDate );
    ListView_SetItemText( m_hwndLv, ix, 4, pStock->szPurPrice );
    ListView_SetItemText( m_hwndLv, ix, 5, pStock->szGain );
    ListView_SetItemText( m_hwndLv, ix, 6, FormatTime( &pStock->ftUpdated, sz ) );

    pStock->ftViewTime = pStock->ftUpdated;
}

/*++
void CStocks::UpdateView
    Update the list view with current list of stocks.
    m_pStocks must be protected by the mutex before calling this routine
--*/
void CStocks::UpdateView( void )
{
    int     ix, cItems;
    PSTOCK  pStock;

    for ( ix = 0, pStock = m_pStocks->rgStocks; ix < (int)m_pStocks->cStocks; ix++, pStock++ )
        pStock->uFlags &= ~SF_IN_VIEW;

    cItems = ListView_GetItemCount( m_hwndLv );
    for ( ix = 0; ix < cItems; ix++ )
    {
        LV_ITEM lvi;
        ClearStruct( lvi );
        lvi.iItem = ix;
        lvi.mask = LVIF_PARAM;
        if ( !ListView_GetItem( m_hwndLv, &lvi ) ) continue;

        pStock = FindStock( lvi.lParam );

        // remove deleted items from list view
        if ( !pStock )
        {
            ListView_DeleteItem( m_hwndLv, ix );
            ix--;
            cItems--;
            continue;
        }

        // update the item in list view if it's changed
        if ( CompareFileTime( &pStock->ftLastModified, &pStock->ftViewTime ) > 0 )
            SetViewItemText( ix, pStock );

        pStock->uFlags |= SF_IN_VIEW;
    }

    // add new items into list view
    for ( ix = 0, pStock = m_pStocks->rgStocks; ix < (int)m_pStocks->cStocks; ix++, pStock++ )
        if ( !( pStock->uFlags & SF_IN_VIEW ) )
            AddItem( pStock );


    ix = ListView_GetNextItem( m_hwndLv, -1, LVNI_SELECTED );

    EnableMenuItem( GetMenu( m_hwndMain ), IDC_CHANGE, m_pStocks->cStocks && ix >= 0? MF_ENABLED : MF_GRAYED );
    EnableMenuItem( GetMenu( m_hwndMain ), IDC_DELETE, m_pStocks->cStocks && ix >= 0? MF_ENABLED : MF_GRAYED );
    EnableMenuItem( GetMenu( m_hwndMain ), IDC_ADD, m_pStocks->cStocks >= MAX_STOCKS? MF_GRAYED : MF_ENABLED );
    DrawMenuBar( m_hwndMain );
}

/*++
--*/
void CStocks::AddItem( PSTOCK pStock )
{
    LV_ITEM     lvi;
    UINT        cItems = ListView_GetItemCount( m_hwndLv );

    ClearStruct( lvi );
    lvi.iItem       = cItems;
    lvi.mask        = LVIF_PARAM;
    lvi.lParam      = (LPARAM)pStock->uidStock;
    ListView_InsertItem( m_hwndLv, &lvi );

    SetViewItemText( cItems, pStock );  
}

/*++
BOOL CStocks::Add
    Takes input from the dialog and add a new stock 
--*/
BOOL CStocks::Add( HWND hDlg )
{
    STOCK       stock;

    UpdateItem( hDlg, &stock, TRUE );

    WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT );

    stock.uidStock = m_pStocks->uidCurrStock;
    GetLocalFileTime( &stock.ftLastModified );
    m_pStocks->uidCurrStock++;
    m_pStocks->rgStocks[ m_pStocks->cStocks ] = stock;
    m_pStocks->cStocks++;

    // add the stock id to the change/delete log so we can sync it
    if ( m_pStocks->cChg < Dim( m_pStocks->rgidChg ) - 1 )
        m_pStocks->rgidChg[ m_pStocks->cChg++ ] = stock.uidStock;
    AddItem( &stock );

    if ( m_pStocks->cStocks >= MAX_STOCKS )
    {
        EnableMenuItem( GetMenu( GetParent( hDlg ) ), IDC_ADD_CHG, MF_BYCOMMAND | MF_GRAYED );
        DrawMenuBar( GetParent( hDlg ) );
    }

    ReleaseMutex( m_hMutex );

    // let the sync module to synchronize now!
    SetEvent( m_hChgEvent );
    return TRUE;
}

/*++
--*/
void CStocks::Delete( UINT uParam )
{
    UINT    ix;
    PSTOCK  pStock;

    WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT );

    pStock = FindStock( uParam, &ix );
    if ( pStock )
    {
        // add the stock id to the change/delete log so we can sync it
        if ( m_pStocks->cDel < Dim( m_pStocks->rgidDel ) - 1 )
            m_pStocks->rgidDel[ m_pStocks->cDel++ ] = pStock->uidStock;

        m_pStocks->cStocks--;
        if ( ix != m_pStocks->cStocks )
            memmove( m_pStocks->rgStocks + ix, 
                     m_pStocks->rgStocks + ix + 1, 
                     ( m_pStocks->cStocks - ix ) * sizeof( m_pStocks->rgStocks[0] ) );
    }

    ReleaseMutex( m_hMutex );

    // let the sync module to synchronize now!
    SetEvent( m_hChgEvent );
}

/*++
BOOL CStocks::SetupDlg
    Setup the Add/Change dialog with the given uParam of the selected item in list view
--*/
BOOL CStocks::SetupDlg( HWND hDlg, UINT uParam )
{
    BOOL    fRet = FALSE;

    WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT );

    PSTOCK  pStock = FindStock( uParam );
    if ( pStock )
    {
        UpdateItem( hDlg, pStock, FALSE );
        fRet = TRUE;
    }

    ReleaseMutex( m_hMutex );
    return fRet;
}

/*++
BOOL CStocks::Change
    Change the stock using data from the dialog
--*/
BOOL CStocks::Change( HWND hDlg, UINT uParam )
{
    BOOL    fRet = FALSE;
    WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT );

    PSTOCK  pStock = FindStock( uParam );
    if ( pStock )
    {
        // add the stock id to the change/delete log so we can sync it
        if ( m_pStocks->cChg < Dim( m_pStocks->rgidChg ) - 1 )
            m_pStocks->rgidChg[ m_pStocks->cChg++ ] = uParam;

        GetLocalFileTime( &pStock->ftLastModified );
        UpdateItem( hDlg, pStock, TRUE );
        UpdateView();
        fRet = TRUE;
    }

    ReleaseMutex( m_hMutex );

    // let the sync module to synchronize now!
    SetEvent( m_hChgEvent );
    return fRet;
}

/*++
void CStocks::OnDataChange
    Responds to data change notification and update the list view
--*/
void CStocks::OnDataChange( void )
{
    WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT );
    UpdateView();
    ReleaseMutex( m_hMutex );
}

/*++
void CStocks::SyncNow
    Find the syncmgr.exe in Windows CE Services and ask it to synchronize now
--*/
void CStocks::SyncNow( void )
{
    HKEY    hKey;
    DWORD   cb, dwType;
    char    szExePath[ MAX_PATH ];

    if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows CE Services", 
                       0, KEY_READ, &hKey ) == ERROR_SUCCESS )
    {
        cb = sizeof( szExePath ) - 30;
        if ( RegQueryValueEx( hKey, "InstalledDir", 0, &dwType, (BYTE*)szExePath, &cb ) == ERROR_SUCCESS )
        {
            if ( szExePath[ lstrlen( szExePath ) - 1 ] != '\\')
                lstrcat( szExePath, "\\" );
            lstrcat( szExePath, "syncmgr.exe /syncnow" );
            WinExec( szExePath, 0 );
        }
        RegCloseKey( hKey );
    }
}
