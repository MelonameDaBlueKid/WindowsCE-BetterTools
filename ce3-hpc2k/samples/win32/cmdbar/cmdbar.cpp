/*************************************************************************



THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright  1997  Microsoft Corporation.  All Rights Reserved.

module: cmdbar.cpp

Abstract: Simple Windows CE application. Shows some common buttons
on the command bar and how to create, add bitmaps to, and destroy the
commandbar. Also shows InsertMenubar function.

The user can use the menu to select from 3 different sets of buttons
to be displayed from the 2 standard bitmaps added to the commandbar.

Commandbar Functions Used in Cmdbar.cpp :

	// Add addornments, add exit button by default to commandbar. Can also
	// be used to add help and OK buttons by passing CMDBAR_HELP or CMDBAR_OK
	// as second parameter

 	CommandBar_AddAdornments(hwndCB, 0, 0);

									
    // Adds bitmap to commandbar  	
	// Call HINST_COMMCTRL for hInst to use standard buttons in Bitmaps
	// IDB_STD_SMALL_COLOR &IDB_STD_VIEW_COLOR
	CommandBar_AddBitmap( HWND hwndCB, HINSTANCE hInst,
		                 int idBitmap, int iNumImages,
						 int iImageWidth, int ImageHeight )
	
    // Adds the buttons that are declared in the array of buttons pointed to
	// by lpButtons to the commandbar
	CommandBar_AddButtons(HWND hwndCB, UINT nNumButtons,
						  LPTBUTTON lpButtons);

    //Creates CommandBar
	CommandBar_Create(HINSTANCE hInst,HWND hwndParent, int idCmdBar);

    // Destroys a commandbar
    CommandBar_Destroy( hwndCB );

    // Returns handle to menu
    CommandBar_GetMenu( HWND hwndCB, int );
	
    // Inserts Menu idMenu before button with index iButtons on the command bar
	CommandBar_InsertMenubar(HWND hwndCB,HINSTANCE hInst,
		                     WORD idMenu, int iButtons);




Additional Functions:

    CreateWindow
    DefWindowProc
    DestroyWindow
  	DispatchMessage
    GetMessage
    GetStockObject
    GetSystemMetrics
    LoadCursorW
    PostQuitMessage
    RegisterClass
	SendMessage
    ShowWindow
	TranslateMessage
	UpdateWindow
	WinMain
    WndProc

Messages:

	WM_CLOSE
	WM_COMMAND
	WM_CREATE
	WM_DESTROY

***************************************************************************/

#include "cmdbar.h"
#include <commctrl.h>


HINSTANCE hInst = NULL;  // Local copy of hInstance
HWND hwndMain = NULL;    // Handle to Main window returned from CreateWindow
HWND hwndCB =NULL;       // Handle to a commandbar
HMENU hMenu =NULL;       // Handle to a commandbar menu
DWORD dPrevMenu=NULL;    // Handle to the previously checked menu item
enum BUTTONVIEWS { STD, VIEW, MIX };// Value of current command bar view
BUTTONVIEWS buttonview;

const int lBufsize = 80;
TCHAR szAppName[lBufsize];
TCHAR szTitle[lBufsize];

// Array tbSTDButton contains all the buttons of bitmap IDB_STD_SMALL_COLOR

static TBBUTTON tbSTDButton[] = {
	{0,              0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{STD_FILENEW,    IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_FILEOPEN,   IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_FILESAVE,   IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,              0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{STD_CUT,        IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0,  0},
	{STD_COPY,       IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_PASTE,      IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,              0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{STD_UNDO,       IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_REDOW,      IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,              0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{STD_FIND,       IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_REPLACE,    IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_DELETE,     IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,              0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{STD_PRINTPRE,   IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_PRINT,      IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,              0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{STD_PROPERTIES, IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_HELP,       IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,              0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0}
};

TCHAR * szSmallTips[] = {
                    NULL, //menu skipping
	                TEXT("STD_FILENEW"),
	                TEXT("STD_FILEOPEN"),
	                TEXT("STD_FILESAVE"),
	                TEXT("STD_CUT"),
	                TEXT("STD_COPY"),
	                TEXT("STD_PASTE"),
	                TEXT("STD_UNDO"),
	                TEXT("STD_REDOW"),
	                TEXT("STD_FIND"),
	                TEXT("STD_REPLACE"),
	                TEXT("STD_DELETE"),
	                TEXT("STD_PRINTPRE"),
	                TEXT("STD_PRINT"),
	                TEXT("STD_PROPERTIES"),
	                TEXT("STD_HELP"),
};

UINT    uNumSmallTips = 16;

// Array tbVIEWButton contains all the buttons of bitmap IDB_VIEW_SMALL_COLOR
static TBBUTTON tbVIEWButton[] = {
	{VIEW_SORTNAME ,	IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_SORTSIZE,     IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_SORTDATE,		IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_SORTTYPE,		IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,					0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{VIEW_DETAILS,		IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_LIST,			IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_SMALLICONS,	IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_LARGEICONS,	IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,					0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{VIEW_PARENTFOLDER, IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_NETCONNECT,   IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_NETDISCONNECT,IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_NEWFOLDER,	IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1}

};

TCHAR * szViewTips[] = {
	NULL, /// skip menu
	TEXT("VIEW_SORTNAME"),
	TEXT("VIEW_SORTSIZE"),
	TEXT("VIEW_SORTDATE"),
	TEXT("VIEW_SORTTYPE"),
	TEXT("VIEW_DETAILS"),
	TEXT("VIEW_LIST"),
	TEXT("VIEW_SMALLICONS"),
	TEXT("VIEW_LARGEICONS"),
	TEXT("VIEW_PARENTFOLDER"),
	TEXT("VIEW_NETCONNECT"),
	TEXT("VIEW_NETDISCONNECT"),
	TEXT("VIEW_NEWFOLDER"), 

};

UINT    uNumViewTips = 13;

    // Array tbMIXButtons contains 8 buttons from IDB_STD_SMALL_COLOR and 6 from
    // IDB_VIEW_SMALL_COLOR. The size of the first bitmap added with the funct-
    // ion Commandbar_AddBitmap must be added to the index value of the buttons
    // of the second bitmap added to show the proper new index value of the
    // buttons added with the second bitmap.
static TBBUTTON tbMIXButton[] = {
	{0,                 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{STD_FILENEW,       IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_FILEOPEN,      IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_FILESAVE,      IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,                 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{STD_CUT,           IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0,  0},
	{STD_COPY,          IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_PASTE,         IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,                 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{STD_UNDO,          IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{STD_REDOW,         IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,                 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{VIEW_SORTNAME + 15,IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_SORTSIZE + 15,IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_SORTDATE + 15,IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_SORTTYPE + 15,IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0,                 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{VIEW_DETAILS + 15, IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{VIEW_LIST + 15,    IDC_NONE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
};


TCHAR * szMIXTips[] = {
	NULL,
	TEXT("STD_FILENEW"),
	TEXT("STD_FILEOPEN"),
	TEXT("STD_FILESAVE"),
	TEXT("STD_CUT"),
	TEXT("STD_COPY"),
	TEXT("STD_PASTE"),
	TEXT("STD_UNDO"),
	TEXT("STD_REDOW"),
	TEXT("VIEW_SORTNAME + 15"),
	TEXT("VIEW_SORTSIZE + 15"),
	TEXT("VIEW_SORTDATE + 15"),
	TEXT("VIEW_SORTTYPE + 15"),
	TEXT("VIEW_DETAILS + 15"),
	TEXT("VIEW_LIST + 15"),
};

UINT    uNumMixTips = 15;
/**************************************************************************************

   WndProc

  *************************************************************************************/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    LRESULT	lResult = TRUE;

	switch(msg)
	{

    // Create Commandbar with buttons from bitmap IDB_STD_SMALL_COLOR.

	case WM_CREATE:
		{
		hwndCB = CommandBar_Create(hInst, hwnd, 1);

        CommandBar_AddToolTips(	hwndCB,	uNumSmallTips,szSmallTips);

		CommandBar_AddBitmap(hwndCB, HINST_COMMCTRL, IDB_STD_SMALL_COLOR,
							 15, 16, 16);

		CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);

        // Add buttons in tbSTDButton to Commandbar
		CommandBar_AddButtons(hwndCB, sizeof(tbSTDButton)/sizeof(TBBUTTON),
							  tbSTDButton);
		
        // Add exit button
		CommandBar_AddAdornments(hwndCB, 0, 0);

		// Set initial view
		buttonview = STD;

		// Get menu handle
		hMenu=CommandBar_GetMenu(hwndCB,0);

		// Set dPrevMenu to default
		dPrevMenu= IDM_SHOW_STD;

		// Check default menu item
		CheckMenuItem(hMenu,IDM_SHOW_STD,MF_CHECKED);

 		break;
		}		
	
	case WM_COMMAND:
	   switch (GET_WM_COMMAND_ID(wp,lp))
	   {
	      case IDM_SHOW_STD:

              // If current buttonview is not STD, then change commandbar
			  if ( buttonview != STD )
			  {
                 CommandBar_Destroy( hwndCB );

	             hwndCB = CommandBar_Create(hInst, hwnd, 1);
				 CommandBar_AddToolTips(	hwndCB,	uNumSmallTips,szSmallTips);

	             CommandBar_AddBitmap(hwndCB, HINST_COMMCTRL, IDB_STD_SMALL_COLOR,
								 15, 16, 16);

	             CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);

	             CommandBar_AddButtons(hwndCB, sizeof(tbSTDButton)/sizeof(TBBUTTON),
								  tbSTDButton);

				 CommandBar_AddAdornments(hwndCB, 0, 0);

                 SendMessage (hwnd, WM_PAINT,NULL, NULL );

				 buttonview = STD;

				 hMenu=CommandBar_GetMenu(hwndCB,0);

                 // Uncheck previous menu item
				 CheckMenuItem(hMenu,dPrevMenu,MF_UNCHECKED);
				
                 // Check new menu item
				 CheckMenuItem(hMenu,IDM_SHOW_STD,MF_CHECKED);

			  }

			  break;

		  case IDM_SHOW_VIEW:

             // If current buttonview is not VIEW, then change commandbar
		     if ( buttonview != VIEW )
			 {
                CommandBar_Destroy( hwndCB );
				
				hwndCB = CommandBar_Create(hInst, hwnd, 1);

				CommandBar_AddToolTips(	hwndCB,	uNumViewTips,szViewTips);
				CommandBar_AddBitmap(hwndCB, HINST_COMMCTRL,
					                 IDB_VIEW_SMALL_COLOR,
								     12, 16, 16);

                CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);

                CommandBar_AddButtons(hwndCB,
					                  sizeof(tbVIEWButton)/sizeof(TBBUTTON),
								      tbVIEWButton);

                CommandBar_AddAdornments(hwndCB, 0, 0);

                SendMessage (hwnd, WM_PAINT,NULL, NULL );

                buttonview = VIEW;

                hMenu=CommandBar_GetMenu(hwndCB,0);

                CheckMenuItem(hMenu,dPrevMenu,MF_UNCHECKED);
				
                CheckMenuItem(hMenu,IDM_SHOW_VIEW,MF_CHECKED);

             }
             break;

          case IDM_SHOW_MIX:
             // If current buttonview is not MIX, then change commandbar
             if ( buttonview != MIX )
             {
                CommandBar_Destroy( hwndCB );
                hwndCB = CommandBar_Create(hInst, hwnd, 1);
				CommandBar_AddToolTips(	hwndCB,	uNumMixTips,szMIXTips);
                CommandBar_AddBitmap(hwndCB, HINST_COMMCTRL,
					                 IDB_STD_SMALL_COLOR,
								     15, 16, 16);
                CommandBar_AddBitmap(hwndCB, HINST_COMMCTRL,
					                 IDB_VIEW_SMALL_COLOR,
								      12, 16, 16);

                CommandBar_InsertMenubar(hwndCB, hInst, IDM_MAIN_MENU, 0);

                CommandBar_AddButtons(hwndCB,
					                  sizeof(tbMIXButton)/sizeof(TBBUTTON),
								      tbMIXButton);

                CommandBar_AddAdornments(hwndCB, 0, NULL);

				SendMessage (hwnd, WM_PAINT,NULL, NULL );

                buttonview = MIX;

                hMenu=CommandBar_GetMenu(hwndCB,0);

                CheckMenuItem(hMenu,dPrevMenu,MF_UNCHECKED);

                CheckMenuItem(hMenu,IDM_SHOW_MIX,MF_CHECKED);

             }

             break;


          case IDM_EXIT:
             SendMessage(hwnd, WM_CLOSE, 0, 0);
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

#ifdef _WIN32_WCE_EMULATION
	hwndMain = CreateWindow(szAppName,						
                			szTitle,
						    WS_POPUP,
							0,0,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL, NULL, hInstance, NULL );
#else
hwndMain = CreateWindow(szAppName,						
                			szTitle,
						    WS_VISIBLE,
							0,0,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL, NULL, hInstance, NULL );
#endif


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

	//Load strings
	LoadString(hInstance,IDS_APPNAME, szAppName,sizeof(szAppName)/sizeof(TCHAR));
	LoadString(hInstance,IDS_APPNAME, szTitle,sizeof(szTitle)/sizeof(TCHAR));

	wc.style = CS_HREDRAW | CS_VREDRAW ;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.hCursor = NULL;// No cursor if target is not NT
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

	if ( !hPrevInstance )
	{
		if ( !InitApplication ( hInstance ) )

		{ return (FALSE); }

	}

	if ( !InitInstance( hInstance, CmdShow )  )
	{
		return (FALSE);
	}


	while ( GetMessage( &msg, NULL, 0,0 ) == TRUE )
	{
		TranslateMessage (&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

// END CMDBAR.CPP

