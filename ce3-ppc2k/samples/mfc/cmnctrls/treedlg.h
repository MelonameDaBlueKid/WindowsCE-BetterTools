#if !defined(AFX_TREEDLG_H__0F9DC951_E073_11D1_84E1_00104B2FDE1D__INCLUDED_)
#define AFX_TREEDLG_H__0F9DC951_E073_11D1_84E1_00104B2FDE1D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeDlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDlg dialog

class CTreeCtrlDlg : public CDialog
{
// Construction
public:
	CTreeCtrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTreeCtrlDlg)
	enum { IDD = IDD_TREECTRLDLG };
	BOOL	m_bEditLabels;
	BOOL	m_bHasButtons;
	BOOL	m_bHasLines;
	BOOL	m_bLinesAtRoot;
	BOOL	m_bDisableDragDrop;
	BOOL	m_bShowSelAlways;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTreeCtrlDlg)
	afx_msg void OnControlChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEDLG_H__0F9DC951_E073_11D1_84E1_00104B2FDE1D__INCLUDED_)
