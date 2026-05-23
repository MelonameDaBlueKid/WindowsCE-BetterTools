// finddlg.h : interface of the CFindDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if (_WIN32_WCE <= 200) 
// Backward compatibility for H/PC 1.0 and 2.0
// For later versions, we use an improved implementation of the Find Dialog
// in MFCCE.

/////////////////////////////////////////////////////////////////////////////
// CFindDlg dialog

class CFindDlg : public CDialog
{
// Construction
public:
	CFindDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindDlg)
	enum { IDD = IDD_FIND };
	BOOL	m_bMatchCase;
	CString	m_szText;
	int m_nDirection;	// search direction 0=down, 1=up
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFindDlg)
	afx_msg void OnEditFindNext();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // _WIN32_WCE <= 200
