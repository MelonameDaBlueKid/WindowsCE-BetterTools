// SliderCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sliddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSliderCtrlDlg dialog


CSliderCtrlDlg::CSliderCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSliderCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSliderCtrlDlg)
	//}}AFX_DATA_INIT
}


void CSliderCtrlDlg::DoDataExchange(CDataExchange* pDX)
{

	if(!pDX->m_bSaveAndValidate)
	{
		CComboBox* pOrientation = (CComboBox*)GetDlgItem(IDC_SLIDER_ORIENTATION);
		pOrientation->ResetContent();
		pOrientation->AddString(CString((LPCTSTR)IDS_HORIZONTAL));
		pOrientation->AddString(CString((LPCTSTR)IDS_VERTICAL));

		CComboBox* pPoint = (CComboBox*)GetDlgItem(IDC_SLIDER_POINT);
		pPoint->ResetContent();
		pPoint->AddString(CString((LPCTSTR)IDS_BOTH));
		pPoint->AddString(CString((LPCTSTR)IDS_TOPLEFT));
		pPoint->AddString(CString((LPCTSTR)IDS_BOTTOMRIGHT));
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSliderCtrlDlg)
	DDX_Check(pDX, IDC_SLIDER_AUTOTICKS, m_bAutoticks);
	DDX_Check(pDX, IDC_SLIDER_ENABLESEL, m_bEnablesel);
	//DDX_Check(pDX, IDC_SLIDER_FIXED, m_bFixed);
	DDX_Check(pDX, IDC_SLIDER_NOTHUMB, m_bNothumb);
	DDX_Check(pDX, IDC_SLIDER_NOTICKS, m_bNoticks);
	DDX_CBIndex(pDX, IDC_SLIDER_ORIENTATION, m_iOrientation);
	DDX_CBIndex(pDX, IDC_SLIDER_POINT, m_iTickpos);
	//}}AFX_DATA_MAP
}

BOOL CSliderCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CSliderCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CSliderCtrlDlg)
	ON_COMMAND(IDOK, OnOK)
	ON_BN_CLICKED(IDC_SLIDER_AUTOTICKS, OnControlChange)
	ON_BN_CLICKED(IDC_SLIDER_ENABLESEL, OnControlChange)
	ON_BN_CLICKED(IDC_SLIDER_FIXED, OnControlChange)
	ON_BN_CLICKED(IDC_SLIDER_NOTHUMB, OnControlChange)
	ON_BN_CLICKED(IDC_SLIDER_NOTICKS, OnControlChange)
	ON_CBN_SELCHANGE(IDC_SLIDER_ORIENTATION, OnControlChange)
	ON_CBN_SELCHANGE(IDC_SLIDER_POINT, OnControlChange)		
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliderCtrlDlg message handlers

void CSliderCtrlDlg::OnControlChange() 
{
	UpdateData();
}

void CSliderCtrlDlg::OnOK()
{
	UpdateData();
	CDialog::OnOK();
}
