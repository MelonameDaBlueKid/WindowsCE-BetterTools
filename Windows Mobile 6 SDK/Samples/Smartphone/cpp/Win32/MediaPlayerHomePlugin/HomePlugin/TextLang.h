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

#ifndef _TEXTLANG_H_
#define _TEXTLANG_H_

////////////////////////////////////////////////////////////
// GetLocalizedTextNodeString
//
// Given an IXMLDOMNode * for a node with one or more <text>
// node children, searches through the children, looking for
// the one with the best lang attribute match. Returns the
// content of that node as a string.
//
// Optionally (if ppNodeFound != NULL) returns the <text>
// node that contained the best match.
//
// NOTE
// ----
// If this function succeeds, the caller must ultimately free
// the string by passing it to free().
////////////////////////////////////////////////////////////

HRESULT GetLocalizedTextNodeString(IXMLDOMNode * pNode, LPWSTR * pwszResult, IXMLDOMNode ** ppNodeFound);

#endif // _TEXTLANG_H_

