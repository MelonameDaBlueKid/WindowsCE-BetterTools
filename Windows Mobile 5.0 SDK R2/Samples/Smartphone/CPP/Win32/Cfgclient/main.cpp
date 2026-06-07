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
// ************************************************************
// main.cpp
//
// ************************************************************

#include <windows.h>
#include <cfgmgrapi.h>  // DMProcessConfigXML
#include "utils.h"


// ************************************************************
//
// WinMain
//
// ************************************************************

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       CmdShow)
{
    HRESULT hr              = S_OK;
    LPCTSTR pszInputXML     = NULL;
    LPTSTR  pszOutputXML    = NULL;

    // Load the input XML from this exe's resources.
    pszInputXML = (LPCTSTR)LoadString(hInstance, IDS_PROVXML, NULL, 0);
    CBR(NULL != pszInputXML);

    // Invoke DMProcessConfigXML to process the input XML.
    hr = DMProcessConfigXML(pszInputXML, CFGFLAG_PROCESS|CFGFLAG_METADATA, &pszOutputXML);
    CHR(hr);

Error:
    delete[] pszOutputXML;

    if (SUCCEEDED(hr))
    {
        RETAILMSG(TRUE, (TEXT("CfgClient Succeeded.")));
        return 0;
    }

    RETAILMSG(TRUE, (TEXT("CfgClient Failed.")));
    return 1;
}
