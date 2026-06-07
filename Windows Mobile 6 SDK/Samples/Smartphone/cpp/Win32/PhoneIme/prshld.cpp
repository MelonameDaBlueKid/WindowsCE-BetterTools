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

// PrsHld.cpp : IME wrapper for input converter. 
//              CPressHoldDetectorclass implemention.

#include "phoneime.h"

/*
    The Press&Hold detector detects if a key has been pressed and held for a
    given time period. It notifies the IME with CIME::OnPressHold at the
    end of the time period. Optionally, the detector can reset at the end of 
    a Press&Hold time period and start a new period, so that multiple 
    Press&Hold events are generated while the user has the key pressed. In this 
    case, the detector will notify the IME with OnPressHold at the end of each 
    time period and with OnPressHoldEnd at the end of all time periods.
*/
#define DLY_KEYHOLD      850    // default (850 ms)
#define DLY_KEYHOLD_MAX 5000    // 5 sec. Max value for press and hold key time.

// Constuctor
CPressHoldDetector::CPressHoldDetector()
{
    m_uVKey = 0;
    m_dwStart = 0;
    m_fPressHold = FALSE;
    m_fPressHoldOnce = FALSE;
    m_fMultiple = FALSE;
    m_dwHoldTimeOut = 0;
}

// Set IME for callbacks.
void CPressHoldDetector::SetIME(
    CIME *pime
)
{
    m_pime = pime;
}

// Start detecting Press&Hold. Called when a key is pressed.
void CPressHoldDetector::Set(
    UINT uVKey,    // In: Key to detect
    BOOL fMultiple // In: Should multiple Press&Hold time periods be used?
)
{
    m_uVKey = uVKey;
    m_dwStart = GetTickCount();
    m_fPressHold = FALSE;
    m_fMultiple = !!fMultiple;
    m_fPressHoldOnce = FALSE;

    // Lazily load timeout from registry
    if (!m_dwHoldTimeOut)
    {
        HKEY hkey = NULL;
        m_dwHoldTimeOut = DLY_KEYHOLD; // default value

        // Registry can override the default value
        RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("ControlPanel\\Accessibility"), 0, 
                     KEY_QUERY_VALUE, &hkey);
        if (hkey)
        {
            DWORD dwSize = sizeof(m_dwHoldTimeOut);
            if (RegQueryValueEx(hkey, 
                    TEXT("HoldTimeOut"), 
                    NULL, 
                    NULL,
                    (LPBYTE)&m_dwHoldTimeOut,
                    &dwSize) == ERROR_SUCCESS)
            {
                if (m_dwHoldTimeOut > DLY_KEYHOLD_MAX)
                {
                    m_dwHoldTimeOut = DLY_KEYHOLD_MAX;
                }
                else if (m_dwHoldTimeOut < DLY_KEYHOLD)
                {
                    m_dwHoldTimeOut = DLY_KEYHOLD;
                }
            }
            RegCloseKey(hkey);
        }
    }
}

// Stop detecting Press&Hold.  Called when a key is released.
// Return TRUE if it was a Press and FALSE if it was a Press&Hold
BOOL CPressHoldDetector::IsPress(UINT uVKey)
{
    BOOL fRet = FALSE;

    if (!m_uVKey)
    {
        // Window got a KEYUP but did not get the KEYDOWN because the 
        // KEYDOWN went to another window -- this can happen during 
        // activation changes.
        goto Error;
    }

    if (uVKey != m_uVKey)
    {
        // Key that Set is not the key that is asking if it was a Press,
        // so clear our state and return FALSE.
        goto Error;
    }

    // If the user did at least one Press&Hold, notify the end of Press&Hold time periods.
    if (m_fMultiple && m_fPressHoldOnce)
    {
        ASSERT(m_pime);
        if (m_pime)
        {
            m_pime->OnPressHoldEnd(uVKey); // Notify IME
        }
    }

    fRet = !m_fPressHoldOnce;

Error:
    m_uVKey = 0;

    return fRet;
}

// Check if a Press&Hold has occured. If it has, process Press&Hold. 
// Called when repeat press events of a pressed key are received.
void CPressHoldDetector::CheckPressHold(HIMC himc, UINT uVKey)
{
    if (uVKey != m_uVKey)
    {
        // Key that Set is not the key that is checking for PressHold.
        // Likely that keydown went to one process and repeats went to
        // another because of activation changes.
        return;
    }

    // If the user pressed and held the star key
    // change the mode.
    if (!m_fPressHold && GetTickCount() - m_dwStart > m_dwHoldTimeOut)
    {
        m_fPressHoldOnce = TRUE;
        ASSERT(m_pime);
        if (m_pime)
        {
            m_pime->OnPressHold(himc, uVKey); // Notify IME
        }

        if (m_fMultiple)
        {
            // Restart Press&Hold processing for multiple Press&Hold time periods.
            m_dwStart = GetTickCount();
            m_fPressHold = FALSE;
        }
        else
        {
            m_fPressHold = TRUE;
        }
    }
}




