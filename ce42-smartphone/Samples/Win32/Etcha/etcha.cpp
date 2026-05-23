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
///////////////////////////////////////////////////////////////////////////////
//
// ETCHA.CPP
//
// Simple Drawing Program
//
#include "windows.h"
#include "aygshell.h"
#include "newres.h"
#include "resource.h"


#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

// Global variables
HWND		g_hWndMain;
HINSTANCE	g_hInst;
RECT		g_rc;
int			g_ix;
int			g_iy;

LRESULT CALLBACK
WndProc ( 
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam 
	)
{

    static POINT line[2];
	BOOL bDrawPoint = FALSE;

    switch (Msg) {
		case WM_CREATE :
			// set up Soft Keys menu
			SHMENUBARINFO mbi;
			ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
			mbi.cbSize = sizeof(SHMENUBARINFO);
			mbi.hwndParent = hWnd;
			mbi.nToolBarId = IDR_ETCHA_MENUBAR;
			mbi.hInstRes = g_hInst;

			if (FALSE == SHCreateMenuBar(&mbi)) {
		        // Couldn't create the menu bar.  Fail creation of the window.
				return -1;
			}

			break;

		case WM_PAINT :
			// Paint Main window, inking on main window not saved
			// window is repainted blank
		    HDC hdc;
		    RECT rect;
			PAINTSTRUCT ps;
			hdc = BeginPaint (hWnd, &ps);
			GetClientRect(hWnd, &rect);
			FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			SetPixel(hdc,g_ix,g_iy,PALETTEINDEX2BPP(1));
			EndPaint (hWnd, &ps);
			break;

		case WM_KEYDOWN:
			line[0].x = g_ix;
			line[0].y = g_iy;

			switch (wParam) 
			{
				case VK_UP:
					if (--g_iy < g_rc.top) 
					{
						g_iy = g_rc.top;
					}
					bDrawPoint = TRUE;
					break;

				case VK_DOWN:
					if (++g_iy >= g_rc.bottom) 
					{
						g_iy = g_rc.bottom-1;
					}
					bDrawPoint = TRUE;
					break;

				case VK_LEFT:
					if (--g_ix < g_rc.left) 
					{
						g_ix = g_rc.left;
					}
					bDrawPoint = TRUE;
					break;

				case VK_RIGHT:
					if (++g_ix >= g_rc.right) 
					{
						g_ix = g_rc.right-1;
					}
					bDrawPoint = TRUE;
					break;
			}

			if (TRUE == bDrawPoint) 
			{
				VERIFY(hdc = GetDC(hWnd));
			
				SetPixel(hdc, g_ix ,g_iy,PALETTEINDEX2BPP(1));
			}

			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) 
			{
				case IDM_ETCHA_QUIT:
                    DestroyWindow(hWnd);
					break;

				case IDM_ETCHA_CLEAR:
					// you could set the cursor back to the center, but a real
					// etch-a-sketch wouldn't behave that way...
					// g_ix = (g_rc.right-g_rc.left) / 2;
					// g_iy = (g_rc.bottom-g_rc.top) / 2;

					// invalidate the client area and repaint
					InvalidateRect (hWnd, NULL, TRUE);
					UpdateWindow(hWnd);
					break;

				default:
					return DefWindowProc(hWnd, Msg, wParam, lParam);
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
    while (cTries > 0)
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


/*****************************************************************************

  WinMain

  ***************************************************************************/


int WINAPI WinMain (
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nShowCmd
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
    LoadString(hInstance, APPNAME, tszAppName, ARRAY_LENGTH(tszAppName));
    LoadString(hInstance, TITLE, tszTitle, ARRAY_LENGTH(tszTitle));

    if(FAILED(ActivatePreviousInstance(tszAppName, tszTitle, &fActivated)) ||
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

    if (RegisterClass(&wc) == FALSE)
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

	// set cursor starting pos
	GetClientRect(g_hWndMain, &g_rc);
	g_ix = (g_rc.right-g_rc.left) / 2;
	g_iy = (g_rc.bottom-g_rc.top) / 2;

    UpdateWindow(g_hWndMain);
    ShowWindow(g_hWndMain, nShowCmd);

    while (GetMessage(&msg, NULL, 0, 0) == TRUE)
    {
        DispatchMessage(&msg);
    }

    return msg.wParam;
}