// HttpDlg.h : header file
//

#if !defined(AFX_HTTPDLG_H__E9CAE8B8_9908_11D1_9327_00600820B4FF__INCLUDED_)
#define AFX_HTTPDLG_H__E9CAE8B8_9908_11D1_9327_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////////////////////////////
// CHttpDlg dialog

class CHttpDlg : public CDialog
{
// Construction
public:
	CHttpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHttpDlg)
#if defined(_WIN32_WCE_PSPC)
	enum { IDD = IDD_HTTP_DIALOG_PSPC };
#else
	enum { IDD = IDD_HTTP_DIALOG };
#endif		
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	int DownloadPage(LPTSTR szAddress);

	// Generated message map functions
	//{{AFX_MSG(CHttpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDownloadpage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTTPDLG_H__E9CAE8B8_9908_11D1_9327_00600820B4FF__INCLUDED_)
