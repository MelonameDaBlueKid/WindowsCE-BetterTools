// ***************************************************************************
// WINMINE.H
//
// Contains various definitions and declarations for Minesweeper
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#pragma once

#include "resource.h"
#include "dialog.h"
#include "game.h"
#include "graphics.h"
#include "registry.h"

#ifndef _WINMINE_H_
#define _WINMINE_H_

// useful macros
#define ARRAY_LENGTH(x)	(sizeof(x)/sizeof((x)[0]))

// game defaults array index
#define INDEX_MINES			0
#define INDEX_XBLOCKS		1
#define INDEX_YBLOCKS		2

// action keys
#define DEFAULT_KEY_MAKEMOVE		0x0D
#define DEFAULT_KEY_MAKEMARK		0x31
#define DEFAULT_KEY_UNCOVER			0x32
#define ASCII_NUMBER_OFFSET			0x30

// gamestate
enum GameState {
	NEWGAME,
	PLAYING,
	GAMEOVER
};

// gametype
enum GameType {
	BEGINNER,
	INTERMEDIATE,
	EXPERT
};

// high score record
typedef struct _HighScores {
	LPTSTR	szName;
	DWORD	dwTime;
} HighScores;

// game-specific data
typedef struct _GameData {
	GameState	gsStatus;
	GameType	gtType;
	DWORD		dwCurTime;
	int			iBlocksLeft;
	int			iFlagsLeft;
	BYTE		cBoard[ARRAY_WIDTH][ARRAY_WIDTH];
	DWORD		dwKeyMakeMove;
	DWORD		dwKeyMakeMark;
	DWORD		dwKeyUncover;
	BOOL		bSounds;
} GameData;

// struct to help find the last active window
typedef struct _LASTACTIVEWINDOW 
{
    HWND   hwndLastActive;      // Out: Thread's last active window
    DWORD  dwMainWindowThread;  // In: Thread of main window
} LASTACTIVEWINDOW;


// global variables
extern HINSTANCE	g_hInst;
extern TCHAR		g_tszTitle[80];
extern TCHAR		g_tszAppName[80];
extern HWND			g_hwndMain;
extern HWND			g_hwndTimer;
extern HWND			g_hwndMines;
extern HWND			g_hwndMB;
extern HPEN			g_hpenBorder;
extern HPEN			g_hpenSelection;
extern HDC			g_hdcImage;
extern HBITMAP		g_hbmpBlocks;
extern int			g_iDefaults[3][3];
extern HighScores	g_hsScores[3];
extern int			g_iCurX;
extern int			g_iCurY;
extern int			g_iOffX;
extern int			g_iOffY;
extern int			g_iWindowWidth;
extern int			g_iWindowHeight;
extern RECT			g_rcBoard;
extern UINT			g_uiTimerID;
extern HKEY			g_hkWinMine;
extern GameData		g_gd;

// function definitions for main.cpp
BOOL InitInstance(
    int iShow
    );
BOOL InitApplication();
BOOL InitMenu(
    HWND hwnd, 
    UINT nToolBarId
    );
LRESULT CALLBACK MainWndProc(
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam
    );
BOOL HandleActionKeys(
    WPARAM wParam
    );
LPCTSTR UseString(
    UINT uID
    );
void CleanUp();
BOOL SaveSettings();
void UpdateMenus();
HWND GetLastActiveAppWindow(
    HWND hwndMain
    );
BOOL CALLBACK GetLastActiveAppWindowEnum(
    HWND hwnd,
    LPARAM lParam
    );

#endif // _WINMINE_H_
