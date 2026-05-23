// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#ifdef _AFXDLL
// The following symbol used to force inclusion of this module for _AFXDLL
#if defined(_WIN32_WCE)
#if defined(_WIN32_WCE_NO_PREFIXED_SYMBOLS) 
extern "C" { int _afxForceSTDAFX; }
#else // _WIN32_WCE_NO_PREFIXED_SYMBOLS
extern "C" { int __afxForceSTDAFX; }
#endif // _WIN32_WCE_NO_PREFIXED_SYMBOLS
#else // _WIN32_WCE
#ifdef _X86_
extern "C" { int _afxForceSTDAFX; }
#else
extern "C" { int __afxForceSTDAFX; }
#endif
#endif // _WIN32_WCE
#endif
