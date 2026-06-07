/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.

  This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/

#include "stdafx.h"
#include "notify.h"


//#define SetDlgItemText SetDlgItemTextW
//#define GetDlgItemText GetDlgItemTextW

// GUID for the app {85EE47B2-57D7-EEFE-8E7A-36480443D062}
static const GUID guidNotifyApp = 
{ 0x85ee47b2, 0x57d7, 0xEEFE, { 0x8e, 0x7a, 0x36, 0x48, 0x4, 0x43, 0xd0, 0x62 } };

// Global Variables:	
HINSTANCE			g_hInst;									// The current instance
HWND				g_hWnd;										// The main window handle
UINT				g_uiNotifyIDCount = 12540;					// id base for notify events
UINT				g_iIDCounter = 10000;
TCHAR				g_szCustomSecs[MAX_STRINGLEN];
TCHAR				g_szCustomTitle[MAX_STRINGLEN];
TCHAR				g_szCustomHTMLSampleText[MAX_MESSAGELEN];
SHNP				g_shnpNotifyType;
DWORD				g_dwCustomFlags;
int					g_iConvertedTime;
HWND				g_hDlg;
CPtrList*			g_pList;

static SHACTIVATEINFO s_sai;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK NotifyMain(
	HWND, 
	UINT, 
	WPARAM,
	LPARAM
	);

LRESULT CALLBACK CustomOptions(
	HWND, 
	UINT, 
	WPARAM, 
	LPARAM
	);

// Linked List Wrapper Functions
SHNOTIFICATIONDATA* CreateAndAddNotification();

BOOL RemoveNotification(
	DWORD dwID
	);

void RemoveNotificationAll();

int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPTSTR lpCmdLine,	
	int nCmdShow
	)
{
	g_hInst = hInstance;

	SHInitExtraControls();

	// just call a dialog box, system will handle messaging, painting, etc...
	DialogBox(hInstance,(LPCTSTR)IDD_NOTIFYMAIN, NULL,(DLGPROC)NotifyMain); 
	return 0;
}

LRESULT CALLBACK NotifyMain(
	HWND hDlg, 
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	)
{
	
	SHINITDLGINFO shidi = {0};
	SHMENUBARINFO shmbi = {0};
	SHNOTIFICATIONDATA shnd = {0};
	HICON hIcon = NULL;
	HWND hPriorityListCtrl = NULL;
	HWND hRemoveListCtrl = NULL;
	int iItemNumber = 0;
	int iRemoveID = 0;
	SHNP shnpNotifyType;
	SHNOTIFICATIONDATA* pCurrentNotification = NULL;
	int iCurrentItem = 0;
	TCHAR* pszID =(TCHAR*)malloc(MAX_STRINGLEN);
	
	hIcon =(HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_MESSAGE),
		IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	
	
	g_hDlg = hDlg;
	
	switch (message)
	{
	case WM_INITDIALOG:
		// Create a Done button and size it.  
		shidi.dwMask = SHIDIM_FLAGS;
		shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
		shidi.hDlg = hDlg;
		SHInitDialog(&shidi);

		shmbi.cbSize = sizeof(shmbi);
		shmbi.hwndParent = hDlg;
		shmbi.nToolBarId = IDR_MENU_DATA;
		shmbi.hInstRes = g_hInst;
		SHCreateMenuBar(&shmbi);

		// get the combo box handle and add the priority items to it
		hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
		
		iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_INFORM);
		SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_INFORM);  
		
		iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_ICONIC);
		SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_ICONIC);  
		
		iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_UPDATED);
		SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)UPDATE_NOTIFICATION);  
		
		iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_CUSTOM);
		SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)CUSTOM_NOTIFICATION);  
		
		// set the inform item as the default
		SendMessage(hPriorityListCtrl, CB_SETCURSEL, 0, 0);
		
		// populate the text information box about the type of priority
		//LoadString(g_hInst, IDS_INFORM_MESSAGE, pszPriorityText, MAX_MESSAGELEN);
		SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_INFORM_MESSAGE);
		
		// initilize the CPtrList object 
		g_pList = new CPtrList;
		
		break;
		
	case WM_MESSAGEBOX:
		MessageBox(NULL, TEXT("User Clicked OK."), TEXT("Notification Callback"), NULL);
		break;
		
	case WM_TIMER:
		// wParam is the pointer to the SHNOTIFICAITONDATA structure to update - using Update Notification to update the event
		SHNOTIFICATIONDATA* pUpdateNotification;
		pUpdateNotification =(SHNOTIFICATIONDATA*)wParam;
		pUpdateNotification->pszTitle = TEXT("Updated Title!");
		SHNotificationUpdate(SHNUM_TITLE, pUpdateNotification);
		break;

	case WM_DESTROY:
		free(pszID);
		RemoveNotificationAll();
		break;
		
	case WM_COMMAND:
			// when the user finishes selecting a priority from the combo box
			if (HIWORD(wParam)== CBN_SELENDOK)
			{
				// we update the text when the user finishes the selection of the priority of the message
				hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
				iItemNumber = SendMessage(hPriorityListCtrl, CB_GETCURSEL, 0, 0);
				shnpNotifyType =(SHNP)SendMessage(hPriorityListCtrl, CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
				switch (shnpNotifyType)
				{
				case SHNP_ICONIC:
					SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_ICONIC_MESSAGE);
					break;
				
				case UPDATE_NOTIFICATION:
					SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_UPDATED_MESSAGE);
					break;
				
				case CUSTOM_NOTIFICATION:
					SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_CUSTOM_MESSAGE);
					break;
				
				default:
					SetDlgItemText(hDlg, IDC_INFOTEXT, IDS_INFORM_MESSAGE);
					break;
				}
			}
			else
			{
				switch (LOWORD(wParam))
				{
					// if the user clicks add
				case IDC_ADD:
					// Get the Selected Priority for the Notification
					hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
					iItemNumber = SendMessage(hPriorityListCtrl, CB_GETCURSEL, 0, 0);
					shnpNotifyType =(SHNP)SendMessage(hPriorityListCtrl, CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
					
					// create a node in the linked list for the notification
					pCurrentNotification = CreateAndAddNotification();
					// add the node to the listbox to show up in the display to remove(we know g_iIDCounter is the number)
					// we do not iconic notificaitons since they expire at preset times
					if (shnpNotifyType != SHNP_ICONIC)
					{
						wsprintf(pszID, TEXT("%i"), g_iIDCounter);
						hRemoveListCtrl = GetDlgItem(hDlg, IDC_REMOVELIST);
						iCurrentItem = SendMessage(hRemoveListCtrl, LB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)pszID);
						SendMessage(hRemoveListCtrl, LB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(UINT)g_iIDCounter); 
					}
					
					// This code is implemented this way to easily facilitate copying to other apps
					switch (shnpNotifyType)
					{
					case SHNP_ICONIC:
						shnd.dwID = g_iIDCounter;
						shnd.clsid = guidNotifyApp;
						shnd.npPriority = SHNP_ICONIC;
						shnd.csDuration = 10;
						shnd.hwndSink = hDlg;
						shnd.pszHTML = IDS_DEFAULTHTMLMESSAGE;
						shnd.hicon = hIcon;
						shnd.cbStruct = sizeof(SHNOTIFICATIONDATA);
						shnd.pszTitle = IDS_DEFAULTTITLE;
						shnd.grfFlags = NULL;
						
						g_iIDCounter++;
						SHNotificationAdd(&shnd);
						break;
					case UPDATE_NOTIFICATION:
						pCurrentNotification->dwID = g_iIDCounter;
						pCurrentNotification->clsid = guidNotifyApp;
						pCurrentNotification->npPriority = SHNP_INFORM;
						pCurrentNotification->csDuration = 20;
						pCurrentNotification->hwndSink = hDlg;
						pCurrentNotification->pszHTML = IDS_DEFAULTHTMLMESSAGE;
						pCurrentNotification->hicon = hIcon;
						pCurrentNotification->cbStruct = sizeof(SHNOTIFICATIONDATA);
						pCurrentNotification->pszTitle = IDS_DEFAULTTITLE;
						pCurrentNotification->grfFlags = NULL;
						
						g_iIDCounter++;
						SHNotificationAdd(pCurrentNotification);
						
						// start the timer for the updated notification in 20 secs
						// this will send a WM_TIMER message to the message queue after 20 seconds
						SetTimer(g_hDlg,(UINT)pCurrentNotification, 20000, NULL);
						break;
					case CUSTOM_NOTIFICATION:
						pCurrentNotification->dwID = g_iIDCounter;
						pCurrentNotification->clsid = guidNotifyApp;
						pCurrentNotification->npPriority = g_shnpNotifyType;
						pCurrentNotification->csDuration = g_iConvertedTime;
						pCurrentNotification->hwndSink = hDlg;
						pCurrentNotification->pszHTML = g_szCustomHTMLSampleText;
						pCurrentNotification->hicon = hIcon;
						pCurrentNotification->cbStruct = sizeof(SHNOTIFICATIONDATA);
						pCurrentNotification->pszTitle = g_szCustomTitle;
						pCurrentNotification->grfFlags = g_dwCustomFlags;
						
						g_iIDCounter++;
						SHNotificationAdd(pCurrentNotification);
						break;
					default:
						pCurrentNotification->dwID = g_iIDCounter;
						pCurrentNotification->clsid = guidNotifyApp;
						pCurrentNotification->npPriority = SHNP_INFORM;
						pCurrentNotification->csDuration = 20;
						pCurrentNotification->hwndSink = hDlg;
						pCurrentNotification->pszHTML = IDS_DEFAULTHTMLMESSAGE;
						pCurrentNotification->hicon = hIcon;
						pCurrentNotification->cbStruct = sizeof(SHNOTIFICATIONDATA);
						pCurrentNotification->pszTitle = IDS_DEFAULTTITLE;
						pCurrentNotification->grfFlags = NULL;
						
						g_iIDCounter++;
						SHNotificationAdd(pCurrentNotification);
						break;
					}
					break;
					
					// if the user clicks the custom dialog
					case IDC_CUSTOM:
						// check and see of the user has Custom Selected
						hPriorityListCtrl = GetDlgItem(hDlg, IDC_NOTIFICATIONPRIORITY);
						iItemNumber = SendMessage(hPriorityListCtrl, CB_GETCURSEL, 0, 0);
						shnpNotifyType =(SHNP)SendMessage(hPriorityListCtrl, CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
						
						if (shnpNotifyType == CUSTOM_NOTIFICATION)
						{
							DialogBox(g_hInst,(LPCTSTR)IDD_CUSTOMOPTIONS, NULL,(DLGPROC)CustomOptions); 
						}
						else
						{
							// change the selection to custom and proceed to the dialog
							iItemNumber = SendMessage(hPriorityListCtrl, CB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)(LPCSTR)IDS_CUSTOM);
							SendMessage(hPriorityListCtrl, CB_SETCURSEL,(WPARAM)iItemNumber, 0);
							DialogBox(g_hInst,(LPCTSTR)IDD_CUSTOMOPTIONS, NULL,(DLGPROC)CustomOptions); 
						}
						break;
						
						// if user clicks remove 
					case IDC_REMOVE:
						hRemoveListCtrl = GetDlgItem(hDlg, IDC_REMOVELIST);
						iItemNumber = SendMessage(hRemoveListCtrl, LB_GETCURSEL, 0, 0);
						iRemoveID =(int)SendMessage(hRemoveListCtrl, LB_GETITEMDATA,(WPARAM)iItemNumber, 0);	
						SendMessage(hRemoveListCtrl, LB_DELETESTRING,(WPARAM)iItemNumber, 0);
						RemoveNotification(iRemoveID);
						break;
						
					case IDOK:
						EndDialog(hDlg, LOWORD(wParam));
						break;
						
						// this is called if the user clicks OK(the HREF is cmd:10)
					case 10:
						wsprintf(pszID, TEXT("%i"),(int)lParam);				
						hRemoveListCtrl = GetDlgItem(hDlg, IDC_REMOVELIST);
						iItemNumber = SendMessage(hRemoveListCtrl, LB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)(LPCSTR)pszID);
						SendMessage(hRemoveListCtrl, LB_DELETESTRING,(WPARAM)iItemNumber, 0);
						RemoveNotification((int)lParam);
						// must post message since notificaiton waits for procedure to end before closing bubble
						// and adding a messagebox would cause it to wait forever
						PostMessage(hDlg, WM_MESSAGEBOX, 0, 0);
						break;	
						
					default:
						break;
				}
			break;
			}
		}
	return FALSE;
}

// this is a dialog procedure for the custom dialog
LRESULT CALLBACK CustomOptions(
	HWND hDlg, 
	UINT message, 
	WPARAM wParam,
	LPARAM lParam
	)
{
	SHINITDLGINFO shidi;
	
	HWND hPriorityListCtrl;
	HWND hCheckBox = NULL;
	int iCurrentItem = 0;
	int iItemNumber = 0;
	
	switch (message)
	{
	case WM_INITDIALOG:
		// Create a Done button and size it.  
		shidi.dwMask = SHIDIM_FLAGS;
		shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
		shidi.hDlg = hDlg;
		SHInitDialog(&shidi);
				
		g_dwCustomFlags = NULL;			
				
		// get the combo box handle and add the priority items to it
		hPriorityListCtrl = GetDlgItem(hDlg, IDC_PRIORITYLIST);
		
		iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_INFORM);
		SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_INFORM);  
				
		iCurrentItem = SendMessage(hPriorityListCtrl, CB_ADDSTRING, NULL,(LPARAM)(LPCTSTR)IDS_SHNP_ICONIC);
		SendMessage(hPriorityListCtrl, CB_SETITEMDATA,(WPARAM)iCurrentItem,(LPARAM)(DWORD)(SHNP)SHNP_ICONIC);  
		
		// set the inform item as the default
		SendMessage(hPriorityListCtrl, CB_SETCURSEL, 0, 0);
		
		// fill out the defualt time of 10 seconds in the time edit box
		SetDlgItemText(hDlg, IDC_SECONDS, IDS_DEFUALT_CUSTOM_TIME);
		
		// fill out the title
		SetDlgItemText(hDlg, IDC_TITLESOURCE, IDS_CUSTOM_TITLE);
		
		// fill out the HTML body
		SetDlgItemText(hDlg, IDC_HTMLSOURCE, IDS_CUSTOM_HTML_SAMPLE);		
		
		break;
		
	case WM_COMMAND:
		if (LOWORD(wParam)== IDOK)
		{
			// collect all of what the user entered
			// get seconds
			GetDlgItemText(hDlg, IDC_SECONDS, g_szCustomSecs, MAX_STRINGLEN);
			g_iConvertedTime = _ttoi(g_szCustomSecs);
			// check for invalid time
			if (g_iConvertedTime == 0)
			{
				MessageBox(NULL, TEXT("Please enter a correct time value."), TEXT("Custom Problem"), NULL);
				return FALSE;
			}
			else
			{
				// get the title
				GetDlgItemText(hDlg, IDC_TITLESOURCE, g_szCustomTitle, MAX_STRINGLEN);
				
				// get the HTML body
				GetDlgItemText(hDlg, IDC_HTMLSOURCE, g_szCustomHTMLSampleText, MAX_STRINGLEN);	
				
				// get what priority the user selected
				// Get the Selected Priority for the Notification
				hPriorityListCtrl = GetDlgItem(hDlg, IDC_PRIORITYLIST);
				iItemNumber = SendMessage(hPriorityListCtrl, CB_GETCURSEL, 0, 0);
				g_shnpNotifyType =(SHNP)SendMessage(hPriorityListCtrl, CB_GETITEMDATA,(WPARAM)iItemNumber, 0);
				
				// get checkbox selections
				hCheckBox = GetDlgItem(hDlg, IDC_SHNF_STRAIGHTTOTRAY);
				if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0)== BST_CHECKED)
				{
					g_dwCustomFlags = g_dwCustomFlags | SHNF_STRAIGHTTOTRAY;
				}
				hCheckBox = GetDlgItem(hDlg, IDC_SHNF_CRITICAL);
				if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0)== BST_CHECKED)
				{
					g_dwCustomFlags = g_dwCustomFlags | SHNF_CRITICAL;
				}
				hCheckBox = GetDlgItem(hDlg, IDC_SHNF_FORCEMESSAGE);
				if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0)== BST_CHECKED)
				{
					g_dwCustomFlags = g_dwCustomFlags | SHNF_FORCEMESSAGE;
				}
				
				EndDialog(hDlg, LOWORD(wParam));
				PostMessage(g_hDlg, WM_COMMAND, IDC_ADD, NULL);
				return TRUE;
			}
		}
		break;
	}
	
	return FALSE;
}

//Add a node to the linked list(MFC Linked List)
SHNOTIFICATIONDATA* CreateAndAddNotification()
{
	SHNOTIFICATIONDATA* pshndTemp =(SHNOTIFICATIONDATA*)malloc( sizeof(SHNOTIFICATIONDATA));
	if (pshndTemp)
	{
		g_pList->AddTail((void*)pshndTemp);
	}
	
	return pshndTemp;	
}

// remove a node with the speficied dwID
BOOL RemoveNotification(
	DWORD dwID
	)
{
	BOOL bFound = FALSE;
	int iIndex = 0;
	POSITION tempPosition;
	SHNOTIFICATIONDATA* pshndTemp;
	while (!bFound &&(iIndex < g_pList->GetCount()))
	{
		tempPosition = g_pList->FindIndex(iIndex);
		pshndTemp =(SHNOTIFICATIONDATA*)g_pList->GetAt(tempPosition);
		if (pshndTemp->dwID == dwID)
		{
			bFound = TRUE;
			SHNotificationRemove(&guidNotifyApp, dwID);
			free(pshndTemp);
			g_pList->RemoveAt(tempPosition);
			
		}
		else
		{
			iIndex++;
		}
	}
	return bFound;	
}

// function removed all nodes in the list
// called when the programme exits
void RemoveNotificationAll()
{
	SHNOTIFICATIONDATA* pshndToDelete;
	POSITION tempPosition;
	int iListSize = g_pList->GetCount();
	
	for (int i = 0; i < iListSize; i++)
	{
		tempPosition = g_pList->GetHeadPosition();
		pshndToDelete =(SHNOTIFICATIONDATA*)g_pList->GetAt(tempPosition);
		SHNotificationRemove(&guidNotifyApp, pshndToDelete->dwID);
		free(pshndToDelete);
		g_pList->RemoveHead();		
	}
}