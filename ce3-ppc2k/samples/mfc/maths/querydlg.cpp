// QueryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "maths.h"
#include "QueryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryDlg dialog


CQueryDlg::CQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryDlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDlg message handlers

int CQueryDlg::GetChoice()
{
	return m_idChoice;
}

BOOL CQueryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strChoice1.LoadString(IDS_MATH1);
	m_strChoice2.LoadString(IDS_MATH2);
	m_strChoice3.LoadString(IDS_MATH3);

	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST1);
	pList->AddString(m_strChoice1);
	pList->AddString(m_strChoice2);
	pList->AddString(m_strChoice3);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQueryDlg::OnSelchangeList1() 
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST1);
	m_idChoice = pList->GetCurSel();
}

void CQueryDlg::OnDblclkList1() 
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST1);
	m_idChoice = pList->GetCurSel();
	EndDialog(IDOK);
}
