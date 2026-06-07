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
#include "common.h"

// Global Count of references to this DLL - defined in Main.cpp
extern UINT g_cDLLRefCount;


///////////////////////////////////////////////////////////////////////////////
// MyClassFactory
//
//  This is a simple implementation of a class which is used to instantiate
//  another class... specifically the Inbox MenuExtension COM class defined in 
//  InboxMenuExt.cpp
//
//  This class is instantiated/constructed by DllGetClassObject (see Main.cpp)
//


MyClassFactory::MyClassFactory(ExtensionType extensionType) :
m_cRef(1)
{
    m_ExtensionType = extensionType;
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
        hr = E_NOINTERFACE;
        goto Error;
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
        hr = CLASS_E_NOAGGREGATION;
        goto Error;
    }

    //
    // Call MenuExtension::Create - this is where the MenuExtension is 
    // actually created
    //
    hr = MenuExtension::Create(&pows, m_ExtensionType);
    CHR(hr);
    CPR(pows);
        
    hr = pows->QueryInterface(riid, ppObject);
    CHR(hr);
    CPR(ppObject);

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
