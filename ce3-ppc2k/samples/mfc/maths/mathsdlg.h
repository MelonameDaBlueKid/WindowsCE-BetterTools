// Mathsdg.h : header file
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
// Definitions for CMathsCtl Event DISPIDs (used in the EVENTSINK map)

#define DISPID_CLICKOUT	1L
#define DISPID_CLICKIN	2L


/////////////////////////////////////////////////////////////////////////////
// CMathsDlg dialog
//{{AFX_INCLUDES()
#include "mathsctl.h"
//}}AFX_INCLUDES

class CMathsDlg : public CDialog
{
// Construction
public:
	CMathsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMathsDlg)
	enum { IDD = IDD_MATHS_DIALOG };
	CButton	m_ctlOpposite;
	CMathsCtl	m_ctlMaths;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMathsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDblClk(UINT, CPoint);
	afx_msg void OnOpposite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Event Handler functions
	afx_msg BOOL OnClickIn(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	afx_msg BOOL OnClickOut();
	DECLARE_EVENTSINK_MAP()
};
