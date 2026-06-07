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
// FUNCTION: ToolsOptionsDialog1
//
// PURPOSE: Dialog proc for the background/puzzle tab of the Tools/Option 
//      dialog.
//
LRESULT CALLBACK ToolsOptionsDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                HWND hWnd = GetDlgItem(hDlg, IDC_LIST1);
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)_T("Puzzle number 1"));
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)_T("Puzzle number 2"));
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)_T("Puzzle number 3"));
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)_T("Puzzle number 4"));
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)_T("Puzzle number 5"));
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)_T("Puzzle number 6"));

                hWnd = GetDlgItem(hDlg, IDC_TAB1);
                TCITEM tcitem;
                tcitem.mask = TCIF_TEXT;
                tcitem.pszText = _T("Mosaic");
                TabCtrl_InsertItem(hWnd, 0, &tcitem);
                tcitem.pszText = _T("Flowers");
                TabCtrl_InsertItem(hWnd, 1, &tcitem);
                tcitem.pszText = _T("Bricks");
                TabCtrl_InsertItem(hWnd, 2, &tcitem);

                HBITMAP hBMP = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND_1));
                SendDlgItemMessage(hDlg, IDC_PREVIEW, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBMP);

                SHMENUBARINFO shmbi;
                shmbi.cbSize = sizeof(shmbi);
                shmbi.hwndParent = hDlg;
                shmbi.dwFlags = SHCMBF_EMPTYBAR;
                SHCreateMenuBar(&shmbi);
            }
            return TRUE; 

        case WM_NOTIFY:
            {
                LPNMHDR pHDR = (LPNMHDR)lParam;
                
                if (pHDR->code == TCN_SELCHANGE)
                {
                    HWND hwndPreview = GetDlgItem(hDlg, IDC_PREVIEW);
                    HBITMAP hBMP = (HBITMAP)SendMessage(hwndPreview, STM_GETIMAGE, IMAGE_BITMAP, 0);
                    DeleteObject(hBMP);
                    switch(TabCtrl_GetCurSel(pHDR->hwndFrom))
                    {
                        case 0: 
                            hBMP = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND_1)); 
                            break;
                        case 1: 
                            hBMP = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND_2)); 
                            break;
                        case 2: 
                            hBMP = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND_3)); 
                            break;
                    }
                    SendMessage(hwndPreview, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBMP);
                }
            }
            return TRUE;
    
        case WM_SIZE:
            {
                DRA::RelayoutDialog(g_hInst, hDlg, InWideMode() ?
                    MAKEINTRESOURCE(IDD_TOOLS_OPTIONS_1_WIDE) :
                    MAKEINTRESOURCE(IDD_TOOLS_OPTIONS_1));
            }
    }
    return FALSE;
}
