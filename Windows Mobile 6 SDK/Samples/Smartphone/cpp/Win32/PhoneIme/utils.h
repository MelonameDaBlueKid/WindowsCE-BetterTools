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

#ifndef __UTILS_H__
#define __UTILS_H__

// Size of composition string components
#define MAXCOMPSIZE             256
#define MAXCLAUSESIZE           16

// Composition and Result string flags for WM_IME_COMPOSITION messages
#define GCS_COMPALL ( GCS_COMPSTR | GCS_COMPATTR | GCS_COMPREADSTR | GCS_COMPREADATTR | GCS_COMPCLAUSE | GCS_COMPREADCLAUSE)
#define GCS_RESULTALL ( GCS_RESULTSTR | GCS_RESULTREADSTR | GCS_RESULTCLAUSE | GCS_RESULTREADCLAUSE)

// Clear flags for composition string
#define CLR_RESULT 0x1
#define CLR_COMP   0x2

// Macros to access composition string components
#define GETLPCOMPREADATTR(lpcs) ((PBYTE)((PBYTE)(lpcs) + (lpcs)->dwCompReadAttrOffset))
#define GETLPCOMPREADCLAUSE(lpcs) ((PDWORD)((PBYTE)(lpcs) + (lpcs)->dwCompReadClauseOffset))
#define GETLPCOMPREADSTR(lpcs) ((PTSTR)((PBYTE)(lpcs) + (lpcs)->dwCompReadStrOffset))
#define GETLPCOMPATTR(lpcs) ((PBYTE)((PBYTE)(lpcs) + (lpcs)->dwCompAttrOffset))
#define GETLPCOMPCLAUSE(lpcs) ((PDWORD)((PBYTE)(lpcs) + (lpcs)->dwCompClauseOffset))
#define GETLPCOMPSTR(lpcs) ((PTSTR)((PBYTE)(lpcs) + (lpcs)->dwCompStrOffset))
#define GETLPRESULTREADCLAUSE(lpcs) ((PDWORD)((PBYTE)(lpcs) + (lpcs)->dwResultReadClauseOffset))
#define GETLPRESULTREADSTR(lpcs) ((PTSTR)((PBYTE)(lpcs) + (lpcs)->dwResultReadStrOffset))
#define GETLPRESULTCLAUSE(lpcs) ((PDWORD)((PBYTE)(lpcs) + (lpcs)->dwResultClauseOffset))
#define GETLPRESULTSTR(lpcs) ((PTSTR)((PBYTE)(lpcs) + (lpcs)->dwResultStrOffset))

// Clause information is a double word array that specifies the position of each clause.
// At a minimum, the length of this information is two double words. This means the 
// length of the clause information is eight bytes. The first double word has to be zero. 
// This is the starting position of the first clause. The last double word has to be 
// the length of this string.  
 
#define SETCLAUSE(pdw, len)   {*((LPDWORD)(pdw)) = 0; *((LPDWORD)(pdw)+1) = len;}

// Message to be generated
typedef struct _GENMSG {
    UINT msg;
    WPARAM wParam;
    LPARAM lParam;
} GENMSG, *PGENMSG;

// Composition string 
typedef struct _MYCOMPSTR{
    COMPOSITIONSTRING cs;
    TCHAR          szCompStr[MAXCOMPSIZE];
    BYTE           bCompAttr[MAXCOMPSIZE];
    TCHAR          szResultStr[MAXCOMPSIZE];
#ifdef FULL_CONVERSION_INFO
    TCHAR          szCompReadStr[MAXCOMPSIZE];
    BYTE           bCompReadAttr[MAXCOMPSIZE];
    DWORD          dwCompReadClause[MAXCLAUSESIZE];
    DWORD          dwCompClause[MAXCLAUSESIZE];
    TCHAR          szTypeInfo[MAXCOMPSIZE];
    TCHAR          szResultReadStr[MAXCOMPSIZE];
    DWORD          dwResultReadClause[MAXCOMPSIZE];
    DWORD          dwResultClause[MAXCOMPSIZE];
    DWORD          dwPrevConversion;
#endif // FULL_CONVERSION_INFO
} MYCOMPSTR, NEAR *PMYCOMPSTR, FAR *LPMYCOMPSTR;

void InitCompStr(LPCOMPOSITIONSTRING pcompstr, DWORD dwSize);
void ClearCompStr(LPCOMPOSITIONSTRING pcompstr, DWORD dwFlags);
void MoveCompositionToResult(COMPOSITIONSTRING *pcompstr);
VOID UpdateComposition(HIMC himc, LPTSTR pszCompNew, int cchCompNew, TCHAR chRead);
BOOL HasComposition(HIMC himc);
BOOL HasComposition(const COMPOSITIONSTRING *pcompstr);
BOOL IsReadingFull(const COMPOSITIONSTRING *pcompstr);


#ifdef DEBUG
BOOL ValidateInitedCompStr(const COMPOSITIONSTRING *pcompstr);
BOOL ValidateCompStr(const COMPOSITIONSTRING *pcompstr);
#endif // _DEBUG

#endif //__UTILS_H__
