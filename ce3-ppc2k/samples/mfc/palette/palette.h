// Palette.h : main header file for the PALETTE application
//

#if !defined(AFX_PALETTE_H__736ADA48_9752_11D1_9327_00600820B4FF__INCLUDED_)
#define AFX_PALETTE_H__736ADA48_9752_11D1_9327_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaletteApp:
// See Palette.cpp for the implementation of this class
//

class CPaletteApp : public CWinApp
{
public:
	CPaletteApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaletteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPaletteApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALETTE_H__736ADA48_9752_11D1_9327_00600820B4FF__INCLUDED_)
