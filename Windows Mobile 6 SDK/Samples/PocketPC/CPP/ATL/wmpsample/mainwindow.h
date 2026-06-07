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
// CMainWindow defines the main window for this application.
// It is derived from IDispEventImpl.
// The WIN32 window and the WMP control are public members 
//
// --------------------------------------------------------------------------

#pragma once

#include "stdafx.h"

class CMainWindow
{
public:
    
    // Required to forward messages to the WMP control
    BOOL TranslateAccelerator(MSG* pMsg);
    
public:
    // handle of the WIN32 window. It is used to contain the WMP control
    HWND m_hwndAppWindow;
    
    // Represents the WMP control contained in the main application.
    // m_wmplayer is used to manage the control and its associated 
    // "AtlAxWin" window. (AtlAxWin is a window class that ATL uses to support 
    // containment of controls in windows.)
    CAxWindow m_wmplayer;

    //the control's interface
    CComPtr<IWMPPlayer>         m_spWMPPlayer;

    //connection point
    CComPtr<IConnectionPoint>   m_spConnectionPoint;
    DWORD                       m_dwAdviseCookie;
    
    // main menu bar for application
    CWindow m_menuBar;

};


