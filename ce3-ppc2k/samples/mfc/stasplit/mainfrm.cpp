// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "stasplit.h"
#include "staspdoc.h"
#include "staspvw.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNestedSplitterWnd

// This overridden function ensures that new views are created correctly,
// since the wrong active view at the time of the split could cause an
// empty document to be attached to the new pane

BOOL CNestedSplitterWnd::SplitRow (int cyBefore)
{
	((CMainFrame*)AfxGetMainWnd())->SetActiveView((CView*)GetPane(0, 0));
	return CSplitterWnd::SplitRow(cyBefore);
}

BOOL CNestedSplitterWnd::SplitColumn(int cxBefore)
{
	((CMainFrame*)AfxGetMainWnd())->SetActiveView((CView*)GetPane(0, 0));
	return CSplitterWnd::SplitColumn(cxBefore);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	ON_COMMAND(IDM_SHAREDNEW, OnSharedNew)
	ON_COMMAND(ID_MYFILE_OPEN, OnMyFileOpen)
#endif // _WIN32_WCE_PSPC
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#if (_WIN32_WCE > 200)
	if(!m_wndCommandBar.Create(this) ||
	   !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	   !m_wndCommandBar.AddAdornments())
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}
#else // MFC for Windows CE 1.0 and 2.0
	if(!AddAdornments(0))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}
#endif

	return 0;
}

//#define WCE_DYNAMIC_SPLITTER // comment this out to change the sample to use dynamic splitters.

BOOL CMainFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
#if defined(WCE_DYNAMIC_SPLITTER)
	SIZE sz = {40,40};
	if(!m_wndSplitter1.Create(this, 2, 2, sz, pContext))
#else
	if(!m_wndSplitter1.CreateStatic(this, 2, 2))
#endif // WCE_DYNAMIC_SPLITTER
		return FALSE;

	// *, 0 are static splitter windows
#if !defined(WCE_DYNAMIC_SPLITTER)
	for (int nRow = 0; nRow < 2; nRow++)
	{
		if (!m_wndSplitter1.CreateView(nRow, 0,	RUNTIME_CLASS(CStaticSplitView), CSize(100, 100), pContext))
			return FALSE;
	}
	// 0, 1 is also a static splitter window
	if (!m_wndSplitter1.CreateView(0, 1, RUNTIME_CLASS(CStaticSplitView), CSize(100, 100), pContext))
		return FALSE;

	if (!m_wndSplitter1.CreateView(1, 1, RUNTIME_CLASS(CStaticSplitView), CSize(100, 100), pContext))
		return FALSE;
#endif // WCE_DYNAMIC_SPLITTER
	return TRUE;
}									 

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
void CMainFrame::OnSharedNew()
{
	CStaticSplitDoc* pDoc = reinterpret_cast<CStaticSplitDoc*>(GetActiveView()->GetDocument());
	pDoc->EmptyDocument();
}
#endif // _WIN32_WCE_PSPC

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
void CMainFrame::OnMyFileOpen()
{
	CStaticSplitDoc* pDoc = reinterpret_cast<CStaticSplitDoc*>(GetActiveView()->GetDocument());
	pDoc->FillDocument();
}
#endif // _WIN32_WCE_PSPC
