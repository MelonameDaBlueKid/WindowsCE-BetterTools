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

///////////////////////////////////////////////////////////////////////////////
//
// poomdata.cpp
//
// This file contains most of the code that deals with interacting
// with POOM for this application.  It stores and manipulates the
// poom model.  Logon/logoff are not in this file because they
// are included in the initialization of windows in poomtasks.cpp



#define INITGUID
#include "poomtasks.h"

#define MAX_SUBJECT 4096
#define MAX_NOTES	10000

// Arrays of days and months for recurrence string building
const UINT c_uDaysOfWeek[] = {IDS_SUNDAY   , IDS_MONDAY  , IDS_TUESDAY, 
                              IDS_WEDNESDAY, IDS_THURSDAY, IDS_FRIDAY,
                              IDS_SATURDAY};

const UINT c_uMonths[] = {0, IDS_JANUARY, IDS_FEBRUARY, IDS_MARCH    ,
                             IDS_APRIL  , IDS_MAY     , IDS_JUNE     ,
							 IDS_JULY   , IDS_AUGUST  , IDS_SEPTEMBER,
							 IDS_OCTOBER, IDS_NOVEMBER, IDS_DECEMBER};

// Global variables
IFolder* g_pTaskFolder;
IPOutlookApp *g_polApp;
FILTER g_Filter;
SORT g_Sort;
extern HINSTANCE			g_hInst;					// The current instance
extern HWND					g_hwndCB;					// The command bar handle
extern HWND					g_hwndLV;					// The list view handle

IPOutlookItemCollection* GetTaskList();

// Helps destruct poom items
void DestructPoom ()
{
	if(g_pTaskFolder)
	{
		g_pTaskFolder->Release();
		g_pTaskFolder=NULL;
	}

	g_polApp->Release();
	g_polApp=NULL;
}


// IsOverdueTask ()
// ---------------------
// Checks if the given task is overdue.  Compares it to the current time.
BOOL IsOverdueTask (ITask* pTask)
{
	DATE duedate;
	SYSTEMTIME systime;
	DATE currdate;
	// Check if overdue
	pTask->get_DueDate (&duedate);
	GetSystemTime (&systime);
	SystemTimeToVariantTime (&systime, &currdate);
					
	return (duedate < currdate);
}

// GetTaskCollection ()
// -----------------------
// An initializing step.  It does the logging onto Outlook
// and gets the task collection. 
BOOL GetTaskCollection (HWND hwnd)
{
	//POOM STUFF
	HRESULT hr;

	// Now, let's get the main outlook application
	hr = CoCreateInstance(CLSID_Application, NULL, CLSCTX_INPROC_SERVER, IID_IPOutlookApp, (LPVOID *) &g_polApp);
	if (FAILED(hr))
	{
		DEBUGMSG(TRUE, (TEXT("Couldn't load Outlook Application object, hr = %x!\r\n"), hr));
		return FALSE;
	}

	// Don't forget to logon to outlook (and logoff when done)
	DEBUGMSG(TRUE, (TEXT("Logging on to Outlook\r\n")));
	hr = g_polApp->Logon((long) hwnd);
	if (FAILED(hr))
	{
		DEBUGMSG(TRUE, (TEXT("Couldn't log on\r\n")));
		return FALSE;
	}

	// Load with all the tasks POOM!!!
	DEBUGMSG(TRUE, (TEXT("Getting folder\r\n")));
	hr = g_polApp->GetDefaultFolder (olFolderTasks, &g_pTaskFolder);
	if (FAILED(hr))
	{
		DebugOut (TEXT("Failed to get default folder\n"));
		return FALSE;
	}
	 
	return RefreshItems();
}

// RefreshItems ()
// ----------------
// This function dumps the current list view then rebuilds it based
// on the outlook model.  This keeps the list view's reflection of the
// POOM data accurate and current.
BOOL RefreshItems ()
{
	HRESULT hr;
	ITask* pTask = NULL;
	VARIANT_BOOL status;
	long priority;
	int listcount = 0;
	
	BSTR tasksubject;
	int numtasks;

	IPOutlookItemCollection* pItemCol = GetTaskList();
	if(!pItemCol)
		return FALSE;

	hr = pItemCol->get_Count (&numtasks);

	DebugOut (TEXT("Got Count %d\n"), numtasks);
	// clear out the listview
	ListView_DeleteAllItems (g_hwndLV);

	for (int i = 1; i <= numtasks; i++) 
	{
		hr = pItemCol->Item (i, (IDispatch**)&pTask);
		// Do something, add it to the list view
		if (FAILED(hr))
		{
			DebugOut (TEXT("couldn't get item\n"));
			continue;
		}

		pTask->get_Complete (&status);
		// Check filter
		switch (g_Filter)
		{
		case completed:
			if (!(status)) // don't put it in the list
			{
				pTask->Release();
				continue;
			}
			break;

		case active:
			if (status) // don't put it in the list
			{
				pTask->Release();
				continue;
			}
			break;
		default:
			break;
		}
// ADD TO LIST
		pTask->get_Subject (&tasksubject);
		pTask->get_Importance (&priority);
		LV_ITEM lv = {0};
		lv.mask = LVIF_TEXT | LVIF_STATE | LVIF_PARAM | LVIF_IMAGE;
		lv.iItem = listcount;
		listcount++;
		lv.lParam = i; // 1 based index in POOM
		switch (priority) // Add the icon
		{
		case olImportanceLow:
			lv.iImage = 1;
			break;
		case olImportanceHigh:
			lv.iImage = 0;
			break;
		default:
			lv.iImage = 2;
			break;

		}
		lv.pszText = tasksubject;
		ListView_InsertItem (g_hwndLV, &lv);
		SysFreeString(tasksubject);
		pTask->Release();		
	}
	
	pItemCol->Release();

	return TRUE;
}


// FindTask ()
// ------------------
// A useful function.  It will find the POOM task item which
// corresponds to the zero-based list view index passed into 
// the function.  If -1 is passed in, it will find the POOM task
// item associated with the currently selected item in the list

ITask* FindTask (int index)
{
	HRESULT hr;
	int selection;
	ITask* pTask = NULL;
	LV_ITEM lv = {0};
	lv.mask = LVIF_PARAM | LVIF_TEXT;

	IPOutlookItemCollection* pItemCol = GetTaskList();
	if(!pItemCol)
		return NULL;

	// First find out which item in the List view is selected
	// if the index is -1, use selection, else use the index
	if (index < 0)
		selection = ListView_GetSelectionMark (g_hwndLV);
	else
		selection = index;

	if (selection == -1)
	{
		pItemCol->Release();
		return NULL;
	}

	// Get the LVITEM to retrieve the LPARAM which is the POOM index
	lv.iItem = selection;
	lv.iSubItem = 0;
	ListView_GetItem (g_hwndLV, &lv);

	hr = pItemCol->Item (lv.lParam, (IDispatch**)&pTask); // 1 based index
	pItemCol->Release();	

	if (pTask == NULL)
		DebugOut (TEXT("Query returned nothing\n"));

	return pTask;
}


DWORD FmtMessage(LPCVOID lpSource, LPTSTR lpBuffer, DWORD nSize, ...)
{
	ASSERT(lpSource);
	ASSERT(lpBuffer);

	DWORD result;
    va_list vaMarker;

    va_start(vaMarker, nSize);
	result = FormatMessage(FORMAT_MESSAGE_FROM_STRING,lpSource,0,0,lpBuffer,
	                       nSize,&vaMarker);
    va_end(vaMarker);
	return result;
}



// SetRecurrenceControls ()
// -------------------------
// Will set the choices in the recurrence spinner box.
// Choices should all be relative to the StartDate, if none then use SystemTime

void SetRecurrenceControls (HWND control, SYSTEMTIME systime)
{
	// Recurrence Spinner (HEADACHE)

	// 0 Once
	// 1 Weekly
	// 2 Monthly
	// 3 Yearly

	TCHAR strWeekly [100];
	TCHAR strMonthly[100];
	TCHAR strYearly [100];
	VARIANT vt;

	VariantInit (&vt);

	if (control == NULL)
		return;

	// Clear out control
	SendMessage (control, LB_RESETCONTENT, 0, 0);
	
	// Once string
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)UseString(IDS_RECURRENCE_ONCE));

	// Build daily string
	FmtMessage(UseString(IDS_RECURWKLY_TEMPLATE),strWeekly,ARRAY_LENGTH(strWeekly),
		       UseString(c_uDaysOfWeek[systime.wDayOfWeek]));
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)strWeekly);
	
	// Build monthly string
	vt.vt = VT_I4;
	vt.lVal = systime.wDay;
	VariantChangeType (&vt, &vt, 0, VT_BSTR);
	FmtMessage(UseString(IDS_RECURMNTHLY_TEMPLATE),strMonthly,ARRAY_LENGTH(strMonthly),
		       vt.bstrVal);
	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)strMonthly);

	// Build Yearly string
	FmtMessage(UseString(IDS_RECURYRLY_TEMPLATE),strYearly,ARRAY_LENGTH(strYearly),
	           UseString(c_uMonths[systime.wMonth]),vt.bstrVal);

	SendMessage (control, LB_ADDSTRING, 0, (LPARAM)strYearly);
	VariantClear(&vt);
}
	
// GetTaskData ()
// -----------------
// This function is used to setup the Edit Dialog
// It will go through the designated task item and set the
// dialog controls to reflect the data in the item
void GetTaskData (HWND hDlg, ITask* pTask)
{
	HWND control;
	BSTR taskSubject = NULL;
	BSTR taskNotes = NULL;
	long importance, sensitivity;
	VARIANT_BOOL completed;
	VARIANT_BOOL hasReminder;
	DATE date;
	SYSTEMTIME sysdate;
	SYSTEMTIME recurtime;
	IRecurrencePattern* pRec;

	HRESULT hr;

	// Subject Field
	pTask->get_Subject (&taskSubject);
	SetDlgItemText (hDlg, IDC_SUBJECT, taskSubject);

	// Priority Spinner
	pTask->get_Importance (&importance);
	control = GetDlgItem (hDlg, IDC_PRIORITYLIST);
	if (control != NULL)
	{
		switch (importance)
		{
		case olImportanceLow:
			SendMessage (control, LB_SETCURSEL, 0, 0);
			break;
		case olImportanceHigh:
			SendMessage (control, LB_SETCURSEL, 2, 0);
			break;
		default:
			SendMessage (control, LB_SETCURSEL, 1, 0);
		
		}
	}

	// Start date
	pTask->get_StartDate (&date);
	control = GetDlgItem (hDlg, IDC_STARTDATE);
	if (date == DATE_NONE)
	{
		SendMessage (control, DTM_SETSYSTEMTIME, GDT_NONE, 0);
	}
	else
	{
		VariantTimeToSystemTime (date, &sysdate);
		if (control != NULL)
		{
			SendMessage (control, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&sysdate);
		}
	}

	// Due date
	pTask->get_DueDate (&date);
	control = GetDlgItem (hDlg, IDC_DUEDATE);
	if (date == DATE_NONE)
	{
		SendMessage (control, DTM_SETSYSTEMTIME, GDT_NONE, 0);
	}
	else
	{
		VariantTimeToSystemTime (date, &sysdate);
		if (control != NULL)
		{
			SendMessage (control, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&sysdate);
		}
	}

	// Notes
	pTask->get_Body (&taskNotes);
	SetDlgItemText (hDlg, IDC_NOTES, taskNotes);

	// Status Spinner
	pTask->get_Complete (&completed);
	control = GetDlgItem (hDlg, IDC_STATUSLIST);
	if (control != NULL)
	{
		if (completed)
			SendMessage (control, LB_SETCURSEL, 1, 0);
	}

	// Occurence
	// First setup list
	hr = pTask->GetRecurrencePattern (&pRec);
	control = GetDlgItem (hDlg, IDC_OCCURSLIST);
	
	pTask->get_StartDate (&date);
	if (date != DATE_NONE)
	{
		VariantTimeToSystemTime (date, &recurtime);
		SetRecurrenceControls (control, recurtime);
	}
	if (hr == S_OK)
	{
		DATE patternstart;
		SYSTEMTIME starttime;
		long patterntype;
		VARIANT_BOOL recurs;
		
		// Get the pattern start date if no startdate

		pRec->get_PatternStartDate(&patternstart);
		VariantTimeToSystemTime (patternstart, &starttime);
		//SetRecurrenceControls (control, starttime);

		// Add the last selection
		pTask->get_IsRecurring (&recurs);
		if (!(recurs))
			SendMessage (control, LB_SETCURSEL, 0, 0);
		else
		{
			// Get Recurrence type FIRST
			pRec->get_RecurrenceType (&patterntype);
			switch (patterntype)
			{
			case olRecursWeekly:
				SendMessage (control, LB_SETCURSEL, 1, 0);
				break;
			case olRecursMonthly:
				SendMessage (control, LB_SETCURSEL, 2, 0);
				break;
			case olRecursYearly:
				SendMessage (control, LB_SETCURSEL, 3, 0);
				break;
			default:  // once
				SendMessage (control, LB_SETCURSEL, 0, 0);
				break;
			}
		}
	}
		
	// Reminder
	pTask->get_ReminderTime (&date);
	pTask->get_ReminderSet (&hasReminder);
	control = GetDlgItem (hDlg, IDC_REMINDER);
	if (!(hasReminder))
	{
		SendMessage (control, DTM_SETSYSTEMTIME, GDT_NONE, 0);
	}
	else
	{
		VariantTimeToSystemTime (date, &sysdate);
		if (control != NULL)
		{
			SendMessage (control, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&sysdate);
		}
	}

	// Sensitivity
	pTask->get_Sensitivity(&sensitivity);
	if (sensitivity == olPrivate)
	{
		DebugOut (TEXT("Private Sensitivity!\n"));
		control = GetDlgItem (hDlg, IDC_PRIVATE);
		SendMessage (control, BM_SETCHECK, BST_CHECKED, 0);
	}

	// Cleanup
	pTask->Release();
	pRec->Release();
	SysFreeString (taskSubject);
	SysFreeString (taskNotes);
}

// SetTaskData
// ---------------
// This function is used to save edited and new task items
// It will go through each dialog box and 
void SetTaskData (HWND hDlg, ITask* pTask)
{
	TCHAR taskSubject[MAX_SUBJECT];
	TCHAR taskNotes [MAX_NOTES]; // Notes max
	IRecurrencePattern* pRec;

	HWND control;
	int selection;
	SYSTEMTIME sysdate;
	DATE date = 0;
	DATE startdate = 0;
	HRESULT hr;

	// Subject Field
	if (pTask== NULL)
		DebugOut (TEXT("PTASK IS NULL!!!\n"));

	GetDlgItemText (hDlg, IDC_SUBJECT, taskSubject, MAX_SUBJECT - 1); // Leave room for null termination

	// Check for at least one character in subject field?
	if (lstrcmp (taskSubject, TEXT("")) == 0)
		lstrcpy (taskSubject, UseString(IDS_NOSUBJECT));

	pTask->put_Subject (taskSubject);

	// Priority
	control = GetDlgItem (hDlg, IDC_PRIORITYLIST);
	if (control != NULL)
	{
		selection = SendMessage (control, LB_GETCURSEL, 0, 0);
		switch (selection)
		{
		case 0:
			pTask->put_Importance (olImportanceLow);
			break;
		case 2:
			pTask->put_Importance (olImportanceHigh);
			break;
		default:
			pTask->put_Importance (olImportanceNormal);
		}
	}

	// Date Rules:
	// 1. You do not need any dates at all
	// 2. If you have a start date, you MUST have a due date
	// 3. You may have just a due date.
	// 4. You may have a reminder time only if you have a due date

	// Start Date
	control = GetDlgItem (hDlg, IDC_STARTDATE);
	if (control != NULL)
	{
		if (SendMessage (control, DTM_GETSYSTEMTIME, 0, (LPARAM)&sysdate) == GDT_NONE)
		{
			pTask->put_StartDate (DATE_NONE);
		}
		else
		{
			NormalizeTime (&sysdate);
			SystemTimeToVariantTime (&sysdate, &date);
			pTask->put_StartDate (date);
			startdate = date;
		}
	}

	// Due Date
	control = GetDlgItem (hDlg, IDC_DUEDATE);
	if (control != NULL)
	{
		if (SendMessage (control, DTM_GETSYSTEMTIME, 0, (LPARAM)&sysdate) == GDT_NONE)
		{
			pTask->put_DueDate (DATE_NONE);
		}
		else
		{
			NormalizeTime (&sysdate);
			SystemTimeToVariantTime (&sysdate, &date);
			pTask->put_DueDate (date);
		}
	}

	// Notes
	GetDlgItemText (hDlg, IDC_NOTES, taskNotes, 999);
	pTask->put_Body (taskNotes);

	// Status
	control = GetDlgItem (hDlg, IDC_STATUSLIST);
	if (control != NULL)
	{
		selection = SendMessage (control, LB_GETCURSEL, 0, 0);
		if (selection == 0)
			pTask->put_Complete (FALSE);
		else
			pTask->put_Complete (TRUE);
	}


	// Occurrence
	control = GetDlgItem (hDlg, IDC_OCCURSLIST);
	if (control != NULL)
	{
		DebugOut (TEXT("Setting recurrence\n"));
		int selection = SendMessage (control, LB_GETCURSEL, 0, 0);
		SYSTEMTIME systime;
		DATE date;
		int daymask;

		pTask->GetRecurrencePattern (&pRec);
		pTask->get_StartDate (&date);
		if (date == DATE_NONE)
		{
			GetSystemTime (&systime);
			SystemTimeToVariantTime (&systime, &date);
		}
		else
		{
			VariantTimeToSystemTime (date, &systime); // Use start date
		}

		switch (selection)
		{
		case 0:
			pTask->ClearRecurrencePattern ();
			break;
		case 1:
			pRec->put_RecurrenceType (olRecursWeekly);
			pRec->put_PatternStartDate (date);
			daymask = (int)(pow(2, (double)systime.wDayOfWeek));
			DebugOut (TEXT("DAY OF WEEK MASK: %d\n"), daymask);
			pRec->put_DayOfWeekMask (daymask); // mask flags 
			pRec->put_Interval (1);
			pRec->put_NoEndDate (TRUE);
			break;
		case 2:
			pRec->put_RecurrenceType (olRecursMonthly);
			pRec->put_Interval (1);
			pRec->put_DayOfMonth (systime.wDay);
			pRec->put_PatternStartDate (date);
			pRec->put_NoEndDate (TRUE);
			break;
		case 3:
			pRec->put_RecurrenceType (olRecursYearly);
			pRec->put_PatternStartDate (date);
			pRec->put_DayOfMonth (systime.wDay);
			pRec->put_MonthOfYear (systime.wMonth);
			pRec->put_NoEndDate (TRUE);
			break;
		default:
			break;
		}
	
	}		

	// Reminder Date
	control = GetDlgItem (hDlg, IDC_REMINDER);
	if (control != NULL)
	{
		if (SendMessage (control, DTM_GETSYSTEMTIME, 0, (LPARAM)&sysdate) == GDT_NONE)
		{
			//pTask->put_ReminderTime (DATE_NONE);
			pTask->put_ReminderSet (FALSE);
		}
		else
		{
			NormalizeTime (&sysdate);
			SystemTimeToVariantTime (&sysdate, &date);
			pTask->put_ReminderTime (date);
			pTask->put_ReminderSet (TRUE);
		}
	}
		
	// Sensitivity
	control = GetDlgItem (hDlg, IDC_PRIVATE);
	if (control != NULL)
	{
		if (SendMessage (control, BM_GETCHECK, 0, 0) == BST_CHECKED)
			pTask->put_Sensitivity(olPrivate);
		else
			pTask->put_Sensitivity(olNormal);
	}

	// Save to POOM
	hr = pTask->Save();
	if (hr == S_OK)
		DebugOut (TEXT("SAVED OK!\n"));
	else
	{
		if (hr == E_INVALIDREMINDERTIME)
			MessageBox (hDlg, UseString(IDS_TASKERR_INVALIDREMINDERTIME), NULL, MB_OK | MB_ICONERROR);
		if (hr == E_INVALIDDATES)
			MessageBox (hDlg, UseString(IDS_TASKERR_INVALIDDATES), NULL, MB_OK | MB_ICONERROR);
		else
			MessageBox (hDlg, UseString(IDS_TASKERR), NULL, MB_OK | MB_ICONERROR);
	}

	pTask->Release();
	pRec->Release();

}

// NormalizeTime ()
// ----------------------
// Normalize all times to 12:00AM
void NormalizeTime (LPSYSTEMTIME systime)
{
	systime->wHour = 0;
	systime->wMinute = 0;
	systime->wSecond = 0;
	systime->wMilliseconds = 0;
}

// SetOptions ()
// -------------------
// Set the filtering and sorting flags based on the
// choices in the options dialog
void SetOptions (HWND hDlg)
{
	HWND control;
	int selection;

	control = GetDlgItem (hDlg, IDC_SORTLIST);
	if (control != NULL)
	{
		selection = SendMessage (control, LB_GETCURSEL, 0, 0);
		switch (selection)
		{
		case 1:
			g_Sort = status;
			break;
		case 2:
			g_Sort = subject;
			break;
		case 3:
			g_Sort = start;
			break;
		case 4:
			g_Sort = due;
			break;
		default:
			g_Sort = importance;
			break;
		}
	}

	control = GetDlgItem (hDlg, IDC_CATEGORYLIST);
	// do something

	control = GetDlgItem (hDlg, IDC_DISPLAYLIST);
	// do something
	if (control != NULL)
	{
		selection = SendMessage (control, LB_GETCURSEL, 0, 0);
		switch (selection)
		{
		case 1:
			g_Filter = completed;
			break;
		case 2:
			g_Filter = active;
			break;
		default:
			g_Filter = all;
			break;
		}
	}
}

// SortItems ()
// -----------------
// Will sort items according to the sort flag
HRESULT SortItems (IPOutlookItemCollection *pItemCol)
{
	HRESULT hr;

	switch (g_Sort)
	{
	case importance:
		hr = pItemCol->Sort (TEXT("[Importance]"), TRUE); // Highest at top
		break;
	case status:
		hr = pItemCol->Sort (TEXT("[Complete]"), TRUE);
		break;
	case subject:
		hr = pItemCol->Sort (TEXT("[Subject]"), FALSE);
		break;
	case start:
		hr = pItemCol->Sort (TEXT("[StartDate]"), FALSE);
		break;
	case due:
		hr = pItemCol->Sort (TEXT("[DueDate]"), FALSE);
		break;
	default:
		break;	
	}

	return hr;
}

IPOutlookItemCollection* GetTaskList()
{
	IPOutlookItemCollection *pItemCol = NULL;
	HRESULT hr;
	
	hr = g_pTaskFolder->get_Items(&pItemCol);
	if(FAILED(hr))
	{
		DebugOut (TEXT("Failed to get task list\n"));
		return NULL;
	}

	hr = SortItems(pItemCol);

	if(FAILED(hr))
	{
		DebugOut (TEXT("Sort failed\n"));
		pItemCol->Release();
		return NULL;
	}

	return pItemCol;
}



