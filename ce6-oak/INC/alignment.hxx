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
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//
#pragma once 
#include <assert.h>

//
//  A group of helper functions that help in writing alignment/padding code.
//

namespace ce
{

// see:  http://www.monkeyspeak.com/alignment/ to understand this technique

template <typename T> struct computeAlignmentHelper
{
    T t;
    char c;
    private:
    computeAlignmentHelper();
    void operator=(computeAlignmentHelper&);
};

template <typename T> struct Alignment 
{
    enum {value = (sizeof(computeAlignmentHelper<T>) == sizeof(T)) ? 
        sizeof(T) : sizeof(computeAlignmentHelper<T>) - sizeof(T)};
}; 

template  <> struct Alignment <void>
{
    enum {value = 1};
}; 

template <typename T> struct cbMaxPad
{
    enum {value = Alignment<T>::value - 1 };
};

// compute padding for type T, given you want to write it at position P.
template <typename T> size_t cbPadding(void const * const p)
{
    const size_t alignment = Alignment<T>::value;
    const size_t cbPastAlignment =  reinterpret_cast<UINT_PTR>(p) % alignment;
    if ( cbPastAlignment == 0 )
    {
        return 0;
    }
    assert( alignment >= cbPastAlignment);
    return alignment - cbPastAlignment;
}

};
