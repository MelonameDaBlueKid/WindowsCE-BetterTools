///////////////////////////////////////////////////////////////////////////////
//
//  This is "Sample Code" and is distributable subject to the terms of the end 
//  user license agreement.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "helpers.h"
#include "ExMan.h"
#include "resource.h"
#include "CurDlg.h"
#include "EditDlg.h"

static ExchangeRateManager* g_perm = NULL;

extern HWND g_hDlgActive;

#define CDM_RATES_CHANGED (WM_APP + 1)

/*****************************************************************************

 ****************************************************************************/
HRESULT OnRatesChanged(
    HWND hDlg
    )
{
    HRESULT hr = S_OK;

    if(FAILED(hr = g_perm->FillControlWithCurrencies(FCWCF_VISIBLE_RATES,
            GetDlgItem(hDlg, IDC_COMBO_SOURCE), g_hInstRes,
            IDS_DROPDOWN_FORMAT, TEXT("USD"))))
        {
        goto Error;
        }

    if(FAILED(hr = g_perm->FillControlWithCurrencies(FCWCF_VISIBLE_RATES,
            GetDlgItem(hDlg, IDC_COMBO_DEST), g_hInstRes,
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
    mbi.nToolBarId = IDM_CURRENCY_CONVERTER;
    mbi.hInstRes = g_hInstRes;

    if(!SHCreateMenuBar(&mbi))
        {
        hr = HRESULT_FROM_WIN32(GetLastError());
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

    // A good app would do a heck of a lot more validation here
    dIn = _tcstod(szAmount, NULL);

    if(FAILED(hr = g_perm->GetSelectedCurrency(GetDlgItem(hDlg, IDC_COMBO_SOURCE), szTLAIn, ARRAYSIZE(szTLAIn))))
        {
        goto Error;
        }

    if(FAILED(hr = g_perm->GetSelectedCurrency(GetDlgItem(hDlg, IDC_COMBO_DEST), szTLAOut, ARRAYSIZE(szTLAOut))))
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
BOOL HandleKeyButton(
    HWND hDlg,
    UINT idc
    )
{
    struct KeyInfo
        {
        UINT idc;
        TCHAR chAppend;
        };
    static const KeyInfo s_rgki[] =
        {
        {IDC_BUTTON_DECIMAL, TEXT('.')},
        {IDC_BUTTON_0, TEXT('0')},
        {IDC_BUTTON_1, TEXT('1')},
        {IDC_BUTTON_2, TEXT('2')},
        {IDC_BUTTON_3, TEXT('3')},
        {IDC_BUTTON_4, TEXT('4')},
        {IDC_BUTTON_5, TEXT('5')},
        {IDC_BUTTON_6, TEXT('6')},
        {IDC_BUTTON_7, TEXT('7')},
        {IDC_BUTTON_8, TEXT('8')},
        {IDC_BUTTON_9, TEXT('9')},
        {0,0}
        };

    const KeyInfo* pki;
    DWORD dwStart;
    DWORD dwEnd;

    for(pki = s_rgki; (0 != pki->idc) && (pki->idc != idc) ; pki++);
    if(0 == pki->idc)
        {
        return(FALSE);
        }

    // If there is a selection, don't send an End.  The user
    // probably wants to replace the selection.
    SendDlgItemMessage(hDlg, IDC_EDIT_SOURCE, EM_GETSEL, (WPARAM)(DWORD*)&dwStart, (WPARAM)(DWORD*)&dwEnd);
    if(dwStart == dwEnd)
        {
        SendDlgItemMessage(hDlg, IDC_EDIT_SOURCE, WM_KEYDOWN, VK_END, 0);
        }

    SendDlgItemMessage(hDlg, IDC_EDIT_SOURCE, WM_CHAR, pki->chAppend, 0);

    return(TRUE);
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

                case IDC_BUTTON_CLEAR:
                    SetDlgItemText(hDlg, IDC_EDIT_SOURCE, TEXT(""));
                    break;

                case IDC_BUTTON_BACKSPACE:
                    SendDlgItemMessage(hDlg, IDC_EDIT_SOURCE, WM_KEYDOWN, VK_END, 0);
                    SendDlgItemMessage(hDlg, IDC_EDIT_SOURCE, WM_CHAR, VK_BACK, 0);
                    break;

                case IDM_CHANGE_RATES:
                    DoCurrencyEditorDialog(hDlg, g_perm);
                    OnRatesChanged(hDlg); // we could be smarter about only calling this if needed
                    break;

                default:
                    if(!(bRet = HandleKeyButton(hDlg, idc)))
                        {
                        bRet = FALSE;
                        }
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
			PostMessage(GetParent(hDlg), WM_CLOSE, 0, 0);
            break;

        case CDM_RATES_CHANGED:
            OnRatesChanged(hDlg);
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


