// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__E86C7396_965D_4438_8867_C8413665E368__INCLUDED_)
#define AFX_STDAFX_H__E86C7396_965D_4438_8867_C8413665E368__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef STRICT
#define STRICT
#endif

#if _WIN32_WCE == 201
#error ATL is not supported for Palm-Size PC
#endif

#define _WIN32_WINNT 0x0400
#define _ATL_FREE_THREADED

#ifndef _ATL_MIN_CRT
#define _ATL_MIN_CRT
#endif  //  !_ATL_MIN_CRT

#ifdef _WIN32_WCE

#define _ATL_NO_MP_HEAP
#endif

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E86C7396_965D_4438_8867_C8413665E368__INCLUDED)
