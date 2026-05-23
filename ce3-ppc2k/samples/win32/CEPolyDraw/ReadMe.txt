========================================================================
       WIN32 APPLICATION : PolyDrawCE
========================================================================

Name: PolyDrawCE
====

What is it: replacement for the PolyDraw routines
==========


Menu Custom Data:
================

/////////////////////////////////////////////////////////////////////////////
//
// Data
//

IDM_MAIN_MENU RCDATA DISCARDABLE
BEGIN
  //Popup menu name
  IDM_MAIN_MENU, 
  //Count of items to put on the menu (er... toolbar)
  3

  I_IMAGENONE, IDM_MAIN_MENUITEM2, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM2, 0, 0, //Next popup menu

  I_IMAGENONE, IDM_MAIN_MENUITEM3, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM3, 0, 1, //Next popup menu

  I_IMAGENONE, IDM_MAIN_MENUITEM4, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM4, 0, 2, //Next popup menu

END

*template

/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

****************************************************************************/
