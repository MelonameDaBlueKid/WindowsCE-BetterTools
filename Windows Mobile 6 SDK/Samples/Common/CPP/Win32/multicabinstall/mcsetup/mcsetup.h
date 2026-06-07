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
// MCSetup.h : main header file for the MCSetup DLL
//

#pragma once

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resourceppc.h"

// CMCSetupApp
// See MCSetup.cpp for the implementation of this class
//

class CMCSetupApp : public CWinApp
{
public:
    CMCSetupApp();

// Overrides
public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};

