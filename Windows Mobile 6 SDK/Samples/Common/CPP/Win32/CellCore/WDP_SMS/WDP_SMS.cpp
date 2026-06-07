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

//
// WDP_SMS.CPP
//
// Simple application sending and receiving WDP messages over SMS bearer.
// This is a demonstration of how to use SMS to transport data.
// *** To use this sample, you must change the const c_szAddress[] to match
// *** the SMS number of the device running the sample. 
//

#include <windows.h>
#include <wap.h>

// Message waiting timeout in seconds
#define TIMEOUT			300

// Number to send/receive data
// REPLACE WITH THE SMS NUMBER OF THE DEVICE RUNNING THE SAMPLE
const TCHAR c_szAddress[] = TEXT("14258828080");

// Data to send
const TCHAR c_szData[] = TEXT("This is a demo of using WDP/SMS to transport data.");

// String appended to outputed data
const TCHAR c_szHeader[] = TEXT("WDP_SMS_DEMO: "); 

//////////////////////////////////////////////////////////////////////
// DebugOutput
//  Printf-like wrapping around OutputDebugString.
//
// Parameters:
//  szFormat        Formatting string (as in printf).
//  ...             Additional arguments.
//////////////////////////////////////////////////////////////////////

void DebugOutput(LPCTSTR szFormat, ...)
{
    const size_t c_cchBufferSize = 1024;
    TCHAR  szBuffer[c_cchBufferSize];
    LPTSTR pszBufferEnd = NULL;
    size_t cchRemaining = 0;

    va_list pArgs;
    va_start(pArgs, szFormat);
    StringCchCopyEx(szBuffer, c_cchBufferSize, c_szHeader, &pszBufferEnd, &cchRemaining, 0);
    StringCchVPrintfEx(pszBufferEnd, cchRemaining, &pszBufferEnd, &cchRemaining, 0, szFormat, pArgs);
    va_end(pArgs);

    StringCchCatEx(pszBufferEnd, cchRemaining, TEXT("\r\n"), &pszBufferEnd, &cchRemaining, 0);

    OutputDebugString(szBuffer);
}


///////////////////////////////////////////////////////////////////////
// Fill in the fields in T_UNITDATA primitive
///////////////////////////////////////////////////////////////////////
void PreparePrimitive( WDP_UNITDATA* const pPrimitive,
                       const WAP_ADDRESS waSender,   const DWORD dwSenderPort,
                       const WAP_ADDRESS waReceiver, const DWORD dwReceiverPort,
                       const BYTE*       pbUserData, const DWORD dwUserDataSize )
{
    ASSERT(pPrimitive && pbUserData);

    pPrimitive->wpiPrimitiveID        = WAP_PRIMITIVE_ID_T_DUNITDATA;
    pPrimitive->wptPrimitiveType      = WAP_PRIMITIVE_TYPE_REQUEST;
    pPrimitive->dwValidFields         = WDP_FIELD_SOURCEADDRESS      |
                                        WDP_FIELD_SOURCEPORT         |
                                        WDP_FIELD_DESTINATIONADDRESS |
                                        WDP_FIELD_DESTINATIONPORT    |
                                        WDP_FIELD_USERDATA;
    pPrimitive->waSourceAddress       = waSender;
    pPrimitive->dwSourcePort          = dwSenderPort;
    pPrimitive->waDestinationAddress  = waReceiver;
    pPrimitive->dwDestinationPort     = dwReceiverPort;
    pPrimitive->pbUserData            = pbUserData;
    pPrimitive->dwUserDataSize        = dwUserDataSize;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//  This program demonstrates how to send data via WDP/SMS. It creates two WDP clients on the same
//  device ( thus same sms address ) but different port. One client sends data to the other one.
//  
//  Return: 0 for success, -1 for failure
//////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain( 
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, 
	int nCmdShow 
	)
{   
    WAP_HANDLE  whSender, whReceiver;
    HANDLE  hSenderMsgEvent, hReceiverMsgEvent;
    DWORD   dwSenderPort   = 1234;
    DWORD   dwReceiverPort = 1235;    
	BOOL    fOK = TRUE;
    DWORD	dwDataSize = sizeof(c_szData);
    WDP_UNITDATA   wuToSend;

    // Sender and receiver's address (hard-coded)
    WAP_ADDRESS waAddress;
    waAddress.watAddressType = WAP_ADDRESS_TYPE_GSM_SMS;
    _tcscpy(waAddress.ptsAddress, c_szAddress);

    DebugOutput(_T("WDP_SMS data sending and receiving demo"));

    // Create two WDP clients on different ports
	DebugOutput(_T("Creating sender and receiver..."));

    // Create sender
    if (SUCCEEDED(WapOpen(WAP_LAYER_WDP, dwSenderPort, &whSender, &hSenderMsgEvent)))
    {
        DebugOutput(_T("Sender created on port %d."), dwSenderPort);

        // Create receiver
        if(SUCCEEDED(WapOpen(WAP_LAYER_WDP, dwReceiverPort, &whReceiver, &hReceiverMsgEvent)))
        {
            DebugOutput(_T("Receiver created on port %d."), dwReceiverPort);
        }
        else
        {
            DebugOutput(_T("Error!  Fail to create receiver!"));
            WapClose(whSender);
            return -1;
        }
        DebugOutput(_T("Sender and receiver's address: %s"), waAddress.ptsAddress);
    }
    else
    {
        DebugOutput(_T("Error!  Fail to create sender!"));
        return -1;
    }

    // Prepare a WDP primitive for sender to send    
	DebugOutput(_T("Date to be sent from sender to receiver: %s"), c_szData);
	DebugOutput(_T("Size of the data: %d bytes"), dwDataSize);
    
    // Prepare the wdp primitive
    PreparePrimitive(&wuToSend, waAddress, dwSenderPort, waAddress, dwReceiverPort, (BYTE *) c_szData, dwDataSize);
    
    // Send the primitive to receiver
    DebugOutput(_T("Sender sending data to receiver."));

	if (SUCCEEDED(WapSend(whSender, (WAP_PRIMITIVE_BASE *) &wuToSend)))    
    {            
		DebugOutput(_T("Sending OK."));

        // Receiver waits for incoming message
        DebugOutput(_T("Receiver waiting %u secs for message..." ), TIMEOUT );

        if (WAIT_OBJECT_0 == WaitForSingleObject(hReceiverMsgEvent, TIMEOUT * 1000)) 
        {
            DebugOutput(_T("Receiver got message"));
                    
            // Get primitive size in order to read it
            DWORD dwSize = 0;
            if (SUCCEEDED(WapGetNextPrimitiveSize(whReceiver, &dwSize)) && dwSize) 
            {  
	            DebugOutput(_T("Get primitive size:  %u"), dwSize);
    
				// Allocate buffer to hold incoming message
	            BYTE *pbBuffer = new BYTE[dwSize];
                
				if (pbBuffer)
                {
                    // Read the primitive   
                    if (SUCCEEDED(WapRead(whReceiver, (WAP_PRIMITIVE_BASE *) pbBuffer, dwSize)))    
                    {
                        // Successfully read the primitive
                        DebugOutput(_T("Receiver successfully read the primitive."));

                        WDP_UNITDATA *pReceived = (WDP_UNITDATA *) pbBuffer;

                        // Now validate the primitive
                        if ((WAP_PRIMITIVE_ID_T_DUNITDATA == pReceived->wpiPrimitiveID) && (WAP_PRIMITIVE_TYPE_INDICATION == pReceived->wptPrimitiveType))
                        {
                            // Print sources address
                            if (WTP_FIELD_SOURCEADDRESS & pReceived->dwValidFields)
                            {
                                TCHAR ptsAddress[MAX_WAP_ADDRESS_LENGTH];

                                 _tcsncpy(ptsAddress, pReceived->waSourceAddress.ptsAddress,MAX_WAP_ADDRESS_LENGTH);
                                ptsAddress[MAX_WAP_ADDRESS_LENGTH - 1] = _T('\0');    // force it to be NULL-terminated
                                DebugOutput(_T("Primitive's source address: %s"), ptsAddress);
                            }
                            else
                            {
                                DebugOutput(_T("Error! Missing source address."));
                                fOK = FALSE;
                            }

                            // Compare received data with sent data
                            if ((WDP_FIELD_USERDATA & pReceived->dwValidFields) && (pReceived->pbUserData))
                            {
                                // Compare data size
                                DebugOutput(_T("Received user data size: %d"), pReceived->dwUserDataSize);
                                if (pReceived->dwUserDataSize == dwDataSize)
                                {
                                    DebugOutput(_T("Data size comparison succeeded."));
                                    
									// Compare data content
                                    if (!memcmp(c_szData, pReceived->pbUserData, dwDataSize))
                                    {   
										// Print received user data
                                        DebugOutput(_T("Received data: %s"), pReceived->pbUserData);
                                        DebugOutput(_T("Data content comparison succeeded"));
                                    }
                                    else
                                    {
                                        DebugOutput(_T("Error! Data content comparison failed."));
                                        fOK = FALSE;
                                    }                                                              
                                }
                                else
                                {
                                    DebugOutput(_T("Error! Data size comparison failed"));
                                    fOK = FALSE;
                                }
                            }
                            else
                            {
                                DebugOutput(_T("Error! Missing user data."));
                                fOK = FALSE;
                            }
                        }
                        else
                        {
                            DebugOutput(_T("Error! Invalid primitive ID or primitive type."));
                            fOK = FALSE;
                        }
                    }
                    else
                    {
                        DebugOutput(_T("Error! Receiver failed to read primitive"));
                        fOK = FALSE;
                    }
                        delete [] pbBuffer;
                }
                else
                {
		            DebugOutput(_T("Error! Receiver fail to allocate buffer to hold incoming message."));
                    fOK = FALSE;
                }                   
                
			}
            else
            {                    
                DebugOutput(_T( "Error! Receiver failed to get primitive size" ) );
                fOK = FALSE;
            }
            
		}
        else    
        {
            DebugOutput(_T("Warning! Receiver timed out waiting for message" ) );
            fOK = FALSE;
        }
        
	}
    else    
    {
        DebugOutput(_T("Error!  Fail to send data!"));
        fOK = FALSE;
    }

    // Clean up
    WapClose(whSender);
    WapClose(whReceiver);

    DebugOutput(_T("Send and receive %s. Exit."), ((fOK) ? _T("succeeded") : _T("failed")));

    return ((fOK) ? 0 : -1);
}

