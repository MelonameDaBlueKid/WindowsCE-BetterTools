/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF

  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO

  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A

  PARTICULAR PURPOSE.

 

    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/
//
// INTERFACE.CPP
//
// Simple SMS Message Sender
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include "interface.h"
#include "resource.h"

// globals variable declarations
extern HINSTANCE	ghInstance;
extern HWND			ghDefault;
extern HWND			ghServer;
extern HWND			ghConfirmation;
extern HWND			ghMessage;
extern BOOL			gbUseDefault;
extern BOOL			gbSendConfirmation;

static const TCHAR	gszDefaultServer[] = TEXT("");

// ***************************************************************************
// Function Name: InitDialog
// 
// Purpose: Smartphone2002 Interface Initialization
//
// Arguments: Handle to the dialog to initialize
//
// Return Values:
//	TRUE if initialization was successful
//	FALSE if initialization failed
//
// Side Effects:
//	Sets gbUseDefault to TRUE and gbSendConfirmation to FALSE
//	Sets all the global HWNDs
//	Checks the Default checkbox
//	
// Description:
//	The purpose of this function is to abstract some of the interface 
//	initialization from the actual program functionality so that the program
//	can more easily be ported to other platforms.

BOOL InitDialog(const HWND hDlg)
{
    // Specify that the dialog box should stretch full screen
	SHINITDLGINFO shidi;
	ZeroMemory(&shidi, sizeof(shidi));
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
    shidi.hDlg = hDlg;
    
	// Set up the menu bar
	SHMENUBARINFO shmbi;
	ZeroMemory(&shmbi, sizeof(shmbi));
    shmbi.cbSize = sizeof(shmbi);
    shmbi.hwndParent = hDlg;
    shmbi.nToolBarId = IDR_HELLOSMS_APPMENUBAR;
    shmbi.hInstRes = ghInstance;

	// If we could not initialize the dialog box, return an error
	if(!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi)))
	{
		return FALSE;
	}

	// set the title bar
	VERIFY(SetWindowText(hDlg, TEXT("HelloSMS")));

	// get the server and checkbox handles
	VERIFY(ghDefault = GetDlgItem(hDlg, IDC_DEFAULT));
	VERIFY(ghConfirmation = GetDlgItem(hDlg, IDC_CONFIRMATION));
	VERIFY(ghServer = GetDlgItem(hDlg, IDC_SERVER));
	VERIFY(ghMessage = GetDlgItem(hDlg, IDC_MESSAGE));
	
	// set the default alternate server
	VERIFY(SetDlgItemText(hDlg, IDC_SERVER, gszDefaultServer));
	
	// check the default check box
	SendMessage(ghDefault, BM_SETCHECK, BST_CHECKED, 0);
	gbUseDefault = TRUE;

	// initialize gbSendConfirmation
	gbSendConfirmation = FALSE;

    // In order to make Back work properly, it's necessary to 
	// override it and then call the appropriate SH API
    (void)SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
					  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
								 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;
}