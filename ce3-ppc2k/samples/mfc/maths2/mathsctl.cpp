// MathsCtl.cpp : Implementation of the CMaths2Ctrl OLE control class.

#include "stdafx.h"
#include "Maths2.h"
#include "MathsCtl.h"
#include "MathsPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMaths2Ctrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMaths2Ctrl, COleControl)
	//{{AFX_MSG_MAP(CMaths2Ctrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMaths2Ctrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMaths2Ctrl)
	DISP_PROPERTY_NOTIFY(CMaths2Ctrl, "Opposite", m_bOpposite, OnOppositeChanged, VT_BOOL)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMaths2Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMaths2Ctrl, COleControl)
	//{{AFX_EVENT_MAP(CMaths2Ctrl)
	EVENT_CUSTOM("Outside", FireOutside, VTS_NONE)
	EVENT_CUSTOM("Inside", FireInside, VTS_XPOS_PIXELS  VTS_YPOS_PIXELS)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CMaths2Ctrl, 1)
	PROPPAGEID(CMaths2PropPage::guid)
END_PROPPAGEIDS(CMaths2Ctrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMaths2Ctrl, "MATHS.Maths2Ctrl.1",
	0x181CB003, 0xbeed, 0x11ce, 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMaths2Ctrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMaths2 =
		{ 0x181cb001, 0xbeed, 0x11ce, { 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf } };
const IID BASED_CODE IID_DMaths2Events =
		{ 0x181cb002, 0xbeed, 0x11ce, { 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMaths2OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMaths2Ctrl, IDS_Maths2, _dwMaths2OleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMaths2Ctrl::CMaths2CtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMaths2Ctrl

BOOL CMaths2Ctrl::CMaths2CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_Maths2,
			IDB_Maths2,
			FALSE,                      //  Not insertable
			_dwMaths2OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths2Ctrl::CMaths2Ctrl - Constructor

CMaths2Ctrl::CMaths2Ctrl()
{
	InitializeIIDs(&IID_DMaths2, &IID_DMaths2Events);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths2Ctrl::~CMaths2Ctrl - Destructor

CMaths2Ctrl::~CMaths2Ctrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CMaths2Ctrl::OnDraw - Drawing function

#define X(x) (int)(xLeft + (x)*xScale/100)	// Scaling macros
#define Y(y) (int)(yTop + (y)*yScale/100)	// so scale is 0 - 100
#define CX(x) (int)((x)*xScale/100)
#define CY(y) (int)((y)*yScale/100)

void CMaths2Ctrl::OnDraw(
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

	// Draw a / sign
	pdc->MoveTo(xLeft + xScale - CX(10), yTop + CY(10));
	pdc->LineTo(xLeft + CX(10), yTop + yScale - CY(10));		// Draw a line from top right to bottom left
	
	if (!m_bOpposite)
	{
		// Draw a X sign
		pdc->MoveTo(xLeft + CX(10), yTop + CY(10));
		pdc->LineTo(xLeft + xScale - CX(10), yTop + yScale - CY(10));		// Draw a line from top left to bottom right
	}

	pdc->SelectObject(pPenSave);
}


/////////////////////////////////////////////////////////////////////////////
// CMaths2Ctrl::DoPropExchange - Persistence support

void CMaths2Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	PX_Bool(pPX, CString((LPCTSTR)IDS_OPPOSITE), m_bOpposite, FALSE);

}


/////////////////////////////////////////////////////////////////////////////
// CMaths2Ctrl::OnResetState - Reset control to default state

void CMaths2Ctrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}

/////////////////////////////////////////////////////////////////////////////
// CMaths2Ctrl message handlers

void CMaths2Ctrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rcBounds;
	GetClientRect(&rcBounds);

	long xLeft = rcBounds.left;			// Use with scaling macros
	long yTop = rcBounds.top;	
	long xScale = rcBounds.Width();
	long yScale = rcBounds.Height();	
	float gradient = (float)yScale / (float)xScale;

	// Is point on bottom-left to top-right line
	if ((point.y >= (yTop + yScale - (gradient * point.x) - CY(5))) && (point.y <= (yTop + yScale - (gradient * point.x) + CY(5))))
		FireInside((short)point.x, (short)point.y);
	else
	{
		if (!m_bOpposite)
		{
			// Is point on top-left to bottom-right line
			if ((point.y >= yTop + (gradient * point.x) - CY(5)) && (point.y <= yTop + (gradient * point.x) + CY(5)))
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
BOOL CMaths2Ctrl::InEllipse(const CPoint& pt,
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

void CMaths2Ctrl::OnOppositeChanged() 
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
	enum { IDD = IDD_ABOUTBOX_Maths2 };
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
// CMaths2Ctrl::AboutBox - Display an "About" box to the user

void CMaths2Ctrl::AboutBox()
{
	CAboutDlg about;
	about.DoModal();
}
