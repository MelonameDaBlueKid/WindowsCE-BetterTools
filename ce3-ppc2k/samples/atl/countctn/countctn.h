// CountCtn.h : main header file for the COUNTCTN application
//

#if !defined(AFX_COUNTCTN_H__B3051BC4_4BDB_11D1_9308_00600820B4FF__INCLUDED_)
#define AFX_COUNTCTN_H__B3051BC4_4BDB_11D1_9308_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCountCtnApp:
// See CountCtn.cpp for the implementation of this class
//

class CCountCtnApp : public CWinApp
{
public:
	CCountCtnApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountCtnApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCountCtnApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTCTN_H__B3051BC4_4BDB_11D1_9308_00600820B4FF__INCLUDED_)
