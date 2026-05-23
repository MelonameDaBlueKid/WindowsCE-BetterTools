Sample:

	GENERIC

Abstract:

This sample contains the source to a generic Windows CE application, which will be used to illustrate part of the functionality of WIN32_WCE.  The application creates a window and draws a horizontal and vertical line.  Each line bisect the client area creating four equal quadrants. WndProc processes the mouseclicks depending of which quadrant the mouse was in
when it was clicked.

	TopLeft quadrant     : Exits application.
	TopRight quadrant    : Cycles through the color palette.
	BottomLeft quadrant  : Changes Z order of window.
	BottomRight quadrant : Draws square the size of 1/6 the window width with
	                       the lower left corner at the point of mouseclick.

	
Functions:

	BeginPaint
	CreateWindow
	DefWindowProc
	DestroyWindow
	DispatchMessage
	DrawText
	EndPaint
	FillRect
	GetDC
	GetMessage
	GetStockObject
	GetStockPen						
	GetSystemMetrics
	GetWindowRect
	POINTSTOPOINT
	Polyline
	PostQuitMessage
	RegisterClass
	ReleaseCapture
	ReleaseDC
	SelectPen						
	SetCapture
	SetFocus
	SetWindowPos
	ShowWindow
	TranslateMessage
	UpdateWindow
	WinMain
	WndProc

Messages:

	WM_DESTROY
	WM_LBUTTONDOWN
	WM_PAINT
