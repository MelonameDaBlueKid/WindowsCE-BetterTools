// Http.h : main header file for the Http application
//

#if !defined(AFX_HTTP_H__E9CAE8B6_9908_11D1_9327_00600820B4FF__INCLUDED_)
#define AFX_HTTP_H__E9CAE8B6_9908_11D1_9327_00600820B4FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define BUFFER_SIZE 1024		// buffer size
#define MAX_WEBPAGE_SIZE 32000	// max WEB page size

/////////////////////////////////////////////////////////////////////////////
// CHttpApp:
//

class CHttpApp : public CWinApp
{
public:
	CHttpApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHttpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
class CMyHttpSession : public CInternetSession
{
public:
	CMyHttpSession(LPCTSTR pszAppName, DWORD dwContext, int nMethod);
	virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus,
		LPVOID lpvStatusInfomration, DWORD dwStatusInformationLen);
};


class CMyHttpException : public CException
{
	DECLARE_DYNCREATE(CMyHttpException)

public:
	CMyHttpException(int nCode = 0);
	~CMyHttpException() { }

	int m_nErrorCode;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_HTTp_H__E9CAE8B6_9908_11D1_9327_00600820B4FF__INCLUDED_)
