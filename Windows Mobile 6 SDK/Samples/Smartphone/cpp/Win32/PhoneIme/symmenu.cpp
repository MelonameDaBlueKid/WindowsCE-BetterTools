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

// SymMenu.cpp : Symbols menu

#include "phoneime.h"
#include <aygshell.h>
#include "symmenu.h"
#include "misc.h"




CSymbolMenu::CSymbolMenu(HINSTANCE hinst)
{
     m_hinst = hinst;
     m_hBoldFont = NULL;
     m_fUseBoldFont = UseBoldFont();
}

// Display menu and return user's selection. Return -1 on
// failure or if user cancelled.
int CSymbolMenu::Run(
    int cRows, // In: Number of rows
    int cCols, // In: Number of columns
    TCHAR* pszItems,  // In: Symbols
    TCHAR* pszTitle   // In: Title of menu window
)
{
    if (!pszItems || cRows <= 0 || cCols <= 0)
    {
        ASSERT(0); // Invalid parameters
        return -1;
    }

    m_cItems = lstrlen(pszItems);
    if (m_cItems == 0 || m_cItems > cRows*cCols)
    {
        ASSERT(0); // Invalid parameter
        return -1;
    }

    m_cRows = cRows;
    m_cCols = cCols;
    m_pszItems = pszItems;

    // Create menu window
    m_hwnd = CreateFullScreenWindow(TEXT("MS_SymMenu"),
                 pszTitle ? pszTitle : TEXT(""),
                 WS_VISIBLE,
                 NULL, NULL, m_hinst, (LPVOID)this);
    if (!m_hwnd)
    {
        DEBUGMSG(1, (TEXT("PHONEIME: Symbol menu creation failed\r\n")));
        return -1;
    }

    m_fEndMenu = FALSE;
    m_nCurSel = 0;

    // Create bold font if allowed
    if (!m_hBoldFont && m_fUseBoldFont)
    {
        HFONT hSysFont = (HFONT)GetStockObject(SYSTEM_FONT);
        if (hSysFont)
        {
            LOGFONT lf;
            GetObject(hSysFont, sizeof(LOGFONT), &lf);

            lf.lfWeight = FW_BOLD;
            m_hBoldFont = CreateFontIndirect(&lf);
        }
    }

    // Wait for user to close menu
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (m_fEndMenu || !IsWindow(m_hwnd))
            goto exit;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
            
    PostQuitMessage(msg.wParam); // Exit because of WM_QUIT. Repost and exit.
    m_nCurSel = -1;

    if (m_hBoldFont)
    {
        DeleteObject(m_hBoldFont);
        m_hBoldFont = NULL;
    }

exit:
    DestroyWindow(m_hwnd);
    return m_nCurSel;
}

// Menu wndproc pre-processor
LRESULT CALLBACK CSymbolMenu::_MenuWndProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wparam, 
    LPARAM lparam
)
{
    CSymbolMenu *psymmenu;

    if (uMsg == WM_CREATE)
    {
        psymmenu = (CSymbolMenu *)(((LPCREATESTRUCT) lparam)->lpCreateParams);
        SetWindowLong(hwnd, GWL_USERDATA, (LONG)psymmenu);
    }
    else
    {
        psymmenu = (CSymbolMenu *) GetWindowLong(hwnd, GWL_USERDATA);
    }

    if (!psymmenu)
        return DefWindowProc(hwnd, uMsg, wparam, lparam);
    else
        return psymmenu->MenuWndProc(hwnd, uMsg, wparam, lparam);
}

// Menu window proc
LRESULT CSymbolMenu::MenuWndProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wparam, 
    LPARAM lparam
)
{
    switch(uMsg)
    {
    case WM_CREATE:
        OnCreate(hwnd);
        break;

    case WM_PAINT:
        OnPaint();
        break;

    case WM_KEYDOWN:
        OnKeyDown((UINT)wparam);
        break;

    case WM_HOTKEY:
        // Close menu when back key is received
        if((HIWORD(lparam) == VK_TBACK) && (LOWORD(lparam) & MOD_KEYUP))
            Close(FALSE);
        break;

    case WM_COMMAND:
        OnCommand(LOWORD(wparam));
        break;

    case WM_DESTROY:
        OnDestroy();
        break;

    case WM_ACTIVATE:
        OnActivate(wparam);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wparam, lparam);
    }

    return 0;
}

// Initialize menu window
void CSymbolMenu::OnCreate(HWND hwnd)
{
    // Create menubar. 
    SHMENUBARINFO smbi = {0};
    smbi.cbSize = sizeof(SHMENUBARINFO);
    smbi.hwndParent = hwnd;
    smbi.nToolBarId = IDR_SYMBOLS_CMDBAR;
    smbi.hInstRes = HINST_RESDLL;
    
    if (!SHCreateMenuBar(&smbi))
    {
        DEBUGMSG(1, (TEXT("PHONEIME: Symbol menu menubar creation failed\r\n")));
        Close(FALSE);
        return;
    }
    m_hwndMenuBar = smbi.hwndMB;

    // Ask menubar to notify parent when user presses Back
    SendMessage(m_hwndMenuBar, SHCMBM_OVERRIDEKEY, VK_TBACK, 
                MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

    // Compute size of each menu item
    RECT rc;
    GetClientRect(hwnd, &rc);
    m_cxItem = (rc.right-rc.left)/m_cRows;
    m_cyItem = (rc.bottom-rc.top)/m_cCols;
}

// Paint menu
void CSymbolMenu::OnPaint()
{
    PAINTSTRUCT ps;
    HFONT       hfontOld = NULL;
    int         nMinItem;
    int         nMaxItem;

    BeginPaint(m_hwnd, &ps);
    if (m_hBoldFont)
    {
        hfontOld = (HFONT)SelectObject(ps.hdc, m_hBoldFont);
    }

    // Do an initial calculation to reduce the number of items
    // we need to worry about.
    GetMenuItemRangeFromRect(&ps.rcPaint, &nMinItem, &nMaxItem);

    for (int n = nMinItem; n <= nMaxItem; n++)
    {
        DrawMenuItem(&ps, n);
    }

    if (hfontOld)
    {
        SelectObject(ps.hdc, hfontOld);
    }
    EndPaint(m_hwnd, &ps);
}

// Draw menuitem
void CSymbolMenu::DrawMenuItem(PAINTSTRUCT *pps, int nItem)
{
    ASSERT(nItem < m_cItems);

    HDC hdc = pps->hdc;
    RECT rc;
    RECT rcIntersect;
    SIZE lSize;
    COLORREF crText = 0;
    COLORREF crBk = 0;
    
    GetMenuItemRect(nItem, &rc);

    // If this item doesn't intersect the clip region,
    // then don't bother drawing it.
    if (!IntersectRect(&rcIntersect, &rc, &pps->rcPaint))
    {
        return;
    }

    if (nItem == m_nCurSel)
    {
        crText = SetTextColor(hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));
        crBk = SetBkColor(hdc, GetSysColor(COLOR_HIGHLIGHT));
    }

    GetTextExtentPoint(hdc, m_pszItems+nItem, 1, &lSize);
    ExtTextOut(hdc, rc.left + (rc.right - rc.left - lSize.cx + 1) / 2,
               rc.top + (rc.bottom - rc.top - lSize.cy) / 2, ETO_OPAQUE, &rc, m_pszItems+nItem, 1, NULL);

    if (nItem == m_nCurSel)
    {
        SetTextColor(hdc, crText);
        SetBkColor(hdc, crBk);
    }
}

// Get menuitem rect
void CSymbolMenu::GetMenuItemRect(int nItem, RECT *prc)
{
    ASSERT(nItem < m_cItems);

    prc->left = (nItem % m_cCols) * m_cxItem;
    prc->top = (nItem / m_cCols) * m_cyItem;
    prc->right = prc->left + m_cxItem;
    prc->bottom = prc->top + m_cyItem;
}

// Get minimum items required for paint
void CSymbolMenu::GetMenuItemRangeFromRect(RECT *prc, int *pnMinItem, int *pnMaxItem)
{
    *pnMinItem = (prc->top / m_cyItem) * m_cCols + (prc->left / m_cxItem); 
    *pnMaxItem = ((prc->bottom - 1) / m_cyItem) * m_cCols + ((prc->right - 1) / m_cxItem);

    if (*pnMaxItem >= m_cItems)
    {
        *pnMaxItem = m_cItems - 1;
    }
}

// Handle key
void CSymbolMenu::OnKeyDown(UINT nVKey)
{
    switch (nVKey)
    {
    case VK_RIGHT:       
    case VK_LEFT:
    case VK_UP:
    case VK_DOWN:
        ChangeSelection(nVKey); // Change selection
        break;

    case VK_RETURN:
        Close(TRUE); // Close menu and return current selection.
        break;

    default:
        break;
    }
}

// Change selection based on arrow key
void CSymbolMenu::ChangeSelection(
    UINT nVKey // In: Arrow key
)
{
    // Compute new selection
    int nOldSel = m_nCurSel;
    int nOffset;
    switch (nVKey)
    {
    case VK_RIGHT:
        // Move right along row. Wrap to beginning of row if necessary.
        nOffset = (m_nCurSel+1) % m_cCols;
        m_nCurSel = (nOldSel/m_cCols) * m_cCols + nOffset;        
        break;

    case VK_LEFT:
        // Move left along row. Wrap to end of row if necessary.
        m_nCurSel--;
        nOffset = (m_nCurSel < 0) ? m_cCols -1 : m_nCurSel % m_cCols;
        m_nCurSel = (nOldSel/m_cCols) * m_cCols + nOffset;
        break;

    case VK_DOWN:
        // Move down along column. Wrap to top of column if necessary.
        m_nCurSel = (m_nCurSel + m_cCols) % (m_cRows*m_cCols);
        break;

    case VK_UP:
        // Move up along column. Wrap to bottom of column if necessary.
        m_nCurSel -= m_cCols;
        if (m_nCurSel < 0)
            m_nCurSel = m_cCols * (m_cRows-1) + (nOldSel % m_cCols);
        break;

    default:
        ASSERT(0); // Only arrow keys are processed
        return;
    }

    // If new selection went beyond number of items, don't
    // change the selection.
    if (m_nCurSel >= m_cItems)
        m_nCurSel = nOldSel;

    if (nOldSel == m_nCurSel)
        return;

    // Redraw selection rectangle
    RECT rc;
    if (nOldSel != -1)
    {
        GetMenuItemRect(nOldSel, &rc);
        InvalidateRect(m_hwnd, &rc, TRUE);
    }
    GetMenuItemRect(m_nCurSel, &rc);
    InvalidateRect(m_hwnd, &rc, TRUE);
    UpdateWindow(m_hwnd);
}

void CSymbolMenu::OnCommand(UINT uID)
{
    switch (uID)
    {
    case IDM_DONE:
        Close(TRUE);
        break;

    case IDM_CANCEL:
        Close(FALSE);
        break;

    default:
        break;
    }
}

void CSymbolMenu::OnDestroy()
{
    DestroyWindow(m_hwndMenuBar);
}

// Handle activation/loss of activation
void CSymbolMenu::OnActivate(
    WPARAM wparam
)
{
    // If menu is not already closing, close menu on loss of activation
    // This will close the menu if another window gains activation.
    if (wparam == WA_INACTIVE && !m_fEndMenu)
    {
        Close(FALSE);
    }
}

// Close menu
void CSymbolMenu::Close(
    BOOL fSelect  // TRUE if user wants to return current selection. FALSE to cancel current selection.
)
{
    if (!fSelect)
        m_nCurSel = -1;

    // Close menu
    m_fEndMenu = TRUE;
    PostMessage(m_hwnd, WM_NULL, 0, 0); // Kick GetMessage out of its wait
}


// Register menu window class
BOOL RegisterSymbolMenuClass(HINSTANCE hinst)
{
    WNDCLASS wc;
    BOOL fRet = FALSE;

    wc.style          = 0;
    wc.lpfnWndProc    = CSymbolMenu::_MenuWndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0; 
    wc.hInstance      = hinst;
    wc.hCursor        = NULL;
    wc.hIcon          = NULL;
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = TEXT("MS_SymMenu");
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);

    if (RegisterClass(&wc))
    {
        fRet = TRUE;
    }
    else
    {
        // If the process has already registered the class, succeed.
        if (ERROR_CLASS_ALREADY_EXISTS == GetLastError())
        {
            fRet = TRUE; 
        }
    }

    return fRet;
}
