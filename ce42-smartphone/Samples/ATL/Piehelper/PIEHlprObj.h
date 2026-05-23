// IEHlprObj.h : Declaration of the CIEHlprObj

#ifndef __IEHLPROBJ_H_
#define __IEHLPROBJ_H_

#include "resource.h"       // main symbols
#include "EventsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CIEHlprObj
class ATL_NO_VTABLE CIEHlprObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIEHlprObj, &CLSID_IEHlprObj>,
	public IObjectWithSiteImpl<CIEHlprObj>,
	public IDispatchImpl<IIEHlprObj, &IID_IIEHlprObj, &LIBID_IEHELPERLib>
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_IEHLPROBJ)
   DECLARE_NOT_AGGREGATABLE(CIEHlprObj)

   BEGIN_COM_MAP(CIEHlprObj)
	   COM_INTERFACE_ENTRY(IIEHlprObj)
	   COM_INTERFACE_ENTRY(IDispatch)
   	COM_INTERFACE_ENTRY_IMPL(IObjectWithSite)
   END_COM_MAP()

// IIEHlprObj
public:
    // IDispatch
    STDMETHOD(Invoke)(DISPID dispidMember,REFIID riid, LCID lcid, WORD wFlags,
                      DISPPARAMS * pdispparams, VARIANT * pvarResult,
                      EXCEPINFO * pexcepinfo, UINT * puArgErr);

    // IOleObjectWithSite
    STDMETHOD(SetSite)(IUnknown *pUnkSite);

private:
   CEventsDlg m_dlgEvents;

   DWORD m_dwCookie;   // Connection Token - used for Advise and Unadvise
   CComQIPtr<IBrowser2, &__uuidof(IBrowser2)> m_spBrowser2;

   enum ConnectType { Advise, Unadvise };   // What to do when managing the connection

   BOOL ManageConnection(enum ConnectType eConnectType);
};

#endif //__IEHLPROBJ_H_
