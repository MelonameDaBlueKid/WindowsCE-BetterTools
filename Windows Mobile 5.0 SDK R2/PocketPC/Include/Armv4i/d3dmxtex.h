//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of your Microsoft Windows CE
// Source Alliance Program license form.  If you did not accept the terms of
// such a license, you are not authorized to use this source code.
//
///////////////////////////////////////////////////////////////////////////
//
//  File:       d3dmxtexp.h
//  Content:    D3DMX texturing APIs
//
///////////////////////////////////////////////////////////////////////////

#include "d3dmx.h"

#ifndef __D3DMXTEX_H__
#define __D3DMXTEX_H__


//-------------------------------------------------------------------------
// D3DMX_FILTER flags:
// ------------------
//
// A valid filter must contain one of these values:
//
//  D3DMX_FILTER_NONE
//      No scaling or filtering will take place.  Pixels outside the bounds
//      of the source image are assumed to be transparent black.
//  D3DMX_FILTER_POINT
//      Each destination pixel is computed by sampling the nearest pixel
//      from the source image.
//  D3DMX_FILTER_LINEAR
//      Each destination pixel is computed by linearly interpolating between
//      the nearest pixels in the source image.  This filter works best 
//      when the scale on each axis is less than 2.
//  D3DMX_FILTER_TRIANGLE
//      Every pixel in the source image contributes equally to the
//      destination image.  This is the slowest of all the filters.
//  D3DMX_FILTER_BOX
//      Each pixel is computed by averaging a 2x2(x2) box pixels from 
//      the source image. Only works when the dimensions of the 
//      destination are half those of the source. (as with mip maps)
//
//
// And can be OR'd with any of these optional flags:
//
//  D3DMX_FILTER_MIRROR_U
//      Indicates that pixels off the edge of the texture on the U-axis
//      should be mirrored, not wrapped.
//  D3DMX_FILTER_MIRROR_V
//      Indicates that pixels off the edge of the texture on the V-axis
//      should be mirrored, not wrapped.
//  D3DMX_FILTER_MIRROR_W
//      Indicates that pixels off the edge of the texture on the W-axis
//      should be mirrored, not wrapped.
//  D3DMX_FILTER_MIRROR
//      Same as specifying D3DMX_FILTER_MIRROR_U, D3DMX_FILTER_MIRROR_V,
//      and D3DMX_FILTER_MIRROR_V
//  D3DMX_FILTER_DITHER
//      Dithers the resulting image.
//
//-------------------------------------------------------------------------

#define D3DMX_FILTER_NONE      (1 << 0)
#define D3DMX_FILTER_POINT     (2 << 0)
#define D3DMX_FILTER_LINEAR    (3 << 0)
#define D3DMX_FILTER_TRIANGLE  (4 << 0)
#define D3DMX_FILTER_BOX       (5 << 0)

#define D3DMX_FILTER_MIRROR_U  (1 << 16)
#define D3DMX_FILTER_MIRROR_V  (2 << 16)
#define D3DMX_FILTER_MIRROR_W  (4 << 16)
#define D3DMX_FILTER_MIRROR    (7 << 16)
#define D3DMX_FILTER_DITHER    (8 << 16)


//-------------------------------------------------------------------------
// D3DMXIMAGE_INFO:
// ---------------
// This structure is used to return a rough description of what the
// the original contents of an image file looked like.
// 
//  Width
//      Width of original image in pixels
//  Height
//      Height of original image in pixels
//  Depth
//      Depth of original image in pixels
//  MipLevels
//      Number of mip levels in original image
//  Format
//      D3DM format which most closely describes the data in original image
//
//-------------------------------------------------------------------------


typedef struct _D3DMXIMAGE_INFO
{
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    D3DMFORMAT Format;

} D3DMXIMAGE_INFO;



#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------
// D3DMXLoadSurfaceFromFile/Resource:
// ---------------------------------
// Load surface from a file or resource
//
// Parameters:
//  pDestSurface
//      Destination surface, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestRect
//      Destination rectangle, or NULL for entire surface
//  pSrcFile
//      File name of the source image.
//  pSrcModule
//      Module where resource is located, or NULL for module associated
//      with image the os used to create the current process.
//  pSrcResource
//      Resource name
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcRect
//      Source rectangle, or NULL for entire image
//  Filter
//      D3DMX_FILTER flags controlling how the image is filtered.
//      Or D3DMX_DEFAULT for D3DMX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//  pSrcInfo
//      Pointer to a D3DMXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DMXLoadSurfaceFromFileW(
        LPDIRECT3DMOBILESURFACE pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        LPCWSTR                 pSrcFile,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DMCOLOR               ColorKey,
        D3DMXIMAGE_INFO*        pSrcInfo);

#define D3DMXLoadSurfaceFromFile D3DMXLoadSurfaceFromFileW

HRESULT WINAPI
    D3DMXLoadSurfaceFromResourceW(
        LPDIRECT3DMOBILESURFACE pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DMCOLOR               ColorKey,
        D3DMXIMAGE_INFO*         pSrcInfo);


#define D3DMXLoadSurfaceFromResource D3DMXLoadSurfaceFromResourceW


HRESULT WINAPI
    D3DMXLoadSurfaceFromFileInMemory(
        LPDIRECT3DMOBILESURFACE pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DMCOLOR               ColorKey,
        D3DMXIMAGE_INFO*        pSrcInfo);



//-------------------------------------------------------------------------
// D3DMXLoadSurfaceFromSurface:
// --------------------------
// Load surface from another surface (with color conversion)
//
// Parameters:
//  pDestSurface
//      Destination surface, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestRect
//      Destination rectangle, or NULL for entire surface
//  pSrcSurface
//      Source surface
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcRect
//      Source rectangle, or NULL for entire surface
//  Filter
//      D3DMX_FILTER flags controlling how the image is filtered.
//      Or D3DMX_DEFAULT for D3DMX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DMXLoadSurfaceFromSurface(
        LPDIRECT3DMOBILESURFACE pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        LPDIRECT3DMOBILESURFACE pSrcSurface,
        CONST PALETTEENTRY*     pSrcPalette,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DMCOLOR               ColorKey);


//-------------------------------------------------------------------------
// D3DMXCreateTextureFromFile:
// --------------------------
// Create a texture object from a file.
//
// Parameters:
//
//  pDevice
//      The D3D device with which the texture is going to be used.
//  pSrcFile
//      File name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module
//  pvSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  Width
//      Width in pixels; if zero or D3DMX_DEFAULT, the width will be taken
//      from the file.
//  Height
//      Height in pixels; if zero of D3DMX_DEFAULT, the height will be taken
//      from the file.
//  MipLevels
//      Number of mip levels;  if zero or D3DMX_DEFAULT, a complete mipmap
//      chain will be created.
//  Usage
//      Texture usage flags
//  Format
//      Desired pixel format.  If D3DMFMT_UNKNOWN, the format will be
//      taken from the file.
//  Pool
//      Memory pool to be used to create texture
//  Filter
//      D3DMX_FILTER flags controlling how the image is filtered.
//      Or D3DMX_DEFAULT for D3DMX_FILTER_TRIANGLE.
//  MipFilter
//      D3DMX_FILTER flags controlling how each miplevel is filtered.
//      Or D3DMX_DEFAULT for D3DMX_FILTER_BOX,
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//  pSrcInfo
//      Pointer to a D3DMXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//  pPalette
//      256 color palette to be filled in, or NULL
//  ppTexture
//      The texture object that will be created
//
//-------------------------------------------------------------------------

HRESULT WINAPI
    D3DMXCreateTextureFromFileExW(
        LPDIRECT3DMOBILEDEVICE     pDevice,
        LPCWSTR               pSrcFile,
        UINT                  Width,
        UINT                  Height,
        UINT                  MipLevels,
        DWORD                 Usage,
        D3DMFORMAT             Format,
        D3DMPOOL               Pool,
        DWORD                 Filter,
        DWORD                 MipFilter,
        D3DMCOLOR              ColorKey,
        D3DMXIMAGE_INFO*       pSrcInfo,
        PALETTEENTRY*         pPalette,
        LPDIRECT3DMOBILETEXTURE*   ppTexture);

#define D3DMXCreateTextureFromFileEx D3DMXCreateTextureFromFileExW

HRESULT WINAPI
    D3DMXCreateTextureFromResourceExW(
        LPDIRECT3DMOBILEDEVICE   pDevice,
        HMODULE                  hSrcModule,
        LPCWSTR                  pSrcResource,
        UINT                     Width,
        UINT                     Height,
        UINT                     MipLevels,
        DWORD                    Usage,
        D3DMFORMAT               Format,
        D3DMPOOL                 Pool,
        DWORD                    Filter,
        DWORD                    MipFilter,
        D3DMCOLOR                ColorKey,
        D3DMXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*            pPalette,
        LPDIRECT3DMOBILETEXTURE* ppTexture);

#define D3DMXCreateTextureFromResourceEx D3DMXCreateTextureFromResourceExW


//-------------------------------------------------------------------------
// D3DMXCheckTextureRequirements:
// -----------------------------
//
// Checks texture creation parameters.  If parameters are invalid, this
// function returns corrected parameters.
//
// Parameters:
//
//  pDevice
//      The D3DM device to be used
//  pWidth
//      Desired width in pixels, or NULL.  Returns corrected width.
//  pHeight
//      Desired height in pixels, or NULL.  Returns corrected height.
//  pNumMipLevels
//      Number of desired mipmap levels, or NULL.  Returns corrected number.
//  Usage
//      Texture usage flags
//  pFormat
//      Desired pixel format, or NULL.  Returns corrected format.
//  Pool
//      Memory pool to be used to create texture
//
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DMXCheckTextureRequirements(
        LPDIRECT3DMOBILEDEVICE pDevice,
        UINT*                  pWidth,
        UINT*                  pHeight,
        UINT*                  pNumMipLevels,
        DWORD                  Usage,
        D3DMFORMAT*            pFormat,
        D3DMPOOL               Pool);


//-------------------------------------------------------------------------
// D3DMXCreateTexture:
// ------------------
// Create an empty texture
//
// Parameters:
//
//  pDevice
//      The D3DM device with which the texture is going to be used.
//  Width
//      width in pixels; must be non-zero
//  Height
//      height in pixels; must be non-zero
//  MipLevels
//      number of mip levels desired; if zero or D3DMX_DEFAULT, a complete
//      mipmap chain will be created.
//  Usage
//      Texture usage flags
//  Format
//      Pixel format.
//  Pool
//      Memory pool to be used to create texture
//  ppTexture
//      The texture object that will be created
//
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DMXCreateTexture(
        LPDIRECT3DMOBILEDEVICE   pDevice,
        UINT                     Width,
        UINT                     Height,
        UINT                     MipLevels,
        DWORD                    Usage,
        D3DMFORMAT               Format,
        D3DMPOOL                 Pool,
        LPDIRECT3DMOBILETEXTURE* ppTexture);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DMXTEX_H__
