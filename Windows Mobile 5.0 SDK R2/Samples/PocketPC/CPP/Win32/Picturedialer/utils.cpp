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

#include <windows.h>
#include <windowsx.h>
#include <aygshell.h>
#include <imaging.h>
#include "utils.h"
#include "macros.h"






// **************************************************************************
// Function Name: GetStreamSize
// 
// Purpose: Given an IStream, returns the size of the stream.  This is needed
//          for streams that do not support the Stat method
//
// Arguments:
//    IN  IStream*  pStream - stream to determine size for
//    OUT ULONG*    pulSize - size of stream
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//
// Side Effects:
//    The stream pointer always resets to the beginning
//

HRESULT GetStreamSize(IStream* pStream, ULONG* pulSize)
{
    HRESULT hr;
    LARGE_INTEGER  li = {0};
    ULARGE_INTEGER uliZero = {0};
    ULARGE_INTEGER uli;

    CBR(pStream != NULL && pulSize != NULL);

    hr = pStream->Seek(li, STREAM_SEEK_END, &uli);
    CHR(hr);

    *pulSize = uli.LowPart;
    hr = S_OK;

Error:
    if (SUCCEEDED(hr))
    {
        // Move the stream back to the beginning of the file
        hr = pStream->Seek(li, STREAM_SEEK_SET, &uliZero);
    }

    return hr;
}


// **************************************************************************
// Function Name: HBITMAPFromImage
// 
// Purpose: Convert IImage to HBITMAP.  If bitmap has transparency, the
//    background will be filled with the color passed in
//
// Arguments:
//    IN  IImage*   pImage      - pointer to the IImage
//    IN  COLORREF  crBackColor - color of the background
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//
HBITMAP HBITMAPFromImage
(
    IN IImage * pImage,
    IN COLORREF crBackColor
    )
{
    HRESULT    hr;
    HBITMAP    hbmResult = NULL;
    ImageInfo  ii;
    HDC        hDC = NULL;
    HBITMAP    hbmNew = NULL;
    void *     pv;
    BITMAPINFO bmi = { 0 };
    HBITMAP    hbmOld = NULL;
    RECT       rc = { 0 };

    CBR(pImage != NULL);

    // Get image width/height
    hr = pImage->GetImageInfo(&ii);
    CHR(hr);

    // Create HDC
    hDC = CreateCompatibleDC(NULL);
    CBR(hDC != NULL);

    // Create DIB section
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = ii.Width;
    bmi.bmiHeader.biHeight      = ii.Height;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = (SHORT) max(16, GetDeviceCaps(hDC, BITSPIXEL));
    bmi.bmiHeader.biCompression = BI_RGB;

    hbmNew = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, &pv, NULL, 0);
    CBR(hbmNew != NULL);

    // Select DIB into DC
    hbmOld = (HBITMAP)SelectObject(hDC, hbmNew);

    rc.right = ii.Width;
    rc.bottom = ii.Height;

    // Clear the bitmap using the background color
    DrawRect(hDC, &rc, crBackColor); 

    // Draw into DC/DIB
    hr = pImage->Draw(hDC, &rc, NULL);
    CHR(hr);

    hbmResult = hbmNew;
    hbmNew = NULL;

Error:
    if (hbmNew)
    {
        DeleteObject(hbmNew);       
    }

    if (hDC)
    {
        if (hbmOld)
        {
            SelectObject(hDC, hbmOld);
        }

        DeleteDC(hDC);
    }

    return hbmResult;
}


// **************************************************************************
// Function Name: ScaleProportional
// 
// Purpose: Scale the width and height to fit the given width and height
//          but maintain the proportion
//
// Arguments:
//    IN     UINT  uFitToWidth     - width of source image
//    IN     UINT  uFitToHeight    - height of source image
//    IN/OUT UINT* puWidthToScale  - width of image to scale to
//    IN/OUT UINT* puHeightToScale - height of image to scale to
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//
void ScaleProportional(UINT uFitToWidth, UINT uFitToHeight, UINT *puWidthToScale, UINT *puHeightToScale)
{
    HRESULT hr;

    CBR(puWidthToScale != NULL && puHeightToScale != NULL);

    // Scale (*puWidthToScale, *puHeightToScale) to fit within (uFitToWidth, uFitToHeight), while
    // maintaining the aspect ratio
    int nScaledWidth = MulDiv(*puWidthToScale, uFitToHeight, *puHeightToScale);

    // If we didn't overflow and the scaled width does not exceed bounds
    if (nScaledWidth >= 0 && nScaledWidth <= (int)uFitToWidth)
    {
        *puWidthToScale  = nScaledWidth;
        *puHeightToScale = uFitToHeight;
    }
    else
    {
        *puHeightToScale = MulDiv(*puHeightToScale, uFitToWidth, *puWidthToScale);
        
        // The height *must* be within the bounds [0, uFitToHeight] since we overflowed
        // while fitting to height
        ASSERT(*puHeightToScale >= 0 && *puHeightToScale <= uFitToHeight);
        
        *puWidthToScale  = uFitToWidth;
    }

Error:
    return;
}


// **************************************************************************
// Function Name: GetBitmapFromStream
// 
// Purpose: Convert an IStream to an HBITMAP and return the new dimensions
//
// Arguments:
//    IN     UINT  uFitToWidth     - width of source image
//    IN     UINT  uFitToHeight    - height of source image
//    OUT UINT* puWidth  - width of image to scale to
//    OUT UINT* puHeight - height of image to scale to
//
// Return Values:
//    HRESULT - S_OK if success, failure code if not
//
HRESULT GetBitmapFromStream(IStream* pStream, HBITMAP* phBitmap, UINT* puWidth, UINT* puHeight)
{
    HRESULT hr;
    HBITMAP           hBitmap = NULL;

    IImagingFactory*  pFactory = NULL;
    IImage*           pImage   = NULL;
    IImage*           pThumbnail = NULL;
    ImageInfo         imgInfo = {0};

    CBR(pStream != NULL && phBitmap != NULL && puWidth != NULL && puHeight != NULL);

    // Use a little imaging help
    hr = CoCreateInstance(CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IImagingFactory, (void**) &pFactory);
    CHR(hr);
    
    hr = pFactory->CreateImageFromStream(pStream, &pImage);
    CHR(hr);

    hr = pImage->GetImageInfo(&imgInfo);
    CHR(hr);
    CBR(imgInfo.Width > 0 && imgInfo.Height > 0);

    // Scale to the new size
    ScaleProportional(*puWidth, *puHeight, &imgInfo.Width, &imgInfo.Height);

    // Get the new image
    hr = pImage->GetThumbnail(imgInfo.Width, imgInfo.Height, &pThumbnail);
    CHR(hr);

    // Convert this to HBITMAP, our target format
    hBitmap = HBITMAPFromImage(pThumbnail, RGB(255,255,255));
    CBR(hBitmap != NULL);

    *puWidth = imgInfo.Width;
    *puHeight = imgInfo.Height;
    *phBitmap = hBitmap;
    hBitmap = NULL;

Error:
    RELEASE_OBJ(pFactory);
    RELEASE_OBJ(pImage);
    RELEASE_OBJ(pThumbnail);

    if (hBitmap)
    {
        DeleteBitmap(hBitmap);
    }

    return hr;

}



// **************************************************************************
// Function Name: DrawRect
// 
// Purpose: Draws a rectangle with the coordinates and the color passed in
//
// Arguments:
//    IN HDC      hdc - DC for drawing
//    IN LPRECT   prc - Area to draw the rectangle
//    IN COLORREF clr - color to draw the rectangle
//
// Return Values:
//    NONE
//

void DrawRect(HDC hdc, LPRECT prc, COLORREF clr)
{
    COLORREF clrSave = SetBkColor(hdc, clr);
    ExtTextOut(hdc,0,0,ETO_OPAQUE,prc,NULL,0,NULL);
    SetBkColor(hdc, clrSave);
}
