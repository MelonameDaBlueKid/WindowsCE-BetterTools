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
#include <windowsx.h>
#include <aygshell.h>

#include <initguid.h>

#define INITGUID
#include <imaging.h>
#include "resource.h"
#include "dialer.h"
#include "main.h"
#include "macros.h"


HINSTANCE   ghInst;
const TCHAR c_szMainWndClass[] = TEXT("PictureDial.MainWnd");
const TCHAR c_szWndTitle[]     = TEXT("PictureDial");


HRESULT RegisterWindowClass()
{
    WNDCLASS wc;
    static BOOL fRegistered;

    if (fRegistered)
    {
        return S_OK;
    }

    if (GetClassInfo(ghInst, c_szMainWndClass, &wc) == FALSE)
    {
        ZeroMemory(&wc, sizeof(wc));

        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = CPictureDial::_WndProc;
        wc.hInstance = ghInst;
        wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wc.lpszClassName = c_szMainWndClass;

        fRegistered = RegisterClass(&wc);
    }

    return (fRegistered ? S_OK : E_FAIL);
}


int APIENTRY WinMain
(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    pszCmdLine,
    int       nCmdShow
)
{
    HRESULT      hr = S_OK;
    int          iRetVal = 0;
    BOOL         fSuccess;
    HWND         hWnd;
    MSG          msg;
    CPictureDial pd;
    RECT         rc;

    ghInst = hInstance;

    hr = RegisterWindowClass();
    CHR(hr);

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    CHR(hr);

    fSuccess = SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
    CBR(fSuccess);

    // Create the main window
    hWnd = CreateWindow(c_szMainWndClass,
                        c_szWndTitle,
                        WS_VISIBLE,
                        rc.left,
                        rc.top,
                        rc.right-rc.left,
                        rc.bottom-rc.top,
                        NULL,
                        NULL,
                        ghInst,
                        &pd);

    CBR(hWnd);

    // Main message loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
        {
            // WinMain should return the wParam part of WM_QUIT
            iRetVal = msg.wParam;
        }
    }


Error:
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("Unable to start application."), TEXT("Error"), MB_OK);
    }

    return iRetVal;
}

