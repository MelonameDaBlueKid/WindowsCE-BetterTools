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
// File: CreateDevice.cpp
//
// Desc: This is the first tutorial for using Direct3D Mobile. In this tutorial,
//       all we are doing is creating a Direct3D device and using it to clear
//       the window.
//
//-----------------------------------------------------------------------------
#pragma comment(linker, "/nodefaultlib:oldnames.lib")

#include <windows.h>
#include <d3dm.h>
#include <aygshell.h>



//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3DMOBILE        g_pD3DM       = NULL;  // Used to create the D3DMDevice
LPDIRECT3DMOBILEDEVICE  g_pd3dmDevice = NULL;  // Our rendering device
HMODULE                 g_hRefDLL     = NULL;  // DLL handle for d3dmref.dll
bool                    g_bUseRef     = false; // Flag denoting use of d3dmref

//-----------------------------------------------------------------------------
// Name: IsScreenRotated()
// Desc: Currently the D3DM runtime does not support a rotated screen. If the 
//       screen is rotated, we should inform the user this is not supported.
//       If this routing returns TRUE the caller should cleanup and exit the application
//-----------------------------------------------------------------------------
BOOL IsScreenRotated()
{
    DEVMODE devMode  = {0};
    devMode.dmSize   = sizeof(DEVMODE);
    devMode.dmFields = DM_DISPLAYORIENTATION;

    ChangeDisplaySettingsEx(NULL, &devMode, NULL, CDS_TEST, NULL);

    if (devMode.dmDisplayOrientation != DMDO_0)
    {
        MessageBox(
            NULL, 
            TEXT("This D3DM sample will not work on a rotated screen.\nThe application will now exit."),
            TEXT("Notice"),
            MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND
            );

        return TRUE;
    }

    return FALSE;
}



//-----------------------------------------------------------------------------
// Name: InitD3DM()
// Desc: Initializes Direct3D Mobile
//-----------------------------------------------------------------------------
HRESULT InitD3DM( HWND hWnd )
{
    // Create the D3DM object, which is needed to create the D3DMDevice.
    if( NULL == ( g_pD3DM = Direct3DMobileCreate( D3DM_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DMDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3DM in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DMPRESENT_PARAMETERS d3dmpp; 
    memset( &d3dmpp, 0, sizeof(d3dmpp) );
    d3dmpp.Windowed = TRUE;
    d3dmpp.SwapEffect = D3DMSWAPEFFECT_DISCARD;
    d3dmpp.BackBufferFormat = D3DMFMT_UNKNOWN;

    // Create the Direct3D Mobile device.
    UINT uAdapter;


    if (g_bUseRef)
    {
        // Load the D3DM reference driver DLL
        g_hRefDLL = (HMODULE)LoadLibrary(TEXT("d3dmref.dll"));
        if (NULL == g_hRefDLL)
        {
            OutputDebugString(TEXT("Unable to load D3DM reference driver DLL.\n"));
            return E_FAIL;
        }

        // Get the reference driver's entry point
        void* pfnD3DMInit = GetProcAddress(g_hRefDLL, TEXT("D3DM_Initialize"));   
        if( NULL == pfnD3DMInit )
        {
            OutputDebugString(TEXT("Unable to retrieve D3DM reference driver entry point.\n"));
            return E_FAIL;
        }

        // Register the software device
        if( FAILED( g_pD3DM->RegisterSoftwareDevice(pfnD3DMInit) ) )
        {
            OutputDebugString(TEXT("Unable to register D3DM reference driver.\n"));
            return E_FAIL;
        }
        
        uAdapter = D3DMADAPTER_REGISTERED_DEVICE;
    }
    else
    {
        // Use the default system D3DM driver    
        uAdapter = D3DMADAPTER_DEFAULT;
    }

    if( FAILED( g_pD3DM->CreateDevice( uAdapter, 
                                    D3DMDEVTYPE_DEFAULT,
                                    hWnd, 0,
                                    &d3dmpp, &g_pd3dmDevice ) ) )
    {
        OutputDebugString(TEXT("Unable to create a D3DM device.\n"));
        return E_FAIL;
    }
    
    // Device state would normally be set here

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pd3dmDevice != NULL) 
        g_pd3dmDevice->Release();

    if( g_pD3DM != NULL)
    {
        if (g_hRefDLL)
        {
            g_pD3DM->RegisterSoftwareDevice(NULL);
            FreeLibrary(g_hRefDLL);
        }
    
        g_pD3DM->Release();
    }
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    if( NULL == g_pd3dmDevice )
        return;

    // Clear the backbuffer to a blue color
    g_pd3dmDevice->Clear( 0, NULL, D3DMCLEAR_TARGET, D3DMCOLOR_XRGB(0,0,255), 1.0f, 0 );
    
    // Begin the scene
    if( SUCCEEDED( g_pd3dmDevice->BeginScene() ) )
    {
        // Rendering of scene objects can happen here
    
        // End the scene
        g_pd3dmDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dmDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_LBUTTONUP: 
        PostMessage(hWnd, WM_CLOSE, 0, 0);
        break;
    case WM_KEYDOWN:
        if (VK_ESCAPE == wParam)
        {
            PostMessage(hWnd, WM_CLOSE, 0, 0);
        }
        break;

    case WM_CLOSE:
        Cleanup();
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            Render();
            EndPaint(hWnd, &ps);
            return 0;
        }

    case WM_SETTINGCHANGE:
        //make sure the screen is not rotated - if it is then abort the app
        if (IsScreenRotated())
        {
            PostMessage(hWnd, WM_CLOSE, 0, 0);
        }
        break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPTSTR szCmd, INT )
{
    // Parse command line to determine if user wants to use
    // the D3DM reference driver instead of the default system driver
    if (0 == lstrcmp(szCmd, TEXT("-ref")))
        g_bUseRef = true;
    

    //we don't support screen rotation (as of yet)
    if (IsScreenRotated())
    {
        return 0;
    }
    
    // Register the window class
    WNDCLASS wc = { 0L, MsgProc, 0L, 0L, 
                      hInst, NULL, NULL, NULL, NULL,
                      TEXT("D3DM Tutorial") };
    RegisterClass( &wc );

    int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create the application's window
    HWND hWnd = CreateWindow(TEXT("D3DM Tutorial"), 
                              TEXT("D3DM Tutorial 01: CreateDevice"), 
                              WS_VISIBLE, 
                              0, 0, iScreenWidth, iScreenHeight,
                              NULL, NULL, wc.hInstance, NULL );

    SHFullScreen(hWnd, SHFS_HIDESIPBUTTON | SHFS_HIDETASKBAR);

    // Initialize Direct3D Mobile
    if( SUCCEEDED( InitD3DM( hWnd ) ) )
    { 
        // Show the window
        ShowWindow( hWnd, SW_SHOWNORMAL );
        UpdateWindow( hWnd );

        // Enter the message loop
        MSG msg; 
        while( GetMessage( &msg, NULL, 0, 0 ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    return 0;
}

