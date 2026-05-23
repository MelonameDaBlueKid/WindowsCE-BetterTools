// shapesvw.cpp : implementation of the CShapesView class
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
#include "propdlg.h"

#include "shapeobj.h"
#include "colorpge.h"
#include "stylepge.h"
#include "propsht.h"
#include "propsht2.h"
#include "shapedoc.h"
#include "shapesvw.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
CModalShapePropSheet *g_pCPropertySheet=NULL;
#else
CPropertySheet *g_pCPropertySheet=NULL;
#endif // _WIN32_WCE_PSPC
/////////////////////////////////////////////////////////////////////////////
// CShapesView

IMPLEMENT_DYNCREATE(CShapesView, CView)

BEGIN_MESSAGE_MAP(CShapesView, CView)
	ON_MESSAGE(WM_USER_CHANGE_OBJECT_PROPERTIES, OnChangeObjectProps)
	//{{AFX_MSG_MAP(CShapesView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_SIMPLE_PROPERTY_SHEET, OnSimplePropertySheet)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShapesView construction/destruction

CShapesView::CShapesView()
{
	m_pShapeSelected = NULL;
	m_pModalShapePropSheet = NULL;
}

CShapesView::~CShapesView()
{
}


/////////////////////////////////////////////////////////////////////////////
// CShapesView drawing

void CShapesView::OnDraw(CDC* pDC)
{
	CShapesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rectDirty, rectIntersect;
	pDC->GetClipBox(&rectDirty);
	if (rectDirty.IsRectNull())
		GetClientRect(&rectDirty);


	CShape* pShape;
	POSITION pos = pDoc->m_shapeList.GetTailPosition();
	// Draw all of the shapes, except the currently selected shape, from
	// back to front.
	while (pos != NULL)
	{
		pShape = pDoc->m_shapeList.GetPrev(pos);
		if (rectIntersect.IntersectRect(&pShape->m_rect, &rectDirty) != 0
			&& pShape != m_pShapeSelected)
			pShape->Draw(pDC, FALSE);
	}
	// Draw the selected shape on top
	if (m_pShapeSelected != NULL)
		m_pShapeSelected->Draw(pDC, TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CShapesView diagnostics

#ifdef _DEBUG
void CShapesView::AssertValid() const
{
	CView::AssertValid();
}

void CShapesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapesDoc* CShapesView::GetDocument() // non-debug version is inline
{
	ASSERT_KINDOF(CShapesDoc, m_pDocument);
	return (CShapesDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShapesView message handlers

void CShapesView::OnLButtonDown(UINT /*nFlags*/, CPoint point)
{
	CShapesDoc* pDoc = GetDocument();

	CClientDC dc(this);

	CShape* pShapeHit;
	pShapeHit = pDoc->HitTest(point);
	if (pShapeHit != NULL)
	{   // Select the object that was clicked.

		CRect rectInvalid;
		// Invalidate the previously selected object, so it will
		// be redrawn as unselected.
		if (m_pShapeSelected != NULL)
			InvalidateRect(&m_pShapeSelected->m_rect);
		m_pShapeSelected = pShapeHit;

		// Invalidate the newly selected object, so it will be
		// redrawn as selected.
		InvalidateRect(&m_pShapeSelected->m_rect);
	}
	else
	{   // Add a new shape

		CShape* pShapeNew = new CShape(
			black,
			rectangle,
			CRect(point.x-50, point.y-50, point.x + 50, point.y + 50));
		pDoc->AddShape(pShapeNew);
		m_pShapeSelected = pShapeNew;
	}
}

void CShapesView::OnSimplePropertySheet()
{
	if (m_pShapeSelected == NULL)
		return;

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	g_pCPropertySheet=new CModalShapePropSheet;

	g_pCPropertySheet->m_colorPage.m_nColor = m_pShapeSelected->m_shapecolor;
	g_pCPropertySheet->m_stylePage.m_nShapeStyle = m_pShapeSelected->m_shapestyle;
#else
	g_pCPropertySheet=new CPropertySheet(AFX_IDS_APP_TITLE);
	
	CStylePage stylePage;
	CColorPage colorPage;

	stylePage.m_nShapeStyle = m_pShapeSelected->m_shapestyle;
	colorPage.m_nColor = m_pShapeSelected->m_shapecolor;

	g_pCPropertySheet->AddPage(&stylePage);
	g_pCPropertySheet->AddPage(&colorPage);
#endif // _WIN32_WCE_PSPC

	if (g_pCPropertySheet->DoModal() == IDOK)
	{
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
		m_pShapeSelected->m_shapecolor = g_pCPropertySheet->m_colorPage.m_nColor;
		m_pShapeSelected->m_shapestyle
			= (SHAPE_STYLE)g_pCPropertySheet->m_stylePage.m_nShapeStyle;
#else
		m_pShapeSelected->m_shapecolor = colorPage.m_nColor;
		m_pShapeSelected->m_shapestyle
			= (SHAPE_STYLE)stylePage.m_nShapeStyle;
#endif // _WIN32_WCE_PSPC
		GetDocument()->SetModifiedFlag();
		GetDocument()->UpdateAllViews(NULL);
	}

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	if(g_pCPropertySheet->m_pWndEmptyCB != NULL)
	{
		g_pCPropertySheet->m_pWndEmptyCB->DestroyWindow();
		delete g_pCPropertySheet->m_pWndEmptyCB;
		g_pCPropertySheet->m_pWndEmptyCB = NULL;
	}
#endif // _WIN32_WCE_PSPC

	delete g_pCPropertySheet;
	g_pCPropertySheet=NULL;
}

LRESULT CShapesView::OnChangeObjectProps(WPARAM, LPARAM)
{
	// The user-defined WM_USER_CHANGE_OBJECT_PROPS message is sent
	// by the modal CModalShapePropSheet when the user chooses Apply Now,
	// or by the modeless CModelessShapePropSheet when the user
	// changes any setting in a property page.

	if (m_pShapeSelected == NULL)
		return 0;

	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL);
	return 0;
}
