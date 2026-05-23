// ctrltest.h : main window class interface
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

#include "resource.h"
#include "res\otherids.h"

/////////////////////////////////////////////////////////////////////////////
// Application class

class CTestApp : public CWinApp
{
public:

	virtual BOOL InitInstance();
	//{{AFX_MSG(CTestApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
};

/////////////////////////////////////////////////////////////////////////////
// Main Window
//   used as the context for running all the tests

class CTestWindow : public CFrameWnd
{
protected:
// Implementation
	//{{AFX_MSG(CTestWindow)
	afx_msg void OnTestDerivedEdit();           // simple test
	afx_msg void OnTestSubclassedEdit();        // simple test
	afx_msg void OnTestBitmapButton1();         // custom control
	afx_msg void OnTestBitmapButton2();         // custom control
	afx_msg void OnTestBitmapButton3();         // custom control
	afx_msg void OnTestSpinEdit();          // custom control
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
