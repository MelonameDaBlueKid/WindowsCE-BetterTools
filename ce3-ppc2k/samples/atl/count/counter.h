// Counter.h : Declaration of the CCounter

#ifndef __COUNTER_H_
#define __COUNTER_H_

#include "resource.h"       // main symbols
#include "Object1.h"

/////////////////////////////////////////////////////////////////////////////
// CCounter
class ATL_NO_VTABLE CCounter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCounter, &CLSID_Counter>,
	public CComControl<CCounter>,
	public IDispatchImpl<ICounter, &IID_ICounter, &LIBID_COUNTLib>,
	public IProvideClassInfo2Impl<&CLSID_Counter, NULL, &LIBID_COUNTLib>,
	public IPersistStreamInitImpl<CCounter>,
	public IPersistStorageImpl<CCounter>,
	public IQuickActivateImpl<CCounter>,
	public IOleControlImpl<CCounter>,
	public IOleObjectImpl<CCounter>,
	public IOleInPlaceActiveObjectImpl<CCounter>,
	public IViewObjectExImpl<CCounter>,
	public IOleInPlaceObjectWindowlessImpl<CCounter>,
	public IDataObjectImpl<CCounter>,
	public ISpecifyPropertyPagesImpl<CCounter>
{
protected:
	IObject1*	m_pIObject;	// pointer to IObject1 interface

public:
	CCounter()
	{
		// Instantiate CSimple1 object
		CComObject<CObject1>* m_pObject = new CComObject<CObject1>;
		// Get ISimple1 interface
		if(m_pObject)
			m_pObject->QueryInterface(IID_IObject1, (void**)&m_pIObject);

		// Call Initialize() method of the IObject1 interface and pass ICounter interface to the CObject1 object
		// Now both objects know the each other's interfaces
		m_pIObject->Initialize((DWORD)(ICounter*)this);
	}


DECLARE_REGISTRY_RESOURCEID(IDR_COUNTER)

BEGIN_COM_MAP(CCounter)
	COM_INTERFACE_ENTRY(ICounter)
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
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CCounter)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
#ifndef UNDER_CE
	PROP_PAGE(CLSID_StockColorPage)
#endif
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CCounter)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()


// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// ICounter
public:
	STDMETHOD(GetInfoFromCounter)(BSTR pInfo);
	STDMETHOD(SetMaxCounter)(int nMax);
	STDMETHOD(StartCounting)();
	HRESULT OnDraw(ATL_DRAWINFO& di);

};

#endif //__COUNTER_H_
