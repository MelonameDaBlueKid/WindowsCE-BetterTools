/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
// TrackStylus.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TrackStylus.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100

//DirectDraw (not implemented yet) does a DSA rectangle 
//MainHDC draws to the foreground HDC by doing a UnionRect of the changed Rect
//BackHDC draws to a background HDC by doing a UnionRect of the changed Rect 
//and blt's forward
enum RectSize {Rect10 = 10 , Rect30 = 30, Rect50 = 50};
RectSize m_Rectsize;
enum DrawType {DirectDraw, MainHDC, BackHDC};
DrawType m_Drawing;

RECT oldRC, newRC;

HDC hdcMain;
HDC hdcBack;
HBITMAP hbmBack;

// Global Variables:
HINSTANCE			hInst;			// The current instance
HWND				hwndCB;			// The command bar handle

TCHAR	szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass	(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);

//
void SetDrawType(DrawType i);
void SetRectSize(RectSize i);
void OnMouseUp(HWND hWnd, POINT pt);
void OnMouseMove(HWND hWnd, POINT pt);
void OnMouseDown(HWND hWnd, POINT pt);


//
int WINAPI WinMain(	HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR    lpCmdLine,int       nCmdShow)
{
  MSG msg;
  
  LoadString(hInstance, IDC_TRACKSTYLUS, szWindowClass, MAX_LOADSTRING);
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow)) 
  {
    return FALSE;
  }
  
  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
  WNDCLASS	wc;
  
  wc.style			= CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc		= (WNDPROC) WndProc;
  wc.cbClsExtra		= 0;
  wc.cbWndExtra		= 0;
  wc.hInstance		= hInstance;
  wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRACKSTYLUS));
  wc.hCursor			= 0;
  wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName		= 0;
  wc.lpszClassName	= szWindowClass;
  
  return RegisterClass(&wc);
}

//
//  FUNCTION: InitInstance(HANDLE, int)
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND	hWnd;
  
  hInst = hInstance;		// Store instance handle in our global variable
  // Initialize global strings
  MyRegisterClass(hInstance, szWindowClass);
  
  hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  
  //When the main window is created using CW_USEDEFAULT the height of the menubar (if one
  // is created is not taken into account). So we resize the window after creating it
  // if a menubar is present
  {
    RECT rc;
    GetWindowRect(hWnd, &rc);
    rc.bottom -= MENU_HEIGHT;
    if (hwndCB)
      MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
  }
  
  if (!hWnd)
  {	
    return FALSE;
  }
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  
  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;
  
  switch (message) 
  {
		case WM_COMMAND:
      wmId    = LOWORD(wParam); 
      wmEvent = HIWORD(wParam); 
      // Parse the menu selections:
      switch (wmId)
      {
      case ID_FILE_ERASE:
        {
          RECT rc;
          HDC hDC = GetDC(hWnd);
          GetClientRect(hWnd, &rc);
          rc.bottom -= MENU_HEIGHT;
          FillRect(hDC, &rc, GetStockBrush(WHITE_BRUSH));
          ReleaseDC(hWnd, hDC);
        }
        break;
      case ID_OPTIONS_RECT10:
        SetRectSize(Rect10);
        break;
      case ID_OPTIONS_RECT30:
        SetRectSize(Rect30);
        break;
      case ID_OPTIONS_RECT50:
        SetRectSize(Rect50);
        break;
      case ID_OPTIONS_USEDIRECTDRAW:
        SetDrawType(DirectDraw);
        break;
      case ID_OPTIONS_USEMAINHDC:
        SetDrawType(MainHDC);
        break;
      case ID_OPTIONS_USEBACKHDC:
        SetDrawType(BackHDC);
        break;
      case IDM_FILE_EXIT:
        DestroyWindow(hWnd);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;
      case WM_LBUTTONDOWN:
        {
          POINT pt; pt.x = LOWORD(lParam); pt.y = HIWORD(lParam);
          OnMouseDown( hWnd, pt);
        }
        break;
      case WM_MOUSEMOVE:
        {
          POINT pt; pt.x = LOWORD(lParam); pt.y = HIWORD(lParam);
          OnMouseMove( hWnd,  pt);
        }
        break;
      case WM_LBUTTONUP:
        {
          POINT pt; pt.x = LOWORD(lParam); pt.y = HIWORD(lParam);
          OnMouseUp( hWnd,  pt);
        }
        break;
      case WM_CREATE:
        //Create a MenuBar
        SHMENUBARINFO mbi;
        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hWnd;
        mbi.nToolBarId = IDM_MAIN_MENU;
        mbi.hInstRes   = hInst;
        mbi.nBmpId     = 0;
        mbi.cBmpImages = 0;	
        
        SHCreateMenuBar(&mbi);
        if (!SHCreateMenuBar(&mbi))
          MessageBox(hWnd, L"SHCreateMenuBar Failed", L"Error", MB_OK);
        hwndCB = mbi.hwndMB;
        
        SetRectSize(Rect10);
        SetDrawType(MainHDC);
        {
          RECT rc;
          HDC hDC = GetDC(hWnd);
          hdcBack = CreateCompatibleDC(hDC);
          GetClientRect(hWnd, &rc);
          hbmBack = CreateCompatibleBitmap(hDC,rc.right, rc.bottom );
          SelectObject(hdcBack, (HBITMAP)hbmBack);
          ReleaseDC(hWnd, hDC);
        }
        break;
      case WM_DESTROY:
        //Destroy MenuBar       
        DestroyWindow(hwndCB);
        DeleteBitmap(hbmBack);
        DeleteDC(hdcBack);
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

/////////////////////////////////////////////////////////////////////////////// 
void SetRectSize(RectSize i){
  m_Rectsize = i;
  HMENU hOptionMenu = SHMenuBar_GetMenu(hwndCB, IDM_MAIN_MENUITEM2);
  switch (i){
		case Rect10:
      CheckMenuRadioItem(hOptionMenu,
        ID_OPTIONS_RECT10, ID_OPTIONS_RECT50, ID_OPTIONS_RECT10, MF_BYCOMMAND );
      break;
    case Rect30:
      CheckMenuRadioItem(hOptionMenu,
        ID_OPTIONS_RECT10, ID_OPTIONS_RECT50, ID_OPTIONS_RECT30, MF_BYCOMMAND );
      break;
    case Rect50:
      CheckMenuRadioItem(hOptionMenu,
        ID_OPTIONS_RECT10, ID_OPTIONS_RECT50, ID_OPTIONS_RECT50, MF_BYCOMMAND );
      break;
    default:
      CheckMenuRadioItem(hOptionMenu,
        ID_OPTIONS_RECT10, ID_OPTIONS_RECT50, ID_OPTIONS_RECT10, MF_BYCOMMAND );
      break;
  }
  return;
}

void SetDrawType(DrawType i){
  m_Drawing = i;
  HMENU hOptionMenu = SHMenuBar_GetMenu(hwndCB, IDM_MAIN_MENUITEM2);
  switch (i){
  case MainHDC:
    CheckMenuRadioItem(hOptionMenu,
      ID_OPTIONS_USEMAINHDC, ID_OPTIONS_USEBACKHDC, ID_OPTIONS_USEMAINHDC, MF_BYCOMMAND );
    break;
  case BackHDC:
    CheckMenuRadioItem(hOptionMenu,
      ID_OPTIONS_USEMAINHDC, ID_OPTIONS_USEBACKHDC, ID_OPTIONS_USEBACKHDC, MF_BYCOMMAND );
    break;
  default:
    CheckMenuRadioItem(hOptionMenu,
      ID_OPTIONS_USEMAINHDC, ID_OPTIONS_USEBACKHDC, ID_OPTIONS_USEMAINHDC, MF_BYCOMMAND );
    break;
  }
  return;
}

void OnMouseDown(HWND hWnd, POINT pt){
  HDC hDC;
  RECT rcUnion, rcIntersect;

	GetCapture();
  memset(&oldRC,0,sizeof(RECT));
  memset(&newRC,0,sizeof(RECT));
  newRC.left = pt.x;newRC.top = pt.y;
  newRC.right = newRC.left + m_Rectsize;
  newRC.bottom = newRC.top + m_Rectsize;
  UnionRect(&rcUnion, &newRC, &oldRC);
  IntersectRect(&rcIntersect, &newRC, &oldRC);
  hDC = GetDC(hWnd);	
  switch(m_Drawing)
  {
  case MainHDC:
    FillRect(hDC, &newRC, GetStockBrush(BLACK_BRUSH));
    break;
  case BackHDC:
    FillRect(hdcBack, &newRC, GetStockBrush(BLACK_BRUSH));
    BitBlt(hDC,newRC.left, newRC.top, newRC.right-newRC.left, newRC.bottom-newRC.top, hdcBack, newRC.left, newRC.top, SRCCOPY);
    break;
  default:
    break;
  }
  CopyRect(&oldRC,&newRC);
  ReleaseDC(hWnd, hDC);
  return;
}

void OnMouseMove(HWND hWnd, POINT pt){
  HDC hDC;
  RECT rcUnion, rcIntersect;
  newRC.left = pt.x;
  newRC.top = pt.y;
  newRC.right = newRC.left + m_Rectsize;
  newRC.bottom = newRC.top + m_Rectsize;
  UnionRect(&rcUnion, &newRC, &oldRC);
  IntersectRect(&rcIntersect, &newRC, &oldRC);
  hDC = GetDC(hWnd);
  switch(m_Drawing){
  case DirectDraw:
    break;
  case MainHDC:
    FillRect(hDC, &oldRC, GetStockBrush(WHITE_BRUSH));
    FillRect(hDC, &newRC, GetStockBrush(BLACK_BRUSH));
    break;
  case BackHDC:
    FillRect(hdcBack, &rcUnion, GetStockBrush(WHITE_BRUSH));
    FillRect(hdcBack, &newRC, GetStockBrush(BLACK_BRUSH));
    BitBlt(hDC,rcUnion.left, rcUnion.top, rcUnion.right-rcUnion.left, 
      rcUnion.bottom-rcUnion.top, hdcBack, rcUnion.left, rcUnion.top, SRCCOPY);
    break;
  default:
    break;
  }
  CopyRect(&oldRC,&newRC);
  ReleaseDC(hWnd, hDC);
  return;
}

void OnMouseUp(HWND hWnd, POINT pt){
  HDC hDC;
  RECT rcUnion, rcIntersect;
  
  newRC.left = pt.x;
  newRC.top = pt.y;
  newRC.right = newRC.left + m_Rectsize;
  newRC.bottom = newRC.top + m_Rectsize;
  UnionRect(&rcUnion, &newRC, &oldRC);
  IntersectRect(&rcIntersect, &newRC, &oldRC);
  hDC = GetDC(hWnd);
  switch(m_Drawing){
  case DirectDraw:
    break;
  case MainHDC:
    FillRect(hDC, &oldRC, GetStockBrush(WHITE_BRUSH));
    FillRect(hDC, &newRC, GetStockBrush(WHITE_BRUSH));
    break;
  case BackHDC:
    FillRect(hdcBack, &rcUnion, GetStockBrush(WHITE_BRUSH));
    BitBlt(hDC,rcUnion.left, rcUnion.top, rcUnion.right-rcUnion.left,
      rcUnion.bottom-rcUnion.top, hdcBack, rcUnion.left, rcUnion.top, SRCCOPY);
    break;
  default:
    break;
  }
  CopyRect(&oldRC,&newRC);
  ReleaseDC(hWnd, hDC);
	ReleaseCapture();
  return;
}


