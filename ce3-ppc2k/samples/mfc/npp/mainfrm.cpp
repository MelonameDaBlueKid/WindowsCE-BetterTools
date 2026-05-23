// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "np.h"
#include "npview.h"
#include "mainfrm.h"
#include "npdoc.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	ON_NOTIFY(DLN_CE_CREATE, AFXCE_ID_DOCLIST, OnCreateDocList)
	ON_WM_DESTROY()
#endif // _WIN32_WCE_PSPC
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
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
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#if defined(_WIN32_WCE_PSPC) // MFC for Palm-Size PC
	m_ToolTipsTable[0] = MakeString(IDS_NEW);
	m_ToolTipsTable[1] = MakeString(IDS_FILE);
	m_ToolTipsTable[2] = MakeString(IDS_MHELP);
	m_ToolTipsTable[3] = MakeString(IDS_CUT);
	m_ToolTipsTable[4] = MakeString(IDS_COPY);
	m_ToolTipsTable[5] = MakeString(IDS_PASTE);

	m_wndCommandBar.m_bShowSharedNewButton = TRUE;
	if(!m_wndCommandBar.Create(this) ||
	   !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	   !m_wndCommandBar.AddAdornments() ||
	   !m_wndCommandBar.LoadToolBar(IDR_MAINFRAME) ||
	   !m_wndCommandBar.SendMessage(TB_SETTOOLTIPS, (WPARAM)(6), (LPARAM)(m_ToolTipsTable)))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}
#elif(_WIN32_WCE > 200) // MFC for Windows CE 2.01 and later
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
	if(!InsertButtons(g_arCBButtons, nNumButtons, IDR_MAINFRAME, 6) ||
	   !AddAdornments(0))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}
#endif

	return 0;
}

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
void CMainFrame::OnCreateDocList(DLNHDR* pNotifyStruct, LRESULT* result)
{
	CFrameWnd::OnCreateDocList(pNotifyStruct, result);
	CCeDocList* pDocList = (CCeDocList*)FromHandle(pNotifyStruct->nmhdr.hwndFrom);
	ASSERT_KINDOF(CCeDocList, pDocList);

	CCeCommandBar* pDocListCB = pDocList->GetCommandBar();
	ASSERT(pDocListCB != NULL);

	pDocListCB->InsertMenuBar(IDM_DOCLIST);
	pDocListCB->SendMessage(TB_SETTOOLTIPS, (WPARAM)(1), (LPARAM)(m_ToolTipsTable));
}

LPTSTR CMainFrame::MakeString(UINT stringID)
{
	TCHAR buffer[255];
	TCHAR* theString;

	::LoadString(AfxGetInstanceHandle(), stringID, buffer, 255);
	theString = new TCHAR[lstrlen(buffer) + 1];
	lstrcpy(theString, buffer);
	return theString;
}                        

void CMainFrame::OnDestroy()
{
	for(int i = 0; i < NUM_TOOL_TIPS; i++)
		delete m_ToolTipsTable[i];

	CFrameWnd::OnDestroy();
}
#endif // _WIN32_WCE_PSPC
