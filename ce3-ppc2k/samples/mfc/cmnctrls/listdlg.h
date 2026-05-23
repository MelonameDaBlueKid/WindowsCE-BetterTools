#if !defined(AFX_LISTCTRLDLG_H__EAF1BE93_DDEF_11D1_84E0_00104B2FDE1D__INCLUDED_)
#define AFX_LISTCTRLDLG_H__EAF1BE93_DDEF_11D1_84E0_00104B2FDE1D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListCtrlDlg.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg dialog

class CListCtrlDlg : public CDialog
{
// Construction
public:
	CListCtrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListCtrlDlg)
	enum { IDD = IDD_LISTCTRLDLG };
	BOOL	m_bSingleSel;
	BOOL	m_bEditLabels;
	BOOL	m_bNoLabelWrap;
	BOOL	m_bNoSortHeader;
	BOOL	m_bNoColumnHeader;
	CString	m_cstrViewMode;
	CString	m_cstrSort;
	CString	m_cstrAlignMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListCtrlDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnControlChange();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLDLG_H__EAF1BE93_DDEF_11D1_84E0_00104B2FDE1D__INCLUDED_)
