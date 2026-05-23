// CheckDlg.h : header file
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
// CCheckDlg dialog

class CCheckDlg : public CDialog
{
// Construction
public:
	CCheckDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckDlg)
#if defined(_WIN32_WCE_PSPC)
	enum { IDD = IDD_CHECK_PSPC };
#else // _WIN32_WCE_PSPC
	enum { IDD = IDD_CHECK };
#endif // _WIN32_WCE_PSPC
	CString	m_strMemo;
	CString	m_strPayTo;
	CString	m_strCheckNo;
	CString	m_strDate;
	DWORD	m_dwCents;
	CString	m_strAmount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDlg)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetDollarsCentsText(DWORD dwCents);
protected:
	CString HundredsTensOnes(DWORD dwHundredsTensOnes);
	CString TensOnes(DWORD dwTensOnes);
	// Generated message map functions
	//{{AFX_MSG(CCheckDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
