// ChkBkDoc.cpp : implementation of the CCheckBookDoc class
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
#include "chkbook.h"

#include "ChkBkDoc.h"
#include "ChkBkVw.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckBookDoc

IMPLEMENT_DYNCREATE(CCheckBookDoc, CDocument)

BEGIN_MESSAGE_MAP(CCheckBookDoc, CDocument)
	//{{AFX_MSG_MAP(CCheckBookDoc)
	ON_COMMAND(ID_VIEW_BOOK, OnViewBook)
	ON_COMMAND(ID_VIEW_CHECK, OnViewCheck)
	ON_COMMAND(ID_EDIT_NEW_CHECK, OnEditNewCheck)
	ON_COMMAND(ID_NEXT_CHECK, OnNextCheck)
	ON_COMMAND(ID_PREV_CHECK, OnPrevCheck)
	ON_COMMAND(ID_EDIT_COMMIT, OnEditCommit)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_UPDATE_COMMAND_UI(ID_NEXT_CHECK, OnUpdateNextCheck)
	ON_UPDATE_COMMAND_UI(ID_PREV_CHECK, OnUpdatePrevCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BOOK, OnUpdateViewBook)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CHECK, OnUpdateViewCheck)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COMMIT,OnUpdateCommitCheck)
    ON_UPDATE_COMMAND_UI(ID_EDIT_NEW_CHECK,OnUpdateNewCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckBookDoc construction/destruction

CCheckBookDoc::CCheckBookDoc()
{
	m_bCheckView = TRUE;
	m_nNewCheckNo = FIRST_CHECK_NO;
	m_nCurrentCheckNo = m_nNewCheckNo;
	m_CheckBook.Reset();
}

CCheckBookDoc::~CCheckBookDoc()
{
}

//***********************************************************************
// Function: CCheckBookDoc::OnNewDocument()
//
// Purpose:
//    OnNewDocument customizes the process of opening a new
//    new document.  This involves the setting the current 
//    check number and new check number to FIRST_CHECK_NO (the
//    first number in the check book) and setting the view to
//    check view.
//    UpdateMenu is then called which sets checks against the
//    check view menu item and loads the check information into the
//    view.
//
// Comments:
//    In the debug version, an assert is generated if the index is
//    out of bounds or if the item is disabled for the document.
//
//***********************************************************************
BOOL CCheckBookDoc::OnNewDocument()
{
	BOOL bRet;
	// Initialize check information
#if defined(_WIN32_WCE_PSPC)
	bRet=FileOpenHelper(FALSE);
#else
	bRet=FileOpenHelper(TRUE);
#endif
	return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// CCheckBookDoc serialization

void CCheckBookDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCheckBookDoc diagnostics

#ifdef _DEBUG
void CCheckBookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCheckBookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCheckBookDoc helper functions

//***********************************************************************
// Function: CCheckBookDoc::UpdateMenu()
//
// Purpose:
//    UpdateMenu checks and enables menu items, and retrieves the values
//    for the current check, passing on this information to the view.
//    If the view is to check view, m_bCheckView is true.  Thus, the
//    check view menu item is enabled and the bookv iew menu item is
//    disabled.
//    If the current check number is the last in the book, the Next Check
//    menu item is disabled, and likewise with the Prev Check menu item,
//    if the current check is the first in the book.
//
//***********************************************************************

void CCheckBookDoc::UpdateRecord() 
{
	// Enter the values for the current check
	CCheckRecord* pChk = m_CheckBook.GetCheck(m_nCurrentCheckNo);
	CString strPayTo, strDate, strMemo;
	pChk->GetPayTo(strPayTo);
	pChk->GetDate(strDate);
	pChk->GetMemo(strMemo);

	// Pass check information to the view class
	((CCheckBookView*)m_pView)->SetCheckInfo(m_nCurrentCheckNo,
		pChk->GetCents(), strPayTo, strDate, strMemo);
	((CCheckBookView*)m_pView)->CheckView(m_bCheckView);
}

//***********************************************************************
// Function: CCheckBookDoc::CheckThisCheck()
//
// Purpose:
//    CheckThisCheck firstly checks to see if any changes have been made
//    to the current check.  If this is the case, a message box is
//    displayed (see QueryCommitCheck) asking the user if the check should
//    be commited.  If the user clicks YES (returning the code IDYES), the
//    check information is saved before continuing.
//
// Returns:
//    If the user clicks YES or NO in the message box, the return value
//    is IDOK.
//    If the user clicks CANCEL, the return value is IDOK
//
//***********************************************************************
UINT CCheckBookDoc::CheckThisCheck()
{
	if (!m_bCheckView)
		return IDOK;
	// Check to see if check has been altered
	DWORD dwCents;
	CString strPayTo, strDate, strMemo;
	((CCheckBookView*)m_pView)->GetCheckInfo(dwCents,
		strPayTo, strDate, strMemo);

	if (!(m_CheckBook.IsCheckSame(m_nCurrentCheckNo, dwCents, 
		strPayTo, strDate, strMemo)))
	{
		// If check has been altered, query if user wants to save
		switch (((CCheckBookView*)m_pView)->QueryCommitCheck())
		{
		case IDCANCEL:
			return IDCANCEL;
		case IDNO:
				break;
		default: // IDYES
			{
				m_nNewCheckNo = m_CheckBook.SetCheck(m_nCurrentCheckNo,
					dwCents, strPayTo, strDate, strMemo);
				break;
			}
		}
	}
	return IDOK;
}

CCheckBook* CCheckBookDoc::GetCheckBook()
{
	return &m_CheckBook;
}

/////////////////////////////////////////////////////////////////////////////
// CCheckBookDoc message handlers

void CCheckBookDoc::OnViewBook() 
{
	// If currently the check view,
	// check if the check needs to be commited 
	if (m_bCheckView && CheckThisCheck() == IDCANCEL)
		return;	// Return if user changes mind

	m_bCheckView = FALSE;
	UpdateRecord();
}

void CCheckBookDoc::OnViewCheck() 
{
	// If currently the check view,
	// check if the check needs to be commited 
	if (m_bCheckView && CheckThisCheck() == IDCANCEL)
		return; // Return if user changes mind

	m_bCheckView = TRUE;
	UpdateRecord();
}

void CCheckBookDoc::OnEditNewCheck() 
{
	// If currently the check view,
	// check if the check needs to be commited 
	if (m_bCheckView && CheckThisCheck() == IDCANCEL)
		return; // Return if user changes mind

	m_nCurrentCheckNo = m_nNewCheckNo;	// Set the current check no to greatest
	m_bCheckView = TRUE; // Put view into check view mode
	UpdateRecord();
	((CCheckBookView*)m_pView)->NewCheck(m_nCurrentCheckNo);
}

void CCheckBookDoc::OnNextCheck() 
{
	// Check that there is a next check in the book
	if (m_nCurrentCheckNo >= m_nNewCheckNo - 1) 
		return;

	if (CheckThisCheck() == IDCANCEL)
		return;

	m_nCurrentCheckNo++;
	UpdateRecord();
}

void CCheckBookDoc::OnPrevCheck() 
{
	// Check that there is a previous check in the book
	if (m_nCurrentCheckNo == FIRST_CHECK_NO)
		return;

	if (CheckThisCheck() == IDCANCEL)
		return;

	m_nCurrentCheckNo--;
	UpdateRecord();
}


void CCheckBookDoc::OnEditCommit() 
{
	if (!m_bCheckView)
		return;

	DWORD dwCents;
	CString strPayTo, strDate, strMemo;
	((CCheckBookView*)m_pView)->GetCheckInfo(dwCents,
		strPayTo, strDate, strMemo);

	if ((strPayTo == "") && (strDate == "") && (dwCents == 0))
	{
		m_pView->MessageBox(CString((LPCTSTR)IDS_MESSAGE2));
		return;
	}

	m_nNewCheckNo = m_CheckBook.SetCheck(m_nCurrentCheckNo,
		dwCents, strPayTo, strDate, strMemo);
	UpdateRecord();
}

void CCheckBookDoc::OnFileNew() 
{
	if (CheckThisCheck() == IDCANCEL)
		return;

#if defined(_WIN32_WCE_PSPC)
	FileOpenHelper(FALSE);
#else
	FileOpenHelper(TRUE);
#endif
}

void CCheckBookDoc::OnFileOpen() 
{
	if (CheckThisCheck() == IDCANCEL)
		return;

	FileOpenHelper(TRUE);
}

void CCheckBookDoc::OnAppExit() 
{
	if (CheckThisCheck() == IDCANCEL)
		return;

	((CCheckBookApp*)AfxGetApp())->OnAppExit();
}

void CCheckBookDoc::OnUpdateNextCheck(CCmdUI* pCmdUI) 
{
	// Disable Next Check menu item, if this is the last check in the book
	// Disable this item if there is no open file
	pCmdUI->Enable(  (m_nCurrentCheckNo < (m_nNewCheckNo - 1))
                  && (m_CheckBook.m_fileCheckBook.IsFileOpen()) );
}

void CCheckBookDoc::OnUpdatePrevCheck(CCmdUI* pCmdUI) 
{
	// Disable Prev Check menu item, if this is the first check in the book
	// Disable this item if there is no open file
	pCmdUI->Enable(  (m_nCurrentCheckNo != FIRST_CHECK_NO)
                  && (m_CheckBook.m_fileCheckBook.IsFileOpen()) );
}

void CCheckBookDoc::OnUpdateViewBook(CCmdUI* pCmdUI) 
{
	// Check the current view menu item
	pCmdUI->SetCheck(!m_bCheckView);

	// Disable this item if there is no open file
	pCmdUI->Enable(m_CheckBook.m_fileCheckBook.IsFileOpen());
}

void CCheckBookDoc::OnUpdateViewCheck(CCmdUI* pCmdUI) 
{
	// Check the current view menu item
	pCmdUI->SetCheck(m_bCheckView);

	// Disable this item if there is no open file
	pCmdUI->Enable(m_CheckBook.m_fileCheckBook.IsFileOpen());
}
void CCheckBookDoc::OnUpdateCommitCheck(CCmdUI* pCmdUI) 
{
	// Disable this item if there is no open file
	pCmdUI->Enable(m_CheckBook.m_fileCheckBook.IsFileOpen());
}
void CCheckBookDoc::OnUpdateNewCheck(CCmdUI* pCmdUI) 
{
	// Disable this item if there is no open file
	pCmdUI->Enable(m_CheckBook.m_fileCheckBook.IsFileOpen());
}

BOOL CCheckBookDoc::FileOpenHelper(BOOL bFileOpen) 
{
	m_bCheckView = TRUE;

	if (bFileOpen)
	{
		if (!m_CheckBook.Open())
		{
			if (!m_CheckBook.DoesBookExist())
			{
				// Quit the program
				PostQuitMessage(0);
			}
			return FALSE;
		}
	}
	else if (!m_CheckBook.New())
	{
		PostQuitMessage(0);
		return FALSE;
	}

	m_nNewCheckNo = m_CheckBook.GetNextNewCheckNo();
	m_nCurrentCheckNo = FIRST_CHECK_NO;

	// Set the value for m_pView
	POSITION pos = GetFirstViewPosition();
	m_pView = GetNextView(pos);
	ASSERT(pos == NULL);	// One and only one view
	ASSERT(m_pView->IsKindOf(RUNTIME_CLASS(CCheckBookView)));

	// Update the information in the view and menu
	UpdateRecord();

	return TRUE;
}
