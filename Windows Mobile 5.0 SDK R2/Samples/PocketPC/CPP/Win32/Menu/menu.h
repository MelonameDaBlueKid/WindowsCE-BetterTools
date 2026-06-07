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

#if !defined(AFX_MENU_H__89B4130C_695D_11D3_93E5_525400E907B2__INCLUDED_)
#define AFX_MENU_H__89B4130C_695D_11D3_93E5_525400E907B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 1998 Microsoft Corp.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// Porting macro
#ifdef WIN32
#define LONG2POINT(l, pt)  ((pt).x = (SHORT)LOWORD(l), (pt).y = (SHORT)HIWORD(l))
#else
#define LONG2POINT(l, pt)  ((pt).x = (INT)LOWORD(l), (pt).y = (INT)HIWORD(l))
#endif

/* Defines for top-level menu positions */
#define IDFILE_POS     0
#define IDCOLORS_POS   1
#define IDSTATES_POS   2
#define IDHELP_POS     3

#define MEASUREITEMWIDTH  40
#define MEASUREITEMHEIGHT 40

/* States menu IDs */
#define IDM_STATE1       610
#define IDM_STATE2       611
#define IDM_STATE3       612
#define IDM_STATE4       613

/* BitBlt Raster operation */
#define ROP_PSDPxax     0x00B8074AL

BOOL MenuInit(HINSTANCE);
LONG CALLBACK MenuWndProc(HWND, UINT, UINT, LONG);
BOOL CALLBACK About(HWND, UINT, UINT, LONG);


#endif // !defined(AFX_MENU_H__89B4130C_695D_11D3_93E5_525400E907B2__INCLUDED_)
