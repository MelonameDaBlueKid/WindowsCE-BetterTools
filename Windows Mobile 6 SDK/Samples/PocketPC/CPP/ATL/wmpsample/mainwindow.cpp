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
//
// CMainWindow implementation
//
// --------------------------------------------------------------------------

#include "stdafx.h"
#include "resource.h"
#include "wmpsample.h"
#include "WMPEventSink.h"


extern CWMPSampleModule _AtlModule;
static BOOL fPlayPause = TRUE; 
static BOOL fFullScreen = TRUE;


// **************************************************************************
//
// CMainWindow::TranslateAccelerator
//
// Required to forward messages to the WMP control (and any other 
// ActiveX controls that may be added to the main window's design).
//
// **************************************************************************
BOOL CMainWindow::TranslateAccelerator(MSG* pMsg)
{
    // Accelerators are only keyboard or mouse messages
    HRESULT hr;
    CWindow control = ::GetFocus();
    UINT uMsg = pMsg->message;

    CBR((WM_KEYFIRST   <= uMsg && uMsg <= WM_KEYLAST) ||
        (WM_MOUSEFIRST <= uMsg && uMsg <= WM_MOUSELAST))
   
    CBR(NULL != m_hwndAppWindow)
    
    // Find a direct child of this window from the window that has focus.
    // This will be AtlAxWin window for the hosted control.
    
    if (IsChild(m_hwndAppWindow, control) && m_hwndAppWindow != control.GetParent())
    {
        do
        {
            control = control.GetParent();
        } while (m_hwndAppWindow != control.GetParent());
    }

    // Give the control (via the AtlAxWin) a chance to translate this message
    if (control.m_hWnd && control.SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg))
    {
        return TRUE;
    }

    // If the main window used accelerators, we could have called the global 
    // ::TranslateAccelerator() function here, instead of simply returning FALSE.
Error:
    return FALSE;
}


HRESULT ProcOnCreate(HWND hwnd)
{
    HRESULT hr = S_OK;
    SHMENUBARINFO mbi = { sizeof(mbi), 0 };
    RECT rcClient;
    RECT rcMainWindow = { 0 };
    CComPtr<IConnectionPointContainer>  spConnectionContainer;
    CComWMPEventDispatch        *pEventListener = NULL;
    CComPtr<IWMPEvents>         spEventListener;

    //initilaize the menu bar
    mbi.hwndParent = hwnd;
    mbi.nToolBarId = IDR_MAIN_MENUBAR; 
    mbi.hInstRes   = _AtlBaseModule.GetResourceInstance();
    SHCreateMenuBar(&mbi);
    _AtlModule.m_appWindow.m_menuBar = mbi.hwndMB; 
    
    //initialize WMP window
    AtlAxWinInit();   
    GetClientRect(hwnd, &rcClient);
    VERIFY(SystemParametersInfo(SPI_GETWORKAREA, 0, &rcMainWindow, 0));
    rcClient.bottom -= rcMainWindow.top;

    //create WMP control
    _AtlModule.m_appWindow.m_wmplayer.Create(hwnd, rcClient, TEXT("{6BF52A52-394A-11d3-B153-00C04F79FAA6}"), 
                WS_CHILD | WS_VISIBLE | WS_BORDER, 0);
    CBR(_AtlModule.m_appWindow.m_wmplayer.m_hWnd != NULL);

    hr = _AtlModule.m_appWindow.m_wmplayer.QueryControl(&(_AtlModule.m_appWindow.m_spWMPPlayer));
    CHR(hr);

    hr = CComWMPEventDispatch::CreateInstance(&pEventListener);
    CHR(hr);

    spEventListener = pEventListener;        
    hr = _AtlModule.m_appWindow.m_spWMPPlayer->QueryInterface(&spConnectionContainer);
    CHR(hr);

    // See if OCX supports the IWMPEvents interface
    hr = spConnectionContainer->FindConnectionPoint(__uuidof(IWMPEvents), 
                        &(_AtlModule.m_appWindow.m_spConnectionPoint));
    if (FAILED(hr))
    {
        // If not, try the _WMPOCXEvents interface, which will use IDispatch
        hr = spConnectionContainer->FindConnectionPoint(__uuidof(_WMPOCXEvents), 
            &(_AtlModule.m_appWindow.m_spConnectionPoint));
    }
    
    hr = _AtlModule.m_appWindow.m_spConnectionPoint->Advise(spEventListener, 
            &(_AtlModule.m_appWindow.m_dwAdviseCookie));
    CHR(hr);

Error:
    return SUCCEEDED(hr) ? 0 : -1;
}

HRESULT ProcOnOpen(HWND hwnd)
{
    HRESULT hr = S_OK;
    OPENFILENAMEEX  ofn;
    TCHAR           szFileName[_MAX_PATH];

    memset(&ofn, 0, sizeof(ofn)); // initialize structure to 0/NULL
    szFileName[0] = TEXT('\0');
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = ARRAYSIZE(szFileName);
    ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER;
    ofn.lpstrFilter = TEXT("All Media files\0*.wma;*.mp3;*.mpeg;*.avi;*.wmv;*.asf;*.wav;*.mid;*.dvr-ms;*.mid;*.rmi;*.midi;*.wm;*.snd;*.au;*.aif;*.mpg;*.m1v;*.mp2;*.mpa\0");
    ofn.hwndOwner = hwnd;
    ofn.hInstance = _AtlBaseModule.GetResourceInstance();

    CBR(GetOpenFileNameEx(&ofn));
    
    EndDialog(hwnd, IDOK);
    hr = _AtlModule.m_appWindow.m_spWMPPlayer->put_URL(CComBSTR(szFileName));

Error:
    return SUCCEEDED(hr) ? 0 : -1;
}


LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{   
    HRESULT hr = S_OK;
    HMENU hMenu;  
  
    DWORD dwControlHeight;
    RECT rcMenuBar= { 0 };
    RECT rcClient;
    RECT rcMainWindow = { 0 };

    CComPtr<IWMPControls> spWMPControls;    
        
    switch (msg)
    {

    case WM_COMMAND:

        hMenu = GetMenu(hwnd);

        switch (LOWORD(wp))
        {
        case IDM_OPEN:

            ProcOnOpen(hwnd);
            return 0;
            
        case IDM_EXIT:

            ::SendMessage(hwnd, WM_CLOSE, 0, 0);
            return 0;

        case IDM_STOP:   

            _AtlModule.m_appWindow.m_spWMPPlayer->get_controls(&spWMPControls);
            spWMPControls->stop();
            fPlayPause = FALSE;
            return 0;

        case IDM_PLAYPAUSE: 
            
            _AtlModule.m_appWindow.m_spWMPPlayer->get_controls(&spWMPControls);
            if (fPlayPause)
            {
                spWMPControls->pause();
            }
            else
            {
                spWMPControls->play();
            }
            fPlayPause = !fPlayPause;
            return 0;

        case IDM_INVISIBLE: 

            _AtlModule.m_appWindow.m_wmplayer.MoveWindow(0,0,0,0);
            return 0;

        case IDM_FULLSCREEN: //switch between fullscreeen and mini

            _AtlModule.m_appWindow.m_wmplayer.MoveWindow(0,0,0,0);
            GetClientRect(hwnd, &rcClient);
            if(fFullScreen)
            {
                _AtlModule.m_appWindow.m_menuBar.GetWindowRect(&rcMenuBar);
                dwControlHeight = 2 * (rcMenuBar.bottom - rcMenuBar.top); // the height of WMP toolbar
                _AtlModule.m_appWindow.m_wmplayer.MoveWindow(rcClient.left, rcClient.top, rcClient.right, dwControlHeight);
            }
            else
            {
                VERIFY(SystemParametersInfo(SPI_GETWORKAREA, 0, &rcMainWindow, 0));
                rcClient.bottom -= rcMainWindow.top;
                _AtlModule.m_appWindow.m_wmplayer.MoveWindow(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
               
            }
            fFullScreen = !fFullScreen;
            return 0;
            break;
        }
        
    case WM_CREATE:

        ProcOnCreate(hwnd);
        return 0;
        break;

    case WM_DESTROY:

        _AtlModule.m_appWindow.m_menuBar = NULL;
        // Tear down connection points while controls are still alive.
        if (_AtlModule.m_appWindow.m_spConnectionPoint)
        {
            if (0 != _AtlModule.m_appWindow.m_dwAdviseCookie)
            {
                _AtlModule.m_appWindow.m_spConnectionPoint->Unadvise(_AtlModule.m_appWindow.m_dwAdviseCookie);
            }
            _AtlModule.m_appWindow.m_spConnectionPoint.Release();
        }

        // close the OCX
        if (_AtlModule.m_appWindow.m_spWMPPlayer)
        {
            _AtlModule.m_appWindow.m_spWMPPlayer->close();
            _AtlModule.m_appWindow.m_spWMPPlayer.Release();
        }
        _AtlModule.m_appWindow.m_wmplayer.Detach();
        PostQuitMessage(0);

        return 0;
   
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
}