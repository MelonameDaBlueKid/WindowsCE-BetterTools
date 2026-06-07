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

#include "stdafx.h"
#include "helpers.h"
#include "ExMan.h"
#include "cur.h"

const UINT c_idtBatch = 1;
const UINT c_cmsBatch = 250; // We have to go a quarter second without receiving a database notify before we notify monitors

const TCHAR g_szERMWorkerClassName[] = TEXT("ExchangeRateManagerWorker");
const TCHAR g_szAppDataDir[] = TEXT("CurrencyConverter"); // location where we put our data files that the user doesn't deal with.
const TCHAR g_szAppDataBaseVolumeFileName[] = TEXT("Rate Database");

const TCHAR c_pszDatabaseName[] = TEXT("Currency Information");
#define CPR_TLA                 PROP_TAG(CEVT_LPWSTR, 0x0001)
#define CPR_RATE                PROP_TAG(CEVT_R8, 0x0002)
#define CPR_VISIBLE             PROP_TAG(CEVT_BOOL, 0x0003)
#define CPR_FULLNAME            PROP_TAG(CEVT_LPWSTR, 0x0004)
#define CPR_UPDATE_TIME         PROP_TAG(CEVT_FILETIME, 0x0005)

/*****************************************************************************
    Initial rate info that is hard coded in the executable.  If the database
    doesn't exist, we fill it in with this information.
 ****************************************************************************/
struct RateDefaultInfo
    {
    const TCHAR* pszTLA;
    double dRate;
    UINT ids;
    };

static const RateDefaultInfo g_rgri[] =
    {
    #define DEFINE_CURRENCY(tla, name, rate) { TEXT( # tla ), rate, IDS_CUR_ ## tla },
    #include "currencies.h"
    {NULL, 0, 0} // last entry
    };

/*****************************************************************************

 ****************************************************************************/
LRESULT CALLBACK ExchangeRateManager::ERMWorkerWndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    LRESULT lResult = 0;
    
    switch(msg)
        {
        case WM_CREATE:
            {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;

            if(NULL == pcs->lpCreateParams)
                {
                lResult = -1;
                break;
                }
            SetLastError(0);
            SetWindowLong(hwnd, 0, (LONG)pcs->lpCreateParams);
            if(0 != GetLastError())
                {
                lResult = -1;
                break;
                }
            }
            break;

        case DB_CEOID_CHANGED:
        case DB_CEOID_CREATED:
        case DB_CEOID_RECORD_DELETED:
            // Since a bulk update of the database
            // can send a flurry of notifications,
            // we batch them up and send a single one.
            KillTimer(hwnd, c_idtBatch);
            VERIFY(SetTimer(hwnd, c_idtBatch, c_cmsBatch, NULL));
            break;

        case WM_TIMER:
            if(c_idtBatch == wParam)
                {
                ExchangeRateManager* pThis;

                VERIFY(KillTimer(hwnd, c_idtBatch));
                
                if(pThis = (ExchangeRateManager*)GetWindowLong(hwnd, 0))
                    {
                    int iMonitor;

                    for(iMonitor = 0; iMonitor < ARRAYSIZE(pThis->m_rgMonitors); iMonitor++)
                        {
                        if(NULL != pThis->m_rgMonitors[iMonitor].hwnd)
                            {
                            PostMessage(pThis->m_rgMonitors[iMonitor].hwnd, pThis->m_rgMonitors[iMonitor].uMsg, 0, 0);
                            }
                        }
                    }
                }
            break;
        

        default:
            lResult = DefWindowProc(hwnd, msg, wParam, lParam);
            break;
            
        }
    return(lResult);
}


/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetDatabase(
    HANDLE* phdb, // out - handle to database.  Caller should NOT delete this handle!
    CEOID* poid // out - oid of the database.
    )
{
    HRESULT hr = S_OK;
    size_t cLen;


    // Create / get the database volume if we don't already have it.
    if(!m_fMounted)
        {
        TCHAR szVolumeFile[MAX_PATH];

        if(!SHGetSpecialFolderPath(NULL, szVolumeFile, CSIDL_APPDATA, TRUE))
            {
            ASSERT(FALSE);
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }

        StringCchLength(szVolumeFile, ARRAYSIZE(szVolumeFile), &cLen);
        if(cLen + ARRAYSIZE(g_szAppDataDir) + ARRAYSIZE(g_szAppDataBaseVolumeFileName) + 10 >
                ARRAYSIZE(szVolumeFile))
            {
            // Not enough space to build our file name
            hr = E_FAIL;
            goto Error;
            }

        // Note that there are better ways to build up a file name...
        StringCchLength(szVolumeFile, ARRAYSIZE(szVolumeFile), &cLen);
        if(cLen == 0 || szVolumeFile[cLen - 1] != TEXT('\\'))
            {
            StringCchLength(szVolumeFile, ARRAYSIZE(szVolumeFile), &cLen);
            StringCchCat(szVolumeFile, ARRAYSIZE(szVolumeFile) - cLen, TEXT("\\"));
            }
        StringCchLength(szVolumeFile, ARRAYSIZE(szVolumeFile), &cLen);
        StringCchCat(szVolumeFile, ARRAYSIZE(szVolumeFile) - cLen, g_szAppDataDir);
        if(0xFFFFFFFF == GetFileAttributes(szVolumeFile))
            {
            if(0 == CreateDirectory(szVolumeFile, NULL))
                {
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Error;
                }
            }
        StringCchLength(szVolumeFile, ARRAYSIZE(szVolumeFile), &cLen);
        StringCchCat(szVolumeFile, ARRAYSIZE(szVolumeFile) - cLen, TEXT("\\"));

        StringCchLength(szVolumeFile, ARRAYSIZE(szVolumeFile), &cLen);
        StringCchCat(szVolumeFile, ARRAYSIZE(szVolumeFile) - cLen, g_szAppDataBaseVolumeFileName);

        if(!CeMountDBVolEx(&m_guidVolume, szVolumeFile, NULL, OPEN_ALWAYS))
            {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }

        m_fMounted = TRUE;
        }


    if(INVALID_HANDLE_VALUE == m_hdb)
        {
        CENOTIFYREQUEST notreq;
        m_oiddb = NULL;

        // Create the worker window that gets informed of database changes.
        if(NULL == m_hwndWorker)
            {
            WNDCLASS wc;

            if(!GetClassInfo(g_hInst, g_szERMWorkerClassName, &wc))
                {
                ZeroMemory(&wc, sizeof(wc));
                wc.hInstance = g_hInst;
                wc.lpfnWndProc = ERMWorkerWndProc;
                wc.cbWndExtra = sizeof(ExchangeRateManager*);
                wc.lpszClassName  = g_szERMWorkerClassName;
                if(0 == RegisterClass(&wc))
                    {
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    goto Error;
                    }
                }
            m_hwndWorker = CreateWindowEx(0, g_szERMWorkerClassName, NULL, WS_CLIPCHILDREN,
                                  0, 0, 0, 0,
                                  NULL, (HMENU)NULL, g_hInst, this);

            if(NULL == m_hwndWorker)
                {
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Error;
                }
            }

        ZeroMemory(&notreq, sizeof(notreq));
        notreq.dwSize = sizeof(notreq);
        notreq.hwnd = m_hwndWorker;
        notreq.dwFlags = 0; // we want V1.0-2.0 behavior
        m_hdb = CeOpenDatabaseEx(&m_guidVolume, &m_oiddb,
                const_cast<TCHAR*>(c_pszDatabaseName), CPR_TLA, 0, &notreq);
        if(INVALID_HANDLE_VALUE == m_hdb)
            {
            DWORD dwError = GetLastError();
            const RateDefaultInfo* prdi;
            FILETIME ftDefaults;
            CEDBASEINFOEX dbi;
            
            if(ERROR_FILE_NOT_FOUND != dwError)
                {
                // We don't deal with errors other than ERROR_FILE_NOT_FOUND
                hr = HRESULT_FROM_WIN32(dwError);
                goto Error;
                }

            // Looks like the database hasn't been created so create it.
            ZeroMemory(&dbi, sizeof(dbi));
            dbi.wVersion = CEDBASEINFOEX_VERSION;
            dbi.dwFlags = CEDB_VALIDNAME | CEDB_VALIDSORTSPEC;

            if(ARRAYSIZE(c_pszDatabaseName) > ARRAYSIZE(dbi.szDbaseName)) // should use CASSERT
                {
                hr = E_FAIL;
                goto Error;
                }
            StringCchCopy(dbi.szDbaseName, ARRAYSIZE(dbi.szDbaseName), c_pszDatabaseName);
            dbi.wNumSortOrder = 1;
            dbi.rgSortSpecs[0].wVersion = SORTORDERSPECEX_VERSION;
            dbi.rgSortSpecs[0].wNumProps = 1;
            dbi.rgSortSpecs[0].wKeyFlags = 0;
            dbi.rgSortSpecs[0].rgPropID[0] = CPR_TLA;
            dbi.rgSortSpecs[0].rgdwFlags[0] = CEDB_SORT_CASEINSENSITIVE;

            m_oiddb = CeCreateDatabaseEx2(&m_guidVolume, &dbi);
            if(NULL == m_oiddb)
                {
                // We should probably check for GetLastError == ERROR_DUP_NAME
                // here and recover. (this could happen if another thread
                // with an ExchangeRateManager is running this code)
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Error;
                }

            // Open the newly created database
            ZeroMemory(&notreq, sizeof(notreq));
            notreq.dwSize = sizeof(notreq);
            notreq.hwnd = m_hwndWorker;
            notreq.dwFlags = 0; // we want V1.0-2.0 behavior
            m_hdb = CeOpenDatabaseEx2(&m_guidVolume,
                                      &m_oiddb,
                                      NULL ,
                                      &dbi.rgSortSpecs[0], 
                                      CEDB_AUTOINCREMENT,
                                      &notreq);

            if(INVALID_HANDLE_VALUE == m_hdb)
                {
                // Something is way messed up.
                m_hdb = INVALID_HANDLE_VALUE;
                m_oiddb = NULL;
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Error;
                }

            // Fill the newly created database with the hard-coded default data

            if(FAILED(hr = GetFileTimeForDate(CUR_UPD_YEAR, CUR_UPD_MONTH, CUR_UPD_DAY, &ftDefaults)))
                {
                goto Error;
                }

            for(prdi = g_rgri; NULL != prdi->pszTLA; prdi++)
                {
                TCHAR szFullName[100];
                CEPROPVAL rgVals[5];
                int iVal = 0;

                ZeroMemory(rgVals, sizeof(rgVals));
                
                rgVals[iVal].propid = CPR_TLA;
                rgVals[iVal].val.lpwstr = const_cast<TCHAR*>(prdi->pszTLA);
                iVal++;

                rgVals[iVal].propid = CPR_RATE;
                rgVals[iVal].val.dblVal = prdi->dRate;
                iVal++;

                // Feel free to put in your own ethnocentric
                // defaults for which currencies are visible
                // (someone will always be peeved...)
                rgVals[iVal].propid = CPR_VISIBLE;
                rgVals[iVal].val.boolVal = TRUE;
                iVal++;

                if(0 == LoadString(g_hInstRes, prdi->ids, szFullName, ARRAYSIZE(szFullName)))
                    {
                    // Couldn't load the string.  It is likely
                    // the resources are out of sync.
                    ASSERT(FALSE);
                    // We should probably delete the entire database at this point
                    // though this error will likely never happen in production.
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    goto Error;
                    }
                rgVals[iVal].propid = CPR_FULLNAME;
                rgVals[iVal].val.lpwstr = szFullName;
                iVal++;

                rgVals[iVal].propid = CPR_UPDATE_TIME;
                rgVals[iVal].val.filetime = ftDefaults;
                iVal++;

                ASSERT(iVal == ARRAYSIZE(rgVals));

                if(NULL == CeWriteRecordProps(m_hdb, NULL, ARRAYSIZE(rgVals), rgVals))
                    {
                    // We should probably delete the entire database here
                    // since it will be missing a bunch of default currency
                    // values.
                    hr = HRESULT_FROM_WIN32(GetLastError());
                    goto Error;
                    }
                
                }
            }
        }

    if(phdb)
        {
        *phdb = m_hdb;
        }
    if(poid)
        {
        *poid = m_oiddb;
        }

Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetSeekedDatabase(
    DWORD dwFlags, // in - flags controling operation of this function
    const TCHAR* pszTLA, // in - TLA of the currency record to seek the database to
    HANDLE* phdb, // out - handle to the database that is seeked to that record.  Don't call DeleteHandle on this!!!
    CEOID* poid // out - oid of the record we seeked to
    )
{
    HRESULT hr = S_OK;
    HANDLE hdb;
    CEPROPVAL val;
    CEOID oid;
    
    if(FAILED(hr = GetDatabase(&hdb, NULL)))
        {
        goto Error;
        }

    val.propid = CPR_TLA;
    val.wFlags = 0;
    val.val.lpwstr = const_cast<TCHAR*>(pszTLA);
    oid = CeSeekDatabase(hdb, CEDB_SEEK_VALUEFIRSTEQUAL, (DWORD)&val,
            NULL /* yes, this param can be null and should be if you don't need it */);
    if(NULL == oid)
        {
        CEPROPVAL val;

        if(!(dwFlags & GSDF_CREATE_NEW))
            {
            // Caller didn't tell us to create a new record.
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }

        // Let's assume that the record was not found because
        // this is a new currency. (probably a bad assumption)
        // Create a new record since the caller told us to.

        val.propid = CPR_TLA;
        val.wFlags = 0;
        val.val.lpwstr = const_cast<TCHAR*>(pszTLA);
        oid = CeWriteRecordProps(hdb, NULL, 1, &val);
        if(NULL == oid)
            {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }
        ResetLookup();
        // Seek the database to the new record.
        if(oid != CeSeekDatabase(hdb, CEDB_SEEK_CEOID, oid, NULL))
            {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }
        
        }

    if(phdb)
        {
        *phdb = hdb;
        }

    if(poid)
        {
        *poid = oid;
        }

Error:
    return(hr);

}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetRate(
    const TCHAR* pszTLA,
    double* pdRate
    )
{
    HRESULT hr = S_OK;
    HANDLE hdb;
    CEPROPID id;
    CEPROPVAL* pVals = NULL;
    WORD cProps;
    DWORD cb;

    // Note that if this were called a lot, a two or three rate cache would
    // probably be good for perf since we wouldn't have to hit the database.
    // As it stands, the CE database is fast enough for the current demands.

    // light parameter check
    if(!pszTLA || (3 != _tcslen(pszTLA)) || !pdRate)
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    // USD is always 1
    if(0 == _tcsicmp(TEXT("USD"), pszTLA))
        {
        *pdRate = 1.0;
        goto Exit;
        }

    if(FAILED(hr = GetSeekedDatabase(0, pszTLA, &hdb, NULL)))
        {
        goto Error;
        }

    cProps = 1;
    id = CPR_RATE;
    
    if(0 == CeReadRecordPropsEx(hdb, CEDB_ALLOWREALLOC, &cProps, &id, (BYTE**)&pVals, &cb, NULL))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    if((CPR_RATE != pVals->propid) || (pVals->wFlags & CEDB_PROPNOTFOUND))
        {
        // Database is messed up since we were able to seek to the rate but there
        // was no rate information there.
        ASSERT(FALSE);
        hr = E_FAIL;
        }

    *pdRate = pVals->val.dblVal;

Error:
Exit:
    VERIFY(NULL == LocalFree(pVals));
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetLookupInfo(
    int* pcVisible,
    CEOID** prgVisible
    )
{
    HRESULT hr = S_OK;
    CEPROPVAL* pVals = NULL;

    if(NULL == m_rgVisibleLookup)
        {
        CEOID oidDB;
        CEOID oidCur;
        CEOIDINFOEX oi;
        DWORD cDatabaseRecords;
        CEPROPID id;
        WORD cProps;
        DWORD cb;
        HANDLE hdb;

        // Need to build the lookup table

        if(FAILED(hr = GetDatabase(&hdb, &oidDB)))
            {
            goto Error;
            }

        oi.wVersion = BY_HANDLE_DB_INFORMATION_VERSION;
        if(!CeOidGetInfoEx2(&m_guidVolume, oidDB, &oi))
            {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }
        cDatabaseRecords = (UINT) oi.infDatabase.dwNumRecords;

        // We allocate the translation array with an entry for every
        // record even though we only create entries for visible
        // records.  Some memory could be saved by later re-allocing
        // the array or by running through the database twice (once
        // to get the record count and another to build the array)

        m_rgVisibleLookup = new CEOID[cDatabaseRecords];
        m_cVisible = 0;

        oidCur = CeSeekDatabase(hdb, CEDB_SEEK_BEGINNING, 0, NULL);
        if(NULL == oidCur)
            {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }

        id = CPR_VISIBLE;
        cProps = 1;
        cb = 0;

        while (NULL != oidCur && m_cVisible < cDatabaseRecords)
            {
            if((oidCur == CeReadRecordPropsEx(hdb, CEDB_ALLOWREALLOC, &cProps, &id, (BYTE**)&pVals, &cb, NULL)) &&
                    !(pVals->wFlags & CEDB_PROPNOTFOUND) &&
                    (pVals->val.boolVal))
                {
                // The current record is visible
                m_rgVisibleLookup[m_cVisible] = oidCur;

                m_cVisible++;
                }
            oidCur = CeSeekDatabase(hdb, CEDB_SEEK_CURRENT, 1, NULL);
            }
        }


    // Set the out parameters
    if(pcVisible)
        {
        *pcVisible = m_cVisible;
        }

    if(prgVisible)
        {
        *prgVisible = m_rgVisibleLookup;
        }

Exit:
    VERIFY(NULL == LocalFree(pVals));
    return(hr);
Error:
    // something bad happened building the lookup table
    ResetLookup();
    goto Exit;
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::CreateRateInfoFromCurrentPosition( // nothing like a descriptive function name...
    HANDLE hdb,
    EMRateInfo** ppemri // out - rate info structure.  Caller must free.
    )
{
    HRESULT hr = S_OK;
    CEPROPVAL* pVals = NULL;
    WORD cProps;
    DWORD cb;
    EMRateInfo riTemp;
    EMRateInfo* priNew = NULL;
    int iProp;

    if(NULL == ppemri)
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    cProps = 0;
    cb = 0;
    if(NULL == CeReadRecordPropsEx(hdb, CEDB_ALLOWREALLOC, &cProps, NULL, (BYTE**)&pVals, &cb, NULL))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    ZeroMemory(&riTemp, sizeof(riTemp));
    for(iProp = 0; iProp < cProps; iProp++)
        {
        const CEPROPVAL* pVal = pVals + iProp;
        if(!(pVal->wFlags & CEDB_PROPNOTFOUND))
            {
            switch(pVal->propid)
                {
                case CPR_TLA:
                    riTemp.dwValid |= EMRIV_TLA;
                    riTemp.pszTLA = pVal->val.lpwstr;
                    break;
                case CPR_FULLNAME:
                    riTemp.dwValid |= EMRIV_FULLNAME;
                    riTemp.pszFullName = pVal->val.lpwstr;
                    break;
                case CPR_RATE:
                    riTemp.dwValid |= EMRIV_RATE;
                    riTemp.rate = pVal->val.dblVal;
                    break;
                case CPR_UPDATE_TIME:
                    riTemp.dwValid |= EMRIV_UPDATE_TIME;
                    riTemp.ftLastUpdate = pVal->val.filetime;
                    break;
                case CPR_VISIBLE:
                    riTemp.dwValid |= EMRIV_VISIBLE;
                    riTemp.fVisible = pVal->val.boolVal;
                    break;
                }
            }
        }

    // Create the EMRateInfo we actually pass back
    priNew = (EMRateInfo*)LocalAlloc(LMEM_FIXED, sizeof(EMRateInfo) +
            (sizeof(TCHAR) * (_tcslen(riTemp.pszTLA) + 1 + _tcslen(riTemp.pszFullName) + 1)));
    if(NULL == priNew)
        {
        hr = E_OUTOFMEMORY;
        goto Error;
        }

    memcpy(priNew, &riTemp, sizeof(riTemp));
    priNew->pszTLA = (TCHAR*)((BYTE*)priNew + sizeof(*priNew));
    _tcscpy(priNew->pszTLA, riTemp.pszTLA);
    priNew->pszFullName = priNew->pszTLA + 1 + _tcslen(priNew->pszTLA);
    _tcscpy(priNew->pszFullName, riTemp.pszFullName);
    
    *ppemri = priNew;
    priNew = NULL;

Error:
    VERIFY(NULL == LocalFree(priNew));
    VERIFY(NULL == LocalFree(pVals));
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
void ExchangeRateManager::ResetLookup()
{
    m_cVisible = 0;
    delete[](m_rgVisibleLookup);
    m_rgVisibleLookup = NULL;
}

/*****************************************************************************

 ****************************************************************************/
void ExchangeRateManager::Reset()
{
    ZeroMemory(m_rgMonitors, sizeof(m_rgMonitors));

    if(m_hwndWorker)
        {
        DestroyWindow(m_hwndWorker);
        m_hwndWorker = NULL;
        }

    ResetLookup();

    if(INVALID_HANDLE_VALUE != m_hdb)
        {
        CloseHandle(m_hdb);
        m_hdb = INVALID_HANDLE_VALUE;
        }
    m_oiddb = NULL;

    if(m_fMounted)
        {
        VERIFY(CeUnmountDBVol(&m_guidVolume));
        m_fMounted = FALSE;
        }
    ZeroMemory(&m_guidVolume, sizeof(m_guidVolume));
}

/*****************************************************************************

 ****************************************************************************/
ExchangeRateManager::ExchangeRateManager() :
    m_hwndWorker(NULL)
    ,m_rgVisibleLookup(NULL)
    ,m_fMounted(FALSE)
    ,m_hdb(INVALID_HANDLE_VALUE)
{
    Reset();
}

/*****************************************************************************

 ****************************************************************************/
ExchangeRateManager::~ExchangeRateManager()
{
    Reset();
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::AddRateChangeMonitor(
    HWND hwnd,
    UINT uMsg
    )
{
    HRESULT hr = S_OK;
    int iMonitor;

    // Find a free slot
    for(iMonitor = 0; (iMonitor < ARRAYSIZE(m_rgMonitors)) &&
            (NULL != m_rgMonitors[iMonitor].hwnd); iMonitor++);
    if(iMonitor >= ARRAYSIZE(m_rgMonitors))
        {
        // No free monitor slots, bump up the dimension of m_rgMonitors.
        ASSERT(FALSE);
        hr = E_FAIL;
        goto Error;
        }
        
    m_rgMonitors[iMonitor].hwnd = hwnd;
    m_rgMonitors[iMonitor].uMsg = uMsg;

Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::RemoveRateChangeMonitor(
    HWND hwnd
    )
{
    HRESULT hr = S_OK;
    int iMonitor;

    // Find the monitor
    for(iMonitor = 0; (iMonitor < ARRAYSIZE(m_rgMonitors)) &&
            (hwnd != m_rgMonitors[iMonitor].hwnd); iMonitor++);
    if(iMonitor >= ARRAYSIZE(m_rgMonitors))
        {
        // Couldn't find the monitor.
        hr = E_FAIL;
        goto Error;
        }
        
    ZeroMemory(m_rgMonitors + iMonitor, sizeof(*m_rgMonitors));

Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::Convert(
    const TCHAR* pszTLAIn,
    double curIn,
    const TCHAR* pszTLAOut,
    double* pcurOut
    )
{
    HRESULT hr = S_OK;
    double dRateIn;
    double dRateOut;

    if(NULL == pcurOut) // very light parameter checking...
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    if(FAILED(hr = GetRate(pszTLAIn, &dRateIn)) || FAILED(hr = GetRate(pszTLAOut, &dRateOut)))
        {
        goto Error;
        }

    *pcurOut = (curIn / dRateIn) * dRateOut;

Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetVisibleRateCount(
    int* pcRates
    )
{
    return(GetLookupInfo(pcRates, NULL));
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetRateInfoByIndex(
    DWORD dwFlags,
    int iRate,
    EMRateInfo** ppemri
    )
{
    HRESULT hr = S_OK;
    HANDLE hdb;

    if(FAILED(hr = GetDatabase(&hdb, NULL)))
        {
        goto Error;
        }

    // Seek the database to the correct record
    if(dwFlags & GRIBI_ALL_RATES)
        {
        if(0 == CeSeekDatabase(hdb, CEDB_SEEK_BEGINNING, (DWORD)iRate, NULL))
            {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }
        }
    else if(dwFlags & GRIBI_VISIBLE_RATES)
        {
        int cVisible;
        CEOID* rgVisible;
        
        if(FAILED(hr = GetLookupInfo(&cVisible, &rgVisible)))
            {
            goto Error;
            }

        if(iRate >= cVisible)
            {
            hr = E_FAIL;
            goto Error;
            }
        if(rgVisible[iRate] != CeSeekDatabase(hdb, CEDB_SEEK_CEOID, (DWORD)rgVisible[iRate], NULL))
            {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }
        }
    else
        {
        // Needed to specify a flag.
        ASSERT(FALSE);
        hr = E_INVALIDARG;
        goto Error;
        }

    // Get the rate info
    if(FAILED(hr = CreateRateInfoFromCurrentPosition(hdb, ppemri)))
        {
        goto Error;
        }

Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetRateInfoByTLA(
    const TCHAR* pszTLA,
    EMRateInfo** ppemri
    )
{
    HRESULT hr = S_OK;
    HANDLE hdb;

    if(FAILED(hr = GetSeekedDatabase(0, pszTLA, &hdb, NULL)))
        {
        goto Error;
        }

    if(FAILED(hr = CreateRateInfoFromCurrentPosition(hdb, ppemri)))
        {
        goto Error;
        }
Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::SetRateInfoByTLA(
    const TCHAR* pszTLA,
    const EMRateInfo* pemri
    )
{
    HRESULT hr = S_OK;
    HANDLE hdb;
    int cValsSet;
    CEPROPVAL vals[4];
    CEOID oid;

    if((NULL == pszTLA) || (3 != _tcslen(pszTLA)) || (NULL == pemri))
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    if(FAILED(hr = GetSeekedDatabase(GSDF_CREATE_NEW, pszTLA, &hdb, &oid)))
        {
        goto Error;
        }

    ZeroMemory(&vals, sizeof(vals));

    if(pemri->dwValid & EMRIV_TLA)
        {
        // Just validate it, don't set it.
        if((NULL == pemri->pszTLA) || (0 != _tcsicmp(pemri->pszTLA, pszTLA)))
            {
            hr = E_INVALIDARG;
            goto Error;
            }
        }
    
    cValsSet = 0;
    if(pemri->dwValid & EMRIV_FULLNAME)
        {
        vals[cValsSet].propid = CPR_FULLNAME;
        vals[cValsSet].val.lpwstr= pemri->pszFullName;
        cValsSet++;
        }

    if(pemri->dwValid & EMRIV_RATE)
        {
        vals[cValsSet].propid = CPR_RATE;
        vals[cValsSet].val.dblVal= pemri->rate;
        cValsSet++;
        }

    if(pemri->dwValid & EMRIV_UPDATE_TIME)
        {
        vals[cValsSet].propid = CPR_UPDATE_TIME;
        vals[cValsSet].val.filetime= pemri->ftLastUpdate;
        cValsSet++;
        }

    if(pemri->dwValid & EMRIV_VISIBLE)
        {
        vals[cValsSet].propid = CPR_VISIBLE;
        vals[cValsSet].val.boolVal= pemri->fVisible;
        cValsSet++;
        }


    ASSERT(cValsSet <= ARRAYSIZE(vals));

    if(oid != CeWriteRecordProps(hdb, oid, cValsSet, vals))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    ResetLookup();
    
Error:
    return(hr);

}

/*****************************************************************************

 ****************************************************************************/
BOOL IsReasonableTLA(
    const TCHAR* pszTLA
    )
{
    return(
        (NULL != pszTLA) &&
        (3 == _tcslen(pszTLA)) &&
        _istupper(pszTLA[0]) &&
        _istupper(pszTLA[1]) &&
        _istupper(pszTLA[2])
        );
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::ResetRateByTLA(
    const TCHAR* pszTLA
    )
{
    HRESULT hr = S_OK;
    const RateDefaultInfo* prdi;
    EMRateInfo emri;
    TCHAR szFullName[100];
    
    if(!IsReasonableTLA(pszTLA))
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    // Find the defaults for this currency
    for(prdi = g_rgri; (NULL != prdi->pszTLA) && (0 != _tcsicmp(prdi->pszTLA, pszTLA)); prdi++);
    if(NULL == prdi->pszTLA)
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    ZeroMemory(&emri, sizeof(emri));

    if(0 == LoadString(g_hInstRes, prdi->ids, szFullName, ARRAYSIZE(szFullName)))
        {
        szFullName[0] = 0;
        }
    if(FAILED(hr = GetFileTimeForDate(CUR_UPD_YEAR, CUR_UPD_MONTH, CUR_UPD_DAY,
            &(emri.ftLastUpdate))))
        {
        goto Error;
        }
    emri.fVisible = TRUE;
    emri.pszFullName = szFullName;
    emri.rate = prdi->dRate;
    emri.dwValid = EMRIV_FULLNAME | EMRIV_RATE | EMRIV_UPDATE_TIME | EMRIV_VISIBLE;

    if(FAILED(hr = SetRateInfoByTLA(pszTLA, &emri)))
        {
        goto Error;
        }

Error:
    return(hr);
}


/*****************************************************************************

 ****************************************************************************/
HRESULT PackTLA(
    const TCHAR* pszTLA,
    DWORD* pdwPacked
    )
{
    HRESULT hr = S_OK;
    int ich;

    if(!IsReasonableTLA(pszTLA))
        {
        hr = E_INVALIDARG;
        goto Error;
        }
    *pdwPacked = 0;
    for(ich = 0; ich < 3; ich++)
        {
        *pdwPacked = (*pdwPacked << 8) | ((pszTLA[ich] - TEXT('A')) & 0xFF);
        }
Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT UnPackTLA(
    DWORD dwPacked,
    TCHAR* pszTLA,
    int cchOut
    )
{
    HRESULT hr = S_OK;
    int ich;

    if((NULL == pszTLA) || (cchOut < 4))
        {
        hr = E_INVALIDARG;
        goto Error;
        }
    for(ich = 2; ich >= 0; ich--, dwPacked >>= 8)
        {
        pszTLA[ich] = (TCHAR)((dwPacked & 0xFF) + TEXT('A'));
        if(!_istupper(pszTLA[ich]))
            {
            hr = E_INVALIDARG;
            goto Error;
            }
        }
    pszTLA[3] = 0;

Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::FillControlWithCurrencies(
    DWORD dwFlags, // in - flags
    HWND hwndControl, // in - hwnd of the control we are filling
    HINSTANCE hInst, // in - resource instance containing idsFormat
    UINT idsFormat, // in - string containing format of text in list
    const TCHAR* pszTLADefault // in - TLA of currency to default the selection to.  May be NULL
    )
{
    HRESULT hr = S_OK;
    TCHAR szClass[20];
    EMRateInfo* pri = NULL;
    BOOL fAllRates;

    if(!(dwFlags & FCWCF_ALL_RATES) == !(dwFlags & FCWCF_VISIBLE_RATES))
        {
        // Need to specify one flag or the other.
        hr = E_INVALIDARG;
        goto Error;
        }
    fAllRates = (dwFlags & FCWCF_ALL_RATES);

    if(0 == GetClassName(hwndControl, szClass, ARRAYSIZE(szClass)))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }
   
    if(0 == _tcsicmp(TEXT("combobox"), szClass))
        {
        int iRate;
        TCHAR szFormat[40];
        TCHAR szUIString[200];
        RECT rcControl;

        if(0 == LoadString(hInst, idsFormat, szFormat, ARRAYSIZE(szFormat)))
            {
            // Something wrong with the resources?
            ASSERT(FALSE);
            hr = E_FAIL;
            goto Error;
            }

        SendMessage(hwndControl, CB_RESETCONTENT, 0, 0);

        // Make the dropped width twice the width of the control.
        // Note that this makes this function a little less general
        // purpose.
        if(!GetClientRect(hwndControl, &rcControl))
            {
            // Something wrong with the control?
            ASSERT(FALSE);
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Error;
            }
        if(CB_ERR == SendMessage(hwndControl, CB_SETDROPPEDWIDTH, (WPARAM)((rcControl.right - rcControl.left) * 2), 0))
            {
            // Something wrong with the control?
            ASSERT(FALSE);
            hr = E_FAIL;
            goto Error;
            }

        iRate = 0;
        while(SUCCEEDED(GetRateInfoByIndex(fAllRates? GRIBI_ALL_RATES : GRIBI_VISIBLE_RATES, iRate, &pri)))
            {
            DWORD dwTLA;
            LRESULT iItem;

            if((pri->dwValid & (EMRIV_TLA | EMRIV_RATE)) != (EMRIV_TLA | EMRIV_RATE))
                {
                // These fields should always be valid...
                ASSERT(FALSE);
                hr = E_FAIL;
                goto Error;
                }

            if(FAILED(hr = PackTLA(pri->pszTLA, &dwTLA)))
                {
                // Corrupt data in the database?
                ASSERT(FALSE);
                goto Error;
                }

            if(0 == FormatMessageHelp(szUIString, ARRAYSIZE(szUIString), szFormat, pri->pszTLA,
                    (pri->dwValid & EMRIV_FULLNAME) ? pri->pszFullName : TEXT("")))
                {
                hr = E_FAIL;
                goto Error;
                }

            iItem = SendMessage(hwndControl, CB_INSERTSTRING, (WPARAM)(int)-1, (LPARAM)szUIString);
            if((CB_ERR == iItem) || (CB_ERRSPACE == iItem))
                {
                hr = E_OUTOFMEMORY; // maybe not true for CB_ERR...
                goto Error;
                }

            if(CB_ERR == SendMessage(hwndControl, CB_SETITEMDATA, (WPARAM)iItem, (LPARAM)dwTLA))
                {
                hr = E_FAIL;
                goto Error;
                }

            if((0 == iItem) || ((NULL != pszTLADefault) && (0 == _tcsicmp(pszTLADefault, pri->pszTLA))))
                {
                // Either we just inserted the first item in the list
                // or we inserted the currency that the caller wants
                // to be the default.
                SendMessage(hwndControl, CB_SETCURSEL, (WPARAM)iItem, 0);
                }
            VERIFY(NULL == LocalFree(pri));
            pri = NULL;
            iRate++;
            }
        }
    else if(0 == _tcsicmp(TEXT("listbox"), szClass))
        {
        int iRate;
        TCHAR szFormat[40];
        TCHAR szUIString[200];

        if(0 == LoadString(hInst, idsFormat, szFormat, ARRAYSIZE(szFormat)))
            {
            // Something wrong with the resources?
            ASSERT(FALSE);
            hr = E_FAIL;
            goto Error;
            }

        SendMessage(hwndControl, LB_RESETCONTENT, 0, 0);

        iRate = 0;
        while(SUCCEEDED(GetRateInfoByIndex(fAllRates? GRIBI_ALL_RATES : GRIBI_VISIBLE_RATES, iRate, &pri)))
            {
            DWORD dwTLA;
            LRESULT iItem;

            if((pri->dwValid & (EMRIV_TLA | EMRIV_RATE)) != (EMRIV_TLA | EMRIV_RATE))
                {
                // These fields should always be valid...
                ASSERT(FALSE);
                hr = E_FAIL;
                goto Error;
                }

            if(FAILED(hr = PackTLA(pri->pszTLA, &dwTLA)))
                {
                // Corrupt data in the database?
                ASSERT(FALSE);
                goto Error;
                }

            if(0 == FormatMessageHelp(szUIString, ARRAYSIZE(szUIString), szFormat, pri->pszTLA,
                    (pri->dwValid & EMRIV_FULLNAME) ? pri->pszFullName : TEXT("")))
                {
                hr = E_FAIL;
                goto Error;
                }

            iItem = SendMessage(hwndControl, LB_INSERTSTRING, (WPARAM)(int)-1, (LPARAM)szUIString);
            if((LB_ERR == iItem) || (LB_ERRSPACE == iItem))
                {
                hr = E_OUTOFMEMORY; // maybe not true for LB_ERR...
                goto Error;
                }

            if(LB_ERR == SendMessage(hwndControl, LB_SETITEMDATA, (WPARAM)iItem, (LPARAM)dwTLA))
                {
                hr = E_FAIL;
                goto Error;
                }

            if((0 == iItem) || ((NULL != pszTLADefault) && (0 == _tcsicmp(pszTLADefault, pri->pszTLA))))
                {
                // Either we just inserted the first item in the list
                // or we inserted the currency that the caller wants
                // to be the default.
                SendMessage(hwndControl, LB_SETCURSEL, (WPARAM)iItem, 0);
                }
            VERIFY(NULL == LocalFree(pri));
            pri = NULL;
            iRate++;
            }

        }
    else
        {
        hr = E_INVALIDARG;
        goto Error;
        }

Error:
    VERIFY(NULL == LocalFree(pri));
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT ExchangeRateManager::GetSelectedCurrency(
    HWND hwndControl, // in - hwnd of the control.  The control needed to be initialized with FillControlWithCurrencies
    TCHAR* pszTLAOut, // out - buffer where we will put the TLA of the selected currency
    int cchBuff // in - size in characters of the buffer.
    )
{
    HRESULT hr = S_OK;
    TCHAR szClass[20];

    if(!pszTLAOut || (cchBuff < c_TLABufferSize))
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    if(0 == GetClassName(hwndControl, szClass, ARRAYSIZE(szClass)))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    if(0 == _tcsicmp(TEXT("combobox"), szClass))
        {
        LRESULT iItem;
        DWORD dwTLA;

        iItem = SendMessage(hwndControl, CB_GETCURSEL, 0, 0);
        if(CB_ERR == iItem)
            {
            hr = E_FAIL;
            goto Error;
            }

        dwTLA = SendMessage(hwndControl, CB_GETITEMDATA, (WPARAM)iItem, (LPARAM)0);
        if(CB_ERR == dwTLA)
            {
            hr = E_FAIL;
            goto Error;
            }

        if(FAILED(hr = UnPackTLA(dwTLA, pszTLAOut, cchBuff)))
            {
            goto Error;
            }
        }
    else if(0 == _tcsicmp(TEXT("listbox"), szClass))
        {
        LRESULT iItem;
        DWORD dwTLA;

        iItem = SendMessage(hwndControl, LB_GETCURSEL, 0, 0);
        if(LB_ERR == iItem)
            {
            hr = E_FAIL;
            goto Error;
            }

        dwTLA = SendMessage(hwndControl, LB_GETITEMDATA, (WPARAM)iItem, (LPARAM)0);
        if(LB_ERR == dwTLA)
            {
            hr = E_FAIL;
            goto Error;
            }

        if(FAILED(hr = UnPackTLA(dwTLA, pszTLAOut, cchBuff)))
            {
            goto Error;
            }
        
        }
    else
        {
        hr = E_INVALIDARG;
        goto Error;
        }

Error:
    return(hr);
}

