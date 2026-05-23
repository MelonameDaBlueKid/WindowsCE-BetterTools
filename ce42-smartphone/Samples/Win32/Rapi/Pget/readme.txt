
This application is used to copy a file from a CE device to the desktop it connected to.
For example, if you want to copy a file from "\windows\cmd.exe" on the CE device to
"c:\cmd.exe" on the desktop, just type "Pget \windows\cmd.exe c:\cmd.exe".


This is the desktop side application. You need Visual Studio .Net 2003 and eMbedded Visual C++ 4.0 
to compile it.

1. Open the project file by using Visual Studio .Net 2003 (Not by eMbedded Visual C++ 4.0).

2. Go to "Tools" -> "Options", select Projects | VC++ Directories 

3. Choose "Include files" for "Show directories for:" listbox.

4. Add a directory.  If you accepted the defaults when 
   installing eMbedded Visual Tools, then the new directory will be
   "C:\Program Files\Windows CE Tools\wce420\POCKET PC 2003\Activesync\Inc".

5. Choose "Library files" for "Show directories for:" listbox.

6. Add a directory. If you accepted the defaults when 
   installing eMbedded Visual Tools, then the new directory will be
   "C:\Program Files\Windows CE Tools\wce420\POCKET PC 2003\Activesync\Lib".

7. Go to "Build" -> "ReBuild All" to compile the executable file.


