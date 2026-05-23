// ListCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg dialog


CListCtrlDlg::CListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListCtrlDlg)
	//}}AFX_DATA_INIT
}


void CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	if(!pDX->m_bSaveAndValidate)
	{
		CComboBox* pViewMode = (CComboBox*)GetDlgItem(IDC_VIEWMODE);
		pViewMode->ResetContent();
		pViewMode->AddString(CString((LPCTSTR)IDS_SMALLICON));
		pViewMode->AddString(CString((LPCTSTR)IDS_ICON));
		pViewMode->AddString(CString((LPCTSTR)IDS_LIST));
		pViewMode->AddString(CString((LPCTSTR)IDS_REPORT));

		CComboBox* pSort = (CComboBox*)GetDlgItem(IDC_SORT);
		pSort->ResetContent();
		pSort->AddString(CString((LPCTSTR)IDS_NONE));
		pSort->AddString(CString((LPCTSTR)IDS_ASCENDING));
		pSort->AddString(CString((LPCTSTR)IDS_DESCENDING));

		CComboBox* pAlign = (CComboBox*)GetDlgItem(IDC_ALIGN);
		pAlign->ResetContent();
		pAlign->AddString(CString((LPCTSTR)IDS_TOP));
		pAlign->AddString(CString((LPCTSTR)IDS_LEFT));
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlDlg)
	DDX_Check(pDX, IDC_SINGLESEL, m_bSingleSel);
	DDX_Check(pDX, IDC_EDITLABELS, m_bEditLabels);
	DDX_Check(pDX, IDC_NOLABELWRAP, m_bNoLabelWrap);
	DDX_Check(pDX, IDC_NOCOLUMNHEADER, m_bNoColumnHeader);
	DDX_Check(pDX, IDC_NOSORTHEADER, m_bNoSortHeader);
	DDX_CBString(pDX, IDC_VIEWMODE, m_cstrViewMode);
	DDX_CBString(pDX, IDC_SORT, m_cstrSort);
	DDX_CBString(pDX, IDC_ALIGN, m_cstrAlignMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CListCtrlDlg)
	ON_BN_CLICKED(IDC_SINGLESEL, OnControlChange)
	ON_BN_CLICKED(IDC_EDITLABELS, OnControlChange)
	ON_BN_CLICKED(IDC_NOLABELWRAP, OnControlChange)
	ON_BN_CLICKED(IDC_NOCOLUMNHEADER, OnControlChange)
	ON_BN_CLICKED(IDC_NOSORTHEADER, OnControlChange)
	ON_CBN_SELCHANGE(IDC_VIEWMODE, OnControlChange)
	ON_CBN_SELCHANGE(IDC_SORT, OnControlChange)
	ON_CBN_SELCHANGE(IDC_ALIGN, OnControlChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg message handlers

BOOL CListCtrlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	OnControlChange();
	return TRUE; 
}



void CListCtrlDlg::OnControlChange()
{
	// Fill the values into the combo boxes
	LONG lStyle;
	BOOL bReport, bIconic;
	
	UpdateData();
	if (m_cstrViewMode == CString((LPCTSTR)IDS_ICON))
		lStyle = LVS_ICON;
	else if (m_cstrViewMode == CString((LPCTSTR)IDS_SMALLICON))
		lStyle = LVS_SMALLICON;
	else if (m_cstrViewMode == CString((LPCTSTR)IDS_REPORT))
		lStyle = LVS_REPORT;
	else
	{
		ASSERT(m_cstrViewMode == CString((LPCTSTR)IDS_LIST));
		lStyle = LVS_LIST;
	}

	bReport = (lStyle == LVS_REPORT);
	bIconic = (lStyle == LVS_ICON || lStyle == LVS_SMALLICON);
	
	GetDlgItem(IDC_SINGLESEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDITLABELS)->EnableWindow(TRUE);
	GetDlgItem(IDC_NOLABELWRAP)->EnableWindow(lStyle == LVS_ICON);
	GetDlgItem(IDC_NOCOLUMNHEADER)->EnableWindow(bReport);
	GetDlgItem(IDC_NOSORTHEADER)->EnableWindow(bReport);
	GetDlgItem(IDC_VIEWMODE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_ALIGN)->EnableWindow(bIconic);
}

