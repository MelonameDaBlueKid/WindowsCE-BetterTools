// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-2000 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

#if (_WIN32_WCE == 201)
// WinCE: This file provides the MFCCE-compatible _DllMainCRTStartup for WinCE 2.01 builds,
//        including Palm-Sized PC.

extern "C" void __cdecl _cinit(void);
extern "C" void __cdecl _cexit(void);

#if defined(_AFXDLL)
extern "C" BOOL (WINAPI* _pRawDllMain)(HINSTANCE, DWORD, LPVOID);
#else
extern "C" BOOL (WINAPI* _pRawDllMain)(HINSTANCE, DWORD, LPVOID) = NULL;
#endif

extern "C" BOOL WINAPI DllMain(HANDLE, DWORD, LPVOID);

extern "C" BOOL __stdcall _DllMainCRTStartup(HINSTANCE hDllHandle, DWORD dwReason, LPVOID lpreserved) 
{
	BOOL retcode = TRUE;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if ( retcode && _pRawDllMain )
			retcode = (*_pRawDllMain)(hDllHandle, dwReason, lpreserved);

		if ( retcode )
			_cinit();
	}
	
	if (retcode)
		retcode = DllMain((HANDLE)hDllHandle, dwReason, lpreserved);
	
	if (dwReason == DLL_PROCESS_DETACH)
	{
		_cexit();
        if ( _pRawDllMain )
		{
			if( (*_pRawDllMain)(hDllHandle, dwReason, lpreserved) == FALSE )
				retcode = FALSE;
		}
	}
	return retcode;
}

// For _USRDLL builds, we need an alternative entry point because the linker is going to favor the 
// one in corelibc.lib.
extern "C" BOOL __stdcall wce_DllMainCRTStartup(HINSTANCE hDllHandle, DWORD dwReason, LPVOID lpreserved) 
{
	return _DllMainCRTStartup(hDllHandle, dwReason, lpreserved);
}

#if defined(_WIN32_WCE_NO_PREFIXED_SYMBOLS)
extern "C" { int _wce_afxForceUSRDLL; }
#else // _WIN32_WCE_NO_PREFIXED_SYMBOLS
extern "C" { int __wce_afxForceUSRDLL; }
#endif // _WIN32_WCE_NO_PREFIXED_SYMBOLS

#endif // _WIN32_WCE
