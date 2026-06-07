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

// FileDRM.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "FileDRM.h"
#include "ImageView.h"

// Global Variables:
HINSTANCE			g_hInst;						// current instance
HWND				g_hWndMenuBar;					// menu bar handle
TCHAR				g_szCurrentDirectory[MAX_PATH];	// Current directory in the list view
CImageView			*g_pDisplayedImage;				// Image being displayed (if any)

// Forward declarations of functions included in this code module:
ATOM			MyRegisterClass(HINSTANCE, LPTSTR);
BOOL			InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
#ifndef WIN32_PLATFORM_WFSP
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
#endif // !WIN32_PLATFORM_WFSP

LRESULT				OnNotify				(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT				DisplayJPEG				(HWND hWnd, const LPCTSTR pszDirectory, const LPCTSTR pszFile);
HRESULT				ShowProtectionStatus	(HWND hWndList);
LRESULT				OnInitMenuPopup			(HWND hWndList, HMENU hmenuPopup);


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
	MSG msg;

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	if (FAILED (CoInitializeEx (NULL, COINIT_MULTITHREADED)))
	{
		return FALSE;
	}

#ifndef WIN32_PLATFORM_WFSP
	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FILEDRM));
#endif // !WIN32_PLATFORM_WFSP

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
#ifndef WIN32_PLATFORM_WFSP
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
#endif // !WIN32_PLATFORM_WFSP
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CoUninitialize ();
	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FILEDRM));
	wc.hCursor       = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szWindowClass;

	return RegisterClass(&wc);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    TCHAR szTitle[MAX_LOADSTRING];		// title bar text
    TCHAR szWindowClass[MAX_LOADSTRING];	// main window class name

    g_hInst = hInstance; // Store instance handle in our global variable

#ifdef WIN32_PLATFORM_PSPC
    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Pocket PC special controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();
#endif // WIN32_PLATFORM_PSPC
	
	// Ensure that the common control DLL is loaded.
	InitCommonControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_FILEDRM, szWindowClass, MAX_LOADSTRING);

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
    //If it is already running, then focus on the window, and exit
    hWnd = FindWindow(szWindowClass, szTitle);	
    if (hWnd) 
    {
        // set focus to foremost child window
        // The "| 0x00000001" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        return 0;
    } 
#endif // WIN32_PLATFORM_PSPC || WIN32_PLATFORM_WFSP

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
    	return FALSE;
    }

	SHGetSpecialFolderPath (NULL, g_szCurrentDirectory, CSIDL_PERSONAL, FALSE);

    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

#ifdef WIN32_PLATFORM_PSPC
    // When the main window is created using CW_USEDEFAULT the height of the menubar (if one
    // is created is not taken into account). So we resize the window after creating it
    // if a menubar is present
    if (g_hWndMenuBar)
    {
        RECT rc;
        RECT rcMenuBar;

        GetWindowRect(hWnd, &rc);
        GetWindowRect(g_hWndMenuBar, &rcMenuBar);
        rc.bottom -= (rcMenuBar.bottom - rcMenuBar.top);
		
        MoveWindow(hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, FALSE);
    }
#endif // WIN32_PLATFORM_PSPC

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND		s_hWndLV = 0;
	int				wmId;
	int				wmEvent;
    PAINTSTRUCT		ps;
    HDC				hdc;

#if defined(SHELL_AYGSHELL) && !defined(WIN32_PLATFORM_WFSP)
    static SHACTIVATEINFO s_sai;
#endif // SHELL_AYGSHELL && !WIN32_PLATFORM_WFSP
	
    switch (message) 
    {
		case WM_NOTIFY:
			return OnNotify (hWnd, message, wParam, lParam);
			break;

		case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            // Parse the menu selections:
            switch (wmId)
            {
#ifndef WIN32_PLATFORM_WFSP
                case IDM_HELP_ABOUT:
                    DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, About);
                    break;
#endif // !WIN32_PLATFORM_WFSP
#ifdef WIN32_PLATFORM_WFSP
                case IDM_OK:
                    if (g_pDisplayedImage)
					{
						ShowWindow (s_hWndLV, SW_SHOW);
						SetFocus (s_hWndLV);

						delete g_pDisplayedImage;
						g_pDisplayedImage = NULL;
					}
                    else
                    {
                        DestroyWindow(hWnd);
                    }
                    break;
#endif // WIN32_PLATFORM_WFSP
#ifndef WIN32_PLATFORM_WFSP
                case IDM_OK:
                    if (g_pDisplayedImage)
					{
						ShowWindow (s_hWndLV, SW_SHOW);
						SetFocus (s_hWndLV);

						delete g_pDisplayedImage;
						g_pDisplayedImage = NULL;
					}
                    else
                    {
                        SendMessage (hWnd, WM_CLOSE, 0, 0);				
                    }
                    break;
#endif // !WIN32_PLATFORM_WFSP

				case ID_MENU_UP:

					if (g_pDisplayedImage)
					{
						ShowWindow (s_hWndLV, SW_SHOW);
						SetFocus (s_hWndLV);

						delete g_pDisplayedImage;
						g_pDisplayedImage = NULL;
					}
					else
					{
						LPTSTR	pszTemp;
	
						pszTemp = _tcsrchr (g_szCurrentDirectory, _T('\\'));
						if (pszTemp)
						{
							if (pszTemp == g_szCurrentDirectory)
							{
								*(pszTemp + 1) = _T('\0');
							}
							else
							{
								*pszTemp = _T('\0');
							}
						}
						FillListView (g_hInst, s_hWndLV, g_szCurrentDirectory);
					}
					break;

				case ID_MENU_DRMPROTECTION:
					ShowProtectionStatus (s_hWndLV);
					break;

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_CREATE:
#ifdef SHELL_AYGSHELL
            SHMENUBARINFO mbi;

            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hWnd;
            mbi.nToolBarId = IDR_MENU;
            mbi.hInstRes   = g_hInst;

            if (!SHCreateMenuBar(&mbi)) 
            {
                g_hWndMenuBar = NULL;
            }
            else
            {
                g_hWndMenuBar = mbi.hwndMB;
            }

#ifndef WIN32_PLATFORM_WFSP
            // Initialize the shell activate info structure
            memset(&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
#endif // !WIN32_PLATFORM_WFSP
#endif // SHELL_AYGSHELL

			s_hWndLV = CreateListView(g_hInst, hWnd, g_hWndMenuBar);
			if (s_hWndLV)
			{	
				FillListView (g_hInst, s_hWndLV, g_szCurrentDirectory);
				SetFocus (s_hWndLV);
			}

            break;
        case WM_PAINT:
            RECT rc;

			hdc = BeginPaint(hWnd, &ps);

			GetClientRect (hWnd, &rc);
            if (g_pDisplayedImage)
			{
				if (FAILED (g_pDisplayedImage->Draw (hWnd, hdc, &rc)))
				{
					delete g_pDisplayedImage;
					g_pDisplayedImage = NULL;

					ShowWindow (s_hWndLV, SW_SHOW);
					SetFocus (s_hWndLV);
				}
			}

            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
#ifdef SHELL_AYGSHELL
            CommandBar_Destroy(g_hWndMenuBar);
#endif // SHELL_AYGSHELL
			if (g_pDisplayedImage)
			{
				delete g_pDisplayedImage;
			}

			PostQuitMessage(0);
            break;

#if defined(SHELL_AYGSHELL) && !defined(WIN32_PLATFORM_WFSP)
        case WM_ACTIVATE:
            // Notify shell of our activate message
            SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
            break;
        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
            break;
#endif // SHELL_AYGSHELL && !WIN32_PLATFORM_WFSP

		case WM_DISPLAYIMAGE:
			ShowWindow (s_hWndLV, SW_HIDE);
			SetFocus (hWnd);
			break;

		case WM_INITMENUPOPUP:
			if (!g_pDisplayedImage)
			{
				const HMENU hmenuPopup = reinterpret_cast<HMENU>(wParam); 
				OnInitMenuPopup (s_hWndLV, hmenuPopup);
			}
			break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

#ifndef WIN32_PLATFORM_WFSP
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
#ifdef SHELL_AYGSHELL
            {
                // Create a Done button and size it.  
                SHINITDLGINFO shidi;
                shidi.dwMask = SHIDIM_FLAGS;
                shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
                shidi.hDlg = hDlg;
                SHInitDialog(&shidi);
            }
#endif // SHELL_AYGSHELL

            return (INT_PTR)TRUE;

        case WM_COMMAND:
#ifdef SHELL_AYGSHELL
            if (LOWORD(wParam) == IDOK)
#endif
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hDlg, message);
            return (INT_PTR)TRUE;

#ifdef _DEVICE_RESOLUTION_AWARE
        case WM_SIZE:
            {
		DRA::RelayoutDialog(
			g_hInst, 
			hDlg, 
			DRA::GetDisplayMode() != DRA::Portrait ? MAKEINTRESOURCE(IDD_ABOUTBOX_WIDE) : MAKEINTRESOURCE(IDD_ABOUTBOX));
            }
            break;
#endif
    }
    return (INT_PTR)FALSE;
}
#endif // !WIN32_PLATFORM_WFSP


LRESULT OnNotify (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	const LPNMHDR pNotifyHeader = reinterpret_cast<LPNMHDR>(lParam);

	if (pNotifyHeader->idFrom == ID_LISTVIEW)
	{
		const HWND hWndList = pNotifyHeader->hwndFrom;

		switch(pNotifyHeader->code)
		{
			case NM_RECOGNIZEGESTURE:
				lResult = TRUE;				// No gestures
				break;

			case LVN_ITEMACTIVATE:
			{
				LVITEM lvi = { 0 };
				const LPNMLISTVIEW lpnmlv = reinterpret_cast<LPNMLISTVIEW>(lParam);
				TCHAR szText[MAX_PATH];

				lvi.mask = LVIF_TEXT | LVIF_PARAM;
				lvi.iItem = lpnmlv->iItem;
				lvi.pszText = szText;
				lvi.cchTextMax = ARRAYSIZE(szText);
				ListView_GetItem (hWndList, &lvi);

				const DWORD dwFileAttributes = lvi.lParam;
				if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					size_t cchCurrentDirectory;
					StringCchLength (g_szCurrentDirectory, ARRAYSIZE(g_szCurrentDirectory), &cchCurrentDirectory);
					if (*((g_szCurrentDirectory + cchCurrentDirectory) - 1) != _T('\\'))
					{
						StringCchCat (g_szCurrentDirectory, ARRAYSIZE(g_szCurrentDirectory), _T("\\"));
					}
					StringCchCat (g_szCurrentDirectory, ARRAYSIZE(g_szCurrentDirectory), szText);
					FillListView (g_hInst, hWndList, g_szCurrentDirectory);
				}
				else
				{
					if (IsJPEGFile (szText))
					{
						if (FAILED (DisplayJPEG (hWnd, g_szCurrentDirectory, szText)))
                        {
                            /*
                             *  In case we fail to display the image ensure that the
                             *  listview window still has focus.
                             */
                            SetFocus(hWndList);
                        }
					}
					else
					{
						TCHAR szMessage [MAX_LOADSTRING];
						TCHAR szTitle [MAX_LOADSTRING];
						
						if (   0 != LoadString (g_hInst, IDS_NOHANDLER_MSG, szMessage, ARRAYSIZE (szMessage))
							&& 0 != LoadString (g_hInst, IDS_NOHANDLER_TITLE, szTitle, ARRAYSIZE (szTitle)))
						{
							MessageBox (hWnd, szMessage, szTitle, MB_OK | MB_ICONERROR);
							SetFocus (hWndList);
						}
					}
				}
				break;
			}

			default:
				break;
		}
	}

	return lResult;
}



HRESULT IsDRMProtected (const LPCTSTR pszDirectory, const LPCTSTR pszFile, BOOL *fIsDRM)
{
	HRESULT	hr;
	BOOL	fResult;
	TCHAR	szFullPath [MAX_PATH];

	fResult = FALSE;
	hr = BuildFullName (szFullPath, ARRAYSIZE (szFullPath), pszDirectory, pszFile);
	if (SUCCEEDED (hr))
	{
		hr = FileDrmIsDRM (szFullPath, &fResult);
		if (SUCCEEDED (hr))
		{
			*fIsDRM = fResult;
		}
	}
	return hr;
}



HRESULT DisplayJPEG (HWND hWnd, const LPCTSTR pszDirectory, const LPCTSTR pszFile)
{
	HRESULT hr;
	TCHAR	szFullName[MAX_PATH];

	hr = BuildFullName (szFullName, ARRAYSIZE (szFullName), pszDirectory, pszFile);
	if (SUCCEEDED (hr))
	{
		assert (g_pDisplayedImage == NULL);
		g_pDisplayedImage = new CImageView ();
		if (g_pDisplayedImage)
		{
			hr = g_pDisplayedImage->OpenImageFile (hWnd, szFullName);
            if (SUCCEEDED (hr))
            {
    			if (SendMessage (hWnd, WM_DISPLAYIMAGE, 0, 0))
	    		{
		    		const DWORD dwLastError = GetLastError ();
			    	hr = HRESULT_FROM_WIN32(dwLastError);
			    }
            }
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}
	}
	return hr;
}

HRESULT ShowProtectionStatus (HWND hWndList)
{
	HRESULT hr;
	LVITEM	lvi = { 0 };
	TCHAR	szText[MAX_PATH];
	BOOL	fIsDRM;

	lvi.mask = LVIF_TEXT;
	lvi.iItem = ListView_GetSelectionMark (hWndList);
	if (lvi.iItem != -1)
	{
		lvi.pszText = szText;
		lvi.cchTextMax = ARRAYSIZE(szText);
	
		if (ListView_GetItem (hWndList, &lvi))
		{
			hr = IsDRMProtected (g_szCurrentDirectory, szText, &fIsDRM);
			if (SUCCEEDED (hr) && fIsDRM)
			{
				TCHAR szFullpath [MAX_PATH];

				hr = BuildFullName (szFullpath, ARRAYSIZE (szFullpath), g_szCurrentDirectory, szText);
				if (SUCCEEDED (hr))
				{
					hr = FileDrmShowLicenseInfo (hWndList, szFullpath);
				}
			}
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}

LRESULT	OnInitMenuPopup	(HWND hWndList, HMENU hmenuPopup)
{
	HRESULT hr;
	LVITEM	lvi = { 0 };
	TCHAR	szText[MAX_PATH];
	BOOL	fIsDRM;

	lvi.mask = LVIF_TEXT;
	lvi.iItem = ListView_GetSelectionMark (hWndList);
	if (lvi.iItem != -1)
	{
		lvi.pszText = szText;
		lvi.cchTextMax = ARRAYSIZE(szText);
		if (ListView_GetItem (hWndList, &lvi))
		{
			hr = IsDRMProtected (g_szCurrentDirectory, szText, &fIsDRM);
			if (SUCCEEDED (hr) && fIsDRM)
			{
				EnableMenuItem (hmenuPopup, ID_MENU_DRMPROTECTION, MF_BYCOMMAND | MF_ENABLED);
			}
			else
			{
				EnableMenuItem (hmenuPopup, ID_MENU_DRMPROTECTION, MF_BYCOMMAND | MF_GRAYED);
			}
		}
	}
	else
	{
		EnableMenuItem (hmenuPopup, ID_MENU_DRMPROTECTION, MF_BYCOMMAND | MF_GRAYED);
	}

	return 0;
}
