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
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

/*
 *  Password History
 *
 *  SUMMARY:
 *
 *      This file implements a password history feature for the sample LAP.
 *      When the user of the device changes their password the old password is
 *      saved into the password history store. During enrollment the user will
 *      enter a potential new password and the LAP will validate that this new
 *      password meets all of the policy requirements. If the password history
 *      policy is enabled then the potential new password is checked against
 *      the password history store and if the potential new password is in the
 *      store the LAP will reject that password.
 *
 *      The number of entries in the password history store is determined by 
 *      the NumberOfPasswords policy (the uNumberOfPasswords field in the 
 *      PASSWDINFO structure).
 *
 *      This file does not implement the actual storage mechanism for 
 *      password history. See the file RegSaveData.cpp for details on the
 *      implementation of the registry based history store.
 *
 *  NOTES:
 *
 *      The password history store does not actually store the passwords but 
 *      rather a salted hash of the password.
 *
 *      Changing the value of uNumberOfPasswords will clear all current
 *      entries in the password history store. This is a limitation of the
 *      implementation of CRegistryBuffer::Resize().
 */

#include "lap_priv.h"
#include "regext.h"
#include "RegSaveData.h"
#include "Password_History.h"
#include "util.h"


// Location in the registry to store the history information
static const TCHAR K_SZPASSWORD_HISTORY_KEY[]  = TEXT("Comm\\Security\\LASSD\\LAP\\SampleLap\\pwdhist");

/*
 *  Internal structure used to hold information about an entry in the password
 *  history store. This structure is serialized to a binary blob before being
 *  put into the history store. When a binary blob is read from the history
 *  store it will be de-serialized into this structure.
 *
 *  If you make any changes at all to this structure you
 *  will need to fix the SerializePasswordData() and
 *  DeSerializePasswordData() routines. In particular 
 *  changing any of the cb* fields to be anything other
 *  than DWORDs will cause strange things to happen.
 */
struct PASSWORD_HISTORY_ENTRY
{
    DWORD   cbEncryptedPassword;
    BYTE   *pbEncryptedPassword;
    DWORD   cbCryptoProvider;
    LPTSTR  pszCryptoProvider;
    DWORD   cbSalt;
    BYTE   *pbSalt;
    ALG_ID  aiHashAlgorithm;
    DWORD   dwProviderType;
};

/*
 *  SerializePasswordData
 *
 *  SUMMARY:
 *
 *      Takes a PASSWORD_HISTORY_ENTRY structure and converts it into a binary
 *      blob that can be stored in the password history store.
 *
 *  PARAMETERS:
 *
 *      phistData           [IN}    Pointer to the PASSWORD_HISTORY_ENTRY to
 *                                  be serialized.
 *
 *      ppbSerializedData   [OUT]   On a succesful return will point to a
 *                                  byte array containing the serialized
 *                                  data. Caller is responsible for freeing
 *                                  this memory using LocalFree().
 *
 *      pcbSerializeData    [OUT]   On a successful return will contain the
 *                                  size (in bytes) of the serialized data.
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 *  NOTES:
 *
 *      The layout of the serialized data is as follows.
 *
 *          Size                    Type            Name                    Description
 *          ----                    ----            -------------------     ------------------------------------
 *            4                     DWORD           cbEncryptedPassword     Size of the encrypted password data
 *          cbEncryptedPassword     BYTE array      bEncryptedPassword      Encrypted password data
 *            4                     DWORD           cbSalt                  Size of the salt data
 *          cbSalt                  BYTE array      bSalt                   Salt data
 *            4                     ALG_ID          aiHashAlgorithm         Algorithm used to hash the password
 *
 */
static HRESULT SerializePasswordData (__in const PASSWORD_HISTORY_ENTRY * const phistData, 
                                      __deref_out_ecount (*pcbSerializedData) BYTE **ppbSerializedData,
                                      __out DWORD *pcbSerializedData)
{
    HRESULT hr = E_UNEXPECTED;
    UINT    cbTotalSize;

    /*
     *  cbTotalSize =   sizeof (DWORD) + phistData->cbEncryptedPassword
     *                + sizeof (DWORD) + phistData->cbSalt
     *                + sizeof (ALG_ID)
     */
    cbTotalSize = 2 * sizeof (DWORD) + sizeof (phistData->aiHashAlgorithm);
    if (   safeIntUAdd (cbTotalSize, phistData->cbEncryptedPassword, &cbTotalSize)
        && safeIntUAdd (cbTotalSize, phistData->cbSalt, &cbTotalSize))
    {
        BYTE *pbTemp = new (localalloc) BYTE[cbTotalSize];
        if (pbTemp)
        {
            BYTE *pbWork = pbTemp;

            memcpy (pbWork, &phistData->cbEncryptedPassword, sizeof (phistData->cbEncryptedPassword));  // Size of password data
            pbWork += sizeof (phistData->cbEncryptedPassword);

            memcpy (pbWork, phistData->pbEncryptedPassword, phistData->cbEncryptedPassword);            // Password data
            pbWork += phistData->cbEncryptedPassword;

            memcpy (pbWork, &phistData->cbCryptoProvider, sizeof (phistData->cbCryptoProvider));        // Size of provider name (including NUL)
            pbWork += sizeof (phistData->cbCryptoProvider);

            if (phistData->cbCryptoProvider != 0)
            {
                memcpy (pbWork, phistData->pszCryptoProvider, phistData->cbCryptoProvider);             // Provider name
                pbWork += phistData->cbCryptoProvider;
            }

            memcpy (pbWork, &phistData->cbSalt, sizeof (phistData->cbSalt));                            // Size of salt
            pbWork += sizeof (phistData->cbSalt);

            memcpy (pbWork, phistData->pbSalt, phistData->cbSalt);                                      // Salt Data
            pbWork += phistData->cbSalt;

            memcpy (pbWork, &phistData->aiHashAlgorithm, sizeof (phistData->aiHashAlgorithm));          // Algorithm ID
            pbWork += sizeof (phistData->aiHashAlgorithm);

            memcpy (pbWork, &phistData->dwProviderType, sizeof (phistData->dwProviderType));            // Provider type
            pbWork += sizeof (phistData->dwProviderType);

            ASSERT ((pbWork - pbTemp) == cbTotalSize);

            *ppbSerializedData = pbTemp;
            *pcbSerializedData = cbTotalSize;

            hr = S_OK;
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }
    }
    else
    {
        hr = HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
    }
    return hr;
}


/*
 *  ValidateBufferSize
 *
 *  SUMMARY:
 *
 *      Helper function for deserialization of a binary blob containing a 
 *      representation of a PASSWORD_HISTORY_ENTRY structure. Verifies that
 *      the length fields of the binary blob are consistent with the total
 *      size of the blob.
 *
 *  PARAMETERS:
 *
 *      pbSerializedData    [IN]    Buffer to be validated
 *
 *      cbSerializeData     [IN]    Size of the buffer
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 */
static HRESULT ValidateBufferSize (__in_ecount (cbSerializedData) const BYTE * const pbSerializedData,
                                   __in DWORD cbSerializedData)
{
    HRESULT     hr      = E_FAIL;
    const BYTE *pbWork  = pbSerializedData;
    UINT        cbTotal = 0;
    UINT        cbTemp  = 0;

    // Validate size fields in buffer
    cbTotal  = sizeof (((PASSWORD_HISTORY_ENTRY *)0)->aiHashAlgorithm);
    if (cbTotal < cbSerializedData)
    {
        // Size of encrypted password data
        memcpy (&cbTemp, pbWork, sizeof (cbTemp));
        if (   safeIntUAdd (cbTemp, sizeof(cbTemp), &cbTemp)                  
            && safeIntUAdd (cbTotal, cbTemp, &cbTotal))
        {
            if (cbTotal < cbSerializedData)
            {
                pbWork += cbTemp;

                // Size of salt data
                memcpy (&cbTemp, pbWork, sizeof (cbTemp));
                if (   safeIntUAdd (cbTemp, sizeof (cbTemp), &cbTemp)
                    && safeIntUAdd (cbTotal, cbTemp, &cbTotal))
                {
                    if (cbTotal == cbSerializedData)
                    {
                        hr = S_OK;
                    }
                }
            }
        }  
    }
    return hr;
}

/*
 *  UnpackBuffer
 *
 *  SUMMARY:
 *
 *      Helper function for deserialization of a binary blob containing a 
 *      representation of a PASSWORD_HISTORY_ENTRY structure. Does the
 *      conversion of data from the binary blob to the PASSWORD_HISTORY_ENTRY
 *      structure.
 *
 *  PARAMETERS:
 *
 *      pbSerializedData    [IN]    Buffer to be unpacked
 *
 *      cbSerializeData     [IN]    Size of the buffer
 *
 *      pphistData          [OUT]   On a succesful return will point to
 *                                  a PASSWORD_HISTORY_ENTRY structure
 *                                  containing the data from the input
 *                                  binary blob. The caller of this function
 *                                  is responsible for freeing this buffer
 *                                  using LocalFree().
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 *  NOTES:
 *
 *      The serialized data is unpacked into a single buffer which represents both
 *      the PASSWORD_HISTORY_ENTRY structure and the byte buffers used to store the
 *      encrypted password and salt information. To avoid aligment issues each byte
 *      array is moved to be aligned on a DWORD boundary.
 */
HRESULT UnpackBuffer (__in_ecount (cbSerializedData) const BYTE * const pbSerializedData,
                      __in DWORD cbSerializedData,
                      __deref_out PASSWORD_HISTORY_ENTRY **pphistData)
{
    HRESULT     hr      = E_FAIL;
    const BYTE *pbWork  = pbSerializedData;
    UINT        cbTotal = cbSerializedData; 

    /*  At this point we've validated that all the buffer lengths are 
     *  reasonable. We just need to add in the structure header size and
     *  then we can unpack the data. Note that we counted an additional 
     *  DWORD length field for blob of data so we already have room to 
     *  DWORD align each blob.
     */
    if (safeIntUAdd(cbTotal, sizeof (**pphistData), &cbTotal))
    {
        BYTE *pbData; 
        PASSWORD_HISTORY_ENTRY *phistTemp;

        pbData = new (localalloc) BYTE[cbTotal];
        if (pbData)
        {
            phistTemp = reinterpret_cast<PASSWORD_HISTORY_ENTRY *>(pbData);
            pbWork = pbSerializedData;
            pbData += ((sizeof (PASSWORD_HISTORY_ENTRY) + (_alignof (DWORD) - 1)) / _alignof (DWORD)) * _alignof (DWORD);

            // Copy out Encrypted password
            phistTemp->pbEncryptedPassword = pbData;
            memcpy (&phistTemp->cbEncryptedPassword, pbWork, sizeof (DWORD));
            pbWork += sizeof (DWORD);
            memcpy (phistTemp->pbEncryptedPassword, pbWork, phistTemp->cbEncryptedPassword);
            pbWork += phistTemp->cbEncryptedPassword;
            pbData += ((phistTemp->cbEncryptedPassword + (_alignof (DWORD) - 1)) / _alignof (DWORD)) * _alignof (DWORD);

            // Copy out Crypto provider
            phistTemp->pszCryptoProvider = reinterpret_cast<TCHAR *>(pbData);
            memcpy (&phistTemp->cbCryptoProvider, pbWork, sizeof (DWORD));
            pbWork += sizeof (DWORD);
            if (phistTemp->cbCryptoProvider != 0)
            {
                memcpy (phistTemp->pszCryptoProvider, pbWork, phistTemp->cbCryptoProvider);
                pbWork += phistTemp->cbCryptoProvider;
                pbData += ((phistTemp->cbCryptoProvider + (_alignof (DWORD) - 1)) / _alignof (DWORD)) * _alignof (DWORD);
            }
            else
            {
                phistTemp->pszCryptoProvider = NULL;
            }

            // Copy out Salt
            phistTemp->pbSalt = pbData;
            memcpy (&phistTemp->cbSalt, pbWork, sizeof (DWORD));
            pbWork += sizeof (DWORD);
            memcpy (phistTemp->pbSalt, pbWork, phistTemp->cbSalt);
            pbWork += phistTemp->cbSalt;
            pbData += ((phistTemp->cbSalt + (_alignof (DWORD) - 1)) / _alignof (DWORD)) * _alignof (DWORD);

            // Copy out algorithm id
            memcpy (&phistTemp->aiHashAlgorithm, pbWork, sizeof (phistTemp->aiHashAlgorithm));
            pbWork += sizeof (phistTemp->aiHashAlgorithm) ;

            // Copy out provider type
            memcpy (&phistTemp->dwProviderType, pbWork, sizeof (phistTemp->dwProviderType));

            // And we're done ...
            *pphistData = phistTemp;
            hr = S_OK;
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }
    }
    return hr;
}


/*
 *  DeSerializePasswordData
 *
 *  SUMMARY:
 *
 *      Converts a binary blob from the password history store into a 
 *      PASSWORD_HISTORY_ENTRY structure. 
 *
 *  PARAMETERS:
 *
 *      pbSerializedData    [IN]    Buffer to be de-serialized
 *
 *      cbSerializeData     [IN]    Size of the buffer
 *
 *      pphistData          [OUT]   On a succesful return will point to
 *                                  a PASSWORD_HISTORY_ENTRY structure
 *                                  containing the data from the input
 *                                  binary blob. The caller of this function
 *                                  is responsible for freeing this buffer
 *                                  using LocalFree().
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 */
static HRESULT DeSerializePasswordData (__in_ecount (cbSerializedData) const BYTE * const pbSerializedData,
                                        __in DWORD cbSerializedData,
                                        __deref_out PASSWORD_HISTORY_ENTRY **pphistData)
{
    HRESULT     hr      = E_FAIL;

    hr = ValidateBufferSize (pbSerializedData, cbSerializedData);
    if (SUCCEEDED(hr))
    {
        hr = UnpackBuffer (pbSerializedData, cbSerializedData, pphistData);
    }
    return hr;
}


/*
 *  PasswordCompare
 *
 *  SUMMARY:
 *
 *      Callback function passed to the password history store when trying to
 *      find a password in the store. This function will be called once for
 *      every entry in the history store to see if the current entry matches
 *      the new potential password being examined.
 *
 *  PARAMETERS:
 *
 *      pbLookingFor        [IN]    Poitner to the password (plaintext) that
 *                                  we are looking for in the password history
 *                                  store.
 *
 *      cbLookingFor        [IN]    Unused
 *
 *      pbPossibleMatch     [IN]    A serialized PASSWORD_HISTORY_ENTRY to be
 *                                  compared with.
 *
 *      cbPossibleMatch     [IN}    Size of the pbPossibleMatch buffer
 *
 *  RETURN:
 *
 *      An integer representing the result of the comparison. A value of 0 means
 *      that the password and the password contained in the serialized
 *      PASSWORD_HISTORY_ENTRY are the same. Any other value indicates that they
 *      are not the same
 *
 */
static int PasswordCompare (__in_ecount (cbLookingFor)    const BYTE * const pbLookingFor,
                            DWORD cbLookingFor, 
                            __in_ecount (cbPossibleMatch) const BYTE * const pbPossibleMatch,
                            DWORD cbPossibleMatch)
{
    HRESULT hr;
    int     iRetVal = -1;

    // pbLookingFor is really pointing to the new password
    // pbPossibleMatch is really pointing to a serialized PASSWORD_HISTORY_ENTRY
    LPCTSTR                 pszPassword = reinterpret_cast<LPCTSTR>(pbLookingFor);
    PASSWORD_HISTORY_ENTRY *phistData   = NULL;
    
    // Deserialize the password blob
    hr = DeSerializePasswordData (pbPossibleMatch, cbPossibleMatch, &phistData);
    if (SUCCEEDED (hr))
    {
        // Now Decrypt the hashed password 
        CRYPT_DATA_BLOB blobEncrypted       = { 0 };
        CRYPT_HASH_BLOB blobHashedPassword  = { 0 };
        CRYPT_HASH_BLOB blobHashToCheck     = { 0 };

        blobEncrypted.cbData = phistData->cbEncryptedPassword;
        blobEncrypted.pbData = phistData->pbEncryptedPassword;

        if (CryptUnprotectData (&blobEncrypted, NULL, NULL, NULL, NULL, 
                                CRYPTPROTECT_SYSTEM, &blobHashedPassword))
        {
            HCRYPTPROV hProv;
            DWORD hashAlg;
            if (GetStoredCryptoSettings(&hProv, &hashAlg))
            {
                // Hash the new password with the same hash parameters as used for
                // the current entry in the history store
                if (HashStringWorker (hProv, hashAlg, pszPassword,
                                      phistData->pbSalt, phistData->cbSalt, 
                                      &blobHashToCheck.pbData, &blobHashToCheck.cbData))
                {
                    if (blobHashedPassword.cbData == blobHashToCheck.cbData)
                    {
                        iRetVal = memcmp (blobHashedPassword.pbData, 
                                            blobHashToCheck.pbData, 
                                            blobHashedPassword.cbData);
                    }
                    (void)LocalFree (blobHashToCheck.pbData);
                }
                ReleaseProvider(hProv);
            }
            (void)LocalFree (blobHashedPassword.pbData);
        }
        (void)LocalFree (phistData);
    }
    return iRetVal;
}


/*
 *  PasswordHistoryCheck
 *
 *  SUMMARY:
 *
 *      Checks a new potential password to see if the same password is in the
 *      password history store. If the same password is found then the new
 *      password is not acceptable and the user will need to choose another
 *      new password.
 *
 *  PARAMETERS:
 *
 *      ppwi                [IN}    Pointer to a PASSWDINFO structure that
 *                                  contains the potential new password as
 *                                  well as the current LAP policies.
 *
 *  RETURN:
 *
 *      An BOOL. A non-zero return value means that the password was not found
 *      in the password history file and is usable as a new password. A return
 *      value of 0 means that the password was found in the password history
 *      store and cannot be used.
 *
 */
BOOL PasswordHistoryCheck (__in const PASSWDINFO* const ppwi)
{
    BOOL            fValid      = FALSE;
    BOOL            fMatchFound = FALSE;
    HRESULT         hr          = S_OK;
    CRegistryBuffer cbStore;

    if (ppwi->Policy.uNumberOfPasswords != 0)
    {
        // Initialize the password history store
        hr = cbStore.Init (ppwi->Policy.uNumberOfPasswords, K_SZPASSWORD_HISTORY_KEY);
        if (SUCCEEDED(hr))
        {
            // See if we can find the new password in the history store
            hr = cbStore.FindMatch (PasswordCompare, 
                                        reinterpret_cast<const BYTE *>(ppwi->szPassword), 
                                        0, &fMatchFound);
            if (SUCCEEDED(hr))
            {
                fValid = (fMatchFound == FALSE);
            }
        }
    }
    else
    {
        fValid = TRUE;
    }

    return fValid;
}



/*
 *  AddCurrentPasswordToHistory
 *
 *  SUMMARY:
 *
 *      Helper function for storing the current password into the password
 *      history store just before the password is updated with a new
 *      password.
 *
 *  PARAMETERS:
 *
 *      pcbStore            [IN]    Pointer to the object implementing
 *                                  the password history store.
 *
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 */
HRESULT AddCurrentPasswordToHistory (CRegistryBuffer *pcbStore)
{
    HRESULT                 hr                      = E_UNEXPECTED;
    DATA_BLOB               blobEncryptedPassword   = { 0 };
    BYTE                   *pbSerializedData        = NULL;
    DWORD                   cbSerializedData        = 0;
    PASSWORD_HISTORY_ENTRY  histData                = { 0 };
    HKEY                    hKey;
    LONG                    lResult;
    BYTE                    bSalt[SALT_LENGTH];
    DWORD                   dwType;

    // Get Current information from registry
    lResult = GetEncryptedPasswordHash (&blobEncryptedPassword);
    hr = HRESULT_FROM_WIN32(lResult);
    if (SUCCEEDED (hr))
    {
        histData.cbEncryptedPassword = blobEncryptedPassword.cbData;
        histData.pbEncryptedPassword = blobEncryptedPassword.pbData;
        blobEncryptedPassword.pbData = NULL;

        // Load the crypto settings from the registry. 
        // They were stored along with the password hash.
        lResult = RegOpenKeyEx(HKEY_ROOT, K_SZLAPKEY, 0, 0, &hKey);
        if(ERROR_SUCCESS == lResult)
        {
            // Get the hash algorithm.
            (void)RegistryGetDWORD(hKey, NULL, K_SZHASHALG, 
                reinterpret_cast<DWORD*>(&(histData.aiHashAlgorithm)));

            // Get the crypto provider type.
            (void)RegistryGetDWORD(hKey, NULL, 
                K_SZPROVTYPE, &(histData.dwProviderType));

            // Get the crypto provider name size.
            lResult = RegQueryValueEx(hKey, K_SZPROVNAME, 
                NULL, NULL, NULL, &(histData.cbCryptoProvider));
            if(ERROR_SUCCESS == lResult)
            {
                histData.pszCryptoProvider = reinterpret_cast<LPTSTR>(
                    LocalAlloc(LMEM_FIXED, histData.cbCryptoProvider));
            }

            // Get the actual provider name.
            if(NULL != histData.pszCryptoProvider)
            {
                lResult = RegQueryValueEx(hKey, K_SZPROVNAME, NULL, &dwType, 
                    reinterpret_cast<BYTE*>(histData.pszCryptoProvider), 
                    &(histData.cbCryptoProvider));
                if(ERROR_SUCCESS != lResult || REG_SZ != dwType)
                {
                    // Failure. Reset the provider name variable.
                    (void)LocalFree(histData.pszCryptoProvider);
                    histData.pszCryptoProvider = NULL;
                    histData.cbCryptoProvider  = 0;
                }
            }

            // Close the registry key.
            (void)RegCloseKey(hKey);
        }

        if (GetSalt (bSalt, ARRAYSIZE(bSalt)))
        {
            histData.cbSalt = ARRAYSIZE(bSalt);
            histData.pbSalt = bSalt;
        }

        hr = SerializePasswordData (&histData, &pbSerializedData, &cbSerializedData);
        if (SUCCEEDED(hr))
        {
            hr = pcbStore->Add (pbSerializedData, cbSerializedData);
            (void)LocalFree (pbSerializedData);
        }

        (void)LocalFree (histData.pszCryptoProvider);
        (void)LocalFree (histData.pbEncryptedPassword);
    }
    else
    {
        hr = S_FALSE;  // Don't fail just because no current password exists
    }
    return hr;
}


/*
 *  AddPasswordToHistory
 *
 *  SUMMARY:
 *
 *      Adds the current password to the password history store. Called
 *      just after the new user password is stored.
 *
 *  PARAMETERS:
 *
 *      ppwi                [IN}    Pointer to a PASSWDINFO structure that
 *                                  contains the potential new password as
 *                                  well as the current LAP policies.
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 */
HRESULT AddPasswordToHistory (const PASSWDINFO * const ppwi)
{
    HRESULT         hr = E_UNEXPECTED;
    CRegistryBuffer cbStore;
    DWORD           cCurrentBufferSize;

    hr = cbStore.Init (ppwi->Policy.uNumberOfPasswords, K_SZPASSWORD_HISTORY_KEY);
    if (SUCCEEDED(hr))
    {
        // Get size of current password history store
        cCurrentBufferSize = cbStore.MaxSize();

        // See if requested size has changed
        if (ppwi->Policy.uNumberOfPasswords != cCurrentBufferSize)
        {
            // Resizing the history buffer clears all existing passwords
            hr = cbStore.ReSize (ppwi->Policy.uNumberOfPasswords);
        }

        // Store the current password into the history store
        if (SUCCEEDED(hr) && ppwi->Policy.uNumberOfPasswords != 0)
        {
            hr = AddCurrentPasswordToHistory(&cbStore);
        }
    }
    return hr;
}
