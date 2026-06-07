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

///////////////////////////////////////////////////////////////////////////////
//
// CMTime.CPP
//
// Connects to a time server using connection manager
//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock.h>
#include <connmgr.h>
#include <winuserm.h>
#include <commctrl.h>
#include <aygshell.h>
#include "resource.h"

#define ARRAY_LENGTH(x)	(sizeof(x)/sizeof((x)[0]))

// some constants
#define HIGHTIME		21968699 // 21968708 // Jan 1, 1900 FILETIME.highTime
#define LOWTIME			4259332096 // 1604626432 // Jan 1, 1900 FILETIME.lowtime
#define EINITFAILED		(-1)

// global variables
HINSTANCE	g_hInst;
LPCTSTR		g_lpctszTitle;
/* *************************************************************************** */
// IP address of "time-a.timefreq.bldrdoc.gov", replace with IP of server running time server. (RFC-868)
// If using the timeserver.exe application supplied in the SDK, set this to the IP address 
// of the computer running timeserver.exe
// Note: Accessing time servers on the Internet requires that Port 37 be opened on you router
//       or you may need to run special client software depending on your network configuration.
//       Talk to your network administrator or help desk for more information
in_addr g_in_addr = { (unsigned char)132,
                      (unsigned char)163,
                      (unsigned char)4,
                      (unsigned char)102 };
/* *************************************************************************** */
typedef struct
{
	HWND		hwndNetwork;	//Network spinner
	HANDLE		hConnection;	//Connection handle
	UINT		WM_CMEVENT;		//Registered Window Message

} SConnection;



static void DestroyConnection(
	SConnection *lpConnection
	)
{
	// If a connection exists, destroy it
	if(NULL != lpConnection->hConnection)
	{
		ConnMgrReleaseConnection(lpConnection->hConnection, FALSE);
		lpConnection->hConnection = NULL;
	}
}


static HRESULT EstablishConnection(
	HWND hDlg, 
	SConnection *lpConnection
	)
{
	int iNetwork;
    HRESULT hResult = E_FAIL;

	// cleanup the old connection
	DestroyConnection(lpConnection);	

	// get the right network to connect to
	iNetwork = SendMessage(lpConnection->hwndNetwork, LB_GETCURSEL, 0, 0);
	if(LB_ERR != iNetwork)
	{
	    CONNMGR_DESTINATION_INFO DestInfo;

		hResult = ConnMgrEnumDestinations(iNetwork, &DestInfo);
		if(SUCCEEDED(hResult))
		{
			// actually try to establish the connection
			CONNMGR_CONNECTIONINFO ConnInfo;
    
			ZeroMemory(&ConnInfo, sizeof(ConnInfo));
			ConnInfo.cbSize = sizeof(ConnInfo);
			ConnInfo.dwParams = CONNMGR_PARAM_GUIDDESTNET;
			ConnInfo.dwPriority = CONNMGR_PRIORITY_USERBACKGROUND;
			ConnInfo.guidDestNet = DestInfo.guid;
			ConnInfo.hWnd = hDlg;
			ConnInfo.uMsg = lpConnection->WM_CMEVENT;

			hResult = ConnMgrEstablishConnection(&ConnInfo, &lpConnection->hConnection);

			// check to see if the attempt failed
			if(FAILED(hResult))
			{
				TCHAR tszBuffer[256];

				FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
									(LPCTSTR)LoadString(g_hInst, IDS_CONNMGR_ESTABLISH_FAILED, 0, 0),
									0,
									0,
									tszBuffer,
									ARRAY_LENGTH(tszBuffer),
									(va_list*)&hResult);

				MessageBox(NULL, tszBuffer, g_lpctszTitle, MB_OK);
			}
		}
	}

    return hResult;
}


static BOOL GetTimeFromServer(
	DWORD *lpdwTime
	)
{
	*lpdwTime = 0;
	BOOL bReturn= FALSE;

	// set up a TCP socket
	SOCKET sSock = socket(AF_INET, SOCK_STREAM, 0);
	if(INVALID_SOCKET != sSock)
	{
		struct sockaddr_in sin;

		// set up a sockaddr for the destination address
		memcpy(&sin.sin_addr, &g_in_addr, sizeof(sin.sin_addr));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(IPPORT_TIMESERVER);

		// try to connect
		if(0 == connect(sSock, (struct sockaddr *) &sin, sizeof(struct sockaddr_in)))
		{
			int iResult, iRead;

			// Read 4 bytes from the time server
			for(iRead = 0; iRead < 4; iRead += iResult)
			{
				iResult = recv(sSock, (char*)lpdwTime + iRead, 4 - iRead, 0);
				if(iResult < 1)
					break;
			}

			if(4 == iRead)
			{
				// swap the bytes round from Network to Host order
				*lpdwTime = ntohl(*lpdwTime);

				bReturn = TRUE;
			}
		}

		closesocket(sSock);
	}

	return bReturn;
}


static BOOL UpdateSysTime(
	DWORD dwTime
	)
{
	UINT64 uiCurTime, uiBaseTime, uiResult;
	SYSTEMTIME st;

	// January 1, 1900
	uiBaseTime = ((UINT64) HIGHTIME << 32) + LOWTIME;

	// convert dwTime to 100 nanosecond intervals
	uiCurTime = (UINT64)dwTime * (UINT64)10000000;
	uiResult = uiBaseTime + uiCurTime;

	FileTimeToSystemTime((LPFILETIME)&uiResult, &st);
	return SetSystemTime(&st);
}



static BOOL InitDialog(
	const HWND hDlg, 
	UINT nToolBarId
	)
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
	mbi.hInstRes = g_hInst;

	// If we could not initialize the dialog box, return an error
	if(FALSE == (SHInitDialog(&shidi) && SHCreateMenuBar(&mbi)))
	{
		return FALSE;
	}

	// set the title bar
	VERIFY(SetWindowText(hDlg, g_lpctszTitle));

	// In order to make Back work properly, it's necessary to 
	// override it and then call the appropriate SH API
	(void)SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
					  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
								 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;
}


static BOOL CALLBACK DialogProc(
	const HWND hDlg, 
	const UINT uiMessage,
	const WPARAM wParam, 
	const LPARAM lParam)
{
	BOOL bProcessedMsg = TRUE;
	SConnection *lpConnection = (SConnection*)GetWindowLong(hDlg, DWL_USER);

	switch(uiMessage)
	{
		case WM_INITDIALOG:
			{
				int iResult, i;
				WSADATA wsaData;
				CONNMGR_DESTINATION_INFO DestInfo;

				SetWindowLong(hDlg, DWL_USER, lParam);
				lpConnection = (SConnection*)lParam;

				// make the dialog full screen and init the menubar
				if(FALSE == InitDialog(hDlg, IDR_CMTIME_MENUBAR))
				{
					EndDialog(hDlg, EINITFAILED);
					return TRUE;
				}

				// create a message to use for CM events
				if(!(lpConnection->WM_CMEVENT = RegisterWindowMessage(TEXT("CM Event"))))
				{
					EndDialog(hDlg, EINITFAILED);
					return TRUE;
				}

				// Init network ID control
				VERIFY(lpConnection->hwndNetwork = GetDlgItem(hDlg, IDC_CMTIME_NETWORK));
				for(i = 0; SUCCEEDED(ConnMgrEnumDestinations(i, &DestInfo)); i++)
				{
					iResult = SendMessage(lpConnection->hwndNetwork, LB_INSERTSTRING, i, (LPARAM)DestInfo.szDescription);
					if(LB_ERR == iResult)
					{
						EndDialog(hDlg, EINITFAILED);
						return TRUE;
					}
				}
				
				// select the first element of the network control
				SendMessage(lpConnection->hwndNetwork, LB_SETCURSEL, 0, 0);

				// initialize Winsock
				iResult = WSAStartup(MAKEWORD(1, 1), &wsaData);
				if (iResult)
				{
					EndDialog(hDlg, EINITFAILED);
					return TRUE;
				}
			}
			break;

		case WM_COMMAND:
			switch (wParam)
			{			
				case IDM_CMTIME_QUIT:
					EndDialog(hDlg, 0);
					break;

				case IDM_CMTIME_CONNECT:
					SetDlgItemText(hDlg, IDC_CMTIME_TSTATUS, NULL);
					SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_FINDING_CONNECTION, 0, 0));

					if(FAILED(EstablishConnection(hDlg, lpConnection)))
					{
						SendMessage(hDlg, lpConnection->WM_CMEVENT, CONNMGR_STATUS_CONNECTIONFAILED, 0);
					}
					break;

				default:
					bProcessedMsg = FALSE;
					break;
			}

		default:
			bProcessedMsg = FALSE;

			// check for messages from connection manager
			if(lpConnection && uiMessage == lpConnection->WM_CMEVENT)
			{
 				bProcessedMsg = TRUE;

				switch(wParam)
				{
					case CONNMGR_STATUS_DISCONNECTED:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_DISCONNECTED, 0, 0));
						break;

					case CONNMGR_STATUS_WAITINGCONNECTION:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_WAITING_CONNECTION, 0, 0));
						break;

					case CONNMGR_STATUS_WAITINGCONNECTIONABORT:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_WAITING_CONNECTION_ABORT, 0, 0));
						break;

					case CONNMGR_STATUS_WAITINGDISCONNECTION:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_WAITING_DISCONNECTION, 0, 0));
						break;

					case CONNMGR_STATUS_CONNECTED:
						{
							DWORD dwTime;
							UINT uFailMsg = IDS_ERROR_GETTING_TIME;

							SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_CONNECTED, 0, 0));

							// Now that we have a connection, get the time from the server
							if (GetTimeFromServer(&dwTime))
							{
								// And set the time we received
								if (UpdateSysTime(dwTime))
								{
									SetDlgItemText(hDlg, IDC_CMTIME_TSTATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_CLOCK_SET, 0, 0));
									return TRUE;
								}
								
								uFailMsg = IDS_ERROR_SETTING_CLOCK;
							}

							SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, uFailMsg, 0, 0));
						}
						break;

					case CONNMGR_STATUS_CONNECTIONFAILED:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_CONNECTION_FAILED, 0, 0));
						DestroyConnection(lpConnection);
						break;

					case CONNMGR_STATUS_NOPATHTODESTINATION:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_NOPATH, 0, 0));
						DestroyConnection(lpConnection);
						break;

					case CONNMGR_STATUS_CONNECTIONCANCELED:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_CONNECTION_CANCELED, 0, 0));
						DestroyConnection(lpConnection);
						break;

					default:
						SetDlgItemText(hDlg, IDC_CMTIME_STATUS, (LPCTSTR)LoadString(g_hInst, IDS_STATE_UNKNOWN_STATUS, 0, 0));
						if(wParam & CONNMGR_STATUS_DISCONNECTED)
						{
							DestroyConnection(lpConnection);
						}

						break;
				}
			}

			break;
	}

	return bProcessedMsg;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pszCmdLine, int nCmdShow)
{
	// load in program name
	g_lpctszTitle = (LPCTSTR)LoadString(hInstance, IDS_CMTIME_TITLE, NULL, 0);
	
	// Use a globally named mutex to detect another instance of HelloSMS
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_CMTIME_EXE_MUTEX_"));

    // check the result code
	if (NULL != hMutex)
	{
        // First instance running?  Okay to proceed...
		if(ERROR_ALREADY_EXISTS != GetLastError())
		{
			int iResult;
			SConnection c;

			g_hInst = hInstance;
			InitCommonControls();

			iResult = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DialogProc, (LONG)&c);
			if(EINITFAILED == iResult)
			{
				MessageBox(NULL,
						(LPCTSTR)LoadString(g_hInst, IDS_ERROR_DIALOGINIT, 0, 0),
						(LPCTSTR)LoadString(g_hInst, IDS_ERROR_CAPTION, 0, 0),
						MB_OK | MB_ICONERROR);
			}

			// cleanup
			DestroyConnection(&c);
		}
        else
		{
            // Already an instance running - attempt to switch to it and then exit
            const HWND hWndExistingInstance = FindWindow(TEXT("Dialog"), g_lpctszTitle);
			VERIFY((0 == hWndExistingInstance) || SetForegroundWindow((HWND) (((ULONG) hWndExistingInstance) | 0x01)));
        }

        VERIFY(CloseHandle(hMutex));
    }

    return TRUE;
}
