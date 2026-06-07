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

extern HRESULT  g_hrPasswordOK;         // E_ABORT means cancel
extern BOOL     g_fEnabled;             // TRUE when user is in verification attempt
extern HANDLE   g_hEventComplete;       // Signaled when verification attempt is complete
extern HANDLE   g_hEventLockoutDone;    // Signaled when lockout timer has reached 0
extern DWORD    g_csecLockout;          // Number of seconds remaining in lockout

#define MAX_LOCKOUT_DISPLAY MAX_PATH

// Common functions
HRESULT DoVerify(LPCWSTR pwszAEDisplayText);
HRESULT DoVerifyUserStart(HWND hwndParent, LPCWSTR pwszAEDisplayText);
void    DoVerifyUserStop();
HWND    CreateVerifyDlg(HWND hwndParent, LPCWSTR pwszDisplayText);
BOOL    VerifyDlgProc(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam);
LRESULT PasswordSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT EmergencySubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
