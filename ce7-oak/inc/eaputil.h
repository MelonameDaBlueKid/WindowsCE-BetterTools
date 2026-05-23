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
/*++


Module Name:

    eaputil.h

Abstract:

    Header file for EAP utility functions.

Environment:

    
--*/

#pragma once

#include <raseapif.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////
//  EAP Utility functions
////////////////////////////////////////////////////////////////

typedef struct _EAP_EXTENSION_INFO
{
	// Information describing the extension loaded from the registry
	DWORD				dwExtensionType;
	WCHAR				wszExtensionDllPath[MAX_PATH];
	WCHAR				wszInteractiveUIPath[MAX_PATH];
	WCHAR				wszIdentityPath[MAX_PATH];
	WCHAR				wszConfigUIPath[MAX_PATH];
	WCHAR				wszFriendlyName[MAX_PATH];
	BOOL				bRequireConfigUI;
	BOOL				bStandaloneSupported;
	BOOL				bMPPEEncryptionSupported;
	BOOL				bInvokeUsernameDialog;
	BOOL				bInvokePasswordDialog;
	WCHAR				wszConfigCLSID[MAX_PATH];
} EAP_EXTENSION_INFO, *PEAP_EXTENSION_INFO;

extern DWORD
eapUtilGetProcAddresses(
	IN	PWCHAR		wszDllName,
	OUT	HINSTANCE	*phDll,
	...);

#define RAS_EAP_EXTENSIONS_REGISTRY_LOCATION	TEXT("Comm\\EAP\\Extension")

extern DWORD
EapRegReadExtensionInfo(
	IN		HKEY				hKey,
	IN		PWSTR				wszSubKeyName,
	IN		DWORD				dwExtensionType,
	OUT		PEAP_EXTENSION_INFO	pInfo);

extern DWORD
EapEnumExtensions(
	IN	DWORD				cbExtensionInfo,
	OUT	PEAP_EXTENSION_INFO	pExtensionInfo,
	OUT	PDWORD				pdwNumExtensions,
	OUT PDWORD				pcbExtensionInfoNeeded);

extern RAS_AUTH_ATTRIBUTE *
EapUtilAuthAttributeGetVendorSpecific(
    IN  RAS_AUTH_ATTRIBUTE *    pUserAttributes,
    IN  DWORD                   dwVendorId,
    IN  BYTE                    dwVendorType);

extern DWORD
EapUtilAuthAttributeInsertVSA(
    IN  DWORD                   iAttribute,
    OUT RAS_AUTH_ATTRIBUTE *    pAttributes,
    IN  DWORD                   dwVendorId,
    IN  BYTE                    bVendorType,
	__in_bcount(cbValue) IN  PBYTE                   pValue,
	IN  BYTE                    cbValue);

extern RAS_AUTH_ATTRIBUTE *
EapUtilAuthAttributeArrayAlloc(
	DWORD nAttrs);

extern void
EapUtilAuthAttributeArrayFree(
	RAS_AUTH_ATTRIBUTE *pAttributes);

#define MAX_MPPE_KEY_LENGTH	32

extern DWORD
EapUtilExtractMPPEKey(
	__inout	PBYTE				pMPPEKey,
		OUT PDWORD				pcbMPPEKey,
    IN  RAS_AUTH_ATTRIBUTE *    pUserAttributes,
    IN  DWORD                   dwVendorId,
    IN  BYTE                    dwVendorType);

///////////////////////////////////////
//	Registry utilities functions
///////////////////////////////////////

//
// dwFlags values:
//
#define REG_ALLOC_MEMORY	(1<<0)

DWORD
RegReadValues(
	IN	HKEY	 hKey,
	IN	TCHAR	*tszSubKeyName,	OPTIONAL
	...);
//
//	Read in a number of registry values.
//
//	For each value to be read in, the following parameters must be passed:
//
//		TCHAR  *tszValueName
//		DWORD	valueType
//		DWORD	dwFlags
//		void   *pValue
//		DWORD	cbValue		// size of space pointed to by pValue
//
//	The list is terminated with a NULL tszValueName
//
//	Returns the count of the number of values that were read in successfully.
//

DWORD
RegWriteValues(
	IN	HKEY	 hKey,
	IN	TCHAR	*tszSubKeyName,	OPTIONAL
	...);
//
//	Write out a number of registry values.
//
//	For each value to be written, the following parameters must be passed:
//
//		TCHAR  *tszValueName
//		DWORD	valueType
//		DWORD	dwFlags
//		void   *pValue
//		DWORD	cbValue		// size of space pointed to by pValue
//
//	The list is terminated with a NULL tszValueName
//
//	Returns the count of the number of values that were written out successfully.
//

LONG
RegDeleteKeyValues(
	HKEY	hKey,
	PWSTR	tszSubKeyName OPTIONAL);
//
//  Delete all the values contained in the specified key.
//

LONG
RegDeleteKeyAndContents(
	IN	HKEY	 hKey,
	IN	TCHAR	*tszSubKeyName);
//
//  A registry key cannot be deleted unless is is empty.
//  This function empties the key and then deletes it.
//


//
//	Enumerate all the subkeys of a key and
//	call the specified function on each
//
DWORD
RegTraverseKey(
	HKEY	hRootKey,
	PWSTR	wszKeyName, OPTIONAL
	DWORD	(*pFunc)(HKEY hKey, PWSTR wszSubKeyName, PVOID pContext),
	PVOID	pContext
	);


#ifdef __cplusplus
}
#endif
