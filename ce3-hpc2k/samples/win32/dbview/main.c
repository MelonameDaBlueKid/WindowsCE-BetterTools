//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     main.c
//
//  PURPOSE:    Startup functions and error handling
//
//  PLATFORMS:  Windows CE
//
//  FUNCTIONS:
//      WinMain()           - Entry point function
//      DoMain()            - Main message loop
//      ErrorHandlerEx()    - Generic error handler code
//
//  COMMENTS:
//
//

#include <windows.h>
#include <commctrl.h>
#include "globals.h"

//----------------------------------------------------------------------------
// Prototypes

int DoMain(void);

//
//  FUNCTION:   WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//
//  PURPOSE:    Entry point function, initializes the application, instance,
//              and then launches the message loop.
//
//  PARAMETERS:
//      hInstance     - handle that uniquely identifies this instance of the
//                      application
//      hPrevInstance - always zero in Win32
//      lpszCmdLine   - any command line arguements pass to the program
//      nCmdShow      - the state which the application shows itself on
//                      startup
//
//  RETURN VALUE:
//      (int) Returns the value from PostQuitMessage().
//
//  COMMENTS:
//

int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPWSTR lpszCmdLine,
                    int nCmdShow)
{
    int iResult = 0;

    if (InitApplication(hInstance))
       if (InitInstance(hInstance, SW_SHOW))
           iResult = DoMain();

    return iResult;
}

//
//  FUNCTION:   DoMain(void)
//
//  PURPOSE:    This is the main message loop for the application.  It
//              retrieves messages from the application's message queue and
//              dispatches the messages to the appropriate window procedure.
//
//  PARAMETERS:
//      none
//
//  RETURN VALUE:
//      (int) Returns the value passed to PostQuitMessage().
//
//  COMMENTS:
//

int DoMain( void )
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);   // Translates virtual key codes
        DispatchMessage(&msg);    // Dispatches message to window procedure
    }

    return ((int) msg.wParam);
}


//
//  FUNCTION:   ErrorHandlerEx(WORD, LPSTR)
//
//  PURPOSE:    Calls GetLastError() and uses FormatMessage() to display the
//              textual information of the error code along with the file
//              and line number.
//
//  PARAMETERS:
//      wLine    - line number where the error occured
//      lpszFile - file where the error occured
//
//  RETURN VALUE:
//      none
//
//  COMMENTS:
//      This function has a macro ErrorHandler() which handles filling in
//      the line number and file name where the error occured.  ErrorHandler()
//      is always used instead of calling this function directly.
//

void WINAPI ErrorHandlerEx( int wLine, LPTSTR lpszFile )
{
   TCHAR  szBuffer[256];
   TCHAR  szBuffer2[256];

   wsprintf(szBuffer, TEXT("An %ld error occured."), GetLastError());
   // Display the error message
   wsprintf(szBuffer2, TEXT("Generic, Line=%d, File=%s"), wLine, lpszFile);
   MessageBox(NULL, szBuffer2, szBuffer, MB_ICONEXCLAMATION | MB_OK);
    return;
}



