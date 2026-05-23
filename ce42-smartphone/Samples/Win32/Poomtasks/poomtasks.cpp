///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////
// poomtasks.cpp : Defines the entry point for the application.
//
// This file controls most of the windows and dialogs.  It contains
// the window procs and initializers.  



#include "poomtasks.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			 g_hInst;					// The current instance
HWND				 g_hwndCB;					// The command bar handle
HWND				 g_hwndLV;					// The list view handle
HFONT                g_hStrikeFont;             // Strike-out font

extern IFolder      *g_pTaskFolder;
extern IPOutlookApp *g_polApp;
extern FILTER        g_Filter;
extern SORT          g_Sort;

static SHACTIVATEINFO s_sai;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass	 (HINSTANCE, LPTSTR);
BOOL				InitInstance	 (HINSTANCE, int);
LRESULT CALLBACK	WndProc			 (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	EditDialogProc	 (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	NewDialogProc	 (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	SummaryDialogProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	OptionsDialogProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	SummaryWndProc   (HWND, UINT, WPARAM, LPARAM);

HWND CreateRpCommandBar(HWND);
BOOL CreateListView(HWND hwnd);

// Base state functions:
void CloseOwnedWindows(HWND hwndMain);
HWND GetLastActiveAppWindow(HWND hwndMain);
BOOL CALLBACK GetLastActiveAppWindowEnum(HWND hwnd, LPARAM lParam);

// ENTRY POINT FOR APPLICATION
// ----------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG     msg;
	TCHAR	szTitle      [MAX_LOADSTRING];		// The title bar text
	TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name
	INITCOMMONCONTROLSEX comctrex = { 0 };

	comctrex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	comctrex.dwICC  = ICC_DATE_CLASSES;

	// Initialize global strings
	LoadString(hInstance, IDC_POOMTASKS, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	if (FAILED(CoInitializeEx( NULL, 0)))
	{
		//Failed to initialize com, exit.
		DebugOut (TEXT("Failed CoInitializeEx, exiting app\n"));
		return 0;
	}

	// Use a globally named mutex to detect another instance of this application
    const HANDLE hMutex = CreateMutex(NULL, 0, TEXT("_POOMTASKS_MUTEX_"));

    // check the result code
	if(0 != hMutex) 
	{
		if(ERROR_ALREADY_EXISTS != GetLastError()) 
		{
			// No previous instance, go ahead and make the window
				
			// Perform application initialization:
			InitCommonControls();
			InitCommonControlsEx(&comctrex);
			if(!InitInstance(hInstance,nCmdShow)) 
			{
				return 0;
			}
		
			// Main message loop:
		    while(GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage (&msg);
				DispatchMessage(&msg);
			}
			return msg.wParam;
		}
		else
		{
			// If already an instance running - attempt to switch to it and then exit
			DebugOut (TEXT("Found Existing instance\n"));
			const HWND hWndExistingInstance = FindWindow(szWindowClass, szTitle);
			VERIFY((0 == hWndExistingInstance) || SetForegroundWindow(hWndExistingInstance));
			CloseOwnedWindows (hWndExistingInstance);
			SendMessage(hWndExistingInstance,WM_PAINT,0,0);
		}
		VERIFY(CloseHandle(hMutex));
	}

	//Clean up COM
	CoUninitialize();

	return 0;
}

// Short-hand to get string from resource
LPCTSTR UseString(UINT uID)
{
	return (LPCTSTR) LoadString(g_hInst, uID, NULL, 0);
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    It is important to call this function so that the application 
//    will get 'well formed' small icons associated with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
	WNDCLASS	wc;

    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POOMTASKS));
    wc.hCursor			= 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;

	return RegisterClass(&wc);
}

//
//  FUNCTION: InitInstance(HANDLE, int)
//
//  PURPOSE: Saves instance handle and creates main window
//
//  COMMENTS:
//
//    In this function, we save the instance handle in a global variable and
//    create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND	hWnd = NULL;
	TCHAR	szTitle      [MAX_LOADSTRING];		// The title bar text
	TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

	g_Filter = all;
	g_Sort   = importance;
	g_hInst  = hInstance;		// Store instance handle in our global variable

	// Initialize global strings
	LoadString(hInstance, IDC_POOMTASKS, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	MyRegisterClass(hInstance, szWindowClass);
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
	                    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{	
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


// Helpers for WndProc
HFONT BuildStrikeFont();

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
	int wmId, wmEvent;
	ITask*  pTask;
	LPNMHDR notifyinfo;
	int     selindex;
	int     iRow;
	LRESULT returnmsg;

	// POOM data recievers
	VARIANT_BOOL completed;
	HIMAGELIST hil;

	switch (message) 
	{
		case WM_COMMAND:
			selindex = ListView_GetSelectionMark (g_hwndLV);
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{	
				case IDM_COMPLETE:
					// Complete the currently selected task
					// Remember the index
					pTask = FindTask (selindex);
					if(pTask != NULL)
					{
						pTask->put_Complete(TRUE);
						pTask->Save();
						pTask->Release();
					}
					RefreshItems();
					// Restore the index
					ListView_SetItemState(g_hwndLV, selindex, LVIS_SELECTED | LVIS_FOCUSED,
						                  LVIS_SELECTED | LVIS_FOCUSED);
				    return TRUE; // dont refresh again at the bottom

				case IDM_ACTIVATE:
					// Activate the currently selected task
					pTask = FindTask(selindex);
					if (pTask != NULL)
					{
						pTask->put_Complete(FALSE);
						pTask->Save();
						pTask->Release();
					}
					RefreshItems();
					ListView_SetItemState(g_hwndLV, selindex, LVIS_SELECTED | LVIS_FOCUSED,
						                  LVIS_SELECTED | LVIS_FOCUSED);
					return TRUE; // dont refresh again at the bottom

				case IDM_TASK_NEW:
					// Bring up a dialog to create a new task
					DialogBox (g_hInst, MAKEINTRESOURCE(IDD_EDITDIALOG), g_hwndLV, (DLGPROC)NewDialogProc);
					break;
				case IDM_TASK_EDIT:
					// Load the data and populate a dialog
					pTask = FindTask (-1);
					if(pTask != NULL) 
					{
						DialogBox(g_hInst, MAKEINTRESOURCE(IDD_EDITDIALOG), g_hwndLV, (DLGPROC)EditDialogProc);
						pTask->Release();
					}
					break;
				case IDM_TASK_DELETE:
					// Delete the selected task, alert message box
					pTask = FindTask(-1);
					if(pTask!=NULL)
					{
						if(MessageBox(hWnd, UseString(IDS_MSG_DELETETASK),
						              UseString(IDS_TTL_DELETETASK),
									  MB_OKCANCEL | MB_ICONWARNING) == IDOK)
						{
							pTask->Delete();
						}
						pTask->Release();
					}
					break;

				case IDM_TASK_OPTIONS:
					DialogBox(g_hInst, MAKEINTRESOURCE (IDD_OPTIONS), g_hwndLV, (DLGPROC)OptionsDialogProc);
					break;

				case IDM_TASK_EXIT: 
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					return TRUE;

				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			RefreshItems();  // Refresh when the list view comes back
			SetFocus(g_hwndLV);
			ListView_SetItemState(g_hwndLV, selindex, LVIS_SELECTED | LVIS_FOCUSED, 
				                  LVIS_SELECTED | LVIS_FOCUSED);
			break;

		case WM_CREATE:
			g_hwndCB      = CreateRpCommandBar(hWnd);
			g_hStrikeFont = BuildStrikeFont();
			if(CreateListView(hWnd))
			{
				SetFocus(g_hwndLV);
			}
			else
			{
				DestroyWindow(hWnd);
			}
			break;

		case WM_PAINT:
			DebugOut(TEXT("WM_PAINT!!\n"));
			RefreshItems(); // In case another app has changed POOM
			break;
		case WM_ACTIVATE:
			DebugOut(TEXT("WM_ACTIVATE CALLED\n"));
			if(!(HWND)lParam)
			{	// Focus list view if we've switched applications
				SetFocus (g_hwndLV);
			}
			break;
		case WM_NOTIFY:
			// List view has had a change
			notifyinfo = (LPNMHDR)lParam;
			if(notifyinfo->code == NM_RETURN)
			{
				selindex = ListView_GetSelectionMark (g_hwndLV);
				DialogBox (g_hInst, MAKEINTRESOURCE(IDD_TASKSUMMARY), hWnd, (DLGPROC)SummaryDialogProc);
				RefreshItems();
				SetFocus (g_hwndLV);
				ListView_SetItemState(g_hwndLV, selindex, LVIS_SELECTED | LVIS_FOCUSED, 
					LVIS_SELECTED | LVIS_FOCUSED);
			}
				
			if (notifyinfo->code == NM_CUSTOMDRAW)  // Custom DRAWING!
			{
				
				LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)notifyinfo;

				switch(lplvcd->nmcd.dwDrawStage)
				{
					case CDDS_PREPAINT:
						UpdateMenus();
						return CDRF_NOTIFYITEMDRAW;          // ask for item notifications.
	
					case CDDS_ITEMPREPAINT:
						
						returnmsg = CDRF_DODEFAULT;
						iRow = lplvcd->nmcd.dwItemSpec;
						// need to get the outlook data
						DebugOut (TEXT("REQUESTING LIST ROW: %d\n"), iRow);
						pTask = FindTask (iRow);
						if(pTask != NULL)
						{
							if (IsOverdueTask (pTask))
							{
								lplvcd->clrText = RGB(255, 0, 0);
								returnmsg = CDRF_NEWFONT;
							}

							pTask->get_Complete (&completed); // If it's been completed, draw as strikeout
							if (completed)
							{
								SelectObject (lplvcd->nmcd.hdc, g_hStrikeFont); 
								lplvcd->clrText = RGB(150, 150, 150);
								returnmsg = CDRF_NEWFONT;
							}
							pTask->Release();

						}
						return returnmsg; // Otherwise do default drawing
						break;

					default:
						return CDRF_DODEFAULT;
				}

			}

			break;

		case WM_DESTROY:
			CommandBar_Destroy(g_hwndCB);
			hil = ListView_GetImageList (g_hwndLV, LVSIL_SMALL);
			if (hil != NULL)
				ImageList_Destroy (hil);
			DestroyWindow (g_hwndLV);
			if(g_polApp)
			{
				g_polApp->Logoff();		// Logoff Outlook
				DestructPoom ();		// Now cleanup poom stuff
			}
			DeleteObject(g_hStrikeFont);
			PostQuitMessage(0);
			break;
		case WM_SETTINGCHANGE:
			SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
     		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// BuildStrikeFont()
// --------------------
// Constructs the font for a completed task in the list view.
HFONT BuildStrikeFont ()
{
	LOGFONT lf;
	HFONT hfont;

	memset(&lf, 0, sizeof(lf));

	// Strike out font
	lf.lfHeight = 18;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = TRUE;
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	wsprintf(lf.lfFaceName, TEXT("Tahoma"));
	hfont = CreateFontIndirect (&lf);

	return hfont;
}

// CreateListView ()
// -------------------
// Initializing, it creates the list view in the main window.
BOOL CreateListView (HWND hwnd)
{
	RECT mainRect;
	// Get the main rect
	GetClientRect (hwnd, &mainRect);
	HIMAGELIST hil;
	HBITMAP hbm;
    LV_COLUMN lvColumn;

	// CreateListView
	g_hwndLV = CreateWindow (WC_LISTVIEW, NULL,WS_CHILD | WS_VISIBLE | 
				LVS_REPORT | LVS_SINGLESEL | LVS_EDITLABELS | LVS_NOCOLUMNHEADER | WS_VSCROLL, 0, 0, 
					mainRect.right - mainRect.left, mainRect.bottom - mainRect.top, 
					hwnd, NULL, g_hInst, 0);

	// Setup Listview
    ListView_SetExtendedListViewStyle(g_hwndLV, 
		ListView_GetExtendedListViewStyle(g_hwndLV) | LVS_EX_FULLROWSELECT);

	lvColumn.mask = LVCF_WIDTH;
	lvColumn.cx = mainRect.right - mainRect.left - GetSystemMetrics(SM_CXVSCROLL);

	if(-1 == ListView_InsertColumn(g_hwndLV, 0, &lvColumn))
	{
		DebugOut (TEXT("Failed to add column to ImageList\n"));
	}

	// Setup ImageList
	hil = ImageList_Create(PIMTASK_PRIORITY_CXICON, PIMTASK_PRIORITY_CYICON, ILC_MASK, 3, 5);
	if ((hbm = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_PRIORITY))) && (hil != NULL))
	{
		ImageList_AddMasked(hil, hbm, RGB(255, 0, 0));
        DeleteObject(hbm);
		ListView_SetImageList (g_hwndLV, hil, LVSIL_SMALL);
	}
	else
		DebugOut (TEXT("Failed to initiate ImageList\n"));

	return GetTaskCollection(hwnd);
}

// CreateRpCommandBar ()
// -----------------------
// Creates the menu bar for the main application.
HWND CreateRpCommandBar(HWND hwnd)
{
	SHMENUBARINFO mbi;

	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hwnd;
	mbi.nToolBarId = IDM_MENU;
	mbi.hInstRes   = g_hInst;
	mbi.nBmpId     = 0;
	mbi.cBmpImages = 0;

	if (!SHCreateMenuBar(&mbi)) 
		return NULL;

	return mbi.hwndMB;
}

// SetDialogDefaults
// ---------------------------------
// Fills spinner controls with the different choices
// Also sets default selections.
void SetDialogDefaults (HWND hDlg)
{
	HWND control;
	SYSTEMTIME systime;

	GetSystemTime (&systime);
	control = GetDlgItem (hDlg, IDC_PRIORITYLIST);
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_PRIORITY_LOW)); 
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_PRIORITY_NORMAL));
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_PRIORITY_HIGH));
	SendMessage (control, LB_SETCURSEL, 1, 0);

	control = GetDlgItem (hDlg, IDC_STATUSLIST);
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_STATUS_NOTCOMP));
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_STATUS_COMP));
	SendMessage (control, LB_SETCURSEL, 0, 0);

	// Set dates to none:
	control = GetDlgItem (hDlg, IDC_STARTDATE);
	SendMessage (control, DTM_SETSYSTEMTIME, GDT_NONE, NULL);
	control = GetDlgItem (hDlg, IDC_DUEDATE);
	SendMessage (control, DTM_SETSYSTEMTIME, GDT_NONE, NULL);
	control = GetDlgItem (hDlg, IDC_REMINDER);
	SendMessage (control, DTM_SETSYSTEMTIME, GDT_NONE, NULL);

	control = GetDlgItem (hDlg, IDC_OCCURSLIST);
	SetRecurrenceControls (control, systime);
	SendMessage (control, LB_SETCURSEL, 0, 0);
}


// Helper for Edit and New Proc
void UpdateRecurrencesFromStartDate (HWND hDlg);

// Mesage handler for the Edit Dialog
LRESULT CALLBACK EditDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	SHINITDLGINFO shidi;
	SHMENUBARINFO shmbi;
	ITask* pTask = NULL;

	switch (message)
	{
		case WM_INITDIALOG: 
			ZeroMemory(&shidi, sizeof(shidi));
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;

			// Set up the menu bar
		
			ZeroMemory(&shmbi, sizeof(shmbi));
			shmbi.cbSize = sizeof(shmbi);
			shmbi.hwndParent = hDlg;
			shmbi.nToolBarId = IDR_EDITMENU;
			shmbi.hInstRes = g_hInst;

			// If we could not initialize the dialog box, return an error
			if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
				DebugOut (TEXT("Failed to make menubar\n"));
				EndDialog(hDlg, -1);
			}
			else
			{
				// Overriding Back button functionality
				(void)SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
				  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
							 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));
				
				// set the title bar
				SetWindowText(hDlg, UseString(IDS_EDIT_TASK));
				SetDialogDefaults (hDlg);
				pTask = FindTask(-1);
				GetTaskData (hDlg, pTask);
				pTask->Release();
			}
			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDM_SAVE:
				pTask = FindTask(-1);
				if (pTask == NULL)
					break;

				SetTaskData (hDlg, pTask);
				EndDialog(hDlg, LOWORD(wParam));
				pTask->Release();
				return TRUE;
			
			case IDCANCEL: //Fall through
			case IDM_CANCEL: 
				EndDialog (hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
			
		case WM_HOTKEY: // Override the back key to delete
			{
				if (VK_TBACK == HIWORD(lParam))
				{
					SHSendBackToFocusWindow (message, wParam, lParam);
				}
				// Override home key?
			}
			break;

		case WM_NOTIFY:
			{
				if (wParam == IDC_STARTDATE)
				{
					UpdateRecurrencesFromStartDate (hDlg);
				}	
			}
			break;

	}
    return FALSE;
}

// Mesage handler for the New Dialog
LRESULT CALLBACK NewDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;
	SHINITDLGINFO shidi;
	SHMENUBARINFO shmbi;
	ITask* pTask = NULL;

	switch (message)
	{
		case WM_INITDIALOG: 
			ZeroMemory(&shidi, sizeof(shidi));
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;

			// Set up the menu bar
		
			ZeroMemory(&shmbi, sizeof(shmbi));
			shmbi.cbSize = sizeof(shmbi);
			shmbi.hwndParent = hDlg;
			shmbi.nToolBarId = IDR_EDITMENU;
			shmbi.hInstRes = g_hInst;

			// If we could not initialize the dialog box, return an error
			if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
				DebugOut (TEXT("Failed to make menubar\n"));
				EndDialog(hDlg,-1);
				return TRUE;
			}

			// Overriding Back button functionality
			(void)SendMessage(shmbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
			  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
						 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));
			
			// set the title bar
			SetWindowText(hDlg, UseString(IDS_NEW_TASK));
			SetDialogDefaults (hDlg);
			// Load defaults
			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDM_SAVE:
				hr = g_polApp->CreateItem (olTaskItem, (IDispatch**)&pTask);
				if (FAILED (hr))
				{
					DebugOut (TEXT("Could not save data\n"));
					return FALSE;
				}

				SetTaskData (hDlg, pTask);
				EndDialog(hDlg, LOWORD(wParam));
				pTask->Release();
				return TRUE;
			
			case IDCANCEL: // Fall through
			case IDM_CANCEL: 
				EndDialog (hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;

		case WM_HOTKEY: // Override the back key to delete
			{
				if (VK_TBACK == HIWORD(lParam))
				{
					SHSendBackToFocusWindow (message, wParam, lParam);
				}
			}
			break;
		case WM_NOTIFY:
			{
				if (wParam == IDC_STARTDATE)
				{
					UpdateRecurrencesFromStartDate (hDlg);	
				}	
			}
			break;
	}
    return FALSE;
}


// UpdateRecurrencesFromStartDate ()
// ---------------------------------
// This function is used to dynamically update the choices in the
// spinner control for recurrences based on the start date changing.
void UpdateRecurrencesFromStartDate (HWND hDlg)
{
	HWND startcontrol;
	HWND reccontrol;
	SYSTEMTIME starttime;
	int selection;

	startcontrol = GetDlgItem (hDlg, IDC_STARTDATE);
	// Reset the recurrence box
	if (SendMessage (startcontrol, DTM_GETSYSTEMTIME, 0, (LPARAM)&starttime) == GDT_NONE)
	{
		GetSystemTime (&starttime);
	}

	// Retrieve original selection
	reccontrol = GetDlgItem (hDlg, IDC_OCCURSLIST);
	selection = SendMessage (reccontrol, LB_GETCURSEL, 0, 0);
	SetRecurrenceControls (reccontrol, starttime);
	// Restore original selection
	SendMessage (reccontrol, LB_SETCURSEL, selection, 0);
}

// InitSummaryDialog ()
// ---------------------
// Initializes the information in the summary dialog to reflect task information
BOOL InitSummaryDialog (HWND hDlg, ITask* pTask)
{
	BSTR taskstr;
	TCHAR sdatebuff[100];
	TCHAR ddatebuff[100];
	DATE date;
	VARIANT datevar;
	HWND hwndLabel;
	VARIANT_BOOL completed;
	HRESULT hr;

	if (pTask == NULL)
			return FALSE;

	hr = pTask->get_Subject (&taskstr);
	hwndLabel = GetDlgItem (hDlg, IDC_SUMMARY_SUBJECT);
	if (hr == S_OK)
	{
		SendMessage (hwndLabel, WM_SETTEXT, 0, (LPARAM)taskstr);
		SysFreeString (taskstr);
	}

	// Show completion date if completed
	pTask->get_Complete (&completed);
	if (completed)
	{
		pTask->get_DateCompleted (&date);
		hwndLabel = GetDlgItem (hDlg, IDC_SUMMARY_STARTDATE);
		datevar.date = date;
		datevar.vt = VT_DATE;
		VariantChangeType (&datevar, &datevar, 0, VT_BSTR);
		lstrcpy (sdatebuff, UseString(IDS_SUMMARY_COMPLETED));
		if (date == DATE_NONE)
			lstrcat (sdatebuff, UseString(IDS_SUMMARY_NONE));
		else
			lstrcat (sdatebuff, datevar.bstrVal);
		VariantClear(&datevar);
		SendMessage (hwndLabel, WM_SETTEXT, 0, (LPARAM)sdatebuff);
	}
	else
	{
		
		// Start Date
		pTask->get_StartDate (&date);
		hwndLabel = GetDlgItem (hDlg, IDC_SUMMARY_STARTDATE);
		datevar.date = date;
		datevar.vt = VT_DATE;
		VariantChangeType (&datevar, &datevar, 0, VT_BSTR);
		lstrcpy (sdatebuff, UseString(IDS_SUMMARY_START));
		if (date == DATE_NONE)
			lstrcat (sdatebuff, UseString(IDS_SUMMARY_NONE));
		else
			lstrcat (sdatebuff, datevar.bstrVal);
		VariantClear(&datevar);
		SendMessage (hwndLabel, WM_SETTEXT, 0, (LPARAM)sdatebuff);
	}

	// Due Date
	pTask->get_DueDate (&date);
	hwndLabel = GetDlgItem (hDlg, IDC_SUMMARY_DUEDATE);
	datevar.date = date;
	datevar.vt = VT_DATE;
	VariantChangeType (&datevar, &datevar, 0, VT_BSTR);
	lstrcpy (ddatebuff, UseString(IDS_SUMMARY_DUE));
	if (date == DATE_NONE)
		lstrcat (ddatebuff, UseString(IDS_SUMMARY_NONE));
	else
		lstrcat (ddatebuff, datevar.bstrVal);
	VariantClear(&datevar);
	SendMessage (hwndLabel, WM_SETTEXT, 0, (LPARAM)ddatebuff);

	// Notes
	hr = pTask->get_Body (&taskstr);
	hwndLabel = GetDlgItem (hDlg, IDC_SUMMARY_NOTES);

	if (hr == S_OK)
	{
		SendMessage (hwndLabel, WM_SETTEXT, 0, (LPARAM)taskstr);
		SysFreeString (taskstr);
	}
	pTask->Release();
	
	return TRUE;

}

// Helper for SummaryDialogProc
BOOL OnSummaryKey (HWND hDlg, int move);
BOOL PaintSummary (HWND hDlg);

// Mesage handler for the Summary Dialog
LRESULT CALLBACK SummaryDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
//	HRESULT hr;
	SHINITDLGINFO shidi;
	SHMENUBARINFO shmbi;
	ITask* pTask;

	switch (message)
	{
		case WM_INITDIALOG: 

			DebugOut (TEXT ("WM_INITDIALOG !!\n"));
			ZeroMemory(&shidi, sizeof(shidi));
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;

			// Set up the menu bar
		
			ZeroMemory(&shmbi, sizeof(shmbi));
			shmbi.cbSize = sizeof(shmbi);
			shmbi.hwndParent = hDlg;
			shmbi.nToolBarId = IDR_SUMMARYMENU;
			shmbi.hInstRes = g_hInst;

			// If we could not initialize the dialog box, return an error
			if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
				DebugOut (TEXT("Failed to make menubar\n"));
				EndDialog(hDlg,-1);
				return TRUE;
			}

			DebugOut (TEXT ("InitSummaryDialog\n"));
			// Setup Dialog data
			pTask = FindTask (-1);
			if (pTask == NULL)
			{
				EndDialog (hDlg, FALSE);
				return FALSE;
			}
			
			if (InitSummaryDialog (hDlg, pTask) == FALSE)
				return FALSE;

			// set the title bar
			SetWindowText(hDlg, UseString(IDS_TASK_SUMMARY));
			pTask->Release();

			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDM_TASK_EDIT:
				pTask = FindTask(-1);
				if (pTask == NULL)
					return FALSE;

				DialogBox(g_hInst, MAKEINTRESOURCE(IDD_EDITDIALOG), hDlg, (DLGPROC)EditDialogProc);
				EndDialog (hDlg, TRUE);	
				pTask->Release();
				return TRUE;
			
			case IDCANCEL: // Fall through
			case IDM_OK: 
				EndDialog (hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;

		case WM_KEYUP:
			DebugOut (TEXT("KEY PRESSED\n"));
			switch (wParam)
			{
			case VK_TRIGHT: // next task
				OnSummaryKey (hDlg, 1);
				break;
			case VK_TLEFT: // prev task
				OnSummaryKey (hDlg, -1);
				break;
			}
			
			SendMessage (hDlg, WM_PAINT, 0, 0); // All keys should refresh screen
			break;

			case WM_NOTIFY:
				DebugOut (TEXT("NOTIFIED!\n"));
				break;
			case WM_PAINT:
				PaintSummary (hDlg);
				break;



	}
    return FALSE;
}

// PaintSummary ()
// ------------------
// Draws the graphical elements of the summary
// This includes the priority icon and the horizontal rule.
BOOL PaintSummary (HWND hDlg)
{
	ITask* pTask = NULL;
	HDC hdc;
	RECT dialogrect;
	POINT hrule[2];
	HPEN hpen;
	HIMAGELIST hil;
	long priority;

	// draw the horizontal rule
	hpen = CreatePen (PS_SOLID, 1, RGB(0, 0, 0));
	hdc = GetDC (hDlg);
	SelectObject (hdc, hpen);
	GetClientRect (hDlg, &dialogrect);
	hrule[0].x = 0;
	hrule[0].y = 65;
	hrule[1].x = dialogrect.right;
	hrule[1].y = 65;
	Polyline (hdc, hrule, 2);
	
	// Draw Priority Icon
	hdc = GetDC (NULL);
	pTask = FindTask(-1);
	if (pTask == NULL)
		return FALSE;

	pTask->get_Importance (&priority);
	hil = ListView_GetImageList (g_hwndLV, LVSIL_SMALL);
	if (hdc != NULL && hil != NULL)
	{
		switch (priority)
		{
		case olImportanceLow:
			ImageList_Draw (hil, 1, hdc, dialogrect.right - 20, 20, ILD_NORMAL );
			break;
		case olImportanceHigh:
			DebugOut (TEXT("DRAWING IMAGE HIGH!\n"));
			ImageList_Draw (hil, 0, hdc, dialogrect.right - 20, 20, ILD_NORMAL );
			break;
		default:
			ImageList_Draw (hil, 2, hdc, dialogrect.right - 20, 20, ILD_NORMAL );
			break;
		}
	}
	pTask->Release();
	return TRUE;
}

// OnSummaryKey ()
// -------------------
// Responds to left and right keys in the summary view
// It will change the displayed task.
BOOL OnSummaryKey (HWND hDlg, int move)
{
	int selindex;
	int numtasks;
	ITask* pTask;

	selindex = ListView_GetSelectionMark (g_hwndLV);
	numtasks = ListView_GetItemCount (g_hwndLV);
	selindex += move;
	if (selindex < 0)
		selindex = numtasks - 1; // Can't even get into this dialog unless there is 1 task
	else
		selindex = selindex % numtasks;

	ListView_SetSelectionMark (g_hwndLV, selindex);
	DebugOut (TEXT("SELECTION %d\n"), selindex);
	pTask = FindTask (-1);
	if (pTask == NULL)
		return FALSE;

	InitSummaryDialog (hDlg, pTask);
	if (pTask != NULL)
		pTask->Release();

	return TRUE;
}

// SetOptionsDefaults ()
// -------------------------
// This fills the spinner controls and selection states for the options dialog
void SetOptionDefaults (HWND hDlg)
{
	HWND control;

	control = GetDlgItem (hDlg, IDC_SORTLIST);
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_PRIORITY)); 
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_STATUS));
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_SUBJECT));
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_STARTDATE));
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_DUEDATE));
	SendMessage (control, LB_SETCURSEL, 0, 0);

	control = GetDlgItem (hDlg, IDC_CATEGORYLIST);
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_ALLCATEGORIES)); 
	SendMessage (control, LB_SETCURSEL, 0, 0);

	control = GetDlgItem (hDlg, IDC_DISPLAYLIST);
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_ALLTASKS)); 
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_COMPLETED));
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_OPTIONS_ACTIVE));
	SendMessage (control, LB_SETCURSEL, g_Filter, 0);
}

// Mesage handler for the Options Dialog
LRESULT CALLBACK OptionsDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
//	HRESULT hr;
	SHINITDLGINFO shidi;
	SHMENUBARINFO shmbi;

	switch (message)
	{
		case WM_INITDIALOG: 

			DebugOut (TEXT ("WM_INITDIALOG !!\n"));
			ZeroMemory(&shidi, sizeof(shidi));
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;

			// Set up the menu bar
		
			ZeroMemory(&shmbi, sizeof(shmbi));
			shmbi.cbSize = sizeof(shmbi);
			shmbi.hwndParent = hDlg;
			shmbi.nToolBarId = IDR_OPTIONSMENU;
			shmbi.hInstRes = g_hInst;

			// If we could not initialize the dialog box, return an error
			if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&shmbi))) {
				DebugOut (TEXT("Failed to make menubar\n"));
				EndDialog(hDlg,-1);
				return TRUE;
			}

			DebugOut (TEXT ("InitOptionsDialog\n"));
			SetOptionDefaults (hDlg);
		
			// set the title bar
			SetWindowText(hDlg, UseString(IDS_OPTIONS));

			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDM_OK:
				SetOptions (hDlg);
				EndDialog (hDlg, TRUE);		
				return TRUE;
			
			case IDCANCEL: // Fall through
			case IDM_CANCEL: 
				EndDialog (hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


// Helper for UpdateMenus()
BOOL EnableMenus (BOOL enable);

// UpdateMenus()
// ------------------
// Changes the left softkey of the main window to reflect the
// current selection state in the list view.  Also dimms the Edit
// option in th menu if no task is selected.
void UpdateMenus ()
{
	VARIANT_BOOL completed;
	ITask* pTask;

	TBBUTTONINFO tbbi;

	tbbi.cbSize  = sizeof(tbbi);
	tbbi.dwMask  = TBIF_LPARAM;

	// Get the current task
	pTask = FindTask (-1);

	TBBUTTONINFO tbbiContext;
	tbbiContext.cbSize = sizeof(tbbi);
	tbbiContext.dwMask = TBIF_COMMAND | TBIF_STATE;

	if (pTask == NULL)
	{
		EnableMenus (FALSE);
		return;
	}

	EnableMenus (TRUE);

	pTask->get_Complete (&completed);

	// set the left soft key
	tbbiContext.dwMask = TBIF_COMMAND | TBIF_TEXT;
	
	// if the item is completed, left softkey should be ACTIVATE
	// otherwise it should be COMPLETE
	DebugOut (TEXT("UPDATING MENUS\n"));
	if (completed) {
		tbbiContext.idCommand = IDM_ACTIVATE;
		(LPCTSTR&)tbbiContext.pszText = UseString(IDS_ACTIVATE);
		SendMessage(g_hwndCB, TB_SETBUTTONINFO, 
					IDM_COMPLETE, (LPARAM) &tbbiContext);
		DebugOut (TEXT("Changed to ACTIVATE\n"));
	} else {
		tbbiContext.idCommand = IDM_COMPLETE;
		(LPCTSTR&)tbbiContext.pszText = UseString(IDS_COMPLETE);
		SendMessage(g_hwndCB, TB_SETBUTTONINFO, 
					IDM_ACTIVATE, (LPARAM) &tbbiContext);
		DebugOut (TEXT("Changed to COMPLETE\n"));
	}

	// cleanup
	pTask->Release();
}

// EnableMenus()
// -----------------
// A helper for UpdateMenus(), it does the actual changing of the 
// button information.
BOOL EnableMenus (BOOL enable)
{
	TBBUTTONINFO tbbiContext;
	HMENU hmenu;
	tbbiContext.cbSize = sizeof(tbbiContext);
	tbbiContext.dwMask = TBIF_COMMAND | TBIF_STATE;

	if (enable)
		tbbiContext.fsState = TBSTATE_ENABLED;
	else
		tbbiContext.fsState = TBSTATE_INDETERMINATE;

	tbbiContext.idCommand = IDM_ACTIVATE;
	SendMessage (g_hwndCB, TB_SETBUTTONINFO, IDM_ACTIVATE, (LPARAM)&tbbiContext);
	
	tbbiContext.idCommand = IDM_COMPLETE;
	SendMessage (g_hwndCB, TB_SETBUTTONINFO, IDM_COMPLETE, (LPARAM)&tbbiContext);

	tbbiContext.idCommand = IDM_TASK_EDIT;
	SendMessage (g_hwndCB, TB_SETBUTTONINFO, IDM_TASK_EDIT, (LPARAM)&tbbiContext);

	tbbiContext.dwMask = TBIF_LPARAM;
	SendMessage (g_hwndCB, TB_GETBUTTONINFO, IDM_TASK_MENU, (LPARAM)&tbbiContext);
	hmenu = (HMENU)tbbiContext.lParam;

	if (enable)
		EnableMenuItem (hmenu, IDM_TASK_EDIT, MF_BYCOMMAND | MF_ENABLED);
	else
		EnableMenuItem (hmenu, IDM_TASK_EDIT, MF_BYCOMMAND | MF_GRAYED);

	return TRUE;
}

// FORCING BASE STATE CODE

// App's dialogs and windows should handle WM_COMMAND/IDCANCEL appropriately.
// A Message Box will close when sent a WM_COMMAND IDCANCEL

// Close windows owned by hwndMain 
// Assumes that all the app's dialogs and message boxes have owners
// and that the top of the owner list is hwndMain.
// Also assumes that the dialogs and messageboxes disable their owner
// (Modal dialogs and message boxes automatically disable their owner.)
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