//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// ************************************************************
// POOMCONTACTS.CPP
// 
// Implementation of reading / creating POOM contact information
//

//Includes
#include "PoomMaster.h"

// **************************************************************************
// Function Name: AddContactsFolderText
// 
// Purpose: Reads and adds existing POOM contacts to the main listbox
//
// Arguments:
//    IN IPOutlookItemCollection * pItenCol - ptr to the Contacts default folder
//		collection interface
//
// Return Values:
//    Describes the return type an meaning of each value.  E.g.:
//    BOOL
//    returns TRUE if the item was successfully read and added. Otherwise FALSE
// 
// Description:  
//   This function terates through the collection of contancts, reading 
//		properties from each. The string data is then combined and added to
//		the main listview control
BOOL AddContactsFolderText(IPOutlookItemCollection * pItemCol)
{
	BSTR bstrFirstName;
	BSTR bstrLastName;
	BSTR bstrPhoneNumber;
	BSTR bstrContactInfo;
	
	
	IContact * pContact = NULL;
	int cItems = 0;
	
	pItemCol->get_Count(&cItems);
	
	for (int i = 1; i <= cItems; i++)
	{
		if (SUCCEEDED(pItemCol->Item (i, reinterpret_cast<IDispatch**>(&pContact))))
		{
			// grab properties
			pContact->get_FirstName(&bstrFirstName);
			pContact->get_LastName(&bstrLastName);
			pContact->get_HomeTelephoneNumber(&bstrPhoneNumber);

			// allocate a buffer for all the properties plus a comma, space. newline, and terminating null
			bstrContactInfo = SysAllocStringByteLen(NULL, SysStringByteLen(bstrFirstName) +
			   SysStringByteLen(bstrLastName) + 
			   SysStringByteLen(bstrPhoneNumber) + 
			   (4*sizeof(OLECHAR)));
		
			// copy the strings into one
			_tcscpy(bstrContactInfo, bstrLastName);
			_tcscat(bstrContactInfo, _T(", "));
			_tcscat(bstrContactInfo, bstrFirstName);
			_tcscat(bstrContactInfo, _T("\n"));
			_tcscat(bstrContactInfo, bstrPhoneNumber);
	
			// add it to the listview
			AddToList(bstrContactInfo);

			// clean up
			SysFreeString(bstrFirstName);
			SysFreeString(bstrLastName);
			SysFreeString(bstrPhoneNumber);
			SysFreeString(bstrContactInfo);
			pContact->Release();
		}
	}
	
	return TRUE;
	
}

// **************************************************************************
// Function Name: NewContactProc
// 
// Purpose: Processes messages for the new contact dialog window
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
//		a new contact is created according to values entered for time and subject
LRESULT CALLBACK NewContactProc(HWND hDlg, 
								UINT message, 
								WPARAM wParam, 
								LPARAM lParam)
{
	BSTR bstrFirstName;
	BSTR bstrLastName;
	BSTR bstrPhoneNumber;
	
	IPOutlookApp * pOutApp = NULL;
	IContact * pNewContact = NULL;
	
	switch (message)
	{
	case WM_INITDIALOG:
	  
		InitNewItemDlg(hDlg);
				if(TRUE == IsSmartphone())
		{
			RemoveBorder(GetDlgItem(hDlg, IDC_FIRSTNAME));
			RemoveBorder(GetDlgItem(hDlg, IDC_LASTNAME));
			RemoveBorder(GetDlgItem(hDlg, IDC_PHONENUMBER));
		}
		return TRUE; 
		
	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{
		case IDM_CANCEL:
			// close the dialog
			EndDialog(hDlg, IDCANCEL);
			break;
		case IDM_OK:
		case IDOK:
			
			GetCtrlBstr(hDlg, IDC_FIRSTNAME, &bstrFirstName); 
			GetCtrlBstr(hDlg, IDC_LASTNAME, &bstrLastName);
			GetCtrlBstr(hDlg, IDC_PHONENUMBER, &bstrPhoneNumber);
			
			if (GetPoomApp(&pOutApp))
			{
				
				if (SUCCEEDED(pOutApp->CreateItem(olContactItem, reinterpret_cast<IDispatch **>(&pNewContact))))
				{
					// set the new contact properties
					pNewContact->put_FirstName(bstrFirstName);
					pNewContact->put_LastName(bstrLastName);
					pNewContact->put_HomeTelephoneNumber(bstrPhoneNumber);
					
					// save and clean up
					pNewContact->Save();
					pNewContact->Release();
					pOutApp->Release();
					
					SysFreeString(bstrFirstName);
					SysFreeString(bstrLastName);
					SysFreeString(bstrPhoneNumber);

					EndDialog(hDlg, IDOK);
				}
			}
			
			return TRUE;
			
		}
		break;
	}
	return FALSE;
}

