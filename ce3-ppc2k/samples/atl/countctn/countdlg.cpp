// CountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CountCtn.h"
#include "CountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountCtnDlg dialog

CCountCtnDlg::CCountCtnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCountCtnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCountCtnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nMaxCounter = 10;
}

void CCountCtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCountCtnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COUNTER, m_Counter);
	DDX_Text(pDX, IDC_EDIT_MAXCOUNTER, m_nMaxCounter);
	DDV_MinMaxInt(pDX, m_nMaxCounter, 1, 15);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCountCtnDlg, CDialog)
	//{{AFX_MSG_MAP(CCountCtnDlg)
// MM not needed in wce dialogs:	ON_WM_PAINT()
// MM not needed in wce dialogs:	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_APPLY, OnSetMaxCounter)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountCtnDlg message handlers

BOOL CCountCtnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Workaround needed on 7258 version of MFC in ROM.  Needed so that events
	// fired from ATL are handled correctly.
	// Note: m_Counter must already be attached to a window.
	ATLConnectSinks(&m_Counter);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// Set initial value for counter
	m_Counter.SetMaxCounter(m_nMaxCounter);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCountCtnDlg::OnStart() 
{
 	m_Counter.StartCounting();
}
 
void CCountCtnDlg::OnSetMaxCounter() 
{
	if(UpdateData())
		m_Counter.SetMaxCounter(m_nMaxCounter);
}

void CCountCtnDlg::OnClose() 
{
	CDialog::OnClose();
}

