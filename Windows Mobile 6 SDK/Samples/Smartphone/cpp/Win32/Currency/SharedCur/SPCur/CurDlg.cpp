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

#include "..\stdafx.h"
#include "..\helpers.h"
#include "..\ExMan.h"
#include <tpcshell.h>
#include <winuserm.h>
#include "resource.h"
#include "CurDlg.h"
#include "EditDlg.h"
#include "..\CurDownload.h"

static ExchangeRateManager* g_perm = NULL;

extern HWND g_hDlgActive;

#define CDM_RATES_CHANGED (WM_APP + 1)
#define CDM_UPDATING (WM_APP + 2)
#define CDM_DONE (WM_APP + 3)

/*****************************************************************************

 ****************************************************************************/
HRESULT OnRatesChanged(
    HWND hDlg
    )
{
    HRESULT hr = S_OK;

    if(FAILED(hr = g_perm->FillControlWithCurrencies(FCWCF_VISIBLE_RATES,
            GetDlgItem(hDlg, IDC_LIST_SOURCE), g_hInstRes,
            IDS_DROPDOWN_FORMAT, TEXT("USD"))))
        {
        goto Error;
        }

    if(FAILED(hr = g_perm->FillControlWithCurrencies(FCWCF_VISIBLE_RATES,
            GetDlgItem(hDlg, IDC_LIST_DEST), g_hInstRes,
            IDS_DROPDOWN_FORMAT, TEXT("EUR"))))
        {
        goto Error;
        }

Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
static BOOL OnInitDialog(
    HWND hDlg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    HRESULT hr = S_OK;
    SHINITDLGINFO shidi;
    SHMENUBARINFO mbi;

    ASSERT(NULL == g_perm);
    g_perm = new ExchangeRateManager;
    if(NULL == g_perm)
        {
        hr = E_OUTOFMEMORY;
        goto Error;
        }

    if(FAILED(hr = g_perm->AddRateChangeMonitor(hDlg, CDM_RATES_CHANGED)))
        {
        goto Error;
        }

    // Get the dialog box the right size.
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
    shidi.hDlg = hDlg;
    if(!SHInitDialog(&shidi))
        {
        hr = E_FAIL;
        goto Error;
        }

    // Create our MenuBar
    ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
    mbi.cbSize = sizeof(mbi);
    mbi.hwndParent = hDlg;
    mbi.nToolBarId = IDM_SP_CURRENCY_CONVERTER;
    mbi.hInstRes = g_hInstRes;

    if(!SHCreateMenuBar(&mbi))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    // Override the BACK key so we can send it to the edit control
    SendMessage(mbi.hwndMB, SHCMBM_OVERRIDEKEY, VK_TBACK, MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

    // Put the edit control in numeric mode
    if(!SendDlgItemMessage(hDlg, IDC_EDIT_SOURCE, EM_SETINPUTMODE, 0, EIM_NUMBERS))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    // Make the * key put a . in the edit control
    if(FAILED(hr = SubclassEditForKeyTranslation(GetDlgItem(hDlg, IDC_EDIT_SOURCE))))
        {
        goto Error;
        }

    // Initialize the drop downs
    if(FAILED(hr = OnRatesChanged(hDlg)))
        {
        goto Error;
        }

    SetFocus(GetDlgItem(hDlg, IDC_EDIT_SOURCE));

Exit:
    return(FALSE); // we set the focus
Error:
    DestroyWindow(hDlg);
    goto Exit;
}

/*****************************************************************************

 ****************************************************************************/
void OnConvert(
    HWND hDlg
    )
{
    HRESULT hr = S_OK;
    double dIn;
    double dOut;
    TCHAR szAmount[50];
    TCHAR szTLAIn[c_TLABufferSize];
    TCHAR szTLAOut[c_TLABufferSize];

    if(0 == GetDlgItemText(hDlg, IDC_EDIT_SOURCE, szAmount, ARRAYSIZE(szAmount) - 1))
        {
        hr = E_FAIL;
        goto Error;
        }

    // A good app would do a lot more validation here
    dIn = _tcstod(szAmount, NULL);

    if(FAILED(hr = g_perm->GetSelectedCurrency(GetDlgItem(hDlg, IDC_LIST_SOURCE), szTLAIn, ARRAYSIZE(szTLAIn))))
        {
        goto Error;
        }

    if(FAILED(hr = g_perm->GetSelectedCurrency(GetDlgItem(hDlg, IDC_LIST_DEST), szTLAOut, ARRAYSIZE(szTLAOut))))
        {
        goto Error;
        }

    if(FAILED(hr = g_perm->Convert(szTLAIn, dIn, szTLAOut, &dOut)))
        {
        goto Error;
        }

    wsprintf(szAmount, TEXT("%f"), dOut);
    SetDlgItemText(hDlg, IDC_EDIT_DEST, szAmount);

    // Select the text in the source edit control
    // so that the next keypress automatically replaces
    // it.
    SetFocus(GetDlgItem(hDlg, IDC_EDIT_SOURCE));
    SendDlgItemMessage(hDlg, IDC_EDIT_SOURCE, EM_SETSEL, 0, -1);

Error:
    if(FAILED(hr))
        {
        DisplayError(hDlg, g_hInstRes, IDS_ERROR_CAPTION, IDS_ERROR_UNABLETOCONVERT, hr);
        }
}

/*****************************************************************************

 ****************************************************************************/
HRESULT OnDownloadRates(
    HWND hDlg
    )
{
    HRESULT hr = S_OK;
    IRateDownloader* prd = NULL;

    if(FAILED(hr = CreateRateDownloader(&prd)))
        {
        goto Error;
        }

    if(FAILED(hr = prd->DownloadRates(hDlg, CDM_UPDATING, CDM_DONE)))
        {
        goto Error;
        }

Error:
    if(NULL != prd)
        {
        prd->Release();
        }
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
LRESULT CALLBACK CurrencyDialogProc(
    HWND hDlg,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
    )
{
    BOOL bRet = TRUE;
    
    switch (message)
        {
        case WM_INITDIALOG:
            bRet = OnInitDialog(hDlg, wParam, lParam);
            break;

        case WM_COMMAND:
            {
            UINT idc;
            
            idc = LOWORD(wParam);
            switch(idc)
                {
                case IDM_QUIT:
                    DestroyWindow(hDlg);
                    break;

                case IDC_BUTTON_CONVERT:
                    OnConvert(hDlg);
                    break;

                case IDM_CHANGE_RATES:
                    DoCurrencyEditorDialog(hDlg, g_perm);
                    OnRatesChanged(hDlg); // we could be smarter about only calling this if needed
                    break;

                case IDM_DOWNLOAD:
                    OnDownloadRates(hDlg);
                    break;

                default:
                    bRet = FALSE;
                    break;
                }
            }
            break;

        case WM_DESTROY:
            if(g_perm)
                {
                // Not really needed since we're about to delete g_perm...
                VERIFY(SUCCEEDED(g_perm->RemoveRateChangeMonitor(hDlg)));
                }
            delete(g_perm);
            g_perm = NULL;
            g_hDlgActive = NULL;
			PostMessage(GetParent(hDlg), WM_CLOSE, 0, 0); // We are the main dialog so if we go away, the app should quit.
            break;

        case CDM_RATES_CHANGED:
            OnRatesChanged(hDlg);
            break;

        case CDM_UPDATING:
            {
            TCHAR szFormat[100];
            TCHAR szMessage[100];

            if(0 != LoadString(g_hInstRes, IDS_DOWNLOADING, szFormat, ARRAYSIZE(szFormat)))
                {
                if(0 != FormatMessageHelp(szMessage, ARRAYSIZE(szMessage), szFormat, (int) (((double)wParam / (double)lParam) * 100.0)))
                    {
                    SetDlgItemText(hDlg, IDC_DOWNLOAD_STATUS, szMessage);
                    }
                }    
            }
            break;
        
        case CDM_DONE:
            if(FAILED((HRESULT)lParam))
                {
                DisplayError(hDlg, g_hInstRes, IDS_ERROR_CAPTION, IDS_DOWNLOAD_FAILED, (HRESULT)lParam);
                }
            SetDlgItemText(hDlg, IDC_DOWNLOAD_STATUS, TEXT(""));
            break;

        case WM_HOTKEY:
            // BACK key will come to us this way since we requested it in WM_INITDIALOG
            if(VK_TBACK == HIWORD(lParam))
                {
                SHSendBackToFocusWindow(message, wParam, lParam);
                }
            break;

        default:
            bRet = FALSE;
            break;
        }
    return bRet;
}


/*****************************************************************************

 ****************************************************************************/
HRESULT StartupCurrencyConverterDialog(HWND hWndOwner)
{
    HRESULT hr = S_OK;

    g_hDlgActive = CreateDialog(g_hInstRes, MAKEINTRESOURCE(IDD_CONVERTER), hWndOwner, (DLGPROC)CurrencyDialogProc); 
    if(NULL == g_hDlgActive)
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    ShowWindow(g_hDlgActive, SW_SHOW);
    UpdateWindow(g_hDlgActive);

Exit:
    return(hr);
Error:
    DisplayError(hWndOwner, g_hInstRes, IDS_ERROR_CAPTION, IDS_ERROR_UNABLETOBRINGUPDIALOG, hr);
    goto Exit;
}


