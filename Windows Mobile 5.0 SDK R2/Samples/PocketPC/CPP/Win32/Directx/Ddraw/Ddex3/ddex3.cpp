//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
//-----------------------------------------------------------------------------
// File: DDEx3.CPP
//
// Desc: Direct Draw example program 3.  Adds functionality to 
//       example program 2.  Creates two offscreen surfaces in 
//       addition to the primary surface and back buffer.  Loads
//       a bitmap file into each offscreen surface.  Uses BltFast
//       to copy the contents of an offscreen surface to the back
//       buffer and then flips the buffers and copies the next 
//       offscreen surface to the back buffer.  Press F12 to exit
//       the program.  This program requires at least 1.2 Megs of 
//       video ram.
//
//-----------------------------------------------------------------------------

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include <windows.h>
#include <ddraw.h>
#include "resource.h"
#include "ddutil.h"
#include "winuserm.h"

//-----------------------------------------------------------------------------
// Local definitions
//-----------------------------------------------------------------------------
#define NAME                TEXT("DDExample3")
#define TITLE               TEXT("Direct Draw Example 3")

//-----------------------------------------------------------------------------
// Default settings
//-----------------------------------------------------------------------------
#define TIMER_ID            1
#define TIMER_RATE          500

//-----------------------------------------------------------------------------
// Global data
//-----------------------------------------------------------------------------
LPDIRECTDRAW                g_pDD = NULL;            // DirectDraw object
LPDIRECTDRAWSURFACE         g_pDDSPrimary = NULL;    // DirectDraw primary surface
LPDIRECTDRAWSURFACE         g_pDDSBack = NULL;       // DirectDraw back surface
LPDIRECTDRAWSURFACE         g_pDDSOne = NULL;        // Offscreen surface 1
LPDIRECTDRAWSURFACE         g_pDDSTwo = NULL;        // Offscreen surface 2
BOOL                        g_bActive = FALSE;       // Is application active?
LPCTSTR                     g_szErrorMessage = NULL; // Error message to display.

//-----------------------------------------------------------------------------
// Local data
//-----------------------------------------------------------------------------
// Name of our bitmap resource.
static TCHAR                szBitmap[] = TEXT("DDEX3");
static const TCHAR          szDDrawError[] = TEXT("DirectDraw Error");
static const TCHAR          szDDrawFailedMsg[] = TEXT("DirectDrawCreate failed.");
static const TCHAR          szSetCooperativeFailMsg[] = TEXT("SetCooperativeLevel failed.");
static const TCHAR          szNoBackBufferMsg[] = TEXT("Display driver doesn't support a back buffer.");
static const TCHAR          szNoFlipSurfacesMsg[] =TEXT("Display driver doesn't support flipping surfaces.");
static const TCHAR          szEnumAttachedSurfacesFailMsg[] = TEXT("EnumAttachedSurfaces failed.");
static const TCHAR          szCreateSurfaceFailMsg[] = TEXT("CreateSurface failed.");
static const TCHAR          szSetTimerFailMsg[] = TEXT("SetTimer failed.");
static const TCHAR          szInitSurfacesFailMsg[] = TEXT("InitSurfaces failed.");
static HINSTANCE            hInstance;

//-----------------------------------------------------------------------------
// Name: ReleaseAllObjects()
// Desc: Finished with all objects we use; release them
//-----------------------------------------------------------------------------
static void
ReleaseAllObjects(void)
{
    if (g_pDDSBack != NULL)
    {
        g_pDDSBack->Release();
        g_pDDSBack = NULL;
    }
    if (g_pDDSPrimary != NULL)
    {
        g_pDDSPrimary->Release();
        g_pDDSPrimary = NULL;
    }
    if (g_pDDSOne != NULL)
    {
        g_pDDSOne->Release();
        g_pDDSOne = NULL;
    }
    if (g_pDDSTwo != NULL)
    {
        g_pDDSTwo->Release();
        g_pDDSTwo = NULL;
    }
    if (g_pDD != NULL)
    {
        g_pDD->Release();
        g_pDD = NULL;
    }
}




//-----------------------------------------------------------------------------
// Name: InitFail()
// Desc: This function is called if an initialization function fails
//-----------------------------------------------------------------------------
HRESULT
InitFail(HWND hWnd, HRESULT hRet, LPCTSTR szError,...)
{
    ReleaseAllObjects();
    DestroyWindow(hWnd);
    g_szErrorMessage = szError;
    return hRet;
}


//-----------------------------------------------------------------------------
// Name: InitSurfaces()
// Desc: This function reads the bitmap file FRNTBACK.BMP and stores half of it
//       in offscreen surface 1 and the other half in offscreen surface 2.
//-----------------------------------------------------------------------------
BOOL 
InitSurfaces()
{
    HBITMAP hbm;

    // Load our bitmap resource.
    hbm = DDGetBitmapHandle(hInstance,szBitmap);
    if (hbm == NULL)
        return FALSE;

    DDCopyBitmap(g_pDDSOne, hbm, 0, 0, 640, 480);
    DDCopyBitmap(g_pDDSTwo, hbm, 0, 480, 640, 480);
    DeleteObject(hbm);
    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: RestoreAll()
// Desc: Restore all lost objects
//-----------------------------------------------------------------------------
HRESULT 
RestoreAll()
{
    HRESULT                     hRet;

    hRet = g_pDDSPrimary->Restore();
    if (hRet == DD_OK)
    {
        hRet = g_pDDSOne->Restore();
        if (hRet == DD_OK)
        {
            hRet = g_pDDSTwo->Restore();
            if (hRet == DD_OK)
            {
                InitSurfaces();
            }
        }
    }
    return hRet;
}




//-----------------------------------------------------------------------------
// Name: UpdateFrame()
// Desc: Displays the proper image for the page
//-----------------------------------------------------------------------------
static void
UpdateFrame(HWND hWnd)
{
    static BYTE                 phase = 0;
    HRESULT                     hRet;
    LPDIRECTDRAWSURFACE         pdds;
    DDBLTFX                     ddbltfx;

    memset(&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwROP = SRCCOPY;

    if (phase)
    {
        pdds = g_pDDSTwo;
        phase = 0;
    }
    else
    {
        pdds = g_pDDSOne;
        phase = 1;
    }
    while (TRUE)
    {
        hRet = g_pDDSBack->Blt(NULL, pdds, NULL, DDBLT_ROP, &ddbltfx);
        if (hRet == DD_OK)
            break;
        if (hRet == DDERR_SURFACELOST)
        {
            hRet = RestoreAll();
            if (hRet != DD_OK)
                break;
        }
        if (hRet != DDERR_WASSTILLDRAWING)
            break;
    }
}


//-----------------------------------------------------------------------------
// Name: EnumFunction()
// Desc: Enumeration callback for surfaces in flipping chain. We expect this
//          function to be called once with the surface interface pointer of
//          our back buffer (we only ask for a single back buffer.)
//-----------------------------------------------------------------------------
static HRESULT PASCAL
EnumFunction(LPDIRECTDRAWSURFACE pSurface,
             LPDDSURFACEDESC lpSurfaceDesc,
             LPVOID  lpContext)
{
    static BOOL bCalled = FALSE;

    if (!bCalled) {

        *((LPDIRECTDRAWSURFACE *)lpContext) = pSurface;
        bCalled = TRUE;
        return DDENUMRET_OK;
    }
    else {

        OutputDebugString(L"DDEX3: Enumerated more than surface?");
        pSurface->Release();
        return DDENUMRET_CANCEL;
    }
}


//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
long FAR PASCAL
WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HRESULT                     hRet;

    switch (message)
    {
#ifdef UNDER_CE
        case WM_ACTIVATE:
#else
        case WM_ACTIVATEAPP:
#endif
            // Pause if minimized or not the top window
            g_bActive = (wParam == WA_ACTIVE) || (wParam == WA_CLICKACTIVE);
            return 0L;

        case WM_DESTROY:
            // Clean up and close the app
            ReleaseAllObjects();
            PostQuitMessage(0);
            return 0L;

        case WM_KEYDOWN:
            // Handle any non-accelerated key commands
            switch (wParam)
            {
                case VK_ACTION:
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    return 0L;
            }
            break;

        case WM_SETCURSOR:
            // Turn off the cursor since this is a full-screen app
            SetCursor(NULL);
            return TRUE;

        case WM_TIMER:
            // Update and flip surfaces
            if (g_bActive && TIMER_ID == wParam)
            {
                UpdateFrame(hWnd);
                while (TRUE)
                {
                    hRet = g_pDDSPrimary->Flip(NULL, 0);
                    if (hRet == DD_OK)
                        break;
                    if (hRet == DDERR_SURFACELOST)
                    {
                        hRet = RestoreAll();
                        if (hRet != DD_OK)
                            break;
                    }
                    if (hRet != DDERR_WASSTILLDRAWING)
                        break;
                }
            }
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: InitApp()
// Desc: Do work required for every instance of the application:
//          Create the window, initialize data
//-----------------------------------------------------------------------------
static HRESULT
InitApp(int nCmdShow)
{
    HWND                        hWnd;
    WNDCLASS                    wc;
    DDSURFACEDESC               ddsd;
    HRESULT                     hRet;

    // Set up and register window class
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH )GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NAME;
    RegisterClass(&wc);

    // Create a window
    hWnd = CreateWindowEx(WS_EX_TOPMOST,
                          NAME,
                          TITLE,
                          WS_POPUP,
                          0,
                          0,
                          GetSystemMetrics(SM_CXSCREEN),
                          GetSystemMetrics(SM_CYSCREEN),
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    SetFocus(hWnd);

    ///////////////////////////////////////////////////////////////////////////
    // Create the main DirectDraw object
    ///////////////////////////////////////////////////////////////////////////


    hRet = DirectDrawCreate(NULL, &g_pDD, NULL);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, szDDrawFailedMsg);

    // Get exclusive mode
    hRet = g_pDD->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, szSetCooperativeFailMsg);

    DDCAPS ddCaps;
    DDCAPS ddHelCaps;

    g_pDD->GetCaps(&ddCaps, &ddHelCaps);

    if (!(ddCaps.ddsCaps.dwCaps & DDSCAPS_BACKBUFFER)) 
    {
        return InitFail(hWnd, E_FAIL, szNoBackBufferMsg);
    }

    if (!(ddCaps.ddsCaps.dwCaps & DDSCAPS_FLIP)) 
    {
        return InitFail(hWnd, E_FAIL, szNoFlipSurfacesMsg);
    }

    // Create the primary surface with 1 back buffer
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
                          DDSCAPS_FLIP;
    ddsd.dwBackBufferCount = 1;
    hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSPrimary, NULL);
    if (hRet != DD_OK)
    {
        return InitFail(hWnd, hRet, szCreateSurfaceFailMsg);
    }

    // Get a pointer to the back buffer
    hRet = g_pDDSPrimary->EnumAttachedSurfaces(&g_pDDSBack, EnumFunction);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, szEnumAttachedSurfacesFailMsg);

    // Create a offscreen bitmap.
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwHeight = 480;
    ddsd.dwWidth = 640;
    hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSOne, NULL);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, szCreateSurfaceFailMsg);

    // Create another offscreen bitmap.
    hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSTwo, NULL);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, szCreateSurfaceFailMsg);

    if (!InitSurfaces())
        return InitFail(hWnd, hRet, szInitSurfacesFailMsg);

    // Create a timer to flip the pages
    if (TIMER_ID != SetTimer(hWnd, TIMER_ID, TIMER_RATE, NULL))
        return InitFail(hWnd, hRet, szSetTimerFailMsg);

    return DD_OK;
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Initialization, message loop
//-----------------------------------------------------------------------------
int PASCAL
WinMain(HINSTANCE hCurInstance,
        HINSTANCE hPrevInstance,
#ifdef UNDER_CE
        LPWSTR lpCmdLine,
#else
        LPSTR lpCmdLine,
#endif
        int nCmdShow)
{
    MSG msg;

    hInstance = hCurInstance;

    InitApp(nCmdShow);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (g_szErrorMessage != NULL){
        MessageBox(NULL, g_szErrorMessage, szDDrawError, MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    return msg.wParam;
}


