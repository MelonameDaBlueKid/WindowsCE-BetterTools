/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//
//  PARTICULAR PURPOSE.
//
// 
//
//  This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//
// closewindow.cpp
//
// A Simple program that will show how to force a program into base state when
// it is relaunched and how to destroy a chain of child windows.  
// Make sure that child windows have a parent: if any window
// has a NULL parent, this sample code will not work.
// 


#include <windows.h>
#include <astdtapi.h>
#include <Aygshell.h>
#include <winuserm.h>
#include <tpcshell.h>
#include "resource.h"


// function declarations
// Initialize Dialogs:
BOOL InitDialog (const HWND hDlg);
BOOL InitSubDialog (const HWND hDlg);

// Dialog Procs
BOOL CALLBACK DialogProc(const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam);

BOOL CALLBACK SubDialogProc (const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam);
BOOL CALLBACK SubDialog2Proc (const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam);

// Closing window functions
BOOL CALLBACK GetLastActiveAppWindowEnum(HWND hwnd, LPARAM lParam);
HWND GetLastActiveAppWindow(HWND hwndMain);
void CloseOwnedWindows(HWND hwndMain);

// globals variable declarations
HINSTANCE		g_hInstance;
LPCTSTR		g_szTitle;
static const TCHAR* g_szAppWndClass = TEXT("CloseWindowApp");



LRESULT CALLBACK WndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    LRESULT lResult = TRUE;

    switch(msg)
    {
        case WM_CREATE:
            lResult = 0;
            break;

        case WM_DESTROY:
			CloseOwnedWindows(hwnd);
            PostQuitMessage(0);
            break;

        default:
            lResult = DefWindowProc(hwnd, msg, wParam, lParam);
            break;
    }

    return(lResult);
}







// ***************************************************************************
// Function Name: WinMain
//
// Purpose: Main entry point into the CloseWindow program
//
// Arguments: Standard WinMain arguments
//
// Return Values: 0
//
// Description:
//	WinMain function creates the main window and base dialog and contains the message loop.

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPTSTR lpCmdLine, int nShowCmd)
{
	
	WNDCLASS wc;
    HWND hwndMain;
	HWND hBaseDialog;
	MSG msg;
	
	// load in program name
	g_szTitle = (LPCTSTR)LoadString(hInstance, IDS_CLOSEWINDOW_TITLE, NULL, 0);
	if (!g_szTitle)
		return 0;

	// Use a globally named mutex to detect another instance of Close Window
    const HANDLE hMutex = CreateMutex(NULL, 0, TEXT("_CLOSEWIN_EXE_MUTEX_"));
	
    // check the result code
	if(0 != hMutex) 
	{
		
		if(ERROR_ALREADY_EXISTS == GetLastError()) 
		{
			
			// If already an instance running - attempt to switch to it and go to base state and then exit
			const HWND hWndExistingInstance = FindWindow(g_szAppWndClass, g_szTitle);
			VERIFY((0 == hWndExistingInstance) || SetForegroundWindow((HWND) (((ULONG) hWndExistingInstance) | 0x01)));
			HWND hwndBaseDialog;
			// Close windows down to the first level modal dialog, so 
			// extract the dialog's handle that we stored in the windows extra storage
			// and pass that to the CloseOwnedWindows function
			
			hwndBaseDialog = (HWND)GetWindowLong(hWndExistingInstance,0);
			if (hwndBaseDialog)
				CloseOwnedWindows (hwndBaseDialog); // Will close windows returning to base state.
		}
		else
		{
			// We're starting up the first instance
			
			g_hInstance = hInstance;
			
			// Register our main window's class.
			ZeroMemory(&wc, sizeof(wc));
			wc.lpfnWndProc = (WNDPROC)WndProc;
			wc.hInstance = g_hInstance;
			wc.lpszClassName = g_szAppWndClass;
			wc.cbWndExtra = 4; // extra storage to save the base dialog's handle.
			if(RegisterClass(&wc))
			{ // successfully registered the class
				
				// Create the main window which will own the first level (modeless) dialog.
				hwndMain = CreateWindow(g_szAppWndClass, g_szTitle,
					WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, 
					CW_USEDEFAULT, CW_USEDEFAULT,
					NULL, NULL, g_hInstance, NULL );
				if(hwndMain)
				{		
					ShowWindow(hwndMain, nShowCmd);
					
					// create the base dialog box
					hBaseDialog = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hwndMain, (DLGPROC)DialogProc);
					if (hBaseDialog)
					{	
						ShowWindow(hBaseDialog, SW_SHOW);
						UpdateWindow(hBaseDialog);
						
						// store the dialog's handle so we know where to stop closing windows.
						SetWindowLong(hwndMain,0,(LONG)hBaseDialog);
						
						// standard message loop
						while(GetMessage(&msg, NULL, 0, 0)) 
						{
							if((NULL == hBaseDialog) || (!IsDialogMessage(hBaseDialog, &msg)))
							{
								TranslateMessage(&msg);
								DispatchMessage(&msg);
							}
						}
					}
				}
			}
		}
		
		
		VERIFY(CloseHandle(hMutex));
		
	}
	
	return 0;
}

// ***************************************************************************
// Function Name: DialogProc
// 
// Purpose: Message Handler for Base level modeless Dialog Box
//
// Arguments: Standard Dialog Procedure Arguments
//
// Return Values:
//	Only returns to exit the dialog
//	
// Description:
//	This is the base state dialog window.  Using the populate option will bring up
//  several child windows.


BOOL CALLBACK DialogProc(const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam)
{
	BOOL	bProcessedMsg = true;
	
	switch(uiMessage)
	{
		case WM_INITDIALOG:
			InitDialog (hDlg);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) 
			{
				case IDM_CLOSEWIN_POPULATE:				
					DialogBox (g_hInstance, MAKEINTRESOURCE(IDD_SUBDIALOG), hDlg, DLGPROC(SubDialogProc));		
					break;
					
				case IDM_CLOSEWIN_EXIT:
					// fall through:
				case IDCANCEL:
					DestroyWindow(hDlg);
					break;
					
				default:
					// nothing was processed
					bProcessedMsg = false;
					break;
			}
			break;
		
		case WM_DESTROY:
			// Destroy the parent window to exit the app
			DestroyWindow(GetParent(hDlg));
			break;

		case WM_CLOSE:	
				DestroyWindow(hDlg);
			break;

		case WM_HOTKEY:
            // The following is necessary to get the appropriate Back key behavior 
			// (handle on key-up as per recommendations)
            if(VK_TBACK == HIWORD(lParam)) 
			{
                DestroyWindow(hDlg);
            }
			else
				bProcessedMsg = false;
            break;	

		default:
			// nothing was processed
			bProcessedMsg = false;
			break;
	}

	return bProcessedMsg;
}

// SubDialogProc
// ------------------
// This is the dialogproc for the first child dialog window.  It will
// automatically populate another dialog window as its child, or will do
// so when the populate key is hit.
BOOL CALLBACK SubDialogProc(const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam)
{
	BOOL	bProcessedMsg = true;
	
	switch(uiMessage)
	{
		case WM_INITDIALOG:
			InitSubDialog (hDlg);
			DialogBox (g_hInstance, MAKEINTRESOURCE(IDD_SUBDIALOG2), hDlg, DLGPROC(SubDialog2Proc));
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDM_CLOSEWIN_POPULATE:				
					DialogBox (g_hInstance, MAKEINTRESOURCE(IDD_SUBDIALOG2), hDlg, DLGPROC(SubDialog2Proc));
					break;
					
				case IDM_CLOSEWIN_EXIT:
					// fall through:
				case IDCANCEL: // Make sure your dialogs respond to this message
							   // it's how they are closed by CloseOwnedWindows()
					EndDialog (hDlg, TRUE);
					break;
				default:
					// nothing was processed
					bProcessedMsg = false;
					break;
			}
			break;	
		
		case WM_CLOSE:	
			EndDialog (hDlg, 0);
			break;

		case WM_HOTKEY:
            // The following is necessary to get the appropriate Back key behavior 
			// (handle on key-up as per recommendations)
            if(VK_TBACK == HIWORD(lParam)) {
				EndDialog (hDlg, TRUE);
            }
			else
				bProcessedMsg = false;
            break;

		default:
			// nothing was processed
			bProcessedMsg = false;
			break;
	}

	return bProcessedMsg;
}

// SubDialog2Proc
// -----------------
// The lowest level dialog window.  It will automatically populate a message box
// or do so when the populate key is hit.  
BOOL CALLBACK SubDialog2Proc(const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam)
{
	BOOL	bProcessedMsg = true;
	LPCTSTR  lpMBoxText;
	LPCTSTR	lpMBoxTitle;
	
	switch(uiMessage)
	{
	case WM_INITDIALOG:
		InitSubDialog (hDlg);
		lpMBoxText = (LPCTSTR)LoadString(g_hInstance, IDS_MESSAGEBOX_TEXT, NULL, 0);
		lpMBoxTitle = (LPCTSTR)LoadString(g_hInstance, IDS_MESSAGEBOX_TITLE, NULL, 0);
		MessageBox(hDlg, lpMBoxText, lpMBoxTitle, MB_OK);
		break;
			
		case WM_COMMAND:
			switch (LOWORD(wParam)) 
			{
			case IDM_CLOSEWIN_POPULATE:			
				lpMBoxText = (LPCTSTR)LoadString(g_hInstance, IDS_MANUALMBOX_TEXT, NULL, 0);
				lpMBoxTitle = (LPCTSTR)LoadString(g_hInstance, IDS_MANUALMBOX_TITLE, NULL, 0);
				MessageBox(hDlg, lpMBoxText, lpMBoxTitle, MB_OK);
				break;
				
			case IDM_CLOSEWIN_EXIT:
				// fall through:lpMBoxTitle
			case IDCANCEL:
				EndDialog (hDlg, TRUE);
				break;
			default:
				// nothing was processed
				bProcessedMsg = false;
				break;
			}
			break;	
			
		case WM_CLOSE:	
			EndDialog (hDlg, 0);
			break;

		case WM_HOTKEY:
            // The following is necessary to get the appropriate Back key behavior 
			// (handle on key-up as per recommendations)
            if(VK_TBACK == HIWORD(lParam)) {
				EndDialog (hDlg, TRUE);
            }
			else
				bProcessedMsg = false;
            break;

		default:
			// nothing was processed
			bProcessedMsg = false;
			break;
	}

	return bProcessedMsg;
}

///////////////////////////////////////////
// InitDialog
//
// Parameters: HWND hDlg
//
// Returns: 
//		TRUE if the dialog was created successfully
//		FALSE if the dialog was not created
//
// Description:
//		Initializes the main level 1 dialog.
//		Applications base state is just this dialog displayed.
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
    shmbi.nToolBarId = IDR_CLOSEWIN_APPMENUBAR;
    shmbi.hInstRes = g_hInstance;

	// If we could not initialize the dialog box, return an error
	if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
		return FALSE;
	}

	// set the title bar
	SetWindowText(hDlg, g_szTitle);
			

	// Overriding Back button functionality
	(void)SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
			  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
						 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;

}

// InitSubDialog
// --------------
// Both subdialog windows use this initialization
BOOL InitSubDialog(const HWND hDlg)
{
	LPCTSTR		lpszSubTitle;

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
    shmbi.nToolBarId = IDR_CLOSEWIN_APPMENUBAR;
    shmbi.hInstRes = g_hInstance;

	// If we could not initialize the dialog box, return an error
	if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
		return FALSE;
	}

	// set the title bar
	lpszSubTitle = (LPCTSTR)LoadString(g_hInstance, IDS_SUBDIALOG_TITLE, NULL, 0);
	if (lpszSubTitle)
		SetWindowText(hDlg, lpszSubTitle);


	// Overriding Back button functionality
	(void)SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
			  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
						 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;

}


// App's dialogs and windows should handle WM_COMMAND/IDCANCEL appropriately.
// A Message Box will close when sent a WM_COMMAND IDCANCEL
// Close windows owned by hwndMain.
// Assumes that all the app's dialogs and message boxes have owners
// and that the top of the owner list is hwndMain.
// Also assumes that the dialogs and messageboxes disable their owner
// (Modal dialogs and message boxes automatically disable their owner.)
// Note: Will only close a single chain of windows.
void CloseOwnedWindows(HWND hwndMain)
{
	
    HWND hwndToClose, hwndOwner;
	
	// Get active window which was most recently active
	hwndToClose = GetLastActiveAppWindow(hwndMain);
	
	// Walk the owner chain backwards, closing windows.
	while (hwndToClose &&
		IsWindow(hwndToClose) &&       
		hwndToClose != hwndMain)
	{
		hwndOwner = GetWindow(hwndToClose, GW_OWNER);
		SendMessage(hwndToClose, WM_COMMAND, IDCANCEL, 0);
		hwndToClose = hwndOwner;
	}
	
}

typedef struct _LASTACTIVEWINDOW 
{
    HWND   hwndLastActive;      // Out: Thread's last active window
    DWORD  dwMainWindowThread;  // In: Thread of main window
} LASTACTIVEWINDOW;

// Gets app's most recently active window
HWND GetLastActiveAppWindow(HWND hwndMain)
{
    LASTACTIVEWINDOW law;

    law.hwndLastActive = NULL;
    law.dwMainWindowThread = GetWindowThreadProcessId(hwndMain, NULL);
    if (EnumWindows(GetLastActiveAppWindowEnum, (LPARAM)&law))
    {
        return law.hwndLastActive;
    }
    else
    {
        return NULL;
    }
}

// Window enumerator to get app's most recently active window.
// Assumes that each dialog/message box in the app disables its owner.
// (Modal dialogs and message boxes automatically disable their owner.)
BOOL CALLBACK GetLastActiveAppWindowEnum(HWND hwnd, LPARAM lParam)
{
    LASTACTIVEWINDOW *plaw;
    DWORD dwThread;

    plaw = (LASTACTIVEWINDOW *)lParam;
    dwThread = GetWindowThreadProcessId(hwnd, NULL);

    // Look for a same-thread, visible, enabled, !WS_EX_NOACTIVATE window.  
    // There should be only one if each of the app's dialogs/messageboxes disables its owner.
    if (dwThread == plaw->dwMainWindowThread &&
        IsWindowVisible(hwnd) &&
        IsWindowEnabled(hwnd) &&
        !(WS_EX_NOACTIVATE & GetWindowLong(hwnd, GWL_EXSTYLE))
       )
    {
        // Found active window
        plaw->hwndLastActive = hwnd;
        return FALSE;
    }

    // Keep enumerating
    return TRUE;
}