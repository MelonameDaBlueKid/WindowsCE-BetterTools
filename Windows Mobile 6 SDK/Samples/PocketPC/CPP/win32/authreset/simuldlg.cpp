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

#include "simuldlg.hpp"
#include "resourceppc.h"


//  Initialize a map for error codes to show on the dialog
//
#define MAKE_PAIR(x) L#x, (DWORD) x,
#define MAKE_WIN32PAIR(x) L#x, (DWORD) HRESULT_FROM_WIN32(x),

SimulDlg::ErrorCodePair SimulDlg::m_errorCodes[] =
{
    MAKE_PAIR(E_FAIL)
    MAKE_PAIR(E_UNEXPECTED)
    MAKE_PAIR(E_OUTOFMEMORY)
    MAKE_PAIR(E_INVALIDARG)
    MAKE_PAIR(E_ACCESSDENIED)
    MAKE_PAIR(E_ABORT)
    MAKE_WIN32PAIR(ERROR_NO_NETWORK)
    MAKE_WIN32PAIR(ERROR_HOST_UNREACHABLE)
};

#undef MAKE_PAIR
#undef MAKE_WIN32PAIR

int SimulDlg::m_errorCodesCount = sizeof(SimulDlg::m_errorCodes) / sizeof(SimulDlg::m_errorCodes[0]);


IMPLEMENT_DYNAMIC(SimulDlg, CDialog)

SimulDlg::SimulDlg(int idd)
    : CDialog(idd, static_cast<CWnd *>(NULL))
    , m_errorCodeRadio(RADIO_SUCCESS)
    , m_errorCodeCBoxSelection(0)
{}

SimulDlg::~SimulDlg()
{}

bool SimulDlg::Success() const
{
    return m_errorCodeRadio == RADIO_SUCCESS;
}

DWORD SimulDlg::ErrorCode() const
{
    return m_errorCodes[m_errorCodeCBoxSelection].value;
}


void SimulDlg::DoDataExchange(CDataExchange * pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_SIMULDLG_SUCCESS, m_errorCodeRadio);
    DDX_Control(pDX, IDC_ERRORCODE_COMBO, m_errorCodeCBox);
    m_errorCodeCBoxSelection = m_errorCodeCBox.GetCurSel();
}


BEGIN_MESSAGE_MAP(SimulDlg, CDialog)
    ON_BN_CLICKED(IDC_SIMULDLG_SUCCESS, SimulDlg::OnBnClickedRadioSuccess)
    ON_BN_CLICKED(IDC_SIMULDLG_FAILURE, SimulDlg::OnBnClickedRadioFailure)
END_MESSAGE_MAP()


// ErrorConditionDlg message handlers

void SimulDlg::OnBnClickedRadioSuccess()
{
    ToggleFailureFields(false);
}

void SimulDlg::OnBnClickedRadioFailure()
{
    ToggleFailureFields(true);
}

BOOL SimulDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    for (int i = 0; i < m_errorCodesCount; ++i)
        m_errorCodeCBox.AddString(m_errorCodes[i].name);

    m_errorCodeCBox.SetCurSel(0);

    return TRUE;
}
