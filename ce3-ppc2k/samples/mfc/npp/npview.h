// npview.h : interface of the CNotepadView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __INC_NPVIEW_H__
#define __INC_NPVIEW_H__

#if (_WIN32_WCE <= 200)
// This sample had its own find dialog under H/PC 2.0.  Newer OS's have an 
// improved find dialog box and this sample uses it instead.
class CFindDlg;		// forward declarations
#endif (_WIN32_WCE <= 200)
class CGotoDlg;		

#include "npdoc.h"

class CNotepadView : public CEditView
{
protected: // create from serialization only
	CNotepadView();
	DECLARE_DYNCREATE(CNotepadView)

// Attributes
public:
	CNotepadDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

public:
// Attributes
#if (_WIN32_WCE <= 200)
	CFindDlg* 	 m_pFindDialog;				// find dialog
#endif (_WIN32_WCE <= 200)
	CGotoDlg*	 m_pGotoDialog;				// goto line number dialog

#if (_WIN32_WCE <= 200)
public:
// Operations
	void OnViewFindNext(CString &s1);
#endif (_WIN32_WCE <= 200)

#if !defined(_WIN32_WCE_PSPC)
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
#endif

// Implementation
public:
	virtual ~CNotepadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void UpdateViewWindow();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNotepadView)
	afx_msg void OnEditGoto();
	afx_msg void OnUpdateEditGoto(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnEditCopy();
	//}}AFX_MSG
#if (_WIN32_WCE <= 200)
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnViewFindNext();
#endif (_WIN32_WCE <= 200)
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnContextMenu(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnEditCut();
	afx_msg void OnEditUndo();
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
#endif  // _WIN32_WCE_PSPC	
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in npview.cpp
inline CNotepadDoc* CNotepadView::GetDocument()
   { return (CNotepadDoc*)m_pDocument; }
#endif

#endif // __INC_NPVIEW_H__
/////////////////////////////////////////////////////////////////////////////
