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

#if !defined(PASSCODEDLG_HPP_892934729)
#define PASSCODEDLG_HPP_892934729

#include "simuldlg.hpp"
#include <string>

//  This dialog provides the user a possibility to simulate
//  the success/error condition and shows a user a recovery key (passcode).
//  It's derived from SimulDlg that provides base dialog functionality.
//
class PasscodeDlg : public SimulDlg
{
public:
    PasscodeDlg(std::wstring const & passcode);

protected:
    virtual BOOL OnInitDialog();

private:
    virtual void ToggleFailureFields(bool enable);

private:
    std::wstring m_passcode;
};

#endif  // PASSCODEDLG_HPP_892934729
