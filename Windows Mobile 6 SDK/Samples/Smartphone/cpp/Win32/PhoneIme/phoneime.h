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

#ifndef __PHONEIME_H__
#define __PHONEIME_H__

#include <windows.h>
#include <windowsx.h>
#include <winuserm.h>
#include <tpcshell.h>
#include <aygshell.h>
#include "utils.h"
#include "resource.h"

EXTERN_C HINSTANCE g_hInst;
EXTERN_C HINSTANCE g_hInstRes;
#ifndef HINST_THISDLL
#define HINST_THISDLL g_hInst
#endif // HINST_THISDLL
#ifndef HINST_RESDLL
#define HINST_RESDLL g_hInstRes
#endif // HINST_RESDLL

#ifndef InitHINST
#define InitHINST(hinstCode) \
    { \
        g_hInst = g_hInstRes = hinstCode; \
    }
#endif // !InitHINST

class CIME;
class CConverter;

// Detects if the user pressed and held a button.
class CPressHoldDetector
{
private:
    UINT m_uVKey;           // Key being pressed
    DWORD m_dwStart;        // Beginning of current Press&Hold time period.
    CIME* m_pime;           // IME to callback.
    DWORD m_dwHoldTimeOut;  // Key hold timeout

    BOOL m_fPressHold:1;    // Did the user do a Press&Hold in the current time period?
    BOOL m_fPressHoldOnce:1;// Did the user do at least one Press&Hold?
    BOOL m_fMultiple:1;     // Support multiple Press&Hold time periods? 

public:
    CPressHoldDetector();
    void SetIME(CIME* pime);
    void Set(UINT uVKey, BOOL fMultiple);
    BOOL IsPress(UINT uVKey);
    void CheckPressHold(HIMC himc, UINT uVKey);
};

// IME
class CIME
{
protected:
    CConverter* m_pConverter;       // Converter
    CPressHoldDetector m_phd;       // Press & Hold detector
    HINSTANCE m_hinst;              // DLL Instance handle
    LPDWORD m_pdwTransBuf;          // Translation buffer passed in by ImeToAsciiEx. Used to
                                    // store translated messages which will be sent by the system on
                                    // return from ImeToAsciiEx.
    UINT m_cTransMsgs;              // Number of translated messages stored in the Translation buffer.
    HIMC m_himc;                    // Input context of the window that opened the IME
    HWND m_hwnd;                    // Window that opened the IME
    UINT m_uVKeyPrev;               // Previous key that was pressed

    BOOL m_fRegisterSymMenuClass:1; // Lazy register of Symbol menu class.
    BOOL m_fOpen:1;                 // Is IME open?
    BOOL m_fIgnoreModeChange:1;     // Should mode change be ignored? Used when the IME itself causes a focus change.
    BOOL m_fRetainModeIcon:1;       // Don't clear input mode icon in the tray when IME is closed.
    BOOL m_fAddToUserDatabase:1;    // Should words be added to user database on mode change to ambig mode or on close.
    BOOL m_fClearOnBackPressHold:1; // Should the Press&Hold of Back key clear contents of window?
    BOOL m_fRetainShiftState:1;     // Don't clear shift mode icon when IME is closed.
    BOOL m_fSkipAmbigMode:1;        // Skip ambig mode when user changes mode
    BOOL m_fSupportIntlPlus:1;      // Support international Plus character

protected:
    virtual void ProcessKeyDown(HIMC himc, UINT uVKey);
    virtual void ProcessKeyUp(HIMC himc, UINT uVKey);
    virtual void ProcessChar(HIMC himc, UINT uVKey);
    virtual void ProcessBack(HIMC himc, DWORD dwKeyState);
    BOOL GenerateMessage(HIMC himc, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL fSendNow = FALSE);
    BOOL SendMessage(HIMC himc, PGENMSG pgmsg);
    BOOL PutMessageInTransBuf(PGENMSG pgmsg);
    virtual void AddChar(HIMC himc, UINT uVKey);
    void SendSymbolFromMenu(HIMC himc);
    void IgnoreModeChange(BOOL fSet);
    void OnOpen(HIMC himc, HWND hwnd);
    void OnClose();
    BOOL ValidateWindow(HIMC himc);

public:
    CIME(HINSTANCE hinst);
    ~CIME();

    virtual LRESULT EscapeFunction(HIMC himc, UINT uFunction, LPVOID pvData);
    BOOL ProcessKey(HIMC himc, UINT uVKey, LPARAM lKeyData, CONST LPBYTE pbKeyState);
    void ProcessPressHoldKey(HIMC himc, UINT uVKey, LPARAM lKeyData);
    void OnPressHold(HIMC himc, UINT uVKey);
    void OnPressHoldEnd(UINT uVKey);
    UINT ToAsciiEx(HIMC himc, UINT uVKey, UINT uScanCode, LPDWORD pdwTransBuf);
    void MakeResultString(HIMC himc, BOOL fSendNow, BOOL fClearConvEngine);
    void ClearCompositionAndResult(HIMC himc);
    BOOL ChangeCompositionString(HIMC himc, DWORD dwAction);
    BOOL OnOpenStatusChanged(HIMC himc);
    void OnMultiPressSequencingTimeOut();
    UINT GetPrevKey() { return m_uVKeyPrev; }
};

// CriticalSection object to protect CIME
class CRITICAL
{
  private:
    LPCRITICAL_SECTION  m_pcs;

  public:
    CRITICAL(LPCRITICAL_SECTION pcs) { EnterCriticalSection(m_pcs = pcs); }
    ~CRITICAL(void) { LeaveCriticalSection(m_pcs); }
};

class CConverter
{
public:
    CConverter() {};
    ~CConverter() {};
    
    virtual BOOL Init() = 0;
    virtual void ClearComposition() = 0;
    virtual int GetInputMode() = 0;
    virtual BOOL SetInputMode(int nMode) = 0;
    virtual void SetModeIcon(BOOL fSet) = 0;
    virtual LPTSTR Convert(TCHAR ch, int *pcchResult, int *pcchComp) = 0;
    virtual void ProcessShiftKey() = 0;
    virtual void NextMode(BOOL fSkipAmbigMode) = 0;
    virtual BOOL SetCustomSymbols(LPTSTR pszSymbols) = 0;
    virtual void ClearCustomSymbols() = 0;
    virtual void InitCustomSymbolsProcessing() = 0;
    virtual void UnInitCustomSymbolsProcessing() = 0;
    virtual void RedrawModeIcon() = 0;
    virtual BOOL AddToUserDatabase(HWND hwnd) = 0;
    virtual BOOL SaveUserDatabase() = 0;
    virtual void LoadMultiPressTimeOut() = 0;
};

BOOL DllProcessInit(HINSTANCE hinst);
void DllProcessUninit();
void DllThreadInit();
void DllThreadUninit();
LRESULT CALLBACK PhoneIMEWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);

CIME* GetIME(HIMC himc);

CIME* CreateIME(HINSTANCE hinst);
void DeleteIME(CIME* pime);

CConverter* CreateConverter();
void DeleteConverter(CConverter* pConverter);

extern DWORD g_dwTLS;
extern CRITICAL_SECTION g_cs;

// Trace flag. Set to TRUE for Trace messages in debug build.
#define DBF_PHONE_IME (FALSE)

#endif //__PHONEIME_H__
