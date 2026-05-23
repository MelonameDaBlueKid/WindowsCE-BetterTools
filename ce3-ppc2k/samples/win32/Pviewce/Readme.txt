========================================================================
       WIN32 APPLICATION : PViewCE
========================================================================

Name: PViewCE
====

What is it:  
==========

An on device process viewer for WindowsCE (same as PView for Windows95)

Demonstrates:
============

Many functions in toolhelp.dll, which must be present on the device.


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

  I_IMAGENONE, IDM_MAIN_MENUITEM3, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM3, 0, 2, //Next popup menu

	0, ID_PROCESS_REFRESH, TBSTATE_ENABLED,
  TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE,
  0, 0, 3, //Next popup menu

  1, ID_PROCESS_KILL, TBSTATE_ENABLED,
  TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE,
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
