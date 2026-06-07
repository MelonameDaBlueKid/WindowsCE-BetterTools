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

#include "keystore.hpp"
#include "types.hpp"
#include "crypt.hpp"
#include "exception.hpp"
#include "config.hpp"

#include "errordlg.hpp"
#include "passcodedlg.hpp"

#include <vector>

using namespace std;

namespace
{
    // Conversion traits for reading data from the registry in a generic typesafe way.
    // It allows to convert binary data to a specified type in a specified way.
    //
    template <typename T>
    struct conversion_traits;

    template <>
    struct conversion_traits<std::wstring>
    {
        std::wstring operator()(BYTE * data) const
        {
            return wstring(reinterpret_cast<wchar_t *>(data));
        }
    };

    template <>
    struct conversion_traits<DWORD>
    {
        DWORD operator()(BYTE * data) const
        {
            return *reinterpret_cast<DWORD *>(data);
        }
    };

//  Registry helper functions

    //  Read a value from the registry.
    //  Value type is specified through the template parameter.
    //  Throws on failure.
    //
    template <typename T>
    T ReadValue(shared_ptr<HKEY> const & key, std::wstring const & valueName)
    {
        // get the size of the value
        DWORD buf_size = 0;
        check_win32result(RegQueryValueEx(key.get()
                                        , valueName.c_str()
                                        , NULL
                                        , NULL
                                        , NULL
                                        , &buf_size));

        // read the value into a buffer
        vector<BYTE> buf(buf_size);
        check_win32result(RegQueryValueEx(key.get()
                                        , valueName.c_str()
                                        , NULL
                                        , NULL
                                        , &buf[0]
                                        , &buf_size));

        conversion_traits<T> converter;
        return converter(&buf[0]);
    }

    //  Check the existance of the value in the registry
    //
    bool ValueExists(shared_ptr<HKEY> const & key, std::wstring const & valueName)
    {
        DWORD size = 0;
        long res = RegQueryValueEx(key.get()
                                 , valueName.c_str()
                                 , NULL
                                 , NULL
                                 , NULL
                                 , &size);
        return res == ERROR_SUCCESS;
    }

    //  Open/Create a registry key
    //
    shared_ptr<HKEY> OpenKey(HKEY root_key, std::wstring const & key)
    {
        HKEY hKey = NULL;
        DWORD disposition;
        check_win32result(RegCreateKeyEx(root_key
                                       , key.c_str()
                                       , 0
                                       , NULL
                                       , 0
                                       , 0
                                       , NULL
                                       , &hKey
                                       , &disposition));

        return shared_ptr<HKEY>(hKey, RegCloseKey);;
    }

    //  Set the string value to the registry
    //
    void SetValue(shared_ptr<HKEY> const & key, std::wstring const & valueName, std::wstring const & value)
    {
        check_win32result(RegSetValueEx(key.get()
                                      , valueName.c_str()
                                      , 0
                                      , REG_SZ
                                      , reinterpret_cast<BYTE const *>(value.c_str())
                                      , (value.size() + 1) * sizeof(wchar_t)));  // including '\0'
    }

    //  Check the value of the registry key for success/error simulation.
    //  If the value is set, no simulation dialog is shown, but this value
    //  is used instead.
    bool CheckSimResultKey(shared_ptr<HKEY> const & key, std::wstring const & valueName)
    {
        if (!ValueExists(key, valueName))
        {
            return false;
        }
        else
        {
            DWORD val = ReadValue<DWORD>(key, valueName);
            check_hresult(val);  // SimResult registry key contains success/error code

            return true;
        }
    }

    //  Handle all exceptions coming from the MFC
    //
    void HandleMFCException()
    {
        try
        {
            throw;
        }
        catch (CException * e)
        {
            e->Delete();
            throw runtime_error("simulation dialog failed");
        }
    }

    //  Display a generic success/error simulation dialog in a modal way
    //
    void DisplayDialog(SimulDlg & dlg)
    {
        if (dlg.DoModal() == IDOK)
        {
            if (!dlg.Success())
                throw system_error(dlg.ErrorCode());
        }
        else
        {
            throw runtime_error("simulation dialog failed");
        }
    }
}

//  KeyStore implementation

KeyStore::KeyStore()
    : m_authreset_key_name(CONFIG().AuthResetKeyName())
    , m_authreset_val_name(CONFIG().AuthResetValName())
    , m_simresult_val_name(CONFIG().SimResultValName())
    , m_root_key(CONFIG().AuthResetRootKey())
{}

//  Store the encryption key in the registry
//
void KeyStore::Store(EncryptionKey const & key)
{
    // open a key where the data is to be stored
    shared_ptr<HKEY> regkey(OpenKey(m_root_key, m_authreset_key_name));

    // check for error simulation automation key, and decide where we need to show the simulation dialog
    if (!CheckSimResultKey(regkey, m_simresult_val_name))
        SimulateErrorCondition();

    // convert the key to a form suitable for storage
    Blob blob(crypt::KeyToBlob(key));
    wstring str(crypt::BlobToString(blob));

    // store the key
    SetValue(regkey, m_authreset_val_name, str);
}

//  Show the success/error simulation dialog
//
void KeyStore::SimulateErrorCondition() const
{
    try
    {
        ErrorConditionDlg dlg;
        DisplayDialog(dlg);
    }
    catch (...)
    {
        HandleMFCException();
    }
}

//  KeyRetrieve implementation

KeyRetrieve::KeyRetrieve()
    : m_authreset_key_name(CONFIG().AuthResetKeyName())
    , m_authreset_val_name(CONFIG().AuthResetValName())
    , m_simresult_val_name(CONFIG().SimResultValName())
    , m_root_key(CONFIG().AuthResetRootKey())
{}

EncryptionKey KeyRetrieve::Retrieve()
{
    // open a key where the data is stored and read the key in string representation
    shared_ptr<HKEY> regkey(OpenKey(m_root_key, m_authreset_key_name));
    wstring str(ReadValue<wstring>(regkey, m_authreset_val_name));

    // check for error simulation automation key, and decide where we need to show the simulation dialog
    if (!CheckSimResultKey(regkey, m_simresult_val_name))
    {
        // show the key on the dialog to illustrate what we store in the registry
        DisplayPasscode(str);
    }

    // convert the key from the string representation into a form usable for decryption with CAPI
    Blob blob(crypt::StringToBlob(str));
    return crypt::BlobToKey(blob);
}

//  Show the success/error simulation dialog
//
void KeyRetrieve::DisplayPasscode(std::wstring const & passcode) const
{
    try
    {
        PasscodeDlg dlg(passcode);
        DisplayDialog(dlg);
    }
    catch (...)
    {
        HandleMFCException();
    }
}
