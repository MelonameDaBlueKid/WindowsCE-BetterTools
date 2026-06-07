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
#include <commctrl.h>   // purely for definition of CLR_NONE
#include <ocidl.h>
#include <home.h>
#include "displayattrs.h"

#ifndef HIDPIMulDiv
#define HIDPISIGN(a) (((a)<0)?-1:1)
#define HIDPIABS(a) (((a)<0)?-(a):a)
#define HIDPIMulDiv(a,b,c) ((((HIDPIABS(a)*(b))+((c)>>1))/(c))*HIDPISIGN(a))
#endif

////////////////////////////////////////////////////////////
// CDisplayAttributes::Initialize
////////////////////////////////////////////////////////////

HRESULT CDisplayAttributes::Initialize(IXMLDOMNode * pNodeDefault, IXMLDOMNode * pNodePlugin, BOOL fSelectedState)
{
    HRESULT     hr;

    // We will search the following nodes (given in XPath notation) in the
    // specified order. If we find an attribute at a "higher" level, it OVERRIDES
    // the attribute value from the "lower" level.
    //
    // ===================================================================
    // == All attributes EXCEPT bgcolor, b-border-width, b-border-color ==
    // ===================================================================
    //
    // Normal (unselected) state
    // -------------------------
    // home/default                                     lower
    // home/plugin                                      higher
    //
    // Selected state
    // --------------
    // home/default                                     lower
    // home/default/format[@state='selected']             |
    // home/plugin                                        |
    // home/plugin/format[@state='selected']            higher
    //
    // ========================================================
    // == bgcolor, b-border-width, b-border-color attributes ==
    // ========================================================
    //
    // Normal (unselected) state
    // -------------------------
    // home/default                                     lower
    // home/plugin/background                           higher
    //
    // Selected state
    // --------------
    // home/default                                     lower
    // home/plugin/background/format[@state='selected'] higher
    //
    // Note that pNodeDefault is assumed to refer to the home/default
    // node, and pNodePlugin is assumed to refer to the home/plugin node.

    if (fSelectedState)
    {
        BSTR            bstrXpathFormatSel = NULL, bstrXpathBackgroundFormatSel = NULL;
        IXMLDOMNode *   pNodeDefaultFormatSel = NULL;
        IXMLDOMNode *   pNodePluginFormatSel = NULL;
        IXMLDOMNode *   pNodePluginBackgroundFormatSel = NULL;

        // Set up the XPath expressions.
        if ((bstrXpathFormatSel = SysAllocString(L"format[@state='selected']")) == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto CleanupSelected;
        }

        if ((bstrXpathBackgroundFormatSel = SysAllocString(L"background/format[@state='selected']")) == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto CleanupSelected;
        }

        // Attempt to find the various additional nodes.
        if  (
            FAILED(hr = pNodeDefault->selectSingleNode(bstrXpathFormatSel, &pNodeDefaultFormatSel))
            ||
            FAILED(hr = pNodePlugin->selectSingleNode(bstrXpathFormatSel, &pNodePluginFormatSel))
            ||
            FAILED(hr = pNodePlugin->selectSingleNode(bstrXpathBackgroundFormatSel, &pNodePluginBackgroundFormatSel))
            )
            goto CleanupSelected;

        // Now search the nodes as described above. Note that we do not require
        // that any of the additional nodes we just looked for exist.
        if  (
            FAILED(hr = InitFromNode(pNodeDefault))
            ||
            (pNodeDefaultFormatSel != NULL && FAILED(hr = InitFromNode(pNodeDefaultFormatSel)))
            ||
            FAILED(hr = InitFromNode(pNodePlugin))
            ||
            (pNodePluginFormatSel != NULL && FAILED(hr = InitFromNode(pNodePluginFormatSel)))
            ||
            FAILED(hr = InitFromNodeBg(pNodeDefault))
            ||
            (pNodePluginBackgroundFormatSel != NULL && FAILED(hr = InitFromNodeBg(pNodePluginBackgroundFormatSel)))
            )
            goto CleanupSelected;

        hr = S_OK;

    CleanupSelected:
        if (bstrXpathBackgroundFormatSel != NULL)
            SysFreeString(bstrXpathBackgroundFormatSel);

        if (bstrXpathFormatSel != NULL)
            SysFreeString(bstrXpathFormatSel);

        if (pNodePluginBackgroundFormatSel != NULL)
            pNodePluginBackgroundFormatSel->Release();

        if (pNodePluginFormatSel != NULL)
            pNodePluginFormatSel->Release();

        if (pNodeDefaultFormatSel != NULL)
            pNodeDefaultFormatSel->Release();
    }
    else
    {
        BSTR            bstrXpathBackground = NULL;
        IXMLDOMNode *   pNodePluginBackground = NULL;

        // Set up the XPath expression.
        if ((bstrXpathBackground = SysAllocString(L"background")) == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto CleanupNormal;
        }

        // Attempt to find the additional node.
        if (FAILED(hr = pNodePlugin->selectSingleNode(bstrXpathBackground, &pNodePluginBackground)))
            goto CleanupNormal;

        // Now search in the order described above. Note that we don't
        // require the additional node to exist.
        if  (
            FAILED(hr = InitFromNode(pNodeDefault))
            ||
            FAILED(hr = InitFromNode(pNodePlugin))
            ||
            FAILED(hr = InitFromNodeBg(pNodeDefault))
            ||
            (pNodePluginBackground != NULL && FAILED(hr = InitFromNodeBg(pNodePluginBackground)))
            )
            goto CleanupNormal;

        hr = S_OK;

    CleanupNormal:
        if (pNodePluginBackground != NULL)
            pNodePluginBackground->Release();

        if (bstrXpathBackground != NULL)
            SysFreeString(bstrXpathBackground);
    }

    // The following values need to be scaled by the target-width.
    if (!FAILED(hr))
    {
        if (m_attrsSet & attridHeight)
            m_nHeight = HIDPIMulDiv(m_nHeight, GetSystemMetrics(SM_CXSCREEN), GetTargetWidth());

        if (m_attrsSet & attridFontSize)
            m_nFontSize = HIDPIMulDiv(m_nFontSize, GetSystemMetrics(SM_CXSCREEN), GetTargetWidth());

        if (m_attrsSet & attridPaddingLeft)
            m_nPaddingLeft = HIDPIMulDiv(m_nPaddingLeft, GetSystemMetrics(SM_CXSCREEN), GetTargetWidth());

        if (m_attrsSet & attridPaddingTop)
            m_nPaddingTop = HIDPIMulDiv(m_nPaddingTop, GetSystemMetrics(SM_CXSCREEN), GetTargetWidth());

        if (m_attrsSet & attridPaddingRight)
            m_nPaddingRight = HIDPIMulDiv(m_nPaddingRight, GetSystemMetrics(SM_CXSCREEN), GetTargetWidth());

        if (m_attrsSet & attridPaddingBottom)
            m_nPaddingBottom = HIDPIMulDiv(m_nPaddingBottom, GetSystemMetrics(SM_CXSCREEN), GetTargetWidth());
    }

    return hr;
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::SaveToStream
////////////////////////////////////////////////////////////

HRESULT CDisplayAttributes::SaveToStream(IStream * pStm)
{
    ULONG   ulIgnored;

    if  (
        FAILED(pStm->Write(&m_attrsSet, sizeof(m_attrsSet), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nTargetWidth, sizeof(m_nTargetWidth), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nHeight, sizeof(m_nHeight), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nFontSize, sizeof(m_nFontSize), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nFontWeight, sizeof(m_nFontWeight), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_fFontStyle, sizeof(m_fFontStyle), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nPaddingLeft, sizeof(m_nPaddingLeft), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nPaddingTop, sizeof(m_nPaddingTop), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nPaddingRight, sizeof(m_nPaddingRight), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nPaddingBottom, sizeof(m_nPaddingBottom), &ulIgnored))
        ||
        FAILED(pStm->Write(&m_nBBorderWidth, sizeof(m_nBBorderWidth), &ulIgnored))
        ||
        FAILED(WriteString(pStm, m_wszFontFace))
        ||
        FAILED(WriteString(pStm, m_wszFgColor))
        ||
        FAILED(WriteString(pStm, m_wszBgColor))
        ||
        FAILED(WriteString(pStm, m_wszBBorderColor))
        )
        return STG_E_CANTSAVE;

    return S_OK;
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::LoadFromStream
////////////////////////////////////////////////////////////

HRESULT CDisplayAttributes::LoadFromStream(IStream * pStm)
{
    ULONG   ulIgnored;

    if  (
        FAILED(pStm->Read(&m_attrsSet, sizeof(m_attrsSet), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nTargetWidth, sizeof(m_nTargetWidth), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nHeight, sizeof(m_nHeight), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nFontSize, sizeof(m_nFontSize), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nFontWeight, sizeof(m_nFontWeight), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_fFontStyle, sizeof(m_fFontStyle), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nPaddingLeft, sizeof(m_nPaddingLeft), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nPaddingTop, sizeof(m_nPaddingTop), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nPaddingRight, sizeof(m_nPaddingRight), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nPaddingBottom, sizeof(m_nPaddingBottom), &ulIgnored))
        ||
        FAILED(pStm->Read(&m_nBBorderWidth, sizeof(m_nBBorderWidth), &ulIgnored))
        ||
        FAILED(ReadString(pStm, &m_wszFontFace))
        ||
        FAILED(ReadString(pStm, &m_wszFgColor))
        ||
        FAILED(ReadString(pStm, &m_wszBgColor))
        ||
        FAILED(ReadString(pStm, &m_wszBBorderColor))
        )
        return E_FAIL;

    return S_OK;
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::GetSize
////////////////////////////////////////////////////////////

INT CDisplayAttributes::GetSize()
{
    return    sizeof(m_attrsSet)
            + sizeof(m_nTargetWidth)
            + sizeof(m_nHeight)
            + sizeof(m_nFontSize)
            + sizeof(m_nFontWeight)
            + sizeof(m_fFontStyle)
            + sizeof(m_nPaddingLeft)
            + sizeof(m_nPaddingTop)
            + sizeof(m_nPaddingRight)
            + sizeof(m_nPaddingBottom)
            + sizeof(m_nBBorderWidth)
            + 4 * sizeof(INT)           // one INT for each string: m_wszFontFace, m_wszFgColor, m_wszBgColor, m_wszBBorderColor
            + (m_wszFontFace == NULL ? 0 : sizeof(WCHAR) * wcslen(m_wszFontFace))
            + (m_wszFgColor == NULL ? 0 : sizeof(WCHAR) * wcslen(m_wszFgColor))
            + (m_wszBgColor == NULL ? 0 : sizeof(WCHAR) * wcslen(m_wszBgColor))
            + (m_wszBBorderColor == NULL ? 0 : sizeof(WCHAR) * wcslen(m_wszBBorderColor));
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::InitFromNode
////////////////////////////////////////////////////////////

HRESULT CDisplayAttributes::InitFromNode(IXMLDOMNode * pNode)
{
    HRESULT                 hr;
    LPWSTR                  wszTemp;
    IXMLDOMNamedNodeMap *   pMapAttrs = NULL;

    // Get the node's attribute map.
    if (FAILED(hr = pNode->get_attributes(&pMapAttrs)))
        goto Cleanup;

    // Get the various attribute values.
    if (FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"target-width", &m_nTargetWidth, attridTargetWidth)))
        goto Cleanup;

    if (FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"height", &m_nHeight, attridHeight)))
        goto Cleanup;

    if (FAILED(hr = GetXmlAttributeString(pMapAttrs, L"font-face", &wszTemp, attridFontFace)))
        goto Cleanup;

    if (hr != S_FALSE)
    {
        // We might already have a value from an earlier call; if
        // so, free it.
        if (m_wszFontFace != NULL)
            free(m_wszFontFace);

        m_wszFontFace = wszTemp;
    }

    if (FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"font-size", &m_nFontSize, attridFontSize)))
        goto Cleanup;

    if (FAILED(hr = GetXmlAttributeString(pMapAttrs, L"font-weight", &wszTemp, attridFontWeight)))
        goto Cleanup;

    if (hr != S_FALSE)
    {
        if (wcsicmp(wszTemp, L"normal") == 0)
            m_nFontWeight = static_cast<INT>(FW_NORMAL);
        else if (wcsicmp(wszTemp, L"bold") == 0)
            m_nFontWeight = static_cast<INT>(FW_BOLD);
        else
            m_nFontWeight = _wtoi(wszTemp);

        free(wszTemp);
    }

    if (FAILED(hr = GetXmlAttributeString(pMapAttrs, L"font-style", &wszTemp, attridFontStyle)))
        goto Cleanup;

    if (hr != S_FALSE)
    {
        if (wcsicmp(wszTemp, L"italics") == 0)
            m_fFontStyle = TRUE;
        else
            m_fFontStyle = FALSE;

        free(wszTemp);
    }

    if  (
        FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"padding-left", &m_nPaddingLeft, attridPaddingLeft))
        ||
        FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"padding-top", &m_nPaddingTop, attridPaddingTop))
        ||
        FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"padding-right", &m_nPaddingRight, attridPaddingRight))
        ||
        FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"padding-bottom", &m_nPaddingBottom, attridPaddingBottom))
        )
        goto Cleanup;

    if (FAILED(hr = GetXmlAttributeString(pMapAttrs, L"fgcolor", &wszTemp, attridFgColor)))
        goto Cleanup;

    if (hr != S_FALSE)
    {
        // We might already have a value from an earlier call; if
        // so, free it.
        if (m_wszFgColor != NULL)
            free(m_wszFgColor);

        m_wszFgColor = wszTemp;
    }

    hr = S_OK;

Cleanup:
    if (pMapAttrs != NULL)
        pMapAttrs->Release();

    return hr;
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::InitFromNodeBg
////////////////////////////////////////////////////////////

HRESULT CDisplayAttributes::InitFromNodeBg(IXMLDOMNode * pNode)
{
    HRESULT                 hr;
    LPWSTR                  wszTemp;
    IXMLDOMNamedNodeMap *   pMapAttrs = NULL;

    // Get the node's attribute map.
    if (FAILED(hr = pNode->get_attributes(&pMapAttrs)))
        goto Cleanup;

    // Get the attribute values bgcolor, b-border-color and b-border-width.
    if (FAILED(hr = GetXmlAttributeString(pMapAttrs, L"bgcolor", &wszTemp, attridBgColor)))
        goto Cleanup;

    if (hr != S_FALSE)
    {
        // We might already have a value from an earlier call; if
        // so, free it.
        if (m_wszBgColor != NULL)
            free(m_wszBgColor);

        m_wszBgColor = wszTemp;
    }

    if (FAILED(hr = GetXmlAttributeString(pMapAttrs, L"b-border-color", &wszTemp, attridBBorderColor)))
        goto Cleanup;

    if (hr != S_FALSE)
    {
        // We might already have a value from an earlier call; if
        // so, free it.
        if (m_wszBBorderColor != NULL)
            free(m_wszBBorderColor);

        m_wszBBorderColor = wszTemp;
    }

    if (FAILED(hr = GetXmlAttributeInt(pMapAttrs, L"b-border-width", &m_nBBorderWidth, attridBBorderWidth)))
        goto Cleanup;

    hr = S_OK;

Cleanup:
    if (pMapAttrs != NULL)
        pMapAttrs->Release();

    return hr;
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::ParseColor
////////////////////////////////////////////////////////////

HRESULT CDisplayAttributes::ParseColor(IHomePluginEnvironment2 * pHpe, HPLUGIN hPlugin, LPCWSTR wszAttrValue, COLORREF * pClrRet)
{
    // NOTE: IHomePluginEnvironment2::GetColor correctly handles
    // named colors (e.g., "COLOR_HOMERULE") and HTML-style colors
    // (e.g., "#FF0000") but does not handle the "transparent" case
    // correctly. So we handle that ourselves.
    if (wcscmp(wszAttrValue, L"transparent") == 0)
    {
        *pClrRet = CLR_NONE;    // meaning: transparency
        return S_OK;
    }
    else
    {
        HRESULT hr;
        BSTR    bstrColorName;

        if ((bstrColorName = SysAllocString(wszAttrValue)) != NULL)
        {
            hr = pHpe->GetColor(hPlugin, bstrColorName, pClrRet);

            SysFreeString(bstrColorName);

            return hr;
        }
        else
        {
            return E_OUTOFMEMORY;
        }
    }
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::WriteString
////////////////////////////////////////////////////////////

/*static*/ HRESULT CDisplayAttributes::WriteString(IStream * pStm, LPCWSTR wsz)
{
    INT     cch = (wsz == NULL) ? 0 : wcslen(wsz);
    ULONG   ulIgnored;

    if (FAILED(pStm->Write(&cch, sizeof(cch), &ulIgnored)))
        return STG_E_CANTSAVE;

    if (cch != 0)
    {
        if (FAILED(pStm->Write(wsz, sizeof(WCHAR) * cch, &ulIgnored)))
            return STG_E_CANTSAVE;
    }

    return S_OK;
}

////////////////////////////////////////////////////////////
// CDisplayAttributes::ReadString
////////////////////////////////////////////////////////////

/*static*/ HRESULT CDisplayAttributes::ReadString(IStream * pStm, LPWSTR * pwsz)
{
    INT     cch;
    ULONG   ulIgnored;
    LPWSTR  wsz;

    if (FAILED(pStm->Read(&cch, sizeof(cch), &ulIgnored)))
        return E_FAIL;

    if ((wsz = static_cast<WCHAR *>(malloc(sizeof(WCHAR) * (cch + 1)))) == NULL)
        return E_OUTOFMEMORY;

    if (cch != 0)
    {
        if (FAILED(pStm->Read(wsz, sizeof(WCHAR) * cch, &ulIgnored)))
        {
            free(wsz);
            return E_FAIL;
        }
    }

    wsz[cch] = L'\0';

    *pwsz = wsz;

    return S_OK;
}
