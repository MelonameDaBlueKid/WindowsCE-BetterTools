//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft
// premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license
// agreement, you are not authorized to use this source code.
// For the terms of the license, please see the license agreement
// signed by you and Microsoft.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//

#pragma once

#include <windows.h>

#define PIXELFORMAT_BASE(bpp, alphabpp) (((bpp)<<3)|((alphabpp)<<10))

enum XRPixelFormat
{
    XRPixelFormat_pixelGray1bpp               = PIXELFORMAT_BASE(1, 0),
    XRPixelFormat_pixelGray8bpp               = PIXELFORMAT_BASE(8, 0),
    XRPixelFormat_pixelGray16bpp              = PIXELFORMAT_BASE(16, 0),
    XRPixelFormat_pixelColor16bpp_X1R5G5B5,  // same base format as above
    XRPixelFormat_pixelColor16bpp_R5G6B5,    // same base format as above
    XRPixelFormat_pixelColor16bpp_A1R5G5B5    = PIXELFORMAT_BASE(16, 1),
    XRPixelFormat_pixelColor32bpp_X8R8G8B8    = PIXELFORMAT_BASE(32, 0),
    XRPixelFormat_pixelColor32bpp_A8R8G8B8    = PIXELFORMAT_BASE(32, 8),

    // non-RGB pixel formats
    XRPixelFormat_pixelPlanar_YV12_CCIR601 = 1,
    XRPixelFormat_pixelPlanar_YV12_CCIR709
};

struct XRRECT_WH
{
    int X;
    int Y;
    int Width;
    int Height;
};

struct XRPOINT
{
    int x;
    int y;
};

//------------------------------------------------------------------------
//
//  Struct:  XRVertex definition
//
//  Synopsis:
//      DirectX/OpenGL abstraction
//
//------------------------------------------------------------------------
struct XRVertex
{
    float x, y, z;            // z allows perspective texturing
    unsigned long dwDiffuse;  // Multiplies with texture and can be used for opacity
                              // effects and solid color draws
    float u0, v0;             // Texture coordinates stage 0
    float u1, v1;             // Texture coordinates stage 1
};


//------------------------------------------------------------------------
//
//  Interface:  ICustomSurface
//
//  Synopsis:
//      Surface methods
//
//------------------------------------------------------------------------

struct ICustomSurface
{
    // Lifetime management
    //
    virtual UINT AddRef() = 0;
    virtual UINT Release() = 0;
    
    virtual __checkReturn HRESULT Lock(
         __out void **ppAddress,
         __out int *pnStride,
         __out UINT *puWidth,
         __out UINT *puHeight
         ) = 0;

    virtual __checkReturn HRESULT Unlock() = 0;

    virtual __checkReturn HRESULT Present(
        __in HWND hTarget, 
        __in_opt XRPOINT *pOffset, 
        __in UINT bAlphaBlt
        ) = 0;

    virtual __checkReturn HRESULT Present(
        __in HWND hTarget,
        __in XRRECT_WH bounds, 
        __in XRRECT_WH clip, 
        __in UINT bAlphaBlend) = 0;

    virtual UINT GetWidth() = 0;
    virtual UINT GetHeight() = 0;

    virtual XRPixelFormat GetPixelFormat() = 0;
    virtual int IsVideoSurface() = 0;
    virtual int IsOpaque() = 0;
    virtual int IsTransparent() = 0;
    virtual void SetIsOpaque(__in int bIsOpaque) = 0;
    virtual void SetIsTransparent(__in int bIsTransparent) = 0;
    virtual HRESULT AddDirty(__in const XRRECT_WH &rcDirty) = 0;
};

//------------------------------------------------------------------------
//
//  Interface:  ICustomGraphicsDevice
//
//  Synopsis:
//      DirectX/OpenGL abstraction
//
//------------------------------------------------------------------------
struct ICustomGraphicsDevice
{
    // AddRef/Release the interface
    //
    virtual UINT AddRef() = 0;
    virtual UINT Release() = 0;

    // Init
    //
    virtual HRESULT Initialize(__in HWND hWindow) = 0;

    //
    // Resize back buffer 
    //

    virtual __checkReturn HRESULT Resize(UINT uWidth, UINT uHeight) = 0;

    // Resource creation API's
    //
    virtual __checkReturn HRESULT CreateTexture(
        __in int fRenderTarget, 
        __in UINT nWidth,
        __in UINT nHeight,
        __in int fKeepSystemMemory,
        __out ICustomSurface **ppSurface
        ) = 0;

    // Draw calls
    //
    virtual __checkReturn HRESULT SetTexture(
        __in UINT uSampler,
        __in ICustomSurface *pTexture
        ) = 0;

    virtual __checkReturn HRESULT SetRenderTarget(
        __in ICustomSurface *pRenderTarget
        ) = 0;

    virtual __checkReturn HRESULT DrawTriangleStrip(
        __in_ecount(cVertices) XRVertex *pVertices,  
        UINT cVertices
        ) = 0;

    virtual __checkReturn HRESULT Clear(
        __in UINT uColor
        ) = 0;

    virtual __checkReturn HRESULT Present() = 0;

    virtual __checkReturn HRESULT Present(
        __in XRRECT_WH bounds, 
        __in XRRECT_WH clip, 
        __in UINT bAlphaBlend
        ) = 0;
    
    // Stats
    // 
    virtual __checkReturn HRESULT GetTextureMemoryUsage(
        UINT *puTextureMemoryUsage,
        UINT *puTextureMemoryUsageNPOT
        ) = 0;
        
    virtual __checkReturn bool IsHardwareComposited() = 0;
};

//------------------------------------------------------------------------
//
//  Class:  IRenderer
//
//  Synopsis:
//      Interface responsible for creating surfaces to render to
//      and presenting them to the display. 
//
//      There is a 1:1 mapping between HWND <--> IRenderer
//
//------------------------------------------------------------------------

struct IRenderer
{
    virtual UINT AddRef() = 0;
    virtual UINT Release() = 0;

    virtual void FreeResources() = 0;
    virtual void Reset() = 0;

    virtual HRESULT PreRender(
        __in HWND hwndRender, 
        __in HDC  hdcRender,
        __in const SIZE * pSurfaceSize, 
        __out BOOL* pfNeedsFullRedraw,
        __out ICustomSurface** ppSurface
        ) = 0;

    virtual HRESULT PostRender(
        __in HWND hwndRender, 
        __in HDC  hdcRender,
        __in const SIZE* pSurfaceSize,
        __in XRRECT_WH * prcUpdate
        ) = 0;
};

//------------------------------------------------------------------------
//
//  Function:  RenderPluginInitialize
//
//  Synopsis:
//      This functions is to be implemented by the plugin renderer DLL.
//      It is called at XamlRuntime initialization. 
//
//      If FAILURE is returned, XamlRuntime will default to an internal 
//      GDI implementation.
//
//------------------------------------------------------------------------
extern "C" HRESULT RenderPluginInitialize();

//------------------------------------------------------------------------
//
//  Function:  RenderPluginCleanup
//
//  Synopsis:
//      Called when XamlRuntime is being shutdown. This gives the plugin 
//      a chance to cleanup allocated resources.
//
//------------------------------------------------------------------------
extern "C" void RenderPluginCleanup();

//------------------------------------------------------------------------
//
//  Function:  CreateRenderer
//
//  Synopsis:
//      This functions is to be implemented by the plugin renderer lib.
//

//    Parameters:
//          [IN]  HWND which the renderer is responsible for presenting 
//                content to
//          [OUT] An IRenderer for this HWND
//
//          [OUT-optional]  If this plugin supports cached-composition, 
//                          provide an implementation of 
//                          ICustomGraphicsDevice here.
//
//  Returns: HRESULT indicating success or failure
//
//------------------------------------------------------------------------
extern "C" HRESULT CreateRenderer(
    __in HWND HostWindow ,
    __out IRenderer **ppRenderer, 
    __out_opt ICustomGraphicsDevice** ppDevice
    );


