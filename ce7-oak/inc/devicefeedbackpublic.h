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
#pragma once

#define DDXF_REGKEY_ROOT_SETTINGS           L"System\\DeviceFeedback"
#define DDXF_REGVALUE_UPLOAD_ENABLED        L"UploadEnabled"
#define DDXF_REGVALUE_COLLECTION_ENABLED    L"CollectionEnabled"
#define DDXF_REGVALUE_HIDE_OTA              L"HideOTA"

#define DDXF_DATA_COLLECTION_DISABLED   0x00000000
#define DDXF_DATA_COLLECTION_ENABLED    0x00000001
#define DDXF_UPLOAD_CONNECTION_DISABLED 0x00000000
#define DDXF_UPLOAD_CONNECTION_CABLED  0x00000001
#define DDXF_UPLOAD_CONNECTION_ANY      0xFFFFFFFF

#define WATSON_UPLOAD_ATTEMPT            L"WatsonUploadAttempt"
