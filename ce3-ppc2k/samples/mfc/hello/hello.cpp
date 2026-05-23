// hello.cpp : Defines the class behaviors for the application.
//           Hello is a simple program which consists of a main window
//           and an "About" dialog which can be invoked by a menu choice.
//           It is intended to serve as a starting-point for new
//           applications.
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
#include "resource.h"

#include "hello.h"
/////////////////////////////////////////////////////////////////////////////

// theApp:
// This code runs the application automatically
//
CTheApp helloApp;

/////////////////////////////////////////////////////////////////////////////

// CMainWindow constructor:
// Load the application frame window
//
CMainWindow::CMainWindow()
{
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	LoadFrame(IDR_MAINFRAME);
	m_bShowDoneButton = TRUE;
	ShowDoneButton(TRUE);
#else
	LoadFrame(IDR_MAINFRAME);
#endif

	// For MFCCE 2.0 and earlier, a command bar was created during
	// the CFrameWnd creation. For MFCCE 2.01 and later, a command bar 
	// is automatically created for you during the call to AddAdornments().
	AddAdornments(0);
}

// OnPaint:
// Function called whenever WCE sends the message WM_PAINT
// This routine draws the string "Hello, WCE!", loaded from IDS_STRING,
// in the center of the application window.
//
void CMainWindow::OnPaint()
{
	CRect rect;
	CString s;
	GetClientRect(rect);

	CPaintDC dc(this);
	dc.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	dc.SetBkMode(TRANSPARENT);
	s.LoadString(IDS_HELLO);
	dc.DrawText(s, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// CMainWindow message map:
// Associate messages with member functions.
//
// It is implied that the ON_WM_PAINT macro expects a member function
// "void OnPaint()".
//
// It is implied that members connected with the ON_COMMAND macro
// receive no arguments and are void of return type, e.g., "void OnAbout()".
//
BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
	//{{AFX_MSG_MAP( CMainWindow )
	ON_WM_PAINT()
	ON_COMMAND(ID_APP_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
#if defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	ON_COMMAND(IDM_SHOW_DONEBUTTON, OnShowDonebutton)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_DONEBUTTON, OnUpdateShowDonebutton)
	ON_COMMAND(IDOK, OnOK)
#endif //   // defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTheApp

// InitInstance:
// When any CTheApp object is created, this member function is automatically
// called.  Any data may be set up at this point.
//
// Also, the main window of the application should be created and shown here.
// Return TRUE if the initialization is successful.
//
BOOL CTheApp::InitInstance()
{
	TRACE0("CTheApp::InitInstance\n");
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
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
	enum { IDD = IDD_ABOUTBOX };
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

// OnAbout:
// Function called when the message WM_COMMAND, with an
// ID_APP_ABOUT code, is received by the CMainWindow class object.
// The message map below is responsible for this routing.
//
// We create a CDialog object using the "AboutBox" resource ,
// defined in hello.rc, and invoke it.
//
void CMainWindow::OnAbout()
{
	CAboutDlg about;
	about.DoModal();
}

#if defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
void CMainWindow::OnOK()
{
	// Call the handler of parent class for default action (close the main window)
	OnClose();
}

void CMainWindow::OnShowDonebutton() 
{
	if (m_bShowDoneButton)
	{
		m_bShowDoneButton = FALSE;
		ShowDoneButton(FALSE);
	}
	else
	{
		m_bShowDoneButton = TRUE;
		ShowDoneButton(TRUE);
	}
}

void CMainWindow::OnUpdateShowDonebutton(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowDoneButton);
}
#endif  // defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
