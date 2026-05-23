// MathsDlg.cpp : implementation file
//

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "Maths.h"
#include "MathsDlg.h"
#include "querydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();	
	return TRUE;  
}

/////////////////////////////////////////////////////////////////////////////
// CMathsDlg dialog

CMathsDlg::CMathsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMathsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMathsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMathsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMathsDlg)
	DDX_Control(pDX, IDC_OPPOSITE, m_ctlOpposite);
//	DDX_Control(pDX, IDC_MATHSCTRL, m_ctlMaths);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMathsDlg, CDialog)
	//{{AFX_MSG_MAP(CMathsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_CONTROL(BN_CLICKED, IDC_OPPOSITE, OnOpposite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMathsDlg Event Map

BEGIN_EVENTSINK_MAP(CMathsDlg, CDialog)
	ON_EVENT(CMathsDlg, IDC_MATHSCTRL, DISPID_CLICKIN, OnClickIn, VTS_XPOS_PIXELS VTS_YPOS_PIXELS)
	ON_EVENT(CMathsDlg, IDC_MATHSCTRL, DISPID_CLICKOUT, OnClickOut, VTS_NONE)
END_EVENTSINK_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMathsDlg message handlers

BOOL CMathsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Find out which control the user would like
	CQueryDlg dlgQuery(this);
	if (dlgQuery.DoModal() == TRUE)
	{
		m_ctlMaths.m_idControl = dlgQuery.GetChoice();
	}
	else
		EndDialog(IDCANCEL);


	// Determine control rect by size of dialog
	CRect rect;
	GetWindowRect(&rect);
	rect.top += 3 * (rect.Height() / 10);
	rect.bottom -= 3 * (rect.Height() / 10);
	rect.left += (rect.Width() / 10);
	rect.right -= (rect.Width() / 10);
	
	if (m_ctlMaths.Create(NULL, WS_VISIBLE, rect, this, IDC_MATHSCTRL))
	{
		m_ctlMaths.ShowWindow(SW_SHOW);
		m_ctlMaths.UpdateWindow();

		// Set the icon for this dialog.  The framework does this automatically
		//  when the application's main window is not a dialog
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon

		// Set the Value of the Opposite Check Button based upon the value of
		// the 'Opposite' property in the CMathsCtl OLE Control.
		m_ctlOpposite.SetCheck(m_ctlMaths.GetOpposite());
	}
	else
	{
		AfxMessageBox(IDS_CREATE_FAILED);
		PostQuitMessage(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMathsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMathsDlg::OnPaint() 
{
	CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMathsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMathsDlg::OnLButtonDblClk(UINT, CPoint)
{
	// Here the Container handles the WM_LBUTTONDBLCLK message where it can
	// do its own processing.  In this case, it sets the BackColor and
	// ForeColor properties in the control.  This handler is only called 
	// when double clicks occur OUTSIDE the control.  To handle double 
	// clicks inside the control, have the control fire the stock DblClk
	// event and then process it in the CMathsDlg EVENTSINK map.

	OLE_COLOR backClr = m_ctlMaths.GetBackColor();
	OLE_COLOR foreClr = m_ctlMaths.GetForeColor();

	// Reverse the Colors!
	m_ctlMaths.SetBackColor(foreClr);
	m_ctlMaths.SetForeColor(backClr);
}

/////////////////////////////////////////////////////////////////////////////
// CMathsDlg Command Handlers

void CMathsDlg::OnOpposite()
{
	m_ctlMaths.SetOpposite((m_ctlOpposite.GetCheck() != 0));
}


/////////////////////////////////////////////////////////////////////////////
// CMathsDlg Event Handlers

// These handlers are called when the user clicks with the mouse inside and
// outside the 'face' on the CMathsCtl OLE Control.

BOOL CMathsDlg::OnClickIn(OLE_XPOS_PIXELS, OLE_YPOS_PIXELS)
{
	OLE_COLOR backClr = m_ctlMaths.GetBackColor();
	OLE_COLOR foreClr = m_ctlMaths.GetForeColor();

	// Reverse the Colors!
	m_ctlMaths.SetBackColor(foreClr);
	m_ctlMaths.SetForeColor(backClr);

	return TRUE;	// We handled the event.  No need for futher processing
}

BOOL CMathsDlg::OnClickOut()
{
	CButton* pCheck = (CButton*)GetDlgItem(IDC_OPPOSITE);
	pCheck->SetCheck(pCheck->GetCheck() ? 0 : 1);
	m_ctlMaths.SetOpposite((m_ctlOpposite.GetCheck() != 0));
	return TRUE;	// We handled the event.  No need for futher processing
}
