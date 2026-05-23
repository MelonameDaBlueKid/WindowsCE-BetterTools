// PolyDlg.h : header file
//
//{{AFX_INCLUDES()
#include "polyctl.h"
//}}AFX_INCLUDES

#if !defined(AFX_POLYCNTRDLG_H__BD7BB4A7_4008_11D1_9306_00600820B4FF__INCLUDED_)
#define AFX_POLYCNTRDLG_H__BD7BB4A7_4008_11D1_9306_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPolyCntrDlg dialog

class CPolyCntrDlg : public CDialog
{
// Construction
public:
	CPolyCntrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPolyCntrDlg)
	enum { IDD = IDD_POLYCNTR_DIALOG };
	CPolyCtl	m_Polygon;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolyCntrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPolyCntrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickInPolyctl1(long x, long y);
	afx_msg void OnClickOutPolyctl1(long x, long y);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLYCNTRDLG_H__BD7BB4A7_4008_11D1_9306_00600820B4FF__INCLUDED_)
