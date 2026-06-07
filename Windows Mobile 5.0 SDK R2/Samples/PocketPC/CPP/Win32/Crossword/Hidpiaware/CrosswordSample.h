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

#if !defined(AFX_CROSSWORDSAMPLE_H__720235CB_6FEE_4BCD_8CC1_FE2A17392AA7__INCLUDED_)
#define AFX_CROSSWORDSAMPLE_H__720235CB_6FEE_4BCD_8CC1_FE2A17392AA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

//////////////////////////////////////////////////////////////////////////////
// STRUCTURES
//////////////////////////////////////////////////////////////////////////////

typedef struct 
{
    LPCWSTR szHint;
    BOOL    fDown;
    INT     x;
    INT     y;
    INT     cLetters;
} CROSSWORD_HINT;

//////////////////////////////////////////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////////////////////////////////////////

const int CROSSWORD_X = 15;
const int CROSSWORD_Y = 11;

//////////////////////////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////////////////////////

// The SHActiveateInfo used by the WM_SETTINGCHANGE and WM_ACTIVATE handlers.
extern SHACTIVATEINFO      g_sai;

// The current instance for this application.
extern HINSTANCE           g_hInst;                

// The handle to the command bar at the bottom of the app.
extern HWND                g_hwndCB;

// The font to use in the hint area.
extern HFONT               g_hFont;

// The offscreen bitmap where we draw the crossword puzzle.
extern HDC                 g_hMemDC;
extern HBITMAP             g_hMemBitmap;

// An index into the g_hints structure representing the currently 
// selected hint, -1 if no hint selected.
extern INT                 g_selectedHint;         

// The image list for the ENTER button.
extern HIMAGELIST          g_hImageList;

// The current state of the crossword (which letters are in which cells).
extern WCHAR               g_crossword[CROSSWORD_Y][CROSSWORD_X];

// The crossword solution (used to generate the g_hints structure).
extern const LPCWSTR       g_crosswordSolution[CROSSWORD_Y];

// An array of CROSSWORD_HINT structures (which contain the text, the start 
// location, the length, and the orientation of each hint).
extern CROSSWORD_HINT      g_hints[63];

//////////////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////

void                CreateCrossword();
HWND                CreateRpCommandBar(HWND);
BOOL                InitInstance    (HINSTANCE, int);
ATOM                MyRegisterClass (HINSTANCE, LPTSTR);
INT     CALLBACK    ToolsAboutDialog   (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    ToolsOptionsDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    ToolsOptionsDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    WndProc         (HWND, UINT, WPARAM, LPARAM);
BOOL                InWideMode();
void                CreateHintFont();
#endif // !defined(AFX_CROSSWORDSAMPLE_H__720235CB_6FEE_4BCD_8CC1_FE2A17392AA7__INCLUDED_)
