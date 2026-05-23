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
/***********************************************************
    ehm.h
    Error handling macros

Author(s): KKennedy (derived from many sources)

    {x,}{CVD}{H,P,B,W}R{A,}{Ex,}
    C=check, V=verify, D=dump
    H=hresult, P=ptr, B=bool, W=windows
    R=result
    A=assert
    Ex=extended version
    x=wart, suppresses assert due to practical pblm (obsolete!)

    C checks, and bails on failure after setting hr
        A adds an ASSERT before the bail
    V checks, and ASSERTs on failure
    D checks, and SPEWs on failure
    (yes, the 'A' is inconsistent)
    Ex adds overriding failure-case 'E_*' of user's choice
    x is obsolete, you shouldn't use it

    n.b. we only have some of the above implemented (the ones we've needed
    so far...)

    if you're an unlucky soul and run into a label collision, use the
    _ehmErrorLab mechanism (see below).

    _ehmOnAssertionFail 
        Allows custom processing of a failure in macros that assert.
        As defined here, this maps to OnAssertionFail().
        By defining this earlier, you could implement custom logging of the failure

    _ehmOnFail
        Allows custom processing of a failure in macros that don't assert. 
        As defined here, this maps to nothing.
        By defining this earlier, you could implement custom logging of the failure.


    UTCore.H - takes advantage of both _ehmOnFail and _ehmOnAssertionFail 
        extensions to provide slightly different behavior and enable logging 
        for unit tests.  

    see also the document: <todo: ptr to in kk's ehm .doc>

NOTES
    we use the "if (0,fResult), while (0,0)" style in order to suppress W4 warnings.  the PF_EXPR wraps that to keep prefix happy.



*/
#ifndef _EHM_H_
#define _EHM_H_

#include <guts_cmn.h>

// Define type checks for parameters of EHM macros
// 
// Disabled if:
//              !__cplusplus    can't use templates in C
//              _PREFAST_       disabled in prefast builds, because type checks don't allow prefast
//                              to make the conclusion about the NULL-ness of pointers passed to the CPR macro
//
#if defined(__cplusplus) && !defined(_PREFAST_)

extern "C++" {

#include <static_assert.hxx>

namespace ce
{
    template<typename T, typename Fn, Fn fnClose, T _Invalid, typename copy_traits>
    class auto_xxx;
}

namespace Typecheck
{
    template <typename T, typename U>
    struct IsSameType
    {
        enum { Value = false };
    };

    template <typename T>
    struct IsSameType<T, T>
    {
        enum { Value = true };
    };

    template <typename T>
    struct IsPointerType
    {
        enum { Value = false };
    };

    template <typename T>
    struct IsPointerType<T *>
    {
        enum { Value = true };
    };

    template <typename T, typename U>
    struct IsConvertibleToType
    {
        // preparation
        typedef char ConvertibleResultType;
        struct UnconvertibleResultType
        {
            char m_internal[2];
        };

        // one of these functions is chosen depending on whether T is convertible to U
        static ConvertibleResultType    Test(U);
        static UnconvertibleResultType  Test(...);

        static T MakeT();

        // actual test
        enum { Value = sizeof(Test(MakeT())) == sizeof(ConvertibleResultType) };
    };

    template <typename T>
    struct IsConvertibleToPointerType
    {
        enum { Value = IsConvertibleToType<T, void *>::Value
                    || IsConvertibleToType<T, void const *>::Value };
    };

    template <typename T>
    struct IsPodType
    {
        enum { Value = __is_pod(T) };  // change to tr1::is_pod when TR1 is supported
    };

    // Windows handle type is defined as void *, or pointer to POD containing a single int
    template <typename T>
    struct IsHandleType
    {
        enum { Value = IsSameType<void *, T>::Value
                       || (IsPointerType<T>::Value
                           && IsPodType<typename DerefPointer<T>::Type>::Value
                           && SizeOf<typename DerefPointer<T>::Type>::Value == sizeof(int)) };
    };

    template <typename T>
    struct DerefPointer
    {
        typedef T Type;
    };

#define DEFINE_DEREF_POINTER(PointerT, T)   \
    template <typename T>                   \
    struct DerefPointer<PointerT>           \
    {                                       \
        typedef T Type;                     \
    }                                       \

    DEFINE_DEREF_POINTER(T *, T);
    DEFINE_DEREF_POINTER(T * const, T);
    DEFINE_DEREF_POINTER(T * volatile, T);
    DEFINE_DEREF_POINTER(T * const volatile, T);

#undef DEFINE_DEREF_POINTER

    template <typename T>
    struct SizeOf
    {
        enum { Value = sizeof(T) };
    };

    template <>
    struct SizeOf<void>
    {
        enum { Value = 0 };
    };

    // Check parameter type for CBR
    // Valid types: bool, BOOL (int)
    // Added due to frequent use: DWORD (unsigned long), pointer
    // Warning for future changes: make sure it still rejects HRESULT (long).
    //
    template <typename T>
    T const & CheckCbrType(T const & arg)
    {
        STATIC_ASSERT((IsSameType<bool, T>::Value
                    || IsSameType<BOOL, T>::Value
                    || IsSameType<DWORD, T>::Value
                    || IsConvertibleToPointerType<T>::Value));
        return arg;
    }

    // Basic check of the parameter type for CBR
    // Designed to catch CBR(HRESULT)
    //
    template <typename T>
    T const & CheckCbrTypeBasic(T const & arg)
    {
        STATIC_ASSERT((!IsSameType<HRESULT, T>::Value));
        return arg;
    }

    // Check parameter type for CPR
    // Valid types: pointer or smart pointer
    //
    template <typename T>
    T const & CheckCprType(T const & arg)
    {
        STATIC_ASSERT(IsConvertibleToPointerType<T>::Value);
        return arg;
    }

    // Check parameter type for CHR
    // Valid types: HRESULT
    //
    template <typename T>
    T const & CheckChrType(T const & arg)
    {
        STATIC_ASSERT((IsSameType<HRESULT, T>::Value));
        return arg;
    }

    // Basic check of the parameter type for CHR
    // Designed to catch CHR(BOOL) and CHR(bool)
    //
    template <typename T>
    T const & CheckChrTypeBasic(T const & arg)
    {
        STATIC_ASSERT((!IsSameType<BOOL, T>::Value
                    && !IsSameType<bool, T>::Value));
        return arg;
    }

    // Check parameter type for CWR
    // Valid types: int, DWORD, handle, ce::auto_xxx<handle>
    // Refer to public\common\sdk\inc\winnt.h for a definition of the handle type.
    //
    template <typename T>
    struct CheckCwrTypeImpl
    {
        enum { Value = IsSameType<int, T>::Value
                    || IsSameType<DWORD, T>::Value
                    || IsHandleType<T>::Value };
    };

    template<typename T, typename Fn, Fn fnClose, T _Invalid, typename copy_traits>
    struct CheckCwrTypeImpl<ce::auto_xxx<T, Fn, fnClose, _Invalid, copy_traits> >
    {
        enum { Value = IsHandleType<T>::Value };
    };

    template <typename T>
    T const & CheckCwrType(T const & arg)
    {
        STATIC_ASSERT(CheckCwrTypeImpl<T>::Value);
        return arg;
    }
}

}  // extern "C++"

#if !defined(NO_CHECKED_EHM)

// Define macros for type checking
//
#define CHECK_CBR_TYPE(x)       \
    Typecheck::CheckCbrType(x)  \

#define CHECK_CPR_TYPE(x)       \
    Typecheck::CheckCprType(x)  \

#define CHECK_CHR_TYPE(x)       \
    Typecheck::CheckChrType(x)  \

#define CHECK_CWR_TYPE(x)       \
    Typecheck::CheckCwrType(x)  \

#else // !NO_CHECKED_EHM

// Define basic type checks if NO_CHECKED_EHM is set.
// This is done by NO_CHECKED_EHM=1 setting in the sources file.
// If NO_CHECKED_EHM is not set the full type checking will be used.
//
#define CHECK_CBR_TYPE(x)           \
    Typecheck::CheckCbrTypeBasic(x) \

#define CHECK_CHR_TYPE(x)           \
    Typecheck::CheckChrTypeBasic(x) \

#endif // !NO_CHECKED_EHM

#endif // __cplusplus && !_PREFAST_

#ifndef CHECK_CBR_TYPE
#define CHECK_CBR_TYPE(x) (x)
#endif

#ifndef CHECK_CPR_TYPE
#define CHECK_CPR_TYPE(x) (x)
#endif

#ifndef CHECK_CHR_TYPE
#define CHECK_CHR_TYPE(x) (x)
#endif

#ifndef CHECK_CWR_TYPE
#define CHECK_CWR_TYPE(x) (x)
#endif

// 99% of the time ehm.h "just works".  however 1% of the time the "Error"
// label is already in use (e.g. for some other macro package).  if you hit
// that, do this:
//      #define _ehmErrorLab    EhmError
//      #include <ehm.h>
// ... and then use EhmError as your label.  it may seem a bit silly to add
// this extra indirection vs. just use EhmError always, but given that it's
// a 99%/1%, it seems worthwhile.
//
// our suggestion is that custom clients standardize on "EhmError", but if
// need be, they can choose whatever they want.
#ifndef _ehmErrorLab
#define _ehmErrorLab   Error
#endif

// If you define the value for _ehmOnAssertionFail before #including ehm.h you
// can change what _ehmOnAssertionFail does
// Remember this affects all xxxA macros
#ifdef USE_REPLACEABLE_EHM
#ifndef _ehmOnAssertionFail
#define _ehmOnAssertionFail(eType, dwCode, pszFile, ulLine, pszMessage) \
         OnAssertionFail(eType, dwCode, pszFile, ulLine, pszMessage)
#endif
#else
#ifdef _ehmOnAssertionFail
#error Define USE_REPLACEABLE_EHM to use _ehmOnAssertionFail
#endif
#define _ehmOnAssertionFail(eType, dwCode, pszFile, ulLine, pszMessage) TRUE
#endif

// If you define the value for _ehmOnFail before #including ehm.h you
// can change what _ehmOnFail does
// Remember this affects all non-A macros
#ifndef _ehmOnFail
#define _ehmOnFail(eType, dwCode, pszFile, ulLine, pszMessage) __noop
#endif

typedef enum
    {
    eHRESULT,
    eBOOL,
    ePOINTER,
    eWINDOWS
    } eCodeType;

#ifdef __cplusplus
// The following functions should always have C linkage
// because they can be used from both C and C++ code.
extern "C"
{
#endif

BOOL ShouldBreakOnAssert();
BOOL SetBreakOnAssert(BOOL fBreakOnAssert);
BOOL OnAssertionFail(eCodeType eType, DWORD dwCode, const TCHAR* pszFile, unsigned long ulLine, const TCHAR* pszMessage);

#ifdef __cplusplus
}
#endif

// Check HRESULT
    #define _CHREx0(hResult) \
        do { \
            hr = CHECK_CHR_TYPE(hResult); \
            if(FAILED(hr)) \
            { \
                __pragma(warning(push)) \
                __pragma(warning(disable:4127)) \
                _ehmOnFail(eHRESULT, hr, TEXT(__FILE__), __LINE__, TEXT("CHR(") TEXT( # hResult ) TEXT(")")); \
                __pragma(warning(pop)) \
                goto _ehmErrorLab; \
            } \
        } while (0,0)

    #define _CHR(hResult, hrFail) \
        do { \
            hr = CHECK_CHR_TYPE(hResult); \
            if(FAILED(hr)) \
            { \
                hr = (hrFail); \
                __pragma(warning(push)) \
                __pragma(warning(disable:4127)) \
                _ehmOnFail(eHRESULT, hr, TEXT(__FILE__), __LINE__, TEXT("CHR(") TEXT( # hResult ) TEXT(")")); \
                __pragma(warning(pop)) \
                goto _ehmErrorLab; \
            } \
        } while (0,0)

// Check pointer result
    #define _CPR(p, hrFail) \
        do { \
            if (PF_EXPR(!CHECK_CPR_TYPE(p))) \
            { \
                hr = (hrFail); \
                __pragma(warning(push)) \
                __pragma(warning(disable:4127)) \
                _ehmOnFail(ePOINTER, hr, TEXT(__FILE__), __LINE__, TEXT("CPR(") TEXT( # p ) TEXT(")")); \
                __pragma(warning(pop)) \
                goto _ehmErrorLab; \
             } \
         } while (0,0)

// Check boolean result
    #define _CBR(fResult, hrFail) \
        do { \
            if (PF_EXPR(!CHECK_CBR_TYPE(fResult))) \
            { \
                hr = (hrFail); \
                __pragma(warning(push)) \
                __pragma(warning(disable:4127)) \
                _ehmOnFail(eBOOL, hr, TEXT(__FILE__), __LINE__, TEXT("CBR(") TEXT( # fResult ) TEXT(")")); \
                __pragma(warning(pop)) \
                goto _ehmErrorLab; \
            } \
        } while(0,0)

// Check windows result.  Exactly like CBR for the non-Asserting case - BUT we log differently
#define _CWR(fResult, hrFail) \
    do { \
        if (PF_EXPR(!CHECK_CWR_TYPE(fResult))) \
        { \
            hr = (hrFail); \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            _ehmOnFail(eWINDOWS, ::GetLastError(), TEXT(__FILE__), __LINE__, TEXT("CWR(") TEXT( # fResult ) TEXT(")")); \
            __pragma(warning(pop)) \
            goto _ehmErrorLab; \
        } \
    } while(0,0)


// The above macros with Asserts when the condition fails
#ifdef DEBUG

#define _CHRAEx0(hResult) \
    do { \
        hr = CHECK_CHR_TYPE(hResult); \
        if(FAILED(hr)) \
            { \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(eHRESULT, hr, TEXT(__FILE__), __LINE__, TEXT("CHRA(") TEXT( # hResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            goto _ehmErrorLab; \
            } \
        } \
    while (0,0)

#define _CHRA(hResult, hrFail) \
    do { \
        hr = CHECK_CHR_TYPE(hResult); \
        if(FAILED(hr)) \
            { \
            hr = (hrFail); \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(eHRESULT, hr, TEXT(__FILE__), __LINE__, TEXT("CHRA(") TEXT( # hResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            goto _ehmErrorLab; \
            } \
        } \
    while (0,0)

#define _CPRA(p, hrFail) \
    do  { \
        if (PF_EXPR(!CHECK_CPR_TYPE(p))) \
            { \
            hr = (hrFail); \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(ePOINTER, hr, TEXT(__FILE__), __LINE__, TEXT("CPRA(") TEXT( # p ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            goto _ehmErrorLab; \
            } \
        } \
    while (0,0)

#define _CBRA(fResult, hrFail) \
    do  { \
        if (PF_EXPR(!CHECK_CBR_TYPE(fResult))) \
            { \
            hr = (hrFail); \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(eBOOL, hr, TEXT(__FILE__), __LINE__, TEXT("CBRA(") TEXT( # fResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            goto _ehmErrorLab; \
            } \
        } \
    while (0,0)

#define _CWRA(fResult, hrFail) \
    do  { \
        if (PF_EXPR(!CHECK_CWR_TYPE(fResult))) \
            { \
            hr = (hrFail); \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(eWINDOWS, ::GetLastError(), TEXT(__FILE__), __LINE__, TEXT("CWRA(") TEXT( # fResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            goto _ehmErrorLab; \
            } \
        } \
    while (0,0)

#define VBR(fResult) \
    do  { \
        if (PF_EXPR(!CHECK_CBR_TYPE(fResult))) \
            { \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(eBOOL, 0, TEXT(__FILE__), __LINE__, TEXT("VBR(") TEXT( # fResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            } \
        } \
    while (0,0)

#define VPR(fResult) \
    do  { \
        if (PF_EXPR(!CHECK_CPR_TYPE(fResult))) \
            { \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(ePOINTER, 0, TEXT(__FILE__), __LINE__, TEXT("VPR(") TEXT( # fResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            } \
        } \
    while (0,0)


// Verify Windows Result
#define VWR(fResult) \
    do  { \
        if (!(PF_EXPR(NULL != CHECK_CWR_TYPE(fResult)))) \
            { \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(eWINDOWS, ::GetLastError(), TEXT(__FILE__), __LINE__, TEXT("VWR(") TEXT( # fResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            } \
        } \
    while (0,0)


// Verify HRESULT (careful not to modify hr)
#define VHR(hResult) \
    do  { \
        HRESULT _EHM_hrTmp = CHECK_CHR_TYPE(hResult); \
        if(FAILED(_EHM_hrTmp)) \
            { \
            __pragma(warning(push)) \
            __pragma(warning(disable:4127)) \
            if(_ehmOnAssertionFail(eHRESULT, _EHM_hrTmp, TEXT(__FILE__), __LINE__, TEXT("VHR(") TEXT( # hResult ) TEXT(")"))) \
                { \
                DebugBreak(); \
                } \
            __pragma(warning(pop)) \
            } \
        } \
    while (0,0)

// NOTE: because the Dxx macros are intended for DEBUG spew - there is no logging extensibility
// make sure you keep the xTmp, can only eval arg 1x
// todo: dump GetLastError in DWR
#define DWR(fResult) \
    do { if (PF_EXPR(!CHECK_CWR_TYPE(fResult))) {DEBUGMSG(1, (TEXT("DWR(") TEXT( # fResult ) TEXT(")\r\n") ));}} while (0,0)
#define DHR(hResult) \
    do { HRESULT hrTmp = CHECK_CHR_TYPE(hResult); if(FAILED(hrTmp)) {DEBUGMSG(1, (TEXT("DHR(") TEXT( # hResult ) TEXT(")=0x%x\r\n"), hrTmp));}} while (0,0)
#define DPR     DWR     // tmp
#define DBR     DWR     // tmp

#define CHRA(e) _CHRAEx0(e)
#define CPRA(e) _CPRA(e, E_OUTOFMEMORY)
#define CBRA(e) _CBRA(e, E_FAIL)
#define CWRA(e) _CWRA(e, E_FAIL)
#define CHRAEx(e, hrFail) _CHRA(e, hrFail)
#define CPRAEx(e, hrFail) _CPRA(e, hrFail)
#define CBRAEx(e, hrFail) _CBRA(e, hrFail)
#define CWRAEx(e, hrFail) _CWRA(e, hrFail)
#else
#define CHRA CHR
#define CPRA CPR
#define CBRA CBR
#define CWRA CWR
#define CHRAEx CHREx
#define CPRAEx CPREx
#define CBRAEx CBREx
#define CWRAEx CWREx
#define VHR(x) (CHECK_CHR_TYPE(x))
#define VPR(x) (CHECK_CPR_TYPE(x))
#define VBR(x) (CHECK_CBR_TYPE(x))
#define VWR(x) (CHECK_CWR_TYPE(x))
#define DHR(x) (CHECK_CHR_TYPE(x))
#define DPR(x) (CHECK_CPR_TYPE(x))
#define DBR(x) (CHECK_CBR_TYPE(x))
#define DWR(x) (CHECK_CWR_TYPE(x))
#endif

#define CHR(e) _CHREx0(e)
#define CPR(e) _CPR(e, E_OUTOFMEMORY)
#define CPP(e) _CPR(e, E_INVALIDARG)
#define CBR(e) _CBR(e, E_FAIL)
#define CWR(e) _CWR(e, E_FAIL)
#define CHREx(e, hrFail) _CHR(e, hrFail)
#define CPREx(e, hrFail) _CPR(e, hrFail)
#define CBREx(e, hrFail) _CBR(e, hrFail)
#define CWREx(e, hrFail) _CWR(e, hrFail)

// obsolete (but still in use)
// - work around various pseudo-pblms:
//  partial images, CEPC no-radio, etc.
// - also things that we want to know about in dev, but not in QA/stress:
//  an e.g. is our DoVerb stuff, there are 'good' failures (END when no call,
// or TALK w/ 0 entries) and 'bad' failures (e.g. TAPI returns an error), we
// don't want to int3 during stress but we do want to on our dev machines
//
// eventually we'll make these do "if (g_Assert) int3;", then we
// can run w/ g_Assert on for dev and off for stress.
#define xCHRA   CHR     // should be CHRA but...
#define xCPRA   CPR     // should be CPRA but...
#define xCBRA   CBR     // should be CBRA but...
#define xCWRA   CWR     // should be CWRA but...
#define xVHR    DHR     // should be VHR  but...
#define xVPR    DPR     // should be VPR  but...
#define xVBR    DBR     // should be VBR  but...
#define xVWR    DWR     // should be VWR  but...

#endif // _EHM_H_
