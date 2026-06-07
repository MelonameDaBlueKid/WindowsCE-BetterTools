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
#include <windows.h>
#include <aygshell.h>
#include <tpcshell.h>

#include "resource.h"

#define MSMQ_IO_FILE L"\\temp\\msmqadmio.txt"
#define MSMQ_STREAM_LEN	(4 * _MAX_PATH)
#define WRAPPER_SZ		50

#define GUID_ELEMENTS(p) \
    p->Data1,                 p->Data2,    p->Data3,\
    p->Data4[0], p->Data4[1], p->Data4[2], p->Data4[3],\
    p->Data4[4], p->Data4[5], p->Data4[6], p->Data4[7]

#define GUID_FORMAT     L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"
#define GUID_STR_LENGTH (8 + 1 + 4 + 1 + 4 + 1 + 4 + 1 + 12)

#define EOL	L"\r\n"

#define CONTROL_HEIGHT  20
#define WINDOW_BORDER   4
#define SPINNER_WIDTH   10

HWND g_hWnd = NULL;
HINSTANCE g_hInst = NULL;

static void DeliverOutput (WCHAR *szFile) {
	HWND hWnd = GetDlgItem (g_hWnd, IDC_RESULTS);

	SendMessage (hWnd, WM_SETTEXT, 0, (LPARAM)L"");

	HANDLE hFile = CreateFile (szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	char szBufferMB[MSMQ_STREAM_LEN];
	DWORD dwLen = 0;

	if ((! ReadFile (hFile, szBufferMB, sizeof(szBufferMB) - 1, &dwLen, NULL)) || (dwLen == 0)) {
		CloseHandle (hFile);

		return;
	}

	CloseHandle (hFile);

	szBufferMB[dwLen] = '\0';

	char szBufferMB2[MSMQ_STREAM_LEN + 2];
	char *p1 = szBufferMB;
	char *p2 = szBufferMB2;

	for ( ; ; ) {
		if (p2 >= &szBufferMB2[MSMQ_STREAM_LEN])
			break;

		if (*p1 == '\0')
			break;

		if (*p1 == '\n')
			*p2++ = '\r';

		*p2++ = *p1++;
	}

	*p2 = '\0';

	WCHAR szBuffer[MSMQ_STREAM_LEN];
	if (MultiByteToWideChar (CP_ACP, 0, szBufferMB2, -1, szBuffer, 2 * _MAX_PATH))
		SendMessage (hWnd, WM_SETTEXT, 0, (LPARAM)szBuffer);
}

static void RunCommand (WCHAR *szCommand) {
	WCHAR szBuffer[_MAX_PATH + 2];
	wcscpy (szBuffer, L"-f " MSMQ_IO_FILE L" ");
	WCHAR *p = wcschr (szBuffer, L'\0');
	wcsncpy (p, szCommand, _MAX_PATH - (p - szBuffer));

	PROCESS_INFORMATION pi;

#if defined (UNDER_CE)
	if (! CreateProcess (L"msmqadm.exe", szBuffer, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &pi)) {
#else
	STARTUPINFO si;
	memset (&si, 0, sizeof(si));
	si.cb = sizeof(si);
	if (! CreateProcess (L"msmqadm.exe", szBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
#endif
		SendMessage (GetDlgItem (g_hWnd, IDC_RESULTS), WM_SETTEXT, 0, (LPARAM)L"MSMQ not present.");
	} else {
		if (WaitForSingleObject (pi.hProcess, 5000) != WAIT_OBJECT_0)
			Sleep (5000);

		CloseHandle (pi.hProcess);
		CloseHandle (pi.hThread);
		SendMessage (GetDlgItem (g_hWnd, IDC_COMMAND), WM_SETTEXT, 0, (LPARAM)L"");
		DeliverOutput (MSMQ_IO_FILE);
	}
}

static int GetMyName (WCHAR *szName, DWORD cChars) {
	HKEY  hKey   = NULL;

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, TEXT("Ident"), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType = REG_SZ;
	DWORD dwSize = sizeof(WCHAR) * cChars;

	if ((RegQueryValueEx (hKey, TEXT("name"), 0, &dwType, (LPBYTE)szName, &dwSize) != ERROR_SUCCESS) ||
		(dwType != REG_SZ) || (dwSize > cChars * sizeof(WCHAR))) {
		RegCloseKey (hKey);
		return FALSE;
	}

	TCHAR szBuffer[16];
	dwSize = sizeof(szBuffer);
	if ((RegQueryValueEx (hKey, TEXT("origname"), 0, &dwType, (LPBYTE)szBuffer, &dwSize) != ERROR_SUCCESS) ||
		(dwType != REG_SZ) || (dwSize > sizeof(szBuffer))) {
		RegCloseKey (hKey);
		return FALSE;
	}

	RegCloseKey (hKey);

	return wcsicmp (szBuffer, szName);
}

static void Verify (void) {
	WCHAR szStream[MSMQ_STREAM_LEN];
	WCHAR *pStream = szStream;
	HKEY hk = NULL;

	WCHAR szBuffer[_MAX_PATH];
	if (GetMyName (szBuffer, _MAX_PATH)) {
		wcscpy (pStream, L"Computer name is ");
		wcscat (pStream, szBuffer);
		wcscat (pStream, EOL);
		pStream += wcslen (pStream);
	} else {
		wcscpy (pStream, L"Computer does NOT have a compatible name." EOL);
		pStream += wcslen (pStream);
	}

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, L"Drivers\\BuiltIn\\MSMQD", 0, KEY_READ, &hk) == ERROR_SUCCESS) {
		wcscpy (pStream, EOL L"MSMQ daemon installed." EOL);
		pStream += wcslen (pStream);
		RegCloseKey (hk);
	} else {
		wcscpy (pStream, EOL L"MSMQ daemon NOT installed." EOL);
		pStream += wcslen (pStream);
	}

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, L"Drivers\\BuiltIn\\NETREGD", 0, KEY_READ, &hk) == ERROR_SUCCESS) {
		wcscpy (pStream, EOL L"NETREG daemon installed." EOL);
		pStream += wcslen (pStream);
		RegCloseKey (hk);
	} else {
		wcscpy (pStream, EOL L"NETREG daemon NOT installed." EOL);
		pStream += wcslen (pStream);
	}

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\MSMQ\\SimpleClient", 0, KEY_READ, &hk) == ERROR_SUCCESS) {
		wcscpy (pStream, EOL L"MSMQ configured." EOL);
		pStream += wcslen (pStream);

		DWORD dw;
		DWORD dwSize, dwType;
		GUID  g;

		dwSize = sizeof(DWORD);
		HRESULT hr = RegQueryValueEx (hk, L"DefaultQuota", NULL, &dwType, (LPBYTE)&dw, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + WRAPPER_SZ < MSMQ_STREAM_LEN))
        {
			wsprintf (pStream, L"Default Quota: %d" EOL, dw);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(DWORD);
		hr = RegQueryValueEx (hk, L"Port", NULL, &dwType, (LPBYTE)&dw, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Port: %d" EOL, dw);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(DWORD);
		hr = RegQueryValueEx (hk, L"PingPort", NULL, &dwType, (LPBYTE)&dw, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Ping Port: %d" EOL, dw);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(DWORD);
		hr = RegQueryValueEx (hk, L"PingTimeout", NULL, &dwType, (LPBYTE)&dw, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Ping Timeout: %d" EOL, dw);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(DWORD);
		hr = RegQueryValueEx (hk, L"FSMaxTimeout", NULL, &dwType, (LPBYTE)&dw, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"FS Startup Timeout: %d" EOL, dw);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(DWORD);
		hr = RegQueryValueEx (hk, L"LanRetrySchedule", NULL, &dwType, (LPBYTE)&dw, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Lan Retry Timeout: %d" EOL, dw);
			pStream += wcslen (pStream);
		}

		unsigned short		asRetrySchedule[200];
		unsigned int		uiRetrySchedule = 0;

		dwSize = sizeof(asRetrySchedule);
		hr = RegQueryValueEx (hk, L"RetrySchedule", NULL, &dwType, (LPBYTE)asRetrySchedule, &dwSize);
		if ((hr == ERROR_SUCCESS) && (dwSize <= sizeof(asRetrySchedule)) && (dwSize > 0) && 
            ((dwSize & 1) == 0) && (dwType == REG_BINARY)) 
        {
			uiRetrySchedule = dwSize / sizeof(short);
        }

		if (uiRetrySchedule && (pStream - szStream + GUID_STR_LENGTH + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Retry schedule: ");
			pStream += wcslen (pStream);
			for (int i = 0 ; i < (int)uiRetrySchedule ; ++i) 
            {
				if (pStream - szStream + GUID_STR_LENGTH + WRAPPER_SZ < MSMQ_STREAM_LEN) 
                {
					wsprintf (pStream, L"%d ", asRetrySchedule[i]);
					pStream += wcslen (pStream);
				}
			}
			wcscat (pStream, EOL);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(g);
		hr = RegQueryValueEx (hk, L"QueueManagerGUID", NULL, &dwType, (LPBYTE)&g, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + GUID_STR_LENGTH + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"QM GUID: " GUID_FORMAT EOL, GUID_ELEMENTS((&g)));
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(szBuffer);
		hr = RegQueryValueEx (hk, L"OutFRSQueue", NULL, &dwType, (LPBYTE)szBuffer, &dwSize);
		if ((hr == ERROR_SUCCESS) && (wcslen (szBuffer) + (pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"OutFRS queue: %s" EOL, szBuffer);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(szBuffer);
		hr = RegQueryValueEx (hk, L"DebugQueue", NULL, &dwType, (LPBYTE)szBuffer, &dwSize);
		if ((hr == ERROR_SUCCESS) && (wcslen (szBuffer) + (pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN)) {
			wsprintf (pStream, L"Debug queue: %s" EOL, szBuffer);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(szBuffer);
		hr = RegQueryValueEx (hk, L"HostName", NULL, &dwType, (LPBYTE)szBuffer, &dwSize);
		if ((hr == ERROR_SUCCESS) && (wcslen (szBuffer) + (pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Host override: %s" EOL, szBuffer);
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(szBuffer);
		hr = RegQueryValueEx (hk, L"CETrackNetwork", NULL, &dwType, (LPBYTE)szBuffer, &dwSize);
		if ((hr == ERROR_SUCCESS) && ((pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Network tracking: %s" EOL, (szBuffer[0] == L'y' || szBuffer[0] == L'Y') ? L"enabled" : L"disabled");
			pStream += wcslen (pStream);
		}

		dwSize = sizeof(DWORD);
		hr = RegQueryValueEx (hk, L"CEStartAtBoot", NULL, &dwType, (LPBYTE)&dw, &dwSize);
		if ((hr == ERROR_SUCCESS) && (pStream - szStream + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Start At Boot: %s" EOL, dw ? L"yes" : L"no");
			pStream += wcslen (pStream);
		}

		szBuffer[0] = L'\0';
		dwSize = sizeof(szBuffer);
		hr = RegQueryValueEx (hk, L"BaseDir", NULL, &dwType, (LPBYTE)szBuffer, &dwSize);
		if ((hr == ERROR_SUCCESS) && (wcslen (szBuffer) + (pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			wsprintf (pStream, L"Base Dir: %s" EOL, szBuffer);
			pStream += wcslen (pStream);
		}

		RegCloseKey (hk);

		if (szBuffer[0] && ((pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN)) 
        {
			DWORD dwAttribs = GetFileAttributes (szBuffer);
			if ((dwAttribs != 0xffffffff) && (dwAttribs & FILE_ATTRIBUTE_DIRECTORY)) 
            {
				wsprintf (pStream, L"Base Dir exists. Contents:" EOL, szBuffer);
				pStream += wcslen (pStream);

				WIN32_FIND_DATA wfd;
				WCHAR *p = szBuffer + wcslen (szBuffer);
				wcscpy (p, L"\\*.*");
				++p;
				HANDLE hSearch = FindFirstFile (szBuffer, &wfd);
				if (hSearch != INVALID_HANDLE_VALUE) 
                {
					do 
                    {
						if ((wcslen (wfd.cFileName) < _MAX_PATH - 2) && (wcscmp (wfd.cFileName, L".") != 0) &&
							(wcscmp (wfd.cFileName, L"..") != 0)) 
                        {
							if (wcslen (wfd.cFileName) + (pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN) 
                            {
								wsprintf (pStream, L"    %s" EOL, wfd.cFileName);
								pStream += wcslen (pStream);
							}
						}
					} while (FindNextFile (hSearch, &wfd));
					FindClose (hSearch);
				}
			} 
            else 
            {
				wsprintf (pStream, L"Base Dir does not exist." EOL, szBuffer);
				pStream += wcslen (pStream);
			}
		}
	} 
    else 
    {
		wcscpy (pStream,  EOL L"MSMQ NOT configured." EOL);
		pStream += wcslen (pStream);
	}

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\netreg", 0, KEY_READ, &hk) == ERROR_SUCCESS) 
    {
		wcscpy (pStream, EOL L"NETREG configured." EOL);
		pStream += wcslen (pStream);

		DWORD dwType;
		DWORD dw;
		DWORD cb = sizeof(dw);

		if ((RegQueryValueEx (hk, L"Cycle", NULL, &dwType, (LPBYTE)&dw, &cb) == ERROR_SUCCESS) &&
			(dwType == REG_DWORD) && (cb == sizeof(dw))) 
        {
			if ((pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN) {
				wsprintf (pStream, L"Cycle duration: %d" EOL, dw);
				pStream += wcslen (pStream);
			}
		}

		if ((RegQueryValueEx (hk, L"EmulateNB", NULL, &dwType, (LPBYTE)&dw, &cb) == ERROR_SUCCESS) &&
			(dwType == REG_DWORD) && (cb == sizeof(dw))) 
        {
			if ((pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN) 
            {
				wsprintf (pStream, L"Emulate netBIOS: %s" EOL, dw ? L"yes" : L"no");
				pStream += wcslen (pStream);
			}
		}

		if ((RegQueryValueEx (hk, L"UseRedirector", NULL, &dwType, (LPBYTE)&dw, &cb) == ERROR_SUCCESS) &&
			(dwType == REG_DWORD) && (cb == sizeof(dw))) 
        {
			if ((pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN) 
            {
				wsprintf (pStream, L"Use Redirector's netBIOS: %s" EOL, dw ? L"yes" : L"no");
				pStream += wcslen (pStream);
			}
		}

		if ((RegQueryValueEx (hk, L"TrackNetwork", NULL, &dwType, (LPBYTE)&dw, &cb) == ERROR_SUCCESS) &&
			(dwType == REG_DWORD) && (cb == sizeof(dw))) 
        {
			if ((pStream - szStream) + WRAPPER_SZ < MSMQ_STREAM_LEN) 
            {
				wsprintf (pStream, L"Track network: %s" EOL, dw ? L"yes" : L"no");
				pStream += wcslen (pStream);
			}
		}

		RegCloseKey (hk);
	} else {
		wcscpy (pStream, EOL L"NETREG NOT configured." EOL);
		pStream += wcslen (pStream);
	}

	SendMessage (GetDlgItem (g_hWnd, IDC_RESULTS), WM_SETTEXT, 0, (LPARAM)szStream);
}

// Purpose: Determine at runtime if the app is running on a smartphone device
static BOOL IsSmartphone() 
{
    WCHAR wszPlatform[64];

    if (TRUE == SystemParametersInfo(SPI_GETPLATFORMTYPE,
         sizeof(wszPlatform)/sizeof(*wszPlatform),wszPlatform,0))
    {
        if (0 == _wcsicmp(L"Smartphone", wszPlatform)) 
        {
            return TRUE;
        }
    }
    return FALSE;   
}

static BOOL CALLBACK DlgProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    BOOL fReturn = FALSE; //Default return value;

	switch (uMsg)
    {
	    case WM_INITDIALOG:
		    g_hWnd = hWnd;

#if defined (UNDER_CE)

	        // Specify that the dialog box should stretch full screen
	        SHINITDLGINFO shidi;

	        ZeroMemory(&shidi, sizeof(shidi));
	        shidi.dwMask = SHIDIM_FLAGS;
	        shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
	        shidi.hDlg = hWnd;

            // If we could not initialize the dialog box, return an error
	        if (false == SHInitDialog(&shidi))
            {
                MessageBox(hWnd, TEXT("Failed to init dialog"), TEXT("Failure"), MB_OK);

                //Failed to init, so quit app
                EndDialog (hWnd, FALSE);
                fReturn = TRUE;
            }

	        // set up Soft Keys menu
	        SHMENUBARINFO mbi;
	        
	        ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
	        mbi.cbSize = sizeof(SHMENUBARINFO);
	        mbi.hwndParent = hWnd;
	        mbi.nToolBarId = IDM_VISADM_MENU;
	        mbi.hInstRes = g_hInst;

            if (false == SHCreateMenuBar(&mbi))
            {
                MessageBox(hWnd, TEXT("Failed to create menu bar"), TEXT("Failure"), MB_OK);

                //Failed to init, so quit app
                EndDialog (hWnd, FALSE);
                fReturn = TRUE;
            }

            //Now find out if we are a smartphone device
            if (IsSmartphone())
            {
                // In order to make Back work properly, it's necessary to 
	            // override it and then call the appropriate SH API
	            (void)SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
                    MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
                    SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

                //Now turn off off the edit boxes scrolls, SPh doesn't like scrolls
                DWORD dwStyles = GetWindowLong(GetDlgItem(hWnd, IDC_RESULTS), GWL_STYLE);
                dwStyles = dwStyles & ~(WS_VSCROLL | WS_HSCROLL);
                SetWindowLong(GetDlgItem(hWnd, IDC_RESULTS), GWL_STYLE, dwStyles);

                //Now create a SPh expandable edit control
                HWND hWndExpander = CreateWindow(UPDOWN_CLASS, NULL, 
                    WS_VISIBLE | UDS_ALIGNRIGHT | UDS_EXPANDABLE | UDS_NOSCROLL, 0, 0, 0, 0,
                    hWnd, (HMENU)IDC_RESULTS_EXPANDER, g_hInst, 0L);
                SendMessage(hWndExpander, UDM_SETBUDDY, (WPARAM)GetDlgItem(hWnd, IDC_RESULTS), 0);
            }

#else
            //Create a desktop menu bar
            SetMenu(hWnd, LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_VISADM_OPTIONS)));
#endif //UNDER_CE
		    SetFocus (GetDlgItem (hWnd, IDC_COMMAND));

            return TRUE;
#if defined (UNDER_CE)

        case WM_ACTIVATE:
            if (WA_INACTIVE == LOWORD(wParam))
            {
                if ((NULL == lParam) || (g_hWnd == (HWND)lParam))
                {
                    EndDialog(hWnd, 0);
                }
            }
            break;

        case WM_SIZE:
            {
                HWND hWndControl;
                int iY, iX, iW, iH;

                //Get the client window size
                RECT rect;
                GetClientRect(hWnd, &rect);

                //Derive the size of the command edit control
                iX = rect.left + WINDOW_BORDER;
                iY = rect.bottom - rect.top - CONTROL_HEIGHT - WINDOW_BORDER;
                iW = rect.right - rect.left - 2 * WINDOW_BORDER;
                iH = CONTROL_HEIGHT;
                hWndControl = GetDlgItem(hWnd, IDC_COMMAND);
                MoveWindow(hWndControl, iX, iY, iW, iH, TRUE);

                //Derive the size of the results edit control
                iH = iY - rect.top - 2 * WINDOW_BORDER;
                iY = rect.top + WINDOW_BORDER;

                if (IsSmartphone())
                {
                    //Make room for the SPh standard 10 pixel width spinner
                    iW -= SPINNER_WIDTH;
                    hWndControl = GetDlgItem(hWnd, IDC_RESULTS_EXPANDER);
                    MoveWindow(hWndControl, iX + iW, iY, SPINNER_WIDTH, iH, TRUE);
                    //Now nudge the results window width back to prevent double border
                    iW++;
                }

                //Move
                hWndControl = GetDlgItem(hWnd, IDC_RESULTS);
                MoveWindow(hWndControl, iX, iY, iW, iH, TRUE);
            }
            break;
#endif //UNDER_CE
	    case WM_COMMAND:
            {
			    int wID = LOWORD(wParam);
			    switch (wID)
			    {
			        case IDOK:
				    {
					    WCHAR szCommand[_MAX_PATH];
					    SendMessage (GetDlgItem (hWnd, IDC_COMMAND), WM_GETTEXT, (WPARAM)_MAX_PATH, (LPARAM)szCommand);
					    RunCommand (szCommand);
					    return 0;
				    }

			        case IDCANCEL:
                        //Exit the program
				        EndDialog (hWnd, FALSE);
				        fReturn = TRUE;
                        break;

                    //Menu bar commands
                    case IDC_BUTTON1:	// install
				        RunCommand (L"register install netreg");
                        break;

			        case IDC_BUTTON2:	// verify
				        RunCommand (L"register uninstall");
                        break;

			        case IDC_BUTTON3:	// register
				        RunCommand (L"register");
                        break;

			        case IDC_BUTTON4:
				        Verify ();
                        break;

			        case IDC_BUTTON5:
				        RunCommand (L"status");
                        break;

			        case IDC_BUTTON6:
				        DeliverOutput (L"\\temp\\msmq\\mqlogfile.txt");
                        break;

			        case IDC_BUTTON7:
				        RunCommand (L"start");
                        break;

			        case IDC_BUTTON8:
				        RunCommand (L"stop");
                        break;

			    }
		    }
		    break;

//WM_HOTKEY SPh specific but won't hurt a PPC app
#if defined (UNDER_CE)

		case WM_HOTKEY:
			if (HIWORD(lParam) == VK_TBACK)
			{
				SHSendBackToFocusWindow(uMsg, wParam, lParam);
			}
			break;
#endif //UNDER_CE
	}

	return fReturn;
}

#if defined (UNDER_CE)
int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpszCmdLine, int nCmdShow) {

    //Init the device specific controls
    SHInitExtraControls();
#else
int WINAPI wWinMain (HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpszCmdLine, int nCmdShow) {
#endif

    g_hInst = hInst;

	DialogBox (hInst, MAKEINTRESOURCE (IDD_DIALOG1), NULL, DlgProc);

	return 0;
}
