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

#include "stdafx.h"

#include "exception.hpp"
#include "crypt.hpp"
#include "config.hpp"


namespace
{
//  Internal implementation functions
//

    //  Wrapper for a provider release function that requires only one parameter
    void ReleaseProvider(HCRYPTPROV hProv)
    {
        CryptReleaseContext(hProv, 0);
    }

    //  Free memory in a secure way
    void SecureLocalFree(BYTE * data)
    {
        // zero memory first, then release it
        size_t size = LocalSize(data);
        SecureZeroMemory(data, size);

        LocalFree(data);
    }

    //  Create a new blob which is OK to use to store sensible data, because the blob is bound to a secure deallocator
    Blob CreateBlob(size_t size)
    {
        Blob blob(reinterpret_cast<BYTE *>(LocalAlloc(0, size)), size, SecureLocalFree);
        if (!blob)
            throw system_error();
        return blob;
    }

    //  Create a new predefined crypto provider
    CryptProv GetCryptProvider()
    {
        HCRYPTPROV hprov;
        check_boolresult(CryptAcquireContext(&hprov
                                           , NULL
                                           , NULL
                                           , CONFIG().CryptProviderType()
                                           , CRYPT_MACHINE_KEYSET | CRYPT_VERIFYCONTEXT | CRYPT_SILENT));

        return CryptProv(hprov, ReleaseProvider);
    }

    //  Generate a crypto key bound to a particular provider and an algorithm ID
    EncryptionKey GenerateKeyImpl(CryptProv const & provider, ALG_ID algId)
    {
        HCRYPTKEY hkey;
        check_boolresult(CryptGenKey(provider.get(), algId, CRYPT_EXPORTABLE, &hkey));

        CryptKey key(hkey, CryptDestroyKey);
        return EncryptionKey(key, provider);
    }

    //  Functions used for blob <-> string conversion

    wchar_t ToHexChar(wchar_t c)
    {
        if (c < 10)
            return c + L'0';
        else
            return c - 10 + 'A';
    }

    std::pair<wchar_t, wchar_t> ToHexPair(BYTE data)
    {
        wchar_t first = data >> 4;
        wchar_t second = data & 0xF;

        return std::make_pair(ToHexChar(first), ToHexChar(second));
    }

    template <typename Iter>
    std::wstring RangeToString(Iter begin, Iter end)
    {
        std::wstring result;
        for (; begin != end; ++begin)
        {
            std::pair<wchar_t, wchar_t> hex = ToHexPair(*begin);
            result += hex.first;
            result += hex.second;
        }

        return result;
    }

    BYTE FromHexChar(wchar_t c)
    {
        c -= L'0';
        assert(c >= 0);

        if (c < 10)
            return static_cast<BYTE>(c);

        c -= L'A' - L'0' - 10;
        assert(c >= 0xA && c < 0x10);

        return static_cast<BYTE>(c);
    }
}


//  Encrypt a blob of data using a given encryption key
//
Blob crypt::Encrypt(Blob const & src, EncryptionKey const & key)
{
    // get result size
    DWORD size = src.size();
    check_boolresult(CryptEncrypt(key.Key().get(), 0, TRUE, 0, NULL, &size, 0));

    // alloc space and copy data to the tgt buffer for encryption
    Blob tgt(CreateBlob(size));
    std::copy(src.begin(), src.end(), tgt.begin());

    // encrypt
    size = src.size();
    check_boolresult(CryptEncrypt(key.Key().get(), 0, TRUE, 0, &tgt[0], &size, tgt.size()));

    assert(size == tgt.size());

    return tgt;
}

//  Decrypt a blob of data using a given decryption key.
//  If the key is invalid (not the one the data was encrypted with),
//  or the data is invalid, this function will fail.
//
Blob crypt::Decrypt(Blob const & src, EncryptionKey const & key)
{
    // copy data to temp buffer for decryption
    Blob buf(CreateBlob(src.size()));
    std::copy(src.begin(), src.end(), buf.begin());

    // decrypt
    DWORD size = buf.size();
    check_boolresult(CryptDecrypt(key.Key().get(), 0, TRUE, 0, &buf[0], &size));

    // 'size' contains the number of bytes decrypted
    // it should not exceed the buffer size
    assert(size <= buf.size());

    // create the blob with decrypted data
    Blob tgt(CreateBlob(size));
    std::copy(buf.begin(), buf.begin() + size, tgt.begin());

    return tgt;
}

//  Generate a new key that can be used for data encryption
//
EncryptionKey crypt::GenerateKey()
{
    CryptProv provider = GetCryptProvider();
    ALG_ID algId = CONFIG().CryptAlgorithm();

    return GenerateKeyImpl(provider, algId);
}

//  Export a key to a plain text blob for storage
//
Blob crypt::KeyToBlob(EncryptionKey const & key)
{
    // get the key blob size
    DWORD size;
    check_boolresult(CryptExportKey(key.Key().get(), 0, PLAINTEXTKEYBLOB, 0, 0, &size));

    // get the key blob
    Blob tgt(CreateBlob(size));
    check_boolresult(CryptExportKey(key.Key().get(), 0, PLAINTEXTKEYBLOB, 0, &tgt[0], &size));

    assert(size == tgt.size());

    return tgt;
}

//  Convert a blob to a readable string.  Blob is usually obtained by converting a key.
//
std::wstring crypt::BlobToString(Blob const & blob)
{
    assert(blob.size() > sizeof(BLOBHEADER) + sizeof(DWORD));

    return RangeToString(blob.begin() + sizeof(BLOBHEADER) + sizeof(DWORD)
                       , blob.end());
}

//  Convert a readable string to a blob that can be used to import a key from
//
Blob crypt::StringToBlob(std::wstring const & str)
{
    assert(str.size() > 0 && (str.size() & 1) == 0);  // even number of characters

    // convert character data into binary
    Blob blob(CreateBlob(str.size() / 2));
    for (size_t i = 0, j = 0; i < str.size(); i += 2, ++j)
    {
        blob[j] = (FromHexChar(str[i]) << 4) | FromHexChar(str[i + 1]);
    }

    // create a full key blob
    Blob keyblob(CreateBlob(sizeof(BLOBHEADER) + sizeof(DWORD) + blob.size()));

    // initialize header
    BLOBHEADER * header = reinterpret_cast<BLOBHEADER *>(&keyblob[0]);
    header->aiKeyAlg = CONFIG().CryptAlgorithm();
    header->bVersion = 0x2;
    header->reserved = 0;
    header->bType = PLAINTEXTKEYBLOB;

    // set size
    DWORD * psize = reinterpret_cast<DWORD *>(&keyblob[0] + sizeof(BLOBHEADER));
    *psize = blob.size();

    // fill the key blob with data
    std::copy(blob.begin(), blob.end(), keyblob.begin() + sizeof(BLOBHEADER) + sizeof(DWORD));

    return keyblob;
}

//  Import a key from a blob.  An appropriate provider is generated along the way.
//  If a blob is invalid (not obtained by exporting a key), this function will fail.
//
EncryptionKey crypt::BlobToKey(Blob const & blob)
{
    // import the key
    CryptProv prov = GetCryptProvider();

    HCRYPTKEY hkey;
    check_boolresult(CryptImportKey(prov.get(), &blob[0], blob.size(), 0, 0, &hkey));

    CryptKey key(hkey, CryptDestroyKey);

    return EncryptionKey(key, prov);
}
