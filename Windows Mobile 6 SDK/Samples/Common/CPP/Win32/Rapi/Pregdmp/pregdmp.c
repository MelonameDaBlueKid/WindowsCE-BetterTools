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
//*******************************************************************************************
//
// Filename : pregdmp.c
//	
//
//*******************************************************************************************
#include <windows.h>
#include <tchar.h>
#include <rapi.h>

#define	MAX_NAME_BUF_SIZE	256
#define	MAX_VALUE_BUF_SIZE	1024


void DumpChild(HKEY hKey, int level)
{
    TCHAR Name[MAX_NAME_BUF_SIZE+2];
    DWORD cbName = MAX_NAME_BUF_SIZE;
    HKEY hChildKey;
    DWORD dwType; DWORD dwcbData;
    BYTE lpData[MAX_VALUE_BUF_SIZE+2];
    LPTSTR lpszString;
    int     i, j, k, x;
    UINT    n;
	LONG	lRet;

    // Throw a pair of NULLS on end of string so printfs don't run off the end of max size strings
    lpData[MAX_VALUE_BUF_SIZE] = lpData[MAX_VALUE_BUF_SIZE+1] = 0;

    for (i = 0; ERROR_SUCCESS == CeRegEnumKeyEx(hKey, i, Name, &cbName, NULL, NULL, NULL, NULL); i++)
    {
		_tprintf( TEXT("<%04ld> "), i);
		for (j = 0; j < level; j++)
			_tprintf(TEXT("\t"));

		_tprintf(TEXT("[%s]\r\n"), Name);

		if ((lRet = CeRegOpenKeyEx(hKey, Name, 0, 0, &hChildKey)) != ERROR_SUCCESS)
		{
		    _tprintf(TEXT("Failed to open key %s, err codee %u\r\n"), Name, lRet);
		}
		else
		{
		    cbName = MAX_NAME_BUF_SIZE;
		    dwcbData = MAX_VALUE_BUF_SIZE;
		    for (k = 0; ERROR_SUCCESS == CeRegEnumValue(hChildKey, k, Name, &cbName, NULL, &dwType, lpData, &dwcbData); k++)
		    {
				_tprintf( TEXT("(%04ld) "), k);
				for (x = 0; x < level+1; x++)
					_tprintf(TEXT("\t"));

				switch(dwType) {
				    case REG_DWORD:
						_tprintf(TEXT("DWORD: %s = "), Name);
						wsprintf(Name, TEXT("0x%lx"), *((LPDWORD)lpData));
						_tprintf(TEXT("%s"), Name);
						break;

				    case REG_SZ:
						_tprintf(TEXT("SZ: %s = %s"), Name, (LPTSTR)lpData);
		
						break;

				    case REG_MULTI_SZ:
                        _tprintf(TEXT("MULTI_SZ: %s"), Name);
                        lpszString = (LPTSTR)lpData;
                        while( 0 != *lpszString )
                        {
                            _tprintf(TEXT("\r\n"));
                            for (x = 0; x < level+2; x++)
                                _tprintf(TEXT("\t"));
                            _tprintf(TEXT("SZ: %s"), lpszString );
                            lpszString += _tcslen( lpszString ) + 1;
                        }
						break;

				    case REG_BINARY :
						_tprintf(TEXT("BINARY: %s ="), Name);
									for (n=0; n < (UINT)dwcbData; n++)
										_tprintf(TEXT(" 0x%lx"), *(lpData+n));
						break;

				    default:
						_tprintf(TEXT("ERROR: Unknown Type"));
				}

				_tprintf(TEXT("\r\n"));
				cbName = MAX_NAME_BUF_SIZE;
				dwcbData = MAX_VALUE_BUF_SIZE;
		    }

		    DumpChild(hChildKey, level + 1);
		    CeRegCloseKey(hChildKey);
		}

		cbName = MAX_NAME_BUF_SIZE;
    }
}




int main(int argc, char *argv[])
{
	HRESULT hRapiResult;

	_tprintf(TEXT("Remote Registry Dump\r\n\r\n"));

	_tprintf( TEXT("Connecting to Windows CE..."));
	hRapiResult = CeRapiInit();

    if (FAILED(hRapiResult))
	{
		_tprintf( TEXT("Failed\n"));
		return 1;
	}

	_tprintf( TEXT("Success\n"));
	
	_tprintf(TEXT("HKEY_CLASSES_ROOT\r\n"));
	DumpChild(HKEY_CLASSES_ROOT, 1);
	_tprintf(TEXT("HKEY_CURRENT_USER\r\n"));
	DumpChild(HKEY_CURRENT_USER, 1);
	_tprintf(TEXT("HKEY_LOCAL_MACHINE\r\n"));
	DumpChild(HKEY_LOCAL_MACHINE, 1);

	_tprintf(TEXT("\r\n"));

	CeRapiUninit();
	return 0;
}

		
