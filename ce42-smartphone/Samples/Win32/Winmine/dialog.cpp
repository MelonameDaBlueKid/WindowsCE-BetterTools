// ***************************************************************************
// DIALOG.CPP
//
// All Dialog Procedures and related functions for Minesweeper
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include "winmine.h"

BOOL InitDialog(
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
	if (FALSE == (SHInitDialog(&shidi) && SHCreateMenuBar(&mbi))) {
		return FALSE;
	}

	// set the title bar
	VERIFY(SetWindowText(hDlg, g_tszTitle));

	// In order to make Back work properly, it's necessary to 
	// override it and then call the appropriate SH API
	(void)SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, 
					  MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, 
								 SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

	return TRUE;
}

BOOL CALLBACK HelpDlgProc(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam, 
    const LPARAM lParam
    )
{
	BOOL bProcessedMsg = TRUE;

	switch(uiMessage)
	{
		case WM_INITDIALOG:
			if (FALSE == InitDialog(hDlg, IDR_WINMINE_DLGMENU)) 
            {
				EndDialog(hDlg, EINITFAILED);
			}
			break;

		case WM_COMMAND:
			switch (wParam) 
            {			
				case IDM_WINMINE_OK:
					EndDialog(hDlg, 0);
					break;

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

BOOL CALLBACK NewHighDlgProc(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam,
    const LPARAM lParam
    )
{
	BOOL bProcessedMsg = TRUE;
	HWND hwnd;
	int	iResult;

	switch(uiMessage)
	{
		case WM_INITDIALOG:
			if (FALSE == InitDialog(hDlg, IDR_WINMINE_DLGMENU)) 
            {
				EndDialog(hDlg, EINITFAILED);
			}

			// set the text in the edit box to be the last known name
			SetDlgItemText(hDlg, IDC_WINMINE_HIGHNAME, g_hsScores[g_gd.gtType].szName);

			// highlight all the text in the box for easier replacement
			VERIFY(hwnd = GetDlgItem(hDlg, IDC_WINMINE_HIGHNAME));
			SetFocus(hwnd);
			SendMessage(hwnd, EM_SETSEL, 0, -1);

			// since I set the focus, return false
			bProcessedMsg = FALSE;

			break;

		case WM_COMMAND:
			switch (wParam) 
            {			
				case IDM_WINMINE_OK:
					// update the best time
					g_hsScores[g_gd.gtType].dwTime = g_gd.dwCurTime;

					// update the best name
					VERIFY(hwnd = GetDlgItem(hDlg, IDC_WINMINE_HIGHNAME));
					iResult = GetWindowTextLength(hwnd) + 1;
					if (iResult) 
                    {
						// cleanup the previous entry
						free(g_hsScores[g_gd.gtType].szName);

						// try to malloc space for a new entry
                        g_hsScores[g_gd.gtType].szName = (LPTSTR) malloc(iResult * sizeof(TCHAR));
						if (NULL == g_hsScores[g_gd.gtType].szName) 
                        {
							EndDialog(hDlg, ENOMEM);
						}
                        VERIFY(GetDlgItemText(hDlg, IDC_WINMINE_HIGHNAME, 
                            g_hsScores[g_gd.gtType].szName, iResult));
					}

					EndDialog(hDlg, 0);
					break;

				default:
					bProcessedMsg = FALSE;
					break;
			}
			break;

		case WM_HOTKEY:
			switch (HIWORD(lParam)) 
            {
				case VK_TBACK:
					SHSendBackToFocusWindow(uiMessage, wParam, lParam);
					break;

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

BOOL CALLBACK HighDlgProc(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam, 
    const LPARAM lParam
    )
{
	BOOL	bProcessedMsg = TRUE;
	TCHAR	tszTemp[4];

	switch(uiMessage)
	{
		case WM_INITDIALOG:
			if (FALSE == InitDialog(hDlg, IDR_WINMINE_DLGMENU))
            {
				EndDialog(hDlg, EINITFAILED);
			}

			// set the text fields
			SetDlgItemText(hDlg, IDC_WINMINE_BNAME, g_hsScores[BEGINNER].szName);
			SetDlgItemText(hDlg, IDC_WINMINE_INAME, g_hsScores[INTERMEDIATE].szName);
			SetDlgItemText(hDlg, IDC_WINMINE_ENAME, g_hsScores[EXPERT].szName);


			// set the numerical fields
			_sntprintf(tszTemp, ARRAY_LENGTH(tszTemp), TEXT("%d"), g_hsScores[BEGINNER].dwTime);
			SetDlgItemText(hDlg, IDC_WINMINE_BTIME, tszTemp);

			_sntprintf(tszTemp, ARRAY_LENGTH(tszTemp), TEXT("%d"), g_hsScores[INTERMEDIATE].dwTime);
			SetDlgItemText(hDlg, IDC_WINMINE_ITIME, tszTemp);

			_sntprintf(tszTemp, ARRAY_LENGTH(tszTemp), TEXT("%d"), g_hsScores[EXPERT].dwTime);
			SetDlgItemText(hDlg, IDC_WINMINE_ETIME, tszTemp);

			break;

		case WM_COMMAND:
			switch (wParam) 
            {			
				case IDM_WINMINE_OK:
					EndDialog(hDlg, 0);
					break;

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

BOOL CALLBACK PrefsDlgProc(
    const HWND hDlg, 
    const UINT uiMessage, 
    const WPARAM wParam, 
    const LPARAM lParam
    )
{
	BOOL	bProcessedMsg = TRUE;
	HWND	hwndMoveList;
	HWND	hwndMarkList;
	HWND	hwndUncList;
	HWND	hwndSoundCB;
	int		iCheck;

	switch(uiMessage)
	{
		case WM_INITDIALOG:
			if (!InitDialog(hDlg, IDR_WINMINE_DLGMENU)) 
            {
				EndDialog(hDlg, EINITFAILED);
			}

			// get handles to the listboxen
			VERIFY(hwndMoveList = GetDlgItem(hDlg, IDC_WINMINE_MOVELIST));
			VERIFY(hwndMarkList = GetDlgItem(hDlg, IDC_WINMINE_MARKLIST));
			VERIFY(hwndUncList = GetDlgItem(hDlg, IDC_WINMINE_UNCLIST));
			VERIFY(hwndSoundCB = GetDlgItem(hDlg, IDC_WINMINE_SOUNDS));

			// populate the listboxen
			AddValidKeys(hwndMoveList, g_gd.dwKeyMakeMove);
			AddValidKeys(hwndMarkList, g_gd.dwKeyMakeMark);
			AddValidKeys(hwndUncList, g_gd.dwKeyUncover);

			// set the checkbox
			SendMessage(hwndSoundCB, BM_SETCHECK, 
						g_gd.bSounds ? BST_CHECKED : BST_UNCHECKED, 0);

			break;

		case WM_COMMAND:
			switch (wParam) 
            {			
				case IDM_WINMINE_OK:
					if (AssignKeys(hDlg)) 
                    {
						EndDialog(hDlg, 0);
					} 
                    else 
                    {
                        MessageBox(hDlg, UseString(IDS_WINMINE_PREFS), 
                            g_tszTitle, MB_OK | MB_ICONWARNING);
					}
					break;

				case IDC_WINMINE_SOUNDS:
					VERIFY(hwndSoundCB = GetDlgItem(hDlg, IDC_WINMINE_SOUNDS));
					iCheck = (int)SendMessage(hwndSoundCB, BM_GETCHECK, 0, 0);
					
					// if it was checked, uncheck it and disable sounds
					if (iCheck)
                    {
						SendMessage(hwndSoundCB, BM_SETCHECK, BST_UNCHECKED, 0);
						g_gd.bSounds = FALSE;
					} 
                    else
                    {
						SendMessage(hwndSoundCB, BM_SETCHECK, BST_CHECKED, 0);
						g_gd.bSounds = TRUE;
					}

					break;

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

BOOL AddValidKeys(
    const HWND hwnd, 
    const DWORD dwCurKey
    )
{
	TCHAR tszTemp[32];
	int iResult;
	DWORD dwItemData;

	// add the action key
	iResult = SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM) TEXT("Action Key"));
	if (iResult < LB_OKAY) return FALSE;

	// if successful set the item data
	SendMessage(hwnd, LB_SETITEMDATA, (WPARAM) iResult, (LPARAM) 0x0D);

	// add numerical keys 0 - 9
	for (int i = 0; i <= 9; i++) 
    {
		_sntprintf(tszTemp, ARRAY_LENGTH(tszTemp), TEXT("Numerical Key %d"), i);
		iResult = SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM) tszTemp);
		if (LB_OKAY > iResult) 
        {
            return FALSE;
        }

		// if successful set the item data
		SendMessage(hwnd, LB_SETITEMDATA, (WPARAM) iResult, 
					(LPARAM) i + ASCII_NUMBER_OFFSET);
	}

	// set the focus to the currently used key
	iResult = SendMessage(hwnd, LB_GETCOUNT, 0, 0);
	if (LB_ERR == iResult)
    {
        return FALSE;
    }

	for (i = 0; i < iResult; i++)
    {
		dwItemData = SendMessage(hwnd, LB_GETITEMDATA, (WPARAM) i, 0);
		if (dwItemData == dwCurKey)
        {
			SendMessage(hwnd, LB_SETCURSEL, (WPARAM) i, 0);
			break;
		}
	}

	return TRUE;
}

BOOL AssignKeys(HWND hDlg)
{
	DWORD dwMove;
    DWORD dwMark;
    DWORD dwUnc;
	int iResult;

	HWND	hwndMoveList;
	HWND	hwndMarkList;
	HWND	hwndUncList;

	// get handles to the listboxen
	VERIFY(hwndMoveList = GetDlgItem(hDlg, IDC_WINMINE_MOVELIST));
	VERIFY(hwndMarkList = GetDlgItem(hDlg, IDC_WINMINE_MARKLIST));
	VERIFY(hwndUncList = GetDlgItem(hDlg, IDC_WINMINE_UNCLIST));

	// get the selected key for MakeMove
	iResult = SendMessage(hwndMoveList, LB_GETCURSEL, 0, 0);
	if (LB_ERR == iResult) 
    {
		return FALSE;
	}
	dwMove = SendMessage(hwndMoveList, LB_GETITEMDATA, (WPARAM) iResult, 0);
	if (LB_ERR == dwMove) 
    {
		return FALSE;
	}

	// get the selected key for MakeMark
	iResult = SendMessage(hwndMarkList, LB_GETCURSEL, 0, 0);
	if (LB_ERR == iResult) 
    {
		return FALSE;
	}
	dwMark = SendMessage(hwndMarkList, LB_GETITEMDATA, (WPARAM) iResult, 0);
	if (LB_ERR == dwMark) 
    {
		return FALSE;
	}

	// get the selected key for Uncover
	iResult = SendMessage(hwndUncList, LB_GETCURSEL, 0, 0);
	if (LB_ERR == iResult) 
    {
		return FALSE;
	}
	dwUnc = SendMessage(hwndUncList, LB_GETITEMDATA, (WPARAM) iResult, 0);
	if (LB_ERR == dwUnc) 
    {
		return FALSE;
	}

	// if there are no duplicates, assign the new keys, else return FALSE
	if ((dwMove == dwMark) || (dwMove == dwUnc) || (dwMark == dwUnc)) 
    {
		return FALSE;
	} 
    else 
    {
		g_gd.dwKeyMakeMark = dwMark;
		g_gd.dwKeyMakeMove = dwMove;
		g_gd.dwKeyUncover = dwUnc;
	}

	return TRUE;
}