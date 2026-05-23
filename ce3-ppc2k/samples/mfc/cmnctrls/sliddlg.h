#if !defined(AFX_SLIDERCTRLDLG_H__35589A83_DFB7_11D1_84E1_00104B2FDE1D__INCLUDED_)
#define AFX_SLIDERCTRLDLG_H__35589A83_DFB7_11D1_84E1_00104B2FDE1D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SliderCtrlDlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSliderCtrlDlg dialog

class CSliderCtrlDlg : public CDialog
{
// Construction
public:
	CSliderCtrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSliderCtrlDlg)
	enum { IDD = IDD_SLIDERCTRLDLG };
	BOOL	m_bAutoticks;
	BOOL	m_bEnablesel;
	BOOL	m_bFixed;
	BOOL	m_bNothumb;
	BOOL	m_bNoticks;
	int		m_iOrientation;
	int		m_iTickpos;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	// Generated message map functions

	//{{AFX_MSG(CSliderCtrlDlg)
	afx_msg void OnControlChange();
	afx_msg void OnOK();
	//}}AFX_MSG

// Implementation
protected:

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDERCTRLDLG_H__35589A83_DFB7_11D1_84E1_00104B2FDE1D__INCLUDED_)
