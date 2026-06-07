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

#ifndef __SYMMENU_H__
#define __SYMMENU_H__

class CSymbolMenu
{
private:
    HWND m_hwnd;              // Window
    HWND m_hwndMenuBar;       // Menu bar window
    HINSTANCE m_hinst;        // DLL/App instance handle
    HFONT m_hBoldFont;        // Bold font
    BOOL m_fUseBoldFont;      // Use bold font?
    int m_cItems;             // Number of symbols
    LPTSTR m_pszItems;        // Symbols 
    int m_cRows;              // Number of Rows                
    int m_cCols;              // Number of Columns
    int m_nCurSel;            // Current selection
    int m_cxItem;             // Width of each menu item
    int m_cyItem;             // Height of each menu item
    BOOL m_fEndMenu : 1;      // Has menu closed?

private:
    void OnCreate(HWND hwnd);
    void OnPaint();
    void OnKeyDown(UINT nVKey);
    void OnCommand(UINT uID);
    void OnDestroy();
    void OnActivate(WPARAM wparam);
    void Close(BOOL fSelect);
    void DrawMenuItem(PAINTSTRUCT *pps, int nItem);
    void GetMenuItemRect(int nItem, RECT *prc);
    void GetMenuItemRangeFromRect(RECT *prc, int *pnMinItem, int *pnMaxItem);
    void ChangeSelection(UINT nVKey);

public:
    CSymbolMenu(HINSTANCE hinst);
    int Run(int cRows, int cCols, TCHAR* pszItems, TCHAR* pszTitle);

    static LRESULT CALLBACK _MenuWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
    LRESULT MenuWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
};

BOOL RegisterSymbolMenuClass(HINSTANCE hinst);

#endif //__SYMMENU_H__
