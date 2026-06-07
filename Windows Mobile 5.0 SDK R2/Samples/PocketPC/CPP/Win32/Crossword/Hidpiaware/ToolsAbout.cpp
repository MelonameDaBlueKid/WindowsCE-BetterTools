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
#include "stdafx.h"
#include "CrosswordSample.h"

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: ToolsAboutDialog
//
// PURPOSE: Dialog proc for the Tools / About dialog.
//
INT CALLBACK ToolsAboutDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                SHMENUBARINFO shmbi;
                shmbi.cbSize = sizeof(shmbi);
                shmbi.hwndParent = hDlg;
                shmbi.dwFlags = SHCMBF_EMPTYBAR;
                SHCreateMenuBar(&shmbi);
                
                SHINITDLGINFO sid;
                sid.dwMask   = SHIDIM_FLAGS;
                sid.dwFlags  = SHIDIF_SIZEDLGFULLSCREEN;
                sid.hDlg     = hDlg;
                SHInitDialog(&sid);
            }
            return TRUE; 

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                EndDialog(hDlg, TRUE);
                return TRUE;
            }

        case WM_SIZE:
            {
                INT nWidth = LOWORD(lParam);
                INT nHeight = HIWORD(lParam);
                HWND hWnd = GetDlgItem(hDlg, IDC_STATIC_1);
                RECT rWnd;
                RECT rDlg;
                GetWindowRect(hWnd, &rWnd);
                GetWindowRect(hDlg, &rDlg);
                OffsetRect(&rWnd, -rDlg.left, -rDlg.top);
                MoveWindow(hWnd, rWnd.left, rWnd.top, nWidth - rWnd.left - SCALEX(8), nHeight - rWnd.top - SCALEY(8), TRUE);
            }
    }
    return FALSE;
}
