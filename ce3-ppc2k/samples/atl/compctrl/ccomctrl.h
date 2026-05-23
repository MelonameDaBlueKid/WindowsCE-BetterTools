// CComCtrl.h : Declaration of the CComCtrl

#ifndef __CCOMCTRL_H_
#define __CCOMCTRL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
//#import "Polygon.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids 
#include "Polygon.tlh"

/////////////////////////////////////////////////////////////////////////////
// CCComCtrl
class ATL_NO_VTABLE CComCtrl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CComCtrl, ICComCtrl, &IID_ICComCtrl, &LIBID_COMPCTRLLib>,
	public CComCompositeControl<CComCtrl>,
	public IPersistStreamInitImpl<CComCtrl>,
	public IOleControlImpl<CComCtrl>,
	public IOleObjectImpl<CComCtrl>,
	public IOleInPlaceActiveObjectImpl<CComCtrl>,
	public IViewObjectExImpl<CComCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CComCtrl>,
	public IPersistStorageImpl<CComCtrl>,
	public ISpecifyPropertyPagesImpl<CComCtrl>,
	public IQuickActivateImpl<CComCtrl>,
	public IDataObjectImpl<CComCtrl>,
	public IProvideClassInfo2Impl<&CLSID_CComCtrl, /*&DIID__CompEvents*/NULL, &LIBID_COMPCTRLLib>,
	public CComCoClass<CComCtrl, &CLSID_CComCtrl>,
	public IDispEventImpl<IDC_POLYCTL1, CComCtrl>,
	public IDispEventImpl<IDC_SMILECTRL1, CComCtrl>
{
public:
	CComCtrl()
	{
		m_bWindowOnly = TRUE;
		CalcExtent(m_sizeExtent);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CCOMCTRL)

BEGIN_COM_MAP(CComCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CComCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CComCtrl)
	COMMAND_HANDLER(IDC_WINK, BN_CLICKED, OnClickedWink)
	COMMAND_HANDLER(IDC_SMILE, BN_CLICKED, OnClickedSmile)
	COMMAND_HANDLER(IDC_SAD, BN_CLICKED, OnClickedSad)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDC_DECREMENT, BN_CLICKED, OnClickedDecrement)
	COMMAND_HANDLER(IDC_INCREMENT, BN_CLICKED, OnClickedIncrement)
	CHAIN_MSG_MAP(CComCompositeControl<CComCtrl>)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);


// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// ICComCtrl
public:
	int UpdateNumberOfSides(DWORD, int, long);
	void UpdateSmileState();
	void DecrementSides();
	void IncrementSides();

	enum { IDD = IDD_COMPCTRL };

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UpdateNumberOfSides(0,0,0);
		UpdateSmileState();

		return 0;
	}

	// Buttons clicked:
	LRESULT OnClickedIncrement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		IncrementSides();
		return 0;
	}
	LRESULT OnClickedDecrement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		DecrementSides();
		return 0;
	}

//Sink map is used to set up event handling
BEGIN_SINK_MAP(CComCtrl)
	SINK_ENTRY(IDC_SMILECTRL1, 0x1, OnOutsideSmilectrl1)
	SINK_ENTRY(IDC_SMILECTRL1, 0x2, OnInsideSmilectrl1)
	SINK_ENTRY(IDC_POLYCTL1, 0x1, OnClickInPolyctl1)
	SINK_ENTRY(IDC_POLYCTL1, 0x2, OnClickOutPolyctl1)
END_SINK_MAP()


	// Events from Polygon Control
	void __stdcall OnClickInPolyctl1(LONG x, LONG y)
	{
		IncrementSides();
	}
	void __stdcall OnClickOutPolyctl1(LONG x, LONG y)
	{
		DecrementSides();
	}
	// Events from Smile Control
	void __stdcall OnInsideSmilectrl1(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
	{
		TCHAR szBuf1[60] = _T("");
		int nResult = LoadString (_Module.m_hInst, IDS_SIMPLE, szBuf1, sizeof(szBuf1) );
		MessageBox(szBuf1);
	}
	void __stdcall OnOutsideSmilectrl1()
	{
		TCHAR szBuf1[60] = _T("");
		int nResult = LoadString (_Module.m_hInst, IDS_OUTSIDE, szBuf1, sizeof(szBuf1) );
		MessageBox(szBuf1);
	}

	// Buttons clicked:
	LRESULT OnClickedSad(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		IDispatch* pISmiley;
		HRESULT hr = GetDlgControl(IDC_SMILECTRL1, IID_IDispatch, (void**)&pISmiley );
		if(SUCCEEDED(hr))
		{
			DISPID		dispidNamed = DISPID_PROPERTYPUT;
			DISPPARAMS	dispparams;
			VARIANT		pArg;

			pArg.vt = VT_BOOL;
			pArg.boolVal = TRUE; // Sad

			dispparams.cArgs = 1;
			dispparams.cNamedArgs = 1;
			dispparams.rgdispidNamedArgs = &dispidNamed;
			dispparams.rgvarg = &pArg;
			
			pISmiley->Invoke(1, IID_NULL, 0, DISPATCH_PROPERTYPUT, &dispparams, NULL, NULL, NULL);
		}
		return 0;
	}
	LRESULT OnClickedSmile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		IDispatch* pISmiley;
		HRESULT hr = GetDlgControl(IDC_SMILECTRL1, IID_IDispatch, (void**)&pISmiley );
		if(SUCCEEDED(hr))
		{
			DISPID		dispidNamed = DISPID_PROPERTYPUT;
			DISPPARAMS	dispparams;
			VARIANT		pArg;

			pArg.vt = VT_BOOL;
			pArg.boolVal = FALSE; // NOT Sad

			dispparams.cArgs = 1;
			dispparams.cNamedArgs = 1;
			dispparams.rgdispidNamedArgs = &dispidNamed;
			dispparams.rgvarg = &pArg;
			
			pISmiley->Invoke(1, IID_NULL, 0, DISPATCH_PROPERTYPUT, &dispparams, NULL, NULL, NULL);
		}
		return 0;
	}
	LRESULT OnClickedWink(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		static BOOL bWink = TRUE;

		IDispatch* pISmiley;
		HRESULT hr = GetDlgControl(IDC_SMILECTRL1, IID_IDispatch, (void**)&pISmiley );
		if(SUCCEEDED(hr))
		{
			DISPPARAMS	dispparams;
			VARIANT		pArg = {VT_I4, 0};

			pArg.lVal = bWink ? 1 : 0;
			bWink = !bWink;

			memset(&dispparams, 0, sizeof dispparams);
			dispparams.cArgs = 1;
			dispparams.rgvarg = &pArg;
			
			pISmiley->Invoke(3, IID_NULL, 0, DISPATCH_METHOD, &dispparams, NULL, NULL, NULL);
		}
		return 0;
	}

	
};

#endif //__CCOMCTRL_H_
