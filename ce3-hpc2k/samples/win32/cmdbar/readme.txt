Sample: CMDBAR.CPP

CMDBAR is a simple Windows CE windows application. It shows some common buttons
on the command bar and how to create, add bitmaps to, and destroy the
commandbar. Also shows InsertMenubar function.

The user can use the menu to select from 3 different sets of buttons
to be displayed from the 2 standard bitmaps added to the commandbar.

Commandbar Functions Used in Cmdbar.cpp :

	// Add adornments, add exit button by default to commandbar. Can also
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

