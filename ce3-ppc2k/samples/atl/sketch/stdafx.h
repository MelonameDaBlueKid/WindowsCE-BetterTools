// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE == 201)
	#error "This sample is not available for Gryphon Palm-Size devices."
#endif

#if defined(_WIN32_WCE) && (_WIN32_WCE < 200)
	#error "This sample is only compatible with ATLCE 2.0 or later."
#endif

#if !defined(AFX_STDAFX_H__D3745038_0D38_11D1_9EB8_006097BA8E24__INCLUDED_)
#define AFX_STDAFX_H__D3745038_0D38_11D1_9EB8_006097BA8E24__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#define _WIN32_WINNT 0x0400

#if defined(_WIN32_WCE)
#undef _WIN32_WINNT
#endif

#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D3745038_0D38_11D1_9EB8_006097BA8E24__INCLUDED)
