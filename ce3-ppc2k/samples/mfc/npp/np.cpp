// np.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <winbase.h>
#include "np.h"
#include "npview.h"
#include "mainfrm.h"
#include "npdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotepadApp

BEGIN_MESSAGE_MAP(CNotepadApp, CWinApp)
	//{{AFX_MSG_MAP(CNotepadApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212))
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
#endif // _WIN32_WCE_PSPC
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CNotepadApp object

CNotepadApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNotepadApp initialization

BOOL CNotepadApp::InitInstance()
{
	// Register document templates
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	CCeDocListDocTemplate* pDocTemplate;
	pDocTemplate = new CCeDocListDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CNotepadDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CNotepadView),
		CString(_T("Text Files|*.txt||")));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	BOOL bResult = ProcessShellCommand(cmdInfo);
	if (!bResult)
	{
		pDocTemplate->ShowDocList();	
	
		// if there is no file in the doclist, we will create a new one.
		CCeDocList* pDL = pDocTemplate->m_pWndDocList;	
		if (pDL->GetItemCount() == 0) 
		{
			pDL->OnClose();
			OnFileNew();
		}
	}
#else
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CNotepadDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CNotepadView));
	AddDocTemplate(pDocTemplate);

	OnFileNew();
#endif

	return TRUE;
}

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

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CNotepadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadApp commands
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
void CNotepadApp::GetFileAndFolder(TCHAR* pszPath, TCHAR* pszFolder, TCHAR* pszFile)
{
	pszFolder[0] = '\0';
	pszFile[0] = '\0';

	lstrcpy(pszFolder, pszPath);

	int length = lstrlen(pszPath);

	for(int i = length - 1; i >= 0 && pszPath[i] != '\\'; i--)
		;

	pszFolder[i] = '\0';

	if(pszPath[i] == '\\')
		i++;

	lstrcpy(pszFile, pszPath + i);
}
#endif
