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

//  PhoneIme.cpp: IME wrapper for input converter. 
//                DLL entry points.


// The IME which the system uses is specified in the registry under:
//
//[HKEY_CURRENT_USER\Keyboard Layout\Preload\1]
//    @="e0010409"
//[HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Layouts\e0010409]
//    "Layout Text"="PHONE IME"
//    "Ime File"="phon_ime.dll"
//
// where 0409 is the language ID.
//
// This IME converts phone keypad input to text using a converter engine.
// Input has uptp 3 modes: Multipress (SPELL), AMBIG or Numbers mode.
// On Windows, the user explicitly opens an IME by pressing hot keys. But on the phone, 
// the edit control automatically opens the IME when it receives focus and closes the IME
// when it loses focus.
// 
// The IME receives a ImeInquire() call when the IME is loaded. The IME specifies
// the size of any private data it needs to save in the Input context when this
// function is called. ImeSetActiveContext is called when the IME is opened/closed.
// The IME data is allocated on the first activation and freed when the thread
// exits. NotifyIME/IMC_SETOPENSTATUS is also called when the IME is opened/closed
// and the IME manages its open/closed state when this happens. 
//
// When an app calls GetMessage to retrieve a key message from its queue, the OS will call
// ImeProcessKey to ask the IME if it wants the message. If it does, the OS will again call 
// ImeToAsciiEx with that key message when the app calls TranslateMessage. The IME
// will process the key message by calling the converter engine to translate the key to
// text. 

#include "phoneime.h"
#include <aygshell.h>

HINSTANCE g_hInst;       // code
HINSTANCE g_hInstRes;    // resources
CRITICAL_SECTION g_cs;
DWORD g_dwTLS;
const LPTSTR c_szUIClassName = TEXT("MS_PHONEIMEUI");

// DLL entry point

BOOL WINAPI DllMain(
    HANDLE hinst,
    DWORD dwReason,
    LPVOID pvReserver
)
{
    UNREFERENCED_PARAMETER(pvReserver);

    BOOL fRet = FALSE;

    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH:
            if (!DllProcessInit((HINSTANCE)hinst))
            {
                goto Exit;
            }
            break;

        case DLL_THREAD_ATTACH:
            DllThreadInit();
            break;

        case DLL_THREAD_DETACH:
            DllThreadUninit();
            break;

        case DLL_PROCESS_DETACH:
            DllProcessUninit();
            break;
    }

    fRet = TRUE;

Exit:
    return fRet;
}

// Init DLL
BOOL DllProcessInit(HINSTANCE hinst)
{
    BOOL fRet = FALSE;

    // Init Multiple Language UI resources (also sets g_hInst)
    InitHINST(hinst);

    // Init critical section
    InitializeCriticalSection(&g_cs);

    // Init thread local storage
    g_dwTLS = TlsAlloc();
    if (0xFFFFFFFF == g_dwTLS)
    {
        goto Error;
    }
    DllThreadInit(); // Init this thread

    // Register IME UI window
    WNDCLASS wc;
    wc.style          = CS_IME;
    wc.lpfnWndProc    = PhoneIMEWndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 8;  // CS_IME windows need 8 extra bytes
    wc.hInstance      = hinst;
    wc.hCursor        = NULL;
    wc.hIcon          = NULL;
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = c_szUIClassName;
    wc.hbrBackground  = NULL;

    fRet = RegisterClass(&wc);

Error:
    if (!fRet)
    {
        DllProcessUninit();
    }
    return fRet;
}

// Uninit DLL
void DllProcessUninit()
{
    if (!g_hInst)
    {
        return;
    }

    DllThreadUninit(); // Thread uninit for main thread

    UnregisterClass(c_szUIClassName, HINST_THISDLL);
    DeleteCriticalSection(&g_cs);
    if (0xFFFFFFFF != g_dwTLS)
    {
        TlsFree(g_dwTLS);
    }
}

// Init Thread
void DllThreadInit()
{
    // Init.
    TlsSetValue(g_dwTLS, NULL); 
}

// Uninit thread
void DllThreadUninit()
{
    CIME *pime;
    // Free CIME object if necessary.
    pime = (CIME*) TlsGetValue(g_dwTLS);
    if (pime)
    {
        DeleteIME(pime);
        DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: Freed CIME pime = %lx\r\n"), pime));
        TlsSetValue(g_dwTLS, NULL);
    }
}

// Window proc for UI window. We assume that all controls in the system
// are IME aware, so we don't do any processing.

LRESULT CALLBACK PhoneIMEWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{

    switch (uMsg)
    {
        // In an IME UI window, the following messages should not be passed to 
        // DefWndProc
        case WM_IME_STARTCOMPOSITION:
        case WM_IME_ENDCOMPOSITION:
        case WM_IME_COMPOSITION:
        case WM_IME_NOTIFY:
        case WM_IME_CONTROL:
        case WM_IME_COMPOSITIONFULL:
        case WM_IME_SELECT:
        case WM_IME_SETCONTEXT:
            return 0L;

       default:
            return DefWindowProc(hwnd, uMsg, wparam, lparam);
    }
}

// Handles initialization of IME. It also returns IMEINFO structure and
// UI class name of IME.

BOOL WINAPI ImeInquire(
   LPIMEINFO pimeinfo,      // Out: IME information.
   LPTSTR pszClassName,     // Out: Return IME's UI class name.
   LPCTSTR lpszData         // In: Unused
)
{
    UNREFERENCED_PARAMETER(lpszData);

    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeInquire\r\n")));
    // Init IMEINFO Structure.

    // Save space for a CIME pointer.
    pimeinfo->dwPrivateDataSize = sizeof(CIME*);

    pimeinfo->fdwProperty = IME_PROP_KBD_CHAR_FIRST | IME_PROP_UNICODE;
    pimeinfo->fdwConversionCaps = IME_CMODE_LANGUAGE | IME_CMODE_FULLSHAPE;
    pimeinfo->fdwSentenceCaps = 0L;
    pimeinfo->fdwUICaps = 0L;
    pimeinfo->fdwSCSCaps = 0L;
    pimeinfo->fdwSelectCaps = 0L;

    // Return UI class name
    lstrcpy(pszClassName, c_szUIClassName);

    return TRUE;
}

// Obtains the list of FE character or string from one character or
// string.

DWORD WINAPI ImeConversionList(
   HIMC himc,                   // Input Method Context.
   LPCTSTR pszSource,           // Source string to be converted.
   LPCANDIDATELIST pcandlist,   // Destination buffer
   DWORD dwBufLen,              // Lenght of destination buffer
   UINT uFlags                  // Action flag.
)
{
    UNREFERENCED_PARAMETER(himc);
    UNREFERENCED_PARAMETER(pszSource);
    UNREFERENCED_PARAMETER(pcandlist);
    UNREFERENCED_PARAMETER(dwBufLen);
    UNREFERENCED_PARAMETER(uFlags);

    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeConversionList\r\n")));

    ASSERT(0); // Not implemented
    return 0;
}

// Provides dialog box to request optional information for an IME.

BOOL WINAPI ImeConfigure(
    HKL    hkl,     // Handle of the keyboard layout for the IME. 
    HWND   hwnd,    // Parent window handle.
    DWORD  dwMode,  // The mode of dialog.
    LPVOID pvData   // Data.
)
{
    UNREFERENCED_PARAMETER(hkl);
    UNREFERENCED_PARAMETER(hwnd);
    UNREFERENCED_PARAMETER(dwMode);
    UNREFERENCED_PARAMETER(pvData);

    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeConfigure\r\n")));

    ASSERT(0); // Not implemented
    return FALSE;
}

// Terminates the IME.

BOOL WINAPI ImeDestroy(UINT uReserved)
{
    UNREFERENCED_PARAMETER(uReserved);

    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeDestroy\r\n")));

    return TRUE;
}

// Allows an application to access the capabilities of a particular 
// IME that are not directly  available though other IMM functions. 
// This is necessary mainly for country-specific functions or 
// private functions in IME.
// Return value depends on subfunction

LRESULT WINAPI ImeEscape(
    HIMC himc,       // Input Method Context.
    UINT uSubFunc,   // Index of the subfunction. 
    LPVOID pvData    // Data required for the escape function specified by uSubFunc
    )
{
    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeEscape\r\n")));
    LRESULT lRet = -1;
    CIME *pime;
    pime = GetIME(himc);
    if (!pime)
        goto Exit;

    switch (uSubFunc)
    {
        case IME_ESC_QUERY_SUPPORT:
            if(pvData == NULL)
            {
                lRet = FALSE;
                break;
            }

            switch (*(LPUINT)pvData)
            {
                case IME_ESC_QUERY_SUPPORT:
                case IME_ESC_SET_MODE:
                case IME_ESC_GET_MODE:
                case IME_ESC_SEND_BACK_TO_FOCUS_WINDOW:
                case IME_ESC_SET_CUSTOM_SYMBOLS:
                case IME_ESC_RETAIN_MODE_ICON:
                case IME_ESC_SAVE_USER_WORDS:
                case IME_ESC_CLEAR_ON_BACK_PRESS_HOLD:
                case IME_ESC_SKIP_AMBIG_MODE:
                    lRet = TRUE;
                    break;

                default:
                    lRet = FALSE;
                    break;
            }
            break;

        default: 
            lRet = pime->EscapeFunction(himc, uSubFunc, pvData);
            break;
    }

Exit:
    return lRet;
}

// Activates or deactivates an input context, and notifies the IME
// of the newly active input context. IME can use the notification 
// for initialization.

BOOL WINAPI ImeSetActiveContext(
    HIMC himc,      // Input Method Context.
    BOOL fActive    // TRUE if activated, FALSE if deactivated.
)
{
    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeSetActiveContext fActive = %lx\r\n "), fActive));
    BOOL fRet = FALSE;
    LPINPUTCONTEXT pimc = NULL;
    CIME **ppime = NULL;
    CIME *pime = NULL;

    if (!himc)
        goto Exit;
    pimc = ImmLockIMC(himc);
    if (!pimc)
        goto Exit;

    // Get private data, which is a pointer to a CIME object. 
    // The size of the private data is specified in IMEInquire. 
    // The private data is alloc'd and freed by the OS.
    ppime = (CIME **) ImmLockIMCC(pimc->hPrivate);
    if (!ppime)
        goto Exit;

    if (fActive)
    {
        // On first activation, create the CIME object and save this
        // pointer in TLS. 
        // For improved perf. we don't create/delete on every
        // activation/deactivation. Instead the CIME object is created
        // on the first activation in the thread and deleted when the
        // thread detaches.
        pime = (CIME*) TlsGetValue(g_dwTLS);
        if (!pime) // First activation?
        {
            pime = CreateIME(HINST_THISDLL);
            if (!pime)
                goto Exit;
            TlsSetValue(g_dwTLS, pime);
            DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: Allocated CIME pime = %lx\r\n"), pime));
        }

        // Put pointer to CIME in the private area of the InputContext
        *ppime = pime;
    }
    else
    {
        // On deactivation, clear CIME in the private area of the InputContext.
        // Don't free. It will be freed when the thread detaches from this DLL.
        *ppime = NULL;
    }

    fRet = TRUE;

Exit:
    if (ppime)
        ImmUnlockIMCC(pimc->hPrivate);
    if (pimc)
        ImmUnlockIMC(himc);
    return fRet;
}

// Processes keystrokes sent by the system (before the app gets it).
// Returns TRUE if IME wants key. Else return FALSE. If IME returns
// TRUE, IMEToAsciiEx will be called with that key when the app calls 
// TranslateMessage.

BOOL WINAPI ImeProcessKey(
    HIMC himc,                  // Input Method Context.
    UINT uVKey,                 // Virtual key to be processed.
    LPARAM lKeyData,            // lParam of a key message.
    CONST LPBYTE pbKeyState     // 256 bytes array that contains the current keyboard state. 
                                // WinCE only shows the state of modifier keys in this array.
)
{
    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeProcessKey\r\n")));
    BOOL fRet = FALSE;
    CIME *pime;

    // Notify Shell that the user entered a key.
    // Do this only on keyups to minimize notifications
    if (HIWORD(lKeyData) & KF_UP)
    {
        SHImeOnKeyPress();
    }

    pime = GetIME(himc);
    if (!pime)
        goto Exit;

    fRet = pime->ProcessKey(himc, uVKey, lKeyData, pbKeyState);

Exit:
    return fRet;
}

// Notifies the IME about changes to the status of the input context.

BOOL WINAPI NotifyIME(
    HIMC himc,       // Input Method Context.
    DWORD dwAction,  // Notification code.
    DWORD dwIndex,   // See docs.
    DWORD dwValue    // See docs.
)
{
    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: NotifyIME\r\n")));
    BOOL fRet = FALSE;
    CIME *pime;
    pime = GetIME(himc);
    if (!pime)
        goto Exit;

    switch(dwAction)
    {
        case NI_COMPOSITIONSTR:
            fRet = pime->ChangeCompositionString(himc, dwIndex);
            break;

        case NI_CONTEXTUPDATED:
            switch (dwValue)
            {
            case IMC_SETOPENSTATUS:
                // The IME open status has changed
                fRet = pime->OnOpenStatusChanged(himc);
                break;

            default: //ignore any notifications we're not interested in
                break;
            }
            break;

        default:
             ASSERT(0); // Not implemented
             break;
    }

Exit:
    return fRet;
}

// Initializes and uninitializes the IME's private context.

BOOL WINAPI ImeSelect(
    HIMC himc,         // Input Method Context.
    IN BOOL fSelect    // Initialization flag.
)
{
    UNREFERENCED_PARAMETER(himc);

    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeSelect fSelect = %lx\r\n"), fSelect));

    return TRUE;
}


// Causes the IME to arrange the composition string structure with
// the given data. 

BOOL WINAPI ImeSetCompositionString(
    HIMC himc,      // Input Method Context.
    DWORD dwIndex,  // See docs
    LPVOID pvComp,  // Buffer with updated composition string.
    DWORD dwComp,   // Length of pvComp buffer
    LPVOID pvRead,  // Buffer with updated reading string
    DWORD dwRead    // Length of pvRead buffer.
)
{
    UNREFERENCED_PARAMETER(himc);
    UNREFERENCED_PARAMETER(dwIndex);
    UNREFERENCED_PARAMETER(pvComp);
    UNREFERENCED_PARAMETER(dwComp);
    UNREFERENCED_PARAMETER(pvRead);
    UNREFERENCED_PARAMETER(dwRead);

    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeSetCompositionString\r\n")));

    ASSERT(0); // Not implemented
    return FALSE; 
}

// Translates keyboard messages that IME said that it wanted in ImeProcessKey.
// Returns the number of translated messages.

UINT WINAPI ImeToAsciiEx(
    UINT uVKey,                 // In: Virtual key code to be translated.
                                   // LOBYTE(LOWORD(uVKey)) : virtual key code
                                   // HIBYTE(LOWORD(uVKey)) : not used
                                   // HIWORD(uVKey)         : unicode character code (16bit)
    UINT uScanCode,             // In: Hardware scan code of the key to be translated.
    CONST LPBYTE pbKeyState,    // In: Keyboard status array.
    LPDWORD pdwTransBuf,        // Out: Buffer that receives translated result
    UINT fuState,               // In: Active menu flag.
    HIMC himc                   // In: Input Method Context.
)
{
    UNREFERENCED_PARAMETER(fuState);
    UNREFERENCED_PARAMETER(pbKeyState);

    CRITICAL crit(&g_cs);
    DEBUGMSG(DBF_PHONE_IME, (TEXT("PHONEIME: ImeToAsciiEx\r\n")));
    UINT uRet = 0;
    CIME *pime;
    pime = GetIME(himc);
    if (!pime)
        goto Exit;

    uRet = pime->ToAsciiEx(himc,  LOBYTE(LOWORD(uVKey)), uScanCode, pdwTransBuf); 

Exit:
    return uRet;
}

// Adds a new string to the dictionary of this IME.

BOOL WINAPI ImeRegisterWord(LPCTSTR lpRead, DWORD dw, LPCTSTR lpStr )
{
    UNREFERENCED_PARAMETER(lpRead);
    UNREFERENCED_PARAMETER(dw);
    UNREFERENCED_PARAMETER(lpStr);

    CRITICAL crit(&g_cs);

    ASSERT(0); // Not implemented
    return FALSE;
}


// Removes a string from the dictionary of this IME.

BOOL WINAPI ImeUnregisterWord(LPCTSTR lpRead, DWORD dw, LPCTSTR lpStr)
{
    UNREFERENCED_PARAMETER(lpRead);
    UNREFERENCED_PARAMETER(dw);
    UNREFERENCED_PARAMETER(lpStr);

    CRITICAL crit(&g_cs);

    ASSERT(0); // Not implemented
    return FALSE;
}

// Retrieves the available styles in this IME. 

UINT WINAPI ImeGetRegisterWordStyle(UINT u, LPSTYLEBUF lp)
{
    UNREFERENCED_PARAMETER(u);
    UNREFERENCED_PARAMETER(lp);

    CRITICAL crit(&g_cs);

    ASSERT(0); // Not implemented
    return 0;
}

// Enumerates all strings that match the given reading string, style,
// or registered string.


UINT WINAPI ImeEnumRegisterWord(REGISTERWORDENUMPROC lpfn, LPCTSTR lpRead, 
    DWORD dw, LPCTSTR lpStr, LPVOID pvData)
{
    UNREFERENCED_PARAMETER(lpfn);
    UNREFERENCED_PARAMETER(lpRead);
    UNREFERENCED_PARAMETER(dw);
    UNREFERENCED_PARAMETER(lpStr);
    UNREFERENCED_PARAMETER(pvData);

    CRITICAL crit(&g_cs);

    ASSERT(0); // Not implemented
    return 0;
}

// Gets the menu items that are registered in IME Menu.

DWORD WINAPI ImeGetImeMenuItems(HIMC himc, DWORD dwFlags, DWORD dwType, 
    LPIMEMENUITEMINFOW lpParentMenu, LPIMEMENUITEMINFOW lpMenu, DWORD dwSize)
{
    UNREFERENCED_PARAMETER(himc);
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(dwType);
    UNREFERENCED_PARAMETER(lpParentMenu);
    UNREFERENCED_PARAMETER(lpMenu);
    UNREFERENCED_PARAMETER(dwSize);

    CRITICAL crit(&g_cs);

    ASSERT(0); // Not implemented
    return 0;
}

// Get CIME pointer from Input Context
CIME* GetIME(HIMC himc)
{
    LPINPUTCONTEXT pimc = NULL;
    CIME **ppime = NULL;
    CIME *pime = NULL;

    ASSERT(himc);
    pimc = ImmLockIMC(himc);
    if (!pimc)
        goto Exit;

    ppime = (CIME **) ImmLockIMCC(pimc->hPrivate);
    if (!ppime)
        goto Exit;

    pime = *ppime;

Exit:
    if (ppime)
        ImmUnlockIMCC(pimc->hPrivate);
    if (pimc)
        ImmUnlockIMC(himc);
    return pime;
}

