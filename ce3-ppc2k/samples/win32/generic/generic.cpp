/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright  1994-1997  Microsoft Corporation.  All Rights Reserved.


Module Name:

    generic.cpp

Abstract:

    This file contains the source code of the "generic" application, which
    will be used to illustrate part of the functionality of Pocket PC. The
	application creates a window and draws a horizontal line to create two 
	equal quadrants. WndProc processes the mouseclicks depending of which 
	quadrant the mouse was in when it was clicked.

	This example resembles to the Generic example of the WIN32_WCE. Instead 
	of four quadrants, this example only has two quadrant because of the 
	following Pocket PC applications properties:
	
	  1) There shouldn't be an exit functionality for Pocket PC applications.
	  2) All the application windows should not be minimized.

	Top quadrant    : Cycles through the color palette.
	Bottom quadrant : Draws square the size of 1/6 the window width with
	                  the lower corner at the point of mouseclick.

--****************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include "resource.h"

// Size and maximum number of squares in lower quadrant
#define SQUARE_SIZE (CLIENT_WIDTH / 6)
#define MAX_SQUARES 20

POINT LowerRight[MAX_SQUARES];
WORD NumberOfSquares = 0;

WCHAR szAppName[8];
WCHAR szTitle[8];
int CLIENT_WIDTH;
int CLIENT_HEIGHT;

// Palette array to cycle through when the upper quadrant is tapped
int rgiBrushColors[4] = {BLACK_BRUSH, DKGRAY_BRUSH, LTGRAY_BRUSH, WHITE_BRUSH};
int iPaletteIterator = 3;							//Start with the white brush.
int iBrushColor = rgiBrushColors[iPaletteIterator];
BOOL bChangeColor = FALSE;

BOOL MouseDown = FALSE;
HWND hwndMain = NULL;
/***************************************************************************

  PaintWindow (HDC hdc)

  **************************************************************************/

void PaintWindow (HDC hdc)
{
    POINT line[5];
    WORD index;
	HBRUSH hBrush;
	RECT rect;
	int iPencolor;
	int iYMiddle =  CLIENT_HEIGHT / 2;

    if (bChangeColor)				// Change colors if the upper quadrant was selected.
	{		
		iPaletteIterator = (iPaletteIterator+1)%4;
		iBrushColor = rgiBrushColors[iPaletteIterator];
		bChangeColor = FALSE;
	}

	hBrush = (HBRUSH)GetStockObject(iBrushColor);	// Set the color of the brush and pen.
	iPencolor = (iPaletteIterator < 2) ? WHITE_PEN : BLACK_PEN;
	SelectPen(hdc, GetStockPen(iPencolor));

	rect.left = 0;					// Fill the screen with the background color.
	rect.top = 0;
	rect.right = CLIENT_WIDTH;
	rect.bottom = CLIENT_HEIGHT;
	FillRect(hdc, &rect, hBrush);
	
     line[0].x = 0;
     line[0].y = iYMiddle;			// Paint a horizontal line that bisects window
     line[1].x = CLIENT_WIDTH - 1;	// with Polyline.
     line[1].y = iYMiddle;
     Polyline(hdc, line, 2);

	rect.left = 1;
	rect.top = iYMiddle+1;
	rect.right = CLIENT_WIDTH;
	rect.bottom = CLIENT_HEIGHT;
	DrawText(hdc, L"Tap here to draw a square.", -1, &rect, DT_TOP | DT_LEFT);

	rect.left = 1;
	rect.top = 1;
	rect.right = CLIENT_WIDTH;
	rect.bottom = iYMiddle;
	DrawText(hdc, L"Tap here to change colors.", -1, &rect, DT_TOP | DT_LEFT);

	// Output the current color in the palette.
	switch (iBrushColor) {
	case WHITE_BRUSH:
		DrawText(hdc, L"White", -1, &rect, DT_CENTER | DT_VCENTER);
		break;
	case LTGRAY_BRUSH:
		DrawText(hdc, L"Light Gray", -1, &rect, DT_CENTER | DT_VCENTER);
		break;
	case DKGRAY_BRUSH:
		DrawText(hdc, L"Dark Gray", -1, &rect, DT_CENTER | DT_VCENTER);
		break;
	case BLACK_BRUSH:
		DrawText(hdc, L"Black", -1, &rect, DT_CENTER | DT_VCENTER);
		break;
	default:
		DrawText(hdc, L"Don't know", -1, &rect, DT_CENTER | DT_VCENTER);
	}

    // Paint squares, with the bottom corner positioned at the point captured
	// by POINTSTOPOINT, if the user has tapped the screen in the lower quadrant.
    for (index = 0; index < NumberOfSquares; index++) {
		line[0].x = line[3].x = line[4].x = LowerRight[index].x;
		line[0].y = line[1].y = line[4].y = LowerRight[index].y;
		line[1].x = line[2].x = LowerRight[index].x - SQUARE_SIZE;
		line[2].y = line[3].y = LowerRight[index].y - SQUARE_SIZE;
		Polyline(hdc, line, 5);
    }
}

/**************************************************************************

  WndProc(	HWND hWnd, UINT message,WPARAM uParam,LPARAM lParam)

  *************************************************************************/

LRESULT CALLBACK WndProc (	HWND hWnd,
							UINT message,
							WPARAM uParam,
							LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT   Pos;

    switch (message) {
	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(uParam,lParam))
		{
		case IDOK:
			SendMessage(hWnd,WM_CLOSE,0,0);
			break;
		default:
			return DefWindowProc(hWnd, message, uParam, lParam);
		}
		break;
	case WM_PAINT:
	    hdc = BeginPaint(hWnd, &ps);
	    PaintWindow(hdc);
	    EndPaint(hWnd, &ps);
	    break;

	case WM_LBUTTONDOWN:

	    POINTSTOPOINT(Pos, lParam);
	
	    if (Pos.y < (CLIENT_HEIGHT / 2)) {	// Upper quadrant: Change the display colors.
			bChangeColor = TRUE;
			hdc = GetDC(hWnd);
			PaintWindow(hdc);
			ReleaseDC(hWnd, hdc);
			return(0);
		}
		else {	// Lower quadrant: Set the point in the Lower array
				// to the coordinates at which the user tapped the screen. The
				// PaintWindow function will draw a square there.
			if (NumberOfSquares < MAX_SQUARES) {
	    			LowerRight[NumberOfSquares].x = Pos.x;
				LowerRight[NumberOfSquares].y = Pos.y;
				NumberOfSquares++;
				hdc = GetDC(hWnd);
				PaintWindow(hdc);
				ReleaseDC(hWnd, hdc);
			}
			else
				MessageBox(hWnd, L"Reached the maximum number of squares allowed!", L"Warning", MB_OK);
		}
	    break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
	break;

	default:
	    return (DefWindowProc(hWnd, message, uParam, lParam));
    }

    return (0);
}
/***************************************************************************

		BOOL InitApplication (HINSTANCE hInstance)

****************************************************************************/
BOOL InitApplication (HINSTANCE hInstance)
{
    WNDCLASSW wc;

    wc.style = 0 ;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;

    BOOL f = (RegisterClass(&wc));
    return f;
}
/*************************************************************************************

		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)

  ************************************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	RECT rc;					// Called in GetClientRect()

                               	// Use the default window settings.
	 hWnd = CreateWindow(szAppName,szTitle,WS_VISIBLE,
	                     0,0,CW_USEDEFAULT,CW_USEDEFAULT,
	                     NULL, NULL, hInstance, NULL);


     if (hWnd == 0)    // Check whether values returned by CreateWindow() are valid.
		return (FALSE);
	 if (IsWindow(hWnd) != TRUE)
	    return (FALSE);

    // Get the client area size, which is used to paint bisecting lines,
    // and determine the quadrant in which the user tapped the screen.
    GetClientRect(hWnd, &rc);
    CLIENT_WIDTH = rc.right;
    CLIENT_HEIGHT = rc.bottom;
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

	hwndMain=hWnd;

    return(TRUE);                  // Window handle hWnd is valid.
}
/***************************************************************************

		int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
						   	 LPWSTR lpCmdLine ,UINT nCmdShow)

  **************************************************************************/

int WINAPI WinMain (HINSTANCE hInstance,
		             HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine,
                     int nCmdShow)
{
    MSG msg;
	HWND hGenWnd = NULL;
	HACCEL hAccel = NULL;

	//Load the application name and widnow title strings.
	LoadString(hInstance,1,szAppName,
		       sizeof(szAppName)/sizeof(TCHAR));
	LoadString(hInstance, 2,szTitle,
		       sizeof(szTitle)/sizeof(TCHAR));

	//Check if Generic.exe is running. If it's running then focus on the window
	hGenWnd = FindWindow(szAppName, szTitle);	
	if (hGenWnd) 
	{
		SetForegroundWindow (hGenWnd);    
		return 0;
	}

    if (hPrevInstance == 0) {
		if (InitApplication(hInstance) == FALSE)
			return(FALSE);
    }

    if (InitInstance(hInstance, nCmdShow) == FALSE)
		return(FALSE);

	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

    while (GetMessage(&msg, NULL, 0, 0) == TRUE) 
	{
		if (!TranslateAccelerator(hwndMain,hAccel, &msg)) 
		{
			TranslateMessage (&msg);
			DispatchMessage(&msg);
		}
    }

    return(msg.wParam);
}

// END GENERIC.CPP
