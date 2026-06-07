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

#include "passcodedlg.hpp"
#include "resourceppc.h"

PasscodeDlg::PasscodeDlg(std::wstring const & passcode)
    : SimulDlg(IDD_PASSCODEDLG_PPC_PORTRAIT)
    , m_passcode(passcode)
{}

//  Toggle enable property of success/failure elements of the dialog
//  based on the user input.
//
void PasscodeDlg::ToggleFailureFields(bool enable)
{
    GetDlgItem(IDC_PASSCODE_STATIC)->EnableWindow(!enable);
    GetDlgItem(IDC_PASSCODE_EDIT)->EnableWindow(!enable);

    GetDlgItem(IDC_ERRORCODE_STATIC)->EnableWindow(enable);
    GetDlgItem(IDC_ERRORCODE_COMBO)->EnableWindow(enable);
}

BOOL PasscodeDlg::OnInitDialog()
{
    SimulDlg::OnInitDialog();

    GetDlgItem(IDC_PASSCODE_EDIT)->SetWindowText(m_passcode.c_str());

    return TRUE;
}
