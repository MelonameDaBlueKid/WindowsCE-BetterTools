// TrackMouse.cpp : Defines the entry point for the application.
//
/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

****************************************************************************/
//

#include "stdafx.h"

//Menu Bar Height
#define MENU_HEIGHT 26

//Global variables
BOOL	bLBDown;
HWND    g_hWndMain;
HWND    g_hWndClear;
HINSTANCE g_hInst;

static TCHAR szAppName[] = TEXT("TrackMouse Application");
static TCHAR szTitle[]   = TEXT("TrackMouse");
static TCHAR szButton[]   = TEXT("Buttons");
static TCHAR szClear[]   = TEXT("Double tap to EXIT");

static TCHAR szOut[40];

static POINT drawlineX[2] = {0,0,0,294};
static POINT drawlineY[2] = {0,0,240,0};

static RECT g_MainRect;

//-----------------------------------------
//     Local Functions
//-----------------------------------------
//Draws a little x target at x,y position
void DrawTarget(HDC hdc, int x, int y)
{
	POINT line[2];

	line[0].x = x;
	line[0].y = y - 15;
	line[1].x = x;
	line[1].y = y + 15;

	Polyline(hdc, line, 2);

	line[0].x = x - 15;
	line[0].y = y;
	line[1].x = x + 15;
	line[1].y = y;

	Polyline(hdc, line, 2);

}

//Draws Four Targets and the Text for resolution
void DrawTextAndTarget(HDC hdc)
{

	ExtTextOut(hdc, g_MainRect.right/2 - 40, g_MainRect.bottom/2 - 20, 0, NULL, szOut, _tcslen(szOut),NULL);
	ExtTextOut(hdc, g_MainRect.right/2 - 50, g_MainRect.bottom/2, 0, NULL, szClear, _tcslen(szClear),NULL);
	DrawTarget(hdc, 50, 50);
	DrawTarget(hdc, 50, 200);
	DrawTarget(hdc, 200, 50);
	DrawTarget(hdc, 200, 200);

}

//-----------------------------------------
//     WndProc()  Main window procedure
//-----------------------------------------

LRESULT CALLBACK WndProc ( HWND hWnd, UINT message, WPARAM uParam, LPARAM lParam )
{
  static HDC   hdc;
  static POINT line[2];
	static POINT oldline;

  RECT rect;

  switch (message) {
    case WM_CREATE :
			GetClientRect(hWnd, &g_MainRect);
			drawlineX[1].y = g_MainRect.bottom;
			drawlineY[1].x = g_MainRect.right;
			break;

    case WM_PAINT :
    {
			//Paint Main window, inking on main window not saved, window is repainted
			//blank
			PAINTSTRUCT ps;
			hdc = BeginPaint (hWnd, &ps);
			GetClientRect(hWnd, &rect);
			FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawTextAndTarget(hdc);
			EndPaint (hWnd, &ps);
			break;
    }

    case WM_LBUTTONDOWN :
		  //Draw CrossHairs

			bLBDown = TRUE;

			line[1].x = LOWORD(lParam);
			line[1].y = HIWORD(lParam);
			hdc = GetDC(hWnd);

			if((line[0].x != line[1].x) || (line[0].y != line[1].y))
			{  
				SelectObject (hdc, GetStockObject (WHITE_PEN)) ;

				Polyline(hdc, drawlineX, 2);
				Polyline(hdc, drawlineY, 2);

				drawlineX[0].x = drawlineX[1].x = line[1].x;
				drawlineY[0].y = drawlineY[1].y = line[1].y;

				SelectObject (hdc, GetStockObject (BLACK_PEN)) ;

				Polyline(hdc, drawlineX, 2);
				Polyline(hdc, drawlineY, 2);
				//reset value of initial point to end point

				wsprintf(szOut,TEXT("X=%03d,Y=%03d"),line[1].x,line[1].y);

				DrawTextAndTarget(hdc);

				line[0] = line[1];
			}

			ReleaseDC(hWnd, hdc);
      break;

    case WM_LBUTTONUP :
			//Erase last line. 

			bLBDown = FALSE;
			line[1].x = LOWORD(lParam);
			line[1].y = HIWORD(lParam);

			break;

    case WM_LBUTTONDBLCLK :
			SendMessage(g_hWndMain, WM_CLOSE,0,0);
			break;

    case WM_MOUSEMOVE :
			//If left mouse button is down save new mouse coordinates in Line[1] point.
			//If point line[1] doesn't equal point line[0], then call erase old crosshairs 
			//and draw new crosshairs

			if ( bLBDown == TRUE )
			{
				hdc = GetDC(hWnd);

				line[1].x = LOWORD(lParam);
				line[1].y = HIWORD(lParam);

				if((line[0].x != line[1].x) || (line[0].y != line[1].y))
				{  

					SelectObject (hdc, GetStockObject (WHITE_PEN)) ;

					Polyline(hdc, drawlineX, 2);
					Polyline(hdc, drawlineY, 2);

					drawlineX[0].x = drawlineX[1].x = line[1].x;
					drawlineY[0].y = drawlineY[1].y = line[1].y;

					SelectObject (hdc, GetStockObject (BLACK_PEN)) ;

					Polyline(hdc, drawlineX, 2);
					Polyline(hdc, drawlineY, 2);
					//reset value of initial point to end point

					wsprintf(szOut,TEXT("X=%03d,Y=%03d"),line[1].x,line[1].y);

					DrawTextAndTarget(hdc);

					line[0] = line[1];
				}

			ReleaseDC(hWnd, hdc);
			}  //end if LButtonDown
      break;


    case WM_KILLFOCUS:
			//If Focus is lost then set Left button down to false so that drawing
			//is enabled until next right button down message is received

			bLBDown = FALSE;
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break; //WM_CLOSE

		case WM_DESTROY :
			PostQuitMessage (0) ;
			return 0 ;

		default :
			return DefWindowProc(hWnd, message, uParam, lParam);

    }
    return 0;
}



//-------------------------------
//     WinMain()
//-------------------------------
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPTSTR pszCommandLine, int nCommandShow)
{
		WNDCLASSW wc;
		MSG msg;
		HWND hPalmMouseRes;
		g_hInst = hInstance;

		//Check to see if app is running 

		hPalmMouseRes = FindWindow(szAppName, szTitle);	
		if (hPalmMouseRes) 
		{
			SetForegroundWindow (hPalmMouseRes);    
			return 0;
		}
	
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = szAppName;

    if ( RegisterClass(&wc) == FALSE )
		{
        OutputDebugString(TEXT("RegisterClass 1 Failed\n"));
        return(FALSE);
    }

		 g_hWndMain = CreateWindow(szAppName, 
								szTitle, 
								WS_VISIBLE ,
								CW_USEDEFAULT, 
								CW_USEDEFAULT,
								CW_USEDEFAULT ,
								CW_USEDEFAULT, 
								NULL, 
								NULL,
								hInstance, 
								NULL);

		UpdateWindow(g_hWndMain);
		ShowWindow(g_hWndMain, nCommandShow);

    while ( GetMessage( &msg, NULL, 0,0 ) )
		{
			TranslateMessage (&msg);
			DispatchMessage(&msg);
		}

		return (msg.wParam);
}


