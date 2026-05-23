
#if !defined(AFX_CEGETDEV_H__B7C12396_0FBD_11D3_8067_525400DA9DDD__INCLUDED_)
#define AFX_CEGETDEV_H__B7C12396_0FBD_11D3_8067_525400DA9DDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**********************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

**********************************************************************/
/////////////////////////// Rapier only samples ///////////////////////
#if _WIN32_WCE < 212  //non-Rapier devices
#error 'This sample works on Rapier devices only'
#endif
#include <aygshell.h>

//Menu Bar Height
#define MENU_HEIGHT 26

////////////////////////// SHGetMenu Macro's
#if _WIN32_WCE > 211 //Rapier devices

//#define SHCMBM_SETSUBMENU   (WM_USER + 400)
//#define SHCMBM_GETSUBMENU   (WM_USER + 401) // lParam == ID
//#define SHCMBM_GETMENU      (WM_USER + 402) // get the owning hmenu (as specified in the load resource)

#define SHGetMenu(hWndMB)  (HMENU)SendMessage((hWndMB), SHCMBM_GETMENU, (WPARAM)0, (LPARAM)0);
#define SHGetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);
#define SHSetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_SETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

//Alternate definition
#define SHMenuBar_GetMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

#else //non-Rapier devices

#define SHGetMenu(hWndCB) (HMENU)CommandBar_GetMenu(hWndCB, 0)
#define SHGetSubMenu(hWndCB,ID_MENU) (HMENU)GetSubMenu((HMENU)CommandBar_GetMenu(hWndCB, 0), ID_MENU)
#define SHSetSubMenu(hWndMB,ID_MENU)

#endif


#include "resource.h"

TCHAR szbufW[100];
TCHAR space[] = _T("   %s");

// structure for the lookup tables. 
typedef struct tagLookupEntry{
	int     Value;
	TCHAR    String[100];
} LookupEntry;

//GetDeviceCaps() codes from WINGDI.H 
#define NINDEX  28
LookupEntry  DevCaps[NINDEX] =
{{  0 , _T("DRIVERVERSION ")},
{  2 , _T("TECHNOLOGY    ")},
{  4 , _T("HORZSIZE      ")},
{  6 , _T("VERTSIZE      ")},
{  8 , _T("HORZRES       ")},
{  10, _T("VERTRES       ")},
{  12, _T("BITSPIXEL     ")},
{  14, _T("PLANES        ")},
{  16, _T("NUMBRUSHES    ")},
{  18, _T("NUMPENS       ")},
{  20, _T("NUMMARKERS    ")},
{  22, _T("NUMFONTS      ")},
{  24, _T("NUMCOLORS     ")},
{  26, _T("PDEVICESIZE   ")},
{  28, _T("CURVECAPS     ")},
{  30, _T("LINECAPS      ")},
{  32, _T("POLYGONALCAPS ")},
{  34, _T("TEXTCAPS      ")},
{  36, _T("CLIPCAPS      ")},
{  38, _T("RASTERCAPS    ")},
{  40, _T("ASPECTX       ")},
{  42, _T("ASPECTY       ")},
{  44, _T("ASPECTXY      ")},
{  88, _T("LOGPIXELSX    ")},
{  90, _T("LOGPIXELSY    ")},
{ 104, _T("SIZEPALETTE   ")},
{ 106, _T("NUMRESERVED   ")},
{ 108, _T("COLORRES      ")}};




/* Device Technologies */
#define NDevice 7
LookupEntry  Device[NDevice] =
{{ 0 , _T("DT_PLOTTER   ")},
{ 1 , _T("DT_RASDISPLAY")},
{ 2 , _T("DT_RASPRINTER")},
{ 3 , _T("DT_RASCAMERA ")},
{ 4 , _T("DT_CHARSTREAM")},
{ 5 , _T("DT_METAFILE  ")},
{ 6 , _T("DT_DISPFILE  ")}};


/* Curve Capabilities */
#define NCurveCaps 9
LookupEntry  CurveCaps[NCurveCaps] =
{{ 0   , _T("CC_NONE      ")},
{ 1   , _T("CC_CIRCLES   ")},
{ 2   , _T("CC_PIE       ")},
{ 4   , _T("CC_CHORD     ")},
{ 8   , _T("CC_ELLIPSES  ")},
{ 16  , _T("CC_WIDE      ")},
{ 32  , _T("CC_STYLED    ")},
{ 64  , _T("CC_WIDESTYLED")},
{ 128 , _T("CC_INTERIORS ")}};


/* Line Capabilities */
#define NLineCaps 8
LookupEntry  LineCaps[NLineCaps] =
{{ 0   , _T("LC_NONE       ")},
{ 2   , _T("LC_POLYLINE   ")},
{ 4   , _T("LC_MARKER     ")},
{ 8   , _T("LC_POLYMARKER ")},
{ 16  , _T("LC_WIDE       ")},
{ 32  , _T("LC_STYLED     ")},
{ 64  , _T("LC_WIDESTYLED ")},
{ 128 , _T("LC_INTERIORS  ")}};


/* Polygonal Capabilities */
#define NPolygonalCaps 10
LookupEntry  PolygonalCaps[NPolygonalCaps] =
{{ 0   , _T("PC_NONE       ")},
{ 1   , _T("PC_POLYGON    ")},
{ 2   , _T("PC_RECTANGLE  ")},
{ 4   , _T("PC_WINDPOLYGON")},
{ 4   , _T("PC_TRAPEZOID  ")},   // HACK   two 4's ???
{ 8   , _T("PC_SCANLINE   ")},
{ 16  , _T("PC_WIDE       ")},
{ 32  , _T("PC_STYLED     ")},
{ 64  , _T("PC_WIDESTYLED ")},
{ 128 , _T("PC_INTERIORS  ")}};


/* Clip Capabilities */
#define NClipCaps 2
LookupEntry  ClipCaps[NClipCaps] =
{{ 0   , _T("CP_NONE     ")},
{ 1   , _T("CP_RECTANGLE")}};


/* Text Capabilities */
#define NTextCaps 16
LookupEntry  TextCaps[NTextCaps] =
{{ 0x0001 , _T("TC_OP_CHARACTER")},
{ 0x0002 , _T("TC_OP_STROKE   ")},
{ 0x0004 , _T("TC_CP_STROKE   ")},
{ 0x0008 , _T("TC_CR_90       ")},
{ 0x0010 , _T("TC_CR_ANY      ")},
{ 0x0020 , _T("TC_SF_X_YINDEP ")},
{ 0x0040 , _T("TC_SA_DOUBLE   ")},
{ 0x0080 , _T("TC_SA_INTEGER  ")},
{ 0x0100 , _T("TC_SA_CONTIN   ")},
{ 0x0200 , _T("TC_EA_DOUBLE   ")},
{ 0x0400 , _T("TC_IA_ABLE     ")},
{ 0x0800 , _T("TC_UA_ABLE     ")},
{ 0x1000 , _T("TC_SO_ABLE     ")},
{ 0x2000 , _T("TC_RA_ABLE     ")},
{ 0x4000 , _T("TC_VA_ABLE     ")},
{ 0x8000 , _T("TC_RESERVED    ")}};


/* Raster Capabilities */
#define NRasterCaps 12
LookupEntry  RasterCaps[NRasterCaps] =
{{  1     , _T("RC_BITBLT       ")},
{  2     , _T("RC_BANDING      ")},
{  4     , _T("RC_SCALING      ")},
{  8     , _T("RC_BITMAP64     ")},
{  0x0010, _T("RC_GDI20_OUTPUT ")},
{  0x0080, _T("RC_DI_BITMAP    ")},
{  0x0100, _T("RC_PALETTE      ")},
{  0x0200, _T("RC_DIBTODEV     ")},
{  0x0400, _T("RC_BIGFONT      ")},
{  0x0800, _T("RC_STRETCHBLT   ")},
{  0x1000, _T("RC_FLOODFILL    ")},
{  0x2000, _T("RC_STRETCHDIB   ")}};

extern void ExpandInfo (HWND, int, int);

#endif // !defined(AFX_CEGETDEV_H__B7C12396_0FBD_11D3_8067_525400DA9DDD__INCLUDED_)
