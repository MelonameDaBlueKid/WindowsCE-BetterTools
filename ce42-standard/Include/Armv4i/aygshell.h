//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
#ifndef _AYGSHELL_H_
#define _AYGSHELL_H_

// aygshell.h - exported functions from aygshell'

#include <shellsdk.h>
#include <shlobj.h>

// USED BY SHDONEBUTTON
//
// Disable the navigation button bestowed by the Shell
// (NOTE: this only works if WS_CAPTION is not set)
#define WS_NONAVDONEBUTTON WS_MINIMIZEBOX



//++++++
//
// SHEnumPropSheetHandlers
//

// this is the maximum number of extension pages that can be added
// to a property sheet

#define MAX_EXTENSION_PAGES 6

// For property sheet extension - enumerates the subkeys under the
// class key hkey.  For each handler, the class is instantiated,
// queried for IShellPropSheetExt and AddPages is called.  The
// handle to the page is inserted in the array prghPropPages, and
// the pointer to the IShellPropSheetExt is added to prgpispse
// with one reference from the caller (these should be released
// by the caller after PropertySheet() is called).  These two arrays
// should be allocated before calling SHEnumPropSheetHandlers.
//
// Typical usage of this function would be:
//
//  - allocate an array of HPROPSHEETPAGEs for the standard pages plus
//    MAX_EXTENSION_PAGES extension pages
//  - fill a PROPSHEETPAGE struct and call CreatePropertySheetPage() on each
//    standard page
//  - store the HPROPSHEETPAGE for the standard pages at the beginning of
//    the array
//  - open a registry key where the app has defined ISV extension
//  - allocate an array of MAX_EXTENSION_PAGES IShellPropSheetExt interface
//    pointers
//  - call SHEnumPropSheetHandlers(), passing in the hkey, a pointer to the
//    first free HPROPSHEETPAGE array element, and a pointer to the array of
//    IShellPropSheetExt interface pointers
//  - call PropertySheet() to display the property sheet
//  - Release each interface pointer in the array of interface pointers
//  - free both arrays

// SHEnumPropSheetHandlers assumes that prghPropPages and prgpispse have been
// allocated with enough space for up to MAX_EXTENSION_PAGES elements.  The
// number of pages added is returned in *pcPages.

BOOL SHEnumPropSheetHandlers(HKEY hkey, int *pcPages, HPROPSHEETPAGE *prghPropPages, IShellPropSheetExt **prgpispse);

//
// End SHEnumPropSheetHandlers
//
//------


// used by SHCreateNewItem
#undef  INTERFACE
#define INTERFACE   INewMenuItemServer

DECLARE_INTERFACE_(INewMenuItemServer, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    STDMETHOD(CreateNewItem)             (THIS_ HWND hwndParent) PURE;
};

#endif // _AYGSHELL_H_
