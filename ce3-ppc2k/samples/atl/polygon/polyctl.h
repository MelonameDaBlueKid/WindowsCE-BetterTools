// PolyCtl.h : Declaration of the CPolyCtl

#include <math.h>
#include "resource.h"       // main symbols
#include "CPPolygn.h"

/////////////////////////////////////////////////////////////////////////////
// CPolyCtl
class CPolyCtl : 
	public CComObjectRoot,
	public CComCoClass<CPolyCtl, &CLSID_PolyCtl>,
	public CComControl<CPolyCtl>,
	public CStockPropImpl<CPolyCtl, IPolyCtl, &IID_IPolyCtl, &LIBID_POLYGONLib>,
	public IProvideClassInfo2Impl<&CLSID_PolyCtl, &DIID__PolyEvents, &LIBID_POLYGONLib>,
	public IPersistStreamInitImpl<CPolyCtl>,
	public IPersistStorageImpl<CPolyCtl>,
	public IQuickActivateImpl<CPolyCtl>,
	public IOleControlImpl<CPolyCtl>,
	public IOleObjectImpl<CPolyCtl>,
	public IPersistPropertyBagImpl<CPolyCtl>,
	public IOleInPlaceActiveObjectImpl<CPolyCtl>,
	public IViewObjectExImpl<CPolyCtl>,
	public IOleInPlaceObjectWindowlessImpl<CPolyCtl>,
	public IDataObjectImpl<CPolyCtl>,
	public ISupportErrorInfo,
	public ISpecifyPropertyPagesImpl<CPolyCtl>,
	public CProxy_PolyEvents<CPolyCtl>,
	public IConnectionPointContainerImpl<CPolyCtl>
{
public:
	CPolyCtl()
	{
		m_nSides = 3;
		m_clrFillColor = RGB(0, 0xFF, 0);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PolyCtl)

DECLARE_POLY_AGGREGATABLE(CPolyCtl)

BEGIN_COM_MAP(CPolyCtl)
	COM_INTERFACE_ENTRY(IPolyCtl)
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
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPolyCtl)
	CONNECTION_POINT_ENTRY(DIID__PolyEvents)
END_CONNECTION_POINT_MAP()

BEGIN_PROPERTY_MAP(CPolyCtl)
	PROP_ENTRY("Sides", 1, CLSID_PolyProp)
	PROP_ENTRY("FillColor", DISPID_FILLCOLOR, CLSID_PolyCtl)
END_PROPERTY_MAP()

BEGIN_MSG_MAP(CPolyCtl)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
END_MSG_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IPolyCtl
public:
	STDMETHOD(get_Sides)(/*[out, retval]*/ short *newVal);
	STDMETHOD(put_Sides)(/*[in]*/ short newVal);
	HRESULT OnDraw(ATL_DRAWINFO& di);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	OLE_COLOR m_clrFillColor;
	short     m_nSides;
	POINT     m_arrPoint[100];
};
