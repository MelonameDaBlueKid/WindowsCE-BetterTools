//--------------------------------------------------------------------
// Microsoft OLE DB Sample OLEDB Simple Provider
// (C) Copyright 1997 Microsoft Corporation.  All Rights Reserved.
//
// module MyOSPObject.cpp | MyOSPObject (OLEDBSimpleProvider) object implementation
//
//

////////////////////////////////////////////////////////
// Includes
//
////////////////////////////////////////////////////////

#include "Common.h"
#include "MyOSPObject.h"
#include <windows.h>
#include <stdlib.h>
#if !defined(UNDER_CE)
#include <stdio.h>
#endif

////////////////////////////////////////////////////////
// MyOSPObject
//
////////////////////////////////////////////////////////

MyOSPObject::MyOSPObject()
{
	//IUnknown
	m_cRef = 0;
	
	//Member variables
	m_rvTable		= NULL;
	m_cRows			= 0;
	m_cColumns		= 0;
	m_szFilePath	= NULL;
}


MyOSPObject::~MyOSPObject()
{
	LONG		i, j;

	// Save the internal table to the data file:
	if (m_szFilePath != NULL)
		saveData();

	// Walk through the internal table.  Free any
	// variants, each row, and finally the table.
	if (m_rvTable != NULL)
	{
		for (i = 0; i <= m_cRows; i++)
		{
			for (j = 1; j <= m_cColumns; j++)
			{
				if (m_rvTable[i][j].vt == VT_BSTR)
					SysFreeString(V_BSTR(&m_rvTable[i][j]));
			}
			CoTaskMemFree(m_rvTable[i]);
		}
		CoTaskMemFree(m_rvTable);
	}

	//Remove all Listeners:
	while(!m_listListeners.IsEmpty())
		m_listListeners.RemoveHead()->Release();

}


HRESULT MyOSPObject::Init(WCHAR* pwszFilePath)
{
	// Store the name of the data file:
	if(m_szFilePath)
	{
		CoTaskMemFree(m_szFilePath);
	}
	
	m_szFilePath = (LPWSTR)CoTaskMemAlloc((wcslen(pwszFilePath) + 1) * sizeof(WCHAR));

	if (!m_szFilePath)
		return E_OUTOFMEMORY;

	wcscpy(m_szFilePath, pwszFilePath);

	// Load the file into a table:
	return loadData();
}


HRESULT MyOSPObject::QueryInterface(REFIID riid, void** ppv)
{
	if (ppv == NULL)
		return E_INVALIDARG;
	
	// IUnknown:
	if (riid == IID_IUnknown)
		*ppv = this;
		
	// OLEDBSimpleProvider:
	else if (riid == IID_OLEDBSimpleProvider)
		*ppv = this;

	// Unsupported:
	else
	{
		*ppv = NULL;								 
		return E_NOINTERFACE;
	}

	SAFE_ADDREF((IUnknown*)*ppv);
	return S_OK;
}

////////////////////////////////////////////////////////
// Routines to load and save table to file
//
////////////////////////////////////////////////////////

HRESULT MyOSPObject::loadData()
{
	FILE *		myOSPFile;
	int			cChar;
	LPWSTR		pwszSeps;		// separator char in file
	LPWSTR		pwszBuffer;		// -> wide character buffer
	LPWSTR		pwszRow;		// -> wide character buffer (position)
	LPWSTR		pwszToken;
	LPWSTR		pwszInput;		// -> input buffer
	LPWSTR		pszPos;
	LONG		i, j;

	// Build the internal array by reading the file:
	// Open for reading.  Fail if the file doesn't exist
	myOSPFile = _wfopen(m_szFilePath, L"r+" );
    if (!myOSPFile)
        return E_FAIL;

	
	
	// Line 1 contains cRows ; cColumns:
	pwszInput = new WCHAR[MAX_INPUT_BUFFER];
	if (NULL == pwszInput || !fgetws(pwszInput, MAX_INPUT_BUFFER, myOSPFile))
	{
        return E_FAIL;
	}
	
		
	pszPos = pwszInput;

	m_cRows = wcstol(pszPos, &pszPos, 10);
	pszPos++;	// consume delimiter
	m_cColumns = wcstol(pszPos, &pszPos, 10);

	// allocate array of size cRows X cColumns:
	m_rvTable = (VARIANT**)CoTaskMemAlloc((m_cRows+1) * sizeof(VARIANT*));
	for (i = 0; i <= m_cRows; i++)
	{
		m_rvTable[i] = (VARIANT*)CoTaskMemAlloc((m_cColumns+1) * sizeof(VARIANT));
	}

	// read the rest of the file and stuff each line into the next row:
	i = 0;
	j = 0;
	pwszSeps = L";";
	pwszBuffer = (BSTR)CoTaskMemAlloc(MAX_WIDE_BUFFER);
	do
	{
		fgetws(pwszInput, MAX_INPUT_BUFFER, myOSPFile);

		pwszRow = pwszInput;

		
		for (j = 1; j <= m_cColumns; j++)
		{
			if (pwszRow == NULL)
			{
				m_rvTable[i][j].vt = VT_NULL;   
				continue;
			}
			cChar = wcscspn(pwszRow, pwszSeps);
			if (cChar)
			{
				pwszToken = wcstok(pwszRow, pwszSeps);
				m_rvTable[i][j].vt = VT_BSTR;
				V_BSTR(&m_rvTable[i][j]) = SysAllocString(pwszToken);
				pwszRow += (cChar+1);
			}
			else
			{
				m_rvTable[i][j].vt = VT_NULL;   
				pwszRow += 1;
			}
		}
		i++;
		if (i > m_cRows)
			break;
	}
	while (!feof(myOSPFile));

	fclose(myOSPFile);
	CoTaskMemFree(pwszBuffer);
	delete [] pwszInput;
	return S_OK;
}


HRESULT MyOSPObject::saveData()
{
	HRESULT		hr = S_OK;
	FILE *		myOSPFile;
	int			nCnt;
	BSTR		pbstrCell;
	LONG		i, j;
	LPWSTR		pwszOutput;		// -> output buffer


	// If the file doesn't already exist, don't save it.
	myOSPFile = _wfopen(m_szFilePath, L"r+");
    if (!myOSPFile)
	{
        return E_FAIL;
	}
	fclose(myOSPFile);


	// Open the file for output:
	// Truncate the file on open for complete rewrite
	myOSPFile = _wfopen(m_szFilePath, L"w+");
    if (!myOSPFile)
	{
        return E_FAIL;
	}

	pwszOutput = new WCHAR[MAX_OUTPUT_BUFFER+1];
	
	// Write the first line containing "rows ; columns":
	wsprintf(pwszOutput, L"%li;%li\n", m_cRows, m_cColumns);
	
	fputws(pwszOutput, myOSPFile);
	fflush(myOSPFile);

	// Write the columns of each row on a line:
	for (i = 0; i <= m_cRows && hr == S_OK; i++)
	{
		nCnt = 0;
		for (j = 1; j <= m_cColumns; j++)
		{
			if (m_rvTable[i][j].vt == VT_NULL)
			{
				if ((nCnt + 1) >= MAX_OUTPUT_BUFFER)
				{
					hr = DB_E_DATAOVERFLOW;
					break;
				}
				nCnt += wsprintf(pwszOutput+nCnt, L";");
			}
			else
			{
				pbstrCell = V_BSTR(&m_rvTable[i][j]);
				if ((nCnt + SysStringByteLen(pbstrCell)) >= MAX_OUTPUT_BUFFER)
				{
					hr = DB_E_DATAOVERFLOW;
					break;
				}
				nCnt += wsprintf(pwszOutput+nCnt, L"%s;", pbstrCell);
			}
		}
		if ((nCnt + wcslen(L"\n")) >= MAX_OUTPUT_BUFFER)
		{
			hr = DB_E_DATAOVERFLOW;
			break;
		}
		nCnt += wsprintf(pwszOutput+nCnt, L"\n");
		fputws(pwszOutput, myOSPFile);
		fflush(myOSPFile);
	}

	// close the file
	fclose(myOSPFile);
	delete [] pwszOutput;

	return hr;
}

////////////////////////////////////////////////////////
// Common notification routine:  send event to each
// Listener in the list.
////////////////////////////////////////////////////////

HRESULT	MyOSPObject::Notify(EOSPEVENTS eEvent, ULONG iRow, ULONG iColumn, ULONG cRows)
{
	//no-op case
	if(m_listListeners.GetCount()==0)
		return S_OK;
	
	//obtain first element
	HRESULT hr = S_OK;
	POS pos = m_listListeners.GetHeadPosition();
	
	//otherwise notify for reason/phase
	switch(eEvent)
	{
		//Multi-Cast
		case CHANGECELL_ABOUTTODO:
			while(pos)
				hr = m_listListeners.GetNext(pos)->aboutToChangeCell(iRow, iColumn);
			break;

		//Multi-Cast
		case CHANGECELL_DIDEVENT:
			while(pos)
				hr = m_listListeners.GetNext(pos)->cellChanged(iRow, iColumn);
			break;

		//Multi-Cast
		case DELETEROWS_ABOUTTODO:
			while(pos)
				hr = m_listListeners.GetNext(pos)->aboutToDeleteRows(iRow, cRows);
			break;

		//Multi-Cast
		case DELETEROWS_DIDEVENT:
			while(pos)
				hr = m_listListeners.GetNext(pos)->deletedRows(iRow, cRows);
			break;

		//Multi-Cast
		case INSERTROWS_ABOUTTODO:
			while(pos)
				hr = m_listListeners.GetNext(pos)->aboutToInsertRows(iRow, cRows);
			break;

		//Multi-Cast
		case INSERTROWS_DIDEVENT:
			while(pos)
				hr = m_listListeners.GetNext(pos)->insertedRows(iRow, cRows);
			break;

		//Multi-Cast
		case ROWSAVAILABLE_DIDEVENT:
			while(pos)
				hr = m_listListeners.GetNext(pos)->rowsAvailable(iRow, cRows);
			break;
	
		//Multi-Cast
		case TRANSFERCOMPLETE_DIDEVENT:
			while(pos)
				hr = m_listListeners.GetNext(pos)->transferComplete(OSPXFER_COMPLETE);
			break;

		//Multi-Cast
		case TRANSFERCOMPLETE_FAILEDTODO:
			while(pos)
				hr = m_listListeners.GetNext(pos)->transferComplete(OSPXFER_ABORT);
			break;

		default:
			//Unknown event?
			break;
	};

	return hr;
}

////////////////////////////////////////////////////////
// OSPSimpleProvider implementation
//
////////////////////////////////////////////////////////

HRESULT MyOSPObject::addOLEDBSimpleProviderListener(OLEDBSimpleProviderListener* pospIListener)
{
	if(pospIListener==NULL)
		return E_INVALIDARG;

	//Add the Listener:
	pospIListener->AddRef();
	m_listListeners.AddTail(pospIListener);

	return S_OK;
}

HRESULT MyOSPObject::deleteRows(LONG iRow, LONG cRows, LONG* pcRowsDeleted)
{
	LONG		cNewRows, i, j;
	VARIANT**	rvNewTable;

	// Doesn't handle label or wildcard rows
	if (iRow <= 0)
		return E_FAIL;
	
	// InvalidArg
	if (cRows < 0)
		return E_INVALIDARG;

	// Is starting row within range?
	if (iRow > m_cRows)
		return E_INVALIDARG;

	// Adjust row count to stay within range:
	if (iRow + cRows > m_cRows + 1)
		cRows = m_cRows - iRow + 1;

	// Notify our Listeners:
	Notify(DELETEROWS_ABOUTTODO, iRow, -1, cRows);

	// Allocate new array with reduced rows:
	cNewRows = m_cRows - cRows;
	rvNewTable = (VARIANT**)CoTaskMemAlloc((cNewRows+1) * sizeof(VARIANT*));

	j = 0;
	for (i = 0; i <= m_cRows; i++)
	{
		if (i < iRow || i > (iRow + cRows - 1))
			rvNewTable[j++] = m_rvTable[i];		// retain rows
		else
			CoTaskMemFree(m_rvTable[i]);		// free deleted row
	}

	// Free old table, point to new table and adjust count:
	CoTaskMemFree(m_rvTable);
	m_rvTable = rvNewTable;
	m_cRows = cNewRows;

	// Save the internal table to the data file:
	if (m_szFilePath != NULL)
		saveData();

	// Notify our Listeners:
	Notify(DELETEROWS_DIDEVENT, iRow, -1, cRows);

	// Return the count of rows deleted:
	*pcRowsDeleted = cRows;
    return S_OK;
}


HRESULT MyOSPObject::find(LONG iRowStart, LONG iColumn, VARIANT val, OSPFIND findFlags, OSPCOMP compType, LONG* piRowFound)
{
	// Check arguments:
	if (piRowFound == NULL)
		return E_INVALIDARG;
	if (iRowStart <= 0 || iRowStart > m_cRows)
		return E_FAIL;
	if (iColumn <= 0 || iColumn > m_cColumns)
		return E_FAIL;

	// Determine search order:
	LONG	iRowStop = (findFlags == OSPFIND_UP || findFlags == OSPFIND_UPCASESENSITIVE) ? 0 : m_cRows+1;
	BOOL	fCaseSensitive = (findFlags == OSPFIND_CASESENSITIVE || findFlags == OSPFIND_UPCASESENSITIVE);

	// Linear search through all rows:
	while (iRowStart != iRowStop)
	{
		LONG iCompVal = CompareVariant(&m_rvTable[iRowStart][iColumn], &val, fCaseSensitive);
		switch(compType)
		{
			case OSPCOMP_EQ:
				if (iCompVal ==	0)
				{
					*piRowFound = iRowStart;
					return S_OK;
				}
				break;
				
			case OSPCOMP_LT:
				if (iCompVal < 0)
				{
					*piRowFound = iRowStart;
					return S_OK;
				}
				break;

			case OSPCOMP_LE:
				if (iCompVal <= 0)
				{
					*piRowFound = iRowStart;
					return S_OK;
				}
				break;
			
			case OSPCOMP_GE:
				if (iCompVal >= 0)
				{
					*piRowFound = iRowStart;
					return S_OK;
				}
				break;
			
			case OSPCOMP_GT:
				if (iCompVal > 0)
				{
					*piRowFound = iRowStart;
					return S_OK;
				}
				break;
			
			case OSPCOMP_NE:
				if (iCompVal != 0)
				{
					*piRowFound = iRowStart;
					return S_OK;
				}
				break;

			default:
				break;
		};

		if (findFlags == OSPFIND_UP || findFlags == OSPFIND_UPCASESENSITIVE)
			iRowStart--;
		else
			iRowStart++;
	}
	*piRowFound = -1;
	return S_FALSE;
}


HRESULT MyOSPObject::insertRows(LONG iRow, LONG cRows, LONG* pcRowsInserted)
{
	LONG		cNewRows, i, j, k;
	VARIANT**	rvNewTable;

	// Doesn't handle label or wildcard rows
	if (iRow <= 0)
		return E_FAIL;
	
	// InvalidArg
	if (cRows < 0)
		return E_INVALIDARG;

	// If called to insert after the end, adjust to insert at the end:
	if (iRow > m_cRows)
		iRow = m_cRows + 1;

	// Notify our Listeners:
	Notify(INSERTROWS_ABOUTTODO, iRow, -1, cRows);

	// Allocate new array with more rows:
	cNewRows = m_cRows + cRows;
	rvNewTable = (VARIANT**)CoTaskMemAlloc((cNewRows+1) * sizeof(VARIANT*));
	j = 0;
	for (i = 0; i <= cNewRows; i++)
	{
		if (i < iRow || i > (iRow + cRows - 1))
			rvNewTable[i] = m_rvTable[j++];		// retain rows
		else
		{										// insert new empty row
			rvNewTable[i] = (VARIANT*)CoTaskMemAlloc((m_cColumns+1) * sizeof(VARIANT));
			for (k = 0; k <= m_cColumns; k++)	// initialize new columns
				rvNewTable[i][k].vt = VT_NULL;
		}
	}

	// Free old table, point to new table and adjust count:
	CoTaskMemFree(m_rvTable);
	m_rvTable = rvNewTable;
	m_cRows = cNewRows;

	// Save the internal table to the data file:
	if (m_szFilePath != NULL)
		saveData();

	// Notify our Listeners:
	Notify(INSERTROWS_DIDEVENT, iRow, -1, cRows);

	// Return the count of rows inserted:
	*pcRowsInserted = cRows;
	return S_OK;
}


HRESULT MyOSPObject::getColumnCount(LONG* pcColumns)
{
	if (pcColumns == NULL)
		return E_INVALIDARG;
	*pcColumns = m_cColumns;
	return S_OK;
}


HRESULT MyOSPObject::getEstimatedRows(LONG* piRows)
{
	return getRowCount(piRows);
}


HRESULT MyOSPObject::getLocale(BSTR* pbstrLocale)
{
	if (pbstrLocale == NULL)
		return E_INVALIDARG;

	// Return default locale:
	WCHAR* pszLocale;
	int cchData = GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SLANGUAGE, NULL, 0);
	pszLocale = (TCHAR*)CoTaskMemAlloc(cchData * sizeof(TCHAR));
	if (pszLocale)
	{
		BSTR bstr = SysAllocStringLen(NULL, cchData);
		GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SLANGUAGE, pszLocale, cchData);

		bstr = SysAllocString(pszLocale);

		*pbstrLocale = bstr;
	}
	return S_OK;
}


HRESULT MyOSPObject::getRowCount(LONG* pcRows)
{
	if (pcRows == NULL)
		return E_INVALIDARG;
	*pcRows = m_cRows;
	return S_OK;
}


HRESULT MyOSPObject::getRWStatus(LONG iRow, LONG iColumn, OSPRW* prwStatus)
{
	if (prwStatus == NULL)
		return E_INVALIDARG;

	*prwStatus = OSPRW_READWRITE;

	return S_OK;
}


HRESULT MyOSPObject::getVariant(LONG iRow, LONG iColumn, OSPFORMAT format, VARIANT* pVar)
{
	//INVALIDARG
	if (pVar == NULL)
		return E_INVALIDARG;

	//Doesn't handle wildcards
	if (iRow < 0 || iColumn < 0)
		return E_FAIL;
	
	//Get Column Value
	VariantCopy(pVar, &m_rvTable[iRow][iColumn]);
	return S_OK;
}


HRESULT MyOSPObject::isAsync(BOOL* pbAsynch)
{
	if(pbAsynch==NULL)
		return E_INVALIDARG;

	*pbAsynch = FALSE;
	return S_OK;
}


HRESULT MyOSPObject::removeOLEDBSimpleProviderListener(OLEDBSimpleProviderListener* pospIListener)
{
	if(pospIListener==NULL)
		return E_INVALIDARG;

	//Find the Listener in the list:
	POS pos = m_listListeners.Find(pospIListener);
	if (pos == NULL)
		return E_FAIL;

	//Remove the Listener from the list and release it:
	SAFE_RELEASE(pospIListener);
	m_listListeners.RemoveAt(pos);

	return S_OK;
}

HRESULT MyOSPObject::setVariant(LONG iRow, LONG iColumn, OSPFORMAT format, VARIANT Var)
{
	// Doesn't handle wildcards
	if (iRow < 0 || iColumn < 0)
		return E_FAIL;

	// Notify our Listeners:
	Notify(CHANGECELL_ABOUTTODO, iRow, iColumn, 1);

	// Set Column Value
	VariantChangeType(&m_rvTable[iRow][iColumn], &Var, 0, VT_BSTR);

	// Save the internal table to the data file:
	if (m_szFilePath != NULL)
		saveData();

	// Notify our Listeners:
	Notify(CHANGECELL_DIDEVENT, iRow, iColumn, 1);

	return S_OK;
}


HRESULT MyOSPObject::stopTransfer()
{
	// Do nothing because we are already populated
	return S_OK;
}
