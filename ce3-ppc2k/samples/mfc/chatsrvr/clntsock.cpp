// clntsock.cpp : implementation of the CClientSocket class
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
#include "clntsock.h"
#include "srvrdoc.h"
#include "msg.h"

/////////////////////////////////////////////////////////////////////////////
// CClientSocket Construction

#if defined(_WIN32_WCE)
CClientSocket::CClientSocket(CServerDoc* pDoc, PURPOSE_E iPurpose) :
	CCeSocket(iPurpose)
#else // _WIN32_WCE
CClientSocket::CClientSocket(CServerDoc* pDoc)
#endif // _WIN32_WCE
{
	m_pDoc = pDoc;
	m_nMsgCount = 0;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CClientSocket Operations

void CClientSocket::Init()
{
	m_pFile       = new CSocketFile(this);
	m_pArchiveIn  = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
}

void CClientSocket::Abort()
{
	if (m_pArchiveOut != NULL)
	{
		m_pArchiveOut->Abort();
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
	}
}

void CClientSocket::SendMsg(CMsg* pMsg)
{
#if defined(_WIN32_WCE)
	if ((m_hSocket == INVALID_SOCKET) || (FromHandle(m_hSocket) == NULL))
		return;
#endif // _WIN32_WCE

	if (m_pArchiveOut != NULL)
	{
		pMsg->Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}

void CClientSocket::ReceiveMsg(CMsg* pMsg)
{
	pMsg->Serialize(*m_pArchiveIn);
}

/////////////////////////////////////////////////////////////////////////////
// CClientSocket Overrablide callbacks

void CClientSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	m_pDoc->ProcessPendingRead(this);
}


/////////////////////////////////////////////////////////////////////////////
// 
#if defined(_WIN32_WCE)
void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
}
#endif // _WIN32_WCE


/////////////////////////////////////////////////////////////////////////////
// CSocket Implementation

CClientSocket::~CClientSocket()
{
	if (m_pArchiveOut != NULL)
		delete m_pArchiveOut;

	if (m_pArchiveIn != NULL)
		delete m_pArchiveIn;

	if (m_pFile != NULL)
		delete m_pFile;
}

#ifdef _DEBUG
void CClientSocket::AssertValid() const
{
	CSocket::AssertValid();
}

void CClientSocket::Dump(CDumpContext& dc) const
{
	CSocket::Dump(dc);
}
#endif //_DEBUG

IMPLEMENT_DYNAMIC(CClientSocket, CSocket)
