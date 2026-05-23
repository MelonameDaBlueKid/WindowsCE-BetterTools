// SpinCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpinCtrlPage dialog
#ifndef INC_SPINCTRL_H
#define INC_SPINCTRL_H

class CSpinCtrlPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSpinCtrlPage)

// Construction
public:
	CSpinCtrlPage();
	~CSpinCtrlPage();

// Dialog Data
	//{{AFX_DATA(CSpinCtrlPage)
	enum { IDD = IDD_SPINCTRL };
	int		m_iAlignment;
	int		m_uiRangeFrom;
	int		m_iOrientation;
	int		m_uiRangeTo;
	BOOL	m_bWrap;
	//}}AFX_DATA

	CSpinButtonCtrl	m_Spin;
	CRect			m_EditRect;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSpinCtrlPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CreateSpinCtrl();
	void ChangeCtrlStyle();

	// Generated message map functions
	//{{AFX_MSG(CSpinCtrlPage)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeSpinAlignment();
	afx_msg void OnKillfocusSpinFrom();
	afx_msg void OnKillfocusSpinEdit();
	afx_msg void OnSelchangeSpinOrientation();
	afx_msg void OnKillfocusSpinTo();
	afx_msg void OnSpinWrap();
	afx_msg void OnChangeSpinEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif
