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
