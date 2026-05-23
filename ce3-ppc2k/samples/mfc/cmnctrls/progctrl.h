// ProgCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgCtrlPage dialog
#ifndef INC_PROGCTRL_H
#define INC_PROGCTRL_H

class CProgCtrlPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CProgCtrlPage)

// Construction
public:
	CProgCtrlPage();
	~CProgCtrlPage();

// Dialog Data
	//{{AFX_DATA(CProgCtrlPage)
	enum { IDD = IDD_PROGCTRL };
	CProgressCtrl	m_Progress;
	UINT	m_uiStep;
	UINT	m_uiRangeFrom;
	UINT	m_uiRangeTo;
	UINT	m_uiPos;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProgCtrlPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProgCtrlPage)
	afx_msg void OnProgressStepit();
	afx_msg void OnFrom();
	afx_msg void OnTo();
	afx_msg void OnStep();
	afx_msg void OnSetpos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif
