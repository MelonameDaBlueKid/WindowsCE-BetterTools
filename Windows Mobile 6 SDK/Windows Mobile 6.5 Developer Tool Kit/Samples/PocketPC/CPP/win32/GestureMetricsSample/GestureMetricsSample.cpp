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
// GestureMetricsSample.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GestureMetricsSample.h"
#include <Gesture.h>

#define ID_HOLD_TIMER 1
#define ID_DOUBLESELECT_TIMER 2
#define TIMER_TIMEOUT 50
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE           g_hInst;            // current instance
HWND                g_hWndMenuBar;      // menu bar handle
HWND                g_hWndLabel;
HWND                g_hWndProgressBar;
POINT               g_ptLastAreaPos = {-1, -1};
DWORD               g_dwLastAreaSize = 0;
HBRUSH              g_hRedBrush = NULL;
GESTUREMETRICS      g_HoldGestureMetrics;
GESTUREMETRICS      g_DoubleSelectGestureMetrics;
DWORD               g_dwStartTime;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE, LPTSTR);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GESTUREMETRICSSAMPLE));

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
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
    WNDCLASS wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GESTUREMETRICSSAMPLE));
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
    LoadString(hInstance, IDC_GESTUREMETRICSSAMPLE, szWindowClass, MAX_LOADSTRING);

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

    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
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
//  FUNCTION: KillTimers(HWND hWnd)
//
//  PURPOSE: Kills timers used by application.
//
void KillTimers(HWND hWnd)
{
    KillTimer(hWnd, ID_HOLD_TIMER);
    KillTimer(hWnd, ID_DOUBLESELECT_TIMER);
}

//
//  FUNCTION: StartTimer(HWND hWnd, DWORD dwTimerId)
//
//  PURPOSE: Starts a timer with given id.
//
void StartTimer(HWND hWnd, DWORD dwTimerId)
{
    KillTimers(hWnd);
    g_dwStartTime = GetTickCount();
    SetTimer(hWnd, dwTimerId, TIMER_TIMEOUT, NULL);
}

//
//  FUNCTION: DrawGestureArea(HDC hDC, const POINT* pptPoint, DWORD dwDistanceTolerance, BOOL fClear)
//
//  PURPOSE: Draws a rectangle representing area within gesture distance tolerance.
//
void DrawGestureArea(HDC hDC, const POINT* pptPoint, DWORD dwDistanceTolerance, BOOL fClear)
{
    HBRUSH hBrush = NULL;
    RECT rc = {
        pptPoint->x - dwDistanceTolerance,
        pptPoint->y - dwDistanceTolerance,
        pptPoint->x + dwDistanceTolerance,
        pptPoint->y + dwDistanceTolerance
    };

    if (fClear)
    {
        hBrush = (HBRUSH) GetStockObject(WHITE_BRUSH);
    }
    else
    {
        hBrush = g_hRedBrush;
    }

    FillRect(hDC, &rc, hBrush);
}

//
//  FUNCTION: NewGestureArea(HWND hWnd, const POINT* pptPoint, DWORD dwDistanceTolerance)
//
//  PURPOSE: Sets up new gesture area.
//
void NewGestureArea(HWND hWnd, const POINT* pptPoint, DWORD dwDistanceTolerance)
{
    HDC hDC = GetDC(hWnd);
    if (0 != g_dwLastAreaSize)
    {
        DrawGestureArea(hDC, &g_ptLastAreaPos, g_dwLastAreaSize, TRUE);
        g_dwLastAreaSize = 0;
    }

    if (pptPoint != NULL && dwDistanceTolerance != 0)
    {
        g_ptLastAreaPos = *pptPoint;
        g_dwLastAreaSize = dwDistanceTolerance;
        DrawGestureArea(hDC, &g_ptLastAreaPos, g_dwLastAreaSize, FALSE);
    }
}

//
//  FUNCTION: OnLButtonDown(HWND hWnd, int xPos, int yPos)
//
//  PURPOSE: WM_LBUTTONDOWN handler.
//
void OnLButtonDown(HWND hWnd, int xPos, int yPos)
{
    POINT pt = {xPos, yPos};
    SetCapture(hWnd);
    StartTimer(hWnd, ID_HOLD_TIMER);

    NewGestureArea(hWnd, &pt, g_HoldGestureMetrics.dwDistanceTolerance);

    SetWindowText(g_hWndLabel, _T(""));
    SendMessage(g_hWndProgressBar, PBM_SETPOS, 0, 0);
}

//
//  FUNCTION: OnSize(HWND hWnd)
//
//  PURPOSE: WM_SIZE handler.
//
void OnSize(HWND hWnd)
{
    RECT rcClient;
    TEXTMETRIC tm;
    GetClientRect(hWnd, &rcClient);

    HDC hDC = GetDC(hWnd);
    GetTextMetrics(hDC, &tm);
    ReleaseDC(hWnd, hDC);

    SetWindowPos(g_hWndLabel, NULL, 
        rcClient.left, rcClient.top, 
        rcClient.right - rcClient.left,
        tm.tmHeight, SWP_NOACTIVATE);

    SetWindowPos(g_hWndProgressBar, NULL, 
        rcClient.left, rcClient.top + tm.tmHeight, 
        rcClient.right - rcClient.left,
        tm.tmHeight, SWP_NOACTIVATE);

    // Delete gesture area and reset timers
    NewGestureArea(hWnd, NULL, 0);
    KillTimers(hWnd);
}

//
//  FUNCTION: OnTimer(DWORD dwTimerId)
//
//  PURPOSE: WM_TIMER handler.
//
void OnTimer(DWORD dwTimerId)
{
    DWORD dwTimeout;

    // Check which timer we are handling now.
    if (dwTimerId == ID_HOLD_TIMER && g_HoldGestureMetrics.dwTimeout != 0)
    {
        dwTimeout = g_HoldGestureMetrics.dwTimeout;
    }
    else if(dwTimerId == ID_DOUBLESELECT_TIMER && g_DoubleSelectGestureMetrics.dwTimeout != 0)
    {
        dwTimeout = g_DoubleSelectGestureMetrics.dwTimeout;
    }
    else
    {
        return;
    }

    // Calculate position of the progress bar based on time passed from the 
    // beginning of calculation and timeout value.
    DWORD nPos = ((GetTickCount() - g_dwStartTime) * 100) / dwTimeout;

    if(nPos > 100)
    {
        nPos = 100;
    }

    // Set position of the progress bar.
    SendMessage(g_hWndProgressBar, PBM_SETPOS, (WPARAM)nPos, 0);
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
    PAINTSTRUCT ps;
    HDC hdc;

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
                    DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, About);
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

            g_hRedBrush = CreateSolidBrush(RGB(128, 0, 0));
            // Prepare GESTUREMETRICS structure to get hold gestre metrics.
            // cbSize - should contain size of the structure 
            // dwID - should contain identifier of the the gesture message which
            // we want to retrieve metrics for.
            g_HoldGestureMetrics.cbSize = sizeof(GESTUREMETRICS);
            g_HoldGestureMetrics.dwID = GID_HOLD;
            if (!TKGetGestureMetrics(&g_HoldGestureMetrics))
            {
                MessageBox(hWnd, _T("RKGetGestureMetrics error"), _T("Error"), MB_ICONERROR);
                return -1;
            }

            // Prepare to get double select gesture metrics
            g_DoubleSelectGestureMetrics.cbSize = sizeof(GESTUREMETRICS);
            g_DoubleSelectGestureMetrics.dwID = GID_DOUBLESELECT;
            if (!TKGetGestureMetrics(&g_DoubleSelectGestureMetrics))
            {
                MessageBox(hWnd, _T("RKGetGestureMetrics error"), _T("Error"), MB_ICONERROR);
                return -1;
            }

            // Set up controls.
            g_hWndLabel = CreateWindow(
                _T("STATIC"), 
                _T(""), 
                WS_CHILD | WS_VISIBLE | SS_CENTER, 
                0, 0, 0, 0, hWnd, NULL, g_hInst, NULL);

            g_hWndProgressBar = CreateWindow(
                PROGRESS_CLASS, 
                _T(""), 
                WS_CHILD | WS_VISIBLE, 
                0, 0, 0, 0, hWnd, NULL, g_hInst, NULL);

            SendMessage(g_hWndProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
            break;

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            if (g_dwLastAreaSize != 0)
            {
                DrawGestureArea(hdc, &g_ptLastAreaPos, g_dwLastAreaSize, FALSE);
            }
            EndPaint(hWnd, &ps);
            break;

        case WM_SIZE:
            OnSize(hWnd);
            break;

        case WM_LBUTTONDOWN:
            OnLButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_LBUTTONUP:
            ReleaseCapture();
            KillTimer(hWnd, ID_HOLD_TIMER);
            break;

        case WM_TIMER:
            OnTimer(wParam);
            break;

        case WM_GESTURE:
            {
                BOOL fHandled = FALSE;
                HGESTUREINFO hgi = (HGESTUREINFO)lParam;
                GESTUREINFO gi;
                POINT ptPos;

                switch(wParam)
                {
                case GID_HOLD:
                    KillTimers(hWnd);
                    SetWindowText(g_hWndLabel, _T("HOLD DETECTED"));
                    SendMessage(g_hWndProgressBar, PBM_SETPOS, 100, 0);
                    fHandled = TRUE;
                    break;

                case GID_SELECT:
                    gi.cbSize = sizeof(GESTUREINFO);
                    if (TKGetGestureInfo(hgi, &gi))
                    {
                        SetWindowText(g_hWndLabel, _T("SELECT DETECTED"));
                        SendMessage(g_hWndProgressBar, PBM_SETPOS, 0, 0);
                        StartTimer(hWnd, ID_DOUBLESELECT_TIMER);

                        POINTSTOPOINT(ptPos, gi.ptsLocation);
                        ScreenToClient(hWnd, &ptPos);
                        NewGestureArea(hWnd, &ptPos, g_DoubleSelectGestureMetrics.dwDistanceTolerance);
                        fHandled = TRUE;
                    }
                    break;

                case GID_DOUBLESELECT:
                    KillTimers(hWnd);
                    SetWindowText(g_hWndLabel, _T("DOUBLE SELECT DETECTED"));
                    fHandled = TRUE;
                    break;

                case GID_PAN:
                    KillTimers(hWnd);
                    fHandled = TRUE;
                    break;
                }

                if (!fHandled)
                {
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;

        case WM_DESTROY:
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

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM /*lParam*/)
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
