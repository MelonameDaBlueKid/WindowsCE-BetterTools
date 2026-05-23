
This application is used to copy a file from the desktop to a connected CE device.
For example, if you want to copy a file from "c:\readme.txt" on the desktop to "\windows\readme.txt" 
on the CE device, just type "Pput c:\readme.txt \windows\readme.txt".



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


