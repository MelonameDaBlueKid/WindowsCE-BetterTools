// dibview.cpp : implementation of the CDibView class
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

#include "dibdoc.h"
#include "dibview.h"
#include "dibapi.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//This is global so that the oldPalette and bmpPalette can be restored
//depending on the menu selection state
//
CPalette* oldPalette;
CPalette* bmpPalette;

/////////////////////////////////////////////////////////////////////////////
// CDibView

IMPLEMENT_DYNCREATE(CDibView, CScrollView)

BEGIN_MESSAGE_MAP(CDibView, CScrollView)
	//{{AFX_MSG_MAP(CDibView)
	ON_MESSAGE(WM_USER, OnDoRealize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDibView construction/destruction

CDibView::CDibView()
{
}

CDibView::~CDibView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDibView drawing

void CDibView::OnDraw(CDC* pDC)
{
	CDibDoc* pDoc = GetDocument();

	HDIB hDIB = pDoc->GetHDIB();
	if (hDIB != NULL)
	{
		LPSTR lpDIB = (LPSTR)(LPSTR)hDIB;
		int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
		int cyDIB = (int) ::DIBHeight(lpDIB);        // Size of DIB - y

		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest;
		rcDest = rcDIB;
		::PaintDIB(pDC->m_hDC, &rcDest, pDoc->GetHDIB(), &rcDIB, pDoc->GetDocPalette());
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDibView commands


LRESULT CDibView::OnDoRealize(WPARAM wParam, LPARAM)
{
	ASSERT(wParam != NULL);
	CDibDoc* pDoc = GetDocument();

	CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_KINDOF(CMainFrame, pAppFrame);

	CClientDC appDC(pAppFrame);

	//restore the oldPalette if it exists
	//and the menu selection is not using the bitmap palette
	//
	if(!m_bUsePalette && oldPalette) {
		bmpPalette = appDC.SelectPalette(oldPalette, ((HWND)wParam) != m_hWnd);
		if (oldPalette)
		{
			UINT nColorsChanged;
			nColorsChanged = appDC.RealizePalette();
			if (nColorsChanged > 0)
				pDoc->UpdateAllViews(NULL);
			appDC.SelectPalette(oldPalette, TRUE);
		}
		else
		{
			TRACE0("\tSelectPalette failed.\n");
		}
		return 0;
		}

	
	if (pDoc->GetHDIB() == NULL)
		return 0L;  // must be a new document

	CPalette* pPal = pDoc->GetDocPalette();
	if (pPal != NULL)
	{

		// All views but one should be a background palette.
		// wParam contains a handle to the active view, so the SelectPalette
		// bForceBackground flag is FALSE only if wParam == m_hWnd (this view)

		oldPalette = appDC.SelectPalette(pPal, ((HWND)wParam) != m_hWnd);
		if (oldPalette)
		{
			UINT nColorsChanged;
			nColorsChanged = appDC.RealizePalette();
			if (nColorsChanged > 0)
				pDoc->UpdateAllViews(NULL);
			appDC.SelectPalette(oldPalette, TRUE);
		}
		else
		{
			TRACE0("\tSelectPalette failed.\n");
		}
	}
	return 0L;
}

void CDibView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	ASSERT(GetDocument() != NULL);

	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());

	ShowPicture(TRUE); // show picture

	//
	// Inform the user if the device uses 256 colors 
	// and therefore (it is assumed) supports palettes
	//
	CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_KINDOF(CMainFrame, pAppFrame);

	CClientDC appDC(pAppFrame);
	if (appDC.GetDeviceCaps(NUMCOLORS) == 256)
		AfxMessageBox(TEXT("This device supports palettes (256 colors)."));
	else
		AfxMessageBox(TEXT("This device does not support palettes."));
	//
}


void CDibView::OnActivateView(BOOL bActivate, CView* pActivateView,
					CView* pDeactiveView)
{
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		ASSERT(pActivateView == this);
		OnDoRealize((WPARAM)m_hWnd, 0);   // same as SendMessage(WM_DOREALIZE);
	}
}

void CDibView::ShowPicture(BOOL bUsePalette)
{
	m_bUsePalette = bUsePalette;
	CDibDoc* pDoc = (CDibDoc*)GetDocument();
	if(pDoc)
	{
		pDoc->OnOpenFile(_T(".\\forest.bmp"));
		Invalidate();
	}
}

