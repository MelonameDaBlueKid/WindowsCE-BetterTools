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

#include "stdafx.h"
#include "DisplayGPSData.h"


// **************************************************************************
// Function Name: CDisplayGPSData:DisplayDeviceInfo
// 
// Purpose: Update local GPS_DEVICE data structure and display the data to 
//          the user
//
// Arguments:
//    __in GPS_DEVICE gps_Device: standar GPS_DEVICE structure
//
// Return Values:
//    HRESULT: S_OK on success
//             An appropriate error value on failure
//
// Side effects:  
//    None
// 
// Description:  
//    See purpose.  Note that it is safe to rely on the compiler to perform 
//    a bitwise copy on gps_Device.
// **************************************************************************
HRESULT CDisplayGPSData::DisplayDeviceInfo(__in GPS_DEVICE gps_Device)
{
    HRESULT hr = E_FAIL;
    m_GPS_Device = gps_Device;

    hr = ShowData();

    return hr;
}

// **************************************************************************
// Function Name: CDisplayGPSData:DisplayGPSLocation
// 
// Purpose: Update local GPS_POSITION data structure and display the data to 
//          the user
//
// Arguments:
//    __in GPS_POSITION gps_Position: standard GPS_POSITION structure
//
// Return Values:
//    HRESULT: S_OK on success
//             An appropriate error value on failure
//
// Side effects:  
//    None
// 
// Description:  
//    See purpose.  Note that it is safe to rely on the compiler to perform 
//    a bitwise copy on GPS_POSITION.
// **************************************************************************
HRESULT CDisplayGPSData::DisplayGPSLocation(__in GPS_POSITION gps_Position)
{
    HRESULT hr = E_FAIL;
    m_GPS_Position = gps_Position;

    hr = ShowData();

    return hr;
}

// **************************************************************************
// Function Name: CDisplayGPSData:ShowData
// 
// Purpose: To display the internal data structure of CDisplayGPSData
//          to the user
//
// Arguments:
//    None
//
// Return Values:
//    HRESULT: S_OK on success
//             An appropriate error value on failure
//
// Side effects:  
//    None
// 
// Description:  
//    ShowData displays a subset of the GPS data to the user.  It is 
//    IMPORTANT to point that ShowData is not intented to demonstrate 
//    how to implement Windows Mobile UI.  It is a mere tool to display the
//    GPS data to the user.  In that sense, it does not integrate with 
//    WM_PAINT to appropriately insure that the UI is refreshed whenever
//    it is invalidated
// **************************************************************************
HRESULT CDisplayGPSData::ShowData()
{
    HRESULT hr = E_FAIL;
    BOOL bRet = FALSE;
    INT dwRet = 0;
    INT iRet = 0;

    HWND hWnd = NULL;
    HDC hdc = NULL;

    RECT rt = {0};
    INT iFontSizePixel = 0;
    LONG lHeightAdjust = 0;
    WCHAR wszTmp[MAX_PATH] = L"";

    hWnd = FindWindow(L"MOBILEGPS", L"MobileGPS");

    hdc = GetDC(hWnd);

    bRet = GetClientRect(hWnd, &rt);

    hr = SHGetUIMetrics(SHUIM_FONTSIZE_PIXEL,
            &iFontSizePixel,
            sizeof(iFontSizePixel),
            NULL);

    if (rt.bottom < iFontSizePixel * 9)
    {
        iRet = DrawText(hdc, L"Not enough Space", -1, &rt, DT_CENTER);
        goto Exit;
    }

    StringCchPrintfEx(wszTmp,
        sizeof(wszTmp)/sizeof(wszTmp[0]),
        NULL,
        NULL,
        STRSAFE_NULL_ON_FAILURE,
        L"Satellites: %d",
        m_GPS_Position.dwSatelliteCount);
    iRet = DrawText(hdc, wszTmp, -1, &rt, DT_CENTER);

    rt.top += iFontSizePixel * 2;
    StringCchPrintfEx(wszTmp,
        sizeof(wszTmp)/sizeof(wszTmp[0]),
        NULL,
        NULL,
        STRSAFE_NULL_ON_FAILURE,
        L"Lattitude: %2.4f",
        m_GPS_Position.dblLatitude);
    iRet = DrawText(hdc, wszTmp, -1, &rt, DT_CENTER);

    rt.top += iFontSizePixel * 2;
    StringCchPrintfEx(wszTmp,
        sizeof(wszTmp)/sizeof(wszTmp[0]),
        NULL,
        NULL,
        STRSAFE_NULL_ON_FAILURE,
        L"Longitude: %2.4f",
        m_GPS_Position.dblLongitude);
    iRet = DrawText(hdc, wszTmp, -1, &rt, DT_CENTER);

    rt.top += iFontSizePixel * 2;
    StringCchPrintfEx(wszTmp,
        sizeof(wszTmp)/sizeof(wszTmp[0]),
        NULL,
        NULL,
        STRSAFE_NULL_ON_FAILURE,
        L"Speed: %2.4f M/H",
        m_GPS_Position.flSpeed);
    iRet = DrawText(hdc, wszTmp, -1, &rt, DT_CENTER);

    StringCchPrintfEx(wszTmp,
        sizeof(wszTmp)/sizeof(wszTmp[0]),
        NULL,
        NULL,
        STRSAFE_NULL_ON_FAILURE,
        L"%s",
        m_GPS_Device.szGPSFriendlyName);
    iRet = DrawText(hdc, wszTmp, -1, &rt, DT_BOTTOM | DT_CENTER);

    hr = S_OK;

Exit:

    ReleaseDC(hWnd, hdc);

    return hr;
}
