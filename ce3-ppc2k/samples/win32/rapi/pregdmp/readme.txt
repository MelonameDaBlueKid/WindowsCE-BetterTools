
This application is used to get a list of the registries of a CE device from the desktop it is
connected to.



This is the desktop side application. You need Visual C++ 6.0 and Microsoft eMbedded Visual C++ 3.0
to compile it.

1. Open the project file (DSP file) by using Visual C++ 6.0 (Not by Microsoft eMbedded Visual C++ 3.0, 
   because Microsoft eMbedded Visual C++ 3.0 doesn't support x86).

2. Go to "Tools" -> "Options", press "Directories" tab.

3. Choose "Include files" for "Show directories for:" listbox.

4. Add a directory "wce300\MS Pocket PC\support\ActiveSync\inc".  If you accepted the defaults when 
   installing eMbedded Visual Tools, then the new directory will be
   "C:\Windows CE Tools\wce300\MS Pocket PC\support\ActiveSync\inc".

5. Choose "Library files" for "Show directories for:" listbox.

6. Add a directory "wce300\MS Pocket PC\support\ActiveSync\lib".  If you accepted the defaults when 
   installing eMbedded Visual Tools, then the new directory will be
   "C:\Windows CE Tools\wce300\MS Pocket PC\support\ActiveSync\lib".

7. Go to "Build" -> "ReBuild All" to compile the executable file.

