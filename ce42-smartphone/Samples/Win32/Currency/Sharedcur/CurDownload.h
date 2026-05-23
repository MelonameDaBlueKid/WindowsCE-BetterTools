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


