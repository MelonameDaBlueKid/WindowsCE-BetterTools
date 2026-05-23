PURPOSE
========
Demonstration part of Pocket PC functionality.

SUMMARY
=========
This sample application illustrates part of the functionality of Pocket PC. It creates a window and draws a horizontal line to create two equal quadrants. WndProc processes the mouseclicks depending on which quadrant the mouse was in when it was clicked.

This example resembles to the "Generic" example of the WIN32_WCE. Instead of four quadrants, this application only has two quadrants because of the following Pocket PC applications properties:

	1) There shouldn't be an exit control for Pocket PC applications.
	2) The application windows should not be minimized.

Top quadrant: 	Cycles through the color palette.
Bottom quadrant:	Draws squares the size of 1/6 the window width with  the upper-left corner at the point of mouseclick.


