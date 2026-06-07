//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
// SDKBack.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include <aygshell.h>
#include <tpcshell.h>
#include <winuserm.h>
#include "resource.h"

HINSTANCE g_hInst = NULL;  // Local copy of hInstance

TCHAR tszAppName[] = TEXT("BACKSDK");
TCHAR tszTitle[]   = TEXT("Back SDK Sample");

TCHAR tszBackText[] = TEXT("The Back button was pressed.\n\nYour device will return to the previous application.");
TCHAR tszBackCaption[] = TEXT("BACK Pressed");


//
//  FUNCTION: InitWindow
//
//  PURPOSE:  Initializes dialog and soft key menus
//            Also sends message to override the back button
//
BOOL InitWindow(
	const HWND hDlg, 
	UINT nToolBarId
	)
{
	// Specify that the dialog box should stretch full screen
	SHINITDLGINFO shidi;
	ZeroMemory(&shidi, sizeof(shidi));
	shidi.dwMask = SHIDIM_FLAGS;
	shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
	shidi.hDlg = hDlg;

	// set up Soft Keys menu
	SHMENUBARINFO mbi;
	ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
	mbi.cbSize = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hDlg;
	mbi.nToolBarId = nToolBarId;
	mbi.hInstRes = g_hInst;

	// If we could not initialize the dialog box, return an error
	if (FALSE == (SHInitDialog(&shidi) && SHCreateMenuBar(&mbi)))
	{
		return FALSE;
	}

	// set the title bar
	SetWindowText(hDlg, tszTitle);

	// In order to make Back work properly, it's necessary to 
	// override it and then call the appropriate SH API
	(void)SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK,
		MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY,
		SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;
	}


//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//

BOOL CALLBACK DlgProc (
	HWND hwnd, 
	UINT Msg, 
	WPARAM wParam, 
	LPARAM lParam)
{
    BOOL bReturn = TRUE;

	switch(Msg)
	{
	case WM_INITDIALOG:

		// Initialize the dialog and softkey menu
		if (FALSE == InitWindow(hwnd, IDR_BACK_MENUBAR))
		{
			EndDialog(hwnd, -1);
		}
		break;

	case WM_COMMAND:

		switch (wParam)
		{
		case IDOK:
			EndDialog(hwnd,IDOK);
			break;
		default:
			bReturn = FALSE;
		}
		break;

	case WM_HOTKEY:

		// If back key is overriden, back button messages are sent in a WM_HOTKEY to the menu bar
		// with the id VK_TBACK in the LPARAM.
		if (VK_TBACK == HIWORD(lParam) && (0 != (MOD_KEYUP & LOWORD(lParam))))
		{
			// Send a message to the check box to see if it's checked or not
			HWND hwndCheck = GetDlgItem(hwnd, IDC_CHECKBACK);

			if (BST_CHECKED == SendMessage(hwndCheck, BM_GETCHECK, 0, 0))
			{
				// check box is enabled, so we process the back key
				SHSendBackToFocusWindow(Msg, wParam, lParam);
			}
			else
			{
				// not enabled, revert to default back behaviour
				MessageBox(hwnd, tszBackText, tszBackCaption, MB_OK | MB_ICONINFORMATION);
				SHNavigateBack();
			}
		}
		break;

	default:
		bReturn = FALSE;
		break;

	}
	return bReturn;
}

//
//  FUNCTION: WinMain(HANDLE, HANDLE, LPWSTR, int)
//
//  PURPOSE: Entry point for the application
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int CmdShow
	)

{
	int nResult = 0;

	// Create mutex to track whether or not an application is already running
	HANDLE hMutex = CreateMutex(0, 0, _T("_BACKSDK_EXE_MUTEX_"));

	// check the result code
	if(NULL != hMutex)
	{
		if(ERROR_ALREADY_EXISTS != GetLastError())
		{
			// If the mutex doesn't already exist, create the dialog and start it.
			g_hInst = hInstance;

			nResult = DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLGBACK),
				NULL, (DLGPROC)DlgProc);
		}
		else
		{
			// Already an instance running - attempt to switch to it and then exit
			HWND hWndExistingInstance = FindWindow(_T("Dialog"), tszTitle);

			if (NULL != hWndExistingInstance)
			{
				SetForegroundWindow(hWndExistingInstance);
			}
		}

		CloseHandle(hMutex);
	}

	return ( nResult >= 0 );
}

// end SDKBack.cpp
