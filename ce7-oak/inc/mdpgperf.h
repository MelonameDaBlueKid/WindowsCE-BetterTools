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
#pragma once

#include "ehm.h"
#include "celog.h"
#include <ceperf.h>

// Deregistering items causes data collected for them to be lost.
// #define the deregistration functions to do nothing to prevent this.
#ifdef CePerfDeregisterTrackedItem
#undef CePerfDeregisterTrackedItem
#endif

#define CePerfDeregisterTrackedItem(hItem) (hItem, S_OK)

#ifdef CePerfDeregisterBulk
#undef CePerfDeregisterBulk
#endif

#define CePerfDeregisterBulk(pItemList, count) (pItemList, count, S_OK)

//PERF DEFAULT LOG FILE
#define MDPGPERF_SESSIONFILE            L"\\mddceperf.log"
#define CEPERF_SESSIONFILE                L"\\ceperf.log"

//PERF Macros for defining performance items
#define PERFITEM(name, type, flags) {INVALID_HANDLE_VALUE, (type), (name), (flags)}
#define DEFAULTSTORAGEFLAGS         (CEPERF_STORE_FILE | CEPERF_STORE_TEXT | CEPERF_STORE_OLDEST)
#define DEFAULTSTATUSFLAGS          (CEPERF_STATUS_RECORDING_DISABLED | CEPERF_STATUS_STORAGE_ENABLED)
#define DURATIONFLAGS               (CEPERF_RECORD_ABSOLUTE_PERFCOUNT | CEPERF_RECORD_ABSOLUTE_TICKCOUNT | CEPERF_RECORD_THREAD_TICKCOUNT | CEPERF_RECORD_ABSOLUTE_CPUPERFCTR | CEPERF_DURATION_RECORD_MIN)
#define PERFITEM_DURATION(name)     PERFITEM(name, CEPERF_TYPE_DURATION, DURATIONFLAGS)
#define PERFITEM_STATISTIC(name)    PERFITEM(name, CEPERF_TYPE_STATISTIC, CEPERF_STATISTIC_RECORD_MIN)

//PERF SESSION NAMES

//GWES
#define EDGPERF_GWES                    TEXT("EDG\\gwes")

// LVMOD - secure loader
#define MDPGPERF_LVMOD                  TEXT("MDPG\\LvMod")

// Security
#define MDPGPERF_SECURITY               TEXT("MDPG\\Security")

// EDB - secure loader
#define EDGPERF_EDB                     TEXT("EDG\\Edb")

//EDG Cell Core
#define EDGPERF_CELLCORE_               TEXT("EDG\\CellCore")

//EDG Cell Core RIL
#define EDGPERF_CELLCORE_RIL            TEXT("EDG\\CellCore\\RIL")

//EDG Cell Core CellTSP
#define EDGPERF_CELLCORE_CELLTSP        TEXT("EDG\\CellCore\\CellTSP")

//EDG Cell Core SIM
#define EDGPERF_CELLCORE_SIM            TEXT("EDG\\CellCore\\SIM")

//EDG Cell Core SMS
#define EDGPERF_CELLCORE_SMS            TEXT("EDG\\CellCore\\SMS")

//Active sync
#define MDPGPERF_ACTIVESYNC             TEXT("MDPG\\ActiveSync")
#define MDPGPERF_SYNCLAP                TEXT("MDPG\\SyncLap")

//Beam
#define MDPGPERF_BEAM                   TEXT("MDPG\\Beam")

//Clock
#define MDPGPERF_CLOCK                  TEXT("MDPG\\Clock")

// DVFC
#define MDPGPERF_DVFC                   TEXT("MDPG\\DVFC")

//FileExplorer
#define MDPGPERF_FILEEXPLORER           TEXT("MDPG\\FileExplorer")

//FilePicker
#define MDPGPERF_FILEPICKER             TEXT("MDPG\\FilePicker")

//Find
#define MDPGPERF_FIND                   TEXT("MDPG\\Find")

//Help
#define MDPGPERF_HELP                   TEXT("MDPG\\Help")

//Inbox
#define MDPGPERF_INBOX                  TEXT("MDPG\\Inbox")
#define MDPGPERF_INBOX_CEMAPI           TEXT("MDPG\\Inbox\\CEMAPI")

//Installer
#define MDPGPERF_INSTALLER              TEXT("MDPG\\Installer")

//MediaPlayer
#define MDPGPERF_MEDIAPLAYER            TEXT("MDPG\\MediaPlayer")

//Zune
#define MDPGPERF_ZUNE                   TEXT("MDPG\\Zune")

//Messenger
#define MDPGPERF_MESSENGER              TEXT("MDPG\\Messenger")

//Multimedia

#define MDPGPERF_AUDIO                  TEXT("MDPG\\Multimedia\\Audio")

//Phone
#define MDPGPERF_PHONE                  TEXT("MDPG\\Phone")
#define MDPGPERF_PHONE_UNIT_TEST        TEXT("MDPG\\Phone\\UnitTests")
#define MDPGPERF_CELLCORE               TEXT("MDPG\\Cellcore")

//Pictures
#define MDPGPERF_PICTURES               TEXT("MDPG\\Pictures")

//pIE
#define MDPGPERF_PIE                    TEXT("MDPG\\pIE")
#define MDPGPERF_IE                     TEXT("IE\\BROWSUI")
#define MDPGPERF_ENTITYEXTACTION        TEXT("IE\\EntityExtraction")
#define MDPGPERF_MSHTML                 TEXT("IE\\MSHTML")
#define MDPGPERF_THUMBVW                TEXT("IE\\THUMBVW")

//pOffice
#define MDPGPERF_POFFICE                TEXT("MDPG\\pOffice")
#define MDPGPERF_POFFICE_PWORD          TEXT("MDPG\\pOffice\\pWord")
#define MDPGPERF_POFFICE_PEXCEL         TEXT("MDPG\\pOffice\\pExcel")
#define MDPGPERF_POFFICE_PPPT           TEXT("MDPG\\pOffice\\ppt")
#define MDPGPERF_POFFICE_TIFF           TEXT("MDPG\\pOffice\\faxview")
#define MDPGPERF_POFFICE_ZIP            TEXT("MDPG\\pOffice\\zipview")
#define MDPGPERF_POFFICE_ONM            TEXT("MDPG\\pOffice\\OneNoteMobile")
#define MDPGPERF_POFFICE_ONM_SMART_SEARCH   TEXT("MDPG\\pOffice\\OneNoteMobile\\SmartSearch")
#define MDPGPERF_POFFICE_SPMC           TEXT("MDPG\\pOffice\\SPMC")
#define MDPGPERF_POFFICE_SPDP           TEXT("MDPG\\pOffice\\SPDP")


//pOutlook 
#define MDPGPERF_POUTLOOK                    TEXT("MDPG\\pOutlook")
#define MDPGPERF_POUTLOOK_CONTACTS           TEXT("MDPG\\pOutlook\\Contacts")
#define MDPGPERF_POUTLOOK_CALENDAR           TEXT("MDPG\\pOutlook\\Calendar")
#define MDPGPERF_POUTLOOK_CALENDAR_SUPPLIER  TEXT("MDPG\\pOutlook\\Calendar\\Supplier")
#define MDPGPERF_POUTLOOK_TASKS              TEXT("MDPG\\pOutlook\\Tasks")
#define MDPGPERF_POUTLOOK_TASK_SUPPLIER      TEXT("MDPG\\pOutlook\\Tasks\\Supplier")
#define MDPGPERF_POUTLOOK_NOTES              TEXT("MDPG\\pOutlook\\Notes")
#define MDPGPERF_POUTLOOK_PIMUTIL            TEXT("MDPG\\pOutlook\\PIMUTIL")
#define MDPGPERF_POUTLOOK_PIMUTILUI          TEXT("MDPG\\pOutlook\\PIMUTILUI")
#define MDPGPERF_POUTLOOK_POOM               TEXT("MDPG\\pOutlook\\POOM")
#define MDPGPERF_POUTLOOK_POOMUI             TEXT("MDPG\\pOutlook\\POOMUI")
#define MDPGPERF_POUTLOOK_STORE              TEXT("MDPG\\pOutlook\\Store")
#define MDPGPERF_POUTLOOK_STORE_EXTERNAL     TEXT("MDPG\\pOutlook\\Store\\External")
#define MDPGPERF_POUTLOOK_MSM                TEXT("MDPG\\pOutlook\\MSM")
#define MDPGPERF_POUTLOOK_KPI                TEXT("MDPG\\pOutlook\\KPITest")

//VoiceCtrl
#define MDPGPERF_VOICECTRL              TEXT("MDPG\\VoiceCtrl")

//TPCUtil
#define MDPGPERF_TPCUTIL                TEXT("MDPG\\Tpcutil")

//Search 
#define MDPGPERF_SEARCH                 TEXT("MDPG\\Search")

//Settings 
#define MDPGPERF_SETTINGS               TEXT("MDPG\\Settings")

//Shell 
#define MDPGPERF_SHELL                  TEXT("MDPG\\Shell")
#define MDPGPERF_HOME                   TEXT("MDPG\\Shell\\Home")               //Home 
#define MDPGPERF_HOME_BOOT              TEXT("MDPG\\Shell\\Home\\Boot")         //Home Boot durations
#define MDPGPERF_SHELLCTRLS             TEXT("MDPG\\Shell\\ShellCtrls")
#define MDPGPERF_MINAPP                 TEXT("MDPG\\Shell\\MinApp")
#define MDPGPERF_EVENTSOUND             TEXT("MDPG\\Shell\\EventSound")
#define MDPGPERF_SHELLCTRLS             TEXT("MDPG\\Shell\\ShellCtrls")
#define MDPGPERF_SHELLCTRLS_RENDERCORE  TEXT("MDPG\\Shell\\ShellCtrls\\RenderCore") // Durations of XGF APIs used by shellctrls.
#define EDGPERF_XR                      TEXT("EDG\\Shell\\XamlRuntime")         // Duration for XAML RunTime Interfaces  

//Rendering 
#define MDPGPERF_RENDERING              TEXT("MDPG\\Rendering")

//SimContacts 
#define MDPGPERF_SIMCONTACTS            TEXT("MDPG\\SimContacts")

//TerminalServicesClient 
#define MDPGPERF_TERMINALSERVICESCLIENT TEXT("MDPG\\TerminalServicesClient")

//Transcriber 
#define MDPGPERF_TRANSCRIBER            TEXT("MDPG\\Transcriber")

//VoIP
#define MDPGPERF_MSVOIPPROV             TEXT("MDPG\\MSVoIPProv")

//Welcome 
#define MDPGPERF_WELCOME                TEXT("MDPG\\Welcome")

//Wininet
#define MDPGPERF_WININET                L"MDPG\\Wininet"

//ConnMGR full record
#define MDPGPERF_CONNMGR                L"MDPG\\Connmgr"

//App Launch
#define MDPGPERF_APPLAUNCH              L"MDPG\\AppLaunch"

//camera
#define MDPGPERF_CAMERA                 TEXT("MDPG\\Camera")

//SmartSearch 
#define MDPGPERF_SMARTSEARCH            TEXT("MDPG\\SmartSearch")

//RIA
#define MDPGPERF_RIA                    TEXT("MDPG\\RIA")

//SvcInfra
#define MDPGPERF_SVCINFRA               TEXT("MDPG\\SvcInfra")
#define MDPGPERF_SVCINFRA_WLID          TEXT("MDPG\\SvcInfra\\WLID")
#define MDPGPERF_SVCINFRA_MSPUSH        TEXT("MDPG\\SvcInfra\\MSPUSH")


// Title and Status bar
#define MDPGPERF_STATUS_DISPATCH        TEXT("MDPG\\Status\\Dispatch")
#define MDPGPERF_TITLEBAR_DRAW          TEXT("MDPG\\Status\\TitleBar_Draw")
#define MDPGPERF_STATUSBAR_DRAW         TEXT("MDPG\\Status\\StatusBar_Draw")

// Telshell
#define MDPGPERF_TELSHELL               TEXT("MDPG\\Telshell")

// Touch/gestures
#define MDPGPERF_TOUCH                  TEXT("MDPG\\Touch")

#define MDPGPERF_START                  TEXT("MDPG\\Start")


// USB
#define MDPGPERF_USB                    TEXT("MDPG\\USB")


//IPSecVPN
#define MDPGPERF_IPSECVPNPM             TEXT("MDPG\\IPSecVPNPM")
#define MDPGPERF_IPSECVPN               TEXT("MDPG\\IPSecVPN")

//Serial
#define MDPGPERF_SERIAL                 TEXT("MDPG\\SERIAL")

//keep this function outside, as it is not only used for perf
_inline BOOL IsLastPaintMessage(HWND hWnd, MSG *pmsg)  
{
    return ((pmsg->message == WM_PAINT) && (!PeekMessage(pmsg, hWnd, WM_PAINT, WM_PAINT, PM_NOREMOVE)));
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Convert a LARGE_INTEGER value from performance counter ticks to microseconds
__inline static VOID MDPGPerformanceCounterToMicroseconds(
    const LARGE_INTEGER* pliPerfCount,  // Performance counter ticks
    ULARGE_INTEGER*       pulMSCount     // Receives value in microseconds
    )
{
    __int64 iVal;
    static LARGE_INTEGER s_liPerfFreq = {0};

    if ((s_liPerfFreq.LowPart == 0) && (s_liPerfFreq.HighPart == 0)) {
        if (!QueryPerformanceFrequency(&s_liPerfFreq)) {
            pulMSCount->QuadPart = 0;
            return;
        }
    }

    iVal = (__int64)pliPerfCount->QuadPart;
    iVal *= 1000000;
    iVal /= s_liPerfFreq.QuadPart;

    pulMSCount->QuadPart = iVal;
}

__inline void MDPGLogTime(LPCWSTR pszEvent)
{
    LARGE_INTEGER liTime;
    DWORD dwMilliSec;
    HKEY hKey;
    LONG lResult;
    ULARGE_INTEGER uliTime = {0};

    QueryPerformanceCounter(&liTime);

    CeLogData(TRUE, CELID_RAW_WCHAR, (PVOID) pszEvent, (WORD)(unsafe_wcslen(pszEvent) + 1) *sizeof (WCHAR), 0, CELZONE_ALWAYSON, 0, FALSE);


    MDPGPerformanceCounterToMicroseconds(&liTime, &uliTime);
    dwMilliSec = (DWORD)((__int64)uliTime.QuadPart/1000);

    lResult = RegCreateKeyExW(HKEY_CURRENT_USER,
                 L"Performance",
                 0, NULL, REG_OPTION_VOLATILE, 
                 0, NULL, &hKey, NULL);

    if (lResult == ERROR_SUCCESS)
    {
    ASSERT(hKey != NULL);
    if(ERROR_SUCCESS != 
       RegQueryValueExW(hKey, pszEvent, NULL, NULL, NULL, NULL))
    {
        RegSetValueExW(hKey, pszEvent, 0, REG_DWORD,
              (LPBYTE)&dwMilliSec, sizeof(DWORD));
    }
        RegCloseKey(hKey);
    }
    
}



#ifndef CEPERF_DISABLE

// Macro for defining session handle variable
#define DEFINE_SESSIONHANDLE(name) HANDLE name = INVALID_HANDLE_VALUE

// Helper function for opening a performance session with default settings
_inline HRESULT MDPGPerfOpenSession(HANDLE *lphSession, LPCWSTR lpszSessionPath)
{
    CEPERF_SESSION_INFO info;
    WCHAR wszSessionFile[] = MDPGPERF_SESSIONFILE;

    // Session setup
    memset(&info, 0, sizeof(info));
    info.wVersion = 1;
    info.dwStorageFlags = DEFAULTSTORAGEFLAGS;
    info.lpszStoragePath = wszSessionFile;

    return CePerfOpenSession(lphSession, lpszSessionPath, DEFAULTSTATUSFLAGS, &info);
}

_inline HRESULT MDPGPerfGetAppLaunchSession(HANDLE *lphSession)
{
    HRESULT hr = S_OK;
    static HANDLE s_hPerfAppLaunchSession = INVALID_HANDLE_VALUE;
    if (s_hPerfAppLaunchSession == INVALID_HANDLE_VALUE)
    {
        hr = MDPGPerfOpenSession(&s_hPerfAppLaunchSession, MDPGPERF_APPLAUNCH);
        CHR(hr);
    }

    *lphSession = s_hPerfAppLaunchSession;

_ehmErrorLab:
    return hr;
}

_inline HRESULT MDPGPerfBeginAppLaunchDuration(LPCWSTR szCmdLine)
{
    HRESULT hr;
    HANDLE hPerfAppLaunchSession, hPerfAppLaunchDuration; 
    const WCHAR c_szLaunching[] = L"Launching";
    hr = MDPGPerfGetAppLaunchSession(&hPerfAppLaunchSession);
    CHR(hr);
    
    hr = CePerfRegisterTrackedItem(hPerfAppLaunchSession, &hPerfAppLaunchDuration, CEPERF_TYPE_DURATION, szCmdLine, DURATIONFLAGS | CEPERF_DURATION_RECORD_SHARED, NULL);
    CHRA(hr);

    CeLogData(TRUE, CELID_RAW_WCHAR, (PVOID) c_szLaunching, sizeof(c_szLaunching), 0, CELZONE_ALWAYSON, 0, FALSE);
    CeLogData(TRUE, CELID_RAW_WCHAR, (PVOID) szCmdLine, (WORD)(unsafe_wcslen(szCmdLine) + 1) * sizeof(WCHAR), 0, CELZONE_ALWAYSON, 0, FALSE);

    hr = CePerfBeginDuration(hPerfAppLaunchDuration);
    CHR(hr);

_ehmErrorLab:
    return hr;
}

// This one should include the the exe name in the szCmdLine passed.  Caller is responsible for
// ensuring it is no more than 32 characters, including terminator.
_inline HRESULT MDPGPerfEndAppLaunchDuration(LPCWSTR szCmdLine)
{
    HRESULT hr;
    HANDLE hPerfAppLaunchSession, hPerfAppLaunchDuration; 
    const WCHAR c_szLaunched[] = L"Launched";
    
    hr = MDPGPerfGetAppLaunchSession(&hPerfAppLaunchSession);
    CHR(hr);
    
    hr = CePerfRegisterTrackedItem(hPerfAppLaunchSession, &hPerfAppLaunchDuration, CEPERF_TYPE_DURATION, szCmdLine, DURATIONFLAGS | CEPERF_DURATION_RECORD_SHARED, NULL);
    CHRA(hr);

    hr = CePerfEndDuration(hPerfAppLaunchDuration, NULL);
    CHR(hr);

    CeLogData(TRUE, CELID_RAW_WCHAR, (PVOID) c_szLaunched, sizeof(c_szLaunched), 0, CELZONE_ALWAYSON, 0, FALSE);
    CeLogData(TRUE, CELID_RAW_WCHAR, (PVOID) szCmdLine, (WORD)(unsafe_wcslen(szCmdLine) + 1) * sizeof(WCHAR), 0, CELZONE_ALWAYSON, 0, FALSE);

_ehmErrorLab:
    return hr;
}

// This one has the exe name and the command line separate
_inline HRESULT MDPGPerfEndAppLaunchDuration2(LPCWSTR szExeName, LPCWSTR szCmdLine)
{
    HRESULT hr = E_FAIL;
    if (szExeName)
    {
        int iExeLen = unsafe_wcslen(szExeName);
        int iCmdLineLen = (szCmdLine && *szCmdLine) ? unsafe_wcslen(szCmdLine) + 1 : 0;

        LPWSTR pszTag = (LPWSTR) LocalAlloc(0, (iExeLen + 1 + iCmdLineLen) * sizeof(WCHAR));
        if (pszTag)
        {
            memcpy(pszTag, szExeName, (iExeLen + 1) * sizeof(WCHAR));
            if (iCmdLineLen)
            {
                pszTag[iExeLen] = TEXT(' ');
                memcpy(pszTag + iExeLen + 1, szCmdLine, iCmdLineLen * sizeof(WCHAR));
            }

            if (iExeLen + iCmdLineLen >= CEPERF_MAX_ITEM_NAME_LEN)
            {
                pszTag[CEPERF_MAX_ITEM_NAME_LEN - 1] = 0;
            }

            hr = MDPGPerfEndAppLaunchDuration(pszTag);
            LocalFree(pszTag);
        }
    }

    return hr;
}

_inline HRESULT MDPGPerfEndAppLaunchDurationUponLastPaint(LPCWSTR szCmdLine, MSG *pmsg)
{
    HRESULT hr = S_OK;
    static BOOL fLaunchDone = FALSE;
    if (!fLaunchDone)
    {
        if(IsLastPaintMessage(NULL, pmsg))
        {
            fLaunchDone = TRUE;
            hr = MDPGPerfEndAppLaunchDuration(szCmdLine);
        }
    }
    return hr;
}

#else  // CEPERF_DISABLE

#define DEFINE_SESSIONHANDLE(name)
#define MDPGPerfOpenSession(lphSession, lpszSessionPath)
#define MDPGPerfGetAppLaunchSession(lphSession)
#define MDPGPerfBeginAppLaunchDuration(szCmdLine)
#define MDPGPerfEndAppLaunchDuration(szCmdLine)
#define MDPGPerfEndAppLaunchDuration2(szExeName, szCmdLine)
#define MDPGPerfEndAppLaunchDurationUponLastPaint(szCmdLine, pmsg)

#endif  // CEPERF_DISABLE

