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
    
      mainmod.cpp

Abstract:

    Implementation of IReplStore

--*/

#include <windows.h>
#include <strsafe.h>
#include <shlobj.h>
#include "mainmod.h"

#define EXIT_ON_FAIL(hr)                                                            \
        if (FAILED (hr))                                                             \
        {                                                                               \
            goto Exit;                                                                  \
        }           \
        else


HINSTANCE       v_hInst;
static char     v_szStockFile[ MAX_PATH ];
static char     v_szDBVol[ MAX_PATH ]; 
static UINT     v_uSyncOpt;
static CStore   *v_pStore;

BOOL WINAPI DllMain ( HANDLE hInstDll, ULONG ulReason, LPVOID lpReserved )
{
    switch( ulReason )
    {
    case DLL_PROCESS_ATTACH :
        v_hInst = (HINSTANCE)hInstDll;
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


//
//  ============ Required OLE implementation for InProc servers ======================
//
// CClassFactory object creates CStore objects

class CClassFactory : public IClassFactory 
{
private:
    LONG    m_cRef; 

public:
    CClassFactory( void ) : m_cRef( 0 ) {};

    virtual STDMETHODIMP            QueryInterface( REFIID iid, LPVOID* ppv);
    virtual STDMETHODIMP_(ULONG)    AddRef(); 
    virtual STDMETHODIMP_(ULONG)    Release();

    // IClassFactory members
    virtual STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID*);
    virtual STDMETHODIMP LockServer(BOOL);
};


// Count number of objects and number of locks
static LONG v_cObj = 0;
static LONG v_cLock = 0;

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)  
{
    if (!IsEqualIID(riid, IID_IUnknown) && !IsEqualIID(riid, IID_IClassFactory))
        return CLASS_E_CLASSNOTAVAILABLE;

    //return our IClassFactory for CStore objects
    *ppv = (LPVOID)new CClassFactory();
    if ( NULL == *ppv ) 
        return E_OUTOFMEMORY;

    //AddRef the object through any interface we return
    ((LPUNKNOWN)*ppv)->AddRef();

    return NOERROR;
}

STDAPI DllCanUnloadNow(void)  
{
    return ResultFromScode( 0L == v_cObj && 0 == v_cLock? S_OK : S_FALSE );
}

HRESULT CreateValue (HKEY hkeyParent, char * szKey, char * szValueName, DWORD dwType, 
                     void * pValue, DWORD dwLength)
{
    HRESULT hr      =   E_UNEXPECTED;
    LONG    lResult;
    HKEY    hkey    =   NULL;



    // create or open hkeyParent\szKey
    lResult = ::RegCreateKeyEx (hkeyParent, szKey, 0, NULL, REG_OPTION_NON_VOLATILE, 
                                KEY_ALL_ACCESS, NULL, &hkey, NULL);
    hr = HRESULT_FROM_WIN32 (lResult);
    EXIT_ON_FAIL (hr);

    
    // create hkeyParent\szKey\szValueName = pValue
    lResult = ::RegSetValueEx (hkey, szValueName, 0, dwType, reinterpret_cast <BYTE *> (pValue), dwLength);
    hr = HRESULT_FROM_WIN32 (lResult);
    EXIT_ON_FAIL (hr);

    
    // success 
    hr = S_OK;


Exit:
    // close key
    lResult = ::RegCloseKey (hkey);
    if (SUCCEEDED (hr))  // only overwrite hr if we haven't already failed above
    {
        hr = HRESULT_FROM_WIN32 (lResult);
    }

    return hr;
}




//
//  DllRegisterServer 
//  Called to register the provider with desktop sync
//
STDAPI DllRegisterServer (void)
{
    LONG    lResult;
    HRESULT hr                      =   E_UNEXPECTED;
    HKEY    hkey                    =   NULL;
    char    szKey[1024];
    char    szTemp[1024];
    HKEY    hkeyGuidProvider        =   NULL;
    char    szFilename[_MAX_PATH];
    DWORD   dwDisabled;
    DWORD   dwVersion;


    // open HKCR\CLSID
    lResult = ::RegOpenKeyEx (HKEY_CLASSES_ROOT, "CLSID", 0, KEY_ALL_ACCESS, &hkey);
    hr = HRESULT_FROM_WIN32 (lResult);
    EXIT_ON_FAIL (hr);


    // create HKCR\CLSID\{guid}
    lResult = ::RegCreateKeyEx (hkey, SZ_GUID_SYNCSAMPLE, 0, NULL, REG_OPTION_NON_VOLATILE, 
                                KEY_ALL_ACCESS, NULL, &hkeyGuidProvider, NULL);
    hr = HRESULT_FROM_WIN32 (lResult);
    EXIT_ON_FAIL (hr);

    // close HKCR\CLSID
    lResult = ::RegCloseKey (hkey);
    hr = HRESULT_FROM_WIN32 (lResult);
    EXIT_ON_FAIL (hr);


    // create HKCR\CLSID\{guid}, default value = store name
    lResult = ::RegSetValueEx (hkeyGuidProvider, NULL, 0, REG_SZ, (BYTE *) SZ_NAME, ::strlen (SZ_NAME) + 1);
    hr = HRESULT_FROM_WIN32 (lResult);
    EXIT_ON_FAIL (hr);

    
    // create HKCR\CLSID\{guid}\InprocServer32, default value = (path to this DLL)
    lResult = ::GetModuleFileName (v_hInst, szFilename, _MAX_PATH);
    if (lResult == 0)
    {
        hr = E_OUTOFMEMORY;
        goto Exit;
    }
    
    hr = ::CreateValue (hkeyGuidProvider, "InprocServer32", NULL, REG_SZ, szFilename, ::strlen (szFilename) + 1);
    EXIT_ON_FAIL (hr);


    // create HKCR\CLSID\{our guid}\ProgID, default value = (progid)
    hr = ::CreateValue (hkeyGuidProvider, "ProgID", NULL, REG_SZ, SZ_STORE_PROG_ID, ::strlen (SZ_STORE_PROG_ID) + 1);
    EXIT_ON_FAIL (hr);

    
    // create HKCR\(prog id), default value = (SZ_NAME)
    // create HKCR\(prog id), "Display Name" = 
    // create HKCR\(prog id), "Version" = 0x00030000    // version 3 or better allows settings
                                                        // to be configured during partnership wiz
    hr = ::CreateValue (HKEY_CLASSES_ROOT, SZ_STORE_PROG_ID, NULL, REG_SZ, SZ_NAME, ::strlen (SZ_NAME) + 1);
    EXIT_ON_FAIL (hr);

    hr = ::CreateValue (HKEY_CLASSES_ROOT, SZ_STORE_PROG_ID, "Display Name", REG_SZ, SZ_DISPLAY_NAME, ::strlen(SZ_DISPLAY_NAME) + 1);
    EXIT_ON_FAIL (hr);

    dwVersion = 0x00030000;
    hr = ::CreateValue (HKEY_CLASSES_ROOT, SZ_STORE_PROG_ID, "Version", REG_DWORD, &dwVersion, sizeof (dwVersion));
    EXIT_ON_FAIL (hr);

    // create HKCR\(prog id)\CLSID, default value = (GUID)
    StringCchPrintf(szKey, ARRAYSIZE(szKey), "%s\\CLSID", SZ_STORE_PROG_ID);
    hr = ::CreateValue (HKEY_CLASSES_ROOT, szKey, NULL, REG_SZ, SZ_GUID_SYNCSAMPLE, ::strlen (SZ_GUID_SYNCSAMPLE) + 1);
    EXIT_ON_FAIL (hr);

    //
    //  Available on PocketPC and Smartphone only

    // create HKLM\SOFTWARE\Microsoft\Windows CE Services\SpecialDefaults\PocketPC\
    //        Services\Synchronization\Objects\(SZ_NAME), (multiple values)
    StringCchPrintf(szKey, ARRAYSIZE(szKey), "SOFTWARE\\Microsoft\\Windows CE Services\\SpecialDefaults\\PocketPC\\"
                       "Services\\Synchronization\\Objects\\%s", SZ_NAME);
    
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, NULL, REG_SZ, SZ_NAME, ::strlen (SZ_NAME) + 1);
    EXIT_ON_FAIL (hr);
    
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Store", REG_SZ, SZ_STORE_PROG_ID, ::strlen (SZ_STORE_PROG_ID) + 1);
    EXIT_ON_FAIL (hr);
    
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Display Name", REG_SZ, SZ_DISPLAY_NAME, ::strlen (SZ_DISPLAY_NAME) + 1);
    EXIT_ON_FAIL (hr);

    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Plural Name", REG_SZ, SZ_PLURAL_NAME, ::strlen (SZ_PLURAL_NAME) + 1);
    EXIT_ON_FAIL (hr);

    dwDisabled = 0;
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Disabled", REG_DWORD, &dwDisabled, sizeof (dwDisabled));
    EXIT_ON_FAIL (hr);

    StringCchPrintf(szTemp, ARRAYSIZE(szTemp), "%s,-%d", szFilename, IDI_ICON);
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "DefaultIcon", REG_SZ, szTemp, ::strlen (szTemp) + 1);
    EXIT_ON_FAIL (hr);


    // create HKLM\SOFTWARE\Microsoft\Windows CE Services\SpecialDefaults\SmartPhone\
    //        Services\Synchronization\Objects\(SZ_NAME), (multiple values)
    StringCchPrintf(szKey, ARRAYSIZE(szKey), "SOFTWARE\\Microsoft\\Windows CE Services\\SpecialDefaults\\SmartPhone\\"
                       "Services\\Synchronization\\Objects\\%s", SZ_NAME);
    
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, NULL, REG_SZ, SZ_NAME, ::strlen (SZ_NAME) + 1);
    EXIT_ON_FAIL (hr);
    
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Store", REG_SZ, SZ_STORE_PROG_ID, ::strlen (SZ_STORE_PROG_ID) + 1);
    EXIT_ON_FAIL (hr);

    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Display Name", REG_SZ, SZ_DISPLAY_NAME, ::strlen (SZ_DISPLAY_NAME) + 1);
    EXIT_ON_FAIL (hr);

    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Plural Name", REG_SZ, SZ_PLURAL_NAME, ::strlen (SZ_PLURAL_NAME) + 1);
    EXIT_ON_FAIL (hr);

    dwDisabled = 0;
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "Disabled", REG_DWORD, &dwDisabled, sizeof (dwDisabled));
    EXIT_ON_FAIL (hr);

    StringCchPrintf(szTemp, ARRAYSIZE(szTemp), "%s,-%d", szFilename, IDI_ICON);
    hr = ::CreateValue (HKEY_LOCAL_MACHINE, szKey, "DefaultIcon", REG_SZ, szTemp, ::strlen (szTemp) + 1);
    EXIT_ON_FAIL (hr);

    hr = S_OK;

Exit:
    return hr;
}





STDAPI DllUnregisterServer (void)
{
    char    szKey[1024];



    StringCchPrintf(szKey, ARRAYSIZE(szKey), "CLSID\\%s\\ProgID", SZ_GUID_SYNCSAMPLE);
    ::RegDeleteKey (HKEY_CLASSES_ROOT, szKey);


    StringCchPrintf(szKey, ARRAYSIZE(szKey), "CLSID\\%s\\InprocServer32", SZ_GUID_SYNCSAMPLE);
    ::RegDeleteKey (HKEY_CLASSES_ROOT, szKey);


    StringCchPrintf(szKey, ARRAYSIZE(szKey), "CLSID\\%s", SZ_GUID_SYNCSAMPLE);
    ::RegDeleteKey (HKEY_CLASSES_ROOT, szKey);


    StringCchPrintf(szKey, ARRAYSIZE(szKey), "%s\\CLSID", SZ_STORE_PROG_ID);
    ::RegDeleteKey (HKEY_CLASSES_ROOT, szKey);


    ::RegDeleteKey (HKEY_CLASSES_ROOT, SZ_STORE_PROG_ID);


    StringCchPrintf(szKey, ARRAYSIZE(szKey), "SOFTWARE\\Microsoft\\Windows CE Services\\SpecialDefaults\\PocketPC\\"
                       "Services\\Synchronization\\Objects\\%s", SZ_NAME);
    ::RegDeleteKey (HKEY_LOCAL_MACHINE, szKey);


    StringCchPrintf(szKey, ARRAYSIZE(szKey), "SOFTWARE\\Microsoft\\Windows CE Services\\SpecialDefaults\\SmartPhone\\"
                       "Services\\Synchronization\\Objects\\%s", SZ_NAME);
    ::RegDeleteKey (HKEY_LOCAL_MACHINE, szKey);
    
    return S_OK;
}





STDMETHODIMP CClassFactory::QueryInterface(REFIID riid, LPVOID* ppv)  
{
    *ppv=NULL;
    if ( IsEqualIID( riid, IID_IUnknown ) || IsEqualIID( riid, IID_IClassFactory ) )
        *ppv=(LPVOID)this;

    if( NULL != *ppv )  
    {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
    }
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CClassFactory::AddRef( void )
{
    ULONG urc;
    urc = (ULONG)InterlockedIncrement( &m_cRef );
    return(urc);
}

STDMETHODIMP_(ULONG) CClassFactory::Release()
{
    ULONG urc;
    urc = (ULONG)InterlockedDecrement( &m_cRef ); 
    if (urc == 0 ) 
        delete this;

    return urc;
}

STDMETHODIMP CClassFactory::CreateInstance( LPUNKNOWN pUnkOuter, REFIID riid, LPVOID* ppvObj )
{
    CStore  *pObj;
    HRESULT hr;
    
    *ppvObj = NULL;
    hr = E_OUTOFMEMORY;

    if ( NULL != pUnkOuter && !IsEqualIID( riid, IID_IUnknown ) )
        return E_NOINTERFACE;

    pObj = new CStore( pUnkOuter );
    if ( NULL == pObj ) 
        return E_OUTOFMEMORY;

    hr = pObj->QueryInterface( riid, ppvObj );

    InterlockedIncrement( &v_cObj );

    if ( FAILED( hr ) ) 
    {
        delete pObj; // <-- this destroys LastError
    }

    return hr;
}


STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        InterlockedIncrement( &v_cLock );
    else     
        InterlockedDecrement( &v_cLock );

    return NOERROR;
}



//
// ================== Basic Implementation of IReplStore ====================
//

/*++
--*/
CStore::CStore( LPUNKNOWN pUnkOuter )
{
    m_cRef          = 0;
    m_pUnkOuter     = pUnkOuter;
    m_uFlags        = 0;
    m_pObjHandler   = new CDataHandler( this );
    m_rgpItems      = NULL;
    m_ixCurrItem    = 0;
    m_cItems        = 0;
    m_hFile         = INVALID_HANDLE_VALUE;
    m_hMapObj       = NULL;
    m_hMutex        = NULL;
    m_pStocks       = NULL;

    m_hListen       = NULL;
    m_hKillListen   = CreateEvent( NULL, FALSE, FALSE, NULL );
    m_hStockChg     = CreateEvent( NULL, FALSE, FALSE, SZ_CHANGE_EVENT );
}

/*++
--*/
CStore::~CStore()
{
    CloseHandle( m_hKillListen );
    CloseHandle( m_hStockChg );

    delete m_pObjHandler;
    InterlockedDecrement( &v_cObj );
}


//
// ==================== IUnknown Implementation ===========================
//

/*++
--*/
STDMETHODIMP CStore::QueryInterface( REFIID iid, LPVOID  *ppvObj )
{
    *ppvObj = NULL;   // set to NULL, in case we fail.

    if ( IsEqualIID( iid, IID_IUnknown ) )
        *ppvObj = (void*)this;
    else if ( IsEqualIID( iid, IID_IReplStore ) )
        *ppvObj = (void*)(IReplStore *)this;
    else if ( IsEqualIID( iid, IID_IReplStore2 ) )
        *ppvObj = (void*)(IReplStore2 *)this;
    else if ( m_pUnkOuter )
        return m_pUnkOuter->QueryInterface( iid, ppvObj );

    if ( *ppvObj )
    {
        ((IUnknown *)(*ppvObj))->AddRef();
        return NOERROR;
    }
    return E_NOINTERFACE;
}

/*++
--*/
STDMETHODIMP_(ULONG) CStore::AddRef()
{
    ULONG   urc;

    if ( m_pUnkOuter )
        urc = m_pUnkOuter->AddRef();
    else
        urc = (ULONG)InterlockedIncrement( &m_cRef );
    return urc;
}

/*++
--*/
STDMETHODIMP_(ULONG) CStore::Release()
{
    ULONG   urc;

    if ( m_pUnkOuter )
        urc = m_pUnkOuter->Release();
    else
    {
        urc =(ULONG)InterlockedDecrement( &m_cRef );
        if ( urc == 0 )
            delete this;
    }
    return urc;
}

//
// ================= thread listening to the changes/deletes in the Stock Portfolio app
//
DWORD WINAPI Listen( LPVOID pvStore )
{
    CStore  *pStore = (CStore *)pvStore;
    DWORD   dwObj;
    HANDLE  rgHandles[] = { pStore->m_hKillListen, pStore->m_hStockChg };
    UINT    ix, jx;

    for ( ;; )
    {
        dwObj = WaitForMultipleObjects( 2, rgHandles, FALSE, INFINITE );

        // will quit this thread for any other value
        if ( dwObj != WAIT_OBJECT_0 + 1 )
            break;

        if ( !pStore->m_pNotify ) continue;

        // get the change/delete log from the Stock Portfolio app
        pStore->Lock();
        for ( ix = 0; ix < pStore->m_pStocks->cChg; ix++ )
        {
            // check if this change is deleted too
            for ( jx = 0; jx < pStore->m_pStocks->cDel && pStore->m_pStocks->rgidChg[ix] != pStore->m_pStocks->rgidDel[jx]; jx++ );
            if ( jx >= pStore->m_pStocks->cDel )
            {
                PITEM   pItem = pStore->MakeNewItem( pStore->m_pStocks->rgidChg[ ix ] );
                if ( pItem && 
                     FAILED( pStore->m_pNotify->OnItemNotify( RNC_MODIFIED, SZ_STORE_PROG_ID, SZ_STOCKPOR, (HREPLITEM)pItem, 0 ) ) )
                    delete pItem;           
            }
        }

        for ( ix = 0; ix < pStore->m_pStocks->cDel; ix++ )
        {
            PITEM   pItem = pStore->MakeNewItem( pStore->m_pStocks->rgidDel[ ix ] );
            if ( pItem &&
                 FAILED( pStore->m_pNotify->OnItemNotify( RNC_DELETED, SZ_STORE_PROG_ID, SZ_STOCKPOR, (HREPLITEM)pItem, 0 ) ) )
                delete pItem;           
        }

        pStore->m_pStocks->cChg = pStore->m_pStocks->cDel = 0;
        pStore->Unlock();
    }
    return 0;
}


//
// ==================== IReplStore Implementation ===========================
//

/*++
--*/
STDMETHODIMP CStore::Initialize
(
    IReplNotify *pNotify,
    UINT        uFlags      // either ISF_SELECTED_DEVICE or ISF_REMOTE_CONNECTED
)
{
    LONG    lErr;
    HKEY    hRootKey;
    DWORD   dw, dwSize;
    char    szFile[ MAX_PATH * 2 ];
    HRESULT hr = NOERROR;

    m_uFlags    = uFlags;
    m_pNotify   = pNotify;

    // get the correct registry key for stock sync options
    hr = m_pNotify->QueryDevice( ( uFlags & ISF_SELECTED_DEVICE )? QDC_SEL_DEVICE_KEY : QDC_CON_DEVICE_KEY, (LPVOID *)&hRootKey );
    if ( FAILED( hr ) )
        goto Exit;

    // read the registry for the stock portfolio file to sync
    dw = REG_SZ;
    dwSize = sizeof( szFile );
    lErr = RegQueryValueEx( hRootKey, "Stock File", NULL, &dw, (const LPBYTE)szFile, &dwSize );
    if ( lErr == ERROR_SUCCESS )
    {
        hr = StringCchCopy( m_szStockFile, ARRAYSIZE(m_szStockFile), szFile );
    }
    else
    {
        // use the default file
        if(SHGetSpecialFolderPath(NULL, m_szStockFile, CSIDL_PERSONAL, TRUE))
        {
            hr = StringCchCat(m_szStockFile, ARRAYSIZE(m_szStockFile), SZ_DEFAULT_PORTFILE);
        }
        else
        {
            hr = E_FAIL;
        }
    }

    if ( FAILED( hr ) )
        goto Exit;

    // read the registry for sync option
    dwSize = sizeof( v_uSyncOpt );
    v_uSyncOpt = SO_ALL;
    RegQueryValueEx( hRootKey, "Sync Option", NULL, &dw, (const LPBYTE)&v_uSyncOpt, &dwSize );

    RegCloseKey( hRootKey );

    hr = Open( TRUE );

    // do not show any blocking UI (like the message box) if we are connected remotely
    if ( FAILED( hr ) && !( uFlags & ISF_REMOTE_CONNECTED ) )
    {
        StringCchPrintf( szFile, ARRAYSIZE(szFile),  "Unable to open Stock Portfolio file %s for synchronization. Error Code: 0x%X", m_szStockFile, hr );
        MessageBox( m_pNotify->GetWindow( 0 ), szFile, "Synchronization Error", MB_OK | MB_ICONSTOP );
    }

Exit:
    if ( SUCCEEDED( hr ) )
        m_uFlags |= ISF_INITIALIZED;

    return hr;
}

/*++
--*/
STDMETHODIMP CStore::GetStoreInfo
(
    PSTOREINFO pInfo    // pointers to the STOREINFO structure
)
{
    if ( pInfo->cbStruct != sizeof( STOREINFO ) )
        return E_INVALIDARG;

    pInfo->uFlags = SCF_SINGLE_THREAD;

    // ProgId of the store
    StringCchCopy( pInfo->szProgId, ARRAYSIZE(pInfo->szProgId), SZ_STORE_PROG_ID );
    StringCchCopy( pInfo->szStoreDesc, ARRAYSIZE(pInfo->szStoreDesc), "Stock Portfolio" );

    // done here if store is not yet initialized
    if ( !( m_uFlags & ISF_INITIALIZED ) )
        return NOERROR;

    // construct something that uniquely identifies the store
    pInfo->cbStoreId = lstrlen( m_szStockFile ) + 1;
    if ( pInfo->cbStoreId > pInfo->cbMaxStoreId )
        return E_OUTOFMEMORY;

    if ( pInfo->lpbStoreId == NULL )
        return E_POINTER;

    memcpy( pInfo->lpbStoreId, m_szStockFile, lstrlen( m_szStockFile ) + 1 );
    return NOERROR;
}

/*++
--*/
STDMETHODIMP_(int) CStore::CompareStoreIDs
(
    LPBYTE  lpbID1,     // points to the first store ID
    UINT    cbID1,      // size of the first store ID
    LPBYTE  lpbID2,     // points to the second store ID
    UINT    cbID2       // size of the second store ID
)
{
    if ( cbID1 < cbID2 )
        return -1;

    if ( cbID1 > cbID2 )
        return 1;

    return memcmp( lpbID1, lpbID2, cbID1 );
}

/*++
--*/
STDMETHODIMP CStore::ReportStatus
(
    HREPLFLD    hFolder,    // Handle of the folder this status applies to. NULL if status applies to all folders
    HREPLITEM   hItem,      // Handle of the object this status applies to. NULL if status applies to all objects
    UINT        uStatus,    // See RSC_xxx defined in cesync.h for all possibble code
    UINT        uParam      // Additional information about the status, based on uStatus code
)
{
    switch( uStatus )
    {
    case RSC_INTERRUPT:     // client should abort whatever it's doing now
        break;

    case RSC_BEGIN_SYNC:    // ActiveSync service manager is about to start
        break;

    case RSC_END_SYNC:      // ActiveSync service manager is about to end
        break;

    case RSC_BEGIN_CHECK:   // FindFirstItem is about to be called, followed by FindNextItem
        break;

    case RSC_END_CHECK:     // FindItemClose has been called
        break;

    case RSC_DATE_CHANGED:  // System Date has changed
        break;

    case RSC_RELEASE:       // ActiveSync service manager is about to release the service provider
        // close file
        Close();

        // wait for the listen thread to die
        if ( m_hListen )
        {
            SetEvent( m_hKillListen );
            WaitForSingleObject( m_hListen, 10000 );
            CloseHandle( m_hListen );
            m_hListen = NULL;
        };
        break;

    case RSC_REMOTE_SYNC:   // Indicates if remote sync is about to start. uParam will TRUE if all sync 
                            // will be remote until this status is reported again with uParam set to FALSE
        break;

    case RSC_BEGIN_SYNC_OBJ:    // ActiveSync service manager is about to start on an object type. uReserved is a pointer to a IEnumReplItem
        break;

    case RSC_END_SYNC_OBJ:      // ActiveSync service manager is about to end on an object type.
        break;

    case RSC_OBJ_TYPE_ENABLED:  // ActiveSync service manager of the given object is enabled, hFolder is indeed a pointer to a string (object type name)
        break;

    case RSC_OBJ_TYPE_DISABLED: // ActiveSync service manager of the given object is disabled, hFolder is indeed a pointer to a string (object type name)
        break;

    case RSC_BEGIN_BATCH_WRITE: // A series of SetPacket will be called on a number of objects, this is the right time for some service providers to start a transaction
        break;

    case RSC_END_BATCH_WRITE:   // above write ends, this is the right time for some service providers to commit the transaction
        break;

    case RSC_CONNECTION_CHG:    // connection status has changed. uParam is TRUE if connection established. FALSE otherwise.
        break;

    case RSC_WRITE_OBJ_FAILED:  // failed writing an object on the device. uParam is the HRESULT code.
        break;

    case RSC_DELETE_OBJ_FAILED: // failed deleting an object on the device. uParam is the HRESULT code.
        break;
    }

    return NOERROR;
}


//
//  ==================== Object management routines =====================
//

/*++
--*/
STDMETHODIMP_(UINT) CStore::ObjectToBytes
(
    HREPLOBJ    hObject,
    LPBYTE      lpb         // Points to a buffer where the array of bytes should be store. Could be NULL.
)
{
    LPBYTE      lpbStart = lpb;
    CReplObject *pObject = (CReplObject *)hObject;
    CFolder     *pFolder = (CFolder *)pObject;
    CItem       *pItem = (CItem *)pObject;

    if ( lpbStart )
        *lpb = OBJECT_VERSION;
    lpb++;

    if ( lpbStart )
        *(PUINT)lpb = pObject->m_uType;
    lpb += sizeof( pObject->m_uType );

    switch( pObject->m_uType )
    {
    case OT_FOLDER:
        break;

    case OT_ITEM:
        if ( lpbStart )
            *(PUINT)lpb = pItem->m_uid;
        lpb += sizeof( pItem->m_uid );

        if ( lpbStart )
            *(FILETIME *)lpb = pItem->m_ftModified;
        lpb += sizeof( pItem->m_ftModified );
        break;
    }

    return lpb - lpbStart;
}

/*++
--*/
STDMETHODIMP_(HREPLOBJ) CStore::BytesToObject
(
    LPBYTE  lpb,        // Points to a buffer where the array of bytes should be store. Could be NULL.
    UINT    cb          // size of the buffer
)
{
    CReplObject *pObject = NULL;
    CFolder     *pFolder;
    CItem       *pItem;

    BYTE    bVersion = *lpb++;
    UINT    uType = *(PUINT)lpb;
    lpb += sizeof( uType );

    if ( bVersion != OBJECT_VERSION )
    {
        // convert the data based on bVersion
    }

    switch( uType )
    {
    case OT_FOLDER:
        pObject = pFolder = new CFolder;
        break;

    case OT_ITEM:
        pObject = pItem = new CItem;

        pItem->m_uid = *(PUINT)lpb;
        lpb += sizeof( pItem->m_uid );

        pItem->m_ftModified = *(FILETIME *)lpb;
        lpb += sizeof( pItem->m_ftModified );

        break;
    }

    return (HREPLOBJ)pObject;
}

/*++
--*/
STDMETHODIMP_(void) CStore::FreeObject
(
    HREPLOBJ    hObject     // handler of the object whose contents need to be freed
)
{
    delete (CReplObject *)hObject;
}

/*++
--*/
STDMETHODIMP_(BOOL) CStore::CopyObject
(
    HREPLOBJ    hObjSrc,    // handle to the source object
    HREPLOBJ    hObjDst     // handle to the destination object
)
{
    CReplObject *pObjSrc = (CReplObject *)hObjSrc;
    CReplObject *pObjDst = (CReplObject *)hObjDst;

    if ( pObjSrc->m_uType != pObjDst->m_uType )
        return FALSE;

    switch( pObjSrc->m_uType )
    {
    case OT_ITEM:
        ((CItem *)pObjDst)->m_uid = ((CItem *)pObjSrc)->m_uid;
        ((CItem *)pObjDst)->m_ftModified = ((CItem *)pObjSrc)->m_ftModified;
        break;

    case OT_FOLDER:
        break;
    }

    return TRUE;
}

/*++
--*/
STDMETHODIMP CStore::IsValidObject
( 
    HREPLFLD    hFolder,    // handle of the folder where this item belongs
    HREPLITEM   hItem,      // handle of the object, could be NULL
    UINT        uFlags      // Reserved. Must be 0.
)
{
    CFolder *pFolder = (CFolder *)hFolder;
    CItem   *pItem = (CItem *)hItem;
    PSTOCK  pStock;

    if ( pFolder )
    {
        if ( pFolder->m_uType != OT_FOLDER )
            return HRESULT_FROM_WIN32( ERROR_INVALID_HANDLE );
    }

    if ( pItem )
    {
        if ( pItem->m_uType != OT_ITEM )
            return HRESULT_FROM_WIN32( ERROR_INVALID_HANDLE );

        Lock();
        pStock = FindStock( pItem->m_uid );
        Unlock();

        if ( !pStock )
            return HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND );
    }

    return NOERROR;
}

//
// ============= folder related routines  ================
//
/*++
--*/
STDMETHODIMP CStore::GetFolderInfo
(
    LPCSTR           lpszName,       // Name of the object type. It's taken from the registry.
    HREPLFLD        *phFolder,      // Output pointers, points to the handle of the new folder 
    IUnknown        **ppObjHandler  // Output pointers, points to the object handler of this object type
)
{
    CFolder *pFolder = (CFolder *)*phFolder;
    BOOL    fNew = (pFolder == NULL);

    // either set up the new CFolder class (when fNew is TRUE) or reinitialize the class (when fNew is FALSE)
    if ( fNew )
        pFolder = new CFolder;

    *phFolder = (HREPLFLD)pFolder;
    *ppObjHandler = m_pObjHandler;

    // we need only to set m_fChange to TRUE here since IsFolderChanged need only to return TRUE once
    pFolder->m_fChanged = TRUE;

    return NOERROR;
}

/*++
--*/
STDMETHODIMP CStore::IsFolderChanged
(
    HREPLFLD    hFolder,    // Handle of the folder
    BOOL        *pfChanged  // Points to a Boolean that will be set to TRUE if folder is changed
)
{
    // since we support real time detection of changes/deletes, we can simply return FALSE here.
    if ( pfChanged )
        *pfChanged = ((CFolder *)hFolder)->m_fChanged;

    ((CFolder *)hFolder)->m_fChanged = FALSE;
    return NOERROR;
}



//
// ============= Enumeration of folder objects ================
//

/*++
--*/
STDMETHODIMP CStore::FindFirstItem
(
    HREPLFLD    hFolder,        // handle to a folder
    HREPLITEM   *phItem,        // Output, points to the handle of the new object
    BOOL        *pfExist        // Output, points to a boolean value that will be set to TRUE if there is an object in the folder
)
{
    UINT    ix;
    CFolder *pFolder = (CFolder *)hFolder;

    // file should be opened by now and make sure enumeration is not nested
    if ( m_hFile == INVALID_HANDLE_VALUE || m_rgpItems )
        return E_UNEXPECTED;

    // take a snap shot of the stock allocate and allocate all items at once
    Lock();

    m_ixCurrItem = 0;
    m_cItems = m_pStocks->cStocks;
    m_rgpItems = new PITEM[ m_cItems ];
    if ( !m_rgpItems )
    {
        Unlock();
        return E_OUTOFMEMORY;
    }

    for ( ix = 0; ix < m_cItems; ix++ )
    {
        m_rgpItems[ix] = new CItem;
        if ( !m_rgpItems[ix] ) 
        {
            Unlock();
            return E_OUTOFMEMORY;
        }
        m_rgpItems[ix]->m_uid           = m_pStocks->rgStocks[ix].uidStock;
        m_rgpItems[ix]->m_ftModified    = m_pStocks->rgStocks[ix].ftLastModified;
    }

    // we don't need change/delete log any more
    m_pStocks->cChg = m_pStocks->cDel = 0;

    Unlock();
    return FindNextItem( hFolder, phItem, pfExist );
}

/*++
--*/
STDMETHODIMP CStore::FindNextItem
(
    HREPLFLD    hFolder,        // handle to a folder
    HREPLITEM   *phItem,        // Output, points to the handle of the new object
    BOOL        *pfExist        // Output, points to a boolean value that will be set to TRUE if there is an object in the folder
)
{
    CFolder *pFolder = (CFolder *)hFolder;

    if ( pfExist )
        *pfExist = FALSE;

    if ( !m_rgpItems ) 
        return E_UNEXPECTED;

    if ( m_ixCurrItem < m_cItems )
    {
        *phItem = (HREPLITEM)m_rgpItems[ m_ixCurrItem ];

        // now ActiveSync service manager owns the handle, reset ours to NULL so it won't be deleted
        m_rgpItems[ m_ixCurrItem ] = NULL;

        m_ixCurrItem++;

        if ( pfExist )
            *pfExist = TRUE;
    }
    return NOERROR;
}

/*++
--*/
STDMETHODIMP CStore::FindItemClose
(
    HREPLFLD    hFolder        // handle to a folder
)
{
    DWORD   dw;

    if ( !m_rgpItems ) 
        return E_UNEXPECTED;

    delete [] m_rgpItems;
    m_rgpItems = NULL;

    // spawn a second thread to listen to changes, if we haven't do so already
    if ( !m_hListen )
        m_hListen = CreateThread( NULL, 0, Listen, (LPVOID)this, 0, &dw );

    return NOERROR;
}

//
// ================== object related routines ================
//

/*++
--*/
STDMETHODIMP_(int) CStore::CompareItem
(
    HREPLITEM hItem1,  // Points to the handle of first object. This handle is guaranteed to be created by IReplStore::FindFirstObject or IReplStore::FindNextObject
    HREPLITEM hItem2   // Points to the handle of second object. This handle is guaranteed to be created by IReplStore::FindFirstObject or IReplStore::FindNextObject
)
{
    CItem   *pItem1 = (CItem *)hItem1;
    CItem   *pItem2 = (CItem *)hItem2;

    if ( pItem1->m_uid == pItem2->m_uid )
        return 0;

    if ( pItem1->m_uid < pItem2->m_uid )
        return -1;

    return 1;
}

/*++
--*/
STDMETHODIMP_(BOOL) CStore::IsItemChanged
(
    HREPLFLD    hFolder,    // Handle of a folder
    HREPLITEM   hItem,      // Handle of an object
    HREPLITEM   hItemComp   // Handle of the object used for comparison, could be NULL
)
{
    CFolder *pFolder = (CFolder *)hFolder;
    CItem   *pItem = (CItem *)hItem;
    CItem   *pItemComp = (CItem *)hItemComp;
    BOOL    fChanged = FALSE;

    if ( pItemComp )
        fChanged = CompareFileTime( &pItem->m_ftModified, &pItemComp->m_ftModified );
    else
    {
        PSTOCK      pStock;

        // read the modification time stamp from the object into ft
        Lock();
        pStock = FindStock( pItem->m_uid );
        fChanged = pStock && CompareFileTime( &pItem->m_ftModified, &pStock->ftLastModified );
        Unlock();
    }

    return fChanged;
}

/*++
--*/
STDMETHODIMP_(BOOL) CStore::IsItemReplicated
(
    HREPLFLD    hFolder,    // Handle of a folder
    HREPLITEM   hItem       // Handle of an object
)
{
    CFolder *pFolder = (CFolder *)hFolder;
    CItem   *pItem = (CItem *)hItem;
    PSTOCK  pStock;
    char    cSym;

    // hItem can be passed NULL.
    if ( pItem == NULL )
        return TRUE;

    // check if pItem should be replicated using information stored both in pFolder & pItem
    Lock();
    pStock = FindStock( pItem->m_uid );
    if ( pStock )
        cSym = pStock->szSym[0]; 
    Unlock();

    if ( !pStock ) return FALSE;

    switch ( v_uSyncOpt )
    {
    case SO_ALL:    return TRUE;
    case SO_AM:     return cSym >= 'A' && cSym <= 'M';
    case SO_NZ:     return cSym >= 'N' && cSym <= 'Z';
    }

    return FALSE;
}

/*++
--*/
STDMETHODIMP_(void) CStore::UpdateItem
(
    HREPLFLD    hFolder,    // Handle of a folder
    HREPLITEM   hItemDst,   // Handle of the destination object
    HREPLITEM   hItemSrc    // Handle to the source object, could be NULL.
)
{
    CFolder *pFolder = (CFolder *)hFolder;
    CItem   *pItemDst = (CItem *)hItemDst;
    CItem   *pItemSrc = (CItem *)hItemSrc;

    if ( pItemSrc )
    {
        pItemDst->m_ftModified = pItemSrc->m_ftModified;
    }
    else 
    {
        // Update the time stamp stored in the given handle
        Lock();
        PSTOCK pStock = FindStock( pItemDst->m_uid );
        if ( pStock )
            pItemDst->m_ftModified = pStock->ftLastModified;
        Unlock();
    }
}

//
//  ==================== UI related routines =====================
//

/*++
--*/
STDMETHODIMP CStore::GetConflictInfo( PCONFINFO pConfInfo )
{
    // make sure we have the right version of OBJUIDATA
    if ( pConfInfo->cbStruct != sizeof( CONFINFO ) )
        return E_INVALIDARG;

    StringCchCopy( pConfInfo->szLocalName, ARRAYSIZE(pConfInfo->szLocalName), "Stock" );
    StringCchCopy( pConfInfo->szRemoteName, ARRAYSIZE(pConfInfo->szRemoteName), "Stock" );

    CItem   *pLocalItem = (CItem *)pConfInfo->hLocalItem;
    CItem   *pRemoteItem = (CItem *)pConfInfo->hRemoteItem;
    PSTOCK  pLocalStock, pRemoteStock;

    Lock();

    pLocalStock = FindStock( pLocalItem->m_uid );
    pRemoteStock = FindStock( pRemoteItem->m_uid );
    if ( pLocalStock && pRemoteStock )
    {
        // resolve the conflict automatically if two stocks are considered identical
        if ( !lstrcmpi( pLocalStock->szCompany, pRemoteStock->szCompany ) && 
             !lstrcmpi( pLocalStock->szSym, pRemoteStock->szSym ) && 
             !lstrcmpi( pLocalStock->szLastPrice, pRemoteStock->szLastPrice ) && 
             !lstrcmpi( pLocalStock->szPurDate, pRemoteStock->szPurDate ) && 
             !lstrcmpi( pLocalStock->szPurPrice, pRemoteStock->szPurPrice ) )
        {
            Unlock();
            return RERR_IGNORE;
        }
    }

    if ( pLocalStock )
        StringCchPrintf( pConfInfo->szLocalDesc, ARRAYSIZE(pConfInfo->szLocalDesc), 
                  "%s\r\nPrice: %s\r\nPur. Price: %s", 
                  pLocalStock->szCompany, pLocalStock->szLastPrice,
                  pLocalStock->szPurPrice, pLocalStock->szCompany );
   
    if ( pRemoteStock )
        StringCchPrintf( pConfInfo->szRemoteDesc, ARRAYSIZE(pConfInfo->szRemoteDesc),
                  "%s\r\nPrice: %s\r\nPur. Price: %s", 
                  pRemoteStock->szCompany, pRemoteStock->szLastPrice,
                  pRemoteStock->szPurPrice, pRemoteStock->szCompany );

    Unlock();
    return NOERROR;
}


STDMETHODIMP CStore::DoOptionsDialog(HWND hwndParent, LPCSTR lpszObjType, IReplNotify * pntfy)
{
    HRESULT     hr = NOERROR;

    v_pStore = this;
    StringCchCopy( v_szStockFile, ARRAYSIZE(v_szStockFile), m_szStockFile );

    StringCchCopy( v_szDBVol, ARRAYSIZE(v_szDBVol), "" );


    //
    //  Note: Unable to call QueryDevice since the SSP may not have been enabled.
    //
    if ( DialogBox( v_hInst, TEXT( "SyncOptDlg" ), hwndParent, (DLGPROC)dlgSyncOpt ) == IDOK )
    {
        hr = NOERROR;
    }
    else
    {
        hr = RERR_CANCEL;
    }

    return hr;
}


BOOL CALLBACK dlgSyncOpt( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
    case WM_INITDIALOG:
        if ( v_uSyncOpt == SO_AM )
            CheckDlgButton( hDlg, IDC_SYNC_AM, TRUE );
        else if ( v_uSyncOpt == SO_NZ )
            CheckDlgButton( hDlg, IDC_SYNC_NZ, TRUE );
        else
            CheckDlgButton( hDlg, IDC_SYNC_ALL, TRUE );

        SetDlgItemText( hDlg, IDC_DB_VOL, v_szDBVol );
        SetDlgItemText( hDlg, IDC_FILE, v_pStore->m_szStockFile );
        return TRUE;

    case WM_COMMAND:
        switch( LOWORD( wParam ) )
        {
        case IDOK:
            if ( IsDlgButtonChecked( hDlg, IDC_SYNC_AM ) )
                v_uSyncOpt = SO_AM;
            else if ( IsDlgButtonChecked( hDlg, IDC_SYNC_NZ ) )
                v_uSyncOpt = SO_NZ;
            else
                v_uSyncOpt = SO_ALL;

            GetDlgItemText( hDlg, IDC_FILE, v_szStockFile, sizeof( v_szStockFile ) );

            EndDialog( hDlg, IDOK ); 
            break;

        case IDCANCEL:      
            EndDialog( hDlg, IDCANCEL ); 
            break;
        };
        break;
    }
    return FALSE;
}

/*++
--*/
STDMETHODIMP CStore::ActivateDialog
( 
    UINT            uDlg,           // Which dialog should be actiavted
    HWND            hwndParent,     // Handle of the window that should be used as parent for the dialog
    HREPLFLD        hFolder,        // Points to a valid STD for the folder
    IEnumReplItem   *penum          // Points to a enumerator of object STD for objects stored in the folder
)
{
    HRESULT     hr;
    SDREQUEST   sd;
    WCHAR       wszDBVol[ MAX_PATH ];

    if ( uDlg != OPTIONS_DIALOG )
        return E_NOTIMPL;

    v_pStore = this;
    StringCchCopy( v_szStockFile, ARRAYSIZE(v_szStockFile), m_szStockFile );

    // call device to get the database volume name, the QueryDevice will return error if no device is connected
    memset( wszDBVol, 0, sizeof( wszDBVol ) );
    memset( &sd, 0, sizeof( sd ) );
    StringCchCopy( sd.szObjType, ARRAYSIZE(sd.szObjType), SZ_STOCKPOR );
    sd.fSet     = FALSE;                // we are reading data from device
    sd.uCode    = 1;                    // we can have up to 8 different code
    sd.lpbData  = (LPBYTE)wszDBVol;    // we are passing a buffer to the call, 
                                        // we can also pass NULL, in which case, 
                                        // we must free the buffer using GlobalFree after we are done
    sd.cbData   = sizeof( wszDBVol );

    hr = m_pNotify->QueryDevice( QDC_SYNC_DATA, (LPVOID *)&sd );
    if ( hr == RERR_NO_DEVICE )
        StringCchCopy( v_szDBVol, ARRAYSIZE(v_szDBVol), "<Device is not connected>" );
    else if ( FAILED( hr ) )
        StringCchCopy( v_szDBVol, ARRAYSIZE(v_szDBVol), "<Erroring reading data from device>" );
    else if ( wszDBVol[0] == 0 )
        StringCchCopy( v_szDBVol, ARRAYSIZE(v_szDBVol), "System Volume" );
    else
    {
        // need to convert Unicode
        WideCharToMultiByte( CP_ACP, 0, wszDBVol, -1, v_szDBVol, sizeof( v_szDBVol ) - 1, NULL, NULL );
    }

    if ( DialogBox( v_hInst, TEXT( "SyncOptDlg" ), hwndParent, (DLGPROC)dlgSyncOpt ) == IDOK )
    {
        // see if the stock file is changed, and if the new file is valid
        if ( lstrcmpi( v_szStockFile, m_szStockFile ) && GetFileAttributes( v_szStockFile ) != (DWORD)-1 )
        {
            // save the new file into registry
            HKEY    hKey;

            // get the correct registry key for stock sync options
            if ( SUCCEEDED( m_pNotify->QueryDevice( ( m_uFlags & ISF_SELECTED_DEVICE )? QDC_SEL_DEVICE_KEY : QDC_CON_DEVICE_KEY, (LPVOID *)&hKey ) ) )
            {
                // read the hKey for the stock portfolio file to sync
                RegSetValueEx( hKey, "Stock File", NULL, REG_SZ, (const LPBYTE)v_szStockFile, lstrlen( v_szStockFile ) + 1 );
                RegSetValueEx( hKey, "Sync Option", NULL, REG_DWORD, (const LPBYTE)&v_uSyncOpt, sizeof( v_uSyncOpt ) );

                RegCloseKey( hKey );

                // ask ActiveSync service manager to unload service providers so the new option can be applied
                return RERR_UNLOAD;
            }
        }

        return NOERROR;
    }

    return RERR_CANCEL;
}

/*++
--*/
STDMETHODIMP CStore::GetObjTypeUIData
( 
    HREPLFLD    hFolder,        // Input, points to a STD of a folder that stores the object 
    POBJUIDATA  pData           // Output, points to a OBJUIDATA structure.
)
{
    // make sure we have the right version of OBJUIDATA
    if ( pData->cbStruct != sizeof( OBJUIDATA ) )
        return E_INVALIDARG;

    pData->hIconLarge = (HICON)LoadImage( v_hInst, MAKEINTRESOURCE( IDI_ICON ), IMAGE_ICON, 32, 32, 0 );
    pData->hIconSmall = (HICON)LoadImage( v_hInst, MAKEINTRESOURCE( IDI_ICON ), IMAGE_ICON, 16, 16, 0 );

    StringCchCopy( pData->szName, ARRAYSIZE(pData->szName), "Stock Portfolio Data" );
    StringCchCopy( pData->szTypeText, ARRAYSIZE(pData->szTypeText), "Database" );
    StringCchCopy( pData->szPlTypeText, ARRAYSIZE(pData->szPlTypeText), "Databases" );

    StringCchCopy( pData->szSyncText,ARRAYSIZE(pData->szSyncText), m_szStockFile );

    return S_OK;
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

/*++
HRESULT CStore::Open
    Open the file named by m_szStockFile
--*/
HRESULT CStore::Open( BOOL fCreateNew )
{
    // is it open already?
    if ( m_hFile != INVALID_HANDLE_VALUE )
        return NOERROR;

    BOOL    fNewFile = ( GetFileAttributes( m_szStockFile ) == (DWORD)-1 );
    HRESULT hr = fNewFile && !fCreateNew? E_FAIL : NOERROR;

    if ( FAILED( hr ) ) goto Exit;   

    // need to create this file if it doesn't exist
    if ( fNewFile )
        m_hFile = CreateFile( m_szStockFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                              NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    else
        m_hFile = CreateFile( m_szStockFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    if ( m_hFile == INVALID_HANDLE_VALUE )
    {
        hr = E_FAIL;
        goto Exit;
    }

    m_hMapObj = CreateFileMapping( m_hFile, NULL, PAGE_READWRITE, 0, sizeof( PORTFILE ), MakeMapObjName( m_szStockFile ) );
    if ( m_hMapObj == NULL )
    {
        hr = E_FAIL;
        goto Exit;
    }

    // Get a pointer to the file-mapped shared memory:
    m_pStocks = (PPORTFILE)MapViewOfFile( m_hMapObj, FILE_MAP_WRITE, 0, 0, 0 );
    if ( m_pStocks == NULL ) 
    {
        hr = E_FAIL;
        goto Exit;
    }

    // Get the Mutex
    if ( !m_hMutex )
        m_hMutex = CreateMutex( NULL, FALSE, SZ_MUTEX );

    if ( !m_hMutex )
    {
        hr = E_FAIL;
        goto Exit;
    }
    
    if ( fNewFile )
    {
        Lock();
        ClearStruct( *m_pStocks );
        m_pStocks->uVer1        = PORTFILE_VERSION;
        m_pStocks->uVer2        = PORTFILE_VERSION;
        m_pStocks->uidCurrStock = 1;
        FlushViewOfFile( 0, sizeof( PORTFILE ) );
        Unlock();
    }
    else
    {
        Lock();
        if ( m_pStocks->uVer1 != PORTFILE_VERSION || m_pStocks->uVer2 != PORTFILE_VERSION )
        {
            hr = E_UNEXPECTED;
            Unlock();
            goto Exit;
        }
        Unlock();
    }

Exit:
    return hr;
}


/*++
HRESULT CStore::Close
    Close the file named by m_szStockFile
--*/
HRESULT CStore::Close( void )
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

    return NOERROR;
}

/*++
PSTOCK CStore::FindStock
    Find a stock using the stock ID, return NULL if not found.
    m_pStocks must be protected by the mutex before calling this routine and
    before finish using the pointer it returns
--*/
PSTOCK CStore::FindStock( UINT uidStock, PUINT puix )
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
--*/
PITEM CStore::MakeNewItem( UINT uidStock )
{
    PITEM   pItem = new CItem;
    PSTOCK  pStock;
    if ( pItem )
    {
        pItem->m_uid = uidStock;

        // set the time stamp if we can
        Lock();
        pStock = FindStock( uidStock );
        if ( pStock )
            pItem->m_ftModified = pStock->ftLastModified;
        Unlock();
    }
    return pItem;
}

//
// Function called when the SSP is enabled in the ActiveSync options dialog
//
HRESULT WINAPI OnSSPEnable(HWND hwnd)
{
    MessageBox(hwnd, "StockPor- OnEnable", "StockPor", MB_OK);

    return S_OK;
}


//
// Function called when the SSP is disabled in the ActiveSync options dialog
//
HRESULT WINAPI OnSSPDisable(HWND hwnd)
{
    MessageBox(hwnd, "StockPor- OnDisable", "StockPor", MB_OK);

    return S_OK;
}

