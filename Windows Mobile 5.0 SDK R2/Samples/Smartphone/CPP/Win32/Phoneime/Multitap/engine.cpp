//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

// engine.cpp : Conversion Engine that implements MultiTap

#include <windows.h>
#include <windowsx.h>
#include <winuserm.h>
#include "..\phoneime.h"
#include "engine.h"

#define ARRAYSIZE(a)  (sizeof(a)/sizeof(a[0]))

#define NUM_KEYS 10

// Conversion Engine which maps a key to character
class CConvEngine
{
private:
    TCHAR m_chComposition;              // Composition character (converted character)
    UINT m_uVKey;                       // Current key that is being converted
    DWORD m_dwState;                    // State
    LPARAM m_lpUser;                    // User value returned in callback
    CONVENG_CALLBACK m_pfnCallBack;     // Callback to client
    LPCTSTR m_ppszChars[NUM_KEYS];      // Set of characters that keys map to when SHIFT is not set.  
    LPCTSTR m_ppszShiftChars[NUM_KEYS]; // Set of characters that keys map to when SHIFT is set.  
    
private:
    HRESULT GetNextCharacter(UINT uVKey, TCHAR chCurrent, TCHAR *pchNext);
    HRESULT LoadKeyData(LPCTSTR ppszChars[], int nKeys, LPCTSTR pszChars);
    LPCTSTR GetNextKeyData(LPCTSTR psz);
    void EndComposition(BOOL fClearShift);
    HRESULT ProcessSpellKey(UINT uVKey, TCHAR* pch);
    HRESULT ProcessNumbersKey(UINT uVKey, TCHAR* pch);

public:
    CConvEngine();

    HRESULT Init(CONVENG_CALLBACK pfnCallBack, LPARAM lpUser);
    HRESULT Terminate();
    HRESULT ProcessKey(UINT uVKey, TCHAR* pch);
    HRESULT SetState(DWORD dwState, DWORD dwMask);
    HRESULT GetState(DWORD* pdwState);
    HRESULT TimedOut();
};

// Initialize engine
HRESULT ConvEngine_Init(
    CONVENG_CALLBACK pfnCallBack,   // In: Client callback
    LPARAM lpUser,                  // In: Client user value 
    HCONVENG* phce                  // Out: Returns conversion 
)
{
    HRESULT hr;
    CConvEngine *pce = NULL;

    // Validate parameters
    if (!pfnCallBack || !phce)
    {
        hr = E_INVALIDARG;
        goto Error;
    }

    *phce = NULL;

    // Create conversion engine
    pce = new CConvEngine();
    if (!pce)
    {
        hr = E_OUTOFMEMORY;
        goto Error;
    }

    // Initialize
    hr = pce->Init(pfnCallBack, lpUser);
    if (FAILED(hr))
        goto Error;

    *phce = (HCONVENG)pce;

Exit:
    return hr;

Error:
    if (pce)
        delete pce;
    goto Exit;
}

// Terminate engine
HRESULT ConvEngine_Terminate(
    HCONVENG hce        // In: Conversion engine handle
)
{
    HRESULT hr;
    CConvEngine *pce;

    // Validate parameters
    if (!hce)
    {
        hr = E_INVALIDARG;
        goto Error;
    }
    pce = (CConvEngine *) hce;

    // Terminate
    hr = pce->Terminate();
    if (FAILED(hr))
        goto Error;

    // Free engine
    delete pce;

Error:
    return hr;
}

// Get state, like mode, composition string state etc.
HRESULT ConvEngine_GetState(
    HCONVENG hce,           // In: Conversion engine handle 
    DWORD* pdwState         // Out: Returns state     
)
{
    HRESULT hr;
    CConvEngine *pce;

    // Validate parameters
    if (!hce || !pdwState)
    {
        hr = E_INVALIDARG;
        goto Error;
    }

    *pdwState = 0;

    pce = (CConvEngine *) hce;

    // Get State
    hr = pce->GetState(pdwState);
    if (FAILED(hr))
        goto Error;

Error:
    return hr;
}

// Set state, like mode, composition string state etc.
HRESULT ConvEngine_SetState(
    HCONVENG hce,           // In: Conversion Engine handle 
    DWORD dwState,          // In: New state value 
    DWORD dwMask            // In: Mask for state bits that dwState is setting/clearing
)
{
    HRESULT hr;
    CConvEngine *pce;

    // Validate parameters
    if (!hce)
    {
        hr = E_INVALIDARG;
        goto Error;
    }
    pce = (CConvEngine *) hce;

    // Set state
    hr = pce->SetState(dwState, dwMask);
    if (FAILED(hr))
        goto Error;

Error:
    return hr;
}

// Process key by converting it to a character
HRESULT ConvEngine_ProcessKey(
    HCONVENG hce,       // In: Conversion Engine handle 
    UINT uVKey,         // In: Key being converted 
    TCHAR* pch          // Out: Character which key is converted to
)
{
    HRESULT hr;
    CConvEngine *pce;

    // Validate parameters
    if (!hce || !pch)
    {
        hr = E_INVALIDARG;
        goto Error;
    }

    *pch = 0;

    pce = (CConvEngine *) hce;

    // Process key
    hr = pce->ProcessKey(uVKey, pch);
    if (FAILED(hr))
        goto Error;

Error:
    return hr;
}

// Called by client whey MultiTap timer times out
HRESULT ConvEngine_TimedOut(
    HCONVENG hce            // In: Conversion Engine handle 
)
{
    HRESULT hr;
    CConvEngine *pce;

    // Validate parameters
    if (!hce)
    {
        hr = E_INVALIDARG;
        goto Error;
    }
    pce = (CConvEngine *) hce;

    // Timed Out
    hr = pce->TimedOut();
    if (FAILED(hr))
        goto Error;

Error:
    return hr;
}

// ------------------------------- CConvEngine --------------------------------

// Constructor
CConvEngine::CConvEngine()
{
    m_chComposition = 0;
    m_uVKey = 0;
    m_dwState = CE_SPELL_MODE;  // Default to spell mode
    m_lpUser = 0;
    m_pfnCallBack = NULL;
}

// Initialize engine
HRESULT CConvEngine::Init(
    CONVENG_CALLBACK pfnCallBack,       // In: Client callback 
    LPARAM lpUser                       // In: Client user value
)
{
    HRESULT hr;
    ASSERT(pfnCallBack);

    m_pfnCallBack = pfnCallBack;
    m_lpUser = lpUser;

    // Load chars into array
    LPCTSTR psz;
    psz = (LPCTSTR)LoadString(HINST_RESDLL, IDS_MTAP_CHARS, NULL, 0);
    ASSERT(psz);

    hr = LoadKeyData(m_ppszChars, ARRAYSIZE(m_ppszChars), psz);
    if (FAILED(hr))
    {
        ASSERT(0);
        goto Error;
    }

    // Load SHIFT chars into array
    psz  = (LPCTSTR)LoadString(HINST_RESDLL, IDS_MTAP_SHIFTCHARS, NULL, 0);
    ASSERT(psz);

    hr = LoadKeyData(m_ppszShiftChars, ARRAYSIZE(m_ppszShiftChars), psz);
    if (FAILED(hr))
    {
        ASSERT(0);
        goto Error;
    }

Error:
    return hr;
}

// Terminate engine
HRESULT CConvEngine::Terminate()
{
    return S_OK;
}

// Process key
HRESULT CConvEngine::ProcessKey(
    UINT uVKey,             // In: Key being converted 
    TCHAR* pch              // Out: Character which key is converted to
)
{
    HRESULT hr;
    ASSERT (pch && *pch == 0);

    // Process key based on input mode
    if (SPELL_MODE(m_dwState))
    {
        hr = ProcessSpellKey(uVKey, pch);
    }
    else if (NUMBERS_MODE(m_dwState))
    {
        hr = ProcessNumbersKey(uVKey, pch);
    }
    else 
    {
        ASSERT(0);  // Invalid mode
        hr = E_FAIL;
    }

    return hr;
}

// Process Key in Spell mode
HRESULT CConvEngine::ProcessSpellKey(
    UINT uVKey,         // In: Key being converted 
    TCHAR* pch          // Out: Character which key is converted to
)
{
    HRESULT hr = E_FAIL;

    ASSERT (pch && *pch == 0);

    if (uVKey >= VK_T0 && uVKey <= VK_T9) // Convert 0-9 keys
    {
        // Get next character which the key maps to
        hr = GetNextCharacter(uVKey, 
                    (m_uVKey == uVKey) ? m_chComposition : 0,  // First character in the set which key maps to?
                    &m_chComposition);
        if (FAILED(hr))
            goto Error;

        *pch = m_chComposition;

        // Get into insert mode (until timer fires or next is pressed)
        m_dwState |= CE_INSERT_MODE;

        // Ask client to start timer to time out the composition string
        CONVENG_REQUEST_DATA crd;
        crd.cbSize = sizeof(CONVENG_REQUEST_DATA);
        crd.cr = crSetTimer;
        hr = m_pfnCallBack((HCONVENG)this, &crd, (LPARAM)m_lpUser);
        if (FAILED(hr))
            goto Error; 

    }
    else if (uVKey == VK_TSTAR) // Process Shift key
    {
        // Ends composition mode
        EndComposition(FALSE);

        // Star key changes Shift state.
        // If in no shift state, change to Shift state.
        // If in Shift state, change to CapsLock state.
        // If in CapsLock state, change to no shift state.
        if (CAPSLOCK_MODE(m_dwState)) // In CapsLock state
        {
            // Change to no shift state.
            m_dwState &= ~(CE_CAPSLOCK_MODE | CE_SHIFT_MODE);
        }
        else if (SHIFT_MODE(m_dwState)) // in Shift state
        {
            // Change to CapsLock state.
            m_dwState |= CE_CAPSLOCK_MODE; 
        }
        else // in no shift state
        {
            // Change to Shift state.
            m_dwState |= CE_SHIFT_MODE;    
        }
    }
    else if (uVKey == VK_TLEFT || uVKey == VK_TRIGHT || uVKey == VK_TPOUND)
    {
        // Any of these keys end composition mode
        EndComposition(TRUE);
    }
    else
    {
        // Key which is not converted
        goto Error;
    }

    hr = S_OK;

Exit:
    // Remember key which was processed.
    m_uVKey = uVKey;
    return hr;

Error:
    goto Exit;
}

// Process Key in Numbers mode
HRESULT CConvEngine::ProcessNumbersKey(
    UINT uVKey,         // In: Key being converted 
    TCHAR* pch          // Out: Character which key is converted to
)
{
    HRESULT hr = E_FAIL;

    ASSERT(pch && *pch == 0);
    ASSERT(!INSERT_MODE(m_dwState));

    if ((uVKey >= VK_T0 && uVKey <= VK_T9) || uVKey == VK_TSTAR || uVKey == VK_TPOUND)
    {
        // These keys convert to themselves
        *pch = (TCHAR)uVKey;
    }
    else if (uVKey == VK_TLEFT || uVKey == VK_TRIGHT)
    {
        // These keys don't convert to anything
    }
    else
    {
        // Key which is not converted
        goto Error;
    }

    hr = S_OK;

Exit:
    return hr;

Error:
    goto Exit;
}

// Set state, like mode, composition string state etc.
HRESULT CConvEngine::SetState(
    DWORD dwNewState,       // In: New state value  
    DWORD dwMask            // In: Mask for state bits that dwState is setting/clearing
)
{
    DWORD dwOldState;
    HRESULT hr = E_FAIL;
    
    dwOldState = m_dwState;

    if (dwMask)
    {
        dwNewState = (m_dwState & ~dwMask) | (dwNewState & dwMask);
    }

    // A major input mode must be set 
    if (!(dwNewState & (CE_NUMBERS_MODE | CE_SPELL_MODE)))
    {
        ASSERT(0);
        hr = E_INVALIDARG;
        goto Error;
    }

    m_dwState = dwNewState;

    // Spell mode changed
    if ((dwOldState ^ m_dwState) & CE_SPELL_MODE) 
    {
        // Change to Spell mode
        if (m_dwState & CE_SPELL_MODE)
        {
            m_dwState &= ~CE_NUMBERS_MODE;
        }
        EndComposition(TRUE);
    }

    // Numbers mode changed
    if ((dwOldState ^ m_dwState) & CE_NUMBERS_MODE) 
    {
        // Change to Numbers mode
        if (m_dwState & CE_NUMBERS_MODE)
        {
            m_dwState &= ~CE_SPELL_MODE;
        }
        EndComposition(TRUE);
    }

    // Must be in a major input mode
    ASSERT(SPELL_MODE(m_dwState) || NUMBERS_MODE(m_dwState)); 

    hr = S_OK;

Error:
    return hr;
}

// Get state, like mode, composition string state etc.
HRESULT CConvEngine::GetState(
    DWORD* pdwState             // Out: Returns state
)
{
    ASSERT(pdwState);

    *pdwState = m_dwState;
    return S_OK;
}

// Time out multitap timer
HRESULT CConvEngine::TimedOut()
{
    // End the composition mode
    EndComposition(TRUE);
    return S_OK;
}

// Get next character a key maps
HRESULT CConvEngine::GetNextCharacter(
    UINT uVKey,             // In: Key
    TCHAR chCurrent,        // In: Current character key maps to
    TCHAR *pchNext          // Out: Next character key maps to
)
{
    HRESULT hr = E_FAIL;
    ASSERT(uVKey >= VK_T0 && uVKey <= VK_T9);
    ASSERT(pchNext);

    *pchNext = 0;

    // In ext spell mode, get next character from client
    if (EXTSPELL_MODE(m_dwState))
    {
        CONVENG_REQUEST_DATA crd;
        crd.cbSize = sizeof(CONVENG_REQUEST_DATA);
        crd.cr = crNextSymbol;
        crd.info.si.uVKey = uVKey;
        crd.info.si.chSymbol = chCurrent;
        hr = m_pfnCallBack((HCONVENG)this, &crd, (LPARAM)m_lpUser);
        if (FAILED(hr))
            goto Error; 

        *pchNext = crd.info.si.chSymbol;
    } 
    else
    {
        // Get character set which this key maps to
        LPCTSTR pszChars;
        if (SHIFT_MODE(m_dwState))
            pszChars = m_ppszShiftChars[uVKey - VK_T0];
        else
            pszChars = m_ppszChars[uVKey - VK_T0];

        if (!pszChars)
        {
            ASSERT(0); // No characters for this key to map to
            goto Error;
        }

        if (chCurrent == 0) // Return first symbol
        {         
             *pchNext = pszChars[0];
        }
        else // Return next symbol
        {
            // Find symbol that was returned previously
            int n, nLen;
            nLen = lstrlen(pszChars);
            for (n = 0; n < nLen; n++)
            {
                if (pszChars[n] == chCurrent)
                {
                    // Return next symbol
                   n = (n+1) % nLen;
                   *pchNext = pszChars[n];
                   hr = S_OK;
                   goto Exit;
                }
            }

            ASSERT(0); // Couldn't find prev. symbol
            goto Error;
        }
    }

    hr = S_OK;

Exit:
    return hr;

Error:
    goto Exit;
}

// Load sets of characters that keys map to
HRESULT CConvEngine::LoadKeyData(
    LPCTSTR ppszChars[],        // Out: Array into which character sets are to be loaded
    int nKeys,                  // In: Number of keys
    LPCTSTR pszChars            // In: String that contains the characters. Each set is NULL terminated.
)
{
    int n;
    HRESULT hr = E_FAIL;

    ASSERT(ppszChars);
    ASSERT(pszChars);

    // Load each key's character set
    for (n = 0; n < nKeys; n++)
    {
        if (!pszChars)
        {
            ASSERT(0); // Resource data is wrong
            goto Error;
        }
        ppszChars[n] = pszChars;
        // Get next key's set
        pszChars = GetNextKeyData(pszChars);
    }

    hr = S_OK;

Error:
    return hr;
}

// Get pointer to next character set (character sets are seperated
// by NULL)
LPCTSTR CConvEngine::GetNextKeyData(
    LPCTSTR psz     // In: Pointer to beginning of current character set
)
{
    if (!psz || !*psz)
        return NULL;

    // Move to end of current character set (terminated by NULL)
    while (*psz)
         psz++;

    // Return beginning of next character set
    return (++psz);
}

// End composition mode
void CConvEngine::EndComposition(
    BOOL fClearShift    // In: TRUE to clear Shift state
)
{
    // Get out of insert mode
    if (INSERT_MODE(m_dwState))
    {
        m_dwState &= ~CE_INSERT_MODE;
    }

    // Clear SHIFT mode if CAPSLOCK is not set
    if (fClearShift && SHIFT_MODE(m_dwState) && !CAPSLOCK_MODE(m_dwState))
    {
        m_dwState &= ~CE_SHIFT_MODE;
    }

    m_uVKey = 0;
    m_chComposition = 0;
}
