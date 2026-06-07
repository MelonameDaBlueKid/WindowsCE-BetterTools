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
//-----------------------------------------------------------------------------
// File: Textures.cpp
//
// Desc: Better than just lights and materials, 3D objects look much more
//       convincing when texture-mapped. Textures can be thought of as a sort
//       of wallpaper, that is shrinkwrapped to fit a texture. Textures are
//       typically loaded from image files. Like a vertex buffer, textures have
//       Lock() and Unlock() functions to access (read or write) the image
//       data. Textures have a width, height, miplevel, and pixel format. The
//       miplevel is for "mipmapped" textures, an advanced performance-
//       enhancing feature which uses lower resolutions of the texture for
//       objects in the distance where detail is less noticeable. The pixel
//       format determines how the colors are stored in a texel. The most
//       common formats are the 16-bit R5G6B5 format (5 bits of red, 6-bits of
//       green and 5 bits of blue) and the 32-bit A8R8G8B8 format (8 bits each
//       of alpha, red, green, and blue).
//
//       Textures are associated with geometry through texture coordinates.
//       Each vertex has one or more sets of texture coordinates, which are
//       named tu and tv and range from 0.0 to 1.0. Texture coordinates can be
//       supplied by the geometry, or can be automatically generated using
//       Direct3D Mobile texture coordinate generation (which is an advanced
//       feature).
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#pragma comment(linker, "/nodefaultlib:oldnames.lib")

#include <windows.h>
#include <d3dm.h>
#include <d3dmx.h>
#include "resource.h"
#include <aygshell.h>



//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3DMOBILE        g_pD3DM       = NULL;  // Used to create the D3DMDevice
LPDIRECT3DMOBILEDEVICE  g_pd3dmDevice = NULL;  // Our rendering device
HMODULE                 g_hRefDLL     = NULL;  // DLL handle for d3dmref.dll
bool                    g_bUseRef     = false; // Flag denoting use of d3dmref

LPDIRECT3DMOBILEVERTEXBUFFER g_pVB    = NULL; // Buffer to hold vertices
LPDIRECT3DMOBILETEXTURE g_pTexture    = NULL; // Our texture

// A structure for our custom vertex type. We added a normal, and omitted the
// color (which is provided by the material)
struct CUSTOMVERTEX
{
    D3DMXVECTOR3 position;     // The position
    D3DMCOLOR    color;   // The color
#ifndef SHOW_HOW_TO_USE_TCI
    float       tu, tv;   // The texture coordinates
#endif
};


// Our custom FVF, which describes our custom vertex structure
#ifdef SHOW_HOW_TO_USE_TCI
#define D3DMFVF_CUSTOMVERTEX (D3DMFVF_XYZ_FLOAT | D3DMFVF_DIFFUSE)
#else
#define D3DMFVF_CUSTOMVERTEX (D3DMFVF_XYZ_FLOAT | D3DMFVF_DIFFUSE | \
                              D3DMFVF_TEX1 | \
                              D3DMFVF_TEXCOORDSIZE2(0) | \
                              D3DMFVF_TEXCOORDFLOAT(0))
#endif


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

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DMPRESENT_PARAMETERS d3dmpp; 
    memset( &d3dmpp, 0, sizeof(d3dmpp) );
    d3dmpp.Windowed = TRUE;
    d3dmpp.SwapEffect = D3DMSWAPEFFECT_DISCARD;
    d3dmpp.BackBufferFormat = D3DMFMT_UNKNOWN;
    d3dmpp.EnableAutoDepthStencil = TRUE;
    d3dmpp.AutoDepthStencilFormat = D3DMFMT_D16;

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
    
    // Turn off culling
    g_pd3dmDevice->SetRenderState( D3DMRS_CULLMODE, D3DMCULL_NONE );

    // Turn off D3D lighting
    g_pd3dmDevice->SetRenderState( D3DMRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    g_pd3dmDevice->SetRenderState( D3DMRS_ZENABLE, TRUE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Creates the scene geometry
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
    // Retrieve the D3DM device's capabilities
    D3DMCAPS caps;
    if( FAILED( g_pd3dmDevice->GetDeviceCaps(&caps) ) )
    {
        return E_FAIL;
    }

    // Determine if the device can create textures in video memory
    // by testing the device caps bits.
    D3DMPOOL texpool;
    if (caps.SurfaceCaps & D3DMSURFCAPS_VIDTEXTURE)
    {
        texpool = D3DMPOOL_VIDEOMEM;
    }
    else
    {
        texpool = D3DMPOOL_SYSTEMMEM;
    }        

    // Load the texture map resource (banana.bmp)
     if( FAILED( D3DMXCreateTextureFromResourceEx( g_pd3dmDevice, GetModuleHandle(NULL), 
        MAKEINTRESOURCE(IDB_BANANA), D3DMX_DEFAULT, D3DMX_DEFAULT, 1, 0, 
        D3DMFMT_UNKNOWN, texpool, D3DMX_FILTER_POINT, D3DMX_FILTER_POINT, 
        0, NULL, NULL, &g_pTexture ) ) )
    {
        return E_FAIL;
    }        
    
    // Determine if the device can create vertex buffers in video memory
    // by testing the device caps bits.
    D3DMPOOL vbpool;
    if (caps.SurfaceCaps & D3DMSURFCAPS_VIDVERTEXBUFFER)
    {
        vbpool = D3DMPOOL_VIDEOMEM;
    }
    else
    {
        vbpool = D3DMPOOL_SYSTEMMEM;
    }        

    // Create the vertex buffer.
    if( FAILED( g_pd3dmDevice->CreateVertexBuffer(50*2*sizeof(CUSTOMVERTEX), 
                                                  0, D3DMFVF_CUSTOMVERTEX,
                                                  vbpool, &g_pVB ) ) )
    {
        return E_FAIL;
    }

    // Fill the vertex buffer. We are setting the tu and tv texture
    // coordinates, which range from 0.0 to 1.0
    CUSTOMVERTEX* pVertices;
    if( FAILED( g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
        return E_FAIL;

    for( DWORD i=0; i<50; i++ )
        {
        FLOAT theta = (2*D3DMX_PI*i)/(50-1);
        pVertices[2*i+0].position = D3DMXVECTOR3( (float)sin(theta),-1.0f, (float)cos(theta) );
        pVertices[2*i+0].color    = 0xffffffff;
#ifndef SHOW_HOW_TO_USE_TCI
        pVertices[2*i+0].tu       = ((float)i)/(50-1);
        pVertices[2*i+0].tv       = 1.0f;
#endif

        pVertices[2*i+1].position = D3DMXVECTOR3( (float)sin(theta), 1.0f, (float)cos(theta) );
        pVertices[2*i+1].color    = 0xff808080;
#ifndef SHOW_HOW_TO_USE_TCI
        pVertices[2*i+1].tu       = ((float)i)/(50-1);
        pVertices[2*i+1].tv       = 0.0f;
#endif
    }
    g_pVB->Unlock();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pTexture != NULL )
        g_pTexture->Release();

    if( g_pVB != NULL )        
        g_pVB->Release();

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
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
    // For our world matrix, we will just leave it as the identity
    D3DMXMATRIX matWorld;
    D3DMXMatrixIdentity( &matWorld );
    D3DMXMatrixRotationX( &matWorld, GetTickCount()/1000.0f );
    g_pd3dmDevice->SetTransform( D3DMTS_WORLD, (D3DMMATRIX*)&matWorld, D3DMFMT_D3DMVALUE_FLOAT );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DMXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DMXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DMXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DMXMATRIX matView;
    D3DMXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dmDevice->SetTransform( D3DMTS_VIEW, (D3DMMATRIX*)&matView, D3DMFMT_D3DMVALUE_FLOAT );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DMXMATRIX matProj;
    D3DMXMatrixPerspectiveFovLH( &matProj, D3DMX_PI/4.0f, 1.0f, 1.0f, 100.0f );
    g_pd3dmDevice->SetTransform( D3DMTS_PROJECTION, (D3DMMATRIX*)&matProj, D3DMFMT_D3DMVALUE_FLOAT );
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer and the zbuffer
    g_pd3dmDevice->Clear( 0, NULL, D3DMCLEAR_TARGET | D3DMCLEAR_ZBUFFER,
                         D3DMCOLOR_XRGB(0,0,255), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dmDevice->BeginScene() ) )
    {
        // Setup the world, view, and projection matrices
        SetupMatrices();

        // Setup our texture. Using textures introduces the texture stage states,
        // which govern how textures get blended together (in the case of multiple
        // textures) and lighting information. In this case, we are modulating
        // (blending) our texture with the diffuse color of the vertices.
        g_pd3dmDevice->SetTexture( 0, g_pTexture );
        g_pd3dmDevice->SetTextureStageState( 0, D3DMTSS_COLOROP,   D3DMTOP_MODULATE );
        g_pd3dmDevice->SetTextureStageState( 0, D3DMTSS_COLORARG1, D3DMTA_TEXTURE );
        g_pd3dmDevice->SetTextureStageState( 0, D3DMTSS_COLORARG2, D3DMTA_DIFFUSE );
        g_pd3dmDevice->SetTextureStageState( 0, D3DMTSS_ALPHAOP,   D3DMTOP_DISABLE );

    #ifdef SHOW_HOW_TO_USE_TCI
        // Note: to use D3DM texture coordinate generation, use the stage state
        // D3DMTSS_TEXCOORDINDEX, as shown below. In this example, we are using
        // the position of the vertex in camera space to generate texture
        // coordinates. The tex coord index (TCI) parameters are passed into a
        // texture transform, which is a 4x4 matrix which transforms the x,y,z
        // TCI coordinates into tu, tv texture coordinates.

        // In this example, the texture matrix is setup to 
        // transform the texture from (-1,+1) position coordinates to (0,1) 
        // texture coordinate space:
        //    tu =  0.5*x + 0.5
        //    tv = -0.5*y + 0.5
        D3DMXMATRIX mat;
        mat._11 = 0.25f; mat._12 = 0.00f; mat._13 = 0.00f; mat._14 = 0.00f;
        mat._21 = 0.00f; mat._22 =-0.25f; mat._23 = 0.00f; mat._24 = 0.00f;
        mat._31 = 0.00f; mat._32 = 0.00f; mat._33 = 1.00f; mat._34 = 0.00f;
        mat._41 = 0.50f; mat._42 = 0.50f; mat._43 = 0.00f; mat._44 = 1.00f;

        g_pd3dmDevice->SetTransform( D3DMTS_TEXTURE0, (D3DMMATRIX*)&mat, D3DMFMT_D3DMVALUE_FLOAT );
        g_pd3dmDevice->SetTextureStageState( 0, D3DMTSS_TEXTURETRANSFORMFLAGS, D3DMTTFF_COUNT2 );
        g_pd3dmDevice->SetTextureStageState( 0, D3DMTSS_TEXCOORDINDEX, D3DMTSS_TCI_CAMERASPACEPOSITION );
    #endif

        // Render the vertex buffer contents
        g_pd3dmDevice->SetStreamSource( 0, g_pVB, sizeof(CUSTOMVERTEX) );
        g_pd3dmDevice->DrawPrimitive( D3DMPT_TRIANGLESTRIP, 0, 2*50-2 );

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

    case WM_SETTINGCHANGE:
        //we don't support screen rotation
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

    //we don't support screen rotation
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
    HWND hWnd = CreateWindow( TEXT("D3DM Tutorial"), 
                              TEXT("D3DM Tutorial 05: Textures"), 
                              WS_VISIBLE,    
                              0, 0, iScreenWidth, iScreenHeight,
                              NULL, NULL, wc.hInstance, NULL );

    SHFullScreen(hWnd, SHFS_HIDESIPBUTTON | SHFS_HIDETASKBAR);

    // Initialize Direct3D Mobile
    if( SUCCEEDED( InitD3DM( hWnd ) ) )
    { 
        // Create the vertex buffer
        if( SUCCEEDED( InitGeometry() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWNORMAL );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            memset( &msg, 0, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                    Render();
            }
        }
    }

    return 0;
}

