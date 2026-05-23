// ***************************************************************************
// GAME.CPP
//
// Main Game Functionality for the Stinger Minesweeper port
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include "winmine.h"

BOOL LoadScores()
{
	// temporary buffer to hold name of regkey
	TCHAR szTemp[10];

	for (int i = 0; i < 3; i++) 
    {
		_sntprintf(szTemp, ARRAY_LENGTH(szTemp), TEXT("%s%d"), REGISTRY_VALUE_HIGHTIME, i);
		if (FALSE == GetRegDWORD(szTemp, &g_hsScores[i].dwTime))
        {
			return FALSE;
		}
		
		// try to get the name from the registry
		_sntprintf(szTemp, ARRAY_LENGTH(szTemp), TEXT("%s%d"), REGISTRY_VALUE_HIGHNAME, i);
		if (FALSE == GetRegString(szTemp, &g_hsScores[i].szName))
        {
			return FALSE;
		}

		// if the time is invalid, then set the name to the default
		if (0 == g_hsScores[i].dwTime) 
        {
			g_hsScores[i].dwTime = 999;
			g_hsScores[i].szName = _tcsdup(TEXT("Anonymous"));
		}
	}

	return TRUE;
}

void NewGame()
{
	// set the game status
	g_gd.gsStatus = NEWGAME;

	// clear out the game board
	for (int i = 0; i < ARRAY_WIDTH; i++) 
    {
		for (int j = 0; j < ARRAY_WIDTH; j++) 
        {
			g_gd.cBoard[i][j] = INVALID_ENTRY;
		}
	}

	// reset the cursor
	g_iCurX = 0;
	g_iCurY = 0;

	// Calculate the offsets for the board
	g_iOffX = (g_iWindowWidth - (g_iDefaults[g_gd.gtType][INDEX_XBLOCKS] * IMAGE_SIZE)) / 2;
	g_iOffY = ((g_iWindowHeight - LABEL_HEIGHT) - (g_iDefaults[g_gd.gtType][INDEX_YBLOCKS] * IMAGE_SIZE)) / 2;

	// Calculate a bounding rectangle for the board + a 1 pixel border
	g_rcBoard.left = g_iOffX - 1;
	g_rcBoard.right = g_rcBoard.left + (g_iDefaults[g_gd.gtType][INDEX_XBLOCKS] * IMAGE_SIZE) + 2;
	g_rcBoard.top = g_iOffY - 1;
	g_rcBoard.bottom = g_rcBoard.top + (g_iDefaults[g_gd.gtType][INDEX_YBLOCKS] * IMAGE_SIZE) + 2;

	// set the block & flag counters
	g_gd.iBlocksLeft = g_iDefaults[g_gd.gtType][INDEX_XBLOCKS] * g_iDefaults[g_gd.gtType][INDEX_YBLOCKS];
	g_gd.iFlagsLeft = g_iDefaults[g_gd.gtType][INDEX_MINES];

	// Stop the timer if it was running, and reset it
	StopTimer();
	g_gd.dwCurTime = 0;
	UpdateTimer();

	// Update the mine count
	UpdateMines();

	// Update the menu (not always necessary, but more efficient to be here)
	UpdateMenus();

	// redraw the screen
	InvalidateRect(g_hwndMain, NULL, TRUE);
}

BOOL ResumeGame(
    HWND hwnd
    )
{
	// in the unlikely case that the user has changed executables between games
	// the code to calculate board position has been replicated here
	
	// Calculate the offsets for the board
	g_iOffX = (g_iWindowWidth - (g_iDefaults[g_gd.gtType][INDEX_XBLOCKS] * IMAGE_SIZE)) / 2;
	g_iOffY = ((g_iWindowHeight - LABEL_HEIGHT) - (g_iDefaults[g_gd.gtType][INDEX_YBLOCKS] * IMAGE_SIZE)) / 2;

	// Calculate a bounding rectangle for the board + a 1 pixel border
	g_rcBoard.left = g_iOffX - 1;
	g_rcBoard.right = g_rcBoard.left + (g_iDefaults[g_gd.gtType][INDEX_XBLOCKS] * IMAGE_SIZE) + 2;
	g_rcBoard.top = g_iOffY - 1;
	g_rcBoard.bottom = g_rcBoard.top + (g_iDefaults[g_gd.gtType][INDEX_YBLOCKS] * IMAGE_SIZE) + 2;

	// create a timer
	if (!(g_uiTimerID = SetTimer(hwnd, IDR_WINMINE_TIMER, 1000, NULL)))
    {
		return FALSE;
	}

	// update the display
	UpdateMines();
	UpdateTimer();
	UpdateMenus();
	
	return TRUE;
}

BOOL StartGame()
{
	int iMinesLeft;
	int x, y;
	char cType;

	// generate the mines
	iMinesLeft = g_iDefaults[g_gd.gtType][INDEX_MINES];
	do 
    {
		do
        {
			x = rand() % g_iDefaults[g_gd.gtType][INDEX_XBLOCKS];
			y = rand() % g_iDefaults[g_gd.gtType][INDEX_XBLOCKS];
		} while (IsMine(x, y) || ((x == g_iCurX) && (y == g_iCurY)));
		SETBLOCK(x, y, STATE_COVERED | TYPE_MINE);
	} while(--iMinesLeft);

	// precompute the values
	for (y = 0; y < g_iDefaults[g_gd.gtType][INDEX_YBLOCKS]; y++)
    {
		for (x = 0; x < g_iDefaults[g_gd.gtType][INDEX_XBLOCKS]; x++) 
        {
			// set all the remaining blocks
			if (!IsMine(x,y))
            {
				cType = 0;
				if (IsMine(x-1, y-1)) ++cType;
				if (IsMine(x-1, y)) ++cType;
				if (IsMine(x-1, y+1)) ++cType;
				if (IsMine(x, y-1)) ++cType;
				if (IsMine(x, y+1)) ++cType;
				if (IsMine(x+1, y-1)) ++cType;
				if (IsMine(x+1, y)) ++cType;
				if (IsMine(x+1, y+1)) ++cType;
				SETBLOCK(x, y, STATE_COVERED | cType);
			}
		}
	}
	
	// update the game status
	g_gd.gsStatus = PLAYING;

	// start the timer
    g_uiTimerID = SetTimer(g_hwndMain, IDR_WINMINE_TIMER, 1000, NULL);
	if (0 == g_uiTimerID)
    {
		return FALSE;
	}
	g_gd.dwCurTime = 0;

	return TRUE;
}

BOOL MakeMove(int ix, int iy)
{
	BOOL bRetVal = TRUE;

	// making a move depends on the game status
	switch (g_gd.gsStatus) {
		case NEWGAME:
			// this should be handled outside of this function - return false
			return FALSE;

		case PLAYING:
			// check the state of the block that has been selected
			switch (BLOCKSTATE(ix, iy)) {
				case STATE_COVERED:
				case STATE_QUESTION:
					// in both these cases we uncover the block
					SETSTATE(ix, iy, STATE_UNCOVERED);
					--g_gd.iBlocksLeft;
					
					// check the block type
					switch (BLOCKTYPE(ix, iy)) 
                    {
						case TYPE_BLANK:
							// recurse in all directions, keeping track of any false values
							if (!MakeMove(ix-1, iy-1)) bRetVal = FALSE;
							if (!MakeMove(ix-1, iy)) bRetVal = FALSE;
							if (!MakeMove(ix-1, iy+1)) bRetVal = FALSE;
							if (!MakeMove(ix, iy-1)) bRetVal = FALSE;
							if (!MakeMove(ix, iy+1)) bRetVal = FALSE;
							if (!MakeMove(ix+1, iy-1)) bRetVal = FALSE;
							if (!MakeMove(ix+1, iy)) bRetVal = FALSE;
							if (!MakeMove(ix+1, iy+1)) bRetVal = FALSE;
							break;

						case TYPE_MINE:
							// uh oh, hit a mine - return false
							bRetVal = FALSE;
							break;

						default:
							// hit a numbered square, just return
							break;
					}
					break;

				case STATE_MARKED:
				case STATE_UNCOVERED:
					// do nothing
					break;
			}
			break;
		
		case GAMEOVER:
			// do nothing
			break;
	}

	return bRetVal;
}

BOOL MakeMark()
{
	// the flag operation depends on the current status of the game/block
	switch (g_gd.gsStatus)
    {
		case NEWGAME:
			// this should be handled outside of this function - return false
			return FALSE;

		case PLAYING:
			// check the state of the block that has been selected
			switch (BLOCKSTATE(g_iCurX, g_iCurY)) {
				case STATE_COVERED:
					SETSTATE(g_iCurX, g_iCurY, STATE_MARKED);
					--g_gd.iBlocksLeft;
					--g_gd.iFlagsLeft;
					break;

				case STATE_QUESTION:
					SETSTATE(g_iCurX, g_iCurY, STATE_COVERED);
					break;
					
				case STATE_MARKED:
					SETSTATE(g_iCurX, g_iCurY, STATE_QUESTION);
					++g_gd.iBlocksLeft;
					++g_gd.iFlagsLeft;
					break;
					
				case STATE_UNCOVERED:
					// do nothing
					break;
			}
			break;
		
		case GAMEOVER:
			// do nothing
			break;
	}

	UpdateMines();

	return TRUE;
}

BOOL UncoverNeighbors()
{
	int iBlockVal, iNumBombs = 0;
	BOOL bRetVal = TRUE;

	// this can only be done on an uncovered number
	if (STATE_UNCOVERED != BLOCKSTATE(g_iCurX, g_iCurY)) 
    {
		return TRUE;
	}

	// this can also only be done on a numbered square
	if (!(iBlockVal = BLOCKTYPE(g_iCurX, g_iCurY))) 
    {
		return TRUE;
	}

	// sanity check
	if (TYPE_MINE == iBlockVal) 
    {
		return FALSE;
	}

	// check the number of marked bombs
	if (BLOCKSTATE(g_iCurX-1, g_iCurY-1) == STATE_MARKED) ++iNumBombs;
	if (BLOCKSTATE(g_iCurX-1, g_iCurY) == STATE_MARKED) ++iNumBombs;
	if (BLOCKSTATE(g_iCurX-1, g_iCurY+1) == STATE_MARKED) ++iNumBombs;
	if (BLOCKSTATE(g_iCurX, g_iCurY-1) == STATE_MARKED) ++iNumBombs;
	if (BLOCKSTATE(g_iCurX, g_iCurY+1) == STATE_MARKED) ++iNumBombs;
	if (BLOCKSTATE(g_iCurX+1, g_iCurY-1) == STATE_MARKED) ++iNumBombs;
	if (BLOCKSTATE(g_iCurX+1, g_iCurY) == STATE_MARKED) ++iNumBombs;
	if (BLOCKSTATE(g_iCurX+1, g_iCurY+1) == STATE_MARKED) ++iNumBombs;

	// if iNumBombs != iBlockVal, ignore command
	if (iBlockVal != iNumBombs) 
    {
		return TRUE;
	}

	// recurse
	if (!MakeMove(g_iCurX-1, g_iCurY-1)) bRetVal = FALSE;
	if (!MakeMove(g_iCurX-1, g_iCurY)) bRetVal = FALSE;
	if (!MakeMove(g_iCurX-1, g_iCurY+1)) bRetVal = FALSE;
	if (!MakeMove(g_iCurX, g_iCurY-1)) bRetVal = FALSE;
	if (!MakeMove(g_iCurX, g_iCurY+1)) bRetVal = FALSE;
	if (!MakeMove(g_iCurX+1, g_iCurY-1)) bRetVal = FALSE;
	if (!MakeMove(g_iCurX+1, g_iCurY)) bRetVal = FALSE;
	if (!MakeMove(g_iCurX+1, g_iCurY+1)) bRetVal = FALSE;
	
	return bRetVal;
}

BOOL InitGame(HWND hwnd)
{
	DWORD dwDisposition;
	int iResult;

	// draw the controls
	if (!AddControls(hwnd)) 
    {
	    RETAILMSG(1, (TEXT("InitGame: unable to draw the controls\n")));
		return FALSE;
	}

	// get all the handles
	if (!GetHandles(hwnd)) 
    {
	    RETAILMSG(1, (TEXT("InitGame: unable to get all the handles\n")));
		return FALSE;
	}

	// open the registry key
	if (!InitRegistry(&dwDisposition)) 
    {
	    RETAILMSG(1, (TEXT("InitGame: unable to open the registry key\n")));
		return FALSE;
	}
	
	// load the high scores
	if (!LoadScores()) 
    {
	    RETAILMSG(1, (TEXT("InitGame: unable to load the high scores\n")));
		return FALSE;
	}

	// initialize the GameData structure
	if (!InitGameData()) 
    {
	    RETAILMSG(1, (TEXT("InitGame: unable to initialize the GameData structure\n")));
		return FALSE;
	}

	// seed the random number generator and start a new game
	srand(GetTickCount());

	// depending on the gamedata, start or resume
	if (PLAYING == g_gd.gsStatus) 
    {
		// try to resume the game
		iResult = MessageBox(hwnd, UseString(IDS_WINMINE_RESUME), 
            g_tszTitle, MB_YESNO | MB_ICONQUESTION);
		if (IDYES == iResult) {
			if (FALSE == ResumeGame(hwnd)) 
            {
				return FALSE;
			}
		} 
        else
        {
			NewGame();
		}
	} 
    else 
    {
		NewGame();
	}

	return TRUE;
}

BOOL InitGameData()
{
	// if there is no game in the registry, set g_gd to the defaults
	if (!GetRegBinary(REGISTRY_VALUE_GAMEDATA, (PBYTE) &g_gd, sizeof(GameData)))
    {
		// default settings
		g_gd.dwCurTime = 0;
		g_gd.gsStatus = NEWGAME;
		g_gd.gtType = BEGINNER;
		g_gd.dwKeyMakeMark = DEFAULT_KEY_MAKEMARK;
		g_gd.dwKeyMakeMove = DEFAULT_KEY_MAKEMOVE;
		g_gd.dwKeyUncover = DEFAULT_KEY_UNCOVER;
		g_gd.bSounds = TRUE;
	}

	return TRUE;
}

void EndGame()
{
	g_gd.gsStatus = GAMEOVER;
	StopTimer();
	UpdateMenus();
}

void StopTimer()
{
	if (g_uiTimerID) 
    {
		if (FALSE == KillTimer(g_hwndMain, IDR_WINMINE_TIMER)) 
        {
			MessageBox(g_hwndMain, UseString(IDS_WINMINE_BADTIMER), 
                UseString(IDS_WINMINE_ERROR), MB_OK | MB_ICONERROR);
		}
		g_uiTimerID = 0;
	}
}

void UpdateTimer()
{
	TCHAR tszCurTime[5];

	_sntprintf(tszCurTime, ARRAY_LENGTH(tszCurTime), TEXT("%d"), g_gd.dwCurTime);
	SendMessage(g_hwndTimer, WM_SETTEXT, 0, (LPARAM) tszCurTime);
}

void UpdateMines()
{
	TCHAR tszMinesLeft[4];

	_sntprintf(tszMinesLeft, ARRAY_LENGTH(tszMinesLeft), TEXT("%d"), g_gd.iFlagsLeft);
	SendMessage(g_hwndMines, WM_SETTEXT, 0, (LPARAM) tszMinesLeft);
}

BOOL IsMine(
    int ix, 
    int iy
    )
{
	return (TYPE_MINE == BLOCKTYPE(ix, iy));
}

BOOL IsWinner()
{
	return ((PLAYING == g_gd.gsStatus) && (0 == g_gd.iBlocksLeft) && (0 == g_gd.iFlagsLeft));
}

BOOL IsHighScore()
{
	return (g_gd.dwCurTime < g_hsScores[g_gd.gtType].dwTime);
}

BOOL myPlaySound(
    LPCTSTR lpctszSoundName, 
    UINT uiSound
    )
{
	if (g_gd.bSounds)
    {
		return sndPlaySound(lpctszSoundName, uiSound);
	} 
    else 
    {
		return TRUE;
	}
}
