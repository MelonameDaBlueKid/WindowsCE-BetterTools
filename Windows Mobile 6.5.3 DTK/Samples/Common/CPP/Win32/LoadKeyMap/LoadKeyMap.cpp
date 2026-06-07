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
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

#include <windows.h>
#include "aygshell.h"
#include "macros.h"

// Define globals
const TCHAR *gc_szProgName = _T("LoadKeyMap");

// Sample key mappings
// Note:  All characters must be lowercase or caseless

// Classic 12-Key mapping table data:
const KEYMAPPING gc_rgKeyMaps_12Key[] =
{   // chHardware   , rgchMatches
    {     L'0'      , L"0+"        },
    {     L'1'      , L"1.,?!-'@:" },  // These characters can be multitapped from 1
    {     L'2'      , L"2abc"      },
    {     L'3'      , L"3def"      },
    {     L'4'      , L"4ghi"      },
    {     L'5'      , L"5jkl"      },
    {     L'6'      , L"6mno"      },
    {     L'7'      , L"7pqrs"     },
    {     L'8'      , L"8tuv"      },
    {     L'9'      , L"9wxyz"     },
    {     L'#'      , L"# "        },    // Let # act as space (and a delimiter)
};
// * is typically reserved for special functions and so characters are not mapped to it

// Sample 15-Key mapping table data:
// Note: All characters must be lowercase or caseless
const KEYMAPPING gc_rgKeyMaps_15Key[] =
{   // chHardware   , rgchMatches
    {     L'q'      , L"q!w"     },
    {     L'e'      , L"e1r"     },
    {     L't'      , L"t2y"     },
    {     L'u'      , L"u3i"     },
    {     L'o'      , L"o.p"     },
    {     L'a'      , L"a?s"     },
    {     L'd'      , L"d4f"     },
    {     L'g'      , L"g5h"     },
    {     L'j'      , L"j6k"     },
    {     L'l'      , L"l,"      },
    {     L'z'      , L"zx"      },
    {     L'c'      , L"c7v"     },
    {     L'b'      , L"b8n"     },
    {     L'm'      , L"m9"      },
    {     L' '      , L" 0"      },
};

// Sample 30-Key mapping table data:
const KEYMAPPING gc_rgKeyMaps_30Key[] =
{   // chHardware   , rgchMatches
    {     L'?'      , L"?0"      },
    {     L'w'      , L"w1"      },
    {     L'e'      , L"e2"      },
    {     L'r'      , L"r3"      },
    {     L's'      , L"s4"      },
    {     L'd'      , L"d5"      },
    {     L'f'      , L"f6"      },
    {     L'x'      , L"x7"      },
    {     L'c'      , L"c8"      },
    {     L'v'      , L"v9"      },
    {     L'q'      , L"q\""     },
    {     L'a'      , L"a;"      },
    {     L'z'      , L"z*"      },
    {     L't'      , L"t("      },
    {     L'y'      , L"y)"      },
    {     L'u'      , L"u-"      },
    {     L'i'      , L"i+"      },
    {     L'o'      , L"o&"      },
    {     L'p'      , L"p:"      },
    {     L'g'      , L"g/"      },
    {     L'h'      , L"h\\"     },
    {     L'j'      , L"j$"      },
    {     L'k'      , L"k="      },
    {     L'l'      , L"l@"      },
    {     L'b'      , L"b#"      },  
    {     L'n'      , L"n!"      },
    {     L'm'      , L"m,"      },
};

typedef int IDMAP;
#define IDMAP_RESTORE      -1
#define IDMAP_NONE          0
#define IDMAP_12KEY        12
#define IDMAP_15KEY        15
#define IDMAP_30KEY        30

HRESULT LoadKeyMapByID(IDMAP idk)
{
    HRESULT hr = S_OK;
    HANDLE hLoadKeyMap = INVALID_HANDLE_VALUE;

    switch (idk)
    {
        case IDMAP_12KEY:
            hLoadKeyMap = LoadKeyMap((PKEYMAPPING)gc_rgKeyMaps_12Key, ARRAYSIZE(gc_rgKeyMaps_12Key));
            CBR(INVALID_HANDLE_VALUE != hLoadKeyMap);
            break;
            
        case IDMAP_15KEY:
            hLoadKeyMap = LoadKeyMap((PKEYMAPPING)gc_rgKeyMaps_15Key, ARRAYSIZE(gc_rgKeyMaps_15Key));
            CBR(INVALID_HANDLE_VALUE != hLoadKeyMap);
            break;
            
        case IDMAP_30KEY:
            hLoadKeyMap = LoadKeyMap((PKEYMAPPING)gc_rgKeyMaps_30Key, ARRAYSIZE(gc_rgKeyMaps_30Key));
            CBR(INVALID_HANDLE_VALUE != hLoadKeyMap);
            break;
            
        case IDMAP_RESTORE:
            // Ideally the handle returned from LoadKeyMap should be used
            // to unload a key mapping but NULL can be used to unload all
            // applicable key mappings.
            CHR(UnloadKeyMap((HANDLE)NULL));
            break;
            
        case IDMAP_NONE:
            hLoadKeyMap = LoadKeyMap(NULL, 0);
            CBR(INVALID_HANDLE_VALUE != hLoadKeyMap);
            break;
            
        default:
            // Unrecognized ID
            CHR(E_INVALIDARG);
            break;
    }

Error:
    
    return hr;
}

// Safer version of _tcstol that checks for errors
HRESULT Safe_tcstol(__in const TCHAR *pszToConvert, __out const TCHAR **ppszEndPtr, int iBase, __out int *piConverted)
{
    HRESULT hr = S_OK;

    ASSERT(pszToConvert && piConverted);

    // Try to convert the string
    *piConverted = _tcstol(pszToConvert, (TCHAR **)ppszEndPtr, iBase);

    // Check for out of bounds
    if ((LONG_MIN == *piConverted) || (*piConverted == LONG_MAX))
    {
        return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
    }

    // Check for conversion error
    if (0 == *piConverted)
    {
        // This could be a conversion error or maybe the converted value really is 0.
        // If a conversion error occurred then pszEndPtr would point at pszToConvert
        CBR(pszToConvert != *ppszEndPtr);
    }

    // If we made it this far, conversion was successful

Error:
    return hr;
}

// Be sure to free pKeyMap.rgchMatches when done
HRESULT GetKeyMapping(__in const TCHAR *pszLine, __out PKEYMAPPING pKeyMap)
{
    HRESULT hr = S_OK;
    int i = 0;
    int nConverted;
    TCHAR chHardware;
    const TCHAR *pszCur = pszLine;
    TCHAR rgchMatches[MAX_PATH];  // This should be more than enough
    TCHAR *pszMatches = NULL;
    DWORD cchMatches = 0;

    if (NULL == pKeyMap)
    {
        return E_INVALIDARG;
    }

    // Get chHardware value
    CHR(Safe_tcstol(pszCur, &pszCur, 16, &nConverted));

    // Verify the colon delimiter is present
    CBR(pszCur && (_T(':') == *pszCur));

    // Verify the chHardware value is valid (full TCHAR range)
    CBR((0 <= nConverted) && (nConverted <= 0xFFFF));

    // Save chHardware
    chHardware = (WCHAR)nConverted;

    // Get rgchMatches values
    pszCur++;  // Advance past :

    // Read and save rgchMatches entries
    while (i < ARRAYSIZE(rgchMatches))
    {
        CHR(Safe_tcstol(pszCur, &pszCur, 16, &nConverted));

        // Verify the comma delimiter is present or
        // there are no more entries
        CBR(pszCur && ((_T(',') == *pszCur) || !*pszCur));

        // Verify the match character value is valid.
        // We assume the full TCHAR range is valid even though it might not be.
        // LoadKeyMap will let us know if there's a problem.
        CBR((0 <= nConverted) && (nConverted <= 0xFFFF));

        // Save match and advance index in preparation for the next one
        rgchMatches[i++] = (WCHAR)nConverted;

        if (!*pszCur)
        {
            // No more characters to map
            break;
        }

        pszCur++;  // Advance past ,
    }
    rgchMatches[i] = _T('\0');  // Terminate string

    // Allocate memory to store matches
    cchMatches = _tcslen(rgchMatches) + 1;
    pszMatches = (TCHAR *)LocalAlloc(LMEM_FIXED, sizeof(TCHAR) * cchMatches);
    CPR(pszMatches);

    // Copy rgchMatches
    CHR(StringCchCopy(pszMatches, cchMatches, rgchMatches));

    // Update KeyMap
    pKeyMap->chHardware = chHardware;
    pKeyMap->rgchMatches = (WCHAR *)pszMatches;

    // Caller owns memory for pszMatches now
    pszMatches = NULL;

Error:
    LocalFree(pszMatches);
    
    return hr;
}

HRESULT ProcessCommand(LPTSTR pszCommand)
{
    FILE *fp = NULL;
    HRESULT hr = S_OK;
    KEYMAPPING rgKeyMaps[MAX_PATH] = {0};  // This should be more than enough
    int iKeyMap = 0;
    TCHAR *pszFilePath = NULL;

    CBR(pszCommand && *pszCommand);

    // Check for Usage1:  <KEYMAPPINGFILE>
    // We assume that the file path will have an extension so we look for .
    pszFilePath = pszCommand;
    if (_tcschr(pszFilePath, _T('.')))
    {
        TCHAR szLine[MAX_PATH];  // Hopefully this is large enough
        // Open KEYMAPPINGFILE
        fp = _tfopen(pszFilePath, _T("r"));
        if (NULL == fp)
        {
            CHR(E_INVALIDARG);
        }
        
        // Read KEYMAPPING data
        while (_fgetts(szLine, ARRAYSIZE(szLine), fp))
        {
            // Terminate line at \r or \n if it exists
            size_t iEnd = _tcscspn(szLine, _T("\r\n"));
            szLine[iEnd] = _T('\0');

            // Check for empty line
            if (0 == iEnd)
            {
                // No more mappings
                break;
            }

            CBR(iKeyMap < ARRAYSIZE(rgKeyMaps));
            CHR(GetKeyMapping(szLine, rgKeyMaps + iKeyMap));

            // Advance index to save the next one
            iKeyMap++;
        }

        CBR(INVALID_HANDLE_VALUE != LoadKeyMap(rgKeyMaps, iKeyMap));
    }
    else
    {
        // Usage2:  <IDMAP>
        TCHAR *pszIDMap = pszCommand;
        int idk = _ttoi(pszIDMap);
        if (0 == idk)
        {
            // Check to see if 0 was returned due to a parsing error
            if (_T('0') != *pszIDMap)
            {
                CHR(E_INVALIDARG);
            }
        }

        CHR(LoadKeyMapByID((IDMAP)idk));
    }

Error:
    // Free all of the allocated memory in rgKeyMaps
    while (0 < iKeyMap)
    {
        // iKeyMap is the next available index so we have to subtract one before freeing
        LocalFree((HLOCAL)rgKeyMaps[--iKeyMap].rgchMatches);
    }
    
    if (fp)
    {
        fclose(fp);
    }

    return hr;
}

