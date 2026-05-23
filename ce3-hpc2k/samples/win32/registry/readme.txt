Application Name: 	REGISTRY
Location:		WINDOWS CE TOOLS\WCE211\MS HPC PRO\SAMPLES\WIN32\REGISTRY

Abstract:

Registry is a simple utility which demonstrates
the Registry API functions needed to access the HPCPRO registry.
Registry can be used to climb up and down the various branches
of the Registry tree, displaying the individual key's data
values.

To use: start an instance of Registry.  A dialog box will
appear with several edit fields, list boxes and buttons.
The listbox in the center of the dialog will always hold the
child keys of the current key.  Initially it has four entries,
representing the four pre-defined key handles of the Registry:
HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER, HKEY_USERS, and
HKEY_CLASSES_ROOT.  If you double click on any of these
entries, or select it and press the "Next/Down" button;
the key that you just selected will appear in the edit field
"Key", and the children of that selected key will
replace the entries in the center list box.  I.e. if you
select HKEY_LOCAL_MACHINE, that name will be present in "Key",
and it's children will appear in the list box:
HARDWARE, Software, and SYSTEM (just to name a few).  To proceed 
deeper into the tree, double click another child.  To back 
out of the Registry, double click on the ".." at the top of the
listbox, or press the "Back/Up" button.

If the current key has values associated with it, the name
of the values will be listed in the right hand listbox 
labeled "VALUES:").  If it does not have values, "VALUES:" will
be followed by a "0".  Once you come upon a key that does
have values associated with it, you can double click on any
of the values in this list box.  At the bottom of the dialog
box are two edit fields: "Type", and "Entry".  By double 
clicking a value entry, these edit fields will be filled in 
with the data's type and the data's value.  I.e. if you follow 
the tree down to HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\TOUCH; 
and double click on the entry "1) DriverName", the "Type"
field will be filled with "REG_SZ: A null-terminated Unicode
string"; and the "Value: Data Entry" may be filled in with
something such as "touch.dll"

If the current key has a Class type associated with it, it
will appear in the "Class" edit field.
