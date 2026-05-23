// mtgdivw.cpp : implementation of the CThreadView class
//
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
#include "mtgdi.h"

#include "mtgdidoc.h"
#include "mtgdivw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadView

IMPLEMENT_DYNCREATE(CThreadView, CView)

BEGIN_MESSAGE_MAP(CThreadView, CView)
	//{{AFX_MSG_MAP(CThreadView)
	ON_COMMAND(ID_BALL_NEWBALL, OnNewBall)
	ON_COMMAND(ID_FILE_KILLTHREADS, OnKillThreads)
	ON_WM_DESTROY()
	ON_COMMAND(ID_LINE_NEWLINE, OnNewLine)
	ON_COMMAND(ID_RECT_NEWRECTANGLE, OnNewRectangle)
	ON_COMMAND(ID_BALL_10NEWBALLS, On10NewBalls)
	ON_COMMAND(ID_LINE_10NEWLINES, On10NewLines)
	ON_COMMAND(ID_RECT_10NEWRECTANGLES, On10NewRectangles)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_BALL_25NEWBALLS, On25NewBalls)
	ON_COMMAND(ID_LINE_25NEWLINES, On25NewLines)
	ON_COMMAND(ID_RECT_25NEWRECTANGLES, On25NewRectangles)
	ON_COMMAND(ID_FILE_KILLTHREADSSLOW, OnThreadKillThreadsSlow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadView construction/destruction

CThreadView::CThreadView()
{
	m_pDC = NULL;
}

CThreadView::~CThreadView()
{
}

void CThreadView::UpdateTitle(int nThreads)
{
	if (nThreads == -1)
		nThreads = m_threadList.GetCount();

	CString strCaption;
	if (nThreads != 0)
	{
		CString strFormat; strFormat.LoadString(IDS_CAPTION_FORMAT);
		strCaption.Format(strFormat, nThreads);
	}
	else
 		strCaption.LoadString(IDS_CAPTION_NOTHREADS);

	GetParentFrame()->SetWindowText(strCaption);
}

BOOL CThreadView::StartThread(int ThreadID)
{
	CGDIThread* pThread;
	CPoint Pos(rand()%100,rand()%100);
	CPoint Vel1((rand()%10)+2,(rand()%10)+2); 
	CPoint Vel2((rand()%5)+2,(rand()%5)+2);
	CSize Size(((rand()%60)+20),((rand()%60)+20));
	COLORREF Color;
	
	// Calculate random color
	// For shades of gray, r == g == b
	int r = (rand()%4);
#if (_WIN32_WCE < 101) && !defined(_WIN32_WCE_EMULATION)
	//Note: For os 100, color handled differently on an HPC    
	r = (r!=0) ? (r!=1) ? (r==3) ? 255 : 2 : 1 : 0;
#else
	r = (r!=0) ? (r!=1) ? (r==3) ? 255 : 192 : 128 : 0;
#endif
	Color = RGB(r,r,r);

	if (rand()%2) Vel1.x*=-1;
	if (rand()%2) Vel1.y*=-1;
	if (rand()%2) Vel2.x*=-1;
	if (rand()%2) Vel2.y*=-1;

	switch(ThreadID)
	{
	case 1:
		pThread = new CBallThread(this, 
			m_pDC->GetSafeHdc(), Pos, Vel1, Size, Color);
		break;
	case 2:
		pThread = new CRectThread(this, 
			m_pDC->GetSafeHdc(), Pos, Vel1, Size, Color);
		break;
	case 3:
		pThread = new CLineThread(this, 
			m_pDC->GetSafeHdc(), Pos, Vel1, Vel2, Size, Color);
		break;
	}

	if (pThread == NULL)
		return FALSE;

	ASSERT_VALID(pThread);
	pThread->m_pThreadParams = NULL;

	// Create Thread in a suspended state so we can set the Priority 
	// before it starts getting away from us
	if (!pThread->CreateThread(CREATE_SUSPENDED))
	{
		delete pThread;
		AfxMessageBox(CString((LPCTSTR)IDS_LIMIT));
		return FALSE;  
	}

	// since everything is successful, add the thread to our list
	m_threadList.AddTail(pThread);

	// If you want to make the sample more sprightly, set the thread priority here 
	// a little higher. It has been set at idle priority to keep from bogging down 
	// other apps that may also be running.
	VERIFY(pThread->SetThreadPriority(THREAD_PRIORITY_IDLE));

	// Now the thread can run wild
	pThread->ResumeThread();

	return TRUE;
}

void CThreadView::OnDraw(CDC*)
{
}

/////////////////////////////////////////////////////////////////////////////
// CThreadView diagnostics

#ifdef _DEBUG
void CThreadView::AssertValid() const
{
	CView::AssertValid();
}

void CThreadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CThreadDoc* CThreadView::GetDocument() // non-debug version is inline
{
	return STATIC_DOWNCAST(CThreadDoc, m_pDocument);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThreadView message handlers

void CThreadView::OnNewBall() 
{
	StartThread(1);
	UpdateTitle();
}

void CThreadView::On10NewBalls() 
{
	for (int i = 0; i < 10; i++) 
	{
		if(!StartThread(1))
			break;
		UpdateTitle();
	}
}

void CThreadView::On25NewBalls() 
{
	for (int i = 0; i < 25; i++) 
	{
		if(!StartThread(1))
			break;
		UpdateTitle();
	}
}

void CThreadView::OnNewRectangle() 
{
	StartThread(2);
	UpdateTitle();
}

void CThreadView::On10NewRectangles() 
{
	for (int i = 0; i < 10; i++) 
	{
		if(!StartThread(2))
			break;
		UpdateTitle();
	}
}

void CThreadView::On25NewRectangles() 
{
	for (int i = 0; i < 25; i++) 
	{
		if(!StartThread(2))
			break;
		UpdateTitle();
	}
}

void CThreadView::OnNewLine() 
{
	StartThread(3);
	UpdateTitle();
}

void CThreadView::On10NewLines() 
{
	for (int i = 0 ;i < 10; i++) 
	{
		if(!StartThread(3))
			break;
		UpdateTitle();
	}
}	
	
void CThreadView::On25NewLines() 
{
	for (int i = 0; i < 25; i++) 
	{
		if(!StartThread(3))
			break;
		UpdateTitle();
	}
}

// A preferred method for killing many threads.  Tell them to go away all
// at once, then wait for them all to be scheduled and to terminate
// themselves.  This is much, much faster than the more straight forward
// way of asking just one to terminate, then waiting for it to do so.
// It is also a little bit more complex.

void CThreadView::OnKillThreads() 
{
	// tell all threads to shutdown
	for (POSITION pos = m_threadList.GetHeadPosition(); pos != NULL; )
	{
		CGDIThread* pThread = m_threadList.GetNext(pos);
	#ifdef _WIN32_WCE_EMULATION
		VERIFY(SetEvent(pThread->m_hEventKill));
	#else
		VERIFY(EventModify(pThread->m_hEventKill, EVENT_SET));
	#endif
	}

	// wait for all threads to finish shutdown
	for (int nThreadsLeft = m_threadList.GetCount(); nThreadsLeft != 0; )
	{
		WaitForSingleObject(CGDIThread::m_hAnotherDead, INFINITE);
		Sleep(nThreadsLeft*2);// 200ms for every 100 threads
		nThreadsLeft = 0;
		for (pos = m_threadList.GetHeadPosition(); pos != NULL; )
		{
			CGDIThread* pThread = m_threadList.GetNext(pos);
			if (WaitForSingleObject(pThread->m_hEventDead, 0) == WAIT_TIMEOUT)
				++nThreadsLeft;
		}
		UpdateTitle(nThreadsLeft);
	}

	// delete all thread objects
	while (!m_threadList.IsEmpty())
	{
		CGDIThread* pThread = m_threadList.RemoveHead();
		VERIFY(WaitForSingleObject(pThread->m_hThread, INFINITE) == WAIT_OBJECT_0);
		delete pThread;
	}
	UpdateTitle();

	// invalidate the window since all threads are now gone
	Invalidate();
}

// KillThreadsSlow is much easier to understand since the process of 
// killing a thread is encapsulated in KillThread.  If you get more 
// than 50 threads running, however, you'll notice quite a difference
// between this method and the one above.

void CThreadView::OnThreadKillThreadsSlow() 
{
	// Iterate through the threads killing each
	// KillThread doesn't return until the Thread is dead
	while (!m_threadList.IsEmpty())
	{
		m_threadList.RemoveHead()->KillThread();
		UpdateTitle();
	}

	// Invalidate the window so it blanks the window
	Invalidate();
}

void CThreadView::OnDestroy() 
{
	while (!m_threadList.IsEmpty())
		m_threadList.RemoveHead()->KillThread();

	delete m_pDC;
	m_pDC = NULL;

	CView::OnDestroy();
}

int CThreadView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// m_pDC must be initialized here instead of the constructor
	// because the HWND isn't created until Create is called.
	m_pDC = new CClientDC(this);
	UpdateTitle();

	return 0;
}

void CThreadView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Instead of getting the client rect every time we draw, we only
	// update it when it changes.
	for (POSITION pos = m_threadList.GetHeadPosition(); pos != NULL; )
		m_threadList.GetNext(pos)->UpdateBorder();
}

