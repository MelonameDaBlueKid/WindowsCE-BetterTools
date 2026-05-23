Currency Converter Sample

This sample shows how to take an application written for the PocketPC platform and port it to the Smartphone platform.  Note that the UI of the Smartphone version is a straight forward port and would need additional refinements to improve usability.

PPCCur
	Workspace of the Pocket PC only version

SharedCur
	Workspace that shares the application engine and helpers but has different user interfaces for each platform.

SharedCur\PPCCur
	PocketPC user interface

SharedCur\SPCur
	Smartphone interface

diffs
	Contains a batch file which shows the main changes needed to get the application working on the Smartphone.