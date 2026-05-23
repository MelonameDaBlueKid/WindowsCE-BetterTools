Application Name:   CEDBVIEW
Location:           wce300\MS Pocket PC\samples\win32\cedbview   

Abstract:

DBVIEW is a small Windows application that highlights the use of the built in
database functions:
    
·   PegCreateDatabase 
·   PegDeleteDatabase 
·   PegFindFirstDatabase 
·   PegFindNextDatabase 
·   PegOidGetInfo 
·   PegOpenDatabase 
·   PegReadRecordProps 
·   PegWriteRecordProps 
.   GetSystemMemoryDivision
.   GetStoreInformation
.   PegSetDatabaseInfo
.   PegSeekDatabase

DBVIEW uses a TreeView to show all available databases.  When the database node is 
selected, database information is displayed in the edit control to the right.  
By expanding the Database node, the available database properties are displayed.  
When a database property is selected the properties' information is also displayed 
in the edit control.

DBVIEW can create databases though the 'Object Store' menu.  The user must provide a name 
and database type (numeric value). The database is created with the database name specified 
as the user's name plus '_TEST' attached to the end.  This is to prevent databases not 
created with DBVIEW from being deleted.

DBVIEW only allows databases it creates to be deleted or modified. Only one database can 
be deleted at a time and only the currently selected database is deleted.

There are three icons on the tool bar.  The 'left arrow' will navigate to the previous 
record in the database, the 'right arrow' will navigate to the next record in the database, 
and the 'add record' icon can be used for adding records to the currently selected database.