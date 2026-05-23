========================================================================
       WIN32 APPLICATION : Bezier
========================================================================

Name: Bezier
====


Demonstrates:
============

Provides replacement functions for PolyBezier, etc.

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
  3,

  
  I_IMAGENONE, IDM_MAIN_MENUITEM2, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM2, 0, 0, 
  I_IMAGENONE, IDM_QUICKTEST, TBSTATE_ENABLED,
  TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM3, 0, 1, 
  I_IMAGENONE, IDM_MAIN_MENUITEM4, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM4, 0, 2, 

END

