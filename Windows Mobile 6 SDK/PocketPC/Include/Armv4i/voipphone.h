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
// voipphone.h
//
// VoIP Phone API
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>

// Override Call Information flags used in 
#define OCIF_CELLULAR_NETWORK       0x00000001
#define OCIF_VOIP_NETWORK           0x00000002
#define OCIF_NETWORK_TYPE_MASK      (OCIF_CELLULAR_NETWORK |  OCIF_VOIP_NETWORK)
#define OCIF_CELLULAR_PHONE_NUMBER  0x00000004
#define OCIF_VOIP_PHONE_NUMBER      0x00000008
#define OCIF_PHONE_NUMBER_TYPE_MASK (OCIF_CELLULAR_PHONE_NUMBER |  OCIF_VOIP_PHONE_NUMBER)
#define OCIF_MASK                   (OCIF_NETWORK_TYPE_MASK | OCIF_VOIP_PHONE_NUMBER)

//  VoIPPhoneOverride API set
//  Used to override the VoIP Phone behavior. The DLL which  implements these
//  APIs should be registered under
//
//  [HKEY_LOCAL_MACHINE\Security\Phone]
//  "VoIPPhoneOverride"=hook.dll

//  VoIPPhoneOverrideInitialize:
//  Invoked whenever the VoIP Phone application is initialized. Right after
//  the DLL is loaded.
//
//  Parameters:
//  None.
//
//  Returns:
//  Must return S_OK.
HRESULT
VoIPPhoneOverrideInitialize(
    void
    );

//  VoIPPhoneOverrideUnInitialize:
//  Invoked whenever the VoIP Phone application is shutdown. Right before
//  the DLL is unloaded.
//
//  Parameters:
//  None.
//
//  Returns:
//  Must return S_OK.
HRESULT
VoIPPhoneOverrideUnInitialize(
    void
    );

//  VoIPPhoneOverrideCallNetwork: 
//  Invoked whenever the VoIP Phone is about to make a call.
//
//  Paramters:
//  [in] pszDialString - number dialed.
//  [in] cchDialStringLength - number of characters of the number dialed.
//  [in/out] pdwCallInformationFlags - call information flags that apply to this call. 
//      One or more of the OCIF_xxx values
//
//  Returns:
//  S_OK : when pCallInformationFlags are processed and the network type is overridden.
//      Only flags that match OCIF_NETWORK_TYPE_MASK are used on output.
//      Any changes to other flags are ignored.
//  E_FAIL : whenever a failure occurrs. Any out parameter will be ignored.
//  E_NOTIMPL : when the default behavior is desired.
HRESULT
VoIPPhoneOverrideCallNetwork(
    LPCTSTR pszDialString,
    DWORD cchDialStringLength,
    DWORD* pdwCallInformationFlags
    );

#ifdef __cplusplus
}
#endif

