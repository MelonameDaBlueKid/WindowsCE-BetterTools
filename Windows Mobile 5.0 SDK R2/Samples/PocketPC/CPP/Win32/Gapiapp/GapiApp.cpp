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
//
// GXSample.cpp : Pocket PC Game API Starfield sample.
//
// Mostly C in a C++ file.
// See the documentation for more information.


//
// Includes
//

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <wingdi.h>
#include <gx.h>
#include <winuserm.h>
#include <aygshell.h>
#include "bitmaps.h"

// Defines
//
// Some handy globals that are fine for a sample app.
//

GXDisplayProperties g_gxdp;		// GX struct
GXKeyList g_gxkl;				// GX struct
BOOL g_fPause = FALSE;			// paused or not
BOOL g_bFullScreen = TRUE;
BYTE *g_pMainBuffer = NULL;
HINSTANCE g_hInstance = 0;
HDC hdc;
HWND hWnd, hWndFullScreenButton, hWndDescriptionText;

DWORD g_dwLastMouseClick = 0;

const int gcBitsPerByte = 8;

#define		COLOR_WHITE 0xFFFF

#define		COLOR_RED_2BPP   0x3
#define		COLOR_GREEN_2BPP 0x2
#define		COLOR_BLUE_2BPP  0x1

#define		COLOR_RED_4BPP   0xF
#define		COLOR_GREEN_4BPP 0xA
#define		COLOR_BLUE_4BPP  0x5

#define		COLOR_RED_PALETTE   249
#define		COLOR_GREEN_PALETTE 250
#define		COLOR_BLUE_PALETTE  252

#define		COLOR_RED_444   0x0F00
#define		COLOR_GREEN_444 0x00F0
#define		COLOR_BLUE_444  0x000F

#define		COLOR_RED_555	0x7C00
#define		COLOR_GREEN_555 0x03E0
#define		COLOR_BLUE_555  0x001F

#define		COLOR_RED_565	0xF800
#define		COLOR_GREEN_565 0x07E0
#define		COLOR_BLUE_565  0x001F

#define		COLOR_RED_888	0x00FF0000
#define		COLOR_GREEN_888 0x0000FF00
#define		COLOR_BLUE_888  0x000000FF

#define		COLOR_SQUARES_TOP		80
#define		COLOR_SQUARES_BOTTOM	240
#define		COLOR_SQUARES_LEFT		40
#define		COLOR_SQUARES_RIGHT		200

#define		EXIT_TOP				0
#define		EXIT_BOTTOM				60
#define		EXIT_LEFT				0
#define		EXIT_RIGHT				60

#define		SWITCH_TASK_TOP			0
#define		SWITCH_TASK_BOTTOM		60
#define		SWITCH_TASK_LEFT		180
#define		SWITCH_TASK_RIGHT		240

#define		REBOUND_DELAY			500


BOOL g_bOrientation = PORTRAIT;


long	g_wKeyLoc[MAX_BUTTONS][2][MAX_ORIENTATION];		// ex : [UP][X][PORTRAIT]
BOOL	g_bKeyInverted[MAX_BUTTONS];

//
// Forward declarations.
//

ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL ClearScreen();
void DrawRect();
void FillLocations(BOOL);
void DrawButtons(BOOL);
void DrawBitmap(DWORD *, WORD, WORD, long, long, BOOL);
void ChangeDisplayMode(BOOL);

//
// Code Body
//

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow
	)
{
	MSG msg;

	// Perform application initialization:

	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	// Main message loop.

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//

ATOM MyRegisterClass(
	HINSTANCE hInstance, 
	LPTSTR szWindowClass
	)
{
	WNDCLASS	wc;

    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= NULL;
    wc.hCursor			= 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;

	return RegisterClass(&wc);
}

BOOL InitInstance(
	HINSTANCE hInstance, 
	int nCmdShow
	)
{
	TCHAR	szTitle[] = L"GXSample";			// The title bar text
	TCHAR	szWindowClass[] = L"GXSample";	// The window class name
	BOOL    bDRAMBuffer;
    INT iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	INT iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// IMPORTANT:  see if this app is already running.  If so just bring
	// it to the front and quit.  All CE apps need to do this.

	g_hInstance = hInstance;

	hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd)
	{
		SetForegroundWindow ((HWND) (((DWORD)hWnd) | 0x01));    
		return 0;
	} 

	MyRegisterClass(hInstance, szWindowClass);

	// In order to create a full screen app CreateWindow() needs to be
	// called with absolute coordinates that cover the entire display.
	// Using CW_USEDEFAULT will not work correctly.

	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 
		NULL, NULL, hInstance, NULL);

	if (!hWnd) 
	{	
		return FALSE;
	}


	if (GXOpenDisplay(hWnd, GX_FULLSCREEN) == 0) {
		return FALSE;				// we won't be able to draw.
	}

	bDRAMBuffer = GXIsDisplayDRAMBuffer();
	if (TRUE == bDRAMBuffer)
	{
		g_bFullScreen = FALSE;

        // on non-standard devices, this is a clipper
	    GXSetViewport(iScreenHeight/2-55, 50, 0, 0);

		hWndFullScreenButton = CreateWindow( _T("BUTTON"), _T("Full screen"),
			BS_CENTER | BS_PUSHBUTTON | WS_VISIBLE, iScreenWidth/2-50,
			iScreenHeight-40, 100, 30, hWnd, NULL, hInstance, NULL);


		hWndDescriptionText =  CreateWindow( _T("STATIC"), 
			_T("DRAM drawing device"), SS_LEFT | WS_VISIBLE, iScreenWidth/2-65,
			iScreenHeight-70, 200, 30, hWnd, NULL, hInstance, NULL);

	}

	GXOpenInput();

	g_gxdp = GXGetDisplayProperties();

	g_gxkl = GXGetDefaultKeys(GX_NORMALKEYS);
	FillLocations(PORTRAIT);

	g_gxkl = GXGetDefaultKeys(GX_LANDSCAPEKEYS);
	FillLocations(LANDSCAPE);

	g_gxkl = GXGetDefaultKeys(GX_NORMALKEYS);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//

LRESULT CALLBACK WndProc(
	HWND hWnd, 
	UINT message, 
	WPARAM wParam, 
	LPARAM lParam
	)
{
	PAINTSTRUCT ps;
	short vkKey;

	switch (message) {
		case WM_COMMAND:
        {
			if ((HWND)lParam == hWndFullScreenButton)
			{
				g_bFullScreen = TRUE;
				GXSetViewport(0, GetSystemMetrics(SM_CYSCREEN), 0, 0);
				ShowWindow(hWndFullScreenButton, SW_HIDE);
				ShowWindow(hWndDescriptionText, SW_HIDE);
				PostMessage(hWnd, WM_PAINT, 0, 0);
			}
		}
		break;

		case WM_CREATE:
			break;


		case WM_ACTIVATE:
		{
			//BOOL bActivating = LOWORD(wParam) != WA_INACTIVE;

			if (WA_INACTIVE == LOWORD(wParam))
			{
				// Always, always call GXSuspend() here.
				GXSuspend();
			}
			else
			{
				// And always call GXResume() here.
				GXResume();
				PostMessage(hWnd, WM_PAINT, 0, 0);
			}

			break;
		}

		case WM_KILLFOCUS:

			break;


		case WM_SETFOCUS:

			break;

		// If your app can only draw directly to the screen then you need to make
		// sure it is frontmost before drawing.

		case WM_PAINT:

			if (GetForegroundWindow() == hWnd) {
				hdc = BeginPaint(hWnd, &ps);
                g_pMainBuffer = (BYTE*)GXBeginDraw();
				if(NULL != g_pMainBuffer) 
				{
					ClearScreen();
					DrawRect();
					DrawButtons(g_bOrientation);
	                GXEndDraw();
				}
				EndPaint(hWnd, &ps);
			}
			break;

		case WM_KEYDOWN:
			vkKey = (short)wParam;

			if (vkKey == g_gxkl.vkUp) 
			{
				if(TRUE != g_bKeyInverted[UP])
				{
					g_bKeyInverted[UP] = TRUE;
					PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}
			else if (vkKey == g_gxkl.vkDown) 
			{
				if(TRUE != g_bKeyInverted[DOWN])
				{
				g_bKeyInverted[DOWN] = TRUE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}
			
			if (vkKey == g_gxkl.vkLeft) {
				if(TRUE != g_bKeyInverted[LEFT])
				{
				g_bKeyInverted[LEFT] = TRUE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}
			
			if (vkKey == g_gxkl.vkRight) {
				if(TRUE != g_bKeyInverted[RIGHT])
				{
				g_bKeyInverted[RIGHT] = TRUE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}
			
			if (vkKey == g_gxkl.vkA) {
				if(TRUE != g_bKeyInverted[A])
				{
				g_bKeyInverted[A] = TRUE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}
			
			if (vkKey == g_gxkl.vkB) {
				if(TRUE != g_bKeyInverted[B])
				{
				g_bKeyInverted[B] = TRUE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}
			
			if (vkKey == g_gxkl.vkC) {
				if(TRUE != g_bKeyInverted[C])
				{
				g_bKeyInverted[C] = TRUE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkStart) {
				if(TRUE != g_bKeyInverted[START])
				{
				g_bKeyInverted[START] = TRUE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

#ifdef WIN32_PLATFORM_WFSP //Smartphone platform define
			if (vkKey == VK_TTALK)
			{
				ChangeDisplayMode(!g_bOrientation);
	            PostMessage(hWnd, WM_PAINT, 0, 0);
				break;
			}
			
			if (vkKey == VK_TEND)
			{
	            PostMessage(hWnd, WM_CLOSE, 0,0);
	            break;
			}
			if (VK_TBACK == vkKey)
			{
				SHNavigateBack();
				break;
			}

			if (VK_THOME == vkKey)
			{
				// Put home in foreground
				HWND hwnd = FindWindow(TEXT("DesktopExplorerWindow"), NULL);
				if((NULL != hwnd) && (TRUE == IsWindow(hwnd)))
				{
					ShowWindow(hwnd, SW_SHOWNA);
					SetForegroundWindow((HWND)(((DWORD)((HWND)hwnd)) | 0x01));					
				}
				break;
			}
#endif //WIN32_PLATFORM_WFSP

			break;

		case WM_KEYUP:
			vkKey = (short)wParam;
			if (vkKey == g_gxkl.vkUp) {
				if(FALSE != g_bKeyInverted[UP])
				{
					g_bKeyInverted[UP] = FALSE;
					PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkDown) {
				if(FALSE != g_bKeyInverted[DOWN])
				{
				g_bKeyInverted[DOWN] = FALSE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkLeft) {
				if(FALSE != g_bKeyInverted[LEFT])
				{

				g_bKeyInverted[LEFT] = FALSE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkRight) {
				if(FALSE != g_bKeyInverted[RIGHT])
				{
				g_bKeyInverted[RIGHT] = FALSE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkA) {
				if(FALSE != g_bKeyInverted[A])
				{
				g_bKeyInverted[A] = FALSE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkB) {
				if(FALSE != g_bKeyInverted[B])
				{
				g_bKeyInverted[B] = FALSE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkC) {
				if(FALSE != g_bKeyInverted[C])
				{
				g_bKeyInverted[C] = FALSE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}

			if (vkKey == g_gxkl.vkStart) {
				if(FALSE != g_bKeyInverted[START])
				{
				g_bKeyInverted[START] = FALSE;
				PostMessage(hWnd, WM_PAINT, 0, 0);
				}
				break;
			}
			break;

		case WM_LBUTTONDOWN:

			break;

		case WM_LBUTTONUP:

			// Turn the timer back on.

			break;

		case WM_MOUSEMOVE:
			if (wParam & MK_LBUTTON)
			{
				WORD xPos = LOWORD(lParam); 
				WORD yPos = HIWORD(lParam);

				if ((xPos >= COLOR_SQUARES_LEFT) && (xPos <= COLOR_SQUARES_RIGHT) &&
					(yPos >= COLOR_SQUARES_TOP)  && (yPos <= COLOR_SQUARES_BOTTOM))
				{
					DWORD l_dwTemp = GetTickCount();
					//Only allow sytlus to rotate every REBOUND_DELAY ms
					if (l_dwTemp - g_dwLastMouseClick > REBOUND_DELAY)
					{
						ChangeDisplayMode(!g_bOrientation);
						PostMessage(hWnd, WM_PAINT, 0, 0);
						g_dwLastMouseClick = l_dwTemp;
					}
				}
				else if ((xPos >= EXIT_LEFT) && (xPos <= EXIT_RIGHT) &&
					(yPos >= EXIT_TOP)  && (yPos <= EXIT_BOTTOM))
				{
					PostMessage(hWnd, WM_CLOSE, 0,0);
				}
				else if ((xPos >= SWITCH_TASK_LEFT) && (xPos <= SWITCH_TASK_RIGHT) &&
					(yPos >= SWITCH_TASK_TOP)  && (yPos <= SWITCH_TASK_BOTTOM))
				{
					MessageBox(NULL, _T("GX OEM Test 1.0"),_T("About"), MB_OK);
				}				
			}
			break;

		case WM_DESTROY:
			GXCloseInput();			
			GXCloseDisplay();
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}



void GameXSetPixel(
	WORD nX, 
	WORD nY, 
	DWORD color
	)
{
	DWORD byteIndex; 

    
	byteIndex = (DWORD)(nY * g_gxdp.cbyPitch) + (nX * g_gxdp.cbxPitch);

    if (g_gxdp.ffFormat & kfDirectInverted)
	{
		color = ~color;
	}

    switch (g_gxdp.cBPP)
    {
    case 1:
		// Mask off the appropriate 1 bits, then or it in from the color.
		g_pMainBuffer[byteIndex] &= ~(0x80 >> ((nX & 0x07)));
		g_pMainBuffer[byteIndex] |= ((color & 0x01) << 8) >> ((nX & 0x07));    
    	break;
    
    case 2:
   		// Mask off the appropriate g_gxdp.cBPP (2) bits, then or it in from the color.
    	g_pMainBuffer[byteIndex] &= ~(0xC0 >> ((nX & 0x03) * g_gxdp.cBPP));
    	g_pMainBuffer[byteIndex] |= ((color & 0x03) << 6) >> ((nX & 0x03) * g_gxdp.cBPP);
    	break;
    
    case 4:
    	// If the nX is even the top g_gxdp.cBPP (4) bits need to be set.
        g_pMainBuffer[byteIndex] &= 0x0F << ((nX & 0x01) * g_gxdp.cBPP);
        g_pMainBuffer[byteIndex] |= (color & 0x0F) << ((!(nX & 0x01)) * g_gxdp.cBPP);
    	break;
        
    case 8:
    	g_pMainBuffer[byteIndex] = (BYTE)color & 0xFF;
    	break;

	case 16:
	   	*(WORD*)(&g_pMainBuffer[byteIndex]) = (WORD)color & 0xFFFF;
		break;
        
	case 32:
    	*(DWORD*)(&g_pMainBuffer[byteIndex]) = color;
		break;        
    }
	
}

//
// 0 clears the screen to black.
// any other value clears the screen to a random value.
//

BOOL ClearScreen()
{
	BYTE color = 0;
    if (g_gxdp.ffFormat & kfDirectInverted)
	{
		color = ~color;
	}
	for (WORD x=0; x<g_gxdp.cxWidth; x++)
        for (WORD y=0; y<g_gxdp.cyHeight; y++)
        {
            GameXSetPixel(x, y, color);
        }
	return FALSE;
}

void DrawRect()
{
	WORD x,y;
    INT iScreenWidth = 0;
    INT iScreenHeight = 0;

	DWORD l_dwRed,l_dwGreen, l_dwBlue;

	if (g_gxdp.ffFormat & kfDirect565)
	{
		l_dwRed = COLOR_RED_565;
		l_dwGreen = COLOR_GREEN_565;
		l_dwBlue = COLOR_BLUE_565;
	}
	else if (g_gxdp.ffFormat & kfDirect555)
	{
		l_dwRed = COLOR_RED_555;
		l_dwGreen = COLOR_GREEN_555;
		l_dwBlue = COLOR_BLUE_555;
	}
	else if (g_gxdp.ffFormat & kfDirect444)
	{
		l_dwRed = COLOR_RED_444;
		l_dwGreen = COLOR_GREEN_444;
		l_dwBlue = COLOR_BLUE_444;
	}
	else if (g_gxdp.ffFormat & kfDirect888)
	{
		l_dwRed = COLOR_RED_888;
		l_dwGreen = COLOR_GREEN_888;
		l_dwBlue = COLOR_BLUE_888;
	}
	else if (g_gxdp.ffFormat & kfPalette)
	{
		l_dwRed = COLOR_RED_PALETTE;
		l_dwGreen = COLOR_GREEN_PALETTE;
		l_dwBlue = COLOR_BLUE_PALETTE;
	}
	else if (g_gxdp.cBPP == 4)
	{
		l_dwRed = COLOR_RED_4BPP;
		l_dwGreen = COLOR_GREEN_4BPP;
		l_dwBlue = COLOR_BLUE_4BPP;
	}
	else if (g_gxdp.cBPP == 2)
	{
		l_dwRed = COLOR_RED_2BPP;
		l_dwGreen = COLOR_GREEN_2BPP;
		l_dwBlue = COLOR_BLUE_2BPP;
	}
	else
	{
		DebugBreak();
	}
	

	iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	
    if (g_bOrientation == PORTRAIT)
    {
        for(x=iScreenWidth/2-70; x<iScreenWidth/2-30;x++)
		{
            for(y=iScreenHeight/2 - 50; y<iScreenHeight/2 - 10; y++)
            {
                GameXSetPixel(x,y,l_dwRed);
            }
		}

        for(x=iScreenWidth/2-20; x<iScreenWidth/2+20;x++)
		{
            for(y=iScreenHeight/2 - 50; y<iScreenHeight/2 - 10; y++)
            {
                GameXSetPixel(x,y,l_dwGreen);
            }
		}

        for(x=iScreenWidth/2+30; x<iScreenWidth/2+70;x++)
		{
            for(y=iScreenHeight/2 - 50; y<iScreenHeight/2 - 10; y++)
            {
                GameXSetPixel(x,y,l_dwBlue);
            }
		}
    }
    else
    {
        for(x=iScreenWidth/2-20; x<iScreenWidth/2+20; x++)
		{
            for(y=iScreenHeight/2 - 10; y<iScreenHeight/2 + 30; y++)
            {
                GameXSetPixel(x,y,l_dwRed);
            }
		}

        for(x=iScreenWidth/2-20; x<iScreenWidth/2+20; x++)
		{
            for(y=iScreenHeight/2 - 60; y<iScreenHeight/2 - 20; y++)
            {
                GameXSetPixel(x,y,l_dwGreen);
            }
		}

        for(x=iScreenWidth/2-20; x<iScreenWidth/2+20; x++)
		{
            for(y=iScreenHeight/2 - 110; y<iScreenHeight/2 - 70; y++)
            {
                GameXSetPixel(x,y,l_dwBlue);
            }
		}
    }

	for(x=0; x<g_gxdp.cxWidth; x++)
	{
		GameXSetPixel(x,0,COLOR_WHITE);
		GameXSetPixel(x,(WORD)g_gxdp.cyHeight-1,COLOR_WHITE);
	}

	for(y=0; y<g_gxdp.cyHeight; y++)
	{
		GameXSetPixel(0,y,COLOR_WHITE);
		GameXSetPixel((WORD)g_gxdp.cxWidth-1, y,COLOR_WHITE);
	}
}

void FillLocations(
	BOOL in_bOrientation 
	)
{
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	if (in_bOrientation == PORTRAIT)
	{
		long l_wXMax = iScreenWidth;
		long l_wXMin = 0;

		long l_wYMax = iScreenHeight;
		long l_wYMin = 0;

		// UP
		if (g_gxkl.ptUp.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptUp.x;
		}

		if (g_gxkl.ptUp.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptUp.x;
		}

		if (g_gxkl.ptUp.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptUp.y;
		}

		if (g_gxkl.ptUp.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptUp.y;
		}

		// DOWN
		if (g_gxkl.ptDown.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptDown.x;
		}

		if (g_gxkl.ptDown.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptDown.x;
		}

		if (g_gxkl.ptDown.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptDown.y;
		}

		if (g_gxkl.ptDown.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptDown.y;
		}

		// Left
		if (g_gxkl.ptLeft.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptLeft.x;
		}

		if (g_gxkl.ptLeft.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptLeft.x;
		}

		if (g_gxkl.ptLeft.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptLeft.y;
		}

		if (g_gxkl.ptLeft.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptLeft.y;
		}

		// Right
		if (g_gxkl.ptRight.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptRight.x;
		}

		if (g_gxkl.ptRight.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptRight.x;
		}

		if (g_gxkl.ptRight.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptRight.y;
		}

		if (g_gxkl.ptRight.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptRight.y;
		}

		// A
		if (g_gxkl.ptA.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptA.x;
		}

		if (g_gxkl.ptA.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptA.x;
		}

		if (g_gxkl.ptA.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptA.y;
		}

		if (g_gxkl.ptA.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptA.y;
		}

		// B
		if (g_gxkl.ptB.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptB.x;
		}

		if (g_gxkl.ptB.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptB.x;
		}

		if (g_gxkl.ptB.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptB.y;
		}

		if (g_gxkl.ptB.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptB.y;
		}

		// C
		if (g_gxkl.ptC.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptC.x;
		}

		if (g_gxkl.ptC.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptC.x;
		}

		if (g_gxkl.ptC.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptC.y;
		}

		if (g_gxkl.ptC.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptC.y;
		}

		// Start
		if (g_gxkl.ptStart.x > l_wXMax)
		{
			l_wXMax = g_gxkl.ptStart.x;
		}

		if (g_gxkl.ptStart.x < l_wXMin)
		{
			l_wXMin = g_gxkl.ptStart.x;
		}

		if (g_gxkl.ptStart.y > l_wYMax)
		{
			l_wYMax = g_gxkl.ptStart.y;
		}

		if (g_gxkl.ptStart.y < l_wYMin)
		{
			l_wYMin = g_gxkl.ptStart.y;
		}

		// Now we have the MIN and MAX in both X and Y
		// Calculate the ratio

 		float l_fXRatio = (float)g_gxdp.cxWidth / (l_wXMax - l_wXMin +20);
		if (l_fXRatio > 1)
		{
			l_fXRatio = 1;
			l_wXMin = 0;
		}
		float l_fYRatio = (float)g_gxdp.cyHeight / (l_wYMax  - l_wYMin +20);

		g_wKeyLoc[UP][X][in_bOrientation] = (long)((float)(g_gxkl.ptUp.x - l_wXMin)* l_fXRatio)-5;
		g_wKeyLoc[UP][Y][in_bOrientation] = (long)((float)(g_gxkl.ptUp.y - l_wYMin) * l_fYRatio);

		g_wKeyLoc[DOWN][X][in_bOrientation] = (long)((float)(g_gxkl.ptDown.x  - l_wXMin) * l_fXRatio)-5;
		g_wKeyLoc[DOWN][Y][in_bOrientation] = (long)((float)(g_gxkl.ptDown.y  - l_wYMin) * l_fYRatio);

		g_wKeyLoc[LEFT][X][in_bOrientation] = (long)((float)(g_gxkl.ptLeft.x  - l_wXMin) * l_fXRatio)-5;
		g_wKeyLoc[LEFT][Y][in_bOrientation] = (long)((float)(g_gxkl.ptLeft.y  - l_wYMin) * l_fYRatio);

		g_wKeyLoc[RIGHT][X][in_bOrientation] = (long)((float)(g_gxkl.ptRight.x  - l_wXMin) * l_fXRatio)-5;
		g_wKeyLoc[RIGHT][Y][in_bOrientation] = (long)((float)(g_gxkl.ptRight.y  - l_wYMin) * l_fYRatio);

		g_wKeyLoc[A][X][in_bOrientation] = (long)((float)(g_gxkl.ptA.x  - l_wXMin) * l_fXRatio)-5;
		g_wKeyLoc[A][Y][in_bOrientation] = (long)((float)(g_gxkl.ptA.y  - l_wYMin) * l_fYRatio);

		g_wKeyLoc[B][X][in_bOrientation] = (long)((float)(g_gxkl.ptB.x  - l_wXMin) * l_fXRatio)-5;
		g_wKeyLoc[B][Y][in_bOrientation] = (long)((float)(g_gxkl.ptB.y  - l_wYMin) * l_fYRatio);

		g_wKeyLoc[C][X][in_bOrientation] = (long)((float)(g_gxkl.ptC.x  - l_wXMin) * l_fXRatio)-5;
		g_wKeyLoc[C][Y][in_bOrientation] = (long)((float)(g_gxkl.ptC.y  - l_wYMin) * l_fYRatio);

		g_wKeyLoc[START][X][in_bOrientation] = (long)((float)(g_gxkl.ptStart.x  - l_wXMin) * l_fXRatio)-5;
		g_wKeyLoc[START][Y][in_bOrientation] = (long)((float)(g_gxkl.ptStart.y  - l_wYMin) * l_fYRatio);


        // if the direction buttons are too close together on the screen, fix this
        if (g_wKeyLoc[UP][Y][in_bOrientation] > g_wKeyLoc[START][Y][in_bOrientation] - LETTER_HEIGHT - 2)
        {
            g_wKeyLoc[UP][Y][in_bOrientation] = g_wKeyLoc[START][Y][in_bOrientation] - LETTER_HEIGHT - 2;
        }
        if (g_wKeyLoc[DOWN][Y][in_bOrientation] < g_wKeyLoc[START][Y][in_bOrientation] + LETTER_HEIGHT + 2)
        {
            g_wKeyLoc[DOWN][Y][in_bOrientation] = g_wKeyLoc[START][Y][in_bOrientation] + LETTER_HEIGHT + 2;
        }
        if (g_wKeyLoc[LEFT][X][in_bOrientation] > g_wKeyLoc[START][X][in_bOrientation] - LETTER_HEIGHT - 2)
        {
            g_wKeyLoc[LEFT][X][in_bOrientation] = g_wKeyLoc[START][X][in_bOrientation] - LETTER_HEIGHT - 2;
        }
        if (g_wKeyLoc[RIGHT][X][in_bOrientation] < g_wKeyLoc[START][X][in_bOrientation] + LETTER_HEIGHT + 2)
        {
            g_wKeyLoc[RIGHT][X][in_bOrientation] = g_wKeyLoc[START][X][in_bOrientation] + LETTER_HEIGHT + 2;
        }
		
	}
	else // Invert the buttons location since GAPI is not reporting Landscape Position
	{
		g_wKeyLoc[UP][X][in_bOrientation] = g_wKeyLoc[LEFT][X][!in_bOrientation];
		g_wKeyLoc[UP][Y][in_bOrientation] = g_wKeyLoc[LEFT][Y][!in_bOrientation];

		g_wKeyLoc[DOWN][X][in_bOrientation] = g_wKeyLoc[RIGHT][X][!in_bOrientation];
		g_wKeyLoc[DOWN][Y][in_bOrientation] = g_wKeyLoc[RIGHT][Y][!in_bOrientation];

		g_wKeyLoc[LEFT][X][in_bOrientation] = g_wKeyLoc[DOWN][X][!in_bOrientation];
		g_wKeyLoc[LEFT][Y][in_bOrientation] = g_wKeyLoc[DOWN][Y][!in_bOrientation];

		g_wKeyLoc[RIGHT][X][in_bOrientation] = g_wKeyLoc[UP][X][!in_bOrientation];
		g_wKeyLoc[RIGHT][Y][in_bOrientation] = g_wKeyLoc[UP][Y][!in_bOrientation];

		g_wKeyLoc[A][X][in_bOrientation] = g_wKeyLoc[A][X][!in_bOrientation];
		g_wKeyLoc[A][Y][in_bOrientation] = g_wKeyLoc[A][Y][!in_bOrientation];

		g_wKeyLoc[B][X][in_bOrientation] = g_wKeyLoc[B][X][!in_bOrientation];
		g_wKeyLoc[B][Y][in_bOrientation] = g_wKeyLoc[B][Y][!in_bOrientation];

		g_wKeyLoc[C][X][in_bOrientation] = g_wKeyLoc[C][X][!in_bOrientation];
		g_wKeyLoc[C][Y][in_bOrientation] = g_wKeyLoc[C][Y][!in_bOrientation];

		g_wKeyLoc[START][X][in_bOrientation] = g_wKeyLoc[START][X][!in_bOrientation];
		g_wKeyLoc[START][Y][in_bOrientation] = g_wKeyLoc[START][Y][!in_bOrientation];

	}

}

void DrawButtons(BOOL in_bOrientation)
{
	for (BYTE l_bButton = 0; l_bButton<MAX_BUTTONS; l_bButton++)
	{
		DrawBitmap((DWORD*)g_dwBitmaps[l_bButton], LETTER_WIDTH,
			LETTER_HEIGHT, g_wKeyLoc[l_bButton][X][in_bOrientation],
			g_wKeyLoc[l_bButton][Y][in_bOrientation], !g_bKeyInverted[l_bButton]);
	}
}

void DrawBitmap(
	DWORD* in_dwBits, 
	WORD in_wWidth, 
	WORD in_wHeight, 
	long in_lx, 
	long in_ly, 
	BOOL in_bInverted
	)
{
	if (in_lx < 2) in_lx = 2;
	if (in_lx > (WORD)g_gxdp.cxWidth - 12) in_lx = g_gxdp.cxWidth - 12;
	if (in_ly < 2) in_ly = 2;
	if (in_ly > (WORD)g_gxdp.cyHeight - 12) in_ly = g_gxdp.cyHeight - 12;

	for(WORD l_wX = 0; l_wX<in_wWidth; l_wX++)
	{
		for(WORD l_wY = 0; l_wY<in_wHeight; l_wY++)
		{
			if (in_bInverted)
			{
				if (g_bOrientation == PORTRAIT)
				{
					GameXSetPixel(in_lx+l_wX, in_ly+l_wY, ~in_dwBits[l_wY*in_wWidth+l_wX]);
				}
				else
				{
					GameXSetPixel(in_lx+l_wY, in_ly + in_wWidth - l_wX, ~in_dwBits[l_wY*in_wWidth+l_wX]);
				}
			}
			else
			{
				if (g_bOrientation == PORTRAIT)
				{
					GameXSetPixel(in_lx+l_wX, in_ly+l_wY, in_dwBits[l_wY*in_wWidth+l_wX]);
				}
				else
				{
					GameXSetPixel(in_lx+l_wY, in_ly + in_wWidth - l_wX, in_dwBits[l_wY*in_wWidth+l_wX]);
				}
			}
		}
	}

}

void ChangeDisplayMode(
	BOOL in_bLandscape
	)
{
    INT iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	INT iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (in_bLandscape)
	{
		if (FALSE == g_bFullScreen)
		{
			GXSetViewport(iScreenHeight/2 - 115, 150, 0, 0);

			RECT sRegion;
			sRegion.left = 0;
			sRegion.right = iScreenWidth;
			sRegion.top = iScreenHeight/2 - 55;
			sRegion.bottom = iScreenHeight/2 - 5;
			InvalidateRect(hWnd, &sRegion, TRUE);
		}
		g_gxkl = GXGetDefaultKeys(GX_LANDSCAPEKEYS);
	}
	else
	{
		if (FALSE == g_bFullScreen)
		{
		    GXSetViewport(iScreenHeight/2-55, 50, 0, 0);

			RECT sRegion;
			sRegion.left = 0;
			sRegion.right = iScreenWidth;
			sRegion.top = iScreenHeight/2 - 115;
			sRegion.bottom = iScreenHeight/2 + 35;
			InvalidateRect(hWnd, &sRegion, TRUE);
		}
		g_gxkl = GXGetDefaultKeys(GX_NORMALKEYS);
	}
	g_bOrientation = in_bLandscape;
}
