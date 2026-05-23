// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     globals.h
//
//  PURPOSE:    contains variables and prototypes global to the application
//
//  PLATFORMS:  Windows CE
//
//  COMMENTS:
//
//

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//----------------------------------------------------------------------------
// Constants and Enumerations
typedef enum tagVERSION {WINNT, WIN32S, WIN95} VERSION;

typedef enum tagIMAGES { IMAGE_OPEN,IMAGE_CLOSED, IMAGE_WINDOW,
						IMAGE_CLASS, IMAGE_DOCUMENT} IMAGES;

//----------------------------------------------------------------------------
// Global Variables

HINSTANCE g_hInstance;                                   // initproc.c
VERSION version;                                         // main.c
HWND hwndCB;
HIMAGELIST himl;			// handle of the image list

//----------------------------------------------------------------------------
// Prototypes

void ErrorHandlerEx(WORD, LPTSTR);                               // main.c
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);       // wndproc.c
BOOL InitApplication(HINSTANCE);                                // initproc.c
BOOL InitInstance(HINSTANCE, int);                              // initproc.c
BOOL InitTreeViewImageLists(HWND);
BOOL InitTreeViewItems(HWND);
HTREEITEM AddItemToTree(HWND, LPTSTR, HTREEITEM, BOOL);
BOOL GetDirectoryContents(HWND hwndTV, LPTSTR pszDirectory,
                          HTREEITEM htiParent);
BOOL BuildDirectory(HWND, TV_ITEM, LPTSTR);
BOOL GetDrives(HWND);


//----------------------------------------------------------------------------
// Macros

#define IDC_TREEVIEW	101
#define CX_BITMAP		 16
#define CY_BITMAP		 15
#define NUM_BITMAPS		  3

#define TVIS_GCNOCHECK   1        // One-based index to state image list
#define TVIS_GCCHECK     2
#define TVIS_GCSOMECHECK 3

#define ErrorHandler() ErrorHandlerEx((WORD)__LINE__, TEXT(__FILE__))






#endif
