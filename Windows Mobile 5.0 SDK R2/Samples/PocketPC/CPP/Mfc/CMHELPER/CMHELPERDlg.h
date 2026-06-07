// CMHELPERDlg.h : header file
//

#if !defined(AFX_CMHELPERDLG_H__ED1E753E_F339_4C09_8134_CA0F083BCA71__INCLUDED_)
#define AFX_CMHELPERDLG_H__ED1E753E_F339_4C09_8134_CA0F083BCA71__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectionState.h"

/////////////////////////////////////////////////////////////////////////////
// CCMHELPERDlg dialog

class CCMHELPERDlg : public CDialog
{
// Construction
public:
	CCMHELPERDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCMHELPERDlg)
	enum { IDD = IDD_CMHELPER_DIALOG };
	CString	m_Path;
	BOOL	m_bProxy;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCMHELPERDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    CConnectionState m_Connection;

	// Generated message map functions
	//{{AFX_MSG(CCMHELPERDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckConnection();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMHELPERDLG_H__ED1E753E_F339_4C09_8134_CA0F083BCA71__INCLUDED_)
