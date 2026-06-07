/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/
#include <cesync.h>
#include "..\..\common.h"
#include "..\..\resource.h"

class CStore;
class CDataHandler;

#define OBJECT_VERSION  1

#define OT_ITEM     1
#define OT_FOLDER   2

// {A95CFA71-1659-4b37-9695-3782E7A35EE6}
//DEFINE_GUID(<<name>>, 
//0xa95cfa71, 0x1659, 0x4b37, 0x96, 0x95, 0x37, 0x82, 0xe7, 0xa3, 0x5e, 0xe6);
#define SZ_GUID_SYNCSAMPLE    "{A95CFA71-1659-4b37-9695-3782E7A35EE6}"
#define SZ_NAME               "StockPor"
#define SZ_DISPLAY_NAME       "Stock Sample"
#define SZ_PLURAL_NAME        "Stock Sample"



class CReplObject
{
public:
    virtual ~CReplObject() {}

    UINT    m_uType;
};

#define SO_ALL      0
#define SO_AM       1
#define SO_NZ       2

class CFolder: public CReplObject
{
public:
    CFolder( void )     { m_uType = OT_FOLDER; m_fChanged = FALSE; }
    virtual ~CFolder()  {}

    BOOL    m_fChanged;
};

class CItem: public CReplObject
{
public:
    CItem( void )       { m_uType = OT_ITEM; ClearStruct( m_ftModified ); }
    virtual ~CItem()    {}

    UINT        m_uid;
    FILETIME    m_ftModified;
};

typedef CItem *PITEM;

// 
//  === Handler to serialize/deserialize objects ====================
//
class CDataHandler : public IReplObjHandler
{
public:
    CDataHandler( CStore *pStore );
    ~CDataHandler();

    // ******** IUnknown methods **************
    STDMETHODIMP_(ULONG)    AddRef( void );
    STDMETHODIMP_(ULONG)    Release( void );
    STDMETHODIMP            QueryInterface( REFIID riid, void **ppvObject );
    
    // ******** IReplObjHandler methods **************
    STDMETHODIMP Setup( PREPLSETUP pSetup );
    STDMETHODIMP Reset( PREPLSETUP pSetup );

    STDMETHODIMP GetPacket( LPBYTE *lppbData,  DWORD *pcbData, DWORD cbRecommend );
    STDMETHODIMP SetPacket( LPBYTE lpbData, DWORD cbData );
    STDMETHODIMP DeleteObj( PREPLSETUP pSetup );

private:
    long        m_cRef;
    CStore      *m_pStore;
    PREPLSETUP  m_pWriteSetup, m_pReadSetup;
    STPACKET    m_packet;
};

#define ISF_INITIALIZED ((UINT)0x80000000)  // set if the store was initialized successfully

/////////////////////////////////////////////////////////////////////////////
class CStore: public IReplStore2
{
private:
    LONG                m_cRef;
    LPUNKNOWN           m_pUnkOuter;

public:
    CStore( LPUNKNOWN );
    ~CStore();

    // ******** IUnknown methods **************
    STDMETHODIMP            QueryInterface(REFIID riid, void **ppvObject);
    STDMETHODIMP_(ULONG)    AddRef(void);
    STDMETHODIMP_(ULONG)    Release(void);

    // ******** IReplStore methods **************
    STDMETHODIMP        Initialize( IReplNotify *, UINT uFlags );
    STDMETHODIMP        GetStoreInfo( PSTOREINFO pStoreInfo );
    STDMETHODIMP        ReportStatus( HREPLFLD hFolder, HREPLITEM hItem, UINT uStatus, UINT uReserved );
    STDMETHODIMP_(int)  CompareStoreIDs( LPBYTE lpbID1, UINT cbID1, LPBYTE lpbID2, UINT cbID2 );

    // object related routines
    STDMETHODIMP_(int)  CompareItem( HREPLITEM hItem1, HREPLITEM hItem2 );
    STDMETHODIMP_(BOOL) IsItemChanged( HREPLFLD hFolder, HREPLITEM hItem, HREPLITEM hItemComp );
    STDMETHODIMP_(BOOL) IsItemReplicated( HREPLFLD hFolder, HREPLITEM hItem );
    STDMETHODIMP_(void) UpdateItem( HREPLFLD hFolder, HREPLITEM hItemDst, HREPLITEM hItemSrc );

    // folder related routines
    STDMETHODIMP        GetFolderInfo( LPCSTR lpszName,  HREPLFLD *phFolder, IUnknown **ppObjHandler );
    STDMETHODIMP        IsFolderChanged( HREPLFLD hFolder, BOOL *pfChanged );

    // enumeration of folder objects
    STDMETHODIMP        FindFirstItem( HREPLFLD hFolder,  HREPLITEM *phItem, BOOL *pfExist );    // get first object the folder
    STDMETHODIMP        FindNextItem( HREPLFLD hFolder,  HREPLITEM *phItem, BOOL *pfExist );     // get next object the folder
    STDMETHODIMP        FindItemClose( HREPLFLD hFolder );                                    // done enumerating

    // STD management routines
    STDMETHODIMP_(UINT)     ObjectToBytes( HREPLOBJ hObject, LPBYTE lpb );
    STDMETHODIMP_(HREPLOBJ) BytesToObject( LPBYTE lpb, UINT cb );
    STDMETHODIMP_(void)     FreeObject( HREPLOBJ hObject );
    STDMETHODIMP_(BOOL)     CopyObject( HREPLOBJ hObjSrc, HREPLOBJ hObjDst );
    STDMETHODIMP            IsValidObject( HREPLFLD hFolder, HREPLITEM hObject, UINT uFlags );

    // UI related routines
    STDMETHODIMP        ActivateDialog( UINT uDlg, HWND hwndParent, HREPLFLD hFolder, IEnumReplItem *penum );
    STDMETHODIMP        GetObjTypeUIData( HREPLFLD hFolder, POBJUIDATA pData );
    STDMETHODIMP        GetConflictInfo( PCONFINFO pConfInfo );
    STDMETHODIMP        RemoveDuplicates( LPCSTR, UINT );

    // ******** IReplStore2 methods **************
    STDMETHODIMP        DoOptionsDialog(HWND hwndParent, LPCSTR lpszObjType, IReplNotify * pntfy);

private:
friend int CALLBACK dlgSyncOpt( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
friend DWORD WINAPI Listen( LPVOID pvStore );
friend class CDataHandler;

    HRESULT         Open( BOOL fCreateNew );
    HRESULT         Close( void );
    PSTOCK          FindStock( UINT uidStock, PUINT puix  = NULL );
    void            Lock( void ) { WaitForSingleObject( m_hMutex, MUTEX_TIMEOUT ); }
    void            Unlock( void ) { ReleaseMutex( m_hMutex ); }
    PITEM           MakeNewItem( UINT uidStock );

    char            m_szStockFile[ MAX_PATH ];
    HANDLE          m_hFile, m_hMapObj, m_hMutex;
    PPORTFILE       m_pStocks;

    UINT            m_uFlags;
    IReplNotify     *m_pNotify;
    CDataHandler    *m_pObjHandler;
    HANDLE          m_hListen, m_hKillListen, m_hStockChg;

    // for enumeration of objects
    CItem           **m_rgpItems;
    UINT            m_ixCurrItem;
    UINT            m_cItems;
};

