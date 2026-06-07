// Copyright (c) Microsoft Corporation. All rights reserved.
//
// DESCRIPTION:
// Device Management APIs

#ifndef DEVMGMT_H
#define DEVMGMT_H

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#include "cfgmgrapi.h"
HRESULT WINAPI QueryPolicy(DWORD dwPolicyId, PDWORD pdwPolicyValue);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* DEVMGMT_H */
