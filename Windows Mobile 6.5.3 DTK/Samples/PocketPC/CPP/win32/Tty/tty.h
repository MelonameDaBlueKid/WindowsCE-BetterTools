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

/***********************************************************************

MODULE: 
  Tty.h

ABSTRACT: 
  This is a header file of the TTY Windows CE sample application.

************************************************************************/

#ifndef _TTY_H_
#define _TTY_H_

// Structure TERM_SCREEN definition
typedef struct _TERM_SCREEN {
  USHORT  NumRows;          // Total number of rows in the buffer
  USHORT  NumCols;          // Total number of columns in the buffer
  USHORT  TopRow;           // Top row visible on the screen
  USHORT  LeftCol;          // Leftmost column visible on the screen    
  USHORT  ScreenRows;       // Number of rows visible on the screen
  USHORT  ScreenCols;       // Number of columns visible on the screen
  USHORT  CursorRow;        // Row of the cursor
  USHORT  CursorCol;        // Column of the cursor
  USHORT  CharHeight;       // Character width
  USHORT  CharWidth;        // Character height
  BOOL    bHaveFocus;       // Indication if it is focused on the screen
  LPTSTR  lpszScreenBuff;   // g_Screen buffer
} TERM_SCREEN, *PTERM_SCREEN;

#define ROWY(row) (((row) - g_Screen.TopRow) * g_Screen.CharHeight)

#define COLX(col) (((col) - g_Screen.LeftCol) * g_Screen.CharWidth)

#define ON_SCREEN(row,col) (((row) >= g_Screen.TopRow) && \
((row) < g_Screen.TopRow + g_Screen.ScreenRows) && \
((col) >= g_Screen.LeftCol) && \
((col) < g_Screen.LeftCol + g_Screen.ScreenCols) ? TRUE : FALSE)

#define SCREENPOS(r,c) (g_Screen.lpszScreenBuff[((r) * \
(g_Screen.NumCols + 1)) +(c)])

#define CURPOS (g_Screen.lpszScreenBuff[(g_Screen.CursorRow * \
(g_Screen.NumCols + 1)) + g_Screen.CursorCol])

// Initial screen values
#define INIT_SCREEN_COLS    36  // Initial screen columns
#define INIT_SCREEN_ROWS    25  // Initial screen rows

// Global Variables
extern TCHAR g_tszTitle[];         // Application window name
extern HWND g_hMainWnd;           // Main window handle
extern HWND g_hTermWnd;           // Terminal window handle
extern HFONT g_hFont;             // Handle to the font to use
extern HANDLE g_hPort;            // Serial port handle
extern HANDLE g_hReadThread;      // Handle to the read thread
extern LPTSTR g_lptszDevName;      // Communication port name
extern TERM_SCREEN g_Screen;      // Global screen structure

// Tty.c
VOID SetLightIndicators(
	DWORD
	);

// Port.c
BOOL PortInitialize(
	LPTSTR
	);
BOOL PortClose(
	HANDLE
	);
void PortWrite(
	BYTE
	);
DWORD PortReadThread(
	LPVOID
	);

// g_Screen.c
BOOL InitScreenSettings(
	HWND
	);
void FillScreen();
void ClearScreen();
void PaintScreen(
	HWND, 
	HDC, 
	RECT*
	);
void InvalidateChar(
	HWND
	);
void ProcessChar(
	BYTE
	);
void ScrollRight(
	int
	);
void ScrollDown(
	int
	);

#endif
