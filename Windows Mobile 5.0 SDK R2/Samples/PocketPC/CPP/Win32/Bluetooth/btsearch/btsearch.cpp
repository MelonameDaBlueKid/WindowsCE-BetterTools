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
// btsearch.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include "resource.h"


HINSTANCE g_hInst;

BOOL WINAPI MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
void PopulateBtDevList(HWND hDlg );
/*************************************************************

  Function: WinMain
  
  Purpose: Standard Win32 Entry point
	
**************************************************************/
int WINAPI WinMain(	HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR    lpCmdLine,
				   int       nCmdShow)
{
	// TODO: Place code here.
	
	WORD wVersionRequested;
	WSADATA wsaData;
	
	g_hInst = hInstance;
	// Initialize Winsock
	wVersionRequested = MAKEWORD( 2, 2 );
	
	if (WSAStartup( wVersionRequested, &wsaData ) == 0)
	{
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	}
	else
	{
		MessageBox(NULL, _T("Could not initialize winsock!"), _T("Fatal Error"), MB_OK);
		
	}
	
	return 0;
}
/*************************************************************

  Function: MainDlgProc
  
  Purpose: Main Dialog Window message handler
	
**************************************************************/
BOOL WINAPI MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			
			SHINITDLGINFO sid;
			SHMENUBARINFO smb;
			RECT rc;
			
			sid.dwMask   = SHIDIM_FLAGS;
			sid.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			sid.hDlg   = hDlg;
			
			// size dialog to full screen
			SHInitDialog(&sid);
			
			smb.cbSize = sizeof(SHMENUBARINFO);
			smb.hInstRes = g_hInst;
			smb.hwndParent = hDlg;
			smb.nToolBarId = IDR_MENUBAR;
			
			// create the Options menubar
			SHCreateMenuBar(&smb);
			
			// size the listbox control
			
			GetClientRect(hDlg, &rc);
			
			// Size the listbox control to the size of the window
			SetWindowPos(GetDlgItem(hDlg, IDC_DEVLIST), 
				0, 
				rc.left, 
				rc.top, 
				rc.right - rc.left+1, 
				rc.bottom - rc.top+1, 
				0);
			
			
			SendMessage(GetDlgItem(hDlg, IDC_DEVLIST),
				LB_ADDSTRING,
				0,
				(LPARAM) _T("Select \'Search\' below")); 
			
			
			
		}
		break;
	case WM_COMMAND:
		
		switch(LOWORD(wParam))
		{
		case IDM_QUIT:
			// 
			EndDialog(hDlg, IDOK);
			break;
			
		case IDM_SEARCH:
			
			PopulateBtDevList(hDlg);
			
			break;
			
		}
		
		
		break;
	}
	
	
	return FALSE;
}

/*************************************************************

  Function: PoplulateBtDevList
  
  Purpose: Searches for available bluetooth devices and displays
			them in the listbox
	
**************************************************************/
void PopulateBtDevList(HWND hDlg )
{
	
	INT				iResult = 0;
	LPWSAQUERYSET	pwsaResults;
	DWORD			dwSize = 0;
	WSAQUERYSET		wsaq;
	HCURSOR			hCurs;
	HANDLE			hLookup = 0;
	
	// empty the list box
	SendMessage(GetDlgItem(hDlg, IDC_DEVLIST),
		LB_RESETCONTENT,
		0,
		0);
	
	SendMessage(GetDlgItem(hDlg, IDC_DEVLIST),
		LB_ADDSTRING,
		0,
		(LPARAM) _T("Results...")); 
	
	
	memset (&wsaq, 0, sizeof(wsaq));
	wsaq.dwSize      = sizeof(wsaq);
	wsaq.dwNameSpace = NS_BTH;
	wsaq.lpcsaBuffer = NULL;
	
	// initialize searching procedure
	iResult = WSALookupServiceBegin(&wsaq, 
		LUP_CONTAINERS, 
		&hLookup);
	
	if (iResult != 0)
	{
		TCHAR tszErr[32];
		iResult = WSAGetLastError();		
		StringCchPrintf(tszErr, 32, _T("Socket Error: %d"), iResult);
		MessageBox(hDlg, tszErr, _T("Error"), MB_OK);
		
		
	}
	
	union {
		CHAR buf[5000];				// returned struct can be quite large 
		SOCKADDR_BTH	__unused;	// properly align buffer to BT_ADDR requirements
	};
	
	// save the current cursor
	hCurs = GetCursor();
	
	for (; ;)
	{
		// set the wait cursor while searching
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		pwsaResults = (LPWSAQUERYSET) buf;
		
		dwSize  = sizeof(buf);
		
		memset(pwsaResults,0,sizeof(WSAQUERYSET));
		pwsaResults->dwSize      = sizeof(WSAQUERYSET);
		// namespace MUST be NS_BTH for bluetooth queries
		pwsaResults->dwNameSpace = NS_BTH;
		pwsaResults->lpBlob      = NULL;
		
		// iterate through all found devices, returning name and address
		// (this sample only uses the name, but address could be used for
		// further queries)
		iResult = WSALookupServiceNext (hLookup, 
			LUP_RETURN_NAME | LUP_RETURN_ADDR, 
			&dwSize, 
			pwsaResults);
		
		
		if (iResult != 0)
		{
			iResult = WSAGetLastError();
			if (iResult != WSA_E_NO_MORE)
			{
				TCHAR tszErr[32];
				iResult = WSAGetLastError();
				StringCchPrintf(tszErr, 32, _T("Socket Error: %d"), iResult);
				MessageBox(hDlg, tszErr, _T("Error"), MB_OK);
				
			}
			// we're finished

			break;
		}
		
		// add the name to the listbox
		if (pwsaResults->lpszServiceInstanceName)
		{
			SendMessage(GetDlgItem(hDlg, IDC_DEVLIST), 
				LB_ADDSTRING, 
				0, 
				(LPARAM)pwsaResults->lpszServiceInstanceName);
			
		}
		
	}
	
	WSALookupServiceEnd(hLookup);
	
	// restore cursor
	SetCursor(hCurs);
	
	
	
}