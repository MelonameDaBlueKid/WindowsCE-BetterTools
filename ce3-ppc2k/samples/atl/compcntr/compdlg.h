// CompDlg.h : header file
//

#if !defined(AFX_COMPDLG_H__5E52C838_D880_11D1_9355_00600820B4FF__INCLUDED_)
#define AFX_COMPDLG_H__5E52C838_D880_11D1_9355_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCompCntrDlg dialog

class CCompCntrDlg : public CDialog
{
// Construction
public:
	CCompCntrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCompCntrDlg)
	enum { IDD = IDD_COMPCNTR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompCntrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCompCntrDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPDLG_H__5E52C838_D880_11D1_9355_00600820B4FF__INCLUDED_)
