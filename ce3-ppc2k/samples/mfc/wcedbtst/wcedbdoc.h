// WCE_DatabaseDoc.h : interface of the CWCEDBDoc class
//
/////////////////////////////////////////////////////////////////////////////


class CWCEDBDoc : public CDocument
{
protected: // create from serialization only
	CWCEDBDoc();
	DECLARE_DYNCREATE(CWCEDBDoc)

// Attributes
public:
	CStringArray Output;

// Operations
public:
	BOOL GeneratePeopleDB();
	BOOL PrintPeopleDB(CCeDBDatabase*);
	void PrintIndex(CCeDBDatabase*); 
	void PrintPerson(CCeDBRecord*); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWCEDBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWCEDBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWCEDBDoc)
	afx_msg void OnFileBasicTests();
	afx_msg void OnFileClear();
	afx_msg void OnFileEnum();
	afx_msg void OnFileSortTest();
	afx_msg void OnFileSeekTest();
	afx_msg void OnFileDeletionTest();
	afx_msg void OnFileModifyTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
