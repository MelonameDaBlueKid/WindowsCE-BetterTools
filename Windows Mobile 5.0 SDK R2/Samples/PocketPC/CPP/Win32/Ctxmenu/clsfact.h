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
// CLSFACT.H - class definition for CContextMenuSampleClassFactory

#pragma once

#pragma warning(push, 3)
#include <windows.h>
#include <objbase.h>
#pragma warning(pop)
#pragma warning(disable: 4514) // unreferenced inline/local function removed
#pragma warning(disable: 4710) // function not inlined


class CContextMenuSampleClassFactory : public IClassFactory
{

public:
    // constructors
    CContextMenuSampleClassFactory();

    // destructor
    ~CContextMenuSampleClassFactory();

    // IUnknown methods
    STDMETHOD (QueryInterface) (REFIID riid, LPVOID *ppv);
    STDMETHOD_(ULONG, AddRef)  (void);
    STDMETHOD_(ULONG, Release) (void);

    // IClassFactory methods
    STDMETHOD (CreateInstance) (LPUNKNOWN punkOuter, REFIID riid,
            LPVOID *ppvObj);
    STDMETHOD (LockServer)     (BOOL fLock);

protected:
    ULONG m_cRef;

};

