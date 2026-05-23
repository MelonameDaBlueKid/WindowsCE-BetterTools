// ***************************************************************************
// GAME.H
//
// Main Game Function Definitions for the Stinger Minesweeper port
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#pragma once

#ifndef _GAME_H_
#define _GAME_H_

// some constants to help define the fixed-size board array
#define MAX_BOARDSIZE		12
#define ARRAY_WIDTH			(MAX_BOARDSIZE+2)

// invalid board positions are functionally equivalent to uncovered blocks
#define INVALID_ENTRY		STATE_UNCOVERED

// array access macros
#define BLOCK(x, y)			(g_gd.cBoard[x+1][y+1])
#define BLOCKSTATE(x, y)	(BLOCK(x, y) & STATE_MASK)
#define BLOCKTYPE(x, y)		(BLOCK(x, y) & TYPE_MASK)
#define SETBLOCK(x, y, val)	(BLOCK(x, y) = val)
#define SETSTATE(x, y, val) (BLOCK(x, y) = BLOCKTYPE(x, y) | val)

// state constants
#define STATE_MASK			0x30
#define STATE_COVERED		0x00
#define STATE_MARKED		0x10
#define STATE_QUESTION		0x20
#define STATE_UNCOVERED		0x30

// blocktype constants
#define TYPE_MASK			0x0F
#define TYPE_MINE			0x0F
#define TYPE_BLANK			0x00

// sounds!!!
#define	SOUND_WIN			TEXT("miniwin.wav")
#define SOUND_BOMB			TEXT("bigexpl.wav")

// function definitions
BOOL InitGame(HWND hwnd);
BOOL InitGameData();
void NewGame();
BOOL StartGame();
BOOL ResumeGame(HWND hwnd);
void EndGame();
BOOL MakeMove(int ix, int iy);
BOOL MakeMark();
void StopTimer();
void UpdateTimer();
void UpdateMines();
BOOL UncoverNeighbors();
BOOL LoadScores();
BOOL IsMine(int ix, int iy);
BOOL IsWinner();
BOOL IsHighScore();
BOOL myPlaySound(LPCTSTR lpszSoundName, UINT fuSound);

#endif	// _GAME_H_