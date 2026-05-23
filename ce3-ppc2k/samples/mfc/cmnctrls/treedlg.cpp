// TreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TreeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDlg dialog


CTreeCtrlDlg::CTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeCtrlDlg)
	DDX_Check(pDX, IDC_TVEDITLABELS, m_bEditLabels);
	DDX_Check(pDX, IDC_TVHASBUTTONS, m_bHasButtons);
	DDX_Check(pDX, IDC_TVHASLINES, m_bHasLines);
	DDX_Check(pDX, IDC_TVLINESATROOT, m_bLinesAtRoot);
	//DDX_Check(pDX, IDC_TVDISABLEDDRAGDROP, m_bDisableDragDrop);
	DDX_Check(pDX, IDC_TVSHOWSELALWAYS, m_bShowSelAlways);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeCtrlDlg)
	ON_BN_CLICKED(IDC_TVEDITLABELS, OnControlChange)
	ON_BN_CLICKED(IDC_TVHASBUTTONS, OnControlChange)
	ON_BN_CLICKED(IDC_TVHASLINES, OnControlChange)
	ON_BN_CLICKED(IDC_TVLINESATROOT, OnControlChange)
	ON_BN_CLICKED(IDC_TVDISABLEDDRAGDROP, OnControlChange)
	ON_BN_CLICKED(IDC_TVSHOWSELALWAYS, OnControlChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDlg message handlers
BOOL CTreeCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData();
	return TRUE; 
}

void CTreeCtrlDlg::OnControlChange()
{
	UpdateData();
}

