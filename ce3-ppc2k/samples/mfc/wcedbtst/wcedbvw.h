// WCE_DatabaseView.h : interface of the CWCEDBView class
//
/////////////////////////////////////////////////////////////////////////////

class CWCEDBView : public CScrollView
{
protected: // create from serialization only
	CWCEDBView();
	DECLARE_DYNCREATE(CWCEDBView)

// Attributes
public:
	CWCEDBDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWCEDBView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWCEDBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWCEDBView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WCE_DatabaseView.cpp
inline CWCEDBDoc* CWCEDBView::GetDocument()
   { return (CWCEDBDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
