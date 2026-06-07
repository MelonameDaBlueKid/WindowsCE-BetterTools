Code Sample Name: CalendarAndDTP

Feature Area: Shell

Description: 

    This sample shows how to use the Calendar and DTP controls. It demonstrates 
    the use of custom formats in the Date Time Picker (DTP) control and some of 
    the styles of the calendar control. You can create the second screen with 
    scollbars and pan a full year.

    The controls are physically laid out on dialog boxes to make them easier to 
    position and interact with at design time. They are the grey boxes on the 
    dialog boxes, in the dialog editor. To set specific styles for these 
    controls, just open the .rc file as text, find the correct control, 
    and add/delete the style.

    For example:

    In the .rc file there will be a line such as...

    CONTROL         "",IDC_CONTROL_DTS_LONGDATEFORMAT,"SysDateTimePick32",
                    0x4,0,0,124,12


    just add a new style next to the '0x4', such as '0x4 | DTM_STYLE'. It will 
    be changed by the dialog compiler to the correct hex value, provided 
    the <commctrl.h> file is included. It is included in the "resource.h" file 
    in this example.

    Note:
    To initialize the controls you must use the following for initialization:
        //Required in order to use the calendar and DTP controls
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(icex);
        icex.dwICC = ICC_DATE_CLASSES;

Relevant APIs: 
    Calendar and Date Time Picker controls.

Usage:

   Load the project from Visual Studio 2005, and build and deploy normally.

Assumptions: 
    None.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK
    ActiveSync 4.0.

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
