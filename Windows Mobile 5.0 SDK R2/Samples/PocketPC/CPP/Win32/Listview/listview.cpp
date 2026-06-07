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
/****************************************************************************
*
*
*    PROGRAM: ListView.cpp
*
*    PURPOSE: Demonstrates the use of the list view control
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "listview.h"

// global current instance
HINSTANCE hInst;

// global array of houses
HOUSEINFO rgHouseInfo[] = 
{
	{TEXT("100 Berry Lane"), TEXT("Redmond"), 175000, 3, 2 },
	{TEXT("523 Apple Road"), TEXT("Redmond"), 125000, 4, 2},
	{TEXT("1212 Peach Street"), TEXT("Redmond"),200000, 4, 3},
	{TEXT("22 Daffodil Lane"), TEXT("Bellevue"), 2500000, 4, 4},
	{TEXT("33542 Orchid Road"), TEXT("Bellevue"), 180000, 3, 2},
	{TEXT("64134 Lily Street"), TEXT("Bellevue"), 250000, 4, 3},
	{TEXT("33 Nicholas Lane"), TEXT("Seattle"), 350000, 3, 2},
	{TEXT("555 Tracy Road"), TEXT("Seattle"), 140000, 3, 2},
	{TEXT("446 Jean Street"), TEXT("Seattle"), 225000, 4, 3}
};

//handle to the MenuBar
HWND hwndCB;
HMENU hmenuCB;

/////////////////////////// Pocket PC only samples ///////////////////////
#if _WIN32_WCE < 212//non-Pocket PC devices
#error 'This sample works on Pocket PC devices only'
#endif
#include <aygshell.h>


////////////////////////// SHGetMenu Macro's
#if _WIN32_WCE > 211 //Pocket PC devices

//#define SHCMBM_SETSUBMENU   (WM_USER + 400)
//#define SHCMBM_GETSUBMENU   (WM_USER + 401) // lParam == ID
//#define SHCMBM_GETMENU      (WM_USER + 402) // get the owning hmenu (as specified in the load resource)

#define SHGetMenu(hWndMB)  (HMENU)SendMessage((hWndMB), SHCMBM_GETMENU, (WPARAM)0, (LPARAM)0);
#define SHGetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);
#define SHSetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_SETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

//Alternate definition
#define SHMenuBar_GetMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

#else //non-Pocket PC devices

#define SHGetMenu(hWndCB) (HMENU)CommandBar_GetMenu(hWndCB, 0)
#define SHGetSubMenu(hWndCB,ID_MENU) (HMENU)GetSubMenu((HMENU)CommandBar_GetMenu(hWndCB, 0), ID_MENU)
#define SHSetSubMenu(hWndMB,ID_MENU)

#endif
/////////////////////////
//Menu Bar Height
#define MENU_HEIGHT 26


/****************************************************************************
*
*    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*    PURPOSE: calls initialization function, processes message loop
*
****************************************************************************/

int APIENTRY WinMain(
					 HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR lpCmdLine,
					 int nCmdShow
					 )
{
	
	MSG msg;                       
	
	if (!InitApplication(hInstance))
		return (FALSE);     
	
	/* Perform initializations that apply to a specific instance */
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);
	
	/* Acquire and dispatch messages until a WM_QUIT message is received. */
	while (GetMessage(&msg,
		NULL,              
		0,                 
		0))                
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return (msg.wParam);  
	
}


/****************************************************************************
*
*    FUNCTION: InitApplication(HANDLE)
*
*    PURPOSE: Initializes window data and registers window class
*
****************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)       /* current instance             */
{
	WNDCLASS  wcListview;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */
	
	wcListview.style = 0;                     
	wcListview.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcListview.cbClsExtra = 0;              
	wcListview.cbWndExtra = 0;              
	wcListview.hInstance = hInstance;       
	wcListview.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(APP_ICON));
	wcListview.hCursor = 0;
	wcListview.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
	wcListview.lpszMenuName =  0;  
	wcListview.lpszClassName = TEXT("ListviewWClass");
	
	return (RegisterClass(&wcListview));
	
}


/****************************************************************************
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
****************************************************************************/

BOOL InitInstance(
				  HINSTANCE          hInstance,
				  int             nCmdShow) 
{
	HWND hWndMain;
	
	hInst = hInstance;
	
	hWndMain = CreateWindow(
		TEXT("ListviewWClass"),
		TEXT("Listview Sample"), 
		WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		hInstance,          
		NULL);
	
	/* If window could not be created, return "failure" */
	if (!hWndMain)
		return (FALSE);
	
	/* Make the window visible; update its client area; and return "success" */
	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain); 
	return (TRUE);      
	
}

/****************************************************************************
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes messages
*
****************************************************************************/

LONG APIENTRY MainWndProc(
						  HWND hWnd,                /* window handle                   */
						  UINT message,             /* type of message                 */
						  UINT wParam,              /* additional information          */
						  LONG lParam)              /* additional information          */
{
	static HWND hWndListView;
	DWORD dwStyle;
	
	switch (message) 
	{
		
	case WM_CREATE:
		//When the main window is created using CW_USEDEFAULT the height of the menubar (if one
		// is created is not taken into account). So we resize the window after creating it
		// if a menubar is present
		{
			RECT rc;
			GetWindowRect(hWnd, &rc);
			// adjust for menu / titlebar height
			rc.bottom -= (2*MENU_HEIGHT -1);
			
			MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
		}
		
		//Create a MenuBar
		SHMENUBARINFO mbi;
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hWnd;
        mbi.nToolBarId = IDM_MAIN_MENU;
        mbi.hInstRes   = hInst;
        mbi.nBmpId     = 0;
        mbi.cBmpImages = 0;	
        
		
		if (!SHCreateMenuBar(&mbi))
			MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
        hwndCB = mbi.hwndMB;
		hmenuCB = SHGetSubMenu(hwndCB, IDM_MAIN_MENUITEM1);
		
		dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
		
		// set inital radio check to the detail/report view
		if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
			SetWindowLong(hWndListView, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);
		CheckMenuRadioItem(hmenuCB, IDM_LARGEICON, IDM_REPORTVIEW, IDM_REPORTVIEW, MF_BYCOMMAND);
		
		hWndListView = CreateListView( hWnd );
		if (hWndListView == NULL)
			MessageBox (NULL, TEXT("Listview not created!"), NULL, MB_OK );
		
		break;
		
	case WM_NOTIFY:
		return( NotifyHandler(hWnd, message, wParam, lParam));
		break;
		
	case WM_COMMAND:
		
		switch( LOWORD( wParam ))
		{
			
		case IDM_LARGEICON:
			dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
			
			if ((dwStyle & LVS_TYPEMASK) != LVS_ICON)
				SetWindowLong(hWndListView, GWL_STYLE,
				(dwStyle & ~LVS_TYPEMASK) | LVS_ICON);
			CheckMenuRadioItem(hmenuCB, IDM_LARGEICON, IDM_REPORTVIEW, IDM_LARGEICON, MF_BYCOMMAND);
			break;
			
		case IDM_SMALLICON:
			dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
			
			if ((dwStyle & LVS_TYPEMASK) != LVS_SMALLICON)
				SetWindowLong(hWndListView, GWL_STYLE,
				(dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
			CheckMenuRadioItem(hmenuCB, IDM_LARGEICON, IDM_REPORTVIEW, IDM_SMALLICON, MF_BYCOMMAND);
			break;
			
		case IDM_LISTVIEW:
			dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
			
			if ((dwStyle & LVS_TYPEMASK) != LVS_LIST)
				SetWindowLong(hWndListView, GWL_STYLE,
				(dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
			CheckMenuRadioItem(hmenuCB, IDM_LARGEICON, IDM_REPORTVIEW, IDM_LISTVIEW, MF_BYCOMMAND);
			break;
			
		case IDM_REPORTVIEW:
			dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
			
			if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
				SetWindowLong(hWndListView, GWL_STYLE,
				(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);
			CheckMenuRadioItem(hmenuCB, IDM_LARGEICON, IDM_REPORTVIEW, IDM_REPORTVIEW, MF_BYCOMMAND);
			break;
			
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
			
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)About);
			break;
			
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
			
		}
		break;
		
		case WM_SIZE:
            MoveWindow(hWndListView, 0, 0, LOWORD(lParam),HIWORD(lParam),TRUE);
            break;
			
		case WM_DESTROY:                  /* message: window being destroyed */
			PostQuitMessage(0);
			break;
			
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}



/****************************************************************************
* 
*    FUNCTION: CreateListView(HWND)
*
*    PURPOSE:  Creates the list view window and initializes it
*
****************************************************************************/
HWND CreateListView (HWND hWndParent)                                     
{
	HWND hWndList;      		// handle to list view window
	RECT rcl;           		// rectangle for setting size of window
	HICON hIcon;        		// handle to an icon
	int index;					// index used in for loops
	HIMAGELIST hSmall, hLarge;	// handles to image lists for small and
	// large icons
	LV_COLUMN lvC;				// list view column structure
	TCHAR szText[MAX_PATH];		// place to store some text
	LVITEM lvI;				// list view item structure
	int iSubItem;				// index into column header string table
	
	// Ensure that the common control DLL is loaded.
	InitCommonControls();
	
	// Get the size and position of the parent window.
	GetClientRect(hWndParent, &rcl);
	
	// Create the list view window that starts out in details view
    // and supports label editing.
/*	hWndList = CreateWindow( 0L,
		WC_LISTVIEW,                // list view class
		TEXT(""),                         // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | WS_HSCROLL |
		LVS_EDITLABELS,// | WS_EX_CLIENTEDGE,	// styles
		rcl.top, rcl.left,
		rcl.right - rcl.left, rcl.bottom - rcl.top - 40,
		hWndParent,
		(HMENU) ID_LISTVIEW,
		hInst,
		NULL ); */

hWndList=	CreateWindow(WC_LISTVIEW, NULL,
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS ,
            rcl.left, rcl.top, rcl.right - rcl.left, rcl.bottom - rcl.top - 20,
            hWndParent, (HMENU)ID_LISTVIEW, hInst,NULL);
	
	if (hWndList == NULL )
		return NULL;
	
	
	// Initialize the list view window.
	// First initialize the image lists you will need:
    // create image lists for the small and the large icons.
	
	hSmall = ImageList_Create( BITMAP_WIDTH, BITMAP_HEIGHT,
		FALSE, 3, 0 );
	
	hLarge = ImageList_Create( LG_BITMAP_WIDTH, LG_BITMAP_HEIGHT,FALSE, 3, 0 );
	
	// Load the icons and add them to the image lists.
	for (index = REDMOND; index <= SEATTLE ; index++)
	{
		hIcon = LoadIcon ( hInst, MAKEINTRESOURCE(index));
		// You have 3 of each type of icon here, so add 3 at a time.
		for (iSubItem = 0; iSubItem < 3; iSubItem++)
		{
			if ((ImageList_AddIcon(hSmall, hIcon) == -1) ||
				(ImageList_AddIcon(hLarge, hIcon) == -1))
				return NULL;
		}
	}
	
	// Be sure that all the small icons were added.
	if (ImageList_GetImageCount(hSmall) < 3)
		return FALSE;
	
	// Be sure that all the large icons were added.
	if (ImageList_GetImageCount(hLarge) < 3)
		return FALSE;
	
	// Associate the image lists with the list view control.
	ListView_SetImageList(hWndList, hSmall, LVSIL_SMALL);
	
	ListView_SetImageList(hWndList, hLarge, LVSIL_NORMAL);
	
	// Now initialize the columns you will need.
	// Initialize the LV_COLUMN structure.
	// The mask specifies that the fmt, width, pszText, and subitem members 
	// of the structure are valid,
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align column
	lvC.cx = 75;            // width of column in pixels
	lvC.pszText = szText;
	
	// Add the columns.
	for (index = 0; index <= NUM_COLUMNS; index++)
	{
		lvC.iSubItem = index;
		LoadString( hInst, 
			IDS_ADDRESS + index,
			szText,
			sizeof(szText)/sizeof(szText[0]));
		if (ListView_InsertColumn(hWndList, index, &lvC) == -1)
			return NULL;
	}
	
	// Finally, add the actual items to the control.
	// Fill out the LV_ITEM structure for each of the items to add to the list.
	// The mask specifies the the pszText, iImage, lParam and state
	// members of the LV_ITEM structure are valid.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvI.state = 0;      
	lvI.stateMask = 0;  
	
	for (index = 0; index < NUM_ITEMS; index++)
	{
		lvI.iItem = index;
		lvI.iSubItem = 0;
		// The parent window is responsible for storing the text. 
		// The list view control will send an LVN_GETDISPINFO 
		// when it needs the text to display.
		lvI.pszText = LPSTR_TEXTCALLBACK; 
		lvI.cchTextMax = MAX_ITEMLEN;
		lvI.iImage = index;
		lvI.lParam = (LPARAM)&rgHouseInfo[index];
		
		if (ListView_InsertItem(hWndList, &lvI) == -1)
			return NULL;
		
		for (iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
		{
			ListView_SetItemText( hWndList,
				index,
				iSubItem,
				LPSTR_TEXTCALLBACK);
		}
	}
	return (hWndList);
}



/****************************************************************************
* 
*    FUNCTION: NotifyHandler(HWND, UINT, UINT, LONG)
*
*    PURPOSE: This function is the handler for the WM_NOTIFY that is 
*    sent to the parent of the list view window.
*
****************************************************************************/
LRESULT NotifyHandler( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;
	HOUSEINFO *pHouse = (HOUSEINFO *)(pLvdi->item.lParam);
	static TCHAR szText[10];
	
	if (wParam != ID_LISTVIEW)
		return 0L;
	
	switch(pLvdi->hdr.code)
	{
	case LVN_GETDISPINFO:
		
		switch (pLvdi->item.iSubItem)
		{
		case 0:     // address
			pLvdi->item.pszText = pHouse->szAddress;
			break;
			
		case 1:     // city
			pLvdi->item.pszText = pHouse->szCity;
			break;
			
		case 2:     // price
			wsprintf(szText, TEXT("$%u"), pHouse->iPrice);
			pLvdi->item.pszText = szText;
			break;
			
		case 3:     // number of bedrooms
			wsprintf(szText, TEXT("%u"), pHouse->iBeds);
			pLvdi->item.pszText = szText;
			break;
			
		case 4:     // number of bathrooms
			wsprintf(szText, TEXT("%u"), pHouse->iBaths);
			pLvdi->item.pszText = szText;
			break;
			
		default:
			break;
		}
		break;
		
        case LVN_BEGINLABELEDIT:
            {
                HWND hWndEdit;
				
                // Get the handle to the edit box.
                hWndEdit = (HWND)SendMessage(hWnd, LVM_GETEDITCONTROL, 
                    0, 0);
                // Limit the amount of text that can be entered.
                SendMessage(hWndEdit, EM_SETLIMITTEXT, (WPARAM)20, 0);
            }
            break;
			
        case LVN_ENDLABELEDIT:
            // Save the new label information
            if ((pLvdi->item.iItem != -1) && 
                (pLvdi->item.pszText != NULL))
				lstrcpy(pHouse->szAddress, pLvdi->item.pszText);
            break;
			
		case LVN_COLUMNCLICK:
			// The user clicked a column header - sort by this criterion.
			ListView_SortItems( pNm->hdr.hwndFrom,
				ListViewCompareProc,
				(LPARAM)(pNm->iSubItem));
			break;
			
		default:
			break;
	}
	return 0L;
}

/****************************************************************************
* 
*    FUNCTION: ListViewCompareProc(LPARAM, LPARAM, LPARAM)
*
*    PURPOSE: Callback function that sorts depending on the column click 
*
****************************************************************************/
int CALLBACK ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	HOUSEINFO *pHouse1 = (HOUSEINFO *)lParam1;
	HOUSEINFO *pHouse2 = (HOUSEINFO *)lParam2;
	LPTSTR lpStr1, lpStr2;
	int iResult;
	
	
	if (pHouse1 && pHouse2)
	{
		switch( lParamSort)
		{
		case 0:     // sort by Address
			lpStr1 = pHouse1->szAddress;
			lpStr2 = pHouse2->szAddress;
			iResult = lstrcmpi(lpStr1, lpStr2);
			break;
			
		case 1:     // sort by city
			lpStr1 = pHouse1->szCity;
			lpStr2 = pHouse2->szCity;
			iResult = lstrcmpi(lpStr1, lpStr2);
			break;
			
		case 2:     // sort by price
			iResult = pHouse1->iPrice - pHouse2->iPrice;
			break;
			
		case 3:     // sort by number of bedrooms
			iResult = pHouse1->iBeds - pHouse2->iBeds;
			break;
			
		case 4:     // sort by number of bathrooms
			iResult = pHouse1->iBaths - pHouse2->iBaths;
			break;
			
		default:
			iResult = 0;
			break;
			
		}
		
	}
	return(iResult);
}

/****************************************************************************
*
*    FUNCTION: About(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "About" dialog box
*
****************************************************************************/

BOOL APIENTRY About(
					HWND hDlg,
					UINT message,
					UINT wParam,
					LONG lParam)
{
	switch (message)
	{	
		case WM_INITDIALOG:
			//On Pocket PC devices you normally create all Dialog's as fullscreen dialog's
      // with an OK button in the upper corner. You should get/set any program settings
      // during each modal dialog creation and destruction
      SHINITDLGINFO shidi;
      // Create a Done button and size it.
      shidi.dwMask = SHIDIM_FLAGS;
      shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
      shidi.hDlg = hDlg;
      //initialzes the dialog based on the dwFlags parameter
      SHInitDialog(&shidi);

			break;
			
	   case WM_COMMAND:              
		   if (LOWORD(wParam) == IDOK)
		   {
			   EndDialog(hDlg, TRUE);
			   return (TRUE);
		   }
		   break;
	}
	return (FALSE);   
	
}
