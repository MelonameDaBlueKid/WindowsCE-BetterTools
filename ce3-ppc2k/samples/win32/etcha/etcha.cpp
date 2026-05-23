/*******************************************************************++


THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright  1994-1997  Microsoft Corporation.  All Rights Reserved.


Module Name:

    etcha.c

Abstract:

    This sample demonstrates a basic drawing application.

    
Functions:

    BeginPaint
    CreateWindow
    DefWindowProc
    DestroyWindow
    DispatchMessage
    EndPaint
    ExtTextOut
    FillRect
    GetClientRect
    GetDC
    GetMessage
    GetStockObject
    InvalidateRect
    Polyline
    PostQuitMessage
    RegisterClass
    ReleaseDC
    SelectObject
    SendMessage
    SetBkColor
    SetTextColor
    TranslateMessage
    UpdateWindow
    WinMain
    WndProc
    WndProcButton
    wsprintf


  Messages:

    WM_CLOSE
    WM_DESTROY
    WM_KILLFOCUS
    WM_LBUTTONDBLCLK
    WM_LBUTTONDOWN
    WM_LBUTTONUP
    WM_MOUSEMOVE
    WM_PAINT

************************************************************************/

#include <windows.h>
#include <tchar.h>
#include "resource.h"

#if (_WIN32_WCE >= 200)
#define PALETTEINDX     PALETTEINDEX2BPP
#else
#define PALETTEINDX        PALETTEINDEX // _WIN32_WCE=100 or _WIN32_WCE=101
#endif

//Global variables
BOOL    bLBDown;
HWND    v_hWndMain;
HWND    v_hWndClear;
HINSTANCE v_hInst;


/**********************************************************************
   WndProcButton -  Window Procedure for the clear screen/EXIT button.
***********************************************************************/


LRESULT CALLBACK
WndProcButton (HWND hWnd,
               UINT message,
               WPARAM uParam,
               LPARAM lParam )
{


    static HFONT    hfont;
    HDC             hdc;
    RECT            rect;
    TCHAR szClear[80];

    //Load string on "clear screen/exit" button
    LoadString(v_hInst, CLEAR, szClear, sizeof(szClear)/sizeof(TCHAR));

    switch (message) {

    case WM_CREATE:
        break;

    case WM_PAINT :
    {   // Repaint clear button
        PAINTSTRUCT ps;

        GetClientRect(hWnd, &rect);

        hdc = BeginPaint (hWnd, &ps);

        FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

        (void)SelectObject(hdc, GetStockObject(SYSTEM_FONT));

        (void)SetTextColor(hdc,PALETTEINDX(0));

        (void)SetBkColor(hdc,PALETTEINDX(3));

        ExtTextOut(hdc, 5, 4, ETO_OPAQUE, &rect, szClear, _tcslen(szClear),
                   NULL);

        EndPaint (hWnd, &ps);

        break;
    }

    case WM_LBUTTONUP :

       //The clear button has been clicked/tapped once and the main window
       //screen must be invalidated.

            InvalidateRect (v_hWndMain, NULL, TRUE);

            UpdateWindow(v_hWndMain);
            break;



    case WM_LBUTTONDBLCLK:

        //The user has doubleclicked the button to exit the program

        SendMessage(v_hWndMain, WM_CLOSE,0,0);
        break;


    default :
        return(DefWindowProc(hWnd, message, uParam, lParam));
    }

    return(0);
}

/*************************************************************************

     WndProc()  Main window procedure

  ************************************************************************/

LRESULT CALLBACK
WndProc ( HWND hWnd,
          UINT message,
          WPARAM uParam,
          LPARAM lParam )
{

    static HDC   hdc;
    static POINT line[2];
    RECT rect;


    switch (message) {
    case WM_CREATE :
        break;

    case WM_PAINT :
    {
        //Paint Main window, inking on main window not saved, window is repainted
        //blank
        PAINTSTRUCT ps;

        hdc = BeginPaint (hWnd, &ps);

        GetClientRect(hWnd, &rect);

        FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

        EndPaint (hWnd, &ps);
        break;
    }


    case WM_LBUTTONDOWN :
    //If Left button is down, save mouse coordinates in Line[0] point

       bLBDown = TRUE;

       line[0].x = LOWORD(lParam);
       line[0].y = HIWORD(lParam);
       break;

            

    case WM_LBUTTONUP :
        //Draw last line. Since Left button down is false, no more lines are drawn
        //until next WM_LBUTTONDOWN message

       bLBDown = FALSE;
       line[1].x = LOWORD(lParam);
       line[1].y = HIWORD(lParam);
    
       if((line[0].x != line[1].x) || (line[0].y != line[1].y))
            { Polyline(hdc, line, 2);}
       break;

    case WM_MOUSEMOVE :
    //If left mouse button is down save mouse coordinates in Line[1] point.
     //If point line[1] doesn't equal point line[0], then call polyline to draw
     //an line from point line[0] to point line [1]

         if ( bLBDown == TRUE )
         {
            hdc = GetDC(hWnd);

            line[1].x = LOWORD(lParam);
            line[1].y = HIWORD(lParam);

            if((line[0].x != line[1].x) || (line[0].y != line[1].y))
             {  Polyline(hdc, line, 2);
            
            //reset value of initial point to end point
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

        PostQuitMessage(0);

        return DefWindowProc(hWnd, message, uParam, lParam);


   default :
        return DefWindowProc(hWnd, message, uParam, lParam);
    }

    return 0;
}



/**********************************************************************************
     WinMain()
**********************************************************************************/


int WINAPI WinMain ( HINSTANCE hInstance,
                     HINSTANCE hPreviousInstance,
                     LPWSTR pszCommandLine,
                     int nCommandShow)
{
    WNDCLASSW wc;
    MSG msg;
    TCHAR szAppName[80],szTitle[80], szButton[80], szNull[80];

    //Load strings
    LoadString(hInstance, APPNAME, szAppName, sizeof(szAppName)/sizeof(TCHAR));
    LoadString(hInstance, TITLE, szTitle, sizeof(szTitle)/sizeof(TCHAR));
    LoadString(hInstance, BUTTON, szButton, sizeof(szButton)/sizeof(TCHAR));
    LoadString(hInstance, NULLSTR, szNull, sizeof(szNull)/sizeof(TCHAR));

    //Pass value to global v_hInst for use in WndProcButton
    v_hInst = hInstance;
       
    wc.style = CS_HREDRAW | CS_VREDRAW;
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
        OutputDebugString(TEXT("RegisterClass Failed\n"));
        return(FALSE);
    }

     v_hWndMain = CreateWindow(szAppName, szTitle, WS_VISIBLE,
                              0, 0,CW_USEDEFAULT ,CW_USEDEFAULT, NULL, NULL,
                              hInstance, NULL);

    wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
    wc.lpszClassName = szButton;
    wc.lpfnWndProc = (WNDPROC) WndProcButton;
    wc.style = CS_DBLCLKS;


    if ( RegisterClass(&wc) == FALSE ) {
        DWORD dwerror=GetLastError();
        OutputDebugString(TEXT("RegisterClass Failed\n"));
        return(FALSE);
    }

    v_hWndClear = CreateWindow( szButton, szNull,
            WS_CHILD | WS_VISIBLE | WS_BORDER ,
            25, 260, 190, 20, v_hWndMain, NULL, hInstance, NULL);

    if ( v_hWndMain == 0 || v_hWndClear == 0)
    {
        OutputDebugString(TEXT("CreateWindow Failed\n"));
        return(FALSE);
    }

    UpdateWindow(v_hWndMain);
    UpdateWindow(v_hWndClear);
    ShowWindow(v_hWndMain, nCommandShow);
    ShowWindow(v_hWndClear, nCommandShow);

    while ( GetMessage(&msg, NULL, 0, 0) == TRUE )
    {
        DispatchMessage(&msg);
    }

    return(TRUE);
}


