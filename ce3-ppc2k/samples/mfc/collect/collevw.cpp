// collevw.cpp : implementation of the CCollectView class
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
#include "collect.h"

#include "colledoc.h"
#include "collevw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCollectView

IMPLEMENT_DYNCREATE(CCollectView, CView)

BEGIN_MESSAGE_MAP(CCollectView, CView)
	//{{AFX_MSG_MAP(CCollectView)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollectView construction/destruction

CCollectView::CCollectView()
{
}

CCollectView::~CCollectView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCollectView drawing

void CCollectView::OnDraw(CDC* pDC)
{
	CCollectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC;    // not used
}

/////////////////////////////////////////////////////////////////////////////
// CCollectView diagnostics

#ifdef _DEBUG
void CCollectView::AssertValid() const
{
	CView::AssertValid();
}

void CCollectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCollectDoc* CCollectView::GetDocument() // non-debug version is inline
{
	return STATIC_DOWNCAST(CCollectDoc, m_pDocument);
}
#endif //_DEBUG

