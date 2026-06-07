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
// File: Matrices.cpp
//
// Desc: Now that we know how to create a device and render some 2D vertices,
//       this tutorial goes the next step and renders 3D geometry. To deal with
//       3D geometry we need to introduce the use of 4x4 matrices to transform
//       the geometry with translations, rotations, scaling, and setting up our
//       camera.
//
//       Geometry is defined in model space. We can move it (translation),
//       rotate it (rotation), or stretch it (scaling) using a world transform.
//       The geometry is then said to be in world space. Next, we need to
//       position the camera, or eye point, somewhere to look at the geometry.
//       Another transform, via the view matrix, is used, to position and
//       rotate our view. With the geometry then in view space, our last
//       transform is the projection transform, which "projects" the 3D scene
//       into our 2D viewport.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#pragma comment(linker, "/nodefaultlib:oldnames.lib")

#include <windows.h>
#include <d3dm.h>
#include <d3dmx.h>
#include <aygshell.h>




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3DMOBILE        g_pD3DM       = NULL;  // Used to create the D3DMDevice
LPDIRECT3DMOBILEDEVICE  g_pd3dmDevice = NULL;  // Our rendering device
HMODULE                 g_hRefDLL     = NULL;  // DLL handle for d3dmref.dll
bool                    g_bUseRef     = false; // Flag denoting use of d3dmref

LPDIRECT3DMOBILEVERTEXBUFFER g_pVB    = NULL; // Buffer to hold vertices

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;  // The transformed position for the vertex
    DWORD color;    // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DMFVF_CUSTOMVERTEX (D3DMFVF_XYZ_FLOAT | D3DMFVF_DIFFUSE)


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
    
    // Turn off culling, so we see the front and back of the triangle
    g_pd3dmDevice->SetRenderState( D3DMRS_CULLMODE, D3DMCULL_NONE );

    // Turn off D3DM lighting, since we are providing our own vertex colors
    g_pd3dmDevice->SetRenderState( D3DMRS_LIGHTING, FALSE );


    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3DM
//       also uses index buffers. 
//-----------------------------------------------------------------------------
HRESULT InitVB()
{
    // Initialize three vertices for rendering a triangle
    CUSTOMVERTEX vertices[] =
    {
        { -1.0f,-1.0f, 0.0f, 0xffff0000 },
        {  1.0f,-1.0f, 0.0f, 0xff0000ff },
        {  0.0f, 1.0f, 0.0f, 0xffffffff }
    };

    // Determine if the device can create vertex buffers in video memory
    // by testing the device caps bits.
    D3DMCAPS caps;
    if( FAILED( g_pd3dmDevice->GetDeviceCaps(&caps) ) )
    {
        return E_FAIL;
    }
    D3DMPOOL pool;
    if (caps.SurfaceCaps & D3DMSURFCAPS_VIDVERTEXBUFFER)
    {
        pool = D3DMPOOL_VIDEOMEM;
    }
    else
    {
        pool = D3DMPOOL_SYSTEMMEM;
    }        
    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
    if( FAILED( g_pd3dmDevice->CreateVertexBuffer( 3*sizeof(CUSTOMVERTEX),
                                                  0, D3DMFVF_CUSTOMVERTEX,
                                                  pool, &g_pVB ) ) )
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    void* pVertices;
    if( FAILED( g_pVB->Lock( 0, sizeof(vertices), &pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, vertices, sizeof(vertices) );
    g_pVB->Unlock();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
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
    // For our world matrix, we will just rotate the object about the y-axis.
    D3DMXMATRIX matWorld;

    // Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
    // every 1000 ms. To avoid the loss of precision inherent in very high 
    // floating point numbers, the system time is modulated by the rotation 
    // period before conversion to a radian angle.
    UINT  iTime  = GetTickCount() % 1000;
    float fAngle = iTime * (2.0f * D3DMX_PI) / 1000.0f;
    D3DMXMatrixRotationY( &matWorld, fAngle );
    g_pd3dmDevice->SetTransform( D3DMTS_WORLD, (D3DMMATRIX*)&matWorld, D3DMFMT_D3DMVALUE_FLOAT );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DMXVECTOR3 vEyePt( 0.0f, 3.0f, -5.0f );
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
    if( NULL == g_pd3dmDevice )
        return;

    // Clear the backbuffer to a blue color
    g_pd3dmDevice->Clear( 0, NULL, D3DMCLEAR_TARGET, D3DMCOLOR_XRGB(0,0,0), 1.0f, 0 );
    
    // Begin the scene
    if( SUCCEEDED( g_pd3dmDevice->BeginScene() ) )
    {
        // Setup the world, view, and projection matrices
        SetupMatrices();
        
        // Render the vertex buffer contents
        g_pd3dmDevice->SetStreamSource( 0, g_pVB, sizeof(CUSTOMVERTEX) );
        g_pd3dmDevice->DrawPrimitive( D3DMPT_TRIANGLELIST, 0, 1 );

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

    //We don't support a rotated screen
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
                              TEXT("D3DM Tutorial 03: Matrices"), 
                              WS_VISIBLE, 
                              0, 0, iScreenWidth, iScreenHeight,
                              NULL, NULL, wc.hInstance, NULL );

    SHFullScreen(hWnd, SHFS_HIDESIPBUTTON | SHFS_HIDETASKBAR);

    // Initialize Direct3D Mobile
    if( SUCCEEDED( InitD3DM( hWnd ) ) )
    { 
        // Create the vertex buffer
        if( SUCCEEDED( InitVB() ) )
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

