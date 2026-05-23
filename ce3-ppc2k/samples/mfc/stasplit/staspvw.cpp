// staspvw.cpp : implementation of the CStaticSplitView class
//

#include "stdafx.h"
#include "stasplit.h"

#include "staspdoc.h"
#include "staspvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitView

IMPLEMENT_DYNCREATE(CStaticSplitView, CEditView)

BEGIN_MESSAGE_MAP(CStaticSplitView, CEditView)
	//{{AFX_MSG_MAP(CStaticSplitView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitView construction/destruction

CStaticSplitView::CStaticSplitView()
{
}

CStaticSplitView::~CStaticSplitView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitView drawing

void CStaticSplitView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitView diagnostics

#ifdef _DEBUG
void CStaticSplitView::AssertValid() const
{
	CEditView::AssertValid();
}

void CStaticSplitView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CStaticSplitDoc* CStaticSplitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStaticSplitDoc)));
	return (CStaticSplitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitView message handlers

void CStaticSplitView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CStaticSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString strPoem = "";
	for (int i = 0; i < pDoc->m_arstrPoem.GetSize(); i++)
	{
		strPoem += pDoc->m_arstrPoem[i] + "\r\n";
	}
	GetEditCtrl().SetWindowText(strPoem);
}

BOOL CStaticSplitView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	if (!CWnd::Create(lpszClassName, lpszWindowName, dwStyle | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE, rect, pParentWnd, nID, pContext))
		return FALSE;

	GetEditCtrl().SetReadOnly(TRUE);
	return TRUE;
}
