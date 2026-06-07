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

