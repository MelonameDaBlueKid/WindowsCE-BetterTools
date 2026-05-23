// deredit.cpp : C++ derived Edit control example
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

#include "stdafx.h"
#include "ctrltest.h"

#include "paredit.h"

/////////////////////////////////////////////////////////////////////////////

class CDerEditDlg : public CDialog
{
protected:
	CFont*  m_pFont;
	// construct
	CParsedEdit m_edit1, m_edit2, m_edit3, m_edit4;
	CStatic m_static1, m_static2, m_static3, m_static4;
public:
	//{{AFX_DATA(CDerEditDlg)
#if defined(_WIN32_WCE_PSPC)
	enum { IDD = IDD_DERIVED_EDIT_PSPC };
#else
	enum { IDD = IDD_DERIVED_EDIT };
#endif			
	//}}AFX_DATA
	CDerEditDlg()
		: CDialog(CDerEditDlg::IDD)
		{ }

	void OnSetFont(CFont* pFont)
			{ m_pFont = pFont; }

	BOOL OnInitDialog();
	//{{AFX_MSG(CDerEditDlg)
		virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CDerEditDlg, CDialog)
	//{{AFX_MSG_MAP(CDerEditDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDerEditDlg::OnInitDialog()
	// create children on InitDialog
	//  (not in CDerEditDlg constructor since the dialog has
	//    no attached HWND in the constructor)
{
	CDialog::OnInitDialog();
	const int yStart = 8;
	const int height = 30;

	CPoint whereLabel(10, yStart);
	CSize sizeLabel(80, 24);

	CPoint whereEdit(90, yStart);
	CSize sizeEdit(140, 24);

	m_static1.Create(CString((LPCTSTR)IDS_LETTERS), WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, (UINT)-1);
	whereLabel.y += height;
	m_edit1.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_LETTERS,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT1);
	whereEdit.y += height;

	m_static2.Create(CString((LPCTSTR)IDS_NUMBERS), WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, (UINT)-1);
	whereLabel.y += height;
	m_edit2.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_NUMBERS,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT2);
	whereEdit.y += height;

	m_static3.Create(CString((LPCTSTR)IDS_EITHER), WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, (UINT)-1);
	whereLabel.y += height;
	m_edit3.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_LETTERS | PES_NUMBERS,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT3);
	whereEdit.y += height;

	m_static4.Create(CString((LPCTSTR)IDS_ANYTHING), WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, (UINT)-1);
	whereLabel.y += height;
	m_edit4.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_ALL,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT4);
	whereEdit.y += height;

	// change the dialog height so everything fits
	int yBottom = whereEdit.y + height * 2; // extra space

#if !defined(_WIN32_WCE_PSPC) || (_WIN32_WCE < 300)
	CRect rect;
	GetWindowRect(rect);
	VERIFY(SetWindowPos(NULL, -1, -1, rect.Width(), yBottom,
		SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE));
#endif 

	// set focus to first one
	m_edit1.SetFocus();
	return FALSE;   // focus set
}

void CDerEditDlg::OnOK()
{
#ifdef _DEBUG
	// dump results, normally you would do something with these
	CString s;
	m_edit1.GetWindowText(s);
	TRACE(_T("edit1 = '%s'\n"), s);
	m_edit2.GetWindowText(s);
	TRACE(_T("edit2 = '%s'\n"), s);
	m_edit3.GetWindowText(s);
	TRACE(_T("edit3 = '%s'\n"), s);
	m_edit4.GetWindowText(s);
	TRACE(_T("edit4 = '%s'\n"), s);
#endif

	EndDialog(IDOK);
}

/////////////////////////////////////////////////////////////////////////////
// Run the test

void CTestWindow::OnTestDerivedEdit()
{
	TRACE(_T("running dialog with special derived CParsedEdit controls in it\n"));
	CDerEditDlg dlg;
	dlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
