========================================================================
       WIN32 APPLICATION : keytest22
========================================================================

Name: keytest22
====

What is it: Displays the message sent to the system, along with the the wParam 
            and the lParam for each keystroke made with the Stylus.
==========

Features: 
========

You need to select (Show\WM_XXXXX) the WM_XXXXX messages that you want to track
and view.


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
  IDS_MAIN_MENUITEM1, 0, 0, //First popup menu

END


*template


