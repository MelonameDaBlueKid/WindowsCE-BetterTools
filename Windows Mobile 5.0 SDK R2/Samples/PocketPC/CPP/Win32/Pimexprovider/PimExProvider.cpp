//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.


#include "PimExProvider.h"



/////////////////////////////////////////////////////////////////////////////
// CSampleProvider::CSampleProvider()
//
// Purpose:
//      Default constructor
//
// Parameters:
//      void
//
// Returns:
//      void
//
// Called by:
//      ATL when instantiating our coclass
//
CSampleProvider::CSampleProvider():m_polApp(NULL)
{   
    return;
}


/////////////////////////////////////////////////////////////////////////////
// CSampleProvider::~CSampleProvider()
//
// Purpose:
//      Virtual destructor
//
// Parameters:
//      void
//
// Returns:
//      void
//
// Called by:
//      Release() when deleting our coclass
//
CSampleProvider::~CSampleProvider()
{
    UnInitPOOM(m_polApp);
    
    return;
}


/////////////////////////////////////////////////////////////////////////////
// EnsurePOOM
//
// Purpose:
//      Makes sure POOM is init and if not, does the init.
//
// Parameters:
//      void
//
// Returns:
//      S_OK    Success
//      ...
//
HRESULT CSampleProvider::EnsurePOOM()
{
    HRESULT hr = S_OK;

    // If we haven't init POOM then do so.
    if (NULL == m_polApp)
    {
        hr  = InitPOOM(&m_polApp);
    }    

    return hr;        
}



/////////////////////////////////////////////////////////////////////////////
// IPimSrcContactSummaryCard::Display
//
// Purpose:
//      Source-specific version of IItem::Display() for contacts.
//      Displays the following info in a message box
//          FileAs Name
//          Source Provider ID
//          OID
//          hwnd Parent
//
// Parameters:
//      IN      hwndParent      Parent HWND to use for UI
//      IN      pitem           IItem instance to display
//
// Returns values:
//      S_OK                    Success
//      E_FAIL                  Failure
//
STDMETHODIMP CSampleProvider::Display(HWND hwndParent, IItem *pitem)
{    
    HRESULT     hr          = E_FAIL;
    CEPROPVAL   *rgVals     = NULL;
    ULONG       cbBuffer    = 0;
    HANDLE      hHeap       = GetProcessHeap();
    CEPROPID    rgPropID[]  = { PIMPR_SOURCE_ID, PIMPR_OID, PIMPR_FILEAS };
    const WORD  cProps      = ARRAYSIZE(rgPropID);
    TCHAR       szBuffer[MAX_BUFFER];
    const TCHAR c_szFormat[] = 
        TEXT("Name = %s\nSourceID = %lu\nOid = 0x%x\nParent Hwnd= 0x%x\n\n");

    hr = EnsurePOOM();
    CHR(hr);
    
    CBR(NULL != pitem);

    // Get the props we want to display for the item.  Let POOM allocate the memory.
    hr = pitem->GetProps(rgPropID, CEDB_ALLOWREALLOC, cProps, &rgVals, &cbBuffer, hHeap);
    CHR(hr);
    
    // Format the string to display in the message box
    hr = StringCchPrintf(szBuffer, 
        ARRAYSIZE(szBuffer), 
        c_szFormat, 
        rgVals[2].val.lpwstr, rgVals[0].val.lpwstr, rgVals[1].val.lpwstr, hwndParent);
    CHR(hr);
    
    // Display our customized summayr card (as a message box).
    // Ideally, you would want to create a more involved dialog to display the info
    MessageBox(NULL, 
        szBuffer,
        TEXT("Custom Summary Card"),
        MB_SETFOREGROUND | MB_OK);


Error:    
    
    if (NULL != rgVals)
    {
        // Free the memory POOM alloced on the heap for the props we got.
        HeapFree(hHeap, 0, rgVals);
    }
    
    DEBUGMSG(FAILED(hr), (L"CSampleProvider::Display  -- HR failure = 0x%x", hr));    
    
    return hr;
}


/////////////////////////////////////////////////////////////////////////////
// IPimSrcContactListIcon::Paint
//
// Purpose:
//      This method enables a source to draw its own icon in the contacts
//      list view.
//
// Parameters:
//      IN      pscd            Painting information that the source can use
//      IN      pcepvOID        The PIMPR_OID (POOM OID) value for the current item. Could be NULL.
//
// Returns values:
//      S_OK                    The source drew the picture for this contact
//      E_INVALIDARG            One of the arguments was invalid
//
STDMETHODIMP CSampleProvider::Paint(const SRCCUSTOMDRAW *pscd, CEOID oid)
{
    HRESULT hr          = E_FAIL;
    IItem   *pItem      = NULL;
    IStream *pStream    = NULL;
    HBITMAP hBmp        = 0;        
    HDC     hdcMem      = NULL;
    BITMAP  bmpInfo     = {0};
    HGDIOBJ hGdiObj     = 0;
    int     iWidth      = 0,
            iHeight     = 0;

    hr = EnsurePOOM();
    CHR(hr);

    // Parm check
    CBR(0 != oid);
    CBR(NULL != pscd);
    
    // Get the IItem from the OID
    hr = m_polApp->GetItemFromOidEx(oid, 0, &pItem);
    CHR(hr);    
    CBR(NULL != pItem);

    // Get the picture from the IItem
    hr = pItem->OpenProperty(PIMPR_PICTURE, GENERIC_READ|GENERIC_WRITE, &pStream);
    CHR(hr);
    CBR(NULL != pStream);

    // Get the HBITMAP from the stream
    hBmp = LoadImageStream(pStream);
    CBR(NULL != hBmp);
        
    // Calculate the height and width of the RECT to scale the picture to.
    iWidth  = (pscd->rc.right - pscd->rc.left);
    iHeight = (pscd->rc.bottom - pscd->rc.top);

    CBR(GetObject(hBmp, sizeof(bmpInfo), &bmpInfo));

    hdcMem = CreateCompatibleDC(pscd->hdc);
    CBR(hdcMem);
        
    hGdiObj = SelectObject(hdcMem, hBmp);

    // Sacle the bitmap from the source HDC to the destination HDC (ie the 
    // contacts app listview).
    CBR(StretchBlt( pscd->hdc, 
        pscd->rc.left, pscd->rc.top, 
        iWidth, iHeight,
        hdcMem, 
        0, 0,
        bmpInfo.bmWidth, bmpInfo.bmHeight,
        SRCCOPY));  
    
Error:
    if (hBmp)
    {
        DeleteObject(hBmp);
    }

    if (hdcMem)
    {
        DeleteDC(hdcMem);
    }
    
    RELEASE_OBJ(pItem);
    RELEASE_OBJ(pStream);

    // If we get here with a failing hresult, the contacts app will just draw the
    // default contact icon.   
    return hr;
}





