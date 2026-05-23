///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>
#include "commctrl.h"
#include <tchar.h>
#include <malloc.h> 
#include <memory.h>
#include <aygshell.h>
#include <winuserm.h>
#include <ocidl.h>
#include <home.h>

/*

Add this to your .home.xml file to see this plugin:
If you are creating a new plugin based on this code
you absolutely must change the clsid!

    <plugin clsid="{30DF3430-0266-11cf-BAA6-00AA003E0EED}">
    </plugin>


*/

#define IMAGENAME TEXT("helloplug.dll")
ULONG g_dwDLLRefCount = 0;

#define INITGUID
#include "initguid.h"

// {30DF3430-0266-11cf-BAA6-00AA003E0EED}
// If you are creating a new plugin based on this code
// you absolutely must change the clsid!
DEFINE_GUID(CLSID_PLUGHELLO, 0x30df3430, 0x266, 0x11cf, 0xba, 0xa6, 0x0, 0xaa, 0x0, 0x3e, 0xe, 0xed);
#define CLSIDTEXT__PLUGHELLO TEXT("30DF3430-0266-11cf-BAA6-00AA003E0EED")


DEFINE_GUID(IID_IHomePlugin, 0x7F0C58E9, 0x4F30, 0x47bb, 0x96, 0x93, 0xd7, 0x78, 0xe9, 0x99, 0xc4, 0x33);
DEFINE_GUID(IID_IHomePluginEnvironment, 0xFF328DC0, 0x22F5, 0x4AC1, 0xA1, 0x03, 0x19, 0xB3, 0x89, 0xC6, 0x33, 0xFA);
DEFINE_GUID(IID_IPersistStream, 0x00000109, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_GUID(IID_IPersist, 0x0000010c, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_GUID(IID_IObjectWithSite, 0xFC4801A3, 0x2BA9, 0x11CF, 0xA2, 0x29, 0x00, 0xAA, 0x00, 0x3D, 0x73, 0x52);

#include "home.h"
#include <COGUID.H>
#undef INITGUID


#undef INITGUID

// Helper for writing information to the debugger.
TCHAR g_szBuffer[2000];
void DebugOut(const TCHAR* szFormat, ...)
{
    va_list vaMarker;

    va_start(vaMarker, szFormat);
    wvsprintf(g_szBuffer, szFormat, vaMarker);
    va_end(vaMarker);

    #ifdef DEBUG
    OutputDebugString(g_szBuffer);
    #endif
}


class PluginFactory : public IClassFactory
{
    int m_cRef;

public:
    PluginFactory();
    virtual ~PluginFactory();

    // IUnknown interface
    STDMETHODIMP QueryInterface(REFIID riid, void** ppObject);
    STDMETHODIMP_(ULONG) AddRef() { m_cRef++; return m_cRef; }
    STDMETHODIMP_(ULONG) Release() {m_cRef--; if(m_cRef > 0) { return(m_cRef); } delete this; return 0; }

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppObject);
    STDMETHODIMP LockServer(BOOL fLock);
};

class PluginHello :
    public IHomePlugin,
    public IPersistStream
{
    int m_cRef;
    IHomePluginEnvironment* m_ppe;

  public:
    PluginHello();
    virtual ~PluginHello();

    // IUnknown interface
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj); 
    STDMETHODIMP_(ULONG) AddRef() { m_cRef++; return m_cRef; }
    STDMETHODIMP_(ULONG) Release() {m_cRef--; if(m_cRef > 0) { return(m_cRef); } delete this; return 0; }

    // IObjectWithSite methods
    virtual STDMETHODIMP SetSite(IUnknown* pSite);
    virtual STDMETHODIMP GetSite(REFIID riid, void** ppvSite);
    
    // IHomePlugin interface (see phonehome.idl for documentation)
    STDMETHODIMP Initialize(HPLUGIN hPlugin, IXMLDOMNode* pnodeParams, IXMLDOMNode* pnodeDefault);
    STDMETHODIMP GetHeight(int* pdyPlugin);
    STDMETHODIMP GetSelectability(BOOL* pfSelectable);
    STDMETHODIMP OnEvent(PluginEvent* ppe);

    // IPersist interface
    virtual STDMETHODIMP GetClassID(CLSID* pClassID);

    // IPersistStream interface
    virtual STDMETHODIMP IsDirty(void);
    virtual STDMETHODIMP Load(IStream* pStm);
    virtual STDMETHODIMP Save(IStream *pStm, BOOL fClearDirty);
    virtual STDMETHODIMP GetSizeMax(ULARGE_INTEGER* pcbSize);
    
};

PluginFactory::PluginFactory() :
    m_cRef(1)
{
}

PluginFactory::~PluginFactory()
{
}

HRESULT PluginFactory::QueryInterface(
    REFIID riid,
    void** ppObject
    )
{
    HRESULT hr = S_OK;
    
    if(riid == IID_IUnknown || riid == IID_IClassFactory)
        {
        *ppObject= (IClassFactory*)this;
        }
    else
        {
        hr = E_NOINTERFACE;
        goto Error;
        }

    AddRef();

Error:
    return(hr);
}

HRESULT PluginFactory::CreateInstance(
    IUnknown *pUnkOuter,
    REFIID riid,
    void** ppObject
    )
{
    HRESULT hr = S_OK;
    IUnknown* punk = NULL;
    
    *ppObject = NULL;

    if(pUnkOuter != NULL)
        {
        hr = CLASS_E_NOAGGREGATION;
        goto Error;
        }

    punk = (IUnknown*)(IHomePlugin*) new PluginHello;
    if(!punk)
        {
        hr = E_OUTOFMEMORY;
        goto Error;
        }

    if(FAILED(punk->QueryInterface(riid, ppObject)))
        {
        hr = E_NOINTERFACE;
        goto Error;
        }

Error:
    if(punk)
        {
        punk->Release();
        }
    return hr;
}

HRESULT PluginFactory::LockServer(
    BOOL fLock
    )
{
    if(fLock)
        {
        g_dwDLLRefCount++;
        }
    else
        {
        g_dwDLLRefCount--;
        }
    return(S_OK);
}

STDAPI DllGetClassObject(
    REFCLSID rclsid,
    REFIID riid,
    void** ppObject
    )
{
    HRESULT hr = S_OK;
    PluginFactory *pFactory = NULL;
    
    if(rclsid == CLSID_PLUGHELLO)
        {
        pFactory = new PluginFactory;
        if(!pFactory)
            {
            hr = E_OUTOFMEMORY;
            goto Error;
            }

        if(FAILED(pFactory->QueryInterface(riid, ppObject)))
            {
            hr = E_NOINTERFACE;
            goto Error;
            }
        }
    else
        {
        hr = CLASS_E_CLASSNOTAVAILABLE;
        goto Error;
        }


Error:
    if(pFactory)
        {
        pFactory->Release();
        }
    return(hr);
}

STDAPI DllCanUnloadNow()
{
    if(g_dwDLLRefCount)
        {
        return S_FALSE;
        }
    else
        {
        return S_OK;
        }
}

STDAPI DllRegisterServer(void)
{
    HRESULT hr = S_OK;
    HKEY hKeyCLSID = NULL;
    HKEY hKeyInproc32 = NULL;
    DWORD dwDisposition;
    HMODULE hModule;
    TCHAR szName[MAX_PATH+1];

    if(ERROR_SUCCESS != RegCreateKeyEx(HKEY_CLASSES_ROOT,
            TEXT("CLSID\\{") CLSIDTEXT__PLUGHELLO TEXT("}"), 
            NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
            &hKeyCLSID, &dwDisposition))
        {
        hr = E_FAIL;
        goto Error;
        }

    if(ERROR_SUCCESS != RegSetValueEx(hKeyCLSID, TEXT(""), NULL, REG_SZ, (BYTE*) TEXT("Demo Plugin"), sizeof(TEXT("Demo Plugin"))))
        {
        hr = E_FAIL;
        goto Error;
        }

    if(ERROR_SUCCESS != RegCreateKeyEx(hKeyCLSID, TEXT("InprocServer32"), 
            NULL, TEXT(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
            &hKeyInproc32, &dwDisposition))
        {
        hr = E_FAIL;
        goto Error;
        }

    hModule = GetModuleHandle(IMAGENAME);
    if(!hModule)
        {
        hr = E_FAIL;
        goto Error;
        }

    if(GetModuleFileName(hModule, szName, sizeof(szName))==0)
        {
        hr = E_FAIL;
        goto Error;
        }

    if(ERROR_SUCCESS != RegSetValueEx(hKeyInproc32, TEXT(""), NULL, REG_SZ, (BYTE*) szName, sizeof(TCHAR)*(lstrlen(szName)+1)))
        {
        hr = E_FAIL;
        goto Error;
        }

Error:
    if(hKeyInproc32)
        {
        RegCloseKey(hKeyInproc32);
        }
    if(hKeyCLSID)
        {
        RegCloseKey(hKeyCLSID);
        }
    return(hr);
}

STDAPI DllUnregisterServer(void)
{
    HRESULT hr = S_OK;
    
    if(ERROR_SUCCESS != RegDeleteKey(HKEY_CLASSES_ROOT, 
            TEXT("CLSID\\{") CLSIDTEXT__PLUGHELLO TEXT("}\\InprocServer32")))
        {
        hr = E_FAIL;
        goto Error;
        }
    if(ERROR_SUCCESS != RegDeleteKey(HKEY_CLASSES_ROOT, 
            TEXT("CLSID\\{") CLSIDTEXT__PLUGHELLO TEXT("}")))
        {
        hr = E_FAIL;
        goto Error;
        }

Error:
    return(hr);
}

PluginHello::PluginHello() :
    m_cRef(1),
    m_ppe(NULL)
{
    g_dwDLLRefCount++;
}

PluginHello::~PluginHello()
{
    g_dwDLLRefCount--;
}


HRESULT PluginHello::QueryInterface(REFIID riid, void** ppObject)
{
    HRESULT hr = S_OK;
    
    if(IID_IUnknown == riid || IID_IObjectWithSite == riid || IID_IHomePlugin == riid)
        {
        *ppObject = (IHomePlugin*)this;
        }
    else if(IID_IPersist == riid || IID_IPersistStream == riid)
        {
        *ppObject = (IPersistStream*)this;
        }
    else
        {
        hr = E_NOINTERFACE;
        goto Error;
        }
    AddRef();

Error:
    return(hr);
}

HRESULT PluginHello::SetSite(IUnknown* pSite)
{
    HRESULT hr = S_OK;

    if(m_ppe)
        {
        m_ppe->Release();
        m_ppe = NULL;
        }

    if(pSite)
        {
        if(FAILED(hr = pSite->QueryInterface(IID_IHomePluginEnvironment, (void**)&m_ppe)))
            {
            goto Error;
            }
        }

Error:
    return(hr);
}

HRESULT PluginHello::GetSite(REFIID riid, void** ppvSite)
{
    HRESULT hr = S_OK;

    if(!m_ppe)
        {
        hr = E_FAIL;
        goto Error;
        }

    if(FAILED(hr = m_ppe->QueryInterface(riid, ppvSite)))
        {
        goto Error;
        }

Error:
    return(hr);
}

HRESULT PluginHello::Initialize(HPLUGIN hPlugin, IXMLDOMNode* pnodeParams, IXMLDOMNode* pnodeDefault)
{
    HRESULT hr = S_OK;

    DebugOut(TEXT("PluginHello::Initialize called \r\n"));

// Error:
    return(hr);
}

HRESULT PluginHello::GetHeight(int* pdyPlugin)
{
    HRESULT hr = S_OK;

    DebugOut(TEXT("PluginHello::GetHeight called \r\n"));

    *pdyPlugin = 20;

// Error:
    return(hr);
}

HRESULT PluginHello::GetSelectability(BOOL* pfSelectable)
{
    HRESULT hr = S_OK;

    DebugOut(TEXT("PluginHello::GetSelectability called \r\n"));

    *pfSelectable = FALSE;

// Error:
    return(hr);
}

HRESULT PluginHello::OnEvent(PluginEvent* ppe)
{
    HRESULT hr = S_OK;

    switch(ppe->idEvent)
        {
        case PE_KEYDOWN:
            DebugOut(TEXT("PluginHello::OnEvent - got event PE_KEYDOWN\r\n"));
            break;

        case PE_ACTION:
            DebugOut(TEXT("PluginHello::OnEvent - got event PE_ACTION\r\n"));
            break;
            
        case PE_PAINT:
            DebugOut(TEXT("PluginHello::OnEvent - got event PE_PAINT\r\n"));
            DrawText(ppe->p.paint.hdc, TEXT("Hello World"), -1, const_cast<RECT*>(&(ppe->p.paint.rcDraw)),
                    DT_SINGLELINE | DT_VCENTER | DT_CENTER);
            break;

        case PE_SYSCOLORCHANGE:
            DebugOut(TEXT("PluginHello::OnEvent - got event PE_SYSCOLORCHANGE\r\n"));
            break;

        case PE_TIMER:
            DebugOut(TEXT("PluginHello::OnEvent - got event PE_TIMER\r\n"));
            break;

        case PE_DATACHANGE:
            DebugOut(TEXT("PluginHello::OnEvent - got event PE_DATACHANGE\r\n"));
            break;

        default:
            break;
        }

// Error:
    return(hr);
}

HRESULT PluginHello::GetClassID(CLSID* pClassID)
{
    *pClassID = CLSID_PLUGHELLO;
    return(S_OK);
}

HRESULT PluginHello::IsDirty(void)
{
    return(S_OK);
}

HRESULT PluginHello::Load(IStream* pStm)
{
    // Nothing to load
    return(S_OK);
}

HRESULT PluginHello::Save(IStream *pStm, BOOL fClearDirty)
{
    // Nothing to save
    return(S_OK);
}

HRESULT PluginHello::GetSizeMax(ULARGE_INTEGER* pcbSize)
{
    ULONGLONG* pl = (ULONGLONG*)pcbSize;

    *pl = 0;

    return(S_OK);
}


