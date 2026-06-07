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

#ifndef LAP_PRIV_H
#define LAP_PRIV_H

#include <windows.h>
#include <tpcshell.h>   // For SHSendBackToFocusWindow
#include <aygshell.h>   // For SHDeviceLockAndPrompt
#include <regext.h>     // For RegistryGet***, RegistryNotifyWindow
#include <secpol.h>     // For SECPOLICY_* and POLICYVAL_* values
#include <devmgmt.h>    // For QueryPolicy
#include <phone.h>      // For PhoneMakeCall
#include <wincrypt.h>   // For Cryptographic functions
#include <snapi.h>      // For PhoneRadioPresent & PhoneActiveCallCount defines
#include <safeint.hxx>  // Safe integer helper functions

#include <lass.h>       // LASS/LAP APIs       
#include <lass_ae.h>
#include <lap.h>

#include "resource.h"   // Resources
#include "util.h"       // Utilities

#endif  // LAP_PRIV_H
