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
// FUNCTION: ToolsOptionsDialog2
//
// PURPOSE: Draws the font picker tab of the Tools Option dialog.
//
LRESULT CALLBACK ToolsOptionsDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                HWND hWnd = GetDlgItem(hDlg, IDC_LIST1);
                RECT r;
                GetWindowRect(hWnd, &r);
                
                LVCOLUMN lvColumn;
                lvColumn.mask = LVCF_SUBITEM | LVCF_WIDTH;
                lvColumn.cx = r.right - r.left - 15;
                lvColumn.fmt = LVCFMT_LEFT;
                lvColumn.iSubItem = 0;
                ListView_InsertColumn(hWnd, 0, &lvColumn);

                LVITEM lvItem;
                lvItem.mask = 0; // LVIF_TEXT;
                lvItem.iSubItem = 0;
                for (lvItem.iItem = 0; lvItem.iItem < 15; lvItem.iItem++)
                {
                    ListView_InsertItem(hWnd, &lvItem);
                }
                return TRUE;
            }

        case WM_DRAWITEM:
            {
                LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;

                //
                // Calculate the font face and size from the item ID.
                //
                LOGFONT lf;
                memset(&lf, 0, sizeof(lf));
                switch(pDIS->itemID / 5)
                {
                    case 0: wcscpy(lf.lfFaceName, L"Courier New"); break;
                    case 1: wcscpy(lf.lfFaceName, L"Frutiger Linotype"); break;
                    case 2: wcscpy(lf.lfFaceName, L"Tahoma"); break;
                }
                int nFontSize = 8 + 2 * (pDIS->itemID % 5);
                lf.lfHeight = -nFontSize * GetDeviceCaps(pDIS->hDC, LOGPIXELSY) / 72;
                lf.lfWeight = FW_NORMAL;
                HFONT hFont = CreateFontIndirect(&lf);

                //
                // Draw the item.
                //
                WCHAR szBuffer[80];
                wsprintf(szBuffer, L"%s %d", lf.lfFaceName, nFontSize);
                HBRUSH hBrush = CreateSolidBrush((pDIS->itemState & ODS_SELECTED)?
                    RGB(128, 128, 255):
                    RGB(255, 255, 255));
                FillRect(pDIS->hDC, &pDIS->rcItem, hBrush);
                HFONT hOldFont = (HFONT)SelectObject(pDIS->hDC, hFont);
                DrawText(pDIS->hDC, szBuffer, -1, &pDIS->rcItem, DT_CENTER | DT_VCENTER);
                SelectObject(pDIS->hDC, hOldFont);
                DeleteObject(hFont);
                DeleteObject(hBrush);
                return TRUE;
            }

        case WM_MEASUREITEM:
            {
                LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
                lpmis->itemHeight = 40;
                return TRUE;
            }

        case WM_SIZE:
            {
                DRA::RelayoutDialog(g_hInst, hDlg, InWideMode() ?
                    MAKEINTRESOURCE(IDD_TOOLS_OPTIONS_2_WIDE) :
                    MAKEINTRESOURCE(IDD_TOOLS_OPTIONS_2));
            }
    }
    return FALSE;
}
