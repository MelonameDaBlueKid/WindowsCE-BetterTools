// CompCntr.h : main header file for the COMPCNTR application
//

#if !defined(AFX_COMPCNTR_H__5E52C836_D880_11D1_9355_00600820B4FF__INCLUDED_)
#define AFX_COMPCNTR_H__5E52C836_D880_11D1_9355_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompCntrApp:
// See CompCntr.cpp for the implementation of this class
//

class CCompCntrApp : public CWinApp
{
public:
	CCompCntrApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompCntrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCompCntrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPCNTR_H__5E52C836_D880_11D1_9355_00600820B4FF__INCLUDED_)
