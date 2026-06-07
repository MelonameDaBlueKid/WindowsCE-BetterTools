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
  Screen.c

ABSTRACT: 
  This is a C file of the TTY Windows CE sample application. It shows
  the definitions of screen related functions.

***********************************************************************/

#include <windows.h>
#include "tty.h"

/***********************************************************************

  ClearScreen()

***********************************************************************/
void ClearScreen()
{
  int index;
  
  memset((char *)g_Screen.lpszScreenBuff, 
          TEXT(' '),
          g_Screen.NumRows *(g_Screen.NumCols + 1) * sizeof(TCHAR));
  
  for (index = 0; index < g_Screen.NumRows; index++) 
  {
    g_Screen.lpszScreenBuff[index *(g_Screen.NumCols + 1) + g_Screen.NumCols]
      = TEXT('\0');
  }

  g_Screen.TopRow = 0;
  g_Screen.LeftCol = 0;
  g_Screen.CursorRow = 0;
  g_Screen.CursorCol = 0;

  InvalidateRect(g_hTermWnd, NULL, TRUE);
  UpdateWindow(g_hTermWnd);
}

/***********************************************************************

  FillScreen()

***********************************************************************/
void FillScreen()
{
  int index;
  
  memset((char *)g_Screen.lpszScreenBuff, 
          TEXT(' '),
          g_Screen.NumRows *(g_Screen.NumCols + 1) * sizeof(TCHAR));
  
  for (index = 0; index < g_Screen.NumRows; index++) 
  {
    memcpy(&(SCREENPOS(index, 0)), 
            TEXT("Test row 00"), 
            11 * sizeof(TCHAR));

    g_Screen.lpszScreenBuff[index *(g_Screen.NumCols + 1) + 9] += 
(index / 10) % 10;

    g_Screen.lpszScreenBuff[index *(g_Screen.NumCols + 1) + 10] += 
      index % 10;

    g_Screen.lpszScreenBuff[index *(g_Screen.NumCols + 1) + g_Screen.NumCols]
      = TEXT('\0');
  }

  g_Screen.TopRow = 0;
  g_Screen.LeftCol = 0;
  g_Screen.CursorRow = 0;
  g_Screen.CursorCol = 0;
  
  InvalidateRect(g_hTermWnd, NULL, TRUE);
  UpdateWindow(g_hTermWnd);
}


/***********************************************************************

  PaintScreen(HWND hWnd, HDC  hDC, RECT* lpRect)

***********************************************************************/
void PaintScreen(
    HWND hWnd,
    HDC  hDC,
    RECT* lpRect
    )
{
    int iRow;
    DWORD dwX, 
        dwY,
        dwStartCol, 
        dwEndCol;
    HFONT hOldFont = NULL;
    
    hOldFont =(HFONT)SelectObject(hDC, g_hFont);
    
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(0xff, 0xff, 0xff));
    
    dwStartCol =(lpRect->left + g_Screen.CharWidth * g_Screen.LeftCol) /
        g_Screen.CharWidth;
    dwEndCol =(lpRect->right +(g_Screen.CharWidth + 1) * g_Screen.LeftCol) /
        g_Screen.CharWidth;
    
    if (dwEndCol > g_Screen.NumCols) 
    {
        dwEndCol = g_Screen.NumCols;
    }
    
    dwX =(dwStartCol - g_Screen.LeftCol) * g_Screen.CharWidth;
    
    for (iRow = g_Screen.TopRow, dwY = 0; 
    iRow <(g_Screen.TopRow + g_Screen.ScreenRows);
    iRow++, dwY += g_Screen.CharHeight) 
    {
        if ((ROWY(iRow+1) >= lpRect->top) &&(ROWY(iRow) <= lpRect->bottom))
        {
            ExtTextOut(hDC, dwX, dwY, 0, 0, &(SCREENPOS(iRow, dwStartCol)),
                dwEndCol - dwStartCol, NULL);
        }
    }
    
    if (!hOldFont) 
    {
        SelectObject(hDC, hOldFont);
    }
    
    if (g_Screen.bHaveFocus) 
    {
        if (ON_SCREEN(g_Screen.CursorRow, g_Screen.CursorCol)) 
        {
            SetCaretPos(COLX(g_Screen.CursorCol), ROWY(g_Screen.CursorRow));
            ShowCaret(g_hTermWnd);
        } 
        else 
        {
            HideCaret(g_hTermWnd);
        }
    }
}


/***********************************************************************

  InitScreenSettings(HWND hWnd)

***********************************************************************/
BOOL InitScreenSettings(
    HWND hWnd
    )
{
    HDC hDC = GetDC(hWnd);
    RECT rect;
    HFONT hOldFont;
    LOGFONT logfont;
    SCROLLINFO ScrollInfo;
    TEXTMETRIC TextMetrics;
    
    if (!g_Screen.lpszScreenBuff) 
    {
        g_Screen.NumRows = INIT_SCREEN_ROWS;
        g_Screen.NumCols = INIT_SCREEN_COLS;
        
        g_Screen.lpszScreenBuff =(PTCHAR) LocalAlloc(LPTR,
            g_Screen.NumRows *(g_Screen.NumCols + 1) * sizeof(TCHAR));
        
        if (!g_Screen.lpszScreenBuff) 
            return FALSE;
        
        memset((char *)&logfont, 0, sizeof(logfont));
        
        logfont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
        logfont.lfHeight = 13;
        
        g_hFont = CreateFontIndirect(&logfont);
    }
    
    hOldFont =(HFONT)SelectObject(hDC, g_hFont);
    
    GetTextMetrics(hDC, &TextMetrics);
    
    g_Screen.CharHeight =(USHORT)TextMetrics.tmHeight;
    g_Screen.CharWidth =(USHORT)TextMetrics.tmMaxCharWidth;
    
    if (!hOldFont)  
    {
        SelectObject(hDC,(HGDIOBJ)hOldFont);
    }
    
    ReleaseDC(hWnd, hDC);
    
    g_Screen.TopRow = 0;
    g_Screen.LeftCol = 0;
    g_Screen.CursorRow = 0;
    g_Screen.CursorCol = 0;
    
    GetClientRect(hWnd, &rect);
    
    g_Screen.ScreenRows =(unsigned short) rect.bottom / g_Screen.CharHeight;
    g_Screen.ScreenCols =(unsigned short) rect.right / g_Screen.CharWidth;
    
    // Set up the scroll bars.
    ScrollInfo.cbSize = sizeof(SCROLLINFO);
    ScrollInfo.fMask = SIF_RANGE|SIF_POS|SIF_PAGE;
    ScrollInfo.nMin = 0;
    ScrollInfo.nMax = g_Screen.NumRows;
    ScrollInfo.nPage = g_Screen.ScreenRows;
    ScrollInfo.nPos = 0;
    SetScrollInfo(hWnd, SB_VERT, &ScrollInfo, TRUE);
    
    ScrollInfo.fMask = SIF_RANGE|SIF_POS|SIF_PAGE;
    ScrollInfo.nMin = 0;
    ScrollInfo.nMax = g_Screen.NumCols;
    ScrollInfo.nPage = g_Screen.ScreenCols;
    ScrollInfo.nPos = 0;
    SetScrollInfo(hWnd, SB_HORZ, &ScrollInfo, TRUE);
    
    return TRUE;
}


/***********************************************************************

  ScrollDown(int iRows)

***********************************************************************/
void ScrollDown(
    int iRows
    )
{
    DWORD dwOldTop = g_Screen.TopRow;
    SCROLLINFO ScrollInfo;
    RECT rect;
    
    // Check some limit conditions.
    if ((iRows < 0) &&(-iRows > g_Screen.TopRow)) 
    {
        g_Screen.TopRow = 0;
    }
    else 
    {
        // Move the top row.
        g_Screen.TopRow += iRows;
        
        if (g_Screen.TopRow >(g_Screen.NumRows - g_Screen.ScreenRows)) 
            g_Screen.TopRow = g_Screen.NumRows - g_Screen.ScreenRows;
    }
    
    if (g_Screen.TopRow == dwOldTop) 
    {
        return;
    }
    
    GetClientRect(g_hTermWnd, &rect);
    HideCaret(g_hTermWnd);
    
    ScrollWindowEx(g_hTermWnd, 0, (dwOldTop - g_Screen.TopRow) * g_Screen.CharHeight,
        &rect, &rect, NULL, NULL, SW_INVALIDATE|SW_ERASE);
    
    ScrollInfo.cbSize = sizeof(SCROLLINFO);
    ScrollInfo.fMask = SIF_POS;
    ScrollInfo.nPos = g_Screen.TopRow;
    SetScrollInfo(g_hTermWnd, SB_VERT, &ScrollInfo, TRUE);
    
    ShowCaret(g_hTermWnd);
}


/***********************************************************************

  ScrollRight(int iCols)

***********************************************************************/
void ScrollRight(
    int iCols
    )
{
    DWORD dwOldLeft = g_Screen.LeftCol;
    SCROLLINFO ScrollInfo;
    RECT rect;
    
    if ((iCols < 0) &&(-iCols > g_Screen.LeftCol)) 
    {
        g_Screen.LeftCol = 0;
    }
    else 
    {
        g_Screen.LeftCol += iCols;
        
        if (g_Screen.LeftCol >(g_Screen.NumCols - g_Screen.ScreenCols)) 
            g_Screen.LeftCol = g_Screen.NumCols - g_Screen.ScreenCols;
    }
    
    if (g_Screen.LeftCol == dwOldLeft) 
        return;
    
    GetClientRect(g_hTermWnd, &rect);
    HideCaret(g_hTermWnd);
    
    ScrollWindowEx(g_hTermWnd, 
        (dwOldLeft - g_Screen.LeftCol) * g_Screen.CharWidth,
        0, &rect, &rect, NULL, NULL, SW_INVALIDATE | SW_ERASE);
    
    ScrollInfo.cbSize = sizeof(SCROLLINFO);
    ScrollInfo.fMask = SIF_POS;
    ScrollInfo.nPos = g_Screen.LeftCol;
    SetScrollInfo(g_hTermWnd, SB_HORZ, &ScrollInfo, TRUE);
    ShowCaret(g_hTermWnd);
}


/***********************************************************************

  PutCursorOnScreen()

***********************************************************************/
void PutCursorOnScreen()
{
    if (ON_SCREEN(g_Screen.CursorRow, g_Screen.CursorCol)) 
    {
        return;
    }
    
    if (g_Screen.CursorRow < g_Screen.TopRow) 
    {
        ScrollDown(g_Screen.CursorRow - g_Screen.TopRow);
    }
    else 
    {
        if (g_Screen.CursorRow >(g_Screen.TopRow + g_Screen.ScreenRows - 1))
        {
            ScrollDown(g_Screen.CursorRow - (g_Screen.TopRow + g_Screen.ScreenRows - 1));
        }
    }
    
    if (g_Screen.CursorCol < g_Screen.LeftCol) 
    {
        ScrollRight(g_Screen.CursorCol - g_Screen.LeftCol);
    }
    else 
    {
        if (g_Screen.CursorCol >(g_Screen.LeftCol + g_Screen.ScreenCols - 1)) 
        {
            ScrollRight(g_Screen.CursorCol - (g_Screen.LeftCol + g_Screen.ScreenCols - 1));
        }
    }
}


/***********************************************************************

  ProcessChar(BYTE byInChar)

***********************************************************************/
void ProcessChar(
    BYTE byInChar
    )
{
    RECT rect;
    int index;
    BOOL bOnScreen = ON_SCREEN(g_Screen.CursorRow, g_Screen.CursorCol);
    
    if (ON_SCREEN(g_Screen.CursorRow, g_Screen.CursorCol)) 
    {
        rect.top = ROWY(g_Screen.CursorRow);
        rect.bottom = ROWY(g_Screen.CursorRow + 1);
        rect.left = COLX((g_Screen.CursorCol) ?(g_Screen.CursorCol - 1) : 0);
        rect.right = COLX(g_Screen.CursorCol + 1);
        InvalidateRect(g_hTermWnd, &rect, TRUE);
    }
    
    switch (byInChar) 
    {
    case 0x08 :
        if (g_Screen.CursorCol) 
        {
            g_Screen.CursorCol--;
            CURPOS = TEXT(' ');
        }
        break;
        
    case 0x0d :
        g_Screen.CursorCol = 0;
        break;
        
    case 0x0a :
        g_Screen.CursorRow++;
        break;
        
    default :
        CURPOS = byInChar;
        g_Screen.CursorCol++;
        break;
    }
    
    if (g_Screen.CursorCol == g_Screen.NumCols) 
    {
        g_Screen.CursorRow++;
        g_Screen.CursorCol = 0;
    }
    
    if (g_Screen.CursorRow == g_Screen.NumRows) 
    {
        // Shift data up.
        for (index = 0; index <(g_Screen.NumRows - 1); index++) 
        {
            memcpy(&(SCREENPOS(index, 0)),
                &(SCREENPOS(index + 1, 0)),
                sizeof(TCHAR) *(g_Screen.NumCols));
        }    
        
        memset(&(SCREENPOS(index, 0)), TEXT(' '), g_Screen.NumCols);
        g_Screen.CursorRow--;
        
        InvalidateRect(g_hTermWnd, NULL, TRUE);
    }
    
    if (bOnScreen && !ON_SCREEN(g_Screen.CursorRow, g_Screen.CursorCol)) 
    {
        PutCursorOnScreen();
    }
}
