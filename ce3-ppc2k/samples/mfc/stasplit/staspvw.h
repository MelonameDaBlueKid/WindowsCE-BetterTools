// staspvw.h : interface of the CStaticSplitView class
//
/////////////////////////////////////////////////////////////////////////////

class CStaticSplitView : public CEditView
{
protected: // create from serialization only
	CStaticSplitView();
	DECLARE_DYNCREATE(CStaticSplitView)

// Attributes
public:
	CStaticSplitDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticSplitView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticSplitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStaticSplitView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in staspvw.cpp
inline CStaticSplitDoc* CStaticSplitView::GetDocument()
   { return (CStaticSplitDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
