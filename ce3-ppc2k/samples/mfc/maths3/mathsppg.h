// MathsPpg.h : Declaration of the CMaths3PropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMaths3PropPage : See  MathsPpg.cpp.cpp for implementation.

class CMaths3PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMaths3PropPage)
	DECLARE_OLECREATE_EX(CMaths3PropPage)

// Constructor
public:
	CMaths3PropPage();

// Dialog Data
	//{{AFX_DATA(CMaths3PropPage)
	enum { IDD = IDD_PROPPAGE_Maths3 };
	BOOL m_bOpposite;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMaths3PropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
