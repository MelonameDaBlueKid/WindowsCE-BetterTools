// SpinCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ctrldemo.h"
#include "SpinCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpinCtrlPage property page

IMPLEMENT_DYNCREATE(CSpinCtrlPage, CPropertyPage)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSpinCtrlPage::CSpinCtrlPage() : CPropertyPage(CSpinCtrlPage::IDD)
{
	//{{AFX_DATA_INIT(CSpinCtrlPage)
	m_iAlignment = 0;
	m_uiRangeFrom = 0;
	m_iOrientation = 0;
	m_uiRangeTo = 100;
	m_bWrap = FALSE;
	//}}AFX_DATA_INIT
}

CSpinCtrlPage::~CSpinCtrlPage()
{
}

void CSpinCtrlPage::DoDataExchange(CDataExchange* pDX)
{
	if(!pDX->m_bSaveAndValidate)
	{
		CComboBox* pOrientation = (CComboBox*)GetDlgItem(IDC_SPIN_ORIENTATION);
		pOrientation->ResetContent();
		pOrientation->AddString(CString((LPCTSTR)IDS_VERTICAL2));
		pOrientation->AddString(CString((LPCTSTR)IDS_HORIZONTAL2));

		CComboBox* pAlign = (CComboBox*)GetDlgItem(IDC_SPIN_ALIGNMENT);
		pAlign->ResetContent();
		pAlign->AddString(CString((LPCTSTR)IDS_UNATTACHED));
		pAlign->AddString(CString((LPCTSTR)IDS_LEFT2));
		pAlign->AddString(CString((LPCTSTR)IDS_RIGHT2));
	}

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpinCtrlPage)
	DDX_CBIndex(pDX, IDC_SPIN_ALIGNMENT, m_iAlignment);
	DDX_Text(pDX, IDC_SPIN_FROM, m_uiRangeFrom);
	DDV_MinMaxInt(pDX, m_uiRangeFrom, -32768, 32767);
	DDX_CBIndex(pDX, IDC_SPIN_ORIENTATION, m_iOrientation);
	DDX_Text(pDX, IDC_SPIN_TO, m_uiRangeTo);
	DDV_MinMaxInt(pDX, m_uiRangeTo, -32768, 32767);
	DDX_Check(pDX, IDC_SPIN_WRAP, m_bWrap);
	//}}AFX_DATA_MAP
}

BOOL CSpinCtrlPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CWnd* pEdit = GetDlgItem( IDC_SPIN_EDIT );
	pEdit->GetWindowRect( &m_EditRect );
	ScreenToClient( &m_EditRect );
	pEdit->SetWindowText(_T("0"));

	CreateSpinCtrl();
	SetModified(TRUE);

	return TRUE;
}

void CSpinCtrlPage::CreateSpinCtrl()
{
	if(m_Spin.m_hWnd != NULL)
	{
#if (_WIN32_WCE > 200)
		m_Spin.SetBuddy(NULL);
#endif // _WIN32_WCE
		m_Spin.DestroyWindow();
	}
	DWORD dwStyles=UDS_ARROWKEYS;

	// Build styles mask
	if ( 1 == m_iAlignment )
		dwStyles |= UDS_ALIGNLEFT;		// Control is placed to the left of buddy, if set
										// (default = unattached)
	else if ( 2 == m_iAlignment )
		dwStyles |= UDS_ALIGNRIGHT;		// Control is placed to the right of buddy, if set
										// (default = unattached)
	if ( 1 == m_iOrientation )
		dwStyles |= UDS_HORZ;			// Control is horizontal, if set (default = vert)

	if ( m_bWrap )
		dwStyles |= UDS_WRAP;			// Position wraps when range exceeded, if set

	// Get edit control and change Z-order (created controls go at bottom of Z-order)
	CWnd *pEdit = GetDlgItem( IDC_SPIN_EDIT );

	pEdit->SetWindowPos(&wndBottom, m_EditRect.left, m_EditRect.top, m_EditRect.Width(), 
		m_EditRect.Height(), SWP_SHOWWINDOW);

	// Create spin (up-down) control 
	CWnd* pWnd = GetDlgItem( IDC_SPIN_POS );
	CRect rect;
	pWnd->GetWindowRect( &rect );
	ScreenToClient( &rect );

	// make the spin control large when it is horizontal
	if (dwStyles & UDS_HORZ)
		rect.right = rect.right + 8;

	m_Spin.Create( WS_VISIBLE | WS_CHILD | dwStyles, rect, this, IDC_SPIN );
	m_Spin.SetRange( m_uiRangeFrom, m_uiRangeTo );	// Sends UDM_SETRANGE
	m_Spin.SetBuddy(pEdit);
	
	int nCurrValue = GetDlgItemInt(IDC_SPIN_EDIT);
	m_Spin.SetPos(nCurrValue);

	CWnd *pStatic = GetDlgItem(IDC_SPIN_STATIC);
	pStatic->SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

BEGIN_MESSAGE_MAP(CSpinCtrlPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSpinCtrlPage)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_SPIN_ALIGNMENT, OnSelchangeSpinAlignment)
	ON_EN_KILLFOCUS(IDC_SPIN_FROM, OnKillfocusSpinFrom)
	ON_EN_KILLFOCUS(IDC_SPIN_EDIT, OnKillfocusSpinEdit)
	ON_CBN_SELCHANGE(IDC_SPIN_ORIENTATION, OnSelchangeSpinOrientation)
	ON_EN_KILLFOCUS(IDC_SPIN_TO, OnKillfocusSpinTo)
	ON_BN_CLICKED(IDC_SPIN_WRAP, OnSpinWrap)
	ON_EN_CHANGE(IDC_SPIN_EDIT, OnChangeSpinEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpinCtrlPage message handlers

void CSpinCtrlPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	TCHAR buf[32];
	wsprintf( buf, _T("%d"), nPos );
	CWnd* pWnd = ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN))->GetBuddy();
	if ( pWnd != NULL )
		pWnd->SetWindowText( buf );
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSpinCtrlPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	TCHAR buf[32];
	wsprintf( buf, _T("%d"), nPos );
	CWnd* pWnd = ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN))->GetBuddy();
	if ( pWnd != NULL )
		pWnd->SetWindowText( buf );
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CSpinCtrlPage::ChangeCtrlStyle()
{
	UpdateData();
	CreateSpinCtrl();
}

void CSpinCtrlPage::OnSpinWrap() 
{
	ChangeCtrlStyle();
}

void CSpinCtrlPage::OnKillfocusSpinFrom() 
{
	UpdateData();
	int min, max;
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN);
	pSpin->GetRange(min, max);
	
	
	if ( (m_uiRangeFrom > m_uiRangeTo) && 
		 (m_uiRangeFrom > -32768) && ( m_uiRangeFrom < 32767 ) &&
		 (m_uiRangeTo > -32768) && ( m_uiRangeTo < 32767 ))
	{
		SWAP(m_uiRangeFrom, m_uiRangeTo);
		UpdateData(FALSE);
	}
	min = m_uiRangeFrom;
	max = m_uiRangeTo;
	pSpin->SetRange(min, max);
	CString strEdit;
	pSpin->GetBuddy()->GetWindowText(strEdit);
	if (_ttoi(strEdit) > max)
	{
		TCHAR buf[32];
		wsprintf( buf, _T("%d"), max );
		pSpin->GetBuddy()->SetWindowText(buf);
	}
}

void CSpinCtrlPage::OnKillfocusSpinTo() 
{
	UpdateData();
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN);
	int min, max;
	pSpin->GetRange(min, max);
	if ( (m_uiRangeFrom > m_uiRangeTo) && 
		 (m_uiRangeFrom > -32768) && ( m_uiRangeFrom < 32767 ) &&
		 (m_uiRangeTo > -32768) && ( m_uiRangeTo < 32767 ))
	{
		SWAP(m_uiRangeFrom, m_uiRangeTo);
		UpdateData(FALSE);
	}
	min = m_uiRangeFrom;
	max = m_uiRangeTo;
	pSpin->SetRange(min, max);
	CString strEdit;
	pSpin->GetBuddy()->GetWindowText(strEdit);
	if (_ttoi(strEdit) < min)
	{
		TCHAR buf[32];
		wsprintf( buf, _T("%d"), min );
		pSpin->GetBuddy()->SetWindowText(buf);
	}
}

void CSpinCtrlPage::OnKillfocusSpinEdit() 
{
	UpdateData();
}

void CSpinCtrlPage::OnSelchangeSpinOrientation() 
{
	ChangeCtrlStyle();
}

void CSpinCtrlPage::OnSelchangeSpinAlignment() 
{
	ChangeCtrlStyle();
}



void CSpinCtrlPage::OnChangeSpinEdit() 
{
	int nCurrValue = GetDlgItemInt(IDC_SPIN_EDIT);
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN);
	if(pSpin != NULL)
		pSpin->SetPos(nCurrValue);
}
