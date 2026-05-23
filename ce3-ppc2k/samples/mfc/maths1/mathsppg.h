// MathsPpg.h : Declaration of the CMaths1PropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMaths1PropPage : See MathsPpg.cpp.cpp for implementation.

class CMaths1PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMaths1PropPage)
	DECLARE_OLECREATE_EX(CMaths1PropPage)

// Constructor
public:
	CMaths1PropPage();

// Dialog Data
	//{{AFX_DATA(CMaths1PropPage)
	enum { IDD = IDD_PROPPAGE_Maths1 };
	BOOL m_bOpposite;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMaths1PropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
