/****************************************************************************
*
*
*    PROGRAM: ListView2.cpp
*
*    PURPOSE: Demonstrates the use of the list view control
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <string.h>
#include "listview2.h"

// global current instance
HINSTANCE hInst;

//handle to the MenuBar
HWND hwndCB;

/////////////////////////// Rapier only samples ///////////////////////
#if _WIN32_WCE < 212//non-Rapier devices
#error 'This sample works on Rapier devices only'
#endif
#include <aygshell.h>


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
	wcListview.lpszClassName = TEXT("ListviewWClass2");
	
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
		TEXT("ListviewWClass2"),
		TEXT("Listview Sample2"), 
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
	
	switch (message) 
	{
		
	case WM_CREATE:
		//When the main window is created using CW_USEDEFAULT the height of the menubar (if one
		// is created is not taken into account). So we resize the window after creating it
		// if a menubar is present
		{
			RECT rc;
			GetWindowRect(hWnd, &rc);
			if (hwndCB)
				MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
		}
		
		
		hWndListView = CreateListView( hWnd );
		if (hWndListView == NULL)
			MessageBox (NULL, TEXT("Listview not created!"), NULL, MB_OK );
		
		break;
		
	case WM_COMMAND:
		
		switch( LOWORD( wParam ))
		{
			
		case IDM_EXIT:
			PostQuitMessage(0);
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
	int index;					// index used in for loops
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
	hWndList = CreateWindowEx( 0L,
		WC_LISTVIEW,                // list view class
		TEXT(""),                         // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT |
		LVS_EDITLABELS | LVS_NOSORTHEADER ,	// styles
		rcl.top, rcl.left,
		rcl.right - rcl.left, rcl.bottom - rcl.top,
		hWndParent,
		(HMENU) ID_LISTVIEW,
		hInst,
		NULL );
	
	if (hWndList == NULL )
		return NULL;
	
	
	
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
			sizeof(szText));
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
		wsprintf(szText, L"Col 1 Item %d", index);
		lvI.pszText = szText; 
		lvI.cchTextMax = MAX_ITEMLEN;
		
		if (ListView_InsertItem(hWndList, &lvI) == -1)
			return NULL;
		
		for (iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
		{
			wsprintf(szText, L"Col %d Item %d",iSubItem, index);
			ListView_SetItemText( hWndList,
				index,
				iSubItem,
				szText);
		}
	}
	return (hWndList);
}


