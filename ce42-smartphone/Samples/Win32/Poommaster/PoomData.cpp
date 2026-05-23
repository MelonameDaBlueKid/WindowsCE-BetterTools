// ************************************************************
// POOMDATA.CPP
// 
// Implementation of generic POOM data access functions
//
// Copyright 1986-2003 Microsoft Corporation, All Rights Reserved

// Includes
#include "PoomMaster.h"

// Globals
IPOutlookApp * g_polApp = NULL;


// **************************************************************************
// Function Name: InitPoom
// 
// Purpose: Creates and logs on to the POOM application object
//
// Arguments:
//    none
//
// Return Values:
//    BOOL
//    returns TRUE if POOM was initialized, FALSE otherwise
// 
// Description:  
//   This function creates the POOM application COM object and starts a POOM
//	session via Logon. This must be done before any subsequent POOM calls are 
//	made.
BOOL InitPoom(HWND hwnd)
{
	
	;
	BOOL bSuccess = FALSE;
	
	if (SUCCEEDED(CoInitializeEx( NULL, 0)))
	{
		// Now, let's get the main outlook application
		   if (SUCCEEDED(CoCreateInstance(CLSID_Application, NULL, CLSCTX_INPROC_SERVER, 
			IID_IPOutlookApp, reinterpret_cast<void **>(&g_polApp))))
		   {
	
			// login to the Pocket Outlook object model
			if(SUCCEEDED(g_polApp->Logon(NULL)))
			{
				// can't login to the app
				bSuccess = TRUE;
			}
		}

	}
	
	return bSuccess;
}

// **************************************************************************
// Function Name: GetPoomFolder
// 
// Purpose: Gets the default folder for the specified POOM item type
//
// Arguments:
//    IN int nFolder - POOM folder type to return, olFolderTasks,
//		olFolderContacts, or olFolderCalendar in this app
//	  OUT IFolder ** ppFolder - pointer to IFolder interface returned. 
//			Must be released by caller of GetPoomFolder
//
// Return Values:
//    BOOL
//    returns TRUE if the folder interface was retrieved, FALSE otherwise
// 
// Description:  
//  This function simply encapsulates a call on the global Outlook app interface. The 
//	returned pointer is simply passed through this function.
BOOL GetPoomFolder(int nFolder, 
				   IFolder ** ppFolder)
{

	if (SUCCEEDED(g_polApp->GetDefaultFolder(nFolder, ppFolder)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

// **************************************************************************
// Function Name: GetPoomApp
// 
// Purpose: Gets pointer to POOM application interface
//
// Arguments:
//	  OUT IFolder ** ppFolder - pointer to IPOutlookApp interface returned. 
//			Must be released by caller of GetPoomApp
//
// Return Values:
//    BOOL
//    returns TRUE if the folder interface was retrieved, FALSE otherwise
// 
// Description:  
//  This function simply returns a pointer to the global Outlook app interface 
//	The returned pointer is simply passed through this function after being AddRef'd.
BOOL GetPoomApp(IPOutlookApp **ppOutApp)
{
	if (g_polApp)
	{
		g_polApp->AddRef();
		*ppOutApp = g_polApp;
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
	
}
// **************************************************************************
// Function Name: PopulateList
// 
// Purpose: Populates listbox with POOM items from given folder
//
// Arguments:
//	  IN int nFolder - POOM folder to read/add items from. In this app, either
//		olFolderTasks, olFolderContacts, or olFolderCalendar
//
// Return Values:
//    BOOL
//    returns TRUE if the items were successfully accessed, FALSE otherwise
// 
// Description:  
//  This function reads each POOM item from the given category (Tasks, Contacts,
//	or Appointments) and adds each to the main listbox control
BOOL PopulateList(int nFolder)
{
	IFolder * pCurrFldr = NULL;
	IPOutlookItemCollection * pItemCol = NULL;
		// Get the folder and its items, depending on
		// the folder type
		if (GetPoomFolder(nFolder, &pCurrFldr))
	{
		
		if (SUCCEEDED(pCurrFldr->get_Items(&pItemCol)))
		{
			switch (nFolder)
			{
			case olFolderTasks:
				
				AddTaskFolderText(pItemCol);
				break;
				
			case olFolderContacts:
				
				AddContactsFolderText(pItemCol);
				break;
				
			case olFolderCalendar:
				
				AddCalendarFolderText(pItemCol);
				break;
			}
			
			pItemCol->Release();
			pCurrFldr->Release();
			return TRUE;
		}
		
		pCurrFldr->Release();
	}
	
	return FALSE;
	
	
}
// **************************************************************************
// Function Name: ShutdownPoom
// 
// Purpose: Shuts down the current POOM session
//
// Arguments:
//	  none
//
// Return Values:
//   none
// 
// Description:  
//  This function logs off the current POOM session and releases the POOM 
//	application interface pointer
void ShutdownPoom()
{

	if (g_polApp)
	{
		g_polApp->Logoff();
		g_polApp->Release();
	}

	CoUninitialize();

}