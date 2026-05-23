// PolyProp.h : Declaration of the CPolyProp

#include "resource.h"       // main symbols
#include "Polygon.h"

EXTERN_C const CLSID CLSID_PolyProp;

/////////////////////////////////////////////////////////////////////////////
// CPolyProp
class CPolyProp :
	public CComObjectRoot,
	public CComCoClass<CPolyProp, &CLSID_PolyProp>,
	public IPropertyPageImpl<CPolyProp>,
	public CDialogImpl<CPolyProp>
{
public:
	CPolyProp() 
	{
		m_dwTitleID = IDS_TITLEPolyProp;
		m_dwHelpFileID = IDS_HELPFILEPolyProp;
		m_dwDocStringID = IDS_DOCSTRINGPolyProp;
	}

	enum {IDD = IDD_PolyProp};

DECLARE_REGISTRY_RESOURCEID(IDR_PolyProp)

BEGIN_COM_MAP(CPolyProp) 
	COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CPolyProp)
	COMMAND_HANDLER(IDC_SIDES, EN_CHANGE, OnSidesChange)
	CHAIN_MSG_MAP(IPropertyPageImpl<CPolyProp>)
END_MSG_MAP()

	STDMETHOD(Apply)(void)
	{
		USES_CONVERSION;
		ATLTRACE(_T("CPolyProp::Apply\n"));
		for (UINT i = 0; i < m_nObjects; i++)
		{
			CComQIPtr<IPolyCtl, &IID_IPolyCtl> pPoly(m_ppUnk[i]);
			short nSides = (short)GetDlgItemInt(IDC_SIDES);
			if FAILED(pPoly->put_Sides(nSides))
			{
				return E_FAIL;
			}
		}
		m_bDirty = FALSE;
		return S_OK;
	}
	LRESULT OnSidesChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
	{
		SetDirty(TRUE);
		return 0;
	}
};
