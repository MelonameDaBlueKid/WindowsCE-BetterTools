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

////////////////////////////////////////////////////////////////////////////
// Function:
//      InitPOOM
//
// Purpose:
//      Created the POOM COM obj and does a Logon.
//
// Parameters:
//      IN/OUT     ppolApp      Ptr to ptr to POOM app that needs to be init
//
// Returns values:
//      S_OK                        Success
//      ...
//
HRESULT InitPOOM(IPOutlookApp2 **ppolApp)
{
    HRESULT hr  = E_FAIL;

    CBR(NULL != ppolApp);

    // Init COM
    hr = CoInitializeEx(NULL, 0);
    CHR(hr);
    

    // Create the POOM app object
    hr = CoCreateInstance(CLSID_Application, 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        IID_IPOutlookApp2, 
        (LPVOID *) ppolApp);
    CHR(hr);

    // Logon to POOM
    hr = (*ppolApp)->Logon(NULL);
    if (FAILED(hr))
    {
        *ppolApp = NULL;
    }
    CHR(hr);

Error:
    return hr;    
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      UnInitPOOM
//
// Purpose:
//      Logoff POOM and destroy the POOM COM obj.
//
// Parameters:
//      IN     polApp           POOM obj to uninit
//
// Returns values:
//      S_OK                        Success
//      ...
//
HRESULT UnInitPOOM(IPOutlookApp2 *polApp)
{
    HRESULT hr = E_FAIL;
    
    CBR(NULL != polApp);
    
    // Logoff POOM
    hr = polApp->Logoff();

Error:    
    RELEASE_OBJ(polApp);
    CoUninitialize();

    return hr;    
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      _HBITMAPFromImage
//
// Purpose:
//      Returns an HBITMAP for the given IImage obj.  Uses GDI+ to do this.
//
// Parameters:
//      IN     pImage           GDI+ IImage obj.
//
// Returns values:
//      Non-NULL HBITMAP        Success
//      ...
//
HBITMAP HBITMAPFromImage(IImage *pImage)
{
    HBITMAP     hbmResult       = NULL;
    COLORREF    crBackColor     = (COLORREF) GetSysColor(COLOR_WINDOW);
    ImageInfo   ii              = {0};
    

    if (!pImage)
    {
        return NULL;
    }

    // Get image width/height    
    if (SUCCEEDED(pImage->GetImageInfo(&ii)))
    {
        // Create HDC
        HDC hDC = CreateCompatibleDC(NULL);
        
        if (hDC != NULL)
        {
            // Create DIB section
            BITMAPINFO  bmi     = { 0 };
            void        *pv     = NULL;
            HBITMAP     hbmNew;

            
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);            
            bmi.bmiHeader.biWidth       = ii.Width;
            bmi.bmiHeader.biHeight      = ii.Height;
            bmi.bmiHeader.biPlanes      = 1;
            bmi.bmiHeader.biBitCount    = (SHORT)GetDeviceCaps(hDC, BITSPIXEL);
            bmi.bmiHeader.biCompression = BI_RGB;

            
            if ((hbmNew = CreateDIBSection(  hDC,
                                             &bmi,
                                             DIB_RGB_COLORS,
                                             &pv,
                                             NULL,
                                             0)) != NULL)
            {

                // Select DIB into DC
                HBITMAP hbmOld = (HBITMAP)SelectObject(hDC, hbmNew);
                if (hbmOld != NULL)
                {
                    RECT rc = { 0, 0, ii.Width, ii.Height };
    
                    // Clear the bitmap using the background color
                    COLORREF clrSave = SetBkColor(hDC, crBackColor);
                    ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
                    SetBkColor(hDC, clrSave);


                    // Draw into DC/DIB
                    if (SUCCEEDED(pImage->Draw(hDC, &rc, NULL)))
                    {
                        hbmResult   = hbmNew;
                        hbmNew      = NULL;
                    }
    
                    SelectObject(hDC, hbmOld);
                }

                if (hbmNew != NULL)
                {
                    DeleteObject(hbmNew);
                }
                
            }
    
            DeleteDC(hDC);
        }
    }
    
    return hbmResult;
}


////////////////////////////////////////////////////////////////////////////
// Function:
//      LoadImageStream
//
// Purpose:
//      Equivalent function to SHLoadImageFromFile, except that this loads 
//      the image from an IStream. Needed to load an image for Contact.
//
// Parameters:
//      IN     pStream           IStream encoded image to create an HBITMAP for.
//
// Returns values:
//      Non-NULL HBITMAP         Success
//      ...
//
HBITMAP LoadImageStream(IStream *pStream)
{
    HBITMAP         hbmReturn       = NULL;
    IImagingFactory *pImgFactory    = NULL;    

 
    if (!pStream)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }
    
    // Create the imaging class factory
    if (SUCCEEDED(CoCreateInstance( CLSID_ImagingFactory,
                                    NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_IImagingFactory,
                                    (void **)&pImgFactory)))
    {
        // Create GDI+ image from stream
        IImage *pImage = NULL;

        if (SUCCEEDED(pImgFactory->CreateImageFromStream(pStream, &pImage)))
        {
            hbmReturn = HBITMAPFromImage(pImage);
        }
        
        RELEASE_OBJ(pImage);
    }

    RELEASE_OBJ(pImgFactory);
    return hbmReturn;
}


