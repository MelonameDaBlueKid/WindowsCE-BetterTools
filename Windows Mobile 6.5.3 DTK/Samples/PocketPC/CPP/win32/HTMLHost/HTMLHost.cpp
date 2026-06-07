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

#define MENU_HEIGHT 26

#define WC_HTMLCONTAINER TEXT("HTMLContainer")
LRESULT TestWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// RegisterTestClass
/////////////////////////////////////////////////////////////////////////////
HRESULT RegisterTestClass
(
    HINSTANCE hInstance
)
{
    WNDCLASS    wc = { 0 };
    HRESULT     hrResult;

    if (!GetClassInfo(hInstance, WC_HTMLCONTAINER, &wc))
    {
        wc.style            = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc      = TestWndProc;
        wc.hInstance        = hInstance;
        wc.lpszClassName    = WC_HTMLCONTAINER;
        wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);

        hrResult = (RegisterClass(&wc) ? S_OK : E_FAIL);
    }
    else
        hrResult = S_OK;

    return hrResult;
}

/////////////////////////////////////////////////////////////////////////////
// WinMain
/////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain
(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPWSTR      lpCmdLine,
    int         nCmdShow
)
{
    HWND hwndParent;
    HWND hwndHTML;

    VERIFY(SUCCEEDED(RegisterTestClass(hInstance)));

    hwndParent = CreateWindow(  WC_HTMLCONTAINER,
                                NULL,
                                WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                240, 280,
                                NULL,
                                NULL,
                                hInstance,
                                0);

    RECT rc;
    GetWindowRect(hwndParent, &rc);

    SHFullScreen(hwndParent, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON);

    MoveWindow( hwndParent, 
                rc.left, 
                rc.top - MENU_HEIGHT, 
                rc.right, 
                rc.bottom + MENU_HEIGHT, 
                TRUE);   

    VERIFY(InitHTMLControl(hInstance));

    hwndHTML = CreateWindow(WC_HTML,
                            NULL,
                            WS_CHILD
                                | WS_BORDER
                                | WS_VISIBLE,
                            5,
                            5,
                            (rc.right - rc.left) - 10,
                            (rc.bottom - rc.top) - 10,
                            hwndParent,
                            NULL,
                            hInstance,
                            NULL);

    if (hwndHTML != NULL)
    {
        // Navigate to pocketpc.com
        BSTR bstrURL = SysAllocString(TEXT("http://www.pocketpc.com"));
        SendMessage(hwndHTML, DTM_NAVIGATE, 0, (LPARAM)bstrURL);
        SysFreeString(bstrURL);
        
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// TestWndProc
/////////////////////////////////////////////////////////////////////////////
LRESULT TestWndProc
(
    HWND    hwnd,
    UINT    uMsg,
    WPARAM  wParam,
    LPARAM  lParam
)
{
    LRESULT lResult = 0;

    switch (uMsg)
    {
        case WM_NOTIFY:
        {
            NMHDR * pnmh = (NMHDR *)lParam;

            switch (pnmh->code)
            {
                case NM_HOTSPOT:
                {
                    OutputDebugString(TEXT("NM_HOTSPOT\r\n"));
                    break;
                }
                
                case NM_INLINE_IMAGE:
                {
                    OutputDebugString(TEXT("NM_INLINE_IMAGE\r\n"));
                    break;
                }

                case NM_INLINE_SOUND:
                {
                    OutputDebugString(TEXT("NM_INLINE_SOUND\r\n"));
                    break;
                }

                case NM_TITLE:
                {
                    OutputDebugString(TEXT("NM_TITLE\r\n"));
                    break;
                }

                case NM_META:
                {
                    OutputDebugString(TEXT("NM_META\r\n"));
                    break;
                }

                case NM_BASE:
                {
                    OutputDebugString(TEXT("NM_BASE\r\n"));
                    break;
                }

                case NM_CONTEXTMENU:
                {
                    OutputDebugString(TEXT("NM_CONTEXTMENU\r\n"));
                    break;
                }

                case NM_INLINE_XML:
                {
                    OutputDebugString(TEXT("NM_INLINE_XML\r\n"));
                    break;
                }

                case NM_BEFORENAVIGATE:
                {
                    OutputDebugString(TEXT("NM_BEFORENAVIGATE\r\n"));
                    break;
                }

                case NM_DOCUMENTCOMPLETE:
                {
                    OutputDebugString(TEXT("NM_DOCUMENTCOMPLETE\r\n"));
                    break;
                }

                case NM_NAVIGATECOMPLETE:
                {
                    OutputDebugString(TEXT("NM_NAVIGATECOMPLETE\r\n"));
                    break;
                }

                case NM_TITLECHANGE:
                {
                    OutputDebugString(TEXT("NM_TITLECHANGE\r\n"));
                    break;
                }

                default:
                {
                    ASSERT(FALSE);
                    break;
                }
            }

            break;
        }

        case WM_LBUTTONDOWN:
        {
            DestroyWindow(hwnd);
            break;
        }
            
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
            
        default:
        {
            lResult = DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
        }
    }

    return lResult;
}


