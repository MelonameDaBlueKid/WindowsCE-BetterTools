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
/***********************************************************************
	  MODULE: 
	  Port.c
	  
		ABSTRACT: 
		This is a C file of the TTY Windows CE sample application. It shows
		the definitions of port related functions.
		
***********************************************************************/

#include <windows.h>
#include "tty.h"

/***********************************************************************

  PortInitialize(LPTSTR lptszPortName)
  
***********************************************************************/
BOOL PortInitialize(
	LPTSTR lptszPortName
	)
{
	DWORD dwError,
	dwThreadID;
	DCB PortDCB;
	COMMTIMEOUTS CommTimeouts;
	
	// Open the serial port.
	g_hPort = CreateFile(lptszPortName, // Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE, // Access(read-write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute to copy
	
	// If it fails to open the port, return FALSE.
	if (INVALID_HANDLE_VALUE == g_hPort) 
	{
		// Could not open the port.
		MessageBox(g_hMainWnd, TEXT("Unable to open the port"), 
			TEXT("Error"), MB_OK);
		dwError = GetLastError();
		return FALSE;
	}
	
	PortDCB.DCBlength = sizeof(DCB);     
	
	// Get the default port setting information.
	GetCommState(g_hPort, &PortDCB);
	
	// Change the DCB structure settings.
	PortDCB.BaudRate = 9600;              // Current baud 
	PortDCB.fBinary = TRUE;               // Binary mode; no EOF check 
	PortDCB.fParity = TRUE;               // Enable parity checking 
	PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control 
	PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control 
	PortDCB.fDtrControl = DTR_CONTROL_ENABLE; 
	// DTR flow control type 
	PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity 
	PortDCB.fTXContinueOnXoff = TRUE;     // XOFF continues Tx 
	PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control 
	PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control 
	PortDCB.fErrorChar = FALSE;           // Disable error replacement 
	PortDCB.fNull = FALSE;                // Disable null stripping 
	PortDCB.fRtsControl = RTS_CONTROL_ENABLE; 
	// RTS flow control 
	PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on 
	// error
	PortDCB.ByteSize = 8;                 // Number of bits/byte, 4-8 
	PortDCB.Parity = NOPARITY;            // 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = ONESTOPBIT;        // 0,1,2 = 1, 1.5, 2 
	
	// Configure the port according to the specifications of the DCB 
	// structure.
	if (FALSE == SetCommState(g_hPort, &PortDCB))
	{
		// Could not create the read thread.
		MessageBox(g_hMainWnd, TEXT("Unable to configure the serial port"), 
			TEXT("Error"), MB_OK);
		dwError = GetLastError();
		return FALSE;
	}
	
	// Retrieve the time-out parameters for all read and write operations
	// on the port. 
	GetCommTimeouts(g_hPort, &CommTimeouts);
	
	// Change the COMMTIMEOUTS structure settings.
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;  
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
	CommTimeouts.ReadTotalTimeoutConstant = 0;    
	CommTimeouts.WriteTotalTimeoutMultiplier = 10;  
	CommTimeouts.WriteTotalTimeoutConstant = 1000;    
	
	// Set the time-out parameters for all read and write operations
	// on the port. 
	if (FALSE == SetCommTimeouts(g_hPort, &CommTimeouts))
	{
		// Could not create the read thread.
		MessageBox(g_hMainWnd, TEXT("Unable to set the time-out parameters"), 
			TEXT("Error"), MB_OK);
		dwError = GetLastError();
		return FALSE;
	}
	
	// Direct the port to perform extended functions SETDTR and SETRTS
	// SETDTR: Sends the DTR(data-terminal-ready) signal.
	// SETRTS: Sends the RTS(request-to-send) signal. 
	EscapeCommFunction(g_hPort, SETDTR);
	EscapeCommFunction(g_hPort, SETRTS);
	
	// Create a read thread for reading data from the communication port.
	g_hReadThread = CreateThread(NULL, 0, PortReadThread, 0, 0, &dwThreadID);
	if (NULL != g_hReadThread)
	{
		CloseHandle(g_hReadThread);
	}
	else
	{
		// Could not create the read thread.
		MessageBox(g_hMainWnd, TEXT("Unable to create the read thread"), 
			TEXT("Error"), MB_OK);
		dwError = GetLastError();
		return FALSE;
	}
	
	return TRUE;
}


/***********************************************************************

  PortWrite(BYTE Byte)
  
***********************************************************************/
void PortWrite(BYTE Byte)
{
	DWORD dwError,
		dwNumBytesWritten;
	
	if (!WriteFile(g_hPort,              // Port handle
		&Byte,              // Pointer to the data to write 
		1,                  // Number of bytes to write
		&dwNumBytesWritten, // Pointer to the number of bytes 
		// written
		NULL))              // Must be NULL for Windows CE
	{
		// WriteFile failed. Report error.
		dwError = GetLastError();
	}
}



/***********************************************************************

  PortReadThread(LPVOID lpvoid)
  
***********************************************************************/
DWORD PortReadThread(LPVOID lpvoid)
{
	BYTE Byte;
	DWORD dwCommModemStatus,
		dwBytesTransferred;
	
	// Specify a set of events to be monitored for the port.
	SetCommMask(g_hPort, EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_RING);
	
	while (INVALID_HANDLE_VALUE != g_hPort) 
	{
		// Wait for an event to occur for the port.
		WaitCommEvent(g_hPort, &dwCommModemStatus, 0);
		
		// Re-specify the set of events to be monitored for the port.
		SetCommMask(g_hPort, EV_RXCHAR | EV_CTS | EV_DSR | EV_RING);
		
		if (dwCommModemStatus & EV_RXCHAR) 
		{
			// Loop for waiting for the data.
			do 
			{
				// Read the data from the serial port.
				ReadFile(g_hPort, &Byte, 1, &dwBytesTransferred, 0);
				
				// Display the data read.
				if (dwBytesTransferred == 1)
				{
					ProcessChar(Byte);
				}
				
			} 
			while (dwBytesTransferred == 1);
		}
		
		// Retrieve modem control-register values.
		GetCommModemStatus(g_hPort, &dwCommModemStatus);
		
		// Set the indicator lights.
		SetLightIndicators(dwCommModemStatus);
	}
	
	return 0;
}


/***********************************************************************

  PortClose(HANDLE hCommPort)
  
***********************************************************************/
BOOL PortClose(
	HANDLE hCommPort
	)
{
	DWORD dwError;
	
	if (INVALID_HANDLE_VALUE != hCommPort)
	{
		// Close the communication port.
		if (FALSE == CloseHandle(hCommPort))
		{
			dwError = GetLastError();
			return FALSE;
		}
		else
		{
			hCommPort = INVALID_HANDLE_VALUE;
			return TRUE;
		}
	}
	
	return FALSE;
}

