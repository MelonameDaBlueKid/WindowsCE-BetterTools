//--------------------------------------------------------------------
// Microsoft OLE DB Sample OLEDB Simple Provider
// (C) Copyright 1997 Microsoft Corporation.  All Rights Reserved.
//
// @doc
//
// @module MyOSPObject.h.H | MyOSPObject implementation
//
//
#ifndef _COSPROVIDER_H_
#define _COSPROVIDER_H_


////////////////////////////////////////////////////////
// Includes
//
////////////////////////////////////////////////////////
#include "msdaosp.h"
#include "CExList.h"

////////////////////////////////////////////////////////
// Defines
//
////////////////////////////////////////////////////////
#define MAX_INPUT_BUFFER	2048
#define MAX_OUTPUT_BUFFER	4096
#define MAX_WIDE_BUFFER		4096

enum EOSPEVENTS
{
	//Change notifcations
	CHANGECELL_ABOUTTODO,
	CHANGECELL_DIDEVENT,
	DELETEROWS_ABOUTTODO,
	DELETEROWS_DIDEVENT,
	INSERTROWS_ABOUTTODO,
	INSERTROWS_DIDEVENT,

	//Asynch Notifications
	ROWSAVAILABLE_DIDEVENT,
	TRANSFERCOMPLETE_DIDEVENT,
	TRANSFERCOMPLETE_FAILEDTODO,
};

////////////////////////////////////////////////////////
// MyOSPObject - Sample OLEDBSimpleProvider
//
////////////////////////////////////////////////////////
class MyOSPObject	: public OLEDBSimpleProvider
{
public:
	//constructors
	MyOSPObject();
	virtual ~MyOSPObject();
	virtual HRESULT Init(WCHAR* pwszFilePath);

	//IUnknown
	virtual inline STDMETHODIMP_(ULONG)	AddRef()								
	{																
		InterlockedIncrement((LONG*)&m_cRef);						
		return m_cRef;												
	}																
	virtual inline STDMETHODIMP_(ULONG)	Release()								
	{																
		if(InterlockedDecrement((LONG*)&m_cRef))					
			return m_cRef;											
																	
		delete this;												
		return 0;													
	}																
	virtual STDMETHODIMP	QueryInterface(REFIID riid, void** ppv);

	//OLEDBSimpleProvider methods
	virtual STDMETHODIMP	getRowCount(LONG* pcRows);
    virtual STDMETHODIMP	getColumnCount(LONG* pcColumns);
	virtual STDMETHODIMP	getRWStatus(LONG iRow, LONG iColumn, OSPRW* prwStatus);
    
	virtual STDMETHODIMP	getVariant(LONG iRow, LONG iColumn, OSPFORMAT format, VARIANT* pVar);
    virtual STDMETHODIMP	setVariant(LONG iRow, LONG iColumn, OSPFORMAT format, VARIANT Var);

	virtual STDMETHODIMP	getLocale(BSTR* pbstrLocale);

    virtual STDMETHODIMP	deleteRows(LONG iRow, LONG cRows, LONG* pcRowsDeleted);
    virtual STDMETHODIMP	insertRows(LONG iRow, LONG cRows, LONG* pcRowsInserted);
    virtual STDMETHODIMP	find(LONG iRowStart, LONG iColumn, VARIANT val, OSPFIND findFlags, OSPCOMP compType, LONG* piRowFound);

    virtual STDMETHODIMP	addOLEDBSimpleProviderListener(OLEDBSimpleProviderListener* pospIListener);
    virtual STDMETHODIMP	removeOLEDBSimpleProviderListener(OLEDBSimpleProviderListener* pospIListener);

	virtual STDMETHODIMP	isAsync(BOOL* pbAsynch);
	virtual STDMETHODIMP	getEstimatedRows(LONG* piRows);
    virtual STDMETHODIMP	stopTransfer();

	// sample-specific routines:
	virtual HRESULT loadData();
	virtual HRESULT	Notify(EOSPEVENTS eEvent, ULONG iRow, ULONG iColumn, ULONG cRows);

protected:
	//data
	VARIANT**								m_rvTable;			// Pointer to start of Array
	LONG									m_cRows;			// Row Count
	LONG									m_cColumns;			// Column Count
	LPWSTR									m_szFilePath;		// Pathname of *.csv File
	CExList<OLEDBSimpleProviderListener*>	m_listListeners;	// List of OSP Listeners

	//IUnknown
	ULONG m_cRef;

private:
	// routines:
	HRESULT saveData();
};

#endif //_COSPROVIDER_H_

