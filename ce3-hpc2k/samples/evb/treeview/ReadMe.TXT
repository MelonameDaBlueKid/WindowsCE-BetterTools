TreeView ReadMe
===============
This is a single-form application that demonstrates the TreeView control and the ImageList control.  The Add and Remove events of the TreeView control are used in this sample.

In this sample, the explorer style pane on the right side of the form shows a tree with nodes.  You can double-click on a node to expand it or use the arrow keys to navigate in the TreeView pane and expand and close branches. The Edit button activates the selected node so that you can change the text.  The other eight buttons change the font style.  The text pane on the bottom right reports the events that take place within the application. 

The code is broken up into the following sections:
* Setup - This section initializes the nodes of the TreeView control and initializes the ImageList.  The primary nodes are set to appear expanded.
* Navigation - The subroutines in this section respond to the keyboard arrow keys.
* Formatting - The subroutines in this section respond to the text format buttons on the form.
* Editing - The subroutine in this section sets the current node's status to editable. 
* Events - The subroutines in this section trap node events and writes the event details to the 'EventText' text box.
 

To Install and Run the Sample
=============================
This sample runs without further modification.

Additional Notes
================
See further documentation on the ImageList control and the TreeView control in the Visual Basic for Windows CE online documentation.
