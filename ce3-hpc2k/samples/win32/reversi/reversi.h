//***************************************************************************
//
// Filename : reversi.h
//	
// Copyright (c) 1997 Microsoft Corporation. All rights reserved
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//***************************************************************************

#define BoardSize           100
#define edge                0
#define empty               1
#define human               2
#define computer            3
#define infin               32767
#define win                 32000
#define loss                (-32000)
#define max_depth           6

#define PASS                20
#define NEW                 25
#define BSkill              40
#define EASY                41
#define MEDIUM              42
#define HARD                44
#define VHARD               46
#define HINT                50
#define EXIT                52

#define MenuGame            1
#define MenuSkill           2

/* Menu ID's */

#define MN_HELP_INDEX       30
#define MN_HELP_KEYBOARD    31
#define MN_HELP_COMMANDS    32
#define MN_HELP_PLAYING     33
#define MN_HELP_RULES       34
#define MN_HELP_USINGHELP   35
#define MN_HELP_ABOUT       36
