/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright  1994-1997  Microsoft Corporation.  All Rights Reserved.


Module Name:

    generic.cpp

Abstract:

    This file contains the source to a generic application, which
    will be used to illustrate part of the functionality of WIN32_WCE. The
    application creates a window and draws a horizontal and vertical line.
    Each line bisect the client area creating four equal quadrants. WndProc
    processes the mouseclicks depending of which quadrant the mouse was in
    when it was clicked.

    TopLeft quadrant     : Exits application.
    TopRight quadrant    : Cycles through the color palette.
    BottomLeft quadrant  : Changes Z order of window.
    BottomRight quadrant : Draws square the size of 1/6 the window width with
                           the lower left corner at the point of mouseclick.

    
Functions:

    BeginPaint
    CreateWindow
    DefWindowProc
    DestroyWindow
    DispatchMessage
    DrawText
    EndPaint
    FillRect
    GetDC
    GetMessage
    GetStockObject
    GetStockPen                     // macro defined in windowsx.h
    GetSystemMetrics
    GetWindowRect
    POINTSTOPOINT
    Polyline
    PostQuitMessage
    RegisterClass
    ReleaseCapture
    ReleaseDC
    SelectPen                       // macro defined in windowsx.h
    SetCapture
    SetFocus
    SetWindowPos
    ShowWindow
    TranslateMessage
    UpdateWindow
    WinMain
    WndProc

  Messages:

    WM_DESTROY
    WM_LBUTTONDOWN
    WM_PAINT

--****************************************************************************/

#include <windows.h>
#include <windowsx.h>

// Size and maximum number of squares in lower right quadrant
#define SQUARE_SIZE (CLIENT_WIDTH / 6)
#define MAX_SQUARES 20

POINT LowerRight[MAX_SQUARES];
WORD NumberOfSquares = 0;

WCHAR szAppName[8];
WCHAR szTitle[8];
int CLIENT_WIDTH;
int CLIENT_HEIGHT;

// Palette array to cycle through when the upper right quadrant is tapped
int rgiBrushColors[4] = {BLACK_BRUSH, DKGRAY_BRUSH, LTGRAY_BRUSH, WHITE_BRUSH};
int iPaletteIterator = 3;                           //Start with the white brush.
int iBrushColor = rgiBrushColors[iPaletteIterator];
BOOL bChangeColor = FALSE;

BOOL MouseDown = FALSE;

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
    int iXMiddle =  CLIENT_WIDTH / 2;
    int iYMiddle =  CLIENT_HEIGHT / 2;

    if (bChangeColor)               // Change colors if the upper right quadrant was selected.
    {       
        iPaletteIterator = (iPaletteIterator+1)%4;
        iBrushColor = rgiBrushColors[iPaletteIterator];
        bChangeColor = FALSE;
    }

    hBrush = (HBRUSH)GetStockObject(iBrushColor);   // Set the color of the brush and pen.
    iPencolor = (iPaletteIterator < 2) ? WHITE_PEN : BLACK_PEN;
    SelectPen(hdc, GetStockPen(iPencolor));

    rect.left = 0;                  // Fill the screen with the background color.
    rect.top = 0;
    rect.right = CLIENT_WIDTH;
    rect.bottom = CLIENT_HEIGHT;
    FillRect(hdc, &rect, hBrush);
    
    line[0].x = iXMiddle;           // Paint a vertical line that bisects window
    line[0].y = 0;                  // with Polyline.
    line[1].x = iXMiddle;
    line[1].y = CLIENT_HEIGHT;
    Polyline(hdc, line, 2);

    line[0].x = 0;
    line[0].y = iYMiddle;           // Paint a horizontal line that bisects window
    line[1].x = CLIENT_WIDTH - 1;   // with Polyline.
    line[1].y = iYMiddle;
    Polyline(hdc, line, 2);

    // Draw descriptive text in each quadrant.
    rect.left = 1;
    rect.top = 1;
    rect.right = iXMiddle;
    rect.bottom = iYMiddle;
    DrawText(hdc, L"Tap here to close.", -1, &rect, DT_TOP | DT_LEFT);

    rect.left = 1;
    rect.top = iYMiddle+1;
    rect.right = iXMiddle;
    rect.bottom = CLIENT_HEIGHT;
    DrawText(hdc, L"Tap here to send to the back of the Z-order.", -1, &rect, DT_TOP | DT_LEFT | DT_WORDBREAK);


    rect.left = iXMiddle+1;
    rect.top = iYMiddle+1;
    rect.right = CLIENT_WIDTH;
    rect.bottom = CLIENT_HEIGHT;
    DrawText(hdc, L"Tap here to draw a square.", -1, &rect, DT_TOP | DT_LEFT | DT_WORDBREAK);

    rect.left = iXMiddle+1;
    rect.top = 1;
    rect.right = CLIENT_WIDTH;
    rect.bottom = iYMiddle;
    DrawText(hdc, L"Tap here to change colors.", -1, &rect, DT_TOP | DT_LEFT | DT_WORDBREAK);

    // Output the current color in the palette.
    switch (iBrushColor) 
    {
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

    // Paint squares, with the right bottom corner positioned at the point captured
    // by POINTSTOPOINT, if the user has tapped the screen in the lower right quadrant.
    for (index = 0; index < NumberOfSquares; index++) 
    {
        line[0].x = line[3].x = line[4].x = LowerRight[index].x;
        line[0].y = line[1].y = line[4].y = LowerRight[index].y;
        line[1].x = line[2].x = LowerRight[index].x - SQUARE_SIZE;
        line[2].y = line[3].y = LowerRight[index].y - SQUARE_SIZE;
        Polyline(hdc, line, 5);
    }
}

/**************************************************************************

  WndProc(  HWND hWnd, UINT message,WPARAM uParam,LPARAM lParam)

  *************************************************************************/

LRESULT CALLBACK WndProc (  HWND hWnd,
                            UINT message,
                            WPARAM uParam,
                            LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT   Pos;

    switch (message) 
    {

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            PaintWindow(hdc);
            EndPaint(hWnd, &ps);
            break;

        case WM_LBUTTONDOWN:

            POINTSTOPOINT(Pos, lParam);

            if (Pos.x < (CLIENT_WIDTH / 2)) 
            {
                if (Pos.y < (CLIENT_HEIGHT / 2)) 
                {   // Left upper quadrant: Destroy the window.
                    DestroyWindow (hWnd);
                }
                else 
                {   // Left lower quadrant: Move the window to the bottom of the Z-order.
                    SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, 0, 0,
                                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                }
            }
            else 
            {
                if (Pos.y < (CLIENT_HEIGHT / 2)) 
                {   // Right upper quadrant: Change the display colors.
                    bChangeColor = TRUE;
                    hdc = GetDC(hWnd);
                    PaintWindow(hdc);
                    ReleaseDC(hWnd, hdc);
                    return(0);
                }
                else 
                {  // Right lower quadrant: Set the point in the LowerRight array
                        // to the coordinates at which the user tapped the screen. The
                        // PaintWindow function will draw a square there.
                   if (NumberOfSquares < MAX_SQUARES) 
                   {
                        LowerRight[NumberOfSquares].x = Pos.x;
                        LowerRight[NumberOfSquares].y = Pos.y;
                        NumberOfSquares++;
                        hdc = GetDC(hWnd);
                        PaintWindow(hdc);
                        ReleaseDC(hWnd, hdc);
                   }
                   else
                   {
                        MessageBox(hWnd, TEXT("The maximum number of squares has been reached."), TEXT("Generic"), MB_OK);
                   }

                }   
            }
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
    RECT rc;                    // Called in GetClientRect()

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

    return(TRUE);                  // Window handle hWnd is valid.
}
/***************************************************************************

        int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                             LPWSTR lpCmdLine ,UINT nCmdShow)

  **************************************************************************/

int WINAPI WinMain (HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPWSTR lpCmdLine,
                     int nCmdShow)
{
    MSG msg;

    //Load the application name and widnow title strings.
    LoadString(hInstance,1,szAppName,
               sizeof(szAppName)/sizeof(TCHAR));
    LoadString(hInstance, 2,szTitle,
               sizeof(szTitle)/sizeof(TCHAR));

    if (hPrevInstance == 0) 
    {
        if (InitApplication(hInstance) == FALSE)
            return(FALSE);
    }

    if (InitInstance(hInstance, nCmdShow) == FALSE)
        return(FALSE);

    while (GetMessage(&msg, NULL, 0, 0) == TRUE) 
    {
        DispatchMessage(&msg);
    }

    return(msg.wParam);
}

// END GENERIC.CPP
