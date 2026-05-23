========================================================================
       WIN32 APPLICATION : ShowFontInfo
========================================================================

Name: ShowFontInfo
====

Features: 
========

Shows how to enumerate fonts on a device.

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
  1

  
  I_IMAGENONE, IDM_MAIN_MENUITEM1, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM1, 0, 1, //First popup menu

END

*template

/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

****************************************************************************/
