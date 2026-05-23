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

#ifdef _PREFAST_
//
// Standard Naming:     PF_*
//                  Keep it SHORT
//
// Current version of PREFast chokes on "if (!(0,0))" so we
// wrote these MACRO helpers.
//
// The reason we have the (0,fResult) thing to begin with 
// (rather than just 'fResult') is that the latter causes warnings 
// "constant in conditional expr" for things like "if (1) ..." and 
// "if (0) ..." (which are what ASSERTs and even non-ASSERTs 
// can sometimes end up generating in a macro-laden world).
//
    #pragma warning(disable: 4127)

#if !defined(PF_EXPR)
#define PF_EXPR(fResult)            (fResult)
#endif // !PF_EXPR

#if !defined(PF_ASSUME)
#define PF_ASSUME( cond )           __assume(cond)
#endif // !PF_ASSUME

    //
    // NOTE!  PF_ASSUME_NOTNULL will be turned off one day
    // It should only be used to workaround the PREfast bug
    // that doesn't recognize __notnull in C++ member functions
    //
#if !defined(PF_ASSUME_NOTNULL)
    #define PF_ASSUME_NOTNULL( ptr )    __assume(NULL != ptr)
#endif // !PF_ASSUME_NOTNULL

#else

#if !defined(PF_EXPR)
    #define PF_EXPR(fResult)            (0,(fResult))
#endif // !PF_EXPR

#if !defined(PF_ASSUME)
    #define PF_ASSUME( cond )           ASSERT(cond)
#endif // !PF_ASSUME

#if !defined(PF_ASSUME_NOTNULL)
    #define PF_ASSUME_NOTNULL( ptr )    ASSERT(NULL != ptr)
#endif // !PF_ASSUME_NOTNULL

#endif
