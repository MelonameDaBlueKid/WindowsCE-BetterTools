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

#ifndef __MTAPCONV_H__
#define __MTAPCONV_H__

#include "..\phoneime.h"
#include "engine.h"
#include <aygshell.h>

// Number of major modes
#define NUM_MODES           (IM_LAST+1)

// Multipress next key wait (in millisecs)
#define MULTIPRESS_TIMER_PERIOD 1000

// Has multipress timeout been disabled by user?
#define MULTIPRESS_TIMEOUT_DISABLED (0xFFFFFFFF)

class CMTapIME;

// Converter
class CMTapConverter : public CConverter
{
private:
    HCONVENG m_hce;             // Conversion engine.
    UINT m_uTimerID;            // Windows timer ID to implement the timer that the conversion engine requires for multi-press.
    LPTSTR m_pszCustomSymbols;  // Optional custom symbols provided by focus window.
    int m_cchCustomSymbols;     // Number of custom symbols.
    SHIME_MODE m_modeIcon;            // Current mode icon
    CMTapIME* m_pime;           // IME to callback.
    DWORD m_dwMultiPressTimeOut; // Multipress Timer timeout
    TCHAR m_chConvBuffer;       // Buffer that holds converted character.

    BOOL m_fInited:1;           // Has converter been initialized?
    BOOL m_fInCustomSymbolSequencing:1; // Is user sequencing through custom symbols using the 1 key.

private:
    void UnInit();
    void ConvEngineCleanUp();
    BOOL ProcessKey(TCHAR ch);
    BOOL SetMode(UINT uMode, BOOL fSet, BOOL fSetIcon);

    // Timer support routines to implement timer that the converter requires for multi-press.
    HRESULT SetMultiPressTimer();
    void KillMultiPressTimer();

    HRESULT NextCustomSymbol(CONVENG_REQUEST_DATA* pcrd);

    HRESULT OnConvEngineRequest(HCONVENG hce, CONVENG_REQUEST_DATA* pcrd);
    static HRESULT ConvEngine_Callback(HCONVENG hce, CONVENG_REQUEST_DATA* crd, LPARAM lpUser);

public:
    CMTapConverter();
    ~CMTapConverter();
    BOOL Init();
    void SetIME(CMTapIME* pime);
    void ClearComposition();
    int GetInputMode();
    BOOL SetInputMode(int nMode);
    void SetModeIcon(BOOL fSet);
    LPTSTR Convert(TCHAR ch, int *pcchResult, int *pcchComp);  
    void ProcessShiftKey();
    void NextMode(BOOL fSkipAmbigMode);
    BOOL SetCustomSymbolMode(BOOL fSet);
    BOOL SetCustomSymbols(LPTSTR pszSymbols);
    void ClearCustomSymbols();
    void InitCustomSymbolsProcessing();
    void UnInitCustomSymbolsProcessing();
    void RedrawModeIcon();
    BOOL AddToUserDatabase(HWND hwnd);
    BOOL SaveUserDatabase();
    void OnMultiPressTimer();
    void LoadMultiPressTimeOut();
};

#endif //__MTAPCONV_H__
