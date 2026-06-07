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
// PersistentNote.cpp
// 
// CPersistentNote class method definitions
//
// Copyright Microsoft Corporation, All Rights Reserved
//
// **************************************************************************

#include "PersistentNote.h"
#include "strsafe.h"



#define BREAK ASSERT(SUCCEEDED(hr))
#define MAX_INKDATA_LEN 10000

BSTR    CPersistentNote::bstrDocTemplate = 
    L"<?xml version=\"1.0\" ?> \
        <Import xmlns=\"http://schemas.microsoft.com/office/onenote/2004/import\"> \
          <EnsurePage path=\"Pocket Notes\\InkFiles.one\" guid=\"\" title=\"\" /> \
            <PlaceObjects pagePath=\"Pocket Notes\\InkFiles.one\" pageGuid=\"\"> \
                <Object guid=\"\"> \
                    <Position x=\"0\" y=\"0\" />  \
                    <Ink> \
                        <Data></Data> \
                    </Ink> \
                </Object> \
            </PlaceObjects> \
        </Import>";



CPersistentNote::CPersistentNote()
{
    m_szNoteFile = NULL;
}


/////////////////////////////////////////////////////////////////////
// Return the Object element
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::getObjectElement( XMLElementPtr& spRootElem, XMLElementPtr& spObjectElement )
{
    HRESULT hr = S_OK;
    XMLNodePtr spObjectNode;
    hr = spRootElem->selectSingleNode( CComBSTR("//Object"), &spObjectNode );
    if(FAILED(hr))
    {
        return hr;
    }
    hr = spObjectNode->QueryInterface( IID_IXMLDOMElement, (void **)&spObjectElement);
    return hr;
}


/////////////////////////////////////////////////////////////////////
// Return the EnsurePage element
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::getEnsurePageElement( XMLElementPtr& spRootElem, XMLElementPtr& spEnsurePageElement)
{
    HRESULT hr = S_OK;

    XMLNodePtr spEnsurePageNode;
    hr = spRootElem->selectSingleNode( CComBSTR("//EnsurePage"), &spEnsurePageNode );
    VERIFY(SUCCEEDED(hr));
    if(FAILED(hr))
    {
        return hr;
    }
    hr = spEnsurePageNode->QueryInterface( IID_IXMLDOMElement, (void **)&spEnsurePageElement);
    VERIFY(SUCCEEDED(hr));

    return hr;
}

HRESULT CPersistentNote::getPlaceObjectsElement( XMLElementPtr& spRootElem, XMLElementPtr& spPlaceObjectsElement)
{
    HRESULT hr = S_OK;

    XMLNodePtr spPlaceObjectsNode;
    hr = spRootElem->selectSingleNode( CComBSTR("//PlaceObjects"), &spPlaceObjectsNode);
    VERIFY(SUCCEEDED(hr));
    if(FAILED(hr))
    {
        return hr;
    }
    hr = spPlaceObjectsNode->QueryInterface( IID_IXMLDOMElement, (void **)&spPlaceObjectsElement);
    VERIFY(SUCCEEDED(hr));

    return hr;

}



/////////////////////////////////////////////////////////////////////
// Return the Ink\Data node 
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::getInkDataNode( XMLElementPtr& spRootElem, XMLNodePtr& spInkDataNode)
{
    HRESULT hr = S_OK;
    hr = spRootElem->selectSingleNode( CComBSTR(L"//Ink/Data"), &spInkDataNode );
    VERIFY(SUCCEEDED(hr));
    return hr;
}




/////////////////////////////////////////////////////////////////////
// Populate the member variable from the ink data in the document
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::PutInkData( XMLElementPtr& spRootElem )
{
    CComBSTR value;
    HRESULT hr = S_OK;
    // Get the Ink/Data Node
    XMLNodePtr spInkDataNode;
    getInkDataNode(spRootElem, spInkDataNode);

    hr = spInkDataNode->get_text( &value );
    VERIFY(SUCCEEDED(hr));
    m_bstrInkData = value;
    return hr;
}


/////////////////////////////////////////////////////////////////////
// Populate the member variable from the page title in the document
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::PutTitle( XMLElementPtr& spRootElem )
{
    HRESULT hr = S_OK;
    VARIANT title;
    XMLElementPtr spEnsurePageElement;
    
    hr = getEnsurePageElement(spRootElem, spEnsurePageElement);
    hr = spEnsurePageElement->getAttribute( CComBSTR(L"title"), &title);
    
    VERIFY(SUCCEEDED(hr));
    m_bstrTitle = title.bstrVal;

    ::VariantClear(&title);
    return hr;
}


/////////////////////////////////////////////////////////////////////
// Populate the member variable from the object GUID in the document
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::PutObjectGUID( XMLElementPtr& spRootElem )
{
    HRESULT hr = S_OK;

    CComVariant spObjectGuid;

    XMLElementPtr spObjectElement;

    hr = getObjectElement(spRootElem, spObjectElement);

    hr = spObjectElement->getAttribute( CComBSTR(L"guid"),  &spObjectGuid );
    
    VERIFY(SUCCEEDED(hr));
    m_bstrObjectGuid = spObjectGuid.bstrVal;

    return hr;
}

HRESULT CPersistentNote::PutPageGUID( XMLElementPtr& spRootElem )
{
    HRESULT hr = S_OK;
    CComVariant spEnsurePageGUID;
    CComVariant spPlaceObjectsGUID;

    // Get the EnsurePage element
    XMLElementPtr spEnsurePageElement;
    getEnsurePageElement( spRootElem, spEnsurePageElement );
    
    hr = spEnsurePageElement->getAttribute(CComBSTR(L"guid"), &spEnsurePageGUID);
    VERIFY(SUCCEEDED(hr));

    XMLElementPtr spPlaceObjectsElement;
    getPlaceObjectsElement( spRootElem, spPlaceObjectsElement);
    hr = spPlaceObjectsElement->getAttribute(CComBSTR(L"pageGuid"), &spPlaceObjectsGUID);
    VERIFY(SUCCEEDED(hr));

    if( spEnsurePageGUID != spPlaceObjectsGUID )
    {
        hr = E_FAIL;
    }
    else
    {
        m_bstrPageGuid = spEnsurePageGUID.bstrVal;
    }

    return hr;
}


/////////////////////////////////////////////////////////////////////
// Add the ink data to the document
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::GetInkData( XMLElementPtr& spRootElem )
{
    HRESULT hr = S_OK;
    // Get the Ink/Data Node
    XMLNodePtr spInkDataNode;
    getInkDataNode(spRootElem, spInkDataNode);

    ASSERT( NULL != m_bstrInkData.m_str );
    hr = spInkDataNode->put_text( m_bstrInkData);
    VERIFY(SUCCEEDED(hr));
    return hr;
}



/////////////////////////////////////////////////////////////////////
// Add the page title to the document
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::GetTitle( XMLElementPtr& spRootElem )
{
    HRESULT hr = S_OK;
    // Get the Ensurepage element
    XMLElementPtr spEnsurePageElement;
    getEnsurePageElement( spRootElem, spEnsurePageElement );
    
    ASSERT(NULL != m_bstrTitle.m_str);
    hr = spEnsurePageElement->setAttribute(CComBSTR(L"title"), CComVariant(m_bstrTitle));
    VERIFY(SUCCEEDED(hr));
    return hr;
}

HRESULT CPersistentNote::GetPageGUID( XMLElementPtr& spRootElem )
{
    HRESULT hr = S_OK;
    
    // Get the EnsurePage element
    XMLElementPtr spEnsurePageElement;
    getEnsurePageElement( spRootElem, spEnsurePageElement );
    
    ASSERT(NULL != m_bstrPageGuid.m_str);
    hr = spEnsurePageElement->setAttribute(CComBSTR(L"guid"), CComVariant(m_bstrPageGuid));
    VERIFY(SUCCEEDED(hr));

    XMLElementPtr spPlaceObjectsElement;
    getPlaceObjectsElement( spRootElem, spPlaceObjectsElement);
    hr = spPlaceObjectsElement->setAttribute(CComBSTR(L"pageGuid"), CComVariant(m_bstrPageGuid));
    VERIFY(SUCCEEDED(hr));

    return hr;
}


/////////////////////////////////////////////////////////////////////
// Add the object GUID to the document
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::GetObjectGUID( XMLElementPtr& spRootElem )
{
    HRESULT hr = S_OK;
    // Get the Object element
    XMLElementPtr spObjectElement;
    getObjectElement(spRootElem, spObjectElement);

    ASSERT(NULL != m_bstrObjectGuid.m_str );

    hr = spObjectElement->setAttribute(CComBSTR(L"guid"), CComVariant(m_bstrObjectGuid));
    VERIFY(SUCCEEDED(hr));
    return hr;
}


/////////////////////////////////////////////////////////////////////
// Load the note from the supplied file
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::LoadFromFile( LPCWSTR wszNoteFile )
{
    HRESULT hr = S_OK;
    XMLDOMDocumentPtr spXMLDoc;
    CComBSTR bstr( wszNoteFile );
    WCHAR szFileName[MAX_PATH];
    VARIANT_BOOL vbLoadResult = VARIANT_FALSE;
    XMLElementPtr spRootElem;
    
    if(NULL != m_szNoteFile)
    {
        delete [] m_szNoteFile;
        m_szNoteFile = NULL;
    }

    // Copy the filename for later 
    m_szNoteFile = new WCHAR[MAX_PATH + 1];
    if(NULL == m_szNoteFile)
    {
        goto Error;
    }

    hr = ::StringCchCopy(m_szNoteFile, MAX_PATH+1, wszNoteFile);
    if(FAILED(hr))
    {
        goto Error;
    }

    //
    // Create a file URL
    // 
    hr = ::StringCchCopyW( szFileName, MAX_PATH, L"file://" );
    if(FAILED(hr))
    {
        goto Error;
    }
    hr = ::StringCchCatW( szFileName, MAX_PATH, wszNoteFile );
    if(FAILED(hr))
    {
        goto Error;
    }


    //
    // Create an XML document and load the file into it
    //
    hr = spXMLDoc.CoCreateInstance( CLSID_DOMDocument );
    ASSERT(SUCCEEDED(hr));
    if(FAILED(hr))
    {
        goto Error;
    }

    hr = spXMLDoc->put_validateOnParse(VARIANT_TRUE);
    hr = spXMLDoc->put_preserveWhiteSpace(VARIANT_TRUE);
    if(FAILED(hr))
    {
        goto Error;
    }


    hr = spXMLDoc->load( CComVariant(szFileName), &vbLoadResult );
    ASSERT( VARIANT_TRUE == vbLoadResult );
    if(FAILED(hr))
    {
        goto Error;
    }

    //
    // Get the root element and apply XPath expressions on it
    //
    hr = spXMLDoc->get_documentElement( &spRootElem );
    if( FAILED( hr ) || NULL == spRootElem.p )    // Empty xml file
    {
        return E_FAIL;
    }

    PutInkData(spRootElem);
    PutPageGUID(spRootElem);
    PutObjectGUID(spRootElem);
    PutTitle(spRootElem);

Error:
    return hr;
}



/////////////////////////////////////////////////////////////////////
// Saves the ink data to the file we previously opened
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::Save()
{
    HRESULT hr = S_OK;
    ASSERT( NULL != m_szNoteFile);
    
    if(NULL == m_szNoteFile)
    {
        return E_FAIL;
    }

    // Save the file
    SaveToFile( m_szNoteFile);
    
    return hr;
}


/////////////////////////////////////////////////////////////////////
// Saves the ink data to the supplied file
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::SaveToFile(LPCWSTR szNoteFile)
{
    HRESULT hr = S_OK;
    CComBSTR bstrFile(szNoteFile);
    XMLDOMDocumentPtr spXMLDoc;
    VARIANT_BOOL vbLoadResult = VARIANT_FALSE;
    WCHAR szFileName[MAX_PATH];
    XMLElementPtr spRootElem;


    if(NULL == szNoteFile)
    {
        hr = E_POINTER;
        goto Error;
    }
    
    // The member variables should be non-empty
    ASSERT( NULL != m_bstrInkData.m_str &&
            NULL != m_bstrObjectGuid.m_str &&
            NULL != m_bstrTitle.m_str );

    if( NULL == m_bstrInkData.m_str ||
        NULL == m_bstrObjectGuid.m_str ||
        NULL == m_bstrTitle.m_str )
    {
        hr = E_FAIL;
        goto Error;
    }


    //
    // Create a file URL
    // 
    hr = ::StringCchCopyW( szFileName, MAX_PATH, L"file://" );
    if(FAILED(hr))
    {
        goto Error;
    }
    hr = ::StringCchCatW( szFileName, MAX_PATH, szNoteFile );
    if(FAILED(hr))
    {
        goto Error;
    }
    
    //
    // Create an XML document and load the template data into it
    //
    hr = spXMLDoc.CoCreateInstance( CLSID_DOMDocument );
    ASSERT(SUCCEEDED(hr));
    if(FAILED(hr))
    {
        goto Error;
    }

    spXMLDoc->put_validateOnParse(VARIANT_TRUE);
    spXMLDoc->put_preserveWhiteSpace(VARIANT_TRUE);

    hr = spXMLDoc->loadXML( bstrDocTemplate, &vbLoadResult);
    ASSERT( VARIANT_TRUE == vbLoadResult );
    if(FAILED(hr))
    {
        goto Error;
    }

    //
    // Get the root element and apply XPath expressions on it
    //
    hr = spXMLDoc->get_documentElement( &spRootElem );
    if( FAILED( hr ) || NULL == spRootElem.p )    // Empty xml file
    {
        return E_FAIL;
    }

    hr = GetInkData(spRootElem);
    if(FAILED(hr))
    {
        goto Error;
    }

    hr = GetTitle(spRootElem);
    VERIFY(SUCCEEDED(hr));
    hr = GetPageGUID(spRootElem);
    VERIFY(SUCCEEDED(hr));
    hr = GetObjectGUID(spRootElem);
    VERIFY(SUCCEEDED(hr));    

    // Finally save the file 
    hr = spXMLDoc->save(CComVariant(szFileName));

Error:

    return hr;
}





//-------------------------------------------------------------------
// PROPERTIES
//-------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////
// Returns the ink data associated with this node
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::get_InkData(BSTR* pBstrInkData)
{
    HRESULT hr = S_OK;
    ASSERT( NULL != pBstrInkData );
    if(NULL == pBstrInkData)
    {
        return E_POINTER;
    }

    CComBSTR bstrRet = L"base64:";
    hr = bstrRet.Append(m_bstrInkData);
    if(FAILED(hr))
    {
        return hr;
    }

    // We have ink data so we return it
    *pBstrInkData = bstrRet.Copy();
    
    
    return hr;
}

/////////////////////////////////////////////////////////////////////
// Sets the ink data associated with this note
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::put_InkData(BSTR bstrInkData)
{
    HRESULT hr = S_OK;
    WCHAR* szData = &(bstrInkData[7]);

    m_bstrInkData = szData;

    return hr;
}

/////////////////////////////////////////////////////////////////////
// Returns the guid of the note as a string
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::get_ObjectGuid(BSTR* pbstrObjGuid)
{
    HRESULT hr = S_OK;

    ASSERT(NULL != pbstrObjGuid);

    *pbstrObjGuid = m_bstrObjectGuid.Copy();

    return hr;
}


/////////////////////////////////////////////////////////////////////
// Sets the guid string of the note to the supplied string
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::put_ObjectGuid(BSTR bstrObjGuid)
{
    HRESULT hr = S_OK;
    
    m_bstrObjectGuid = bstrObjGuid;

    return hr;
}

/////////////////////////////////////////////////////////////////////
// Sets the page guid string of the note to the supplied string
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::put_PageGuid(BSTR bstrPageGuid)
{
    HRESULT hr = S_OK;
    
    m_bstrPageGuid = bstrPageGuid;

    return hr;
}

/////////////////////////////////////////////////////////////////////
// Returns the title of the note 
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::get_Title(BSTR* pbstrTitle)
{
    HRESULT hr = S_OK;
    
    ASSERT(NULL != pbstrTitle);

    *pbstrTitle = m_bstrTitle.Copy();
    return hr;
}

/////////////////////////////////////////////////////////////////////
// Sets the title of the note to the supplied title
/////////////////////////////////////////////////////////////////////
HRESULT CPersistentNote::put_Title(BSTR bstrTitle)
{
    HRESULT hr = S_OK;

    m_bstrTitle = bstrTitle;
    
    return hr;
}


void CPersistentNote::Clear()
{

    m_bstrInkData.Empty();
    m_bstrObjectGuid.Empty();
    m_bstrPageGuid.Empty();
    m_bstrTitle.Empty();

    if(NULL != m_szNoteFile)
    {
        delete [] m_szNoteFile;
        m_szNoteFile = NULL;
    }

}