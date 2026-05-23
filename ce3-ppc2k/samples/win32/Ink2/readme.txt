========================================================================
       WIN32 APPLICATION : ink2
========================================================================

Name: ink2
====

Features: 
========

Shows how to stream rtf, txt into and out of a richink control.
This uses the richink control. To use the inkX control look at the 
ink3 sample.

Note: Passing an rtf file with no text content in it will eventually cause an exception
in the richink control. 

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

*#define SF_PWI          ( SF_RTF | SFF_PWI | 0x010000 ) // Pocket Word Ink (PWI) format
*template

/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

****************************************************************************/
