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
 *  Registry based history store
 *
 *  SUMMARY:
 *
 *      Implementation of a registry based history store. Other code may use the
 *      CRegistryBuffer class contained within to implement a circular buffer
 *      based history store that is persisted in the device's registry.
 *
 *  NOTES:
 *
 *      Data is stored under a single registry key as a set of named values.
 *      These values are treated as a circular buffer and named with their
 *      offset into the buffer (for instance a 3 element buffer would have
 *      values named "0", "1", and "2").
 *
 *      When the registry store is initialized it is given a base registy key
 *      name. Under this key it will create three values and a subkey used to
 *      store the buffer data. The three values are named "MaxSize",
 *      "CurrentSize", and "Next" while the subkey is named "Data".
 *
 *      "MaxSize" is the maximum number of entries allowed in the buffer, 
 *      "CurrentSize" is the current number of entries in the buffer, and
 *      "Next" is the index to the next entry to be used to store a history
 *      entry. When the "Next" index reaches "MaxSize" it will wrap around to 0.
 */

#include "lap_priv.h"
#include "regext.h"
#include "RegSaveData.h"

// Errors
CONST HRESULT E_NOMOREITEMS = HRESULT_FROM_WIN32(ERROR_NO_MORE_ITEMS);

// Constants
const DWORD gc_cchName = 10;

// Registry key names (subkeys of base registry key)
static const TCHAR g_szRegKeyData[] = _T("DATA");

// Registry Value names
static const TCHAR g_szMax[]        = _T("MaxSize");
static const TCHAR g_szCurrent[]    = _T("CurrentSize");
static const TCHAR g_szNext[]       = _T("Next");

static const TCHAR g_szNameFormatString[]   = _T("%d");


// Internal helper class

/*
 *  CRegistryBufferIterator
 *
 *  SUMMARY:
 *
 *      Internal helper class to iterate through all the entries in the store.
 *      See CRegistryBuffer::FindMatch() for an example of using this class
 *
 *  NOTES:
 *
 *      The member function Data() returns a raw pointer to the data contained
 *      in this class. While in general this is a bad idea we can do this here
 *      since we aren't exposing CRegistryBufferIterator outside of this file.
 *
 *      This class assumes that it is the only entity reading/writing the
 *      history entries in the registry. The behavior of this class if other
 *      entities are using the same registry keys is undefined.
 */
class CRegistryBufferIterator
{
    public:
        explicit CRegistryBufferIterator () : m_dwIndex(0), m_cbSize(0), m_pbData(NULL), m_pszValueName(NULL) {};
        ~CRegistryBufferIterator ();

        HRESULT Init            (HKEY hKey);
        HRESULT Next            ();
        BOOL    IsMoreData      () const { return (m_dwIndex != 0); };
        DWORD   DataSize        () const { return m_cbSize; };
        const BYTE * const Data () const { return m_pbData; };

    private:
        // Leave these functions unimplemented to prevent copying
        CRegistryBufferIterator (const CRegistryBufferIterator &);
        CRegistryBufferIterator & operator = (const CRegistryBufferIterator &);

    private:
        HRESULT ReadCurrentData ();

    private:
        HKEY        m_hKey;
        DWORD       m_dwIndex;
        DWORD       m_cchMaxNameLen;
        DWORD       m_cbMaxValueLen;

        LPTSTR      m_pszValueName;
        DWORD       m_cbSize;
        BYTE       *m_pbData;
};


/*
 *  CRegistryBufferIterator::~CRegistryBufferIterator
 *
 *  SUMMARY:
 *
 *      Cleans up any resources allocated by the CRegistryBufferIterator class
 */
CRegistryBufferIterator::~CRegistryBufferIterator ()
{
    ::LocalFree (m_pszValueName);
    ::LocalFree (m_pbData);
}

/*
 *  CRegistryBufferIterator::ReadCurrentData
 *
 *  SUMMARY:
 *
 *      Reads the current registry data pointed to by the iterator. Use the
 *      member functions Data and DataSize to access the data
 */
HRESULT CRegistryBufferIterator::ReadCurrentData ()
{
    HRESULT hr = E_UNEXPECTED;
    long    lResult;
    DWORD   cchValueName;
    DWORD   dwType;

    cchValueName = m_cchMaxNameLen + 1;
    m_cbSize = m_cbMaxValueLen;

    lResult = ::RegEnumValue (m_hKey, m_dwIndex - 1, m_pszValueName, 
                                &cchValueName, NULL, &dwType, m_pbData, &m_cbSize);
    if (lResult == ERROR_SUCCESS)
    {
        if (dwType != REG_BINARY)
        {
            lResult = ERROR_DATATYPE_MISMATCH;
        }
    }

    hr = HRESULT_FROM_WIN32(lResult);
    return hr;
}

/*
 *  CRegistryBufferIterator::Init
 *
 *  SUMMARY:
 *
 *      Begins the iteration process for the values of a given registry key.
 *
 *  PARAMETERS:
 *
 *      hKey            [IN]    Opened handle to the registry key whose values
 *                              we want to iterate over
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 *  SIDE EFFECTS:
 *
 *      The name and data associated with the first value are read into
 *      memory after successful initialization.
 *
 *  NOTES:
 *
 *      Even though we never need the value name we still get it during the
 *      registry enumration process so we will query the key and find out the
 *      length of the longest value name and allocate a buffer to store these
 *      names.
 *
 *      The basie pattern to use the buffer iterator is...
 *
 *          CRegistryBufferIterator rbi;
 *          rbi.Init()
 *          while (rbi.IsMoreData())
 *          {
 *              // Process current entry using rbi.DataSize() and rbi.Data()
 *              rbi.Next();
 *          )
 */
HRESULT CRegistryBufferIterator::Init (HKEY hKey)
{
    HRESULT hr = E_UNEXPECTED;
    long lResult;

    m_hKey = hKey;

    // How long are the longest value name and value data ?
    lResult = RegQueryInfoKey (m_hKey, NULL, NULL, NULL, NULL, NULL, NULL, 
                                &m_dwIndex, &m_cchMaxNameLen, &m_cbMaxValueLen,
                                NULL, NULL);
    hr = HRESULT_FROM_WIN32(lResult);
    if (SUCCEEDED(hr))
    {
        if (m_dwIndex != 0)
        {
            // Get max reg name size in characters
            UINT cchBufferSize = m_cchMaxNameLen;

            // Add 1 for nul terminator & convert to byte count
            if (!safeIntUAdd (cchBufferSize, 1, &cchBufferSize)
                || cchBufferSize > STRSAFE_MAX_CCH)
            {
                hr = HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
            }
            else
            {
                m_pszValueName = new (localalloc) TCHAR[cchBufferSize];
                if (m_pszValueName)
                {
                    m_pbData = new (localalloc) BYTE[m_cbMaxValueLen];
                    if (m_pbData)
                    {
                        hr = ReadCurrentData ();
                    }
                    else
                    {
                        hr = E_OUTOFMEMORY;
                    }
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                }
            }
        }
        else
        {
            hr = E_NOMOREITEMS;
        }
    }
    return hr;
}

/*
 *  CRegistryBufferIterator::Next
 *
 *  SUMMARY:
 *
 *      Advances to the next item in the registy enumeration
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 */
HRESULT CRegistryBufferIterator::Next ()
{
    HRESULT hr = E_NOMOREITEMS;

    // m_dwIndex will be 0 when we run out of data
    if (m_dwIndex != 0)
    {
        --m_dwIndex;
        hr = ReadCurrentData();
    }

    return hr;
}

/*
 *  CRegistryBuffer::~CRegistryBuffer
 *
 *  SUMMARY:
 *
 *      Cleans up any resources allocated by the CRegistryBuffer class
 */
CRegistryBuffer::~CRegistryBuffer ()
{
    ::RegCloseKey (m_hkeyBase);
    ::RegCloseKey (m_hkeyData);
}


/*
 *  CRegistryBuffer::InitEmptyBuffer
 *
 *  SUMMARY:
 *
 *      Helper function to create a new (empty) buffer in the registry
 *
 *  PARAMETERS:
 *
 *      nBufSize        [IN]    Max number of entries in the history store
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 */
HRESULT CRegistryBuffer::InitEmptyBuffer (DWORD nBufSize)
{
    HRESULT hr = E_UNEXPECTED;

    hr = m_nMaxSize.Set (nBufSize);
    if (SUCCEEDED (hr))
    {
        hr = m_nCurrentSize.Set(0);
        if (SUCCEEDED (hr))
        {
            hr = m_idxNext.Set(0);
        }
    }

    return hr;
}

/*
 *  CRegistryBuffer::InitBufferVars
 *
 *  SUMMARY:
 *
 *      Do an initial read/write of the variables used to control writing
 *      to the history store.
 *
 *  PARAMETERS:
 *
 *      fNew            [IN]    non-zero if store has just been created and
 *                              registry needs to be initialized with default
 *                              values. zero to read current values from the
 *                              registry
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 */
HRESULT CRegistryBuffer::InitBufferVars (BOOL fNew)
{
    HRESULT hr;

    hr = m_idxNext.Init (g_szNext, m_hkeyBase, fNew);
    if (SUCCEEDED (hr))
    {
        hr = m_nCurrentSize.Init (g_szCurrent, m_hkeyBase, fNew);
        if (SUCCEEDED(hr))
        {
            hr = m_nMaxSize.Init (g_szMax, m_hkeyBase, fNew);
        }
    }
    return hr;
}


/*
 *  CRegistryBuffer::Init
 *
 *  SUMMARY:
 *
 *      Initializes the registry based history store.
 *
 *  PARAMETERS:
 *
 *      nMaxSize        [IN]    The maximum number of entries in the store
 *
 *      pszRegKeyBase   [IN]    Name of the registry key to store the
 *                              history under. Assumed to be in the 
 *                              HKEY_LOCAL_MACHINE hive.
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 */
HRESULT CRegistryBuffer::Init (DWORD nMaxSize, LPCTSTR pszRegKeyBase)
{
    HRESULT hr = E_UNEXPECTED;
    BOOL    fIsNewKey;
    long    lResult;
    DWORD   dwDisposition;

    lResult = ::RegCreateKeyEx (HKEY_LOCAL_MACHINE, pszRegKeyBase, 
                                    0, NULL, 0, KEY_ALL_ACCESS, NULL, 
                                    &m_hkeyBase, &dwDisposition);
    hr = HRESULT_FROM_WIN32(lResult);
    if (SUCCEEDED (hr))
    {
        fIsNewKey = (dwDisposition == REG_CREATED_NEW_KEY);

        hr = InitBufferVars(fIsNewKey);
        if (SUCCEEDED(hr))
        {
            if (fIsNewKey)
            {
                hr = InitEmptyBuffer(nMaxSize);
            }
            
            if (SUCCEEDED (hr) && nMaxSize != 0)
            {
                lResult = ::RegCreateKeyEx (m_hkeyBase, g_szRegKeyData, 
                                                0, NULL, 0, KEY_ALL_ACCESS, NULL, 
                                                &m_hkeyData, &dwDisposition);
                hr = HRESULT_FROM_WIN32(lResult);
            }
        }
    }
    
    return hr;
}

/*
 *  CRegistryBuffer::Add
 *
 *  SUMMARY:
 *
 *      Adds a new entry to the history store
 *
 *  PARAMETERS:
 *
 *      pbData      [IN]    Pointer to a byte array containing the data to be
 *                          placed into the history store
 *
 *      cbData      [IN]    Size of the data (in bytes) to be stored
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 */
HRESULT CRegistryBuffer::Add (__in_ecount(cbData) const BYTE *pbData, DWORD cbData)
{
    TCHAR szName[gc_cchName];
    HRESULT hr = StringCchPrintf (szName, gc_cchName, 
                                    g_szNameFormatString, m_idxNext.Get());
    if (SUCCEEDED (hr))
    {
        const long lResult = ::RegSetValueEx (m_hkeyData, szName, 0,
                                                REG_BINARY, pbData, cbData);
        hr = HRESULT_FROM_WIN32(lResult);
        if (SUCCEEDED (hr))
        {
            // Bump the next pointer and wrap if necessary
            hr = m_idxNext.Set ((m_idxNext.Get() + 1) % m_nMaxSize.Get());
            if (SUCCEEDED(hr))
            {
                if (m_nCurrentSize.Get() != m_nMaxSize.Get())
                {
                    hr = m_nCurrentSize.Set (m_nCurrentSize.Get() + 1);
                }
            }
        }
    }
    return hr;
}

/*
 *  CRegistryBuffer::FindMatch
 *
 *  SUMMARY:
 *
 *      Find an entry in the history store
 *
 *  PARAMETERS:
 *
 *      fCompare        [IN]    Pointer to a callback function that will do
 *                              the comparison. Must return 0 when a match
 *                              is found
 *
 *      pbData          [IN]    Data to be found (not used by this function,
 *                              but passed to the comparison function
 *
 *      cbData          [IN]    Size of the data (in bytes) to be found
 *
 *      pfMatchFound    [OUT]   On success will be set to a non-zero value if
 *                              a matching entry was found.
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 *
 *  NOTES:
 *
 *      All entries in the store are examined even if a match is found before
 *      the last entry in the store is reached.
 */
HRESULT CRegistryBuffer::FindMatch (__in CFP fCompare, 
                                    __in_ecount (cbData) const BYTE *pbData, 
                                    DWORD cbData, 
                                    __out BOOL *pfMatchFound)
{
    HRESULT hr = E_UNEXPECTED;
    CRegistryBufferIterator rbi;

    hr = rbi.Init(m_hkeyData);
    if (SUCCEEDED(hr))
    {
        *pfMatchFound = FALSE;
        while (rbi.IsMoreData())
        {
            if ((*fCompare)(pbData, cbData, rbi.Data(), rbi.DataSize()) == 0)
            {
                *pfMatchFound = TRUE;
            }
            rbi.Next();
        }
    }
    else
    {
        if (hr == HRESULT_FROM_WIN32(ERROR_NO_MORE_ITEMS))
        {
            // Nothing in the history to check against
            *pfMatchFound = FALSE;
            hr = S_OK;
        }
    }

    return hr;
}

/*
 *  CRegistryBuffer::Resize
 *
 *  SUMMARY:
 *
 *      Resize an existing history store. All entries currently in the store
 *      will be lost.
 *
 *  PARAMETERS:
 *
 *      nNewSize        [IN]    The new size for the history store
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 */
HRESULT CRegistryBuffer::ReSize (DWORD nNewSize)
{
    HRESULT hr = E_INVALIDARG;
    LONG lResult;

    lResult = ::RegCloseKey (m_hkeyData);
    hr = HRESULT_FROM_WIN32(lResult);
    if (SUCCEEDED(hr))
    {
        lResult = ::RegDeleteKey (m_hkeyBase, g_szRegKeyData);
        hr = HRESULT_FROM_WIN32(lResult);
        if (SUCCEEDED(hr))
        {
            hr = InitEmptyBuffer (nNewSize);
            if (SUCCEEDED (hr) && nNewSize != 0)
            {
                DWORD dwDisposition;
                lResult = ::RegCreateKeyEx (m_hkeyBase, g_szRegKeyData, 
                                                0, NULL, 0, KEY_ALL_ACCESS, NULL, 
                                                &m_hkeyData, &dwDisposition);
                hr = HRESULT_FROM_WIN32(lResult);
            }
        }
    }
    return hr;
}

