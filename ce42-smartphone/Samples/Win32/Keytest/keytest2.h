/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

****************************************************************************/

#if !defined(AFX_KEYTEST2_H__A76303F3_1971_11D3_8E2D_00C04FAE2D6D__INCLUDED_)
#define AFX_KEYTEST2_H__A76303F3_1971_11D3_8E2D_00C04FAE2D6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#define MAX_LOADSTRING 100


//
// some privately defined application launching sequences
//  i guess this is totally unreliable and you shouldn't use it for a life threatening project
//  but you could always figure out of they changed by using this application 8)
// as such this is unsupported 
//
#define VK_APP_LAUNCH1       0xC1
#define VK_APP_LAUNCH2       0xC2
#define VK_APP_LAUNCH3       0xC3
#define VK_APP_LAUNCH4       0xC4
#define VK_APP_LAUNCH5       0xC5
#define VK_APP_LAUNCH6       0xC6
#define VK_APP_LAUNCH7       0xC7
#define VK_APP_LAUNCH8       0xC8
#define VK_APP_LAUNCH9       0xC9
#define VK_APP_LAUNCH10      0xCA
#define VK_APP_LAUNCH11      0xCB
#define VK_APP_LAUNCH12      0xCC
#define VK_APP_LAUNCH13      0xCD
#define VK_APP_LAUNCH14      0xCE
#define VK_APP_LAUNCH15      0xCF


// prototypes defined in keytest2.cpp
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About			(HWND, UINT, WPARAM, LPARAM);
void 				GetKeyName(WPARAM wParam, PTSTR szOut);
void 				ResizeWindow(HWND hwnd, BOOL bFullScreen);
BOOL				HandleCommand(HWND, WPARAM, LPARAM);
HWND				CreateMenuBar(HWND hwnd, HWND hwndCB, BOOL bCreating);



//
// globals
//
extern BOOL g_bHaveButtons;
extern WNDPROC g_lpfnListView;
extern BOOL fWM_KEYDOWN ;
extern BOOL fWM_KEYUP ;
extern BOOL fWM_CHAR ;
extern BOOL fWM_MOUSEMOVE ;
extern BOOL fWM_LBUTTONDOWN  ;
extern BOOL fWM_LBUTTONDBLCLK ;
extern BOOL fWM_LBUTTONUP ;
extern BOOL fWM_RBUTTONDOWN ;
extern BOOL fWM_RBUTTONUP ;
extern BOOL fWM_RBUTTONDBLCLK ;


#endif // !defined(AFX_KEYTEST2_H__A76303F3_1971_11D3_8E2D_00C04FAE2D6D__INCLUDED_)
