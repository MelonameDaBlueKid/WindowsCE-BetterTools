// clntsock.h : interface of the CClientSocket class
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

#ifndef __CLNTSOCK_H__
#define __CLNTSOCK_H__

class CMsg;
class CServerDoc;

#if defined(_WIN32_WCE)
class CClientSocket : public CCeSocket
#else // _WIN32_WCE
class CClientSocket : public CSocket
#endif // _WIN32_WCE
{
	DECLARE_DYNAMIC(CClientSocket);
private:
	CClientSocket(const CClientSocket& rSrc);         // no implementation
	void operator=(const CClientSocket& rSrc);  // no implementation

// Construction
public:
#if defined(_WIN32_WCE)
	CClientSocket(CServerDoc* pDoc, PURPOSE_E iPurpose=FOR_DATA);
#else // _WIN32_WCE
	CClientSocket(CServerDoc* m_pDoc);
#endif // _WIN32_WCE

// Attributes
public:
	int m_nMsgCount;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
	CServerDoc* m_pDoc;
	BOOL IsAborted() { return m_pArchiveOut == NULL; }

// Operations
public:
	void Init();
	void Abort();
	void SendMsg(CMsg* pMsg);
	void ReceiveMsg(CMsg* pMsg);

// Overridable callbacks
protected:
	virtual void OnReceive(int nErrorCode);
#if defined(_WIN32_WCE)
	virtual void OnClose(int nErrorCode);
#endif // _WIN32_WCE

// Implementation
public:
	virtual ~CClientSocket();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif // __CLNTSOCK_H__
