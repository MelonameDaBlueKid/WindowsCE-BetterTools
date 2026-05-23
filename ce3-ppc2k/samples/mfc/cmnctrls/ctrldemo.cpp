// ctrldemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ctrldemo.h"

#include "propsht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtrldemoApp

BEGIN_MESSAGE_MAP(CCtrldemoApp, CWinApp)
	//{{AFX_MSG_MAP(CCtrldemoApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CCtrldemoApp object

CCtrldemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCtrldemoApp initialization

BOOL CCtrldemoApp::InitInstance()
{
	CString str;
	str.LoadString(IDS_COMCTRLSAM);
	CAllControlsSheet	allcontrolssheet((LPCTSTR)str);
	m_pMainWnd = &allcontrolssheet;
	allcontrolssheet.DoModal();
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CCtrldemoApp commands

