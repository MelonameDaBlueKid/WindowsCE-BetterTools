/*++

  Copyright (c) 1995 Microsoft Corporation

  File: main.c

  Abstract:

  Contents:
      WinMain()
      InitApplication()
      InitInstance()
      MainWndProc()

  History:

--*/

#include <windowsx.h>
#include "rapi.h"

#include "Cei.h"


UINT WChar2Char( 
    LPCWSTR pwszSrc, 
    LPSTR pszDst )
{
   return WideCharToMultiByte( CP_ACP, 0, pwszSrc, -1, pszDst, MAX_PATH, 
      NULL, NULL );
}


UINT Char2WChar( 
   LPCSTR pszSrc, 
   LPWSTR pwszDst )
{
   return MultiByteToWideChar( CP_ACP, 0, pszSrc, -1, pwszDst, MAX_PATH );
}


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd )
{
   TCHAR szTmp[ cchSzMax ];
   WCHAR szFn[  cchSzMax ];
   WCHAR szCmd[ cchSzMax ];
   LPTSTR szOut = NULL;
   BOOL  fStream = FALSE;
   int   iFn = 0;

   IRAPIStream *pStream = NULL;

   DWORD cbInput = 0;
   DWORD cbOut = cchSzMax;

   CeRapiInit();
   if ( lstrlen( lpCmdLine ) )
   {
      if ( !( lstrcmpi( lpCmdLine, c_szStoreInfo ) ) )
      {
         wcscpy( szFn, c_szFnBlock );
         wcscpy( szCmd, c_szGetStoreInfo );
         cbInput = ( wcslen( c_szGetStoreInfo ) + 1 ) * 2;
      }
      else if ( !( lstrcmpi( lpCmdLine, c_szStream1 ) ) )
      {
         fStream = TRUE; 
         iFn = 1;
         wcscpy( szFn, c_szFnStreamMode1   );
         wcscpy( szCmd, c_szFnStreamMode1   );
         cbInput = ( wcslen( c_szFnStreamMode1 ) + 1 ) * 2;
      }
      else if ( !( lstrcmpi( lpCmdLine, c_szStream2 ) ) )
      {
         fStream = TRUE; 
         iFn = 2;
         wcscpy( szFn, c_szFnStreamMode2 );
         wcscpy( szCmd, c_szFnStreamMode2 );
         cbInput = ( wcslen( c_szFnStreamMode2 ) + 1 ) * 2;
      }
      else
      {
         wcscpy( szFn, c_szFnBlock );
         wcscpy( szCmd, L"Unknown" );
         cbInput = ( wcslen( szCmd ) + 1 ) * 2;
         
      }

   }

   TCHAR sz[ cchSzMax ];

   HRESULT  hr = CeRapiInvoke( c_szDllName, szFn,
      cbInput, ( BYTE * ) szCmd,  
      &cbOut, ( BYTE ** ) &szOut, fStream ? &pStream : NULL, NULL );

   if ( !fStream ) 
   {
      if ( szOut )
      {
         WChar2Char( ( WCHAR * ) szOut, sz );
         wsprintf( szTmp, "Return = 0x%X, '%s'", hr, sz );
      }
      else
         wsprintf( szTmp, "Return = 0x%X, ( Unknown string )", hr );

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
               BYTE * pBuf = ( BYTE * ) new BYTE[ cbOut + 2 ];

               if ( SUCCEEDED( hr = pStream->Read( pBuf, cbOut , &cbRead ) ) )
               {
                  WChar2Char( ( WCHAR * ) pBuf, szTmp );
                  delete[] pBuf;
               }
               else
                  wsprintf( szTmp, "Return = 0x%X, ( Unknown stream )", hr );

               MessageBox( NULL, szTmp, "CeInvoke", MB_OK );

            }
            pStream->Release();
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
                  BYTE * pBuf = ( BYTE * ) new BYTE[ cbOut + 2 ];

                  if ( SUCCEEDED( hr = pStream->Read( pBuf, cbOut , &cbRead ) ) )
                  {
                     WChar2Char( ( WCHAR * ) pBuf, szTmp );
                     if ( lstrcmpi( szTmp, c_szDone ) )
                     {
                        lstrcat( szLarge, szTmp );
                        lstrcat( szLarge, ", " );
                     }
                     else
                     {
                        delete[] pBuf;
                        goto DisplayInfo;
                     }
                  }
                  else
                     wsprintf( szTmp, "Return = 0x%X, ( Unknown stream )", hr );

                  delete[] pBuf;
               }
            }

DisplayInfo:
               pStream->Release();
               MessageBox( NULL, szLarge, "CeInvoke", MB_OK );
         }
      }
   }

   CeRapiUninit();
   return(1);
}
