// WCE_DatabaseView.cpp : implementation of the CWCEDBView class
//

#include "stdafx.h"

#include "wcedbtst.h"
#include "wcedbdoc.h"
#include "wcedbvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWCEDBView

IMPLEMENT_DYNCREATE(CWCEDBView, CScrollView)

BEGIN_MESSAGE_MAP(CWCEDBView, CScrollView)
	//{{AFX_MSG_MAP(CWCEDBView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
		ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWCEDBView construction/destruction

CWCEDBView::CWCEDBView()
{
}

CWCEDBView::~CWCEDBView()
{
}

BOOL CWCEDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWCEDBView drawing

void CWCEDBView::OnDraw(CDC* pDC)
{
	CWCEDBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	CRect wndRect;
	GetClientRect(&wndRect);

	// Workaround for VIEWSCRL.CPP omission of an erase in the ScrollBy() ScrollWindowEX call.
	pDC->FillSolidRect(wndRect,pDC->GetBkColor());

	// Workaround for lack of origins in WCE
	// Also, note that SetScrollSizes should use the MM_TEXT map mode
	int nOrgX = -GetScrollPosition().x;
	int nOrgY = -GetScrollPosition().y;

	for(int n=0; n < pDoc->Output.GetSize(); n++)
	{
		CClientDC clientDC(this);
		CRect textRect(nOrgX, n*tm.tmHeight + nOrgY, wndRect.Width(), (n+1)*tm.tmHeight + nOrgY);
		clientDC.DrawText(pDoc->Output[n],pDoc->Output[n].GetLength(),textRect,DT_LEFT|DT_TOP);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWCEDBView diagnostics

#ifdef _DEBUG
void CWCEDBView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWCEDBView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWCEDBDoc* CWCEDBView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWCEDBDoc)));
	return (CWCEDBDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWCEDBView message handlers

void CWCEDBView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CRect rect;
	GetClientRect(&rect);
	
	CSize page(rect.Width()*8/10, rect.Height()*8/10);

	SetScrollSizes(MM_TEXT,CSize(1000,1000),page);
	InvalidateRect(NULL);
	UpdateWindow();
}

void CWCEDBView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nMapMode;
	CSize sizeTotal, sizePage, sizeLine;
	GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);

	if(nChar == VK_UP)
		OnScrollBy(CSize(0,-sizeLine.cy));
	else if(nChar == VK_DOWN)
		OnScrollBy(CSize(0,sizeLine.cy));
	else if(nChar == VK_LEFT)
		OnScrollBy(CSize(-sizeLine.cx,0));
	else if(nChar == VK_RIGHT)
		OnScrollBy(CSize(sizeLine.cx,0));
	else
		CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}
