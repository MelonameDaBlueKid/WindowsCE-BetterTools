// ***************************************************************************
// MAIN.CPP
//
// WinMain and WndProc for the Stinger Minesweeper port
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include "winmine.h"

// global variables
HINSTANCE	g_hInst;
TCHAR		g_tszTitle[80];
TCHAR		g_tszAppName[80];
HWND		g_hwndMain;
HWND		g_hwndTimer;
HWND		g_hwndMines;
HWND		g_hwndMB;
HPEN		g_hpenBorder = NULL;
HPEN		g_hpenSelection = NULL;
HDC			g_hdcImage;
HBITMAP		g_hbmpBlocks = NULL;
int			g_iDefaults[3][3] = {{10, 8, 8}, {20, 10, 10}, {30, 12, 12}};
HighScores	g_hsScores[3];
int			g_iCurX = 0;
int			g_iCurY = 0;
int			g_iOffX;
int			g_iOffY;
int			g_iWindowWidth;
int			g_iWindowHeight;
RECT		g_rcBoard;
UINT		g_uiTimerID = 0;
HKEY		g_hkWinMine = NULL;
BOOL		g_bIgnoreTimer = TRUE;
GameData	g_gd;

int WINAPI WinMain (
    HINSTANCE hInstance,
    HINSTANCE hPreviousInstance,
    LPWSTR lpCmdLine,
    int nShowCmd
    )
{
	MSG Msg;

	// load in program name
	LoadString(hInstance, IDS_WINMINE_TITLE, g_tszTitle, ARRAY_LENGTH(g_tszTitle));
	LoadString(hInstance, IDS_WINMINE_APPNAME, g_tszAppName, ARRAY_LENGTH(g_tszAppName));
	
	// Use a globally named mutex to detect another instance of HelloSMS
    const HANDLE hMutex = CreateMutex(0, 0, TEXT("_WINMINE_EXE_MUTEX_"));

    // check the result code
	if(0 != hMutex)
    {
        // First instance running?  Okay to proceed...
		if(ERROR_ALREADY_EXISTS != GetLastError()) 
        {
			// store the hInstance
			g_hInst = hInstance;

			// initialize the window
			if (FALSE == InitApplication()) 
            { 
				return FALSE; 
			}

			// initialize the instance
			if (FALSE == InitInstance(nShowCmd)) 
            {
				return FALSE;
			}
			
			// begin message pump
			while (GetMessage(&Msg, NULL, 0,0) == TRUE) 
            {
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}

			// save settings
			if (FALSE == SaveSettings()) 
            {
				MessageBox(NULL, UseString(IDS_WINMINE_SAVEFAIL), 
						   UseString(IDS_WINMINE_ERROR), MB_OK | MB_ICONERROR);
			}
			
			// return all created objects
			CleanUp();
			
			VERIFY(CloseHandle(hMutex));
			return Msg.wParam;
		}
        else
        {
            // Already an instance running - attempt to switch to it and then exit
            const HWND hWndExistingInstance = FindWindow(g_tszAppName, g_tszTitle);
			HWND hwndRestore = GetLastActiveAppWindow(hWndExistingInstance);
			VERIFY((0 == hwndRestore) || SetForegroundWindow(hwndRestore));
			VERIFY(CloseHandle(hMutex));
        }
    }

    return TRUE;
}

BOOL InitInstance(
    int iShow
    )
{
	g_hwndMain = CreateWindow(g_tszAppName, g_tszTitle, WS_VISIBLE, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, g_hInst, NULL );

	if (NULL == g_hwndMain) 
    {
		return FALSE;
	}

	ShowWindow(g_hwndMain, iShow);
	UpdateWindow(g_hwndMain);

	return TRUE;
}

BOOL InitApplication()
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC) MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hInstance = g_hInst;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_tszAppName;
	
	return RegisterClass(&wc);
}

LRESULT CALLBACK MainWndProc(
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    )
{
    LRESULT lResult = TRUE;
	LPCREATESTRUCT lpcs;

	switch(Msg)
	{
		case WM_CREATE:
			// create the menu
			if (FALSE == InitMenu(hWnd, IDR_WINMINE_MAINMENU)) 
            {
				MessageBox(hWnd, UseString(IDS_WINMINE_MENUFAIL),
						   UseString(IDS_WINMINE_ERROR), MB_OK | MB_ICONERROR);
				return (-1);
			}

			// store the window width and height
			lpcs = (LPCREATESTRUCT) lParam;
			g_iWindowWidth = lpcs->cx;
			g_iWindowHeight = lpcs->cy;

			// initialize global game state variables
			if (FALSE == InitGame(hWnd)) 
            {
				MessageBox(hWnd, UseString(IDS_WINMINE_INITFAIL),
						   UseString(IDS_WINMINE_ERROR), MB_OK | MB_ICONERROR);
				return (-1);
			}
			
			break;
	
		case WM_COMMAND:
			switch (wParam)
			{
				case IDM_WINMINE_QUIT:
					// destroy the timer (if it exists) before quitting
					StopTimer();
					SendMessage(hWnd, WM_CLOSE, 0, 0);
					break;

				case IDM_WINMINE_HELP:
					DialogBox(g_hInst, MAKEINTRESOURCE(IDD_WINMINE_HELP),
							  hWnd, (DLGPROC) HelpDlgProc);
					break;

				case IDM_WINMINE_SHOWHIGH:
					DialogBox(g_hInst, MAKEINTRESOURCE(IDD_WINMINE_HIGH),
							  hWnd, (DLGPROC) HighDlgProc);
					break;

				case IDM_WINMINE_PREFS:
					DialogBox(g_hInst, MAKEINTRESOURCE(IDD_WINMINE_PREFS),
							  hWnd, (DLGPROC) PrefsDlgProc);
					break;

				case IDM_WINMINE_BEGINNER:
					g_gd.gtType = BEGINNER;
					NewGame();
					break;

				case IDM_WINMINE_INTERMEDIATE:
					g_gd.gtType = INTERMEDIATE;
					NewGame();
					break;

				case IDM_WINMINE_EXPERT:
					g_gd.gtType = EXPERT;
					NewGame();
					break;

				case IDM_WINMINE_NEWGAME:
					NewGame();
					break;

				case IDM_WINMINE_PAUSE:
					MessageBox(hWnd, UseString(IDS_WINMINE_PAUSEMB), 
							   g_tszTitle, MB_OK | MB_ICONWARNING);
					break;

				default:
					lResult = DefWindowProc(hWnd, Msg, wParam, lParam);
			}
			break;

		case WM_KEYDOWN:
			switch (wParam)
            {
				case VK_RIGHT:
					g_iCurX = (g_iCurX+1) % g_iDefaults[g_gd.gtType][INDEX_XBLOCKS];
					break;
				
				case VK_LEFT:
					if (--g_iCurX < 0) 
                    {
						g_iCurX = g_iDefaults[g_gd.gtType][INDEX_XBLOCKS] - 1;
					}
					break;
				
				case VK_DOWN:
					g_iCurY = (g_iCurY+1) % g_iDefaults[g_gd.gtType][INDEX_YBLOCKS];
					break;
				
				case VK_UP:
					if (--g_iCurY < 0) 
                    {
						g_iCurY = g_iDefaults[g_gd.gtType][INDEX_YBLOCKS] - 1;
					}
					break;
				
				default:
					// if it wasn't an arrow key, then it must have been an action key
					// or an invalid key.  Since the action keys are not constant, they cannot
					// be handled by a switch, so we redirect all keys to HAK to be checked...
					if (FALSE == HandleActionKeys(wParam)) 
                    {
						lResult = DefWindowProc(hWnd, Msg, wParam, lParam);
					}
			}

			// something happened, so redraw
			InvalidateRect(g_hwndMain, &g_rcBoard, FALSE);
			break;

		case WM_PAINT:
			DrawScreen();
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_TIMER:
			// increment the timer only if it hasn't maxed out yet
			if ((g_gd.dwCurTime != 999) && (!g_bIgnoreTimer)) 
            {
				++g_gd.dwCurTime;
				UpdateTimer();
			}
			break;

		case WM_ACTIVATE:
			// if we lose focus for any reason, stop the clock
			if (wParam) 
            {
				g_bIgnoreTimer = FALSE;
			}
            else
            {
				g_bIgnoreTimer = TRUE;
			}
			break;

		default:
			lResult = DefWindowProc(hWnd, Msg, wParam, lParam);
			break;
	}

	return (lResult);
}

BOOL HandleActionKeys(WPARAM wParam)
{
	int iResult;

	// if it wasn't an action key, bail out now...
	if (!((wParam == g_gd.dwKeyMakeMove) ||
		  (wParam == g_gd.dwKeyMakeMark) ||
		  (wParam == g_gd.dwKeyUncover))) 
    {
		return FALSE;
	}
	
	// if this is a new game, start it up...
	if (g_gd.gsStatus == NEWGAME) 
    {
		// if this is a new game, start the game and then fall through
		if (!StartGame()) 
        {
			MessageBox(g_hwndMain, UseString(IDS_WINMINE_STARTFAIL),
					   UseString(IDS_WINMINE_ERROR), MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			// we don't want to risk further harm to the system, so do nothing upon return
			return TRUE;
		}
	}

	// user tried to uncover the current square
	if (wParam == g_gd.dwKeyMakeMove)
    {
		if (!MakeMove(g_iCurX, g_iCurY))
        {
			myPlaySound(SOUND_BOMB, SND_ASYNC | SND_NODEFAULT);
			EndGame();
		}
	}

	// user tried to flag/unflag the current square
	if (wParam == g_gd.dwKeyMakeMark)
    {
		if (!MakeMark()) 
        {
			myPlaySound(SOUND_BOMB, SND_ASYNC | SND_NODEFAULT);
			EndGame();
		}
	}

	// user tried to uncover all the squares around current square
	if (wParam == g_gd.dwKeyUncover)
    {
		if (!UncoverNeighbors())
        {
			myPlaySound(SOUND_BOMB, SND_ASYNC | SND_NODEFAULT);
			EndGame();
		}
	}

	// check for a winner
	if (IsWinner()) 
    {
		// stop the clock immediately
		EndGame();

		// regardless of whether you have a high score or not, play sound
		myPlaySound(SOUND_WIN, SND_ASYNC | SND_NODEFAULT);

		// check to see if the time beats the previous best
		if (IsHighScore())
        {
			iResult = DialogBox(g_hInst, MAKEINTRESOURCE(IDD_WINMINE_NEWHIGH),
			    g_hwndMain, (DLGPROC) NewHighDlgProc);
		}
	}

	return TRUE;
}

BOOL InitMenu(
    HWND hWnd, 
    UINT nToolBarId
    )
{
	// fill in the menubar info struct
	SHMENUBARINFO mbi;
	ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
	mbi.cbSize = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hWnd;
	mbi.nToolBarId = nToolBarId;
	mbi.hInstRes = g_hInst;

	if (FALSE == SHCreateMenuBar(&mbi))
    {
		return FALSE;
	}
	
	// store a handle to the main menu
	g_hwndMB = mbi.hwndMB;

	return TRUE;
}

LPCTSTR UseString(UINT uID)
{
	return (LPCTSTR) LoadString(g_hInst, uID, NULL, 0);
}

void CleanUp()
{
	// free the high score strings
	for (int i = 0; i < 3; i++)
    {
		free(g_hsScores[i].szName);
	}
	
	// return the handle on the bitmap
	if (g_hbmpBlocks)
    {
		DeleteObject(g_hbmpBlocks);
	}

	// cleanup the pens
	if (g_hpenBorder) 
    {
		DeleteObject(g_hpenBorder);
	}
	if (g_hpenSelection) 
    {
		DeleteObject(g_hpenSelection);
	}

	// return the compatible HDC
	if (g_hdcImage) 
    {
		DeleteDC(g_hdcImage);
	}

	// close the registry key
	if (g_hkWinMine)
    {
		RegCloseKey(g_hkWinMine);
	}
}

BOOL SaveSettings()
{
	// temporary buffer to hold name of regkey
	TCHAR tszTemp[10];

	// save the high scores
	for (int i = 0; i < 3; i++) 
    {
		_sntprintf(tszTemp, ARRAY_LENGTH(tszTemp), TEXT("%s%d"), REGISTRY_VALUE_HIGHTIME, i);
		if (!SetRegDWORD(tszTemp, g_hsScores[i].dwTime)) 
        {
			return FALSE;
		}
		
		// try to get the name from the registry
		_sntprintf(tszTemp, ARRAY_LENGTH(tszTemp), TEXT("%s%d"), REGISTRY_VALUE_HIGHNAME, i);
		if (FALSE == SetRegString(tszTemp, g_hsScores[i].szName)) 
        {
			return FALSE;
		}

	}

	// save the gamedata array
	if (FALSE == SetRegBinary(REGISTRY_VALUE_GAMEDATA, (PBYTE) &g_gd, sizeof(GameData))) 
    {
		return FALSE;
	}

	return TRUE;
}

void UpdateMenus()
{
	// just set the check marks on the menus
	TBBUTTONINFO tbbi;
	tbbi.cbSize = sizeof(tbbi);
	tbbi.dwMask = TBIF_LPARAM;
	SendMessage(g_hwndMB, TB_GETBUTTONINFO, IDM_WINMINE_OPTIONS, (LPARAM)&tbbi);
	HMENU hm = (HMENU)tbbi.lParam;

	CheckMenuItem(hm, IDM_WINMINE_BEGINNER, 
				  (g_gd.gtType == BEGINNER) ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hm, IDM_WINMINE_INTERMEDIATE, 
				  (g_gd.gtType == INTERMEDIATE) ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hm, IDM_WINMINE_EXPERT, 
				  (g_gd.gtType == EXPERT) ? MF_CHECKED : MF_UNCHECKED);

	// set the left soft key
	TBBUTTONINFO tbbiContext;
	tbbiContext.cbSize = sizeof(tbbi);
	tbbiContext.dwMask = TBIF_COMMAND | TBIF_TEXT;
	
	// if the game is over, we want to say "New Game"
	// else, we want to be able to pause the game
	if (GAMEOVER == g_gd.gsStatus) {
		tbbiContext.idCommand = IDM_WINMINE_NEWGAME;
		tbbiContext.pszText = _tcsdup(UseString(IDS_WINMINE_NEWGAME));
		SendMessage(g_hwndMB, TB_SETBUTTONINFO, 
					IDM_WINMINE_PAUSE, (LPARAM) &tbbiContext);
	} 
    else 
    {
		tbbiContext.idCommand = IDM_WINMINE_PAUSE;
		tbbiContext.pszText = _tcsdup(UseString(IDS_WINMINE_PAUSE));
		SendMessage(g_hwndMB, TB_SETBUTTONINFO, 
					IDM_WINMINE_NEWGAME, (LPARAM) &tbbiContext);
	}

	// cleanup
	free(tbbiContext.pszText);
}

HWND GetLastActiveAppWindow(HWND hwndMain)
{
    LASTACTIVEWINDOW law;

    law.hwndLastActive = NULL;
    law.dwMainWindowThread = GetWindowThreadProcessId(hwndMain, NULL);
    if (EnumWindows(GetLastActiveAppWindowEnum, (LPARAM)&law))
    {
        return law.hwndLastActive;
    }
    else
    {
        return NULL;
    }
}

BOOL CALLBACK GetLastActiveAppWindowEnum(HWND hWnd, LPARAM lParam)
{
    LASTACTIVEWINDOW *plaw;
    DWORD dwThread;

    plaw = (LASTACTIVEWINDOW *)lParam;
    dwThread = GetWindowThreadProcessId(hWnd, NULL);

    // Look for a same-thread, visible, enabled, !WS_EX_NOACTIVATE window.  
    // There should be only one if each of the app's dialogs/messageboxes disables its owner.
    if (dwThread == plaw->dwMainWindowThread &&
        IsWindowVisible(hWnd) &&
        IsWindowEnabled(hWnd) &&
        !(WS_EX_NOACTIVATE & GetWindowLong(hWnd, GWL_EXSTYLE))
       )
    {
        // Found active window
        plaw->hwndLastActive = hWnd;
        return FALSE;
    }

    // Keep enumerating
    return TRUE;
}
