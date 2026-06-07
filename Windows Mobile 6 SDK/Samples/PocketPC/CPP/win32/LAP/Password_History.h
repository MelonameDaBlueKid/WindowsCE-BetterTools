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
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#pragma once

/*
 *  AddPasswordToHistory
 *
 *  SUMMARY:
 *
 *      Adds the current password to the password history store. Called
 *      just before the new user password is stored.
 *
 *  PARAMETERS:
 *
 *      ppwi                [IN}    Pointer to a PASSWDINFO structure that
 *                                  contains the potential new password as
 *                                  well as the current LAP policies.
 *
 *  RETURN:
 *
 *      An HRESULT indicating success or failure. The SUCCEEDED/FAILED macros
 *      should be used to determine success or failure. 
 */
HRESULT AddPasswordToHistory (__in const PASSWDINFO * pwi);


/*
 *  PasswordHistoryCheck
 *
 *  SUMMARY:
 *
 *      Checks a new potential password to see if the same password is in the
 *      password history store. If the same password is found then the new
 *      password is not acceptable and the user will need to choose another
 *      new password.
 *
 *  PARAMETERS:
 *
 *      ppwi                [IN}    Pointer to a PASSWDINFO structure that
 *                                  contains the potential new password as
 *                                  well as the current LAP policies.
 *
 *  RETURN:
 *
 *      An BOOL. A non-zero return value means that the password was not found
 *      in the password history file and is usable as a new password. A return
 *      value of 0 means that the password was found in the password history
 *      store and cannot be used.
 *
 */
BOOL    PasswordHistoryCheck (__in const PASSWDINFO* ppwi);
