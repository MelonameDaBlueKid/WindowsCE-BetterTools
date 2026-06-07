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
#include <windows.h>
#include "macros.h"
#include "aygshell.h"

HWND g_hwndMain = NULL;       // Handle to the application main window
TCHAR gc_szTitle[] = _T("LoadKeyMap"); // Application main window name
TCHAR gc_szClassName[] = _T("LoadKeyMap window class");  // Main window class name
TCHAR gc_szDirections[] = _T("Please type one of the following keys:\n\
    1 to restore the default mapping\n\
    2 to load a null mapping\n\
    3 to load a 12-key mapping\n\
    4 to load a 15-key mapping\n\
    5 to load a 30-key mapping\n\
    6 to load a custom Mapping.txt");

HRESULT ProcessCommand(LPTSTR pszCommand);

/***********************************************************************

FUNCTION: 
  DrawTextWrapper

PURPOSE: 
  Helper for drawing text in our window.

***********************************************************************/
HRESULT DrawTextWrapper(TCHAR *pszText)
{
    HRESULT hr = S_OK;
    HDC hdc = GetDC(g_hwndMain);
    RECT rect;
    TCHAR s_szText[3 * MAX_PATH];

    CBR(hdc);

    CBR(GetClientRect(g_hwndMain, &rect));
    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

    // Prepend app instructions to text to paint
    CHR(StringCchPrintf(s_szText, ARRAYSIZE(s_szText), _T("%s\n\n%s"), gc_szDirections, pszText));

    // Draw the text
    CBR(DrawText(hdc, s_szText, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP));

Error:
    if (hdc)
    {
        ReleaseDC(g_hwndMain, hdc);
    }
    
    return hr;
}

/***********************************************************************

FUNCTION: 
  ReportAndQuit
  
PURPOSE: 
  Helper for reporting the results of ProcessCommand then quitting.

***********************************************************************/
void ReportAndQuit(TCHAR *pszCommand, HRESULT hrCommand)
{
    TCHAR szMsg[2 * MAX_PATH] = _T("");
    if (SUCCEEDED(hrCommand))
    {
        StringCchPrintf(szMsg, ARRAYSIZE(szMsg), _T("Successfully executed %s"), pszCommand);
    }
    else
    {
        StringCchPrintf(szMsg, ARRAYSIZE(szMsg), _T("Failed to execute %s\nError = 0x%x"), pszCommand, hrCommand);
    }
    DrawTextWrapper(szMsg);

    // Sleep to give user time to see results
    Sleep(1000);  

    // We're done
    DestroyWindow(g_hwndMain);
}

/***********************************************************************

FUNCTION: 
  WndProc

PURPOSE: 
  The callback function for the main window. It processes messages that
  are sent to the main window.

***********************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
    BOOL fHandled = FALSE;
    
    switch (umsg)
    {
        case WM_KEYDOWN:
            // Check to see if one of our supported inputs has been pressed.
            // The supported inputs are
            //    1 to restore the device's default mapping\n\
            //    2 to load a null mapping\n\
            //    3 to load a 12-key mapping\n\
            //    4 to load a 15-key mapping\n\
            //    5 to load a 30-key mapping\n\
            //    6 to load a custom Mapping.txt");

            switch ((TCHAR)wParam)
            {
                // WM_KEYDOWN values for digits are the same as their TCHAR values
                case _T('1'):
                    ReportAndQuit(_T("UnloadKeyMap"), ProcessCommand(_T("-1")));
                    break;

                case _T('2'):
                    ReportAndQuit(_T("LoadKeyMap NULL)"), ProcessCommand(_T("0")));
                    break;

                case _T('3'):
                    ReportAndQuit(_T("LoadKeyMap 12-key"), ProcessCommand(_T("12")));
                    break;
                    
                case _T('4'):
                    ReportAndQuit(_T("LoadKeyMap 15-key"), ProcessCommand(_T("15")));
                    break;

                case _T('5'):
                    ReportAndQuit(_T("LoadKeyMap 30-key"), ProcessCommand(_T("30")));
                    break;

                case _T('6'):
                {
                    // Try to load a custom mapping from the release directory first
                    HRESULT hrCommand = ProcessCommand(_T("\\release\\Mapping.txt"));
                    if (FAILED(hrCommand))
                    {
                        // Let's try just the file name
                        // This typically means the root will be searched
                        hrCommand = ProcessCommand(_T("Mapping.txt"));
                    }
                    ReportAndQuit(_T("LoadKeyMap Mapping.txt"), hrCommand);
                    break;
                }

                default:
                    // Unsupported input
                    // Nothing to do since our directions are already showing
                    break;
            }

            fHandled = TRUE;
            break;
            
        case WM_CLOSE:
            DestroyWindow(hwnd);
            fHandled = TRUE;
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            fHandled = TRUE;
            break;
    }

    return (fHandled ? 0 : DefWindowProc(hwnd, umsg, wParam, lParam));
}

/***********************************************************************

FUNCTION: 
  InitInstance

PURPOSE: 
  Create and display the main window.

***********************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int iCmdShow)
{
    g_hwndMain = CreateWindow (
                    gc_szClassName,  // Registered class name         
                    gc_szTitle,      // Application window name
                    WS_OVERLAPPED,  // Window style
                    CW_USEDEFAULT,  // Horizontal position of the window
                    CW_USEDEFAULT,  // Vertical position of the window
                    CW_USEDEFAULT,  // Window width
                    CW_USEDEFAULT,  // Window height
                    NULL,           // Handle to the parent window
                    NULL,           // Handle to the menu the identifier
                    hInstance,      // Handle to the application instance
                    NULL);          // Pointer to the window-creation data

    if (g_hwndMain)
    {
        ShowWindow(g_hwndMain, iCmdShow);
        UpdateWindow(g_hwndMain);

        // We don't need an IME
        ImmDisableIME(0);

        // Set keyboard input mode to numbers
        SHSetImeMode(g_hwndMain, SHIME_MODE_NUMBERS);

        // Show directions
        DrawTextWrapper(_T(""));
    }
    
    return (BOOL)(NULL != g_hwndMain);
}

/***********************************************************************

FUNCTION: 
  InitApplication

PURPOSE:
  Declare the window class structure, assign values to the window class
  structure members, and register the window class.

***********************************************************************/
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS wndclass;
  
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = (WNDPROC)WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hIcon = NULL;
    wndclass.hInstance = hInstance;
    wndclass.hCursor = NULL;
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = gc_szClassName;
    
    return RegisterClass(&wndclass);
}

/***********************************************************************

FUNCTION: 
  WinMain

PURPOSE: 
  The WinMain function of the application. It is called by the system as
  the initial entry point for this Windows CE-based application.

***********************************************************************/
BOOL WINAPI WinMain (HINSTANCE hInstance,     // Handle to the current instance
                    HINSTANCE hPrevInstance, // Handle to the previous instance
                    LPWSTR lpCmdLine,        // Pointer to the command line
                    int iCmdShow)            // Shows the state of the window
{
    HWND hwnd = FindWindow(gc_szClassName, gc_szTitle);
    MSG msg = {0};                             
    
    // Prevent the application from starting twice
    if (hwnd)
    {
        // Bring previous instance of application to the foreground
        SetForegroundWindow(hwnd);
        return FALSE;
    }

    // We don't want IME interference
    ImmDisableIME(0);
  
    if (!hPrevInstance && (!InitApplication(hInstance) || !InitInstance(hInstance, iCmdShow)))
    {
        return FALSE; 
    }

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  
    return msg.wParam;
}
