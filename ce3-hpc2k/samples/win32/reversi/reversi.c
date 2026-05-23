/*****************************************************************************
  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.

  Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

  PROGRAM: Reversi.c

  ABSTRACT: Reversi Sample Game for _WIN32_WCE

  APPLICATION DEFINED FUNCTIONS:

  UpdateCursor() - Update the cursor position
  checkdepth() - Update Skill menu items
  clearboard() - Clear board and set starting pieces
  RevCreate() - Called on WM_CREATE messages
  printboard() - Draws game pieces on board
  ClearMessageTop() - Clears message bar
  ShowMessageTop() - Displays string in message bar
  drawboard() - Draws game board
  RevPaint() - Called on WM_PAINT messages
  FlashMessageTop() - Sets up system timer for callback procedure
  RevMessage() - Outputs flashing message at top of window
  flashsqr() - Flashes game piece
  RevMouseMove() - Update cursor to show legality of move
  ShowBestMove() - Update cursor and mouse position to show best move
  gameover() - Find a human reply to the computers move
  paintmove() - Make a move and show the results
  RevMenu() - Called on WM_COMMAND messages
  RevInit() - Initializes window data and registers window
  RevMouseClick() - Handle mouse click or keyboard space or CR
  Next() - Find next square
  Previous() - Find previous square
  ShowNextMove() - Show next legal move
  RevChar() - Called on WM_KEYDOWN messages
  InverseMessage() - Callback - inverts message bitmap or kills timer
  ReversiWndProc() - Processes messages for "Reversi" window
  AboutDlgProc() - processes messages for "About" dialog box

******************************************************************************

Functions:

    CheckMenuItem
    CommandBar_AddAdornments
    CommandBar_Create
    CommandBar_InsertMenubar
    CreateCommandBar
    CreateWindow
    DeleteObject
    DialogBox
    DispatchMessage
    Ellipse
    EndDialog
    EndPaint
    ExtTextOut
    GetClientRect
    GetDC
    GetDeviceCaps
    GetStockObject
    GetSystemMetrics
    GetTextExtentExPoint
    GetTextMetrics
    DefWindowProc
    KillTimer
    LoadAccelerators
    LoadImage
    LoadCursor
    LocalAlloc
    LocalFree
    MessageBox
    PostMessage
    Rectangle
    RegisterClass
    ReleaseCapture
    ReleaseDC
    SelectObject
    SetBkMode
    SetCapture
    SetFocus
    SetTimer
    SetWindowText   
    ShowWindow
    TranslateAccelerator
    TranslateMessage
    WndMain
    WndProc
    

    ******************************************************************************/

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "reversi.h"

// Exported procedures called from other modules
LONG APIENTRY ReversiWndProc(HWND, UINT, WPARAM, LONG);
LONG APIENTRY InverseMessage(HWND, UINT, WPARAM, LONG);
BOOL APIENTRY AboutDlgProc(HWND, WORD, WORD, LONG);

// Global variables
LPTSTR  pDisplayMessage;
HBRUSH  hbrBlack;
HBRUSH  hbrPat;
HBRUSH  hbrWhite;
HBRUSH  hbrRed;
HBRUSH  hbrGreen;
HBRUSH  hbrBlue;
HBRUSH  hbrHuman;
HBRUSH  hbrComputer;
HINSTANCE  hInst = NULL;
BOOL    fThinking = FALSE;
BOOL    fCheated = FALSE;
INT     direc[9] = {9, 10, 11, 1, -1, -9, -10, -11, 0};
WORD     prevCheck;
BYTE    board[max_depth+2][BoardSize];
INT     fPass;
INT     flashtimes;
INT     count;
INT     MessageOn;
INT     charheight;
INT     charwidth;
INT     xscr;
TCHAR   strBuf[80];
BOOL    bMouseDownInReversi = FALSE;
INT     xExt;
INT     yExt;
INT     Bx;
INT     By;
INT     ASPECT;
INT     COLOR;
INT     TXMIN;
INT     TYMIN = 45;
INT     dimension;
BOOL    ffirstmove;
POINT   LastHint;       //  to cleanup the ellipse drawn as a hint

TCHAR   szReversi[] = TEXT("Reversi");
TCHAR   szReversiPractice[] = TEXT("Reversi Practice Game");
TCHAR   szPass[] = TEXT("Pass");
TCHAR   szMustPass[] = TEXT("You must Pass");
TCHAR   szTie[] = TEXT("Tie Game");
TCHAR   szLoss[] = TEXT("You Lost by ");
TCHAR   szWon[] = TEXT("You Won by ");
TCHAR   szWonPost[30] = TEXT("");
TCHAR   szLossPost[30] = TEXT("");
TCHAR   szAbout[] = TEXT("About...");
TCHAR   szIllegal[] = TEXT("You may only move to a space where the cursor is a cross.");
TCHAR   szNoPass[] = TEXT("You may not pass.");
TCHAR   szHelpFile[] = TEXT("reversi.hlp");

HANDLE  hAccel;

POINT   MousePos;

INT     depth;
INT     BestMove[max_depth+2];
HDC     hDisp;
HWND    hWin;
INT     moves[61] = {11,18,81,88, 13,31,16,61,
                     38,83,68,86, 14,41,15,51,
                     48,84,58,85, 33,36,63,66,
                     34,35,43,46, 53,56,64,65,
                     24,25,42,47, 52,57,74,75,
                     23,26,32,37, 62,67,73,76,
                     12,17,21,28, 71,78,82,87,
                     22,27,72,77,
              0};

// declarations of functions in rev.c
INT NEAR PASCAL minmax(BYTE b[max_depth + 2][100], INT move, INT friendly,
    INT enemy, INT ply, INT vmin, INT vmax);
VOID NEAR PASCAL makemove(BYTE b[], INT move, INT friendly, INT enemy);
INT NEAR PASCAL legalcheck(BYTE b[], INT move, INT friendly, INT enemy);

#define LONG2POINT(l, pt)               ((pt).x = (SHORT)LOWORD(l), (pt).y = (SHORT)HIWORD(l))

#ifdef _WIN32_WCE
HWND hWndCB = NULL;
#endif


//
//  FUNCTION: checkdepth()
//
//  PURPOSE:  Update Skill menu items
//
VOID NEAR WINAPI checkdepth(
HWND hWindow,
WORD  d)
{
  HMENU hMenu;

#ifdef _WIN32_WCE
  hMenu = CommandBar_GetMenu( hWndCB, 0 );
  hMenu = GetSubMenu( hMenu, 1 );
#else
  hMenu = GetMenu(hWindow);
#endif

  CheckMenuItem(hMenu, prevCheck, MF_UNCHECKED);
  CheckMenuItem(hMenu, d, MF_CHECKED);
  prevCheck = d;
}

//
//  FUNCTION: clearboard()
//
//  PURPOSE:  Clear board and set starting pieces
//

VOID NEAR PASCAL clearboard(
BYTE b[max_depth+2][BoardSize])
{
  register INT  i,j;
  INT           k;

  for (i=0; i<=max_depth ; i++)
      for (j=0 ; j<=99 ; j++)
          b[i][j] = edge;

    for (i=0 ; i<=max_depth ; i++)
      {
        for (j=11 ; j<=81 ; j=j+10)
            for (k=j ; k<j+8 ; k++)
                b[i][k] = empty;

        b[i][45]=computer;
        b[i][54]=computer;
        b[i][44]=human;
        b[i][55]=human;
      }
}


//
//  FUNCTION: RevCreate()
//
//  PURPOSE:  Called on WM_CREATE messages
//

VOID NEAR PASCAL RevCreate(
register HWND   hWindow)

{
  register HDC  hDC;
  TEXTMETRIC    charsize;           // characteristics of the characters

  MessageOn   = FALSE;
  hDC = GetDC(hWindow);
  GetTextMetrics(hDC, (LPTEXTMETRIC)&charsize);

  charheight = charsize.tmHeight;
  charwidth = charsize.tmAveCharWidth;

  ReleaseDC(hWindow, hDC);

  if (COLOR == TRUE)
    {
      hbrComputer = hbrBlue;
      hbrHuman = hbrRed;
    }
  else
    {
      hbrComputer = hbrBlack;
      hbrHuman = hbrWhite;
    }

  TXMIN = 45 * ASPECT;

  clearboard(board);

  fPass = PASS;   // Okay to pass on first move
  depth = 1;
  prevCheck = EASY;
  ffirstmove = TRUE;
  checkdepth(hWindow, prevCheck);
}


//
//  FUNCTION: printboard()
//
//  PURPOSE:  Draws game pieces on board
//

VOID NEAR PASCAL printboard(
BYTE b[max_depth+2][BoardSize])

{
  register INT  i,j;
  INT sq;

  for (i=0; i < 8; i++)
    {
      for (j=0; j < 8; j++)
        {
          if ((sq = (INT)b[0][i*10+j+11]) != empty)
            {
              if (sq == computer)
                  SelectObject(hDisp, hbrComputer);
              else
                  SelectObject(hDisp, hbrHuman);

              Ellipse(hDisp,
                      Bx+2*ASPECT+i*xExt,
                      By+2+j*yExt,
                      Bx+2*ASPECT + i*xExt + xExt-4*ASPECT,
                      By+2+j*yExt + yExt-4);
            }
        }
    }
}


//
//  FUNCTION: ClearMessageTop()
//
//  PURPOSE:  Clears message bar
//

VOID NEAR PASCAL ClearMessageTop(
HDC     hDC)

{
  if (MessageOn == TRUE)
    {
      flashtimes = count + 1;
      SelectObject(hDC, (COLOR) ? hbrGreen : hbrWhite);
      Rectangle(hDC, 0, 0, xscr, charheight);
      MessageOn = FALSE;
    }
}


//
//  FUNCTION: ShowMessageTop()
//
//  PURPOSE:  Displays string in message bar
//

VOID NEAR PASCAL ShowMessageTop(
HDC     hDC,
LPTSTR  string)

{
  LONG  dx;
  SIZE  sizeRet;
  INT   MaxChar;
  #define WIDTH(x)  sizeRet.cx

  pDisplayMessage = string;
  ClearMessageTop(hDC);
  SelectObject(hDC, hbrWhite);
  Rectangle(hDC, 0, 0, xscr, charheight);
  SetBkMode(hDC, TRANSPARENT);
  GetTextExtentExPoint(hDC, string, lstrlen(string), xscr, &MaxChar, NULL, &sizeRet);
  dx = WIDTH(x);
  ExtTextOut(hDC, (INT)(xscr - dx)/2, 0, 0, NULL, string, lstrlen(string), NULL);
  MessageOn = TRUE;
  SetBkMode(hDC, OPAQUE);
}


//
//  FUNCTION()
//
//  PURPOSE:  Draws game board
//

VOID NEAR PASCAL drawboard(
BYTE b[max_depth+2][BoardSize])
{
  register INT  i;
  INT           lcx,lcy;
  register INT  xdimension;
  INT           xLineExt,yLineExt;
  POINT         pt[5];

  yLineExt = 8 * yExt;
  xLineExt = 8 * xExt;
  xdimension = dimension * ASPECT;

  SelectObject(hDisp, hbrBlack);
  Rectangle(hDisp, Bx+2*xdimension, By+2*dimension, xLineExt+Bx+2*xdimension, yLineExt+By+2*dimension);
  SelectObject(hDisp, hbrPat);
  Rectangle(hDisp, Bx, By, xLineExt+Bx, yLineExt+By);

  SelectObject(hDisp, hbrBlack);
  for (i=Bx; i <= Bx + xLineExt; i += xExt)
      Rectangle(hDisp, i, By, ASPECT+i, yLineExt+By);

  for (i=By; i <= By + yLineExt; i += yExt)
      Rectangle(hDisp, Bx, i, xLineExt+Bx, 1+i);

  lcx = Bx+xLineExt;
  lcy = By+yLineExt;

  SelectObject(hDisp, hbrPat);

  for (i=1; i < xdimension; ++i)
      Rectangle(hDisp, lcx+i, By+i/ASPECT, 1+lcx+i, yLineExt+By+i/ASPECT);


  for (i=1; i < dimension; ++i)   // Fill in bottom edge of puzzle.
      Rectangle(hDisp, Bx+i*ASPECT, lcy+i, xLineExt+Bx+i*ASPECT, 1+lcy+i);

  SelectObject(hDisp, hbrBlack);

  pt[0].x = lcx;                pt[0].y = By;
  pt[1].x = lcx+xdimension;     pt[1].y = By+dimension;
  pt[2].x = lcx+xdimension;     pt[2].y = lcy+dimension;
  pt[3].x = Bx+xdimension;      pt[3].y = lcy+dimension;
  pt[4].x = Bx;                 pt[4].y = lcy;
  Polyline(hDisp,pt,5);
  pt[0].x = lcx+xdimension;     pt[0].y = lcy+dimension;
  pt[1].x = lcx;                pt[1].y = lcy;
  Polyline(hDisp,pt,2);

  printboard(b);
}


//
//  FUNCTION: RevPaint()
//
//  PURPOSE:  Called on WM_PAINT messages
//

VOID NEAR PASCAL RevPaint(
HWND    hWindow,
HDC     hDC)

{
  register INT  Tx, Ty;
  INT           xLineExt, yLineExt;
  RECT          lpSize;

  hDisp = hDC;    // Since it is easy to resize we'll do it on every repaint
  hWin  = hWindow;
  SetBkMode(hDisp, OPAQUE);
  GetClientRect(hWindow, (LPRECT)&lpSize);

// The command bar is a control on the window client area, though it
//  behaves like non-client area. Thus we fake the paint routine out by making the
//  client area smaller by the amount of the command bar.
  lpSize.top -= CommandBar_Height (hWndCB);


  xscr = Tx = lpSize.right - lpSize.left;
  Ty = lpSize.bottom - lpSize.top;

  if (Tx < Ty*ASPECT)    // Dont go below minimum size
    {
      if (Tx < TXMIN)
          Tx = TXMIN;
      xExt = Tx / (9 + 1);
      yExt = xExt / ASPECT;
    }
  else
    {
      if (Ty < TYMIN)
          Ty = TYMIN;
      yExt = Ty / (9 + 1);
      xExt = yExt * ASPECT;
    }
  yLineExt = 8 * yExt;
  xLineExt = 8 * xExt;
  dimension = yLineExt/30;

  Bx = (Tx > xLineExt) ? (Tx - xLineExt) / 2 : 0;
  By = (Ty > yLineExt) ? (Ty - yLineExt) / 2 : 0;

  drawboard(board);

  if (MessageOn)
    {
      ShowMessageTop(hDisp, pDisplayMessage);
      Rectangle(hDC, 0, 0, xscr, charheight);
    }
}


//
//  FUNCTION: FlashMessageTop()
//
//  PURPOSE:  Sets up system timer for callback procedure
//
#ifndef _WIN32_WCE
VOID NEAR PASCAL FlashMessageTop(
HWND    hWindow)
{
  flashtimes = 0;
  count = 4;
  SetTimer(hWindow, 666, 200, (WNDPROC)InverseMessage);    /* Timer ID is 666 */
}
#endif

//
//  FUNCTION: RevMessage()
//
//  PURPOSE:  Outputs flashing message at top of window
//

VOID NEAR PASCAL RevMessage(
HWND            hWindow,
HDC             hDC,
register TCHAR  *pS,
INT             n,
TCHAR           *pchPostStr)
{
  register TCHAR *pch;

  pch = strBuf;
  while (*pS)
      *pch++ = *pS++;

  if (n)
    {
      if (n / 10)
          *pch++ = (TCHAR)(n / 10 + '0');
      *pch++ = (TCHAR)(n % 10 + '0');
    }

  if (pchPostStr)
    {
      while (*pchPostStr)
          *pch++ = *pchPostStr++;
    }
  *pch = (TCHAR)'\0';

#ifndef _WIN32_WCE
  ShowMessageTop(hDC, strBuf);
  FlashMessageTop(hWindow);
#else
  // just put up a message box right now as the cmdbar covers the area
  //  where the message would've been displayed.  plus we're already
  //  cramped for space vertically, so don't shrink the board to allow
  //  for the space used by the cmdbar
  MessageBox(hWindow, (LPTSTR)strBuf, (LPTSTR)szReversi, MB_OK);
#endif
}


//
//  FUNCTION: flashsqr()
//
//  PURPOSE:  Flashes game piece
//

VOID NEAR PASCAL flashsqr(
register HDC    hDC,
INT             x1,
INT             y1,
INT             Ex,
INT             Ey,
INT             color,
BOOL            fBlankSquare,
INT             n)

{
  register INT  i;

  if (fBlankSquare)
      SelectObject(hDC, GetStockObject(NULL_PEN));

//  SetCursor(curBlank);

  for (i=0; i < n; ++i)
    {
      if (color == 1)
          color = 2;
      else
          color = 1;

      if (color == 1)
          SelectObject(hDC,hbrComputer);
      else
          SelectObject(hDC, hbrHuman);

      SetBkMode(hDC, OPAQUE);
      Ellipse(hDC, x1, y1, x1+Ex, y1+Ey);
    }

  if (fBlankSquare)
    {
      SelectObject(hDC, hbrPat);
      Ellipse(hDC, x1, y1, x1+Ex, y1+Ey);
    }
}



//
//  FUNCTION: ShowBestMove()
//
//  PURPOSE:  Update cursor and mouse position to show best move
//

VOID NEAR PASCAL ShowBestMove(
HWND hwnd)

{
  HDC           hdc;
  INT           sq;
  register INT  x, y;
  INT           *pMoves;
  BOOL          bDone;

  if (fPass == PASS && !ffirstmove)
      return;

  if (!fCheated)
      SetWindowText(hwnd, (LPTSTR)szReversiPractice);

  fCheated = TRUE;
  fThinking = TRUE;

  if (ffirstmove)
    {
      x = 4;    // Hardcode the first move hint.
      y = 2;
    }
  else
    {
      if (depth == 1)
        {
          bDone = FALSE;
          pMoves = moves;
          sq = *pMoves;
          while (!bDone)
            {
              sq = *pMoves;
              if (legalcheck(board[0], sq, human, computer))
                  bDone = TRUE;
              else
                  pMoves++;
            }
          y = (sq - 11) % 10;
          x = (sq - 11) / 10;
        }
      else
        {
          minmax(board, BestMove[0],  computer, human, 1, -infin, infin);
          y = (BestMove[1] - 11) % 10;
          x = (BestMove[1] - 11) / 10;
        }
    }

  MousePos.x = (x * xExt) + Bx + xExt/2;
  MousePos.y = (y * yExt) + By + yExt/2;


  hdc = GetDC(hwnd);

  x = x * xExt + Bx + 2 * ASPECT;
  y = y * yExt + By + 2;

  // since we can't flash the square we just
  //  draw an outline of the piece as the hint
  SelectObject(hdc,GetStockObject(BLACK_PEN));
  SelectObject(hdc, hbrPat);
  SetBkMode(hdc, OPAQUE);
  Ellipse(hdc, x, y, x+xExt-4*ASPECT, y+yExt-4);
  LastHint.x = x; LastHint.y = y;

  fThinking = FALSE;

  ReleaseDC(hwnd, hdc);

}


//
//  FUNCTION: gameover()
//
//  PURPOSE:  Find a human reply to the computers move
//
//  COMMENTS:
//
//      As a side effect set flag fPass if the human
//      has a legal move.
//

VOID NEAR PASCAL gameover(
register HWND   hWindow,
HDC             hDC,
BYTE            b[max_depth + 2][BoardSize],
INT             r)

{
  register INT  i;
  INT           cc;
  INT           hc;
  INT           sq;
  INT           reply2;
  INT           *pMoves;

  pMoves = moves;
  fPass = PASS;
  reply2 = PASS;
  while ((sq = *pMoves++) != 0)
    {
      if (legalcheck(b[0], sq, human, computer))
          fPass = sq;
      else if (legalcheck(b[0], sq, computer, human))
          reply2 = sq;
    }

  if (fPass == PASS)
    {
      if ((r == PASS) || (reply2 == PASS))
        {
          hc = 0;
          cc = 0;
          for (i=11; i <= 88; i++)
            {
              if (b[0][i] == human)
                  hc++;
              else if (b[0][i] == computer)
                  cc++;
            }

          if (hc > cc)
              RevMessage(hWindow, hDC, szWon, hc-cc, szWonPost);
          else if (hc < cc)
              RevMessage(hWindow, hDC, szLoss, cc-hc, szLossPost);
          else
              RevMessage(hWindow, hDC, szTie, 0, NULL);
        }
      else
        {
          RevMessage(hWindow, hDC, szMustPass, 0, NULL);
        }
    }
  else if (r == PASS)
    {
      RevMessage(hWindow, hDC, szPass, 0, NULL);
    }
}


//
//  FUNCTION: paintmove()
//
//  PURPOSE:  Make a move and show the results
//

VOID NEAR PASCAL paintmove(
BYTE    b[BoardSize],
INT     move,
BYTE    friendly,
BYTE    enemy)
{
  INT           d;
  INT           sq;
  INT           *p;
  register INT  i,j;
  INT           color;

  if (LastHint.x) {     // to remove leftover artifact from a hint
    SelectObject(hDisp,GetStockObject(NULL_PEN));
    SelectObject(hDisp, hbrPat);
    SetBkMode(hDisp, OPAQUE);
    Ellipse(hDisp, LastHint.x-1, LastHint.y-1, LastHint.x+xExt-4*ASPECT+2, LastHint.y+yExt-4+2);
    SelectObject(hDisp,GetStockObject(BLACK_PEN));
    LastHint.x = LastHint.y = 0;
  }

  if (move != PASS)
    {
      if (friendly == computer)
        {
          SelectObject(hDisp, hbrComputer);
          color = 1;
        }
      else
        {
          SelectObject(hDisp, hbrHuman);
          color = 2;
        }

      i = ((move - 11) / 10) * xExt + Bx + 2 * ASPECT;
      j = ((move - 11) % 10) * yExt + By + 2;
      Ellipse(hDisp, i, j, i + xExt - 4 * ASPECT, j + yExt - 4);
      flashsqr(hDisp, i, j, xExt - 4 * ASPECT, yExt - 4, color, FALSE, 4);

      p = direc;
      while ((d = *p++) != 0)
        {
          sq=move;
          if (b[sq += d] == enemy)
           {
             while(b[sq += d] == enemy)
                ;
             if (b[sq] == (BYTE)friendly)
               {
                 while(b[sq -= d] == enemy)
                   {
                     board[0][sq] = b[sq] = friendly;
                     i = ((sq - 11)/10)*xExt+Bx+2*ASPECT;
                     j = ((sq - 11)%10)*yExt+By+2;
                     Ellipse(hDisp, i, j, i + xExt-4*ASPECT, j + yExt-4);
                   }
               }
           }
        }
      b[move]=friendly;
    }
}


//
//  FUNCTION: RevMenu()
//
//  PURPOSE:  Called on WM_COMMAND messages
//

VOID NEAR PASCAL RevMenu(
register HWND   hWindow,
INT             idval)

{
  HDC           hDC;
  register INT  cmd;

  if (fThinking)
      return;

  hWin = hWindow;

  switch (idval)
    {
      case EXIT:
          PostMessage(hWindow, WM_CLOSE, 0, 0L);
          break;

      case MN_HELP_ABOUT:
          DialogBox(hInst, MAKEINTRESOURCE(3), hWindow, (WNDPROC)AboutDlgProc);
          break;

      case MN_HELP_INDEX:
          break;

      case MN_HELP_USINGHELP:
          break;

      case MN_HELP_KEYBOARD:
          cmd = 0x1e;
          goto HelpCommon;

      case MN_HELP_COMMANDS:
          cmd = 0x20;
          goto HelpCommon;

      case MN_HELP_PLAYING:
          cmd = 0x21;
          goto HelpCommon;

      case MN_HELP_RULES:
          cmd = 0x22;
HelpCommon:
          break;

      case HINT:
          ShowBestMove(hWindow);
          return;
          break;

      case NEW:
          SetWindowText(hWindow , (LPTSTR)szReversi);
          ffirstmove = TRUE;
          hDisp = hDC = GetDC(hWindow);
          fCheated = FALSE;
          SetBkMode(hDisp, OPAQUE);
          ClearMessageTop(hDC);
          fPass = PASS;
          clearboard(board);
          drawboard(board);
          ReleaseDC(hWindow, hDC);
          hDisp = 0;
          break;

      case EASY:
          depth = 1;                      // MUST BE AT LEAST 1.
          checkdepth(hWindow, EASY);      // KEEP HANDS OFF!
          break;

      case MEDIUM:
          depth = 2;
          checkdepth(hWindow, MEDIUM);
          break;

      case HARD:
          depth = 4;
          checkdepth(hWindow, HARD);
          break;

      case VHARD:
          depth = 6;
          checkdepth(hWindow, VHARD);
          break;

      case PASS:
          if (fPass == PASS)
            {
              hDisp = hDC = GetDC(hWindow);
              SetBkMode(hDisp, OPAQUE);
              fThinking = TRUE;
              ClearMessageTop(hDC);
              ReleaseDC(hWindow, hDC);
              hDisp = 0;
              minmax(board, PASS, human, computer, 0, -infin, infin);
              hDisp = hDC = GetDC(hWindow);
              paintmove(board[0], BestMove[0], (BYTE)computer, (BYTE)human);
              gameover(hWindow, hDC, board, BestMove[0]);
              fThinking = FALSE;
              ReleaseDC(hWindow, hDC);
              hDisp = 0;
            }
          else
              MessageBox(hWindow, (LPTSTR)szNoPass, (LPTSTR)szReversi, MB_OK | MB_ICONASTERISK);
          break;
    }
}


//
//  FUNCTION: RevInit()
//
//  PURPOSE:  Initializes window data and registers window
//

BOOL NEAR PASCAL RevInit(
HINSTANCE hInstance)

{
  int iNumColors;

  register PWNDCLASS    pRevClass;
  HDC                   hdc;
  hInst = hInstance;
  hbrWhite = GetStockObject(WHITE_BRUSH);
  hbrBlack = GetStockObject(BLACK_BRUSH);
  hbrPat   = GetStockObject(LTGRAY_BRUSH);
  
  if (!hbrPat)
      return(FALSE);
  ffirstmove = TRUE;
  hdc = GetDC((HWND)NULL);
  
  iNumColors = GetDeviceCaps(hdc, NUMCOLORS);

  if(iNumColors > 4 || iNumColors == -1)
  {
    COLOR = TRUE;
  }
  else
  {
    COLOR = FALSE;  
  }

  if (GetDeviceCaps(hdc, VERTRES) == 200)
      ASPECT = 2;
  else
      ASPECT = 1;
  ReleaseDC((HWND)NULL, hdc);

  hbrRed        = (HBRUSH)CreateSolidBrush(RGB(0xFF,0,0));
  hbrGreen      = (HBRUSH)CreateSolidBrush(RGB(0,0xFF,0));
  hbrBlue       = (HBRUSH)CreateSolidBrush(RGB(0,0,0xFF));

  if (!hbrRed || !hbrGreen || !hbrBlue)
      return(FALSE);


  hAccel = LoadAccelerators(hInstance, (LPTSTR)TEXT("MAINACC"));
  pRevClass = (PWNDCLASS)((BYTE *)LocalAlloc(LMEM_ZEROINIT, sizeof(WNDCLASS)));
  if (!pRevClass)
      return(FALSE);

  pRevClass->hIcon  = (HICON)LoadImage(hInstance,
                                       MAKEINTRESOURCE(3),
                                       IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

  pRevClass->hCursor = 0;
  pRevClass->lpszClassName = (LPTSTR)TEXT("Reversi");
  pRevClass->hbrBackground = ((COLOR) ? hbrGreen : hbrWhite);
  pRevClass->lpfnWndProc   = ReversiWndProc;
  pRevClass->lpszMenuName  = NULL;
  pRevClass->hInstance    = hInstance;
  pRevClass->style         = CS_VREDRAW | CS_HREDRAW;

  if (!(RegisterClass (pRevClass)))
    {
      TCHAR ErrorMsg[32];
      wsprintf(ErrorMsg, TEXT("RegisterClass err=%ld\r\n"), GetLastError());
      OutputDebugString(ErrorMsg);
      LocalFree((HANDLE)pRevClass);
      return(FALSE);
    }
  LocalFree((HANDLE)pRevClass);

  return(TRUE);
}


//
//  FUNCTION: RevMouseClick()
//
//  PURPOSE:  Handle mouse click or keyboard space or CR
//

VOID NEAR PASCAL RevMouseClick(
HWND  hWnd,
POINT point)
{
  INT     move;
  INT     Si, Sj;
  INT     yLineExt = 8 * yExt;
  INT     xLineExt = 8 * xExt;
  HDC     hDC;

  MousePos.x = point.x;
  MousePos.y = point.y;

  if (xExt == 0 || yExt == 0)
      return;

  if ((point.x > Bx) && (point.x < (Bx+xLineExt)) && (point.y > By) && (point.y < (By+yLineExt)))
    {
      Si = (point.x - Bx) / xExt;
      Sj = (point.y - By) / yExt;
      move = Si * 10 + Sj + 11;
      if (legalcheck(board[0], move, human, computer))
        {
          board[0][move] = human;
          ffirstmove = FALSE;
          fThinking = TRUE;

          hDisp = hDC = GetDC(hWnd);
          ClearMessageTop(hDC);

          minmax(board, move, human, computer, 0, -infin, infin);
          makemove(board[0], move, human, computer);

          hDisp = hDC;

          paintmove(board[0], BestMove[0], computer, human);
          gameover(hWnd, hDC, board, BestMove[0]);

          ReleaseDC(hWnd, hDC);
          hDisp = 0;

          fThinking = FALSE;
        }
   }
}


//
//  FUNCTION: Next()
//
//  PURPOSE:  Find next square
//

VOID NEAR PASCAL Next(
register INT *px,
register INT *py)

{
  (*px)++;
  if (*px > 7)
    {
      *px = 0;
      (*py)++;
      if (*py > 7)
          *py = 0;
    }
}


//
//  FUNCTION: Previous()
//
//  PURPOSE:  Find previous square
//

VOID NEAR PASCAL Previous(
register INT *px,
register INT *py)
{
  (*px)--;
  if (*px < 0)
    {
      *px = 7;
      (*py)--;
      if (*py < 0)
          *py = 7;
    }
}


//
//  FUNCTION: ShowNextMove()
//
//  PURPOSE:  Show next legal move
//

VOID NEAR PASCAL ShowNextMove(
HWND    hwnd,
BOOL    fforward)
{
  INT       x, y;
  INT       potentialmove;
  BOOL      done;

  if (fPass == PASS && !ffirstmove)   // Watch out for infinite loops
      return;

  x = (MousePos.x - Bx) / xExt;
  y = (MousePos.y - By) / yExt;

  done = FALSE;
  while (!done)
    {
      do
        {
          if (fforward)
              Next(&x, &y);
          else
              Previous(&x, &y);
        }
      while ((board[0][potentialmove = (x * 10 + y + 11)]) != empty);

      fThinking = TRUE;
      if (legalcheck(board[0], potentialmove, human, computer))
          done = TRUE;

      fThinking = FALSE;
    }

  MousePos.x = x * xExt + Bx + xExt / 2;
  MousePos.y = y * yExt + By + yExt / 2;

//  UpdateCursor(hwnd);
//  RevMouseMove(MousePos);
}



//
//  FUNCTION: InverseMessage()
//
//  PURPOSE:  Callback - inverts message bitmap or kills timer
//
#ifndef _WIN32_WCE
LONG APIENTRY InverseMessage(
register HWND   hWindow,
UINT            message,
WPARAM          wParam,
LONG            lParam)
{
  HDC   hDC;

  message;
  wParam;
  lParam;

  if (flashtimes <= count)
    {
      hDC = GetDC(hWindow);
      Rectangle(hDC, 0, 0, xscr, charheight);
      //PatBlt(hDC, 0, 0, xscr, charheight, DSTINVERT);
      flashtimes++;
      ReleaseDC(hWindow, hDC);
    }
  else
      KillTimer(hWindow, 666);
  return(0L);
}
#endif


//
//  FUNCTION: ReversiWndProc()
//
//  PURPOSE:  Processes messages for "Reversi" window
//

LONG APIENTRY ReversiWndProc (
HWND            hWnd,
register UINT   message,
WPARAM          wParam,
LONG            lParam)
{
  PAINTSTRUCT   ps;
  POINT         curpoint;
  INT           bflag;
  int           nshow;
  BOOL          bmenu, badd;

  switch (message)
    {
      case WM_COMMAND:
          RevMenu(hWnd, GET_WM_COMMAND_ID(wParam, lParam));
          break;

      case WM_CREATE:
#ifdef _WIN32_WCE
          hWndCB = CommandBar_Create(hInst,hWnd,1);
          bmenu= CommandBar_InsertMenubar(hWndCB, hInst, 1, 0);
          badd= CommandBar_AddAdornments(hWndCB, 0, 0);
          nshow = CommandBar_Show(hWndCB, TRUE);
          bflag=(int)CommandBar_IsVisible( hWndCB,);
#endif
          RevCreate(hWnd);
          hWin = hWnd;
          break;

      case WM_CLOSE:
          return(DefWindowProc(hWnd, message, wParam, lParam));

      case WM_DESTROY:
            {
              // check this because the green brush is used as the class
              // background brush if we are on a color system in which
              // case we don't handle the brush deletion, Windows does
              if (!COLOR)
                DeleteObject(hbrGreen);

              DeleteObject(hbrRed);
              DeleteObject(hbrBlue);
            }

          // In case WinHelp keys off hWindow, we need to do the HELP_QUIT
          // here instead of when there is just one instance of help...
          //
          PostQuitMessage(0);
          break;

      case WM_ACTIVATE:
          if (!GetSystemMetrics(SM_MOUSEPRESENT))
            {
              if (GET_WM_ACTIVATE_STATE(wParam, lParam))
                {
                  if (GET_WM_ACTIVATE_HWND(wParam, lParam) != hWnd)
                    {
                      curpoint.x = MousePos.x;
                      curpoint.y = MousePos.y;
                      ClientToScreen(hWnd, (LPPOINT)&curpoint);
                    }
                }
            }
          if (wParam && (!HIWORD(lParam)))
              SetFocus(hWnd);
          break;

      case WM_PAINT:
          BeginPaint (hWnd, &ps);
          RevPaint(hWnd, ps.hdc);
          EndPaint(hWnd, &ps);
          break;

      case WM_MOUSEMOVE:
          {
          POINT pt;

          LONG2POINT(lParam, pt);  // convert LONG lParam to POINT structure

          break;
          }

      case WM_LBUTTONDOWN:
          SetCapture(hWnd);
          bMouseDownInReversi = TRUE;
          break;

      case WM_LBUTTONUP:
          {
          POINT pt;

          LONG2POINT(lParam, pt);  // convert LONG lParam to POINT structure

          ReleaseCapture();
          if (!fThinking && bMouseDownInReversi)
#ifdef ORGCODE
              RevMouseClick(hWnd, MAKEMPOINT(lParam));
#else
              RevMouseClick(hWnd, pt);
#endif
          bMouseDownInReversi = FALSE;
          break;
          }
      case WM_TIMER:
          // This should never be called.
          break;

      case WM_VSCROLL:
      case WM_HSCROLL:
              break;

      default:
          return(DefWindowProc(hWnd, message, wParam, lParam));
          break;
      }
  return(0L);
}

//
//  FUNCTION: AboutDlgProc(HWND, WORD, WORD, LONG)
//
//  PURPOSE:  Processes messages for "About" dialog box
//
//  MESSAGES:
//
//      WM_INITDIALOG - initialize dialog box
//      WM_COMMAND    - Input received
//

BOOL APIENTRY AboutDlgProc(
HWND        hDlg,
WORD        message,
WORD        wParam,
LONG        lParam)

{
  if (message == WM_COMMAND)
    {
      EndDialog(hDlg, TRUE);
      return(TRUE);
    }
  if (message == WM_INITDIALOG)
      return(TRUE);
  else
      return(FALSE);
  UNREFERENCED_PARAMETER(wParam);
  UNREFERENCED_PARAMETER(lParam);
}


//
//  FUNCTION: WinMain
//
//  PURPOSE: calls initialization function, processes message loop
//

int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrev,
    LPWSTR     lpCmdLine,
    int       cmdShow
) {
  HWND hWnd;
  MSG   msg;


  if (!hPrev)
    {
      if (!RevInit(hInstance))
          return(FALSE);
    }
  else
    {
      if (fThinking)
          return FALSE;
    }

  TYMIN = 45;
  fThinking = FALSE;


  hWnd = CreateWindow((LPTSTR)TEXT("Reversi"),
                fCheated ? (LPTSTR)szReversiPractice : (LPTSTR)szReversi,
                WS_VISIBLE,
                CW_USEDEFAULT,
                0,
                CW_USEDEFAULT,
                240,
                (HANDLE)NULL,
                (HANDLE)NULL,
                (HANDLE)hInstance,
                NULL);


  if (!hWnd)
      return(FALSE);

  ShowWindow(hWnd, cmdShow);
  UpdateWindow(hWnd);

  // Messaging Loop
  while (GetMessage((LPMSG)&msg, NULL, 0, 0))
    {
      if (!TranslateAccelerator(msg.hwnd, hAccel, (LPMSG)&msg))
        {
          TranslateMessage((LPMSG)&msg);
          DispatchMessage((LPMSG)&msg);
        }
    }
  return(0);
}
