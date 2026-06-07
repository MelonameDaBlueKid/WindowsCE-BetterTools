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
/******************************************************************************\
*
*  PROGRAM:     SPINTEST.C
*
*  PURPOSE:     Demonstrates the use of the SPINCUBE custom control.
*
*  FUNCTIONS:   WinMain        - standard stuff; also loads the
*                                  SPINCUBE.DLL and creates a couple
*                                  of spincube controls.
*               MainWndProc    - generic window procedure.
*               SpintestDlgProc- generic dialog procedure.
*               AboutDlgProc   - processes about dialog messages
*
*
\******************************************************************************/

#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <aygshell.h>
#include "spintest.h"
#include "spincube\\spincube.h"

#define MENU_HEIGHT         26

HWND  g_hWndCmdBar;    // hwnd to the CommandBar

/******************************************************************************\
*
*  FUNCTION:    WinMain (standard WinMain INPUTS/RETURNS)
*
\******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	WNDCLASS wc;
	HWND   hwnd;
	MSG    msg;
	RECT   rect;
	WORD   i;
	DWORD dwStyle;
	
	wc.style         = 0;
	wc.lpfnWndProc   = (WNDPROC) MainWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon (hInstance, TEXT("spintesticon"));
	wc.hCursor       = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = TEXT("Main");
	
	if (!RegisterClass (&wc))
	{
		MessageBox(NULL, TEXT("WinMain(): RegisterClass() failed"),
			TEXT("Err! - SPINTEST"), MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}
	
	ghInst = hInstance;
	dwStyle = WS_VISIBLE;
	hwnd = CreateWindow (TEXT("Main"), TEXT("Spintest Sample Application"),
		dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, ghInst, NULL);
	if (NULL == hwnd) 
	{
		return 0;
	}
	
	//
	// Create a couple of SpinCube custom controls, we'll size them later in
	//   the WM_SIZE Msg handler
	//
	for (i = 0; i < 4; i++)
	{
		gahwndSpin[i] = CreateWindow(TEXT("Spincube"), TEXT(""),
			WS_VISIBLE | WS_CHILD | SS_INMOTION | SS_ERASE,
			0, 0, 0, 0, hwnd, NULL, NULL, NULL);
		if (NULL == gahwndSpin[i])
		{
			MessageBox(hwnd, L"Fail", L"", MB_OK);
		}
	}
	
	//
	// Delete the SS_ERASE to the 1st & 4th controls so we get the
	//   trailing cubes effect.
	//
	SetWindowLong(gahwndSpin[0], GWL_STYLE,
		GetWindowLong (gahwndSpin[0], GWL_STYLE) & ~ SS_ERASE);
	SetWindowLong(gahwndSpin[3], GWL_STYLE,
		GetWindowLong (gahwndSpin[3], GWL_STYLE) & ~ SS_ERASE);
	
	//
	// Send ourself a WM_SIZE so the controls will get sized appropriately
	//
	GetClientRect(hwnd, &rect);
	SendMessage(hwnd, WM_SIZE, 0,
		MAKELONG((WORD)rect.right,(WORD)rect.bottom));
	ShowWindow (hwnd, nCmdShow);
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage  (&msg);
	}
	return (msg.wParam);
}



/******************************************************************************\
*
*  FUNCTION:    MainWndProc (standard window procedure INPUTS/RETURNS)
*
\******************************************************************************/

LRESULT CALLBACK MainWndProc(
	HWND hwnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		{
			//Create the menubar.
			SHMENUBARINFO mbi;
			
			memset (&mbi, 0, sizeof (SHMENUBARINFO));
			mbi.cbSize     = sizeof (SHMENUBARINFO);
			mbi.hwndParent = hwnd;
			mbi.nToolBarId = IDM_MAIN_MENU;
			mbi.hInstRes   = ghInst;
			mbi.nBmpId     = 0;
			mbi.cBmpImages = 0;    
			
			if (FALSE == SHCreateMenuBar(&mbi))
			{
				MessageBox(hwnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
				break;
			}
			
			g_hWndCmdBar = mbi.hwndMB;
		}
		
		return 0;
		
	case IDM_EXIT:
		SendMessage( hwnd, WM_CLOSE, 0, 0 );
		return 0;
		
	case WM_CLOSE:
		DestroyWindow( hwnd );
		return 0;
		
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_DLGEDITDIALOG:
			DialogBox( ghInst, (LPCTSTR) TEXT("SpintestDlg"), hwnd, DlgProc);
			break;
			
		case IDM_SPINTESTSTATS:
			DialogBox( ghInst, (LPCTSTR) TEXT("Stats"), hwnd, (DLGPROC) DlgProc);
			break;
			
		case IDM_ABOUT:
			DialogBox( ghInst, (LPCTSTR)TEXT("About"), hwnd, (DLGPROC) DlgProc);
			break;
			
		}
		break;
		
		case WM_SIZE:
			{
				//
				// Resize the controls such that each cover half the client area
				//   (plus a little border).
				//
				int width  = (int) LOWORD(lParam);
				int height = (int) HIWORD(lParam) - MENU_HEIGHT;
				
				SetWindowPos(gahwndSpin[0], NULL,
                    BORDER, BORDER,
                    width/2 - BORDER, height/2 - BORDER,
                    SWP_SHOWWINDOW);
				SetWindowPos(gahwndSpin[1], NULL,
                    width/2 + BORDER, BORDER,
                    width/2 - 2*BORDER, height/2 - BORDER,
                    SWP_SHOWWINDOW);
				SetWindowPos(gahwndSpin[2], NULL,
                    BORDER, height/2 + BORDER,
                    width/2 - BORDER, height/2 - 2*BORDER,
                    SWP_SHOWWINDOW);
				SetWindowPos(gahwndSpin[3], NULL,
                    width/2 + BORDER, height/2 + BORDER,
                    width/2 - 2*BORDER, height/2 - 2*BORDER,
                    SWP_SHOWWINDOW);
				break;
			}
			
		case WM_DESTROY:
			CommandBar_Destroy (g_hWndCmdBar);
			PostQuitMessage (0);
			break;
			
		default:
			return (DefWindowProc (hwnd, msg, wParam, lParam));
	}
	return 0;
}



/******************************************************************************\
*
*  FUNCTION:    DlgProc (standard dialog procedure INPUTS/RETURNS)
*
*  COMMENTS:    Our common dlg proc (why have 3 that do the same thing???)
*
\******************************************************************************/

BOOL CALLBACK DlgProc(
	HWND hwnd, 
	UINT Msg, 
	WPARAM wParam, 
	LPARAM lParam)
{
	int iThisProcess = 0;
	int iAllProcesses = 0;
	
	switch (Msg)
	{
    case WM_INITDIALOG:
		{
			//On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
			// with an OK button in the upper corner. You should get/set any program settings
			// during each modal dialog creation and destruction
			SHINITDLGINFO shidi;
			// Create a Done button and size it.
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hwnd;
			//initialzes the dialog based on the dwFlags parameter
			SHInitDialog(&shidi);
			
			//
			// If this dlg the "Stats" dlg fill in the appropriate fields.
			//   If not these calls will just fail.
			//
			// If the references to the giNum* vars are commented out &
			//   the program gets rebuilt don't be surprised if no spincubes
			//   appear- since no references to spincube.lib the linker will
			//   infer that it is not needed, & will not cause it to get
			//   loaded. You'll need to make a call to LoadLibrary ("SPINCUBE.DLL")
			//   prior to calling CreateWindow ("SPINCUBE"...).
			//
			iThisProcess = GetgiNumSpincubesThisProcess();
			iAllProcesses = GetgiNumSpincubesAllProcesses();
			SetDlgItemInt (hwnd, 500, iThisProcess, TRUE);
			SetDlgItemInt (hwnd, 501, iAllProcesses, TRUE);
			
			return (TRUE);
		}
		
    case WM_COMMAND:
		if ( (LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL) )
		{
			EndDialog (hwnd, TRUE);
		}
		return (TRUE);
	}
	return (FALSE);
}
