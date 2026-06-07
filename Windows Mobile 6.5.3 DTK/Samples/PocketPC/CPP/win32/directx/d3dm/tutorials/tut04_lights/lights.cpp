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
// File: Lights.cpp
//
// Desc: Rendering 3D geometry is much more interesting when dynamic lighting
//       is added to the scene. To use lighting in D3DM, you must create one or
//       lights, setup a material, and make sure your geometry contains surface
//       normals. Lights may have a position, a color, and be of a certain type
//       such as directional (light comes from one direction) or point (light
//       comes from a specific x,y,z coordinate and radiates in all directions).
//       Materials describe the surface of your geometry, specifically, how it 
//       gets lit (diffuse color, ambient color, etc.).  Surface normals are
//       part of a vertex, and are needed for the D3DM's internal lighting 
//       calculations.
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

// A structure for our custom vertex type. We added a normal, and omitted the
// color (which is provided by the material)
struct CUSTOMVERTEX
{
    D3DMXVECTOR3 position; // The 3D position for the vertex
    D3DMXVECTOR3 normal;   // The surface normal for the vertex
};


// Our custom FVF, which describes our custom vertex structure
#define D3DMFVF_CUSTOMVERTEX (D3DMFVF_XYZ_FLOAT | D3DMFVF_NORMAL_FLOAT)

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

    // Create the vertex buffer.
    if( FAILED( g_pd3dmDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
                                                  0, D3DMFVF_CUSTOMVERTEX,
                                                  pool, &g_pVB ) ) )
    {
        return E_FAIL;
    }

    // Fill the vertex buffer. We are algorithmically generating a cylinder
    // here, including the normals, which are used for lighting.
    CUSTOMVERTEX* pVertices;
    if( FAILED( g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    for( DWORD i=0; i<50; i++ )
    {
        FLOAT theta = (2*D3DMX_PI*i)/(50-1);
        pVertices[2*i+0].position = D3DMXVECTOR3( (float)sin(theta),-1.0f, (float)cos(theta) );
        pVertices[2*i+0].normal   = D3DMXVECTOR3( (float)sin(theta), 0.0f, (float)cos(theta) );
        pVertices[2*i+1].position = D3DMXVECTOR3( (float)sin(theta), 1.0f, (float)cos(theta) );
        pVertices[2*i+1].normal   = D3DMXVECTOR3( (float)sin(theta), 0.0f, (float)cos(theta) );
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
    D3DMXMatrixRotationX( &matWorld, GetTickCount()/500.0f );
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
// Name: SetupLights()
// Desc: Sets up the lights and materials for the scene.
//-----------------------------------------------------------------------------
VOID SetupLights()
{
    // Set up a material. The material here just has the diffuse and ambient
    // colors set to yellow. Note that only one material can be used at a time.
    D3DMMATERIAL mtrl;
    memset( &mtrl, 0, sizeof(D3DMMATERIAL) );
    float f = 1.0f;
    mtrl.Diffuse.r = mtrl.Ambient.r = *(D3DMVALUE*)&f; // 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = *(D3DMVALUE*)&f; // 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 0;               // 0.0f
    mtrl.Diffuse.a = mtrl.Ambient.a = *(D3DMVALUE*)&f; // 1.0f;
    g_pd3dmDevice->SetMaterial( &mtrl, D3DMFMT_D3DMVALUE_FLOAT );

    // Set up a white, directional light, with an oscillating direction.
    // Note that many lights may be active at a time (but each one slows down
    // the rendering of our scene). However, here we are just using one. Also,
    // we need to set the D3DMRS_LIGHTING renderstate to enable lighting
    D3DMXVECTOR3 vecDir;
    D3DMLIGHT light;
    memset( &light, 0, sizeof(D3DMLIGHT) );
    light.Type       = D3DMLIGHT_DIRECTIONAL;
    light.Diffuse.r  = *(D3DMVALUE*)&f; // 1.0f;
    light.Diffuse.g  = *(D3DMVALUE*)&f; // 1.0f;
    light.Diffuse.b  = *(D3DMVALUE*)&f; // 1.0f;
    vecDir = D3DMXVECTOR3((float)cos(GetTickCount()/350.0f),
                         1.0f,
                         (float)sin(GetTickCount()/350.0f) );
    D3DMXVec3Normalize( (D3DMXVECTOR3*)&light.Direction, &vecDir );
    light.Range       = 1000.0f;
    g_pd3dmDevice->SetLight( 0, &light, D3DMFMT_D3DMVALUE_FLOAT );
    g_pd3dmDevice->LightEnable( 0, TRUE );
    g_pd3dmDevice->SetRenderState( D3DMRS_LIGHTING, TRUE );

    // Finally, turn on some ambient light.
    g_pd3dmDevice->SetRenderState( D3DMRS_AMBIENT, 0x00202020 );
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
        // Setup the lights and materials
        SetupLights();

        // Setup the world, view, and projection matrices
        SetupMatrices();

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
    

    //check that we are not rotated
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
                              TEXT("D3DM Tutorial 04: Lights"), 
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

