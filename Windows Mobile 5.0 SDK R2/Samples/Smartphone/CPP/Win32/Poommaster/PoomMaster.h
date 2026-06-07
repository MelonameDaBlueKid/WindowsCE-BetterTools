//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#if !defined(AFX_POOMMASTER_H__6FF2A2E6_F8C1_478E_A5FA_DEC0CEE72870__INCLUDED_)
#define AFX_POOMMASTER_H__6FF2A2E6_F8C1_478E_A5FA_DEC0CEE72870__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <pimstore.h>

#include <windows.h>
#include <aygshell.h>
#include "resource.h"


//interface IFolder;

#define MENU_HEIGHT 26

enum eDisplayMode {EDM_TASKS, EDM_CONTACTS, EDM_CALENDAR};

BOOL InitPoom(HWND hwnd);
void ShutdownPoom();
BOOL GetPoomFolder(int nFolder, IFolder ** ppFolder);
BOOL PopulateList(int nFolder);
BOOL GetPoomApp(IPOutlookApp **ppOutApp);
BOOL AddTaskFolderText(IPOutlookItemCollection * pItemCol);
BOOL AddContactsFolderText(IPOutlookItemCollection * pItemCol);
BOOL AddCalendarFolderText(IPOutlookItemCollection * pItemCol);
void AddToList(TCHAR * tszTxt);
int GetTaskPriority(int nIndex);
BOOL TaskIsComplete(int nIndex);

void GetCtrlBstr(HWND hDlg, int nCtrlId, BSTR * pbstrTxt);


BOOL InitNewItemDlg(HWND hDlg);
void RemoveBorder(HWND hWndControl);
BOOL IsSmartphone();

LRESULT CALLBACK	NewContactProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	NewTaskProc			(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	NewAppntmntProc			(HWND, UINT, WPARAM, LPARAM);

#endif // !defined(AFX_POOMMASTER_H__6FF2A2E6_F8C1_478E_A5FA_DEC0CEE72870__INCLUDED_)
