// ***************************************************************************
// GRAPHICS.CPP
//
// Graphics routines for Minesweeper
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include "winmine.h"

void DrawScreen()
{
	HDC			hdc;
	PAINTSTRUCT	ps;
	RECT		rc;

	if ((hdc = BeginPaint(g_hwndMain, &ps))) 
    {
		DrawBoard(hdc);
		DrawRectangle(hdc, g_hpenBorder, &g_rcBoard);

		// don't draw the selection rectangle if the game is over
		if (g_gd.gsStatus != GAMEOVER)
        {
			// calculate where the selection rectangle should go
			// rectangle should be one pixel above and to the left of the normal block position
			rc.top = SCREENY(g_iCurY, g_iOffY);
			rc.left = SCREENX(g_iCurX, g_iOffX);
			rc.bottom = rc.top + IMAGE_SIZE;
			rc.right = rc.left + IMAGE_SIZE;
			DrawRectangle(hdc, g_hpenSelection, &rc);
		}

		EndPaint(g_hwndMain, &ps);
	}
}

void DrawBoard(HDC hdc)
{
	int iImg, x, y;

	// get a handle on the window's device context
	VERIFY(SelectObject(g_hdcImage, g_hbmpBlocks));

	switch (g_gd.gsStatus) 
    {
		case NEWGAME:
			for (y = 0; y < g_iDefaults[g_gd.gtType][INDEX_YBLOCKS]; y++) 
            {
				for (x = 0; x < g_iDefaults[g_gd.gtType][INDEX_XBLOCKS]; x++) 
                {
                    BitBlt(hdc, SCREENX(x, g_iOffX), SCREENY(y, g_iOffY), IMAGE_SIZE, 
                        IMAGE_SIZE, g_hdcImage, 0, IMGY(IMAGE_COVERED), SRCCOPY);
				}
			}
			break;

		case PLAYING:
			for (y = 0; y < g_iDefaults[g_gd.gtType][INDEX_YBLOCKS]; y++) 
            {
				for (x = 0; x < g_iDefaults[g_gd.gtType][INDEX_XBLOCKS]; x++) 
                {
					switch (BLOCKSTATE(x, y)) {
						case STATE_COVERED:
							iImg = IMAGE_COVERED;
							break;

						case STATE_UNCOVERED:
							iImg = BLOCKTYPE(x, y);
							break;

						case STATE_MARKED:
							iImg = IMAGE_MARKED;
							break;

						case STATE_QUESTION:
							iImg = IMAGE_QUESTION;
							break;
					}

					// now that we know the image type, paint the bomb
					BitBlt(hdc, SCREENX(x, g_iOffX), SCREENY(y, g_iOffY), IMAGE_SIZE, 
						   IMAGE_SIZE, g_hdcImage, 0, IMGY(iImg), SRCCOPY);
				}
			}
			break;

		case GAMEOVER:
			for (y = 0; y < g_iDefaults[g_gd.gtType][INDEX_YBLOCKS]; y++) 
            {
				for (x = 0; x < g_iDefaults[g_gd.gtType][INDEX_XBLOCKS]; x++) 
                {
					switch (BLOCKSTATE(x, y)) 
                    {
						case STATE_COVERED:
							if (IsMine(x, y)) 
                            {
								iImg = IMAGE_BOMB;
							} 
                            else 
                            {
								iImg = IMAGE_COVERED;
							}
							break;

						case STATE_UNCOVERED:
							if (IsMine(x, y)) 
                            {
								iImg = IMAGE_REDBOMD;
							} 
                            else 
                            {
								iImg = BLOCKTYPE(x, y);
							}
							break;

						case STATE_MARKED:
							if (IsMine(x, y)) 
                            {
								iImg = IMAGE_MARKED;
							} 
                            else 
                            {
								iImg = IMAGE_WRONGBOMB;
							}
							break;

						case STATE_QUESTION:
							if (IsMine(x, y)) 
                            {
								iImg = IMAGE_BOMB;
							} 
                            else 
                            {
								iImg = IMAGE_QUESTION;
							}
							break;
					}

					// now that we know the image type, paint the bomb
                    BitBlt(hdc, SCREENX(x, g_iOffX), SCREENY(y, g_iOffY), IMAGE_SIZE, 
                        IMAGE_SIZE, g_hdcImage, 0, IMGY(iImg), SRCCOPY);
    			}
			}
			break;
	}
}

void DrawRectangle(
    HDC hdc, 
    HPEN hPen, 
    LPRECT rc
    )
{
	HGDIOBJ hPenOld;
	HGDIOBJ hbrOld;

	// select the pen and a NULL brush into the hdc
	hPenOld = SelectObject(hdc, hPen);
	hbrOld = SelectObject(hdc, GetStockObject(NULL_BRUSH));
 
	// draw the border rectangle
	Rectangle(hdc, rc->left, rc->top, rc->right, rc->bottom);
 
	// Put back the old stuff
	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hbrOld); 
}

HPEN MyCreatePen(
    UINT uiStyle, 
    UINT uiWidth,
    COLORREF crColor
    )
{
	LOGPEN lp;
	POINT pt;

	// set the style information
	pt.x = uiWidth;
	pt.y = 0;
	lp.lopnStyle = uiStyle;
	lp.lopnWidth = pt;
	lp.lopnColor = crColor;

	return CreatePenIndirect(&lp);
}

BOOL AddControls(
    HWND hwnd
    )
{
	HDC hdc;
	SIZE sTemp;
	LPTSTR tszMaxNum = TEXT("999");
	int ixOff, iyOff, iHeight, iMinesWidth, iTimeWidth, iNumWidth, ixTimeOff;
	
	// do some calculations for text
	if (!(hdc = GetDC(hwnd))) 
    {
		return FALSE;
	}

	// get the width of the "Mines:" string
	if (!GetTextExtentPoint32(hdc, UseString(IDS_WINMINE_MINES), 
		_tcslen(UseString(IDS_WINMINE_MINES)), &sTemp))
    {
		ReleaseDC(hwnd, hdc);
		return FALSE;
	}
	iMinesWidth = sTemp.cx;

	// get the width of the "Time:" string
	if (!GetTextExtentPoint32(hdc, UseString(IDS_WINMINE_TIME), 
		_tcslen(UseString(IDS_WINMINE_TIME)), &sTemp))
    {
		ReleaseDC(hwnd, hdc);
		return FALSE;
	}
	iTimeWidth = sTemp.cx;

	// get the width of the maximum number string (999)
	// hack: add 1 because some numbers are getting truncated...
	if (!GetTextExtentPoint32(hdc, tszMaxNum, _tcslen(tszMaxNum), &sTemp))
    {
		ReleaseDC(hwnd, hdc);
		return FALSE;
	}
	iNumWidth = sTemp.cx + 1;

	ReleaseDC(hwnd, hdc);

	// height is just the LABEL_HEIGHT minus a pixel overlap for the selection
	// rectangle and a 1 pixel boundary
	iHeight = LABEL_HEIGHT - 2;

	// yOffset is LABEL_HEIGHT minus a pixel overlap for the selection
	// rectangle and a 1 pixel boundary
	iyOff = g_iWindowHeight - LABEL_HEIGHT + 2;

	// xOffset is the leftmost point of the largest board
	ixOff = (g_iWindowWidth - (IMAGE_SIZE * MAX_BOARDSIZE)) / 2;

	// ixTimeOff is the rightmost point of the largest board, minus
	// (iTimeWidth + iNumWidth)
	ixTimeOff = (g_iWindowWidth - (ixOff)) - (iTimeWidth + iNumWidth);

	// Create the "Mines" label
	if (NULL == CreateWindow(TEXT("STATIC"), UseString(IDS_WINMINE_MINES), 
        WS_CHILD | WS_VISIBLE | SS_LEFT, ixOff, iyOff, iMinesWidth, iHeight,
        hwnd, (HMENU) IDC_STATIC, g_hInst, NULL)) 
    {
		return FALSE;	
	};

	// Create the label for the mine count
	g_hwndMines = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 
        ixOff + iMinesWidth, iyOff, iNumWidth, iHeight, hwnd, (HMENU)IDC_STATIC, 
        g_hInst, NULL);

	if (NULL == g_hwndMines)
    {
		return FALSE;
	}
	
	// Create the "Time:" label
	if (!CreateWindow(TEXT("STATIC"), UseString(IDS_WINMINE_TIME), WS_CHILD | WS_VISIBLE | SS_LEFT,
        ixTimeOff, iyOff, iTimeWidth, iHeight, hwnd, (HMENU) IDC_STATIC, g_hInst, NULL)) 
    {
		return FALSE;	
	};

	// Create the label for the timer
	g_hwndTimer = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 
        ixTimeOff + iTimeWidth, iyOff, iNumWidth, iHeight, hwnd,  (HMENU) IDC_STATIC, 
        g_hInst, NULL);

	if (NULL == g_hwndTimer) 
    {
		return FALSE;
	}

	return TRUE;
}

BOOL GetHandles(
    HWND hwnd
    )
{
	HDC hdc;

	// get a handle on the bitmap
    g_hbmpBlocks = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDR_WINMINE_BLOCKS));
	if (NULL == g_hbmpBlocks)
    {
		return FALSE;
	}

	// get a compatible HDC
    hdc = GetDC(hwnd);
	if (NULL == hdc) 
    {
		return FALSE;
	}
	g_hdcImage = CreateCompatibleDC(hdc);
	ReleaseDC(hwnd, hdc);
	if (NULL == g_hdcImage) 
    {
		return FALSE;
	}

	// create the pens
	g_hpenBorder = MyCreatePen(PS_SOLID, 1, COLOR_BORDER);
	g_hpenSelection = MyCreatePen(PS_SOLID, 2, COLOR_SELECTION);
	if ((NULL == g_hpenBorder) || (NULL == g_hpenSelection)) 
    {
		return FALSE;
	}

	return TRUE;
}