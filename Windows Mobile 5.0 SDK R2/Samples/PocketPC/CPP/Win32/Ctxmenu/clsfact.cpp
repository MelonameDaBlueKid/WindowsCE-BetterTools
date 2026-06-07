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
/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.
    
****************************************************************************/

// CLSFACT.CPP - class implementation for CContextMenuSampleClassFactory

#include "common.h"

extern UINT g_cRefDLL;

CContextMenuSampleClassFactory::CContextMenuSampleClassFactory()
{
    m_cRef = 0;

    ++g_cRefDLL;
}


CContextMenuSampleClassFactory::~CContextMenuSampleClassFactory()
{
    ASSERT(0 == m_cRef);

    --g_cRefDLL;
}


STDMETHODIMP_(ULONG) CContextMenuSampleClassFactory::AddRef()
{
    return ++m_cRef;
}


STDMETHODIMP_(ULONG) CContextMenuSampleClassFactory::Release()
{
    if (0 == --m_cRef)
    {
        delete this;
        return 0;
    }

    return m_cRef;
}


STDMETHODIMP CContextMenuSampleClassFactory::QueryInterface(
	REFIID riid,
    LPVOID *ppv
	)
{
    if (NULL == ppv)
	{
        return E_INVALIDARG;
	}

    *ppv = NULL;

    if (IID_IUnknown == riid)
	{
        *ppv = (LPVOID)this;
	}
    else if (IID_IClassFactory == riid)
	{
        *ppv = (IClassFactory *)this;
	}

    if (NULL != *ppv)
    {
        ((IUnknown *)(*ppv))->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}


STDMETHODIMP CContextMenuSampleClassFactory::CreateInstance(LPUNKNOWN punkOuter,
        REFIID riid, LPVOID *ppvObj)
{
    CContextMenuSample *pobjNew;

    if (NULL == ppvObj)
	{
        return E_INVALIDARG;
	}

    if (NULL != punkOuter)
	{
        return CLASS_E_NOAGGREGATION;
	}

    pobjNew = new CContextMenuSample;
    if (NULL == pobjNew)
	{
        return E_OUTOFMEMORY;
	}

    return pobjNew->QueryInterface(riid, ppvObj);
}


STDMETHODIMP CContextMenuSampleClassFactory::LockServer(
	BOOL fLock
	)
{
    UNREFERENCED_PARAMETER(fLock);

    return S_OK;
}

