Code Sample Name: Battery Status Sample

Feature Area: State and Notifications Broker

Description: 
    This sample demonstrates how to use the State and Notification Broker APIs.  More specifically, it
    demonstrates:
    - use of Window Message Notifications - RegistryNotifyWindow
    - use of Window Callback Notifications - RegistryNotifyCallback
    - use of Persistent Notifications - RegistryNotifyApp
    - use of the Main Battery and Backup Battery Strength and State notifications
    - how to apply bitmasks when registering the notifications 
    - how to extract and interpret the changed values using the proper bitmasks
    - how to include or exclude command line information in the Persistent Notifications
    - how to form the proper application path in a Persistent Notification  (ie  inserting quotes around the path)
    - how to unregister Message Notifications
    - how to unregister Callback Notifications
    - how to unregister Persistent Notifications
    
    The program is designed to show the user the current status of their main and backup battery.  
    Whenever a battery notification event is received, the battery status information will be updated
    in the display.
    
    The notification can be made persistent by selecting the "Persist" command from the menu.  Then, when
    a battery notification is sent, BattStat will be launched and display the updated status.

Usage:
    Load the project from Visual Studio 2005, and build and deploy normally.

Relevant APIs/Associated Help Topics: 
    RegistryGetDWORD
    RegistryNotifyWindow
    RegistryNotifyCallback
    RegistryNotifyApp
    WM_SETTINGCHANGE
    WM_CHANGE_BATTSTRENGTH
    WM_CHANGE_BATTSTATE
    WM_CHANGE_BACKUPSTRENGTH
    WM_CHANGE_BACKUPSTATE
    SN_POWERBATTERYSTRENGTH_ROOT
    SN_POWERBATTERYSTRENGTH_PATH
    SN_POWERBATTERYSTRENGTH_VALUE
    SN_POWERBATTERYSTRENGTH_BITMASK
    SN_POWERBATTERYSTATE_ROOT
    SN_POWERBATTERYSTATE_PATH
    SN_POWERBATTERYSTATE_VALUE
    SN_POWERBATTERYSTATE_BITMASK
    SN_POWERBATTERYBACKUPSTRENGTH_ROOT
    SN_POWERBATTERYBACKUPSTRENGTH_PATH
    SN_POWERBATTERYBACKUPSTRENGTH_VALUE
    SN_POWERBATTERYBACKUPSTRENGTH_BITMASK
    SN_POWERBATTERYBACKUPSTATE_ROOT
    SN_POWERBATTERYBACKUPSTATE_PATH 
    SN_POWERBATTERYBACKUPSTATE_VALUE
    SN_POWERBATTERYBACKUPSTATE_BITMASK

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
