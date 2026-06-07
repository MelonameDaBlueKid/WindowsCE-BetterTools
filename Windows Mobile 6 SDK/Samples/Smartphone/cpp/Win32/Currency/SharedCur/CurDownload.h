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
///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ExMan.h"


class IRateDownloader :
    public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE DownloadRates(HWND hwndMonitor, UINT umsgProgress, UINT uFinished) = 0;
    virtual HRESULT STDMETHODCALLTYPE Abort() = 0;
};


HRESULT CreateRateDownloader(IRateDownloader** pprd);


