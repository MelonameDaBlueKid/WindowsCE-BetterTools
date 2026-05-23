// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE == 201)
	#error "This sample is not available for Palm-Size devices."
#endif

#if (_WIN32_WCE < 200)
	#error "This sample is only compatible with MFCCE 2.0 or later."
#endif

#include <afxctl.h>         // MFC support for OLE Custom Controls

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#ifndef _UNICODE
#include <afxdb.h>			// MFC database classes
#include <afxdao.h>			// MFC DAO database classes
#endif // _UNICODE
