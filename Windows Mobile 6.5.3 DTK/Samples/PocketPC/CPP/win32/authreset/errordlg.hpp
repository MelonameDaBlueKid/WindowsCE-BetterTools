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

#if !defined(ERRORDLG_HPP_927948273)
#define ERRORDLG_HPP_927948273

#include "simuldlg.hpp"

//  Error condition dialog provides the user a possibility to simulate
//  the success/error condition.
//  It's derived from SimulDlg that provides base dialog functionality.
//
class ErrorConditionDlg : public SimulDlg
{
public:
    ErrorConditionDlg();

private:
    virtual void ToggleFailureFields(bool enable);
};

#endif  // ERRORDLG_HPP_927948273
