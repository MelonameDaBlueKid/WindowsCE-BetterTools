// SKETCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SKETCNTR.h"
#include "SKETCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSKETCNTRDlg dialog

CSKETCNTRDlg::CSKETCNTRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSKETCNTRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSKETCNTRDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSKETCNTRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSKETCNTRDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_SKETCH1, m_Sketch); 
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSKETCNTRDlg, CDialog)
	//{{AFX_MSG_MAP(CSKETCNTRDlg)
// MM not needed in wce dialogs:	ON_WM_PAINT()
// MM not needed in wce dialogs:	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ERASE, OnErase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSKETCNTRDlg message handlers

BOOL CSKETCNTRDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Workaround needed on 7258 version of MFC in ROM.  Needed so that events
	// fired from ATL are handled correctly.
	// Note: m_Sketch must already be attached to a window.
	ATLConnectSinks(&m_Sketch);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSKETCNTRDlg::OnErase() 
{
	// TODO: Add your control notification handler code here
	m_Sketch.Erase();
}
