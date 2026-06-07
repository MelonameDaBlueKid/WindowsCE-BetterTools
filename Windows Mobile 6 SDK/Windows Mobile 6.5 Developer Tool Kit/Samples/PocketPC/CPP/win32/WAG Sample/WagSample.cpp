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
#include "WagSample.h"
#include <gesture.h>
#include <GesturePhysicsEngine.h>
#include <WindowAutoGesture.h>
#include <stdlib.h>

#define MAX_LOADSTRING 100

// message used from WAGI
#define WM_PRIVATEANIMATEMSG        WM_USER+101
#define WM_PRIVATESTATUSMSG         WM_USER+102

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)  (sizeof(a)/sizeof(a[0]))
#endif

namespace 
{
// Global Variables:
HPHYSICSENGINE   g_hPhysicsEngine = NULL;
HBITMAP          g_hBmp = NULL;
HDC              g_hMemDC = 0;
HGDIOBJ          g_hOldBmp = 0;
int              g_nXPos = 0;
int              g_nYPos = 0;
int              g_nMaxXExtent = 0;
int              g_nMaxYExtent = 0;
UINT             g_uTimerId = 0;

int              g_nBmpWidth = 0;
int              g_nBmpHeight = 0;
int              g_nVWhiteSpace = 0;
int              g_nHWhiteSpace = 0;

HINSTANCE        g_hInst;           // current instance
HWND             g_hWndMenuBar;     // menu bar handle

bool      g_fAnimating = false;
bool      g_fAllowPAN = true;
bool      g_fAllowSCROLL = true;
bool      g_fLockAxis = false;
bool      g_fUseWMSCroll = false;
bool      g_fHScrollable = true;
bool      g_fVScrollable = true;
int       g_nHorizExtent = 100;
int       g_nVertExtent = 100;
int       g_nVertItemSize = 1;
int       g_nHorizItemSize = 1;
};

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE, LPTSTR);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ConfigWndProc(HWND, UINT, WPARAM, LPARAM);

void DoPaint(HWND hWnd);
void RecalcScrollBarRanges(HWND hWnd);
void ConfigureWAG(HWND hWnd);
void InitConfigDialog(HWND hDlg);
BOOL SaveConfigDialogState(HWND hDlg);

//
//  FUNCTION WinMain
//
//  PURPOSE: Entry point of the application.
//
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE /*hPrevInstance*/,
                   LPTSTR    /*lpCmdLine*/,
                   int       nCmdShow)
{
    MSG msg;

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow)) 
    {
        return FALSE;
    }

    HACCEL hAccelTable;
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WAG_SAMPLE));

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
    WNDCLASS wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAG_SAMPLE));
    wc.hCursor       = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = 0;
    wc.lpszClassName = szWindowClass;

    return RegisterClass(&wc);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    TCHAR szTitle[MAX_LOADSTRING];          // title bar text
    TCHAR szWindowClass[MAX_LOADSTRING];    // main window class name

    g_hInst = hInstance; // Store instance handle in our global variable

    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the device specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_WAG_SAMPLE, szWindowClass, MAX_LOADSTRING);

    //If it is already running, then focus on the window, and exit
    hWnd = FindWindow(szWindowClass, szTitle);
    if (hWnd) 
    {
        // set focus to foremost child window
        // The "| 0x00000001" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        return 0;
    } 

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
        return FALSE;
    }

    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE |WS_VSCROLL | WS_HSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    // When the main window is created using CW_USEDEFAULT the height of the menubar (if one
    // is created is not taken into account). So we resize the window after creating it
    // if a menubar is present
    if (g_hWndMenuBar)
    {
        RECT rc;
        RECT rcMenuBar;

        GetWindowRect(hWnd, &rc);
        GetWindowRect(g_hWndMenuBar, &rcMenuBar);
        rc.bottom -= (rcMenuBar.bottom - rcMenuBar.top);
        
        MoveWindow(hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, FALSE);
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

//
//   FUNCTION: ReleaseResources()
//
//   PURPOSE: Frees all resources used by application.
//
void ReleaseResources()
{
    // release the offscreen DC
    if (0 != g_hMemDC)
    {
        SelectObject(g_hMemDC, g_hOldBmp);
        DeleteDC(g_hMemDC);
        g_hMemDC = NULL;
    }

    // relase the loaded BMP (if any)
    if (g_hBmp)
    {
        DeleteObject(g_hBmp);
        g_hBmp = NULL;
    }
}

//
//   FUNCTION: PrepareImage()
//
//   PURPOSE: Loads an image from resources and calculates scrolling area.
//
BOOL PrepareImage(HWND hWnd)
{
    HDC hDC = NULL;
    BITMAP bmpInfo = {0};

    // Load the image
    g_hBmp = (HBITMAP)LoadImage( g_hInst,
                                 MAKEINTRESOURCE(IDB_DEFAULT_IMAGE),
                                 IMAGE_BITMAP,
                                 0,0,0);

    if (NULL == g_hBmp)
    {
        MessageBox(hWnd, TEXT("Load Error"), TEXT("Failed to open main image"), MB_OK);
        return FALSE;
    }

    // Now get the compatible DC for blt'ing
    hDC = GetDC(hWnd);
    g_hMemDC = CreateCompatibleDC(hDC);
    GetObject( g_hBmp, sizeof(bmpInfo), &bmpInfo);
    g_nBmpWidth = bmpInfo.bmWidth;
    g_nBmpHeight = bmpInfo.bmHeight;
    ReleaseDC(hWnd, hDC);
    g_hOldBmp = SelectObject(g_hMemDC, g_hBmp);

    // Now set the scroll range
    RecalcScrollBarRanges(hWnd);
    ConfigureWAG(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;

    static SHACTIVATEINFO s_sai;
    
    switch (message) 
    {
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            // Parse the menu selections:
            switch (wmId)
            {
                case IDM_HELP_ABOUT:
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutWndProc);
                    break;
                case ID_OPTIONS_CONFIGUREWAG:
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_WAG_CONFIG), hWnd, ConfigWndProc);
                    break;
                case IDM_OK:
                    SendMessage (hWnd, WM_CLOSE, 0, 0);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_CREATE:
            SHMENUBARINFO mbi;

            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hWnd;
            mbi.nToolBarId = IDR_MENU;
            mbi.hInstRes   = g_hInst;

            if (!SHCreateMenuBar(&mbi)) 
            {
                g_hWndMenuBar = NULL;
            }
            else
            {
                g_hWndMenuBar = mbi.hwndMB;
            }

            // Initialize the shell activate info structure
            memset(&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
            if (!PrepareImage(hWnd))
            {
                return -1;
            }
            break;

        case WM_ERASEBKGND:
            return TRUE;

        case WM_PAINT:
            DoPaint(hWnd);
            break;

        case WM_DESTROY:
            ReleaseResources();
            CommandBar_Destroy(g_hWndMenuBar);
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            // Notify shell of our activate message
            SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
            break;
        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
            break;

        case WM_SIZE:
            RecalcScrollBarRanges(hWnd);
            break;

        case WM_VSCROLL:
        case WM_HSCROLL:
        {
            int increment = (WM_VSCROLL==message) ? g_nVertItemSize : g_nHorizItemSize;
            int nBar = (WM_VSCROLL==message) ? SB_VERT:SB_HORZ;
            int * pnVal = (WM_VSCROLL==message) ? &g_nYPos:&g_nXPos;
            int nVal = (*pnVal)/increment;
            int nMax = 0;
            int nDelta = 0;

            SCROLLINFO sbi = {sizeof(SCROLLINFO)};
            sbi.fMask  = SIF_ALL;
            GetScrollInfo(hWnd, nBar, &sbi);
            int pos = sbi.nPos;
            nMax = sbi.nMax - (sbi.nPage -1);   // nPage should never be zero

            switch (LOWORD(wParam))
            {
                case SB_BOTTOM:
                    nVal = nMax;
                    break;
                case SB_LINEDOWN:
                    nVal = pos + 1;
                    break;

                case SB_LINEUP:
                    nVal = pos - 1;
                    break;

                case SB_PAGEDOWN:
                    nVal = pos + 5;
                    break;

                case SB_PAGEUP:
                    nVal = pos - 5;
                    break;

                case SB_TOP:
                    nVal = 0;
                    break;

                case SB_THUMBTRACK:
                    nVal = sbi.nTrackPos;
                    break;
                case SB_THUMBPOSITION:
                case SB_ENDSCROLL:
                default:
                    break;
            }

            nVal = max(nVal, 0);
            nVal = min(nVal, nMax);

            nDelta = *pnVal;
            *pnVal = nVal * increment;
            nDelta -= *pnVal;

            if (nVal != pos)
            {
                RECT rcClient;
                SetScrollPos(hWnd, nBar, nVal, TRUE);

                GetClientRect(hWnd, &rcClient);
                int dx = (WM_VSCROLL==message) ? 0 : nDelta;
                int dy = (WM_VSCROLL==message) ? nDelta : 0;
                ScrollWindowEx(hWnd, dx, dy, &rcClient, &rcClient, NULL, NULL, SW_INVALIDATE);
                UpdateWindow(hWnd);
            }
        }
        break;

        // Animation message from the gesture. 
        case WM_PRIVATEANIMATEMSG:
            {
                RECT rcClient;
                ANIMATEMESSAGEINFO ami = {sizeof(ANIMATEMESSAGEINFO) };

                // Grab the information 
                if (!TKGetAnimateMessageInfo(hWnd, wParam, lParam, &ami))
                {
                    // Failed - I cant get a location so doing nothing here:
                    break;
                }

                GetClientRect(hWnd, &rcClient);
                ScrollWindowEx(hWnd, 
                    g_nXPos - ami.nHPixelPosition, 
                    g_nYPos - ami.nVPixelPosition, 
                    &rcClient, 
                    &rcClient, 
                    NULL, NULL, SW_INVALIDATE);

                // get the pixel positions
                g_nXPos = ami.nHPixelPosition;
                g_nYPos = ami.nVPixelPosition;

                // Set the scrollbar positions
                SetScrollPos(hWnd, SB_VERT, g_nYPos / g_nVertItemSize, TRUE);
                SetScrollPos(hWnd, SB_HORZ, g_nXPos / g_nHorizItemSize, TRUE);
                    
                UpdateWindow(hWnd);
            }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK AboutWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM /*lParam*/)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                // Create a Done button and size it.  
                SHINITDLGINFO shidi;
                shidi.dwMask = SHIDIM_FLAGS;
                shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
                shidi.hDlg = hDlg;
                SHInitDialog(&shidi);
            }
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hDlg, message);
            return TRUE;

    }
    return (INT_PTR)FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK ConfigWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM /*lParam*/)
{
    switch (message)
    {
        case WM_INITDIALOG:
            InitConfigDialog(hDlg);
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                if (IDYES == MessageBox(hDlg, _T("Save the changes?"), _T("Configuration"), MB_ICONQUESTION | MB_YESNO))
                {
                    if(!SaveConfigDialogState(hDlg))
                    {
                        // Error during saving values. Don't close the window yet.
                        return TRUE;
                    }
                }
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hDlg, message);
            return TRUE;

    }
    return (INT_PTR)FALSE;
}

//
//  FUNCTION: DoPaint( HWND hwnd )
//
//  PURPOSE:  Paint the image at the current coordinates
//
void DoPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc;
    hdc = BeginPaint(hWnd, &ps);
    RECT rcClient = {0};
        
    GetClientRect(hWnd, &rcClient);
 

    // just blt the image out using the stored offset
    BitBlt( ps.hdc, 
            ps.rcPaint.left, 
            ps.rcPaint.top,
            ps.rcPaint.right - ps.rcPaint.left, 
            ps.rcPaint.bottom - ps.rcPaint.top, 
            g_hMemDC, 
            g_nXPos + ps.rcPaint.left, 
            g_nYPos + ps.rcPaint.top,
            SRCCOPY);
    // Now blt any extra rounding we need...

    // If the bitmap height is less than the scroll max, 
    // and white might be displayed, then blat it in 
    if ((0 != g_nHWhiteSpace) && 
        g_nXPos > g_nMaxXExtent)
    {
        RECT rc = {
            rcClient.right - (g_nXPos - g_nMaxXExtent),
            g_nYPos < 0 ? abs(g_nYPos) : 0,
            rcClient.right - (g_nXPos - g_nMaxXExtent) + g_nHWhiteSpace,
            rcClient.bottom - (g_nYPos - g_nMaxYExtent)
        };

        if (IntersectRect(&rc, &rc, &ps.rcPaint))
        {
            BitBlt( ps.hdc,
                    rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                    g_hMemDC, 
                    0, 0,
                    WHITENESS);
        }
    }

    if ((0 != g_nVWhiteSpace) && 
        g_nYPos > g_nMaxYExtent)
    {
        RECT rc = {
            g_nXPos < 0 ? abs(g_nXPos) : 0,
            rcClient.bottom - (g_nYPos - g_nMaxYExtent),
            rcClient.right - (g_nXPos - g_nMaxXExtent),
            rcClient.bottom - (g_nYPos - g_nMaxYExtent) + g_nVWhiteSpace
        };

        if (IntersectRect(&rc, &rc, &ps.rcPaint))
        {
            BitBlt( ps.hdc,
                    rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                    g_hMemDC, 
                    0, 0,
                    WHITENESS);
        }
    }

    if (((0 != g_nVWhiteSpace) || (0 != g_nHWhiteSpace) ) && 
        ((g_nYPos > g_nMaxYExtent) || (g_nXPos > g_nMaxXExtent)))
    {
        RECT rc = {
            rcClient.right - (g_nXPos - g_nMaxXExtent),
            rcClient.bottom - (g_nYPos - g_nMaxYExtent),
            rcClient.right - (g_nXPos - g_nMaxXExtent) + g_nHWhiteSpace,
            rcClient.bottom - (g_nYPos - g_nMaxYExtent) + g_nVWhiteSpace
        };

        if (IntersectRect(&rc, &rc, &ps.rcPaint))
        {
            BitBlt( ps.hdc,
                    rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                    g_hMemDC, 
                    0, 0,
                    WHITENESS);
        }
    }

    // Check for any 'black' space
    if (g_nXPos < 0)
    {
        RECT rc = {
            rcClient.left,
            rcClient.top,
            abs(g_nXPos),
            rcClient.bottom
        };

        if (IntersectRect(&rc, &rc, &ps.rcPaint))
        {
            BitBlt( ps.hdc, 
                    rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                    g_hMemDC, 
                    0 , 0,
                    BLACKNESS);
        }
    }

    if (g_nYPos < 0)
    {
        RECT rc = {
            rcClient.left,
            rcClient.top,
            rcClient.right,
            abs(g_nYPos)
        };
        if (IntersectRect(&rc, &rc, &ps.rcPaint))
        {
            BitBlt( ps.hdc,
                    rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                    g_hMemDC,
                    0, 0,
                    BLACKNESS);
        }
    }

    if (g_nXPos > g_nMaxXExtent + g_nHWhiteSpace)
    {
        RECT rc = {
            rcClient.right - (g_nXPos - g_nMaxXExtent) + g_nHWhiteSpace,
            rcClient.top,
            rcClient.right,
            rcClient.bottom
        };

        if (IntersectRect(&rc, &rc, &ps.rcPaint))
        {
            BitBlt( ps.hdc, 
                    rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                    g_hMemDC, 
                    0, 0,
                    BLACKNESS);
        }
    }

    if (g_nYPos > g_nMaxYExtent + g_nVWhiteSpace)
    {
        RECT rc = {
            rcClient.left,
            rcClient.bottom - (g_nYPos - g_nMaxYExtent) + g_nVWhiteSpace,
            rcClient.right,
            rcClient.bottom
        };

        if (IntersectRect(&rc, &rc, &ps.rcPaint))
        {
            BitBlt( ps.hdc,
                    rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
                    g_hMemDC, 
                    0, 0,
                    BLACKNESS);
        }
    }
    EndPaint(hWnd, &ps);
}

//
//  FUNCTION: RecalcScrollBarRanges(HWND hWnd)
//
//  PURPOSE:  calculate and set the scollbar range based on the item height.
//
void RecalcScrollBarRanges(HWND hWnd)
{
// Now setup the scroll ranges as appropriate
    SCROLLINFO sbi = {sizeof(SCROLLINFO)};
    RECT rcClient;
    DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
    GetClientRect(hWnd, &rcClient);

    rcClient.right -= (dwStyle | WS_HSCROLL) ? 0 : GetSystemMetrics(SM_CXVSCROLL);
    rcClient.bottom -= (dwStyle | WS_VSCROLL) ? 0 : GetSystemMetrics(SM_CYHSCROLL);
    g_nMaxXExtent = g_nBmpWidth - rcClient.right;
    g_nMaxYExtent = g_nBmpHeight - rcClient.bottom;
    g_nXPos = 0;
    g_nYPos = 0;

    sbi.fMask = SIF_ALL | SIF_DISABLENOSCROLL;
    sbi.nMin = 0;
    sbi.nMax = ((g_nBmpHeight + g_nVertItemSize -1) / g_nVertItemSize)-1;
    sbi.nPage = rcClient.bottom / g_nVertItemSize;
    sbi.nPos = 0;
    sbi.nTrackPos =0;
    SetScrollInfo(hWnd, SB_VERT, &sbi, FALSE);

    if (1 < g_nVertItemSize)
    {
        g_nVWhiteSpace = ((g_nVertItemSize * (sbi.nMax+1)) - g_nBmpHeight) + (rcClient.bottom % g_nVertItemSize);
    }
    else
    {
        g_nVWhiteSpace = 0;
    }

    sbi.nMax = ((g_nBmpWidth  + g_nHorizItemSize -1) / g_nHorizItemSize)-1;
    sbi.nPage = rcClient.right / g_nHorizItemSize;
    sbi.nPos = 0;
    sbi.nTrackPos =0;
    SetScrollInfo(hWnd, SB_HORZ, &sbi, FALSE);

    if (1 < g_nHorizItemSize)
    {
        g_nHWhiteSpace = ((g_nHorizItemSize * (sbi.nMax+1)) - g_nBmpWidth) + (rcClient.right % g_nHorizItemSize);
    }
    else
    {
        g_nHWhiteSpace = 0;
    }
}

//
//  FUNCTION: ConfigureWAG(HWND hWnd)
//
//  PURPOSE:  Configure auto gestures for window.
//
void ConfigureWAG(HWND hWnd)
{
    WAGINFO wagInfo = {sizeof(WAGINFO)};
    
    wagInfo.dwFlags = WAGIF_OWNERANIMATE | 
        (g_fHScrollable ? WAGIF_HSCROLLABLE : 0) | 
        (g_fVScrollable ? WAGIF_VSCROLLABLE : 0) | 
        (g_fAllowPAN    ? 0 : WAGIF_IGNOREPAN) |
        (g_fAllowSCROLL ? 0 : WAGIF_IGNORESCROLL) |
        (g_fLockAxis    ? WAGIF_LOCKAXES : 0);

    wagInfo.nOwnerAnimateMessage = (g_fUseWMSCroll ? 0 : WM_PRIVATEANIMATEMSG);
    wagInfo.nItemHeight = g_nVertItemSize;
    wagInfo.nItemWidth = g_nHorizItemSize;
    wagInfo.bHorizontalExtent = (BYTE)g_nHorizExtent;
    wagInfo.bVerticalExtent = (BYTE)g_nVertExtent;

    if (!TKSetWindowAutoGesture(hWnd, &wagInfo))
    {
        MessageBox( hWnd,
                    TEXT("Failure from SetWindowAutoGesture()"),
                    TEXT("Error"), 
                    MB_OK);
    }

    // Make sure the item sizes are at least 1 for now - i.e. calculated size is 1 pixel
    g_nHorizItemSize = max(1,g_nHorizItemSize);
    g_nVertItemSize = max(1,g_nVertItemSize);
}

//
//  FUNCTION: InitConfigDialog(HWND hDlg)
//
//  PURPOSE:  Initialize WAG configuration dialog box 
//
void InitConfigDialog(HWND hDlg)
{
    // Create a Done button and size it.  
    SHINITDLGINFO shidi;
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
    shidi.hDlg = hDlg;
    SHInitDialog(&shidi);

    SendMessage(
        GetDlgItem(hDlg, IDC_PAN_ENABLED), 
        BM_SETCHECK, 
        g_fAllowPAN ? BST_CHECKED : BST_UNCHECKED,
        0);

    SendMessage(
        GetDlgItem(hDlg, IDC_SCROLL_ENABLED), 
        BM_SETCHECK, 
        g_fAllowSCROLL ? BST_CHECKED : BST_UNCHECKED,
        0);

    SendMessage(
        GetDlgItem(hDlg, IDC_LOCK_AXIS), 
        BM_SETCHECK, 
        g_fLockAxis ? BST_CHECKED : BST_UNCHECKED,
        0);

    SendMessage(
        GetDlgItem(hDlg, IDC_USE_WM_SCROLL), 
        BM_SETCHECK, 
        g_fUseWMSCroll ? BST_CHECKED : BST_UNCHECKED,
        0);

    SendMessage(
        GetDlgItem(hDlg, IDC_HSCROLL), 
        BM_SETCHECK, 
        g_fHScrollable ? BST_CHECKED : BST_UNCHECKED,
        0);

    SendMessage(
        GetDlgItem(hDlg, IDC_VSCROLL), 
        BM_SETCHECK, 
        g_fVScrollable? BST_CHECKED : BST_UNCHECKED,
        0);

    SetDlgItemInt(hDlg, IDC_HORZEXTENT, g_nHorizExtent, FALSE);
    SetDlgItemInt(hDlg, IDC_VERTEXTENT, g_nVertExtent, FALSE);
    SetDlgItemInt(hDlg, IDC_CXITEM, g_nHorizItemSize, FALSE);
    SetDlgItemInt(hDlg, IDC_CYITEM, g_nVertItemSize, FALSE);
}

//
//  FUNCTION: SaveConfigDialogState(HWND hDlg)
//
//  PURPOSE:  Saves state of the WAG configuration dialog box 
//
BOOL SaveConfigDialogState(HWND hDlg)
{
    BOOL fReadOk;
    UINT nHorzExtend = 0;
    UINT nVertExtend = 0;
    UINT cxItem = 1;
    UINT cyItem = 1;

    nHorzExtend = GetDlgItemInt(hDlg, IDC_HORZEXTENT, &fReadOk, FALSE);
    if (!fReadOk || nHorzExtend > 100)
    {
        MessageBox(hDlg, _T("Horizontal extent: value should be in within 0-100"), _T("Error"), MB_ICONERROR);
        return FALSE;
    }
    nVertExtend = GetDlgItemInt(hDlg, IDC_VERTEXTENT, &fReadOk, FALSE);
    if (!fReadOk || nVertExtend > 100)
    {
        MessageBox(hDlg, _T("Vertical extent: value should be in within 0-100"), _T("Error"), MB_ICONERROR);
        return FALSE;
    }
    cxItem = GetDlgItemInt(hDlg, IDC_CXITEM, &fReadOk, FALSE);
    if (!fReadOk || cxItem > 500)
    {
        MessageBox(hDlg, _T("Item width: value should be in within 0-100"), _T("Error"), MB_ICONERROR);
        return FALSE;
    }
    cyItem = GetDlgItemInt(hDlg, IDC_CYITEM, &fReadOk, FALSE);
    if (!fReadOk || cyItem > 500)
    {
        MessageBox(hDlg, _T("Item height: value should be in within 0-100"), _T("Error"), MB_ICONERROR);
        return FALSE;
    }

    g_nHorizExtent = nHorzExtend;
    g_nVertExtent = nVertExtend;
    g_nHorizItemSize = cxItem;
    g_nVertItemSize = cyItem;
    g_fAllowPAN = SendMessage(GetDlgItem(hDlg, IDC_PAN_ENABLED), BM_GETCHECK, 0, 0) == BST_CHECKED;
    g_fAllowSCROLL = SendMessage(GetDlgItem(hDlg, IDC_SCROLL_ENABLED), BM_GETCHECK, 0, 0) == BST_CHECKED;
    g_fLockAxis = SendMessage(GetDlgItem(hDlg, IDC_LOCK_AXIS), BM_GETCHECK, 0, 0) == BST_CHECKED;
    g_fUseWMSCroll = SendMessage(GetDlgItem(hDlg, IDC_USE_WM_SCROLL), BM_GETCHECK, 0, 0) == BST_CHECKED;
    g_fHScrollable = SendMessage(GetDlgItem(hDlg, IDC_HSCROLL), BM_GETCHECK, 0, 0) == BST_CHECKED;
    g_fVScrollable = SendMessage(GetDlgItem(hDlg, IDC_VSCROLL), BM_GETCHECK, 0, 0) == BST_CHECKED;

    RecalcScrollBarRanges(GetParent(hDlg));
    ConfigureWAG(GetParent(hDlg));

    return TRUE;
}
