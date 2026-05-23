// SKETCDlg.h : header file
//
//{{AFX_INCLUDES()
#include "sketch.h"
//}}AFX_INCLUDES

#if !defined(AFX_SKETCDLG_H__B1110A97_4029_11D1_9306_00600820B4FF__INCLUDED_)
#define AFX_SKETCDLG_H__B1110A97_4029_11D1_9306_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSKETCNTRDlg dialog

class CSKETCNTRDlg : public CDialog
{
// Construction
public:
	CSKETCNTRDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSKETCNTRDlg)
	enum { IDD = IDD_SKETCNTR_DIALOG };
	CSketcCtl m_Sketch;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSKETCNTRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSKETCNTRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnErase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKETCDLG_H__B1110A97_4029_11D1_9306_00600820B4FF__INCLUDED_)
