========================================================================
       WIN32 APPLICATION : ComCtls
========================================================================

Name: ComCtls
====

What is it: Shows the new visual appearance of controls.
==========


Menu Custom Data:
================

/////////////////////////////////////////////////////////////////////////////
//
// Data
//
IDM_MAIN_MENU RCDATA DISCARDABLE
BEGIN
  IDM_MAIN_MENU, 1,

  I_IMAGENONE, IDM_MAIN_MENUITEM2, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE ,
  IDS_MAIN_MENUITEM2, 0, 0, //Next popup menu
END




*template