// CountDlg.h : header file
//
//{{AFX_INCLUDES()
#include "counter.h"
//}}AFX_INCLUDES

#if !defined(AFX_COUNTDLG_H__1113B1B8_41BA_11D1_9307_00600820B4FF__INCLUDED_)
#define AFX_COUNTDLG_H__1113B1B8_41BA_11D1_9307_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCountctnDlg dialog

class CCountCtnDlg : public CDialog
{
// Construction
public:
	CCountCtnDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCountctnDlg)
	enum { IDD = IDD_COUNTCTN_DIALOG };
	CCounter m_Counter;
	int		m_nMaxCounter;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountctnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCountCtnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnStart();
	afx_msg void OnSetMaxCounter();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTDLG_H__1113B1B8_41BA_11D1_9307_00600820B4FF__INCLUDED_)
