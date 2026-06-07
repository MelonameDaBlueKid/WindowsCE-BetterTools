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


