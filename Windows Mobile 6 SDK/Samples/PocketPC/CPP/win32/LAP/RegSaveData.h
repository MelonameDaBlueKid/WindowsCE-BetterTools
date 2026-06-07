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
// Copyright (c) Microsoft Corporation. All rights reserved.
//
#pragma once


// Typedef for the Comparision Function Pointer passed to CRegistryBuffer::FindMatch as the first parameter
typedef int (*CFP) (__in_ecount (cbDataA) const BYTE *pbDataA, DWORD cbData, __in_ecount (cbDataB) const BYTE *pbDataB, DWORD cbDataB);

// Forward declarations
class CRegistryBufferIterator;

/*
 *  CRegDWORD
 *
 *  SUMMARY:
 *
 *      Helper class implementing variables that are persisted in the registry.
 */
class CRegDWORD
{
    public:
        explicit CRegDWORD () : m_pszValueName(NULL), m_dwValue(0) {};

        HRESULT Init (__in LPCTSTR pszValueName, __in HKEY hKey, BOOL fNew);

        DWORD Get () const;
        HRESULT Set (DWORD dwNew);

    private:
        // Leave these functions unimplemented to prevent copying
        CRegDWORD (const CRegDWORD &);
        CRegDWORD & operator = (const CRegDWORD &);

    private:
        HKEY        m_hKey;
        LPCTSTR     m_pszValueName;
        DWORD       m_dwValue;
};


/*
 *  CRegistryBuffer
 *
 *  SUMMARY:
 *
 *      History store implementation
 */
class CRegistryBuffer
{
    public:
        explicit CRegistryBuffer() : m_hkeyBase (0), m_hkeyData (0) {};
        ~CRegistryBuffer ();

        HRESULT Init (DWORD nMaxSize, LPCTSTR pszRegKeyBase);
        HRESULT Add (__in_ecount(cbData) const BYTE *pbData, DWORD cbData);

        HRESULT FindMatch (__in CFP fCompare, __in_ecount (cbData) const BYTE *pbData, DWORD cbData, __out BOOL *pfMatchFound);
        HRESULT ReSize (DWORD nNewSize);
        DWORD   MaxSize () { return m_nMaxSize.Get(); };

    private:
        // Leave these functions unimplemented to prevent copying
        CRegistryBuffer (const CRegistryBuffer &);
        CRegistryBuffer & operator = (const CRegistryBuffer &);

    private:
        // Initialization Helpers
        HRESULT InitEmptyBuffer (DWORD nBufSize);
        HRESULT InitBufferVars (BOOL fNew);
        
    private:
        CRegDWORD   m_nMaxSize;
        CRegDWORD   m_nCurrentSize;
        CRegDWORD   m_idxNext;

        HKEY        m_hkeyBase;
        HKEY        m_hkeyData;
};


inline HRESULT CRegDWORD::Init (__in LPCTSTR pszValueName, __in HKEY hKey, BOOL fNew)
{
    HRESULT hr = E_UNEXPECTED;

    m_pszValueName = pszValueName;
    m_hKey = hKey;

    if (fNew)
    {
        m_dwValue = 0;
        hr = RegistrySetDWORD (m_hKey, NULL, m_pszValueName, m_dwValue);
    }
    else
    {
        hr = RegistryGetDWORD (m_hKey, NULL, m_pszValueName, &m_dwValue);
    }
    return hr;
}

inline DWORD CRegDWORD::Get () const
{
    return m_dwValue;
}

inline HRESULT CRegDWORD::Set (DWORD dwNew)
{
    HRESULT hr = E_UNEXPECTED;

    hr = RegistrySetDWORD (m_hKey, NULL, m_pszValueName, dwNew);
    if (SUCCEEDED (hr))
    {
        m_dwValue = dwNew;
    }
    return hr;
}

