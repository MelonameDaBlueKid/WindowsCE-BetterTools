========================================================================
       WIN32 APPLICATION : shell	
========================================================================

Name: shell
====


Demonstrates:
============

Demonstrates a Rapier alternative to the General shell sample for Wyvern.
It also shows how to use bitmaps on the menubar.
Remember that the each button bitmap on the strip of bitmaps must be 16 x 16 
pixels. 

Note: The red dots on the menubar bitmap are markers to show where the 16x16 
grid is. They should be removed in any shipping applications

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
  5

  I_IMAGENONE, IDM_MAIN_MENUITEM1, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM1, 0, 0, //First popup menu

  I_IMAGENONE, IDM_MAIN_MENUITEM2, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM2, 0, 1, //Next popup menu

  //Use the first bitmap 
  0, IDM_FILENEW, TBSTATE_ENABLED,
  TBSTYLE_BUTTON ,
  0, 0, 2, //Next popup menu

  //Use the second bitmap 
  1, IDM_FILEOPEN, TBSTATE_ENABLED,
  TBSTYLE_BUTTON ,
  0, 0, 3, //Next popup menu

  //Use the third bitmap 
  2, IDM_FILESAVE, TBSTATE_ENABLED,
  TBSTYLE_BUTTON ,
  0, 0, 4, //Next popup menu

END




*template

/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

****************************************************************************/
