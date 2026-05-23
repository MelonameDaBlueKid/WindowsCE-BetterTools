// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE == 201)
	#error "This sample is not available for Gryphon Palm-Size devices."
#endif

#if (_WIN32_WCE < 200)
	#error "This sample is only compatible with ATLCE 2.0 or later."
#endif

#if !defined(AFX_STDAFX_H__BD7BB4A9_4008_11D1_9306_00600820B4FF__INCLUDED_)
#define AFX_STDAFX_H__BD7BB4A9_4008_11D1_9306_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BD7BB4A9_4008_11D1_9306_00600820B4FF__INCLUDED_)
