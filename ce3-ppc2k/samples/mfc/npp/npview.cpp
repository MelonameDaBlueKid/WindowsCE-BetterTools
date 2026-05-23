// npview.cpp : implementation of the CNotepadView class
//

#include "stdafx.h"
#include "np.h"
#include "npview.h"
#include "mainfrm.h"
#include "npdoc.h"
#include "gotodlg.h"
#if (_WIN32_WCE <= 200)
// This sample had its own find dialog under H/PC 2.0.  Newer OS's have an 
// improved find dialog box and this sample uses it instead.
#include "finddlg.h"
#endif (_WIN32_WCE <= 200)
#include <afxcoll.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotepadView

IMPLEMENT_DYNCREATE(CNotepadView, CEditView)

BEGIN_MESSAGE_MAP(CNotepadView, CEditView)
	//{{AFX_MSG_MAP(CNotepadView)
	ON_COMMAND(ID_EDIT_GOTO, OnEditGoto)
	ON_UPDATE_COMMAND_UI(ID_EDIT_GOTO, OnUpdateEditGoto)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
#if (_WIN32_WCE <= 200)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_COMMAND(ID_VIEW_FIND_NEXT, OnViewFindNext)
#endif (_WIN32_WCE <= 200)
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(GN_CONTEXTMENU, OnContextMenu)
	ON_WM_DESTROY()
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
#endif // _WIN32_WCE_PSPC
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotepadView construction/destruction

CNotepadView::CNotepadView()
{
#if (_WIN32_WCE <= 200)
	m_pFindDialog = new CFindDlg;
#endif (_WIN32_WCE <= 200)
	m_pGotoDialog = new CGotoDlg;
}

CNotepadView::~CNotepadView()
{
	delete 	m_pGotoDialog;
#if (_WIN32_WCE <= 200)
	delete	m_pFindDialog;		
#endif (_WIN32_WCE <= 200)
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadView drawing

void CNotepadView::OnDraw(CDC* pDC)
{
	CNotepadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadView diagnostics

#ifdef _DEBUG
void CNotepadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNotepadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNotepadDoc* CNotepadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNotepadDoc)));
	return (CNotepadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNotepadView message handlers

void CNotepadView::OnEditGoto() 
{
	if(m_pGotoDialog->DoModal() != IDOK)
		return;

	if(m_pGotoDialog->m_nLineNum < 1)
	{
		CString s1;
		s1.LoadString(NPERROR_INVALID_LINENUM);
		AfxMessageBox(s1);
		return;
	}

	CEdit &edit = GetEditCtrl();
	int i = edit.LineFromChar();			// this is the current line the cursor is on
	int nLine = m_pGotoDialog->m_nLineNum;	// line number to go to

	if(nLine > (edit.GetLineCount()))
	{
		CString s1;
		
		s1.LoadString(NPERROR_NUM_TOO_BIG);
		AfxMessageBox(s1);
		return;
	}

	// move window and caret
	--nLine;					// edit control is zero based
	edit.LineScroll(nLine-i);	// new line number - the current line

	int idx;
	idx = edit.LineIndex(nLine);
	edit.SetSel(idx, idx);
}

void CNotepadView::OnUpdateEditGoto(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetWindowTextLength());
}

#if (_WIN32_WCE <= 200)
void CNotepadView::OnEditFind() 
{
	CString s1, s2;

	// add user selected text from CEditView to the buffer
	GetSelectedText(s1);
	s2 = m_pFindDialog->m_szText; // save old string if user cancels

	if(s1.GetLength()) 
		m_pFindDialog->m_szText = s1;

	if(m_pFindDialog->DoModal() != IDOK)
	{
		m_pFindDialog->m_szText = s2; // restore old string.  user selected cancel
		return;
	}
	
  	ASSERT(m_pFindDialog->m_szText.GetLength());

	// add it to the combo control on the toolbar
	if(m_pFindDialog->m_szText.GetLength())
		OnFindNext(m_pFindDialog->m_szText, m_pFindDialog->m_nDirection, m_pFindDialog->m_bMatchCase);
}

void CNotepadView::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetWindowTextLength());
}

void CNotepadView::OnViewFindNext(CString &s1)
{
	OnFindNext(s1, m_pFindDialog->m_nDirection, m_pFindDialog->m_bMatchCase);
}

void CNotepadView::OnViewFindNext() 
{
	CString s1;

	// if the user presses F3, see if there is a search pattern. if not, ask for one
	if (m_pFindDialog->m_szText.GetLength())
		OnFindNext(m_pFindDialog->m_szText, m_pFindDialog->m_nDirection, m_pFindDialog->m_bMatchCase);
	else 
		PostMessage(WM_COMMAND, ID_EDIT_FIND);
}
#endif (_WIN32_WCE <= 200)

BOOL CNotepadView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CNotepadView::OnEditPaste() 
{
	CWnd* pFocusWnd;

	// Note: this is the handler for the accelerator (CTRL+V).  Since the accelerator goes to the
	// frame, find who has the focus to determine where to paste to.

	pFocusWnd = GetFocus();
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	if(pFocusWnd == NULL)
		pFocusWnd = GetActiveWindow();
#endif
	ASSERT(pFocusWnd);

	CEditView::OnEditPaste();

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	UpdateViewWindow();
#endif // _WIN32_WCE_PSPC
}

void CNotepadView::OnEditCopy() 
{
	CWnd* pFocusWnd;
	// Note: this is the handler for the accelerator (CTRL+C).  Since the accelerator goes to the
	// frame, find who has the focus to determine where to copy from.

	pFocusWnd = GetFocus();
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	if(pFocusWnd == NULL)
		pFocusWnd = GetActiveWindow();
#endif
	ASSERT(pFocusWnd);

	// if the focus is in the combobox edit control, do the copy from the control
	GetEditCtrl().Copy();
}

#if !defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 210)
BOOL CNotepadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Disable margins
	pInfo->m_pPD->m_pd.dwFlags &= ~PD_MARGINS;
	pInfo->m_pPD->m_pd.dwFlags |= PD_DISABLEMARGINS | PD_DISABLEPRINTRANGE;

	return CEditView::OnPreparePrinting(pInfo);
}
#endif

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
BOOL CNotepadView::PreCreateWindow( CREATESTRUCT& cs )
{
	if(!CEditView::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_VSCROLL;
	cs.style &= ~WS_HSCROLL;
	cs.style &= ~ES_AUTOHSCROLL;

	m_dwDefaultStyle &= ~WS_VSCROLL;
	m_dwDefaultStyle &= ~WS_HSCROLL;
	m_dwDefaultStyle &= ~ES_AUTOHSCROLL;
	return TRUE;
}

int CNotepadView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	int iResult = CEditView::OnCreate(lpCreateStruct);

	if(iResult == 0)
		ShowDoneButton(TRUE);

	return iResult;
}

void CNotepadView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);

	if(nChar == VK_DELETE)
	{
		CEdit& edit = GetEditCtrl();
		TEXTMETRIC tm;
		CDC* pDC = edit.GetDC();
		pDC->GetTextMetrics(&tm);
		edit.ReleaseDC(pDC);
		CRect r;
		edit.GetRect(&r);
		int noOfVisibleLines = r.Height() / tm.tmHeight;

		if(edit.GetLineCount() <= noOfVisibleLines)
		{
			long lwStyle = ::GetWindowLong(edit.GetSafeHwnd(), GWL_STYLE);
			if(!(lwStyle & WS_VSCROLL))
				return;
			int nFirstVisible = edit.GetFirstVisibleLine();
		    edit.LineScroll(-nFirstVisible, 0);

			lwStyle &= ~WS_VSCROLL;
			::SetWindowLong(edit.GetSafeHwnd(), GWL_STYLE, lwStyle);
		}
	}
}

void CNotepadView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CEditView::OnChar(nChar, nRepCnt, nFlags);
	UpdateViewWindow();
}

void CNotepadView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CEditView::OnUpdate(pSender, lHint, pHint);
	UpdateViewWindow();
}

void CNotepadView::OnContextMenu(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMRGINFO* pnmhdr = reinterpret_cast <NMRGINFO*>(pNMHDR);
	CEdit &edit = GetEditCtrl();

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_TEXT_SELECTION_CM));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	POINT point = pnmhdr->ptAction;

	pPopup->TrackPopupMenu(TPM_RIGHTALIGN | TPM_TOPALIGN | TPM_NONOTIFY, point.x, point.y,
			pWndPopupOwner);
}

void CNotepadView::OnDestroy()
{
	CWnd*  pParentWnd = GetParent();
	if ( pParentWnd != NULL ) 
	{
		::SHSipPreference(pParentWnd->m_hWnd, SIP_FORCEDOWN);
		::SendMessage(pParentWnd->m_hWnd, WM_SETTINGCHANGE, -1, 0);
	}
	CEditView::OnDestroy();
}

void CNotepadView::UpdateViewWindow()
{
	CEdit& edit = GetEditCtrl();
	TEXTMETRIC tm;
	CDC* pDC = edit.GetDC();
	pDC->GetTextMetrics(&tm);
	edit.ReleaseDC(pDC);
	CRect r;
	edit.GetRect(&r);
	int noOfVisibleLines = r.Height() / tm.tmHeight;

	if(edit.GetLineCount() > noOfVisibleLines)
	{
		long lwStyle = ::GetWindowLong(edit.GetSafeHwnd(), GWL_STYLE);
		if(!(lwStyle & WS_VSCROLL))
		{
			lwStyle |= WS_VSCROLL;
			::SetWindowLong(edit.GetSafeHwnd(), GWL_STYLE, lwStyle);
		}

		// scroll the window to the cursor
		int nCaretLine = edit.LineFromChar();
		int nFirstVisible = edit.GetFirstVisibleLine();
		
		if(nFirstVisible + noOfVisibleLines <= nCaretLine)
		{
			HideCaret();
			edit.LineScroll(nCaretLine - nFirstVisible - noOfVisibleLines + 1);
			ShowCaret();
		}
		
		if(nFirstVisible > nCaretLine)
		{
			HideCaret();
			edit.LineScroll(nCaretLine - nFirstVisible);
			ShowCaret();
		}
	}
	else
	{
		long lwStyle = ::GetWindowLong(edit.GetSafeHwnd(), GWL_STYLE);
		if(!(lwStyle & WS_VSCROLL))
			return;
		int nFirstVisible = edit.GetFirstVisibleLine();
	    edit.LineScroll(-nFirstVisible, 0);
		lwStyle &= ~WS_VSCROLL;
		::SetWindowLong(edit.GetSafeHwnd(), GWL_STYLE, lwStyle);
	}
}

void CNotepadView::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CEditView::OnSettingChange(uFlags, lpszSection);
	UpdateViewWindow();
}

void CNotepadView::OnEditCut()
{
	CEditView::OnEditCut();
	UpdateViewWindow();
}

void CNotepadView::OnEditUndo()
{
	CEditView::OnEditUndo();
	UpdateViewWindow();
}
#endif

