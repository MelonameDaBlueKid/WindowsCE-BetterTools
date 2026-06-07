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
#include <commctrl.h>
#include "resource.h"



#define ARRAYSIZE(a)   (sizeof(a)/sizeof(*a))

const TCHAR* g_szAppWndClass = TEXT("VirtListViewApp");
HINSTANCE g_hInst;
HWND g_hwndListView;
int g_cItems;
TCHAR g_szColumn0Format[30];
TCHAR g_szColumnNFormat[30];
int g_nMenuHeight;

/****************************************************************************

   ActivatePreviousInstance

  ****************************************************************************/
HRESULT ActivatePreviousInstance(
    const TCHAR* pszClass,
    const TCHAR* pszTitle,
    BOOL* pfActivated
    )
{
    HRESULT hr = S_OK;
    int cTries;
    HANDLE hMutex = NULL;

    *pfActivated = FALSE;
    cTries = 5;
    while(cTries > 0)
    {
        hMutex = CreateMutex(NULL, FALSE, pszClass); // NOTE: We don't want to own the object.
        if(NULL == hMutex)
        {
            // Something bad happened, fail.
            hr = E_FAIL;
            goto Exit;
        }

        if(GetLastError() == ERROR_ALREADY_EXISTS)
        {
            HWND hwnd;

            CloseHandle(hMutex);
            hMutex = NULL;

            // There is already an instance of this app
            // running.  Try to bring it to the foreground.

            hwnd = FindWindow(pszClass, pszTitle);
            if(NULL == hwnd)
            {
                // It's possible that the other window is in the process of being created...
                Sleep(500);
                hwnd = FindWindow(pszClass, pszTitle);
            }

            if(NULL != hwnd)
            {
                // Set the previous instance as the foreground window

                // The "| 0x01" in the code below activates
                // the correct owned window of the
                // previous instance's main window.
                SetForegroundWindow((HWND) (((ULONG) hwnd) | 0x01));

                // We are done.
                *pfActivated = TRUE;
                break;
            }

            // It's possible that the instance we found isn't coming up,
            // but rather is going down.  Try again.
            cTries--;
        }
        else
        {
            // We were the first one to create the mutex
            // so that makes us the main instance.  'leak'
            // the mutex in this function so it gets cleaned
            // up by the OS when this instance exits.
            break;
        }
    }

    if(cTries <= 0)
    {
        // Someone else owns the mutex but we cannot find
        // their main window to activate.
        hr = E_FAIL;
        goto Exit;
    }

Exit:
    return(hr);
}


/**************************************************************************************

   FormatMessageHelp

    Variants of printf should be avoided as they don't allow re-ordering of parameters.
    This can be important when an application is required to work in multiple languages
    without code changes.

 **************************************************************************************/
DWORD FormatMessageHelp(
    TCHAR* pszOut,
    UINT cchOut,
    const TCHAR* pszFormat,
    ...
    )
{
    va_list marker;
    DWORD dwRet;

    va_start(marker, pszFormat);
    dwRet = FormatMessage(FORMAT_MESSAGE_FROM_STRING,
            pszFormat, 0, 0, pszOut, cchOut, &marker);
    va_end(marker);
    return dwRet;
}


/**************************************************************************************

   FormattedMessageBox

 **************************************************************************************/
int FormattedMessageBox(
    HWND hwnd,
    UINT uType,
    HINSTANCE hInst,
    UINT idsCaption,
    UINT idsFormat,
    ...
    )
{
    va_list marker;
    DWORD dwRet;
    // If these buffers are too small, you will get truncation
    TCHAR szCaption[100];
    TCHAR szFormat[200];
    TCHAR szText[ARRAYSIZE(szFormat) + 100];

    if(0 == LoadString(hInst, idsCaption, szCaption, ARRAYSIZE(szCaption)) ||
       0 == LoadString(hInst, idsFormat, szFormat, ARRAYSIZE(szFormat)))
    {
        // Couldn't load a needed string.
        return(0);
    }

    va_start(marker, idsFormat);
    dwRet = FormatMessage(FORMAT_MESSAGE_FROM_STRING,
            szFormat, 0, 0, szText, ARRAYSIZE(szText), &marker);
    va_end(marker);
    if(0 == dwRet)
    {
        // Something bad happened in FormatMessage.
        return(0);
    }

    return(MessageBox(hwnd, szText, szCaption, uType));

}

/**************************************************************************************

   SetVirtualItemCount

 **************************************************************************************/
void SetVirtualItemCount(
    int cItems
    )
{
    g_cItems = cItems;
    ListView_SetItemCount(g_hwndListView, cItems);
}

/**************************************************************************************

   OnCreate

 **************************************************************************************/
LRESULT OnCreate(
    HWND hwnd,
    CREATESTRUCT* lParam
    )
{
    RECT rcClient;
    HICON hIcon;
    HIMAGELIST himlSmall;
    int rgcxCols[3];
    int iColumn;

    //
    // create the menu bar
    //
    SHMENUBARINFO mbi;
    ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
    mbi.cbSize = sizeof(SHMENUBARINFO);
    mbi.hwndParent = hwnd;
    mbi.nToolBarId = IDM_MAIN_MENU;
    mbi.hInstRes = g_hInst;
    if(!SHCreateMenuBar(&mbi))
    {
        // Couldn't create the menu bar.  Fail creation of the window.
        goto Error;
    }

    RECT rect;
    //Set menu height
    GetWindowRect(mbi.hwndMB, &rect);
    g_nMenuHeight = rect.bottom - rect.top;

    //
    // Load some random strings needed later.
    //
    // helpful hint - see documentation of LoadString on how
    // to load strings without needing to copy them to a
    // buffer.
    if(0 == LoadString(g_hInst, IDS_COLUMN0FORMAT, g_szColumn0Format, ARRAYSIZE(g_szColumn0Format)) ||
       0 == LoadString(g_hInst, IDS_COLUMNNFORMAT, g_szColumnNFormat, ARRAYSIZE(g_szColumnNFormat)))
    {
        // Couldn't load a needed string.
        goto Error;
    }

    //
    // create the ListView control
    //

    // On the Smartphone platform you should only use LVS_REPORT.
    // Although the other styles do work, they are not very
    // usable.
    //
    // Avoid column headers unless they are absolutely
    // needed.  They take up a row of the UI that could otherwise
    // be used to display data.
    GetClientRect(hwnd, &rcClient);
    g_hwndListView = CreateWindow(WC_LISTVIEW, NULL,
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_OWNERDATA,
            rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top - g_nMenuHeight,
            hwnd, (HMENU)ID_LISTVIEW, g_hInst,NULL);
    if(!g_hwndListView)
    {
        goto Error;
    }

    // Put the list view in full row select mode
    ListView_SetExtendedListViewStyle(g_hwndListView,
            ListView_GetExtendedListViewStyle(g_hwndListView) | LVS_EX_FULLROWSELECT);

    //create an image list for the ListView
    himlSmall = ImageList_Create(16, 16, ILC_COLOR | ILC_MASK, 0, 0);
    if(NULL == himlSmall)
    {
        goto Error;
    }

    //set up the small image list
    hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON));
    if(NULL == hIcon)
    {
        goto Error;
    }
    if(-1 == ImageList_AddIcon(himlSmall, hIcon))
    {
        goto Error;
    }

    ListView_SetImageList(g_hwndListView, himlSmall, LVSIL_SMALL);

    //
    // Create the columns.
    //

    // column 2 is 35 pixels wide
    rgcxCols[2] = 35;
    // column 1 is 40 pixels wide
    rgcxCols[1] = 40;
    // column 0 is the remaining space left in the control
    rgcxCols[0] = (rcClient.right - rcClient.left) -
            (GetSystemMetrics(SM_CXVSCROLL) + rgcxCols[1] + rgcxCols[2]);
    for(iColumn = 0; iColumn < ARRAYSIZE(rgcxCols); iColumn++)
    {
        LV_COLUMN lvColumn;

        lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_WIDTH;
        lvColumn.fmt = LVCFMT_LEFT;
        lvColumn.cx = rgcxCols[iColumn];

        if(-1 == ListView_InsertColumn(g_hwndListView, iColumn, &lvColumn))
        {
            goto Error;
        }
    }

    //set the number of items in the list
    SetVirtualItemCount(5);

    return(0);
Error:
    return(-1);
}

/****************************************************************************

   OnListViewNotify

  ****************************************************************************/
LRESULT OnListViewNotify(
    HWND hwnd,
    LPARAM lParam
    )
{
    NMHDR* pnmh = (NMHDR*) lParam;
    LRESULT lResult = 0;

    switch(pnmh->code)
    {
        case LVN_GETDISPINFO:
            {
                LV_DISPINFO* pdi = (LV_DISPINFO*)lParam;

                if(0 == pdi->item.iSubItem)
                {
                    if(pdi->item.mask & LVIF_TEXT)
                    {
                        FormatMessageHelp(pdi->item.pszText, pdi->item.cchTextMax,
                            g_szColumn0Format, pdi->item.iItem + 1);
                    }

                    if(pdi->item.mask & LVIF_IMAGE)
                    {
                        pdi->item.iImage = 0;
                    }
                }
                else
                {
                    if(pdi->item.mask & LVIF_TEXT)
                    {
                        FormatMessageHelp(pdi->item.pszText, pdi->item.cchTextMax,
                                g_szColumnNFormat, pdi->item.iItem + 1, pdi->item.iSubItem);
                    }
                }
            }
            break;

        case LVN_ITEMACTIVATE:
            {
                NMLISTVIEW* pnmlv = (NMLISTVIEW*)lParam;
                FormattedMessageBox(hwnd, MB_OK, g_hInst, IDS_MB_CAPTION, IDS_MB_FORMAT, pnmlv->iItem + 1);
            }
            break;

        // Handle this notify if you want to use the number keys to select
        // items in the view (like how the desktop file explorer lets you
        // select files by typing the first few characters of the file name.)
        // This notify is also used then the control is sent an LVM_FINDITEM
        case LVN_ODFINDITEM:
            {
                NMLVFINDITEM* pFindItem = (NMLVFINDITEM*)lParam;
                // Used if you are trying to find an item in the list view
            }
            break;
    }

    return(lResult);
}

/****************************************************************************

   ResizeMainWindow

  ****************************************************************************/

void ResizeMainWindow(HWND hwnd)
{
    RECT rect;

    //Get all workspace the client can use
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, FALSE);

    SIPINFO si = {0};
    si.cbSize = sizeof(si);
    SHSipInfo(SPI_GETSIPINFO, 0, &si, 0);

    //Change rect to be left/top/width/height
    rect.right = rect.right - rect.left;
    rect.bottom = rect.bottom - rect.top - g_nMenuHeight;

    if (SIPF_ON == (si.fdwFlags & SIPF_ON))
    {
        //SIP is shown, make space for it on bottom of screen
        rect.bottom = rect.bottom - (si.rcSipRect.bottom - si.rcSipRect.top);
    }

    //Move main window
    MoveWindow(hwnd, rect.left, rect.top, rect.right, rect.bottom, FALSE);


    //Moving a child window, X & Y relative to parent window
    MoveWindow(g_hwndListView,  0, 0, rect.right, rect.bottom, FALSE);
    //Update after moving - CE MoveWindow assumes bRepaint of MoveWindow is always false
    
}

/****************************************************************************

   MainWndProc

  ****************************************************************************/
LRESULT CALLBACK MainWndProc(
    HWND hwnd,
    UINT uMessage,
    WPARAM wParam,
    LPARAM lParam
    )
{

  long lResult = 0;

    switch(uMessage)
    {
        case WM_CREATE:
            lResult = OnCreate(hwnd, (CREATESTRUCT*)lParam);
            break;

        case WM_NOTIFY:
            if(ID_LISTVIEW == wParam)
                {
                lResult = OnListViewNotify(hwnd, lParam);
                }
            else
                {
                goto DoDefault;
                }
            break;

        case WM_COMMAND:
            switch(GET_WM_COMMAND_ID(wParam, lParam))
            {
                case IDM_5_ITEMS:
                    SetVirtualItemCount(5);
                    break;

                case IDM_5000_ITEMS:
                    SetVirtualItemCount(5000);
                    break;

                case IDM_EXIT:
                    // Note that real applications should not have a quit option.
                    // It should be left to the system to shut them down when
                    // memory is low or a process slot is needed.

                    // This code is in samples to make it easier to try things.
                    DestroyWindow(hwnd);
                    break;

                default:
                    goto DoDefault;
            }
            break;

        case WM_INITMENUPOPUP:
            if(0 == (UINT)LOWORD(lParam))
            {
                // This is menu 0 from IDM_MAIN_MENU
                // Put a check next to the selected
                // item count and uncheck the other
                // item.
                CheckMenuItem((HMENU)wParam, IDM_5_ITEMS,
                            MF_BYCOMMAND | (5 == g_cItems ? MF_CHECKED : MF_UNCHECKED));
                CheckMenuItem((HMENU)wParam, IDM_5000_ITEMS,
                            MF_BYCOMMAND | (5000 == g_cItems ? MF_CHECKED : MF_UNCHECKED));
                lResult = 0;
            }
            else
            {
                goto DoDefault;
            }
            break;
        case WM_SETTINGCHANGE:
            if ((SETTINGCHANGE_RESET == wParam) ||
                (SPI_SETSIPINFO == wParam))
            {
                //Orientation change
                ResizeMainWindow(hwnd);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            {
                DWORD dwFlags = LOWORD(wParam);

                if(dwFlags != WA_INACTIVE)
                {
                    SetFocus(g_hwndListView);
                }
            }
            break;

        DoDefault:
        default:
            lResult = DefWindowProc(hwnd, uMessage, wParam, lParam);
            break;
    }

    return lResult;
}

/*****************************************************************************

  WinMain

  ***************************************************************************/
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow
    )
{
    MSG msg;
    HWND hwnd = NULL;
    BOOL fActivated;
    WNDCLASS wc;
    HWND hwndMain;
    TCHAR szAppTitle[30];

    g_hInst = hInstance;

    if(0 == LoadString(g_hInst, IDS_TITLE, szAppTitle, ARRAYSIZE(szAppTitle)))
    {
        return(0);
    }

    if(FAILED(ActivatePreviousInstance(g_szAppWndClass, szAppTitle, &fActivated)) ||
            fActivated)
    {
        return(0);
    }

    //required to use the common controls
    InitCommonControls();

    // Register our main window's class.
    ZeroMemory(&wc, sizeof(wc));
    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = NULL;
    wc.hInstance = g_hInst;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szAppWndClass;
    if(!RegisterClass(&wc))
    {
        return(0);
    }

    // Create the main window.
    hwndMain = CreateWindow(g_szAppWndClass, szAppTitle,
            WS_CLIPCHILDREN, // Setting this to 0 gives a default style we don't want.  Use a benign style bit instead.
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, g_hInst, NULL );
    if(!hwndMain)
    {
        return(0);
    }

    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    // Pump messages until a PostQuitMessage.
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg);
        DispatchMessage(&msg);
    }
    return(msg.wParam);
}

