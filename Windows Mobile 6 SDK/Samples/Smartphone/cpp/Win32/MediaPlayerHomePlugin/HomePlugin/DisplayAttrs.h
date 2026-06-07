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

#ifndef _DISPLAYATTRS_H_
#define _DISPLAYATTRS_H_

#include "..\common\xmlsupport.h"

////////////////////////////////////////////////////////////
// CDisplayAttributes
//
// This class encapsulates the display attributes of our
// homescreen plugin, as read from the XML file.
////////////////////////////////////////////////////////////

class CDisplayAttributes
{
public:
    ////////////////////////////////////////
    // Constructor, destructor
    ////////////////////////////////////////
    CDisplayAttributes()
        : m_attrsSet(0),
          m_nTargetWidth(0),
          m_nHeight(0),
          m_wszFontFace(NULL),
          m_nFontSize(0),
          m_fFontStyle(FALSE),
          m_nFontWeight(0),
          m_nPaddingLeft(0),
          m_nPaddingTop(0),
          m_nPaddingRight(0),
          m_nPaddingBottom(0),
          m_wszFgColor(NULL),
          m_wszBgColor(NULL),
          m_wszBBorderColor(NULL),
          m_nBBorderWidth(0)
    {
    }

    ~CDisplayAttributes()
    {
        if (m_wszFontFace != NULL)
            free(m_wszFontFace);

        if (m_wszFgColor != NULL)
            free(m_wszFgColor);

        if (m_wszBgColor != NULL)
            free(m_wszBgColor);

        if (m_wszBBorderColor != NULL)
            free(m_wszBBorderColor);
    }

    ////////////////////////////////////////
    // Initialize
    //
    // Initialize this instance given the <default>
    // node and the <plugin> node from the .home.xml
    // file.
    //
    // This method will actually search various
    // child nodes of the two specified nodes, according
    // to standard behavior. See implementation.
    ////////////////////////////////////////

    HRESULT Initialize( IXMLDOMNode *   pNodeDefault,
                        IXMLDOMNode *   pNodePlugin,
                        BOOL            fSelectedState);

    ////////////////////////////////////////
    // Get* methods
    ////////////////////////////////////////

    INT GetTargetWidth()
    {
        if (m_attrsSet & attridTargetWidth)
            return m_nTargetWidth;
        else
            return 176;                     // default
    }

    INT GetHeight()
    {
        if (m_attrsSet & attridHeight)
            return m_nHeight;
        else
            return 40;                      // default
    }

    LPCWSTR GetFontFace()
    {
        if (m_attrsSet & attridFontFace)
            return m_wszFontFace;
        else
            return L"Nina";                 // default
    }

    INT GetFontSize()
    {
        if (m_attrsSet & attridFontSize)
            return m_nFontSize;
        else
            return 0;                       // default
    }

    INT GetFontWeight()
    {
        if (m_attrsSet & attridFontWeight)
            return m_nFontWeight;
        else
            return FW_NORMAL;               // default
    }

    // TRUE if italic, FALSE if normal
    BOOL GetFontStyle()
    {
        if (m_attrsSet & attridFontStyle)
            return m_fFontStyle;
        else
            return FALSE;                   // default
    }

    INT GetLeftPadding()
    {
        if (m_attrsSet & attridPaddingLeft)
            return m_nPaddingLeft;
        else
            return 0;                       // default
    }

    INT GetTopPadding()
    {
        if (m_attrsSet & attridPaddingTop)
            return m_nPaddingTop;
        else
            return 0;                       // default
    }

    INT GetRightPadding()
    {
        if (m_attrsSet & attridPaddingRight)
            return m_nPaddingRight;
        else
            return 0;                       // default
    }

    INT GetBottomPadding()
    {
        if (m_attrsSet & attridPaddingBottom)
            return m_nPaddingBottom;
        else
            return 0;                       // default
    }

    // Returns CLR_NONE to mean transparency.
    //
    // Environment interface pointer and plugin handle are
    // needed for color translation.
    COLORREF GetFgColor(IHomePluginEnvironment2 * pHpe, HPLUGIN hPlugin)
    {
        if (m_attrsSet & attridFgColor)
        {
            COLORREF    clr;

            if (SUCCEEDED(ParseColor(pHpe, hPlugin, m_wszFgColor, &clr)))
                return clr;
        }

        return RGB(0xFF, 0xFF, 0xFF);       // default
    }

    // Returns CLR_NONE to mean transparency.
    //
    // Environment interface pointer and plugin handle are
    // needed for color translation.
    COLORREF GetBgColor(IHomePluginEnvironment2 * pHpe, HPLUGIN hPlugin)
    {
        if (m_attrsSet & attridBgColor)
        {
            COLORREF    clr;

            if (SUCCEEDED(ParseColor(pHpe, hPlugin, m_wszBgColor, &clr)))
                return clr;
        }

        return CLR_NONE;                    // default: transparent
    }

    // Returns CLR_NONE to mean transparency.
    //
    // Environment interface pointer and plugin handle are
    // needed for color translation.
    COLORREF GetBBorderColor(IHomePluginEnvironment2 * pHpe, HPLUGIN hPlugin)
    {
        if (m_attrsSet & attridBBorderColor)
        {
            COLORREF    clr;

            if (SUCCEEDED(ParseColor(pHpe, hPlugin, m_wszBBorderColor, &clr)))
                return clr;
        }

        return RGB(0x00, 0x00, 0x00);       // default
    }

    INT GetBBorderWidth()
    {
        if (m_attrsSet & attridBBorderWidth)
            return m_nBBorderWidth;
        else
            return 0;                       // default
    }

    ////////////////////////////////////////
    // Stream-related methods
    ////////////////////////////////////////

    // Save all attributes to the specified stream.
    HRESULT SaveToStream(IStream * pStm);

    // Load all attributes from the specified stream (assumed to have
    // been written to by SaveToStream).
    HRESULT LoadFromStream(IStream * pStm);

    // Get the size required for all attributes.
    INT GetSize();

private:
    ////////////////////////////////////////
    // ATTRID enum
    //
    // Each attribute is associated with an
    // ATTRID value. We use these to keep track
    // of which attributes we actually found.
    ////////////////////////////////////////
    enum ATTRID
    {
        attridTargetWidth           = 0x0001,
        attridHeight                = 0x0002,
        attridFontFace              = 0x0004,
        attridFontSize              = 0x0008,
        attridFontStyle             = 0x0010,
        attridFontWeight            = 0x0020,
        attridPaddingLeft           = 0x0040,
        attridPaddingTop            = 0x0080,
        attridPaddingRight          = 0x0100,
        attridPaddingBottom         = 0x0200,
        attridFgColor               = 0x0400,
        attridBgColor               = 0x0800,
        attridBBorderWidth          = 0x1000,
        attridBBorderColor          = 0x2000
    };

    ////////////////////////////////////////
    // Helper methods
    ////////////////////////////////////////

    // This method searches a particular node for all attributes
    // EXCEPT bgcolor, b-border-color and b-border-width, setting
    // attribute values (and m_attrsSet) as appropriate.
    HRESULT InitFromNode(IXMLDOMNode * pNode);

    // This method searches a particular node for the attributes
    // bgcolor, b-border-color and b-border-width, setting attribute
    // values (and m_attrsSet) as appropriate.
    HRESULT InitFromNodeBg(IXMLDOMNode * pNode);

    // Convert an attribute value from the .home.xml file to a COLORREF.
    //
    // Environment interface pointer and plugin handle are needed for
    // color translation.
    HRESULT ParseColor(IHomePluginEnvironment2 * pHpe, HPLUGIN hPlugin, LPCWSTR wszAttrValue, COLORREF * pClrRet);

    // Helpers for reading and writing strings in an IStream.
    static HRESULT WriteString(IStream * pStm, LPCWSTR wsz);
    static HRESULT ReadString(IStream * pStm, LPWSTR * pwsz);

    // This method simply calls the helper method to fetch the actual
    // attribute value. If the attribute exists, this method sets the
    // specified ATTRID bit in m_attrsSet. If the attribute does not
    // exist, this method returns S_FALSE.
    HRESULT GetXmlAttributeString(IXMLDOMNamedNodeMap * pMapAttrs, LPCWSTR wszAttrName, LPWSTR * pwszSet, ATTRID attrid)
    {
        HRESULT     hr;
        LPWSTR      wszTemp;

        if (FAILED(hr = CXmlHelpers::GetAttributeStringValueFromAttrMap(pMapAttrs, wszAttrName, &wszTemp)))
            return hr;

        if (hr != S_FALSE)
        {
            *pwszSet = wszTemp;
            m_attrsSet |= attrid;
        }

        return hr;
    }

    // This method simply calls the helper method to fetch the actual
    // attribute value. If the attribute exists, this method sets the
    // specified ATTRID bit in m_attrsSet. If the attribute does not
    // exist, this method returns S_FALSE.
    HRESULT GetXmlAttributeInt(IXMLDOMNamedNodeMap * pMapAttrs, LPCWSTR wszAttrName, INT * pnSet, ATTRID attrid)
    {
        HRESULT     hr;
        INT         nTemp;

        if (FAILED(hr = CXmlHelpers::GetAttributeIntValueFromAttrMap(pMapAttrs, wszAttrName, &nTemp)))
            return hr;

        if (hr != S_FALSE)
        {
            *pnSet = nTemp;
            m_attrsSet |= attrid;
        }

        return hr;
    }

    ////////////////////////////////////////
    // Data
    ////////////////////////////////////////
    DWORD       m_attrsSet;         // Bitflags indicating which attrs were set
    INT         m_nTargetWidth;     // Width of target device, in pixels
    INT         m_nHeight;          // Height of plugin
    LPWSTR      m_wszFontFace;      // Facename of font to use when drawing
    INT         m_nFontSize;        // Point size of font
    INT         m_nFontWeight;      // Weight of font
    BOOL        m_fFontStyle;       // If TRUE, use italic font (else normal)
    INT         m_nPaddingLeft;     // Left padding, in pixels
    INT         m_nPaddingTop;      // Top padding, in pixels
    INT         m_nPaddingRight;    // Right padding, in pixels
    INT         m_nPaddingBottom;   // Bottom padding, in pixels
    LPWSTR      m_wszFgColor;       // Foreground color attribute (unparsed)
    LPWSTR      m_wszBgColor;       // Background color attribute (unparsed)
    LPWSTR      m_wszBBorderColor;  // Bottom border color attribute (unparsed)
    INT         m_nBBorderWidth;    // Width of bottom border
};

#endif // _DISPLAYATTRS_H_
