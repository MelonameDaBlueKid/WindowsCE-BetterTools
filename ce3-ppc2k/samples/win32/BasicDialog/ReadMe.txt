========================================================================
       WIN32 APPLICATION : BasicDialog
========================================================================

Name: BasicDialog
====

What is it: A dialog-based application.
==========

Features: 
========

Allows the developer to quickly build an application which has a large number of controls. 
For example a calculator. All you need to do is layout the controls you wish to use, 
using the dialog resource editor. Then response to the messages in the BasicDialogProc. 
This allows you to do quick application UI prototyping.

Demonstrates:
============

SHCreateMenuBar API and the SHInitDialog dialog API for the about box

Menu Custom Data:
================

/////////////////////////////////////////////////////////////////////////////
//
// Data
//

IDM_MAIN_MENU SHMENUBAR DISCARDABLE 
BEGIN
    IDM_MAIN_MENU, 1,
    I_IMAGENONE, IDM_MAIN_MENUITEM2, TBSTATE_ENABLED, 
    TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE, IDS_MAIN_MENUITEM2, 0, 0,
END


/////////////////////////////////////////////////////////////////////////////
//
// Menubar
//

IDM_MAIN_MENU MENU PRELOAD DISCARDABLE 
BEGIN
    POPUP "Help"
    BEGIN
        MENUITEM "About",                       IDM_HELP_ABOUT
    END
END

