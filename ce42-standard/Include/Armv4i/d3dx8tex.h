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
///////////////////////////////////////////////////////////////////////////
//
//  File:       d3dx8tex.h
//  Content:    D3DX texturing APIs
//
///////////////////////////////////////////////////////////////////////////

#include "d3dx8.h"

#ifndef __D3DX8TEX_H__
#define __D3DX8TEX_H__


//-------------------------------------------------------------------------
// D3DX_FILTER flags:
// ------------------
//
// A valid filter must contain one of these values:
//
//  D3DX_FILTER_NONE
//      No scaling or filtering will take place.  Pixels outside the bounds
//      of the source image are assumed to be transparent black.
//  D3DX_FILTER_POINT
//      Each destination pixel is computed by sampling the nearest pixel
//      from the source image.
//  D3DX_FILTER_LINEAR
//      Each destination pixel is computed by linearly interpolating between
//      the nearest pixels in the source image.  This filter works best 
//      when the scale on each axis is less than 2.
//  D3DX_FILTER_TRIANGLE
//      Every pixel in the source image contributes equally to the
//      destination image.  This is the slowest of all the filters.
//  D3DX_FILTER_BOX
//      Each pixel is computed by averaging a 2x2(x2) box pixels from 
//      the source image. Only works when the dimensions of the 
//      destination are half those of the source. (as with mip maps)
//
//
// And can be OR'd with any of these optional flags:
//
//  D3DX_FILTER_MIRROR_U
//      Indicates that pixels off the edge of the texture on the U-axis
//      should be mirrored, not wraped.
//  D3DX_FILTER_MIRROR_V
//      Indicates that pixels off the edge of the texture on the V-axis
//      should be mirrored, not wraped.
//  D3DX_FILTER_MIRROR_W
//      Indicates that pixels off the edge of the texture on the W-axis
//      should be mirrored, not wraped.
//  D3DX_FILTER_MIRROR
//      Same as specifying D3DX_FILTER_MIRROR_U, D3DX_FILTER_MIRROR_V,
//      and D3DX_FILTER_MIRROR_V
//  D3DX_FILTER_DITHER
//      Dithers the resulting image.
//
//-------------------------------------------------------------------------

#define D3DX_FILTER_NONE      (1 << 0)
#define D3DX_FILTER_POINT     (2 << 0)
#define D3DX_FILTER_LINEAR    (3 << 0)
#define D3DX_FILTER_TRIANGLE  (4 << 0)
#define D3DX_FILTER_BOX       (5 << 0)

#define D3DX_FILTER_MIRROR_U  (1 << 16)
#define D3DX_FILTER_MIRROR_V  (2 << 16)
#define D3DX_FILTER_MIRROR_W  (4 << 16)
#define D3DX_FILTER_MIRROR    (7 << 16)
#define D3DX_FILTER_DITHER    (8 << 16)


//-------------------------------------------------------------------------
// D3DXIMAGE_INFO:
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
//      D3D format which most closely describes the data in original image
//
//-------------------------------------------------------------------------


typedef struct _D3DXIMAGE_INFO
{
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    D3DFORMAT Format;

} D3DXIMAGE_INFO;



#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------
// D3DXLoadSurfaceFromFile/Resource:
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
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//  pSrcInfo
//      Pointer to a D3DXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DXLoadSurfaceFromFileW(
        LPDIRECT3DSURFACE8    pDestSurface,
        CONST PALETTEENTRY*   pDestPalette,
        CONST RECT*           pDestRect,
        LPCWSTR               pSrcFile,
        CONST RECT*           pSrcRect,
        DWORD                 Filter,
        D3DCOLOR              ColorKey,
        D3DXIMAGE_INFO*       pSrcInfo);

#define D3DXLoadSurfaceFromFile D3DXLoadSurfaceFromFileW

HRESULT WINAPI
    D3DXLoadSurfaceFromResourceW(
        LPDIRECT3DSURFACE8    pDestSurface,
        CONST PALETTEENTRY*   pDestPalette,
        CONST RECT*           pDestRect,
        HMODULE               hSrcModule,
        LPCWSTR               pSrcResource,
        CONST RECT*           pSrcRect,
        DWORD                 Filter,
        D3DCOLOR              ColorKey,
        D3DXIMAGE_INFO*       pSrcInfo);


#define D3DXLoadSurfaceFromResource D3DXLoadSurfaceFromResourceW


HRESULT WINAPI
    D3DXLoadSurfaceFromFileInMemory(
        LPDIRECT3DSURFACE8    pDestSurface,
        CONST PALETTEENTRY*   pDestPalette,
        CONST RECT*           pDestRect,
        LPCVOID               pSrcData,
        UINT                  SrcDataSize,
        CONST RECT*           pSrcRect,
        DWORD                 Filter,
        D3DCOLOR              ColorKey,
        D3DXIMAGE_INFO*       pSrcInfo);



//-------------------------------------------------------------------------
// D3DXLoadSurfaceFromSurface:
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
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DXLoadSurfaceFromSurface(
        LPDIRECT3DSURFACE8    pDestSurface,
        CONST PALETTEENTRY*   pDestPalette,
        CONST RECT*           pDestRect,
        LPDIRECT3DSURFACE8    pSrcSurface,
        CONST PALETTEENTRY*   pSrcPalette,
        CONST RECT*           pSrcRect,
        DWORD                 Filter,
        D3DCOLOR              ColorKey);


//-------------------------------------------------------------------------
// D3DXCreateTextureFromFile:
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
//      Width in pixels; if zero or D3DX_DEFAULT, the width will be taken
//      from the file.
//  Height
//      Height in pixels; if zero of D3DX_DEFAULT, the height will be taken
//      from the file.
//  MipLevels
//      Number of mip levels;  if zero or D3DX_DEFAULT, a complete mipmap
//      chain will be created.
//  Usage
//      Texture usage flags
//  Format
//      Desired pixel format.  If D3DFMT_UNKNOWN, the format will be
//      taken from the file.
//  Pool
//      Memory pool to be used to create texture
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  MipFilter
//      D3DX_FILTER flags controlling how each miplevel is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_BOX,
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//  pSrcInfo
//      Pointer to a D3DXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//  pPalette
//      256 color palette to be filled in, or NULL
//  ppTexture
//      The texture object that will be created
//
//-------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateTextureFromFileExW(
        LPDIRECT3DDEVICE8     pDevice,
        LPCWSTR               pSrcFile,
        UINT                  Width,
        UINT                  Height,
        UINT                  MipLevels,
        DWORD                 Usage,
        D3DFORMAT             Format,
        D3DPOOL               Pool,
        DWORD                 Filter,
        DWORD                 MipFilter,
        D3DCOLOR              ColorKey,
        D3DXIMAGE_INFO*       pSrcInfo,
        PALETTEENTRY*         pPalette,
        LPDIRECT3DTEXTURE8*   ppTexture);

#define D3DXCreateTextureFromFileEx D3DXCreateTextureFromFileExW

HRESULT WINAPI
    D3DXCreateTextureFromResourceExW(
        LPDIRECT3DDEVICE8     pDevice,
        HMODULE               hSrcModule,
        LPCWSTR               pSrcResource,
        UINT                  Width,
        UINT                  Height,
        UINT                  MipLevels,
        DWORD                 Usage,
        D3DFORMAT             Format,
        D3DPOOL               Pool,
        DWORD                 Filter,
        DWORD                 MipFilter,
        D3DCOLOR              ColorKey,
        D3DXIMAGE_INFO*       pSrcInfo,
        PALETTEENTRY*         pPalette,
        LPDIRECT3DTEXTURE8*   ppTexture);

#define D3DXCreateTextureFromResourceEx D3DXCreateTextureFromResourceExW


//-------------------------------------------------------------------------
// D3DXCheckTextureRequirements:
// -----------------------------
//
// Checks texture creation parameters.  If parameters are invalid, this
// function returns corrected parameters.
//
// Parameters:
//
//  pDevice
//      The D3D device to be used
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
    D3DXCheckTextureRequirements(
        LPDIRECT3DDEVICE8     pDevice,
        UINT*                 pWidth,
        UINT*                 pHeight,
        UINT*                 pNumMipLevels,
        DWORD                 Usage,
        D3DFORMAT*            pFormat,
        D3DPOOL               Pool);


//-------------------------------------------------------------------------
// D3DXCreateTexture:
// ------------------
// Create an empty texture
//
// Parameters:
//
//  pDevice
//      The D3D device with which the texture is going to be used.
//  Width
//      width in pixels; must be non-zero
//  Height
//      height in pixels; must be non-zero
//  MipLevels
//      number of mip levels desired; if zero or D3DX_DEFAULT, a complete
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
    D3DXCreateTexture(
        LPDIRECT3DDEVICE8     pDevice,
        UINT                  Width,
        UINT                  Height,
        UINT                  MipLevels,
        DWORD                 Usage,
        D3DFORMAT             Format,
        D3DPOOL               Pool,
        LPDIRECT3DTEXTURE8*   ppTexture);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX8TEX_H__
