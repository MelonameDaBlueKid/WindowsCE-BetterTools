// Maths1Ctl.cpp : Implementation of the CMaths1Ctrl OLE control class.

#include "stdafx.h"
#include "Maths1.h"
#include "MathsCtl.h"
#include "MathsPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMaths1Ctrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMaths1Ctrl, COleControl)
	//{{AFX_MSG_MAP(CMaths1Ctrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMaths1Ctrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMaths1Ctrl)
	DISP_PROPERTY_NOTIFY(CMaths1Ctrl, "Opposite", m_bOpposite, OnOppositeChanged, VT_BOOL)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMaths1Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMaths1Ctrl, COleControl)
	//{{AFX_EVENT_MAP(CMaths1Ctrl)
	EVENT_CUSTOM("Outside", FireOutside, VTS_NONE)
	EVENT_CUSTOM("Inside", FireInside, VTS_XPOS_PIXELS  VTS_YPOS_PIXELS)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CMaths1Ctrl, 1)
	PROPPAGEID(CMaths1PropPage::guid)
END_PROPPAGEIDS(CMaths1Ctrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMaths1Ctrl, "MATHS.Maths1Ctrl.1",
	0x183CB003, 0xbeed, 0x11ce, 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMaths1Ctrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMaths1 =
		{ 0x183cb001, 0xbeed, 0x11ce, { 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf } };
const IID BASED_CODE IID_DMaths1Events =
		{ 0x183cb002, 0xbeed, 0x11ce, { 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMaths1OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMaths1Ctrl, IDS_Maths1, _dwMaths1OleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl::CMaths1CtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMaths1Ctrl

BOOL CMaths1Ctrl::CMaths1CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_Maths1,
			IDB_Maths1,
			FALSE,                      //  Not insertable
			_dwMaths1OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl::CMaths1Ctrl - Constructor

CMaths1Ctrl::CMaths1Ctrl()
{
	InitializeIIDs(&IID_DMaths1, &IID_DMaths1Events);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl::~CMaths1Ctrl - Destructor

CMaths1Ctrl::~CMaths1Ctrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl::OnDraw - Drawing function

#define X(x) (int)(xLeft + (x)*xScale/100)	// Scaling macros
#define Y(y) (int)(yTop + (y)*yScale/100)	// so scale is 0 - 100
#define CX(x) (int)((x)*xScale/100)
#define CY(y) (int)((y)*yScale/100)

void CMaths1Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	long xLeft = rcBounds.left;			// Use with scaling macros
	long yTop = rcBounds.top;	
	long xScale = rcBounds.Width();
	long yScale = rcBounds.Height();	

	int iPenWidth = max(CX(5), CY(5)); // Pen width based on control size
	CBrush brushBack;				   // Background brush
	CPen penFore(PS_SOLID, iPenWidth, TranslateColor(GetForeColor()));
	COLORREF crBack = TranslateColor(GetBackColor());	//Use BackColor
	brushBack.CreateSolidBrush(crBack);                 //Stock Property

	pdc->FillRect(rcBounds, &brushBack);				// Clear background		

	CPen* pPenSave = pdc->SelectObject(&penFore);

	pdc->MoveTo(xLeft + CX(5), yTop + (yScale / 2));
	pdc->LineTo(xLeft + xScale - CX(5), yTop + (yScale / 2));		// Draw a horizontol line

	if (!m_bOpposite)
	{
		pdc->MoveTo(xLeft + (xScale / 2), yTop + CY(5));
		pdc->LineTo(xLeft + (xScale / 2), yTop + yScale - CY(5));		// Draw a vertical line
	}

	pdc->SelectObject(pPenSave);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl::DoPropExchange - Persistence support

void CMaths1Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	PX_Bool(pPX, CString((LPCTSTR)IDS_OPPOSITE), m_bOpposite, FALSE);

}


/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl::OnResetState - Reset control to default state

void CMaths1Ctrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}

/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl message handlers

void CMaths1Ctrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rcBounds;
	GetClientRect(&rcBounds);

	long xLeft = rcBounds.left;			// Use with scaling macros
	long yTop = rcBounds.top;	
	long xScale = rcBounds.Width();
	long yScale = rcBounds.Height();	

	// Is point on horizontal line
	if ((point.y <= (yTop + (yScale / 2) + CY(5))) && (point.y >= (yTop + (yScale / 2) - CY(5))))
		FireInside((short)point.x, (short)point.y);
	else
	{
		if (!m_bOpposite)
		{
			// Is point on vertical line
			if ((point.x <= (xLeft + (xScale / 2) + CX(5))) && (point.x >= (xLeft + (xScale / 2) - CX(5))))
				FireInside((short)point.x, (short)point.y);
			else
				FireOutside();
		}
		else
			FireOutside();
	}
	
	COleControl::OnLButtonDown(nFlags, point);
}

//Simple Ellipse Hit-Testing
BOOL CMaths1Ctrl::InEllipse(const CPoint& pt,
	int x1, int y1, int x2, int y2)
{
	// Determine radii                       
	double a = (x2 - x1) / 2;
	double b = (y2 - y1) / 2;
	
	// Determine x, y
	double x = pt.x - (x1 + x2) / 2;
	double y = pt.y - (y1 + y2) / 2;
	
	// Apply ellipse formula
	return ((x * x) / (a * a) + (y * y) / (b * b) <= 1);
}

void CMaths1Ctrl::OnOppositeChanged() 
{
	InvalidateControl();
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog
{
// Construction
public:
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX_Maths1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CMaths1Ctrl::AboutBox - Display an "About" box to the user

void CMaths1Ctrl::AboutBox()
{
	CAboutDlg about;
	about.DoModal();
}
