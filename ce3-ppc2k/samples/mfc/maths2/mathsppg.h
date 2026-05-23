// MathsPpg.h : Declaration of the CMaths2PropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMaths2PropPage : See MathsPpg.cpp.cpp for implementation.

class CMaths2PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMaths2PropPage)
	DECLARE_OLECREATE_EX(CMaths2PropPage)

// Constructor
public:
	CMaths2PropPage();

// Dialog Data
	//{{AFX_DATA(CMaths2PropPage)
	enum { IDD = IDD_PROPPAGE_Maths2 };
	BOOL m_bOpposite;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMaths2PropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
