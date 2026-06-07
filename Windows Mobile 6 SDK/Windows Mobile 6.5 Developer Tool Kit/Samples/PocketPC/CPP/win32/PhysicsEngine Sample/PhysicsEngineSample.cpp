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
#include "PhysicsEngineSample.h"
#include <gesture.h>
#include <GesturePhysicsEngine.h>
#include <WindowAutoGesture.h>

#define MAX_LOADSTRING 100

/// <summary>
/// Identifier of the timer used for gesture animation.
/// </summary>
#define GESTURE_ANIMATION_TIMER_ID 10

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

HINSTANCE        g_hInst;           // current instance
HWND             g_hWndMenuBar;     // menu bar handle

bool             g_fAnimating = false;
};

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE, LPTSTR);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DoPaint(HWND hWnd);
void RecalcScrollBarRanges(HWND hWnd);
BOOL ProcessGesture(HWND hWnd, UINT, WPARAM wParam, LPARAM lParam);
void SnapBackToFrame( HWND hwnd);
void AnimationTimerProc(HWND hwnd,UINT,UINT_PTR idEvent,DWORD);
HRESULT ProcessEndPan( HWND    hwnd, int     nTransitionSpeed, DWORD   nTransitionAngle, __in GESTUREINFO const * );

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
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PHYSICS_SAMPLE));

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
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PHYSICS_SAMPLE));
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
    LoadString(hInstance, IDC_PHYSICS_SAMPLE, szWindowClass, MAX_LOADSTRING);

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

        case WM_GESTURE:
            if (!ProcessGesture(hWnd, message, wParam, lParam))
            {
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
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
            int nBar = (WM_VSCROLL==message) ? SB_VERT:SB_HORZ;
            int * pnVal = (WM_VSCROLL==message) ? &g_nYPos:&g_nXPos;
            int nVal = (*pnVal);
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
            *pnVal = nVal;
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

    if (g_nXPos > g_nMaxXExtent)
    {
        RECT rc = {
            rcClient.right - (g_nXPos - g_nMaxXExtent),
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

    if (g_nYPos > g_nMaxYExtent)
    {
        RECT rc = {
            rcClient.left,
            rcClient.bottom - (g_nYPos - g_nMaxYExtent),
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

    sbi.fMask= SIF_ALL | SIF_DISABLENOSCROLL;
    sbi.nMin = 0;
    sbi.nMax = g_nBmpHeight - 1;
    sbi.nPage = rcClient.bottom;
    sbi.nPos = 0;
    sbi.nTrackPos =0;
    SetScrollInfo(hWnd, SB_VERT, &sbi, FALSE);


    sbi.nMax = g_nBmpWidth - 1;
    sbi.nPage = rcClient.right;
    sbi.nPos = 0;
    sbi.nTrackPos =0;
    SetScrollInfo(hWnd, SB_HORZ, &sbi, FALSE);
}

//
//  FUNCTION: ProcessGesture(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Handles processing of WM_GESTURE command.
//
BOOL ProcessGesture(HWND hWnd, UINT, WPARAM wParam, LPARAM lParam)
{
    BOOL fHandled = FALSE; 
    GESTUREINFO gi = {sizeof(gi)};

    // Go get the gesture - will return FALSE if the gesture engine is not present in the system.
    if (TKGetGestureInfo(reinterpret_cast<HGESTUREINFO>(lParam), &gi))
    {
        static POINT ptsLast = {0};
        switch (wParam)
        {
            case GID_PAN:
            {
                if (g_fAnimating)
                {
                    // Stop any running animations
                    SnapBackToFrame(hWnd);
                }
                if (GF_BEGIN == (gi.dwFlags & GF_BEGIN))
                {
                    ptsLast.x = gi.ptsLocation.x;
                    ptsLast.y = gi.ptsLocation.y;
                }
                else
                {
                    RECT rcClient;
                    GetClientRect(hWnd, &rcClient);

                    ScrollWindowEx(hWnd, 
                        gi.ptsLocation.x - ptsLast.x, 
                        gi.ptsLocation.y - ptsLast.y, 
                        &rcClient, &rcClient, NULL, NULL, SW_INVALIDATE);

                    g_nXPos -= gi.ptsLocation.x - ptsLast.x;
                    g_nYPos -= gi.ptsLocation.y - ptsLast.y;
                    ptsLast.x = gi.ptsLocation.x;
                    ptsLast.y = gi.ptsLocation.y;
                    SetScrollPos(hWnd, SB_VERT, g_nYPos, TRUE);
                    SetScrollPos(hWnd, SB_HORZ, g_nXPos, TRUE);

                    UpdateWindow(hWnd);
                }
                fHandled = TRUE;
            }
            break;

            case GID_SCROLL:
            {
                ProcessEndPan( hWnd, 
                               (int)GID_SCROLL_VELOCITY(gi.ullArguments), 
                               (int)GID_SCROLL_ANGLE(gi.ullArguments),
                               &gi);

                fHandled = TRUE;
            }
            break;

            case GID_END:
            {
                ProcessEndPan( hWnd, 
                               0,0,
                               &gi);

                // GID_BEGIN/GID_END should always be send to DefGestureProc
            }
            break;
        }
    }

    return fHandled;
}



//
//  FUNCTION: ProcessEndPan(HWND, int, WPARAM, LPARAM)
//
//  PURPOSE:  Processes the end gesture and figures out what 
//            physics engine animation is needed
//
HRESULT 
ProcessEndPan( 
    HWND    hwnd,
    int     nTransitionSpeed,            // @parm Start speed of animation (relevant for flick end gesture). Must be a posative value
    DWORD   nTransitionAngle,            // @parm Angle for start speed (relevant for flick end gesture)
    __in GESTUREINFO const *             // @parm Gesture information - not used here.
    )
{
    HRESULT hr = S_OK;
    int nYExtendedPan = 0;
    int nXExtendedPan = 0;
    PHYSICSENGINEINIT initState = {sizeof(initState)};
    RECT rctClient = {0};

    if (g_fAnimating)
    {
        hr = E_UNEXPECTED;
        goto Exit;
    }

    if (0> g_nXPos)
    {
        nXExtendedPan = g_nXPos;
    }
    else if ( g_nMaxXExtent < g_nXPos)
    {
        nXExtendedPan = g_nXPos - g_nMaxXExtent;
    }

    if (0> g_nYPos)
    {
        nYExtendedPan = g_nYPos;
    }
    else if ( g_nMaxYExtent < g_nYPos)
    {
        nYExtendedPan = g_nYPos - g_nMaxYExtent;
    }

    initState.dwEngineType              = 0;
    initState.dwFlags                   = 0;
    initState.lInitialVelocity          = -nTransitionSpeed;
    initState.dwInitialAngle            = nTransitionAngle;
    initState.bXAxisMovementMode        = PHYSICSENGINE_MOVEMENT_MODE_DECELERATE;
    initState.bYAxisMovementMode        = PHYSICSENGINE_MOVEMENT_MODE_DECELERATE;
    initState.bXAxisBoundaryMode        = PHYSICSENGINE_BOUNDARY_MODE_RUBBERBAND;
    initState.bYAxisBoundaryMode        = PHYSICSENGINE_BOUNDARY_MODE_RUBBERBAND;
    GetClientRect(hwnd, &rctClient);
    initState.rcBoundary.left           = 0;
    initState.rcBoundary.right          = rctClient.right + g_nMaxXExtent;
    initState.rcBoundary.top            = 0;
    initState.rcBoundary.bottom         = rctClient.bottom + g_nMaxYExtent;
    initState.sizeView.cx               = rctClient.right;
    initState.sizeView.cy               = rctClient.bottom;
    initState.ptInitialPosition.x       = g_nXPos;
    initState.ptInitialPosition.y       = g_nYPos;
    initState.sizeItem.cx               = 1;       
    initState.sizeItem.cy               = 1;       

    // create the physics engine and store it 
    if (SUCCEEDED(TKCreatePhysicsEngine(&initState, &g_hPhysicsEngine)))
    {
        g_fAnimating = true; // we are now animating
        // Setup the timer
        g_uTimerId = SetTimer(  hwnd,
                                GESTURE_ANIMATION_TIMER_ID,
                                GESTURE_ANIMATION_FRAME_DELAY_MS, 
                                AnimationTimerProc);
    }

Exit:
    return hr;
}

//
//  FUNCTION: AnimationTimerProc( HWND hwnd, UINT, UINT_PTR idEvent, DWORD )
//
//  PURPOSE:  callback to process the timer events
//
//
VOID CALLBACK
AnimationTimerProc(
    HWND hwnd,
    UINT,
    UINT_PTR idEvent,
    DWORD
)
{
    RECT rcClient;
    PHYSICSENGINESTATE state = {sizeof(state)};
    
    if ( NULL == g_hPhysicsEngine ||
         true != g_fAnimating || 
         g_uTimerId != idEvent)
    {
        SnapBackToFrame(hwnd);
        MessageBox(hwnd, TEXT("Error"), TEXT("Invalid state in timer callback"), MB_OK);
        return;
    }

    TKQueryPhysicsEngine(g_hPhysicsEngine, &state);

    GetClientRect(hwnd, &rcClient);
    ScrollWindowEx(hwnd, 
        g_nXPos - state.ptPosition.x,
        g_nYPos - state.ptPosition.y,
        &rcClient, &rcClient, NULL, NULL, SW_INVALIDATE);

    g_nXPos = state.ptPosition.x;
    g_nYPos = state.ptPosition.y;
    SetScrollPos(hwnd, SB_VERT, g_nYPos, TRUE);
    SetScrollPos(hwnd, SB_HORZ, g_nXPos, TRUE);

    UpdateWindow(hwnd);
    // If the animation is now complete we need to clean up all our resources.
    // Just to be safe this is done by calling Snap to ensure there is no residual offset
    if (state.fComplete)
    {
        // pPanState here should be valid still (even tho PanAxis can release it) because
        // the fAnimating flag is guaranteed to be set at this point
        SnapBackToFrame(hwnd);
    }
}

//
//  FUNCTION: SnapBackToFrame( HWND hwnd )
//
//  PURPOSE:  bring the content back into the visible area 
//
//
void SnapBackToFrame( HWND hwnd)
{
    g_fAnimating = false;

    g_nXPos = max(g_nXPos, 0);
    g_nYPos = max(g_nYPos, 0);
    g_nXPos = min(g_nXPos, g_nMaxXExtent);
    g_nYPos = min(g_nYPos, g_nMaxYExtent);
    SetScrollPos(hwnd, SB_VERT, g_nYPos, TRUE);
    SetScrollPos(hwnd, SB_HORZ, g_nXPos, TRUE);

    InvalidateRect(hwnd, NULL, FALSE);
    KillTimer(hwnd, g_uTimerId);
    // its safe to pass a null here
    (void) TKDestroyPhysicsEngine(g_hPhysicsEngine);
    g_hPhysicsEngine = NULL;
}
