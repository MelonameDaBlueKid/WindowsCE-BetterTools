// CheckVw.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "chkbook.h"
#include "ChkBkVw.h"
#include "chkrec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckBookView

IMPLEMENT_DYNCREATE(CCheckBookView, CView)

CCheckBookView::CCheckBookView()
{
	m_bCheckView = TRUE;
}

CCheckBookView::~CCheckBookView()
{
}

BEGIN_MESSAGE_MAP(CCheckBookView, CView)
	//{{AFX_MSG_MAP(CCheckBookView)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
#if (_WIN32_WCE > 200)
	ON_WM_SETTINGCHANGE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckBookView drawing

/////////////////////////////////////////////////////////////////////////////
// CCheckBookView diagnostics

#ifdef _DEBUG
void CCheckBookView::AssertValid() const
{
	CView::AssertValid();
}

void CCheckBookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCheckBookDoc* CCheckBookView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCheckBookDoc)));
	return (CCheckBookDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCheckBookView message handlers

void CCheckBookView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);
	if (m_bCheckView)
	{
		bShow ? m_dlg.ShowWindow(SW_SHOW) : m_dlg.ShowWindow(SW_HIDE);
		m_edit.ShowWindow(SW_HIDE);
		m_dlg.UpdateWindow();
		m_dlg.SetFocus();
	}
	else
	{
		bShow ? m_edit.ShowWindow(SW_SHOW) : m_edit.ShowWindow(SW_HIDE);
		m_dlg.ShowWindow(SW_HIDE);
		m_edit.UpdateWindow();
		m_edit.SetFocus();
	}
}

void CCheckBookView::CheckView(BOOL bCheckView)
{
	m_bCheckView = bCheckView;
	if (bCheckView)
	{
		m_dlg.ShowWindow(SW_SHOW);
		m_edit.ShowWindow(SW_HIDE);
		m_dlg.SetFocus();
	}
	else
	{
		UpdateBookViewWindow();
		m_dlg.ShowWindow(SW_HIDE);
		m_edit.ShowWindow(SW_SHOW);
		m_edit.SetFocus();
	}
}

UINT CCheckBookView::QueryCommitCheck()
{
	return AfxMessageBox(CString((LPCTSTR)IDS_MESSAGE3), MB_YESNOCANCEL);
}

void CCheckBookView::NewCheck(const UINT nCheckNo)
{
	ASSERT(m_bCheckView);
	
	// Set dialog edit boxes to blank
	(m_dlg.m_strCheckNo).Format(_T("%d"), nCheckNo);
	m_dlg.m_strDate = "";
	m_dlg.m_dwCents = 0;
	m_dlg.m_strAmount = m_dlg.GetDollarsCentsText(0);
	m_dlg.m_strPayTo = "";
	m_dlg.m_strMemo = "";
	m_dlg.UpdateData(FALSE);
}

void CCheckBookView::GetCheckInfo(DWORD& dwCents, CString& strPayTo,
	CString& strDate, CString& strMemo)
{
	m_dlg.UpdateData(TRUE);

	// DDX for DWORD member of edit box is not working
	CString strDollars = "", strCents = "";

	dwCents = m_dlg.m_dwCents;

	strPayTo = m_dlg.m_strPayTo;
	strDate = m_dlg.m_strDate;
	strMemo = m_dlg.m_strMemo;
}

void CCheckBookView::SetCheckInfo(const UINT CheckNo,
	DWORD dwCents, CString strPayTo,
	CString strDate, CString strMemo)
{
	// DDX for DWORD in edit box is not working currently
	// Use m_strCents as a dummy value for the moment
	(m_dlg.m_strCheckNo).Format(_T("%d"), CheckNo);
	m_dlg.m_dwCents = dwCents;
	m_dlg.m_strAmount = m_dlg.GetDollarsCentsText(dwCents);
	m_dlg.m_strPayTo = strPayTo;
	m_dlg.m_strDate = strDate;
	m_dlg.m_strMemo = strMemo;
	m_dlg.UpdateData(FALSE);

	if (m_bCheckView)
		m_dlg.SetFocus();
	else
		m_edit.SendMessage(WM_SETFOCUS);
}

void CCheckBookView::OnDraw(CDC* pDC) 
{	
}

int CCheckBookView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#if defined(_WIN32_WCE_PSPC)
#if (_WIN32_WCE >= 212)
	m_dlg.m_bFullScreen=FALSE;
#endif 
	m_dlg.Create(IDD_CHECK_PSPC, this);
#else // _WIN32_WCE_PSPC
	m_dlg.Create(IDD_CHECK, this);
#endif	// _WIN32_WCE_PSPC
	CRect rect;
	GetClientRect(&rect);
	m_edit.Create(WS_HSCROLL | WS_VSCROLL | ES_READONLY | ES_MULTILINE,
			rect, this, IDC_CHECKBOOK);

	// Get the text metrics to determine the tab stops
	TEXTMETRIC tm;
	CDC* pDC = GetDC();
	pDC->GetTextMetrics(&tm);

	int tabStops[4] = {
		4 * tm.tmAveCharWidth,	// Width of Check# column
		11 * tm.tmAveCharWidth,	// Width of Date column
		26 * tm.tmAveCharWidth,	// Pay To / Memo column
		11 * tm.tmAveCharWidth	// Amount column
		};
	m_edit.SetTabStops(4, (LPINT)tabStops);
	ReleaseDC(pDC);

	return 0;
}

void CCheckBookView::UpdateBookViewWindow() 
{	
	CRect rect;
	GetClientRect(&rect);	
	m_edit.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(),
				SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
}

#if (_WIN32_WCE > 200) 
void CCheckBookView::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	UpdateBookViewWindow();
}
#endif
