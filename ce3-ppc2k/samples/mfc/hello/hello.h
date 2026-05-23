// hello.h : Declares the class interfaces for the application.
//         Hello is a simple program which consists of a main window
//         and an "About" dialog which can be invoked by a menu choice.
//         It is intended to serve as a starting-point for new
//         applications.
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

#ifndef __HELLO_H__
#define __HELLO_H__

/////////////////////////////////////////////////////////////////////////////

// CMainWindow:
// See hello.cpp for the code to the member functions and the message map.
//
class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();

	//{{AFX_MSG( CMainWindow )
	afx_msg void OnPaint();
	afx_msg void OnAbout();
	//}}AFX_MSG
#if defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	BOOL m_bShowDoneButton;
	afx_msg void OnShowDonebutton();
	afx_msg void OnUpdateShowDonebutton(CCmdUI* pCmdUI);
	void OnOK();
#endif  //  defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

// CTheApp:
// See hello.cpp for the code to the InitInstance member function.
//
class CTheApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////

#endif // __HELLO_H__
