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
#ifndef __AXSAMPLECTL_H__
#define __AXSAMPLECTL_H__

#include "resource.h"

#ifdef _CE_DCOM
#pragma message ( "The threading model for this object has been set to 'Free' in the .rgs file. Because you are compiling against an SDK which supports DCOM, you may wish to change this." )
#endif

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

/////////////////////////////////////////////////////////////////////////////
// CAXSampleCtl
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE CAXSampleCtl : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CAXSampleCtl, &CLSID_AXSampleCtl>,

    public IDispatchImpl<IAXSampleCtl, &IID_IAXSampleCtl, &LIBID_AXSAMPLELib>,
    public IProvideClassInfoImpl<&CLSID_AXSampleCtl, &LIBID_AXSAMPLELib>,

    public CComControl<CAXSampleCtl>,
    public IOleControlImpl<CAXSampleCtl>,
    public IOleObjectImpl<CAXSampleCtl>,
    public IViewObjectExImpl<CAXSampleCtl>,
    public IOleInPlaceActiveObjectImpl<CAXSampleCtl>,
    public IOleInPlaceObjectWindowlessImpl<CAXSampleCtl>,

    public IPersistPropertyBagImpl<CAXSampleCtl>,

    public IObjectSafetyImpl<CAXSampleCtl, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
// Construction/Destruction
public:
	CAXSampleCtl();

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

    DECLARE_REGISTRY_RESOURCEID(IDR_AXSAMPLECTL)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    static LPCTSTR GetWindowClassName()
    { return TEXT("CAXSampleCtl"); }

// Data
public:
    COLORREF m_crFillColor;

    BEGIN_PROP_MAP(CAXSampleCtl)
        PROP_ENTRY("FillColor", DISPID_FILLCOLOR, CLSID_NULL)
    END_PROP_MAP()

// Messages
public:
    BEGIN_MSG_MAP(CAXSampleCtl)
        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        CHAIN_MSG_MAP(CComControl<CAXSampleCtl>)
    END_MSG_MAP()

    LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);

// Methods
protected:
    HRESULT OnDraw(ATL_DRAWINFO& di);
    BOOL    PtInCircle(POINT & pt, INT iLeft, INT iTop, INT iRight, INT iBottom);

// Interfaces
public:
    BEGIN_COM_MAP(CAXSampleCtl)
	    COM_INTERFACE_ENTRY(IAXSampleCtl)

	    COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IProvideClassInfo)

        COM_INTERFACE_ENTRY_IMPL(IOleControl)
        COM_INTERFACE_ENTRY_IMPL(IOleObject)
        COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceActiveObject)
        COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
        COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)

        COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IPersist, IPersistPropertyBag)

        COM_INTERFACE_ENTRY(IObjectSafety)
    END_COM_MAP()

    // IAXSampleCtl
    STDMETHOD(put_FillColor)(COLORREF crFill);
    STDMETHOD(get_FillColor)(COLORREF * pcrFill);
};

OBJECT_ENTRY_AUTO(__uuidof(AXSampleCtl), CAXSampleCtl)
#endif //__AXSAMPLECTL_H__

