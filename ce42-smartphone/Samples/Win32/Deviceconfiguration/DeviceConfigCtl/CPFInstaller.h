// CPFInstaller.h : Declaration of the CCPFInstaller
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "DeviceConfigCtl.h"
#include "_ICPFInstallerEvents_CP.h"


#define MAX_PROFILE_ENTRY_LEN	100

typedef struct tagPROFILEENTRY
{
	TCHAR szProfileName[MAX_PROFILE_ENTRY_LEN];
	TCHAR szDeviceType[MAX_PROFILE_ENTRY_LEN];
} PROFILEENTRY;

// Check HRESULT
#define CHR(hResult)\
	do {hr = (hResult); if(FAILED(hr))goto Error;} while (0,0)

// Check pointer result
#define CPR(p)\
    do {if(!(0,(p))) {hr = E_OUTOFMEMORY; goto Error;} } while (0,0)

// Check boolean result
#define CBR(fResult)\
    do {if (!(0,(fResult))) {hr = E_FAIL; goto Error;}} while(0,0);

// Check Windows result
#define CWR(fResult)\
    do {if (!(0,(fResult))) {hr = HRESULT_FROM_WIN32(GetLastError()); goto Error;}} while(0,0);

const TCHAR c_szDeviceFileName[] = _T("\\DevConfig.cpf");
const TCHAR c_szPPCInstaller[] = _T("\\Windows\\wceloadsp.exe");
const TCHAR c_szSPInstaller[] = _T("\\Windows\\wceload.exe");
const TCHAR c_szDeviceTypePPC[] = _T("PocketPC");
const TCHAR c_szDeviceTypeSP[] = _T("SmartPhone");


// CCPFInstaller
class ATL_NO_VTABLE CCPFInstaller : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICPFInstaller, &IID_ICPFInstaller, &LIBID_DeviceConfigCtlLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CCPFInstaller>,
	public IOleControlImpl<CCPFInstaller>,
	public IOleObjectImpl<CCPFInstaller>,
	public IOleInPlaceActiveObjectImpl<CCPFInstaller>,
	public IViewObjectExImpl<CCPFInstaller>,
	public IOleInPlaceObjectWindowlessImpl<CCPFInstaller>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CCPFInstaller>,
	public CProxy_ICPFInstallerEvents<CCPFInstaller>, 
	public IPersistStorageImpl<CCPFInstaller>,
	public ISpecifyPropertyPagesImpl<CCPFInstaller>,
	public IQuickActivateImpl<CCPFInstaller>,
	public IDataObjectImpl<CCPFInstaller>,
	public IProvideClassInfo2Impl<&CLSID_CPFInstaller, &__uuidof(_ICPFInstallerEvents), &LIBID_DeviceConfigCtlLib>,
	public CComCoClass<CCPFInstaller, &CLSID_CPFInstaller>,
	public CComControl<CCPFInstaller>
{
public:

	CCPFInstaller():m_dwNumProfiles(0),
				m_fProfileInitd(FALSE),
				m_pProfiles(NULL)
	{
	}

	~CCPFInstaller()
	{
		delete [] m_pProfiles;
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_CPFINSTALLER)

BEGIN_COM_MAP(CCPFInstaller)
	COM_INTERFACE_ENTRY(ICPFInstaller)
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
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CCPFInstaller)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CCPFInstaller)
	CONNECTION_POINT_ENTRY(__uuidof(_ICPFInstallerEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CCPFInstaller)
	CHAIN_MSG_MAP(CComControl<CCPFInstaller>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_ICPFInstaller,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ICPFInstaller
public:
		HRESULT OnDraw(ATL_DRAWINFO& di)
		{
		RECT& rc = *(RECT*)di.prcBounds;
		// Set Clip region to the rectangle specified by di.prcBounds
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != NULL)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 7.0 : CPFInstaller");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		return S_OK;
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}
	STDMETHOD(InitProfiles)(LONG* dwProfileCount);
	STDMETHOD(GetProfileString)(LONG dwProfileIndex, BSTR bstrValueName, BSTR* pbstrProfileValue);
	STDMETHOD(GetCurrentDeviceName)(BSTR* pbstrDeviceName);
	STDMETHOD(IsDeviceConnected)(VARIANT_BOOL* pfDeviceConnected);
	STDMETHOD(InstallToDevice)(BSTR bstrServerCPFLocation, BSTR bstrDeviceName, VARIANT_BOOL* pfSuccess);
	STDMETHOD(InstallToCurrentDevice)(BSTR bstrServerCPFLocation, VARIANT_BOOL* pfSuccess);

protected:
	DWORD			m_dwNumProfiles;
	BOOL			m_fProfileInitd;
	PROFILEENTRY*	m_pProfiles;
public:
	HRESULT CopyFileServerToDevice(BSTR bstrServerFileName, BSTR bstrDeviceFileName);
	HRESULT CopyFileServerToDesktop(LPTSTR szServerFileName, LPTSTR szDesktopFileName);
	HRESULT GetCurrentDeviceID(DWORD * pdwCurrDeviceID);
	HRESULT GetCurrentDeviceType(BSTR * bstrCurrDeviceType);
	HRESULT GetCurrentDeviceString(LPCTSTR pszValueName, BSTR * pbstrProfileValue);
	static HRESULT CreateTempFolder(LPTSTR szFolderName);

};

OBJECT_ENTRY_AUTO(__uuidof(CPFInstaller), CCPFInstaller)
