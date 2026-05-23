/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF

  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO

  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A

  PARTICULAR PURPOSE.

 

    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/
///////////////////////////////////////////////////////////////////////////////
//
// SIMMgr.CPP
//
// Main implementation file for the SIMMgr Phonebook
//

#define INITGUID

#include <windows.h>
#include <aygshell.h>
#include <tpcshell.h>
#include <simmgr.h>
#include <astdtapi.h>
#include <pimstore.h>
#include "newres.h"
#include "resource.h"


// useful macros
#define ARRAY_LENGTH(x)		(sizeof(x)/sizeof((x)[0]))
#define EINITFAILED			(-1)
#define EADDFAILED			(-2)
#define	INDEX_BUFFER		4
#define REASONABLE_BUFFER	1024
#define SMALL_BUFFER		32
#define CALLBACKID			

// global variables
HINSTANCE		g_hInst;
HWND			g_hwndMain;
HWND			g_hwndLV;
HSIM			g_hSim = NULL;
IPOutlookApp	*g_polApp = NULL;
BYTE *			g_pbyteInUse;	// PB usage cache
SIMCAPS			g_simcaps;

const DWORD		g_dwLocation = SIM_PBSTORAGE_SIM;
LPCTSTR			g_tszTitle;
LPCTSTR			g_tszAppName;


// struct to help find the last active window
typedef struct
{
    HWND   hwndLastActive;      // Out: Thread's last active window
    DWORD  dwMainWindowThread;  // In: Thread of main window

} LASTACTIVEWINDOW;

// function declarations
BOOL InitInstance(
    int iShow
    );
BOOL InitApplication();
BOOL InitMenu(
    HWND hWnd, 
    UINT nToolBarId
    );
LPCTSTR UseString(
    UINT uID
    );
LRESULT CALLBACK MainWndProc(
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    );
BOOL CreateListview(
    HWND hwndParent
    );
HWND GetLastActiveAppWindow(
    HWND hwndMain
    );
BOOL CALLBACK GetLastActiveAppWindowEnum(
    HWND hWnd, 
	LPARAM lParam
    );
BOOL RefreshListview();
BOOL AddLVEntry(
    LPSIMPHONEBOOKENTRY lpspbe, 
    DWORD dwIndex
    );
BOOL InitializeSIM();

void CALLBACK SimNotifProc(
    DWORD dwNotifyCode, 
    const void* pData, 
    DWORD dwDataSize, 
    DWORD dwParam
    );
BOOL CALLBACK DialogProc(
    const HWND hDlg,
    const UINT Msg, 
    const WPARAM wParam,
    const LPARAM lParam
    );
BOOL InitDialog(
    const HWND hDlg, 
    UINT nToolBarId
    );
BOOL AddPBEntry(
    HWND hDlg
    );
BOOL DeletePBEntry();
BOOL DialPBEntry();
BOOL AddToOLContacts();
BOOL InitPOOM();
void CleanupPOOM();


int WINAPI WinMain (
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance, 
    LPWSTR lpCmdLine, 
    int nShowCmd
    )
{
	// load in program name
	g_tszTitle = (LPCTSTR)LoadString(hInstance, IDS_SIMMGR_TITLE, 0, 0);
	g_tszAppName = (LPCTSTR)LoadString(hInstance, IDS_SIMMGR_APPNAME, 0, 0);

    // Use a globally named mutex to detect another instance of HelloSMS
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_SIMMGR_EXE_MUTEX_"));

    // check the result code
	if (0 == hMutex)
    {
		return 1;
    }

    // First instance running?  Okay to proceed...
	if (ERROR_ALREADY_EXISTS != GetLastError())
	{
		// store the hInstance
		g_hInst = hInstance;

		// initialize the application
		if (TRUE == InitApplication())
		{
			// initialize the instance
			if (TRUE == InitInstance(nShowCmd))
			{
				// initialize POOM
				if (InitPOOM())
				{
					MSG msg;

					// begin message pump
					while (GetMessage(&msg, NULL, 0,0) == TRUE)
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					
					CleanupPOOM();
					VERIFY(CloseHandle(hMutex));
					return msg.wParam;
				}
			}
		}

		return FALSE;
	}
	else
	{
		// Already an instance running - attempt to switch to it and then exit
		const HWND hWndExistingInstance = FindWindow(g_tszAppName, g_tszTitle);
		HWND hwndRestore = GetLastActiveAppWindow(hWndExistingInstance);

		VERIFY((0 == hwndRestore) || SetForegroundWindow((HWND)((ULONG)hwndRestore | 0x01)));
		VERIFY(CloseHandle(hMutex));
	}

    return TRUE;
}


BOOL InitInstance(int iCmdShow)
{
	g_hwndMain = CreateWindow(g_tszAppName, g_tszTitle, WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, g_hInst, NULL);

	if (NULL == g_hwndMain)
	{
		return FALSE;
	}

	ShowWindow(g_hwndMain, iCmdShow);
	UpdateWindow(g_hwndMain);

	return TRUE;
}

BOOL InitApplication()
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hInstance = g_hInst;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_tszAppName;
	
	return RegisterClass(&wc);
}

LRESULT CALLBACK MainWndProc(
	HWND hWnd, 
	UINT Msg,
	WPARAM wParam, 
	LPARAM lParam
	)
{
    int		iResult;
	LRESULT	lResult = TRUE;

	switch(Msg)
	{
		case WM_CREATE:
			// create the menu
			if (InitMenu(hWnd, IDR_SIMMGR_MAINMENU))
			{
				// create the listview
				if (CreateListview(hWnd))
				{
					// initialize the SIM
					if (InitializeSIM())
					{
						// populate the listview
						if (TRUE == RefreshListview())
							break;
					}
				}
			}

			MessageBox(NULL, UseString(IDS_SIMMGR_INITFAIL), UseString(IDS_SIMMGR_ERROR), MB_OK); 
			return -1;

		case WM_COMMAND:
			switch(wParam)
			{
				case IDM_SIMMGR_QUIT:
					SendMessage(hWnd, WM_CLOSE, 0, 0);
					break;

				case IDM_SIMMGR_ADDENTRY:
					iResult = DialogBox(g_hInst, MAKEINTRESOURCE(IDD_SIMMGR_ADDPB),
								0, (DLGPROC)DialogProc);
					switch(iResult)
					{
						case EINITFAILED:
							MessageBox(NULL, UseString(IDS_SIMMGR_ADDDIALOG_FAILED),
									   UseString(IDS_SIMMGR_ERROR), MB_OK ); 
							break;

						case EADDFAILED:
							MessageBox(NULL, UseString(IDS_SIMMGR_ADDENTRY_FAILED),
									   UseString(IDS_SIMMGR_ERROR), MB_OK );
							break;

						default:
							// success
							/*
							** No need to call RefreshListview(); as the SIM Callback
							** function is called, and we update there instead
							*/
							break;
					}
					break;

				case IDM_SIMMGR_DELENTRY:
					if (DeletePBEntry())
					{
						// success
						/*
						** No need to call RefreshListview(); as the SIM Callback
						** function is called, and we update there instead
						*/
					}
					else
					{
						MessageBox(NULL, UseString(IDS_SIMMGR_DELETEENTRY_FAILED),
								   UseString(IDS_SIMMGR_ERROR), MB_OK ); 
					}
					break;

				case IDM_SIMMGR_POOM:
					if (TRUE == AddToOLContacts())
					{
						MessageBox(NULL, UseString(IDS_SIMMGR_ADDOUTLOOK_SUCCESS),
								   UseString(IDS_SIMMGR_SUCCESS), MB_OK ); 
					}
					else
					{
						MessageBox(NULL, UseString(IDS_SIMMGR_ADDOUTLOOK_FAILED),
								   UseString(IDS_SIMMGR_ERROR), MB_OK );
					}
					break;

				case IDM_SIMMGR_DIALENTRY:
					if (FALSE == DialPBEntry())
					{
						MessageBox(NULL, UseString(IDS_SIMMGR_DIALENTRY_FAILED),
								   UseString(IDS_SIMMGR_ERROR), MB_OK ); 
					}
					break;

				default:
					lResult = DefWindowProc(hWnd, Msg, wParam, lParam);
			}
			break;

		case WM_DESTROY:
			if (g_hSim)
				SimDeinitialize(g_hSim);

			PostQuitMessage(0);
			break;

		case WM_ACTIVATE:
			if (wParam)
			{
				SetFocus(g_hwndLV);
			}
			break;

		default:
			lResult = DefWindowProc(hWnd, Msg, wParam, lParam);
			break;
	}
	
	return lResult;
}

BOOL InitMenu(
	HWND hWnd, 
	UINT nToolBarId
	)
{
	SHMENUBARINFO mbi;
	
	// fill in the menubar info struct
	ZeroMemory(&mbi, sizeof(mbi));
	mbi.cbSize = sizeof(mbi);
	mbi.hwndParent = hWnd;
	mbi.nToolBarId = nToolBarId;
	mbi.hInstRes = g_hInst;

	return SHCreateMenuBar(&mbi);
}


LPCTSTR UseString(
	UINT uID
	)
{
	//Return a pointer to a const resource string
	return (LPCTSTR)LoadString(g_hInst, uID, NULL, 0);
}

BOOL CreateListview(
	HWND hwndParent
	)
{
	LVCOLUMN 	lvc;
	INT			iRet;
	RECT		rc;
	HFONT		hf;
	LOGFONT		lf;

	GetClientRect(hwndParent, &rc);
	
	// create the listview
	// it is a child of the main window in report view which the user cannot sort
	g_hwndLV = CreateWindow(WC_LISTVIEW, TEXT("ListItem"), 
		WS_CHILD | LVS_EDITLABELS | LVS_REPORT | LVS_SORTASCENDING | WS_VISIBLE | WS_HSCROLL, 
		0, 0, rc.right, rc.bottom, hwndParent, NULL, g_hInst, NULL); 
	
	if (NULL == g_hwndLV) 
	{
		return FALSE; 
	}
	
	// enable full row select
	ListView_SetExtendedListViewStyle(g_hwndLV, LVS_EX_FULLROWSELECT);

	// setup headers
	lvc.mask		= LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvc.fmt			= 0;
	lvc.cx			= (rc.right - rc.left) / 2 - 20;
	lvc.cchTextMax	= 0;
	lvc.iSubItem	= 0;
	
	lvc.iImage		= 0;
	lvc.iOrder		= 0;
	
	// need to add columns in order
	
	// add column for name
	lvc.pszText = (LPTSTR)UseString(IDS_SIMMGR_COLUM_NAME);
	iRet = ListView_InsertColumn(g_hwndLV, lvc.iSubItem, &lvc);
	
	// add column for telephone number
	lvc.iSubItem++;
	lvc.pszText = (LPTSTR)UseString(IDS_SIMMGR_COLUMN_PHONE);
	iRet = ListView_InsertColumn(g_hwndLV, lvc.iSubItem, &lvc);

	// add column for index
	lvc.iSubItem++;
	lvc.cx = 40;
	lvc.pszText = (LPTSTR)UseString(IDS_SIMMGR_COLUMN_INDEX);
	iRet = ListView_InsertColumn(g_hwndLV, lvc.iSubItem, &lvc);
	
	// change the font
	lf.lfHeight = 12;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	_tcscpy(lf.lfFaceName, TEXT("Tahoma"));

	VERIFY(hf = CreateFontIndirect(&lf));

	SendMessage(g_hwndLV, WM_SETFONT, (WPARAM) hf, TRUE);

	return TRUE;
}


HWND GetLastActiveAppWindow(HWND hwndMain)
{
    LASTACTIVEWINDOW law;

    law.hwndLastActive = NULL;
    law.dwMainWindowThread = GetWindowThreadProcessId(hwndMain, NULL);
    
	if (EnumWindows(GetLastActiveAppWindowEnum, (LPARAM)&law))
    {
        return law.hwndLastActive;
    }

	return NULL;
}

BOOL CALLBACK GetLastActiveAppWindowEnum(HWND hWnd, LPARAM lParam)
{
    LASTACTIVEWINDOW *plaw;
    DWORD dwThread;

    plaw = (LASTACTIVEWINDOW *)lParam;
    dwThread = GetWindowThreadProcessId(hWnd, NULL);

    // Look for a same-thread, visible, enabled, !WS_EX_NOACTIVATE window.  
    // There should be only one if each of the app's dialogs/messageboxes disables its owner.
    if (dwThread == plaw->dwMainWindowThread &&
        TRUE == IsWindowVisible(hWnd) &&
        TRUE == IsWindowEnabled(hWnd) &&
        !(WS_EX_NOACTIVATE & GetWindowLong(hWnd, GWL_EXSTYLE)))
    {
        // Found active window
        plaw->hwndLastActive = hWnd;
        return FALSE;
    }

    // Keep enumerating
    return TRUE;
}


BOOL InitializeSIM()
{
	if (SUCCEEDED(SimInitialize(SIM_INIT_SIMCARD_NOTIFICATIONS, SimNotifProc, 0, &g_hSim)))
	{
		if (SUCCEEDED(SimGetDevCaps(g_hSim, SIM_CAPSTYPE_PBINDEXRANGE, &g_simcaps)))
		{
			// Allocate PB usage cache
			g_pbyteInUse = new BYTE[
				(g_simcaps.dwMaxPBIndex - g_simcaps.dwMinPBIndex)/(sizeof(*g_pbyteInUse)*8)];
			if (NULL != g_pbyteInUse)
				return TRUE;				
		}

		SimDeinitialize(g_hSim);
		g_hSim = NULL;
	}

	return FALSE;
}


void SimNotifProc(
	DWORD dwNotifyCode, 
	const void* pData, 
	DWORD dwDataSize, 
	DWORD dwParam
	)
{
	SIMPHONEBOOKENTRY spbe;
	int i;
	TCHAR	szSmallBuffer[SMALL_BUFFER];
	SIMPBECHANGE *pspc = NULL;
	BOOL	fDone = FALSE;
	int		iLVSelected;
	int		iLVItemCount;

    switch (dwNotifyCode)
    {
        case SIM_NOTIFY_PBE_STORED:
            pspc = (SIMPBECHANGE *) pData;
            DEBUGMSG(TRUE, (TEXT("Entry %d in storage %x changed\r\n"), pspc->dwEntry, pspc->dwStorage));

			// Is this a random PB addition?
			if (SIM_PBINDEX_FIRSTAVAILABLE == pspc->dwEntry)
			{
				// We don't know what record changed, so update everything
				RefreshListview();
			}
			else
			{
				// Can we get the PB data?
				if (SUCCEEDED(SimReadPhonebookEntry(g_hSim, g_dwLocation, pspc->dwEntry, &spbe)))
				{
					// Turn off LV redraw
					SendMessage(g_hwndLV, WM_SETREDRAW, (WPARAM)FALSE, NULL);

					// Add it to the ListView
					AddLVEntry(&spbe, pspc->dwEntry);

					// Turn on LV redraw
					SendMessage(g_hwndLV, WM_SETREDRAW, (WPARAM)TRUE, NULL);
				}
			}
			break;

        case SIM_NOTIFY_PBE_DELETED:
            pspc = (SIMPBECHANGE *) pData;
            DEBUGMSG(TRUE, (TEXT("Entry %d in storage %x changed\r\n"), pspc->dwEntry, pspc->dwStorage));

			// Get LV selection mark
			iLVSelected = ListView_GetSelectionMark(g_hwndLV);
			iLVItemCount = ListView_GetItemCount(g_hwndLV);

			// Was deleted the selected LV item?
			if (-1 != iLVSelected)
			{
				// Have a valid LV index, compare PB entry values
				ListView_GetItemText(g_hwndLV, iLVSelected, 2, szSmallBuffer, ARRAY_LENGTH(szSmallBuffer));

				// Find the index of the LV item that matches
				for(i = 0; i < iLVItemCount && pspc->dwEntry != (DWORD)_wtoi(szSmallBuffer); i++)
				{
					ListView_GetItemText(g_hwndLV, i, 2, szSmallBuffer, ARRAY_LENGTH(szSmallBuffer));
				}

				// Did we find a LV match?  //shouldn't happen
				if (i < iLVItemCount)
				{
					// Delete the LV entry
					ListView_DeleteItem(g_hwndLV, i ? i : iLVSelected);
				}
				
				if (!i)
				{
					if (iLVSelected == iLVItemCount - 1)
					{
						ListView_SetItemState(g_hwndLV, iLVSelected - 1, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
					}
				}

            break;
        }
            
        default:
            break;
    }
}

BOOL RefreshListview()
{
	SIMPHONEBOOKENTRY spbe;
	
	// sanity check
	ASSERT(g_hwndLV);

	// Turn off LV redraw
	SendMessage(g_hwndLV, WM_SETREDRAW, (WPARAM)FALSE, NULL);

	// Clear the contents of the ListView
	VERIFY(ListView_DeleteAllItems(g_hwndLV));

	// Clear PB usage cache
	ZeroMemory(g_pbyteInUse, (g_simcaps.dwMaxPBIndex - g_simcaps.dwMinPBIndex)/(sizeof(*g_pbyteInUse)*8));

	// Iterate through the entries, adding valid PB entries to the LV
	for(DWORD i = g_simcaps.dwMinPBIndex; i <= g_simcaps.dwMaxPBIndex; i++)
	{
		// assume: error means location is not being used
		if (SUCCEEDED(SimReadPhonebookEntry(g_hSim, g_dwLocation, i, &spbe)))
		{
			if (FALSE == AddLVEntry(&spbe, i))
			{
				return FALSE;
			}

			// Update PB usage cache
			g_pbyteInUse[(i-g_simcaps.dwMinPBIndex)/(sizeof(*g_pbyteInUse)*8)] |=
				(1<<((i-g_simcaps.dwMinPBIndex)%(sizeof(*g_pbyteInUse)*8)));
		}
	}

	//set default item
	ListView_SetItemState(g_hwndLV, 0, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);

	// Turn on LV redraw
	SendMessage(g_hwndLV, WM_SETREDRAW, (WPARAM)TRUE, NULL);

	// set the focus and return
	return TRUE;
}

BOOL AddLVEntry(
	LPSIMPHONEBOOKENTRY lpspbe, 
	DWORD dwIndex
	)
{
	LVITEM 		lvi;
	TCHAR		tszOut[SMALL_BUFFER];
	HWND		hwndLV = g_hwndLV;
	
	// set up the LVITEM structure
	ZeroMemory(&lvi, sizeof(LVITEM));
	
	lvi.mask = LVIF_TEXT | LVIF_STATE;

	// in subitem 0 lives the name
	lvi.pszText	= lpspbe->lpszText;
	lvi.cchTextMax = MAX_LENGTH_PHONEBOOKENTRYTEXT;

	int iItem = ListView_InsertItem(g_hwndLV, &lvi);
	int iSubItem = 0;
	
	if (-1 == iItem)
	{
		MessageBox(NULL, UseString(IDS_SIMMGR_INSERT_FAILED), UseString(IDS_SIMMGR_INSERT), MB_OK);
		return FALSE;
	}
	
	// in subitem 1 lives the phone number
	iSubItem++;
	ListView_SetItemText(g_hwndLV, iItem, iSubItem, lpspbe->lpszAddress);
	
	// in subitem 2 lives the index
	iSubItem++;
	_sntprintf(tszOut, ARRAY_LENGTH(tszOut), TEXT("%u"), dwIndex);
	ListView_SetItemText(g_hwndLV, iItem, iSubItem, tszOut);
	
	// it is good practice to ensure visible for all inserted items
	ListView_EnsureVisible(g_hwndLV, lvi.iItem, FALSE);

	return TRUE;
}

BOOL CALLBACK DialogProc(
	const HWND hDlg, 
	const UINT uiMessage, 
	const WPARAM wParam,
	const LPARAM lParam
	)
{
	HRESULT	hr;
	HWND	hwndText, hwndAddress;
	BOOL	bProcessedMsg = TRUE;
	SIMCAPS	sc;
	
	switch(uiMessage)
	{
		case WM_INITDIALOG:
			// create the dialog
			if (InitDialog(hDlg, IDR_SIMMGR_DLGMENU))
			{
				// get the device capabilities
				sc.cbSize = sizeof(SIMCAPS);
				hr = SimGetDevCaps(g_hSim, SIM_CAPSTYPE_PBENTRYLENGTH, &sc);
				if (SUCCEEDED(hr))
				{
					VERIFY(hwndText = GetDlgItem(hDlg, IDC_SIMMGR_NAME));
					SendMessage(hwndText, EM_SETLIMITTEXT, sc.dwMaxPBETextLength, 0);

					VERIFY(hwndAddress = GetDlgItem(hDlg, IDC_SIMMGR_PHONE));
					SendMessage(hwndAddress, EM_SETLIMITTEXT, sc.dwMaxPBEAddressLength, 0);
					break;
				}
			}
					
			EndDialog(hDlg, EINITFAILED);
			return TRUE;

		case WM_COMMAND:
			switch (wParam)
			{
				case IDM_SIMMGR_DONE:
					if (!AddPBEntry(hDlg))
					{
						EndDialog(hDlg, EADDFAILED);
					}
					else
					{
						EndDialog(hDlg, 0);
					}
					break;

				default:
					bProcessedMsg = FALSE;
					break;
			}
			break;
		case WM_HOTKEY:
			if ( HIWORD(lParam) == VK_TBACK )
			{
				SHSendBackToFocusWindow( uiMessage, wParam, lParam );
			}
			break;

		default:
			bProcessedMsg = FALSE;
			break;
	}

	return bProcessedMsg;
}

BOOL InitDialog(
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
	if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&mbi)))
		return FALSE;

	// set the title bar
	VERIFY(SetWindowText(hDlg, g_tszTitle));

	// In order to make Back work properly, it's necessary to 
	// override it and then call the appropriate SH API
	(void)SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
					  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
								 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;
}

BOOL AddPBEntry(
	HWND hDlg
	)
{
    SIMPHONEBOOKENTRY spbe;
	int iResult;
	DWORD dwIndex;
   
    // get the strings out of the text boxes
	iResult = GetDlgItemText(hDlg, IDC_SIMMGR_NAME, spbe.lpszText, MAX_LENGTH_PHONEBOOKENTRYTEXT);
	if (!iResult)
		return FALSE;

	iResult = GetDlgItemText(hDlg, IDC_SIMMGR_PHONE, spbe.lpszAddress, MAX_LENGTH_ADDRESS);
	if (!iResult)
		return FALSE;

    // set the other parameters
	spbe.cbSize = sizeof(SIMPHONEBOOKENTRY);
    spbe.dwParams = SIM_PARAM_PBE_ADDRESS | SIM_PARAM_PBE_ADDRESS_TYPE | SIM_PARAM_PBE_NUMPLAN | SIM_PARAM_PBE_TEXT;
    spbe.dwAddressType = SIM_ADDRTYPE_INTERNATIONAL;
    spbe.dwNumPlan = SIM_NUMPLAN_TELEPHONE;

    // Find first empty slot
	for(dwIndex = g_simcaps.dwMinPBIndex;
			(dwIndex <= (g_simcaps.dwMaxPBIndex - g_simcaps.dwMinPBIndex)) && 
		((g_pbyteInUse[(dwIndex-g_simcaps.dwMinPBIndex)/(sizeof(*g_pbyteInUse)*8)] & 
		(1<<((dwIndex-g_simcaps.dwMinPBIndex)%(sizeof(*g_pbyteInUse)*8)))));
			dwIndex++); // <-- Intentional

	if (dwIndex > (g_simcaps.dwMaxPBIndex - g_simcaps.dwMinPBIndex))
	{
		// Didn't find match, but try anyways
		dwIndex = SIM_PBINDEX_FIRSTAVAILABLE;
	}

	// Add an entry
    if (SUCCEEDED(SimWritePhonebookEntry(g_hSim, g_dwLocation, dwIndex, &spbe)))
	{
		// Update PB usage cache
		g_pbyteInUse[(dwIndex-g_simcaps.dwMinPBIndex)/(sizeof(*g_pbyteInUse)*8)] |= 
			(1<<((dwIndex-g_simcaps.dwMinPBIndex)%(sizeof(*g_pbyteInUse)*8)));
		
		return TRUE;
	}

	return FALSE;
}


BOOL DeletePBEntry()
{
	LVITEM lvi;
	LPTSTR pszName;
	TCHAR szIndex[INDEX_BUFFER];
	TCHAR szMessage[REASONABLE_BUFFER];
	TCHAR tszName[MAX_LENGTH_PHONEBOOKENTRYTEXT];
	int iSel, iResult;

	// get the currently selected entry
	iSel = ListView_GetSelectionMark(g_hwndLV);
	
	// if nothing was selected, return
	if (iSel == -1)
		return TRUE;

	// set the lvitem parameters - we just want the text...
	lvi.mask = LVIF_TEXT;
	lvi.iItem = iSel;
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR) &szIndex;
	lvi.cchTextMax = INDEX_BUFFER;
	
	// if we can't get the index, or we get an invalid index, return FALSE
	BOOL bRet = ListView_GetItem(g_hwndLV, &lvi);
	if (!bRet || !_ttoi(lvi.pszText))
		return FALSE;

	// if we can't get the name, return FALSE
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR) &tszName;
	lvi.cchTextMax = MAX_LENGTH_PHONEBOOKENTRYTEXT;
	if (!(bRet = ListView_GetItem(g_hwndLV, &lvi)))
		return FALSE;

	
	// delete confirmation
	pszName = tszName;
	FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
					UseString(IDS_SIMMGR_DELETEENTRY_CONFIRM), 0, 0, szMessage, 
					ARRAY_LENGTH(szMessage), (va_list*)&pszName);

	iResult = MessageBox(NULL, szMessage, g_tszTitle, MB_YESNO );

	// did the user agree?
	if (IDYES == iResult)
	{
		// Remove PB entry
		if (SUCCEEDED(SimDeletePhonebookEntry(g_hSim, g_dwLocation, _ttoi(szIndex))))
		{
			// Update PB usage cache
			g_pbyteInUse[(_ttoi(szIndex)-g_simcaps.dwMinPBIndex)/(sizeof(*g_pbyteInUse)*8)] &= 
				~(1<<((_ttoi(szIndex)-g_simcaps.dwMinPBIndex)%(sizeof(*g_pbyteInUse)*8)));
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	// if the user didn't agree, just return success...
	return TRUE;
}

BOOL DialPBEntry()
{
	int iSel;
	BOOL bRet;
	LONG lResult;
	LVITEM lvi;
	TCHAR tszPhoneNum[MAX_LENGTH_ADDRESS];

	// get the currently selected entry
	iSel = ListView_GetSelectionMark(g_hwndLV);
	
	// if nothing was selected, fail to make the call
	if (iSel == -1)
		return FALSE;

	// set the lvitem parameters - we just want the text...
	lvi.mask = LVIF_TEXT;
	lvi.iItem = iSel;
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR) &tszPhoneNum;
	lvi.cchTextMax = MAX_LENGTH_ADDRESS;

	// if we can't get the item, return FALSE
	bRet = ListView_GetItem(g_hwndLV, &lvi);
	if (FALSE == bRet)
	{
		return FALSE;
	}

	lResult = tapiRequestMakeCall(tszPhoneNum, NULL, NULL, NULL);

	return TRUE;
}

BOOL AddToOLContacts()
{
	int iSel;
	BOOL bRet;
	LVITEM lvi;
	TCHAR tszName[MAX_LENGTH_PHONEBOOKENTRYTEXT];
	TCHAR tszPhoneNum[MAX_LENGTH_ADDRESS];
	LPTSTR lptszFirstName = NULL;
	LPTSTR lptszLastName;
    IContact *pContact = NULL;
    HRESULT hr;

	// get the currently selected entry
	iSel = ListView_GetSelectionMark(g_hwndLV);
	
	// if nothing was selected, fail to make the call
	if (-1 == iSel) 
	{
		return FALSE;
	}

	// set the lvitem parameters - we just want the text...
	lvi.mask = LVIF_TEXT;
	lvi.iItem = iSel;
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR) &tszName;
	lvi.cchTextMax = MAX_LENGTH_PHONEBOOKENTRYTEXT;

	// if we can't get the item, return FALSE
	if (!(bRet = ListView_GetItem(g_hwndLV, &lvi)))
		return FALSE;

	// now get the phone number
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR) &tszPhoneNum;
	lvi.cchTextMax = MAX_LENGTH_ADDRESS;
	if (!(bRet = ListView_GetItem(g_hwndLV, &lvi)))
		return FALSE;

	// try to find the first space - for the purpose of this sample the character
	// after it will always be considered the beginning of the last name.
	// destructively modify tszName and point lptszLastName and lptszFirstName appropriately...
	lptszLastName = _tcschr(tszName, TEXT(' '));
	if (lptszLastName)
	{
		lptszLastName[0] = TEXT('\0');
		lptszLastName++;
		lptszFirstName = tszName;
	}
	else
	{
		lptszLastName = tszName;
	}

	// now that we have the names, try to create a new contact
	hr = g_polApp->CreateItem(olContactItem, (IDispatch **) &pContact);
	if (FAILED(hr))
	{
		return FALSE;
	}
    
	// put all the info into the contact
	if (lptszLastName)
		pContact->put_LastName(lptszLastName);

    if (lptszFirstName)
		pContact->put_FirstName(lptszFirstName);
	
	pContact->put_HomeTelephoneNumber(tszPhoneNum);

    pContact->Save();
    pContact->Release();

	return TRUE;
}

BOOL InitPOOM()
{
    HRESULT hr;

	// Start by initializing COM
    CoInitializeEx(NULL, 0);

    // Now, let's get the main application
    hr = CoCreateInstance(CLSID_Application, NULL, CLSCTX_INPROC_SERVER, IID_IPOutlookApp, (LPVOID*)&g_polApp);
	if (SUCCEEDED(hr))
	{
		// try logging on to pOL
		hr = g_polApp->Logon((long)g_hwndMain);
		if (SUCCEEDED(hr))
		{
			return TRUE;
		}

		g_polApp->Release();
	}

	CoUninitialize();

	return FALSE;
}

void CleanupPOOM()
{
    g_polApp->Logoff();
    g_polApp->Release();
    CoUninitialize();
}

