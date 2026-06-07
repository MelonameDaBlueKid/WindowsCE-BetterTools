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
// HandleSIP.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HandleSIP.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100



// Global Variables:
HINSTANCE			g_hInst;			// The current instance
HWND				hwndCB;			// The command bar handle
HWND				hwndEdit1, hwndEdit2;
HWND				hwndEdit3, hwndEdit4;

TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

BOOL fSHFORCERESIZE = FALSE;
BOOL fENFOCUS = TRUE;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR    lpCmdLine,
				   int       nCmdShow)
{

	
	/// InitInstance
	LoadString(hInstance, IDC_HANDLESIP, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	
	// Look for running instance of application
	if (FindWindow(szWindowClass, szTitle)){
		SetForegroundWindow(FindWindow(szWindowClass, szTitle));
		return FALSE;
	}

	g_hInst = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)WndProc);
	
	return 0;
}


//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	SHACTIVATEINFO sai;
	LRESULT retVal = 0;
	
	
	/////////////////////////	
	switch (message) 
	{
	case WM_SETTINGCHANGE:
		if (SPI_SETSIPINFO == wParam){
			memset(&sai, 0, sizeof(SHACTIVATEINFO));
			SHHandleWMSettingChange(hWnd, (fSHFORCERESIZE ? -1 : wParam), (fSHFORCERESIZE ? 0 : lParam), &sai);
	
			Edit_SetText(GetDlgItem(hWnd, IDC_MESSAGE), L"WM_SETTINGCHANGE");
			
			RECT rect;
			GetClientRect(hWnd, &rect);
			InvalidateRect(hWnd, &rect, TRUE); 
			
			
		}
		
		
		
		break;
		
	case WM_ACTIVATE:
		if (SPI_SETSIPINFO == wParam){
			memset(&sai, 0, sizeof(SHACTIVATEINFO));
			SHHandleWMActivate(hWnd, wParam, lParam, &sai, 0);
			Edit_SetText(GetDlgItem(hWnd, IDC_MESSAGE), L"WM_ACTIVATE");
		}
		break;
		
	case WM_SIZE:
		Edit_SetText(GetDlgItem(hWnd, IDC_MESSAGE), L"WM_SIZE");
		
		break;
		
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_SIPPOPPER:
			switch(wmEvent){
			case EN_SETFOCUS:
				if (fENFOCUS) SHSipPreference(hWnd, SIP_UP);
				Edit_SetText(GetDlgItem(hWnd, IDC_SIPPOPPER), L"EN_SETFOCUS");
				break;
			case EN_KILLFOCUS:
				if (fENFOCUS) SHSipPreference(hWnd, SIP_DOWN);
				Edit_SetText(GetDlgItem(hWnd, IDC_SIPPOPPER), L"EN_KILLFOCUS");
				break;
			}
			break;
			
			case IDC_FOCUSSTEALER:
				switch(wmEvent){
				case EN_SETFOCUS:
					Edit_SetText(GetDlgItem(hWnd, IDC_FOCUSSTEALER), L"EN_SETFOCUS");
					break;
				case EN_KILLFOCUS:
					Edit_SetText(GetDlgItem(hWnd, IDC_FOCUSSTEALER), L"EN_KILLFOCUS");
					break;
				}
				break;
				
				
				case ID_SHOW_SHSIPPREFRENCE_SIPUP:
					SHSipPreference(hWnd, SIP_UP);
					break;
				case ID_SHOW_SHSIPPREFRENCE_SIPDOWN:
					SHSipPreference(hWnd, SIP_DOWN);
					break;
				case ID_SHOW_SHSIPPREFRENCE_SIPFORCEDOWN:
					SHSipPreference(hWnd, SIP_FORCEDOWN);
					break;
				case ID_SHOW_SHSIPPREFRENCE_SIPUNCHANGED:
					SHSipPreference(hWnd, SIP_UNCHANGED);
					break;
					
				case ID_SHOW_SHFORCERESIZE:
					{
						fSHFORCERESIZE = (fSHFORCERESIZE ? FALSE : TRUE); 
						HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
						CheckMenuItem(hm, ID_SHOW_SHFORCERESIZE, (fSHFORCERESIZE ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
					}
					break;
					
				case ID_SHOW_ONENFOCUS:
					{
						fENFOCUS = (fENFOCUS ? FALSE : TRUE); 
						HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
						CheckMenuItem(hm, ID_SHOW_ONENFOCUS, (fENFOCUS ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
					}
					break;
					
				case IDM_HELP_ABOUT:
					DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
					break;
				case IDOK:
				case IDM_FILE_EXIT:
					DestroyWindow(hWnd);
					break;
					
					
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		
		case WM_INITDIALOG:
			
			//On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
			// with an OK button in the upper corner. You should get/set any program settings
			// during each modal dialog creation and destruction
			SHINITDLGINFO shidi;
			// Create a Done button and size it.
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hWnd;
			//initialzes the dialog based on the dwFlags parameter
			SHInitDialog(&shidi);
			memset(&sai, 0, sizeof(SHACTIVATEINFO));
			
			
			SHMENUBARINFO mbi;
			memset(&mbi, 0, sizeof(SHMENUBARINFO));
			mbi.cbSize     = sizeof(SHMENUBARINFO);
			mbi.hwndParent = hWnd;
			mbi.nToolBarId = IDM_MAIN_MENU;
			mbi.hInstRes   = g_hInst;
			mbi.nBmpId     = 0;
			mbi.cBmpImages = 0;	
			
			
			if (!SHCreateMenuBar(&mbi))
				MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
			else
			{
				hwndCB = mbi.hwndMB;
				HMENU hm = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM2);
				CheckMenuItem(hm, ID_SHOW_ONENFOCUS, (fENFOCUS ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
			}
			retVal = 1;
			break;
		case WM_PAINT:
			RECT rt;
			SIPINFO sinfo;
			memset(&sinfo, 0, sizeof(SIPINFO));

			sinfo.cbSize = sizeof(SIPINFO);

			SHSipInfo(SPI_GETSIPINFO,0, &sinfo, 0);

			if (sinfo.fdwFlags & SIPF_ON)
			{
				Edit_SetText(GetDlgItem(hWnd, IDC_SIPSTATE), _T("SipUP"));
			}
			else
			{
				Edit_SetText(GetDlgItem(hWnd, IDC_SIPSTATE), _T("SipDOWN"));
			}
			

			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);
			
			Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
			InflateRect(&rt, -2, -2);
			Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
			InflateRect(&rt, -2, -2);
			Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
			
			DrawText(hdc, L"Center", _tcslen(L"Center"), &rt, 
				DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			EndPaint(hWnd, &ps);
			break;//WM_PAINT
			
			
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;//WM_DESTROY
			
			
	}
	return retVal;
}




// Mesage handler for the About box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			//On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
			// with an OK button in the upper corner. 
			SHINITDLGINFO shidi;
			// Create a Done button and size it.
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			//initialzes the dialog based on the dwFlags parameter
			SHInitDialog(&shidi);
			return TRUE;
		}
		
	case WM_COMMAND:
		if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
