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

#pragma once

class MyClassFactory : public IClassFactory
{
    private:
    int m_cRef;
    ExtensionType m_ExtensionType;
    
    public:
    MyClassFactory(ExtensionType extensionType);
    virtual ~MyClassFactory();

    ///////////////////////////////////////////////////////////////////////////
    // IUnknown interface Methods
    //
    STDMETHODIMP QueryInterface(REFIID riid, void** ppObject);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    //
    ///////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////
    // IClassFactory Interface Methods
    //
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppObject);
    STDMETHODIMP LockServer(BOOL fLock);
    //
    ///////////////////////////////////////////////////////////////////////////
    
};

