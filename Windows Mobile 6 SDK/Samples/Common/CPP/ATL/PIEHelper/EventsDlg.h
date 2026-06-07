//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// EventsDlg.h : Declaration of the CEventsDlg

#ifndef __EVENTSDLG_H_
#define __EVENTSDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEventsDlg
class CEventsDlg : public CDialogImpl<CEventsDlg>
{
public:
	CEventsDlg();
	~CEventsDlg();

	enum { IDD = IDD_EVENTSDLG };

   BEGIN_MSG_MAP(CEventsDlg)
	   MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	   COMMAND_ID_HANDLER(IDOK, OnOK)
   END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

   void AddEventToList(BSTR pszEvent);

private:
   HWND m_hwndEventsLst;
   int  m_nHorizExtent;
};

#endif //__EVENTSDLG_H_
