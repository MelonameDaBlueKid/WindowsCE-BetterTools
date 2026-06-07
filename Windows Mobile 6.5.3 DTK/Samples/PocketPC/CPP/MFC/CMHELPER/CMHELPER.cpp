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

// CMHELPER.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CMHELPER.h"
#include "CMHELPERDlg.h"
#include "connection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCMHELPERApp

BEGIN_MESSAGE_MAP(CCMHELPERApp, CWinApp)
	//{{AFX_MSG_MAP(CCMHELPERApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCMHELPERApp construction

CCMHELPERApp::CCMHELPERApp()
	: CWinApp()
{
	// add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCMHELPERApp object

CCMHELPERApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCMHELPERApp initialization

BOOL CCMHELPERApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

    SHInitExtraControls();  // for WC_SIPPREF

	CCMHELPERDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
