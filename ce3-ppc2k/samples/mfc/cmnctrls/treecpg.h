// TreeCtrlPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlPage dialog
#ifndef INC_TRCPAGE_H
#define INC_TRCPAGE_H

#include "mlistctl.h"
#include "mtreectl.h"
#include "notifwdw.h"

class CTreeCtrlPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTreeCtrlPage)

// Construction
public:
	CTreeCtrlPage();
	~CTreeCtrlPage();

// Dialog Data
	//{{AFX_DATA(CTreeCtrlPage)
	enum { IDD = IDD_TREECTRL };
	CNotifyShowCase	m_notifshowcase;
	CMyTreeCtrl	m_mytreectrl;
	BOOL	m_bDisableDragDrop;
	BOOL	m_bHasButtons;
	BOOL	m_bHasLines;
	BOOL	m_bLinesAtRoot;
	BOOL	m_bEditLabels;
	BOOL	m_bShowSelAlways;
	CString	m_cstrStatus;
	//}}AFX_DATA


	HTREEITEM	m_rghItem[12];
	HTREEITEM	m_hitemDrag;
	HTREEITEM	m_hitemDrop;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	// Generated message map functions
	//{{AFX_MSG(CTreeCtrlPage)
	afx_msg void ShowNotification(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void OnMore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetTreeCtrlStyle();
};

#endif
