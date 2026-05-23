// CCheckRecord implementation
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
#include "chkrec.h"
#include "resource.h"

CCheckRecord::CCheckRecord() 
{
	m_dwCents = 0;
	m_szPayTo[0] = '\0';
	m_szDate[0] = '\0';
	m_szMemo[0] = '\0';
}

void CCheckRecord::Reset() 
{ 
	m_dwCents = 0; 
	m_szPayTo[0] = '\0';
	m_szDate[0] = '\0'; 
	m_szMemo[0] = '\0'; 
}

void CCheckRecord::GetCheck(DWORD dwCents, CString& strPayTo,
	CString& strDate, CString& strMemo)
{ 
	dwCents = m_dwCents; 
	strPayTo = m_szPayTo;
	strDate = m_szDate; 
	strMemo = m_szMemo;
}

void CCheckRecord::SetCheck(DWORD dwCents, CString strPayTo,
	CString strDate, CString strMemo)
{	
	m_dwCents = dwCents;
	_tcsncpy(m_szPayTo, strPayTo, sizeof(m_szPayTo)/sizeof(TCHAR) - 1);
	_tcsncpy(m_szDate, strDate, sizeof(m_szDate)/sizeof(TCHAR) - 1);
	_tcsncpy(m_szMemo, strMemo, sizeof(m_szMemo)/sizeof(TCHAR) - 1);
	m_szPayTo[39] = '\0';
	m_szDate[9] = '\0';
	m_szMemo[39] = '\0';
}

BOOL CCheckRecord::IsEmpty()
{
	return ((m_dwCents == 0) && (m_szPayTo[0] == '\0') &&
		(m_szDate[0] == '\0') && (m_szMemo[0] == '\0'));
}

BOOL CCheckRecord::IsSame(DWORD dwCents, CString strPayTo,
	CString strDate, CString strMemo)
{
	return ((m_dwCents == dwCents) && (_tcscmp(m_szPayTo, strPayTo) == 0) &&
		(_tcscmp(m_szDate, strDate) == 0) && (_tcscmp(m_szMemo, strMemo) == 0));
}

// CCheckBookFile implementation
CCheckBookFile::CCheckBookFile()
{
	m_strFileName = _T("");
	m_nRecordLength = 0;
	m_nRecordCount = 0;
}

CCheckBookFile::~CCheckBookFile()
{
	if(IsFileOpen())
    {
        m_file.Close();
    }
}

BOOL CCheckBookFile::New()
{
#if defined(_WIN32_WCE_PSPC)
	CFileDialog dlg(FALSE, NULL, TEXT("\\My Documents\\NewFile"), OFN_CREATEPROMPT | OFN_HIDEREADONLY, NULL, NULL);
#else
	CFileDialog dlg(FALSE, _T("chb"), NULL, OFN_CREATEPROMPT | OFN_HIDEREADONLY, NULL, NULL);
#endif
	
	CString allFilter;
	CString strFilter;
	CString strTitle;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0'; 
	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0'; 
	dlg.m_ofn.nMaxCustFilter++;
	dlg.m_ofn.lpstrFilter = strFilter;
	dlg.m_ofn.lpstrFilter = strFilter;
	strTitle.LoadString(IDS_FILE_NEW);
	dlg.m_ofn.lpstrTitle = strTitle;
	if (dlg.DoModal() == IDCANCEL)
		return FALSE;


	if (m_file.m_hFile != (UINT)CFile::hFileNull)
		m_file.Close();
	if (!m_file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite))
	{
		AfxMessageBox(CString((LPCTSTR)IDS_MESSAGE5));
		// Call open again
		if (!New()) 
			return FALSE;
		else
			return TRUE;
	}

	m_strFileName = dlg.GetPathName();
	m_nRecordLength = sizeof(CCheckRecord);
	m_nRecordCount = m_file.GetLength() / m_nRecordLength;

	return TRUE;
}

BOOL CCheckBookFile::Open()
{
	CFileDialog dlg(TRUE, _T("chb"), NULL, OFN_CREATEPROMPT | OFN_HIDEREADONLY, NULL, NULL);
	
	CString allFilter;
	CString strFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0'; 
	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0'; 
	dlg.m_ofn.nMaxCustFilter++;
	dlg.m_ofn.lpstrFilter = strFilter;
	if (dlg.DoModal() == IDCANCEL)
		return FALSE;

	if (m_file.m_hFile != (UINT)CFile::hFileNull)
		m_file.Close();
	if (!m_file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
	{
		AfxMessageBox(CString((LPCTSTR)IDS_MESSAGE5));
		// Call open again
		if (!Open()) 
			return FALSE;
		else
			return TRUE;
	}

	m_strFileName = dlg.GetPathName();
	m_nRecordLength = sizeof(CCheckRecord);
	m_nRecordCount = m_file.GetLength() / m_nRecordLength;
	return TRUE;
}

BOOL CCheckBookFile::WriteRecord(UINT nPos, CCheckRecord* pRecord)
{
	if (nPos >= m_nRecordCount)
		m_nRecordCount++;
	if(!IsFileOpen())
    {
        return FALSE;
    }
    m_file.Seek(nPos * m_nRecordLength, CFile::begin);
    m_file.Write((void*)pRecord, sizeof(CCheckRecord));
	return TRUE;
}


BOOL CCheckBookFile::ReadRecord(UINT nPos, CCheckRecord* pRecord)
{
	if(!IsFileOpen())
    {
        return FALSE;
    }
	m_file.Seek(nPos * m_nRecordLength, CFile::begin);
	m_file.Read((void*)pRecord, sizeof(CCheckRecord));
	return TRUE;
}

BOOL CCheckBookFile::IsFileOpen()
{
    if(m_file.m_hFile != (UINT)CFile::hFileNull)    
    {
        return TRUE;
    }
    return FALSE;
}
// CCheckBook implementation
CCheckBook::CCheckBook() 
{
	Reset();
}

void CCheckBook::Reset()
{
	m_check.Reset();
	m_fileCheckBook.Reset();
	m_bExists = FALSE;
}

BOOL CCheckBook::New()
{
	BOOL bIsOK = m_fileCheckBook.New();
	if (bIsOK)
	{
		m_bExists = TRUE;	// Not necessarily the opposite
		m_check.Reset();
	}
	return bIsOK;
}

BOOL CCheckBook::Open()
{
	BOOL bIsOK = m_fileCheckBook.Open();
	if (bIsOK)
	{
		m_bExists = TRUE;	// Not necessarily the opposite
		m_check.Reset();
	}
	return bIsOK;
}

CCheckRecord* CCheckBook::GetCheck(int nCheck)
{ 
	m_fileCheckBook.ReadRecord(nCheck - FIRST_CHECK_NO, &m_check);
	return &m_check;
}

int CCheckBook::SetCheck(int nCheck, DWORD dwCents, CString strPayTo,
	CString strDate, CString strMemo)
{
	m_check.SetCheck(dwCents, strPayTo, strDate, strMemo);
	m_fileCheckBook.WriteRecord(nCheck - FIRST_CHECK_NO, &m_check);
	return (m_fileCheckBook.GetRecordCount() + FIRST_CHECK_NO);
}

BOOL CCheckBook::IsCheckEmpty(int nCheck)
{
	GetCheck(nCheck);
	return m_check.IsEmpty();
}

BOOL CCheckBook::IsCheckSame(int nCheck, DWORD dwCents, CString strPayTo,
	CString strDate, CString strMemo)
{
	GetCheck(nCheck);
	return m_check.IsSame(dwCents, strPayTo, strDate, strMemo);
}

