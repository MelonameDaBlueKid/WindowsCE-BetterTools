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
//***************************************************************************
//
// Filename : reversi.h
//    
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

#define IDM_MAIN_MENUITEM1              401
#define IDM_MAIN_MENUITEM2              402
#define IDM_MAIN_MENUITEM3              403
#define IDS_MAIN_MENUITEM1              410
#define IDS_MAIN_MENUITEM2              411
#define IDS_MAIN_MENUITEM3              412
#define IDM_MAIN_MENU                   450
