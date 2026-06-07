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

#include "phoneime.h"

// NOTE: The OS allocates the COMPOSITIONSTRING structure. The IME lazily
// initializes this structure by resizing (see call to ImmReSizeIMCC) to 
// a MYCOMPSTR, which contains COMPOSITIONSTRING followed by conversion
// data. Use utility functions in this file to read and write data in COMPOSITIONSTRING
// and MYCOMPSTR. Before read/write in the utility functions, ASSERT that the
// COMPOSITIONSTRING or MYCOMPSTR is valid using ValidateCompStr or ValidateInitedCompStr
// depending on the data being accessed. For example, if only the data in COMPOSITIONSTRING
// is accessed, use ValidateCompStr. If the conversion data that follows COMPOSITIONSTRING
// is accessed, use ValidateInitedCompStr.
// This will prevent bugs caused by writing into a MYCOMPSTR when pcompstr really
// points to a COMPOSITIONSTRING which has not been resized.
// COMPOSITIONSTRING and MYCOMPSTR are freed by the OS when the thread dies.


// Initializes the COMPOSITIONSTRING structure.
void InitCompStr(
    COMPOSITIONSTRING *pcompstr,           // In/Out: COMPOSITIONSTRING to be initialized
    DWORD dwSize
    )
{
    ASSERT(dwSize == sizeof(MYCOMPSTR));
    memset(pcompstr, 0, dwSize);

    pcompstr->dwSize = dwSize;
    pcompstr->dwCompStrOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->szCompStr - (LPBYTE)pcompstr;
    pcompstr->dwCompAttrOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->bCompAttr - (LPBYTE)pcompstr;
    pcompstr->dwResultStrOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->szResultStr - (LPBYTE)pcompstr;

#ifdef FULL_CONVERSION_INFO
    ASSERT(0); // Need to test
    pcompstr->dwCompReadAttrOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->bCompReadAttr - (LPBYTE)pcompstr;
    pcompstr->dwCompReadClauseOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->dwCompReadClause - (LPBYTE)pcompstr;
    pcompstr->dwCompReadStrOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->szCompReadStr - (LPBYTE)pcompstr;
    pcompstr->dwCompClauseOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->dwCompClause - (LPBYTE)pcompstr;
    pcompstr->dwResultClauseOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->dwResultClause - (LPBYTE)pcompstr;
    pcompstr->dwResultReadStrOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->szResultReadStr - (LPBYTE)pcompstr;
    pcompstr->dwResultReadClauseOffset = 
        (LPBYTE)((LPMYCOMPSTR)pcompstr)->dwResultReadClause - (LPBYTE)pcompstr;
#endif // FULL_CONVERSION_INFO

    ASSERT(ValidateInitedCompStr(pcompstr));
}

// Clear COMPOSITIONSTRING structure elements
void ClearCompStr(
    COMPOSITIONSTRING *pcompstr,   // Out: COMPOSITIONSTRING to be cleared
    DWORD dwFlags                  // In: Clear operation. Combination of CLR_COMP and CLR_RESULT
    )
{
    ASSERT(ValidateCompStr(pcompstr));

    if (dwFlags & CLR_COMP)
    {
        pcompstr->dwCursorPos = 0;
        pcompstr->dwDeltaStart = 0;
        pcompstr->dwCompStrLen = 0;
        pcompstr->dwCompAttrLen = 0;

#ifdef FULL_CONVERSION_INFO
        ASSERT(0); // Need to test
        pcompstr->dwCompReadStrLen = 0;
        pcompstr->dwCompReadAttrLen = 0;
        pcompstr->dwCompClauseLen = 0;
        pcompstr->dwCompReadClauseLen = 0;
#endif // FULL_CONVERSION_INFO
    }

    if (dwFlags & CLR_RESULT)
    {
        pcompstr->dwResultStrLen = 0;

#ifdef FULL_CONVERSION_INFO
        ASSERT(0); // Need to test
        pcompstr->dwResultClauseLen = 0;
        pcompstr->dwResultReadStrLen = 0;
        pcompstr->dwResultReadClauseLen = 0;
#endif // FULL_CONVERSION_INFO
    }
}

// Move composition string to result string
void MoveCompositionToResult(
    COMPOSITIONSTRING *pcompstr // COMPOSITIONSTRING 
)
{
    // COMPOSITIONSTRING must be initialized
    ASSERT(ValidateInitedCompStr(pcompstr));

    // Copy composition string to result sting. Clear composition string.
    _tcsncpy(GETLPRESULTSTR(pcompstr), GETLPCOMPSTR(pcompstr), pcompstr->dwCompStrLen);
    pcompstr->dwResultStrLen = pcompstr->dwCompStrLen;
    ClearCompStr(pcompstr, CLR_COMP);

#ifdef FULL_CONVERSION_INFO
    ASSERT(0); // Need to test
    // Move reading string
    lstrcpyn(GETLPRESULTREADSTR(pcompstr), GETLPCOMPREADSTR(pcompstr), pcompstr->dwCompReadStrLen);
    pcompstr->dwResultReadStrLen = pcompstr->dwCompReadStrLen;
    pcompstr->dwCompReadStrLen = 0;

    // Set clause information
    SETCLAUSE(GETLPRESULTCLAUSE(pcompstr), pcompstr->dwResultStrLen);
    SETCLAUSE(GETLPRESULTREADCLAUSE(pcompstr), pcompstr->dwResultReadStrLen);
    pcompstr->dwResultClauseLen = 8; 
    pcompstr->dwResultReadClauseLen = 8;
#endif // FULL_CONVERSION_INFO
}

// Does composition string exist?
BOOL HasComposition(
    const COMPOSITIONSTRING *pcompstr
    )
{
    ASSERT(ValidateCompStr(pcompstr));
    return (pcompstr->dwCompStrLen > 0);
}

// Is reading string at it's max size?
BOOL IsReadingFull(
    const COMPOSITIONSTRING *pcompstr
    )
{
    ASSERT(ValidateCompStr(pcompstr));

#ifndef FULL_CONVERSION_INFO
    // Composition string is equal to reading string here. But it some languages this may not
    // be true. Those languages will need full conversion info.
    return (pcompstr->dwCompStrLen >= MAXCOMPSIZE); 
#else
    return (pcompstr->dwCompReadStrLen >= MAXCOMPSIZE); 
#endif // FULL_CONVERSION_INFO
}

// Updates composition string.
// Called when the the contents of the composition string are changed.
VOID UpdateComposition(
    HIMC himc,          // In: Input Method Context
    LPTSTR pszCompNew,  // In: New composition string (May not be NULL terminated)
    int cchCompNew,     // In: Number of characters in new composition string
    TCHAR chRead        // In: Character to be added to reading string. 0 to add none.
    )
{
    UNREFERENCED_PARAMETER(chRead);

    LPINPUTCONTEXT pimc = NULL;
    LPCOMPOSITIONSTRING pcompstr = NULL;
    LPTSTR pszComp;

    pimc = ImmLockIMC(himc);
    if (pimc == NULL) 
        goto Error;

    pcompstr = (LPCOMPOSITIONSTRING)ImmLockIMCC(pimc->hCompStr);
    if (pcompstr == NULL)
        goto Error;
    
    // COMPOSITIONSTRING must be initialized
    ASSERT(ValidateInitedCompStr(pcompstr));

    // Set composition string
    int cchComp;
    pszComp = GETLPCOMPSTR(pcompstr);
    if (pszCompNew && cchCompNew <= MAXCOMPSIZE)
    {
        _tcsncpy(pszComp, pszCompNew, cchCompNew);
        cchComp = cchCompNew;
    }
    else 
    {
        cchComp = 0;
    }
    
    // Set length
    pcompstr->dwCompStrLen = cchComp;

    // Set cursor pos & start position of change in composition string.
    pcompstr->dwCursorPos = (DWORD)cchCompNew;
    if ( pcompstr->dwCursorPos > 0 )
        pcompstr->dwDeltaStart = pcompstr->dwCursorPos - 1;
    else
        pcompstr->dwDeltaStart = 0;

    memset(GETLPCOMPATTR(pcompstr), ATTR_TARGET_NOTCONVERTED, cchComp);
    pcompstr->dwCompAttrLen = cchComp;

#ifdef FULL_CONVERSION_INFO
    ASSERT(0); // Need to test
    // Add chRead to reading string.
    LPTSTR pszRead;
    pszRead = GETLPCOMPREADSTR(pcompstr);
    DWORD cchRead = pcompstr->dwCompReadStrLen;
    if (chRead && cchRead < MAXCOMPSIZE)
    {
        pszRead[cchRead++] = chRead;
    }

    memset(GETLPCOMPREADATTR(pcompstr),0, cchRead);

    // Set length
    pcompstr->dwCompReadStrLen = cchRead;
    pcompstr->dwCompReadAttrLen = cchRead;

    // Set clause info 
    SETCLAUSE(GETLPCOMPCLAUSE(pcompstr), cchComp);
    SETCLAUSE(GETLPCOMPREADCLAUSE(pcompstr), cchRead);
    pcompstr->dwCompClauseLen = 8;
    pcompstr->dwCompReadClauseLen = 8;
#endif // FULL_CONVERSION_INFO

Error:
    if (pcompstr)
        ImmUnlockIMCC(pimc->hCompStr);
    if (pimc)
        ImmUnlockIMC(himc);
    return;
}

// Determines whether the specified context has a composition string
// Returns TRUE, if composition string exists. FALSE otherwise.
BOOL HasComposition(
    HIMC himc       // In: Input Method Context.
    )
{
    LPINPUTCONTEXT pimc = NULL;
    LPCOMPOSITIONSTRING pcompstr = NULL;
    BOOL fRet = FALSE;

    pimc = ImmLockIMC(himc);
    if (!pimc)
        goto Error;

    pcompstr = (LPCOMPOSITIONSTRING)ImmLockIMCC(pimc->hCompStr);
    if (!pcompstr)
        goto Error;

    fRet = HasComposition(pcompstr);

Error:
    if (pcompstr)
        ImmUnlockIMCC(pimc->hCompStr);
    if (pimc)
        ImmUnlockIMC(himc);
    return fRet;
}

#ifdef DEBUG
// Check if an initialized COMPOSITIONSTRING is valid.
// The structure is initialized if we have resized it to 
// hold conversion info.
BOOL ValidateInitedCompStr(
    const COMPOSITIONSTRING *pcompstr
)
{
    ASSERT(pcompstr);

    return (pcompstr->dwSize == sizeof(MYCOMPSTR)
        && ValidateCompStr(pcompstr));
}

// Check if COMPOSITIONSTRING is valid. The COMPOSITIONSTRING can be
// initialized (rezsized to MYCOMPSTR) or not. It is validated in both
// cases.
BOOL ValidateCompStr(
    const COMPOSITIONSTRING *pcompstr 
)
{
    BOOL fRet = FALSE;
    BOOL fInited;

    ASSERT(pcompstr);

    // Is the size correct? The structure is uninitialized if
    // we haven't resized it to hold the conversion info.
    if (pcompstr->dwSize == sizeof(COMPOSITIONSTRING))
    {
        fInited = FALSE;
    }
    else if (pcompstr->dwSize == sizeof(MYCOMPSTR))
    {
        fInited = TRUE;
    }
    else
    {
        ASSERT(0);
        goto Error;
    }

#ifndef FULL_CONVERSION_INFO
    // The following should be 0 if full conversion info is not provided.
    if (pcompstr->dwCompReadAttrLen
        || pcompstr->dwCompReadAttrOffset
        || pcompstr->dwCompReadClauseLen
        || pcompstr->dwCompReadClauseOffset
        || pcompstr->dwCompReadStrLen
        || pcompstr->dwCompReadStrOffset
        || pcompstr->dwCompClauseLen
        || pcompstr->dwCompClauseOffset
        || pcompstr->dwResultReadClauseLen
        || pcompstr->dwResultReadClauseOffset
        || pcompstr->dwResultReadStrLen
        || pcompstr->dwResultReadStrOffset
        || pcompstr->dwResultClauseLen
        || pcompstr->dwResultClauseOffset  
        || pcompstr->dwPrivateSize
        || pcompstr->dwPrivateOffset
        )
    {
        ASSERT(0);
        goto Error;
    }     
#else
    ASSERT(0); // Validation of full conversion info not implemented.
#endif // FULL_CONVERSION_INFO

    if (fInited)
    {
        // Is the composition string data valid?
        if ((pcompstr->dwCompStrOffset != (DWORD)((LPBYTE)((LPMYCOMPSTR)pcompstr)->szCompStr - (LPBYTE)pcompstr))
            || (pcompstr->dwCompStrLen > (DWORD)sizeof(((LPMYCOMPSTR)pcompstr)->szCompStr))
            || (pcompstr->dwCursorPos && pcompstr->dwCursorPos > pcompstr->dwCompStrLen)
            || (pcompstr->dwDeltaStart && pcompstr->dwDeltaStart > pcompstr->dwCompStrLen))
        {
            ASSERT(0);
            goto Error;
        }
        // Is the result string data valid?
        if ((pcompstr->dwResultStrOffset != (DWORD)((LPBYTE)((LPMYCOMPSTR)pcompstr)->szResultStr - (LPBYTE)pcompstr))
            || (pcompstr->dwResultStrLen > (DWORD)sizeof(((LPMYCOMPSTR)pcompstr)->szResultStr)))
        {
            ASSERT(0);
            goto Error;
        }
    }
    else
    {
        // If uninitialized, composition and result string info should be 0.
        if (pcompstr->dwCompStrOffset
            || pcompstr->dwCompStrLen
            || pcompstr->dwCursorPos
            || pcompstr->dwDeltaStart
            || pcompstr->dwResultStrOffset
            || pcompstr->dwResultStrLen)
        {
            ASSERT(0);
            goto Error;
        }
    }

    fRet = TRUE;

Error:
    return fRet;
}
#endif // _DEBUG


