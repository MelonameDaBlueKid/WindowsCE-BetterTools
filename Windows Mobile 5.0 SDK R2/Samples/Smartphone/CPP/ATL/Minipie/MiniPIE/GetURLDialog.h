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

// GetURLDialog.h : Defines a dialog that allows a user to enter an URL.
// This is not really needed to host the PIEWebBrowser control. However, it's 
// implemented here in order to allow the user to navigate on Smartphone, 
// where the AddressBar property is not implemented.

#pragma once

#include "stdafx.h"
#include "resource.h"

class CGetURLDialog : 
    public CDialogImpl<CGetURLDialog>
{
public:
    CGetURLDialog();
    ~CGetURLDialog();

    BSTR GetURL() const
    { return m_bstrURL; }

    enum { IDD = IDD_GETURLDIALOG };

    BEGIN_MSG_MAP(CGetURLDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
        COMMAND_ID_HANDLER(IDOK, OnOKCommand)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancelCommand)
    END_MSG_MAP()

private:
    // Handler prototypes:
    //  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    //  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnOKCommand(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancelCommand(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    BSTR m_bstrURL;
};


