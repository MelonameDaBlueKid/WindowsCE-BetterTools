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

#if !defined(AFX_POOMTASKS_H__756F516D_C62A_44CA_B257_EC663654DF52__INCLUDED_)
#define AFX_POOMTASKS_H__756F516D_C62A_44CA_B257_EC663654DF52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"


#define MENU_HEIGHT 26

#endif // !defined(AFX_POOMTASKS_H__756F516D_C62A_44CA_B257_EC663654DF52__INCLUDED_)


#include "windows.h"
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
#include "pimstore.h" // POOM STUFF
#include <tpcshell.h>
#include <winuserm.h> // Button defs
#include "htmlctrl.h" // HTML VIEW

#define PIMTASK_PRIORITY_CXICON 10
#define PIMTASK_PRIORITY_CYICON 13

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

enum FILTER {all, completed, active};
enum SORT	{importance, status, subject, start, due, none};

BOOL IsOverdueTask (ITask*);
void DestructPoom ();
void SetRecurrenceControls (HWND control, SYSTEMTIME systime);


ITask*				FindTask (int i);
BOOL				RefreshItems ();
BOOL				GetTaskCollection (HWND hwnd);
void				UpdateMenus();
void				SetOptions(HWND hDlg);
void				SetOptionDefaults (HWND hDlg);

void NormalizeTime (LPSYSTEMTIME systime); // ALL TIMES ARE NORMALIZED TO 7PM

// Load string from resource
LPCTSTR UseString(UINT uID);

// Some helper decomped functions
// ----------------------------
void GetTaskData (HWND hDlg, ITask* pTask);
void SetTaskData (HWND hDlg, ITask* pTask);
void SetDialogDefaults (HWND hDlg);


static TCHAR g_szBuffer[2000];
static void DebugOut(const TCHAR* szFormat, ...)
{
    va_list vaMarker;

    va_start(vaMarker, szFormat);
    wvsprintf(g_szBuffer, szFormat, vaMarker);
    va_end(vaMarker);

    OutputDebugString(g_szBuffer);
}
