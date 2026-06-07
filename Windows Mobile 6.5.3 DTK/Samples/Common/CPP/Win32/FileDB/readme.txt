Code Sample Name: FileDB

Feature Area: EDB

Description: 
    This sample demonstrates how an application that used CEDB can been ported 
    to use EDB. Using #ifdef EDB both the CEDB and EDB versions are shown in the 
    sample. If you would like to build for CEDB just remove the #define EDB 
    at the top of the FileDB.cpp file. 

    This sample is very simple; it creates a database with 3 rows and populates 
    it with the names, size and time of the files in a directory. The database 
    is then closed and opened sorted by date, time and size respectively. 
    The results are shown in Visual Studio 2005 debug output window.

Usage: 
    Load the project from Visual Studio 2005, and build and deploy normally.

Relevant APIs/Associated Help Topics:     
    EDB/CEDB
    CeOidGetInfoEx2
    CeMountDBVol
    CeCreateDatabaseWithProps
    CeCreateSession
    CeOpenDatabaseInSession
    CeSeekDatabaseEx
    
    
Assumptions: none.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK
    Activesync 4.5.


** For more information about this code sample, please see the Windows Mobile 
SDK help system. **
