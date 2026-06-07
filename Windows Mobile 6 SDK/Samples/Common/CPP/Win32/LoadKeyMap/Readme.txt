//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//


Code Sample Name: 
    LoadKeyMap

Feature Area: 
    SmartFilter

Description: 
    The app allows the user to update the active keyboard mappings on the device.

Usage: 
    Launch application then type one of the following options:
    1 to restore the device's default keyboard mappings
    2 to load an empty set of keyboard mappings (use for unambiguous keyboards)
    3 to load a sample 12-key mapping
        where an input of 2 matches abc, 3 matches def, and so forth
    4 to load a sample 15-key mapping
        where an input of e matches 1r, t matches 2y, and so forth
    5 to load a sample 30-key mapping
        where an input of w matches 1, e matches 2, and so forth
    6 to load a custom Mapping.txt
        where Mapping.txt must be present in the release directory or in \ on the device.
        The syntax for Mapping.txt is as follows:
            <chFilter1>:<chMatch1_1>,<chMatch1_2>,...
            <chFilter2>:<chMatch2_1>,<chMatch2_2>,...
            ...
                where <chFilter*> is the hex code for a character that might appear in a filter string
                and <chMatch*_#> is the hex code for a character that should match <chFilter*>.
                The first matching character for each key mapping, e.g. <chMatch*_1> is also the character
                that will be displayed in SmartDial's No Matches Text when the filter string matches nothing.
                See documentation for the LoadKeyMap API for more details.

Relevant APIs/Associated Help Topics: 
    SmartFilter

Important:
    The resulting binary must be signed to work on Smartphones.

Notes: 
    In order to show what this sample can do, you should have some contacts created and emails on the device.
    Filter your contacts in SmartDial or the Contacts applications by typing letters and/or numbers.
    Filter your emails by typing letters and/or numbers.
    Run the program using the enumerations in USAGE2 and try filtering your contacts and emails to see how
    different keyboard mappings affect matching results.
    Create your own keyboard mappings using USAGE1 and try filtering your contacts and emails.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK or
    Windows Mobile 5.0 Smartphone SDK,
    ActiveSync 4.0.
    


** For more information about this code sample, please see the Windows Mobile SDK help system. **
