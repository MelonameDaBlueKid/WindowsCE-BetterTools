// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   about.c
//
//  PURPOSE:   Displays the "About" dialog box
//
//  FUNCTIONS:
//    CmdAbout        - Displays the "About" dialog box
//    About           - Processes messages for "About" dialog box.
//    MsgAboutInit    - To initialize the about box with version info
//                      from resources.
//    MsgAboutCommand - Process WM_COMMAND message sent to the about box.
//    CmdAboutDone    - Free the about box and related data.
//
//  COMMENTS:
//
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#include "globals.h"            // prototypes specific to this application
#include "resource.h"

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//
//  FUNCTION: CmdAbout(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Displays the "About" dialog box
//
//  PARAMETERS:
//    hwnd      - Window handle
//    wCommand  - IDM_ABOUT (unused)
//    wNotify   - Notification number (unused)
//    hwndCtrl  - NULL (unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//    To process the IDM_ABOUT message, call DialogBox() to display the
//    about dialog box.

LRESULT CmdAbout(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    DialogBox(hInst, L"AboutBox", hwnd, (DLGPROC)About);
    return 0;
}


// Mesage handler for the About box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
      //On Rapier devices you normally create all Dialog's as fullscreen dialog's
      // with an OK button in the upper corner. 
      SHINITDLGINFO shidi;
      // Create a Done button and size it.
      shidi.dwMask = SHIDIM_FLAGS;
      shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
      shidi.hDlg = hDlg;
      //initialzes the dialog based on the dwFlags parameter
      SHInitDialog(&shidi);
			return TRUE;

		case WM_COMMAND:
			if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


