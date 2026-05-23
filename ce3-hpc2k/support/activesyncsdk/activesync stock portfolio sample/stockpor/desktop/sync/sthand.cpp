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
    
      replhand.cpp

Abstract:

    Implementation of IReplObjHandler class

--*/

#include <windows.h>
#include "mainmod.h"

void GetLocalFileTime( FILETIME *pft )
{
    SYSTEMTIME  st;
    GetLocalTime( &st );
    SystemTimeToFileTime( &st, pft );
}

/*++
--*/
CDataHandler::CDataHandler( CStore *pStore )
{
    m_pStore = pStore;
}

/*++
--*/
CDataHandler::~CDataHandler()
{
}

/*++
--*/
STDMETHODIMP CDataHandler::QueryInterface( REFIID iid, LPVOID  *ppvObj )
{
    *ppvObj = NULL;   // set to NULL, in case we fail.

    if ( IsEqualIID( iid, IID_IUnknown ) )
        *ppvObj = (void*)this;

    if ( *ppvObj )
    {
        ((IUnknown *)(*ppvObj))->AddRef();
        return NOERROR;
    }
    return E_NOINTERFACE;
}

/*++
--*/
STDMETHODIMP_(ULONG) CDataHandler::AddRef()
{
    // don't need reference counting
    return 0;
}

/*++
--*/
STDMETHODIMP_(ULONG) CDataHandler::Release()
{
    // don't need reference counting
    return 0;
}


//
//
//

/*++
--*/
STDMETHODIMP CDataHandler::Setup
( 
    PREPLSETUP pSetup   // Points to REPLSETUP, which has information about the object to be serialized/deserialized
)
{
    // we could be reading and writing at the same time, so need to save the pointer to setup struct differently
    if ( pSetup->fRead )
        m_pReadSetup = pSetup;
    else
        m_pWriteSetup = pSetup;

    return NOERROR;
}

BOOL CALLBACK FindStockWin( HWND hwnd, LPARAM lParam )
{
    char    szName[ MAX_PATH * 2 ];

    GetClassName( hwnd, szName, sizeof( szName ) );
    if ( !lstrcmp( szName, SZ_WND_CLASS ) )
        PostMessage( hwnd, WM_DATA_CHANGED, 0, 0 );

    return TRUE;
}

/*++
--*/
STDMETHODIMP CDataHandler::Reset
( 
    PREPLSETUP pSetup   // Points to REPLSETUP, which has information about the object just serialized/deserialized
)
{
    // we don't have any resources we need to free
    return NOERROR;
}

/*++
--*/
STDMETHODIMP CDataHandler::GetPacket
( 
    LPBYTE  *lppbPacket, 
    DWORD   *pcbPacket, 
    DWORD   cbRecommend 
)
{
    PSTOCK      pStock;

    if ( m_pReadSetup->hItem == NULL )
        return E_UNEXPECTED;

    m_pStore->Lock();

    // setup the packet
    ClearStruct( m_packet );
    pStock = m_pStore->FindStock( ((PITEM)m_pReadSetup->hItem)->m_uid );
    if ( pStock )
    {
        MultiByteToWideChar( CP_ACP, 0, pStock->szSym, -1, m_packet.wszSym, sizeof( m_packet.wszSym ) - 1 );
        MultiByteToWideChar( CP_ACP, 0, pStock->szCompany, -1, m_packet.wszCompany, sizeof( m_packet.wszCompany ) - 1 );
        MultiByteToWideChar( CP_ACP, 0, pStock->szLastPrice, -1, m_packet.wszLastPrice, sizeof( m_packet.wszLastPrice ) - 1 );
        MultiByteToWideChar( CP_ACP, 0, pStock->szPurDate, -1, m_packet.wszPurDate, sizeof( m_packet.wszPurDate ) - 1 );
        MultiByteToWideChar( CP_ACP, 0, pStock->szPurPrice, -1, m_packet.wszPurPrice, sizeof( m_packet.wszPurPrice ) - 1 );
        MultiByteToWideChar( CP_ACP, 0, pStock->szGain, -1, m_packet.wszGain, sizeof( m_packet.wszGain ) - 1 );
        m_packet.ftUpdated = pStock->ftUpdated;
    }

    m_pStore->Unlock();

    *pcbPacket = sizeof( m_packet );
    *lppbPacket = (LPBYTE)&m_packet;

    return pStock? RWRN_LAST_PACKET : E_UNEXPECTED;
}


/*++
--*/
STDMETHODIMP CDataHandler::SetPacket( LPBYTE lpbPacket, DWORD cbPacket )
{
    // write the packet
    if ( cbPacket != sizeof( STPACKET ) )
        return E_UNEXPECTED;

    PSTPACKET   pPacket = (PSTPACKET)lpbPacket;
    PSTOCK      pStock = NULL;
    PITEM       pItem = new CItem;
    STOCK       stock;

    if ( !pItem )
        return E_OUTOFMEMORY;

    m_pStore->Lock();

    // write the packet
    WideCharToMultiByte( CP_ACP, 0, pPacket->wszSym, -1, stock.szSym, sizeof( stock.szSym ) - 1, NULL, NULL );
    WideCharToMultiByte( CP_ACP, 0, pPacket->wszCompany, -1, stock.szCompany, sizeof( stock.szCompany ) - 1, NULL, NULL );
    WideCharToMultiByte( CP_ACP, 0, pPacket->wszLastPrice, -1, stock.szLastPrice, sizeof( stock.szLastPrice ) - 1, NULL, NULL );
    WideCharToMultiByte( CP_ACP, 0, pPacket->wszPurDate, -1, stock.szPurDate, sizeof( stock.szPurDate ) - 1, NULL, NULL );
    WideCharToMultiByte( CP_ACP, 0, pPacket->wszPurPrice, -1, stock.szPurPrice, sizeof( stock.szPurPrice ) - 1, NULL, NULL );
    WideCharToMultiByte( CP_ACP, 0, pPacket->wszGain, -1, stock.szGain, sizeof( stock.szGain ) - 1, NULL, NULL );
    stock.ftUpdated = pPacket->ftUpdated;
    GetLocalFileTime( &stock.ftLastModified );

    // change an existing stock or create a new stock
    if ( m_pWriteSetup->hItem )
    {
        pStock = m_pStore->FindStock( ((PITEM)m_pWriteSetup->hItem)->m_uid );
        if ( pStock )
        {
            stock.uidStock = pStock->uidStock;
            stock.uFlags = pStock->uFlags;
            stock.ftViewTime = pStock->ftViewTime;
            *pStock = stock;
        }
    }
    else
    {
        if ( m_pStore->m_pStocks->cStocks < MAX_STOCKS - 1 )
        {
            stock.uidStock = m_pStore->m_pStocks->uidCurrStock;
            stock.ftViewTime = stock.ftLastModified;
            m_pStore->m_pStocks->uidCurrStock++;
            m_pStore->m_pStocks->rgStocks[ m_pStore->m_pStocks->cStocks ] = stock;
            m_pStore->m_pStocks->cStocks++;
            pStock = &stock;
        }
    }

    if ( pStock )
    {
        pItem->m_uid = pStock->uidStock;
        pItem->m_ftModified = stock.ftLastModified;
    }

    m_pStore->Unlock();

    // find all instance of Stock Portfolio application and post a message to let it refersh
    if ( pStock )
    {
        m_pWriteSetup->hItem = (HREPLITEM)pItem;
        EnumWindows( (WNDENUMPROC)FindStockWin, NULL );
    }
    else
        delete pItem;

    return pStock? NOERROR : E_UNEXPECTED;
}

/*++
--*/
STDMETHODIMP CDataHandler::DeleteObj
( 
    PREPLSETUP  pSetup
)
{
    UINT    ix;
    PSTOCK  pStock;

    if ( !pSetup->hItem ) return E_UNEXPECTED;
    m_pStore->Lock();

    pStock = m_pStore->FindStock( ((PITEM)pSetup->hItem)->m_uid, &ix );
    if ( !pStock )
    {
        m_pStore->Unlock();
        return HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND );
    }

    m_pStore->m_pStocks->cStocks--;
    if ( ix != m_pStore->m_pStocks->cStocks )
        memmove( m_pStore->m_pStocks->rgStocks + ix, 
                 m_pStore->m_pStocks->rgStocks + ix + 1, 
                 ( m_pStore->m_pStocks->cStocks - ix ) * sizeof( m_pStore->m_pStocks->rgStocks[0] ) );

    m_pStore->Unlock();

    // find all instance of Stock Portfolio application and post a message to let it refersh
    EnumWindows( (WNDENUMPROC)FindStockWin, NULL );
    return NOERROR;
}


/*++
--*/
STDMETHODIMP CStore::RemoveDuplicates
( 
    LPSTR   lpszObjType,  // Points to the name of object type for which this operation is intended. NULL if all object types should be checked.
    UINT    uFlags        // Reserved. Always 0.
)
{
    if ( lpszObjType && lstrcmp( lpszObjType, SZ_STOCKPOR ) )
        return E_NOTIMPL;

    UINT    ix, jx;
    PSTOCK  ps1, ps2;
    BOOL    fUpdate = FALSE;

    Lock();

    for ( ix = 0, ps1 = m_pStocks->rgStocks; ix < m_pStocks->cStocks; ix++, ps1++ )
    {
        for ( jx = ix + 1, ps2 = m_pStocks->rgStocks + jx; jx < m_pStocks->cStocks; jx++, ps2++ )
        {
            if ( !lstrcmp( ps1->szSym, ps2->szSym ) &&
                 !lstrcmp( ps1->szCompany, ps2->szCompany ) &&
                 !lstrcmp( ps1->szLastPrice, ps2->szLastPrice ) &&
                 !lstrcmp( ps1->szPurPrice, ps2->szPurPrice ) &&
                 !lstrcmp( ps1->szPurDate, ps2->szPurDate ) &&
                 !lstrcmp( ps1->szGain, ps2->szGain ) )
            {
                // notify ActiveSync service manager that this stock is deleted
                PITEM   pItem = MakeNewItem( ps2->uidStock );
                if ( pItem &&
                     FAILED( m_pNotify->OnItemNotify( RNC_DELETED, SZ_STORE_PROG_ID, SZ_STOCKPOR, (HREPLITEM)pItem, 0 ) ) )
                        delete pItem;

                // remove this stock
                m_pStocks->cStocks--;
                if ( jx != m_pStocks->cStocks )
                    memmove( ps2, ps2 + 1, ( m_pStocks->cStocks - jx ) * sizeof( m_pStocks->rgStocks[0] ) );
                jx--;

                fUpdate = TRUE;
                continue;
            }
        }
    }

    Unlock();

    if ( fUpdate )
    {
        // find all instance of Stock Portfolio application and post a message to let it refersh
        EnumWindows( (WNDENUMPROC)FindStockWin, NULL );
    }
    return NOERROR;
}

