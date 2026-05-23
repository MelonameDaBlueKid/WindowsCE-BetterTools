// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__736ADA4C_9752_11D1_9327_00600820B4FF__INCLUDED_)
#define AFX_MAINFRM_H__736ADA4C_9752_11D1_9327_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if (_WIN32_WCE < 300)
#define GlobalFree LocalFree
#define GlobalAlloc LocalAlloc
#define GlobalSize LocalSize
#define GHND LMEM_FIXED | LMEM_ZEROINIT
#endif//_WIN32_WCE_PSPC

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	BOOL m_bPalette;
#if (_WIN32_WCE > 200)
	CCeCommandBar m_wndCommandBar;
#endif
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
	afx_msg void OnFilePalette();
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__736ADA4C_9752_11D1_9327_00600820B4FF__INCLUDED_)
