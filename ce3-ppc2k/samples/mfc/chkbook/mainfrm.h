// MainFrm.h : interface of the CMainFrame class
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

/////////////////////////////////////////////////////////////////////////////
#ifndef __INC_MAINFRM_H__
#define __INC_MAINFRM_H__

// Array for the toolbar buttons

#if (_WIN32_WCE <= 200)
static TBBUTTON g_arCBButtons[] = {
	{ 0,	0,					TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1},
	{ 0,    ID_EDIT_NEW_CHECK,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  0},
	{ 0,	0,					TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1},
	{ 1,    ID_EDIT_COMMIT,		TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  1},
	{ 0,	0,					TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1},
	{ 2,	ID_PREV_CHECK,		TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  2},
	{ 3,    ID_NEXT_CHECK,		TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  3},
	{ 0,	0,					TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1}
};
#endif

class CMainFrame : public CFrameWnd
{
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
#if (_WIN32_WCE > 200)
	CCeCommandBar m_wndCommandBar;
#endif
	HACCEL GetAccelTable() { return m_hAccelTable; } 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __INC_MAINFRM_H__
/////////////////////////////////////////////////////////////////////////////
