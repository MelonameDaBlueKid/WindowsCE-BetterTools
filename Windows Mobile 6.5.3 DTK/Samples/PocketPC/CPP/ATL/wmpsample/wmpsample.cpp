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
// --------------------------------------------------------------------------
// WMPSample.cpp : Implementation of the main module.
//
// --------------------------------------------------------------------------


#include "stdafx.h"
#include "resource.h"
#include "wmpsample.h"

// This method is called immediately before entering the message loop.
// It contains initialization code for the application.
// Returns:
// S_OK => Success. Continue with RunMessageLoop() and PostMessageLoop().
// S_FALSE => Skip RunMessageLoop(), call PostMessageLoop().
// error code => Failure. Skip both RunMessageLoop() and PostMessageLoop().
HRESULT CWMPSampleModule::PreMessageLoop(int nShowCmd) throw()
{
    
    HRESULT hr = __super::PreMessageLoop(nShowCmd);
    WNDCLASS wc = { 0 };
    CHR(hr);        
    
    // Allow only one instance of the application.
    // the "| 0x01" activates the correct owned window of the previous instance's main window
    HWND hWnd = FindWindow(TEXT("WMP Sample"), NULL);
    if (hWnd)
    {
        SetForegroundWindow( HWND( DWORD(hWnd) | 0x01 ) );
        return S_FALSE;
    }
    
    // Create the main WIN32 application container    
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = _AtlBaseModule.GetModuleInstance();
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = TEXT("WMP Sample");
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // Register the window class
    BOOL bClassName = ::RegisterClass(&wc);
    CBR(bClassName);
    
    m_appWindow.m_hwndAppWindow = ::CreateWindow(TEXT("WMP Sample"), 
                                    TEXT("WMP Sample"), 
                                    WS_CLIPCHILDREN,
                                    CW_USEDEFAULT, 
                                    CW_USEDEFAULT, 
                                    CW_USEDEFAULT, 
                                    CW_USEDEFAULT,
                                    NULL, 
                                    NULL, 
                                    _AtlBaseModule.GetModuleInstance(), 
                                    NULL);

    CBR(m_appWindow.m_hwndAppWindow != NULL);
    
    // Show the main application window
    ::ShowWindow(m_appWindow.m_hwndAppWindow, nShowCmd);
    hr = S_OK;

Error:
    return hr;
}

void CWMPSampleModule::RunMessageLoop( ) throw( )
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {  
        if (!m_appWindow.TranslateAccelerator(&msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

CWMPSampleModule _AtlModule;


extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

