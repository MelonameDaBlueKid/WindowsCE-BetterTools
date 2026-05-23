// finddlg.cpp : implementation file
//

#include "stdafx.h"
#if (_WIN32_WCE <= 200) 
// Backward compatibility for H/PC 1.0 and 2.0
// For later versions, we use an improved implementation of the Find Dialog
// in MFCCE.
#include "np.h"
#include "npview.h"
#include "mainfrm.h"
#include "npdoc.h"
#include "finddlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDlg dialog


CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlg)
	m_bMatchCase = FALSE;
	m_szText = _T("");
	m_nDirection = 1; // down by default
	//}}AFX_DATA_INIT
}


void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)						 
	DDX_Check(pDX, IDC_CHECK1, m_bMatchCase);
	DDX_Radio(pDX, IDC_RADIO1, m_nDirection);
	DDX_Text(pDX,  IDC_EDIT1,  m_szText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	ON_BN_CLICKED(ID_EDIT_FIND_NEXT, OnEditFindNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFindDlg message handlers
void CFindDlg::OnEditFindNext() 
{
	// the user selected to search. see if there is a search pattern in the edit control 
	// using the default data exchange. 
	// if no search string is present, keep the dialog box up.
	UpdateData(TRUE);

	if (!m_szText.GetLength())
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return ;
	}

	EndDialog(TRUE);
}

BOOL CFindDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
#endif // _WIN32_WCE <= 200

