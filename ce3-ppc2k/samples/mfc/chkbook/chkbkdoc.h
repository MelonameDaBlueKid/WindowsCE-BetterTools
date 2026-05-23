// ChkBkDoc.h : interface of the CCheckBookDoc class
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

#ifndef __INC_CHKBKDOC_H__
#define __INC_CHKBKDOC_H__

#include "chkrec.h"

class CCheckBookDoc : public CDocument
{
protected: // create from serialization only
	CCheckBookDoc();
	DECLARE_DYNCREATE(CCheckBookDoc)

// Attributes
public:
	BOOL		m_bCheckView;
	CCheckBook	m_CheckBook;
	CView*		m_pView;
	UINT		m_nNewCheckNo;
	UINT		m_nCurrentCheckNo;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBookDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCheckBookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CCheckBook* GetCheckBook();
	void UpdateRecord();

protected:
	UINT CheckThisCheck();
	BOOL FileOpenHelper(BOOL bFileOpen);

// Generated message map functions
protected:
	//{{AFX_MSG(CCheckBookDoc)
	afx_msg void OnViewBook();
	afx_msg void OnViewCheck();
	afx_msg void OnEditNewCheck();
	afx_msg void OnNextCheck();
	afx_msg void OnPrevCheck();
	afx_msg void OnEditCommit();
	afx_msg void OnFileOpen();
	afx_msg void OnAppExit();
	afx_msg void OnUpdateNextCheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrevCheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewBook(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewCheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommitCheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewCheck(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __INC_CHKBKDOC_H__
/////////////////////////////////////////////////////////////////////////////
