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

#if !defined (AUTHRESET_H_982894908)
#define AUTHRESET_H_982894908

#include "util.h"
#include <memory>

namespace arc
{
typedef std::auto_ptr<BYTE> BlobPtr;

//  Data class incapsulates the data authentication reset worker operates with.
//
class Data
{
public:
    //  Construct default
    Data();

    //  Construct deserializeing from the blob
    //
    Data(BYTE * blob, size_t blobSize);
    ~Data();
    
    //  Serialize the data into the blob
    //  Blob should be released by the caller
    //
    HRESULT Serialize(/*out*/ BYTE *& blob, /*out*/ size_t & blobSize) const;

    //  Since there is a default constructor,
    //  we need this method to protect against invalid state.
    //  
    bool IsValid()
    {
        return m_valid;
    }

    //  Get/set password data
    //
    BYTE * Password() const
    {
        return m_protectedPassword.get();
    }
    
    size_t PasswordSize() const
    {
        return m_protectedPasswordSize;
    }
    
    void Password(BlobPtr passwd, size_t passwdSize)
    {
        m_protectedPassword = passwd;
        m_protectedPasswordSize = passwdSize;
    }

    //  Get/set salt data
    //
    BYTE * Salt() const
    {
        return m_salt.get();
    }
    
    size_t SaltSize() const
    {
        return m_saltSize;
    }
    
    void Salt(BlobPtr salt, size_t saltSize)
    {
        m_salt = salt;
        m_saltSize = saltSize;
    }

    //  Get/set hash data
    //
    BYTE * Hash() const
    {
        return m_hash.get();
    }
    
    size_t HashSize() const
    {
        return m_hashSize;
    }
    
    void Hash(BlobPtr hash, size_t hashSize)
    {
        m_hash = hash;
        m_hashSize = hashSize;
    }

    //  Compare passed hash with the open stored in the object
    //
    bool CompareHashValues(BYTE * hash, size_t hashSize) const;

private:
    //  Deserialize the data from the blob
    //
    HRESULT Deserialize(BYTE * blob, size_t blobSize);

private:
    //  protect from copying
    Data(Data const &);
    Data & operator=(Data const &);

private:
    BlobPtr m_protectedPassword;
    size_t m_protectedPasswordSize;
    BlobPtr m_salt;
    size_t m_saltSize;
    BlobPtr m_hash;
    size_t m_hashSize;
    bool m_valid;
};

//  This is a temporary solution untill the AuthReset API appears in the SDK.
//  TODO: remove
//
class ModuleWrapper
{
public:
    ModuleWrapper();
    ~ModuleWrapper();

    HRESULT AuthResetSetup(HWND parent, BYTE const * input, size_t inputSize, /*out*/ BYTE ** output, /*out*/ size_t * outputSize) const;
    HRESULT AuthResetRequest(HWND parent, BYTE const * input, size_t inputSize, /*out*/ BYTE ** output, /*out*/ size_t * outputSize) const;
    HRESULT AuthResetGetValue(DWORD dwValueId, PVOID pInData, DWORD cbInData, /*out*/ PVOID pOutBuffer, /*out*/ DWORD * pcbOutBuffer) const;
    
private:
    HRESULT LazyLoadModule() const;

private:
    typedef HRESULT (*AuthResetSetupFunc)(HWND parent, BYTE const * input, size_t inputSize, /*out*/ BYTE ** output, /*out*/ size_t * outputSize);
    typedef HRESULT (*AuthResetRequestFunc)(HWND parent, BYTE const * input, size_t inputSize, /*out*/ BYTE ** output, /*out*/ size_t * outputSize);
    typedef HRESULT (*AuthResetGetValueFunc)(DWORD dwValueId, PVOID pInData, DWORD cbInData, /*out*/ PVOID pOutBuffer, /*out*/ DWORD * pcbOutBuffer);
    
private:
    LPCTSTR m_dllName;
    HMODULE mutable m_dllModule;
    AuthResetSetupFunc mutable m_setup;
    AuthResetRequestFunc mutable m_request;
    AuthResetGetValueFunc mutable m_getValue;
};

//  ResetWorker provides an easy way to work with the ARC
//  by implementing non-ui backend for setup and reset actions.
//
class ResetWorker
{
public:
    ResetWorker(HWND parent = NULL);
    HRESULT Setup(LPCTSTR passwd, HANDLE heventDisplayed, /*out*/ arc::Data & protectedData, /*out*/ TCHAR ** status);
    HRESULT Request(arc::Data & data, function1<void> & enroll, /*out*/ TCHAR ** passwd, /*out*/ TCHAR ** status);

private:
    HRESULT DisplaySetupMessage(HANDLE heventDisplayed) const;
    HRESULT DisplayRequestMessage() const;
    HRESULT DisplayMessage(unsigned int prefixStringId, unsigned int stringId, HANDLE heventDisplayed) const;
    HRESULT GetArcMessage(DWORD messageId, /*out*/ TCHAR ** message) const;
    HRESULT GetArcMessage(DWORD messageId, DWORD secondaryId, /*out*/ TCHAR ** message) const;
    HRESULT DoSetup(HWND parent, BYTE const * input, size_t inputSize, /*out*/ BYTE ** output, /*out*/ size_t * outputSize);
    HRESULT DoRequest(HWND parent, BYTE const * input, size_t inputSize, /*out*/ BYTE ** output, /*out*/ size_t * outputSize);
    HRESULT GetSetupStatus(HRESULT setupHR, /*out*/ TCHAR ** status) const;
    HRESULT GetRequestStatus(HRESULT requestHR, /*out*/ TCHAR ** status) const;

private:
    arc::ModuleWrapper m_arcModule;
    HWND m_wndParent;
};

}  // namespace arc

#endif  // AUTHRESET_H_982894908

