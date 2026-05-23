// HelloHibernate.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include <commctrl.h>

/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
****************************************************************************/

#include <windows.h>
#include <windowsx.h>

#define ID_BUTTON 5000

HINSTANCE hInst = NULL;  // Local copy of hInstance
HWND hwndMain = NULL;    // Handle to Main window returned from CreateWindow

TCHAR szAppName[] = TEXT("Hello Application");
TCHAR szTitle[]   = TEXT("Hibernate");

/**************************************************************************************

  WndProc
  
**************************************************************************************/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
  LRESULT		lResult = TRUE;
  RECT		rect;
  
  switch(msg)
  {
  case WM_COMMAND:
    {
      WORD wID = LOWORD(wp);         // item, control, or accelerator identifier 
      if (wID == ID_BUTTON)
        PostMessage(hwnd, WM_HIBERNATE, 0, 0);
    }
    break;
    
		case WM_CREATE:
      {
        GetClientRect (hwnd, &rect);
        
        rect.left = (rect.right - rect.left)/2 - 50;
        rect.top = (rect.bottom - rect.top)/2 - 25;
        
        HWND hwndButton = CreateWindow(L"button", L"Hello World", BS_DEFPUSHBUTTON,
          rect.left, rect.top, 100, 50,
          hwnd, (HMENU)ID_BUTTON, hInst, NULL);
        
        if (hwndButton){
          ShowWindow(hwndButton, SW_SHOW);
          UpdateWindow(hwndButton);
        }
      }		
      break;
      
    case WM_HIBERNATE:
      PostMessage(hwnd, WM_CLOSE, 0, 0);
      break;
      
    case WM_CLOSE:
      DestroyWindow(hwnd);
      break;
      
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
      
    default:
      lResult = DefWindowProc(hwnd, msg, wp, lp);
      break;
  }
  return (lResult);
}


/****************************************************************************

  InitInstance
  
*****************************************************************************/

BOOL InitInstance (HINSTANCE hInstance, int CmdShow )
{
  
  hInst = hInstance;
  hwndMain = CreateWindow(szAppName,						
    szTitle,
    WS_VISIBLE,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL );
  
  if ( !hwndMain )		
  {
    return FALSE;
  }
  ShowWindow(hwndMain, CmdShow );
  UpdateWindow(hwndMain);
  return TRUE;
}

/****************************************************************************

  InitApplication
  
****************************************************************************/

BOOL InitApplication ( HINSTANCE hInstance )
{
  WNDCLASS wc;
  BOOL f;
  
  wc.style = CS_HREDRAW | CS_VREDRAW ;
  wc.lpfnWndProc = (WNDPROC)WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hIcon = NULL;
  wc.hInstance = hInstance;
  wc.hCursor = NULL;
  wc.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );
  wc.lpszMenuName = NULL;
  wc.lpszClassName = szAppName;
  
  f = (RegisterClass(&wc));
  
  return f;
}


/*****************************************************************************

  WinMain
  
***************************************************************************/

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPWSTR     lpCmdLine,
                   int        CmdShow)
                   
{
  MSG msg;
  HWND hHelloWnd = NULL;	
  
  //Check if Hello.exe is running. If it's running then focus on the window
  hHelloWnd = FindWindow(szAppName, szTitle);	
  if (hHelloWnd) 
  {
    SetForegroundWindow (hHelloWnd);    
    return 0;
  }
  
  if ( !hPrevInstance )
  {
    if ( !InitApplication ( hInstance ) )
    { 
      return (FALSE); 
    }
    
  }
  if ( !InitInstance( hInstance, CmdShow )  )
  {
    return (FALSE);
  }
  while ( GetMessage( &msg, NULL, 0,0 ) == TRUE )
  {
    TranslateMessage (&msg);
    DispatchMessage(&msg);
  }
  return (msg.wParam);
}

// END HELLO.CPP

