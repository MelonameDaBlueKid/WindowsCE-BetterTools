// AllControlsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "ctrldemo.h"
#include "propsht.h"
#include "mtreectl.h"
#include "listdlg.h"
#include "treedlg.h"
#include "sliddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CListCtrlDlg * g_listCtrlDlg;
extern CTreeCtrlDlg * g_ptreeCtrlDlg;
extern CSliderCtrlDlg * g_pSlidCtrlDlg;
/////////////////////////////////////////////////////////////////////////////
// CAllControlsSheet

IMPLEMENT_DYNAMIC(CAllControlsSheet, CPropertySheet)

CAllControlsSheet::CAllControlsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CAllControlsSheet::CAllControlsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CAllControlsSheet::~CAllControlsSheet()
{
}

void CAllControlsSheet::AddControlPages()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psh.dwFlags |= PSP_USEHICON;
	m_psh.hIcon = m_hIcon;

	AddPage(&m_listctrlpage);
	AddPage(&m_treectrlpage);
    AddPage(&m_progctrlpage);
    AddPage(&m_sliderctrlpage);
	AddPage(&m_spinctrlpage);
}

BEGIN_MESSAGE_MAP(CAllControlsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CAllControlsSheet)
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllControlsSheet message handlers

BOOL CAllControlsSheet::OnInitDialog()
{
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	CString csTitle;
	csTitle.LoadString((UINT)AFX_IDS_APP_TITLE);
	LPTSTR lpszTitle = csTitle.GetBuffer(40);
	SetTitle(lpszTitle);
	csTitle.ReleaseBuffer();
	return CPropertySheet::OnInitDialog();
}

HCURSOR CAllControlsSheet::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}

void CAllControlsSheet::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	if (g_listCtrlDlg)
	{
		g_listCtrlDlg->EndDialog(IDCANCEL);
	}
	if (g_ptreeCtrlDlg)
	{
		g_ptreeCtrlDlg->EndDialog(IDCANCEL);
	}
	if (g_pSlidCtrlDlg)
	{
		g_pSlidCtrlDlg->EndDialog(IDCANCEL);
	}

	CPropertySheet::OnClose();
}
