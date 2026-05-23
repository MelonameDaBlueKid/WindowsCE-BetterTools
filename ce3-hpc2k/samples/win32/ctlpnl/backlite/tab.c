//*******************************************************************************************
//
// Filename : tab.c
//	
// Copyright (c) 1997 Microsoft Corporation. All rights reserved
//
//*******************************************************************************************
#include <windows.h>
#include <windowsx.h>


#include <commctrl.h>


#include <string.h>
#include "resource.h"
#include "system.h"

// Handle Ctrl+Tab to switch pages
BOOL IsTabDialogMessage(HWND hwndTabDlg, LPMSG lpMsg)
{
int   whichTab, howMany;

	if (lpMsg->wParam == VK_TAB && lpMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL)) {
		howMany  = TabCtrl_GetItemCount(hwndTab);
		if (howMany <= 1)
			return TRUE;
		whichTab = TabCtrl_GetCurSel(hwndTab);

		if (++whichTab >= howMany)
			whichTab = 0;
				
		DisplayTabDialog(whichTab);
		return TRUE;
		}

	return IsDialogMessage(hwndTabDlg, lpMsg);
}

BOOL APIENTRY TabDlgProc(HWND hDlg, UINT msg, UINT wp, LONG lp)
{

    switch (msg)     {
        case WM_NOTIFY:
            TabNotify( hDlg,  msg,  wp,  lp);
			break;
		case WM_HELP:
			PostMessage(GetParent(hDlg), msg, wp, lp);
			break;
	    case WM_COMMAND:
			switch (LOWORD(wp))	 {
				case IDOK:
				case IDCANCEL:
					PostMessage(hwndMain,WM_COMMAND, wp, lp);
					return TRUE;
				default:
					MsgToDialogs(WM_COMMAND, wp, lp);
					return TRUE;
				}
			break;
		}
    return FALSE;
}
// Set focus to first control
void SetFocusFirstControl(void)
{
HWND  hwnd;

	hwnd = GetNextDlgTabItem(hwndTabDlg, hwndTab, FALSE);
	if (hwnd) {
		SetFocus(hwnd);
		if (SendMessage(hwnd, WM_GETDLGCODE, 0, 0) & DLGC_HASSETSEL)
			SendMessage(hwnd, EM_SETSEL, 0, -1);
		}
}

// Tab Dialog Proc
void SetTabControl(void)
{
RECT	rc;
TC_ITEM tie;

    hwndTabDlg = CreateDialog(g_hinst,
	                   MAKEINTRESOURCE(TAB_DLG),
	                   hwndMain,
	                   TabDlgProc);

    hwndTab = GetDlgItem(hwndTabDlg, IDC_TAB);

	GetClientRect(hwndTab, &rc);
	TabCtrl_SetItemSize(hwndTab, (rc.right - rc.left) / 4, 20);
	TabCtrl_SetPadding(hwndTab, 20, 3);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;

	tie.iImage = -1;

	if (CurrApplet == 	0) { 		// only if 1st Applet
    	tie.pszText = TEXT("BackLight");
		TabCtrl_InsertItem(hwndTab, 0, &tie);

    	tie.pszText = TEXT("General");
		TabCtrl_InsertItem(hwndTab, 1, &tie);
		}
	else
	if (CurrApplet == 	1) { 		
		// set up tab if you have more then one applet in this control panel
		}
   	TabCtrl_SetCurSel(hwndTab, 0);			//select 1st Tab
	InvalidateRect(hwndTab, NULL, TRUE);	//this will fix border repaint
}

void TabNotify(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
int whichTab;
NMHDR *notifyHeader;

		if (wParam != IDC_TAB)
			return;
		notifyHeader = (NMHDR *)lParam;
		if (notifyHeader->code == TCN_SELCHANGE) {
	
			MsgToDialogs(WM_COMMAND, IDC_TAB, 0);  // tell dialogs about the tab change, inacse they want to do something w/ it
			
			whichTab = TabCtrl_GetCurSel(hwndTab);
			if (CurrApplet == 0) {		//  if 1st Applet
				switch (whichTab) {
					// Do not close dialog since need to save to registry on OK
    				case 0:			  		// system
						if (hwndGeneral)
							ShowWindow(hwndGeneral, SW_HIDE);
							
						if (! hwndSystem) {
		        			hwndSystem = CreateDialog(g_hinst,
		          					MAKEINTRESOURCE(LIGHT_DLG),
		          					hwndTabDlg, 		   // Tab is our parent
		          					(DLGPROC)SystemDlgProc);
							SetWindowPos(hwndSystem, HWND_TOP, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
							}
						else
							ShowWindow(hwndSystem, SW_SHOW);
						break;
					case 1:					// general
						if (hwndSystem)
							ShowWindow(hwndSystem, SW_HIDE);
							
						if (! hwndGeneral) {
			        		hwndGeneral = CreateDialog(g_hinst,
		          					MAKEINTRESOURCE(GENERAL_DLG),
		           					hwndTabDlg, 	  // Tab is our parent
		          					(DLGPROC)GeneralDlgProc);
							SetWindowPos(hwndGeneral, HWND_TOP, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
							}
						else
							ShowWindow(hwndGeneral, SW_SHOW);
						break;
					}
				}
			else
			if (CurrApplet == 1) {	
				//  if you have a 2nd applet
				}
			//set focus to first control
			SetFocusFirstControl();
			}
}

// dispaly desired Tab dialog
void DisplayTabDialog(int i)
{
NMHDR notifyHeader;

	notifyHeader.code = TCN_SELCHANGE;
	TabCtrl_SetCurSel(hwndTab, i);										//select desired Tab
	TabNotify(hwndTabDlg, WM_NOTIFY, IDC_TAB, (LPARAM)&notifyHeader);	//tell Tab to display dialog
}
