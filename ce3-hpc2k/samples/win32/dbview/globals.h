// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     globals.h
//
//  PURPOSE:    contains variables and prototypes global to the application
//
//  PLATFORMS:  Windows CE
//
//  COMMENTS:
//
//

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//----------------------------------------------------------------------------
// Constants and Enumerations

typedef enum tagIMAGES {  IMAGE_OPEN, IMAGE_CLOSED, IMAGE_WINDOW, IMAGE_CLASS, IMAGE_DOCUMENT} IMAGES;



typedef struct tagINSERTSTRUCT {
    short               shNumber;
    unsigned short      ushNumber;
    long                lNumber;
    unsigned long       ulNumber;
    TCHAR   *           pString;
    BYTE    *           pBlob;
    DWORD               cbBlob;
} INSERTSTRUCT;

typedef struct tagMODSORT {

    SORTORDERSPEC   SortOrderIn[CEDB_MAXSORTORDER];
    SORTORDERSPEC   SortOrderOut[CEDB_MAXSORTORDER];
    WORD            MaxProps;
    WORD            RemainProps;
    WORD            PropsIndexed;
    HANDLE          hOpenDB;
    TCHAR       *   pszDBName;
    BYTE        *   RemainingProps;

} MODSORT;


//----------------------------------------------------------------------------
// Global Variables

HINSTANCE   g_hInstance;                                   // initproc.c
HWND        hwndCB;
HIMAGELIST  himl;           // handle of the image list
HWND        hEdit;
HWND        g_hwndTreeView;
BOOL        bRemovingProps;

//----------------------------------------------------------------------------
// Prototypes

void WINAPI         ErrorHandlerEx(int, LPTSTR);                               // main.c
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);       // wndproc.c
BOOL WINAPI         InitApplication(HINSTANCE);                                // initproc.c
BOOL WINAPI         InitInstance(HINSTANCE, int);                              // initproc.c
HTREEITEM WINAPI    AddItemToTree(HWND, LPTSTR, HTREEITEM, BOOL, DWORD);

BOOL WINAPI         InitDBViewImageLists(HWND hwndTV);
BOOL WINAPI         InitDBViewItems(HWND hwndTV);

void WINAPI         EnumDbase(HWND hwndTV, HTREEITEM htiParent);

void WINAPI         EnumDbaseProps(HWND hwndTV, HTREEITEM htiParent, DWORD dwOpenHandle);

LRESULT WINAPI      Main_OnCommand(HWND, int, HWND, UINT);
void WINAPI         Main_OnDestroy(HWND);
BOOL WINAPI         Main_OnCreate(HWND, LPCREATESTRUCT);
LRESULT CALLBACK    AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI      Main_OnNotify(HWND, int, LPNMHDR);
void WINAPI         Main_OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);

BOOL CALLBACK       MemoryDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam );
BOOL CALLBACK       NewDBDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam );
BOOL CALLBACK       AddRecDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam );
BOOL CALLBACK       ModIndexDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam );
BOOL CALLBACK       UseIndexDlgProc( HWND  hDlg,UINT  message, WPARAM  wParam, LPARAM  lParam );

void WINAPI         ShowDBInformation( TCHAR * pDBName);
void WINAPI         ShowPropDesc(CEPROPID PropId, DWORD dwOpenHandle, LONG dwCurrentRecord);
void WINAPI         DeleteCurrentDB(HWND hwnd);
void WINAPI         SeekNextRecord(HWND hwnd, DWORD dwSkip);
void WINAPI         AddRecToCurrentDB(HWND hwnd);
void WINAPI         ModifyIndex(HWND hwnd);
void WINAPI         GetIndexesProps( MODSORT * pModIndex);
void WINAPI         OpenIndex(HWND hwnd);


//----------------------------------------------------------------------------
// Macros
#define GETDATABASES    0
#define GETDATAPROPS    1


#define IDC_TREEVIEW    101
#define IDC_EDITCONTROL 102
#define CX_BITMAP        16
#define CY_BITMAP        15
#define NUM_BITMAPS       3

#define TVIS_GCNOCHECK   1        // One-based index to state image list
#define TVIS_GCCHECK     2
#define TVIS_GCSOMECHECK 3

#define   PROP_SHORT        MAKELONG( CEVT_I2, 0) // column 0
#define   PROP_USHORT       MAKELONG( CEVT_UI2, 1) // column 1
#define   PROP_LONG         MAKELONG( CEVT_I4, 2)// column 2
#define   PROP_ULONG        MAKELONG( CEVT_UI4, 3)// column 3
#define   PROP_FILETIME     MAKELONG( CEVT_FILETIME, 4)// column 4
#define   PROP_LPWSTR       MAKELONG( CEVT_LPWSTR, 5)// column 5
#define   PROP_CEBLOB       MAKELONG( CEVT_BLOB, 6)// column 6


#define ErrorHandler() ErrorHandlerEx(__LINE__, TEXT(__FILE__))


#define DB_NEXT_REC 0
#define DB_PREV_REC 1
#define DB_ADD_REC 2



#endif
