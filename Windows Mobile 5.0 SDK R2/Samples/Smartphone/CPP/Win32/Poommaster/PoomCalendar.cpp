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
// POOMCALENDAR.CPP
// 
// Implementation of reading / creating POOM calendar information
//
//

// Includes
#include "PoomMaster.h"

// Constants
#define MAX_DATE_LENGTH 28

// Forward Declarations
void FillDateString(LPSYSTEMTIME pst, 
					TCHAR * tszDate, 
					int nLen);

// **************************************************************************
// Function Name: AddCalendarFolderText
// 
// Purpose: Reads and adds existing POOM appointments to the main listbox
//
// Arguments:
//    IN IPOutlookItemCollection * pItenCol - ptr to the Calendar's default folder
//		collection interface
//
// Return Values:
//    Describes the return type an meaning of each value.  E.g.:
//    BOOL
//    returns TRUE if the item was successfully read and added. Otherwise FALSE
// 
// Description:  
//   This function terates through the collection of appointments, reading 
//		properties from each. The date data is converted into a presentable
//		string and added to the listview along with the appointment subject

BOOL AddCalendarFolderText(IPOutlookItemCollection * pItemCol)
{
	
	BSTR bstrSubject;
	DATE dateStart;
	SYSTEMTIME stStart;
	BSTR bstrAppntmnt;
	TCHAR tszStartDate[MAX_DATE_LENGTH];
	
	
	IAppointment * pAppntmnt = NULL;
	int cItems = 0;
	
	if (!pItemCol)
	{
		return FALSE;
	}
	
	pItemCol->get_Count(&cItems);
	
	for (int i = 1; i <= cItems; i++)
	{
		if (SUCCEEDED(pItemCol->Item (i, 
			reinterpret_cast<IDispatch**>(&pAppntmnt))))
		{
			// grab some of the more relevant props
			pAppntmnt->get_Subject(&bstrSubject);
			pAppntmnt->get_Start(&dateStart);
			
			VariantTimeToSystemTime(dateStart,
				&stStart);
			// convert numerical date to a formatted string
			FillDateString(&stStart, tszStartDate, MAX_DATE_LENGTH);
			
			//allocate a BSTR to store the Appointment information
			bstrAppntmnt = SysAllocStringLen(NULL, SysStringLen(bstrSubject) + _tcslen(tszStartDate)+ (2*(sizeof(TCHAR))) );
			memset(bstrAppntmnt, 0, SysStringLen(bstrAppntmnt)*sizeof(TCHAR));
			
			//copy thing Appointment subject and date into the same string
			_tcsncpy(bstrAppntmnt, bstrSubject, SysStringLen(bstrSubject));
			_tcscat(bstrAppntmnt, _T("\n"));
			_tcscat(bstrAppntmnt, tszStartDate);
			
			// add the string to the listview control
			AddToList(bstrAppntmnt);
	
			// clean up
			pAppntmnt->Release();
			SysFreeString(bstrAppntmnt);
			SysFreeString(bstrSubject);
			bstrAppntmnt = NULL;
			bstrSubject = NULL;
			tszStartDate[0] = _T('\0');
		
		}
		else
		{
			return FALSE;
		}
	}
	
	return TRUE;
	
}

// **************************************************************************
// Function Name: FillDateString
// 
// Purpose: provide readable date data by formatting SYSTEMTIME data
//
// Arguments:
//    IN LPSYSTEMTIME - ptr to struct containing date and time information
//    OUT TCHAR tszDate - buffer for returned formatted string
//	  IN int nLen - length (in chars) of tszDate
//
//
// Return Values:
//    void
// 
// Description:  
//    This function simply creates a human-readable date string from a given
//	SYSTEMTIME struct. the output should look like: "1/02/2003 - 17:49"
void FillDateString(LPSYSTEMTIME pst, 
					TCHAR * tszDate, 
					int nLen)
{
	
	TCHAR tmp[5];
	_itot(pst->wMonth, tmp, 10);
	_tcscpy(tszDate, tmp);
	_tcscat(tszDate, _T("/"));
	
	_itot(pst->wDay, tmp, 10);
	_tcscat(tszDate, tmp);
	_tcscat(tszDate, _T("/"));
	
	_itot(pst->wYear, tmp, 10);
	_tcscat(tszDate, tmp);
	_tcscat(tszDate, _T(" - "));
	
	_itot(pst->wHour, tmp, 10);
	
	_tcscat(tszDate, tmp);
	_tcscat(tszDate, _T(":"));
	
	if (pst->wMinute < 10)
		_tcscat(tszDate, _T("0"));
	
	_itot(pst->wMinute, tmp, 10);
	_tcscat(tszDate, tmp); 
	
}

// **************************************************************************
// Function Name: NewAppntmntProc
// 
// Purpose: Processes messages for the new appointment dialog window
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
//		a new appointment is created according to values entered for time and subject
LRESULT CALLBACK NewAppntmntProc(HWND hDlg, 
								 UINT message, 
								 WPARAM wParam, 
								 LPARAM lParam)
{
	
	SYSTEMTIME stSelectedTime;
	int nDay;
	int nMonth;
	int nYear;
	IPOutlookApp * pOutApp = NULL;
	IAppointment * pNewAppntmnt = NULL;
	DATE date;
	BSTR bstrSubject;
	
	HWND hDayMonthCtrl;
	HWND hTimeCtrl;
	
	switch (message)
	{
	case WM_INITDIALOG:
		
		InitNewItemDlg(hDlg);
		if(TRUE == IsSmartphone())
		{
			RemoveBorder(GetDlgItem(hDlg, IDC_DAYMONTHPICKER));
			RemoveBorder(GetDlgItem(hDlg, IDC_TIMEPICKER));
			RemoveBorder(GetDlgItem(hDlg, IDC_DESC));
		}
		return TRUE; 
		
	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{
		case IDM_CANCEL:
			
				EndDialog(hDlg, IDCANCEL);
				break;
		case IDM_OK:
		case IDOK:
			hDayMonthCtrl = GetDlgItem(hDlg, IDC_DAYMONTHPICKER);
			MonthCal_GetCurSel(hDayMonthCtrl, &stSelectedTime);
			nDay = stSelectedTime.wDay;
			nMonth = stSelectedTime.wMonth;
			nYear = stSelectedTime.wYear;
			
			hTimeCtrl = GetDlgItem(hDlg, IDC_TIMEPICKER);
			MonthCal_GetCurSel(hTimeCtrl, &stSelectedTime);
			stSelectedTime.wDay = nDay;
			stSelectedTime.wMonth = nMonth;
			stSelectedTime.wYear = nYear;
			
			GetCtrlBstr(hDlg, IDC_DESC, &bstrSubject);
			
			if (SysStringLen(bstrSubject) <= 1)
			{
				MessageBox(hDlg, _T("Please enter a description"), _T("Error"), MB_OK);
				return TRUE;
				
			}
			
			if (GetPoomApp(&pOutApp))
			{
				
				if (SUCCEEDED(pOutApp->CreateItem(olAppointmentItem, (IDispatch **)&pNewAppntmnt)))
				{
					SystemTimeToVariantTime(&stSelectedTime, &date);
					
					pNewAppntmnt->put_Start(date);
					pNewAppntmnt->put_Subject(bstrSubject);
					
					pNewAppntmnt->Save();
					
					pNewAppntmnt->Release();
					pOutApp->Release();
					
					
				}
				else // CreateItem Failed
				{
					MessageBox(hDlg, _T("Could not create new item"), _T("Error"), MB_OK);
					pOutApp->Release();
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
					
				}
			}
			else //GetPoomApp failed
			{
				MessageBox(hDlg, _T("POOM session failure"), _T("Error"), MB_OK);
				EndDialog(hDlg, IDCANCEL);
				return TRUE;
			}
			
			SysFreeString(bstrSubject);
			EndDialog(hDlg, IDOK);
			return TRUE;
		}
		
		break;
	}
	return FALSE;
}
