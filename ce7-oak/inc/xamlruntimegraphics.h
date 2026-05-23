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

// Return result and handle types
typedef __success(return >= 0) long XRESULT;

typedef void   *XHANDLE;

typedef signed int      XINT32;

typedef unsigned int    XUINT32;

typedef XUINT32             XBOOL;

struct IPALSurface;
struct ICustomGraphicsDevice;


//------------------------------------------------------------------------
//
//  Struct:  XRVertexFormat type
//
//------------------------------------------------------------------------
enum XRVertexFormat
{
    XRVertex_XYZDiffuseUV2 = 2, // 2 texture units
    XRVertex_XYZDiffuseUV8 = 8, // 8 texture units
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
    float x, y, z, w;         // z, w allows perspective texturing
    unsigned long dwDiffuse;  // Multiplies with texture and can be used for opacity
                              // effects and solid color draws
    float u0, v0;             // Texture coordinates stage 0
    float u1, v1;             // Texture coordinates stage 1
    enum 
    {
        Format = XRVertex_XYZDiffuseUV2
    };

};



//------------------------------------------------------------------------
//
//  Interface:  IXRCustomEffect
//
//  Synopsis:
//      Custom UIElement.Effect rendering
//
//------------------------------------------------------------------------
class  __declspec(novtable) __declspec(uuid("{AE2B9711-B018-42a9-8210-FCF4A9F21F16}"))
IXRCustomEffect : public IUnknown
{
public:
    virtual __checkReturn HRESULT SetGraphicsDevice(ICustomGraphicsDevice* pGraphicsDevice) = 0;

    virtual __checkReturn HRESULT SetMVPMatrix(float pMVPMatrix[16]) = 0;

    virtual __checkReturn HRESULT SetTexture(
        __in UINT uiSampler,
        __in UINT uiTexture
        ) = 0;

    virtual __checkReturn HRESULT DrawTriangleStrip(
        __in_ecount(cVertices) XRVertex *pVertices,  
        __in UINT32 cVertices
        ) = 0;
};


//------------------------------------------------------------------------
//
//  Interface:  IXRGPUPixelShader 
//
//  Synopsis:
//      DirectX/OpenGL abstraction
//
//------------------------------------------------------------------------
struct IXRGPUPixelShader 
{
    //
    // AddRef/Release the interface
    //

    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;

    virtual HRESULT SetParameters(void* pParameters) = 0;
};


//------------------------------------------------------------------------
//
//  Enum:  XRGPUPixelShaderID
//
//  Synopsis:
//      Stock pixel shaders
//
//------------------------------------------------------------------------
enum XRGPUPixelShaderID
{
    XRPixelShader_Greyscale = 1,
    XRPixelShader_BlurDirection = 2,
};


//------------------------------------------------------------------------
//
//  Enum:  XRRenderState
//
//  Synopsis:
//      Device render states
//
//------------------------------------------------------------------------
enum XRRenderState
{
    XRRS_ALPHABLEND_ENABLE         = 27,   /* TRUE/FALSE  */
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
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;
    
    virtual __checkReturn HRESULT Lock(
         __out void **ppAddress,
         __out int *pnStride,
         __out UINT *puWidth,
         __out UINT *puHeight,
         __in UINT nLOD = 0
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
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;

    virtual __checkReturn HRESULT AcquireDevice() = 0;
    virtual __checkReturn HRESULT ReleaseDevice() = 0;


    // Init
    //
    virtual HRESULT Initialize(__in HWND hWindow) = 0;

    //
    // Resize back buffer 
    //

    virtual __checkReturn HRESULT Resize(__in UINT uWidth, __in UINT uHeight) = 0;

    // Resource creation API's
    //
    virtual __checkReturn HRESULT CreateTexture(
        __in int fRenderTarget, 
        __in UINT nWidth,
        __in UINT nHeight,
        __in XRPixelFormat pixelFormat,
        __in int fKeepSystemMemory,
        __out ICustomSurface **ppSurface
        ) = 0;

    virtual __checkReturn HRESULT GetStockPixelShader(
        __in XRGPUPixelShaderID pixelShader,
        __out IXRGPUPixelShader **ppPixelShader
        ) = 0;


    // Draw calls
    //
    virtual __checkReturn HRESULT SetVertexFormat(
        __in XRVertexFormat vertexFormat
        ) = 0;
    
    virtual __checkReturn HRESULT SetTexture(
        __in UINT uSampler,
        __in ICustomSurface *pTexture
        ) = 0;

    virtual __checkReturn XRESULT SetClip( 
        __in_opt XRRECT_WH* pClip 
        ) = 0;

    virtual __checkReturn XRESULT GetClip( 
        __out XRRECT_WH* pClip, 
        __out XBOOL* pbClipping
        ) = 0;

    virtual __checkReturn HRESULT SetPixelShader(
        __in IXRGPUPixelShader *pPixelShader
        ) = 0;

    virtual __checkReturn HRESULT SetRenderTarget(
        __in ICustomSurface *pRenderTarget
        ) = 0;

    virtual __checkReturn HRESULT SetCustomEffect(
        __in IXRCustomEffect* pCustomEffect
        ) = 0;

    virtual __checkReturn HRESULT DrawTriangleStrip(
        __in_ecount(cVertices) XRVertex *pVertices,  
        __in UINT32 cVertices
        ) = 0;

    virtual __checkReturn HRESULT SetRenderState(
        __in XRRenderState state,
        __in UINT32 uValue
        ) = 0;
    
    virtual __checkReturn HRESULT Clear(
        __in UINT uColor
        ) = 0;

    virtual __checkReturn HRESULT ClearWindow(
        __in UINT32 uColor,
        __in BOOL fIncremental
        ) = 0;

    virtual __checkReturn HRESULT SetScissorRect(
        __in const XRRECT_WH &rcBounds
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
        __out UINT *puTextureMemoryUsage,
        __out UINT *puTextureMemoryUsageNPOT
        ) = 0;
        
    virtual __checkReturn HRESULT GetFrameRateCounter(
        __out UINT32 *puFrameRateCounter) = 0;

    virtual __checkReturn BOOL IsHardwareComposited() = 0;

    virtual __checkReturn BOOL IsDeviceLost(__in HRESULT status) = 0;

    virtual __checkReturn XINT32 IsValidSurface(__in IPALSurface *pSurface) = 0;

    virtual __checkReturn XINT32 IsDeviceOccluded(__in XRESULT status) = 0;
    //
    // Full screen
    //

    virtual __checkReturn XRESULT GoFullScreen(__in XHANDLE hwnd, __out XBOOL * pfNewDeviceCreated) = 0;
    virtual __checkReturn XRESULT ExitFullScreen() = 0;
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
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;

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


