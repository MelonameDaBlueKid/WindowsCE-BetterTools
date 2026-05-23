// CCheckBookEdit.cpp : implementation file
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

// The class CCheckBookEdit is the application specific implementation
// for CEdit.  When CCheckBookView is in Book View, this edit window is
// displayed.

#include "stdafx.h"
#include "chkbook.h"
#include "ChkbkEdt.h"
#include "chkbkvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckBookEdit

CCheckBookEdit::CCheckBookEdit()
{
}

CCheckBookEdit::~CCheckBookEdit()
{
}


BEGIN_MESSAGE_MAP(CCheckBookEdit, CEdit)
	//{{AFX_MSG_MAP(CCheckBookEdit)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckBookEdit message handlers

void CCheckBookEdit::OnSetfocus() 
{
	static bSetTabStops = FALSE;

	if(!bSetTabStops)
	{
		int nTabStops[] = {30, 60, 200};
		SetTabStops(sizeof(nTabStops)/sizeof(int), nTabStops);
		bSetTabStops = TRUE;
	}

	// Get a pointer to the owner document
	m_pDoc = (CCheckBookDoc*)
		((CFrameWnd*)AfxGetMainWnd())->GetActiveDocument();

	CString strCents, strCheckNo, strPayTo, strDate, strMemo;
	CCheckRecord* pRec;
	int y = 0;

	CPaintDC dc(this); // device context for painting
	
	// Get the checkbook information
	CCheckBook* chkBk;
	chkBk = m_pDoc->GetCheckBook();

	// Column headers will go at the top of the window
	CString strEditContents;
	strEditContents.LoadString(IDS_EDITCONTENTS);

	// Add the each check's information into the edit string
	for (UINT nCheck = FIRST_CHECK_NO; 
		nCheck < m_pDoc->m_nNewCheckNo; nCheck++)
	{
		pRec = chkBk->GetCheck(nCheck);
		strCheckNo.Format(_T("%d"), nCheck);
		strCents.Format(_T("%9lu.%02u"), pRec->GetCents() / 100, // Dollars
			pRec->GetCents() % 100); // Cents

		pRec->GetPayTo(strPayTo);
		pRec->GetMemo(strMemo);
		// Only print out 20 chars of the Pay To & Memo - not enough space
		// Add "..." if the string is shortened, so the user realizes
		if (strPayTo.GetLength() > 20)
		{
			strPayTo = strPayTo.Left(20);
			strPayTo += _T("...");
		}
		if (strMemo.GetLength() > 20)
		{
			strMemo = strMemo.Left(20);
			strMemo += _T("...");
		}

		pRec->GetDate(strDate);

		strEditContents += strCheckNo + _T("\t") + strDate + _T("\t") + strPayTo + _T("\t$") + strCents + _T("\r\n\t\t") +  strMemo + _T("\t\t\t\r\n");
	}

	// Now we have the edit box's contents, write it to the window
	SetWindowText(strEditContents);

	// Highlight the current check
	int startPos = (m_pDoc->m_nCurrentCheckNo - FIRST_CHECK_NO) * 2 + 2;
	SetSel(LineIndex(startPos), LineIndex(startPos + 2));
	InvalidateRect(NULL,FALSE);
}

void CCheckBookEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int pos = HIWORD(CharFromPos(point)) - (HIWORD(CharFromPos(point)) % 2);
	if ((pos == 0) || (LineLength(LineIndex(pos)) == 0))
		pos = 2;
	SetSel(LineIndex(pos), LineIndex(pos + 2));
	m_pDoc->m_nCurrentCheckNo = ((pos - 2) / 2) + FIRST_CHECK_NO;
}

void CCheckBookEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (nFlags & MK_LBUTTON)
	{
		int pos = HIWORD(CharFromPos(point)) - (HIWORD(CharFromPos(point)) % 2);
		if ((pos == 0) || (LineLength(LineIndex(pos)) == 0))
			pos = 2;
		SetSel(LineIndex(pos), LineIndex(pos + 2));
		m_pDoc->m_nCurrentCheckNo = ((pos - 2) / 2) + FIRST_CHECK_NO;
	}
}

void CCheckBookEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int pos = HIWORD(CharFromPos(point)) - (HIWORD(CharFromPos(point)) % 2);
	if ((pos == 0) || (LineLength(LineIndex(pos)) == 0))
		pos = 2;
	SetSel(LineIndex(pos), LineIndex(pos + 2));
	m_pDoc->m_nCurrentCheckNo = ((pos - 2) / 2) + FIRST_CHECK_NO;
	Default();
}


void CCheckBookEdit::OnKillfocus() 
{
	m_pDoc->UpdateRecord();
}
