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
// POOMTASKS.CPP
// 
// Implementation of reading / creating POOM task information
//
#include "PoomMaster.h"
extern HINSTANCE g_hInst;


// **************************************************************************
// Function Name: AddTaskFolderText
// 
// Purpose: Reads and adds existing POOM tasks to the main listbox
//
// Arguments:
//    IN IPOutlookItemCollection * pItenCol - ptr to the Tasks default folder
//		collection interface
//
// Return Values:
//    Describes the return type an meaning of each value.  E.g.:
//    BOOL
//    returns TRUE if the item was successfully read and added. Otherwise FALSE
// 
// Description:  
//   This function iterates through the collection of tasks, reading 
//		properties from each. The string data is then added to the main 
//		listview control
BOOL AddTaskFolderText(IPOutlookItemCollection * pItemCol)
{
	HRESULT hr;
	BSTR bstrSubject;

	ITask * pTask = NULL;
	int cItems = 0;

	hr = pItemCol->get_Count(&cItems);

	for (int i = 1; i <= cItems; i++)
	{
		hr = pItemCol->Item (i, (IDispatch**)&pTask);

		hr = pTask->get_Subject(&bstrSubject);

		AddToList(bstrSubject);
		pTask->Release();
	}
	
	return TRUE;

}

// **************************************************************************
// Function Name: GetTaskPriority
// 
// Purpose: Returns the Task importance given an index from the listbox
//
// Arguments:
//    IN int nIndex - position within the listbox which corresponds (off-by-one)
//		with the position in the item collection
//
// Return Values:
//
//    int 
//    returns olImportanceLow, olImportanceNormal, or olImportanceHigh
// 
// Description:  
//   This function takes an index, gets the corresponding Task item, and returns
//	its Importance property
int GetTaskPriority(int nIndex)
{
	IFolder * pFolder = NULL;
	IPOutlookItemCollection * pItemCol = NULL;
	ITask * pTask = NULL;
	LONG nRetVal;
	
	GetPoomFolder(olFolderTasks, &pFolder);
	pFolder->get_Items(&pItemCol);

	pItemCol->Item(++nIndex, (IDispatch**)&pTask);

	pTask->get_Importance(&nRetVal);

	return nRetVal;
}
// **************************************************************************
// Function Name: TaskIsComplete
// 
// Purpose: Returns the Task completion state given an index from the listbox
//
// Arguments:
//   none
//
// Return Values:
//
//    BOOL
//    returns TRUE if the task is complete, FALSE otherwise
// 
// Description:  
//   This function takes an index, gets the corresponding Task item, and returns
//	its Complete property
BOOL TaskIsComplete(int nIndex)
{
	IFolder * pFolder = NULL;
	IPOutlookItemCollection * pItemCol = NULL;
	ITask * pTask = NULL;
	VARIANT_BOOL vbIsComplete;
	
	 GetPoomFolder(olFolderTasks, &pFolder);
	pFolder->get_Items(&pItemCol);

	pItemCol->Item(++nIndex, reinterpret_cast<IDispatch**>(&pTask));

	pTask->get_Complete(&vbIsComplete);
	
	return vbIsComplete;
}
// **************************************************************************
// Function Name: NewTaskProc
// 
// Purpose: Processes messages for the new task dialog window
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
//		WM_INITDIALOG and WM_COMMAND messages. Upon receipt of an IDOK notificationm
//		a new task is created according to values entered for subject and importance
LRESULT CALLBACK NewTaskProc(HWND hDlg, 
							 UINT message, 
							 WPARAM wParam, 
							 LPARAM lParam)
{
	
	BSTR bstrDesc;
	int nPriority;
	IPOutlookApp * pOutApp = NULL;
	ITask * pTask = NULL;
	
	switch (message)
	{

	case WM_INITDIALOG:
		{
			InitNewItemDlg(hDlg);

			SendMessage(GetDlgItem(hDlg, IDC_IMPORTANCE), LB_INSERTSTRING, 0, (LPARAM) _T("High"));
			SendMessage(GetDlgItem(hDlg, IDC_IMPORTANCE), LB_INSERTSTRING, 0, (LPARAM) _T("Medium"));
			SendMessage(GetDlgItem(hDlg, IDC_IMPORTANCE), LB_INSERTSTRING, 0, (LPARAM) _T("Low"));
			SendMessage(GetDlgItem(hDlg, IDC_IMPORTANCE), LB_SETCURSEL, 1, 0);

			if(TRUE == IsSmartphone())
			{
				RemoveBorder(GetDlgItem(hDlg, IDC_IMPORTANCE));
			}
			HWND hwndUpDown = CreateWindow(UPDOWN_CLASS, NULL, WS_VISIBLE | UDS_HORZ | 
				UDS_ALIGNRIGHT | UDS_ARROWKEYS |  UDS_SETBUDDYINT | UDS_WRAP | UDS_EXPANDABLE, 
				0, 0, 0, 0, hDlg, (HMENU)IDC_UPDOWN, g_hInst, 0L);

			SendMessage(hwndUpDown, UDM_SETBUDDY, (WPARAM)GetDlgItem(hDlg, IDC_IMPORTANCE), 0);

			
			return TRUE; 
		}
		break;
		
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDM_CANCEL:
			
			EndDialog(hDlg, IDCANCEL);
			break;
		
		case IDM_OK:
		case IDOK:
		
			GetCtrlBstr(hDlg, IDC_TASKDESC, &bstrDesc);

			nPriority = SendMessage(GetDlgItem(hDlg, IDC_IMPORTANCE), LB_GETCURSEL, 0, 0);

			if (nPriority == 0)
				nPriority = olImportanceLow;
			else if (nPriority == 1)
				nPriority = olImportanceNormal;
			else
				nPriority = olImportanceHigh;

			if (SysStringLen(bstrDesc) > 1)
			{
				if (GetPoomApp(&pOutApp))
				{
					if (SUCCEEDED(pOutApp->CreateItem(olTaskItem, reinterpret_cast<IDispatch**>(&pTask))))
					{
						pTask->put_Subject(bstrDesc);
						pTask->put_Importance(nPriority);
						pTask->Save();
					
						pTask->Release();
						pOutApp->Release();
					}
				}				
			}
			
			
			EndDialog(hDlg, IDOK);
			return TRUE;
			
		}
		break;
	}
	return FALSE;
}
