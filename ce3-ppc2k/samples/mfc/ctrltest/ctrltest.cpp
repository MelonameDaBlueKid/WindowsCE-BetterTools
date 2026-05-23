// ctrltest.cpp : Dialogs and Controls test applet
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
#include "ctrltest.h"

/////////////////////////////////////////////////////////////////////////////
// Main Window

// The OnTest routines are in the source files containing the particular
// dialog that they are working with.  For example OnTestDerivedEdit is
// in file dertest.cpp

BEGIN_MESSAGE_MAP(CTestWindow, CFrameWnd)
	//{{AFX_MSG_MAP(CTestWindow)
	ON_COMMAND(IDM_TEST_DERIVED_EDIT, OnTestDerivedEdit)
	ON_COMMAND(IDM_TEST_SUB_EDIT, OnTestSubclassedEdit)
	ON_COMMAND(IDM_TEST_BITMAP_BUTTON1, OnTestBitmapButton1)
	ON_COMMAND(IDM_TEST_BITMAP_BUTTON2, OnTestBitmapButton2)
	ON_COMMAND(IDM_TEST_BITMAP_BUTTON3, OnTestBitmapButton3)
	ON_COMMAND(IDM_TEST_SPIN_EDIT, OnTestSpinEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
	//{{AFX_MSG_MAP(CTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTestApp theTestApp;

BOOL CTestApp::InitInstance()
{
	CTestWindow* pMainWnd = new CTestWindow;
	if (!pMainWnd->Create(NULL, CString((LPCTSTR)AFX_IDS_APP_TITLE),
		WS_VISIBLE, CFrameWnd::rectDefault, NULL,
		MAKEINTRESOURCE(AFX_IDI_STD_FRAME)/*menu*/))
		return FALSE;

	// Add 'X' adornment to the command bar
	// For MFCCE 2.0 and earlier, a command bar was created during
	// the CFrameWnd creation. For MFCCE 2.01 and later, a command bar 
	// is automatically created for you during the call to AddAdornments().
	pMainWnd->AddAdornments(0);

	pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd = pMainWnd;      // store in CWinApp member
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
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
	return TRUE;  
}

void CTestApp::OnAppAbout()
{
	CAboutDlg about;
	about.DoModal();
}
