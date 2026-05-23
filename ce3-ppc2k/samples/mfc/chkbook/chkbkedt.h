// CheckBookEdit.h : header file
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

#ifndef __INC_CHKBKEDT_H__
#define __INC_CHKBKEDT_H__

#include "chkbkdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckBookEdit window

class CCheckBookEdit : public CEdit
{
// Construction
public:
	CCheckBookEdit();

// Attributes
private:
	CCheckBookDoc* m_pDoc;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBookEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCheckBookEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckBookEdit)
	afx_msg void OnSetfocus();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __INC_CHKBKEDT_H__
