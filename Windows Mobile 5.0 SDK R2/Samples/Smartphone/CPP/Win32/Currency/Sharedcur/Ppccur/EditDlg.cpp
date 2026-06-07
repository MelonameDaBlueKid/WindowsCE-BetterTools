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


#include "..\stdafx.h"
#include "..\helpers.h"
#include "..\ExMan.h"
#include "resource.h"

/*****************************************************************************

 ****************************************************************************/
HRESULT GetRateManagerAndSelectedCurrency(
    HWND hDlg,
    ExchangeRateManager** pperm,
    TCHAR* pszTLA
    )
{
    HRESULT hr = S_OK;
    ExchangeRateManager* perm;
    TCHAR szTLA[c_TLABufferSize];

    perm = (ExchangeRateManager*)GetWindowLong(hDlg, DWL_USER);
    if(NULL == perm)
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }
    
    if(FAILED(hr = perm->GetSelectedCurrency(GetDlgItem(hDlg, IDC_CURRENTY_LIST),
            szTLA, ARRAYSIZE(szTLA))))
        {
        goto Error;
        }

    if(pperm)
        {
        *pperm = perm;
        }
    if(pszTLA)
        {
        _tcscpy(pszTLA, szTLA);
        }
        
Error:
    return(hr);
}

/*****************************************************************************

 ****************************************************************************/
HRESULT OnSelectedCurrencyChanged(
    HWND hDlg
    )
{
    HRESULT hr = S_OK;
    ExchangeRateManager* perm;
    TCHAR szTLA[c_TLABufferSize];
    EMRateInfo* pemri = NULL;
    const DWORD c_dwRequired = EMRIV_TLA | EMRIV_RATE | EMRIV_VISIBLE;
    TCHAR szRate[40];

    if(FAILED(hr = GetRateManagerAndSelectedCurrency(hDlg, &perm, szTLA)))
        {
        goto Error;
        }

    if(FAILED(hr = perm->GetRateInfoByTLA(szTLA, &pemri)))
        {
        goto Error;
        }

    if((pemri->dwValid & c_dwRequired) != c_dwRequired)
        {
        ASSERT(FALSE); // likely corrupt database
        hr = E_FAIL;
        goto Error;
        }

    SendDlgItemMessage(hDlg, IDC_VISIBLE, BM_SETCHECK, pemri->fVisible, 0);
    wsprintf(szRate, TEXT("%f"), pemri->rate);
    SetDlgItemText(hDlg, IDC_CURRENT_RATE, szRate);
    SetDlgItemText(hDlg, IDC_NEW_RATE, szRate);
    SetFocus(GetDlgItem(hDlg, IDC_NEW_RATE));
    SendDlgItemMessage(hDlg, IDC_NEW_RATE, EM_SETSEL, 0, -1);

    // Can't edit the US currency value
    SendDlgItemMessage(hDlg, IDC_NEW_RATE, EM_SETREADONLY, 0 == _tcsicmp(szTLA, TEXT("USD")), 0);

Error:
    VERIFY(NULL == LocalFree(pemri));
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
    ExchangeRateManager* perm;

    // Use our window data to hold a pointer to the ExchangeRateManager
    perm = (ExchangeRateManager*) lParam;
    if(NULL == perm)
        {
        hr = E_INVALIDARG;
        goto Error;
        }
    SetWindowLong(hDlg, DWL_USER, lParam);

    // Get the dialog box the right size.
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
    shidi.hDlg = hDlg;
    if(!SHInitDialog(&shidi))
        {
        hr = E_FAIL;
        goto Error;
        }

    // Initialize the list box
    if(FAILED(hr = perm->FillControlWithCurrencies(FCWCF_ALL_RATES,
            GetDlgItem(hDlg, IDC_CURRENTY_LIST), g_hInstRes,
            IDS_LISTBOX_FORMAT, NULL)))
        {
        goto Error;
        }

    if(FAILED(hr = OnSelectedCurrencyChanged(hDlg)))
        {
        goto Error;
        }

Exit:
    return(TRUE);
Error:
    EndDialog(hDlg, hr);
    goto Exit;
}


/*****************************************************************************

 ****************************************************************************/
HRESULT OnCommit(
    HWND hDlg
    )
{
    HRESULT hr = S_OK;
    ExchangeRateManager* perm;
    TCHAR szTLA[c_TLABufferSize];
    EMRateInfo emri;
    TCHAR szRate[40];

    if(FAILED(hr = GetRateManagerAndSelectedCurrency(hDlg, &perm, szTLA)))
        {
        goto Error;
        }

    ZeroMemory(&emri, sizeof(emri));

    if(0 == GetDlgItemText(hDlg, IDC_NEW_RATE, szRate, ARRAYSIZE(szRate) - 1))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }

    // A good app would do a heck of a lot more validation here
    emri.rate = _tcstod(szRate, NULL);
    emri.dwValid |= EMRIV_RATE;

    emri.fVisible = (BST_UNCHECKED != SendDlgItemMessage(hDlg, IDC_VISIBLE, BM_GETCHECK, 0, 0));
    emri.dwValid |= EMRIV_VISIBLE;

    GetSystemTimeAsFileTime(&(emri.ftLastUpdate));
    emri.dwValid |= EMRIV_UPDATE_TIME;

    if(FAILED(hr = perm->SetRateInfoByTLA(szTLA, &emri)))
        {
        goto Error;
        }

Exit:
    return(hr);

Error:
    DisplayError(hDlg, g_hInstRes, IDS_ERROR_CAPTION, IDS_ERROR_UNABLETOCHANGERATE, hr);
    goto Exit;
}


/*****************************************************************************

 ****************************************************************************/
HRESULT OnReset(
    HWND hDlg
    )
{
    HRESULT hr = S_OK;
    ExchangeRateManager* perm;
    TCHAR szTLA[c_TLABufferSize];

    if(FAILED(hr = GetRateManagerAndSelectedCurrency(hDlg, &perm, szTLA)))
        {
        goto Error;
        }

    if(FAILED(hr = perm->ResetRateByTLA(szTLA)))
        {
        goto Error;
        }

    OnSelectedCurrencyChanged(hDlg);
    
Exit:
    return(hr);

Error:
    DisplayError(hDlg, g_hInstRes, IDS_ERROR_CAPTION, IDS_ERROR_UNABLETORESET, hr);
    goto Exit;
}

/*****************************************************************************

 ****************************************************************************/
LRESULT CALLBACK CurrencyEditorDialogProc(
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
                case IDC_CURRENTY_LIST:
                    switch(HIWORD(wParam))
                        {
                        case LBN_SELCHANGE:
                            OnSelectedCurrencyChanged(hDlg);
                            break;

                        default:
                            bRet = FALSE;
                            break;
                        }
                    break;

                case IDOK:
                    OnCommit(hDlg);
                    EndDialog(hDlg, S_OK);
                    break;

                case IDC_COMMIT:
                    OnCommit(hDlg);
                    break;

                case IDC_RESET_CURRENCY:
                    OnReset(hDlg);
                    break;

                default:
                    bRet = FALSE;
                    break;
                }
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
HRESULT DoCurrencyEditorDialog(HWND hWndOwner, ExchangeRateManager* perm)
{
    HRESULT hr = S_OK;
    int iRetval;

    iRetval = DialogBoxParam(g_hInstRes, MAKEINTRESOURCE(IDD_EDITOR),
            hWndOwner, (DLGPROC)CurrencyEditorDialogProc, (LPARAM)perm); 
    if(-1 == iRetval)
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Error;
        }
    hr = (HRESULT)(int)iRetval;
    if(FAILED(hr))
        {
        goto Error;
        }

Exit:
    return(hr);
Error:
    DisplayError(hWndOwner, g_hInstRes, IDS_ERROR_CAPTION, IDS_ERROR_UNABLETOBRINGUPDIALOG, hr);
    goto Exit;
}


