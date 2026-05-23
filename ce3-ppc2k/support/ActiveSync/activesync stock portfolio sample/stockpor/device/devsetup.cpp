/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/*++

Module Name:
    
      devsetup.cpp

Abstract:

      Setup the device registry for the Stock Portfolio device synchronization module
--*/

#include <windows.h>

#include "..\common.h"

const TCHAR v_szRegRoot[] = TEXT( "Windows CE Services\\Synchronization\\Objects" );
const TCHAR v_szSyncDll[] = TEXT( "\\Windows\\stdevs.dll" );
const TCHAR v_szTempDll[] = TEXT( "\\stdevs.dll" );
const TCHAR v_szSuccess[] = TEXT( "Installation completed. Please disconnect and reconnect the device to use the module." );
const TCHAR v_szFailure[] = TEXT( "Installation failed. Error Code: %d" );
const TCHAR v_szMsgTitle[] = TEXT( "Stock Portfolio Synchronization Module" );
const TCHAR v_szMoved[] = TEXT( "ActiveSync module is moved to \\Windows" );
const TCHAR v_szNotExist[] = TEXT( "ActiveSync module doesn't exist in \\Windows directory" );

/*++
--*/
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
    LONG    lErr;
    HKEY    hRootKey, hKey;
    DWORD   dw;

    lErr = RegCreateKeyEx( HKEY_LOCAL_MACHINE, v_szRegRoot, 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &hRootKey, &dw );
    if ( lErr != ERROR_SUCCESS ) goto Exit;

    lErr = RegCreateKeyEx( hRootKey, SZ_STOCKPOR, 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &hKey, &dw );
    if ( lErr != ERROR_SUCCESS ) goto Exit;

    lErr = RegSetValueEx( hKey, TEXT( "Store" ), NULL, REG_SZ, (const LPBYTE)v_szSyncDll, ( wcslen( v_szSyncDll ) + 1 ) * sizeof( WCHAR ) );

    RegCloseKey( hKey );
    RegCloseKey( hRootKey ); 

Exit:
    if ( GetFileAttributes( v_szTempDll ) != (DWORD)-1 )
    {
        if ( GetFileAttributes( v_szSyncDll ) != (DWORD)-1 )
            DeleteFile( v_szSyncDll );

        if ( MoveFile( v_szTempDll, v_szSyncDll ) )
            MessageBox( NULL, v_szMoved, v_szMsgTitle, MB_OK );
    }

    if ( lErr == ERROR_SUCCESS )
    {
        if ( GetFileAttributes( v_szSyncDll ) == (DWORD)-1 )
            MessageBox( NULL, v_szNotExist, v_szMsgTitle, MB_OK | MB_ICONSTOP );
        else
            MessageBox( NULL, v_szSuccess, v_szMsgTitle, MB_OK );
    }
    else 
    {   
        TCHAR   szMsg[ 200 ];
        wsprintf( szMsg, v_szFailure, lErr );
        MessageBox( NULL, szMsg, v_szMsgTitle, MB_OK | MB_ICONSTOP );
    }

    return lErr;
}

