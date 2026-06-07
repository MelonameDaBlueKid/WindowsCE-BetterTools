Code Sample Name: PoomMaster

Feature Area: PIM

Description: 
    This sample demonstrates the use of the POOM API. Via an owner-drawn 
    listview control, PoomMaster displays currently stored PIM items (Contacts, 
    Tasks, and calendar Appointments). There is also functionality to create 
    new items. For simplicity’s sake, only a few properties for each item are 
    shown, typically the subject and one two other essential values such as 
    a phone number for Contacts or a date and time for Appointments. 
    
    Functionally, the application has three modes of display accessible from the 
    Modes menu: Tasks, Contacts, or Appointments (labeled as Calendar in the 
    menu). New items corresponding to the current mode can be created from each 
    display using the "New" item from the "Options" menu. The "Options" menu 
    also contains a "Quit" item - this is merely here for the user’s convenience 
    and is not demonstrative of typical Pocket PC / Smartphone application 
    behavior.
    
    Other properties for ITask, IContact, and IAppointment are analogous to 
    those shown in the sample, and can be found in MSDN. 
    
    Source file listing and summary:
    
    PoomMaster.cpp - contains the entry point and the main dialog window proc, 
    as well as a number of utility functions

    PoomData.cpp - contains high-level POOM API calls for initialization, logon, 
    and retrieving POOM properties
    
    PoomContacts.cpp - contains routines which retrieve and set PIM Contact 
    items. Also contains the dialog proc for creating new Contacts.
        
    PoomTasks.cpp - contains routines which retrieve and set PIM Task items. 
    Also contains the dialog proc for creating new Tasks.
        
    PoomCalendar.cpp - contains routines which retrieve and set PIM Appointment 
    items. Also contains the dialog proc for creating new Appointments.
        
    PoomMaster.h - Function prototypes and global data
    
    PoomMaster.rc - resource script for dialogs and menus
    

Usage: 
    Load the project from Visual Studio 2005, and build and deploy normally.
 
Relevant APIs/Associated Help Topics:     
    Writing POOM applications
    POOM API
    IPOutlookApp
    IPOutlookCollection
    ITask
    IContact
    IAppointment
    Listview control
    Date-time control

Assumptions: none.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **

