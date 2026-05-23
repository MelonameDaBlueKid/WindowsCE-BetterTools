// ***************************************************************************
// GRAPHICS.H
//
// Contains various definitions and declarations for the Minesweeper UI
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#pragma once

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

// which bitmap set?
#define USE_BW				0

// pen colors
#define COLOR_BORDER		0x00FFFFFF
#define COLOR_SELECTION		0x00000000

// image definitions and macros
#define NUM_IMAGES			15
#define IMAGE_SIZE			13	// (pixels)
#define IMAGE_COVERED		15
#define IMAGE_MARKED		14
#define IMAGE_QUESTION		13
#define IMAGE_REDBOMD		12
#define IMAGE_WRONGBOMB		11
#define IMAGE_BOMB			10
#define IMAGE_BLANK			0
#define IMGY(y)				((NUM_IMAGES-y) * IMAGE_SIZE)
#define SCREENX(x, off)		((x * IMAGE_SIZE) + off)
#define SCREENY(y, off)		((y * IMAGE_SIZE) + off)

// height reserved for status labels
#define LABEL_HEIGHT		20

void DrawBoard(HDC hdc);
void DrawRectangle(HDC hdc, HPEN hPen, LPRECT rc);
void DrawScreen();
BOOL AddControls(HWND hwnd);
BOOL GetHandles(HWND hwnd);
HPEN MyCreatePen(UINT uiStyle, UINT uiWidth, COLORREF crColor);

#endif