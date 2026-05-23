// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)

BEGIN_MESSAGE_MAP(CCeSaveModifiedDlg, CDialog)
	//{{AFX_MSG_MAP(CCeSaveModifiedDlg)
	ON_COMMAND(IDYES, OnYes)
	ON_COMMAND(IDNO, OnNo)
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_COMMAND(ID_FILE_SAVE_AS, OnSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCeSaveModifiedDlg::OnInitDialog()
{
	SetDlgItemText(AFX_IDP_ASK_TO_SAVE, m_strPrompt);
	return CDialog::OnInitDialog();
}

void CCeSaveModifiedDlg::OnYes()
{
	EndDialog(IDYES); 
}

void CCeSaveModifiedDlg::OnNo()
{
	EndDialog(IDNO);
}

void CCeSaveModifiedDlg::OnCancel()
{
	EndDialog(IDCANCEL);
}

void CCeSaveModifiedDlg::OnSaveAs()
{
	EndDialog(ID_FILE_SAVE_AS);
}

#endif // _WIN32_WCE_PSPC

