///////////////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  This is "Sample Code" and is distributable subject to the terms of the end
//  user license agreement.
//
//
///////////////////////////////////////////////////////////////////////////////
//
// DRAWINGTEXT.CPP
//
// Draws sample text on the screen
//

#include <windows.h>
#include <aygshell.h>
#include "resource.h"

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

// Global variables
HWND g_hWndMain;
HINSTANCE g_hInst;


LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam 
	)
{

	switch (Msg) 
	{
	case WM_CREATE:
		// set up Soft Keys menu
		SHMENUBARINFO mbi;
		ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
		mbi.cbSize = sizeof(SHMENUBARINFO);
		mbi.hwndParent = hWnd;
		mbi.nToolBarId = IDR_DT_MENUBAR;
		mbi.hInstRes = g_hInst;

		if (FALSE == SHCreateMenuBar(&mbi)) {
		    // Couldn't create the menu bar.  Fail creation of the window.
			return -1;
		}

		break;

	case WM_COMMAND:
		switch (wParam) 
		{
			case IDM_DT_QUIT:
                DestroyWindow(hWnd);
				break;

			default:
				return DefWindowProc(hWnd, Msg, wParam, lParam);
		}

		break;

	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT	ps;
			RECT rcString, rcClient;
			POINT ptTrig[4]; 
			INT i, cy;

			GetClientRect (hWnd, &rcClient);
			hdc = BeginPaint (hWnd, &ps);
			
			ptTrig[0].x = ptTrig[3].x = ptTrig[1].x = rcClient.left;
			ptTrig[0].y = ptTrig[3].y = rcClient.top;
			ptTrig[2].y = ptTrig[1].y = rcClient.bottom;
			ptTrig[2].x = rcClient.right;
			SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
			Polygon(hdc, ptTrig, 4);
			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			ptTrig[0].x = ptTrig[3].x = ptTrig[2].x /2; 
			ptTrig[0].y = ptTrig[3].y = ptTrig[2].y /3; 
			Polygon(hdc, ptTrig, 4);
			SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));

			// DT_CALCRECT fills in &rcString with the height/width of string
			DrawText (hdc, TEXT ("Sample DrawText"), -1, &rcString, 
				DT_CALCRECT | DT_CENTER | DT_SINGLELINE);
			// Text rectangle size plus some padding
			cy = rcString.bottom - rcString.top + 5;

			rcClient.bottom = rcClient.top + cy;
			SetBkMode (hdc, TRANSPARENT);
			for (i = 0; i < 4; i++) 
			{
				SetTextColor (hdc, PALETTEINDEX2BPP(i));
				SetBkColor (hdc, PALETTEINDEX2BPP(3 -i));
				DrawText (hdc, TEXT ("Sample DrawText Here"), -1, &rcClient, DT_CENTER | DT_SINGLELINE);
				rcClient.top += cy;
				rcClient.bottom += cy;
			}

			SetBkMode (hdc, OPAQUE);
			for (i = 0; i < 4; i++) 
			{
				SetTextColor (hdc, PALETTEINDEX2BPP(i));
				SetBkColor (hdc, PALETTEINDEX2BPP(3 -i));
				DrawText (hdc, TEXT ("Sample DrawText Here"), -1, &rcClient, DT_CENTER | DT_SINGLELINE);
				rcClient.top += cy;
				rcClient.bottom += cy;
			}
			EndPaint(hWnd, &ps);
		}
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}


/****************************************************************************

   ActivatePreviousInstance

  ****************************************************************************/
HRESULT ActivatePreviousInstance(
    const TCHAR* lptszClass,
    const TCHAR* lptszTitle,
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
        hMutex = CreateMutex(NULL, FALSE, lptszClass); // NOTE: We don't want to own the object.
        if(NULL == hMutex)
        {
            // Something bad happened, fail.
            hr = E_FAIL;
            goto Exit;
        }

        if(ERROR_ALREADY_EXISTS == GetLastError())
        {
            HWND hwnd;

            CloseHandle(hMutex);
            hMutex = NULL;

            // There is already an instance of this app
            // running.  Try to bring it to the foreground.

            hwnd = FindWindow(lptszClass, lptszTitle);
            if(NULL == hwnd)
            {
                // It's possible that the other window is in the process of being created...
                Sleep(500);
                hwnd = FindWindow(lptszClass, lptszTitle);
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


/*****************************************************************************

  WinMain

  ***************************************************************************/


int WINAPI WinMain( 
	HINSTANCE hInstance,
	HINSTANCE hPreviousInstance,
	LPWSTR pszCommandLine,
	int nCommandShow
	)
{
    WNDCLASS wc;
    MSG msg;
    TCHAR tszAppName[80];
	TCHAR tszTitle[80];
    BOOL fActivated;

    // Pass value to global g_hInst for use in WndProc
    g_hInst = hInstance;

    // Load strings
    LoadString(hInstance, IDS_DT_APPNAME, tszAppName, ARRAY_LENGTH(tszAppName));
    LoadString(hInstance, IDS_DT_TITLE, tszTitle, ARRAY_LENGTH(tszTitle));

    if (FAILED(ActivatePreviousInstance(tszAppName, tszTitle, &fActivated)) ||
            fActivated)
    {
		// Exit immediately if previous instance exists
        return 0;
    }

    // Register our main window's class.
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = tszAppName;

    if (FALSE == RegisterClass(&wc) )
    {
        OutputDebugString(TEXT("RegisterClass Failed\n"));
        return 0;
    }

	g_hWndMain = CreateWindow(tszAppName, tszTitle,
                              WS_CLIPCHILDREN, // Setting this to 0 gives a default style we don't want.  Use a benign style bit instead.
                              CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                              NULL, NULL, hInstance, NULL );
    if (NULL == g_hWndMain)
    {
        OutputDebugString(TEXT("CreateWindow Failed\n"));
        return 0;
    }

	UpdateWindow(g_hWndMain);
    ShowWindow(g_hWndMain, nCommandShow);

    while (GetMessage(&msg, NULL, 0, 0) == TRUE)
    {
        DispatchMessage(&msg);
    }

    return msg.wParam;
}