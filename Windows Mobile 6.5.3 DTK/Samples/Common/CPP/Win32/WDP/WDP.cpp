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
#include <windows.h>
#include <wap.h>

// Used for SMS bearer
// Change this phone number to your device's phone number.
const TCHAR *const g_pszTelNum = _T("4255550100");

// For UDP bearer
const TCHAR *const g_pszIpLoopbackAddr = _T("127.0.0.1");

//
//  The following routine illustrates how to send a primitive with UserData 
//  through WDP_LAYER and how to read a primitive with UserData from WDP_LAYER.
//  It uses one device for both initator and responder, 
//  which are distinguished by different ports.
//
//  Arguments:
//    bool bUDP - TRUE if UDP bearer, FALSE if  SMS bearer.
bool WdpSendAndReadEcho( bool bUDP ) 
{

    bool bSendReadOK = false;

    HRESULT hResult;

    //  Open WAP for Sending WDP UnitData
    const WAP_LAYER wlLayer = WAP_LAYER_WDP;
    const DWORD dwSendPort = 3000L;
    WAP_HANDLE hWapSend = 0L;
    HANDLE hWapSendMsgEvent= NULL;
    WDP_UNITDATA *pcbWdpRecvData = NULL;

    OutputDebugString( _T("Opening handle for sending a WAP message.\n"));
    hResult = WapOpen( wlLayer, dwSendPort, &hWapSend, &hWapSendMsgEvent );
    if ( FAILED(hResult) || !hWapSend || !hWapSendMsgEvent  ) 
    {
        OutputDebugString( _T("WapOpen() for sending WDP UnitData failed\n") );
        hWapSend = 0L;
        hWapSendMsgEvent= NULL;
        return false;
    }

    //  Open WAP for reading WDP UnitData
    const DWORD dwRecvPort = 3001L;
    WAP_HANDLE hWapRecv= 0L;
    HANDLE hWapRecvMsgEvent = NULL;

    OutputDebugString( _T("Opening handle for receiving a WAP message.\n"));
    hResult = WapOpen( wlLayer, dwRecvPort, &hWapRecv, &hWapRecvMsgEvent );
    if ( FAILED(hResult) || !hWapRecv || !hWapRecvMsgEvent ) 
    {
        OutputDebugString( _T("WapOpen() for reading WDP UnitData failed\n") );
        hWapRecv= 0L;
        goto exit_label;
    }

    //  Create WDP UnitData structure with user data
    WAP_ADDRESS waSendRecv;



    if(bUDP)
    {
        _tcsncpy( waSendRecv.ptsAddress, g_pszIpLoopbackAddr, MAX_WAP_ADDRESS_LENGTH );
    }
    else
    {
        _tcsncpy( waSendRecv.ptsAddress, g_pszTelNum, MAX_WAP_ADDRESS_LENGTH);
    }

    waSendRecv.watAddressType = bUDP ? WAP_ADDRESS_TYPE_UDP : WAP_ADDRESS_TYPE_GSM_SMS;

    WDP_UNITDATA Wdpunitdata;
    // Initialize the WDP UnitData
    memset( &Wdpunitdata, 0, sizeof(Wdpunitdata) );
    Wdpunitdata.wpiPrimitiveID = WAP_PRIMITIVE_ID_T_DUNITDATA;
    Wdpunitdata.wptPrimitiveType = WAP_PRIMITIVE_TYPE_REQUEST;
    Wdpunitdata.dwValidFields =  (WDP_FIELD_SOURCEADDRESS      |
                                  WDP_FIELD_SOURCEPORT         |
                                  WDP_FIELD_DESTINATIONADDRESS |
                                  WDP_FIELD_DESTINATIONPORT    |
                                  WDP_FIELD_USERDATA );
    Wdpunitdata.waSourceAddress =  waSendRecv;
    Wdpunitdata.dwSourcePort = dwSendPort;
    Wdpunitdata.waDestinationAddress = Wdpunitdata.waSourceAddress;
    Wdpunitdata.dwDestinationPort = dwRecvPort;
    // Set Random user data with size = 0x100
    Wdpunitdata.dwUserDataSize = 0x100;

    // Use temporary buffer because pbUserData is const BYTE * 
    BYTE *pbBuffer = NULL;

    if(pbBuffer = new BYTE[Wdpunitdata.dwUserDataSize])
    {
    // Fill the user data section with random data
        for ( DWORD dw = 0; dw < Wdpunitdata.dwUserDataSize; dw++ ) 
        {
            pbBuffer[ dw ] = rand() % 0xFF;
        }
    }        
    else 
    {
        goto exit_label;
    }
    Wdpunitdata.pbUserData = pbBuffer;

    //  Send WDP Data
    OutputDebugString( _T("Sending WAP data.\n"));
    hResult = WapSend( hWapSend, (WAP_PRIMITIVE_BASE *)&Wdpunitdata );
    if ( FAILED(hResult) ) 
    {
        OutputDebugString( _T("WapSend() with WDP Unitdata failed.\n") );
        goto exit_label;
    }

    OutputDebugString( _T("Waiting for expected WDP Data.\n") );
    //  Wait for WAP message received Event
    if ( WAIT_OBJECT_0 != WaitForSingleObject( hWapRecvMsgEvent , 10000L ))
    {
        OutputDebugString( _T("Failed to wait for or timed out waiting for expected WDP Data.\n") );
        goto exit_label;
    }

    DWORD dwWdpRecvDataSize = 0L;
 
    OutputDebugString( _T("Getting the size of the next packet to read.\n"));
    hResult = WapGetNextPrimitiveSize( hWapRecv, &dwWdpRecvDataSize);
    if ( FAILED(hResult) || (0 == dwWdpRecvDataSize) ) 
    {
        OutputDebugString( _T("WapGetNextPrimitiveSize() failed\n") );
        goto exit_label;
    }

    //  Allocate memory for storing received WDP Data
    pcbWdpRecvData =( WDP_UNITDATA* ) new BYTE[ dwWdpRecvDataSize  ];
    if ( !pcbWdpRecvData) 
    {
        OutputDebugString( _T("Failed to allocate memory for storing WDP Unit Data\n") );
        goto exit_label;
    }

    //  Read WDP Data
    OutputDebugString( _T("Reading WAP packet.\n"));
    hResult = WapRead( hWapRecv, (WAP_PRIMITIVE_BASE *)pcbWdpRecvData, dwWdpRecvDataSize );
    if ( FAILED(hResult) ) 
    {
        OutputDebugString( _T("WapRead() failed\n") );
        goto exit_label;
    }

    // Validate the received primitive and
    // Compare the received user data to the sent user data
    if (!pcbWdpRecvData)
        goto exit_label;

    bSendReadOK = true;
    bSendReadOK &= (WAP_PRIMITIVE_ID_T_DUNITDATA == pcbWdpRecvData->wpiPrimitiveID);
    bSendReadOK &= (WAP_PRIMITIVE_TYPE_INDICATION == pcbWdpRecvData->wptPrimitiveType);
    bSendReadOK &= (pcbWdpRecvData->dwValidFields & WDP_FIELD_SOURCEADDRESS ) && ( pcbWdpRecvData->dwValidFields & WDP_FIELD_SOURCEPORT );
    bSendReadOK &= (pcbWdpRecvData->dwUserDataSize == Wdpunitdata.dwUserDataSize);    
    if(bSendReadOK && pcbWdpRecvData->pbUserData)
    {
        bSendReadOK &= !memcmp(pcbWdpRecvData->pbUserData, Wdpunitdata.pbUserData, pcbWdpRecvData->dwUserDataSize);
    }
 
    exit_label:
    
    //  Close WAP  for Sending WDP UnitData
    if ( hWapSend) 
    {
        OutputDebugString( _T("Closing the WAP sending handle.\n"));
        hResult = WapClose( hWapSend );
        if ( FAILED(hResult) ) 
        {
            OutputDebugString( _T("WapClose() for sending WDP UnitData failed.\n") );
            bSendReadOK = false;
        } 
        else 
        {
            hWapSend = 0L;
        }
    }

    //  Close WAP  for Receiving WDP UnitData
    if ( hWapRecv ) 
    {
        OutputDebugString( _T("Closing the WAP receiving handle.\n"));
        hResult = WapClose( hWapRecv );
        if ( FAILED(hResult) ) 
        {
            OutputDebugString( _T("WapClose() for reading WDP UnitData failed.\n") );
            bSendReadOK = false;
        } 
        else 
        {
            hWapRecv = 0L;
        }
    }
    // Clear the buffers
    if (pbBuffer) 
    {
        delete[] (BYTE*) pbBuffer;
    }

    if ( pcbWdpRecvData ) 
    {
        delete [] (BYTE*) pcbWdpRecvData;
        pcbWdpRecvData = NULL;
    }

    if (bSendReadOK)
    {
        OutputDebugString( _T("Sent and read through WDP layer succesfully.\n") );
    }
    else
    {
        OutputDebugString( _T("Could not succesfully send and read through WDP layer.\n") );
    }
    return bSendReadOK;
}

int _tmain(int argc, _TCHAR* argv[])
{

//  The following routine illustrates
//  how to send a primitive with UserData through WDP_LAYER and
//  read a primitive with UserData from WDP_LAYER.
//  It uses one device for both initator and responder, which are distinguished by different ports.
//  Use UDP bearer if bUDP = true, Use SMS bearer if bUDP = false;

    OutputDebugString( _T("  SENDING AND RECEIVING A PRIMITIVE WITH USERDATA THROUGH WDP_LAYER.\n"));
    OutputDebugString( _T("  USING UDP BEARER.\n\n"));

    WdpSendAndReadEcho(TRUE);

    OutputDebugString( _T("  SENDING AND RECEIVING A PRIMITIVE WITH USERDATA THROUGH WDP_LAYER. \n"));
    OutputDebugString( _T("  USING SMS BEARER.\n\n"));
    WdpSendAndReadEcho(FALSE);

    return 0;
}

