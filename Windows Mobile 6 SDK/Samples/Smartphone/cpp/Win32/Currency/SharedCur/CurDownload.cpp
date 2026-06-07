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
#include "CurDownload.h"
#include "URLMon.h"


class RateDownloader :
    public IRateDownloader,
    public IBindStatusCallback
{
    LONG   m_cRef; // COM refcount

    HWND m_hwndMonitor;
    UINT m_msgProgress;
    UINT m_msgFinished;

    HRESULT m_hrBindResult;
    BOOL m_fAborted;

    static DWORD WINAPI RateDownloadThreadProc(void* param);

    RateDownloader();
    virtual ~RateDownloader();

    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj) {UNREFERENCED_PARAMETER(riid);UNREFERENCED_PARAMETER(ppvObj); return(E_NOTIMPL); }
    STDMETHODIMP_(ULONG) AddRef() { InterlockedIncrement(&m_cRef); return m_cRef; }
    STDMETHODIMP_(ULONG) Release() {InterlockedDecrement(&m_cRef); if(0 == m_cRef){delete this; return(0);} return(m_cRef);}

    // IRateDownloader
    STDMETHODIMP DownloadRates(HWND hwndMonitor, UINT msgProgress, UINT msgFinished);
    STDMETHODIMP Abort();

    // IBindStatusCallback
    STDMETHODIMP OnStartBinding(DWORD dwReserved, IBinding* pib);
    STDMETHODIMP GetPriority(LONG* pnPriority);
    STDMETHODIMP OnLowResource(DWORD reserved);
    STDMETHODIMP OnProgress(ULONG ulProgress,ULONG ulProgressMax,ULONG ulStatusCode,LPCWSTR szStatusText);
    STDMETHODIMP OnStopBinding(HRESULT hresult,LPCWSTR szError);
    STDMETHODIMP GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo);
    STDMETHODIMP OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed);
    STDMETHODIMP OnObjectAvailable(REFIID riid, IUnknown* punk);

    friend HRESULT CreateRateDownloader(IRateDownloader** pprd);
};

// Place where we get the rates from.
// A real app would let you set this in the UI
static const TCHAR* g_szRateInfoURL = TEXT("http://www.contactor.se/~dast/currency/rates.cgi");

/****************************************************************************

 ****************************************************************************/
HRESULT GetTLA(
    const TCHAR** ppszText, // in/out - the text line we are parsing
    TCHAR pszTLA[c_TLABufferSize] // out - the TLA we got from the text
    )
{
    HRESULT hr = S_OK;
    int ich;

    for(ich = 0; ich < c_TLACharacters; ich++)
        {
        if((0 != (*ppszText)[ich]) && !_istupper((*ppszText)[ich]))
            {
            hr = E_FAIL;
            goto Error;
            }
        }

    _tcsncpy(pszTLA, *ppszText, c_TLACharacters);
    pszTLA[c_TLACharacters] = 0;
    *ppszText += c_TLACharacters;
    
Error:
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT EatWhite(const TCHAR** ppszText)
{
    HRESULT hr = S_OK;

    if(!_istspace((*ppszText)[0]))
        {
        hr = E_FAIL;
        goto Error;
        }
    while(_istspace((*ppszText)[0]))
        {
        *ppszText += 1;
        }

Error:
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT EatString(
    const TCHAR** ppszText,
    const TCHAR* pszString // in - string to eat
    )
{
    HRESULT hr = S_OK;

    if(0 != _tcsncmp(*ppszText, pszString, _tcslen(pszString)))
        {
        hr = E_FAIL;
        goto Error;
        }

    *ppszText += _tcslen(pszString);
    
Error:
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT ParseDouble(
    const TCHAR** ppszText,
    double* pd
    )
{
    HRESULT hr = S_OK;

    if(!(_istdigit((*ppszText)[0]) || (TEXT('.') == (*ppszText)[0])))
        {
        hr = E_FAIL;
        goto Error;
        }

    *pd = _tcstod(*ppszText, const_cast<TCHAR**>(ppszText));

Error:
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT ParseExpression( // Parse a trivialy simple expression that is.  Either a number or (1/double) expression
    const TCHAR** ppszText,
    double* pd
    )
{
    HRESULT hr = S_OK;

    if(_istdigit((*ppszText)[0]))
        {
        // Assume this is just a double
        if(FAILED(hr = ParseDouble(ppszText, pd)))
            {
            goto Error;
            }
        }
    else if(SUCCEEDED(EatString(ppszText, TEXT("(1/"))))
        {
        if(FAILED(hr = ParseDouble(ppszText, pd)))
            {
            goto Error;
            }
        *pd = 1.0 / *pd;
        if(FAILED(hr = EatString(ppszText, TEXT(")"))))
            {
            goto Error;
            }
        }
Error:
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT ParseDate(
    const TCHAR** ppszText,
    FILETIME* pft
    )
{
    HRESULT hr = S_OK;
    TCHAR szTemp[10];
    SYSTEMTIME st;
    int ich;
    const int c_cchYear = 4;
    const int c_cchMonth = 2;
    const int c_cchDay = 2;
    const int c_cchDate = c_cchYear + c_cchMonth + c_cchDay;

    if(TEXT(':') != (*ppszText)[0])
        {
        hr = E_FAIL;
        goto Error;
        }

    for(ich = 1; ich < c_cchDate + 1; ich++)
        {
        if(!_istdigit((*ppszText)[ich]))
            {
            hr = E_FAIL;
            goto Error;
            }
        }

    *ppszText += 1;

    ZeroMemory(&st, sizeof(st));

    _tcsncpy(szTemp, *ppszText, c_cchYear);
    szTemp[c_cchYear] = 0;
    st.wYear = (USHORT) _ttol(szTemp);
    *ppszText += c_cchYear;

    _tcsncpy(szTemp, *ppszText, c_cchMonth);
    szTemp[c_cchMonth] = 0;
    st.wMonth = (USHORT) _ttol(szTemp);
    *ppszText += c_cchMonth;

    _tcsncpy(szTemp, *ppszText, c_cchDay);
    szTemp[c_cchDay] = 0;
    st.wDay = (USHORT) _ttol(szTemp);
    *ppszText += c_cchDay;

    if(!SystemTimeToFileTime(&st, pft))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

Error:
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT ParseLine(
    ExchangeRateManager* prm,
    const TCHAR* pszLine
    )
{
    HRESULT hr = S_OK;
    TCHAR szTLA[c_TLABufferSize];
    double dRate;
    FILETIME ftUpdate;

    if(
        SUCCEEDED(GetTLA(&pszLine, szTLA)) &&
        SUCCEEDED(EatWhite(&pszLine)) &&
        SUCCEEDED(ParseExpression(&pszLine, &dRate)) &&
        SUCCEEDED(EatWhite(&pszLine)) &&
        SUCCEEDED(ParseDate(&pszLine, &ftUpdate)))
        {
        EMRateInfo ri;

        ZeroMemory(&ri, sizeof(ri));
        ri.dwValid = EMRIV_TLA | EMRIV_RATE | EMRIV_UPDATE_TIME;
        ri.pszTLA = szTLA;
        ri.rate = dRate;
        ri.ftLastUpdate = ftUpdate;
        if(FAILED(hr = prm->SetRateInfoByTLA(szTLA, &ri)))
            {
            goto Error;
            }
        }

Error:
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT ParseRateFile(const TCHAR* pszFile)
{
    HRESULT hr = S_OK;
    FILE* pFile = NULL;
    TCHAR szBuffer[1000];
    ExchangeRateManager erm;

    pFile = _tfopen(pszFile, TEXT("r"));
    if(NULL == pFile)
        {
        hr = E_FAIL;
        goto Error;
        }

    while(NULL != _fgetts(szBuffer, ARRAYSIZE(szBuffer), pFile))
        {
        ParseLine(&erm, szBuffer);
        }

Error:
    if(NULL != pFile)
        {
        fclose(pFile);
        }
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
/* static */ DWORD WINAPI RateDownloader::RateDownloadThreadProc(void* param)
{
    HRESULT hr = S_OK;
    RateDownloader* pThis = (RateDownloader*)param;
    TCHAR szCacheFile[MAX_PATH];

    pThis->m_hrBindResult = S_OK;
    
    if(FAILED(hr = URLDownloadToCacheFile(NULL, g_szRateInfoURL,
            szCacheFile, ARRAYSIZE(szCacheFile), 0,
            (IBindStatusCallback*) pThis)))
        {
        if(FAILED(pThis->m_hrBindResult))
            {
            hr = pThis->m_hrBindResult;
            }
        goto Error;
        }

    if(FAILED(hr = ParseRateFile(szCacheFile)))
        {
        goto Error;
        }


Error:
    PostMessage(pThis->m_hwndMonitor, pThis->m_msgFinished, 0, hr);
    pThis->Release(); // release the ref added before the thread was created
    return((DWORD)hr);
}


/****************************************************************************

 ****************************************************************************/
RateDownloader::RateDownloader()
{
    m_cRef = 1;
}

/****************************************************************************

 ****************************************************************************/
RateDownloader::~RateDownloader()
{
    ASSERT(0 == m_cRef);
}

/****************************************************************************

 ****************************************************************************/
HRESULT RateDownloader::DownloadRates(
    HWND hwndMonitor, // in - hwnd to send progerss mesages to
    UINT msgProgress, // in - message to send when there is a progress update
    UINT msgFinished  // in - message to send when we are finished downloading
    )
{
    HRESULT hr = S_OK;
    HANDLE hThread = NULL;

    if(!IsWindow(hwndMonitor) || (msgProgress < WM_USER) || (msgFinished < WM_USER))
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    m_hwndMonitor = hwndMonitor;
    m_msgProgress = msgProgress;
    m_msgFinished = msgFinished;

    m_fAborted = FALSE;

    AddRef(); // Add a ref for the thread.
    hThread = CreateThread(NULL, 0, RateDownloadThreadProc, this, 0, NULL);
    if(NULL == hThread)
        {
        Release(); // The thread never ran so release the ref.  Note that an event should really be used to determine if the thread successfuly started and will release the ref.
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

Error:
    if(hThread)
        {
        VERIFY(CloseHandle(hThread));
        }
    return(hr);
}

/****************************************************************************

 ****************************************************************************/
HRESULT RateDownloader::Abort()
{
    HRESULT hr = S_OK;

    m_fAborted = TRUE;

//Error:
    return(hr);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::OnStartBinding(DWORD dwReserved, IBinding* pib)
{
    m_hrBindResult = S_OK;
    return(S_OK);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::GetPriority(LONG* pnPriority)
{
    return(E_NOTIMPL);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::OnLowResource(DWORD reserved)
{
    return(E_NOTIMPL);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::OnProgress(ULONG ulProgress,ULONG ulProgressMax,ULONG ulStatusCode,LPCWSTR szStatusText)
{
    HRESULT hr = S_OK;

    PostMessage(m_hwndMonitor, m_msgProgress, (WPARAM)ulProgress, (LPARAM)ulProgressMax);

//Error:
    return(m_fAborted ? E_ABORT : hr);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::OnStopBinding(HRESULT hresult,LPCWSTR szError)
{
    m_hrBindResult = hresult;
    return(S_OK);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo)
{
    return(E_NOTIMPL);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed)
{
    return(E_NOTIMPL);
}

/****************************************************************************
    IBindStatusCallback method
 ****************************************************************************/
STDMETHODIMP RateDownloader::OnObjectAvailable(REFIID riid, IUnknown* punk)
{
    return(E_NOTIMPL);
}

/*****************************************************************************
    External function to create a RateDownloader accessor.
    
    Author(s): 
 *****************************************************************************/
HRESULT CreateRateDownloader(
    IRateDownloader** pprd // out - the new RateDownloader access object
    )
{
    HRESULT hr = S_OK;

    if(NULL == pprd)
        {
        hr = E_INVALIDARG;
        goto Error;
        }

    *pprd = new RateDownloader();
    ASSERT((!*pprd) || (1 == ((RateDownloader*)*pprd)->m_cRef));
    if(NULL == *pprd)
        {
        hr = E_OUTOFMEMORY;
        goto Error;
        }

Error:
    return(hr);

}


