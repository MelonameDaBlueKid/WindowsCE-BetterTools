Database Viewer ReadMe
=======================

This sample lets you view the structure of any Pocket Access Database (.cdb) down to the 
field properties level. It demonstrates the use of the CommonDialog control (displaying the Open
Common Dialog box), the ImageList control,
and the TreeView Control.

At startup, the explorer-style pane in the main part of the form shows a tree
with a single node ("Empty").  To load a database to view:

1. Enter the database name in the text box.
2. Tap the Load button.

-- OR --

1. Tap the Browse button (...) to invoke the Open Common Dialog box.
2. Navigate to the database you wish to view.
3. Double-tap the name of the database to open.

The database structure will then display in the TreeView.  The database name will appear alone, as
the top-level of the tree.  Tap the icon to the left of the database name to reveal the list of
tables. To reveal the field names and proprties, tap the plus sign (+) next to the table or field 
name, respectively.


Additional Notes
=================
This sample will run on the emulator.

You must have a database loaded on the device or in the same directory as the emulator so 
there is something for the application to find.  If no data is available, the TreeView will display
a tree with a single node, which reads "Empty."

For more information on the controls used in this sample, see the eMbedded Visual Basic online
documentaion.