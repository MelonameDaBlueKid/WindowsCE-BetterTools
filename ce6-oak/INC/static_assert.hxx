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

#if !defined(STATIC_ASSERT_HXX_5E1FA2A6)
#define STATIC_ASSERT_HXX_5E1FA2A6

// This is the implementation of the static_assert concept.
// It causes an error at compile time if the asserted condition is false.
// STATIC_ASSERT is typedef-based, it doesn't declare a temporary variable,
// so it's completely overhead free.

extern "C++"
{
namespace ce
{
    template <bool>
    struct static_assert_test;

    template <>
    struct static_assert_test<true> {};

    template <int>
    struct sizeof_test {};
}
}

#if !defined(STATIC_ASSERT)

#if defined(_MSC_VER) && (_MSC_VER < 1300)

//  MSVC 6 doesn't have line macro,
//  and __LINE__ is broken for /ZI,
//  but it ignores duplicate typedefs
//
#define STATIC_ASSERT(cond) \
    typedef ce::sizeof_test<sizeof(ce::static_assert_test<(bool)(cond)>)> \
        __static_assert_test__

#else  // _MSC_VER < 1300

#if !defined(CE_STRING_JOIN)
#define CE_PREPROC_EVAL(x) x
#define CE_STRING_JOIN(a,b) CE_PREPROC_EVAL(a) ## CE_PREPROC_EVAL(b)
#endif

#define STATIC_ASSERT(cond) \
    typedef ce::sizeof_test<sizeof(ce::static_assert_test<(bool)(cond)>)> \
        CE_STRING_JOIN(static_assert_test, __COUNTER__)

#endif  // _MSC_VER < 1300
#endif  // !defined(STATIC_ASSERT)


#endif  // STATIC_ASSERT_HXX_5E1FA2A6
