//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#include <windows.h>
#include <memory.h>
#include <ocidl.h>
#include <home.h>

#define ARRAYSIZE(a)   (sizeof(a)/sizeof(*a))


/*

Add this to your .home.xml file to see this plugin:
If you are creating a new plugin based on this code
you absolutely must change the clsid!

	<plugin clsid="{55EE36E7-7CC3-47e8-85E2-1D8644280E7A}" name="Memory Usage" height="40">
	</plugin>


*/

#define IMAGENAME TEXT("homescreen.dll")
ULONG g_dwDLLRefCount = 0;

#define INITGUID
#include "initguid.h"


//{55EE36E7-7CC3-47e8-85E2-1D8644280E7A}

// If you are creating a new plugin based on this code
// you absolutely must change the clsid!

DEFINE_GUID(CLSID_PLUGMEM, 
0x55ee36e7, 0x7cc3, 0x47e8, 0x85, 0xe2, 0x1d, 0x86, 0x44, 0x28, 0xe, 0x7a);

#define CLSIDTEXT__PLUGMEM TEXT("55EE36E7-7CC3-47e8-85E2-1D8644280E7A")

// define all IID GUIDs

DEFINE_GUID(IID_IHomePlugin, 0x7F0C58E9, 0x4F30, 0x47bb, 0x96, 0x93, 0xd7, 0x78, 0xe9, 0x99, 0xc4, 0x33);
DEFINE_GUID(IID_IHomePluginEnvironment,  0xFF328DC0, 0x22F5, 0x4AC1, 0xA1, 0x03, 0x19, 0xB3, 0x89, 0xC6, 0x33, 0xFA);
DEFINE_GUID(IID_IHomePluginEnvironment2, 0xE01A8A84, 0xDDEF, 0x438e, 0x90, 0x04, 0x3F, 0xB2, 0xA9, 0x08, 0xE4, 0x65);
DEFINE_GUID(IID_IPersistStream, 0x00000109, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_GUID(IID_IPersist, 0x0000010c, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_GUID(IID_IObjectWithSite, 0xFC4801A3, 0x2BA9, 0x11CF, 0xA2, 0x29, 0x00, 0xAA, 0x00, 0x3D, 0x73, 0x52);

//#include "home.h"
#include <COGUID.H>
#undef INITGUID



// Helper for writing information to the debugger.
TCHAR g_szBuffer[2000];
void DebugOut(
    const TCHAR* szFormat, ...
    )
{
    va_list vaMarker;

    va_start(vaMarker, szFormat);
    wvsprintf(g_szBuffer, szFormat, vaMarker);
    va_end(vaMarker);

    #ifdef DEBUG
    OutputDebugString(g_szBuffer);
    #endif
}

// Standard COM class factory for our plugin object
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

// ************************************************************
// Class PluginMem - Implementation of custom Home Screen plugin
//
// Inheritance:
//     IHomePlugin, IPersistStream, IUnknown, IObjectWithSite
//
// Purpose:
//     
//  The PluginMem class implements interfaces which are used to
//	create, configure and operate a custom Home Screen plugin. 
//	This	particular plugin reports current device memory 
//	usage
// ************************************************************

class PluginMem :
    public IHomePlugin,
    public IPersistStream
{
    int m_cRef;
    IHomePluginEnvironment2* m_ppe;
	BSTR m_bstrTitle;
	VARIANT m_varTitle;
	ULONG m_cbStrBytes;
    HPLUGIN m_hPlugin;
	
	

  public:
    PluginMem();
    virtual ~PluginMem();

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

// ************************************************************
//
// Implementation of class PluginFactory
//
// ************************************************************

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
    
    punk = (IUnknown*)(IHomePlugin*) new PluginMem;
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

// ************************************************************
//
// Implementation of standard COM exports
//
// ************************************************************

STDAPI DllGetClassObject(
    REFCLSID rclsid,
    REFIID riid,
    void** ppObject
    )
{
    HRESULT hr = S_OK;
    PluginFactory *pFactory = NULL;
    
    if(rclsid == CLSID_PLUGMEM)
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
        TEXT("CLSID\\{") CLSIDTEXT__PLUGMEM TEXT("}"), 
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
    
    if(GetModuleFileName(hModule, szName, ARRAYSIZE(szName))==0)
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
        TEXT("CLSID\\{") CLSIDTEXT__PLUGMEM TEXT("}\\InprocServer32")))
    {
        hr = E_FAIL;
        goto Error;
    }
    if(ERROR_SUCCESS != RegDeleteKey(HKEY_CLASSES_ROOT, 
        TEXT("CLSID\\{") CLSIDTEXT__PLUGMEM TEXT("}")))
    {
        hr = E_FAIL;
        goto Error;
    }
    
Error:
    return(hr);
}

// ************************************************************
//
// Implementation of class PluginMem
//
// ************************************************************

PluginMem::PluginMem() :
    m_cRef(1),
    m_ppe(NULL),
	m_bstrTitle(NULL),
	m_cbStrBytes(0)
{
    g_dwDLLRefCount++;
}

PluginMem::~PluginMem()
{
    g_dwDLLRefCount--;
	
	if (m_bstrTitle)
    {
		SysFreeString(m_bstrTitle);
    }

	VariantClear(&m_varTitle);
}


HRESULT PluginMem::QueryInterface(
    REFIID riid, void** ppObject
    )
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

// **********************************************************************
// Function Name: SetSite
//
// Description: Implements IObjectWithSite::SetSite method. This is
// called by the system to set a local reference to an 
// IHomePluginEnvironment pointer, which can be used to force a redraw
// of the plugin, or set a one-time timer callback.
//
// See the SDK docs on IHomePluginEnvironment for more information
 
HRESULT PluginMem::SetSite(
    IUnknown* pSite
    )
{
    HRESULT hr = S_OK;
    
    if(m_ppe)
    {
        m_ppe->Release();
        m_ppe = NULL;
    }
    
    if(pSite)
    {
        if(FAILED(hr = pSite->QueryInterface(IID_IHomePluginEnvironment2, (void**)&m_ppe)))
        {
            goto Error;
        }
    }
    
Error:
    return(hr);
}

// **********************************************************************
// Function Name: GetSite
//
// Description: Implementation of IObjectWithSite::GetSite
//
// See SDK documentation for more information

HRESULT PluginMem::GetSite(
    REFIID riid, 
    void** ppvSite
    )
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


// **********************************************************************
// Function Name: Initialize
// 
// Purpose: Called from the Plugin Manager to provide data for the 
//	intermediate config file
//
// Arguments:
//    IN HPLUGIN hPlugin - handle to plugin. Used for calls to 
//		IHomePluginEnvironment.
//	  IN IXMLDOMNode* pnodeParams - XML DOM node representing specific 
//		plugin configuration
//	  IN IXMLDOMNode* pnodeDefault - XML DOM node representing global 
//		plugin configuration (applying to all plugins)
//
// Return Values:
//
//	HRESULT  -  S_OK if parsing operations succeed, E_FAIL otherwise 
//
// Side effects:  
//    Data parsed and stored as member data in this function can only be
//	  used in the Save method below, as the other member functions are
//	  only called in seperate instance of this class (created by home.exe)
//	  instead of the Plugin Manager.
// 
// Description:  
//    This function is called by the Plugin Manager exclusively when the 
//	  plugin is FIRST LOADED from the Home Screen settings menu. 
//    Configuration data should be saved as member data to be written 
//    to an intermediate file via the Save method below
//	 
//	   See the ReadMe notes for more information


HRESULT PluginMem::Initialize(
    HPLUGIN hPlugin, 
    IXMLDOMNode* pnodeParams, 
    IXMLDOMNode* pnodeDefault
    )
{
    HRESULT hr = S_OK;
    BSTR bstrVal = NULL;
    IXMLDOMNode* pFoundNode = NULL;
    IXMLDOMNamedNodeMap * DOMNamedNodeMapPtr = NULL;
    
    DebugOut(TEXT("PluginMem::Initialize called \r\n"));
    
    //Attribute of our XML plugin node to look for
    bstrVal = SysAllocString(L"name");
    if (bstrVal == NULL)
    {
        return E_OUTOFMEMORY;
    }
    if (FAILED(pnodeParams->get_attributes(&DOMNamedNodeMapPtr)))
    {
        return E_FAIL;
    }
    if (FAILED(DOMNamedNodeMapPtr->getNamedItem(bstrVal, &pFoundNode)))
    {
        return E_FAIL;
    }
    
    // store the string so we can write it out when Save is called
    if (FAILED(pFoundNode->get_nodeValue(&m_varTitle)))
    {
        return E_FAIL;
    }
    
    if (m_varTitle.bstrVal != NULL)
    {
        // store the length of the string in bytes
        m_cbStrBytes = SysStringByteLen(m_varTitle.bstrVal)+sizeof(WCHAR);
    }
    
    if (pFoundNode)
        pFoundNode->Release();
    
    if (DOMNamedNodeMapPtr)
        DOMNamedNodeMapPtr->Release();
    
    ::SysFreeString(bstrVal);
    
    m_hPlugin = hPlugin;
    
    return(hr); 
}


// **********************************************************************
// Function Name: GetHeight
// 
// Purpose: Called from the home.exe process to ascertain plugin height.
//		For this sample, we set the plugin height to be hard coded at 40
//		pixels
//
// See SDK documentation for details

HRESULT PluginMem::GetHeight(
    int* pdyPlugin
    )
{

    DebugOut(TEXT("PluginMem::GetHeight called \r\n"));

	// hard-coded height for plugin. This could optionally be set with
	// an XML attribute
    *pdyPlugin = 40;

    return S_OK;
}

// **********************************************************************
// Function Name: GetSelectability
// 
// Purpose: Called from the home.exe process to determine if plugin can
//		be selected. For this sample, we want our plugin to be selectable
//		spo we set the OUT param to TRUE
//
// See SDK documentation for details

HRESULT PluginMem::GetSelectability(BOOL* pfSelectable)
{
    HRESULT hr = S_OK;

    DebugOut(TEXT("PluginMem::GetSelectability called \r\n"));

	*pfSelectable = TRUE;


    return(hr);
}

// **********************************************************************
// Function Name: OnEvent
// 
// Purpose: Called from the home.exe process when a plugin event occurs.
//
// Arguments:
//
//	PluginEvent * ppe - pointer to a Plugin Event struct
// Return Values:
//
//	HRESULT  -  S_OK 
//
// Side effects:  
//    Any member configuration data originating from the XML and used in
//	  this function MUST have been read from the Load method first, as 
//	  the XML parsing in Initialize occured in a different object
//	  instance (and process!)
// 
// Description:  
//    This function behaves like a watered down 'WndProc' callback. The 
//	  system (home.exe) calls this function any time a relevant plugin
//	  event occurs. Of particular interest to us are the events PE_ACTION
//	  (plugin selected and clicked) and PE_PAINT (analogous to WM_PAINT)
//
//	See SDK documentation for more details

HRESULT PluginMem::OnEvent(
    PluginEvent* ppe
    )
{
    HRESULT hr = S_OK;
	MEMORYSTATUS memstat;
	WCHAR wszLoad[3];
	WCHAR wszDetail[128];
	WCHAR wszTmp[16];
	ULONG ulPercent;
	RECT rect;
	HBRUSH hbr;
	COLORREF rgbLeft = RGB(0,255,0);
	
	memstat.dwLength = sizeof(MEMORYSTATUS);

    switch(ppe->idEvent)
    {
    case PE_KEYDOWN:
        DebugOut(TEXT("PluginMem::OnEvent - got event PE_KEYDOWN\r\n"));
        break;
        
        // our plugin has been selected and clicked
    case PE_ACTION:
        
        // Get device memory status
        GlobalMemoryStatus(&memstat);
        
        // build our detailed memory info for display
        wcscpy(wszDetail, L"Total Physical: ");
        _itow(memstat.dwTotalPhys, wszTmp, 10);
        wcscat(wszDetail, wszTmp);
        wcscat(wszDetail, L"\n");
        
        wcscat(wszDetail, L"Avail Physical: ");
        _itow(memstat.dwAvailPhys, wszTmp, 10);
        wcscat(wszDetail, wszTmp);
        wcscat(wszDetail, L"\n\n");
        
        wcscat(wszDetail, L"Total Virtual: ");
        _itow(memstat.dwTotalVirtual, wszTmp, 10);
        wcscat(wszDetail, wszTmp);
        wcscat(wszDetail, L"\n");
        
        
        wcscat(wszDetail, L"Avail Virtual: ");
        _itow(memstat.dwAvailVirtual, wszTmp, 10);
        wcscat(wszDetail, wszTmp);
        wcscat(wszDetail, L"\n");
        
        // show it
        MessageBox(NULL, wszDetail, L"System Memory Info", MB_OK);
        break;
        
        // we've recieved a paint message for our plugin, so we need
        // to update and draw the memory usage status bar
    case PE_PAINT:
        {
            HDC hdc = ppe->p.paint.hdc;
            COLORREF crText, crBackground;
            
            hbr = CreateSolidBrush(rgbLeft);
            
            // update our memory usage data
            GlobalMemoryStatus(&memstat);
            _itow(memstat.dwMemoryLoad, wszLoad, 10);
            
            
            
            ulPercent = memstat.dwMemoryLoad;
            
            //set status bar dimensions
            rect=ppe->p.paint.rcDraw;
            
            rect.left+=5;
            rect.right-=5;
            rect.right=rect.left + ((rect.right - rect.left)*ulPercent)/100;
            rect.top+=20;
            rect.bottom--;
            
            // draw the status bar and our XML-specfied custom title
            FillRect(hdc, &rect, hbr); 
            if (ppe->p.paint.fSelected)
            {
                BSTR bstrText = SysAllocString(TEXT("COLOR_HOMEHIGHLIGHTTEXT"));
                BSTR bstrBackground = SysAllocString(TEXT("COLOR_HOMEHIGHLIGHT"));
                
                m_ppe->GetColor(m_hPlugin, bstrText, &crText);
                SetTextColor(hdc, crText);
                
                m_ppe->GetColor(m_hPlugin, bstrBackground, &crBackground);
                SetBkColor(hdc, crBackground);
                
                SetBkMode(hdc, OPAQUE);
                
                SysFreeString(bstrText);
                SysFreeString(bstrBackground);
            }
            else
            {
                BSTR bstrText = SysAllocString(TEXT("COLOR_HOMETEXT"));
                
                m_ppe->GetColor(m_hPlugin, bstrText, &crText);
                SetTextColor(hdc, crText);
                
                SysFreeString(bstrText);
            }
            DrawText(hdc, m_bstrTitle, -1, const_cast<RECT*>(&(ppe->p.paint.rcDraw)),
                DT_SINGLELINE | DT_CENTER | DT_TOP);
            
            break;
        }
        
    case PE_SYSCOLORCHANGE:
        DebugOut(TEXT("PluginMem::OnEvent - got event PE_SYSCOLORCHANGE\r\n"));
        break;
        
    case PE_TIMER:
        DebugOut(TEXT("PluginMem::OnEvent - got event PE_TIMER\r\n"));
        break;
        
    case PE_DATACHANGE:
        DebugOut(TEXT("PluginMem::OnEvent - got event PE_DATACHANGE\r\n"));
        break;
        
    default:
        break;
        }
        
        return(hr);
}

// **********************************************************************
// Function Name: GetClassID
//
//	Purpose: Implementation of the IPersist::GetClassID method
// 
HRESULT PluginMem::GetClassID(
    CLSID* pClassID
    )
{
    *pClassID = CLSID_PLUGMEM;
    return(S_OK);
}

// **********************************************************************
// Function Name: IsDirty
//
//	Purpose: Trivial implementation of the IPersistStream::IsDirty
//	method. 

HRESULT PluginMem::IsDirty(void)
{
    return(S_OK);
}

// **********************************************************************
// Function Name: Load
// 
// Purpose: Called from the home.exe process to load plugin configuration
//	data from an intermediate file.
//
// Arguments:
//
//	IN IStream * pStm - pointer to the intermediate file's IStream 
//  interface
// 
// Return Values:
//
//	HRESULT  -  S_OK if Read operations succeed, E_FAIL otherwise
//
// Side effects:
//	This function provides a quicker/safer method of loading data than 
//  using the XML DOM every time. It loads the data that was saved by the 
//	Plugin Manager when the plugin was initially loaded.  
//    
// 
// Description:  
// 
//	Implements IPersistStream's Load method, using the intermediate 
//	configuration file's IStream interface pointer to read plugin
//	configuration data. In this sample, the only data we read is for 
//	the custom title, specified in the XML as the plugin's "name"
//  attribute.
//
//	See SDK documentation for more details


HRESULT PluginMem::Load(
    IStream* pStm
    )
{
    
    DebugOut(TEXT("PluginMem::Load - Called\r\n"));
    
    // read the size first
    if (FAILED(pStm->Read(&m_cbStrBytes, sizeof(m_cbStrBytes), 0)))
    {
        return E_FAIL;
    }
    
    // using the size in bytes (less one NULL char), allocate a BSTR
    m_bstrTitle = SysAllocStringByteLen(NULL, m_cbStrBytes-sizeof(WCHAR));
    if (m_bstrTitle == NULL)
    {
        return E_OUTOFMEMORY;
    }
    
    if (FAILED(pStm->Read(m_bstrTitle, m_cbStrBytes, 0)))
    {
        return E_FAIL;
    }
    if (FAILED(pStm->Read(&m_hPlugin, sizeof m_hPlugin, 0)))
    {
        return E_FAIL;
    }
    
    return(S_OK);
}

// **********************************************************************
// Function Name: Save
// 
// Purpose: Called from the Plugin Manager process to save plugin 
//	configuration data to an intermediate file.
//
// Arguments:
//
//	IN IStream * pStm - pointer to the intermediate file's IStream 
//  interface
// 
// Return Values:
//
//	HRESULT  -  S_OK if Write operations succeed, E_FAIL otherwise
//
// Side effects:
//	This function provides a quicker/safer method of persisting data than 
//  using the XML DOM every time. The DOM data that was parsed from 
//	Initialize is saved to an intermediate file here, for quicker loading
//	later.  
//    
// Description:  
//
//	Implements IPersistStream's Save method, using the intermediate file's
//	IStream interface to write plugin configuration data. Since the data
//	being written is stored as a BSTR, we write the size of the string in
//	bytes to the stream first, then the actual string data
//
//	See SDK documentation for more details
HRESULT PluginMem::Save(
    IStream *pStm,
    BOOL fClearDirty
    )
{
    
    DebugOut(TEXT("PluginMem::Save - Called\r\n"));
    
    // true to BSTR form, write the string length (in bytes) first
    if (FAILED(pStm->Write(&m_cbStrBytes, sizeof(m_cbStrBytes), 0)))
    {
        return E_FAIL;
    }
    
    if (FAILED(pStm->Write(m_varTitle.bstrVal, m_cbStrBytes, 0)))
    {
        return E_FAIL;
    }
    if (FAILED(pStm->Write(&m_hPlugin, sizeof m_hPlugin, 0)))
    {
        return E_FAIL;
    }
    
    
    return(S_OK);
}

// **********************************************************************
// Function Name: GetSizeMax
// 
// Purpose: Trivial implementation of IPersistStream's GetSizeMax method

HRESULT PluginMem::GetSizeMax(
    ULARGE_INTEGER* pcbSize
    )
{
    ULONGLONG* pl = (ULONGLONG*)pcbSize;

    *pl = 0;

    return(S_OK);
}


