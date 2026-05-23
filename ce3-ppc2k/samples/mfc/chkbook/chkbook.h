// chkbook.h : main header file for the CHKBOOK application
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

#ifndef __INC_CHKBOOK_H__
#define __INC_CHKBOOK_H__

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckBookApp:
// See chkbook.cpp for the implementation of this class
//

class CCheckBookApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBookApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	void CheckView(BOOL bCheckView);
	//{{AFX_MSG(CCheckBookApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	void OnAppExit();
	DECLARE_MESSAGE_MAP()
};

#endif // __INC_CHKBOOK_H__
/////////////////////////////////////////////////////////////////////////////
