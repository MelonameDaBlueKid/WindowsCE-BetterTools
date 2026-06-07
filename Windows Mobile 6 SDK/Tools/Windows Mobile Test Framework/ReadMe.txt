This file offers a brief overview of the contents of the Windows Mobile Test Framework.

Installation:

Unzip the contents of the zip file to the location where you plan to build your tests.  
The Test Framework command window will use this directory as the root of your workspace.

Contents of Framework:

Tools:
	Desktop:
		AreaGen		Generates source code for a named Area Library skeleton.
		CeCopy		Copies files between a device and the desktop using Active Sync.
		CeStrip		Extracts resource strings from Windows Mobile DLLs.
		RapiStart	Executes device command lines from the desktop using Active Sync.
		RCToCS		Generates UIAL managed source code from RCML markup.
		SetupDevice	Script which sets up a connected Windows Mobile device to use the test framework.
		UIALAppGen	Generates the main application class template for a UIAL.
		
	Device:
		GenFinder	Generates source code for a Microsoft.WindowsCE.Datk.WindowFinder at runtime.
		RCMLSnap	Generates RCML markup from an actual Windows Mobile device UI at runtime.
		Tux.Net		The test harness which executes the actual test cases.
		WceLoad		A runtime cab file loader for Windows Mobile devices.

Directory Structure
	Common 		Hosts Tux.Net deployment project and sample projects.
	Bin		Desktop binaries and support files.
	DeviceFiles 	A collection of a recent release of all MDPG QA binaries and support files.
	Documentation	Html and CHM documentation of the framework, along with Readme, Tutorial, and Tux.Net documentation.
	TuxNetSkeleton	A skeleton solution for tux.net test assemblies.
	CalViewSample	A sample test DLL that uses a sample UIAL and Area Library.
	SamplePlugin	A sample Tux.Net plugin project.

Usage Notes
	The main help file WMTF.chm is located in the Documentation directory.
	It contains detailed documentation on all of the tools and APIs included with the framework.
	It also contains a step-by-step tutorial on creating the CalView sample test libraries and cases.
