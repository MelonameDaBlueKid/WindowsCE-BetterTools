//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// CMHELPER.h : main header file for the CMHELPER application
//

#if !defined(AFX_CMHELPER_H__AF9B2C3A_3844_4F5F_B00F_5239F19CF180__INCLUDED_)
#define AFX_CMHELPER_H__AF9B2C3A_3844_4F5F_B00F_5239F19CF180__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCMHELPERApp:
// See CMHELPER.cpp for the implementation of this class
//

class CCMHELPERApp : public CWinApp
{
public:
	CCMHELPERApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCMHELPERApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCMHELPERApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMHELPER_H__AF9B2C3A_3844_4F5F_B00F_5239F19CF180__INCLUDED_)
