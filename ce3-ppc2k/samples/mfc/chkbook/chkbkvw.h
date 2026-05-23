// CheckVw.h : header file
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

#ifndef __INC_CHKBKVW_H__
#define __INC_CHKBKVW_H__

#include "chkbkdoc.h"
#include "CheckDlg.h"
#include "chkbkEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckBookView view

class CCheckBookView : public CView
{
protected:
	CCheckBookView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCheckBookView)

// Attributes
public:
	BOOL m_bCheckView;
	CCheckDlg m_dlg;
	CCheckBookEdit m_edit;
	CCheckBookDoc* GetDocument();
	void UpdateBookViewWindow();
// Operations
public:
	void CheckView(BOOL bCheckView);
	UINT QueryCommitCheck();
	void NewCheck(const UINT checkNo);
	void GetCheckInfo(DWORD& dwCents,
		CString& strPayTo, CString& strDate, CString& strMemo);
	void SetCheckInfo(const UINT checkNo, DWORD dwCents,
		CString strPayTo, CString strDate, CString strMemo);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBookView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCheckBookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckBookView)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
#if (_WIN32_WCE > 200) 
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ChkBkVw.cpp
inline CCheckBookDoc* CCheckBookView::GetDocument()
   { return (CCheckBookDoc*)m_pDocument; }
#endif

#endif // __INC_CHKBKVW_H__
