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
/*++


  File: main.c

  Abstract:

  Contents:
      WinMain()
      InitApplication()
      InitInstance()
      MainWndProc()

  History:

--*/

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include <string.h>
#include <memory.h>
#include <rapi.h>
#include <strsafe.h>

#include "CeInvoke.h"

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

UINT WChar2Char( 
    LPCWSTR pwszSrc, 
    LPSTR pszDst,
    UINT cbDest)
{
   return WideCharToMultiByte( CP_ACP, 0, pwszSrc, -1, pszDst, cbDest, 
      NULL, NULL );
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd )
{
   TCHAR     szTmp[cchSzMax];
   WCHAR     szFn[cchSzMax];
   WCHAR     szCmd[cchSzMax];
   LPTSTR    szOut = NULL;
   BOOL      fStream = FALSE;
   BOOL      fRapiInitialized = FALSE;
   BYTE    * pBuf = NULL;
   HRESULT   hr;
   int       iFn = 0;
   
   IRAPIStream * pStream = NULL;

   DWORD cbInput = 0;
   DWORD cbOut = cchSzMax;

   hr = CeRapiInit();
   if(FAILED(hr))
   { 
        goto Error;
   }
   fRapiInitialized = TRUE;

   if ( lstrlen( lpCmdLine ) )
   {
      if ( !( lstrcmpi( lpCmdLine, c_szStoreInfo ) ) )
      {
         hr = StringCchCopyW(szFn, ARRAYSIZE(szFn), c_szFnBlock);
         if(FAILED(hr))
         {
            goto Error;
         }

         hr = StringCchCopyW(szCmd, ARRAYSIZE(szCmd), c_szGetStoreInfo);
         if(FAILED(hr))
         {
             goto Error;
         }
         cbInput = ( wcslen( c_szGetStoreInfo ) + 1 ) * sizeof(WCHAR);
      }
      else if ( !( lstrcmpi( lpCmdLine, c_szStream1 ) ) )
      {
         fStream = TRUE; 
         iFn = 1;
         hr = StringCchCopyW(szFn, ARRAYSIZE(szFn), c_szFnStreamMode1);
         if(FAILED(hr))
         {
             goto Error;
         }
         hr = StringCchCopyW(szCmd, ARRAYSIZE(szCmd), c_szFnStreamMode1);
         if(FAILED(hr))
         {
             goto Error;
         }
         
         cbInput = ( wcslen( c_szFnStreamMode1 ) + 1 ) * sizeof(WCHAR);
      }
      else if ( !( lstrcmpi( lpCmdLine, c_szStream2 ) ) )
      {
         fStream = TRUE; 
         iFn = 2;
         hr = StringCchCopyW(szFn, ARRAYSIZE(szFn), c_szFnStreamMode2);
         if(FAILED(hr))
         {
             goto Error;
         }
         hr = StringCchCopyW(szCmd, ARRAYSIZE(szCmd), c_szFnStreamMode2);
         if(FAILED(hr))
         {
             goto Error;
         }
         cbInput = ( wcslen( c_szFnStreamMode2 ) + 1 ) * sizeof(WCHAR);
      }
      else
      {
         hr = StringCchCopyW(szFn, ARRAYSIZE(szFn), c_szFnBlock);
         if(FAILED(hr))
         {
             goto Error;
         }
         hr = StringCchCopyW(szCmd, ARRAYSIZE(szCmd), L"Unknown");
         if(FAILED(hr))
         {
             goto Error;
         }
         cbInput = ( wcslen( szCmd ) + 1 ) * sizeof(WCHAR);
         
      }

   }

   TCHAR sz[ cchSzMax ];

   hr = CeRapiInvoke( c_szDllName, szFn,
                      cbInput, ( BYTE * ) szCmd,  
                      &cbOut, ( BYTE ** ) &szOut, fStream ? &pStream : NULL, NULL );
   if(FAILED(hr))
   {
       goto Error;
   }

   if ( !fStream ) 
   {
      if ( szOut )
      {
         WChar2Char( ( WCHAR * ) szOut, sz, sizeof(sz));
         StringCchPrintf(szTmp, ARRAYSIZE(szTmp), "Return = 0x%X, '%s'", hr, sz );         
      }
      else
      {
         StringCchPrintf(szTmp, ARRAYSIZE(szTmp), "Return = 0x%X, ( Unknown string )", hr );
      }

      MessageBox( NULL, szTmp, "CeInvoke", MB_OK );
      // RapiFreeBuffer( szOut );
   }
   else
   {
      if ( pStream )
      {
         DWORD cbRead;
         if ( iFn == 1 )
         {

            if ( SUCCEEDED( hr = pStream->Read( &cbOut, sizeof ( cbOut ), &cbRead ) ) )
            {
               pBuf = ( BYTE * ) new BYTE[ cbOut + sizeof(WCHAR)];
               if(!pBuf)
               {
                   goto Error;
               }

               if ( SUCCEEDED( hr = pStream->Read( pBuf, cbOut , &cbRead ) ) )
               {
                  WChar2Char( ( WCHAR * ) pBuf, szTmp, sizeof(szTmp) );
                  delete[] pBuf;
                  pBuf = NULL;
               }
               else
               {
                  StringCchPrintf(szTmp, ARRAYSIZE(szTmp), "Return = 0x%X, ( Unknown stream )", hr );
               }

               MessageBox( NULL, szTmp, "CeInvoke", MB_OK );

            }
            pStream->Release();
            pStream = NULL;
         }
         else if ( iFn == 2 )
         {
            TCHAR szLarge[ cchSzMax * 10 ];

            *szTmp = 0;
            *szLarge = 0;
            while ( lstrcmpi( szTmp, c_szDone ) != 0 )
            {
               if ( SUCCEEDED( hr = pStream->Read( &cbOut, 
                  sizeof ( cbOut ), &cbRead ) ) )
               {
                  pBuf = ( BYTE * ) new BYTE[ cbOut + sizeof(WCHAR)];
                  if(!pBuf)
                  {
                      goto Error;
                  }

                  if ( SUCCEEDED( hr = pStream->Read( pBuf, cbOut , &cbRead ) ) )
                  {
                     WChar2Char( ( WCHAR * ) pBuf, szTmp, sizeof(szTmp));
                     if ( lstrcmpi( szTmp, c_szDone ) )
                     {
                        hr = StringCchCat(szLarge, ARRAYSIZE(szLarge), szTmp);
                        if(FAILED(hr))
                        {
                            goto Error;
                        }
                        hr = StringCchCat(szLarge, ARRAYSIZE(szLarge), ", ");
                        if(FAILED(hr))
                        {
                            goto Error;
                        }
                     }
                     else
                     {
                        delete[] pBuf;
                        pBuf = NULL;
                        goto DisplayInfo;
                     }
                  }
                  else
                  {
                     StringCchPrintf(szTmp, ARRAYSIZE(szTmp), "Return = 0x%X, ( Unknown stream )", hr );
                  }

                  delete[] pBuf;
                  pBuf = NULL;
               }
            }

DisplayInfo:
               pStream->Release();
               pStream = NULL;
               MessageBox( NULL, szLarge, "CeInvoke", MB_OK );
         }
      }
   }

Error:
   if(pBuf)
   {
       delete [] pBuf;
   }
   if(pStream)
   {
       pStream->Release();
   }
   if(fRapiInitialized)
   {
       CeRapiUninit();
   }
   return(1);
}
