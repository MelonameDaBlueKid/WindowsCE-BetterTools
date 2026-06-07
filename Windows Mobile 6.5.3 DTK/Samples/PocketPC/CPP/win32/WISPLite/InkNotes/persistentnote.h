//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// **************************************************************************
// PersistentNote.h
// 
// CPersistentNote class declaration.
//
// Copyright Microsoft Corporation, All Rights Reserved
//
// **************************************************************************

#pragma once

#define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA

#include "windows.h"
#include "msxml.h"
#include "atlbase.h"

typedef CComPtr<IXMLDOMDocument>    XMLDOMDocumentPtr;
typedef CComPtr<IXMLDOMNode>        XMLNodePtr;
typedef CComPtr<IXMLDOMElement>     XMLElementPtr;
typedef CComPtr<IXMLDOMNodeList>    XMLNodeListPtr;


//
// This class handles the file reading/writing part
//
class CPersistentNote
{
public:
    CPersistentNote();
    ~CPersistentNote(){};

    HRESULT LoadFromFile( LPCWSTR wszNoteFile );
    HRESULT Save();
    HRESULT SaveToFile( LPCWSTR szNoteFile );

public:
    // Properties

    HRESULT get_InkData(BSTR* pBstrInkData);
    HRESULT put_InkData(BSTR bstrInkData);

    HRESULT put_PageGuid(BSTR bstrPageGuid);

    HRESULT get_ObjectGuid(BSTR* pbstrObjGuid);
    HRESULT put_ObjectGuid(BSTR bstrObjGuid);

    HRESULT get_Title(BSTR* pbstrTitle);
    HRESULT put_Title(BSTR bstrTitle);

    void    Clear();

private:
    HRESULT PutInkData( XMLElementPtr& spRootElem );
    HRESULT PutTitle( XMLElementPtr& spRootElem );
    HRESULT PutObjectGUID( XMLElementPtr& spRootElem );
    HRESULT PutPageGUID( XMLElementPtr& spRootElem );
    
    HRESULT GetInkData( XMLElementPtr& spRootElem );
    HRESULT GetTitle( XMLElementPtr& spRootElem );
    HRESULT GetObjectGUID( XMLElementPtr& spObjectElement );
    HRESULT GetPageGUID( XMLElementPtr& spRootElem );
    

    HRESULT getObjectElement( XMLElementPtr& spRootElem, XMLElementPtr& spObjectElement );
    HRESULT getEnsurePageElement( XMLElementPtr& spRootElem, XMLElementPtr& spEnsurePageElement);
    HRESULT getInkDataNode( XMLElementPtr& spRootElem, XMLNodePtr& spInkDataNode);
    HRESULT getPlaceObjectsElement( XMLElementPtr& spRootElem, XMLElementPtr& spPlaceObjectsElement);
    

    static BSTR     bstrDocTemplate;

    CComBSTR        m_bstrPageGuid;
    CComBSTR        m_bstrObjectGuid;
    CComBSTR        m_bstrTitle;
    CComBSTR        m_bstrInkData;
    LPWSTR          m_szNoteFile;
};