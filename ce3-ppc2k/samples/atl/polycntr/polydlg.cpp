// PolyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PolyCntr.h"
#include "PolyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolyCntrDlg dialog

CPolyCntrDlg::CPolyCntrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPolyCntrDlg::IDD, pParent)
{
// MM not needed in wce dialogs:	ON_WM_
	//{{AFX_DATA_INIT(CPolyCntrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPolyCntrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPolyCntrDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_POLYCTL1, m_Polygon); 
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPolyCntrDlg, CDialog)
	//{{AFX_MSG_MAP(CPolyCntrDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolyCntrDlg message handlers

BOOL CPolyCntrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Workaround needed on 7258 version of MFC in ROM.  Needed so that events
	// fired from ATL are handled correctly.
	// Note: m_Polygon must already be attached to a window.
	ATLConnectSinks(&m_Polygon); 

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_EVENTSINK_MAP(CPolyCntrDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPolyContDlg)
	ON_EVENT(CPolyCntrDlg, IDC_POLYCTL1, 1 /* ClickIn */, OnClickInPolyctl1, VTS_I4 VTS_I4)
	ON_EVENT(CPolyCntrDlg, IDC_POLYCTL1, 2 /* ClickOut */, OnClickOutPolyctl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPolyCntrDlg::OnClickInPolyctl1(long x, long y) 
{
   m_Polygon.SetSides(m_Polygon.GetSides() + 1);
}

void CPolyCntrDlg::OnClickOutPolyctl1(long x, long y) 
{
	short nSides = m_Polygon.GetSides();
   if(nSides > 3)
	  m_Polygon.SetSides(nSides - 1);
}
