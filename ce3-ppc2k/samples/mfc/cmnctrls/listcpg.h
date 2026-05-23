// ListCtrlPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlPage dialog
#ifndef INC_LISTCTRLPAGE_H
#define INC_LISTCTRLPAGE_H

#include "mlistctl.h"
#include "notifwdw.h"

class CListCtrlPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CListCtrlPage)

// Construction
public:
	CListCtrlPage();
	~CListCtrlPage();

// Dialog Data
	//{{AFX_DATA(CListCtrlPage)
	enum { IDD = IDD_LISTCTRL };
	CMyListCtrl	m_listctrl;
	CString	m_cstrStatus;
	BOOL	m_bSingleSel;
	BOOL	m_bEditLabels;
	BOOL	m_bNoLabelWrap;
	BOOL	m_bNoColumnHeader;
	BOOL	m_bNoSortHeader;
	CString	m_cstrViewMode;
	CString	m_cstrSort;
	CString	m_cstrAlignMode;
	//}}AFX_DATA


	CImageList	*m_pimagelist;
	CImageList	*m_pimagelistSmall;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog(void);
	//}}AFX_VIRTUAL

// Implementation
protected:

//	void ChangeListCtrlStyle(long lStyle, BOOL bSetBit);
	void FillListCtrl(void);
//	void RenewListCtrl(long lStyle, BOOL bSetBit);
	void OnButtonUp(CPoint point);
	void OnButtonDown(CPoint point);

public:

	// Generated message map functions
	//{{AFX_MSG(CListCtrlPage)
    afx_msg void ShowNotification(LPNMHDR pnmhdr, LRESULT *plResult);
	afx_msg void OnMore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetListControlStyle();
};


#endif
