//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

#pragma once

#include <windows.h>

// Include ATL headers.
#define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

// SDK macros (ie CBR, CHR, RELEASE_OBJ etc are defined here).
#include "Macros.h"

// Product headers
#include <pimstore.h>       // For POOM and PIM APIs 
#include <aygshell.h>       // For Shell APIs
#include <commctrl.h>       // For UI common controls
#include <imaging.h>        // For Imaging functions (ie IImagingFactory etc).
#include <RegExt.h>         // For registry helper functions

#define MAX_BUFFER                  1024

// Custom error code if we can't do anymore customizations
#define E_PIMSRC_NO_AVAILABLE_ID    MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x00)

// Defines what customization we are implementing in this source provider
#define PIM_CUSTOMIZATIONS          PIMSRC_CUSTOM_CONTACTS_SUMMARY_CARD | \
                                    PIMSRC_CUSTOM_CONTACTS_PAINT_LIST_ICON | \
                                    PIMSRC_CUSTOM_APPOINTMENTS_COLORS

// Defines the Outlook item types the customizations apply to
#define PIM_CUSTOMIZED_TYPES        PIMSRC_TYPE_CONTACTS | PIMSRC_TYPE_APPOINTMENTS

// Consts (see Const.cpp for defined values)
extern HANDLE           g_currentInstance;
extern const GUID       CLSID_SampleProvider;
extern const LPTSTR     g_szCLSID_SampleProvider;
extern const LPWSTR     g_szDllName;
extern const COLORREF   g_crCalendarBackground;
extern const WCHAR      g_wszOurKey[];
extern const WCHAR      g_wszOurValueName[];


///////////////////////////////////////////////////////////////////////////////
//
// Forward Funciton declarations
//

// Function to Init and UnInit POOM. Used for the DLL setup and CSampleProvider class
HRESULT InitPOOM(IPOutlookApp2 **ppolApp);
HRESULT UnInitPOOM(IPOutlookApp2 *polApp);

// Function to register/unregister this source provider
HRESULT LookupSourceId(DWORD *pdwSourceId);
HRESULT RegisterPIMSource();
HRESULT UnregisterPIMSource();

// Function to so some additional setup for the PIM source provider
HRESULT ItemSetup(IPOutlookApp2 *polApp, int olItemType, BOOL bInstall);

// Function to get HMITMAP from IStream
HBITMAP LoadImageStream(IStream *pStream);


///////////////////////////////////////////////////////////////////////////////
//
// SampleProvider class defination
//
class CSampleProvider :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CSampleProvider, &CLSID_SampleProvider>,
    public IPimSrcContactListIcon,
    public IPimSrcContactSummaryCard
{
public:
    // Misc. ATL stuff...
    DECLARE_NO_REGISTRY();
    DECLARE_PROTECT_FINAL_CONSTRUCT()
    BEGIN_COM_MAP(CSampleProvider)
        COM_INTERFACE_ENTRY(IPimSrcContactListIcon)
        COM_INTERFACE_ENTRY(IPimSrcContactSummaryCard)
    END_COM_MAP()

protected:
    // Our lifetime is managed by CComObject<>, which derives from us - therefore,
    // our constructor and destructor should be protected, so no one else can
    // create or destroy us.
    CSampleProvider();
    virtual         ~CSampleProvider();

    HRESULT EnsurePOOM();


    // All access to our methods should be through our interface pointers.

    // IPimSrcContactSummaryCard
    STDMETHOD(Display)(HWND hwndParent, IItem *pitem);

    // IPimSrcContactListIcon
    STDMETHOD(Paint)(const SRCCUSTOMDRAW *pscd, CEOID oid);        

private:
    IPOutlookApp2   *m_polApp;    
    
};


