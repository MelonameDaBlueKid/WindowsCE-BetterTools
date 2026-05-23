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
    
      stockpor.cpp

Abstract:

    Stock Portfolio sample app. for Windows 95/NT to demonstrate synchronization with a
Windows CE app.

--*/

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include "resource.h"
#include "common.h"

// define class CStocks
#ifdef UNDER_CE
    #include "device\stocks.h"
#else
    #include "desktop\stocks.h"
#endif

#define SZ_WND_NAME         TEXT( "Stock Portfolios" )

#ifdef UNDER_CE
    #define WS_OUR_STYLE    WS_VISIBLE
    HWND    v_hwndCommBar;
    LPTSTR  v_lpszDBVol;

    // list view column width
    #define COMP_WIDTH  120
    #define PRICE_WIDTH 65
    #define PUR_WIDTH   60
    #define MOD_WIDTH   100

    #define PRICE       TEXT( "Price" )
    #define PUR_DATE    TEXT( "Pur. Date" )
    #define PUR_PRICE   TEXT( "Pur. Price" )
#else
    #define WS_OUR_STYLE    WS_OVERLAPPEDWINDOW | WS_VISIBLE

    // list view column width
    #define COMP_WIDTH  160
    #define PRICE_WIDTH 65
    #define PUR_WIDTH   90
    #define MOD_WIDTH   120

    #define PRICE       TEXT( "Last Price" )
    #define PUR_DATE    TEXT( "Purchase Date" )
    #define PUR_PRICE   TEXT( "Purchase Price" )
#endif

HINSTANCE   v_hInstance;
HWND        v_hwndMain, v_hwndLv;
CStocks     *v_pStocks;
BOOL        v_fAddStock;

typedef struct tagColInfo
{
    LPTSTR  lpszName;
    UINT    uWidth;
    BYTE    bAlign;
    BYTE    bSortOrder;
} COLINFO, *PCOLINFO;

static COLINFO v_rgCol[] =
{
    { TEXT( "Sym." ),           40,             LVCFMT_LEFT,    0 },
    { TEXT( "Company Name" ),   COMP_WIDTH,     LVCFMT_LEFT,    0 },
    { PRICE,                    PRICE_WIDTH,    LVCFMT_LEFT,    0 },
    { PUR_DATE,                 PUR_WIDTH,      LVCFMT_LEFT,    0 },
    { PUR_PRICE,                PUR_WIDTH,      LVCFMT_LEFT,    0 },
    { TEXT( "Gain/Loss" ),      65,             LVCFMT_LEFT,    0 },
    { TEXT( "Last Updated" ),   MOD_WIDTH,      LVCFMT_LEFT,    0 },
};

LONG APIENTRY MainWndProc( HWND hWnd, UINT message, UINT wParam, LONG lParam );

/*++
--*/
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
    WNDCLASS    wc;
    MSG         msg;
    HMENU       hMenu = NULL;
    HINSTANCE   hInstCtrl = NULL;

    v_hInstance = hInstance;
    ClearStruct( wc );

    wc.lpfnWndProc     = (WNDPROC)MainWndProc;
    wc.hInstance       = hInstance;
    wc.hIcon           = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON ) );
    wc.hbrBackground   = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName   = SZ_WND_CLASS;
    if ( !RegisterClass( &wc ) )
        return 0;

#ifndef UNDER_CE
    FARPROC     pInit;

    hInstCtrl = LoadLibrary( TEXT( "COMCTL32.DLL" ) );
    if ( !hInstCtrl )
        return 0;

    if ( ( pInit = GetProcAddress( hInstCtrl, TEXT( "InitCommonControls" ) ) ) != NULL )
        (*pInit)();

    hMenu = LoadMenu( hInstance, MAKEINTRESOURCE( IDR_MAIN_MENU ) );
#else
    InitCommonControls();
#endif

    v_hwndMain = CreateWindow( SZ_WND_CLASS, SZ_WND_NAME, WS_OUR_STYLE,
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                               NULL, hMenu, hInstance, NULL );
    if ( !v_hwndMain )
    {
        if ( hMenu )
            DestroyMenu( hMenu );
        return 0;
    }

#ifdef UNDER_CE
    if ( v_hwndCommBar )
        CommandBar_Show( v_hwndCommBar, nCmdShow );

    HKEY    hKey;
    long    lErr;
    DWORD   dw;
    LPTSTR  lpszTitle;

    // open the registry key where database volume is stored
    lErr = RegOpenKeyEx( HKEY_LOCAL_MACHINE, SZ_REG_ROOT, 0, KEY_READ, &hKey );
    if ( lErr != ERROR_SUCCESS )
        lErr = RegCreateKeyEx( HKEY_LOCAL_MACHINE, SZ_REG_ROOT, 0, 0, REG_OPTION_NON_VOLATILE, KEY_WRITE, 0, &hKey, &dw );

    // save command line parameter as the database volume we want to use
    v_lpszDBVol = ( lpCmdLine == NULL )? TEXT( "" ) : lpCmdLine;

    if ( lErr == ERROR_SUCCESS )
    {
        RegSetValueEx( hKey, SZ_REG_DBVOL, NULL, REG_SZ, (const LPBYTE)v_lpszDBVol, ( lstrlen( v_lpszDBVol ) + 1 ) * sizeof( TCHAR ) );
        RegCloseKey( hKey );
    }

    // change the main window title based on the given database volume name
    if ( lpCmdLine == NULL || *lpCmdLine == 0 )
        lpCmdLine = TEXT( "System Volume" );

    lpszTitle = new TCHAR[ lstrlen( SZ_WND_NAME ) + lstrlen( lpCmdLine ) + 5 ];
    wsprintf( lpszTitle, TEXT( "%s - %s" ), lpCmdLine, SZ_WND_NAME );
    SetWindowText( v_hwndMain, lpszTitle );
    delete lpszTitle;
#endif

    ShowWindow( v_hwndMain, nCmdShow );

    v_pStocks = new CStocks( v_hwndMain, v_hwndLv );

    while ( GetMessage( &msg, NULL, 0, 0 ) )
    {
#ifdef UNDER_CE
        if ( !v_hwndCommBar || !IsCommandBarMessage( v_hwndCommBar, &msg ) )
#endif
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    delete v_pStocks;

    if ( hMenu )
        DestroyMenu( hMenu );

    if ( hInstCtrl )
        FreeLibrary( hInstCtrl );
    UnregisterClass( SZ_WND_CLASS, hInstance );
    return 0;
}

/*++
UINT SzToPrice
    Convert a string into a intergal price in the unit of 1/100th of a cent 
    (ie. 1/10000th of a dollar). The given string may have a leading dollar 
    sign. Returns 0 in case of unrecognizable string
--*/
UINT SzToPrice( LPTSTR lpszPrice )
{
    LPTSTR   lpsz = lpszPrice;
    UINT    u = 0, uFrac = 0, uOrder, u1, u2;
    BOOL    fSuccess = FALSE;

    // skip spaces
    while ( *lpsz && *lpsz == TEXT( ' ' ) )
        lpsz++;

    if ( *lpsz == '$' )
        lpsz++;

    // skip more spaces
    while ( *lpsz && *lpsz == ' ' )
        lpsz++;

    // the integer
    while ( *lpsz && *lpsz != '.' && *lpsz != ' ' && *lpsz != '/' )
    {
        if ( *lpsz < '0' || *lpsz > '9' )
            goto Exit;

        u = u * 10 + *lpsz - '0';
        lpsz++;
    }

    // calculate uFrac
    if ( *lpsz == '.' )
    {
        lpsz++;
        uOrder = 100 * 100;
        while ( *lpsz )
        {
            if ( *lpsz < '0' || *lpsz > '9' )
                goto Exit;

            uFrac = uFrac * 10 + *lpsz - '0';
            uOrder /= 10;
            if ( uOrder == 1 )
                break;
            lpsz++;
        }
        uFrac *= uOrder;
    }
    else if ( *lpsz == ' ' || *lpsz == '/' )
    {
        if ( *lpsz == ' ' )
        {
            // skip more spaces
            while ( *lpsz && *lpsz == ' ' )
                lpsz++;

            u1 = 0;
            while ( *lpsz && *lpsz != '/' )
            {
                if ( *lpsz < '0' || *lpsz > '9' )
                    goto Exit;
                u1 = u1 * 10 + *lpsz - '0';
                lpsz++;
            }

            if ( *lpsz != '/' ) goto Exit;
        }
        else
        {
            u1 = u;
            u = 0;
        }

        lpsz++;
        u2 = 0;
        while ( *lpsz )
        {
            if ( *lpsz < '0' || *lpsz > '9' )
                goto Exit;
            u2 = u2 * 10 + *lpsz - '0';
            lpsz++;
        }

        if ( u2 == 0 ) goto Exit;
        uFrac = u1 * 100 * 100 / u2;
    }
    else if ( *lpsz )
        goto Exit;

    // u is in dollar, convert it into 1/100 of a cent
    u *= 100 * 100;

    fSuccess = TRUE;

Exit:
    return fSuccess? u + uFrac: 0;
}

//
// ================ Add/Change Stock Dialog ==========================
//
BOOL CALLBACK dlgAddChg( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    int     iSel;
    LV_ITEM lvi;

    switch( uMsg )
    {
    case WM_INITDIALOG:
        if ( v_fAddStock )
        {
            SetDlgItemText( hDlg, IDC_ADD_CHG, TEXT( "&Add" ) );
        }
        else
        {
            iSel = ListView_GetNextItem( v_hwndLv, -1, LVNI_SELECTED );
            if ( iSel < 0 )
            {
                MessageBox( hDlg, TEXT( "Couldn't find a selected stock." ), TEXT( "Error" ), MB_OK | MB_ICONSTOP );
                PostMessage( hDlg, WM_COMMAND, IDCANCEL, 0 );
            }
            else
            {
                LV_ITEM lvi;
                ClearStruct( lvi );
                lvi.iItem = iSel;
                lvi.mask = LVIF_PARAM;
                if ( !ListView_GetItem( v_hwndLv, &lvi ) || !v_pStocks->SetupDlg( hDlg, lvi.lParam ) )
                {
                    MessageBox( hDlg, TEXT( "Unable to change stock." ), TEXT( "Error" ), MB_OK | MB_ICONSTOP );
                    PostMessage( hDlg, WM_COMMAND, IDCANCEL, 0 );
                }

                SetDlgItemText( hDlg, IDC_ADD_CHG, TEXT ( "&Change" ) );
            }
        }
        return TRUE;

    case WM_COMMAND:
        switch( LOWORD( wParam ) )
        {
        case IDC_ADD_CHG:
            if ( v_fAddStock )
            {
                if ( v_pStocks->Add( hDlg ) )
                    EndDialog( hDlg, IDOK ); 
            }
            else
            {
                iSel = ListView_GetNextItem( v_hwndLv, -1, LVNI_SELECTED );
                if ( iSel >= 0 )
                {
                    ClearStruct( lvi );
                    lvi.iItem = iSel;
                    lvi.mask = LVIF_PARAM;
                    if ( ListView_GetItem( v_hwndLv, &lvi ) && v_pStocks->Change( hDlg, lvi.lParam ) )
                        EndDialog( hDlg, IDOK ); 
                }
            }
            break;

        case IDCANCEL:      
            EndDialog( hDlg, IDCANCEL ); 
            break;

        case IDC_LAST_PRICE:
        case IDC_PUR_PRICE:
            if ( HIWORD( wParam ) == EN_CHANGE )
            {
                TCHAR   sz[ 80 ];
                UINT    uLast, uPur;

                // update the gain/loss field
                GetDlgItemText( hDlg, IDC_LAST_PRICE, sz, sizeof( sz ) );
                uLast = SzToPrice( sz );

                GetDlgItemText( hDlg, IDC_PUR_PRICE, sz, sizeof( sz ) );
                uPur = SzToPrice( sz );

                if ( !uPur || !uLast )
                    lstrcpy( sz, TEXT( "N/A" ) );
                else if ( uPur < uLast )
                    wsprintf( sz, TEXT( "Gain %d%%" ), uLast * 100 / uPur - 100 );
                else if ( uPur > uLast )
                    wsprintf( sz, TEXT( "Loss %d%%" ), 100 - uLast * 100 / uPur );
                else
                    lstrcpy( sz, TEXT( "Even" ) );

                SetDlgItemText( hDlg, IDC_GAIN_LOSS, sz );

            }
            break;
        };
        break;
    }
    return FALSE;
}


//
// ================ Messages and Command Handlers ==========================
//

/*++
--*/
void OnAddChg( void )
{
    if ( v_pStocks->BeforeAddChg() )
        DialogBox( v_hInstance, TEXT( "Add_Change" ), v_hwndMain, (DLGPROC)dlgAddChg );
}

/*++
--*/
void OnDelete( void )
{
    LV_ITEM lvi;
    UINT    ix, cDeleted, cItems = ListView_GetItemCount( v_hwndLv );
    LPARAM  *rgParam = new LPARAM[ cItems ];

    if ( rgParam == NULL ) return;

    cDeleted = 0;
    for ( ix = 0; ix < cItems; ix++ )
    {
        ClearStruct( lvi );

        lvi.mask = LVIF_PARAM | LVIF_STATE;
        lvi.iItem = ix;
        lvi.stateMask = 0x000F;

        if ( ListView_GetItem( v_hwndLv, &lvi ) && ( lvi.state & LVIS_SELECTED ) )
            rgParam[ cDeleted++ ] = lvi.lParam;
    }

    for ( ix = 0; ix < cDeleted; ix++ )
        v_pStocks->Delete( rgParam[ ix ] );

    delete [] rgParam;

    // update the list view
    PostMessage( v_hwndMain, WM_DATA_CHANGED, 0, 0 );
}

/*++
--*/
void OnSize( HWND hwnd, UINT state, int cx, int cy )
{
#ifdef UNDER_CE
    if ( v_hwndCommBar )
        cy -= CommandBar_Height( v_hwndCommBar );
#endif
    if ( v_hwndLv )
        SetWindowPos( v_hwndLv, NULL, 0, 0, cx, cy, SWP_NOMOVE );
}

/*++
--*/
BOOL OnCreate( HWND hwnd, LPCREATESTRUCT lpCreateStruct )
{
    UINT        ix, y = 0;
    LV_COLUMN   lvc;

#ifdef UNDER_CE
    // Create a command bar
    if ( !( v_hwndCommBar = CommandBar_Create( v_hInstance, hwnd, 1 ) ) )
        return FALSE;

    // Add the menus and adornments
    if ( !CommandBar_InsertMenubar( v_hwndCommBar, v_hInstance, IDR_MAIN_MENU, 0 ) )
        return FALSE;

    if ( !CommandBar_AddAdornments( v_hwndCommBar, 0, 0 ) )
        return FALSE;

    y = CommandBar_Height( v_hwndCommBar );
#endif

    v_hwndLv = CreateWindowEx( 0, WC_LISTVIEW, TEXT(""),
        WS_CHILD | WS_VISIBLE | LVS_AUTOARRANGE | LVS_REPORT | LVS_SHOWSELALWAYS,
        0, y, 0, 0, hwnd, (HMENU)IDC_VIEW, v_hInstance, NULL );
    if ( !v_hwndLv )
        return FALSE;

    ClearStruct( lvc );
    lvc.mask    = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;  
    for ( ix = 0; ix < Dim( v_rgCol ); ix++ )
    {
        lvc.iSubItem    = ix;
        lvc.pszText     = v_rgCol[ix].lpszName;
        lvc.cchTextMax  = lstrlen( v_rgCol[ix].lpszName );
        lvc.cx          = v_rgCol[ix].uWidth;
        lvc.fmt         = v_rgCol[ix].bAlign;

        ListView_InsertColumn( v_hwndLv, ix, &lvc );
    }

    PostMessage( hwnd, WM_COMMAND, IDC_OPEN, 111 );
    return TRUE;
}

/*++
--*/
void OnNotify( int idCtrl, LPNMHDR pHdr )
{
    if ( idCtrl != IDC_VIEW ) return;

    NM_LISTVIEW *pNMLV = (NM_LISTVIEW *)pHdr;

    switch( pHdr->code )
    {
    case NM_DBLCLK:
        PostMessage( v_hwndMain, WM_COMMAND, IDC_CHANGE, 0 );
        break;

    case LVN_ITEMCHANGED:
        if ( pNMLV->uChanged & LVIF_STATE )
        {
            HMENU   hMenu;

#ifdef UNDER_CE
            hMenu = CommandBar_GetMenu( v_hwndCommBar, 0 );
#else
            hMenu = GetMenu( v_hwndMain );
#endif

            int ix = ListView_GetNextItem( v_hwndLv, -1, LVNI_SELECTED );

            EnableMenuItem( hMenu, IDC_DELETE, ix >= 0? MF_ENABLED : MF_GRAYED );
            EnableMenuItem( hMenu, IDC_CHANGE, ix >= 0? MF_ENABLED : MF_GRAYED );

#ifdef UNDER_CE
            CommandBar_Show( v_hwndCommBar, FALSE );
            CommandBar_Show( v_hwndCommBar, TRUE );
#else
            DrawMenuBar( v_hwndMain );
#endif
        }
        break;
    }
}

//
// ================ Main Window Proc ==========================
//
/*++
--*/
LONG APIENTRY MainWndProc( HWND hwnd, UINT uMsg, UINT wParam, LONG lParam )
{
    LONG    lResult = 0;
    int     iSel;

    switch ( uMsg )
    {
    HANDLE_MSG( hwnd, WM_SIZE, OnSize );
    HANDLE_MSG( hwnd, WM_CREATE, OnCreate );

    case WM_DATA_CHANGED:
        v_pStocks->OnDataChange();
        break;

    case WM_COMMAND:
        switch( wParam )
        {
        case IDC_OPEN:      
            // try open the default file first, if requested (lParam == 111)
            if ( lParam == 111 && v_pStocks->Open( SZ_DEFAULT_PORTFILE, TRUE ) )
                break;

            v_pStocks->Open( NULL, FALSE );
            break;

        case IDC_ADD:   
            v_fAddStock = TRUE;
            OnAddChg(); 
            break;

        case IDC_CHANGE:
            iSel = ListView_GetNextItem( v_hwndLv, -1, LVNI_SELECTED );
            if ( iSel >= 0 )
            {
                v_fAddStock = FALSE;
                OnAddChg();
            }
            break;

        case IDC_DELETE:
            if ( MessageBox( v_hwndMain, TEXT( "Are you sure to delete selected stocks?" ), TEXT( "Warning" ), MB_YESNO | MB_ICONEXCLAMATION ) == IDYES )
            {
                OnDelete(); 
            }
            break;

        case IDC_SYNC_NOW:
            v_pStocks->SyncNow();
            break;
        };
        break;

    case WM_NOTIFY:
        OnNotify( (int)wParam, (LPNMHDR)lParam );
        break;

    case WM_DESTROY:                  
#ifdef UNDER_CE
        if ( v_hwndCommBar )
            CommandBar_Destroy( v_hwndCommBar );
#endif

        PostQuitMessage(0);
        break;

    default:
        lResult = DefWindowProc( hwnd, uMsg, wParam, lParam );
        break;
    }

    return lResult;
}


