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

#include <windows.h>
#include <msxml.h>
#include "..\common\xmlsupport.h"

////////////////////////////////////////////////////////////
// CheckPriAndSwap
//
// A small helper function to handle priority-based swapping
// of nodes (see GetUIString below).
////////////////////////////////////////////////////////////

static void CheckPriAndSwap(IXMLDOMNode ** ppNodeDst, IXMLDOMNode ** ppNodeSrc, int * pnPri, int nPriTest)
{
    if (nPriTest > *pnPri)
    {
        // Release the old 'dst'.
        if (*ppNodeDst != NULL)
            (*ppNodeDst)->Release();

        // The new 'dst' becomes the 'src'. Note that we essentially
        // transfer ref ownership here.
        *ppNodeDst = *ppNodeSrc;
        *ppNodeSrc = NULL;

        // Bump the new priority.
        *pnPri = nPriTest;
    }
}

////////////////////////////////////////////////////////////
// GetLocalizedTextNodeString
//
// See comment in TextLang.h for details on this function.
////////////////////////////////////////////////////////////

HRESULT GetLocalizedTextNodeString(IXMLDOMNode * pNode, LPWSTR * pwszResult, IXMLDOMNode ** ppNodeFound)
{
    HRESULT             hr;
    int                 nPriorityCur;
    long                iTextNode, cTextNodes;
    LANGID              langidPreferred;
    BSTR                bstrTextChildren = NULL;
    BSTR                bstrActualText = NULL;
    IXMLDOMNode *       pNodeText = NULL;
    IXMLDOMNode *       pNodeSelected = NULL;
    IXMLDOMNodeList *   pNodelist = NULL;

    // Initialization (in case of failure).
    *pwszResult = NULL;

    if (ppNodeFound != NULL)
        *ppNodeFound = NULL;

    // Select all <text> children of the specified node.
    if ((bstrTextChildren = SysAllocString(L"text")) == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    }

    if (FAILED(hr = pNode->selectNodes(bstrTextChildren, &pNodelist)))
        goto Cleanup;

    // Get the current system LANGID.
    langidPreferred = GetUserDefaultLangID();

    // Iterate over the <text> children, using the following priority-based
    // scheme to determine which one to ultimately select:
    //
    //(lowest)  0 == no node yet
    //          1 == a node with a lang attribute, but a different family
    //          2 == a node with no lang attribute
    //          3 == a node with a lang attribute from the English family
    //          4 == a node with a lang attribute and the same family, but a different subfamily
    //(highest) 5 == a node with a lang attribute and the same family and subfamily
    nPriorityCur = 0;

    if (FAILED(hr = pNodelist->get_length(&cTextNodes)))
        goto Cleanup;

    for (iTextNode=0 ; iTextNode<cTextNodes ; ++iTextNode)
    {
        LPWSTR  wszLangValue;

        // Get the node.
        if (FAILED(hr = pNodelist->get_item(iTextNode, &pNodeText)))
            goto Cleanup;

        // Get the node's 'lang' attribute value (if any).
        if (FAILED(hr = CXmlHelpers::GetAttributeStringValueFromNode(pNodeText, L"lang", &wszLangValue)))
            goto Cleanup;

        if (wszLangValue != NULL)
        {
            LANGID  langidCur = (LANGID)_wtol(wszLangValue);

            free(wszLangValue);

            if (PRIMARYLANGID(langidCur) == PRIMARYLANGID(langidPreferred))
            {
                if (SUBLANGID(langidCur) == SUBLANGID(langidPreferred))
                {
                    CheckPriAndSwap(&pNodeSelected, &pNodeText, &nPriorityCur, 5);
                    break;  // this is definitely the best we can do; no need to continue checking
                }
                else
                {
                    CheckPriAndSwap(&pNodeSelected, &pNodeText, &nPriorityCur, 4);
                }
            }
            else if (PRIMARYLANGID(langidCur) == LANG_ENGLISH)
            {
                CheckPriAndSwap(&pNodeSelected, &pNodeText, &nPriorityCur, 3);
            }
            else
            {
                CheckPriAndSwap(&pNodeSelected, &pNodeText, &nPriorityCur, 1);
            }
        }
        else
        {
            CheckPriAndSwap(&pNodeSelected, &pNodeText, &nPriorityCur, 2);
        }

        // Prepare for the next iteration.
        if (pNodeText != NULL)
        {
            pNodeText->Release();
            pNodeText = NULL;
        }
    }

    // Fail if we didn't find anything useful.
    if (pNodeSelected == NULL)
    {
        hr = E_FAIL;
        goto Cleanup;
    }

    // Get the node's text.
    if (FAILED(hr = pNodeSelected->get_text(&bstrActualText)))
        goto Cleanup;

    // Dup the text to return.
    if ((*pwszResult = wcsdup(bstrActualText)) == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    }

    // Copy the selected node if so requested.
    if (ppNodeFound != NULL)
    {
        *ppNodeFound = pNodeSelected;
        (*ppNodeFound)->AddRef();
    }

    // Success!
    hr = S_OK;

Cleanup:
    if (bstrActualText != NULL)
        SysFreeString(bstrActualText);

    if (pNodeSelected != NULL)
        pNodeSelected->Release();

    if (pNodeText != NULL)
        pNodeText->Release();

    if (pNodelist != NULL)
        pNodelist->Release();

    return hr;
}
