#ifndef _PROCESSCFG_H_
#define _PROCESSCFG_H_
// Copyright (c) Microsoft Corporation. All rights reserved.	
//
// DESCRIPTION:
// Configmanager API to process XML configuration files

#ifdef __cplusplus
extern "C" {
#endif

#define CFGFLAG_PROCESS              0x0001
#define CFGFLAG_METADATA             0x0002

HRESULT DMProcessConfigXML(LPCWSTR pszWXMLin, DWORD dwFlags, LPWSTR *ppszwXMLout);

#ifdef __cplusplus
}
#endif

#endif // _PROCESSCFG_H_
