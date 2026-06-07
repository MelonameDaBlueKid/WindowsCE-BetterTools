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
    }
    return FALSE;
}
