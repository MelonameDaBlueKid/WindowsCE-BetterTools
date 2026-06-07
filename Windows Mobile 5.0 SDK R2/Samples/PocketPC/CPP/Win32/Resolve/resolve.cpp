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

// ****************************************************************************
// FILE: resolve.cpp
// ABTRACT: Main implementation file that supports the dialog, gathers user
//			input, resolves an IP or looksup a host name from IP, 
//			and displays the requested information
// ****************************************************************************
//

#include "stdafx.h"
#include "resolve.h"

#define ARRAYSIZE(a) (sizeof(a)/sizeof(*a))

#define MAX_ENTRYLEN 255

// Global Variables:
HINSTANCE			g_hInst;					// The current instance
HWND				g_hwndCB;					// The command bar handle

static SHACTIVATEINFO s_sai;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK	Resolve				(HWND, UINT, WPARAM, LPARAM);
HWND				CreateRpCommandBar	(HWND);


int WINAPI WinMain(	HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR    lpCmdLine,
				   int       nCmdShow)
{
	g_hInst = hInstance;
	DialogBox(g_hInst, (LPCTSTR)IDD_RESOLVE, NULL, (DLGPROC)Resolve);
	return 0;
}

// Mesage handler for the About box.
LRESULT CALLBACK Resolve(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	SHINITDLGINFO shidi;
	TCHAR szUserEntry[MAX_ENTRYLEN];
	TCHAR szTextToDisplay[MAX_ENTRYLEN];
	CHAR chszUserEntry[MAX_ENTRYLEN];
	CHAR chszTextToDisplay[MAX_ENTRYLEN];
	IN_ADDR inetAddr;
	IPAddr byteOrderIP;
	WSADATA wsadata;
	HOSTENT* pHostent;
	
	switch (message)
	{
	case WM_INITDIALOG:
		// Create a Done button and size it.  
		shidi.dwMask = SHIDIM_FLAGS;
		shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
		shidi.hDlg = hDlg;
		SHInitDialog(&shidi);

		g_hwndCB = CreateRpCommandBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_INPUT, EM_LIMITTEXT, MAX_ENTRYLEN, 0);
		
		// if we can't start winsock services, msgbox and exit
		//  request version 1.01 of winsock services
		if(WSAStartup(0x0101, &wsadata ) != 0)
		{
			MessageBox(hDlg, TEXT("Winsock Start Failed - Exiting Program."), TEXT("Resolve Error:"), MB_OK);
			EndDialog(hDlg, NULL);
			return TRUE;
		}
		return TRUE; 
		
	case WM_COMMAND:
		// if the user clicks the IP to Host button
		if (IDC_IPTOHOST == LOWORD(wParam))
		{
			// disable the two pushbuttons on this dialog while we lookup the name
			HWND hIPToHostButton = GetDlgItem(hDlg, IDC_IPTOHOST);
			HWND hHostToIPButton = GetDlgItem(hDlg, IDC_HOSTTOIP);			
			EnableWindow(hIPToHostButton, FALSE);
			EnableWindow(hHostToIPButton, FALSE);
			
			// get the user input
			GetDlgItemText(hDlg, IDC_INPUT, szUserEntry, MAX_ENTRYLEN);
			
			// convert the unicode input to ascii for lookup functions
			wcstombs(chszUserEntry, szUserEntry, MAX_ENTRYLEN);
			
			// convert the dotted IP to a byte order IP
			byteOrderIP = inet_addr((const char*)chszUserEntry);
			
			if(INADDR_NONE == byteOrderIP)
			{
				MessageBox(hDlg, TEXT("Invalid IP Entered (inet_addr)"), TEXT("Resolve Status:"), 0);
			}
			else
			{
				
				// resolve the host and the result struct is at pHostent
				if((pHostent = gethostbyaddr((char*)&byteOrderIP,4,AF_INET)) == NULL)
				{
					MessageBox(hDlg, TEXT("Cannot resolve IP"), TEXT("Resolve Status:"), 0);					
				}
				else
				{
					// copy the host name out of the struct
					StringCchCopyA(chszTextToDisplay, ARRAYSIZE(chszTextToDisplay), pHostent->h_name);
					
					// convert back to Unicode for display in the dialog
					mbstowcs(szTextToDisplay, chszTextToDisplay, MAX_ENTRYLEN);
					
					// display the resolved name
					SetDlgItemText(hDlg, IDC_RESULTS, szTextToDisplay);					
				}
				
				
			}
			// turn back on the conversion buttons
			EnableWindow(hIPToHostButton, TRUE);
			EnableWindow(hHostToIPButton, TRUE);
		}
		
		// if the user clicks the Host To IP button
		if (IDC_HOSTTOIP == LOWORD(wParam))
		{
			// disable the two pushbuttons on this dialog while we lookup the name
			HWND hIPToHostButton = GetDlgItem(hDlg, IDC_IPTOHOST);
			HWND hHostToIPButton = GetDlgItem(hDlg, IDC_HOSTTOIP);			
			EnableWindow(hIPToHostButton, FALSE);
			EnableWindow(hHostToIPButton, FALSE);
			
			// get the user input
			GetDlgItemText(hDlg, IDC_INPUT, szUserEntry, MAX_ENTRYLEN);
			
			// convert the unicode input to ascii for lookup functions
			wcstombs(chszUserEntry, szUserEntry, MAX_ENTRYLEN);
			
			
			// check to see if the host entered has a valid IP address
			if((pHostent = gethostbyname(chszUserEntry)) == NULL)
			{
				MessageBox(hDlg, TEXT("No IP Found!"), TEXT("Resolve Status:"), 0);
				
			}
			else
			{
				// determine the IP address returned in the HOSTENT structure
				char* pcDottedIP = NULL;
					
				// make sure that the address we are going to copy is the same
				// size or less than the inetAddr
				if (pHostent->h_length > 0 && pHostent->h_length <= sizeof(inetAddr))
				{
					// copy the IP as a IN_ADDR structure out of the HOSTENT structure
					memcpy((void*)&inetAddr, (void*)pHostent->h_addr_list[0], pHostent->h_length);
							
					// convert the (Ipv4) Internet network address (IN_ADDR structure) 
					// into a string in Internet standard dotted format.
					pcDottedIP = inet_ntoa(inetAddr);
					if(pcDottedIP)
					{
						// convert the text back to unicode for display
						mbstowcs(szTextToDisplay, pcDottedIP, MAX_ENTRYLEN);
						
						// display the text
						SetDlgItemText(hDlg, IDC_RESULTS, szTextToDisplay);					
					}
				}

			}
			// turn back on the conversion buttons
			EnableWindow(hIPToHostButton, TRUE);
			EnableWindow(hHostToIPButton, TRUE);		
		}
		
		if (IDOK == LOWORD(wParam))
		{
			WSACleanup();
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
    return FALSE;
}


HWND CreateRpCommandBar(HWND hwnd)
{
	SHMENUBARINFO mbi;
	
	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hwnd;
	mbi.nToolBarId = NULL;
	mbi.hInstRes   = g_hInst;
	mbi.nBmpId     = 0;
	mbi.cBmpImages = 0;
	mbi.dwFlags	   = SHCMBF_EMPTYBAR;
	
	if (!SHCreateMenuBar(&mbi)) 
		return NULL;
	
	return mbi.hwndMB;
}
