
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

// ceinvoke.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "ceinvoke.h"

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

//---Copied from rapi.h---//
typedef enum tagRAPISTREAMFLAG
{
	STREAM_TIMEOUT_READ
} RAPISTREAMFLAG;

DECLARE_INTERFACE_ (IRAPIStream,  IStream)
{
		STDMETHOD(SetRapiStat)( THIS_ RAPISTREAMFLAG Flag, DWORD dwValue) PURE;
		STDMETHOD(GetRapiStat)( THIS_ RAPISTREAMFLAG Flag, DWORD *pdwValue) PURE;
};
//---//


////////////////////////////////////////////////////////////////////////
//
//  dll entry point 
//
////////////////////////////////////////////////////////////////////////
STDAPI_(BOOL) APIENTRY DllInit(HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
   switch( dwReason )
   {
      case DLL_PROCESS_ATTACH:
         RETAILMSG( TRUE, ( L"CeInvoke: DLL_PROCESS_ATTACH\n" ) );
         break;

      case DLL_PROCESS_DETACH:
         RETAILMSG( TRUE, ( L"CeInvoke: DLL_PROCESS_DETACH\n" ) );
         break;

      case DLL_THREAD_ATTACH:
         break;

      case DLL_THREAD_DETACH:
         break;

   }
   return TRUE;
}

void GetStoreInfo( LPTSTR pszStore, UINT cchStore)
{
   STORE_INFORMATION si;

   GetStoreInformation( &si );

   StringCchPrintfW(pszStore, cchStore,
      L"Total Storage Memory = %d bytes, Free Storage Memory = %d bytes",
      si.dwStoreSize, si.dwFreeSize );
}


STDAPI FnBlockMode(
   DWORD cbInput,
   BYTE  *pInput,
   DWORD *pcbOutput,
   BYTE  **ppOutput,
   IRAPIStream *pIRAPIStream )
{
   WCHAR    szTmp[ cchSzMax ];
   DWORD    dwOut = 0;
   HRESULT  hr = S_OK;

   RETAILMSG( TRUE, ( L"CeInvoke: Entering FnBlockMode\n" ) );

   if ( cbInput )
   {
      RETAILMSG( TRUE, ( L"FnBlockMode: %d, %s\n", cbInput, pInput ) );
      if ( !( wcscmp( ( WCHAR * ) pInput, c_szGetStoreInfo ) ) )
      {
         GetStoreInfo(szTmp, ARRAYSIZE(szTmp));
         dwOut = ( wcslen( szTmp ) + 1 ) * sizeof(WCHAR);
      }
      else
      {
		 StringCchCopyW(szTmp, ARRAYSIZE(szTmp), L"Unknown Command String passed in.");
         dwOut = ( wcslen( szTmp ) + 1 ) * sizeof(WCHAR);
      }
   }
   else
   {
	  StringCchCopyW(szTmp, ARRAYSIZE(szTmp), L"Empty Input buffer passed in.");
      dwOut = wcslen( szTmp ) * sizeof( WCHAR );
   }

   BYTE *pOut = ( BYTE * ) LocalAlloc( LPTR, dwOut );

   if ( pOut )
   {
      memcpy( pOut, szTmp, dwOut );
      *pcbOutput = dwOut;
      *ppOutput = pOut;
      RETAILMSG( TRUE, ( L"FnBlockMode: '%s'\n", szTmp ) );
   }
   else
   {
      RETAILMSG( TRUE, ( L"FnBlockMode: OOM\n" ) );
      *pcbOutput = 0;
      hr = E_OUTOFMEMORY;
      goto EndFBN;
   }

EndFBN:
   RETAILMSG( TRUE, ( L"CeInvoke: Leaving FnBlockMode\n" ) );
   return ( hr );
}


STDAPI FnStreamMode1(
   DWORD cbInput,
   BYTE  *pInput,
   DWORD *pcbOutput,
   BYTE  **ppOutput,
   IRAPIStream *pIRAPIStream )
{
   RETAILMSG( TRUE, ( L"CeInvoke: Entering FnStreamMode1\n" ) );

   const WCHAR szOut[] = L"FnStreamMode1: Ouput to a stream";

   if(!pIRAPIStream)
   {
	   return E_INVALIDARG;
   }

   DWORD cbWrite = ( wcslen( szOut ) + 1 ) * 2;
   DWORD cbWritten;

   HRESULT hr = pIRAPIStream->Write( &cbWrite, sizeof( cbWrite ), &cbWritten );
   hr = pIRAPIStream->Write( szOut, cbWrite, &cbWritten );
   pIRAPIStream->Release();

   // 

   RETAILMSG( TRUE, ( L"CeInvoke: Leaving FnStreamMode1\n" ) );
   return S_OK;
}


STDAPI FnStreamMode2(
   DWORD cbInput,
   BYTE  *pInput,
   DWORD *pcbOutput,
   BYTE  **ppOutput,
   IRAPIStream *pIRAPIStream )
{
   RETAILMSG( TRUE, ( L"CeInvoke: Entering FnStreamMode2\n" ) );

   HRESULT     hr;
   WCHAR       szOut[ cchSzMax ];
   DWORD       cbWrite;
   DWORD       cbWritten;

   CEOID       oidParent;
   CEOIDINFO   oidInfo;

   if(!pIRAPIStream)
   {
	   return E_INVALIDARG;
   }
      
   HANDLE      hFind = CeFindFirstDatabase( 0 );

   while ( ( oidParent = CeFindNextDatabase( hFind ) ) != 0 )
   {
      if ( !CeOidGetInfo( oidParent, &oidInfo ) )
	  {
         continue;
	  }

      RETAILMSG( TRUE, ( L"Database: Oid: 0x%X  Type: %d, Name: %s",
         oidParent, oidInfo.infDatabase.dwDbaseType, 
         oidInfo.infDatabase.szDbaseName ) );

      cbWrite = ( wcslen( oidInfo.infDatabase.szDbaseName ) + 1 ) * sizeof(WCHAR);

      hr = pIRAPIStream->Write( &cbWrite, sizeof( cbWrite ), &cbWritten );
      hr = pIRAPIStream->Write( oidInfo.infDatabase.szDbaseName, cbWrite, 
         &cbWritten );
   }

   CloseHandle( hFind );

   StringCchCopyW(szOut, ARRAYSIZE(szOut), L"_Done_");
   cbWrite = ( wcslen( szOut ) + 1 ) * sizeof(WCHAR);

   // Signal that we are done:
   hr = pIRAPIStream->Write( &cbWrite, sizeof( cbWrite ), &cbWritten );
   hr = pIRAPIStream->Write( szOut, cbWrite, &cbWritten );

   pIRAPIStream->Release();

   RETAILMSG( TRUE, ( L"CeInvoke: Leaving FnStreamMode2\n" ) );
   return S_OK;
}
