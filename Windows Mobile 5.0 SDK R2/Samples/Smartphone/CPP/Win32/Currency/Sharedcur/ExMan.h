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

#pragma once

const int c_TLACharacters = 3;
const int c_TLABufferSize = c_TLACharacters + 1;

const DWORD EMRIV_TLA =         0x00000001;
const DWORD EMRIV_FULLNAME =    0x00000002;
const DWORD EMRIV_RATE =        0x00000004;
const DWORD EMRIV_UPDATE_TIME = 0x00000008;
const DWORD EMRIV_VISIBLE =     0x00000010;

struct EMRateInfo
{
    DWORD dwValid; // EMRIV_ flags
    TCHAR* pszTLA; // Three Letter Acronym of the currency
    TCHAR* pszFullName;
    double rate; // how many of these per USD
    FILETIME ftLastUpdate; // UTC of the last time this was updated
    BOOL fVisible; // TRUE if this is visible in the UI
};

// Flags for GetRateInfoByIndex
const DWORD GRIBI_ALL_RATES =       0x00000001;
const DWORD GRIBI_VISIBLE_RATES =   0x00000002;

// Flags for GetSeekedDatabase
const DWORD GSDF_CREATE_NEW =       0x00000001;

// Flags for FillControlWithCurrencies
const DWORD FCWCF_ALL_RATES =       0x00000001;
const DWORD FCWCF_VISIBLE_RATES =       0x00000002;

class ExchangeRateManager
{
    struct Monitor
    {
        HWND hwnd;
        UINT uMsg; // Message that we send to the window to say the rate information has changed
    };

    Monitor m_rgMonitors[3];

    HWND m_hwndWorker;

    DWORD m_cVisible;
    CEOID* m_rgVisibleLookup;

    BOOL m_fMounted; // Flag set if we have mounted the database volume
    CEGUID m_guidVolume; // Guid of the volume

    HANDLE m_hdb; // Handle to the exchange rate CE database
    CEOID m_oiddb; // CEOID of the database

    static LRESULT CALLBACK ERMWorkerWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HRESULT GetDatabase(HANDLE* phdb, CEOID* poid);
    HRESULT GetSeekedDatabase(DWORD dwFlags, const TCHAR* pszTLA, HANDLE* phdb, CEOID* poid);
    HRESULT GetRate(const TCHAR* pszTLA, double* pdRate);
    HRESULT GetLookupInfo(int* pcVisible, CEOID** prgVisible);
    HRESULT CreateRateInfoFromCurrentPosition(HANDLE hdb, EMRateInfo** ppemri);

    void ResetLookup();
    void Reset();
public:
    ExchangeRateManager();
    ~ExchangeRateManager();

    HRESULT AddRateChangeMonitor(HWND hwnd, UINT uMsg);
    HRESULT RemoveRateChangeMonitor(HWND hwnd);

    HRESULT Convert(const TCHAR* pszTLAIn, double curIn, const TCHAR* pszTLAOut, double* pcurOut);
    HRESULT GetVisibleRateCount(int* pcRates); // Returns the number of visible rates
    HRESULT GetRateInfoByIndex(DWORD dwFlags, int iRate, EMRateInfo** ppemri);
    HRESULT GetRateInfoByTLA(const TCHAR* pszTLA, EMRateInfo** ppemri);
    HRESULT SetRateInfoByTLA(const TCHAR* pszTLA, const EMRateInfo* pemri);
    HRESULT ResetRateByTLA(const TCHAR* pszTLA);
    
    HRESULT FillControlWithCurrencies(DWORD dwFlags, HWND hwndControl, HINSTANCE hInst, UINT idsFormat, const TCHAR* pszTLADefault);
    HRESULT GetSelectedCurrency(HWND hwndControl, TCHAR* pszTLAOut, int cchBuff);
};

