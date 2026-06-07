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
// IEHlprObj.h : Declaration of the CIEHlprObj

#ifndef __IEHLPROBJ_H_
#define __IEHLPROBJ_H_

#include "resource.h"       // main symbols
#include "EventsDlg.h"

#ifdef _CE_DCOM
#pragma message ( "The threading model for this object has been set to 'Free' in the .rgs file. Because you are compiling against an SDK which supports DCOM, you may wish to change this." )
#endif

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

const UINT ID_BROWSER = 1;

/////////////////////////////////////////////////////////////////////////////
// CIEHlprObj
class ATL_NO_VTABLE CIEHlprObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIEHlprObj, &CLSID_IEHlprObj>,
	public IObjectWithSiteImpl<CIEHlprObj>,
	public IDispEventSimpleImpl<ID_BROWSER, CIEHlprObj, &DIID_DWebBrowserEvents2>,
	public IIEHlprObj
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_IEHLPROBJ)
   DECLARE_NOT_AGGREGATABLE(CIEHlprObj)

   BEGIN_COM_MAP(CIEHlprObj)
	   COM_INTERFACE_ENTRY(IIEHlprObj)
   	COM_INTERFACE_ENTRY_IMPL(IObjectWithSite)
   END_COM_MAP()

// IIEHlprObj
public:
    // IOleObjectWithSite
    STDMETHOD(SetSite)(IUnknown *pUnkSite);

// Events
public:
    BEGIN_SINK_MAP(CIEHlprObj)
        SINK_ENTRY_INFO(ID_BROWSER, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete, &OnDocumentCompleteInfo)
        SINK_ENTRY_INFO(ID_BROWSER, DIID_DWebBrowserEvents2, DISPID_TITLECHANGE, OnTitleChange, &OnTitleChangeInfo)
        SINK_ENTRY_INFO(ID_BROWSER, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, OnBeforeNavigate2, &OnBeforeNavigate2Info)
        SINK_ENTRY_INFO(ID_BROWSER, DIID_DWebBrowserEvents2, DISPID_NAVIGATECOMPLETE2, OnNavigateComplete2, &OnNavigateComplete2Info)
    END_SINK_MAP()

private:
    static _ATL_FUNC_INFO OnDocumentCompleteInfo;
    static _ATL_FUNC_INFO OnTitleChangeInfo;
    static _ATL_FUNC_INFO OnBeforeNavigate2Info;
    static _ATL_FUNC_INFO OnNavigateComplete2Info;

    void __stdcall OnDocumentComplete(IDispatch * pDisp, VARIANT * pvtURL);
    void __stdcall OnTitleChange(BSTR bstrTitleText);
    void __stdcall OnBeforeNavigate2(IDispatch* pDisp,
                                     VARIANT * URL, 
                                     VARIANT * pvtFlags, 
                                     VARIANT * pvtTargetFrameName, 
                                     VARIANT * pvtPostData, 
                                     VARIANT * pvtHeaders,
                                     VARIANT_BOOL * pvbCancel);
    void __stdcall OnNavigateComplete2(IDispatch * pDisp, VARIANT * pvtURL);

private:
   CEventsDlg m_dlgEvents;

   CComQIPtr<IWebBrowser2, &__uuidof(IWebBrowser2)> m_spWebBrowser2;
};

OBJECT_ENTRY_AUTO(__uuidof(IEHlprObj), CIEHlprObj)
#endif //__IEHLPROBJ_H_
