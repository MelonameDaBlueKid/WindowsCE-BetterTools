#ifndef __AXSAMPLECTL_H__
#define __AXSAMPLECTL_H__

#include "resource.h"

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

#endif //__AXSAMPLECTL_H__

