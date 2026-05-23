// propsht.cpp : implementation of the CModalShapePropSheet class
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
#include "resource.h"
#include "shapeobj.h"
#include "colorpge.h"
#include "stylepge.h"
#include "propsht.h"

IMPLEMENT_DYNAMIC(CModalShapePropSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CModalShapePropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModalShapePropSheet)
	ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CModalShapePropSheet::CModalShapePropSheet(CWnd* pWndParent)
	: CPropertySheet(AFX_IDS_APP_TITLE, pWndParent)
{
	AddPage(&m_stylePage);
	AddPage(&m_colorPage);
}

BOOL CModalShapePropSheet::OnInitDialog()
{
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
// WinCE: modal property sheets initially want no menu, so we create an
//        empty menu bar.
	m_pWndEmptyCB = new CCeCommandBar;

	if(m_pWndEmptyCB != NULL)
		((CCeCommandBar*)m_pWndEmptyCB)->CreateEx(this);
#endif // _WIN32_WCE_PSPC

	BOOL bResult = CPropertySheet::OnInitDialog();

	return bResult;
}

void CModalShapePropSheet::SetSheetPropsFromShape(CShape* pShape)
{
	m_stylePage.m_nShapeStyle = pShape->m_shapestyle;
	m_stylePage.SetModified(FALSE);

	m_colorPage.m_nColor = pShape->m_shapecolor;
	m_colorPage.SetModified(FALSE);

	// Reflect the new shape properties in the controls of the
	// currently active property page.
	GetActivePage()->UpdateData(FALSE);
}

void CModalShapePropSheet::SetShapePropsFromSheet(CShape* pShape)
{
	pShape->m_shapecolor = m_colorPage.m_nColor;
	pShape->m_shapestyle = (SHAPE_STYLE)m_stylePage.m_nShapeStyle;

	m_colorPage.SetModified(FALSE);
	m_stylePage.SetModified(FALSE);
}

void CModalShapePropSheet::OnApplyNow()
{
	Default();

	CFrameWnd* pFrameWnd = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());
	CView* pView = pFrameWnd->GetActiveFrame()->GetActiveView();
	pView->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
	m_stylePage.SetModified(FALSE);
	m_colorPage.SetModified(FALSE);
	SendMessage(PSM_CANCELTOCLOSE);
}
