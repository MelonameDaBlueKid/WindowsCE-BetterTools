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
/*
   ExTAPI.CPP
  
   Sample that demonstrates some functionality of ExTAPI.
   NOTE: ExTAPI is a privileged API and any application using it must
   be signed using a priviliged certificate.

*/


#include <windows.h>
#include <tapi.h>
#include <extapi.h>
#include <aygshell.h>
#include <tsp.h>
#include "resource.h"


// some definitons
#define ARRAY_LENGTH(x)         (sizeof(x)/sizeof((x)[0]))
#define TAPI_API_LOW_VERSION    0x00020000
#define TAPI_API_HIGH_VERSION   0x00020000
#define EXT_API_LOW_VERSION     0x00010000
#define EXT_API_HIGH_VERSION    0x00010000
#define HUGE_BUFFER             4096

// global variables
HINSTANCE   g_hInstance;
// Friendly application name passed to ExTAPI.
// This is loaded from a STRINGTABLE in the program resources
// to help enable internationalisation.
TCHAR gszFriendlyAppName[160]; 

// function declarations
BOOL GetExTAPIInfo();
DWORD GetTSPLineDeviceID(const HLINEAPP hLineApp, const DWORD dwNumberDevices, 
                         const DWORD dwAPIVersionLow, const DWORD dwAPIVersionHigh, 
                         const TCHAR* const psTSPLineName);

// ***************************************************************************
// Function Name: WinMain
//
// Purpose: Main entry point into the ExTAPI program
//
// Arguments: Standard WinMain arguments
//
// Return Values: TRUE
//
// Description:
//  This WinMain simply calls GetExTAPIInfo, which pops up a MessageBox

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPreviousInstance,
                    LPWSTR pszCommandLine,
                    int nCommandShow)
{
    // store the hInstance
    g_hInstance = hInstance;
    
    // Get the friendly application name from the STRINGTABLE
    LoadString(g_hInstance, IDS_FRIENDLYNAME, 
               gszFriendlyAppName, ARRAY_LENGTH(gszFriendlyAppName)); 

    // pop up a message box with general info
    if (!GetExTAPIInfo()) 
    {
        TCHAR szCGI[160]; 
        LoadString(g_hInstance, IDS_CANTGETINFO, szCGI, ARRAY_LENGTH(szCGI)); 
        MessageBox(NULL, szCGI, gszFriendlyAppName, MB_OK | MB_ICONERROR);
    }

    return TRUE;
}

// ***************************************************************************
// Function Name: GetExTAPIInfo
//
// Purpose: To get and display general ExTAPI information.
//
// Arguments: None
//
// Return Values: 
//  TRUE if all ExTAPI operations completed successfully, FALSE otherwise
//
// Description:
//  This function initializes ExTAPI and then calls lineGetGeneralInfo.
//  It then takes the info that lGGI returned and displays it in a MessageBox

BOOL GetExTAPIInfo()
{
    DWORD dwNumDevs;
    DWORD dwAPIVersion = TAPI_API_HIGH_VERSION;
    LINEINITIALIZEEXPARAMS liep;
    HLINEAPP hLineApp = 0;
    HLINE hLine = 0;
    DWORD dwExtVersion;
    TCHAR szMBString[HUGE_BUFFER];
    BOOL bRetVal = FALSE;
    LPBYTE pLineGeneralInfoBytes = NULL;
    DWORD dwTAPILineDeviceID;
    const DWORD dwMediaMode = LINEMEDIAMODE_DATAMODEM | LINEMEDIAMODE_INTERACTIVEVOICE;
    LINEGENERALINFO lviGeneralInfo;
    LPLINEGENERALINFO plviGeneralInfo;
    LPTSTR tsManufacturer, tsModel, tsRevision, tsSerialNumber, tsSubscriberNumber;
    TCHAR szUnavailable[160]; 

    // Load text from STRINGTABLE
    LoadString(g_hInstance, IDS_UNAVAILABLE, szUnavailable, ARRAY_LENGTH(szUnavailable)); 

    // set the line init params
    liep.dwTotalSize = sizeof(liep);
    liep.dwOptions = LINEINITIALIZEEXOPTION_USEEVENT;
    
    if (lineInitializeEx(&hLineApp, 0, 0, gszFriendlyAppName, 
                         &dwNumDevs, &dwAPIVersion, &liep)) 
    {
        goto cleanup;
    }

    // get the device ID
    dwTAPILineDeviceID = GetTSPLineDeviceID(hLineApp, dwNumDevs, 
                                                  TAPI_API_LOW_VERSION, 
                                                  TAPI_API_HIGH_VERSION, 
                                                  CELLTSP_LINENAME_STRING);

    // error getting the line device ID?
    if (0xffffffff == dwTAPILineDeviceID) 
    {
        goto cleanup;
    }

    // now try and open the line
    if(lineOpen(hLineApp, dwTAPILineDeviceID, 
                &hLine, dwAPIVersion, 0, 0, 
                LINECALLPRIVILEGE_OWNER, dwMediaMode, 0)) 
    {
        goto cleanup;
    }

    // set up ExTAPI
    if (lineNegotiateExtVersion(hLineApp, dwTAPILineDeviceID, 
                                dwAPIVersion, EXT_API_LOW_VERSION, 
                                EXT_API_HIGH_VERSION, &dwExtVersion)) 
    {
        goto cleanup;
    }

    // try to get the general info
    lviGeneralInfo.dwTotalSize = sizeof(lviGeneralInfo);

    // step 1: find out how much space we need
    if (lineGetGeneralInfo(hLine, &lviGeneralInfo)) 
    {
        goto cleanup;
    }

    // step 2: malloc space for all the info we need
    pLineGeneralInfoBytes = new BYTE[lviGeneralInfo.dwNeededSize];
    plviGeneralInfo = (LPLINEGENERALINFO)pLineGeneralInfoBytes;

    // step 3: call lGGI again with the appropriately sized buffer
    if(NULL != pLineGeneralInfoBytes) 
    {
        plviGeneralInfo->dwTotalSize = lviGeneralInfo.dwNeededSize;
        if (lineGetGeneralInfo(hLine, plviGeneralInfo)) 
        {
            goto cleanup;
        }
    } else 
    {
        goto cleanup;
    }

    // step 4: cast all the arguments to strings
    if(0 < plviGeneralInfo->dwManufacturerSize)
    { 
        tsManufacturer = (WCHAR*)(((BYTE*)plviGeneralInfo)+plviGeneralInfo->dwManufacturerOffset);
    }
    else
    {
        tsManufacturer = szUnavailable;
    }

    if(0 < plviGeneralInfo->dwModelSize)
    { 
        tsModel = (WCHAR*)(((BYTE*)plviGeneralInfo)+plviGeneralInfo->dwModelOffset);
    }
    else
    {
        tsModel = szUnavailable;
    }

    if(0 < plviGeneralInfo->dwRevisionSize)
    {
        tsRevision = (WCHAR*)(((BYTE*)plviGeneralInfo)+plviGeneralInfo->dwRevisionOffset);
    }
    else
    {
        tsRevision = szUnavailable;
    }

    if(0 < plviGeneralInfo->dwSerialNumberSize)
    {
        tsSerialNumber = (WCHAR*)(((BYTE*)plviGeneralInfo)+plviGeneralInfo->dwSerialNumberOffset);
    }
    else
    {
        tsSerialNumber = szUnavailable;
    }

    if(0 < plviGeneralInfo->dwSubscriberNumberSize)
    {
        tsSubscriberNumber = (WCHAR*)(((BYTE*)plviGeneralInfo)+plviGeneralInfo->dwSubscriberNumberOffset);
    }
    else
    {
        tsSubscriberNumber = szUnavailable;
    }
    // create the message box string.
    // 
    {
        TCHAR szManufacturer[80]; 
        TCHAR szModel[80]; 
        TCHAR szRevision[80];
        TCHAR szSerialNumber[80];
        TCHAR szSubscriberNumber[80];

        LoadString(g_hInstance, IDS_MANUFACTURER, szManufacturer, ARRAY_LENGTH(szManufacturer)); 
        LoadString(g_hInstance, IDS_MODEL, szModel, ARRAY_LENGTH(szModel)); 
        LoadString(g_hInstance, IDS_REVISION, szRevision, ARRAY_LENGTH(szRevision)); 
        LoadString(g_hInstance, IDS_SERIALNUMBER, szSerialNumber, ARRAY_LENGTH(szSerialNumber)); 
        LoadString(g_hInstance, IDS_SUBSCRIBERNUMBER, szSubscriberNumber, ARRAY_LENGTH(szSubscriberNumber)); 

        _sntprintf(szMBString, ARRAY_LENGTH(szMBString),
                   TEXT("%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n"),
                   szManufacturer, tsManufacturer, 
                   szModel, tsModel, 
                   szRevision, tsRevision, 
                   szSerialNumber, tsSerialNumber, 
                   szSubscriberNumber, tsSubscriberNumber);
    }
    // pop up the message box
    {
        TCHAR szExTapiLineInfo[80];
        LoadString(g_hInstance, IDS_EXTAPILINEINFO, szExTapiLineInfo, ARRAY_LENGTH(szExTapiLineInfo)); 
        MessageBox(NULL, szMBString, szExTapiLineInfo, MB_OK | MB_ICONINFORMATION);
    }
    bRetVal = TRUE;

cleanup:
    if (pLineGeneralInfoBytes) delete [] pLineGeneralInfoBytes;
    if (hLine) lineClose(hLine);
    if (hLineApp) lineShutdown(hLineApp);

    return bRetVal;
}

// ***************************************************************************
// Function Name: GetTSPLineDeviceID
//
// Purpose: To get a TSP Line Device ID
//
// Arguments:
//  hLineApp = the HLINEAPP returned by lineInitializeEx
//  dwNumberDevices = also returned by lineInitializeEx
//  dwAPIVersionLow/High = min version of TAPI that we need
//  psTSPLineName = "Cellular Line"
//
// Return Values: Current Device ID
//
// Description:
//  This function returns the device ID of a named TAPI TSP.  The Device ID is 
//  used in the call to lineOpen

DWORD GetTSPLineDeviceID(const HLINEAPP hLineApp, 
                         const DWORD dwNumberDevices, 
                         const DWORD dwAPIVersionLow, 
                         const DWORD dwAPIVersionHigh, 
                         const TCHAR* const psTSPLineName)
{
    DWORD dwReturn = 0xffffffff;
    for(DWORD dwCurrentDevID = 0 ; dwCurrentDevID < dwNumberDevices ; dwCurrentDevID++)
    {
        DWORD dwAPIVersion;
        LINEEXTENSIONID LineExtensionID;
        if(0 == lineNegotiateAPIVersion(hLineApp, dwCurrentDevID, 
                                        dwAPIVersionLow, dwAPIVersionHigh, 
                                        &dwAPIVersion, &LineExtensionID)) 
        {
            LINEDEVCAPS LineDevCaps;
            LineDevCaps.dwTotalSize = sizeof(LineDevCaps);
            if(0 == lineGetDevCaps(hLineApp, dwCurrentDevID, 
                                   dwAPIVersion, 0, &LineDevCaps)) 
            {
                BYTE* pLineDevCapsBytes = new BYTE[LineDevCaps.dwNeededSize];
                if(0 != pLineDevCapsBytes) 
                {
                    LINEDEVCAPS* pLineDevCaps = (LINEDEVCAPS*)pLineDevCapsBytes;
                    pLineDevCaps->dwTotalSize = LineDevCaps.dwNeededSize;
                    if(0 == lineGetDevCaps(hLineApp, dwCurrentDevID, 
                                           dwAPIVersion, 0, pLineDevCaps)) 
                    {
                        if(0 == _tcscmp((TCHAR*)((BYTE*)pLineDevCaps+pLineDevCaps->dwLineNameOffset), 
                                        psTSPLineName)) 
                        {
                            dwReturn = dwCurrentDevID;
                        }
                    }
                    delete[]  pLineDevCapsBytes;
                }
            }
        }
    }
    return dwReturn;
}
