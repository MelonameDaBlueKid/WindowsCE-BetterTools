/*****************************************************************************

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
 ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 PARTICULAR PURPOSE.

 Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.

 MODULE:   Project.cpp

 PURPOSE: CPP source file for "Project" Pocket PC sample application.
		
 DESCRIPTION:
		Projects is a Pocket PC technology for carrying out the file input 
		and output. Projects consists of four dialogs and a small number 
		of API. The functions are for file manipulations. And the dialogs 
		provide users with a set of user interface elements for opening 
		and saving documents. The documents are organized by projects. A 
		file is associated with its project folder and identified by its 
		file name. It has a set of editable attributes that describes 
		various file properties, such as the  location, type, size and date 
		of the last modification. The four dialogs are: "Folder", "Open", 
		"Save As" and "Properties". This sample demonstrates how to open 
		these four dialogs.
		
 COMMENTS: N/A

--****************************************************************************/

#include "project.h"
#include <commctrl.h>
#include <commdlg.h>
#include <projects.h>

HINSTANCE hInst = NULL;  // Local copy of hInstance
HWND hwndMain = NULL;    // Handle to Main window returned from CreateWindow
HWND hwndCB = NULL;      // Handle to a commandbar
HMENU hMenu = NULL;      // Handle to a commandbar menu

TCHAR szAppName[] = TEXT("Project Application");
TCHAR szTitle[] = TEXT("Project");

/**************************************************************************************

   WndProc

 **************************************************************************************/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT	lResult = TRUE;
	TCHAR	szFile[MAX_PATH] = TEXT("\0");
	OPENFILENAME		ofn;
	
	memset( &(ofn), 0, sizeof(ofn));
	ofn.lStructSize	= sizeof(ofn);
	ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;	
    		
	switch(msg)
	{
	case WM_CREATE:
		{
			hwndCB = CommandBar_Create(hInst, hwnd, 1);	
			CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);
		}		
		break;
		
	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wp,lp))
		{
		case IDM_OPENPRJ:
			{
			TCHAR	szFileTitle[MAX_PATH] = TEXT("\0");

			ofn.lpstrTitle = TEXT("Open Folder");
    		ofn.Flags = OFN_PROJECT;		//Open project dialog for Pocket PC.
			ofn.lpstrFileTitle = szFileTitle;
			ofn.nMaxFileTitle = MAX_PATH;	
						
			if (GetOpenFileName(&ofn))	
				ShowInfo(hwnd,ofn.lpstrFile);
				//Add opening project code here.
			break;
			}
		case IDM_OPENFILE:
			ofn.lpstrFilter = TEXT("All (*.*)\0*.*\0");	
   			ofn.lpstrTitle = TEXT("Open File");
    		ofn.Flags = OFN_EXPLORER;

			if (GetOpenFileName(&ofn))	
				ShowInfo(hwnd,ofn.lpstrFile);
				//Add opening file code here.
			break;

		case IDM_SAVEFILE:
			ofn.lpstrFilter = TEXT("Text (*.txt)\0*.txt\0");	
   			ofn.lpstrTitle = TEXT("Save File As");
			ofn.Flags = OFN_HIDEREADONLY; 
			ofn.lpstrDefExt = TEXT("txt");
			
			if (GetSaveFileName(&ofn))	
				ShowInfo(hwnd,ofn.lpstrFile);
				//Add saving file code here.
            break;

		case IDM_PROPERTY:
			//Use GetOpenFileName to choose a file and then use 
			//GetSaveFileName to display its property. 
			ofn.lpstrFilter = TEXT("All (*.*)\0*.*\0");	
   			ofn.lpstrTitle = TEXT("File Property");
    		ofn.Flags = OFN_EXPLORER;

			if (GetOpenFileName(&ofn))	{
				ofn.lpstrTitle = TEXT("Property");
				ofn.Flags = OFN_PROPERTY;		//Open property dialog for Pocket PC.
				GetSaveFileName(&ofn);
			}
            break;
		case IDOK:
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wp, lp);
		}
	break;

	case WM_CLOSE:
       CommandBar_Destroy(hwndCB);
       DestroyWindow(hwnd);
	break;

	case WM_DESTROY:
       PostQuitMessage(0);
	break;

	default:
		lResult = DefWindowProc(hwnd, msg, wp, lp);
	break;
	}
	return (lResult);
}


/****************************************************************************

  InitInstance

*****************************************************************************/

BOOL InitInstance (HINSTANCE hInstance, int CmdShow )
{

	hInst = hInstance;
	hwndMain = CreateWindow(szAppName,						
                	szTitle,
					WS_VISIBLE,
					CW_USEDEFAULT,CW_USEDEFAULT,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					NULL, NULL, hInstance, NULL );

	if ( !hwndMain )		
	{
		return FALSE;
	}
	ShowWindow(hwndMain, CmdShow );
	UpdateWindow(hwndMain);
	return TRUE;
}

/****************************************************************************

   InitApplication

  ****************************************************************************/

BOOL InitApplication ( HINSTANCE hInstance )
{
	WNDCLASS wc;
	BOOL f;

	wc.style = CS_HREDRAW | CS_VREDRAW ;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	
	f = (RegisterClass(&wc));

	return f;
}


/*****************************************************************************

  WinMain

  ***************************************************************************/

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPWSTR     lpCmdLine,
                   int        CmdShow)

{
	MSG msg;
	HWND hPrjWnd = NULL;	
	HACCEL hAccel = NULL;
    
	//Check if Project.exe is running. If it's running then focus on the window
	hPrjWnd = FindWindow(szAppName,	szTitle);	
	if (hPrjWnd) 
	{
		SetForegroundWindow (hPrjWnd);    
		return 0;
	}

	if ( !hPrevInstance )
	{
		if ( !InitApplication ( hInstance ) )
		{ 
			return (FALSE); 
		}

	}
	if ( !InitInstance( hInstance, CmdShow )  )
	{
		return (FALSE);
	}

	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while ( GetMessage( &msg, NULL, 0,0 ) == TRUE )
	{
		if (!TranslateAccelerator(hwndMain,hAccel, &msg)) 
		{
			TranslateMessage (&msg);
			DispatchMessage(&msg);
		}
	}
	return (msg.wParam);
}

// END PROJECT.CPP

