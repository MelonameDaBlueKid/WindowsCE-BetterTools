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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <aygshell.h>
#include "resource.h"

// helper macros
#define ARRAYSIZE(a) (UINT_PTR)(sizeof(a)/sizeof((a)[0]))

// strings
static const TCHAR g_szClassName[] = TEXT("ClassName");

// function declarations
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);
HANDLE FindPrevInstance();
HWND CreateMainWindow(int nShowCmd);
BOOL OnCreateMainWindow(HWND hwnd);
void PaintMainWindow(HWND hwnd);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

HBITMAP LoadPaintImage(LPTSTR pszLabel, UINT_PTR cchLabel);
HFONT LoadPaintFont();
void FreePaintImage();
void FreePaintFont();

// global variables
HINSTANCE g_hInstance;
HBITMAP   g_hBitmapPaint = NULL;
HFONT     g_hFontPaint = NULL;
DWORD     g_dwFontSize;
DWORD     g_dwCurrentImage = 0;
UINT      g_uMsgMetricChange = RegisterWindowMessage(SH_UIMETRIC_CHANGE);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	HANDLE hEvent;
    HWND   hwnd;
    MSG    msg;

    // Save the instance handle so we can access it later
    g_hInstance = hInstance;

	// Check to see if this application is already running
	hEvent = FindPrevInstance();
	if (hEvent == NULL)
	{
		// We found another instance
		return -1;
	}

    // Create our main application window
    hwnd = CreateMainWindow(nShowCmd);
    if (hwnd == NULL)
    {
        // Failed to initialize
		CloseHandle(hEvent);
        return GetLastError();
    }

    // Run the message loop (note that GetMessage() returns -1 for error)
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	// Clean up
	FreePaintImage();
	FreePaintFont();

    // This is the value we passed to PostQuitMessage()
	CloseHandle(hEvent);
    return msg.wParam;
}

HANDLE FindPrevInstance()
{
	HANDLE hEvent;
	HWND   hwnd;
	UINT   cTries = 0;

	// Create a named event
	hEvent = CreateEvent(NULL, TRUE, FALSE, g_szClassName);
	if (hEvent != NULL)
	{
		// If the event already existed, that means there's another copy of our app
		// already running
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			do
			{
				// Just in case the other window needs to finish initialization
				Sleep(cTries ? 250 : 0);

				// Try to find the other application window
				hwnd = FindWindow(g_szClassName, NULL);
				if (hwnd != NULL)
				{
					SetForegroundWindow((HWND)((UINT_PTR)hwnd | 0x01));
					CloseHandle(hEvent);
					return NULL;
				}
			}
			while (++cTries < 2);  // only try twice

			// If we didn't find the window, the other application was probably
			// shutting down, so we'll just continue
		}
	}

	// Done
	return hEvent;
}

HWND CreateMainWindow(int nShowCmd)
{
    WNDCLASS wc;
    ATOM     atm;
    TCHAR    szTitle[128];
    HWND     hwnd;

    // Set up the window class description
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = g_hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;

	// We want to redraw the window contents anytime we get resized. That way
	// we'll respond appropriately when the user switches between portrait and
	// landscape. If we had any child windows or controls, we'd need to
	// reposition or resize them when we get a WM_SIZE message.
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // Register the window class
    atm = RegisterClass(&wc);
    if (atm == 0)
    {
        // Failed!!
        return NULL;
    }

    // Load the window title string resource
    if (!LoadString(g_hInstance, IDS_APPTITLE, szTitle, ARRAYSIZE(szTitle)))
    {
        // Failed!!
        return NULL;
    }

    // Create a window using the class we just registered. Note that the
	// initial size and position don't matter, because we're going to make it
	// fullscreen when we get WM_CREATE, before it's ever displayed.
    hwnd = CreateWindow((LPCTSTR)atm, szTitle, WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, g_hInstance, NULL);
    if (hwnd == NULL)
    {
        // Failed!!
        return NULL;
    }

    // Make the window visible and paint before returning
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);
    return hwnd;
}

BOOL OnCreateMainWindow(HWND hwnd)
{
	SHMENUBARINFO shmbi;
	SHINITDLGINFO shidi;

	// Create our softkey bar
	ZeroMemory(&shmbi, sizeof(shmbi));
	shmbi.cbSize = sizeof(shmbi);
	shmbi.hwndParent = hwnd;
	shmbi.dwFlags = SHCMBF_HMENU;
	shmbi.nToolBarId = IDM_MAIN;
	shmbi.hInstRes = g_hInstance;
	if (!SHCreateMenuBar(&shmbi))
	{
		// Failed!!
		return FALSE;
	}

	// Windows Mobile applications should always display their main window
	// full-screen. We're going to let the OS do this for us by calling
	// SHInitDialog, even though technically this window isn't a dialog window.
	shidi.dwMask = SHIDIM_FLAGS;
	shidi.hDlg = hwnd;
	shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_SIPDOWN;
	if (!SHInitDialog(&shidi))
	{
		// Failed!!
		return FALSE;
	}

	// Get the current user preference for text size
	SHGetUIMetrics(SHUIM_FONTSIZE_PIXEL,
		&g_dwFontSize, sizeof(g_dwFontSize), NULL);

	// Success
	return TRUE;
}

void PaintMainWindow(HWND hwnd)
{
	PAINTSTRUCT ps;
	int         nSavedDC;
	HBITMAP     hBitmap, hOldBitmap;
	TCHAR       szLabel[64];
	HFONT       hFont;
	RECT        rect;
	BITMAP      bm;
	int         cy;
	HDC         hMemDC;

	// Start the paint operation
	if (!GetUpdateRect(hwnd, NULL, FALSE) ||
		BeginPaint(hwnd, &ps) == NULL)
	{
		return;
	}

	// Load the correct image and get its label
	hBitmap = LoadPaintImage(szLabel, ARRAYSIZE(szLabel));
	if (hBitmap != NULL)
	{
		// Load the display font
		hFont = LoadPaintFont();
		if (hFont != NULL)
		{
			// Save the device context state
			nSavedDC = SaveDC(ps.hdc);

			// Calculate the height of our display image and text
			GetObject(hBitmap, sizeof(bm), &bm);
			cy = bm.bmHeight;

			SelectObject(ps.hdc, hFont);
			GetClientRect(hwnd, &rect);
			cy += DrawText(ps.hdc, szLabel, -1, &rect,
				DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);

			// Draw the image
			GetClientRect(hwnd, &rect);
			hMemDC = CreateCompatibleDC(ps.hdc);
			if (hMemDC != NULL)
			{
				hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
				BitBlt(ps.hdc, (rect.right - bm.bmWidth) / 2,
					(rect.bottom - cy) / 2, bm.bmWidth, bm.bmHeight,
					hMemDC, 0, 0, SRCCOPY);
				SelectObject(hMemDC, hOldBitmap);
				DeleteDC(hMemDC);
			}

			// Draw the text
			rect.top = (rect.bottom - cy) / 2 + bm.bmHeight;
			DrawText(ps.hdc, szLabel, -1, &rect,
				DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);

			// Restore the device context
			RestoreDC(ps.hdc, nSavedDC);
		}
	}

	// Always need to finish!!
	EndPaint(hwnd, &ps);
}

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static SHACTIVATEINFO sai;

    switch (msg)
    {
    case WM_CREATE:
		// Initialize the static window state information. The shell helper functions
		// will use this buffer to store their state.
		ZeroMemory(&sai, sizeof(sai));
		sai.cbSize = sizeof(sai);

		// Initialize the window (if we fail, return -1)
        return (OnCreateMainWindow(hwnd) ? 0 : -1);

	case WM_ACTIVATE:
		// Calling this function when we get WM_ACTIVATE ensures that our
		// application will handle the SIP properly. This function does
		// nothing when we're running on Smartphone.
		SHHandleWMActivate(hwnd, wp, lp, &sai, 0);
		break;

	case WM_SETTINGCHANGE:
		// This helper function will resize our main application window when the SIP
		// goes up and down. Try commenting out this function and see how it affects
		// our drawing code. This function is optional, so choose whichever behavior
		// you prefer. Again, this function does nothing on Smartphone.
		SHHandleWMSettingChange(hwnd, wp, lp, &sai);
		break;

	case WM_HIBERNATE:
		// We get this message when the device is running low on memory. All
		// applications should free any memory and resources that they can. We'll
		// free our cached bitmap and font, since we can just re-create them the next
		// time we need them.
		FreePaintImage();
		FreePaintFont();
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wp) == ID_SWITCH)
		{
			// Switch to our next image
			g_dwCurrentImage = !g_dwCurrentImage;
			FreePaintImage();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;

    case WM_KEYDOWN:
        // Allow Ctrl+Q to quit the application. Most users won't ever see
        // this, but it's handy for debugging.
        if (wp == 'Q' &&
            GetKeyState(VK_CONTROL) < 0)
        {
            SendMessage(hwnd, WM_CLOSE, 0, 0);
        }
        break;

	case WM_PAINT:
		PaintMainWindow(hwnd);
		return 0;

    case WM_DESTROY:
        // When this window is destroyed, it's time to quit the application
        PostQuitMessage(0);
        break;
    }

	if (msg == g_uMsgMetricChange)
	{
		DWORD dwFontSize;

		// The UI metrics have changed. This is how we get notified when the
		// user changes their preferred font size (PPC only). We free our
		// cached font and save the new size for the next time we paint.
		if (SUCCEEDED(SHGetUIMetrics(SHUIM_FONTSIZE_PIXEL,
			&dwFontSize, sizeof(dwFontSize), NULL)) &&
			dwFontSize != g_dwFontSize)
		{
			g_dwFontSize = dwFontSize;
			FreePaintFont();
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}

    return DefWindowProc(hwnd, msg, wp, lp);
}

HBITMAP LoadPaintImage(LPTSTR pszLabel, UINT_PTR cchLabel)
{
	// Load the current label string
	pszLabel[0] = 0;
	LoadString(g_hInstance, IDS_LABEL1 + g_dwCurrentImage,
		pszLabel, cchLabel);

	// Load the current image
	if (g_hBitmapPaint == NULL)
	{
		// Note that the resource type must be "GIF", but actually the resource
		// data can contain a BMP, GIF, JPG, or PNG image. This enables us to
		// pick the best image format for our purposes (quality, size, etc).
		g_hBitmapPaint = SHLoadImageResource(g_hInstance,
			IDR_IMAGE1 + g_dwCurrentImage);
	}

	// Return the cached image handle
	return g_hBitmapPaint;
}

HFONT LoadPaintFont()
{
	LOGFONT lf;

	if (g_hFontPaint == NULL)
	{
		// Create the font handle
		ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = -(LONG)g_dwFontSize;
		lf.lfWeight = FW_NORMAL;
		lf.lfCharSet = DEFAULT_CHARSET;
		lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
		g_hFontPaint = CreateFontIndirect(&lf);
	}

	// Return the cached font handle
	return g_hFontPaint;
}

void FreePaintImage()
{
	if (g_hBitmapPaint != NULL)
	{
		DeleteObject(g_hBitmapPaint);
		g_hBitmapPaint = NULL;
	}
}

void FreePaintFont()
{
	if (g_hFontPaint != NULL)
	{
		DeleteObject(g_hFontPaint);
		g_hFontPaint = NULL;
	}
}
