// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "wcedbtst.h"
#include "MainFrm.h"

// Array tbSTDButton contains relevant buttons of bitmap IDB_STD_SMALL_COLOR

static TBBUTTON g_arCBButtons[] = {
	{0,	ID_APP_ABOUT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1}
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
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
	
#if(_WIN32_WCE > 200)
	if(!m_wndCommandBar.Create(this) ||
	   !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
   	   !m_wndCommandBar.InsertSeparator(6) ||
       !m_wndCommandBar.LoadToolBar(IDR_MAINFRAME) ||
	   !m_wndCommandBar.AddAdornments())
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}
#else // MFC for Windows CE 1.0 and 2.0
	int nNumButtons = sizeof(g_arCBButtons)/sizeof(TBBUTTON);
	if(!InsertButtons(g_arCBButtons, nNumButtons, IDR_MAINFRAME, 1) ||
	   !AddAdornments(0))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}
#endif


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
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


