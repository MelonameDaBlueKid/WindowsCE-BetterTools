//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF

  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO

  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A

  PARTICULAR PURPOSE.

  

    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/

// CMHELPERDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMHELPER.h"
#include "CMHELPERDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCMHELPERDlg dialog

CCMHELPERDlg::CCMHELPERDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCMHELPERDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCMHELPERDlg)
	m_Path = _T("");
	m_bProxy = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCMHELPERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCMHELPERDlg)
	DDX_Text(pDX, IDC_PATH, m_Path);
	DDX_Check(pDX, IDC_PROXY, m_bProxy);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCMHELPERDlg, CDialog)
	//{{AFX_MSG_MAP(CCMHELPERDlg)
	ON_BN_CLICKED(IDC_CHECK, OnCheckConnection)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCMHELPERDlg message handlers

BOOL CCMHELPERDlg::OnInitDialog()
{
    m_Path=TEXT("http://www.msn.com");
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// Add extra initialization here
    m_Connection.SetOutputWindow( GetDlgItem( IDC_OUTPUT )->m_hWnd );
    
	return TRUE;  // return TRUE  unless you set the focus to a control
}



// 
void CCMHELPERDlg::OnCheckConnection() 
{
    UpdateData();
    m_Connection.IsAvailable( m_Path, m_bProxy );
}

void CCMHELPERDlg::OnConnect() 
{
    UpdateData();
    m_Connection.AttemptConnect( m_Path, m_bProxy );
}

void CCMHELPERDlg::OnDisconnect() 
{
    m_Connection.HangupConnection();
}
