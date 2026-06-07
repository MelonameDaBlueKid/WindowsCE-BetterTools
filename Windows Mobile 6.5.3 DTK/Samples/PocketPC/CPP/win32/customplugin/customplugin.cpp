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
//
// Copyright (c) 2004 Microsoft Corporation
//
// Module Name:
//
//      customPlugin.cpp
//
// Abstract:
//
//      A sample of custom plugin
//
// Author:
//      
// TODO: 
//

#include "stdafx.h"
#include <todaycmn.h>
#include "resource.h"

#ifndef WS_EX_TRANSPARENT
#define WS_EX_TRANSPARENT 0x00000020L
#endif

HINSTANCE g_hinstDLL;

#define PLUGIN_SELECTED     0x00000001
#define PLUGIN_TEXTRESIZE   0x00000002

#define TEXT_MARGIN  10

TCHAR g_szPluginClass[] = TEXT("SamplePlugin");
DWORD g_cyItemHeight;
DWORD g_cyInitItemHeight;
uint g_uMetricChangeMsg2;

void InitPluginGlobals(void)
{
    // Plug-in height
    g_uMetricChangeMsg2 = RegisterWindowMessage(SH_UIMETRIC_CHANGE);

    g_cyItemHeight = SCALEY(20);
    g_cyInitItemHeight = g_cyItemHeight;
}

void SetItemState(HWND hwnd, LONG lState, BOOL fSet)
{
    LONG lData = GetWindowLong(hwnd, GWL_USERDATA);
    if (fSet)
    {
        lData |= lState;
    }
    else
    {
        lData &= ~lState;
    }
    SetWindowLong(hwnd, GWL_USERDATA, lData);
}

BOOL IsItemState(HWND hwnd, LONG lState)
{
    return ((GetWindowLong(hwnd, GWL_USERDATA) & lState) == lState);
}

void FillRectClr(HDC hdc, LPRECT prc, COLORREF clr)
{
    COLORREF clrSave = SetBkColor(hdc, clr);
    ExtTextOut(hdc,0,0,ETO_OPAQUE,prc,NULL,0,NULL);
    SetBkColor(hdc, clrSave);
}

void Plugin_OnPaint(HWND hwnd, HDC hdc)
{
    HWND    hwndParent = GetParent(hwnd);
    RECT    rcDraw;
    TODAYDRAWWATERMARKINFO dwi = {0};
    COLORREF crText, crHighlightedText, crOld;
    int nBkMode;

    ASSERT(NULL != hdc);

    GetClientRect(hwnd, &rcDraw);
    
    dwi.rc = rcDraw;
    dwi.hwnd = hwnd;
    dwi.hdc = hdc;

    if (IsItemState(hwnd, PLUGIN_SELECTED))
    {
        COLORREF crHighlight;

        crHighlight = SendMessage(hwndParent, TODAYM_GETCOLOR, TODAYCOLOR_HIGHLIGHT, 0);
        
        nBkMode = SetBkMode(hdc, OPAQUE);
        FillRectClr(hdc, &rcDraw, crHighlight);
        SetBkMode(hdc, nBkMode);
    }
    else
    {
        if (!SendMessage(hwndParent, TODAYM_DRAWWATERMARK, 0, (LPARAM) &dwi))
        {
            FillRectClr(hdc, &rcDraw, GetSysColor(COLOR_WINDOW));
        }
    }
    
    /* display text for no messages */
    LPCTSTR pszText = (LPCTSTR) LoadString(g_hinstDLL, IDS_PLUGIN_TEXT, NULL, 0);

    rcDraw.left += TEXT_MARGIN;
    rcDraw.right -= TEXT_MARGIN;

    crHighlightedText = SendMessage(hwndParent, TODAYM_GETCOLOR, TODAYCOLOR_HIGHLIGHTEDTEXT, 0);
    crText = SendMessage(hwndParent, TODAYM_GETCOLOR, TODAYCOLOR_TEXT, 0);

    nBkMode = SetBkMode(hdc, TRANSPARENT);
    crOld = SetTextColor(hdc, IsItemState(hwnd, PLUGIN_SELECTED) ? crHighlightedText : crText);
    DrawText(hdc, pszText, -1, &rcDraw, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
    crText = SetTextColor(hdc, crOld);
    SetBkMode(hdc, nBkMode);

    return;
}

BOOL Plugin_OnQueryRefreshCache(HWND hwnd, TODAYLISTITEM* ptli)
{
    // Hmm.... no ptli, that means we are probably refreshing ourselves, and don't
    // need to return antyhing.
    if(!ptli)
    {
        return FALSE;
    }

    if(ptli->cyp != g_cyItemHeight)
    {
        // If the heights are not equal, return true so we tell the Today screen our
        // height has changed.
        OutputDebugString(TEXT("***first time...***"));
        ptli->cyp = g_cyItemHeight;
        InvalidateRect(hwnd, NULL, FALSE);
        return TRUE;
    }
    else if (IsItemState(hwnd, PLUGIN_TEXTRESIZE))
    {
        if (ptli->cyp > g_cyInitItemHeight)
        {
            OutputDebugString(TEXT("***shrinking...***"));
            g_cyItemHeight = g_cyInitItemHeight;
            ptli->cyp = g_cyItemHeight;
        }
        else
        {
            OutputDebugString(TEXT("***growing...***"));
            g_cyItemHeight = g_cyInitItemHeight + SCALEY(20);
            ptli->cyp = g_cyItemHeight;
        }

        SetItemState(hwnd, PLUGIN_TEXTRESIZE, FALSE);
        InvalidateRect(hwnd, NULL, FALSE);
        return TRUE;        
    }
    else
    {
        return FALSE;
    }
}

BOOL Plugin_OnReceivedSelection(HWND hwnd, UINT vKey)
{
    BOOL fRet = FALSE;

    switch(vKey)
    {
        case VK_UP:
        case VK_DOWN:
            SetItemState(hwnd, PLUGIN_SELECTED, TRUE);
            fRet = TRUE;
            break;

        case 0:
            // We got it via the tap, we set our selection in our handling of WM_LBUTTON*
            break;
            
        default:
            ASSERT(0);
    }
    return fRet;
}

void Plugin_OnLostSelection(HWND hwnd)
{
    SetItemState(hwnd, PLUGIN_SELECTED, FALSE);
    InvalidateRect(hwnd, NULL, FALSE);
}

LRESULT PluginWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRet = 0;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            SetWindowLong(hwnd, GWL_USERDATA, 0);
            InitPluginGlobals();
            break;
        }
        
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hwnd, &ps);
            Plugin_OnPaint(hwnd, hDC);
            EndPaint(hwnd, &ps);
            break;            
        }

        case WM_LBUTTONDOWN:
            PostMessage(GetParent(hwnd), TODAYM_TOOKSELECTION, (WPARAM)hwnd, 0);
            SetItemState(hwnd, PLUGIN_SELECTED, TRUE);
            break;

        case WM_ERASEBKGND:
            lRet = 1;
            break;

        case WM_TODAYCUSTOM_QUERYREFRESHCACHE:
            lRet = Plugin_OnQueryRefreshCache(hwnd, (TODAYLISTITEM*) wParam);
            break;

        case WM_TODAYCUSTOM_RECEIVEDSELECTION:
            lRet = Plugin_OnReceivedSelection(hwnd, wParam);
            break;

        case WM_TODAYCUSTOM_LOSTSELECTION:
            Plugin_OnLostSelection(hwnd);
            break;
            
        case WM_TODAYCUSTOM_CLEARCACHE:
        case WM_TODAYCUSTOM_USERNAVIGATION:
        case WM_TODAYCUSTOM_ACTION:
        default:
            if (uMsg == g_uMetricChangeMsg2)
            {
                //user changed the Text Size.  we should resize this plugin in the next WM_TODAYCUSTOM_QUERYREFRESHCACHE
                SetItemState(hwnd, PLUGIN_TEXTRESIZE, TRUE);
            }
            lRet = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return lRet;
}


HWND InitializeCustomItem(TODAYLISTITEM * ptli, HWND hwndParent)
{
    HWND hwnd;
    WNDCLASS wc;

    if (!GetClassInfo(g_hinstDLL, g_szPluginClass, &wc))
    {
        // Class is not registered yet. Register now...
        memset(&wc, 0, sizeof(wc));

        wc.style         = 0;                  
        wc.lpfnWndProc   = (WNDPROC)PluginWndProc;
        wc.hInstance     = g_hinstDLL;
        wc.hIcon         = 0;
        wc.hCursor       = 0;
        wc.hbrBackground = NULL;
        wc.lpszClassName = g_szPluginClass;

        // register our window
        if(!RegisterClass(&wc))
        { 
            return NULL;
        }
    }

    //create a new window
    hwnd = CreateWindowEx(WS_EX_TRANSPARENT,
                          g_szPluginClass, 
                          g_szPluginClass,
                          WS_CHILD,   
                          0,0,0,0,
                          hwndParent, NULL, g_hinstDLL, NULL);

    //display the window
    if(ptli->fEnabled)
    {
        ShowWindow (hwnd, SW_SHOW);
    }

    return hwnd;

}


EXTERN_C
BOOL __stdcall DllMain(void * hmod, DWORD dwReason, void* lpvReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            g_hinstDLL = (HINSTANCE)hmod;
            break;
        case DLL_PROCESS_DETACH:
            UnregisterClass(g_szPluginClass, g_hinstDLL);
            g_hinstDLL = NULL;
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
   }

    return TRUE;
}
