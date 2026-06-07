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

#if !defined(CRYPT_HPP_9273490)
#define CRYPT_HPP_9273490

#include "types.hpp"
#include <string>


//  Provides basic crypto primitives and wrapper functions around CAPI.
//

//  EncryptionKey is an abstraction that incapsulates the data needed
//  to perform encryption/decryption using CAPI functions.
//  It combines both HCRYPTKEY and HCRYPTPROV, because the key
//  cannot be used without a provider (it internally depends on the provider).
//
class EncryptionKey
{
public:
    EncryptionKey(CryptKey const & key, CryptProv const & prov)
        : m_key(key)
        , m_prov(prov)
    {}

    CryptKey const & Key() const
    {
        return m_key;
    }

    CryptProv const & Provider() const
    {
        return m_prov;
    }

private:
    CryptKey m_key;
    CryptProv m_prov;
};


//  These are wrappers for CAPI function that simplify and provide higher level
//  access to crypto functionality.
//
namespace crypt
{
    //  perform encryption of a data using a given key
    Blob Encrypt(Blob const & src, EncryptionKey const & key);

    //  perform decryption of a data using a given key
    Blob Decrypt(Blob const & src, EncryptionKey const & key);

    //  generates a new key that can be used for encryption
    EncryptionKey GenerateKey();

    //  export a key to a blob
    Blob KeyToBlob(EncryptionKey const & key);

    //  import a key from a blob
    EncryptionKey BlobToKey(Blob const & blob);

    //  convert a blob to a readable string
    std::wstring BlobToString(Blob const & blob);

    //  convert a readable string to a blob
    Blob StringToBlob(std::wstring const & str);
}

#endif  // CRYPT_HPP_9273490
