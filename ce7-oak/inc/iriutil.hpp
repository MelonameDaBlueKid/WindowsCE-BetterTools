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

#ifndef __IRIUTIL_HPP_INCLUDED__
#define __IRIUTIL_HPP_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif

#include <windows.h>
#include <iri.h>
#include <auto_xxx.hxx>

#ifndef __cplusplus
#error "iriutil.hpp can only be included from C++"
#endif // !__cplusplus

namespace IriUtil
{

extern const __declspec(selectany) WCHAR c_szCoreDll[]              = L"COREDLL.DLL";
extern const __declspec(selectany) WCHAR c_szLCMapStringWFn[]       = L"LCMapStringW";

extern const __declspec(selectany) WCHAR c_szIriDll[]               = L"IRI.DLL";
extern const __declspec(selectany) WCHAR c_szIriCloseFn[]           = L"IriClose";
extern const __declspec(selectany) WCHAR c_szIriMutableCloseFn[]    = L"IriMutableClose";
extern const __declspec(selectany) WCHAR c_szIriMakeConstantFn[]    = L"IriMakeConstant";
extern const __declspec(selectany) WCHAR c_szIriCreateFromString[]  = L"IriCreateFromString";
extern const __declspec(selectany) WCHAR c_szIriGetAsString[]       = L"IriGetAsString";
extern const __declspec(selectany) WCHAR c_szIriAppendSegment[]     = L"IriAppendSegment";
extern const __declspec(selectany) WCHAR c_szIriAppendRelativeIri[] = L"IriAppendRelativeIri";
extern const __declspec(selectany) WCHAR c_szIriCopy[]              = L"IriCopy";
extern const __declspec(selectany) WCHAR c_szIriSetMetadata[]       = L"IriSetMetadata";
extern const __declspec(selectany) WCHAR c_szIriGetSegmentCount[]   = L"IriGetSegmentCount";
extern const __declspec(selectany) WCHAR c_szIriGetSegment[]        = L"IriGetSegment";
extern const __declspec(selectany) WCHAR c_szIriGetRelative[]       = L"IriGetRelative";

typedef int     (*PFNLCMAPSTRINGW)          (LCID, DWORD, LPCWSTR, int, LPWSTR, int);

typedef HRESULT (*PFNIRICLOSE)              (HIRI);
typedef HRESULT (*PFNIRIMUTABLECLOSE)       (HMUTABLEIRI);
typedef HRESULT (*PFNIRIMAKECONSTANT)       (HMUTABLEIRI,HIRI*);
typedef HRESULT (*PFNIRICREATEFROMSTRING)   (LPCWSTR,DWORD,HMUTABLEIRI*);
typedef HRESULT (*PFNIRIGETRELATIVEASSTRING)(HIRI,DWORD,DWORD,DWORD,LPWSTR,DWORD,DWORD*);
typedef HRESULT (*PFNIRIAPPENDSEGMENT)      (HMUTABLEIRI,LPCWSTR,DWORD);
typedef HRESULT (*PFNIRIAPPENDRELATIVEIRI)  (HMUTABLEIRI,HIRI,DWORD);
typedef HRESULT (*PFNIRICOPY)               (HIRI,DWORD,DWORD,DWORD,HMUTABLEIRI*);
typedef HRESULT (*PFNIRISETMETADATA)        (HMUTABLEIRI,DWORD);
typedef HRESULT (*PFNIRIGETSEGMENTCOUNT)    (HIRI,DWORD*);
typedef HRESULT (*PFNIRIGETSEGMENT)         (HIRI,DWORD,LPCWSTR*);
typedef HRESULT (*PFNIRIGETRELATIVE)        (HIRI,DWORD,DWORD,DWORD,HIRI*);

// Soft imports for IRI.DLL
//
// This class allows access to the functionality of IRI.DLL without taking a
// static dependency on it. This ability is useful for clients that determine
// at runtime whether or not security policy needs to be enforced. All public
// functions are static and operate on a protected singleton instance of the
// IriDll class.
//
class IriDll
{

public:

    // Public static members:
    //

    // NOTE: Initialization will occur automatically on the first call to an
    // IriUtil API, but the Initialize API is provided so that a client may
    // pre-load the IRI Dll for two reasions:
    //
    //      1)  Client needs to call IriUtil APIs while potentially holding the
    //          loader critical section.
    //
    //      2)  The client needs to determine whether or not the IriUtil APIs
    //          are available.
    //
    // It should NOT be called from DllMain/DllEntry because it will call the
    // LoadLibrary API.
    //
    static inline
    BOOL Initialize()
    {
        return (NULL != GetInstance());
    }

    // aka LCMapString (a COREDLL.DLL function, not an IRI.DLL function)
    static inline
    int MapStringW(LCID Locale, DWORD dwMapFlags, LPCWSTR pszSrc, int cchSrc, LPWSTR pszDest, int cchDest)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnLCMapStringW(Locale, dwMapFlags, pszSrc, cchSrc, pszDest, cchDest) : 0;
    }

    // aka IriClose
    static inline
    HRESULT Close(__in HIRI hiri)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriClose(hiri) : E_NOTIMPL;
    }

    // aka IriMutableClose
    static inline 
    HRESULT MutableClose(__in HMUTABLEIRI hmiri)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriMutableClose(hmiri) : E_NOTIMPL;
    }

    // aka IriMakeConstant
    static inline
    HRESULT MakeConstant(__in HMUTABLEIRI hmiri, __out HIRI* phiri)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriMakeConstant(hmiri, phiri) : E_NOTIMPL;
    }

    // aka IriCreateFromString
    static inline
    HRESULT CreateFromString(__in LPCWSTR pszIri, __in DWORD grfEncoding,
        __out HMUTABLEIRI* phmiri)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriCreateFromString(pszIri, grfEncoding,
            phmiri) : E_NOTIMPL;
    }

    // aka IriGetAsString
    static inline
    HRESULT GetAsString(__in HIRI hiri, __in DWORD idwStartSegment,
        __in DWORD idwEndSegment, __in DWORD grfDestinationComponents, 
        __out_ecount_opt(cchRelativeIri) LPWSTR pszRelativeIri, __in DWORD cchRelativeIri,
        __out_opt DWORD* pcchRelativeIri)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriGetAsString(hiri, idwStartSegment,
            idwEndSegment, grfDestinationComponents, pszRelativeIri,
            cchRelativeIri, pcchRelativeIri) : E_NOTIMPL;
    }
    
    // aka IriAppendSegment
    static inline
    HRESULT AppendSegment(__in HMUTABLEIRI hmiri, __in LPCWSTR pszSegment,
        DWORD grfEncoding)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriAppendSegment(hmiri, pszSegment,
            grfEncoding) : E_NOTIMPL;
    }

    // aka IriAppendRelativeIri
    static inline
    HRESULT AppendRelativeIri(__in HMUTABLEIRI hmiri, __in HIRI hiri, DWORD idwSegment)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriAppendRelativeIri(hmiri, hiri, idwSegment) 
                    : E_NOTIMPL;
    }

    // aka IriCopy
    static inline
    HRESULT Copy(__in HIRI hiri, DWORD idwStartSegment, DWORD idwEndSegment,
                 DWORD grfDestinationComponents, __out HMUTABLEIRI* phmiri)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriCopy(hiri, idwStartSegment, idwEndSegment, 
            grfDestinationComponents, phmiri) :  E_NOTIMPL;
    }

    // aka IriSetMetadata
    static inline
    HRESULT SetMetadata(__in HMUTABLEIRI hmiri, DWORD grfMetadata)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriSetMetadata(hmiri, grfMetadata) :  E_NOTIMPL;
    }

    // aka IriGetSegmentCount
    static inline
    HRESULT GetSegmentCount(__in HIRI hiri, __out DWORD* pcdwSegments)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriGetSegmentCount(hiri, pcdwSegments) : E_NOTIMPL;
    }

    // aka IriGetSegment
    static inline
    HRESULT GetSegment(__in HIRI hiri, DWORD idwSegment, __out LPCWSTR* ppszSegment)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriGetSegment(hiri, idwSegment, ppszSegment) : E_NOTIMPL;
    }

    // aka IriGetRelative
    static inline
    HRESULT GetRelative(__in HIRI hiri, DWORD idwStartSegment, DWORD idwLastSegment, 
                       DWORD grfDestinationComponents, __out HIRI* phiriRelative)
    {
        IriDll* pIri = GetInstance();
        return pIri ? pIri->m_pfnIriGetRelative(hiri, idwStartSegment, idwLastSegment, 
                                                grfDestinationComponents, phiriRelative) : E_NOTIMPL;
    }

protected:

    // Private members:
    //

    IriDll() :
        m_pfnLCMapStringW(NULL),
        m_hIriDll(NULL),
        m_pfnIriClose(NULL),
        m_pfnIriMutableClose(NULL),
        m_pfnIriMakeConstant(NULL),
        m_pfnIriCreateFromString(NULL),
        m_pfnIriGetAsString(NULL),
        m_pfnIriAppendSegment(NULL),
        m_pfnIriAppendRelativeIri(NULL),
        m_pfnIriCopy(NULL),
        m_pfnIriSetMetadata(NULL),
        m_pfnIriGetSegmentCount(NULL),
        m_pfnIriGetSegment(NULL),
        m_pfnIriGetRelative(NULL)
    {
        // Load COREDLL.DLL
        
        HINSTANCE hCoreDll = GetModuleHandle(c_szCoreDll);
        if(hCoreDll)
        {
            m_pfnLCMapStringW = (PFNLCMAPSTRINGW)GetProcAddress(hCoreDll, c_szLCMapStringWFn);
        }

        if(m_pfnLCMapStringW)
        {
            // Load IRI.DLL

            m_hIriDll = LoadLibrary(c_szIriDll);

            if(m_hIriDll)
            {
                m_pfnIriClose = (PFNIRICLOSE)GetProcAddress(m_hIriDll, c_szIriCloseFn);

                m_pfnIriMutableClose = (PFNIRIMUTABLECLOSE)GetProcAddress(m_hIriDll,
                    c_szIriMutableCloseFn);

                m_pfnIriMakeConstant = (PFNIRIMAKECONSTANT)GetProcAddress(m_hIriDll,
                    c_szIriMakeConstantFn);

                m_pfnIriCreateFromString = (PFNIRICREATEFROMSTRING)GetProcAddress(
                    m_hIriDll, c_szIriCreateFromString);

                m_pfnIriGetAsString = (PFNIRIGETRELATIVEASSTRING)GetProcAddress(m_hIriDll,
                    c_szIriGetAsString);

                m_pfnIriAppendSegment = (PFNIRIAPPENDSEGMENT)GetProcAddress(m_hIriDll,
                    c_szIriAppendSegment);

                m_pfnIriAppendRelativeIri = (PFNIRIAPPENDRELATIVEIRI)GetProcAddress(m_hIriDll,
                    c_szIriAppendRelativeIri);

                m_pfnIriCopy = (PFNIRICOPY)GetProcAddress(m_hIriDll, c_szIriCopy);

                m_pfnIriSetMetadata = (PFNIRISETMETADATA)GetProcAddress(m_hIriDll, c_szIriSetMetadata);

                m_pfnIriGetSegmentCount = (PFNIRIGETSEGMENTCOUNT)GetProcAddress(m_hIriDll, c_szIriGetSegmentCount);

                m_pfnIriGetSegment = (PFNIRIGETSEGMENT)GetProcAddress(m_hIriDll, c_szIriGetSegment);

                m_pfnIriGetRelative = (PFNIRIGETRELATIVE)GetProcAddress(m_hIriDll, c_szIriGetRelative);

                if(!m_pfnIriClose || !m_pfnIriMutableClose || !m_pfnIriMakeConstant ||
                   !m_pfnIriCreateFromString || !m_pfnIriGetAsString || !m_pfnIriAppendSegment ||
                   !m_pfnIriAppendRelativeIri || !m_pfnIriCopy || !m_pfnIriSetMetadata || 
                   !m_pfnIriGetSegmentCount || !m_pfnIriGetSegment || !m_pfnIriGetRelative)
                {
                    ASSERT(0);
                    FreeLibrary(m_hIriDll);
                    m_hIriDll = NULL;
                }
            }
        }
    }

    ~IriDll()
    {
        if(m_hIriDll)
        {
            FreeLibrary(m_hIriDll);
        }
    }

    inline BOOL Validate()
    {
        return (NULL != m_hIriDll);
    }

    HINSTANCE m_hIriDll;

    PFNIRICLOSE                 m_pfnIriClose;
    PFNIRIMUTABLECLOSE          m_pfnIriMutableClose;
    PFNIRIMAKECONSTANT          m_pfnIriMakeConstant;
    PFNIRICREATEFROMSTRING      m_pfnIriCreateFromString;
    PFNIRIGETRELATIVEASSTRING   m_pfnIriGetAsString;
    PFNIRIAPPENDSEGMENT         m_pfnIriAppendSegment;
    PFNIRIAPPENDRELATIVEIRI     m_pfnIriAppendRelativeIri;
    PFNIRICOPY                  m_pfnIriCopy;
    PFNIRISETMETADATA           m_pfnIriSetMetadata;
    PFNIRIGETSEGMENTCOUNT       m_pfnIriGetSegmentCount;
    PFNIRIGETSEGMENT            m_pfnIriGetSegment;
    PFNIRIGETRELATIVE           m_pfnIriGetRelative;

    PFNLCMAPSTRINGW             m_pfnLCMapStringW;

protected:

    // Private static members:
    //

    static IriDll* s_pInstance;

    static IriDll* GetInstance()
    {
        if(!s_pInstance)
        {
            IriDll* pInstance = new IriDll();
            if(pInstance && pInstance->Validate())
            {
                // Detect a race with another thread calling GetInstance
                // simultaneously.
                if(NULL != InterlockedCompareExchangePointer(&s_pInstance,
                    pInstance, NULL))
                {
                    // Another thread initialized s_pInstance first, delete
                    // the object that this thread created.
                    delete pInstance;
                }

                ASSERT(s_pInstance);
            }
        }

        return s_pInstance;
    }
};

/* static */ __declspec(selectany) IriDll* IriDll::s_pInstance;

typedef ce::auto_xxx<HIRI, HRESULT (__cdecl*)(const HIRI), IriDll::Close, NULL> auto_hiri;
typedef ce::auto_xxx<HMUTABLEIRI, HRESULT (__cdecl*)(const HMUTABLEIRI), IriDll::MutableClose, NULL> auto_hmutableiri;

}; // end namespace IriUtil

#endif // __IRIUTIL_HPP_INCLUDED__
