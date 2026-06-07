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

#if !defined(TYPES_HPP_9278492)
#define TYPES_HPP_9278492

#include <windows.h>
#include <wincrypt.h>
#include "shared_ptr.hpp"

//  Type definitions necessary to automate the resource management
//  with help of shared_ptr class
//

//  TypeWrapper is used to create a distinct type
//  from a Win32 resource typedef.
//  Many Win32 resource typedefs are identical.  TypeWrapper separates them.
//
template <typename T, typename Tag>
class TypeWrapper
{
public:
    TypeWrapper()
        : m_val()
    {}

    TypeWrapper(T val)
        : m_val(val)
    {}

    operator T() const
    {
        return m_val;
    }

private:
    T m_val;
};

class HCryptProvTag {};
class HCryptKeyTag {};

typedef TypeWrapper<HCRYPTPROV, HCryptProvTag> HCryptProv;
typedef TypeWrapper<HCRYPTKEY, HCryptKeyTag> HCryptKey;


//  Specialize shared_ptr traits for resource management
//

SMART_PTR_HANDLE_TRAITS(HCryptProv);
SMART_PTR_HANDLE_TRAITS(HCryptKey);
SMART_PTR_HANDLE_TRAITS(HKEY);

typedef shared_ptr<HCryptProv> CryptProv;
typedef shared_ptr<HCryptKey> CryptKey;
typedef shared_array<BYTE> Blob;

#endif  // TYPES_HPP_9278492
