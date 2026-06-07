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

#include "kfuncs.h"

#include "shared_ptr.hpp"
#include "types.hpp"
#include "crypt.hpp"
#include "keystore.hpp"
#include "exception.hpp"
#include "messages.hpp"

#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

namespace
{
    //  A generic exception handler.
    //  Useful for handling exceptions in a consistent way at an
    //  exception-error code transition boundary
    //
    HRESULT HandleException()
    {
        try
        {
            throw;
        }
        catch (system_error & e)
        {
            return e.hresult();
        }
        catch (std::bad_alloc &)
        {
            return E_OUTOFMEMORY;
        }
        catch (std::exception &)
        {
            return E_FAIL;
        }
        catch (...)
        {
            assert(false && "unknown exception type");
            return E_FAIL;
        }
    }
}


//  Implementation of the ARC public interface
//

extern "C" {

//  Perform the setup step of the Authentication Reset process.
//  The purpose of setup is to protect the authentication related data
//  and make possible to restore it in case of loss.
//
//  For detailed description of this function parameters see aygshell.h
//
//  The typical process of data protection works as follows:
//  LAP passes the data that needs to be protected in pbResetData parameter.
//  ARC protects the data by encrypting and returns it in ppbRequestData parameter.
//  An encryption key used to protect the data is stored separately from the protected data
//  in a secure way.  Typically it needs to be stored on the server that can perform
//  secure key management.  This sample for the sake of clarity stores the key in
//  the secure portion of Registry.
//
HRESULT ARCSetup(                                       HWND /*hWndParent*/
    , __in_bcount_opt(cbResetData)                      BYTE const * pbResetData
    ,                                                   DWORD cbResetData
    , __deref_out_bcount(*pcbRequestData)               LPBYTE * ppbRequestData
    , __out                                             LPDWORD pcbRequestData)
{
    // check the trust and validate input parameters
    if (CeGetCallerTrust() != OEM_CERTIFY_TRUST)
    {
        return HRESULT_FROM_WIN32(ERROR_TRUST_FAILURE);
    }

    if (pbResetData == NULL
        || cbResetData == 0)
    {
        return E_INVALIDARG;
    }

    if (ppbRequestData == NULL
        || pcbRequestData == NULL)
    {
        return E_POINTER;
    }

    try
    {
        // combine a pointer to the data (pbResetData) and its size (cbResetData)
        // in a single array-like abstraction
        Blob resetData(const_cast<BYTE *>(pbResetData), cbResetData, null_deleter<BYTE>());

        // generate a key to protect the data
        // uses Crypto API to generate cryptographically strong keys
        EncryptionKey key(crypt::GenerateKey());

        // protect the data with the key
        Blob requestData(crypt::Encrypt(resetData, key));

        // export the key and store it in a secure place
        KeyStore store;
        store.Store(key);

        // if the above operations completed successfully
        // we can release the ownership of the requestData
        // and return it to the caller
        *pcbRequestData = requestData.size();
        *ppbRequestData = requestData.release();

        return S_OK;
    }
    catch (...)
    {
        // handle exceptions and tranform them into error codes on the component boudary
        return HandleException();
    }
}

//  Perform the request step of the Authentication Reset process.
//  The purpose of the request step is to restore the authentication related data
//  in case of loss.
//
//  For detailed description of this function parameters see aygshell.h
//
//  The typical process of restoring the authentication data conbines
//  two pieces of information coming from two different places:
//  RequestData from the LAP and a protection key from a secure key management server.
//  RequestData is the authentication data that was protected on the setup step
//  of the Authentication Reset process.  A key from a key management server is the exact key
//  that was used to protect the data.  For the sake of clarity this sample reads the key
//  from a secure portion of Registry.  RequestData is decrypted using
//  the encryption key and returned back to the LAP in ppbResetData parameter.
//
HRESULT ARCRequest(                                     HWND /*hWndParent*/
    , __in_bcount_opt(cbResetData)                      BYTE const * pbRequestData
    ,                                                   DWORD cbRequestData
    , __deref_out_bcount_opt(*pcbResetData)             LPBYTE * ppbResetData
    , __out                                             LPDWORD pcbResetData)
{
    // check the trust and validate input parameters
    if (CeGetCallerTrust() != OEM_CERTIFY_TRUST)
    {
        return HRESULT_FROM_WIN32(ERROR_TRUST_FAILURE);
    }

    if (pbRequestData == NULL
        || cbRequestData == 0)
    {
        return E_INVALIDARG;
    }

    if (ppbResetData == NULL
        || pcbResetData == NULL)
    {
        return E_POINTER;
    }

    try
    {
        // retrieve the key from a secure place and import using Crypto API
        KeyRetrieve keyretrieve;
        EncryptionKey key(keyretrieve.Retrieve());

        // combine a pointer to the data (pbResetData) and its size (cbResetData)
        // in a single array-like abstraction
        Blob requestData(const_cast<BYTE *>(pbRequestData), cbRequestData, null_deleter<BYTE>());

        // decrypt the protected data with the retrieved key
        // if either key or the data is invalid this step will fail
        Blob resetData(crypt::Decrypt(requestData, key));

        // if the above operations completed successfully
        // we can release the ownership of the resetData
        // and return it to the caller
        *pcbResetData = resetData.size();
        *ppbResetData = resetData.release();

        return S_OK;
    }
    catch (...)
    {
        // handle exceptions and tranform them into error codes on the component boudary
        return HandleException();
    }
}

//  Provides LAP with UI messages and error messages to help guide the user
//  through the Authentication Reset process.  This function also supposed
//  to provide some Authentication Reset parameters, but it's not covered
//  by this sample.
//
//  For detailed description of this function parameters see aygshell.h
//
//  For messages, this function receives two message IDs:
//      Primary ID      - dwValueId
//      Secondary ID    - pInData, cbInData pair
//
LONG ARCGetValue(                                           DWORD dwValueId
    , __in_bcount_opt(cbInData)                             PVOID pInData
    ,                                                       DWORD cbInData
    , __out_bcount_part_opt(*pcbOutBuffer, *pcbOutBuffer)   PVOID pOutBuffer
    , __inout                                               DWORD * pcbOutBuffer)
{
    // check the trust and validate input parameters
    if (CeGetCallerTrust() != OEM_CERTIFY_TRUST)
    {
        return HRESULT_FROM_WIN32(ERROR_TRUST_FAILURE);
    }

    if (pcbOutBuffer == NULL)
    {
        return HRESULT_CODE(E_INVALIDARG);
    }

    try
    {
        CString message;
        wchar_t * output = static_cast<wchar_t *>(pOutBuffer);

        // find out what message is requested
        if (pInData == NULL)
        {
            // no secondary id passed.  return a message for primary id
            message = mes::GetMessage(dwValueId);
        }
        else
        {
            if (cbInData != sizeof(HRESULT))
                return HRESULT_CODE(E_INVALIDARG);

            // return a message assigned to the primary id + secondary id pair
            message = mes::GetMessage(dwValueId, *static_cast<DWORD *>(pInData));
        }

        size_t messageSize = sizeof(wchar_t) * (message.GetLength() + 1);

        if (output)
        {
            if (*pcbOutBuffer < messageSize)
            {
                // output buffer is not large enough to hold the entire message
                *pcbOutBuffer = messageSize;
                return ERROR_MORE_DATA;
            }
            else
            {
                // copy the message to the output buffer
                CString::CopyChars(output, *pcbOutBuffer, message.GetBuffer(), message.GetLength());
                output[message.GetLength()] = L'\0';
            }
        }
        else
        {
            // no output buffer, just calculate and return the length of the message
            *pcbOutBuffer = messageSize;
        }

        return ERROR_SUCCESS;
    }
    catch (...)
    {
        // handle exceptions and tranform them into error codes on the component boudary
        return HRESULT_CODE(HandleException());
    }
}

}
