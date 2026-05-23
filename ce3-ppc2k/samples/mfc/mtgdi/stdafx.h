// stdafx.h : include file for standard system include files
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include <afxwin.h>		 // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxtempl.h>		// MFC templates

#include <afxmt.h>

#if defined (_SH3_) || defined(_MIPS_)
	#define rand   Random
#endif
#if defined (_WIN32_WCE_EMULATION)
	extern "C" int    __cdecl rand(void);
#endif
