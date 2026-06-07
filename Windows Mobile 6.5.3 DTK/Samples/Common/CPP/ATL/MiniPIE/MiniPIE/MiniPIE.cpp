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

// MiniPIE.cpp : Implementation of WinMain.


#include "stdafx.h"
#include "MainWindow.h"


class CMiniPIEModule : public CAtlExeModuleT< CMiniPIEModule >
{
public :
    // This method is called immediately before entering the message loop.
    // It contains initialization code for the application.
    // Returns:
    // S_OK => Success. Continue with RunMessageLoop() and PostMessageLoop().
    // S_FALSE => Skip RunMessageLoop(), call PostMessageLoop().
    // error code => Failure. Skip both RunMessageLoop() and PostMessageLoop().
    HRESULT PreMessageLoop(int nShowCmd) throw()
    {
        HRESULT hr = __super::PreMessageLoop(nShowCmd);
        if (FAILED(hr))
        {
            return hr;
        }
        // Note: In this sample, we don't respond differently to different hr success codes.

        // Allow only one instance of the application.
        // the "| 0x01" activates the correct owned window of the previous instance's main window
        HWND hWnd = FindWindow(CMainWindow::GetWndClassInfo().m_wc.lpszClassName, NULL);
        if (hWnd)
        {
            SetForegroundWindow( HWND( DWORD(hWnd) | 0x01 ) );
            return S_FALSE;
        }

        // Create the main application window
        m_appWindow.Create(NULL, CWindow::rcDefault, TEXT("MiniPIE"));
        if (NULL == m_appWindow.m_hWnd)
        {
            return S_FALSE;
        }

        // Show the main application window
        m_appWindow.ShowWindow(nShowCmd);
        return S_OK;
    }


    void RunMessageLoop( ) throw( )
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

private:
    CMainWindow m_appWindow;
};

CMiniPIEModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

