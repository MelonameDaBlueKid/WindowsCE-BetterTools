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

// Define a window class derived from CFrameWnd
class CMainWindow : public CFrameWnd
{
private:
	CPoint m_line[2], m_SaveLine[1000];
	int m_nPoint;
	BOOL bLBDown;
//	CMemoryState vv;

public:
	CMainWindow();

	//{{AFX_MSG( CMainWindow )
	afx_msg void OnFileNew();
	afx_msg void OnHelpAbout();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CAboutDlg : public CDialog
{
public:
	CAboutDlg( UINT uiResourceID ) : CDialog( uiResourceID )	{}

	//{{AFX_MSG( CAboutDlg )
	afx_msg void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Define an application class derived from CWinApp
class CEtchaApp : public CWinApp
{
public:
	virtual BOOL InitInstance();

	//{{AFX_MSG(CCtrldemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};				  

//////////////////////////////////////////////////////////////////////////
//  Implementation
//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CEtchaApp, CWinApp)
	//{{AFX_MSG_MAP(CEtchaApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_EXIT, CWinApp::OnAppExit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();	
	return TRUE; 
}

// Create the application's main window and perform initialization chores
BOOL CEtchaApp::InitInstance()
{
	m_pMainWnd = new CMainWindow();
	m_pMainWnd->ShowWindow( m_nCmdShow );
	m_pMainWnd->UpdateWindow();

	return (TRUE);
}

// CEtchaApp's contructor initializes and runs the app
CEtchaApp goDlgFRApp;

CMainWindow::CMainWindow()
{
	LoadFrame(IDR_MAINFRAME);

	// For MFCCE 2.0 and earlier, a command bar was created during
	// the CFrameWnd creation. For MFCCE 2.01 and later, a command bar 
	// is automatically created for you during the call to AddAdornments().
	AddAdornments(0);

	m_nPoint = 0;
}

// CMainWindow message map:
BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
	//{{AFX_MSG_MAP( CMainWindow )
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMainWindow::OnFileNew() 
{
	m_nPoint = 0;

	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);
}

void CMainWindow::OnHelpAbout() 
{
	CAboutDlg about(IDD_ABOUT);
	about.DoModal();
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	bLBDown = TRUE;

	m_line[0] = point;
	m_SaveLine[m_nPoint] = point;
	m_nPoint++;
	if (m_nPoint >= 1000)
	{
		m_nPoint = 0;
	}

	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Check that the LButton is down
	if (nFlags & bLBDown)
	{
		CDC* pDC = GetDC();
		m_line[1] = point;
		if (m_line[0] != m_line[1])
		{
			pDC->Polyline(m_line, 2);
			m_SaveLine[m_nPoint] = point;
			m_nPoint++;
			if (m_nPoint >= 1000)
			{
				m_nPoint = 0;
			}
		}
		m_line[0] = m_line[1];
		ReleaseDC(pDC);
	}
	
	CFrameWnd::OnMouseMove(nFlags, point);
}

BEGIN_MESSAGE_MAP( CAboutDlg, CDialog )
	//{{AFX_MSG_MAP( CAboutDlg )
	ON_COMMAND(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAboutDlg::OnOK()
{
	// Just wish to close dialog box, so treat as a cancel
	CDialog::OnCancel();
}



void CMainWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	int i = 0;
	CPoint pZero(0,0);
	while(i < m_nPoint)
	{
		int k = 0, m = i;
		while(m_SaveLine[i] != pZero && i < m_nPoint)
		{
			i++;
			k++;
		}
		i++;
		dc.Polyline(&(m_SaveLine[m]), k);
	}
	// Do not call CFrameWnd ::OnPaint() for painting messages
}

void CMainWindow::OnLButtonUp(UINT nFlags, CPoint point) 
{
	bLBDown = FALSE;

	CPoint pointTmp(0,0);

	m_SaveLine[m_nPoint] = pointTmp;
	m_nPoint++;
	if (m_nPoint >= 1000)
	{
		m_nPoint = 0;
	}

	CFrameWnd ::OnLButtonUp(nFlags, point);
}

