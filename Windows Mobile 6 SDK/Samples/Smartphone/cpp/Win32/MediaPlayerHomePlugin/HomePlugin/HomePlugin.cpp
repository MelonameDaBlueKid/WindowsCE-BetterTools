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

#define INITGUID

#include <windows.h>
#include <commctrl.h>
#include <ocidl.h>
#include <msgqueue.h>
#include <home.h>
#include "..\common\comsupport.h"
#include "..\common\xmlsupport.h"
#include "..\common\communication.h"
#include "displayattrs.h"
#include "textlang.h"
#include "resource.h"

////////////////////////////////////////////////////////////
// CLSID_HomePlugin
//
// This is the class ID for our plugin.
//
// PLEASE CHANGE THIS BEFORE USING IN PRODUCTION CODE!
//
// ALSO, PLEASE MAKE SURE THIS MATCHES THE CALL TO
// DllRegisterServerImplementation!
////////////////////////////////////////////////////////////

// {07326E2E-D59C-4AFF-BBEA-DE783325B5EC}
DEFINE_GUID(CLSID_HomePlugin, 0x07326e2e, 0xd59c, 0x4aff, 0xbb, 0xea, 0xde, 0x78, 0x33, 0x25, 0xb5, 0xec);

////////////////////////////////////////////////////////////
// Global CServer instance
////////////////////////////////////////////////////////////

CServer * g_pServer;

////////////////////////////////////////////////////////////
// Constant strings
//
// CHANGE THESE FOR PRODUCTION CODE!
////////////////////////////////////////////////////////////

static const TCHAR s_szRegDescription[] = _T("Homescreen Plugin - Controls Windows Media Player Plugin");
static const TCHAR s_szModuleName[] = _T("mphp_homeplugin.dll");

////////////////////////////////////////////////////////////
// Display constants
////////////////////////////////////////////////////////////

#define CLR_BUTTON_TRANSPARENCY     RGB(0xFF, 0x00, 0xFF)

#define CX_BUTTON                   20      // Width of each button image, in pixels
#define CY_BUTTON                   20      // Height of each button image, in pixels

#define CY_TEXT_BUTTON_PAD          4       // Y-pad between bottom of text and button row
#define CX_INTRA_BUTTON_PAD         4       // X-pad between buttons

#define IBTN_PLAY                   0       // Index of 'play' button in image strip IDB_BUTTONS
#define IBTN_PAUSE                  1       // Index of 'pause' button in image strip IDB_BUTTONS
#define IBTN_PREV                   2       // Index of 'previous' button in image strip IDB_BUTTONS
#define IBTN_NEXT                   3       // Index of 'next' button in image strip IDB_BUTTONS
#define IBTN_DIMPLAY                4       // Index of disabled 'play' button in image strip IDB_BUTTONS
#define IBTN_DIMPAUSE               5       // Index of disabled 'pause' button in image strip IDB_BUTTONS
#define IBTN_DIMPREV                6       // Index of disabled 'previous' button in image strip IDB_BUTTONS
#define IBTN_DIMNEXT                7       // Index of disabled 'next' button in image strip IDB_BUTTONS

////////////////////////////////////////////////////////////
// Other constants
////////////////////////////////////////////////////////////

#define CMSEC_INVALIDATE_TIMER      500     // When Media Player's state changes, we wait this
                                            // long (in msec.) before invalidating our plugin
                                            //
                                            // See Notes section in README.HTM for more details

////////////////////////////////////////////////////////////
// GetUIString
//
// Searches children of the specified 'base' node for a <uistring>
// node with an 'id' attribute matching the specified ID string.
// If such a node is found, looks through all <text> children of
// that node looking for one with an appropriate 'lang' attribute;
// if found, returns that string.
//
// For example, given the following XML subtree:
//
// <plugin>
//      <uistring id='criticalerror'>
//          <text lang='0x0409'>Critical error!</text>
//          <text lang='0x0407'>Kritischer Fehler!</text>
//      </uistring>
// </plugin>
//
// and the call
//
//      GetUIString(pNodePlugin, L"criticalerror", &pwszResult);
//
// If the current language is English, returns "Critical error!"
// in *pwszResult; if the current language is German, returns
// "Kritischer Fehler!" in *pwszResult.
//
// If the current language is none of the above, this function
// will return the best match.
//
// NOTE
// ----
// If this function succeeds, the caller must ultimately free
// the string by passing it to free().
////////////////////////////////////////////////////////////

HRESULT GetUIString(IXMLDOMNode * pNodeBase, LPCWSTR wszID, LPWSTR * pwszResult)
{
    HRESULT             hr;
    int                 cwchXpathExpr;
    LPWSTR              wszXpathExpr = NULL;
    BSTR                bstrXpathExpr = NULL;
    IXMLDOMNode *       pNodeUIString = NULL;

    // First find the appropriate <uistring> node.
    //
    // The XPath expression is "uistring[@id='<id>']".
    cwchXpathExpr = 17 + wcslen(wszID);

    if ((wszXpathExpr = new WCHAR[cwchXpathExpr]) == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    }

    StringCchCopyW(wszXpathExpr, cwchXpathExpr, L"uistring[@id='");
    StringCchCat(wszXpathExpr, cwchXpathExpr, wszID);
    StringCchCat(wszXpathExpr, cwchXpathExpr, L"']");

    if ((bstrXpathExpr = SysAllocString(wszXpathExpr)) == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    }

    if (FAILED(hr = pNodeBase->selectSingleNode(bstrXpathExpr, &pNodeUIString)))
        goto Cleanup;

    if (pNodeUIString == NULL)
    {
        hr = E_FAIL;
        goto Cleanup;
    }

    // Now call GetLocalizedTextNodeString to get the text.
    if (FAILED(GetLocalizedTextNodeString(pNodeUIString, pwszResult, NULL)))
        goto Cleanup;

    // Success!
    hr = S_OK;

Cleanup:
    if (pNodeUIString != NULL)
        pNodeUIString->Release();

    if (bstrXpathExpr != NULL)
        SysFreeString(bstrXpathExpr);

    if (wszXpathExpr != NULL)
        delete [] wszXpathExpr;

    return hr;
}

////////////////////////////////////////////////////////////
// CHomePluginClassFactory class
//
// This is the 'class factory' (class implementing IClassFactory)
// for our plugin object.
////////////////////////////////////////////////////////////

class CHomePluginClassFactory : IClassFactory
{
public:
    ////////////////////////////////////////
    // Constructor, destructor
    ////////////////////////////////////////
    CHomePluginClassFactory()
        : m_cRefs(0)
    {
        g_pServer->Lock();
    }

    ~CHomePluginClassFactory()
    {
        g_pServer->Unlock();
    }

    ////////////////////////////////////////
    // IUnknown implementation (for IClassFactory)
    ////////////////////////////////////////
    STDMETHODIMP_(ULONG) AddRef()
    {
        return m_cRefs.Increment();
    }

    STDMETHODIMP_(ULONG) Release()
    {
        ULONG   cRefsNew = m_cRefs.Decrement();

        if (cRefsNew == 0)
            delete this;

        return cRefsNew;
    }

    STDMETHODIMP QueryInterface(REFIID riid, VOID ** ppvObject);

    ////////////////////////////////////////
    // IClassFactory implementation
    ////////////////////////////////////////
    STDMETHODIMP CreateInstance(IUnknown * pUnkOuter, REFIID riid, VOID ** ppvObject);
    STDMETHODIMP LockServer(BOOL fLock);

private:
    ////////////////////////////////////////
    // Data
    ////////////////////////////////////////
    CThreadSafeULONG    m_cRefs;    // Thread-safe reference count
};

////////////////////////////////////////////////////////////
// CWMPInfo class
//
// This class encapsulates the information we receive from
// our Windows Media Player plugin regarding the state of
// Windows Media Player.
//
// Why a separate class for this information? Because this
// information is WRITTEN to by our auxiliary thread and
// READ from our main thread. Thus, we need to synchronize
// access to this information, which is exactly what this
// class does.
////////////////////////////////////////////////////////////

class CWMPInfo
{
public:
    ////////////////////////////////////////
    // Constructor, destructor
    ////////////////////////////////////////
    CWMPInfo()
        : m_status(WMP_STATUS_UNKNOWN)
    {
        m_szTitle[0] = _T('\0');
        InitializeCriticalSection(&m_cs);
    }

    ~CWMPInfo()
    {
        DeleteCriticalSection(&m_cs);
    }

    LPCTSTR GetTitle()
    {
        LPCTSTR     szRet;

        EnterCriticalSection(&m_cs);
        szRet = m_szTitle;
        LeaveCriticalSection(&m_cs);

        return szRet;
    }

    BOOL SetTitle(LPCTSTR szTitle)
    {
        BOOL    fRet = FALSE;   // meaning: value didn't change (assume)
        EnterCriticalSection(&m_cs);
        if (_tcscmp(m_szTitle, szTitle) != 0)
        {
            StringCchCopy(m_szTitle, CCH_MEDIA_TITLE_MAX, szTitle);
            fRet = TRUE;        // meaning: value DID change
        }
        LeaveCriticalSection(&m_cs);
        return fRet;
    }

    WMP_STATUS GetStatus()
    {
        WMP_STATUS  statusRet;

        EnterCriticalSection(&m_cs);
        statusRet = m_status;
        LeaveCriticalSection(&m_cs);

        return statusRet;
    }

    BOOL SetStatus(WMP_STATUS status)
    {
        BOOL    fRet = FALSE;   // meaning: value didn't change (assume)
        EnterCriticalSection(&m_cs);
        if (m_status != status)
        {
            m_status = status;
            fRet = TRUE;        // meaning: value DID change
        }
        LeaveCriticalSection(&m_cs);
        return fRet;
    }

private:
    ////////////////////////////////////////
    // Data
    ////////////////////////////////////////
    CRITICAL_SECTION    m_cs;
    TCHAR               m_szTitle[CCH_MEDIA_TITLE_MAX];
    WMP_STATUS          m_status;
};

////////////////////////////////////////////////////////////
// CHomePlugin
//
// This is our actual plugin component which implements
// IHomePlugin and IPersistStream.
////////////////////////////////////////////////////////////

class CHomePlugin:
    public IHomePlugin,
    public IPersistStream
{
public:
    ////////////////////////////////////////
    // Constructor, destructor
    ////////////////////////////////////////
    CHomePlugin()
        : m_cRefs(0),
          m_wszMessage(NULL),
          m_pHpe(NULL),
          m_hPlugin(NULL),
          m_hThread(NULL),
          m_hMsgQueue(NULL),
          m_hEventLifetime(NULL),
          m_fTimerSet(FALSE),
          m_hbmpButtons(NULL)
    {
        g_pServer->Lock();
    }

    ~CHomePlugin()
    {
        if (m_hbmpButtons != NULL)
            DeleteObject(m_hbmpButtons);

        if (m_hMsgQueue != NULL)
            CloseMsgQueue(m_hMsgQueue);

        if (m_hEventLifetime != NULL)
            CloseHandle(m_hEventLifetime);

        if (m_pHpe != NULL)
            m_pHpe->Release();

        if (m_wszMessage != NULL)
            free(m_wszMessage);

        g_pServer->Unlock();
    }

    ////////////////////////////////////////
    // InternalAddRef and InternalRelease
    //
    // Internal versions of AddRef and Release, mimicking ATL.
    //
    // See our class factory's CreateInstance method.
    ////////////////////////////////////////
    VOID InternalAddRef()
    {
        m_cRefs.Increment();
    }

    VOID InternalRelease()
    {
        m_cRefs.Decrement();
    }

    ////////////////////////////////////////
    // FinalConstruct method (mimicking ATL).
    //
    // This is called by our class factory's CreateInstance method to allow
    // us to perform additional initialization and possibly return an error
    // code (which isn't easily done with just the constructor).
    //
    // This is where we create our hidden communication window.
    ////////////////////////////////////////
    HRESULT FinalConstruct();

    ////////////////////////////////////////
    // IUnknown implementation (for both interfaces)
    ////////////////////////////////////////
    STDMETHODIMP_(ULONG) AddRef()
    {
        return m_cRefs.Increment();
    }

    STDMETHODIMP_(ULONG) Release()
    {
        ULONG   cRefsNew = m_cRefs.Decrement();

        if (cRefsNew == 0)
        {
            // We have to make sure our auxiliary thread (if it exists)
            // is shut down properly before we delete 'this'. Signal it
            // and then wait for it to shut down.
            if (m_hThread != NULL)
            {
                SetEvent(m_hEventLifetime);
                WaitForSingleObject(m_hThread, INFINITE);
            }

            delete this;
        }

        return cRefsNew;
    }

    STDMETHODIMP QueryInterface(REFIID riid, VOID ** ppvObject);

    ////////////////////////////////////////
    // IObjectWithSite implementation (for IHomePlugin)
    ////////////////////////////////////////
    STDMETHODIMP SetSite(IUnknown * pSite);
    STDMETHODIMP GetSite(REFIID riid, VOID ** ppvSite);

    ////////////////////////////////////////
    // IHomePlugin implementation
    ////////////////////////////////////////
    STDMETHODIMP Initialize(HPLUGIN hPlugin, IXMLDOMNode * pNodeParams, IXMLDOMNode * pNodeDefault);
    STDMETHODIMP GetHeight(INT * pdyPlugin);
    STDMETHODIMP GetSelectability(BOOL * pfSelectable);
    STDMETHODIMP OnEvent(PluginEvent * pEvent);

    ////////////////////////////////////////
    // IPersist implementation (for IPersistStream)
    ////////////////////////////////////////
    STDMETHODIMP GetClassID(CLSID * pClassID);

    ////////////////////////////////////////
    // IPersistStream implementation
    ////////////////////////////////////////
    STDMETHODIMP IsDirty();
    STDMETHODIMP Load(IStream * pStm);
    STDMETHODIMP Save(IStream * pStm, BOOL fClearDirty);
    STDMETHODIMP GetSizeMax(ULARGE_INTEGER * pcbSize);

private:
    ////////////////////////////////////////
    // Helper methods
    ////////////////////////////////////////

    // Create the font for the specified state.
    HFONT GetFont(BOOL fSelected)
    {
        LOGFONT     lf;

        lf.lfHeight = (fSelected ? m_dispattrsSel.GetFontSize() : m_dispattrsNormal.GetFontSize());
        lf.lfWidth = 0;
        lf.lfEscapement = 0;
        lf.lfOrientation = 0;
        lf.lfWeight = (fSelected ? m_dispattrsSel.GetFontWeight() : m_dispattrsNormal.GetFontWeight());
        lf.lfItalic = static_cast<BYTE>(fSelected ? m_dispattrsSel.GetFontStyle() : m_dispattrsNormal.GetFontStyle());
        lf.lfUnderline = 0;
        lf.lfStrikeOut = 0;
        lf.lfCharSet = DEFAULT_CHARSET;
        lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
        lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        lf.lfQuality = DEFAULT_QUALITY;
        lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
        StringCchCopy(lf.lfFaceName, sizeof(lf.lfFaceName)/sizeof(TCHAR), (fSelected ? m_dispattrsSel.GetFontFace() : m_dispattrsNormal.GetFontFace()));

        return CreateFontIndirect(&lf);
    }

    // Draw a button at the specified location. The 'hdcSrc' parameter must be
    // a compatible (memory) DC which has the buttons bitmap selected in.
    VOID DrawButton(HDC hdcDst, HDC hdcSrc, INT x, INT y, INT iBtn);

    // Return the handle to the communication window owned by our
    // Windows Media Player plugin, or NULL if it doesn't exist.
    HWND GetMediaPlayerPluginWindow();

    ////////////////////////////////////////
    // Auxiliary thread methods
    ////////////////////////////////////////
    static DWORD WINAPI StaticThreadProc(VOID * pvParam);
    DWORD ThreadProc();

    ////////////////////////////////////////
    // Data
    ////////////////////////////////////////
    CThreadSafeULONG            m_cRefs;            // Thread-safe reference count
    LPWSTR                      m_wszMessage;       // Our single localized UI message
    IHomePluginEnvironment2 *   m_pHpe;             // Pointer to IHomePluginEnvironment2 interface
    HPLUGIN                     m_hPlugin;          // Our plugin 'handle'
    HANDLE                      m_hThread;          // Handle to our auxiliary thread
    HANDLE                      m_hMsgQueue;        // Message queue used for notifications from WMP plugin
    HANDLE                      m_hEventLifetime;   // Event object used to control auxiliary thread's lifetime
    HBITMAP                     m_hbmpButtons;      // Handle to 'buttons' bitmap
    CWMPInfo                    m_wmpinfo;          // Information about state of Windows Media Player
    BOOL                        m_fTimerSet;        // TRUE if we set our 'invalidate' timer (see ThreadProc)
    CDisplayAttributes          m_dispattrsNormal;  // Normal (unselected) display attributes
    CDisplayAttributes          m_dispattrsSel;     // Selected display attributes
};

////////////////////////////////////////////////////////////
// CHomePluginClassFactory::QueryInterface
////////////////////////////////////////////////////////////

HRESULT CHomePluginClassFactory::QueryInterface(REFIID riid, VOID ** ppvObject)
{
    *ppvObject = NULL;

    if (IsEqualIID(riid, __uuidof(IUnknown)))
        *ppvObject = static_cast<IUnknown *>(static_cast<IClassFactory *>(this));
    else if (IsEqualIID(riid, __uuidof(IClassFactory)))
        *ppvObject = static_cast<IClassFactory *>(this);

    if (*ppvObject == NULL)
        return E_NOINTERFACE;

    AddRef();

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePluginClassFactory::CreateInstance
////////////////////////////////////////////////////////////

HRESULT CHomePluginClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, VOID ** ppvObject)
{
    HRESULT         hr;
    CHomePlugin *   pPlugin;

    // Assume failure.
    *ppvObject = NULL;

    // We don't support aggregation.
    if (pUnkOuter != NULL)
        return CLASS_E_NOAGGREGATION;

    // Create the plugin instance.
    if ((pPlugin = new CHomePlugin()) == NULL)
        return E_OUTOFMEMORY;

    // Call the plugin's FinalConstruct method to allow it to perform
    // additional initialization.
    //
    // Once again mimicking ATL's behavior, we first artifically increment
    // its ref count before calling FinalConstruct and then artificially
    // decrement it afterward. Why? Because we don't know what the plugin
    // will do in its FinalConstruct method. It could (in theory) hand its
    // interface pointer to some _other_ object, which might AddRef it, use
    // it, and then Release it (according to the standard COM rules). However,
    // because the object currently has a reference count of 0, the hypothetical
    // AddRef would bump it to 1, and the Release would drop it to 0 and destroy
    // the object!
    //
    // When we do this artifical "lifetime support", though, we can't use the
    // IUnknown AddRef and Release methods because we're likely to end up deleting
    // the object for exactly the same reason (its ref count might go to 0 on the
    // Release call). So instead, we use the InternalAddRef and InternalRelease
    // methods. The InternalRelease method, in particular, doesn't check for a
    // resulting ref count of 0 (and thus will never delete the instance).
    pPlugin->InternalAddRef();
    hr = pPlugin->FinalConstruct();
    pPlugin->InternalRelease();

    if (FAILED(hr))
    {
        delete pPlugin;
        return hr;
    }

    // Make sure the plugin object supports the requested interface. Yes, we
    // could probably do this _before_ the FinalConstruct call, thus avoiding
    // the whole InternalAddRef/Release stuff, but only now has the object
    // been properly constructed.
    if (FAILED(hr = pPlugin->QueryInterface(riid, ppvObject)))
    {
        delete pPlugin;
        return hr;
    }

    // The plugin object should have a reference count of at least 1, courtesy
    // of the call to QueryInterface.

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePluginClassFactory::LockServer
////////////////////////////////////////////////////////////

HRESULT CHomePluginClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        g_pServer->Lock();
    else
        g_pServer->Unlock();

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::QueryInterface
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::QueryInterface(REFIID riid, VOID ** ppvObject)
{
    *ppvObject = NULL;

    if (IsEqualIID(riid, __uuidof(IUnknown)))
        *ppvObject = static_cast<IUnknown *>(static_cast<IHomePlugin *>(this));
    else if (IsEqualIID(riid, __uuidof(IObjectWithSite)))
        *ppvObject = static_cast<IObjectWithSite *>(static_cast<IHomePlugin *>(this));
    else if (IsEqualIID(riid, __uuidof(IHomePlugin)))
        *ppvObject = static_cast<IHomePlugin *>(this);
    else if (IsEqualIID(riid, __uuidof(IPersist)))
        *ppvObject = static_cast<IPersist *>(static_cast<IPersistStream *>(this));
    else if (IsEqualIID(riid, __uuidof(IPersistStream)))
        *ppvObject = static_cast<IPersistStream *>(this);

    if (*ppvObject == NULL)
        return E_NOINTERFACE;

    AddRef();

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::FinalConstruct
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::FinalConstruct()
{
    HRESULT             hr;
    HWND                hwndComm;
    MSGQUEUEOPTIONS     mqo;

    // Create the message queue we'll use to receive notifications from the
    // Windows Media Player plugin. This is named so the Windows Media Player
    // plugin can find it.
    mqo.dwSize = sizeof(mqo);
    mqo.dwFlags = DW_MSGQUEUE_FLAGS;
    mqo.dwMaxMessages = DW_MSGQUEUE_MAXMSGS;
    mqo.cbMaxMessage = sizeof(MQMESSAGE);
    mqo.bReadAccess = TRUE;

    if ((m_hMsgQueue = CreateMsgQueue(SZ_MSGQUEUE_NAME, &mqo)) == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Cleanup;
    }

    // Create our event which controls the thread's lifetime. This one doesn't
    // need to be named since it's only used within this code.
    if ((m_hEventLifetime = CreateEvent(NULL, /*bManualReset=*/FALSE, /*bInitialState=*/FALSE, NULL)) == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Cleanup;
    }

    // Create a thread to watch the message queue and event. When either one
    // becomes signaled, we know that either our Windows Media Player plugin has
    // information for us OR that the main thread wants this auxiliary thread to
    // shut down.
    if ((m_hThread = CreateThread(NULL, 0, StaticThreadProc, this, 0, NULL)) == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Cleanup;
    }

    // If the Windows Media Player plugin communication window exists, post
    // it a message to tell it to write a status update to the message queue.
    if ((hwndComm = GetMediaPlayerPluginWindow()) != NULL)
        PostMessage(hwndComm, WM_MPHPSAMPLE_REPORT, 0, 0);

    // Success.
    hr = S_OK;

Cleanup:
    if (FAILED(hr))
    {
        if (m_hMsgQueue != NULL)
        {
            CloseMsgQueue(m_hMsgQueue);
            m_hMsgQueue = NULL;
        }

        if (m_hEventLifetime != NULL)
        {
            CloseHandle(m_hEventLifetime);
            m_hEventLifetime = NULL;
        }
    }

    return hr;
}

////////////////////////////////////////////////////////////
// CHomePlugin::SetSite
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::SetSite(IUnknown * pSite)
{
    // If we already have an interface pointer, discard it.
    if (m_pHpe != NULL)
    {
        m_pHpe->Release();
        m_pHpe = NULL;
    }

    // Now grab the new interface pointer and QI it for IHomePluginEnvironment2.
    if (pSite != NULL)
        pSite->QueryInterface(__uuidof(IHomePluginEnvironment2), (VOID **)&m_pHpe);

    // If the QueryInterface call succeeded, then m_pHpe will be non-NULL and we will
    // have added a ref to it.
    //
    // If the QueryInterface call failed, then m_pHpe will be NULL.

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::GetSite
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::GetSite(REFIID riid, VOID ** ppvSite)
{
    *ppvSite = NULL;

    if (m_pHpe == NULL)
        return E_FAIL;      // *ppvSite is already NULL

    return m_pHpe->QueryInterface(riid, ppvSite);
}

////////////////////////////////////////////////////////////
// CHomePlugin::Initialize
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::Initialize(HPLUGIN hPlugin, IXMLDOMNode * pNodeParams, IXMLDOMNode * pNodeDefault)
{
    HRESULT         hr;

    // We must have our IHomePluginEnvironment2 interface pointer by now.
    if (m_pHpe == NULL)
        return E_FAIL;

    // Save our plugin handle, provided to us by the home app.
    m_hPlugin = hPlugin;

    // Initialize our display-attribute classes by getting them to
    // read from the XML nodes.
    if (FAILED(hr = m_dispattrsNormal.Initialize(pNodeDefault, pNodeParams, /*fSelectedState=*/FALSE)))
        return hr;

    if (FAILED(hr = m_dispattrsSel.Initialize(pNodeDefault, pNodeParams, /*fSelectedState=*/TRUE)))
        return hr;

    // Get our only UI string from the appropriate <uistring> node (child
    // of the <plugin> node).
    if (FAILED(hr = GetUIString(pNodeParams, L"initialmessage", &m_wszMessage)))
        return hr;

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::GetHeight
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::GetHeight(INT * pdyPlugin)
{
    if (pdyPlugin == NULL)
        return E_INVALIDARG;

    // The 'height' attribute should ONLY be present in the <default>
    // node or the <plugin> node, so fetch it from there.
    *pdyPlugin = m_dispattrsNormal.GetHeight();

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::GetSelectability
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::GetSelectability(BOOL * pfSelectable)
{
    if (pfSelectable == NULL)
        return E_INVALIDARG;

    *pfSelectable = TRUE;

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::OnEvent
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::OnEvent(PluginEvent * pEvent)
{
    switch(pEvent->idEvent)
    {
        case PE_KEYDOWN:
            if (pEvent->p.key.wVKey == VK_LEFT || pEvent->p.key.wVKey == VK_RIGHT)
            {
                WMP_STATUS  status = m_wmpinfo.GetStatus();
                HWND        hwndComm = GetMediaPlayerPluginWindow();

                if (hwndComm == NULL)
                {
                    // Can't find the plugin communication window, which
                    // presumably means that Windows Media Player shut down
                    // without telling us (perhaps it faulted). Reset our
                    // status.
                    m_wmpinfo.SetStatus(WMP_STATUS_UNKNOWN);
                    m_pHpe->InvalidatePlugin(m_hPlugin, 0);
                }
                else
                {
                    // Tell the WMP plugin to move to the previous or next
                    // media item.
                    PostMessage(hwndComm,
                                pEvent->p.key.wVKey == VK_LEFT ? WM_MPHPSAMPLE_PREV : WM_MPHPSAMPLE_NEXT,
                                0,
                                0);
                }
            }
            break;
        
        case PE_ACTION:
        {
            WMP_STATUS      status = m_wmpinfo.GetStatus();

            if (status == WMP_STATUS_UNKNOWN || m_wmpinfo.GetTitle()[0] == _T('\0'))
            {
                SHELLEXECUTEINFO    sei;

                // If status is WMP_STATUS_UNKNOWN, then Windows Media
                // Player probably isn't running (it's possible that it's
                // running and just hasn't reported to us yet, but there's
                // no way we can tell that).
                //
                // If the title is an empty string, then there is no current
                // media item.
                //
                // In either case, we want to launch Windows Media Player.
                // If it's already running, this will just bring it to the
                // foreground.
                memset(&sei, 0, sizeof(sei));
                sei.cbSize = sizeof(sei);
                sei.lpFile = _T(":WMPlayer");
                sei.nShow = SW_SHOWNORMAL;

                ShellExecuteEx(&sei);
            }
            else
            {
                HWND    hwndComm = GetMediaPlayerPluginWindow();

                // Take this opportunity to check for a NULL HWND value.
                // Even though we *think* Windows Media Player is still
                // running (as evidenced by the status value), it's possible
                // that it shut down without letting us know (e.g., some
                // sort of fault or other unexpected termination). If
                // we can't find the window, there's no point in posting
                // the request, and we should reset our status to 'unknown'.
                if (hwndComm == NULL)
                {
                    m_wmpinfo.SetStatus(WMP_STATUS_UNKNOWN);
                    m_pHpe->InvalidatePlugin(m_hPlugin, 0);
                }
                else
                {
                    if (status == WMP_STATUS_PLAYING)
                        PostMessage(hwndComm, WM_MPHPSAMPLE_PAUSE, 0, 0);
                    else
                        PostMessage(hwndComm, WM_MPHPSAMPLE_PLAY, 0, 0);
                }
            }

            break;
        }
        
        case PE_PAINT:
        {
            HDC                     hdc = pEvent->p.paint.hdc, hdcMem = NULL;
            HBITMAP                 hbmpPrev = NULL;
            BOOL                    fDimButtons = false;
            BOOL                    fSelected = pEvent->p.paint.fSelected;
            INT                     cchTitle;
            HFONT                   hfont, hfontPrev = NULL;
            RECT                    rectFull, rectTitle, rectTemp;
            POINT                   ptPrev, ptPlayPause, ptNext;
            SIZE                    sizeText;
            LPCTSTR                 szTitle;
            TEXTMETRIC              tm;
            CDisplayAttributes *    pDispAttrsUse = (fSelected ? &m_dispattrsSel : &m_dispattrsNormal);

            // First see if we've loaded our buttons bitmap strip; if not,
            // do so now.
            if (m_hbmpButtons == NULL)
            {
                m_hbmpButtons = (HBITMAP)LoadImage( GetModuleHandle(s_szModuleName),
                                                    MAKEINTRESOURCE(IDB_BUTTONS),
                                                    IMAGE_BITMAP,
                                                    0,
                                                    0,
                                                    0);
            }

            // If we have a buttons bitmap, create a compatible (memory) DC
            // and select it in. Note that either call (CreateCompatibleDC
            // or SelectObject) could fail, but we'll handle that by simply
            // not drawing the buttons. That is, we only draw the buttons if
            // hbmpPrev is non-NULL.
            if (m_hbmpButtons != NULL)
            {
                if ((hdcMem = CreateCompatibleDC(hdc)) != NULL)
                    hbmpPrev = (HBITMAP)SelectObject(hdcMem, m_hbmpButtons);
            }

            // Get our drawing rectangle.
            rectFull = pEvent->p.paint.rcDraw;

            // Create our font.
            if ((hfont = GetFont(fSelected)) != NULL)
                hfontPrev = (HFONT)SelectObject(hdc, hfont);

            // Get text metrics for the font.
            GetTextMetrics(hdc, &tm);

            // Calculate the rectangle for the title text.
            if (m_wmpinfo.GetStatus() == WMP_STATUS_UNKNOWN || m_wmpinfo.GetTitle()[0] == _T('\0'))
            {
                szTitle = m_wszMessage;
                fDimButtons = TRUE;
            }
            else
            {
                szTitle = m_wmpinfo.GetTitle();
            }
            cchTitle = _tcslen(szTitle);
            GetTextExtentPoint32(hdc, szTitle, cchTitle, &sizeText);
            rectTitle.left = rectFull.left + pDispAttrsUse->GetLeftPadding();
            rectTitle.right = rectFull.right - pDispAttrsUse->GetRightPadding();
            rectTitle.top = rectFull.top + pDispAttrsUse->GetTopPadding();
            rectTitle.bottom = rectTitle.top + tm.tmHeight;

            // Calculate the locations of the previous, play/pause, and next buttons.
            ptPlayPause.x = (rectFull.left + rectFull.right) / 2 - (CX_BUTTON / 2);
            ptPlayPause.y = rectTitle.bottom + CY_TEXT_BUTTON_PAD;
            ptPrev.x = ptPlayPause.x - CX_INTRA_BUTTON_PAD - CX_BUTTON;
            ptPrev.y = ptPlayPause.y;
            ptNext.x = ptPlayPause.x + CX_BUTTON + CX_INTRA_BUTTON_PAD;
            ptNext.y = ptPlayPause.y;

            // Set up to draw.
            SetTextColor(hdc, pDispAttrsUse->GetFgColor(m_pHpe, m_hPlugin));

            if (pDispAttrsUse->GetBgColor(m_pHpe, m_hPlugin) != CLR_NONE)    // non-transparent case
            {
                SetBkColor(hdc, pDispAttrsUse->GetBgColor(m_pHpe, m_hPlugin));

                // Fill our entire rectangle except for the bottom rule area.
                // Using ExtTextOut to do this (and specifying no actual text
                // to draw) is a trick that allows us to avoid having to create
                // an HBRUSH.
                rectTemp = rectFull;
                rectTemp.bottom -= pDispAttrsUse->GetBBorderWidth();

                ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rectTemp, NULL, 0, NULL);
            }

            // Draw the title information.
            ExtTextOut(hdc, rectTitle.left, rectTitle.top, ETO_CLIPPED, &rectTitle, szTitle, cchTitle, NULL);

            // Draw the buttons.
            DrawButton(hdc, hdcMem, ptPrev.x, ptPrev.y, fDimButtons ? IBTN_DIMPREV : IBTN_PREV);
            if (m_wmpinfo.GetStatus() == WMP_STATUS_PLAYING)
                DrawButton(hdc, hdcMem, ptPlayPause.x, ptPlayPause.y, fDimButtons ? IBTN_DIMPAUSE : IBTN_PAUSE);
            else
                DrawButton(hdc, hdcMem, ptPlayPause.x, ptPlayPause.y, fDimButtons ? IBTN_DIMPLAY : IBTN_PLAY);
            DrawButton(hdc, hdcMem, ptNext.x, ptNext.y, fDimButtons ? IBTN_DIMNEXT : IBTN_NEXT);

            if (pDispAttrsUse->GetBBorderWidth() > 0 && pDispAttrsUse->GetBBorderColor(m_pHpe, m_hPlugin) != CLR_NONE)
            {
                // Draw the bottom rule. Once again, we use the ExtTextOut trick
                // to avoid having to create an HBRUSH or HPEN.
                rectTemp = rectFull;
                rectTemp.top = rectTemp.bottom - pDispAttrsUse->GetBBorderWidth();

                SetBkColor(hdc, pDispAttrsUse->GetBBorderColor(m_pHpe, m_hPlugin));
                ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rectTemp, NULL, 0, NULL);
            }

            // Clean up.
            if (hdcMem != NULL)
            {
                if (hbmpPrev != NULL)
                    SelectObject(hdcMem, hbmpPrev);

                DeleteDC(hdcMem);
            }

            if (hfontPrev != NULL)
                SelectObject(hdc, hfontPrev);

            if (hfont != NULL)
                DeleteObject(hfont);

            break;
        }
        
        case PE_SYSCOLORCHANGE:
            break;
        
        case PE_TIMER:
            // See ThreadProc for comments about this timer notification.
            //
            // Also, see the Notes section in the README.HTM file.
            if (m_fTimerSet)
            {
                m_fTimerSet = FALSE;
                m_pHpe->InvalidatePlugin(m_hPlugin, 0);
            }
            break;
        
        case PE_DATACHANGE:
            break;
        
        default:
            break;
    }
        
    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::GetClassID
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::GetClassID(CLSID * pClassID)
{
    *pClassID = CLSID_HomePlugin;

    return(S_OK);
}

////////////////////////////////////////////////////////////
// CHomePlugin::IsDirty
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::IsDirty()
{
    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::Load
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::Load(IStream * pStm)
{
    HRESULT hr;
    INT     cchMessage;
    ULONG   ulIgnored;

    // Our CDisplayAttributes instances handle most of the hard
    // work of dealing with the XML attributes. The only things
    // we need to load are our plugin handle and our UI message.
    if (FAILED(pStm->Read(&m_hPlugin, sizeof(m_hPlugin), &ulIgnored)))
        return E_FAIL;

    if (FAILED(pStm->Read(&cchMessage, sizeof(cchMessage), &ulIgnored)))
        return E_FAIL;

    if ((m_wszMessage = static_cast<WCHAR *>(malloc(sizeof(WCHAR) * (cchMessage + 1)))) == NULL)
        return E_FAIL;

    if (FAILED(pStm->Read(m_wszMessage, sizeof(WCHAR) * cchMessage, &ulIgnored)))
        return E_FAIL;

    m_wszMessage[cchMessage] = L'\0';

    if  (
        FAILED(hr = m_dispattrsNormal.LoadFromStream(pStm))
        ||
        FAILED(hr = m_dispattrsSel.LoadFromStream(pStm))
        )
        return hr;

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::Save
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::Save(IStream * pStm, BOOL fClearDirty)
{
    HRESULT hr;
    INT     cchMessage;
    ULONG   ulIgnored;

    // Our CDisplayAttributes instances handle most of the hard
    // work of dealing with the XML attributes. The only things
    // we need to save are our plugin handle and our UI message.
    if (FAILED(pStm->Write(&m_hPlugin, sizeof(m_hPlugin), &ulIgnored)))
        return STG_E_CANTSAVE;

    cchMessage = wcslen(m_wszMessage);

    if (FAILED(pStm->Write(&cchMessage, sizeof(cchMessage), &ulIgnored)))
        return STG_E_CANTSAVE;

    if (FAILED(pStm->Write(m_wszMessage, sizeof(WCHAR) * cchMessage, &ulIgnored)))
        return STG_E_CANTSAVE;

    if  (
        FAILED(hr = m_dispattrsNormal.SaveToStream(pStm))
        ||
        FAILED(hr = m_dispattrsSel.SaveToStream(pStm))
        )
        return hr;

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::GetSizeMax
////////////////////////////////////////////////////////////

HRESULT CHomePlugin::GetSizeMax(ULARGE_INTEGER * pcbSize)
{
    pcbSize->LowPart = sizeof(m_hPlugin)
        + sizeof(INT)                           // 'cchMessage'
        + sizeof(WCHAR) * wcslen(m_wszMessage)
        + m_dispattrsNormal.GetSize()
        + m_dispattrsSel.GetSize();

    pcbSize->HighPart = 0;

    return S_OK;
}

////////////////////////////////////////////////////////////
// CHomePlugin::DrawButton
////////////////////////////////////////////////////////////

VOID CHomePlugin::DrawButton(HDC hdcDst, HDC hdcSrc, INT x, INT y, INT iBtn)
{
    TransparentImage(hdcDst, x, y, CX_BUTTON, CY_BUTTON, hdcSrc, iBtn * CX_BUTTON, 0, CX_BUTTON, CY_BUTTON, CLR_BUTTON_TRANSPARENCY);
}

////////////////////////////////////////////////////////////
// CHomePlugin::GetMediaPlayerPluginWindow
////////////////////////////////////////////////////////////

HWND CHomePlugin::GetMediaPlayerPluginWindow()
{
    // Note that we don't cache the window handle since Windows Media Player could be
    // started at any time, and could go away at any time.
    return FindWindow(SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_CLASSNAME, SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_WINDOWNAME);
}

////////////////////////////////////////////////////////////
// CHomePlugin::StaticThreadProc
////////////////////////////////////////////////////////////

/*static*/ DWORD CHomePlugin::StaticThreadProc(VOID * pvParam)
{
    return ((CHomePlugin *)pvParam)->ThreadProc();
}

////////////////////////////////////////////////////////////
// CHomePlugin::ThreadProc
////////////////////////////////////////////////////////////

DWORD CHomePlugin::ThreadProc()
{
    HANDLE  rgHandles[2];

    // Set up our HANDLE array.
    rgHandles[0] = m_hMsgQueue;
    rgHandles[1] = m_hEventLifetime;

    // Loop endlessly. During each iteration of the loop, wait for one of
    // the two objects to become signaled.
    //
    // If m_hMsgQueue is signaled, then our Windows Media Player plugin
    // has a message for us regarding the status of Windows Media Player.
    //
    // If m_hEventLifetime is signaled, we're being asked to shut down,
    // so just return.
    for (;;)
    {
        DWORD   dwObjSignaled;

        dwObjSignaled = WaitForMultipleObjects(2, rgHandles, /*fWaitAll=*/FALSE, INFINITE);

        if (dwObjSignaled == WAIT_OBJECT_0)
        {
            DWORD       cbRead, dwFlags;
            MQMESSAGE   msg;

            // We have a message from our Windows Media Player plugin. Copy the
            // information to our m_wmpinfo instance.
            if (ReadMsgQueue(m_hMsgQueue, &msg, sizeof(msg), &cbRead, INFINITE, &dwFlags) && cbRead == sizeof(msg))
            {
                BOOL    fStatusChanged, fTitleChanged;

                // Note that both SetStatus and SetTitle return TRUE if the value
                // we're passing actually changed.
                //
                // Therefore, if they both return FALSE, nothing really changed and
                // we can ignore this notification.
                //
                // Warning: don't "optimize" the code like this:
                //
                //      if (m_wmpinfo.SetStatus(msg.status) || m_wmpinfo.SetTitle(msg.szMediaTitle))
                //
                // to get rid of the two BOOL variables (fStatusChanged and fTitleChanged)
                // because BOTH methods need to be called. If you were to code it like that,
                // and if the SetStatus method returned TRUE, then the SetTitle method would
                // never be called due to the "short-circuit" behavior of the || operator.
                fStatusChanged = m_wmpinfo.SetStatus(msg.status);
                fTitleChanged = m_wmpinfo.SetTitle(msg.szMediaTitle);

                if (fStatusChanged || fTitleChanged)
                {
                    // We tend to get a LOT of notifications from Media Player, so when we
                    // get a notification, we actually set a short timer and don't invalidate
                    // our plugin until the timer goes off.
                    //
                    // This helps to prevent 'flicker' in the display when Media Player gives
                    // us notifications in a quick sequence like this: { playing, paused, playing,
                    // paused, ... }. Those correspond to internal state changes in Media Player,
                    // and we don't need to draw them all.
                    //
                    // Of course, we don't want to set a one-shot timer if we've already set
                    // one, because then we'd get a slew of timer notifications, one for each
                    // Media Player notification, which wouldn't solve the problem.
                    if (!m_fTimerSet)
                    {
                        if (SUCCEEDED(m_pHpe->SetSingleShotTimer(m_hPlugin, CMSEC_INVALIDATE_TIMER)))
                        {
                            // Remember that we set the timer so we don't do it again until
                            // AFTER it goes off.
                            m_fTimerSet = TRUE;
                        }
                        else
                        {
                            // SetSingleShotTimer failed for some reason, so we're forced to just
                            // invalidate here.
                            m_pHpe->InvalidatePlugin(m_hPlugin, 0);
                        }
                    }
                }
            }
        }
        else
        {
            // This is probably our 'lifetime' event, telling us to shut down. It could
            // also be an error return from WaitForMultipleObjects, but in that case
            // we should just exit as well.
            return 0;
        }
    }
}

////////////////////////////////////////////////////////////
// DLL-level implementation
//
// DllGetClassObject, DllCanUnloadNow and DllRegisterServer
// are exported courtesy of our .DEF file.
////////////////////////////////////////////////////////////

BOOL WINAPI DllMain(HANDLE hModule, DWORD ulReason, VOID * pvReserved)
{
    if (ulReason == DLL_PROCESS_ATTACH)
    {
        if ((g_pServer = new CServer) == NULL)
            return FALSE;
    }
    else if (ulReason == DLL_PROCESS_DETACH)
    {
        delete g_pServer;
    }

    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID clsid, REFIID riid, VOID ** ppv)
{
    HRESULT                     hr;
    CHomePluginClassFactory *   pcf;

    *ppv = NULL;

    if ((pcf = new CHomePluginClassFactory()) == NULL)
        return E_OUTOFMEMORY;

    if (FAILED(hr = pcf->QueryInterface(riid, ppv)))
    {
        delete pcf;
        return hr;
    }

    return S_OK;
}

STDAPI DllCanUnloadNow()
{
    if (g_pServer->CanUnload())
        return S_OK;
    else
        return S_FALSE;
}

STDAPI DllRegisterServer()
{
    TCHAR   szModulePath[MAX_PATH];

    // Get our module path.
    if (!GetModuleFileName(GetModuleHandle(s_szModuleName), szModulePath, MAX_PATH))
        return E_FAIL;

    szModulePath[MAX_PATH - 1] = _T('\0');

    // NOTE THAT THE GUID STRING HERE MUST MATCH CLSID_HomePlugin!
    return DllRegisterServerImplementation(_T("{07326E2E-D59C-4AFF-BBEA-DE783325B5EC}"), s_szRegDescription, szModulePath, _T("Free"));
}
