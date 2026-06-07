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
#include "stdafx.h"
#include "CrosswordSample.h"

//////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////////////

SHACTIVATEINFO      g_sai;
HINSTANCE           g_hInst;                // The current instance
HWND                g_hwndCB;               // The command bar handle
HFONT               g_hFont;
HDC                 g_hMemDC;               // The DC for the background bitmap.
HBITMAP             g_hMemBitmap;           // The background bitmap itself.
INT                 g_selectedHint;         // An index into the g_hints structure.
HIMAGELIST          g_hImageList;           // The image list for the ENTER button.
WCHAR               g_crossword[CROSSWORD_Y][CROSSWORD_X];    // The current state of the crossword.

const LPCWSTR g_crosswordSolution[] = 
{
    L"ABCD*FGHI*KLMN*",
    L"ABCD*FGHI*KL*N*",
    L"ABCD*FGHIJKLMN*",
    L"ABCDEF**IJ*LMN*",
    L"***DEFGH***LMN*",
    L"ABC***GHIJK****",
    L"ABC*EF**IJKLMN*",
    L"ABCDEFGHI*KLMN*",
    L"A*CD*FGHI*KLMN*",
    L"ABCD*FGHI*KLMN*",
    L"***************"
};

CROSSWORD_HINT g_hints[63] =
{
    // 
    // The rest of the CROSSWORD_HINT structure (x, y, cLetters, and fDown)
    //    for each hint listed here gets initialized in CreateCrossword().
    //
    {L"Pull along"},
    {L"Hair on animal's neck"},
    {L"Used to form a question"},
    {L"Stranger"},
    {L"Ligneous plant"},
    {L"Regret greatly"},
    {L"Greek letter"},
    {L"Putter's target"},
    {L"Show confidence at the poker table"},
    {L"Translucent apples"},
    {L"Takeoff artist"},
    {L"Get better"},
    {L"Center of marked success?"},
    {L"Ho chi minh trail locale"},
    {L"Brutus's breakfast?"},
    {L"Chesapeake Bay, for example"},
    {L"King Lear daughter"},
    {L"Sudden thrust"},
    {L"Data-sharing acronym"},
    {L"'Watership down' denizen"},
    {L"'American Pie' singer Don"},
    {L"Membership on Wall Street."},
    {L"Chill-inducing"},
    {L"Cube inventor Rubik"},
    {L"Soviet news agency"},
    {L"Walled city near Madrid"},
    {L"Poet Whitman"},
    {L"Acidulous"},
    {L"'Return of the Jedi' creature"},
    {L"Linear measure"},
    {L"Indigo source"},
    {L"Pacific, for one"},
    {L"Monopoly purchase"},
    {L"Aria for two"},
    {L"Lewis or Seinfeld"},
    {L"Get what's left"},
    {L"It's south of Seattle on Puget Sound"},
    {L"Social environment"},
    {L"Venerated structure or place"},
    {L"Imitate a chimp"},
    {L"Gulf in the Arabian Sea"},
    {L"Algonquian tribe of eastern Canada"},
    {L"Seabird fund's reported stir"},
    {L"Containing NaCl"},
    {L"Food on a hook"},
    {L"Graceful"},
    {L"Fail to win"},
    {L"Smallest"},
    {L"Toward shelter"},
    {L"Severe"},
    {L"Muscle contraction"},
    {L"School year"},
    {L"Liter"},
    {L"Whirlpool"},
    {L"Great fighter pilot"},
    {L"The outward flow of the tide"},
};
