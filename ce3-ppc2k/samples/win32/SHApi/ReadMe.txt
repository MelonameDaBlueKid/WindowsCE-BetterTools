========================================================================
       WIN32 APPLICATION : SHApi
========================================================================

Name: SHApi
====

What is it: Demonstrates some of the new shell API's
==========

Features: 
========

Shows how to show/hide taskbars, menubars, and SIP buttons. 
Also shows how to use SHInitDialog for full screen dialogs.

Not demonstrated yet
*// SHHandleWMActivate and SHHandleWMSettingChange fun
*// New menu notifications
*// SHSipPreference
*// SHRecognizeGesture 

Menu Custom Data:
================

/////////////////////////////////////////////////////////////////////////////
//
// Data
//

IDM_MAIN_MENU RCDATA DISCARDABLE
BEGIN
  IDM_MAIN_MENU, 1,
  I_IMAGENONE, IDM_MAIN_SHAPI, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_SHAPI, 0, 0,
END



*template


/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

****************************************************************************/
