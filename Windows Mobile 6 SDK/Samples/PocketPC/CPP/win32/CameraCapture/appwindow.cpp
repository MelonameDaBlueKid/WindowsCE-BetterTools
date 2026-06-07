//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
#include "stdafx.h"

#define WINDOWWIDTH 240
#define WINDOWHEIGHT 320
#define CMD_START_RECORD_VIDEO 1
#define CMD_STOP_RECORD_VIDEO 2
#define CMD_STILL_IMAGE 3

CAppWindow::CAppWindow()
{
    m_hwnd = NULL;
    m_startButtonHwnd = NULL;
    m_wzStatusString = NULL;
}


CAppWindow::~CAppWindow()
{
    if( m_hwnd )
    {
        DestroyWindow( m_hwnd );
    }

    if( m_startButtonHwnd )
    {
        DestroyWindow( m_startButtonHwnd );
    }

    if( m_wzStatusString )
    {
        LocalFree( m_wzStatusString );
    }

    if( m_pGraphManager )
    {
        delete m_pGraphManager;
    }
}


HRESULT
CAppWindow::CreateControls( HINSTANCE hInstance )
{
    HRESULT     hr = S_OK;
    WNDCLASS    wndClass;
    ATOM        classAtom;
    LONG     	lReturn;
	RECT		rcWorkArea;

    // First, let's register the window class
    ZeroMemory( &wndClass, sizeof( wndClass ));
    wndClass.lpfnWndProc = CAppWindow::AppWindowProc; 
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = L"Camera Recording Video Class";

    classAtom = RegisterClass( &wndClass );
    if( classAtom == NULL )
    {
        ERR( HRESULT_FROM_WIN32( GetLastError() ));
    }


    // Now, create the main window
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);

    m_hwnd = CreateWindow( 
			L"Camera Recording Video Class", 
			L"Main Window", 
			WS_VISIBLE, 
			rcWorkArea.left,
            rcWorkArea.top,
            rcWorkArea.right - rcWorkArea.left,
            rcWorkArea.bottom - rcWorkArea.top,
			NULL, 
			NULL, 
			hInstance, 
			(PVOID) this );

    if( m_hwnd == NULL )
    {
        ERR( HRESULT_FROM_WIN32( GetLastError() ));
    }
    
    // Workaround for bug in SetWindowLong, call twice the API
    lReturn = SetWindowLong( m_hwnd, GWL_USERDATA, (LONG) this );
    lReturn = SetWindowLong( m_hwnd, GWL_USERDATA, (LONG) this );
    if( lReturn == NULL )
    {
        ERR( HRESULT_FROM_WIN32( GetLastError() ));
    }

    // Create a "Start Capture" button and add it to the main window
    m_startButtonHwnd = CreateWindow( 
			L"Button", 
			L"Start Video Recording", 
			WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHBUTTON | BS_VCENTER, 
			30, 
			10, 
			150, 
			20, 
			m_hwnd, 
			(HMENU) CMD_START_RECORD_VIDEO, 
			hInstance, 
			NULL );

    if( m_startButtonHwnd == NULL )
    {
        ERR( HRESULT_FROM_WIN32( GetLastError() ));
    }

    // Create a "Stop Capture" button and add it to the main window
    m_stopButtonHwnd = CreateWindow( 
			L"Button", 
			L"Stop Video Recording", 
			WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHBUTTON | BS_VCENTER, 
			30, 
			40, 
			150, 
			20, 
			m_hwnd, 
			(HMENU) CMD_STOP_RECORD_VIDEO, 
			hInstance, 
			NULL );

    if( m_startButtonHwnd == NULL )
    {
        ERR( HRESULT_FROM_WIN32( GetLastError() ));
    }
    
    // The stop capture button is disabled by default
    EnableWindow( m_stopButtonHwnd, FALSE );

	// Create the take still image button
	m_stillButtonHwnd = CreateWindow( 
			L"Button", 
			L"Take a still image", 
			WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHBUTTON | BS_VCENTER, 
			30, 
			70, 
			150, 
			20, 
			m_hwnd, 
			(HMENU) CMD_STILL_IMAGE, 
			hInstance, 
			NULL );

    if( m_startButtonHwnd == NULL )
    {
        ERR( HRESULT_FROM_WIN32( GetLastError() ));
    }

    // Create the graph manager. This will control the dshow capture pipeline
    m_pGraphManager = new CGraphManager();
    if( m_pGraphManager == NULL )
    {
        ERR( E_OUTOFMEMORY );
    }

    CHK( m_pGraphManager->RegisterNotificationWindow( m_hwnd ));

    CHK( m_pGraphManager->Init());
    CHK( m_pGraphManager->BuildCaptureGraph());

Cleanup:
    return hr; 
}


LRESULT CALLBACK
CAppWindow::AppWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    CAppWindow *pThis;

    //Let's retrieve the pointer to this first
    pThis = (CAppWindow*) GetWindowLong( hwnd, GWL_USERDATA );
    if( pThis )
    {
        return pThis->HandleWindowProc( hwnd, uMsg, wParam, lParam );
    }

    return DefWindowProc( hwnd, uMsg, wParam, lParam );
}


LRESULT 
CAppWindow::HandleWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    HRESULT hr = S_OK;

    switch( uMsg )
    {
        case WM_PAINT:
            RepaintWindow();
            break;

        case WM_CLOSE:
            PostMessage( NULL, WM_QUIT, 0, 0 );
            return 0;
            break;

        case WM_USER:
            UpdateNotification( (Message*) lParam );
            break;

		case WM_ACTIVATE:
			if( LOWORD( wParam ) == WA_INACTIVE )
			{
				PostMessage( NULL, WM_QUIT, 0, 0 );
			}

        case WM_COMMAND:
			HandleCommand( wParam );
            break;

        default:
            return DefWindowProc( hwnd, uMsg, wParam, lParam );
    }

    return 0;
}


HRESULT
CAppWindow::HandleCommand( WPARAM wParam )
{
	HRESULT hr = S_OK;

	if( m_pGraphManager == NULL )
	{
		ERR( E_FAIL );
	}

	switch( wParam )
	{
		case CMD_START_RECORD_VIDEO:
			EnableWindow( m_startButtonHwnd, FALSE );
			EnableWindow( m_stopButtonHwnd, TRUE );
			EnableWindow( m_stillButtonHwnd, FALSE );
			m_pGraphManager->StartRecordVideo();
			break;

		case CMD_STOP_RECORD_VIDEO:
			EnableWindow( m_stopButtonHwnd, FALSE );
			m_pGraphManager->StopRecordVideo();
			break;

		case CMD_STILL_IMAGE:
			EnableWindow( m_startButtonHwnd, FALSE );
			EnableWindow( m_stopButtonHwnd, FALSE );
			EnableWindow( m_stillButtonHwnd, FALSE );
			m_pGraphManager->CaptureStillImage();
			break;

		default:
			break;
    }

Cleanup:
	return hr;
}


HRESULT
CAppWindow::RepaintWindow()
{
    HDC         hdc;
    HBRUSH      hBrush, hOldBrush;
    HPEN        hPen, hOldPen;
    RECT        rcText = { 30, 110, 200, 130 };
    PAINTSTRUCT ps;

    // The window is repainted in white
    hdc = BeginPaint( m_hwnd, &ps );

    hBrush = (HBRUSH) GetStockObject( WHITE_BRUSH );
    hPen = (HPEN) GetStockObject( WHITE_PEN );
    hOldBrush = (HBRUSH) SelectObject( hdc, hBrush );
    hOldPen   = (HPEN)   SelectObject( hdc, hPen );
    
    Rectangle( hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT );

    SelectObject( hdc, hOldBrush );
    SelectObject( hdc, hOldPen );

    // And let's add the status string on the window
    if( m_wzStatusString )
    {
        hPen = (HPEN) GetStockObject( BLACK_PEN );
        hOldPen   = (HPEN)   SelectObject( hdc, hPen );

        DrawText( hdc, m_wzStatusString, -1, &rcText , DT_LEFT );

        SelectObject( hdc, hOldPen );
    }

    EndPaint( m_hwnd, &ps );

    return S_OK;
}


HRESULT
CAppWindow::Run()
{
    HRESULT hr = S_OK;
    MSG msg;

    // Start the capture graph
    CHK( m_pGraphManager->RunCaptureGraph());

    // Run the message pump
    while( GetMessage( &msg, NULL, 0, 0 ))
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    // Shutdown the capture graph.
    CHK( m_pGraphManager->ShutDown());

Cleanup:
    return 0;
}


HRESULT CAppWindow::UpdateNotification( Message *pMessage )
{
    HRESULT hr = S_OK;

    if( pMessage == NULL )
    {
        ERR( E_POINTER );
    }

    if(( pMessage->wzMessage == NULL ) || ( *(pMessage->wzMessage) == 0 ))
    {
        return S_OK;
    }
    
    if( m_wzStatusString )
    {
        LocalFree( m_wzStatusString );
        m_wzStatusString = NULL;
    }

    m_wzStatusString = pMessage->wzMessage;

    if( pMessage->dwMessage == MESSAGE_ENDRECORDING )
    {
        EnableWindow( m_startButtonHwnd, TRUE );        
		EnableWindow( m_stillButtonHwnd, TRUE );
    }
	else if( pMessage->dwMessage == MESSAGE_FILECAPTURED )
	{
        EnableWindow( m_startButtonHwnd, TRUE );        
		EnableWindow( m_stillButtonHwnd, TRUE );
	}

    LocalFree( pMessage );
    InvalidateRect( m_hwnd, NULL, TRUE );

Cleanup:
    return hr;
}
