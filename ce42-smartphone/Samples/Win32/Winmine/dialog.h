// ***************************************************************************
// DIALOG.H
//
// Function Declarations for Minesweeper dialog boxes
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#pragma once

#ifndef _DIALOG_H_
#define _DIALOG_H_

// bad return values
#define ENOMEM			(-2)
#define EINITFAILED		(-1)

// Function Declarations
BOOL CALLBACK HelpDlgProc(const HWND hDlg, const UINT uiMessage, 
						  const WPARAM wParam, const LPARAM lParam);
BOOL CALLBACK HighDlgProc(const HWND hDlg, const UINT uiMessage, 
						  const WPARAM wParam, const LPARAM lParam);
BOOL CALLBACK NewHighDlgProc(const HWND hDlg, const UINT uiMessage, 
							 const WPARAM wParam, const LPARAM lParam);
BOOL CALLBACK PrefsDlgProc(const HWND hDlg, const UINT uiMessage, 
						   const WPARAM wParam, const LPARAM lParam);
BOOL InitDialog(const HWND hDlg, UINT nToolBarId);
BOOL AddValidKeys(const HWND hwnd, const DWORD dwCurKey);
BOOL AssignKeys(HWND hDlg);

#endif	// _DIALOG_H_