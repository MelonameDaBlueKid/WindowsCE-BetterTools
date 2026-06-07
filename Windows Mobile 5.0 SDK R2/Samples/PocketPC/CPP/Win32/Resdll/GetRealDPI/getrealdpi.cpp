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
// GetRealDPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPTSTR    lpCmdLine,
                    int       nCmdShow)
{
    HDC hdc = ::GetDC(NULL);
    INT ans = ::GetDeviceCaps(hdc, LOGPIXELSX);
    ::ReleaseDC(NULL, hdc);
    return ans;
}

