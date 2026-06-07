Code Sample Name: SyncManager

Feature Area: Device ActiveSync 

Description: 
The App runs on a WinCE Device and displays the usage of the ActiveSync APIs, 
utilising ActiveSyncStart() and ActiveSyncStop() to launch and terminate sync sessions. 
It also displays the use of State and Notification APIs to register for changes 
to the two sync related Status Entries:
	- one that represents the Sync Status and
	- the other, representing the Cradle Status

Usage: Click to Launch the SyncManager
          Click MENU -> Start to launch sync session, Stop to terminate the session
          The Main Dialog shows Device Cradle and Sync Status.

Relevant APIs/Associated Help Topics: ActiveSyncStart, ActiveSyncStop, IsCradled, IsSynchronizing

Assumptions: None

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.

Comments:
You must compile this application with Visual Studio 2005 or newer.

1. Open the solution file in Visual Studio.
2. Point to "Platform", and select the platform you want to run this application on (Pocket PC, Smartphone, emulator, etc.).
3. Navigate to "Build", and click "ReBuild All" to compile the executable file.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
