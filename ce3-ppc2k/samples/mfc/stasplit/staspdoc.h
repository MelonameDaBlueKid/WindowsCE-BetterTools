// staspdoc.h : interface of the CStaticSplitDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CStaticSplitDoc : public CDocument
{
protected: // create from serialization only
	CStaticSplitDoc();
	DECLARE_DYNCREATE(CStaticSplitDoc)

// Attributes
public:
    CStringArray m_arstrPoem;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticSplitDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticSplitDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	void FillDocument();
	void EmptyDocument();
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStaticSplitDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
