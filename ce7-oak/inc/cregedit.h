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
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  

Abstract:

Notes: 
--*/
#ifndef __CREGEDIT_H_
#define __CREGEDIT_H_
#include <winreg.h>
#include <ddkreg.h>

class CRegistryEdit
{
public:
    CRegistryEdit( LPCTSTR RegPath )
    {
        m_hDevKey = NULL;
        if( RegPath )
        {
            m_hDevKey = OpenDeviceKey( RegPath );
        }
    }
    
    CRegistryEdit( HKEY hKey, LPCTSTR pszRegPath )
    {
        m_hDevKey = NULL;
        if( pszRegPath )
        {
            if( RegOpenKeyEx( hKey, pszRegPath, 0, 0, &m_hDevKey ) != ERROR_SUCCESS )
            {
                m_hDevKey = NULL;
            }
        }
    }

    CRegistryEdit( HKEY hKey, LPCTSTR pszRegPath, REGSAM SamDesired )
    {
        m_hDevKey = NULL;
        if( pszRegPath )
        {
            if( RegOpenKeyEx( hKey, pszRegPath, 0, SamDesired, &m_hDevKey ) != ERROR_SUCCESS )
            {
                m_hDevKey = NULL;
            }
        }
    }
    
    CRegistryEdit( HKEY hKey,
                           LPCTSTR pszRegPath,
                           PDWORD pdwDisposition )
    {
        m_hDevKey = NULL;
        if( pszRegPath )
        {
            if( RegCreateKeyEx( hKey,
                                pszRegPath,
                                0,
                                NULL,
                                0,
                                0,
                                NULL,
                                &m_hDevKey,
                                pdwDisposition ) != ERROR_SUCCESS )
            {
                m_hDevKey = NULL;
            }
        }
    }
    
    ~CRegistryEdit( void )
    {
        CloseKey();
    }
    BOOL CloseKey() {
        if( m_hDevKey )
        {
            RegCloseKey( m_hDevKey );
            m_hDevKey = NULL;
            return TRUE;
        }
        return FALSE;
    }
    
    DWORD   GetWindowInfo( DDKWINDOWINFO* pdwi )
    {
        if( pdwi && m_hDevKey )
        {
            pdwi->cbSize = sizeof( DDKWINDOWINFO );
            DWORD status = DDKReg_GetWindowInfo( m_hDevKey, pdwi );
            return status;
        }
        else
        {
            return ERROR_INVALID_FUNCTION;
        }
    }
    
    DWORD   GetIsrInfo( DDKISRINFO* pddi )
    {
        if( pddi && m_hDevKey )
        {
            pddi->cbSize = sizeof( DDKISRINFO );
            DWORD status = DDKReg_GetIsrInfo( m_hDevKey, pddi );
            return status;
        }
        else
        {
            return ERROR_INVALID_FUNCTION;
        }
    }
    
    DWORD   GetPciInfo( DDKPCIINFO* pdpi )
    {
        if( pdpi && m_hDevKey )
        {
            pdpi->cbSize = sizeof( DDKPCIINFO );
            DWORD status = DDKReg_GetPciInfo( m_hDevKey, pdpi );
            return status;
        }
        else
        {
            return ERROR_INVALID_FUNCTION;
        }
    };
    
    BOOL    GetRegValue( LPCWSTR lpcName, __out_bcount(dwDataLen) LPBYTE lpData, DWORD dwDataLen )
    {
        DWORD dwType = 0;
        LONG status = ::RegQueryValueEx( m_hDevKey,
                                           lpcName,
                                           NULL,
                                           &dwType,
                                           lpData,
                                           &dwDataLen );
        return ( status == ERROR_SUCCESS );
    }
    BOOL    GetRegSize( LPCWSTR lpcName, DWORD& dwDataLen )
    {
        DWORD dwType = 0;
        LONG status = ::RegQueryValueEx( m_hDevKey,
                                           lpcName,
                                           NULL,
                                           &dwType,
                                           NULL,
                                           &dwDataLen );
        return ( status == ERROR_SUCCESS || status == ERROR_MORE_DATA);
    }

    BOOL    RegQueryValueEx( LPCWSTR lpcName,
                             PDWORD pdwType,
                             __out_bcount_opt(*pdwDataLen) LPBYTE lpData,
                             PDWORD pdwDataLen )
    {
        LONG status = ::RegQueryValueEx( m_hDevKey,
                                           lpcName,
                                           NULL,
                                           pdwType,
                                           lpData,
                                           pdwDataLen );
        return ( status == ERROR_SUCCESS );
    };
    
    BOOL    RegSetValueEx( LPCWSTR lpcName,
                           DWORD dwType,
                           __in_bcount(dwDataLen) BYTE const*const lpData,
                           DWORD dwDataLen )

    {
        LONG status = ::RegSetValueEx( m_hDevKey,
                                         lpcName,
                                         NULL,
                                         dwType,
                                         lpData,
                                         dwDataLen );
        return ( status == ERROR_SUCCESS );
    }
    
    BOOL IsKeyOpened() const
    {
        return ( m_hDevKey != NULL );
    }
    
    HKEY GetHKey()
    {
        return m_hDevKey;
    }
    
    BOOL RegQueryInfoKey( __out_ecount_opt(*lpcchClass) LPWSTR lpClass,
                          __inout_opt LPDWORD lpcchClass,
                          LPDWORD lpReserved,
                          LPDWORD lpcSubKeys,
                          LPDWORD lpcbMaxSubKeyLen,
                          LPDWORD lpcbMaxClassLen,
                          LPDWORD lpcValues,
                          LPDWORD lpcbMaxValueNameLen,
                          LPDWORD lpcbMaxValueLen,
                          LPDWORD lpcbSecurityDescriptor,
                          PFILETIME lpftLastWriteTime )
    {
        return ( ::RegQueryInfoKey( m_hDevKey,
                                    lpClass,
                                    lpcchClass,
                                    lpReserved,
                                    lpcSubKeys,
                                    lpcbMaxSubKeyLen,
                                    lpcbMaxClassLen,
                                    lpcValues,
                                    lpcbMaxValueNameLen,
                                    lpcbMaxValueLen,
                                    lpcbSecurityDescriptor,
                                    lpftLastWriteTime ) == ERROR_SUCCESS );
    }
    
    BOOL RegEnumKeyEx( DWORD dwIndex,
                       __out_ecount(*lpcchName) LPWSTR lpName,
                       LPDWORD lpcchName,
                       LPDWORD lpReserved,
                       __inout_ecount_opt(*lpcbClass) LPWSTR lpClass,
                       __inout_opt LPDWORD lpcbClass,
                       PFILETIME lpftLastWriteTime )
    {
        PREFAST_SUPPRESS(386, "Buffer overrun while writing to 'lpClass': the writable size is 'lpcbClass' bytes, but 'lpcbClass*2' bytes may be written.");
        return ( ::RegEnumKeyEx( m_hDevKey,
                                 dwIndex,
                                 lpName,
                                 lpcchName,
                                 lpReserved,
                                 lpClass,
                                 lpcbClass,
                                 lpftLastWriteTime ) == ERROR_SUCCESS );
    }
    
    BOOL RegEnumValue( DWORD dwIndex,
                       __out_ecount(*lpcchValueName) LPWSTR lpValueName,
                       __inout LPDWORD lpcchValueName,
                       LPDWORD lpReserved,
                       LPDWORD lpType,
                       __out_bcount(*lpcbData) LPBYTE lpData,
                       __inout LPDWORD lpcbData )
    {
        return ( ::RegEnumValue( m_hDevKey,
                                 dwIndex,
                                 lpValueName,
                                 lpcchValueName,
                                 lpReserved,
                                 lpType,
                                 lpData,
                                 lpcbData ) == ERROR_SUCCESS );
    }
    
    BOOL RegDeleteValue( LPCWSTR lpValueName )
    {
        return ( ::RegDeleteValue( m_hDevKey, lpValueName ) == ERROR_SUCCESS );
    }

    BOOL    RegGetList( LPCWSTR ValName, PDWORD pNum, __out_ecount(*pNum) DWORD List[] )
    {
        union {
            WCHAR ValList[2 * DEVKEY_LEN];

            // ValList is cast to a DWORD* so we put it in a union
            // with a DWORD to guarantee proper alignment;
            DWORD dwToForceFourByteAlignment;
        };
        
        DWORD ValLen = sizeof( ValList );
        DWORD ValType;
        if( pNum == NULL || List == NULL )
        {
            return FALSE;
        }

        DWORD MaxItems = *pNum;
        DWORD Status = ::RegQueryValueEx( m_hDevKey,
                                          ValName,
                                          NULL,
                                          &ValType,
                                          ( PBYTE ) ValList,
                                          &ValLen );

        *pNum = 0;

        if( Status != ERROR_SUCCESS )
        {
            return FALSE;
        }

        if( ValType == REG_MULTI_SZ )
        {
            // Registry entry is multiple strings
            DWORD i;
            WCHAR const* bp;

            for( bp = ValList, i = 0; i < MaxItems; i++ )
            {
                PWCHAR ep;

                if( *bp == ( WCHAR ) '\0' )
                    break;

                List[i] = wcstoul( bp, &ep, 16 );

                if( bp == ep )
                    break;

                ( *pNum )++;
                bp = ++ep;
            }

            if( ( i == MaxItems ) && ( *bp != ( WCHAR ) '\0' ) )
            {
                // There are more strings in the registry entry than there are locations on the List
                return FALSE;
            }
        }
        else if( ValType == REG_DWORD )
        {
            // Registry entry is DWORD
            List[0] = *( DWORD * ) ValList;
            *pNum = 1;
        }
        else
        {
            // Registry entry is some other type; ignore
            return FALSE;
        }

        return TRUE;
    }

    BOOL    RegSetList( LPCWSTR ValName, DWORD Num, DWORD __out_ecount(Num) List[] )
    {
        WCHAR ValList[2 * DEVKEY_LEN];
        DWORD Status;

        if( Num == 0 )
        {
            return TRUE;
        }
        else if( Num == 1 )
        {
            Status = ::RegSetValueEx( m_hDevKey,
                                      ValName,
                                      0,
                                      REG_DWORD,
                                      ( PBYTE ) List,
                                      sizeof( List[0] ) );
        }
        else
        {
            DWORD i;
            PWCHAR bp = ValList;
            DWORD cbp = _countof(ValList);
            WCHAR Item[11];          // Largest number of characters produced by _ultow is 10 + termination character
            size_t ItemSize, Size = 0;

            for( i = 0; i < Num; i++ )
            {
                _ultow_s( List[i], Item, _countof(Item), 16 );
                StringCchLength(Item, _countof(Item), &ItemSize);
                ++ItemSize;

                Size += ItemSize;
                if( Size < ItemSize || Size >= 2 * DEVKEY_LEN )
                {
                    // List too big
                    return FALSE;
                }

                wcscpy_s( bp, cbp, Item );
                bp += ItemSize;
                cbp -= ItemSize;
            }

            *bp = ( WCHAR ) '\0';
            Size++;

            Status = ::RegSetValueEx( m_hDevKey,
                                      ValName,
                                      0,
                                      REG_MULTI_SZ,
                                      ( PBYTE ) ValList,
                                      Size * sizeof( WCHAR ) );
        }

        if( Status == ERROR_SUCCESS )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

private:
    HKEY    m_hDevKey;
};

#endif
