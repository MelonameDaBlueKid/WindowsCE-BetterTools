// helloapp.cpp : Minimal MFC Windows app.
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

#include <afxwin.h>
#include "resource.h"

// Define a window class derived from CFrameWnd
class CHelloWindow : public CFrameWnd
{
public:
	// N.B. The caption is not shown
	CHelloWindow()
	{ 
		Create(NULL, CString((LPCTSTR)AFX_IDS_APP_TITLE), WS_VISIBLE, rectDefault); 

		// For MFCCE 2.0 and earlier, a command bar was created during
		// the CFrameWnd creation. For MFCCE 2.01 and later, a command bar 
		// is automatically created for you during the call to AddAdornments().
		AddAdornments(0); 

		InvalidateRect(NULL,TRUE);
#if defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
		ShowDoneButton(TRUE);
	}
	//{{AFX_MSG( CHelloWindow )
	void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
#else  // _WIN32_WCE_PSPC
	}
#endif // _WIN32_WCE_PSPC
};

// Define an application class derived from CWinApp
class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

// Construct the CHelloApp's m_pMainWnd data member
BOOL CHelloApp::InitInstance()
{
	m_pMainWnd = new CHelloWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// HelloApp's constructor initializes and runs the app
CHelloApp HelloApp;

#if defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
BEGIN_MESSAGE_MAP( CHelloWindow, CFrameWnd )
	//{{AFX_MSG_MAP( CHelloWindow )
	ON_COMMAND(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif // _WIN32_WCE_PSPC

#if defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
void CHelloWindow::OnOK()
{
	CFrameWnd::OnClose();
}
#endif  // _WIN32_WCE_PSPC