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

#include <aygshell.h>
#include "phoneime.h"
#include "symmenu.h"
#include "keybd.h"
#include "misc.h"


// Init IME
CIME::CIME(
    HINSTANCE hinst   // In: Instance handle
)
{
    m_hinst = hinst;

    m_pdwTransBuf = NULL;
    m_cTransMsgs = 0;
    m_himc = NULL;
    m_hwnd = NULL;
    m_uVKeyPrev = 0;

    m_fRegisterSymMenuClass = FALSE;
    m_fOpen = FALSE;
    m_fIgnoreModeChange = FALSE;
    m_fRetainModeIcon = FALSE;
    m_fAddToUserDatabase = FALSE;
    m_fClearOnBackPressHold = FALSE;
    m_fRetainShiftState = FALSE;
    m_fSkipAmbigMode = FALSE;
    m_fSupportIntlPlus = FALSE;

    DWORD dwPhoneFeatureLevel = 0;


    m_fSupportIntlPlus = SupportIntlPlus();

    // Set callbacks
    m_phd.SetIME(this);

    // Create converter
    m_pConverter = CreateConverter();
}

CIME::~CIME()
{
    if (m_pConverter)
    {
        DeleteConverter(m_pConverter);
        m_pConverter = NULL;
    }
}

// Implements private IME functions
LRESULT CIME::EscapeFunction(
    HIMC himc,  
    UINT uFunction,   // In: Function
    LPVOID pvData     // In: Data
)
{
    LRESULT lRet = -1;
 
    if (!himc || !m_fOpen || !ValidateWindow(himc))
        goto Exit;

    switch (uFunction)
    { 
        case IME_ESC_SET_MODE:
            if (m_fIgnoreModeChange)
                break;
            if (m_pConverter->SetInputMode((int)pvData))
                lRet = 1; 
            break;

        case IME_ESC_GET_MODE:
            lRet = m_pConverter->GetInputMode();
            break;

        case IME_ESC_SEND_BACK_TO_FOCUS_WINDOW:
            ProcessBack(himc, (DWORD)pvData);
            lRet = 1;
            break;

        // Set custom symbols to be displayed in multi-press mode
        // when the user presses the 1 key. pvData is the string
        // of custom symbols or NULL to clear the current custom
        // symbols.
        case IME_ESC_SET_CUSTOM_SYMBOLS:
        {
            if (m_pConverter->SetCustomSymbols((PTSTR)pvData))
                lRet = 1;
            break;
        }

        // The window has lost focus and is about to close the IME.
        // However the focus is going to another IME aware window.
        // so don't clear the mode icon in the tray.
        case IME_ESC_RETAIN_MODE_ICON:
            m_fRetainModeIcon = ((DWORD)pvData & IMEAF_AWARE) ? TRUE : FALSE;
            m_fRetainShiftState = (((DWORD)pvData) & IMEAF_SMART_CAPS) ? TRUE : FALSE;
            lRet = 1;
            break;

        // Should user words be saved to the user database?
        case IME_ESC_SAVE_USER_WORDS:
            m_fAddToUserDatabase = TRUE;
            lRet = 1;
            break;

        // Should the Press&Hold of Back key clear contents of window?
        case IME_ESC_CLEAR_ON_BACK_PRESS_HOLD:
            m_fClearOnBackPressHold = (pvData) ? TRUE : FALSE;
            lRet = 1;
            break;

        // Skip Ambig mode when user changes mode
        case IME_ESC_SKIP_AMBIG_MODE:
            m_fSkipAmbigMode = (pvData) ? TRUE : FALSE;            
            lRet = 1;
            break;

        default:
           ASSERT(0); // Not implemented
           break;
    }

Exit:
    return lRet;
}

// Implements ImeProcessKey
// Processes keystrokes sent by the system (before the app gets it).
// Returns TRUE if IME wants key. Else return FALSE. If IME returns
// TRUE, IMEToAsciiEx will be called with that key when the app calls 
// TranslateMessage.

BOOL CIME::ProcessKey(
    HIMC himc,                  // Input Method Context.
    UINT uVKey,                 // Virtual key to be processed.
    LPARAM lKeyData,            // lParam of a key message.
    CONST LPBYTE pbKeyState     // 256 bytes array that contains the current keyboard state. 
                                // WinCE only shows the state of modifier keys in this array.
)
{
    BOOL fRet = FALSE;
    int nMode;

    if (!himc || !m_fOpen || !ValidateWindow(himc))
        return FALSE;

    // Don't process keystrokes with ALT and CTRL modifiers
    if (pbKeyState[VK_MENU] & KeyStateDownFlag ||
        pbKeyState[VK_CONTROL] & KeyStateDownFlag)
    {
        goto Exit;
    }

    // Lazily Init converter when the first keydown that the IME is interested 
    // in is received.
    switch(uVKey)
    {
    case VK_T0:
    case VK_T1:
    case VK_T2:
    case VK_T3:
    case VK_T4:
    case VK_T5:
    case VK_T6:
    case VK_T7:
    case VK_T8:
    case VK_T9:
    case VK_TSTAR:
    case VK_TPOUND:
    case VK_TRIGHT:
    case VK_TLEFT:
    case VK_TDOWN:
    case VK_TUP:
    case VK_TACTION:
        if (!(HIWORD(lKeyData) & KF_UP))
        {
            if (!m_pConverter->Init())
                goto Exit;
        }
        break;
    
    case VK_TBACK:
        // We don't want to process this character, but we don't want it to end the
        // current composition either.
        goto Exit;

    default:
        // Output and end current composition if any non-composition characters come in
        MakeResultString(himc, TRUE, TRUE);
        goto Exit;
    }
    
    // Keys are processed only in Spell, Ambig or Numbers mode
    nMode = m_pConverter->GetInputMode();
    if (nMode == -1)
    {
        ASSERT(0); // Invalid mode
        goto Exit;
    }
    nMode &= IM_MASK;

    // Keyups are needed only for the Press&Hold keys: *, 0 and #
    if (HIWORD(lKeyData) & KF_UP)
    {
        if (uVKey == VK_T0
            || uVKey == VK_TSTAR
            || uVKey == VK_TPOUND)
        {
            fRet = m_phd.IsPress(uVKey); // Was it a press or press & hold?
        }
        goto Exit;
    }

    // Determine if these keydowns are needed by IME
    switch(uVKey)
    {
    case VK_T0:
        // Process the '0' keys as hold key if international plus is supportted or
        //   or in Ambiguous mode. Otherwise, it will be just liked number key.
        if (m_fSupportIntlPlus || nMode == IM_AMBIG)
        {
            // Press&Hold keys
            ProcessPressHoldKey(himc, uVKey, lKeyData);
            fRet = TRUE;
        }
        else
        {
            // Output and end current composition if VK_T0 come in and we don't support IntlPlus
            MakeResultString(himc, TRUE, TRUE);
            goto Exit;
        }
        break;
        
    case VK_T1:
    case VK_T2:
    case VK_T3:
    case VK_T4:
    case VK_T5:
    case VK_T6:
    case VK_T7:
    case VK_T8:
    case VK_T9:
    {
        // Process the number keys only in Ambiguous or Spell modes      
        if (nMode != IM_SPELL && nMode != IM_AMBIG)
        {
            goto Exit;
        }
        fRet = TRUE;
        break;
    }

    // Press&Hold keys
    case VK_TSTAR:
    case VK_TPOUND: 
        ProcessPressHoldKey(himc, uVKey, lKeyData);
        fRet = TRUE;
        break;

    // Convert any Composition string to Result string
    // when the user uses the Direction or Action keys.
    case VK_TRIGHT:
    case VK_TLEFT:
        // Eat left & right if a composition string exists, so
        // caret in window is not advanced. Instead the arrows will
        // determine the string if a composition exists.
        if (HasComposition(himc))
            fRet = TRUE;
        // FALL THRU

    case VK_TDOWN:
    case VK_TUP:
    case VK_TACTION:
        MakeResultString(himc, TRUE, TRUE);
        break;

    default:
        break;
   }

Exit:
    return fRet;
}

void CIME::ProcessPressHoldKey(
    HIMC himc,              // In: Input Method Context. 
    UINT uVKey,             // In: Virtual key to be processed.
    LPARAM lKeyData         // In: key state.
)
{
    // Start Press&Hold detector on first keydown.
    if (!(HIWORD(lKeyData) & KF_REPEAT))
    {
        switch (uVKey)
        {
        case VK_TSTAR:
            // Multiple Press&Hold time periods
            m_phd.Set(uVKey, TRUE);
            break;

        case VK_T0:
        case VK_TPOUND:
            // Single Press&Hold time period
            m_phd.Set(uVKey, FALSE);
            break;

        default:
            ASSERT(0); // Unsupported Press&Hold key
            break;
        }
    }
    else
    {
        m_phd.CheckPressHold(himc, uVKey);
    }
}

// Translates keyboard messages that IME said that it wanted in ImeProcessKey.
// Returns the number of translated messages.

UINT CIME::ToAsciiEx(
    HIMC himc,                  // In: Input Method Context.                     
    UINT uVKey,                 // In: Virtual key code to be translated.
    UINT uScanCode,             // In: Hardware scan code of the key to be translated.
    LPDWORD pdwTransBuf         // Out: Buffer that receives translated result
)
{
    m_cTransMsgs = 0;

    if (!himc || !m_fOpen || !ValidateWindow(himc))
        goto Exit;

    // Store translation buffer
    m_pdwTransBuf = pdwTransBuf;   

    if (uScanCode & KF_UP) 
        ProcessKeyUp(himc, uVKey);
    else
        ProcessKeyDown(himc, uVKey);

Exit:
    m_pdwTransBuf = NULL; // Remove translation buffer

    return m_cTransMsgs;
}

// Process keydown
void CIME::ProcessKeyDown(
    HIMC himc,                  // In: Input Method Context.                     
    UINT uVKey                  // In: Virtual key code to be processed.
)
{
    // Don't process keydown of Press&Hold keys. Press of a Press&Hold key
    // is processed on keyup.
    if (uVKey == VK_T0 || uVKey == VK_TSTAR || uVKey == VK_TPOUND)
        return;

    ProcessChar(himc, uVKey);
}

// Process keyup
void CIME::ProcessKeyUp(
    HIMC himc,                  // In: Input Method Context.                     
    UINT uVKey                  // In: Virtual key code to be processed.
)
{
    // Process keyup of Press&Hold keys only. Press of other keys are 
    // processed on keydown.
    if (uVKey != VK_T0 && uVKey != VK_TSTAR && uVKey != VK_TPOUND)
        return;

    ProcessChar(himc, uVKey);
}

// Process character.

void CIME::ProcessChar(
    HIMC himc,                  // In: Input Method Context.                     
    UINT uVKey                  // In: Virtual key code to be processed.
)
{
    int nMode = m_pConverter->GetInputMode();
    ASSERT(nMode != -1);
    nMode &= IM_MASK;

    // In spell mode, init/uninit custom symbol processing for the '1' key.
    // Also convert the composition string to a result string when a new key is pressed.
    if (nMode == IM_SPELL
        && uVKey != m_uVKeyPrev)
    {
        m_uVKeyPrev = uVKey;

        if (uVKey == VK_T1)
            m_pConverter->InitCustomSymbolsProcessing();
        else
            m_pConverter->UnInitCustomSymbolsProcessing();
    
        MakeResultString(himc, TRUE, TRUE);
    }

    switch (uVKey) 
    {
        case VK_TLEFT:
        case VK_TRIGHT:
            // Ignore. These were not sent to the window because
            // they converted a composition to result.
            break;

        case VK_TSTAR: // Press (not Press&Hold) of * key
        {
            if (nMode == IM_NUMBERS)
            {
                // In Numbers mode, VK_TSTAR translates to '*'
                GenerateMessage(himc, WM_CHAR, TEXT('*'), 0);
                break;
            }
            
            // In Ambig and Spell modes VK_TSTAR is the Shift key
            m_pConverter->ProcessShiftKey();
            break;                   
        }

        case VK_TPOUND: // Press (not Press&Hold) of # key
        {
            if (nMode == IM_NUMBERS)
            {
                // In Numbers mode, VK_TPOUND translates to '#'
                GenerateMessage(himc, WM_CHAR, TEXT('#'), 0);
                break;
            }

            // In Ambig and Spell modes VK_TPOUND is the space key

            // If there is a composition string, this key will convert it
            // to a result string.
            if (HasComposition(himc))
            {
                AddChar(himc, uVKey);
                MakeResultString(himc, FALSE, TRUE);
            }
            else
            {
                // If there isn't a composition string, translate to Space.
                GenerateMessage(himc, WM_CHAR, VK_SPACE, 0);
            }
            break;
        }

        case VK_T0: // Press (not Press&Hold) of 0 key
        {
            if (nMode == IM_NUMBERS
                || nMode == IM_SPELL)
            {
                // In Numbers mode, VK_T0 translates to '0'
                GenerateMessage(himc, WM_CHAR, TEXT('0'), 0);
                break;
            }
            // In Ambig mode VK_T0 translates to Next. The converter engine 
            // will handle Next.

            // Fall through. 
        }

        default:
            AddChar(himc, uVKey);
            break;
    }

    return;
}

// Process Back key
void CIME::ProcessBack(
    HIMC himc,          // In: Input context
    DWORD dwKeyState    // In: Flags that specify Back key state
)
{

    // Some windows want the entire contents to be cleared on Press&Hold of Back.
    // m_fClearOnBackPressHold is set to TRUE for those windows.

    if (m_fClearOnBackPressHold) // Window wants Back Press&Hold behavior
    {
        // HOLDDOWN = keydown with MOD_HOLD
        // The Back key is processed on keyup (without HOLD) or on HOLDDOWN.

        if (!(dwKeyState & MOD_KEYUP) && (dwKeyState & MOD_HOLD)) // HOLDDOWN
        {
            UINT msg;
            WPARAM wp;
            LPARAM lp;
            
            // Clear composition string
            MakeResultString(himc, TRUE, TRUE); 
            // Ask window to clear contents
            SHImeGetClearMessage(himc, &msg, &wp, &lp);
            GenerateMessage(himc, msg, wp, lp);
        }
        else if ((dwKeyState & MOD_KEYUP) && !(dwKeyState & MOD_HOLD)) // Keyup (without HOLD)
        {
            // Delete current character
            ProcessChar(himc, VK_TBACK);
        }
    }
    else
    {
        // Delete a character on each keydown
        if (!(dwKeyState & MOD_KEYUP) && !(dwKeyState & MOD_HOLD)) 
        {
            // Delete current character
            ProcessChar(himc, VK_TBACK);
        }
    }
}

// If there is no Translation buffer or if the caller explicitly specifies it, 
// use ImmGenerateMessage to send the message immediately to the window with the
// focus. Else add message to Transation buffer if it exists, in which case the 
// message will be sent to the window with focus by the OS when ImeToAsciiEx returns. 
// Returns TRUE if successful, else returns FALSE.

BOOL CIME::GenerateMessage(
    HIMC himc,               // In: Input Method Context.
    UINT uMsg,               // In: Message to be generated.
    WPARAM wParam,           // In: wParam of message
    LPARAM lParam,           // In: lParam of message
    BOOL fSendNow            // In: Send message immediately?
)
{
    GENMSG gmsg;

    gmsg.msg = uMsg;
    gmsg.wParam = wParam;
    gmsg.lParam = lParam; 

    if (!m_pdwTransBuf || fSendNow)
        return SendMessage(himc, &gmsg);
    else
        return PutMessageInTransBuf(&gmsg);
}

// Send message immediately to window with focus

BOOL CIME::SendMessage(
    HIMC himc,               // In: Input Method Context.
    PGENMSG pgmsg            // In: Message to be sent.
)
{  
    BOOL fRet = FALSE;
    PBYTE pbMsgBuf;
    LPINPUTCONTEXT pimc;
    HIMCC himcc;

    pimc = ImmLockIMC(himc);
    if (!pimc)
        goto Exit;

    if (!IsWindow(pimc->hWnd))
        goto Exit;

    // Reallocate message buffer for one more message
    himcc = ImmReSizeIMCC(pimc->hMsgBuf, sizeof(GENMSG) * (pimc->dwNumMsgBuf + 1));
    if (!himcc)
        goto Exit;
    pimc->hMsgBuf = himcc; 
    
    // Put message into message buffer
    pbMsgBuf = (PBYTE)ImmLockIMCC(pimc->hMsgBuf);
    if (!pbMsgBuf)
        goto Exit;
    pbMsgBuf += pimc->dwNumMsgBuf * sizeof(GENMSG);
    *(PGENMSG)pbMsgBuf = *pgmsg;
    ImmUnlockIMCC(pimc->hMsgBuf);

    // Increment number of messages
    pimc->dwNumMsgBuf++;

    // Send message to window with focus
    fRet = ImmGenerateMessage(himc);

Exit:
    if (pimc)
        ImmUnlockIMC(himc);
    return fRet;
}

// Put message into translation buffer provided by ImeToAsciiEx. Messages in 
// the buffer will be sent by the OS to the window with focus after ImeToAsciiEx 
// returns.

BOOL CIME::PutMessageInTransBuf(
    PGENMSG pgmsg            // In: Message to be put.
)
{
    BOOL fRet = FALSE;
    PGENMSG pgmsgDest;

    if (!m_pdwTransBuf)
    {
        ASSERT(0);  // Should not be called unless there is a translation buffer.
        goto Exit;
    }

    // Determine if there is space in the translation buffer for a new message.
    // The first DWORD in the translation buffer specifies the number of messages
    // that can be put into the buffer.
    if (m_cTransMsgs + 1 >= *m_pdwTransBuf)
    {
        ASSERT(0); // Investigate why the translation buffer is full
        goto Exit;
    }

    // Put message into buffer
    m_cTransMsgs++;

    pgmsgDest = (PGENMSG)(m_pdwTransBuf+1) + (m_cTransMsgs-1);
    *pgmsgDest = *pgmsg;

    fRet = TRUE;

Exit:
    return fRet;
}


// Add a character to composition string.

void CIME::AddChar(
    HIMC himc,                  // In: Input Method Context.                     
    UINT uVKey                  // In: Virtual key code to be processed.
)
{
    LPINPUTCONTEXT pimc;
    LPCOMPOSITIONSTRING pcompstr = NULL;
    HIMCC himcc;
    BOOL fSentIMEStart = FALSE;

    pimc = ImmLockIMC(himc);
    if (!pimc)
        goto Error;

    if (ImmGetIMCCSize(pimc->hCompStr) < sizeof (MYCOMPSTR))
    {
        DWORD dwSize;

        // Initialize Composition string the first time it is used
        dwSize = sizeof(MYCOMPSTR);
        himcc = ImmReSizeIMCC(pimc->hCompStr, dwSize);
        if (!himcc)
            goto Error;
        pimc->hCompStr = himcc;
        pcompstr = (LPCOMPOSITIONSTRING) ImmLockIMCC(pimc->hCompStr);
        if (!pcompstr)
            goto Error;
        InitCompStr(pcompstr, dwSize);
    }
    else
    {
        pcompstr = (LPCOMPOSITIONSTRING) ImmLockIMCC(pimc->hCompStr);
        if (!pcompstr)
            goto Error;
    }
    ASSERT(ValidateInitedCompStr(pcompstr));

    if (!HasComposition(pcompstr))     // Is the composition string empty?
    {
        if (uVKey == VK_TBACK)
        {
            // Pass Backspace to app if we don't have a composition string.
            GenerateMessage(himc, WM_CHAR, VK_BACK, 0);
            goto Exit;
        }
        else
        {
            // Start new composition string
            ClearCompStr(pcompstr, CLR_COMP | CLR_RESULT); 
            GenerateMessage(himc, WM_IME_STARTCOMPOSITION, 0, 0, TRUE);
            fSentIMEStart = TRUE;
        }
    }

    // Limit reading string
    if (IsReadingFull(pcompstr))
    {
        MessageBeep(0); 
        goto Error;
    }

    // Use converter to add character to composition string
    LPTSTR pszConverterBuf;
    int cchComp, cchResult;
    cchComp = pcompstr->dwCompStrLen;
    pszConverterBuf = m_pConverter->Convert((TCHAR)uVKey, &cchResult, &cchComp);
    if (!pszConverterBuf)
        goto Error;

    // If addition of uVkey caused a result string, send it to the window.
    if (cchResult > 0)
    {
        // Update composition structure with the composition string that was converted to result.
        UpdateComposition(himc, pszConverterBuf, cchResult, 0);
        // Convert previous composition string to result string and send it the window.
        // To retain context, don't clear converter buffer. The buffer will be cleared
        // when the user determines the entire word.
        MakeResultString(himc, TRUE, FALSE); 

        // Start new composition string
        ClearCompStr(pcompstr, CLR_COMP | CLR_RESULT);
        GenerateMessage(himc, WM_IME_STARTCOMPOSITION, 0, 0, TRUE);
    }

    // Update composition string structure with new composition string
    ASSERT(VK_T0 < VK_T9);
    UpdateComposition(himc, pszConverterBuf+cchResult, cchComp, 
        (TCHAR)((uVKey >= VK_T0 && uVKey <= VK_T9) ? uVKey : 0)); // Only 0-9 are valid reading string characters
    // Send composition message to window
    GenerateMessage(himc, WM_IME_COMPOSITION, 0, GCS_COMPALL | GCS_CURSORPOS | GCS_DELTASTART);

Exit:
    if (pcompstr)
        ImmUnlockIMCC(pimc->hCompStr);
    if (pimc)
        ImmUnlockIMC(himc);
    return;

Error:
    // If a WM_IME_STARTCOMPOSITION was sent, send WM_IME_ENDCOMPOSITION on error.
    // If there is no error, WM_IME_ENDCOMPOSITION will be sent when the composition
    // string is converted to a result string.
    if (fSentIMEStart)
    {
        // The composition string should be empty because it was empty when this function
        // was called, and nothing was added to it because this function failed.
        ASSERT(!HasComposition(himc));
        GenerateMessage(himc, WM_IME_ENDCOMPOSITION, 0, 0, TRUE);
    }

    goto Exit;
}

// Convert composition string to result string.

void CIME::MakeResultString(
    HIMC himc,              // Input Method Context.
    BOOL fSendNow,          // Should the WM_IME_ messages be sent before this function returns?
    BOOL fClearConverter    // Should the converter be cleared?
)
{
    LPCOMPOSITIONSTRING pcompstr = NULL;
    LPINPUTCONTEXT pimc = NULL;

    // Clear converter
    if (fClearConverter)
        m_pConverter->ClearComposition();

    if (!HasComposition(himc)) // Composition string is empty?
        goto Exit;

    pimc = ImmLockIMC(himc);
    if (!pimc)
        goto Exit;

    pcompstr = (LPCOMPOSITIONSTRING)ImmLockIMCC(pimc->hCompStr);
    if (!pcompstr)
        goto Exit;

    // Move composition string to result string. Clear composition string.
    MoveCompositionToResult(pcompstr);

    // Send composition messages
    GenerateMessage(himc, WM_IME_COMPOSITION, 0, GCS_RESULTALL, fSendNow);
    GenerateMessage(himc, WM_IME_ENDCOMPOSITION, 0, 0, fSendNow);

Exit:
    if (pcompstr)
        ImmUnlockIMCC(pimc->hCompStr);
    if (pimc)
        ImmUnlockIMC(himc);
    return;
}

// Clear composition and result string
void CIME::ClearCompositionAndResult(
    HIMC himc
)
{
    LPCOMPOSITIONSTRING pcompstr = NULL;
    LPINPUTCONTEXT pimc = NULL;

    ASSERT(himc);

    // Clear converter
    m_pConverter->ClearComposition();

    pimc = ImmLockIMC(himc);
    if (!pimc)
        goto Exit;

    pcompstr = (LPCOMPOSITIONSTRING)ImmLockIMCC(pimc->hCompStr);
    if (!pcompstr)
        goto Exit;

    // Clear composition & result strings
    ClearCompStr(pcompstr, CLR_COMP | CLR_RESULT);

    // Send composition messages
    GenerateMessage(himc, WM_IME_COMPOSITION, 0, 0);
    GenerateMessage(himc, WM_IME_ENDCOMPOSITION, 0, 0);

Exit:
    if (pcompstr)
        ImmUnlockIMCC(pimc->hCompStr);
    if (pimc)
        ImmUnlockIMC(himc);
    return;
}



// Process user's Press&Hold
void CIME::OnPressHold(HIMC himc, UINT uVKey)
{
    switch (uVKey)
    {
    case VK_T0:
        // Make result string if necessary, before inserting '+'
        MakeResultString(himc, TRUE, TRUE);
        // Press and Hold of 0 sends '+' if support international plus, or send '0'.
        GenerateMessage(himc, WM_CHAR, m_fSupportIntlPlus ? TEXT('+') : TEXT('0'), 0, TRUE);
        break;

    case VK_TSTAR:
        m_pConverter->NextMode(m_fSkipAmbigMode);
        // Make result string when mode is changed
        MakeResultString(himc, TRUE, TRUE);
        break;

    case VK_TPOUND:
        SendSymbolFromMenu(himc);
        break;
    }
}

// Process end of Press&Hold sequence
void CIME::OnPressHoldEnd(UINT uVKey)
{
    switch (uVKey)
    {
    case VK_TSTAR:
        // Add words to the user database when user
        // switches to Ambig mode.
        if (IM_AMBIG == (m_pConverter->GetInputMode() & IM_MASK))
        {
            if (m_fAddToUserDatabase)
            {
                m_pConverter->AddToUserDatabase(m_hwnd);
            }
        }
        break;

    default:
        ASSERT(0); // Multiple Press&Hold time periods not supported for these keys.
        break;
    }
}

// Display the Symbols menu. Send user's selection to window with focus.

void CIME::SendSymbolFromMenu(HIMC himc)
{
    // Lazy register of Symbol menu class
    if (!m_fRegisterSymMenuClass)
    {
        m_fRegisterSymMenuClass = !!RegisterSymbolMenuClass(m_hinst);
        if (!m_fRegisterSymMenuClass)
        {
            DEBUGMSG(1, (TEXT("PHONEIME: RegisterSymbolMenuClass failed\r\n")));
            return;
        }
    }

    LPINPUTCONTEXT pimc;
    DWORD dwLastFocusStartSel = (DWORD)-1;
    DWORD dwLastFocusEndSel = (DWORD)-1;
    LPTSTR pszSymbols = (LPTSTR)LoadString(HINST_RESDLL, IDS_SYMBOL_DATA, NULL, 0);

    // Display Symbol menu and get user's selection. 
    CSymbolMenu *psymmenu = new CSymbolMenu(m_hinst);
    if (!psymmenu)
        return;

    // The window will lose and gain focus when the menu is displayed and closed. 
    // When the window gains focus, it asks the IME to change to its default mode,
    // which will override the mode the user may have changed to before displaying the
    // menu. To prevent this, ignore mode changes until the menu is closed,
    IgnoreModeChange(TRUE);

    pimc = (LPINPUTCONTEXT)ImmLockIMC(himc);
    if (pimc)
    {
        // Cache the control selection before displaying the symbol picker dialog,
        // because app might be adjusting it with changes in focus, and we would
        // rather have had the app not notice the focus changes due to this dialog
        // (kinda like a menu), but what can you do.
        ::SendMessage(pimc->hWnd, EM_GETSEL, (WPARAM)&dwLastFocusStartSel, (LPARAM)&dwLastFocusEndSel);
        ImmUnlockIMC(himc);
    }

    int nRet = psymmenu->Run(10, 10, pszSymbols, (LPTSTR)LoadString(HINST_RESDLL, IDS_SYMBOLS, NULL, 0));
    delete psymmenu;
    
    // Restore mode change capability
    IgnoreModeChange(FALSE);

    // User canceled menu or menu failed
    if (nRet == -1)
        return;

    // Restore selection in IME window to what it was before dialog showed up
    GenerateMessage(himc, EM_SETSEL, dwLastFocusStartSel, dwLastFocusStartSel, TRUE);
    
    // Restore selection in IME window to what it was before dialog showed up
    GenerateMessage(himc, EM_SETSEL, dwLastFocusStartSel, dwLastFocusEndSel, TRUE);
    
    // Send symbol to window with focus
    GenerateMessage(himc, WM_CHAR, pszSymbols[nRet], 0, TRUE);
}

// Change composition string
BOOL CIME::ChangeCompositionString(
    HIMC himc,          // In: Input context of window using the IME                   
    DWORD dwAction      // In: Action to be done on composition string
)
{
    BOOL fRet = FALSE;

    if (!himc || !m_fOpen || !ValidateWindow(himc))
    {
        goto Exit;
    }

    switch (dwAction)
    {
    // Complete composition string
    case CPS_COMPLETE:
        MakeResultString(himc, TRUE, TRUE);
        fRet = TRUE;
        break;

    case CPS_CANCEL:
        ClearCompositionAndResult(himc);
        fRet = TRUE;
        break;

    default:
        ASSERT(0); // Not implemented
        break;
    }

Exit:
    return fRet;
}

// Open status of the IME has changed. An IME aware window
// opens the IME when it gains focus and closes it when it loses
// focus.

BOOL CIME::OnOpenStatusChanged(
    HIMC himc   // In: Input context of window that is opening or closing the IME
)
{
    LPINPUTCONTEXT pimc;

    if (!himc)
    {
        return FALSE;
    }

    pimc = ImmLockIMC(himc);
    if (!pimc)
    {
        return FALSE;
    }
    
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: OnOpenStatusChanged fOpen = %lx\r\n"), pimc->fOpen));
    ASSERT(pimc->fOpen != !!m_fOpen); // A window did not correctly open/close the IME

    if (pimc->fOpen)
    {
        OnOpen(himc, pimc->hWnd);
    }
    else
    {
        OnClose();
    }
        
    ImmUnlockIMC(himc);
    return TRUE;
}

// IME is being opened.

void CIME::OnOpen(
    HIMC himc,  // In: Input context of window that opened IME
    HWND hwnd   // In: Window that opened IME
)
{
    OnClose(); // Make sure previous session was closed.
    m_himc = himc;
    m_hwnd = hwnd; // Remember the window that opened it, so the window can be validated when IME is used.
    m_fOpen = TRUE;

    // Reload multipress timeout in case it has been changed.
    m_pConverter->LoadMultiPressTimeOut();
}

// IME is being closed. This can be called multiple times after
// the IME is closed.

void CIME::OnClose()
{
    if (!m_fOpen) // Already closed?
    {
        goto Exit;
    }

    // Convert any composition string to result string when IME is closed.
    MakeResultString(m_himc, TRUE, TRUE);

    m_pConverter->UnInitCustomSymbolsProcessing();
    m_pConverter->ClearCustomSymbols();
    if (m_fAddToUserDatabase && m_hwnd)
    {
        m_pConverter->AddToUserDatabase(m_hwnd);
    }
    m_pConverter->SaveUserDatabase();

    // Clear CAPS lock or Shift if they are set. This is done because
    // we don't want to carry over Shift or CapsLock to the next IME aware window
    int nMode; 
    nMode = m_pConverter->GetInputMode();
    if (-1 != nMode)
    {
        if (!m_fRetainShiftState // Don't clear shift if focus is changing to a smart caps window
                && (nMode & IMMF_SHIFT))
        {
            m_pConverter->SetInputMode(IMMF_SETCLR_SHIFT | (nMode & IM_MASK));
        }
        if (nMode & IMMF_CAPSLOCK)
        {
            m_pConverter->SetInputMode(IMMF_SETCLR_CAPSLOCK | (nMode & IM_MASK));
        }
    }

    if (!m_fRetainModeIcon)
    {
        m_pConverter->SetModeIcon(FALSE); // Clear mode icon in tray
    }

    m_uVKeyPrev = 0;
    m_himc = NULL;
    m_hwnd = NULL;
    m_fAddToUserDatabase = FALSE;
    m_fClearOnBackPressHold = FALSE;
    m_fSkipAmbigMode = FALSE;
    m_fRetainModeIcon = FALSE;  
    m_fRetainShiftState = FALSE;
    m_fOpen = FALSE;

Exit:
    return;
}

// Make sure that the window which opened the IME is
// the current window. Else, close the IME.

BOOL CIME::ValidateWindow(
    HIMC himc   // In: Input context of window that is using the IME
)
{
    LPINPUTCONTEXT pimc = NULL;
    BOOL fRet = FALSE;

    if (!himc)
    {
        goto Exit;
    }

    pimc = ImmLockIMC(himc);
    if (!pimc)
    {
        goto Exit;
    }
    
    // If a window other than the window which opened the IME is using it,
    // close the IME.
    if (pimc->hWnd != m_hwnd)
    {
        ASSERT(0); // Window that opened IME is not the one using it. Likely that the 
                   // window that opened the IME did not close it.                   
        OnClose();
        goto Exit;
    }

    fRet = TRUE;

Exit:
    if (pimc)
    {
        ImmUnlockIMC(himc);
    }
    return fRet;
}

// Sequencing through characters by pressing the same
// key in multipress mode has timed out.
void CIME::OnMultiPressSequencingTimeOut()
{
    // Don't do anything if IME has been closed by the time the timer is received.
    if (!m_fOpen)
        goto Exit;

    if (m_himc)
        MakeResultString(m_himc, TRUE, TRUE);

    // Change Shift state icon if necessary
    // The Shift state (not CAPS lock) is cleared after the time out.
    m_pConverter->SetModeIcon(TRUE); 

Exit:
    return;
}

// If fSet is TRUE, mode change requests from the window are not processed.
// Else mode mode change processing in switched on. 
void CIME::IgnoreModeChange(BOOL fSet)
{
    m_fIgnoreModeChange = fSet;

    // Redraw mode icon when mode change processing is switched on.
    if (!m_fIgnoreModeChange
        && m_fOpen) // May not be open if symbol menu closed because another window appeared above it
    {
        m_pConverter->RedrawModeIcon();
    }
}

