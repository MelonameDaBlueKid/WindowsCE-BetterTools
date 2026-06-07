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

// GetDeviceID.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GetDeviceID.h"
#include <windows.h>
#include <commctrl.h>
#include <GetDeviceUniqueId.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE           g_hInst;            // current instance
HWND                g_hWndMenuBar;      // menu bar handle


// Buffers to hold the two device IDs we are going to generate
BYTE                g_bDeviceID1[GETDEVICEUNIQUEID_V1_OUTPUT];
BYTE                g_bDeviceID2[GETDEVICEUNIQUEID_V1_OUTPUT];

// Lengths of the returned device IDs
DWORD               g_cbDeviceID1;
DWORD               g_cbDeviceID2;


// Forward declarations of functions included in this code module:
ATOM            MyRegisterClass(HINSTANCE, LPTSTR);
BOOL            InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#ifndef WIN32_PLATFORM_WFSP
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
#endif // !WIN32_PLATFORM_WFSP


/*
 *    Call the GetDeviceUniqueID function twice using different
 *    Application Specific Data to demonstrate that different
 *    values are returned. This allows different applications to
 *    have a device ID that can be used to identify a device. If 
 *    two (or more) applications need to use the same device ID then
 *    they need to use the same Application Specific Data when calling
 *    GetDeviceUniqueID.
 */
static HRESULT GetDeviceIDs ()
{
    HRESULT            hr;

    // Get the first device id

    // Application specific data
    // {8D552BD1-E232-4107-B72D-38B6A4726439}
    const GUID     bApplicationData1  = { 0x8d552bd1, 0xe232, 0x4107, { 0xb7, 0x2d, 0x38, 0xb6, 0xa4, 0x72, 0x64, 0x39 } };
    const DWORD    cbApplicationData1 = sizeof (bApplicationData1);

    g_cbDeviceID1 = GETDEVICEUNIQUEID_V1_OUTPUT;
    hr = GetDeviceUniqueID (reinterpret_cast<LPBYTE>(const_cast<LPGUID>(&bApplicationData1)), 
                             cbApplicationData1, 
                             GETDEVICEUNIQUEID_V1, 
                             g_bDeviceID1, 
                             &g_cbDeviceID1);
    
    if (SUCCEEDED (hr))
    {
        // Get a second ID to verify that they are different for
        // different Application data

        // Application specific data
        // {C5BEC46D-2A43-4200-BBB7-5FF14097954D}
        const GUID     bApplicationData2  = { 0xc5bec46d, 0x2a43, 0x4200, { 0xbb, 0xb7, 0x5f, 0xf1, 0x40, 0x97, 0x95, 0x4d } };
        const DWORD    cbApplicationData2 = sizeof (bApplicationData2);

        g_cbDeviceID2 = GETDEVICEUNIQUEID_V1_OUTPUT;
        hr = GetDeviceUniqueID (reinterpret_cast<LPBYTE>(const_cast<LPGUID>(&bApplicationData2)), 
                                 cbApplicationData2, 
                                 GETDEVICEUNIQUEID_V1, 
                                 g_bDeviceID2, 
                                 &g_cbDeviceID2);
    }

    return hr;
}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    MSG msg;

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow)) 
    {
        return FALSE;
    }

#ifndef WIN32_PLATFORM_WFSP
    HACCEL hAccelTable;
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GETDEVICEID));
#endif // !WIN32_PLATFORM_WFSP

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
#ifndef WIN32_PLATFORM_WFSP
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
#endif // !WIN32_PLATFORM_WFSP
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
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GETDEVICEID));
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
    TCHAR szTitle[MAX_LOADSTRING];        // title bar text
    TCHAR szWindowClass[MAX_LOADSTRING];    // main window class name

    g_hInst = hInstance; // Store instance handle in our global variable

#ifdef WIN32_PLATFORM_PSPC
    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Pocket PC special controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();
#endif // WIN32_PLATFORM_PSPC

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_GETDEVICEID, szWindowClass, MAX_LOADSTRING);

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
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
#endif // WIN32_PLATFORM_PSPC || WIN32_PLATFORM_WFSP

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

#ifdef WIN32_PLATFORM_PSPC
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
#endif // WIN32_PLATFORM_PSPC

    // Get the application specific device IDs (to display later)
    if (FAILED (GetDeviceIDs()))
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

static HRESULT HexString (const BYTE value, LPTSTR pszBuffer, const DWORD cbBufferSize, DWORD *pcbAdded)
{
    static const TCHAR HexLookup[16] =  {_T('0'), _T('1'), _T('2'), _T('3'),
                                         _T('4'), _T('5'), _T('6'), _T('7'),
                                         _T('8'), _T('9'), _T('A'), _T('B'),
                                         _T('C'), _T('D'), _T('E'), _T('F')
                                        };
    HRESULT hr;

    if (cbBufferSize < 3)
    {
        hr = HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
    }
    else
    {
        *pszBuffer++ = HexLookup[(value >> 4) & 0x0F];
        *pszBuffer++ = HexLookup[value & 0x0F];
        *pszBuffer = _T('\0');

        *pcbAdded = 2;

        hr = S_OK;
    }

    return hr;
}

// Generate printable version of device ID
static HRESULT DeviceID2String (const BYTE * const bDeviceID, const DWORD cbDeviceID, const LPTSTR pszIDAsString, const DWORD cbIDAsString)
{
    HRESULT hr;
    LPTSTR    pszOutput            = pszIDAsString;
    DWORD    cbOutputRemaining    = cbIDAsString;
    DWORD    i;
    DWORD    cbAdded;

    for (i = 0; i < cbDeviceID; ++i)
    {
        hr = HexString (bDeviceID[i], pszOutput, cbOutputRemaining, &cbAdded);
        if (FAILED (hr))
        {
            break;
        }

        cbOutputRemaining -= cbAdded;
        pszOutput += cbAdded;
    }
    return hr;
}

static void OnPaint (HWND hWnd, HFONT hFont)
{
    HDC            hdc;
    PAINTSTRUCT ps;
    RECT        rt;
    TEXTMETRIC    tm;
    TCHAR        szDeviceID[(GETDEVICEUNIQUEID_V1_OUTPUT * 2) + 1];
    TCHAR        szHeader[MAX_LOADSTRING];

    hdc = BeginPaint(hWnd, &ps);
    
    if (hFont)
    {
        SelectObject (hdc, hFont);
    }
    GetClientRect(hWnd, &rt);
    GetTextMetrics (hdc, &tm);

    // Display the first ID
    if (SUCCEEDED (DeviceID2String (g_bDeviceID1, g_cbDeviceID1, szDeviceID, ARRAYSIZE (szDeviceID))))
    {
        LoadString(g_hInst, IDS_DEVICEID1, szHeader, MAX_LOADSTRING); 

        rt.bottom = tm.tmHeight + tm.tmExternalLeading;
        DrawText (hdc, szHeader, -1, &rt, DT_CENTER);

        rt.top = rt.bottom;
        rt.bottom += tm.tmHeight + tm.tmExternalLeading;
        DrawText (hdc, szDeviceID, 10, &rt, DT_CENTER);
            
        rt.top = rt.bottom;
        rt.bottom += tm.tmHeight + tm.tmExternalLeading;
        DrawText (hdc, &szDeviceID[10], 10, &rt, DT_CENTER);
    }

    // Display the second ID
    if (SUCCEEDED (DeviceID2String (g_bDeviceID2, g_cbDeviceID2, szDeviceID, ARRAYSIZE (szDeviceID))))
    {
        LoadString(g_hInst, IDS_DEVICEID2, szHeader, MAX_LOADSTRING); 

        rt.top = rt.bottom + tm.tmHeight + tm.tmExternalLeading;
        rt.bottom = rt.top + tm.tmHeight + tm.tmExternalLeading;
        DrawText (hdc, szHeader, -1, &rt, DT_CENTER);

        rt.top = rt.bottom;
        rt.bottom += tm.tmHeight + tm.tmExternalLeading;
        DrawText (hdc, szDeviceID, 10, &rt, DT_CENTER);
            
        rt.top = rt.bottom;
        rt.bottom += tm.tmHeight + tm.tmExternalLeading;
        DrawText (hdc, &szDeviceID[10], 10, &rt, DT_CENTER);
    }

    EndPaint(hWnd, &ps);
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
    int                wmId, wmEvent;
    static HFONT    hFont;

#if defined(SHELL_AYGSHELL) && !defined(WIN32_PLATFORM_WFSP)
    static SHACTIVATEINFO s_sai;
#endif // SHELL_AYGSHELL && !WIN32_PLATFORM_WFSP
    
    switch (message) 
    {
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            // Parse the menu selections:
            switch (wmId)
            {
#ifndef WIN32_PLATFORM_WFSP
                case IDM_HELP_ABOUT:
                    DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, About);
                    break;
#endif // !WIN32_PLATFORM_WFSP
#ifdef WIN32_PLATFORM_WFSP
                case IDM_OK:
                    DestroyWindow(hWnd);
                    break;
#endif // WIN32_PLATFORM_WFSP
#ifndef WIN32_PLATFORM_WFSP
                case IDM_OK:
                    SendMessage (hWnd, WM_CLOSE, 0, 0);                
                    break;
#endif // !WIN32_PLATFORM_WFSP
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_CREATE:
#ifdef SHELL_AYGSHELL
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

#ifndef WIN32_PLATFORM_WFSP
            // Initialize the shell activate info structure
            memset(&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
#endif // !WIN32_PLATFORM_WFSP
#endif // SHELL_AYGSHELL

            // Create a fixed pitch font to display results
            LOGFONT lf;
            HDC        hdc;
            memset (&lf, 0, sizeof (lf));

            hdc = GetDC (hWnd);
            lf.lfHeight = -MulDiv (10, GetDeviceCaps (hdc, LOGPIXELSY), 72);
            lf.lfCharSet = DEFAULT_CHARSET;
            lf.lfWeight = FW_NORMAL;
            lf.lfPitchAndFamily = FIXED_PITCH || FF_DONTCARE;
            hFont = CreateFontIndirect (&lf);
            ReleaseDC (hWnd, hdc);

            break;
        case WM_PAINT:
            OnPaint (hWnd, hFont);
            break;
        case WM_DESTROY:
#ifdef SHELL_AYGSHELL
            CommandBar_Destroy(g_hWndMenuBar);
#endif // SHELL_AYGSHELL
            PostQuitMessage(0);
            break;

#if defined(SHELL_AYGSHELL) && !defined(WIN32_PLATFORM_WFSP)
        case WM_ACTIVATE:
            // Notify shell of our activate message
            SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
            break;
        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
            break;
#endif // SHELL_AYGSHELL && !WIN32_PLATFORM_WFSP

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

#ifndef WIN32_PLATFORM_WFSP
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
#ifdef SHELL_AYGSHELL
            {
                // Create a Done button and size it.  
                SHINITDLGINFO shidi;
                shidi.dwMask = SHIDIM_FLAGS;
                shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
                shidi.hDlg = hDlg;
                SHInitDialog(&shidi);
            }
#endif // SHELL_AYGSHELL

            return (INT_PTR)TRUE;

        case WM_COMMAND:
#ifdef SHELL_AYGSHELL
            if (LOWORD(wParam) == IDOK)
#endif
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hDlg, message);
            return (INT_PTR)TRUE;

#ifdef _DEVICE_RESOLUTION_AWARE
        case WM_SIZE:
            {
        DRA::RelayoutDialog(
            g_hInst, 
            hDlg, 
            DRA::GetDisplayMode() != DRA::Portrait ? MAKEINTRESOURCE(IDD_ABOUTBOX_WIDE) : MAKEINTRESOURCE(IDD_ABOUTBOX));
            }
            break;
#endif
    }
    return (INT_PTR)FALSE;
}
#endif // !WIN32_PLATFORM_WFSP
