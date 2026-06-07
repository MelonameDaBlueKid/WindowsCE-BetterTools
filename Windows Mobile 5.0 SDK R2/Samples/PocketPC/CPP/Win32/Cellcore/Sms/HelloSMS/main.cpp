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

// ***************************************************************************
// MAIN.CPP
//
// Simple SMS Message Sender
//
//

#include "interface.h"
#include "resource.h"


// Useful macros
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))


// Result codes for termination of our dialog
enum EDialogResult
{
	eDialogResult_None = 0,				// no error. Just don't send the SMS
	eDialogResult_SendSMS = 1,			// Send the SMS
	eDialogResult_ErrorNoMem = -1,		// Out of memory
	eDialogResult_ErrorGeneral = -2		// Another error occurred
};


// globals variable declarations
HINSTANCE		ghInstance;
WNDPROC			gfMsgProc;
LPTSTR			gpszRecipient = NULL;
LPTSTR			gpszServer = NULL;
LPTSTR			gpszMessage = NULL;
HWND			ghDefault;
HWND			ghConfirmation;
HWND			ghServer;
HWND			ghMessage;
BOOL			gbUseDefault;
BOOL			gbSendConfirmation;

// function declarations
BOOL CALLBACK DialogProc(const HWND hDlg, const UINT uiMessage, const WPARAM wParam, const LPARAM lParam);
LRESULT CALLBACK EditBoxSubProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SendSMS(BOOL bSendConfirmation, BOOL bUseDefaultSMSC, LPCTSTR lpszSMSC, LPCTSTR lpszRecipient, LPCTSTR lpszMessage);


static EDialogResult lGetText(HWND hDlg, int nIDDlgItem, TCHAR **lplpszDlgText)
{
	HWND hText;
	TCHAR *lpszText;
	int iText;
	EDialogResult eReturn = eDialogResult_ErrorNoMem;

	ASSERT(lplpszDlgText);
	*lplpszDlgText = 0;

	VERIFY(hText = GetDlgItem(hDlg, nIDDlgItem));

	iText = GetWindowTextLength(hText);
	lpszText = (LPTSTR)malloc((iText + 1) * sizeof(TCHAR));
	if(lpszText)
	{
		lpszText[0] = 0;

		if(!iText || GetDlgItemText(hDlg, nIDDlgItem, lpszText, iText + 1))
		{
			*lplpszDlgText = lpszText;
			return eDialogResult_None;
		}

		free(lpszText);

		eReturn = eDialogResult_ErrorGeneral;
	}

	return eReturn;
}



// ***************************************************************************
// Function Name: WinMain
//
// Purpose: Main entry point into the HelloSMS program
//
// Arguments: Standard WinMain arguments
//
// Return Values: 0
//
// Side Effects:
//	When finished sending the message, it frees all the global strings
//
// Description:
//	Our WinMain function checks to see if a previous instance of the program is
//  running, and if it is not, it pops up a dialog box allowing a user to enter
//  information about the SMS message they would like to send.

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
    // Use a globally named mutex to detect another instance of HelloSMS
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_HELLOSMS_EXE_MUTEX_"));

    // check the result code
	if(hMutex)
	{
        // First instance running?  Okay to proceed...
		if(ERROR_ALREADY_EXISTS != GetLastError())
		{
			int iResult;

			// store the hInstance
			ghInstance = hInstance;

			// create the dialog box
			iResult = DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DialogProc);

			switch(iResult)
			{
			// send the message
			case eDialogResult_SendSMS:
				SendSMS(gbSendConfirmation, gbUseDefault, gpszServer, gpszRecipient, gpszMessage);
				free(gpszRecipient);
				free(gpszServer);
				free(gpszMessage);
				break;

			case eDialogResult_ErrorNoMem:
				MessageBox(NULL, 
					(LPCTSTR)LoadString(hInstance, IDS_ERROR_NOMEM, 0, 0),
					(LPCTSTR)LoadString(hInstance, IDS_CAPTION_ERROR, 0, 0),
					MB_OK | MB_ICONERROR);
				break;
			}
        }
        else
		{
            // Already an instance running - attempt to switch to it and then exit
            const HWND hWndExistingInstance = FindWindow(TEXT("Dialog"), TEXT("HelloSMS"));
			VERIFY((0 == hWndExistingInstance) || SetForegroundWindow((HWND)((ULONG)hWndExistingInstance | 0x01)));
        }
        
		VERIFY(CloseHandle(hMutex));
    }

	return 0;
}

// ***************************************************************************
// Function Name: DialogProc
// 
// Purpose: Message Handler for HelloSMS Dialog Box
//
// Arguments: Standard Dialog Procedure Arguments
//
// Return Values:
//	Returns a number between -1 and 1, inclusive, indicating the following:
//	   -1	An error occurred while initializing the Dialog
//		0	Cancel was pressed
//		1	Send the message
//
// Side Effects:
//	Mallocs and sets all the global strings to the values in the edit boxes.
//	Subclasses the WndProc for the Message Edit Box
//	
// Description:
//	Dialog Procedure for the main HelloSMS Dialog.  Accepts a message destination,
//	an alternate SMS server, requests send confirmation, and allows the user to 
//	enter the SMS message itself.

BOOL CALLBACK DialogProc(const HWND hDlg, const UINT uiMessage, 
						 const WPARAM wParam, const LPARAM lParam)
{
	BOOL	bProcessedMsg = TRUE;
	int		iCheck;
	EDialogResult eResult;
	
	switch(uiMessage)
	{
		case WM_INITDIALOG:
			// make sure the dialog box was created
			if(InitDialog(hDlg))
			{
				HWND hMsgDlg;

				// subclass the edit box
				VERIFY(hMsgDlg = GetDlgItem(hDlg, IDC_MESSAGE));
				if(gfMsgProc = (WNDPROC)GetWindowLong(hMsgDlg, GWL_WNDPROC))
				{
					if(SetWindowLong(hMsgDlg, GWL_WNDPROC, (LONG)EditBoxSubProc))
					{
						// successful
						break;
					}
				}
			}

			// return an error
			EndDialog(hDlg, eDialogResult_ErrorGeneral);
			break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDM_HELLOSMS_SEND:
					eResult = lGetText(hDlg, IDC_RECIPIENT, &gpszRecipient);
					if(eDialogResult_None == eResult)
					{
						eResult = lGetText(hDlg, IDC_SERVER, &gpszServer);
						if(eDialogResult_None == eResult)
						{
							eResult = lGetText(hDlg, IDC_MESSAGE, &gpszMessage);
							if(eDialogResult_None == eResult)
							{
								EndDialog(hDlg, eDialogResult_SendSMS);
								break;
							}

							free(gpszServer);
							gpszServer = 0;
						}

						free(gpszRecipient);
						gpszRecipient = 0;
					}

					EndDialog(hDlg, eResult);
					break;

				case IDM_HELLOSMS_CANCEL:
					// do nothing
					EndDialog(hDlg, eDialogResult_None);
					break;

				case IDC_DEFAULT:
					iCheck = (int)SendMessage(ghDefault, BM_GETCHECK, 0, 0);
					
					// if it was checked, uncheck it and enable IDC_SERVER
					if(iCheck)
					{
						SendMessage(ghDefault, BM_SETCHECK, BST_UNCHECKED, 0);
						EnableWindow(ghServer, TRUE);
						gbUseDefault = FALSE;
					}
					else
					{
						SendMessage(ghDefault, BM_SETCHECK, BST_CHECKED, 0);
						EnableWindow(ghServer, FALSE);
						gbUseDefault = TRUE;
					}

					break;

				case IDC_CONFIRMATION:
					iCheck = (int)SendMessage(ghConfirmation, BM_GETCHECK, 0, 0);
					
					// if it was checked, uncheck it and update the global var
					if(iCheck)
					{
						SendMessage(ghConfirmation, BM_SETCHECK, BST_UNCHECKED, 0);
						gbSendConfirmation = FALSE;
					}
					else
					{
						SendMessage(ghConfirmation, BM_SETCHECK, BST_CHECKED, 0);
						gbSendConfirmation = TRUE;
					}

					break;
				
				case IDC_MESSAGE:
					if(EN_CHANGE == HIWORD(wParam))
					{
						int iMsgLen;
						TCHAR szMsg[10];

						// update the character count
						iMsgLen = GetWindowTextLength(ghMessage);
						_sntprintf(szMsg, ARRAY_LENGTH(szMsg), TEXT("%d"), iMsgLen);

						VERIFY(SetDlgItemText(hDlg, IDC_LBLCOUNT, szMsg));
					}

					break;
			}

        case WM_HOTKEY:
            // The following is necessary to get the appropriate Back key behavior 
			// (handle on key-up as per recommendations)
            if((VK_TBACK == HIWORD(lParam)) && (0 != (MOD_KEYUP & LOWORD(lParam))))
			{
                // BUGBUG - might have to change
				SHNavigateBack();
            }
            break;

		default:
			// nothing was processed
			bProcessedMsg = FALSE;
			break;
	}

	return bProcessedMsg;
}

// ***************************************************************************
// Function Name: EditBoxSubProc
// 
// Purpose: Subclassed Message Handler for IDC_MESSAGE Edit Box
//
// Arguments: Standard Window Procedure Arguments
//
// Return Values:
//	The LRESULT for a normal message to the Edit Box, ANDed with ~DLGC_WANTMESSAGE
//	if the message is an up arrow and the cursor is on the first line.
//
// Side Effects:
//	Sends an up arrow command to the dialog box
//	
// Description:
//	Intercepts the message from the parent dialog box, asking if the edit control
//	wants to accept the message, and if the cursor is on the first line and the
//	up arrow has been pressed, it rejects the message.

LRESULT CALLBACK EditBoxSubProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult;
	
	switch(uMsg)
	{
		// this is the message that is sent to the Edit Box asking if the Edit Box
		// wants a particular message.  In the case of an up arrow on the top line,
		// we actually want the Edit Box to deny the message and send it back to
		// the dialog box.  This way, focus will return to the previous control.
		case WM_GETDLGCODE:
			// Get the default response
			lResult = CallWindowProc(gfMsgProc, hwnd, uMsg, wParam, lParam);

			if(lParam)
			{
				LPMSG pmsg = (LPMSG)lParam;

				if((pmsg->message == WM_KEYDOWN || pmsg->message == WM_KEYUP)
					&& (pmsg->wParam == VK_UP))
				{
					// If we are on the first line (line index == 0), deny the message
					if(!SendMessage(hwnd, EM_LINEINDEX, -1, 0))
					{
						lResult &= ~DLGC_WANTMESSAGE;
					}
				}
			}

			break;

		default:
			// respond to the messages with the default action
			lResult = CallWindowProc(gfMsgProc, hwnd, uMsg, wParam, lParam);
			break;
	}
	
	return lResult;
}

// ***************************************************************************
// Function Name: SendSMS
// 
// Purpose: Send an SMS Message
//
// Arguments: none
//
// Return Values: none
//
// Description:
//	Called after everything has been set up, this function merely opens an
//	SMS_HANDLE and tries to send the SMS Message.
 
void SendSMS(BOOL bSendConfirmation, BOOL bUseDefaultSMSC, LPCTSTR lpszSMSC, LPCTSTR lpszRecipient, LPCTSTR lpszMessage)
{
	SMS_HANDLE smshHandle;
	SMS_ADDRESS smsaSource;
	SMS_ADDRESS smsaDestination;
	TEXT_PROVIDER_SPECIFIC_DATA tpsd;
	SMS_MESSAGE_ID smsmidMessageID;

	// try to open an SMS Handle
	if(FAILED(SmsOpen(SMS_MSGTYPE_TEXT, SMS_MODE_SEND, &smshHandle, NULL)))
	{
		MessageBox(NULL,
					(LPCTSTR)LoadString(ghInstance, IDS_ERROR_SMSOPEN, 0, 0), 
					(LPCTSTR)LoadString(ghInstance, IDS_CAPTION_ERROR, 0, 0),
					MB_OK | MB_ICONERROR);
		return;
	}

	// Create the source address
	if(!bUseDefaultSMSC)
	{
		smsaSource.smsatAddressType = SMSAT_INTERNATIONAL;
		_tcsncpy(smsaSource.ptsAddress, lpszSMSC, SMS_MAX_ADDRESS_LENGTH);
	}

	// Create the destination address
	smsaDestination.smsatAddressType = SMSAT_INTERNATIONAL;
	_tcsncpy(smsaDestination.ptsAddress, lpszRecipient, SMS_MAX_ADDRESS_LENGTH);

	// Set up provider specific data
    memset(&tpsd, 0, sizeof(tpsd));
	tpsd.dwMessageOptions = bSendConfirmation ? PS_MESSAGE_OPTION_STATUSREPORT : PS_MESSAGE_OPTION_NONE;
	tpsd.psMessageClass = PS_MESSAGE_CLASS1;
	tpsd.psReplaceOption = PSRO_NONE;
	tpsd.dwHeaderDataSize = 0;

	// Send the message, indicating success or failure
	if(SUCCEEDED(SmsSendMessage(smshHandle, ((bUseDefaultSMSC) ? NULL : &smsaSource), 
								 &smsaDestination, NULL, (PBYTE) lpszMessage, 
								 _tcslen(lpszMessage) * sizeof(TCHAR), (PBYTE) &tpsd, 
								 sizeof(TEXT_PROVIDER_SPECIFIC_DATA), SMSDE_OPTIMAL, 
								 SMS_OPTION_DELIVERY_NONE, &smsmidMessageID)))
	{
		MessageBox(NULL,
					(LPCTSTR)LoadString(ghInstance, IDS_SMSSENT, 0, 0), 
					(LPCTSTR)LoadString(ghInstance, IDS_CAPTION_SUCCESS, 0, 0),
					MB_OK);
	}
	else
	{
		MessageBox(NULL,
					(LPCTSTR)LoadString(ghInstance, IDS_ERROR_SMSSEND, 0, 0), 
					(LPCTSTR)LoadString(ghInstance, IDS_CAPTION_ERROR, 0, 0),
					MB_OK | MB_ICONERROR);
	}

	// clean up
	VERIFY(SUCCEEDED(SmsClose(smshHandle)));
}

