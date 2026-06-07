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
/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF

  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO

  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A

  PARTICULAR PURPOSE.

  

    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/

// ****************************************************************************
// FILE: dvorak_classfactory.h
// ABSTRACT: Dvorak Input Method COM Class Factory CClassFactory header.
// **************************************************************************** 
 
#ifndef __IMCF_H__
#define __IMCF_H__



class CClassFactory : public IClassFactory
{
public:

    //
    // Ctor, Dtor
    //

    CClassFactory(REFCLSID rclsid);
    virtual ~CClassFactory();


    //
    // IUnknown methods
    //

    STDMETHOD(QueryInterface) (REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG,AddRef) (VOID);
    STDMETHOD_(ULONG,Release) (VOID);


    //
    // IClassFactory methods
    //

    STDMETHOD(CreateInstance) (IUnknown FAR* pUnkOuter, REFIID riid,
                               LPVOID FAR *ppunkObject);
    STDMETHOD(LockServer) (BOOL fLock);


protected:

    ULONG m_cRef;
    CLSID m_clsid;

};



#endif // __IMCF_H__
