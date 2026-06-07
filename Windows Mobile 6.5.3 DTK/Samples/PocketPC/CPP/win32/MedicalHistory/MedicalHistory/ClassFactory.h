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
extern ULONG g_dwDLLRefCount;

// **************************************************************************
// MedicalHistoryClassFactory
//
//  This is a simple implementation of a class which is used to instantiate
//  another class... specifically the MedicalHistoryMenuExtension COM class
//
//  This class is instantiated/constructed by DllGetClassObject (see Main.cpp)
//
class MedicalHistoryClassFactory : public IClassFactory
{
private:
    long m_cRef;

public:
    MedicalHistoryClassFactory();
    virtual ~MedicalHistoryClassFactory();

    // IUnknown interface
    STDMETHODIMP QueryInterface(REFIID riid, void** ppObject);

    STDMETHODIMP_(ULONG) AddRef(); 
    STDMETHODIMP_(ULONG) Release();

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppObject);
    STDMETHODIMP LockServer(BOOL fLock);
};
