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
//

// ExTAPIASync.CPP
//
// Sample that demonstrates some asynchronous functionality of ExTAPI
//
// NOTE: ExTAPI is a privileged API and any application using it must
// be signed using a priviliged certificate.
//

#include <windows.h>
#include <tapi.h>
#include <extapi.h>
#include <tsp.h>
#include <winuserm.h>
#include <aygshell.h>
#include "newres.h"
#include "resource.h"

// some definitons
#define ARRAY_LENGTH(x)			(sizeof(x)/sizeof((x)[0]))
#define TAPI_API_LOW_VERSION	0x00020000
#define TAPI_API_HIGH_VERSION	0x00020000
#define EXT_API_LOW_VERSION		0x00010000
#define EXT_API_HIGH_VERSION	0x00010000
#define REASONABLE_BUFFER		1024
#define EINITFAILED				(-1)

// global variables
HINSTANCE	g_hInstance;
TCHAR		g_szAppName[80];
TCHAR		g_szTitle[80];
HLINEAPP	g_hLineApp;
HLINE		g_hLine;
HWND		g_hwndOpList;
HWND		g_hDlg;

// function declarations
BOOL InitExTAPI();
BOOL GetCurrentOperator(HWND hDlg);
BOOL GetAvailableOperators(HWND hDlg);
DWORD GetTSPLineDeviceID(const HLINEAPP hLineApp, const DWORD dwNumberDevices, 
						 const DWORD dwAPIVersionLow, const DWORD dwAPIVersionHigh, 
						 const TCHAR* const psTSPLineName);
BOOL CALLBACK MainDialogProc(const HWND hDlg, const UINT uiMessage, 
							 const WPARAM wParam, const LPARAM lParam);
void CALLBACK TAPIProc(DWORD hDevice, DWORD dwMessage, DWORD dwInstance,
					   DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);
BOOL InitDialog(const HWND hDlg, UINT nToolBarId);
void RegisterNewOperator();
void CleanupLB();

// ***************************************************************************
// Function Name: WinMain
//
// Purpose: Main entry point into the ExTAPIAsync program
//
// Arguments: Standard WinMain arguments
//
// Return Values: TRUE
//
// Description:
//	Our WinMain function essentialy just pops up a Dialog box that displays
//	the current operator and allows you to register with a new one

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPreviousInstance,
                    LPWSTR pszCommandLine,
                    int nCommandShow)
{
	int		iResult;

	// Load strings
	LoadString(hInstance, IDS_EXTAPIA_APPNAME, g_szAppName, ARRAY_LENGTH(g_szAppName));
	LoadString(hInstance, IDS_EXTAPIA_TITLE, g_szTitle, ARRAY_LENGTH(g_szTitle));

    // Use a globally named mutex to detect another instance of EXTAPIAsync
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_EXTAPIA_EXE_MUTEX_"));

    // check the result code
	if(0 != hMutex) {
        // First instance running?  Okay to proceed...
		if(ERROR_ALREADY_EXISTS != GetLastError()) {
			g_hInstance = hInstance;
			InitCommonControls();

			// try to initialize ExTAPI
			if (InitExTAPI()) {
				iResult = DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_EXTAPIA_DLGMAIN),
									0, (DLGPROC)MainDialogProc);
				
				if (iResult) {
					MessageBox(NULL, TEXT("An error occurred while getting ExTAPI information"),
							   TEXT("Error!!!"), MB_OK | MB_ICONERROR);
				}
				
				// cleanup
				lineClose(g_hLine);
				lineShutdown(g_hLineApp);
			} else {
				MessageBox(NULL, TEXT("Unable to initialize ExTAPI"),
						   TEXT("Error!!!"), MB_OK | MB_ICONERROR);
			}
		}
        else {
            // Already an instance running - attempt to switch to it and then exit
            const HWND hWndExistingInstance = FindWindow(TEXT("Dialog"), g_szTitle);
			VERIFY((0 == hWndExistingInstance) || SetForegroundWindow(hWndExistingInstance));
        }
        VERIFY(CloseHandle(hMutex));
    }

    return TRUE;
}

// ***************************************************************************
// Function Name: InitExTAPI
// 
// Purpose: Set up ExTAPI
//
// Arguments: none
//
// Return Values:
//	TRUE if successful, FALSE otherwise
//
// Side Effects:
//	Sets g_hLineApp and g_hLine
//	Sets up TapiProc as a TAPI callback function
//	
// Description:
//	This function initializes and opens lines for ExTAPI.  The HLINEAPP and HLINE
//	will be used later to get and set operators.

BOOL InitExTAPI()
{
	DWORD dwNumDevs;
	DWORD dwAPIVersion = TAPI_API_HIGH_VERSION;
	LINEINITIALIZEEXPARAMS liep;
	DWORD dwExtVersion;

	// set the line init params
	liep.dwTotalSize = sizeof(liep);
	liep.dwOptions = LINEINITIALIZEEXOPTION_USEHIDDENWINDOW;
	
	if (lineInitializeEx(&g_hLineApp, g_hInstance, &TAPIProc, TEXT("EXTAPISAMPLE"), 
						 &dwNumDevs, &dwAPIVersion, &liep)) {
		return FALSE;
	}

	// get the device ID
	DWORD dwTAPILineDeviceID = GetTSPLineDeviceID(g_hLineApp, dwNumDevs, 
												  TAPI_API_LOW_VERSION, 
												  TAPI_API_HIGH_VERSION, 
												  CELLTSP_LINENAME_STRING);

	// error getting the line device ID?
	if (0xffffffff == dwTAPILineDeviceID) {
		lineShutdown(g_hLineApp);
		return FALSE;
	}

	// now try and open the line
	const DWORD dwMediaMode = LINEMEDIAMODE_DATAMODEM | LINEMEDIAMODE_INTERACTIVEVOICE;

	if(lineOpen(g_hLineApp, dwTAPILineDeviceID, 
				&g_hLine, dwAPIVersion, 0, 0, 
				LINECALLPRIVILEGE_OWNER, dwMediaMode, 0)) {
		lineShutdown(g_hLineApp);
		return FALSE;
	}

	// set up ExTAPI
	if (lineNegotiateExtVersion(g_hLineApp, dwTAPILineDeviceID, 
								dwAPIVersion, EXT_API_LOW_VERSION, 
								EXT_API_HIGH_VERSION, &dwExtVersion)) {
		lineClose(g_hLine);
		lineShutdown(g_hLineApp);
		return FALSE;
	}

	return TRUE;
}

// ***************************************************************************
// Function Name: GetTSPLineDeviceID
//
// Purpose: To get a TSP Line Device ID
//
// Arguments:
//	hLineApp = the HLINEAPP returned by lineInitializeEx
//	dwNumberDevices = also returned by lineInitializeEx
//	dwAPIVersionLow/High = min version of TAPI that we need
//	psTSPLineName = "Cellular Line"
//
// Return Values: Current Device ID
//
// Description:
//	This function returns the device ID of a named TAPI TSP.  The Device ID is 
//	used in the call to lineOpen

DWORD GetTSPLineDeviceID(const HLINEAPP hLineApp, 
						 const DWORD dwNumberDevices, 
						 const DWORD dwAPIVersionLow, 
						 const DWORD dwAPIVersionHigh, 
						 const TCHAR* const psTSPLineName)
{
	DWORD dwReturn = 0xffffffff;
	for(DWORD dwCurrentDevID = 0 ; dwCurrentDevID < dwNumberDevices ; dwCurrentDevID++)
	{
		DWORD dwAPIVersion;
		LINEEXTENSIONID LineExtensionID;
		if(0 == lineNegotiateAPIVersion(hLineApp, dwCurrentDevID, 
										dwAPIVersionLow, dwAPIVersionHigh, 
										&dwAPIVersion, &LineExtensionID)) {
			LINEDEVCAPS LineDevCaps;
			LineDevCaps.dwTotalSize = sizeof(LineDevCaps);
			if(0 == lineGetDevCaps(hLineApp, dwCurrentDevID, 
								   dwAPIVersion, 0, &LineDevCaps)) {
				BYTE* pLineDevCapsBytes = new BYTE[LineDevCaps.dwNeededSize];
				if(0 != pLineDevCapsBytes) {
					LINEDEVCAPS* pLineDevCaps = (LINEDEVCAPS*)pLineDevCapsBytes;
					pLineDevCaps->dwTotalSize = LineDevCaps.dwNeededSize;
					if(0 == lineGetDevCaps(hLineApp, dwCurrentDevID, 
										   dwAPIVersion, 0, pLineDevCaps)) {
						if(0 == _tcscmp((TCHAR*)((BYTE*)pLineDevCaps+pLineDevCaps->dwLineNameOffset), psTSPLineName)) {
							dwReturn = dwCurrentDevID;
						}
					}
					delete[]  pLineDevCapsBytes;
				}
			}
		}
	}
	return dwReturn;
}

// ***************************************************************************
// Function Name: MainDialogProc
// 
// Purpose: Message Handler for ExTAPIAsync Dialog Box
//
// Arguments: Standard Dialog Procedure Arguments
//
// Return Values:
//	EINITFAILED - One of the components in the dialog box could not be initialized
//	0 - success
//
// Side Effects:
//	Sets g_hDlg and g_hwndOpList
//	
// Description:
//	Dialog Procedure for the main ExTAPIAsync Dialog.  Displays the current
//	operator and a list of available operators.  Allows the user to try and register
//	with a different operator.

BOOL CALLBACK MainDialogProc(const HWND hDlg, const UINT uiMessage, 
							 const WPARAM wParam, const LPARAM lParam)
{
	BOOL	bProcessedMsg = TRUE;

	switch(uiMessage)
	{
		case WM_INITDIALOG:
			if (!InitDialog(hDlg, IDR_EXTAPIA_DLGMENU)) {
				EndDialog(hDlg, EINITFAILED);
				return TRUE;
			}

			// store the hDlg
			g_hDlg = hDlg;
			
			// get current operator
			if (!GetCurrentOperator(hDlg)) {
				EndDialog(hDlg, EINITFAILED);
				return TRUE;
			}

			// get a handle to the listbox
			VERIFY(g_hwndOpList = GetDlgItem(hDlg, IDC_EXTAPIA_AVAILOP));
			
			// get available operators
			if (!GetAvailableOperators(hDlg)) {
				CleanupLB();
				EndDialog(hDlg, EINITFAILED);
				return TRUE;
			}

			// set the currently selected item
			SendMessage(g_hwndOpList, LB_SETCURSEL, 0, 0);

			break;

		case WM_COMMAND:
			switch (wParam) {			
				case IDM_EXTAPIA_QUIT:
					CleanupLB();
					EndDialog(hDlg, 0);
					break;

				case IDM_EXTAPIA_REG:
					{
						RegisterNewOperator();
						break;
					}

				default:
					bProcessedMsg = FALSE;
					break;
			}
			break;
		
		default:
			bProcessedMsg = FALSE;
			break;
	}

	return bProcessedMsg;
}

// ***************************************************************************
// Function Name: InitDialog
// 
// Purpose: Sizes a dialog box to be full screen and adds the menus
//
// Arguments:
//	hDlg = the HWND of the dialog box
//	nToolBarId = the ID of the menu bar to add
//
// Return Values:
//	TRUE if successful, FALSE otherwise
//
// Description:
//	This function simply takes an HWND for a dialog, makes it full screen, adds
//	a menu bar, and sets the title bar to be the title of the application.

BOOL InitDialog(const HWND hDlg, UINT nToolBarId)
{
	// Specify that the dialog box should stretch full screen
	SHINITDLGINFO shidi;
	ZeroMemory(&shidi, sizeof(shidi));
	shidi.dwMask = SHIDIM_FLAGS;
	shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
	shidi.hDlg = hDlg;

	// set up Soft Keys menu
	SHMENUBARINFO mbi;
	ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
	mbi.cbSize = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hDlg;
	mbi.nToolBarId = nToolBarId;
	mbi.hInstRes = g_hInstance;

	// If we could not initialize the dialog box, return an error
	if (!(SHInitDialog(&shidi) && SHCreateMenuBar(&mbi))) {
		return FALSE;
	}

	// set the title bar
	VERIFY(SetWindowText(hDlg, g_szTitle));

	// In order to make Back work properly, it's necessary to 
	// override it and then call the appropriate SH API
	(void)SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
					  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
								 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;
}

// ***************************************************************************
// Function Name: TAPIProc
// 
// Purpose: Callback function for asynchronous TAPI calls
//
// Arguments: Standard TAPI callback arguments
//
// Return Values: None
//
// Description:
//	Normally, this function would respond to any messages created by calls to
//	asynchronous TAPI functions.  One would definitely want to keep track of the
//	request numbers so they could be matched to their replies.  However, since this 
//	program only has one asynchronous call, we just assume that anything that passes
//	through here was a reply to that call.

void CALLBACK TAPIProc(DWORD hDevice, DWORD dwMessage, DWORD dwInstance,
					   DWORD dwParam1, DWORD dwParam2, DWORD dwParam3)
{
	// since we only made one asynch request, we just want to see if it was
	// successful or not.  A dwParam2 of 0 indicates success.
	if (dwMessage == LINE_REPLY) {
		if (!dwParam2) {
			MessageBox(g_hDlg, TEXT("LINE_REPLY: Success!"), 
					   g_szTitle, MB_OK | MB_ICONINFORMATION);
		} else {
			MessageBox(g_hDlg, TEXT("LINE_REPLY: Failure"), 
					   g_szTitle, MB_OK | MB_ICONERROR);
		}
		// Update the Current Operator text box
		GetCurrentOperator(g_hDlg);
	}
}

// ***************************************************************************
// Function Name: GetCurrentOperator
// 
// Purpose: Get the current operator and update the dialog display
//
// Arguments:
//	hDlg - the dialog containing the IDC_EXTAPIA_CUROP control
//
// Return Values:
//	TRUE if successful, FALSE otherwise
//
// Side Effects:
//	Updates the text for control IDC_EXTAPIA_CUROP
//
// Description:
//	This function simply calls the lineGetCurrentOperator function and updates
//	the display with the results.

BOOL GetCurrentOperator(HWND hDlg)
{
	LINEOPERATOR CurrentOperator;
	if (lineGetCurrentOperator(g_hLine, &CurrentOperator)) {
		return FALSE;
	}
	SetDlgItemText(hDlg, IDC_EXTAPIA_CUROP, CurrentOperator.lpszLongName);

	return TRUE;
}

// ***************************************************************************
// Function Name: GetAvailableOperators
// 
// Purpose: Get the available operators and update the dialog display
//
// Arguments:
//	hDlg - the dialog containing the IDC_EXTAPIA_CUROP control
//
// Return Values:
//	TRUE if successful, FALSE otherwise
//
// Side Effects:
//	Updates the text in the listbox with HWND g_hwndOpList
//	Allocates memory to copy the operator strings
//
// Description:
//	This function simply calls the lineGetOperatorStatus function and updates
//	the display with the results.  If there are more operators than can fit in pbInit
//	it also temporarily allocates memory.

BOOL GetAvailableOperators(HWND hDlg)
{
	// set up the initial mega data structure
	BYTE pbInit[REASONABLE_BUFFER];
	LPLINEOPERATORSTATUS plosOperatorStatus = (LPLINEOPERATORSTATUS)pbInit;
	LPBYTE pLineOperatorStatusBytes = NULL;
	LPTSTR lpszItemData;
	DWORD dwNeededSize;
	int iResult;

	plosOperatorStatus->dwTotalSize = REASONABLE_BUFFER;
	if (lineGetOperatorStatus(g_hLine, plosOperatorStatus)) {
		return FALSE;
	}

	// check to see if our buffer was large enough
	if (plosOperatorStatus->dwNeededSize >= plosOperatorStatus->dwTotalSize) {
		// allocate a byte array and cast it to a LPLINEOPERATORSTATUS
		dwNeededSize = plosOperatorStatus->dwNeededSize;
		pLineOperatorStatusBytes = new BYTE[dwNeededSize];
		if (!pLineOperatorStatusBytes) {
			return FALSE;
		}
		plosOperatorStatus = (LPLINEOPERATORSTATUS)pLineOperatorStatusBytes;
		
		// call lGOS again to fill the new structure
		plosOperatorStatus->dwTotalSize = dwNeededSize;
		if (lineGetOperatorStatus(g_hLine, plosOperatorStatus)) {
			delete[] pLineOperatorStatusBytes;
			return FALSE;
		}
	}

	// set the pointer to the first available operator and iterate
	LPLINEOPERATOR ploOperator;
	DWORD dwOperatorNumber;
	ploOperator = (LPLINEOPERATOR)((LPBYTE)plosOperatorStatus+(plosOperatorStatus->dwAvailableOffset));
	for(dwOperatorNumber = 0; 
		dwOperatorNumber < plosOperatorStatus->dwAvailableCount; 
		dwOperatorNumber++) {
		// add the element to the listbox
		iResult = SendMessage(g_hwndOpList, LB_ADDSTRING, 0, (LPARAM) ploOperator->lpszLongName);

		// copy the lpszNumName and store the pointer as ItemData
		if (iResult >= LB_OKAY) {
			lpszItemData = _tcsdup(ploOperator->lpszNumName);
			if (!lpszItemData) {
				delete[] pLineOperatorStatusBytes;
				return FALSE;
			}
			SendMessage(g_hwndOpList, LB_SETITEMDATA, iResult, (LPARAM) lpszItemData);
		} else {
			delete[] pLineOperatorStatusBytes;
			return FALSE;
		}

		// increment the pointer
		ploOperator++;
	}

	// cleanup
	delete[] pLineOperatorStatusBytes;
	return TRUE;
}

// ***************************************************************************
// Function Name: RegisterNewOperator
// 
// Purpose: call lineRegister on the currently selected operator
//
// Arguments: none
//
// Return Values: none
//
// Description:
//	This function simply takes the currently selected member of g_hwndOpList and
//	tries to register it as a new operator.  lineRegister is asynchronous, so the
//	result of this call is posted to TAPIProc.

void RegisterNewOperator()
{
	LPTSTR lpszNumName;
	int iCurSel, iResult;

	iCurSel = SendMessage(g_hwndOpList, LB_GETCURSEL, 0, 0);
	if (iCurSel != LB_ERR) {
		// get the provider name
		lpszNumName = (LPTSTR) SendMessage(g_hwndOpList, LB_GETITEMDATA, 
										   (WPARAM) iCurSel, (LPARAM) 0);

		// now try to set the current provider
		// normally we would store this ID and verify it in TAPIProc, but since we are
		// only making one asynchronous request, we ignore this value...
		iResult = lineRegister(g_hLine, LINEREGMODE_MANUAL, 
							   lpszNumName, LINEOPFORMAT_NUMERIC);
	} else {
		MessageBox(NULL, TEXT("Unable to get current selection"),
				   TEXT("Error!!!"), MB_OK | MB_ICONERROR);
	}

}

// ***************************************************************************
// Function Name: CleanupLB
// 
// Purpose: free the strings pointed to by a listbox's itemdata
//
// Arguments: none
//
// Return Values: none
//
// Description:
//	This function simply iterates through the members of a listbox, gets their
//	item data values, which should be pointers to strings, and frees them.

void CleanupLB()
{
	int iResult;
	LPTSTR lpszNumName;
	
	// get the number of items in the listbox
	iResult = SendMessage(g_hwndOpList, LB_GETCOUNT, 0, 0);
	if (iResult != LB_ERR) {
		for (int i = 0; i < iResult; i++) {
			lpszNumName = (LPTSTR) SendMessage(g_hwndOpList, LB_GETITEMDATA, (WPARAM) i, (LPARAM) 0);
			free(lpszNumName);
		}
	}
}