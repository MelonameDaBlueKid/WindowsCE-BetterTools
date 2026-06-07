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
//ink2.h

#if defined _x86_ || defined _X86_
#undef _x86_
#undef _X86_
#define _x86_
#define _X86_
#endif


/**********************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

**********************************************************************/
#include <windows.h>
#include <windowsx.h>

#include <tchar.h>
#include <commctrl.h>

#include <inkx.h>
#include <richink.h>

#include "resource.h"
#include "resrc1.h"

//
#ifndef SF_UTEXT
#define SF_UTEXT        0x0005
#endif



/////////////////////////// Pocket PC only samples ///////////////////////
#if _WIN32_WCE < 212 //non-Pocket PC devices
#error 'This sample works on Pocket PC devices only'
#endif
#include <aygshell.h>

#define LAYOUT_BUFFER       4
#define EDIT_HEIGHT         12
#define RADIO_BUTTOM_SIZE   18
#define BUTTON_SIZE         16

////////////////////////// SHGetMenu Macro's
#if _WIN32_WCE > 211 //Pocket PC devices

//#define SHCMBM_SETSUBMENU   (WM_USER + 400)
//#define SHCMBM_GETSUBMENU   (WM_USER + 401) // lParam == ID
//#define SHCMBM_GETMENU      (WM_USER + 402) // get the owning hmenu (as specified in the load resource)

#define SHGetMenu(hWndMB)  (HMENU)SendMessage((hWndMB), SHCMBM_GETMENU, (WPARAM)0, (LPARAM)0);
#define SHGetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);
#define SHSetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_SETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

//Alternate definition
#define SHMenuBar_GetMenu(hWndMB,ID_MENU) (HMENU)SendMessage((hWndMB), SHCMBM_GETSUBMENU, (WPARAM)0, (LPARAM)ID_MENU);

#else //non-Pocket PC devices

#define SHGetMenu(hWndCB) (HMENU)CommandBar_GetMenu(hWndCB, 0)
#define SHGetSubMenu(hWndCB,ID_MENU) (HMENU)GetSubMenu((HMENU)CommandBar_GetMenu(hWndCB, 0), ID_MENU)
#define SHSetSubMenu(hWndMB,ID_MENU)

#endif
