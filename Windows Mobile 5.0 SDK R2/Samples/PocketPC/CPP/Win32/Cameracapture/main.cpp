//
// Copyright (c) Microsoft Corporation.� All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
#include "stdafx.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd )
{
    HRESULT hr = S_OK;

    CAppWindow      appWindow;

    // Launch COM
    CHK( CoInitialize( NULL ));

    // Initialize the UI Controls
    CHK( appWindow.CreateControls( hInstance ));
    
    // Start the UI and run the message pump
    CHK( appWindow.Run());

Cleanup:
    CoUninitialize();
    return 0;
}