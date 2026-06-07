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

#if !defined(SIMULDLG_HPP_328429749)
#define SIMULDLG_HPP_328429749

#include <afx.h>
#include <afxwin.h>

//  This is a base class for a success/error simulation dialog
//  It provides basic functionality of displaying the dialog,
//  presenting a choice of success/error codes,
//  doing data exchange and reacting to the user input.
//  The base class doesn't have a dialog resource ID.
//  Derived classes are responsible of providing the resource ID
//  for the concrete dialog to show.
//

class SimulDlg : public CDialog
{
    DECLARE_DYNAMIC(SimulDlg)

    enum { RADIO_SUCCESS, RADIO_FAILURE };

public:
    SimulDlg(int idd);
    virtual ~SimulDlg();

    //  Indicates if a success option was selected by the user
    bool Success() const;

    //  Get the selected error code, if it was selected
    DWORD ErrorCode() const;

protected:
    virtual void DoDataExchange(CDataExchange * pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

private:
    struct ErrorCodePair
    {
        wchar_t const * name;
        DWORD value;
    };

private:
    afx_msg void OnBnClickedRadioSuccess();
    afx_msg void OnBnClickedRadioFailure();

private:
    //  Toggle enable property of success/failure elements of the dialog based on the user input.
    //  Provide the concrete behavior by implementing it in derived classes.
    virtual void ToggleFailureFields(bool enable) = 0;

private:
    int m_errorCodeRadio;
    CComboBox m_errorCodeCBox;
    int m_errorCodeCBoxSelection;

    static ErrorCodePair m_errorCodes[];
    static int m_errorCodesCount;
};

#endif  // SIMULDLG_HPP_328429749

