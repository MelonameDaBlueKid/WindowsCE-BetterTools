// SKETCNTR.h : main header file for the SKETCNTR application
//

#if !defined(AFX_SKETCNTR_H__B1110A95_4029_11D1_9306_00600820B4FF__INCLUDED_)
#define AFX_SKETCNTR_H__B1110A95_4029_11D1_9306_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSKETCNTRApp:
// See SKETCNTR.cpp for the implementation of this class
//

class CSKETCNTRApp : public CWinApp
{
public:
	CSKETCNTRApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSKETCNTRApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSKETCNTRApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKETCNTR_H__B1110A95_4029_11D1_9306_00600820B4FF__INCLUDED_)
