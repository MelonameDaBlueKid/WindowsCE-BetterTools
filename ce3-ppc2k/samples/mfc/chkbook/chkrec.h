// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1999 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __INC_CHKREC_H__
#define __INC_CHKREC_H__

#define FIRST_CHECK_NO 1000
#define NO_OF_CHECKS 100


class CCheckRecord
{
friend class CCheckBookFile;
protected:
	DWORD   m_dwCents;
	TCHAR   m_szPayTo[40];
	TCHAR   m_szDate[10];
	TCHAR   m_szMemo[40];
public:
	CCheckRecord();
	void Reset();

	CCheckRecord* GetCheck() { return this; }
	void GetCheck(DWORD dwCents, CString& strPayTo,
		CString& strDate, CString& strMemo);
	void SetCheck(DWORD dwCents, CString strPayTo,
		CString strDate, CString strMemo);

	DWORD GetCents() { return m_dwCents; }
	void GetPayTo(CString& strPayTo) { strPayTo = m_szPayTo; }
	void GetDate(CString& strDate) { strDate = m_szDate; }
	void GetMemo(CString& strMemo) { strMemo = m_szMemo; }
	
	void SetCents(DWORD dwCents) { m_dwCents = dwCents; }
	void SetPayTo(CString strPayTo) { 		
		_tcsncpy(m_szPayTo, strPayTo, sizeof(m_szPayTo)/sizeof(TCHAR) - 1);
		m_szPayTo[39] = '\0'; }
	void SetDate(CString strDate) { 
		_tcsncpy(m_szDate, strDate, sizeof(m_szDate)/sizeof(TCHAR) - 1);
		m_szDate[9] = '\0'; }
	void SetMemo(CString strMemo) { 
		_tcsncpy(m_szMemo, strMemo, sizeof(m_szMemo)/sizeof(TCHAR) - 1);
		m_szMemo[39] = '\0'; }

	BOOL IsEmpty();
	BOOL IsSame(DWORD dwCents, CString strPayTo,
		CString strDate, CString strMemo);
};

class CCheckBookFile
{
public:
	CString m_strFileName;		// File name information
protected:
	UINT m_nRecordCount;        // count of records in the file
	UINT m_nRecordLength;       // length of fixed-length records
	CFile m_file;				// Current .chb file
public:
	CCheckBookFile();
	~CCheckBookFile();
	UINT GetRecordCount() { return m_nRecordCount; }
	UINT GetRecordLength() { return m_nRecordLength; }
	void IncRecordCount() { m_nRecordCount++; }
	void DelRecordCount() { m_nRecordCount--; }
	void Reset() { m_nRecordCount = 0;
		m_nRecordLength = sizeof(CCheckRecord); if (m_file.m_hFile != -1) m_file.Close();}
	BOOL New();
	BOOL Open();
	BOOL WriteRecord(UINT nPos, CCheckRecord* pRecord);
	BOOL ReadRecord(UINT nPos, CCheckRecord* pRecord);
    BOOL IsFileOpen();
};

class CCheckBook
{
public:
	CCheckBookFile m_fileCheckBook;
protected:
	CCheckRecord m_check;
	BOOL		 m_bExists;
public:
	CCheckBook();

	void Reset();
	CCheckRecord* GetCheck(int nCheck);
	int SetCheck(int nCheck, DWORD dwCents, CString strPayTo,
		CString strDate, CString strMemo);

	BOOL IsCheckEmpty(int nCheck);
	BOOL IsCheckSame(int nCheck, DWORD dwCents, CString strPayTo,
		CString strDate, CString strMemo);
	BOOL New();
	BOOL Open();
	BOOL DoesBookExist() { return m_bExists; }
	int GetNextNewCheckNo() {return (m_fileCheckBook.GetRecordCount() + FIRST_CHECK_NO);}
};

#endif // __INC_CHKREC_H__
