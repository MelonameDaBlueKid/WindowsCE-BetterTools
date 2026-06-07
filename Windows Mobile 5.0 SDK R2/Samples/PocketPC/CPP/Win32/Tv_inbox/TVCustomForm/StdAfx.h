// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__FA6769B3_5E3B_4003_869C_872F64997338__INCLUDED_)
#define AFX_STDAFX_H__FA6769B3_5E3B_4003_869C_872F64997338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <cemapi.h>

#include "macros.h"

// TODO: REMOVE THIS AFTER WHIDBEY FIXES THIS BUG
#pragma comment(linker, "/nodefaultlib:oldnames.lib")

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FA6769B3_5E3B_4003_869C_872F64997338__INCLUDED_)
