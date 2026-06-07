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

#pragma once
#include "..\MobileGPSLib\GPSController.h"

// *************************************************************************
// Class CDisplayGPSData 
//
// Inheritance:
//      None
//
// Purpose:
//      To display the GPS data to the user.  
//
//      This classs is used by CGPSSink to display the GPS data
// **************************************************************************
class CDisplayGPSData
{
public:
    HRESULT DisplayDeviceInfo(__in GPS_DEVICE gps_Device);
    HRESULT DisplayGPSLocation(__in GPS_POSITION gps_Position);

private:
    HRESULT ShowData();

private:
    GPS_DEVICE m_GPS_Device;
    GPS_POSITION m_GPS_Position;
};