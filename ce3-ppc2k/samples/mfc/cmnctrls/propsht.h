// AllControlsSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAllControlsSheet

#include "listcpg.h"
#include "treecpg.h"
#include "spinctrl.h"
#include "slidctrl.h"
#include "progctrl.h"

class CAllControlsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAllControlsSheet)

// Construction
public:
	CAllControlsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAllControlsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

	CListCtrlPage		m_listctrlpage;
	CTreeCtrlPage		m_treectrlpage;
	CProgCtrlPage		m_progctrlpage;
	CSliderCtrlPage		m_sliderctrlpage;
	CSpinCtrlPage		m_spinctrlpage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllControlsSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAllControlsSheet();
	virtual BOOL OnInitDialog();

	// Generated message map functions
protected:

	HICON m_hIcon;

	//{{AFX_MSG(CAllControlsSheet)
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
