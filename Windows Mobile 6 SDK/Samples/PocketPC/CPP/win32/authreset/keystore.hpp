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

#if !defined(KEY_STORE_HPP_928734928)
#define KEY_STORE_HPP_928734928

#include <string>
#include <windows.h>

class EncryptionKey;

//  KeyStore is supposed to store an encryption key in a secure location.
//  This sample uses secure registry to store the key.
//
//  NOTE:
//  The key storage policy is a very important part of the secure environment.
//  The sample uses registry for the sake of simplicity.  The production code
//  of the ARC should never follow this example.
//  The key should be stored securely on a key management server.  For for information
//  search "key archival and management" on MSDN.
//
class KeyStore
{
public:
    KeyStore();
    void Store(EncryptionKey const & key);

private:
    void SimulateErrorCondition() const;
    
private:
    std::wstring m_authreset_key_name;
    std::wstring m_authreset_val_name;
    std::wstring m_simresult_val_name;
    HKEY m_root_key;
};


//  KeyRetrive retrieves an encryption key (also called recovery key).
//  This sample retrieves the key from the secure registry.
//  In real life the key should be stored on a key management server
//  and retrieved according to a proper process forcing a user
//  to verify his/her credentials before obtaining the recovery key.
//
class KeyRetrieve
{
public:
    KeyRetrieve();
    EncryptionKey Retrieve();

private:
    void DisplayPasscode(std::wstring const & passcode) const;

private:
    std::wstring m_authreset_key_name;
    std::wstring m_authreset_val_name;
    std::wstring m_simresult_val_name;
    HKEY m_root_key;
};

#endif  // KEY_STORE_HPP_928734928
