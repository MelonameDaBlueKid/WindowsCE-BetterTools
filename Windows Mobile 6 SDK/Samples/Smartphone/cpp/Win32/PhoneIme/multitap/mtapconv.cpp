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

//  MtapConv.cpp : CMTapConverter class implemention. Conversion engine wrapper.

#include "mtapconv.h"
#include "mtapime.h"
#include <winuser.h>
#include <winuserm.h>
#include <aygshell.h>

// compile-time assert
#ifndef CASSERT
#define CASSERT(e)  extern int dummary_array[(e)]
#endif

// Major modes in converter. Order must be same as the IM_ definitions
const UINT g_uModes[NUM_MODES] = 
{
    CE_SPELL_MODE,               // Multi-press
    0,                           // Ambig mode not supported by this engine
    CE_NUMBERS_MODE              // Numbers
};

// Compile time verification that CONVMODE_ definitions are the in the same order
// as g_uModes entries 
CASSERT(IM_SPELL == 0 && IM_AMBIG == 1 && IM_NUMBERS == 2);

// Create converter
CConverter* CreateConverter()
{
    CMTapConverter* pMTapConverter = new CMTapConverter;

    return (CConverter*)pMTapConverter;
}

// Delete converter
void DeleteConverter(CConverter* pConverter)
{
    if (pConverter)
    {
        delete (CMTapConverter*)pConverter;
    }
}

// Constructor
CMTapConverter::CMTapConverter()
{
    m_hce = NULL;
    m_uTimerID = 0;
    m_pszCustomSymbols = NULL;
    m_cchCustomSymbols = 0;
    m_modeIcon = SHIME_MODE_NONE;
    m_fInited = FALSE;
    m_fInCustomSymbolSequencing = FALSE;
    m_dwMultiPressTimeOut = MULTIPRESS_TIMER_PERIOD;

    // Don't call Init. CMTapConverter is lazily inited.
}

// Destructor
CMTapConverter::~CMTapConverter()
{
    UnInit();
}

// Timer to support Multipress processing
VOID CALLBACK MultiPressTimerProc(
      HWND hwnd,         // handle to window
      UINT uMsg,         // WM_TIMER message
      UINT uID,          // timer identifier
      DWORD dwTime       // current system time
)
{
    UNREFERENCED_PARAMETER(hwnd);
    UNREFERENCED_PARAMETER(uMsg);
    UNREFERENCED_PARAMETER(dwTime);

    CRITICAL crit(&g_cs);
    CMTapIME *pime;

    pime = (CMTapIME*) TlsGetValue(g_dwTLS);
    if (!pime)
    {
        ASSERT(0); // Investigate why this failed.
        KillTimer(NULL, uID); // At least kill timer
        goto Exit;
    }

    pime->GetMTapConverter()->OnMultiPressTimer();

Exit:
    return;
}

// Conversion engine callback
HRESULT CMTapConverter::ConvEngine_Callback(
    HCONVENG hce, 
    CONVENG_REQUEST_DATA* crd,
    LPARAM lpUser
)
{
    CMTapConverter *pconv;
    HRESULT hr = E_FAIL;


    pconv = (CMTapConverter *) lpUser;
    if (!pconv)
    {
        ASSERT(0);
        goto Error;
    }

    hr = pconv->OnConvEngineRequest(hce, crd);  
    
Error:
    return hr;
}

// Handle requests from converter engine
HRESULT CMTapConverter::OnConvEngineRequest(
    HCONVENG hce, 
    CONVENG_REQUEST_DATA* pcrd
)
{
    UNREFERENCED_PARAMETER(hce);

    HRESULT hr; 

    switch (pcrd->cr)
    {
    case crSetTimer:
        // Provide timer to time multi-press sequencing
        hr = SetMultiPressTimer();
        break;

    case crNextSymbol:
        // Provide next custom symbol.
        hr = NextCustomSymbol(pcrd);
        break;

    default:
        ASSERT(0); // Not implemented
        hr = E_FAIL;
        goto Error;
    }

Error:
    return hr;
}

static LPCTSTR c_szAccessibility = TEXT("ControlPanel\\Accessibility");
static LPCTSTR c_szMultiTimeout = TEXT("CharTimeout");

// Load MultiPress timout value from registry
void CMTapConverter::LoadMultiPressTimeOut()
{
    HKEY hkey = NULL;

    if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, c_szAccessibility, 0, KEY_READ, &hkey))
    {
        ASSERT(0);
        goto Error;
    }

    DWORD cb;
    DWORD dwTimeOut;
    cb = sizeof(dwTimeOut);
    if (ERROR_SUCCESS != RegQueryValueEx(hkey, c_szMultiTimeout, NULL, NULL, (BYTE*)&dwTimeOut, &cb))
        goto Error;
    ASSERT(cb == sizeof(dwTimeOut));

    m_dwMultiPressTimeOut = dwTimeOut;

Exit:
    if (hkey)
        RegCloseKey(hkey);
    return;

Error:
    // Use a default timeout if it can't be read from registry
    m_dwMultiPressTimeOut = MULTIPRESS_TIMER_PERIOD;
    goto Exit;
}

// Set timer to support multi-press
HRESULT CMTapConverter::SetMultiPressTimer()
{
    HRESULT hr;

    if (m_uTimerID)
        KillTimer(NULL, m_uTimerID);
    if (m_dwMultiPressTimeOut != MULTIPRESS_TIMEOUT_DISABLED)
    {
        m_uTimerID = SetTimer(NULL, 0, m_dwMultiPressTimeOut, MultiPressTimerProc); 
        if (!m_uTimerID)
        {
            hr = E_FAIL;
            goto Error;
        }
    }
    else
    {
        // User has asked that timeout never happen. Composition string will
        // be converted to result string when user presses another key.
        m_uTimerID = 0;
    }

    hr = S_OK;

Error:
    return hr;
}

// Kill timer to support multi-press
void CMTapConverter::KillMultiPressTimer()
{
    if (m_uTimerID)
        KillTimer(NULL, m_uTimerID);
    m_uTimerID = 0;
}

// Notify Conversion engine when the multi-press timer fires
void CMTapConverter::OnMultiPressTimer()
{
    KillMultiPressTimer();

    if (!m_fInited)
    {
        ASSERT(0);
        return;
    }

    // Notify engine of timeout
    VERIFY(SUCCEEDED(ConvEngine_TimedOut(m_hce)));

    // Notify IME that the seqencing has timed out, so that it
    // can convert the composition string to a result string.
    if (m_pime)
    {
        m_pime->OnMultiPressSequencingTimeOut();
    }
    else
    {
        ASSERT(0);
    }
}

// Initialize converter
BOOL CMTapConverter::Init()
{
    HRESULT hr;
    HBITMAP hbm = NULL;

    BOOL fRet = FALSE;

    // Already initialized?
    if (m_fInited)
    {
        fRet = TRUE;
        goto Exit;
    }

    // Initialize conversion engine
    hr = ConvEngine_Init(ConvEngine_Callback, (LPARAM)this, &m_hce);
    if (FAILED(hr))
        goto Error;

    // Set default mode
    VERIFY(SUCCEEDED(ConvEngine_SetState(m_hce, CE_SPELL_MODE, CE_SPELL_MODE)));


    // Tell the shell which icons to display when we are in one of our custom input modes.
    // Also see CMTapConverter::SetModeIcon().
    hbm = LoadBitmap(HINST_RESDLL, MAKEINTRESOURCE(IDB_CUSTOMINPUT));
    SHImeSetCustomInputIcons(hbm);


    m_fInited = TRUE;
    fRet = TRUE;

Exit:

    DeleteObject(hbm);

    return fRet;

Error:
    // Terminate Engine
    if (m_hce)
    {
        ConvEngineCleanUp();
    }
    m_fInited = FALSE;
    goto Exit;
}

void CMTapConverter::ConvEngineCleanUp()
{
    if (m_hce)
    {
        VERIFY(SUCCEEDED(ConvEngine_Terminate(m_hce)));
        m_hce = NULL;
    }
}

void CMTapConverter::UnInit()
{
    if (!m_fInited)
        return;

    // Terminate Engine
    ConvEngineCleanUp();
    ClearCustomSymbols();
    m_fInited = FALSE;
}

// Set IME for callbacks.
void CMTapConverter::SetIME(
    CMTapIME *pime
)
{
    m_pime = pime;
}

// Process a key
BOOL CMTapConverter::ProcessKey(
    TCHAR ch
)
{
    HRESULT hr;
    BOOL fRet = FALSE;

    if (!m_fInited)
    {
        ASSERT(0);
        goto Error;
    }

    hr = ConvEngine_ProcessKey(m_hce, ch, &m_chConvBuffer);
    if (FAILED(hr))
    {
        goto Error;
    }

    fRet = TRUE;

Error:
    return fRet;
}

// Convert a key to a composition/result character
//
// Return Values:
// Returns pointer to the restul/composition character in m_chConvBuffer
// pcchResult : Returns number of characters in the result string caused by
//      processing of ch. -1 on failure.
// pcchComp: Passed in the original composition string length. Returns number of
//      composition characters. -1 on failure.
//

LPTSTR CMTapConverter::Convert(
    TCHAR ch,          // In: Key to be converted.
    int *pcchResult,   // Out: Number of characters in result string caused by processing of ch.
    int *pcchComp      // In/Out: Passed in the original composition string length. Returns number of characters in composition string.
)  
{
    LPTSTR pszRet = NULL;
    *pcchResult = *pcchComp = -1;
    
    if (!m_fInited)
    {
        ASSERT(0);
        goto Error;
    }

    // Process character
    if (!ProcessKey(ch))
        goto Error;

    // Set number of characters converted to result and the number of characters
    // in composition after ch is processed.
    DWORD dwState;
    HRESULT hr;
    hr = ConvEngine_GetState(m_hce, &dwState);
    if (FAILED(hr))
    {
        ASSERT(0);
        goto Error;
    }
    if (INSERT_MODE(dwState))
    {
        *pcchResult =  0;
        *pcchComp = 1;
    }
    else
    {
        *pcchResult =  1;
        *pcchComp = 0;
    }
   
    // Update Shift state icon if necessary.
    // (The Shift state (not CAPS lock) is cleared after the a new key is pressed.)
    SetModeIcon(TRUE);

    // return a pointer to the beginning of the new result and composition.
    pszRet = &m_chConvBuffer;

Error:
    return pszRet;
}

// Clear composition string
void CMTapConverter::ClearComposition()
{
    DWORD dwState;
    HRESULT hr;

    hr = ConvEngine_GetState(m_hce, &dwState);
    if (FAILED(hr))
    {
        ASSERT(0);
        goto Error;
    }

    // Clear composition string.
    // If a multipress timer is active, kill it and process it now because the converter 
    // is being cleared. Otherwise the timer will fire later.
    if (INSERT_MODE(dwState))
    {
        OnMultiPressTimer();
        ASSERT(!m_uTimerID);
    }

Error:
    return;
}

// Set mode
BOOL CMTapConverter::SetMode(
    UINT uMode,
    BOOL fSet,      // In: TRUE to set. FALSE to clear.
    BOOL fSetIcon   // In: Reset icon?
)
{
    BOOL fRet = FALSE;
    HRESULT hr;

    if (!m_fInited)
    {
        // The converter may be asked to set mode before the first key is
        // pressed (at which point lazy initialization takes place). So initialize
        // lazily here too.
        if (!Init())   
            goto Error;
    }

    if (uMode == 0)
    {
        ASSERT(0); // Invalid mode
        goto Error;
    }

    hr = ConvEngine_SetState(m_hce, fSet ? uMode : 0, uMode);
    if (FAILED(hr))
    {
        ASSERT(0); // SetMode failed
        goto Error;
    }

    // Set mode icon in tray
    if (fSetIcon)
    {
        SetModeIcon(TRUE); 
    }
    fRet = TRUE;
 
Error:
    return fRet;
}

// Returns mode. Returns major modes: Spell, Ambig and Numbers. Also
// return Shift and CapsLock states.
// Else returns -1;
int CMTapConverter::GetInputMode()
{
    int nRet = -1;

    // Verify g_uMode elements are the same order as IM_ values
    ASSERT(g_uModes[IM_SPELL] == CE_SPELL_MODE && 
           g_uModes[IM_AMBIG] == 0 && 
           g_uModes[IM_NUMBERS] == CE_NUMBERS_MODE);

    if (!m_fInited)
    {
        goto Exit;
    }

    // Get state
    DWORD dwState;
    if (FAILED(ConvEngine_GetState(m_hce, &dwState)))
    {
        goto Exit;
    }

    // Get major mode
    if (NUMBERS_MODE(dwState))
        nRet = IM_NUMBERS;
    else if (SPELL_MODE(dwState))
        nRet = IM_SPELL;
    else 
    {
        ASSERT(0); // Not in a major mode
        goto Exit;
    }

    // Get Modifiers
    if (SHIFT_MODE(dwState))
        nRet |= IMMF_SHIFT;        
    if (CAPSLOCK_MODE(dwState))
        nRet |= IMMF_CAPSLOCK;

Exit:
    return nRet;
}

// Set input mode. This sets only the major modes: Spell, Ambig and Numbers, Shift & Caps Lock.
// Use SetMode to set other modes.
BOOL CMTapConverter::SetInputMode(int nMode)
{
    BOOL fRet = FALSE;
    BOOL fSetModeIcon = FALSE;
    int nModifier = nMode & IMMF_MASK;
    nMode &= IM_MASK;

    switch(nMode)
    {
    case IM_SPELL:
    case IM_NUMBERS:
        if (!SetMode(g_uModes[nMode], TRUE, FALSE))
            goto Exit;
        break;

    case IM_AMBIG:
        // Not supported. Set to Spell mode instead.
        if (!SetMode(g_uModes[IM_SPELL], TRUE, FALSE))
            goto Exit;
        break;
                
    default:
        ASSERT(0);  // Invalid input mode
        goto Exit;
    }

    fSetModeIcon = TRUE;

    // Set/Clear Shift/CapsLock modifiers if necessary
    if (nModifier & IMMF_SETCLR_SHIFT)
    {
        if (!SetMode(CE_SHIFT_MODE, (nModifier & IMMF_SHIFT), FALSE))
            goto Exit;
    }
    if (nModifier & IMMF_SETCLR_CAPSLOCK)
    {
        if (!SetMode(CE_CAPSLOCK_MODE, (nModifier & IMMF_CAPSLOCK), FALSE))
            goto Exit;
    }

    fRet = TRUE;

Exit:
    // Set icon in tray.
    if (fSetModeIcon)
        SetModeIcon(TRUE); 

    return fRet;
}

// Set icon corresponding to current mode
void CMTapConverter::SetModeIcon(
    BOOL fSet // TRUE to set. FALSE to clear
)
{
    int nMode;
    SHIME_MODE modeIcon;


    DWORD nCustomMode;


    // Get current mode icon
    if (fSet)
    {
        nMode = GetInputMode();
        if (-1 == nMode)
            goto Exit;

        BOOL fCaps, fCapsLock;
        fCaps = (nMode & IMMF_SHIFT);
        fCapsLock = (nMode & IMMF_CAPSLOCK);

        switch(nMode & IM_MASK)
        {
        case IM_SPELL:
            if (fCapsLock)
                modeIcon = SHIME_MODE_SPELL_CAPS_LOCK;
            else if (fCaps)
                modeIcon = SHIME_MODE_SPELL_CAPS;
            else
                modeIcon = SHIME_MODE_SPELL;
            break;

        case IM_AMBIG:
            if (fCapsLock)
                modeIcon = SHIME_MODE_AMBIGUOUS_CAPS_LOCK;
            else if (fCaps)
                modeIcon = SHIME_MODE_AMBIGUOUS_CAPS;
            else
                modeIcon = SHIME_MODE_AMBIGUOUS;
            break;

        case IM_NUMBERS:

            // The following two lines, along with the call SHImeSetModeIcon() below,
            // illustrate how to provide custom icons for custom input modes (or even 
            // for a standard input mode).
            modeIcon = SHIME_MODE_CUSTOM;
            nCustomMode = 0;  // This is the index of the icon to use within the HBITMAP 
                           // passed to SHImeSetCustomInputIcons()

            break;

        default:
            modeIcon = SHIME_MODE_NONE;
            break;
        }
    }
    else
    {
        modeIcon = SHIME_MODE_NONE;
    }

    // Don't set the mode icon if current icon is the same as the prev.
    if (modeIcon == m_modeIcon)
        goto Exit;

    m_modeIcon = modeIcon;

    // Set the mode icon in the tray

    SHImeSetModeIcon(m_modeIcon, (m_modeIcon == SHIME_MODE_CUSTOM) ? nCustomMode : 0);


Exit:
    return;
}

// Force redraw of mode icon.
void CMTapConverter::RedrawModeIcon()
{
    m_modeIcon = SHIME_MODE_NONE; 
    SetModeIcon(TRUE);
}

// Process Shift key. If the user presses it once, only the next key is shifted.
// If the user presses it twice in successsion, the shift key is locked until
// Shift is pressed again to cancel ShiftLock. 
void CMTapConverter::ProcessShiftKey()
{
    ProcessKey(VK_TSTAR);
    SetModeIcon(TRUE); 
}

// Change to next mode (Multipress or Numbers)
void CMTapConverter::NextMode(BOOL fSkipAmbigMode)
{
    UNREFERENCED_PARAMETER(fSkipAmbigMode);

    int nMode = GetInputMode();
    if (nMode == -1)
    {
        // Not in one of the major modes (Spell, Ambiguous or Numbers).
        // Set to Multipress
        SetMode(g_uModes[IM_SPELL], TRUE, TRUE);
    }
    else
    {
        // Move to next mode
        nMode &= IM_MASK;
        nMode = (nMode+1) % NUM_MODES;

        // Skip Ambig mode which is not supported by this converter
        if (nMode == IM_AMBIG)
            nMode = (nMode+1) % NUM_MODES;

/*      If this converter supported Ambig mode, it would use code like
        the following:

        // Skip Ambig mode if the window doesn't want it
        if (nMode == IM_AMBIG && fSkipAmbigMode)
        {
            nMode = (nMode+1) % NUM_MODES;
        }
*/
        SetMode(g_uModes[nMode], TRUE, TRUE);
    }
}

// Set or clear conversion engine's custom symbol mode
BOOL CMTapConverter::SetCustomSymbolMode(BOOL fSet)
{
    if (fSet && !m_pszCustomSymbols)
    {
        ASSERT(0);  // No symbols and we are being asked to set custom symbol mode
        return FALSE;
    }
    return SetMode(CE_EXTSPELL_MODE, fSet, TRUE);
}

// Set custom symbols to be used for the 1 key in multi-press mode.

BOOL CMTapConverter::SetCustomSymbols(
    LPTSTR pszSymbols // In: Symbols. Pass NULL to clear the symbols.
)
{   

    // Uninit custom symbol mode
    if (!pszSymbols)
    {
        UnInitCustomSymbolsProcessing();
    }

    // Clear previous symbols, if any
    ClearCustomSymbols();

    // Set new symbols
    if (pszSymbols)
    {
        m_cchCustomSymbols = lstrlen(pszSymbols);
        m_pszCustomSymbols = _tcsdup(pszSymbols);

        // If the last key that was pressed was 1, re-enter custom symbol mode if necessary.
        // Otherwise it will be entered when 1 is pressed next.
        if (VK_T1 == m_pime->GetPrevKey())
        {
            InitCustomSymbolsProcessing();
        }

        DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: Custom symbols = %s\r\n"), m_pszCustomSymbols));
    }

    return TRUE;
}

// Clear custom symbols.
void CMTapConverter::ClearCustomSymbols()
{
    if (m_pszCustomSymbols)
    {
        LocalFree(m_pszCustomSymbols);
        m_pszCustomSymbols = NULL;
    }
    m_cchCustomSymbols = 0;
}

// If not in custom symbol mode, get into that mode.
void CMTapConverter::InitCustomSymbolsProcessing()
{
    if (IM_SPELL == (GetInputMode() & IM_MASK)
        && m_cchCustomSymbols > 0 
        && !m_fInCustomSymbolSequencing)
    {
        m_fInCustomSymbolSequencing = !!SetCustomSymbolMode(TRUE);
    }
}

// If in custom symbol mode, get out of that mode.
void CMTapConverter::UnInitCustomSymbolsProcessing()
{
    if (m_fInCustomSymbolSequencing)
    {
        if (SetCustomSymbolMode(FALSE))
            m_fInCustomSymbolSequencing = FALSE;
    }
}


// Provide the conversion engine callback with the next custom symbol.
HRESULT CMTapConverter::NextCustomSymbol(
    CONVENG_REQUEST_DATA* pcrd)
{
    HRESULT hr;

    if (!m_pszCustomSymbols || m_cchCustomSymbols <= 0)
    {
        ASSERT(0); // Symbols must be available
        goto Error;
    }

    if (pcrd->cr != crNextSymbol)
    {
        ASSERT(0); // Wrong request
        goto Error;
    }

    if (pcrd->info.si.uVKey != VK_T1)
    {
        ASSERT(0); // Only the 1 key provides custom symbols
        goto Error;
    }

    TCHAR chSymbol;
    chSymbol = pcrd->info.si.chSymbol;

    // Return first symbol
    if (chSymbol == 0)
    {
         pcrd->info.si.chSymbol = m_pszCustomSymbols[0];
         hr = S_OK;
         goto Exit;
    }

    // Find symbol that was returned previously
    int n;
    for (n = 0; n < m_cchCustomSymbols; n++)
    {
        if (m_pszCustomSymbols[n] == chSymbol)
        {
            // Return next symbol
           n = (n+1) % m_cchCustomSymbols;
           pcrd->info.si.chSymbol = m_pszCustomSymbols[n];
           hr = S_OK;
           goto Exit;
        }
    }

    ASSERT(0); // Conversion engine provided a previous symbol that we don't have
    goto Error;

Exit:
    return hr;

Error:
    hr = E_FAIL;
    goto Exit;
}

// Scan contents of window for user words and add them
// to the user database.
BOOL CMTapConverter::AddToUserDatabase(
    HWND hwnd       // In: Window whose text is to be scanned for words to
                    // add to the user database.
)
{
    UNREFERENCED_PARAMETER(hwnd);

    // Not implemented
    return TRUE;
}

// Save user database information in shared memory to 
// the database file.
BOOL CMTapConverter::SaveUserDatabase()
{
    // Not implemented
    return TRUE;
}
