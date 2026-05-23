/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//
//  PARTICULAR PURPOSE.
//
// 
//
//  This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CEGETDEV_H__B7C12396_0FBD_11D3_8067_525400DA9DDD__INCLUDED_)
#define AFX_CEGETDEV_H__B7C12396_0FBD_11D3_8067_525400DA9DDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <aygshell.h>
#include "resource.h"

// support macros
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// structure for the lookup tables. 
typedef struct tagLookupEntry{
	int     Value;
	const TCHAR    * String;
} LookupEntry;

#define MENU_HEIGHT 26

//These lookup entries map the codes defined in WINGDI.H to readable character strings for display 
#define NINDEX  28
static const LookupEntry  DevCaps[NINDEX] =
{{  DRIVERVERSION , TEXT("DRIVERVERSION ")},
{  TECHNOLOGY , TEXT("TECHNOLOGY    ")},
{  HORZSIZE , TEXT("HORZSIZE      ")},
{  HORZSIZE , TEXT("VERTSIZE      ")},
{  HORZRES , TEXT("HORZRES       ")},
{  VERTRES, TEXT("VERTRES       ")},
{  BITSPIXEL, TEXT("BITSPIXEL     ")},
{  PLANES, TEXT("PLANES        ")},
{  NUMBRUSHES, TEXT("NUMBRUSHES    ")},
{  NUMPENS, TEXT("NUMPENS       ")},
{  NUMMARKERS, TEXT("NUMMARKERS    ")},
{  NUMFONTS, TEXT("NUMFONTS      ")},
{  NUMCOLORS, TEXT("NUMCOLORS     ")},
{  PDEVICESIZE, TEXT("PDEVICESIZE   ")},
{  CURVECAPS, TEXT("CURVECAPS     ")},
{  LINECAPS, TEXT("LINECAPS      ")},
{  POLYGONALCAPS, TEXT("POLYGONALCAPS ")},
{  TEXTCAPS, TEXT("TEXTCAPS      ")},
{  CLIPCAPS, TEXT("CLIPCAPS      ")},
{  RASTERCAPS, TEXT("RASTERCAPS    ")},
{  ASPECTX, TEXT("ASPECTX       ")},
{  ASPECTY, TEXT("ASPECTY       ")},
{  ASPECTXY, TEXT("ASPECTXY      ")},
{  LOGPIXELSX, TEXT("LOGPIXELSX    ")},
{  LOGPIXELSY, TEXT("LOGPIXELSY    ")},
{ SIZEPALETTE, TEXT("SIZEPALETTE   ")},
{ NUMRESERVED, TEXT("NUMRESERVED   ")},
{ COLORRES, TEXT("COLORRES      ")}};



/* Device Technologies */
#define NDEVICE 6
static const LookupEntry  Device[NDEVICE] =
{{ DT_PLOTTER , TEXT("DT_PLOTTER   ")},
{ DT_RASDISPLAY , TEXT("DT_RASDISPLAY")},
{ DT_RASPRINTER , TEXT("DT_RASPRINTER")},
{ DT_RASCAMERA , TEXT("DT_RASCAMERA ")},
{ DT_CHARSTREAM , TEXT("DT_CHARSTREAM")},
{ DT_DISPFILE , TEXT("DT_DISPFILE  ")}};


/* Curve Capabilities */
#define NCURVECAPS 10
static const LookupEntry  CurveCaps[NCURVECAPS] =
{{ CC_NONE   , TEXT("CC_NONE      ")},
{ CC_CIRCLES   , TEXT("CC_CIRCLES   ")},
{ CC_PIE   , TEXT("CC_PIE       ")},
{ CC_CHORD   , TEXT("CC_CHORD     ")},
{ CC_ELLIPSES   , TEXT("CC_ELLIPSES  ")},
{ CC_WIDE  , TEXT("CC_WIDE      ")},
{ CC_STYLED  , TEXT("CC_STYLED    ")},
{ CC_WIDESTYLED  , TEXT("CC_WIDESTYLED")},
{ CC_INTERIORS , TEXT("CC_INTERIORS ")},
{ CC_ROUNDRECT , TEXT("CC_ROUNDRECT ")}};


/* Line Capabilities */
#define NLINECAPS 8
static const LookupEntry  LineCaps[NLINECAPS] =
{{ LC_NONE   , TEXT("LC_NONE       ")},
{ LC_POLYLINE   , TEXT("LC_POLYLINE   ")},
{ LC_MARKER   , TEXT("LC_MARKER     ")},
{ LC_POLYMARKER   , TEXT("LC_POLYMARKER ")},
{ LC_WIDE  , TEXT("LC_WIDE       ")},
{ LC_STYLED  , TEXT("LC_STYLED     ")},
{ LC_WIDESTYLED  , TEXT("LC_WIDESTYLED ")},
{ LC_INTERIORS , TEXT("LC_INTERIORS  ")}};


/* Polygonal Capabilities */
#define NPOLYGONALCAPS 10
static const LookupEntry  PolygonalCaps[NPOLYGONALCAPS] =
{{ PC_NONE   , TEXT("PC_NONE       ")},
{ PC_POLYGON   , TEXT("PC_POLYGON    ")},
{ PC_RECTANGLE   , TEXT("PC_RECTANGLE  ")},
{ PC_WINDPOLYGON   , TEXT("PC_WINDPOLYGON")},
{ PC_TRAPEZOID   , TEXT("PC_TRAPEZOID  ")},   
{ PC_SCANLINE   , TEXT("PC_SCANLINE   ")},
{ PC_WIDE  , TEXT("PC_WIDE       ")},
{ PC_STYLED  , TEXT("PC_STYLED     ")},
{ PC_WIDESTYLED  , TEXT("PC_WIDESTYLED ")},
{ PC_INTERIORS , TEXT("PC_INTERIORS  ")}};


/* Clip Capabilities */
#define NCLIPCAPS 3
static const LookupEntry  ClipCaps[NCLIPCAPS] =
{{ CP_NONE   , TEXT("CP_NONE     ")},
{ CP_RECTANGLE   , TEXT("CP_RECTANGLE")}};


/* Text Capabilities */
#define NTEXTCAPS 17
static const LookupEntry  TextCaps[NTEXTCAPS] =
{{ TC_OP_CHARACTER , TEXT("TC_OP_CHARACTER")},
{ TC_OP_STROKE , TEXT("TC_OP_STROKE   ")},
{ TC_CP_STROKE , TEXT("TC_CP_STROKE   ")},
{ TC_CR_90 , TEXT("TC_CR_90       ")},
{ TC_CR_ANY , TEXT("TC_CR_ANY      ")},
{ TC_SF_X_YINDEP , TEXT("TC_SF_X_YINDEP ")},
{ TC_SA_DOUBLE , TEXT("TC_SA_DOUBLE   ")},
{ TC_SA_INTEGER , TEXT("TC_SA_INTEGER  ")},
{ TC_SA_CONTIN , TEXT("TC_SA_CONTIN   ")},
{ TC_EA_DOUBLE , TEXT("TC_EA_DOUBLE   ")},
{ TC_IA_ABLE , TEXT("TC_IA_ABLE     ")},
{ TC_UA_ABLE , TEXT("TC_UA_ABLE     ")},
{ TC_SO_ABLE , TEXT("TC_SO_ABLE     ")},
{ TC_RA_ABLE , TEXT("TC_RA_ABLE     ")},
{ TC_VA_ABLE , TEXT("TC_VA_ABLE     ")},
{ TC_RESERVED , TEXT("TC_RESERVED    ")},
{ TC_SCROLLBLT , TEXT("TC_SCROLLBLT    ")}};


/* Raster Capabilities */
#define NRASTERCAPS 15
static const LookupEntry  RasterCaps[NRASTERCAPS] =
{{  RC_BITBLT     , TEXT("RC_BITBLT       ")},
{  RC_BANDING     , TEXT("RC_BANDING      ")},
{  RC_SCALING     , TEXT("RC_SCALING      ")},
{  RC_BITMAP64     , TEXT("RC_BITMAP64     ")},
{  RC_GDI20_OUTPUT, TEXT("RC_GDI20_OUTPUT ")},
{  RC_GDI20_STATE, TEXT("RC_GDI20_STATE ")},
{  RC_SAVEBITMAP, TEXT("RC_SAVEBITMAP ")},
{  RC_DI_BITMAP, TEXT("RC_DI_BITMAP    ")},
{  RC_PALETTE, TEXT("RC_PALETTE      ")},
{  RC_DIBTODEV, TEXT("RC_DIBTODEV     ")},
{  RC_BIGFONT, TEXT("RC_BIGFONT      ")},
{  RC_STRETCHBLT, TEXT("RC_STRETCHBLT   ")},
{  RC_STRETCHDIB, TEXT("RC_STRETCHDIB   ")},
{  RC_OP_DX_OUTPUT, TEXT("RC_OP_DX_OUTPUT   ")},
{  RC_DEVBITS, TEXT("RC_DEVBITS   ")}
};



#endif // !defined(AFX_CEGETDEV_H__B7C12396_0FBD_11D3_8067_525400DA9DDD__INCLUDED_)
