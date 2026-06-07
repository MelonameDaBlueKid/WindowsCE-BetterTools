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

// Imaging.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>

#include <imaging.h>
#include <initguid.h>
#include <imgguids.h>

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 
#ifdef SMARTPHONE2003_UI_MODEL
#include "resourcesp.h"
#endif

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE            g_hInst;            // current instance
HWND                g_hWndMenuBar;        // menu bar handle

// Forward declarations of functions included in this code module:
ATOM            MyRegisterClass(HINSTANCE, LPTSTR);
BOOL            InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#ifndef WIN32_PLATFORM_WFSP
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
#endif // !WIN32_PLATFORM_WFSP

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
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IMAGING));
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
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IMAGING));
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
    LoadString(hInstance, IDC_IMAGING, szWindowClass, MAX_LOADSTRING);

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

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

//
//   FUNCTION:  DrawImage(HDC)
//
//   PURPOSE: Load an image from a file and draw it to the given HDC
//
//
void DrawImage(HDC hdc)
{
    IImagingFactory *pImgFactory = NULL;
    IImage *pImage = NULL;
    RECT rc = { 0, 0, 110, 88};

    // Normally you would only call CoInitialize/CoUninitialize
    // once per thread.  This sample calls CoInitialize in this
    // draw function simply to illustrate that you must call 
    // CoInitialize before calling CoCreateInstance.
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // Create the imaging factory.
    if (SUCCEEDED(CoCreateInstance (CLSID_ImagingFactory,
                                    NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_IImagingFactory,
                                    (void **)&pImgFactory)))
    {
        // Load the image from the JPG file.
        if (SUCCEEDED(pImgFactory->CreateImageFromFile(
                        TEXT("\\Program Files\\Imaging\\flower.jpg"),
                        &pImage)))
        {
            // Draw the image.
            pImage->Draw(hdc, &rc, NULL);
            pImage->Release();
        }

        pImgFactory->Release();
    }
    CoUninitialize();
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND    - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY    - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

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
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            
            DrawImage(hdc);
                    
            EndPaint(hWnd, &ps);
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
