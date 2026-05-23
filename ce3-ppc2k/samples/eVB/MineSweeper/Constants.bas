Attribute VB_Name = "Constants"
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
'ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
'THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'PARTICULAR PURPOSE.

'Copyright  2000  Microsoft Corporation.  All Rights Reserved

Option Explicit

Public Const MAX_SIZE = 14
Public Const MAX_MINE = 30
Public Const MAX_TIME = 999

Public Const GAME_INPLAY = 0
Public Const GAME_LOSE = 1
Public Const GAME_WIN = 2
Public Const GAME_PAUSE = 2

Public Const BAD_MARKED = 2
Public Const EXPOSED = 1
Public Const UNEXPOSED = 0

Public Const MARKED = -1
Public Const FLAGED = -2

Public Const MINE = -1
Public Const BLANK = 0

Public Const RIGHT_BUTTON = 0
Public Const LEFT_BUTTON = 1

'All bit map files
Public Const EXPOSED_MINE_BITMAP = "B"
Public Const MINE_BITMAP = "B"
Public Const BAD_MINE_BITMAP = "F"

Public Const EMPTY_BITMAP = ""
Public Const ONE_BITMAP = "1"
Public Const TWO_BITMAP = "2"
Public Const THREE_BITMAP = "3"
Public Const FOUR_BITMAP = "4"
Public Const FIVE_BITMAP = "5"
Public Const SIX_BITMAP = "6"
Public Const SEVEN_BITMAP = "7"
Public Const EIGHT_BITMAP = "8"

Public Const FLAG_BITMAP = "X"
Public Const MARK_BITMAP = "?"

Public Const UNEXPOSED_BITMAP = &H0
Public Const BLANK_BITMAP = &HC0C0C0

'File constants
Public Const BESTRECORD_TXT = "BestRecord.txt"
Public Const CLOCK1_BMP = "Clock1.bmp"
Public Const CLOCK2_BMP = "Clock2.bmp"
Public Const CLOCK3_BMP = "Clock3.bmp"
Public Const CLOCK4_BMP = "Clock4.bmp"
Public Const FLAG_BMP = "Flag.bmp"
Public Const SADLYFACE_BMP = "SadlyFace.bmp"
Public Const SMILEYFACE_BMP = "SmileyFace.bmp"
Public Const WORRIEDFACE1_BMP = "WorriedFace1.bmp"
Public Const WORRIEDFACE2_BMP = "WorriedFace2.bmp"

'Color constants
Public Const ORANGE = &H80FF&
