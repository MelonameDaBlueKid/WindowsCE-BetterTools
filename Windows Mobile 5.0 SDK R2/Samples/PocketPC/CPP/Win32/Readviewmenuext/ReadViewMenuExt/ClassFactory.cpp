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
#include "common.h"

// Global Count of references to this DLL - defined in Main.cpp
extern UINT g_cDLLRefCount;

MyClassFactory::MyClassFactory() :
m_cRef(1)
{
}

MyClassFactory::~MyClassFactory()
{
}

STDMETHODIMP_(ULONG) MyClassFactory::AddRef() 
{ 
    m_cRef++; 
    return m_cRef; 
}

STDMETHODIMP_(ULONG) MyClassFactory::Release()
{   
    m_cRef--; 
    if(m_cRef > 0) 
    { 
        return(m_cRef); 
    } 
    delete this; 
    return 0; 
}

HRESULT MyClassFactory::QueryInterface(REFIID riid, void** ppObject)
{
    HRESULT hr = S_OK;

    if(riid == IID_IUnknown || riid == IID_IClassFactory)
    {
        *ppObject= (IClassFactory*)this;
    }
    else
    {
        CHR(E_NOINTERFACE);
    }

    AddRef();

Error:
    return(hr);
}

HRESULT MyClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppObject)
{
    HRESULT hr = S_OK;
    IObjectWithSite* pows = NULL;

    *ppObject = NULL;

    if(pUnkOuter != NULL)
    {
        CHR(CLASS_E_NOAGGREGATION);
    }

    hr = MenuExtension::Create(&pows);
    CHR(hr);
    
    hr = pows->QueryInterface(riid, ppObject);
    CHR(hr);

Error:
    RELEASE_OBJ(pows);
    return hr;
}

HRESULT MyClassFactory::LockServer(BOOL fLock)
{
    if(fLock)
    {
        g_cDLLRefCount++;
    }
    else
    {
        g_cDLLRefCount--;
    }
    return(S_OK);
}
