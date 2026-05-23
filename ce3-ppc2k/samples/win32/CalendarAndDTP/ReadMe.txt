========================================================================
       WIN32 APPLICATION : CalendarAndDTP
========================================================================

Name: CalendarAndDTP
====

What is it: Calendar control and Date and Time Picker control
==========

Features: 
========

Shows how to use the Calendar and DTP controls 
This example demonstrates how to use these controls on top of dialogs 
It also demonstrates the use of custom formats in the DTP control and 
some of the styles of the calendar control 
Although I was too lazy to do so, you can create the second screen 
with scollbars and pan a full year

Note: To initialize the controls you must use the following for initialization.

	//Required in order to use the calendar and DTP controls
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(icex);
	icex.dwICC = ICC_DATE_CLASSES;


A sample showing some of the uses of the Calendar/DTP controls for the PsPC.

The controls are physically laid out on dialog boxes to make them easier to position and interact with at design time. They are the grey boxes on the dialog boxes, in the dialog editor. To set specific styles for these controls, just open the .rc file as text, find the correct control, and add/delete the style.

For example:

In the .rc file there will be a line such as...

    CONTROL         "",IDC_CONTROL_DTS_LONGDATEFORMAT,"SysDateTimePick32",
                    0x4,0,0,124,12


just add a new style next to the '0x4', such as '0x4 | DTM_STYLE'. It will be changed by the dialog compiler to the correct hex value, provided the <commctrl.h> file is included. It is included in the "resource.h" file in this example.



Menu Custom Data:
================

/////////////////////////////////////////////////////////////////////////////
//
// Data
//

IDM_MAIN_MENU RCDATA DISCARDABLE
BEGIN
  IDM_MAIN_MENU, 
  2,  
  I_IMAGENONE, IDM_MAIN_MENUITEM2, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM2, 0, 0, //First popup menu

  I_IMAGENONE, IDM_MAIN_MENUITEM3, TBSTATE_ENABLED,
  TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE,
  IDS_MAIN_MENUITEM3, 0, 1, //Next popup menu
END

*template

/*****************************************************************************

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

This is sample code and is freely distributable.

****************************************************************************/

