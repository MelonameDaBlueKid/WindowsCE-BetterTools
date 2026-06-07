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

// GetURLDialog.cpp : Defines a dialog that allows a user to enter an URL.
// This is not really needed to host the PIEWebBrowser control. However, it's 
// implemented here in order to allow the user to navigate on Smartphone, 
// where the AddressBar property is not implemented.

#include "stdafx.h"
#include "GetURLDialog.h"

// CGetURLDialog
CGetURLDialog::CGetURLDialog() : m_bstrURL(NULL)
{
}

CGetURLDialog::~CGetURLDialog()
{
    ::SysFreeString(m_bstrURL);
}

LRESULT CGetURLDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    SHINITDLGINFO shidi = { SHIDIM_FLAGS, m_hWnd, SHIDIF_SIZEDLGFULLSCREEN };
    VERIFY(SHInitDialog(&shidi));

    SHMENUBARINFO mbi = { sizeof(mbi), 0 };
    mbi.hwndParent = m_hWnd;
    mbi.nToolBarId = IDR_GETURL_MENUBAR; // ID of toolbar resource
    mbi.hInstRes = _AtlBaseModule.GetResourceInstance();
    VERIFY(SHCreateMenuBar(&mbi));

    // For devices that have a back key (i.e. Smartphones),
    // override the back key since we have an edit control 
    CWindow(mbi.hwndMB).SendMessage(SHCMBM_OVERRIDEKEY, VK_TBACK, 
                                    MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY,
                                               SHMBOF_NODEFAULT | SHMBOF_NOTIFY));

    VERIFY(SetDlgItemText(IDC_EDIT_URL, TEXT("http://")));

    return 1;  // Let the system set the focus
}

LRESULT CGetURLDialog::OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    if (VK_TBACK == HIWORD(lParam)) // Smartphone-only
    {
        SHSendBackToFocusWindow(uMsg, wParam, lParam);
    }

    return 0;
}

LRESULT CGetURLDialog::OnOKCommand(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    GetDlgItemText(IDC_EDIT_URL, m_bstrURL);
    EndDialog(wID);
    return 0;
}

LRESULT CGetURLDialog::OnCancelCommand(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    EndDialog(wID);
    return 0;
}
