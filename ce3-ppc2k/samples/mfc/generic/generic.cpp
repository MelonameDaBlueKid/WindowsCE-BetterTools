// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "resource.h"

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 214
#define SQUARE_SIZE (WINDOW_WIDTH / 6)
#define LOWER_LEFT 20

// Define a window class derived from CFrameWnd
class CMainWindow : public CFrameWnd
{
private:
	CPoint m_LowerLeft[LOWER_LEFT];
	WORD m_nLowerLefts;
	BOOL m_bMouseDown;
	int m_nCaptionSize;

public:
	CMainWindow();

	//{{AFX_MSG( CMainWindow )
	afx_msg void OnFileExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CAboutDlg: public CDialog
{
public:
	CAboutDlg::CAboutDlg() 
	{CDialog(IDD_ABOUT);}
};

// Define an application class derived from CWinApp
class CGenericApp : public CWinApp
{
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};				  

//////////////////////////////////////////////////////////////////////////
//  Implementation
//////////////////////////////////////////////////////////////////////////

// Create the application's main window and perform initialization chores
BOOL CGenericApp::InitInstance()
{

	int ClientWidth;
	int ClientHeight;

	m_pMainWnd = new CMainWindow();
	m_pMainWnd->ShowWindow( m_nCmdShow );
	m_pMainWnd->UpdateWindow();

	CRect rect;
	m_pMainWnd->GetClientRect(&rect);
	ClientWidth = rect.right;
	ClientHeight = rect.bottom;
	m_pMainWnd->InvalidateRect(rect);

	return (TRUE);
}

// CGenericApp's contructor initializes and runs the app
CGenericApp goGenApp;

CMainWindow::CMainWindow()
: m_bMouseDown(FALSE),
m_nLowerLefts(0),
m_nCaptionSize(GetSystemMetrics(SM_CYCAPTION))
{
	LoadFrame(IDR_MAINFRAME);

	// For MFCCE 2.0 and earlier, a command bar was created during
	// the CFrameWnd creation. For MFCCE 2.01 and later, a command bar 
	// is automatically created for you during the call to AddAdornments().
	AddAdornments(0);
}

// CMainWindow message map:
BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
	//{{AFX_MSG_MAP( CMainWindow )
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CGenericApp message map:
BEGIN_MESSAGE_MAP( CGenericApp, CWinApp )
	//{{AFX_MSG_MAP( CGenericApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_EXIT, CWinApp::OnAppExit)
END_MESSAGE_MAP()

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pos = point;
	int ClientWidth;
	int ClientHeight;

	CRect rect;
	GetClientRect(&rect);
	ClientWidth = rect.right;
	ClientHeight = rect.bottom;

	// Confirm that pos is not on command bar
#if defined (_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)   // For Rapier, you don't have the command bar
	if (pos.y > m_nCaptionSize)
#else
	if (pos.y > m_poCommandBar->GetHeight())
#endif
	{
		if (pos.x < (ClientWidth / 2))
		{
			if (pos.y < (ClientHeight / 2))
			{
				// Upper left quadrant
				// Exit the application
				SendMessage(WM_CLOSE);
				return;
			}
			else
			{
				// Lower left quadrant
				// Change Z Order of window to 'bottom'
				SetWindowPos(&wndBottom, 0, 0, 0, 0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}
		}
		else
		{
			if (pos.y < (ClientHeight / 2))
			{
				// Upper right quadrant
				if (!m_bMouseDown)
				{
					SetCapture();
					m_bMouseDown = TRUE;
				}
				else
				{
					m_bMouseDown = FALSE;
					ReleaseCapture();
				}
			}
			else
			{
				// Lower right quadrant
				if (m_nLowerLefts < LOWER_LEFT)
				{
					if (this != GetFocus())
						SetFocus();

					m_LowerLeft[m_nLowerLefts].x = pos.x;
					m_LowerLeft[m_nLowerLefts].y = pos.y;
					m_nLowerLefts++;
					// Repaint window
					CRect rect;
					GetClientRect(&rect);
					InvalidateRect(rect);
				}
			}
		}
	}

	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int ClientWidth;
	int ClientHeight;

	CRect rect;
	GetClientRect(&rect);
	ClientWidth = rect.right;
	ClientHeight = rect.bottom;

	CPoint line[5];

	// Paints a vertical line that bisects the window
	line[0] = CPoint(ClientWidth / 2, 0);
	line[1] = CPoint(ClientWidth / 2, ClientHeight);
	dc.Polyline(line, 2);

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
	// Paints a horizontal line that bisects the window
	line[0] = CPoint(0, (ClientHeight) / 2);
	line[1] = CPoint(ClientWidth, (ClientHeight) / 2);
	dc.Polyline(line, 2);
#else
	// Paints a horizontal line that bisects the window
	line[0] = CPoint(0, (ClientHeight + m_nCaptionSize) / 2);
	line[1] = CPoint(ClientWidth - 1, (ClientHeight + m_nCaptionSize) / 2);
	dc.Polyline(line, 2);
#endif

	// Paint any small squares at the point captured
	// (See OnLButtonDown for lower right quadrant)
	for (WORD i = 0; i < m_nLowerLefts; i++)
	{
		line[3].x = line[4].x = line[0].x = m_LowerLeft[i].x;
		line[1].y = line[4].y = line[0].y = m_LowerLeft[i].y;
		
		line[2].x = line[1].x = (line[0].x - SQUARE_SIZE);
		line[2].y = line[3].y = (line[0].y - SQUARE_SIZE);

		dc.Polyline(line, 5);
	}
}

