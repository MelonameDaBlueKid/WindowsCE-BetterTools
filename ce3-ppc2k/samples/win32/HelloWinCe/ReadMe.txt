========================================================================
       WIN32 APPLICATION : HelloWinCE
========================================================================

Name: HelloWinCE
====


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
  1, //2

  
  //I_IMAGENONE, IDM_MAIN_MENUITEM1, TBSTATE_ENABLED,
  //TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  //IDS_MAIN_MENUITEM1, 0, 0, //First popup menu

  I_IMAGENONE, IDM_MAIN_MENUITEM2, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM2, 0, 0, //1, //Next popup menu

END

*template




