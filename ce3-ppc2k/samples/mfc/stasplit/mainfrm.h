// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CNestedSplitterWnd : public CSplitterWnd
{
protected:
	virtual BOOL SplitRow(int);
	virtual BOOL SplitColumn(int);
};

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd		m_wndSplitter1;	// Static splitter
	CNestedSplitterWnd	m_wndSplitter2;	// Nested dynamic splitter
#if (_WIN32_WCE > 200)
	CCeCommandBar m_wndCommandBar;
#endif

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	afx_msg void OnSharedNew();
	afx_msg void OnMyFileOpen();
#endif // _WIN32_WCE_PSPC	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
