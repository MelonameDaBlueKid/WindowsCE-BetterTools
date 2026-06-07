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

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "UILayout.h"
#include <windows.h>
#include <commctrl.h>

#include "ScreenLib.h"

// helper macros
#define ARRAYSIZE(a) (UINT_PTR)(sizeof(a)/sizeof((a)[0]))

#define IDC_INSTRUCTIONS 2000

static const TCHAR g_szClassName[] = _T("UILayout");

// function declarations
int WINAPI	WinMain(HINSTANCE, HINSTANCE, LPWSTR, int);
HANDLE		FindPrevInstance();
HWND		CreateMainWindow(int nShowCmd);
BOOL		OnCreateMainWindow(HWND);
BOOL		OnCreateDialog(HWND);
BOOL		CreateInstructionsTextBox();
BOOL		CreateSoftKeyBar(HWND, UINT);

// Messages for the main (parent) window
LRESULT		CALLBACK MainWindowProc(HWND, UINT, WPARAM, LPARAM);

// Messages for the demo dialog boxes
LRESULT		CALLBACK DlgProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT		CALLBACK DlgProc2(HWND, UINT, WPARAM, LPARAM);
LRESULT		CALLBACK DlgProc3(HWND, UINT, WPARAM, LPARAM);

// global variables
HINSTANCE g_hInstance;
HWND g_hMainWnd = NULL;
HWND g_hDialogWnd = NULL;
HWND g_hInstructionsWnd = NULL;

#ifdef WIN32_PLATFORM_PSPC
static SHACTIVATEINFO s_sai;
#endif  /* WIN32_PLATFORM_PSPC */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	HANDLE hEvent;
    HWND   hwnd;
    MSG    msg;

    // Save the instance handle so we can access it later
    g_hInstance = hInstance;

	// Check to see if this application is already running
	hEvent = FindPrevInstance();
	if (hEvent == NULL)
	{
		// We found another instance
		return -1;
	}

    // Create our main application window
    hwnd = CreateMainWindow(nShowCmd);
    if (hwnd == NULL)
    {
        // Failed to initialize
		CloseHandle(hEvent);
        return GetLastError();
    }

    // Run the message loop (note that GetMessage() returns -1 for error)
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	// This is the value we passed to PostQuitMessage()
	CloseHandle(hEvent);
    return msg.wParam;
}

HWND CreateMainWindow(int nShowCmd)
{
    WNDCLASS wc;
    
    // Set up the window class description
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = g_hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszClassName = g_szClassName;

	// We want to redraw the window contents anytime we get resized. That way
	// we'll respond appropriately when the user switches between portrait and
	// landscape. If we had any child windows or controls, we'd need to
	// reposition or resize them when we get a WM_SIZE message.
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // Register the window class
    ATOM atom = RegisterClass(&wc);
    if (atom == 0)
    {
        // Failed!!
        return NULL;
    }

    // Load the window title string resource
	TCHAR szTitle[128];
    if (!LoadString(g_hInstance, IDS_APP_TITLE, szTitle, ARRAYSIZE(szTitle)))
    {
        // Failed!!
        return NULL;
    }

    // Create a window using the class we just registered. Note that the
	// initial size and position don't matter, because we're going to make it
	// fullscreen when we get WM_CREATE, before it's ever displayed.

    g_hMainWnd = CreateWindow((LPCTSTR)atom, szTitle, WS_OVERLAPPED|WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, g_hInstance, NULL);

    if (g_hMainWnd == NULL)
    {
        // Failed to create main window
        return NULL;
    }

	if (!CreateInstructionsTextBox())
	{
        // Failed to create textbox control
        return NULL;
	}

    // Make the window visible and paint before returning
    ShowWindow(g_hMainWnd, nShowCmd);
    UpdateWindow(g_hMainWnd);

    return g_hMainWnd;
}

BOOL CreateInstructionsTextBox()
{
	// Create the Edit control that will contain demo instructions
	// and be docked to the fill the entire available screen space.

	g_hInstructionsWnd = CreateWindow(_T("EDIT"), NULL, 
		WS_CHILD|WS_VISIBLE|WS_VSCROLL|
		ES_MULTILINE|ES_AUTOVSCROLL|ES_WANTRETURN|ES_READONLY,
		0, 0, 0, 0, g_hMainWnd, (HMENU)IDC_INSTRUCTIONS, g_hInstance, NULL);

	// Notice how we are setting the initial width and height as zero above.
	// It doesn't really matter what we set the size as because the control
	// gets resized as soon as the parent window receives WM_SIZE.

    if (g_hInstructionsWnd == NULL) return FALSE;
	
	// Display instructions from the string resources
	TCHAR szInstructions[1000];
	LoadString(g_hInstance, IDS_INSTRUCTIONS, szInstructions, 1000);
	SetDlgItemText(g_hMainWnd, IDC_INSTRUCTIONS, szInstructions);

	SetFocus(g_hInstructionsWnd);
	return TRUE;
}

// Messages for the main (parent) window
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
    {
	    case WM_CREATE:
			// Initialize the window (if we fail, return -1)
			return OnCreateMainWindow(hwnd) ? 0 : -1;

		case WM_COMMAND:
			switch (LOWORD(wp))
			{
				case ID_DEMO1:		
					// Launch the Demo 1 dialog
					DialogBox(g_hInstance, 
						MAKEINTRESOURCE(IDD_DEMO1), 
						g_hMainWnd, (DLGPROC)DlgProc1);
					break;

				case ID_DEMO2:				
					// Launch the Demo 2 dialog
					DialogBox(g_hInstance, 
						MAKEINTRESOURCE(IDD_DEMO2), 
						g_hMainWnd, (DLGPROC)DlgProc2);
					break;

				case ID_DEMO3:			
					// Launch the Demo 3 dialog
					DialogBox(g_hInstance,
						MAKEINTRESOURCE(IDD_DEMO3),
						g_hMainWnd, (DLGPROC)DlgProc3);
					break;

				case ID_EXIT: 
					// Quit the application
					PostQuitMessage(0);
					break;
			}
			break;

		case WM_SIZE:
			if (g_hInstructionsWnd != NULL)
			{
				// Dock the instructions edit box to fill the entire
				// screen. Without ScreenLib, this would have taken 
				// several lines of code to determine the ClientRect
				// and then resize the control. With ScreenLib, it takes
				// a single line.
				CScreenLib::DockControl(g_hMainWnd, IDC_INSTRUCTIONS);
			}
			break;

	#ifdef WIN32_PLATFORM_PSPC
		case WM_ACTIVATE:
            SHHandleWMActivate(hwnd, wp, lp, &s_sai, FALSE);
            break;

		// Our window receives this when the Input Panel opens or closes
		case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hwnd, wp, lp, &s_sai);
            break;
	#endif  /* WIN32_PLATFORM_PSPC */		

		case WM_DESTROY:
			// When this window is destroyed, it's time to quit the application
			PostQuitMessage(0);
			break;
	}

    return DefWindowProc(hwnd, msg, wp, lp);
}

LRESULT	CALLBACK DlgProc1(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_INITDIALOG:
			return OnCreateDialog(hwnd) ? 0 : 1;

		case WM_COMMAND:
			if (LOWORD(wp) == IDOK) 
			{	
				EndDialog(hwnd, IDOK);
				return (INT_PTR)TRUE;
			}
			break;

		case WM_SIZE:
			// Use ScreenLib to maximize the use of available screen space.
			CScreenLib::MakeSameSize(hwnd, CScreenLib::SCREENLIB_SIZE_HEIGHT, 1, IDC_LIST1, IDC_LIST2);
			CScreenLib::DockControl(hwnd, IDC_LIST1, CScreenLib::SCREENLIB_DOCK_TOP);
			CScreenLib::DockControl(hwnd, IDC_LIST2, CScreenLib::SCREENLIB_DOCK_BOTTOM);
			break;

	#ifdef WIN32_PLATFORM_PSPC
		// Our dialog receives this when the Input Panel opens or closes
		case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hwnd, wp, lp, &s_sai);
            break;
	#endif  /* WIN32_PLATFORM_PSPC */		
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

LRESULT	CALLBACK DlgProc2(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_INITDIALOG:
			return OnCreateDialog(hwnd) ? 0 : 1;

		case WM_COMMAND:
			if (LOWORD(wp) == IDOK) 
			{
				EndDialog(hwnd, IDOK);
				return (INT_PTR)TRUE;
			}
			break;

		case WM_SIZE:
			// Use ScreenLib to maximize the use of available screen space.
			
			// Notice how we can use a single line of code to stretch 6 
			// separate controls. 

			CScreenLib::OptimizeWidth(hwnd, 6, 
				IDC_STATIC1, IDC_STATIC2, IDC_STATIC3,
				IDC_EDIT1, IDC_EDIT2, IDC_EDIT3);

			CScreenLib::OptimizeHeight(hwnd, IDC_EDIT3);
			break;

	#ifdef WIN32_PLATFORM_PSPC
		// Our dialog receives this when the Input Panel opens or closes
		case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hwnd, wp, lp, &s_sai);
            break;
	#endif  /* WIN32_PLATFORM_PSPC */		
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

LRESULT	CALLBACK DlgProc3(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HWND hWndListCtrl;

	switch (msg)
	{
		case WM_INITDIALOG:
			// Display some sample data in the controls to mimic the look of
			// the Pocket PC 'Today' screen applet.
			SetDlgItemText(hwnd, IDC_EDIT1, _T("\\My Documents\\Sample.jpg"));
			
			hWndListCtrl = GetDlgItem(hwnd, IDC_LIST1);
			SendMessage(hWndListCtrl, LB_ADDSTRING, 0, (LPARAM)_T("Windows Default"));
			SendMessage(hWndListCtrl, LB_ADDSTRING, 0, (LPARAM)_T("Guava Bubbles"));

			return OnCreateDialog(hwnd) ? 0 : 1;

		case WM_COMMAND:
			if (LOWORD(wp) == IDOK) 
			{
				EndDialog(hwnd, IDOK);
				return (INT_PTR)TRUE;
			}
			break;

		case WM_SIZE:
			// Use ScreenLib to maximize the use of available screen space.
			CScreenLib::OptimizeWidth(hwnd, 3, IDC_STATIC1, IDC_EDIT1, IDC_CHECK1);
			
		#ifdef WIN32_PLATFORM_WFSP
			CScreenLib::OptimizeWidth(hwnd, 1, IDC_LIST1);
			CScreenLib::OptimizeHeight(hwnd, IDC_LIST1);
		#else
			CScreenLib::OptimizeWidthWithRightButton(hwnd, IDC_LIST1, IDC_BUTTON1, TRUE);
			CScreenLib::AlignControls(hwnd, CScreenLib::SCREENLIB_ALIGN_LEFT, 1, IDC_BUTTON1, IDC_BUTTON2);
		#endif  /* WIN32_PLATFORM_WFSP */
						
			break;

	#ifdef WIN32_PLATFORM_PSPC
		// Our dialog receives this when the Input Panel opens or closes
		case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hwnd, wp, lp, &s_sai);
            break;
	#endif  /* WIN32_PLATFORM_PSPC */		
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

// Initialize the main window
BOOL OnCreateMainWindow(HWND hwnd)
{
#ifdef WIN32_PLATFORM_PSPC
	// Initialize the shell activate info structure.
	// This will ensure that our main window and dialog boxes get
	// resized when the Input Panel opens or closes.

	memset(&s_sai, 0, sizeof(s_sai));
	s_sai.cbSize = sizeof(s_sai);
#endif  /* WIN32_PLATFORM_PSPC */

	if (!CreateSoftKeyBar(hwnd, IDR_MENU))
	{
		return FALSE;
	}

	// Windows Mobile applications should always display their main window
	// full-screen. We're going to let the OS do this for us by calling
	// SHInitDialog, even though technically this window isn't a dialog window.

	SHINITDLGINFO shidi;
	shidi.dwMask	= SHIDIM_FLAGS;
	shidi.hDlg		= hwnd;
	shidi.dwFlags	= SHIDIF_SIZEDLGFULLSCREEN|SHIDIF_SIPDOWN;

	return SHInitDialog(&shidi);
}

// Initialize the dialog box
BOOL OnCreateDialog(HWND hwnd)
{
	if (!CreateSoftKeyBar(hwnd, IDR_DIALOG))
	{
		return FALSE;
	}

	SHINITDLGINFO shidi;

	shidi.dwMask	= SHIDIM_FLAGS;
	shidi.hDlg		= hwnd;

#ifdef WIN32_PLATFORM_WFSP
	shidi.dwFlags	= SHIDIF_SIZEDLGFULLSCREEN;
#else
	shidi.dwFlags	= SHIDIF_SIZEDLGFULLSCREEN|SHIDIF_DONEBUTTON|SHIDIF_SIPDOWN;
#endif  /* WIN32_PLATFORM_WFSP */

	return SHInitDialog(&shidi);
}

// Given a parent window and resource ID, create a softkey bar
BOOL CreateSoftKeyBar(HWND hwndParent, UINT nID)
{
	SHMENUBARINFO shmbi;

	ZeroMemory(&shmbi, sizeof(shmbi));
	shmbi.cbSize		= sizeof(shmbi);
	shmbi.hwndParent	= hwndParent;
	shmbi.dwFlags		= SHCMBF_HMENU;
	shmbi.nToolBarId	= nID;
	shmbi.hInstRes		= g_hInstance;

	return SHCreateMenuBar(&shmbi);
}

// Code to ensure only a single instance of the application runs.
HANDLE FindPrevInstance()
{
	HANDLE hEvent;
	HWND   hwnd;
	UINT   cTries = 0;

	// Create a named event
	hEvent = CreateEvent(NULL, TRUE, FALSE, g_szClassName);
	if (hEvent != NULL)
	{
		// If the event already existed, that means there's another copy of our app
		// already running
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			do
			{
				// Just in case the other window needs to finish initialization
				Sleep(cTries ? 250 : 0);

				// Try to find the other application window
				hwnd = FindWindow(g_szClassName, NULL);
				if (hwnd != NULL)
				{
					SetForegroundWindow((HWND)((UINT_PTR)hwnd | 0x01));
					CloseHandle(hEvent);
					return NULL;
				}
			}
			while (++cTries < 2);  // only try twice

			// If we didn't find the window, the other application was probably
			// shutting down, so we'll just continue
		}
	}

	// Done
	return hEvent;
}