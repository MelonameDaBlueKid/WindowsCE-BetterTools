// SketcCtl.h : Declaration of the CSketcCtl

#ifndef __SKETCCTL_H_
#define __SKETCCTL_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CSketcCtl
class ATL_NO_VTABLE CSketcCtl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSketcCtl, &CLSID_SketcCtl>,
	public CComControl<CSketcCtl>,
	public CStockPropImpl<CSketcCtl, ISketcCtl, &IID_ISketcCtl, &LIBID_SKETCHLib>,
	public IProvideClassInfo2Impl<&CLSID_SketcCtl, NULL, &LIBID_SKETCHLib>,
	public IPersistStreamInitImpl<CSketcCtl>,
	public IPersistStorageImpl<CSketcCtl>,
	public IQuickActivateImpl<CSketcCtl>,
	public IOleControlImpl<CSketcCtl>,
	public IOleObjectImpl<CSketcCtl>,
	public IPersistPropertyBagImpl<CSketcCtl>,
	public IOleInPlaceActiveObjectImpl<CSketcCtl>,
	public IViewObjectExImpl<CSketcCtl>,
	public IOleInPlaceObjectWindowlessImpl<CSketcCtl>,
	public IDataObjectImpl<CSketcCtl>,
	public ISupportErrorInfo,
	public ISpecifyPropertyPagesImpl<CSketcCtl>
{
public:
	CSketcCtl()
	{
		bLBDown = FALSE; 
		m_PenWidth = 1;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SKETCCTL)

BEGIN_COM_MAP(CSketcCtl)
	COM_INTERFACE_ENTRY(ISketcCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CSketcCtl)
	PROP_ENTRY("PenWidth", 1, CLSID_SketcCtl)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CSketcCtl)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	//MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnRButtonDown)
END_MSG_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// ISketcCtl
public:
	STDMETHOD(Erase)();
	STDMETHOD(get_PenWidth)(short *pval);
	STDMETHOD(put_PenWidth)(short newVal);
	HRESULT OnDraw(ATL_DRAWINFO& di);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam,
								BOOL& bHandled); 
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam,
				                  BOOL& bHandled); 
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam,
				                  BOOL& bHandled); 

	BOOL bLBDown;
	POINT line[2];
	int left, right, top, bottom;
	short m_PenWidth;
};

#endif //__SKETCCTL_H_
