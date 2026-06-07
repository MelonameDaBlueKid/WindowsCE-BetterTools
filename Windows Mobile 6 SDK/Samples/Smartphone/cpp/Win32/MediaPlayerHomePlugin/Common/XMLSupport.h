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
////////////////////////////////////////////////////////////
// This is "Sample Code" and is distributable subject to the
// terms of the end user license agreement.
////////////////////////////////////////////////////////////

#ifndef _XMLSUPPORT_H_
#define _XMLSUPPORT_H_

////////////////////////////////////////////////////////////
// CXmlHelpers class
//
// A class with only static methods that provide help with
// parsing XML.
////////////////////////////////////////////////////////////

class CXmlHelpers
{
public:
    // Returns an attribute string (LPWSTR) value, given an attribute map
    // and the attribute name.
    //
    // If the specified attribute doesn't exist, this method will return
    // S_FALSE and *pwszResult will be NULL.
    //
    // If this method succeeds, it is the caller's responsibility to free
    // the string (*pwszResult) by passing it to 'free'. Note that even if
    // this method returns S_FALSE, passing the resultant string (which will
    // be NULL) to 'free' is acceptable, since 'free(NULL)' is perfectly
    // fine.
    //
    // Thus, code like the following is acceptable:
    //
    // HRESULT hr;
    // LPWSTR wszAttrValue;
    //
    // if (SUCCEEDED(hr = CXmlHelpers::GetAttributeStringValueFromAttrMap(pMyMap, L"some-attr", &wszAttrValue)))
    // {
    //     if (hr != S_FALSE)
    //         // got attribute value; use it
    //     else
    //         // didn't get attribute value -- use default or handle error
    //
    //     free(wszAttrValue);  // acceptable in either case
    // }
    static HRESULT GetAttributeStringValueFromAttrMap(IXMLDOMNamedNodeMap * pMapAttrs, LPCWSTR wszAttrName, LPWSTR * pwszResult)
    {
        HRESULT         hr;
        VARIANT         var;
        BSTR            bstrAttrName = NULL;
        IXMLDOMNode *   pNodeAttr = NULL;
        LPWSTR          wszCopy;

        // Initialize the VARIANT. Do this first because in our Cleanup code, we
        // will blindly call VariantClear on it.
        VariantInit(&var);

        // Create a BSTR for the attribute name.
        if ((bstrAttrName = SysAllocString(wszAttrName)) == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto Cleanup;
        }

        // Get the attribute. Note that getNamedItem will succeed with S_FALSE if
        // the specified attribute doesn't exist.
        if (FAILED(hr = pMapAttrs->getNamedItem(bstrAttrName, &pNodeAttr)))
            goto Cleanup;

        if (hr == S_FALSE)
        {
            *pwszResult = NULL;
            goto Cleanup;
        }

        // We found the attribute. Get its value.
        if (FAILED(hr = pNodeAttr->get_nodeValue(&var)))
            goto Cleanup;

        // The VARIANT type should be VT_BSTR. Assuming it is, make a copy for the return string.
        if (var.vt != VT_BSTR)
        {
            hr = E_UNEXPECTED;
            goto Cleanup;
        }

        if ((wszCopy = wcsdup(var.bstrVal)) == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto Cleanup;
        }

        // Success!
        *pwszResult = wszCopy;
        hr = S_OK;

    Cleanup:
        VariantClear(&var);

        if (pNodeAttr != NULL)
            pNodeAttr->Release();

        if (bstrAttrName != NULL)
            SysFreeString(bstrAttrName);

        return hr;
    }

    // Similar to GetAttributeStringValueFromAttrMap, but 'returns' an INT instead.
    //
    // If the attribute doesn't exist, returns S_FALSE. In this case, *pnResult will
    // be 0.
    static HRESULT GetAttributeIntValueFromAttrMap(IXMLDOMNamedNodeMap * pMapAttrs, LPCWSTR wszAttrName, INT * pnResult)
    {
        HRESULT     hr;
        LPWSTR      wszValue;

        // Get the attribute value as a string.
        if (FAILED(hr = GetAttributeStringValueFromAttrMap(pMapAttrs, wszAttrName, &wszValue)))
            return hr;

        if (hr == S_FALSE)  // attribute does not exist
        {
            *pnResult = 0;
            return S_FALSE;
        }

        // Convert to int.
        *pnResult = _wtoi(wszValue);

        // Clean up and return successfully.
        free(wszValue);

        return S_OK;
    }

    // Similar to GetAttributeStringValueFromAttrMap, but takes an IXMLDOMNode * instead and calls
    // get_attributes on it to fetch the attribute map.
    //
    // Don't make multiple calls to this method on the same node. Instead, fetch the attribute map
    // yourself and make calls to GetAttributeStringValueFromAttrMap.
    //
    // The comments for GetAttributeStringValueFromAttrMap regarding the return value and the
    // returned string apply here as well.
    static HRESULT GetAttributeStringValueFromNode(IXMLDOMNode * pNode, LPCWSTR wszAttrName, LPWSTR * pwszResult)
    {
        HRESULT                 hr;
        IXMLDOMNamedNodeMap *   pMap = NULL;

        if (FAILED(hr = pNode->get_attributes(&pMap)))
            goto Cleanup;

        if (FAILED(hr = GetAttributeStringValueFromAttrMap(pMap, wszAttrName, pwszResult)))
            goto Cleanup;

        // Success.
        hr = S_OK;

    Cleanup:
        if (pMap != NULL)
            pMap->Release();

        return hr;
    }

    // Similar to GetAttributeIntValueFromAttrMap, but takes an IXMLDOMNode * instead and calls
    // get_attributes on it to fetch the attribute map.
    //
    // Don't make multiple calls to this method on the same node. Instead, fetch the attribute map
    // yourself and make calls to GetAttributeIntValueFromAttrMap.
    //
    // The comments for GetAttributeIntValueFromAttrMap regarding the return value and the
    // returned INT apply here as well.
    static HRESULT GetAttributeIntValueFromNode(IXMLDOMNode * pNode, LPCWSTR wszAttrName, INT * pnResult)
    {
        HRESULT                 hr;
        IXMLDOMNamedNodeMap *   pMap = NULL;

        if (FAILED(hr = pNode->get_attributes(&pMap)))
            goto Cleanup;

        if (FAILED(hr = GetAttributeIntValueFromAttrMap(pMap, wszAttrName, pnResult)))
            goto Cleanup;

        // Success.
        hr = S_OK;

    Cleanup:
        if (pMap != NULL)
            pMap->Release();

        return hr;
    }


private:
    // Constructor is private to prevent instantiation.
    CXmlHelpers() { }
};

#endif // _XMLSUPPORT_H_
