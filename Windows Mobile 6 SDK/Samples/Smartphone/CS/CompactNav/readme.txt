Code Sample Name: CompactNav

Feature Area: Managed Code, PInvoke

Description: 
	This sample demonstrates how to implement a basic .NETCF file-system navigator, 
	as well has how to use Platform Invoking (pInvoke) to make calls to 
	unmanaged APIs (in this case, CreateProcess). Some exception handling is shown, 
	as well as how to load images from the file system. Executable files may be 
	executed by selecting them (using the aforementioned pInvoke’d CreateProcess), 
	and directories may be entered by selecting them and hitting the action key. 
	Parent directories may be accessed using a menu item (UpDir) or by 
	selecting the conventional ".." directory. There is also a Quit option, which 
	is provided for testing convenience only, as this is not typical or 
	recommended for real Smartphone applications.

Usage: Build and Run

Relevant APIs/Associated Help Topics: PInvoke, Listviews, C#

Assumptions: none

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 
