Sample: CEInvoke   

Summary:
=======
This sample illustrates the use of the CEInvoke API in different ways. 
This sample can be compiled for Windows CE 2.0 or later, but not for Windows CE 1.0 or 1.01.
This sample is not supported for emulation.

Server:
=======
Has the device side code. Builds a DLL, CeInvoke.Dll which will be used by 
the actual call to CeInvoke by RAPI.
Note: CeInvoke.dll must exist in the windows folder on the device. DevStudio will
always download it if Project > Settings > Debug tab > General category 
> Remote executable path and file name: is set to windows\ceinvoke.dll


Client:
======
This is the desktop side code. You need Visual C++ 6.0 and eMbedded Visual C++ to compile it.
1. Open the project file (DSP file) by using Visual C++ 6.0 (Not by eMbedded Visual C++ 3.0,
   because eMbedded Visual C++ 3.0 doesn't support x86).
2. Go to "Tools" -> "Options", press "Directories" tab.
3. Choose "Include files" for "Show directories for:" listbox.
4. Add a directory "CEStudioRootDir\EVC\include", if you installed Microsoft eMbedded Tools under
   "C:\Program Files\Microsoft eMbedded Tools" then the new directory will be 
   "C:\Program Files\Microsoft eMbedded Tools\EVC\include"
5. Choose "Library files" for "Show directories for:" listbox.
6. Add a directory "CEStudioRootDir\EVC\lib", if you installed CEStudio under
   "C:\Program Files\Microsoft eMbedded Tools" then the new directory will be 
   "C:\Program Files\Microsoft eMbedded Tools\EVC\lib"
7. Go to "Build" -> "ReBuild All" to compile the executable file, CeInvoke.exe.

Has the desktop side code. It is a Windows app without any UI. Builds an exe
called CeInvoke.exe. The results are displayed in a simple Message Box.
You can run the exe from the command line with one of the following or 
any other parameters:

Command Line Param  Tests           Expected Result
------------------  -----           ---------------

No param            Simple Block    Will return an error code
StoreInfo           Simple Block    Will return the store info on the device
S1                  Simple Stream   Will return some text specifying Stream Mode 1
S2                  Multiple Stream Will return a list of all databases on the device.

You can also run the exe from within DevStudio (by altering the Project > Settings
> Debug tab > General category > Program Arguments).



