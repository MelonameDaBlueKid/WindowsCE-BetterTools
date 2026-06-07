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
#include <msgqueue.h>
#include "wmpplug.h"
#include "..\common\comsupport.h"
#include "..\common\communication.h"

////////////////////////////////////////////////////////////
// CLSID_MediaPlayerPlugin
//
// This is the class ID for our plugin.
////////////////////////////////////////////////////////////

// {5FA5BBCA-0DAC-46CA-9AF3-9A61BB92BC9D}
DEFINE_GUID(CLSID_MediaPlayerPlugin, 0x5fa5bbca, 0xdac, 0x46ca, 0x9a, 0xf3, 0x9a, 0x61, 0xbb, 0x92, 0xbc, 0x9d);

////////////////////////////////////////////////////////////
// Global CServer instance
////////////////////////////////////////////////////////////

CServer * g_pServer;

////////////////////////////////////////////////////////////
// Constant strings
////////////////////////////////////////////////////////////

static const TCHAR s_szRegDescription[] = _T("Windows Media Player Plugin - Controlled by Homescreen Plugin");
static const TCHAR s_szModuleName[] = _T("mphp_mediaplayerplugin.dll");

////////////////////////////////////////////////////////////
// CMediaPlayerPluginClassFactory class
//
// This is the 'class factory' (class implementing IClassFactory)
// for our plugin object.
////////////////////////////////////////////////////////////

class CMediaPlayerPluginClassFactory:
    public IClassFactory
{
public:
    ////////////////////////////////////////
    // Constructor, destructor
    ////////////////////////////////////////
    CMediaPlayerPluginClassFactory()
        : m_cRefs(0)
    {
        g_pServer->Lock();
    }

    ~CMediaPlayerPluginClassFactory()
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
// CMediaPlayerPlugin
//
// This is our actual plugin component which implements
// IWMPPluginUI and IWMPEvents.
////////////////////////////////////////////////////////////

class CMediaPlayerPlugin:
    public IWMPPluginUI,
    public IWMPEvents
{
public:
    ////////////////////////////////////////
    // Constructor, destructor
    ////////////////////////////////////////
    CMediaPlayerPlugin()
        : m_cRefs(0),
          m_hwndComm(NULL),
          m_pCore(NULL),
          m_pConnPt(NULL),
          m_dwAdviseCookie(0),
          m_status(WMP_STATUS_UNKNOWN),
          m_wszMediaTitle(NULL)
    {
        g_pServer->Lock();
    }

    ~CMediaPlayerPlugin()
    {
        if (m_wszMediaTitle != NULL)
            free(m_wszMediaTitle);

        if (m_pConnPt != NULL)
        {
            m_pConnPt->Unadvise(m_dwAdviseCookie);
            m_pConnPt->Release();
        }

        if (m_pCore != NULL)
            m_pCore->Release();

        if (m_hwndComm != NULL)
        {
            DestroyWindow(m_hwndComm);
            UnregisterClass(SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_CLASSNAME, NULL);
        }

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
    // WndProcs
    //
    // We have a static version that's our official WndProc; this method looks
    // up our 'this' pointer in window data and then calls our instance WndProc.
    ////////////////////////////////////////
    static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    ////////////////////////////////////////
    // IUnknown implementation (for IWMPPluginUI)
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
    // IWMPPluginUI implementation
    ////////////////////////////////////////
    STDMETHODIMP Create(HWND hwndParent, HWND * phwndWindow);
    STDMETHODIMP Destroy();
    STDMETHODIMP DisplayPropertyPage(HWND hwndParent);
    STDMETHODIMP GetProperty(LPCWSTR wszName, VARIANT * pvarProperty);
    STDMETHODIMP SetCore(IWMPCore * pCore);
    STDMETHODIMP SetProperty(LPCWSTR wszName, const VARIANT * pvarProperty);
    STDMETHODIMP TranslateAccelerator(MSG * pMsg);

    ////////////////////////////////////////
    // IWMPEvents implementation
    ////////////////////////////////////////
    STDMETHODIMP_(VOID) OpenStateChange(LONG NewState);
    STDMETHODIMP_(VOID) PlayStateChange(LONG NewState);
    STDMETHODIMP_(VOID) AudioLanguageChange(LONG LangID);
    STDMETHODIMP_(VOID) StatusChange();
    STDMETHODIMP_(VOID) ScriptCommand(BSTR scType, BSTR Param);
    STDMETHODIMP_(VOID) NewStream();
    STDMETHODIMP_(VOID) Disconnect(LONG Result);
    STDMETHODIMP_(VOID) Buffering(VARIANT_BOOL Start);
    STDMETHODIMP_(VOID) Error();
    STDMETHODIMP_(VOID) Warning(LONG WarningType, LONG Param, BSTR Description);
    STDMETHODIMP_(VOID) EndOfStream(LONG Result);
    STDMETHODIMP_(VOID) PositionChange(DOUBLE oldPosition, DOUBLE newPosition);
    STDMETHODIMP_(VOID) MarkerHit(LONG MarkerNum);
    STDMETHODIMP_(VOID) DurationUnitChange(LONG NewDurationUnit);
    STDMETHODIMP_(VOID) CdromMediaChange(LONG CdromNum);
    STDMETHODIMP_(VOID) PlaylistChange(IDispatch * Playlist, WMPPlaylistChangeEventType change);
    STDMETHODIMP_(VOID) CurrentPlaylistChange(WMPPlaylistChangeEventType change);
    STDMETHODIMP_(VOID) CurrentPlaylistItemAvailable(BSTR bstrItemName);
    STDMETHODIMP_(VOID) MediaChange(IDispatch * Item);
    STDMETHODIMP_(VOID) CurrentMediaItemAvailable(BSTR bstrItemName);
    STDMETHODIMP_(VOID) CurrentItemChange(IDispatch *pdispMedia);
    STDMETHODIMP_(VOID) MediaCollectionChange();
    STDMETHODIMP_(VOID) MediaCollectionAttributeStringAdded(BSTR bstrAttribName,  BSTR bstrAttribVal);
    STDMETHODIMP_(VOID) MediaCollectionAttributeStringRemoved(BSTR bstrAttribName,  BSTR bstrAttribVal);
    STDMETHODIMP_(VOID) MediaCollectionAttributeStringChanged(BSTR bstrAttribName, BSTR bstrOldAttribVal, BSTR bstrNewAttribVal);
    STDMETHODIMP_(VOID) PlaylistCollectionChange();
    STDMETHODIMP_(VOID) PlaylistCollectionPlaylistAdded(BSTR bstrPlaylistName);
    STDMETHODIMP_(VOID) PlaylistCollectionPlaylistRemoved(BSTR bstrPlaylistName);
    STDMETHODIMP_(VOID) PlaylistCollectionPlaylistSetAsDeleted(BSTR bstrPlaylistName, VARIANT_BOOL varfIsDeleted);
    STDMETHODIMP_(VOID) ModeChange(BSTR ModeName, VARIANT_BOOL NewValue);
    STDMETHODIMP_(VOID) MediaError(IDispatch * pMediaObject);
    STDMETHODIMP_(VOID) OpenPlaylistSwitch(IDispatch *pItem);
    STDMETHODIMP_(VOID) DomainChange(BSTR strDomain);
    STDMETHODIMP_(VOID) SwitchedToPlayerApplication();
    STDMETHODIMP_(VOID) SwitchedToControl();
    STDMETHODIMP_(VOID) PlayerDockedStateChange();
    STDMETHODIMP_(VOID) PlayerReconnect();
    STDMETHODIMP_(VOID) Click(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY);
    STDMETHODIMP_(VOID) DoubleClick(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY);
    STDMETHODIMP_(VOID) KeyDown(SHORT nKeyCode, SHORT nShiftState);
    STDMETHODIMP_(VOID) KeyPress(SHORT nKeyAscii);
    STDMETHODIMP_(VOID) KeyUp(SHORT nKeyCode, SHORT nShiftState);
    STDMETHODIMP_(VOID) MouseDown(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY);
    STDMETHODIMP_(VOID) MouseMove(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY);
    STDMETHODIMP_(VOID) MouseUp(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY);

private:
    ////////////////////////////////////////
    // Implementation methods
    ////////////////////////////////////////

    // Searches for the message queue object that the homescreen plugin
    // creates and returns it (or NULL if it doesn't exist). It is the
    // caller's responsibility to pass the HANDLE to CloseMsgQueue when
    // it's no longer required.
    HANDLE FindMsgQueue();

    // Queries MediaPlayer for the current media title.
    //
    // If successful, calls SetMediaTitle with the media title and calls
    // SendStatusUpdate (if fSendStatusUpdate is TRUE).
    //
    // If unsuccessful, calls SetMediaTitle(NULL) and calls SendStatus-
    // Update (if fSendStatusUpdate is TRUE).
    VOID UpdateMediaTitle(BOOL fSendStatusUpdate = TRUE);

    // Set our current media title.
    VOID SetMediaTitle(LPCWSTR wszMediaTitle)
    {
        if (m_wszMediaTitle != NULL)
            free(m_wszMediaTitle);

        if (wszMediaTitle == NULL)
            m_wszMediaTitle = NULL;
        else
            m_wszMediaTitle = wcsdup(wszMediaTitle);    // will be NULL if failed
    }

    // Send a status-update message to the homescreen plugin, if it exists,
    // using m_status and m_wszMediaTitle.
    VOID SendStatusUpdate();

    // Control the player: start or resume playing, pause, move to next in
    // playlist, move to previous in playlist. The parameter is the window
    // message we were sent: WM_MPHPSAMPLE_PLAY, WM_MPHPSAMPLE_PAUSE,
    // WM_MPHPSAMPLE_NEXT or WM_MPHPSAMPLE_PREV.
    VOID ControlPlayer(UINT uMsg);

    ////////////////////////////////////////
    // Data
    ////////////////////////////////////////
    CThreadSafeULONG    m_cRefs;            // Thread-safe reference count
    HWND                m_hwndComm;         // Our hidden communication window
    IWMPCore *          m_pCore;            // Cached interface pointer for communicating with Windows Media Player
    IConnectionPoint *  m_pConnPt;          // Connection point used to register for events
    DWORD               m_dwAdviseCookie;   // 'Cookie' associated with IConnectionPoint::Advise call
    WMP_STATUS          m_status;           // Current status of Windows Media Player
    LPWSTR              m_wszMediaTitle;    // Current media title
};

////////////////////////////////////////////////////////////
// CMediaPlayerPluginClassFactory::QueryInterface
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPluginClassFactory::QueryInterface(REFIID riid, VOID ** ppvObject)
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
// CMediaPlayerPluginClassFactory::CreateInstance
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPluginClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, VOID ** ppvObject)
{
    HRESULT                 hr;
    CMediaPlayerPlugin *    pPlugin;

    // Assume failure.
    *ppvObject = NULL;

    // We don't support aggregation.
    if (pUnkOuter != NULL)
        return CLASS_E_NOAGGREGATION;

    // Create the plugin instance.
    if ((pPlugin = new CMediaPlayerPlugin()) == NULL)
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
// CMediaPlayerPluginClassFactory::LockServer
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPluginClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        g_pServer->Lock();
    else
        g_pServer->Unlock();

    return S_OK;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::QueryInterface
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::QueryInterface(REFIID riid, VOID ** ppvObject)
{
    *ppvObject = NULL;

    if (IsEqualIID(riid, __uuidof(IUnknown)))
        *ppvObject = static_cast<IUnknown *>(static_cast<IWMPPluginUI *>(this));
    else if (IsEqualIID(riid, __uuidof(IWMPPluginUI)))
        *ppvObject = static_cast<IWMPPluginUI *>(this);
    else if (IsEqualIID(riid, __uuidof(IWMPEvents)))
        *ppvObject = static_cast<IWMPEvents *>(this);

    if (*ppvObject == NULL)
        return E_NOINTERFACE;

    AddRef();

    return S_OK;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::FinalConstruct
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::FinalConstruct()
{
    WNDCLASS    wc;

    // As stated in the class declaration, here's where we create our
    // hidden communication window.
    //
    // First, of course, we have to register our window class.
    wc.style = 0;
    wc.lpfnWndProc = StaticWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = NULL;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_CLASSNAME;

    if (RegisterClass(&wc) == 0)
        return HRESULT_FROM_WIN32(GetLastError());

    // Now create the window.
    m_hwndComm = CreateWindow(  SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_CLASSNAME,
                                SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_WINDOWNAME,
                                WS_OVERLAPPED,      // style (note: does NOT include WS_VISIBLE)
                                0,                  // x
                                0,                  // y
                                1,                  // width
                                1,                  // height
                                NULL,               // parent window handle
                                NULL,               // menu
                                NULL,               // instance handle
                                NULL);              // parameter

    if (m_hwndComm == NULL)
    {
        UnregisterClass(SZ_MEDIAPLAYERPLUGIN_COMMWINDOW_CLASSNAME, NULL);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    // Add our 'this' pointer to the window data.
    SetWindowLong(m_hwndComm, GWL_USERDATA, reinterpret_cast<LONG>(this));

    return S_OK;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::StaticWndProc
////////////////////////////////////////////////////////////

/*static*/ LRESULT CALLBACK CMediaPlayerPlugin::StaticWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CMediaPlayerPlugin *   pThis;

    // Fetch our 'this' pointer from window data.
    //
    // NOTE: Since we don't SET this value until AFTER the window is created
    // (see FinalConstruct), we're not guaranteed to have this value yet. That
    // is, AS the window is being constructed, we'll get some set of messages
    // here and we won't yet have our 'this' pointer. Therefore, just punt those
    // to DefWindowProc.
    if ((pThis = reinterpret_cast<CMediaPlayerPlugin *>(GetWindowLong(hwnd, GWL_USERDATA))) == NULL)
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    else
        return pThis->WndProc(hwnd, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::WndProc
////////////////////////////////////////////////////////////

LRESULT CMediaPlayerPlugin::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_MPHPSAMPLE_REPORT:
            SendStatusUpdate();
            break;

        case WM_MPHPSAMPLE_PLAY:
        case WM_MPHPSAMPLE_PAUSE:
        case WM_MPHPSAMPLE_NEXT:
        case WM_MPHPSAMPLE_PREV:
            ControlPlayer(uMsg);
            break;

        default:
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::Create
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::Create(HWND hwndParent, HWND * phwndWindow)
{
    // As per the IWMPPluginUI documentation, this method will never be called
    // because we're a background plugin (our registry Capabilities flags include
    // PLUGIN_TYPE_BACKGROUND = 0x00000001).

    return E_NOTIMPL;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::Destroy
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::Destroy()
{
    MQMESSAGE   msg;
    HANDLE      hMsgQueue;

    // Despite what the SDK docs say, this method _will_ be called when Windows
    // Media Player is shutting down.
    //
    // Use this as an opportunity to tell the homescreen plugin to reset our
    // status to 'unknown' (essentially: not running).
    if ((hMsgQueue = FindMsgQueue()) != NULL)
    {
        msg.status = WMP_STATUS_UNKNOWN;
        msg.szMediaTitle[0] = _T('\0');

        // Write the message. If this fails, we just ignore it as there's not much we can
        // do about it.
        WriteMsgQueue(hMsgQueue, &msg, sizeof(msg), INFINITE, 0);

        // Clean up.
        CloseMsgQueue(hMsgQueue);
    }

    return S_OK;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::DisplayPropertyPage
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::DisplayPropertyPage(HWND hwndParent)
{
    // We provide no property pages, and therefore don't need to do anything here.

    return E_NOTIMPL;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::GetProperty
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::GetProperty(LPCWSTR wszName, VARIANT * pvarProperty)
{
    return S_OK;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::SetCore
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::SetCore(IWMPCore * pCore)
{
    IConnectionPointContainer *     pCPC;

    // This method is called shortly after this instance is created, and allows
    // us to hook up to Windows Media Player. Save the interface pointer.
    //
    // When WMP is shutting down, it calls SetCore(NULL) so we have to handle that
    // as well.
    if (m_pCore != NULL)
    {
        // If we had a core interface, and if we were registered for events,
        // we'd better unregister now.
        if (m_pConnPt != NULL)
        {
            m_pConnPt->Unadvise(m_dwAdviseCookie);
            m_pConnPt->Release();
            m_pConnPt = NULL;
        }

        m_pCore->Release();
    }

    m_pCore = pCore;

    if (m_pCore != NULL)
    {
        m_pCore->AddRef();

        // Register for events.
        if (SUCCEEDED(pCore->QueryInterface(__uuidof(IConnectionPointContainer), (VOID **)&pCPC)))
        {
            IConnectionPoint *  pCP;

            if (SUCCEEDED(pCPC->FindConnectionPoint(__uuidof(IWMPEvents), &pCP)))
            {
                if (SUCCEEDED(pCP->Advise(static_cast<IUnknown *>(static_cast<IWMPEvents *>(this)), &m_dwAdviseCookie)))
                    m_pConnPt = pCP;    // transfer ref 'ownership'
            }

            pCPC->Release();
        }
    }

    // Attempt to write a status update to the homescreen plugin's message queue.
    if (m_pCore != NULL)
        SendStatusUpdate();

    return S_OK;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::SetProperty
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::SetProperty(LPCWSTR wszName, const VARIANT * pvarProperty)
{
    return S_OK;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::TranslateAccelerator
////////////////////////////////////////////////////////////

HRESULT CMediaPlayerPlugin::TranslateAccelerator(MSG * pMsg)
{
    // We have no reason to want to respond to keystroke events.

    return S_FALSE;
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin event handlers.
////////////////////////////////////////////////////////////

VOID CMediaPlayerPlugin::OpenStateChange(LONG lNewState)
{
    // If we get wmposPlaylistOpenNoMedia, don't fetch the
    // current media title, because it sometimes gets reported
    // back incorrectly.
    //
    // In fact, in that case, set our current title to NULL.
    if (lNewState == wmposPlaylistOpenNoMedia)
    {
        SetMediaTitle(NULL);
        SendStatusUpdate();
    }
    else
    {
        UpdateMediaTitle();
    }
}

VOID CMediaPlayerPlugin::PlayStateChange(LONG lNewState)
{
    switch (lNewState)
    {
        case wmppsStopped:
            m_status = WMP_STATUS_STOPPED;
            break;

        case wmppsPaused:
            m_status = WMP_STATUS_PAUSED;
            break;

        case wmppsPlaying:
            m_status = WMP_STATUS_PLAYING;
            break;

        default:
            m_status = WMP_STATUS_OTHER;
            break;
    }

    UpdateMediaTitle();
}

VOID CMediaPlayerPlugin::AudioLanguageChange(LONG lLangID) { }
VOID CMediaPlayerPlugin::StatusChange() { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::ScriptCommand(BSTR scType, BSTR bstrParam) { }
VOID CMediaPlayerPlugin::NewStream() { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::Disconnect(LONG lResult) { }
VOID CMediaPlayerPlugin::Buffering(VARIANT_BOOL vfStart) { }
VOID CMediaPlayerPlugin::Error() { }
VOID CMediaPlayerPlugin::Warning(LONG lWarningType, LONG lParam, BSTR bstrDescription) { }
VOID CMediaPlayerPlugin::EndOfStream(LONG lResult) { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::PositionChange(DOUBLE dblOldPosition, DOUBLE dblNewPosition) { }
VOID CMediaPlayerPlugin::MarkerHit(LONG lMarkerNum) { }
VOID CMediaPlayerPlugin::DurationUnitChange(LONG lNewDurationUnit) { }
VOID CMediaPlayerPlugin::CdromMediaChange(LONG lCdromNum) { }
VOID CMediaPlayerPlugin::PlaylistChange(IDispatch * pdispPlaylist, WMPPlaylistChangeEventType change) { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::CurrentPlaylistChange(WMPPlaylistChangeEventType change) { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::CurrentPlaylistItemAvailable(BSTR bstrItemName) { }
VOID CMediaPlayerPlugin::MediaChange(IDispatch * pdispItem) { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::CurrentMediaItemAvailable(BSTR bstrItemName) { }
VOID CMediaPlayerPlugin::CurrentItemChange(IDispatch *pdispMedia) { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::MediaCollectionChange() { }
VOID CMediaPlayerPlugin::MediaCollectionAttributeStringAdded(BSTR bstrAttribName,  BSTR bstrAttribVal) { }
VOID CMediaPlayerPlugin::MediaCollectionAttributeStringRemoved(BSTR bstrAttribName,  BSTR bstrAttribVal) { }
VOID CMediaPlayerPlugin::MediaCollectionAttributeStringChanged(BSTR bstrAttribName, BSTR bstrOldAttribVal, BSTR bstrNewAttribVal) { }
VOID CMediaPlayerPlugin::PlaylistCollectionChange() { }
VOID CMediaPlayerPlugin::PlaylistCollectionPlaylistAdded(BSTR bstrPlaylistName) { }
VOID CMediaPlayerPlugin::PlaylistCollectionPlaylistRemoved(BSTR bstrPlaylistName) { }
VOID CMediaPlayerPlugin::PlaylistCollectionPlaylistSetAsDeleted(BSTR bstrPlaylistName, VARIANT_BOOL vfIsDeleted) { }
VOID CMediaPlayerPlugin::ModeChange(BSTR bstrModeName, VARIANT_BOOL vfNewValue) { }
VOID CMediaPlayerPlugin::MediaError(IDispatch * pdispMediaObject) { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::OpenPlaylistSwitch(IDispatch *pdispItem) { UpdateMediaTitle(); }
VOID CMediaPlayerPlugin::DomainChange(BSTR bstrDomain) { }
VOID CMediaPlayerPlugin::SwitchedToPlayerApplication() { }
VOID CMediaPlayerPlugin::SwitchedToControl() { }
VOID CMediaPlayerPlugin::PlayerDockedStateChange() { }
VOID CMediaPlayerPlugin::PlayerReconnect() { }
VOID CMediaPlayerPlugin::Click(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY) { }
VOID CMediaPlayerPlugin::DoubleClick(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY) { }
VOID CMediaPlayerPlugin::KeyDown(SHORT nKeyCode, SHORT nShiftState) { }
VOID CMediaPlayerPlugin::KeyPress(SHORT nKeyAscii) { }
VOID CMediaPlayerPlugin::KeyUp(SHORT nKeyCode, SHORT nShiftState) { }
VOID CMediaPlayerPlugin::MouseDown(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY) { }
VOID CMediaPlayerPlugin::MouseMove(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY) { }
VOID CMediaPlayerPlugin::MouseUp(SHORT nButton, SHORT nShiftState, LONG fX, LONG fY) { }

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::FindMsgQueue
////////////////////////////////////////////////////////////

HANDLE CMediaPlayerPlugin::FindMsgQueue()
{
    MSGQUEUEOPTIONS     mqo;

    mqo.dwSize = sizeof(mqo);
    mqo.dwFlags = DW_MSGQUEUE_FLAGS;
    mqo.dwMaxMessages = DW_MSGQUEUE_MAXMSGS;
    mqo.cbMaxMessage = sizeof(MQMESSAGE);
    mqo.bReadAccess = FALSE;

    return CreateMsgQueue(SZ_MSGQUEUE_NAME, &mqo);
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::UpdateMediaTitle
////////////////////////////////////////////////////////////

VOID CMediaPlayerPlugin::UpdateMediaTitle(BOOL fSendStatusUpdate /*=TRUE*/)
{
    BOOL            fHaveTitle = FALSE;
    IWMPControls *  pControls;

    if (SUCCEEDED(m_pCore->get_controls(&pControls)))
    {
        IWMPMedia *     pMedia;

        if (SUCCEEDED(pControls->get_currentItem(&pMedia)))
        {
            BSTR    bstrName;

            if (SUCCEEDED(pMedia->get_name(&bstrName)))
            {
                SetMediaTitle(bstrName);    // this will copy string...
                SysFreeString(bstrName);    // ...so we can free it now
                fHaveTitle = TRUE;
            }

            pMedia->Release();
        }

        pControls->Release();
    }

    if (!fHaveTitle)
        SetMediaTitle(NULL);

    if (fSendStatusUpdate)
        SendStatusUpdate();
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::SendStatusUpdate
////////////////////////////////////////////////////////////

VOID CMediaPlayerPlugin::SendStatusUpdate()
{
    HANDLE          hMsgQueue;
    MQMESSAGE       msg;

    // If the message queue object owned by the homescreen plugin
    // doesn't exist, we can't continue here.
    if ((hMsgQueue = FindMsgQueue()) == NULL)
        return;

    // Set up our message.
    msg.status = m_status;

    if (m_wszMediaTitle == NULL)
        msg.szMediaTitle[0] = _T('\0');
    else
        StringCchCopy(msg.szMediaTitle, CCH_MEDIA_TITLE_MAX, m_wszMediaTitle);

    // Write the message. If this fails, we just ignore it as there's not much we can
    // do about it.
    WriteMsgQueue(hMsgQueue, &msg, sizeof(msg), INFINITE, 0);

    // Clean up.
    CloseMsgQueue(hMsgQueue);
}

////////////////////////////////////////////////////////////
// CMediaPlayerPlugin::ControlPlayer
////////////////////////////////////////////////////////////

VOID CMediaPlayerPlugin::ControlPlayer(UINT uMsg)
{
    IWMPControls *  pControls;

    // Get the 'controls' interface.
    if (SUCCEEDED(m_pCore->get_controls(&pControls)))
    {
        switch (uMsg)
        {
            case WM_MPHPSAMPLE_PLAY:
                pControls->play();
                break;

            case WM_MPHPSAMPLE_PAUSE:
                pControls->pause();
                break;

            case WM_MPHPSAMPLE_PREV:
                pControls->previous();
                break;

            case WM_MPHPSAMPLE_NEXT:
                pControls->next();
                break;

            default:
                break;
        }

        pControls->Release();
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
    HRESULT                             hr;
    CMediaPlayerPluginClassFactory *    pcf;

    *ppv = NULL;

    if ((pcf = new CMediaPlayerPluginClassFactory()) == NULL)
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

    return DllRegisterServerImplementation(_T("{5FA5BBCA-0DAC-46CA-9AF3-9A61BB92BC9D}"), s_szRegDescription, szModulePath, _T("Free"));
}
