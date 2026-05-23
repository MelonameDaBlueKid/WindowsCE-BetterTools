// CBARTEST.CPP
//
// Description:  This sample application demonstrates the use of the
// CCeCommandBar class, which has been added specifically for WCE
//
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

//////////////////////////////////////////////////////////////////////////
//  Declarations
//////////////////////////////////////////////////////////////////////////

class CMainWindow : public CFrameWnd
{
private:
	BOOL UpdateCommandBar(BOOL);
	void CheckMenuItems(CMenu*);

	BOOL m_bCombo;
	BOOL m_bToolbar;

#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300))
	BOOL m_bHelp;
	BOOL m_bOK;
#endif // _WIN32_WCE_PSPC


#if (_WIN32_WCE > 200)
	CCeCommandBar m_wndCommandBar;
#endif

public:
	CMainWindow();
	~CMainWindow() {};

	//{{AFX_MSG( CMainWindow )
	afx_msg void OnPaint();
	afx_msg void OnFileExit();
	afx_msg void OnAbout();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnOptionsCombo();
	afx_msg void OnOptionsToolbar();
#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300))
	afx_msg void OnOptionsHelp();
	afx_msg void OnOptionsOk();		
#endif // _WIN32_WCE_PSPC
	afx_msg void OnOK();
	afx_msg void OnHelpInfo(HELPINFO *pHelpInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CCmdBarApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		m_pMainWnd = new CMainWindow();
		m_pMainWnd->ShowWindow( m_nCmdShow );
		m_pMainWnd->UpdateWindow();
		return TRUE;
	}
} theApp;


CMainWindow::CMainWindow()
{
	m_bCombo = TRUE;
	m_bToolbar = TRUE;

#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300))
	m_bHelp = TRUE;
	m_bOK = TRUE;
#endif // _WIN32_WCE_PSPC

	LoadFrame(IDR_MAINFRAME);
	UpdateCommandBar(FALSE);
}

void CMainWindow::OnPaint()
{
	CRect rect;
	GetClientRect(rect);

	CPaintDC dc(this);
	dc.DrawText(CString((LPCTSTR)IDS_HELLO), rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}


#if (_WIN32_WCE > 200)

// MFCCE 2.01 and later uses CCeCommandBar, a derivitive of CToolBar, to implement command bars. 

BOOL CMainWindow::UpdateCommandBar(BOOL bReset)
{
	BOOL bOk = TRUE;

	if(m_wndCommandBar.m_hWnd == NULL)
		bOk = m_wndCommandBar.Create(this);

	if(bOk)
	{
		if(bReset)
			m_wndCommandBar.ResetCommandBar();

		CMenu *pMenu = m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME);
		CheckMenuItems(pMenu);

#if defined(_WIN32_WCE_PSPC) 
#if (_WIN32_WCE < 300)
		bOk = m_wndCommandBar.AddAdornments(m_bOK*CMDBAR_OK | m_bHelp*CMDBAR_HELP);
#endif
#else
		bOk = m_wndCommandBar.InsertSeparator(6);
#endif
	}

	if(m_bCombo && bOk)
	{
		CComboBox* pComboBox = m_wndCommandBar.InsertComboBox(100, 1001);
		bOk = (pComboBox != NULL);
		if(bOk)
		{
			pComboBox->AddString(CString((LPCTSTR)IDS_ONE));
			pComboBox->AddString(CString((LPCTSTR)IDS_TWO));
			pComboBox->AddString(CString((LPCTSTR)IDS_THREE));
			pComboBox->AddString(CString((LPCTSTR)IDS_FOUR));
			pComboBox->SetCurSel(0);
			bOk = m_wndCommandBar.InsertSeparator(6);
		}
	}

	if(m_bToolbar && bOk)
		bOk = m_wndCommandBar.LoadToolBar(IDR_MAINFRAME);

#if !defined(_WIN32_WCE_PSPC)
	if(bOk)
		bOk = m_wndCommandBar.AddAdornments(m_bOK*CMDBAR_OK | m_bHelp*CMDBAR_HELP);
#endif

	return bOk;
}

#else

// MFCCE 2.0 and earlier handled command bars through special members of CFrameWnd.
// Do not use this function for MFCCE 2.01 and later.

BOOL CMainWindow::UpdateCommandBar(BOOL bReset)
{
	// Note: At this point, CFrameWnd has a command bar	
	if(bReset)
	{
		ResetCommandBar(); // start over with the command bar
		m_hCommandBarMenu = InsertMenu(IDR_MAINFRAME);
	}
	CheckMenuItems(GetMenu());

	if(m_bCombo)
	{
		InsertComboBox( 100 );
		AddComboBoxString( CString((LPCTSTR)IDS_ONE) );
		AddComboBoxString( CString((LPCTSTR)IDS_TWO) );
		AddComboBoxString( CString((LPCTSTR)IDS_THREE) );
		AddComboBoxString( CString((LPCTSTR)IDS_FOUR) );
		SetComboCurSel(0);
	}

	if(m_bToolbar)
	{
		static TBBUTTON buttons[] = {
			{ 0,	0,				TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1},
			{ 0,    ID_EDIT_CUT,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  0},
			{ 1,    ID_EDIT_COPY,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  1},
			{ 2,    ID_EDIT_PASTE,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  2},
			{ 0,	0,				TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1},
			{ 3,	ID_EDIT_UNDO,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  3},
			{ 4,	ID_APP_ABOUT,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  3},
			{ 0,	0,				TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1}};
		InsertButtons( buttons, sizeof(buttons)/sizeof(TBBUTTON), IDR_MAINFRAME, 5 );
	}

	AddAdornments(m_bOK*CMDBAR_OK | m_bHelp*CMDBAR_HELP);

	return TRUE;
}

#endif // _WIN32_WCE <= 200


void CMainWindow::CheckMenuItems(CMenu* pMenu)
{
	pMenu->CheckMenuItem(ID_OPTIONS_COMBO,   (m_bCombo   ? MF_CHECKED : MF_UNCHECKED));
	pMenu->CheckMenuItem(ID_OPTIONS_TOOLBAR, (m_bToolbar ? MF_CHECKED : MF_UNCHECKED));
#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300))
	pMenu->CheckMenuItem(ID_OPTIONS_OK,      (m_bOK   ? MF_CHECKED : MF_UNCHECKED));
	pMenu->CheckMenuItem(ID_OPTIONS_HELP,    (m_bHelp ? MF_CHECKED : MF_UNCHECKED));
#endif // _WIN32_WCE_PSPC

}



BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
	//{{AFX_MSG_MAP( CMainWindow )
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_APP_ABOUT, OnAbout)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_OPTIONS_COMBO, OnOptionsCombo)
	ON_COMMAND(ID_OPTIONS_TOOLBAR, OnOptionsToolbar)
#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300))
	ON_COMMAND(ID_OPTIONS_HELP, OnOptionsHelp)
	ON_COMMAND(ID_OPTIONS_OK, OnOptionsOk)
#endif // _WIN32_WCE_PSPC
	ON_COMMAND(IDOK, OnOK)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMainWindow::OnFileExit()
{
	SendMessage(WM_CLOSE);
}

void CMainWindow::OnOptionsCombo() 
{
	m_bCombo ^= 1;
	UpdateCommandBar(TRUE); 
}

void CMainWindow::OnOptionsToolbar() 
{
	m_bToolbar ^= 1;
	UpdateCommandBar(TRUE); 
}

#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300))
void CMainWindow::OnOptionsHelp() 
{
	m_bHelp ^= 1;
	UpdateCommandBar(TRUE);
}

void CMainWindow::OnOptionsOk() 
{
	m_bOK ^= 1;
	UpdateCommandBar(TRUE); 
}
#endif // _WIN32_WCE_PSPC

void CMainWindow::OnEditCut()
{	
	// Display message box to confirm button pressed
	MessageBox(CString((LPCTSTR)ID_EDIT_CUT), CString((LPCTSTR)IDS_TOOLBAR));
}

void CMainWindow::OnEditCopy()
{
	// Display message box to confirm button pressed
	MessageBox(CString((LPCTSTR)ID_EDIT_COPY), CString((LPCTSTR)IDS_TOOLBAR));
}

void CMainWindow::OnEditPaste()
{
	// Display message box to confirm button pressed
	MessageBox(CString((LPCTSTR)ID_EDIT_PASTE), CString((LPCTSTR)IDS_TOOLBAR));
}

void CMainWindow::OnEditUndo()
{
	// Display message box to confirm button pressed
	MessageBox(CString((LPCTSTR)ID_EDIT_UNDO), CString((LPCTSTR)IDS_TOOLBAR));
}

void CMainWindow::OnOK()
{
	// Display message box to confirm button pressed
	MessageBox(CString((LPCTSTR)IDS_OK_ADORNMENT), CString((LPCTSTR)IDS_TOOLBAR));
}

void CMainWindow::OnHelpInfo(HELPINFO *pHelpInfo)
{
	// Display message box to confirm button pressed
	MessageBox(CString((LPCTSTR)IDS_HELP_ADORNMENT), CString((LPCTSTR)IDS_TOOLBAR));
}



//////////////////////////////////////////////////////////////////////////
//  About dialog
//////////////////////////////////////////////////////////////////////////

class CAboutDlg : public CDialog
{
public:
	CAboutDlg( UINT uiResourceID ) : CDialog( uiResourceID )	{}

	//{{AFX_MSG( CAboutDlg )
	afx_msg void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
// Implementation

	DECLARE_MESSAGE_MAP()
};


BEGIN_MESSAGE_MAP( CAboutDlg, CDialog )
	//{{AFX_MSG_MAP( CAboutDlg )
	ON_COMMAND(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMainWindow::OnAbout()
{
	CAboutDlg about(IDD_ABOUTBOX);
	about.DoModal();
}

void CAboutDlg::OnOK()
{
	CDialog::OnCancel();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();	
	return TRUE;  
}

