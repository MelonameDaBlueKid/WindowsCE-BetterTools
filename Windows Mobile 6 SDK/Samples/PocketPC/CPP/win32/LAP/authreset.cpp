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

#include "authreset.h"
#include "util.h"
#include "scope_guard.h"
#include "resource.h"

#include <windows.h>
#include <aygshell.h>

namespace arc
{

//  Data class
//
Data::Data()
    : m_protectedPassword()
    , m_protectedPasswordSize(0)
    , m_salt()
    , m_saltSize(0)
    , m_hash()
    , m_hashSize(0)
    , m_valid(true)
{
}

Data::Data(BYTE * blob, size_t blobSize)
    : m_protectedPassword()
    , m_protectedPasswordSize(0)
    , m_salt()
    , m_saltSize(0)
    , m_hash()
    , m_hashSize(0)
    , m_valid(false)
{
    HRESULT hr = Deserialize(blob, blobSize);
    m_valid = SUCCEEDED(hr);
}

Data::~Data()
{}

//  Compare passed hash with the open stored in the object
//
bool Data::CompareHashValues(BYTE * hash, size_t hashSize) const
{
    if (m_hashSize != hashSize)
    {
        return false;
    }

    return memcmp(m_hash.get(), hash, m_hashSize) == 0;
}

//  Serialize data into a blob.
//  The caller is responsible for freeing the result blob with LocalFree.
//
HRESULT Data::Serialize(/*out*/ BYTE *& blob, /*out*/ size_t & blobSize) const
{
    // alloc requires space
    size_t requiredSize = 3 * sizeof(size_t) + PasswordSize() + HashSize() + SaltSize();

    blob = new (localalloc) BYTE[requiredSize];
    if (!blob) return E_OUTOFMEMORY;

    // copy data
    size_t * cur_size_t = reinterpret_cast<size_t *>(blob);
    *cur_size_t++ = PasswordSize();
    *cur_size_t++ = HashSize();
    *cur_size_t++ = SaltSize();

    BYTE * cur = reinterpret_cast<BYTE *>(cur_size_t);
    memcpy(cur, Password(), PasswordSize());
    cur += PasswordSize();
    memcpy(cur, Hash(), HashSize());
    cur += HashSize();
    memcpy(cur, Salt(), SaltSize());
    cur += SaltSize();

    blobSize = requiredSize;
    return S_OK;
}

//  Deserialize data from a blob.
//
HRESULT Data::Deserialize(BYTE * blob, size_t blobSize)
{
    // validate the input data
    if (blobSize < 3 * sizeof(size_t))
        return E_INVALIDARG;

    size_t * cur_size_t = reinterpret_cast<size_t *>(blob);
    size_t passwordSize = *cur_size_t++;
    size_t hashSize = *cur_size_t++;
    size_t saltSize = *cur_size_t++;

    BYTE * cur = reinterpret_cast<BYTE *>(cur_size_t);
    if (blobSize - (cur - blob) != passwordSize + hashSize + saltSize)
        return E_INVALIDARG;

    // data is valid, read
    BYTE * password = new (localalloc) BYTE[passwordSize];
    BYTE * hash = new (localalloc) BYTE[hashSize];
    BYTE * salt = new (localalloc) BYTE[saltSize];

    if (! (password && hash && salt))
    {
        return E_OUTOFMEMORY;
    }

    memcpy(password, cur, passwordSize);
    cur += passwordSize;
    memcpy(hash, cur, hashSize);
    cur += hashSize;
    memcpy(salt, cur, saltSize);

    Password(BlobPtr(password), passwordSize);
    Hash(BlobPtr(hash), hashSize);
    Salt(BlobPtr(salt), saltSize);

    return S_OK;
}

    
//  ModuleWrapper clas
//
    
ModuleWrapper::ModuleWrapper()
    : m_dllName(L"aygshell.dll")
    , m_dllModule(NULL)
    , m_setup(NULL)
    , m_request(NULL)
    , m_getValue(NULL)
{}

ModuleWrapper::~ModuleWrapper()
{
    FreeLibrary(m_dllModule);
}

//  Load the ARC module and its export functions.
//
HRESULT ModuleWrapper::LazyLoadModule() const
{
    if (!m_dllModule)
    {
        m_dllModule = static_cast<HMODULE>(LoadLibrary(m_dllName));
        if (!m_dllModule)
        {
            return HResultFromWin32(GetLastError());
        }

        m_setup = reinterpret_cast<AuthResetSetupFunc>(GetProcAddress(m_dllModule, L"AuthResetSetup"));
        if (!m_setup)
        {
            return HResultFromWin32(GetLastError());
        }

        m_request = reinterpret_cast<AuthResetRequestFunc>(GetProcAddress(m_dllModule, L"AuthResetRequest"));
        if (!m_request)
        {
            return HResultFromWin32(GetLastError());
        }

        m_getValue = reinterpret_cast<AuthResetGetValueFunc>(GetProcAddress(m_dllModule, L"AuthResetGetValue"));
        if (!m_getValue)
        {
            return HResultFromWin32(GetLastError());
        }
    }

    return S_OK;
}

HRESULT ModuleWrapper::AuthResetSetup(HWND parent
                                    , BYTE const * input
                                    , size_t inputSize
                                    , /*out*/ BYTE ** output
                                    , /*out*/ size_t * outputSize) const
{
    HRESULT hr = LazyLoadModule();
    if (FAILED(hr)) return hr;

    return (*m_setup)(parent, input, inputSize, output, outputSize);
}

HRESULT ModuleWrapper::AuthResetRequest(HWND parent
                                      , BYTE const * input
                                      , size_t inputSize
                                      , /*out*/ BYTE ** output
                                      , /*out*/ size_t * outputSize) const
{
    HRESULT hr = LazyLoadModule();
    if (FAILED(hr)) return hr;

    return (*m_request)(parent, input, inputSize, output, outputSize);
}

HRESULT ModuleWrapper::AuthResetGetValue(DWORD dwValueId
                                        , PVOID pInData
                                        , DWORD cbInData
                                        , /*out*/ PVOID pOutBuffer
                                        , /*out*/ DWORD * pcbOutBuffer) const
{
    HRESULT hr = LazyLoadModule();
    if (FAILED(hr)) return hr;

    return (*m_getValue)(dwValueId, pInData, cbInData, pOutBuffer, pcbOutBuffer);
}


//  ResetWorker class
//

ResetWorker::ResetWorker(HWND parent /*= NULL*/)
    : m_arcModule()
    , m_wndParent(parent)
{}

//  Do all the work needed for authentication reset setup.
//  AR setup protects the password passed to this function
//  and returns the protected data which LAP needs to store
//  and use on AR request.
//  On success or failure, the textual status message is returned.
//  The caller is responsible of releasing it with LocalFree.
//
HRESULT ResetWorker::Setup(LPCTSTR passwd
                         , HANDLE  heventDisplayed
                         , /*out*/ Data & protectedData
                         , /*out*/ TCHAR ** status)
{
    *status = NULL;  // reset the status message

    //  display setup message and ask if the user wants to proceed
    HRESULT hr = DisplaySetupMessage(heventDisplayed);
    if (FAILED(hr)) return hr;

    //  ask ARC to protect the password
    BYTE * protectedPasswd = NULL;
    size_t protectedPasswdSize = 0;
    hr = DoSetup(m_wndParent, reinterpret_cast<BYTE const *>(passwd), (wcslen(passwd) + 1) * sizeof(TCHAR), &protectedPasswd, &protectedPasswdSize);

    ScopeGuard protectedPasswdSc = ScopeProtect(protectedPasswd, LocalFree);

    //  retrieve the result of the setup operation
    HRESULT hr1 = GetSetupStatus(hr, status);
    if (FAILED(hr)) return hr;
    if (FAILED(hr1)) return hr1;

    //  create a crypt provider and hash algorithm
    HCRYPTPROV hProv = CreateCryptProv();
    if (!hProv)
        return E_FAIL;
    ScopeGuard hProvSc = ScopeProtect(hProv, ReleaseProvider);
    ALG_ID hashAlg  = GetHashAlgorithm();

    //  compute password hash
    BYTE * hash = NULL;
    DWORD hashSize = 0;
    BYTE * salt = NULL;
    BOOL br = HashString(hProv, hashAlg, passwd, &hash, &hashSize, &salt);  // creates a new salt
    if (!br) return E_FAIL;

    ScopeGuard hashSc = ScopeProtect(hash, LocalFree);
    ScopeGuard saltSc = ScopeProtect(salt, LocalFree);

    //  set output
    protectedData.Password(BlobPtr(protectedPasswd), protectedPasswdSize);
    protectedData.Hash(BlobPtr(hash), hashSize);
    protectedData.Salt(BlobPtr(salt), SALT_LENGTH);

    protectedPasswdSc.release();
    hashSc.release();
    saltSc.release();

    return S_OK;
}

//  Wrapper for the AuthResetSetup function
//
HRESULT ResetWorker::DoSetup(HWND parent
                           , BYTE const * input
                           , size_t inputSize
                           , /*out*/ BYTE ** output
                           , /*out*/ size_t * outputSize)
{
    return m_arcModule.AuthResetSetup(parent, input, inputSize, output, outputSize);
}

//  Do all the work needed for authentication reset request.
//  AR request recovers the password protected on AR setup
//  from the protected data.
//  Since the process of AR request requires to provide a new the password
//  at the same time, the enrollment delegate must be passed to the method
//  to perform this action.
//  On success or failure, the textual status message is returned.
//  The caller is responsible of releasing it with LocalFree.
//
HRESULT ResetWorker::Request(Data & data
                           , function1<void> & enroll
                           , /*out*/ TCHAR ** passwd
                           , /*out*/ TCHAR ** status)
{
    *status = NULL;  // reset the status message

    //  display request message and ask if the user wants to proceed
    HRESULT hr = DisplayRequestMessage();
    if (FAILED(hr)) return hr;

    //  perform new password enrollment
    enroll();
    
    //  perform the AR request and display the result
    BYTE * passwdBlob = NULL;
    size_t passwdSize = 0;
    hr = DoRequest(m_wndParent, data.Password(), data.PasswordSize(), &passwdBlob, &passwdSize);

    //  retrieve the result of the request operation
    HRESULT hr1 = GetRequestStatus(hr, status);
    if (FAILED(hr)) return hr;
    if (FAILED(hr1)) return hr1;

    //  create a crypt provider and hash algorithm
    HCRYPTPROV hProv = CreateCryptProv();
    if (!hProv)
        return E_FAIL;
    ScopeGuard hProvSc = ScopeProtect(hProv, ReleaseProvider);
    ALG_ID hashAlg  = GetHashAlgorithm();

    //  compute password hash and compare with the existing one
    TCHAR * retrievedPasswd = reinterpret_cast<TCHAR *>(passwdBlob);
    BYTE * hash = NULL;
    DWORD hashSize = 0;
    hr = HashStringWorker(hProv, hashAlg, retrievedPasswd, data.Salt(), data.SaltSize(), &hash, &hashSize);
    if (FAILED(hr)) return hr;

    //  hashes should be identical, otherwise the data is corrupt
    if (!data.CompareHashValues(hash, hashSize))
        return E_FAIL;

    *passwd = retrievedPasswd;
    return S_OK;
}

//  Wrapper for the AuthResetRequest function
//
HRESULT ResetWorker::DoRequest(HWND parent
                             , BYTE const * input
                             , size_t inputSize
                             , /*out*/ BYTE ** output
                             , /*out*/ size_t * outputSize)
{
    return m_arcModule.AuthResetRequest(parent, input, inputSize, output, outputSize);
}

//  The next number of methods retrieve setup and request UI and error messages from the ARC
//  and display them to the user.
//

HRESULT ResetWorker::DisplaySetupMessage(HANDLE heventDisplayed) const
{
    return DisplayMessage(IDS_AR_SETUP, 
        AUTHRESET_VALUE_SETUP_MESSAGE, heventDisplayed);
}

HRESULT ResetWorker::DisplayRequestMessage() const
{
    return DisplayMessage(IDS_AR_REQUEST, 
        AUTHRESET_VALUE_REQUEST_MESSAGE, NULL);
}

HRESULT ResetWorker::GetSetupStatus(HRESULT setupHR, /*out*/ TCHAR ** status) const
{
    HRESULT hr = GetArcMessage(AUTHRESET_VALUE_SETUPRESULT_MESSAGE, setupHR, status);
    return hr;
}

HRESULT ResetWorker::GetRequestStatus(HRESULT requestHR, /*out*/ TCHAR ** status) const
{
    HRESULT hr = GetArcMessage(AUTHRESET_VALUE_REQUESTRESULT_MESSAGE, requestHR, status);
    return hr;
}

HRESULT ResetWorker::DisplayMessage(unsigned int resourceStringId, unsigned int stringId, HANDLE heventDisplayed) const
{
    TCHAR * message;
    HRESULT hr = GetArcMessage(stringId, &message);
    if (FAILED(hr)) return hr;

    ScopeGuard messageSc = ScopeProtect(message, LocalFree);

    // concatenate it with the footer string loaded from resources
    LPCTSTR question = CELOADSZ(resourceStringId); // don't need to free
    
    TCHAR * fullMessage;
    hr = Concat(message, question, &fullMessage);
    if (FAILED(hr)) return hr;

    ScopeGuard fullMessageSc = ScopeProtect(fullMessage, LocalFree);

    // display the question to the user
    LPCTSTR caption = CELOADSZ(IDS_AR_CAPTION);
    int selection = ::DisplayMessage(m_wndParent, caption, 
        fullMessage, BUTTON_INFO_YESNO, heventDisplayed);
    return selection == IDOK ? S_OK : E_ABORT;
}

HRESULT ResetWorker::GetArcMessage(DWORD messageId, /*out*/ TCHAR ** message) const
{
    DWORD bufSize = 0;
    HRESULT hr = m_arcModule.AuthResetGetValue(messageId, 0, NULL, NULL, &bufSize);
    if (FAILED(hr)) return hr;

    BYTE * buf = new (localalloc) BYTE[bufSize];
    if (!buf) return E_OUTOFMEMORY;

    hr = m_arcModule.AuthResetGetValue(messageId, 0, NULL, buf, &bufSize);
    if (FAILED(hr)) return hr;

    *message = reinterpret_cast<TCHAR *>(buf);
    return S_OK;
}

HRESULT ResetWorker::GetArcMessage(DWORD messageId, DWORD secondaryId, /*out*/ TCHAR ** message) const
{
    DWORD bufSize = 0;
    HRESULT hr = m_arcModule.AuthResetGetValue(messageId, &secondaryId, sizeof(secondaryId), NULL, &bufSize);
    if (FAILED(hr)) return hr;

    BYTE * buf = new (localalloc) BYTE[bufSize];
    if (!buf) return E_OUTOFMEMORY;

    hr = m_arcModule.AuthResetGetValue(messageId, &secondaryId, sizeof(secondaryId), buf, &bufSize);
    if (FAILED(hr)) return hr;

    *message = reinterpret_cast<TCHAR *>(buf);
    return S_OK;
}

}  // namespace arc
