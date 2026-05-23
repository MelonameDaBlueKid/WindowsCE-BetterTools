// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if (_WIN32_WCE < 201)
	#error "This sample is only compatible with MFCCE 2.01 or later."
#endif

#if !defined(AFX_STDAFX_H__736ADA4A_9752_11D1_9327_00600820B4FF__INCLUDED_)
#define AFX_STDAFX_H__736ADA4A_9752_11D1_9327_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define READ_BM_FROM_RESOURCE // read bitmap from resource

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__736ADA4A_9752_11D1_9327_00600820B4FF__INCLUDED_)
