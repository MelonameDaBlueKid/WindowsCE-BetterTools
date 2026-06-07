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

#ifndef DLGUTIL_H
#define DLGUTIL_H

#include <windows.h>
#include <wincrypt.h>
#include <regext.h>
#include <functional>

#define HKEY_ROOT HKEY_LOCAL_MACHINE

extern HINSTANCE    g_hInst;

// Maximum settings.
#define MAX_PASSWORD            40
#define MAX_CODEWORD            32
#define MAX_FREQUENCY_VALUE     9999
#define MAX_COMPLEXITY          4
#define MAX_INT_LENGTH          10 // Num of chars in INT_MAX
#define MAX_PASSWORD_HISTORY    50

#define SALT_LENGTH                 128   // Salt the hash with 128 bytes.

// Timers.
#define IDT_IDLE_TIMEOUT  901
#define IDT_LOCKOUT       902

extern const TCHAR * K_SZRESETTEXT;
extern const TCHAR * K_SZLAPKEY;
extern const TCHAR * K_SZHASHALG;
extern const TCHAR * K_SZPROVTYPE;
extern const TCHAR * K_SZPROVNAME;

// String loading defs.
#define CELOADSZ(ids) ((LPCTSTR)LoadString(g_hInst, ids, NULL, 0))
inline const TCHAR* SafeCELOADSZ(int ids)
{
    const TCHAR *pszRes = (LPCTSTR)LoadString(g_hInst, ids, NULL, 0);
    return (NULL != pszRes ? pszRes : TEXT(""));
}

// RECT helpers.
#define RECTWIDTH(rc)  ((rc).right - (rc).left)
#define RECTHEIGHT(rc) ((rc).bottom - (rc).top)

// Common macros.
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))
#define BOOLIFY(x)   (!!(x))      

typedef struct
{
    // Policies.
    BOOL        bPasswordOn;
    UINT        uFrequencyType;
    UINT        uFrequencyValue;
    UINT        uComplexity;
    UINT        uMinLength;
    UINT        uNumberOfPasswords;
} PASSWDPOLICY;

struct PASSWDINFO
{
    // User settings.
    BOOL        bPasswordOn;
    UINT        uFrequencyType;
    UINT        uFrequencyValue;
    TCHAR       szPassword[MAX_PASSWORD + 1];

    // Policy struct.
    PASSWDPOLICY Policy;

    // Other dialog info not related to saved settings.
    HFONT       hFont;
    BOOL        bSecure;
    BOOL        bPasswordChanged;
};

typedef enum tagBUTTON_INFO
{
    BUTTON_INFO_OK = 0,  // OK only (default).
    BUTTON_INFO_YESNO    // Yes & No .
} BUTTON_INFO;

typedef struct
{
    LPCTSTR     pszTitle;
    LPCTSTR     pszMessage;
    BUTTON_INFO biButtons;  // Defaults to OK only.
    HANDLE      heventDisplayed;
    BOOL        fCloseOnActivationLoss;
    HREGNOTIFY  hNotify;
} MESSAGEINFO;

extern BOOL         g_fPolicyRequiresUpdate;


// Window management.
//

typedef enum tagLAP_WINDOW
{
    LAP_WINDOW_VERIFY,
    LAP_WINDOW_CODEWORD,
    LAP_WINDOW_PREWIPE,
    LAP_WINDOW_ENROLL,
    LAP_WINDOW_LAST = LAP_WINDOW_ENROLL
} LAP_WINDOW;

class WindowManager;

WindowManager & WndManager();

class WindowManager
{
private:
    friend WindowManager & WndManager();

    WindowManager()
    {
        for (int i = 0; i < m_windows_size; ++i)
            m_windows[i] = NULL;
    }

public:
    void Reserve(int index)
    {
        Check(index);
        m_windows[index] = reinterpret_cast<HWND>(m_reserved_wnd);
    }

    bool IsReserved(int index) const
    {
        Check(index);
        return m_windows[index] == reinterpret_cast<HWND>(m_reserved_wnd);
    }

    void Clear(int index)
    {
        m_windows[index] = NULL;
    }

    bool IsStored(int index) const
    {
        return m_windows[index] != NULL;
    }

    HWND & operator[](int index)
    {
        return m_windows[index];
    }

    HWND const & operator[](int index) const
    {
        return m_windows[index];
    }

private:
    void Check(int index) const
    {
        ASSERT(index < m_windows_size);
    }

private:
    static const int m_windows_size = LAP_WINDOW_LAST + 1;
    static const int m_reserved_wnd = -1;

    HWND m_windows[m_windows_size];
};

inline WindowManager & WndManager()
{
    static WindowManager inst;
    return inst;
}


// User messages.
#define WM_APP_FOREGROUND      (WM_APP +  1)
#define WM_APP_ENABLE          (WM_APP +  2)
#define WM_APP_DISABLE         (WM_APP +  3)
#define WM_APP_ONOK            (WM_APP +  4)
#define WM_APP_ONCANCEL        (WM_APP +  5)
#define WM_APP_ACTIVECALLS     (WM_APP +  6)
#define WM_APP_ONEDIT          (WM_APP +  7)
#define WM_APP_ENUMBER         (WM_APP +  8)
#define WM_APP_REGISTERCALLS   (WM_APP +  9)
#define WM_APP_DEACTIVATE      (WM_APP + 10)
#define WM_APP_LOCK            (WM_APP + 11)

// Read/write data store.
HRESULT GetPasswordInfo(PASSWDINFO* ppwi);
HRESULT SavePasswordInfo(PASSWDINFO const * ppwi);
HRESULT GetPolicy(PASSWDPOLICY* pPolicy);
HRESULT GetLKGPolicy(PASSWDPOLICY* pPolicy);
HRESULT SaveLKGPolicy(PASSWDPOLICY const * pPolicy);
BOOL    LapGetPasswordOn();
BOOL    LapCheckPassword(LPCTSTR pszPassword);
BOOL    LapSetPasswordOff(LPCTSTR pszPassword);
BOOL    LapSetPasswordOn(LPCTSTR pszOldPassword, LPCTSTR pszNewPassword);

// Utility functions.
void    SavePasswordForEnrollment(LPCTSTR pszPassword);
void    FreePasswordForEnrollment();
BOOL    SetWindowToTop(LAP_WINDOW lw);
DWORD   PolicyThreadProc(LPVOID lpParameter);
BOOL    PolicyRequiresUpdate(PASSWDINFO* ppwi, PASSWDPOLICY* pLKGPolicy);
BOOL    LASSVerifyUser(const GUID *AEKey, LPCWSTR pwszAEDisplayText, HWND hwndParent, DWORD dwOptions, PVOID pExtended);
void    MakeEmergencyCall(LPCTSTR pszNumber);
void    ResetIdleTimer(HWND hwnd);
void    KillIdleTimer (HWND hwnd);
DWORD   MsgBlockOnEvent(HANDLE hEvent, HWND hwndDlg);
HRESULT DisplayPolicyUpdate(HWND hwndParent);
HRESULT DisplayMessage  (HWND hwndOwner, UINT uTitle, UINT uMessage);
HRESULT DisplayQuestion (HWND hwndOwner, UINT uTitle, UINT uMessage);
HRESULT DisplayMessageEx(HWND hwndOwner, UINT uTitle, LPCTSTR pszMessage);
int     DisplayMessage(HWND owner, LPCTSTR title, LPCTSTR message, BUTTON_INFO dlgButtons, HANDLE heventDisplayed);
BOOL    DeviceHasPhone();
HREGNOTIFY RegisterCallNotifications(HWND hwnd);
void    UnregisterCallNotifications(HREGNOTIFY hRegNotify);
DWORD   GetActiveCallCount();
BOOL    MessageDlgProc(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam);
DWORD   GetPasswordTimeout();
void    ShowInfo(HWND hwndDlg, BOOL fIsEmergency, BOOL fIsCodeword, BOOL fClear, LPCTSTR pszOverride);
ALG_ID  GetHashAlgorithm();
DWORD   GetProviderType();
HCRYPTPROV CreateCryptProv();
HRESULT GetCryptoProviderName(__deref_out LPTSTR *ppszName);
BOOL    GetStoredCryptoSettings(__out HCRYPTPROV* phCryptProv, __out DWORD* pdwCryptHashAlg);
BOOL    SetStoredCryptoSettings(__in HCRYPTPROV hCryptProv, DWORD dwCryptHashAlg);
BOOL    InitProvider(DWORD dwProvType, __in_opt LPCTSTR pszProvName, __out HCRYPTPROV* phCryptProv);
BOOL    HashStringWorker (HCRYPTPROV hCryptProv, ALG_ID alg, LPCTSTR pszString, LPBYTE pbSalt, DWORD cbSalt, BYTE** ppbHash, DWORD* pcbHash);
BOOL    HashString(HCRYPTPROV hCryptProv, ALG_ID alg, LPCTSTR pszString, BYTE** ppbHash, DWORD* pcbHash, LPBYTE* ppbSalt);
TCHAR   MapVKeyToChar(UINT uvKey);
LONG    GetEncryptedPasswordHash (DATA_BLOB *pblobData);
BOOL    GetSalt (BYTE *pbSalt, DWORD cbSize);

//  Release provider with a function having one argument.
//  CryptReleaseContext cannot be passed to ScopeProtect because
//  it has two arguments.
//
inline void ReleaseProvider(HCRYPTPROV prov)
{
    CryptReleaseContext(prov, 0);
}

inline HRESULT HResultFromWin32(DWORD error)
{
    return HRESULT_FROM_WIN32(error);
}

//  Concatenate two strings.
//  The output string is null terminated, allocated with LocalAlloc and should be freed by the caller.
//
HRESULT Concat(LPCTSTR str1, LPCTSTR str2, /*out*/ TCHAR ** output);


//  Function object template.
//  Intended for generic callbacks.
//  Derive from it to make your own callback
//  
template <typename Ret, typename Arg = void>
struct function1 : public std::unary_function<Arg, Ret>
{
    virtual Ret operator()(Arg) = 0;
};

template <typename Ret, typename Arg1, typename Arg2>
struct function2 : public std::binary_function<Arg1, Arg2, Ret>
{
    virtual Ret operator()(Arg1, Arg2) = 0;
};

template <typename Ret, typename Arg1, typename Arg2, typename Arg3>
struct function3
{
    virtual Ret operator()(Arg1, Arg2, Arg3) = 0;
};


//  Non-throwing operator new() defined as LocalAlloc.
//  Use LocalFree to free the memory allocated this way.
//

class localalloc_t {};
extern const localalloc_t localalloc;

inline
void * operator new(size_t size, localalloc_t) throw()
{
    return LocalAlloc(0, size);
}

inline
void * operator new[](size_t size, localalloc_t) throw()
{
    return LocalAlloc(0, size);
}

inline
void operator delete(void * p, localalloc_t) throw()
{
    LocalFree(p);
}

inline
void operator delete[](void * p, localalloc_t) throw()
{
    LocalFree(p);
}

template <typename T>
void localalloc_delete(T * p) throw()
{
    if (!p)
    {
        return;
    }

    p->~T();
    ::operator delete(p, localalloc);
}

template <typename T>
void localalloc_array_delete(T * p, size_t size) throw()
{
    if (!p)
    {
        return;
    }

    for (; size != 0; --size; ++p)
    {
        p->~T();
    }

    ::operator delete[](p, localalloc_t);
}

#endif  // DLGUTIL_H
