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

#include <WinSock2.h>
#include <rapi2.h>

#include <iostream>
using namespace std;

// **************************************************************************
//	Sample Description:
//		DeviceInfo is a Win32 Desktop component that demontrates the use of 
//		IRAPI interfaces to get information about the Windows Mobile device
//		connected through ActiveSync and the corresponding communication
//		medium used.  Once the information is collected, it is printed
//		on the console window
// **************************************************************************

// **************************************************************************
// GetInfo
//  
//  Purpose:
//              Retreive device and connection information of the connected device
//
//  Parameters:
//              OUT RAPI_DEVICEINFO *pDeviceInfo
//              OUT RAPI_CONNECTIONINFO* pConnectionInfo
//              
//  Side Effects:
//              on success, pDeviceInfo is to be freed by the calling funtion
//
//  Returns:
//              HRESULT: S_OK on Success, an appropriate HR on failure.
//
// **************************************************************************
HRESULT GetInfo(OUT RAPI_DEVICEINFO *pDeviceInfo, OUT RAPI_CONNECTIONINFO* pConnectionInfo)
{
    HRESULT hr = E_FAIL;

    IRAPIDesktop *pIRapiDesktop = NULL;
    IRAPIEnumDevices *pIRapiEnumDevices = NULL;
    IRAPIDevice *pIRapiDevice = NULL;

	// Sanity check the arguments passed to GetInfo
    if (NULL == pDeviceInfo || NULL == pConnectionInfo)
    {
        hr = E_INVALIDARG;
        goto Exit;
    }

	// This call assumes that the threading model has already been set
	hr = CoCreateInstance(CLSID_RAPI, NULL, CLSCTX_INPROC_SERVER, 
                    IID_IRAPIDesktop,
                    (void**)&pIRapiDesktop
                    );
    if (FAILED(hr))
    {
        goto Exit;
    }

	// Create an enumeration to the existing devices connected
    hr = pIRapiDesktop->EnumDevices(&pIRapiEnumDevices);
    if (FAILED(hr))
    {
        goto Exit;
    }

	// Only one device can be connected to ActiveSync 4.0 at a time
	hr = pIRapiEnumDevices->Next(&pIRapiDevice);
    if (FAILED(hr))
    {
        goto Exit;
    }

    // Use pIRapiDevice retreived previously to get connection information
	hr = pIRapiDevice->GetConnectionInfo(pConnectionInfo);
    if (FAILED(hr))
    {
        goto Exit;
    }

	// Use pIRapiDevice to get the device information
    hr = pIRapiDevice->GetDeviceInfo(pDeviceInfo);
    if (FAILED(hr))
    {
        goto Exit;
    }

    hr = S_OK;

Exit:
	// Free resources
    if (NULL != pIRapiDesktop)
    {
        pIRapiDesktop->Release();
    }

    if (NULL != pIRapiEnumDevices)
    {
        pIRapiEnumDevices->Release();
    }

    if (NULL != pIRapiDevice)
    {
        pIRapiDevice->Release();
    }

	if (FAILED(hr))
	{
		FreeDeviceInfoData(pDeviceInfo);
	}

    return hr;
}

// **************************************************************************
// DisplayInfo
//  
//  Purpose:
//              Displays device and connection information of the connected device
//
//  Parameters:
//              OUT RAPI_DEVICEINFO *pDeviceInfo
//              OUT RAPI_CONNECTIONINFO* pConnectionInfo
//              
//  Side Effects:
//              on success, pDeviceInfo is to be freed by the calling funtion
//
//  Returns:
//              HRESULT: S_OK on Success, an appropriate HR on failure.
//
// **************************************************************************
HRESULT DisplayInfo(IN RAPI_DEVICEINFO *pDeviceInfo, IN RAPI_CONNECTIONINFO* pConnectionInfo)
{
    HRESULT hr = E_FAIL;
    
    WCHAR wszConnType[][20] = {
                        L"USB",
                        L"IR",
                        L"Serial",
                        };
    
    WCHAR *pwszGUID = NULL;
    SOCKADDR_STORAGE *pIpaddr = NULL;
    SOCKADDR_STORAGE *pHostIpaddr = NULL;
    sockaddr_in *psoc4;

	// Validate arguments passed to DisplayInfo
    if (NULL == pDeviceInfo || NULL == pConnectionInfo)
    {
        hr = E_INVALIDARG;
        goto Exit;
    }

    // print connection information
    wprintf(L"The device is connected through: %s\n", wszConnType[static_cast<int> (pConnectionInfo->connectionType)] );

    pIpaddr = &(pConnectionInfo->ipaddr);
    pHostIpaddr = &(pConnectionInfo->hostIpaddr);

    psoc4 = reinterpret_cast<sockaddr_in *> (pIpaddr);
    wprintf(L"DeviceIpaddr is: %S\n", inet_ntoa(psoc4->sin_addr) );

    psoc4 = reinterpret_cast<sockaddr_in *> (pHostIpaddr);
    wprintf(L"DeviceHostIpaddr is: %S\n\n", inet_ntoa(psoc4->sin_addr) );

    // print device information
    wprintf(L"Device Name is: %s \n",  pDeviceInfo->bstrName);
    wprintf(L"DeviceType is: %s \n",  pDeviceInfo->bstrPlatform);        
    wprintf(L"DevicedwOsVersionMajor is: %d\n",  pDeviceInfo->dwOsVersionMajor);
    wprintf(L"DevicedwOsVersionMinor is: %d\n",  pDeviceInfo->dwOsVersionMinor);        

    hr = StringFromCLSID(pDeviceInfo->DeviceId, &pwszGUID );
    if (FAILED(hr))
    {
        goto Exit;
    }
    wprintf(L"DeviceID: %s\n", pwszGUID);
        
    hr = S_OK;

Exit:
    if (NULL != pwszGUID)
    {
        CoTaskMemFree(pwszGUID);
    }    

    return hr;
}

int main(int argc, char* argv[])
{
    HRESULT hr = E_FAIL;
    HRESULT hrCoinit = S_OK;

    RAPI_DEVICEINFO deviceInfo = {0};
    RAPI_CONNECTIONINFO connectionInfo = {0};
   
    // Initialize the threading model
    hrCoinit = CoInitialize(NULL);
    if (FAILED(hrCoinit))
    {
        hr = hrCoinit;
        goto Exit;
    }

    // Retreive device and connection information
    hr = GetInfo(&deviceInfo, &connectionInfo);
    if (HRESULT_FROM_WIN32(ERROR_NOT_FOUND) == hr)
    {
        wprintf(L"There is no device connected");
        goto Exit;
    }
    else if(FAILED(hr))
    {
        goto Exit;
    }

    // Output device connect connection information to the console screen
    hr = DisplayInfo(&deviceInfo, &connectionInfo);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = S_OK;
     
Exit:
    
    FreeDeviceInfoData(&deviceInfo);
    
    if (SUCCEEDED(hrCoinit))
    {
        ::CoUninitialize();        
    }

    return SUCCEEDED(hr);
}

