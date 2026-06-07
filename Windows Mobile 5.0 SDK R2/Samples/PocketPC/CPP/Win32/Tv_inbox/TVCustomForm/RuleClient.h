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

class CRuleClient : public IMailRuleClient
{
public:
    CRuleClient();
    ~CRuleClient();
    
    // IUnknown
    STDMETHOD (QueryInterface)(REFIID iid, LPVOID *ppv);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    // IMailRuleClient
    MAPIMETHOD(Initialize)(
            IMsgStore *pMsgStore,
            MRCACCESS *pmaDesired
            );
            
    MAPIMETHOD(ProcessMessage)(
            IMsgStore *pMsgStore, 
            ULONG cbMsg,
            LPENTRYID lpMsg,
            ULONG cbDestFolder,
            LPENTRYID lpDestFolder,
            ULONG *pulEventType,
            MRCHANDLED *pHandled
            );

private:
    long m_cRef;
};

class CFactory : public IClassFactory
{
public:
    CFactory();
    ~CFactory();
    
    // IUnknown
    STDMETHOD (QueryInterface)(REFIID iid, LPVOID *ppv);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    // IClassFactory interfaces
    STDMETHOD (CreateInstance)(IUnknown *pUnknownOuter, const IID& iid, LPVOID *ppv);
    STDMETHOD (LockServer)(BOOL bLock);

private:
    long m_cRef;
};

