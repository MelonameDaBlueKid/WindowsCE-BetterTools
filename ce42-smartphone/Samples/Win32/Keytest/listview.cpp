/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
	
****************************************************************************/
//
// file listview.cpp
// tried to make this somewhat generic isolates the listview interaction from the rest of the application
//
#include "stdafx.h"

// GLobal Variables
HWND				g_hwndLV = NULL;		// handle to the listview window
WNDPROC g_lpfnListView;

//flags to determine what key messages to log
BOOL fWM_KEYDOWN = FALSE;
BOOL fWM_KEYUP = FALSE;
BOOL fWM_CHAR = FALSE;
BOOL fWM_MOUSEMOVE = FALSE;
BOOL fWM_LBUTTONDOWN  = FALSE;
BOOL fWM_LBUTTONDBLCLK = FALSE;
BOOL fWM_LBUTTONUP = FALSE;
BOOL fWM_RBUTTONDOWN = FALSE;
BOOL fWM_RBUTTONUP = FALSE;
BOOL fWM_RBUTTONDBLCLK = FALSE;

// AddMessageToLV
//   adds an item to the listview g_hwndLV
//   the item will be a WM_KEYDOWN, WM_KEYUP, or WM_CHAR message.
//
BOOL AddMessageToLV(PTSTR szMsg, WPARAM wParam, LPARAM lParam, BOOL bCHAR)
{
	LVITEM 		lvi;
	TCHAR		szOut[100];
	HWND		hwndLV = g_hwndLV;
	
	//
	// set up the LVITEM structure
	//
	memset(&lvi, 0, sizeof(LVITEM));
	
	lvi.mask = LVIF_TEXT | LVIF_STATE;
	//
	// in subitem 0 lives the message name
	//
	wsprintf(szOut, TEXT("%s"), szMsg);
	lvi.pszText		= szOut;  // we'll just reset szOut each time
	lvi.cchTextMax	= MAX_ITEMLEN;
	int iItem = ListView_InsertItem(g_hwndLV, &lvi);
	int iSubItem = 0;
	
	if (iItem == -1)
		MessageBox(g_hwnd, TEXT("Listview Insert Failed"), TEXT("Insert"), MB_OK);
	
	//
	// in subitem 1 lives the wParam
	//
	iSubItem++;
	// looks nicer to convert the WM_CHAR messages
	if (!bCHAR)
		GetKeyName(wParam, szOut);
	else if (!lstrcmp(szMsg, TEXT("CHAR")))
		wsprintf(szOut, TEXT("%c"), wParam);
	else 
		wsprintf(szOut, TEXT("%x"), wParam);
	
	ListView_SetItemText(g_hwndLV, iItem, iSubItem, szOut);
	
	//
	// in subitem 2 lives the lParam
	//
	iSubItem++;
	wsprintf(szOut, TEXT("%x"), lParam);
	
	ListView_SetItemText(g_hwndLV, iItem, iSubItem, szOut);
	
	//
	// it is good practice to ensure visible for all inserted items
	//
	ListView_EnsureVisible(hwndLV, lvi.iItem, FALSE);
	InvalidateRect(g_hwndLV, NULL, TRUE);
	UpdateWindow(g_hwndLV);

	//
	// don't run out of space in the listview
	//
	int iCnt = ListView_GetItemCount(g_hwndLV);
	if (iCnt > 200)
		for (int iDelete = iCnt; iDelete > 100; iDelete--)
			ListView_DeleteItem(g_hwndLV, iDelete);

	return TRUE;
}

//
// Handle Input Messages
//
BOOL HandleInputMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_KEYDOWN:
		if (fWM_KEYDOWN) return AddMessageToLV(TEXT("KEYDOWN"), wParam, lParam, FALSE);
		return FALSE;
	case WM_KEYUP:
		if (fWM_KEYUP) return AddMessageToLV(TEXT("KEYUP"), wParam, lParam, FALSE);
		return FALSE;
	case WM_CHAR:
		if (fWM_CHAR) return AddMessageToLV(TEXT("CHAR"), wParam, lParam, TRUE);
		return FALSE;
	case WM_MOUSEMOVE:
		if (fWM_MOUSEMOVE) return AddMessageToLV(TEXT("MOUSEMOVE"), wParam, lParam, TRUE);
		return FALSE;
	case WM_LBUTTONDOWN:
		if (fWM_LBUTTONDOWN) return AddMessageToLV(TEXT("LDOWN"), wParam, lParam, TRUE);
		return FALSE;
	case WM_LBUTTONDBLCLK:
		if (fWM_LBUTTONDBLCLK) return AddMessageToLV(TEXT("LDBL"), wParam, lParam, TRUE);
		return FALSE;
	case WM_LBUTTONUP:
		if (fWM_LBUTTONUP) return AddMessageToLV(TEXT("LUP"), wParam, lParam, TRUE);
		return FALSE;
	case WM_RBUTTONDOWN:
		if (fWM_RBUTTONDOWN) return AddMessageToLV(TEXT("RDOWN"), wParam, lParam, TRUE);
		return FALSE;
	case WM_RBUTTONUP:
		if (fWM_RBUTTONUP) return AddMessageToLV(TEXT("RUP"), wParam, lParam, TRUE);
		return FALSE;
	case WM_RBUTTONDBLCLK:
		if (fWM_RBUTTONDBLCLK) return AddMessageToLV(TEXT("RDBL"), wParam, lParam, TRUE);
		return FALSE;
	}
	return FALSE;
}
//
// dialog proc for the listview
//  being a dialog procedure, return TRUE for messages handled
//
LRESULT CALLBACK ListviewProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (HandleInputMessages(msg, wParam, lParam))
		return TRUE;
	
	switch (msg)
	{
	case WM_SETFOCUS:
		// set the focus back to the the control losing the focus
		SetFocus(g_hwnd);
		return 0;
		
	default:
		return CallWindowProc((WNDPROC)g_lpfnListView, hwnd, msg, wParam, lParam);
	}
	
	return 0;
}

static BOOL IsSmartphone() 
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

//
// create the listview and resize it to available screen size
// when bCreating is false, destroy the listview
//
HWND CreateListview(HWND hwndParent, BOOL bCreating)
{
	LVCOLUMN 	lvc;
	TCHAR		szOut[100];
	INT			iRet;
	HWND 		hwndLV = g_hwndLV;
	RECT		rc;
	INT			iHeightMod = 0;


	
	// get rid of old one to avoid a leak
	if (hwndLV)
	{
		ShowWindow(hwndLV, SW_HIDE);
		DestroyWindow(hwndLV);
		hwndLV = NULL;
	}
	
	if (bCreating)
	{
		GetClientRect(hwndParent, &rc);
	
		//adjust for menu/header height
		if (!IsSmartphone())
		{
			iHeightMod = GetSystemMetrics(SM_CYMENU) + 3;
		}
		// create the listview
		// it is a child of the main window in report view which the user cannot sort
		hwndLV = CreateWindow(WC_LISTVIEW, TEXT("ListItem"), 
			WS_CHILD | LVS_EDITLABELS | LVS_REPORT | LVS_NOSORTHEADER | WS_VISIBLE | WS_HSCROLL, 
			0, 0, rc.right, rc.bottom - iHeightMod, 
			hwndParent, NULL, g_hinst, NULL); 
		
		
		if (NULL == hwndLV) 
			return NULL; 
		
		// setup headers
		lvc.mask		= LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		lvc.fmt			= 0;
		lvc.cx			= 75;
		lvc.cchTextMax	= 0;
		lvc.iSubItem	= 0;
		
		lvc.pszText		= szOut;
		lvc.iImage		= 0;
		lvc.iOrder		= 0;
		
		// need to add columns in order
		
		// add column for message
		wsprintf(szOut, TEXT("Message"));
		iRet = ListView_InsertColumn(hwndLV, lvc.iSubItem, &lvc);
		
		// add column for wParam
		lvc.iSubItem++;
		wsprintf(szOut, TEXT("wParam"));
		iRet = ListView_InsertColumn(hwndLV, lvc.iSubItem, &lvc);
		
		// add column for lParam
		lvc.iSubItem++;
		wsprintf(szOut, TEXT("lParam"));
		iRet = ListView_InsertColumn(hwndLV, lvc.iSubItem, &lvc);
		
		// Subclass the list view so that we can set the focus back to
		// the process list view if the user should select anything in the
		// thread list view.
		g_lpfnListView = (WNDPROC)SetWindowLong(hwndLV,GWL_WNDPROC,(LONG)ListviewProc);
		
		
	}
	
	// this return value should be used to set g_hwndLV
	return hwndLV;
}

