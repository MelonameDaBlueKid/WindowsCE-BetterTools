// HttpDlg.cpp : implementation file
//

#include "stdafx.h"

#include "Http.h"
#include "HttpDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum {
	kErrorMin	=0x10000000,
	kError1		=0x10000001,
	kError2		=0x10000010
};

/////////////////////////////////////////////////////////////////////////////
// CHttpApp

BEGIN_MESSAGE_MAP(CHttpApp, CWinApp)
	//{{AFX_MSG_MAP(CHttpApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHttpApp construction

CHttpApp::CHttpApp(LPCTSTR lpszAppName)
	: CWinApp(lpszAppName)
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHttpApp object

// WCE MFC apps require the application name to be specified in the CWinApp 
// constructor. A help contents filename may also be specified.

CHttpApp theApp(_T("Http MFC Sample"));

/////////////////////////////////////////////////////////////////////////////
// CHttpApp initialization

BOOL CHttpApp::InitInstance()
{
	CHttpDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHttpSession object

// Http wants to use its own derivative of the CHttpSession class
// just so it can implement an OnStatusCallback() override.

CMyHttpSession::CMyHttpSession(LPCTSTR pszAppName, DWORD dwContext, int nMethod)
	: CInternetSession(pszAppName, dwContext, nMethod)
{
}

void CMyHttpSession::OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus,
	LPVOID /* lpvStatusInfomration */, DWORD /* dwStatusInformationLen */)
{
	CHttpDlg* pDlg = (CHttpDlg*)dwContext;
	if(!pDlg)
		return;

	switch(dwInternetStatus)
	{
		case INTERNET_STATUS_RESOLVING_NAME: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_IPLOOKING));
			break;
		case INTERNET_STATUS_NAME_RESOLVED: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_IPFOUND));
			break;
		case INTERNET_STATUS_CONNECTING_TO_SERVER: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_CONNECTING));
			break;
		case INTERNET_STATUS_CONNECTED_TO_SERVER: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_CONNECTED));
			break;
		case INTERNET_STATUS_SENDING_REQUEST: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_REQUEST));
			break;
		case INTERNET_STATUS_REQUEST_SENT: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_SENT));
			break;
		case INTERNET_STATUS_RECEIVING_RESPONSE: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_WAITING));
			break;
		case INTERNET_STATUS_RESPONSE_RECEIVED: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_RECEIVED));
			break;
		case INTERNET_STATUS_CLOSING_CONNECTION: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_CLOSING));
			break;
		case INTERNET_STATUS_CONNECTION_CLOSED: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_CLOSED));
			break;
		case INTERNET_STATUS_HANDLE_CREATED: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_CONNECTED2));
			break;
		case INTERNET_STATUS_HANDLE_CLOSING: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_DISCONNECTED));
			break;
		case INTERNET_STATUS_REQUEST_COMPLETE: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_COMPLETED));
			break;
		case INTERNET_STATUS_REDIRECT: 
			pDlg->SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_REDIRECTED));
			break;
	}
}

void ThrowHttpException(int nCode)
{
	CInternetException* pEx = new CInternetException(nCode);
	THROW(pEx);
}


/////////////////////////////////////////////////////////////////////////////
// CHttpDlg dialog

CHttpDlg::CHttpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHttpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHttpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHttpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHttpDlg, CDialog)
	//{{AFX_MSG_MAP(CHttpDlg)
	ON_BN_CLICKED(ID_DOWNLOADPAGE, OnDownloadpage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHttpDlg message handlers

BOOL CHttpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	SetDlgItemText(IDC_ADDRESS, CString((LPCTSTR)IDS_DEFAULT));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHttpDlg::OnDownloadpage() 
{
	TCHAR szAddress[INTERNET_MAX_HOST_NAME_LENGTH];
	GetDlgItemText(IDC_ADDRESS, szAddress, INTERNET_MAX_HOST_NAME_LENGTH - 1);

	SetDlgItemText(IDC_MESSAGE, _T(""));
	SetDlgItemText(IDC_EDIT_PAGE, _T(""));

	DownloadPage(szAddress);
}

int CHttpDlg::DownloadPage(LPTSTR szAddress)
{
	int   nRetCode = 0;
	DWORD dwAccessType = PRE_CONFIG_INTERNET_ACCESS;
	const TCHAR szHeaders[] = _T("Accept: text/*\r\nUser-Agent: MFC_Http_Sample\r\n");
	DWORD dwHttpRequestFlags = INTERNET_FLAG_NO_AUTO_REDIRECT;
	BOOL  bSuccess = TRUE;

	CMyHttpSession session(CString((LPCTSTR)IDS_HTTPAPP), (DWORD)this, dwAccessType);
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	TRY
	{
		// check to see if this is a reasonable URL
		CString strServerName;
		CString strObject;
		INTERNET_PORT nPort;
		DWORD dwServiceType;

		if (!AfxParseURL(szAddress, dwServiceType, strServerName, strObject, nPort) || 
			dwServiceType != INTERNET_SERVICE_HTTP)
		{
			SetDlgItemText(IDC_EDIT_PAGE, CString((LPCTSTR)IDS_ERROR1));
			ThrowHttpException(kError1);
		}

		session.EnableStatusCallback(TRUE);

		pServer = session.GetHttpConnection(strServerName, nPort);

		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject, NULL, (DWORD)this, NULL, NULL, dwHttpRequestFlags);
		pFile->AddRequestHeaders(szHeaders);
		pFile->SendRequest();

		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);

		if (dwRet == HTTP_STATUS_DENIED)
    {
      MessageBox (L"Access to the secured http site is denied!", L"Error", MB_OK);
			return 0;
    }

		CString strNewLocation;
		pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, strNewLocation);

		// were we redirected?
		// these response status codes come from WININET.H

		if (dwRet == HTTP_STATUS_MOVED ||
			dwRet == HTTP_STATUS_REDIRECT ||
			dwRet == HTTP_STATUS_REDIRECT_METHOD)
		{
			CString strNewLocation;
			pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, strNewLocation);

			int nPlace = strNewLocation.Find(_T("Location: "));
			if (nPlace == -1)
			{
				SetDlgItemText(IDC_EDIT_PAGE, CString((LPCTSTR)IDS_ERROR2) );
				ThrowHttpException(kError2);
			}

			strNewLocation = strNewLocation.Mid(nPlace + 10);
			nPlace = strNewLocation.Find('\n');
			if (nPlace > 0)
				strNewLocation = strNewLocation.Left(nPlace);

			// close up the redirected site

			pFile->Close();
			delete pFile;
			pServer->Close();
			delete pServer;

			CString csMsg = CString((LPCTSTR)IDS_CAUTION) + strNewLocation;
			SetDlgItemText(IDC_MESSAGE, csMsg);

			// figure out what the old place was
			if (!AfxParseURL(strNewLocation, dwServiceType, strServerName, strObject, nPort))
			{
				SetDlgItemText(IDC_EDIT_PAGE, CString((LPCTSTR)IDS_ERROR3));
				ThrowHttpException(kError2);
			}

			if (dwServiceType != INTERNET_SERVICE_HTTP)
			{
				SetDlgItemText(IDC_EDIT_PAGE, CString((LPCTSTR)IDS_ERROR4));
				ThrowHttpException(kError2);
			}

			// try again at the new location
			pServer = session.GetHttpConnection(strServerName, nPort);
			pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
				strObject, NULL, (DWORD)this, NULL, NULL, dwHttpRequestFlags);
			pFile->AddRequestHeaders(szHeaders);
			pFile->SendRequest();

			pFile->QueryInfoStatusCode(dwRet);
			if (dwRet != HTTP_STATUS_OK)
				ThrowHttpException(kError2);
		}

		TCHAR* szWEBPage = new TCHAR[MAX_WEBPAGE_SIZE+1];
		if(szWEBPage)
		{
			szWEBPage[0] = L'\0';

			TCHAR* sz     = new TCHAR[BUFFER_SIZE+1];
			TCHAR* szwBuf = new TCHAR[(BUFFER_SIZE+1)*2];

			sz[0] = L'\0';
			szwBuf[0] = L'\0';
			int n = 0;
			pFile->SetReadBufferSize(BUFFER_SIZE*2);
			while (pFile->ReadString(sz, BUFFER_SIZE))
			{
				wce_AsciiToWide(szwBuf, (const char*)sz);

				n += _tcslen(szwBuf);
				if(n >= MAX_WEBPAGE_SIZE)
					break;
				_tcscat(szWEBPage, szwBuf);
			}
			delete [] sz;
			delete [] szwBuf;
			SetDlgItemText(IDC_EDIT_PAGE, szWEBPage);
		}

		delete [] szWEBPage;
		pFile->Close();
		pServer->Close();
	}
	CATCH (CInternetException,  pEx)
	{
		// catch things wrong with parameters, etc
		if (pEx->m_dwError < kErrorMin)
		{
			TCHAR szError[MAX_PATH]=TEXT("\0");
			pEx->GetErrorMessage(szError,MAX_PATH,NULL);
			SetDlgItemText(IDC_EDIT_PAGE, szError);			
		}
		bSuccess = FALSE;
	}
	AND_CATCH (CMemoryException,  pMemory)
	{
		// catch things wrong with memory
		SetDlgItemText(IDC_EDIT_PAGE,CString((LPCTSTR)IDS_MEMORYEXCEPTION));
		pMemory->Delete();
		bSuccess = FALSE;
	}
	END_CATCH_ALL

	if (pFile != NULL)
		delete pFile;
	if (pServer != NULL)
		delete pServer;
	session.Close();

	if(bSuccess)
		SetDlgItemText(IDC_MESSAGE, CString((LPCTSTR)IDS_DOWNLOADED));

	return nRetCode;
}

