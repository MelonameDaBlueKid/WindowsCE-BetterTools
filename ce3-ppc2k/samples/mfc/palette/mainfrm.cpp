// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Palette.h"

#include "MainFrm.h"
#include "dibdoc.h"
#include "dibview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_FILE_PALETTE, OnFilePalette)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bPalette = TRUE; // initially use picture pallete
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

void CMainFrame::OnFilePalette() 
{
	CMenu* menu = GetMenu();
	if(menu)
	{
		menu->CheckMenuItem(ID_FILE_PALETTE, m_bPalette ? MF_UNCHECKED : MF_CHECKED);
		m_bPalette = !m_bPalette;
	}
	CString str;
	if (m_bPalette == MF_UNCHECKED)
		str.LoadString(IDS_UNCHECK);
	else
		str.LoadString(IDS_CHECK);
	AfxMessageBox((LPCTSTR)str);

	if (!::IsWindow(m_hWnd))
		return;

	CDibView* pView = (CDibView*)GetActiveView();
	if(pView) 
		pView->ShowPicture(m_bPalette);
}

