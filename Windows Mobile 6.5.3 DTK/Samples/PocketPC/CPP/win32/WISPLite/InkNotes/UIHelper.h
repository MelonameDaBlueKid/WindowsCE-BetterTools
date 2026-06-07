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
/*++

Copyright (c) 2003 Microsoft Corporation

Module Name:

    uihelper.h

Abstract:

    Include file for HIDPI / orientation / font change helper functions.

--*/

#ifndef __UIHELPER_H__
#define __UIHELPER_H__

#include <windows.h>
#include <commctrl.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// HIDPI functions and constants.
////////////////////////////////////////////////////////////////////////////////

#ifndef ILC_COLORMASK
#define ILC_COLORMASK 0x00FE
#endif

//
// The two macros HIDPISIGN and HIDPIABS are there to ensure correct rounding
// for negative numbers passed into HIDPIMulDiv as x (we want -1.5 to round 
// to -1, 2.5 to round to 2, etc).  So we use the absolute value of x, and then 
// multiply the result by the sign of x.  Y and z should never be negative, as 
// y is the dpi of the device (presumably 192 or 96), and z is always 96, as 
// that is our original dpi we developed on.
//

#define HIDPISIGN(x) (((x)<0)?-1:1)
#define HIDPIABS(x) (((x)<0)?-(x):x)
#define HIDPIMulDiv(x,y,z) ((((HIDPIABS(x)*(y))+((z)>>1))/(z))*HIDPISIGN(x))

//
// Cached values of GetDeviceCaps(LOGPIXELSX/Y) for the screen DC.
//
EXTERN_C int g_HIDPI_LogPixelsX;
EXTERN_C int g_HIDPI_LogPixelsY;

//
// You need to define these somewhere in your .c files only if you make use of 
// the scaling macros.  (Defined in UIHelper.cpp).
//
#define HIDPI_ENABLE \
    int g_HIDPI_LogPixelsX; \
    int g_HIDPI_LogPixelsY; 

//
// Scaling macros.
//
#define SCALEX(argX) (HIDPIMulDiv(argX,g_HIDPI_LogPixelsX,96))
#define SCALEY(argY) (HIDPIMulDiv(argY,g_HIDPI_LogPixelsY,96))

#define UNSCALEX(argX) (HIDPIMulDiv(argX,96,g_HIDPI_LogPixelsX))
#define UNSCALEY(argY) (HIDPIMulDiv(argY,96,g_HIDPI_LogPixelsY))

#define SCALERECT(rc) { rc.left = SCALEX(rc.left); rc.right = SCALEX(rc.right); rc.top = SCALEY(rc.top); rc.bottom = SCALEY(rc.bottom);}
#define SCALEPT(pt) { pt.x = SCALEX(pt.x); pt.y = SCALEY(pt.y);}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION: HIDPI_InitScaling
//
// PURPOSE: Initializes g_HIDPI_LogPixelsX and g_HIDPI_LogPixelsY.  This 
//     should be called once at the beginning of any HIDPI-aware application.
//
__inline void HIDPI_InitScaling()
{
    HDC screen;
    
    if( g_HIDPI_LogPixelsX )
        return;
    
    screen = GetDC(NULL);
    g_HIDPI_LogPixelsX = GetDeviceCaps(screen, LOGPIXELSX);
    g_HIDPI_LogPixelsY = GetDeviceCaps(screen, LOGPIXELSY);
    ReleaseDC(NULL, screen);
}


#ifdef __cplusplus
}
#endif
 
#endif // __UIHELPER_H__
