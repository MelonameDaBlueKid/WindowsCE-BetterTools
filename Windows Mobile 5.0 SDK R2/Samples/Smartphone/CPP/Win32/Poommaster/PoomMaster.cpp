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
// ************************************************************
// POOMMASTER.CPP
// 
// Implementation of application entry point and top-level processing
//
//
//

// Defines
#define INITGUID
#define MAX_LOADSTRING 100
#define MAX_LISTVIEW_ITEMS 32
#define FT_BOLD 0x1
#define FT_STRIKE 0x2
// Includes
#include <windows.h>
#include <pimstore.h>
#include <aygshell.h>
#include "PoomMaster.h"



// Global Variables:
HINSTANCE			g_hInst;				// The current instance
HWND				g_hwndCB;					// The command bar handle
HWND				g_hwndLV;					// The ListView control

HFONT				g_hfBaseFont;
HWND				g_hwndMain;
static int listcount = 0;
static SHACTIVATEINFO s_sai;


int g_nCurrFolder = olFolderTasks;
// Forward declarations of functions included in this code module:

LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);


HWND				CreateRpCommandBar(HWND, int);
HWND				CreateListView(HWND hwndParent);
void				RefreshListView(HWND hwndLV);
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow);
HFONT				BuildFont(HDC hDC, HFONT hBaseFont, DWORD dwFlags);


// **************************************************************************
// Function Name: WinMain
// 
// Purpose: Application entry point
//
// Arguments:
//	  IN HINSTANCE hInstance - handle to application instance
//	  IN HINSTANCE hPrevInstance - not used
//	  IN LPTSTR	lpCmdLine - command line string, not used
//    IN int nCmdShow - not used
//
// Return Values:
//    int
//    Application exit code
// 
// Description:  
//  This function defines the standard application entry point. It starts 
//	initialization and creates the main application dialog box
int WINAPI WinMain(	HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR    lpCmdLine,
				   int       nCmdShow)
{
	
	HACCEL hAccelTable;
	
	// Perform application initialization:
	INITCOMMONCONTROLSEX comctrex = { 0 };
	
	comctrex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	comctrex.dwICC  = ICC_DATE_CLASSES;
	InitCommonControls();
	InitCommonControlsEx(&comctrex);
	g_hInst = hInstance;
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_POOMMASTER);
	
	
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), 0, (DLGPROC)WndProc); 
	return 0;
}


// **************************************************************************
// Function Name: InitInstance
// 
// Purpose: Checks for existing instance of the app and activates it if existing
//
// Arguments:
//	 none
//
// Return Values:
//    BOOL
//    returns TRUE if there is no previously existing instance, FALSE otherwise
// 
// Description:  
//  This function tries to find an existing instance of the application window. 
//	This is a simple check, looking only for the name "PoomMaster" and does not
//	check for the window class. If the window is found, it is brought to the 
//	foreground
BOOL InitInstance(HINSTANCE hInstance, 
				  int nCmdShow)
{
	HWND	hWnd = NULL;
	TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
	
	
	g_hInst = hInstance;		// Store instance handle in our global variable
	// Initialize global strings
	
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	
	//If it is already running, then focus on the window
	hWnd = FindWindow(NULL, szTitle);	
	if (hWnd) 
	{
		// set focus to foremost child window
		// The "| 0x01" is used to bring any owned windows to the foreground and
		// activate them.
		SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
		return FALSE;
	} 
	
	return TRUE;
} 

// **************************************************************************
// Function Name: WndProc
// 
// Purpose: Processes messages for the main dialog window
//
// Arguments:
//    IN HWND hDlg - handle to the dialog window
//	  IN UINT message - indentifier for message to be processed
//	  IN WPARAM wParam - message parameter
//	  IN LPARAM lParam - message parameter
//
// Return Values:
//	  LRESULT
//		The return value is the result of the message processing and depends on 
//		the message sent.
// 
// Description:  
//    This is a standard dialog window message processing function. It handles 
//		the following:
//		WM_COMMAND - menu events
//		WM_INITDIALOG - dialog initialization
//		WM_DESTROY - window cleanup
//		WM_ACTIVATE - shell activation notification
//		WM_SETTINGCHANGE - system wide setting change notification
//		WM_DRAWITEM - owner-drawn painting of listview control
//		WM_MEASUREITEM - owner-drawn sizing of listview items
LRESULT CALLBACK WndProc(HWND hWnd, 
						 UINT message, 
						 WPARAM wParam, 
						 LPARAM lParam)
{
	HDC hdc;
	LPDRAWITEMSTRUCT lpdis;
	LPMEASUREITEMSTRUCT lpmi;
	
	switch (message) 
	{
	case WM_COMMAND:
		
		
		// Parse the menu selections:
		switch (LOWORD(wParam))
		{	
	
		case IDOK:
		case IDM_QUIT:
		
			EndDialog(hWnd, 0);
			break;
		case IDM_NEWITEM:
			switch (g_nCurrFolder)
			{
			case olFolderTasks:
				if (DialogBox(g_hInst, (LPCTSTR)IDD_NEWTASK, hWnd, (DLGPROC)NewTaskProc) == IDOK)
				{
					RefreshListView(g_hwndLV);
				}
				break;
			case olFolderContacts:
				if (DialogBox(g_hInst, (LPCTSTR)IDD_NEWCONTACT, hWnd, (DLGPROC)NewContactProc) == IDOK)
				{
					RefreshListView(g_hwndLV);
				}
				break;
			case olFolderCalendar:
				if (DialogBox(g_hInst, (LPCTSTR)IDD_NEWAPPNTMNT, hWnd, (DLGPROC)NewAppntmntProc) == IDOK)
				{
					RefreshListView(g_hwndLV);
				}
				break;
				
			}
			
			break;
			case IDM_MODE_CONTACTS:
				g_nCurrFolder = olFolderContacts;
				RefreshListView(g_hwndLV);SetWindowText(hWnd, _T("POOM Contacts"));
				break;
			case IDM_MODE_TASKS:
				g_nCurrFolder = olFolderTasks;
				RefreshListView(g_hwndLV);
		
				SetWindowText(hWnd, _T("POOM Tasks"));
				break;
			case IDM_MODE_CALENDAR:
				g_nCurrFolder = olFolderCalendar;
				RefreshListView(g_hwndLV);
				SetWindowText(hWnd, _T("POOM Calendar"));
				break;

		}
		break;
		case WM_INITDIALOG:
			SHINITDLGINFO shidi;
			
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hWnd;
			SHInitDialog(&shidi);
			
			g_hwndMain = hWnd;
			g_hwndCB = CreateRpCommandBar(hWnd, IDM_MAINMENU);
            // Initialize the shell activate info structure
            memset (&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
			
			if (InitPoom(hWnd))
			{
				
				// Create the ListView control
				g_hwndLV = CreateListView(hWnd);
				// populate the main listview display
				RefreshListView(g_hwndLV);
				SetWindowText(hWnd, _T("POOM Tasks"));
				
				// save our default starting font
				hdc = GetDC(g_hwndLV);
				g_hfBaseFont = (HFONT)GetCurrentObject(hdc, OBJ_FONT);
				ReleaseDC(g_hwndLV, hdc);
			
			}
			else 
			{
				//POOM could not initialize
				MessageBox(hWnd, _T("Cannot start POOM session"), _T("COM Error"), MB_OK);
				EndDialog(hWnd, IDOK);
			}
			return TRUE;
			
		case WM_DESTROY:
			// logout of POOM session
			ShutdownPoom();
			CommandBar_Destroy(g_hwndCB);
			break;
		case WM_ACTIVATE:
            // Notify shell of our activate message
			SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
			break;
		case WM_SETTINGCHANGE:
			SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
			break;
			
		case WM_DRAWITEM:
			// redraw a listview item...called for each item
			lpdis = (LPDRAWITEMSTRUCT)lParam;
			
			if (lpdis->CtlType == ODT_LISTVIEW)
			{
				TCHAR buf[64];
				HBRUSH hbrBkColor;
				HBRUSH hbrSEL;
				COLORREF crOldBkColor;
				COLORREF crOldTextColor;
				COLORREF crRed = RGB(255,0,0);
				DWORD dwFontFlags =0;
				HFONT hCustomFont = 0;
				
				hdc = lpdis->hDC;
				
				// save the current text and background colors
				crOldTextColor = GetTextColor(hdc);
				crOldBkColor = GetBkColor(hdc);
				
				
				hbrBkColor = CreateSolidBrush (crOldBkColor);
				hbrSEL = CreateSolidBrush (GetSysColor(COLOR_HIGHLIGHT));
				// make sure standard font is the default
				SelectObject(hdc, g_hfBaseFont);
				
				// if this item is selected, draw the highlight box
				if ((lpdis->itemAction | ODA_SELECT) && (lpdis->itemState & ODS_SELECTED))
				{
					SetTextColor(hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));
					FillRect(hdc, &lpdis->rcItem,hbrSEL);
				}
				// otherwise fill with standard background color and draw a rectangle around the item
				else
				{
					RECT r;
					
					FillRect(hdc, &lpdis->rcItem,hbrBkColor);
					r = lpdis->rcItem;
					Rectangle(hdc, r.left-1, r.top-1, r.right, r.bottom);
					
				}
				
				DeleteObject (hbrSEL);
				DeleteObject (hbrBkColor);
				
				ListView_GetItemText(g_hwndLV, lpdis->itemID, 0, buf, 64);
				// if viewing tasks, set some font properties
				if (g_nCurrFolder == olFolderTasks)
				{
					if (GetTaskPriority(lpdis->itemID) == olImportanceHigh)
					{
						// color text red to denote high importance
						SetTextColor(hdc, crRed);
						dwFontFlags |= FT_BOLD;
					}

					if (TaskIsComplete(lpdis->itemID))
					{
						// cross out if task is complete
						dwFontFlags |= FT_STRIKE;
						
					}
					
					// Build and select the font
					hCustomFont = BuildFont(hdc, g_hfBaseFont, dwFontFlags);
					SelectObject(hdc, hCustomFont) ;
				}
				
				// Draw the item's text
				DrawText(hdc, buf, _tcslen(buf),&lpdis->rcItem , DT_LEFT| DT_WORDBREAK |DT_TOP); 
				
				// Reset the background color and the text color back to their
				// original values.
				SetTextColor(hdc, crOldTextColor);
				SetBkColor(hdc, crOldBkColor);
			
				if (hCustomFont != 0)
				{
					DeleteObject(hCustomFont);
				}
				
				ReleaseDC (g_hwndLV, hdc);
			}
			
			return TRUE;
			
		case WM_MEASUREITEM:
			// set the height for each item box
			lpmi = (LPMEASUREITEMSTRUCT)lParam;
			lpmi->itemHeight= 36;
			
			return TRUE;
		
   }
   return FALSE;
}

// **************************************************************************
// Function Name: CreateRpCommandBar
// 
// Purpose: Creates a Rapier shell command bar
//
// Arguments:
//	 IN HWND hwnd - handle to parent window
//	 IN int nMenu - Resource ID of menu resource
//
// Return Values:
//    HWND
//    handle of created command bar
// 
// Description:  
//  This function creates a shell-specific menu bar specified by the given
//	resource ID. 
HWND CreateRpCommandBar(HWND hwnd, 
						int nMenu)
{
	SHMENUBARINFO mbi;
	
	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hwnd;
	mbi.nToolBarId = nMenu;
	mbi.hInstRes   = g_hInst;
	mbi.nBmpId     = 0;
	mbi.cBmpImages = 0;
	
	if (!SHCreateMenuBar(&mbi)) 
		return NULL;
	
	return mbi.hwndMB;
}



// **************************************************************************
// Function Name: CreateListView
// 
// Purpose: Create a listview control suitable for listing POOM items
//
// Arguments:
//	 IN HWND hwnd - handle to parent window
//
// Return Values:
//    HWND
//    handle of created list view control
// 
// Description:  
//  This function creates an owner-drawn listview control with a single column. 
//	All drawing is handled in the WM_DRAWITEM handler in WndProc. The list items are 
//	sized via the WM_MEASUREITEM handler.
HWND CreateListView(HWND hwndPrnt)
{
	HWND hwndRet = NULL;
	
    LV_COLUMN lvColumn;
	RECT mainRect;
	// Get the main rect
	GetClientRect (hwndPrnt, &mainRect);
	
	
	// Create ListView
	hwndRet = CreateWindow (WC_LISTVIEW, NULL,WS_CHILD | WS_VISIBLE | 
		LVS_REPORT | LVS_SINGLESEL | LVS_EDITLABELS | LVS_OWNERDRAWFIXED | LVS_NOCOLUMNHEADER, 
		0, 0, mainRect.right - mainRect.left, mainRect.bottom - mainRect.top, 
		hwndPrnt, NULL, g_hInst, 0);
	
	ListView_SetItemCount(hwndRet, MAX_LISTVIEW_ITEMS);
	
	// set column width to screen width
	lvColumn.mask = LVCF_WIDTH;
	lvColumn.cx = mainRect.right - mainRect.left;
	
	ListView_InsertColumn(hwndRet, 0, &lvColumn);
	
	return hwndRet;
}
// **************************************************************************
// Function Name: InitNewItemDlg
// 
// Purpose: Common intialization routine for new item dialogs
// Arguments:
//	 IN HWND hDlg - handle new dialog box
//
// Return Values:
//    BOOL
//    TRUE if initialization succeeds, FALSE otherwise
// 
// Description:  
//	This function supplies a common initialization implementation for all of the
//	apps New Item dialog boxes (New Contact, New Task, New Appointment). It provides
//  each dialog with the same shell properties and menu.  
BOOL InitNewItemDlg(HWND hDlg)
{
	
	SHINITDLGINFO shidi;
	
	
	shidi.dwMask = SHIDIM_FLAGS;
	shidi.dwFlags =  SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
    if (FALSE == IsSmartphone())
    {
        shidi.dwFlags = shidi.dwFlags | SHIDIF_DONEBUTTON;
    }
	shidi.hDlg = hDlg;
	if (!SHInitDialog(&shidi))
	{
		return FALSE;
	}
	
	return IsWindow(CreateRpCommandBar(hDlg, IDM_NEWITEMMENU));
	
}

// **************************************************************************
// Function Name: RefreshListView
// 
// Purpose: Create a listview control suitable for listing POOM items
//
// Arguments:
//	 IN HWND hwnd - handle to listview control
//
// Return Values:
//  none
// 
// Description:  
//  This function deletes and repopulates the the listview items with POOM 
//	data and sets the first item as selected.
void RefreshListView(HWND hwndLV)
{
	listcount = 0;
	ListView_DeleteAllItems (hwndLV);
	PopulateList(g_nCurrFolder);	
	ListView_SetItemState(hwndLV, 0, LVIS_SELECTED, LVIS_SELECTED);
}
// **************************************************************************
// Function Name: AddToList
// 
// Purpose: Add text to a listview item, then insert the item into the list
//
// Arguments:
//	 IN TCHAR * tszTxt - ptr to a string containing text to add to listview item
//
// Return Values:
//  none
// 
// Description:  
//	This function simply creates a listview item with text content, then adds it 
//	to the list. It also sets the item order (0 based) and sort parameter (1 based).
//	See LVITEM documentation for details 
void AddToList(TCHAR * tszTxt)
{
	LVITEM lv = {0};
	lv.mask = LVIF_TEXT | LVIF_STATE | LVIF_PARAM | LVIF_IMAGE;
	lv.iItem = listcount++;
	lv.lParam = listcount;
	lv.pszText = tszTxt;
	ListView_InsertItem (g_hwndLV, &lv);		
}
// **************************************************************************
// Function Name: GetCtrlText
// 
// Purpose: Get the displayed text from a given control
//
// Arguments:
//	 IN HWND hDlg - control's parent hwnd
//	 IN int nCtrlId - resource ID of the control
//	 OUT BSTR * pbstrTxt - length-prefixed buffer for returned string. Must be
//		freed (SysFreeString) by calling code
//
// Return Values:
//  none
// 
// Description:  
//  This function retrieves the specified control's window text and stores it in
// an newly allocated BSTR which is rerturned via output parameter. The allocated
// string must be be freed by the calling code with SysFreeString
void GetCtrlBstr(HWND hDlg, 
					 int nCtrlId, 
					 BSTR * pbstrTxt)
{
	int nLen = 0;
	
	nLen = GetWindowTextLength(GetDlgItem(hDlg, nCtrlId));
	(*pbstrTxt) = SysAllocStringLen(NULL, nLen+1);
	GetWindowText(GetDlgItem(hDlg, nCtrlId), *pbstrTxt, nLen+1);
	
}

HFONT BuildFont(HDC hDC, HFONT hBaseFont, DWORD dwFlags)
{
	LOGFONT lf;
	HFONT hFont = NULL;
	
	memset(&lf, 0, sizeof(LOGFONT));
	
	GetObject(hBaseFont, sizeof(lf), (LOGFONT*)&lf);
	
	if (dwFlags & FT_BOLD)
		lf.lfWeight=FW_BOLD;
	if (dwFlags & FT_STRIKE)
		lf.lfStrikeOut=TRUE;	
	
	return CreateFontIndirect(&lf);
}

// **************************************************************************
// Function Name: IsSmartphone
// 
// Purpose: Determine if platform is smartphone
//
// Arguments:
//	 none
//
// Return Values:
//  BOOL
//   TRUE if the current platform is a Smartphone platform
//   FALSE if the current platform is not a Smartphone platform
// 
// Description:  
//  This function retreives the current platforms type and then
// does a case insensitive string comparison.
BOOL IsSmartphone() 
{
    TCHAR tszPlatform[64];

    if (TRUE == SystemParametersInfo(SPI_GETPLATFORMTYPE,
         sizeof(tszPlatform)/sizeof(*tszPlatform),tszPlatform,0))
    {
        if (0 == _tcsicmp(TEXT("Smartphone"), tszPlatform)) 
        {
            return TRUE;
        }
    }
    return FALSE;   
}

void RemoveBorder(HWND hWndControl)
{
	DWORD dwStyles = GetWindowLong(hWndControl, GWL_STYLE);
	dwStyles = dwStyles & ~(WS_BORDER);
	SetWindowLong(hWndControl, GWL_STYLE, dwStyles);
}

