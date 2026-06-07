Code Sample Name: SocketApp

Feature Area: RAPI

Description: 
	SocClient is a Win32 Desktop component that demontrates the use of
	sockets to communicate with a Windows Mobile device. At first hand,
	the application uses IRAPI interfaces to get the IP of the 
	Windows Mobile connected through ActiveSync.  In a second step,
	it sends a hello string and listen for the device to repond
	back.

Usage: 
	First, connect a windows Mobile Device and Start SocketSRV.exe on the device.  Then
	run, SocClient.exe from the desktop.

Relevant APIs/Associated Help Topics: 
	iRAPIDesktop, EnumDevices, IRAPIDevice, IRAPIDevice::GetConnectionInfo

Assumptions: 
	This project file assumes that Visual Studio default Headers and Libraries search path
	have been updated properly.  The Windows Mobile 6 SDK will install ActiveSync
	libraries and header files to the following default locations:
	c:\Program Files\Windows Mobile 6 SDK\Activesync\Lib
        c:\Program Files\Windows Mobile 6 SDK\Activesync\inc

Requirements: 
   Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.
