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
// CTXMENU.H - class definition for CContextMenuSample

#pragma once

#pragma warning(push, 3)
#include <windows.h>
#include <objbase.h>
#pragma warning(pop)
#pragma warning(disable: 4514) // unreferenced inline/local function removed


class CContextMenuSample : public IContextMenu, IObjectWithSite
{   

public:
    // constructors
    CContextMenuSample();

    // destructor
    ~CContextMenuSample();

    // IUnknown methods
    STDMETHOD (QueryInterface) (REFIID riid, LPVOID *ppv);
    STDMETHOD_(ULONG, AddRef)  (void);
    STDMETHOD_(ULONG, Release) (void);

    // IContextMenu methods
    STDMETHOD (GetCommandString) (UINT idCmd, UINT uFlags, UINT *pwReserved,
        LPSTR pszName, UINT cchMax);
    STDMETHOD (InvokeCommand)  (LPCMINVOKECOMMANDINFO pici);
    STDMETHOD (QueryContextMenu) (HMENU hmenu, UINT indexMenu, UINT idCmdFirst,
        UINT idCmdLast, UINT uFlags);

    // IObjectWithSite methods
    STDMETHOD (GetSite) (REFIID riid, void **ppvSite);
    STDMETHOD (SetSite) (IUnknown *pUnkSite);

    // CContextMenuSample methods
    // None

protected:
    ULONG    m_cRef;            // reference count
    IUnknown *m_punkSite;       // site (owner) pointer

};

