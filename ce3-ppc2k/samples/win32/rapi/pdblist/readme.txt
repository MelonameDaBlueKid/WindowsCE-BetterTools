
To list the database of all types, type "Pdblist" or "Pdblist 0".
To list the database of one type, take "24" for example, type "Pdblist 24".


This is the desktop side application. You need Visual C++ 6.0 and eMbedded Visual C++ 3.0 
to compile it.

1. Open the project file (DSP file) by using Visual C++ 6.0 (Not by eMbedded Visual C++ 3.0, because 
   eMbedded Visual C++ 3.0 doesn't support x86).

2. Go to "Tools" -> "Options", press "Directories" tab.

3. Choose "Include files" for "Show directories for:" listbox.

4. Add a directory "wce300\MS Pocket PC\support\ActiveSync\inc". If you accepted the defaults when 
   installing eMbedded Visual Tools, then the new directory will be
   "C:\Windows CE Tools\wce300\MS Pocket PC\support\ActiveSync\inc".

5. Choose "Library files" for "Show directories for:" listbox.

6. Add a directory "wce300\MS Pocket PC\support\ActiveSync\lib". If you accepted the defaults when 
   installing eMbedded Visual Tools, then the new directory will be
   "C:\Windows CE Tools\wce300\MS Pocket PC\support\ActiveSync\lib".

7. Go to "Build" -> "ReBuild All" to compile the executable file.
