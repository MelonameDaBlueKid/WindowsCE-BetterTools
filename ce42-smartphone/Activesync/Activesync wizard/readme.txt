___________________________________________________________________

Readme for Microsoft® ActiveSync Service Provider Wizard
___________________________________________________________________

Note: This tool is unsupported by Microsoft, and is supplied 'as is'.

CONTENTS:
=========

 1.0 SYSTEM REQUIREMENTS
 2.0 WHAT'S IN THIS DIRECTORY
 3.0 INSTALLATION
 4.0 USING THE WIZARD
 5.0 REGISTERING YOUR SYNC SERVICE PROVIDER(SSP)
 6.0 USING THE SIMPLE FILE SYNC SAMPLE
 7.0 UNREGISTERING YOUR SSP

1.0 SYSTEM REQUIREMENTS:
========================

* Microsoft Windows® 95, Windows® 98, Windows NT® 4.00(x86), Windows® 2000, or Windows® XP
* Microsoft ActiveSync 2.2 or higher
* Microsoft Visual C++® 6.0
* Microsoft® eMbedded Visual C++ 4.0 *or* Microsoft Windows® CE Toolkit for Microsoft Visual C++® 6.0

2.0 WHAT'S IN THIS DIRECTORY:
=========================

This directory contains the following files,

Syncwiz.awx: Custom app wizard file used by Visual C++ to create the ActiveSync service provider project
Readme.txt: This file.

3.0 INSTALLATION:
===============

* Copy the file syncwiz.awx to your \Microsoft Visual Studio\Common\MSDev98\Template directory.

* The Pocket PC SDK 2003 already has the file cesync.h in the include directory. 
  For the older SDKs, you will need to copy the supplied ..\inc\cesync.h file, to the SDK include directory.
	\Windows CE Tools\Wce200\MS HPC\include
	\Windows CE Tools\Wce201\MS Palm Size PC\include

* You will also need the cabwiz.exe Application Installation program to register the device side dll - the AppInstall files can be found in the directory:
    ..\Windows CE Tools\Wce420\Pocket PC 2003\Tools\

4.0 USING THE WIZARD:
===================

Start Visual C++ and get to the New Project dialog. From the list, select "Microsoft ActiveSync Service Provider Wizard".
Enter a name for your project,  and hit OK. Step through the dialogs and change any settings as appropriate. Hit the "Finish" button when done.

The wizard will create a Win32 dll project for your desktop & a device side dll project targeting the MIPS/SH3 platforms for the Windows CE device and ARM platform for new devices.

Microsoft eMbedded Visual C++ Users:
========================================================

Start eMbedded Visual C++ and open the device side .dsp file that can be found in the <Project Directory>\Device directory using the "File->Open Workspace" menu. eMbedded Visual C++ will generate a new .vcp file using the supplied .dsp file.

DESKTOP PROJECT FILES:
=====================
The wizard will create the following files for your desktop project,

*  <ProjectName>Fctry.h / .cpp - Implementation of class Factory that creates your store objects.
*  <ProjectName>.h / .cpp - Contains the dll exports and declaration of the module class.
*  <ProjectName>Store.h / .cpp - Implementation of the IReplStore interface.
*  <ProjectName>objhand.h/ .cpp - Implementation of the IReplObjHandler interface.
*  <ProjectName>.def - Dll Export definitions.
*  <ProjectName>Fldr.h / .cpp - Implementation of the your Folder class.
*  <ProjectName>.rc - Contains the list of resources used by the project.
*  stdafx.h/ .cpp	 - contains standard system headers that will be used to build precompiled header(.pch).
*  replobjs.h - Contains declarations of the "cookie" objects that are stored in the repl.dat file.
*  resource.h - Contains listing of resource IDs used in the project.
*  Basefolder.h - Contains definition of the abstract CBaseFolder class.
*  res\<FolderName>.ico - Icon resource file for your folder object.

DEVICE PROJECT FILES:
====================
The wizard will create the following files for your device project(in the \Device directory),

*  Dev<ProjectName>.h / .cpp - Implementation of the IReplStore interface.
*  Dev<ProjectName>.dsp - Device side project file.
*  Dev<ProjectName>.def - Dll Export definitions.
*  Dev<ProjectName>objhand.h / .cpp - Implementation of the IReplObjHandler interface.
*  Dev<ProjectName>Fldr.h / .cpp - Implementation of your Folder class.
*  Basefolder.h - Contains definition of the abstract CBaseFolder class.
*  Dev<ProjectName>.ini - CE Application Manager initialization file.
*  Dev<ProjectName>.inf - Cabwizard setup file used to create the Dev<ProjectName>.cab file.
*  register.bat - Batch file for registering the device side provider dll.

5.0 REGISTERING YOUR SYNC SERVICE PROVIDER:
=========================================

Compiling the desktop side dll project will automatically register it on the desktop, using regsv32.exe in the custom build step.

To register the device side dll,

*  Copy the device dll file over to the device's root directory using the "Build->Update Remote Output File" menu in VC++/eVC or manually using the ActiveSync Mobile Devices Folder window. Note: VC++ may not copy your device dll to the device's root directory by default. If that is the case, you will have to manually move the file to the root directory.

*  Open the file register.bat from your \Device directory and enter the complete paths to the cabwiz.exe & CeAppMgr.exe files. If you have the Pocket PC SDK 2003 installed, the cabwiz.exe file can be found under \Windows CE Tools\Wce420\Pocket PC 2003\Tools\ directory. The ceappmgr.exe can be found in your Microsoft ActiveSync directory.

Run the register.bat file which will create all the required registry entries on the device. Your provider should now be successfully registered with ActiveSync. To complete the installation process, you will need to **disconnect & re-connect** your device.

Note: For more information on using the cabwizard & CE application manager, refer to the Visual C++ online documentation.

6.0 USING THE SIMPLE FILE SYNC SAMPLE:
===================================

The generated Simple File Sync sample provider is a simple file sync provider that will sync up a text file "c:\sample.txt" from your desktop to your device. The sample provider will have to be registered following the steps outlined in section 5.0 above. To test the sample provider, create the sample file on the desktop and put some text in it, wait for sync to complete. A sample file should be created on the device with the same name and should also have the same content. Make some changes to the desktop file and save the file - sync should automatically update the device file. Delete the desktop sample file,  and the device file should also get deleted. Try the same scenarios from the device.

7.0 UNREGISTERING YOUR SYNC SERVICE PROVIDER:
===========================================

*  Run regsvr32 -u <Desktop dll name>
*  Run CeAppMgr.exe, choose your provider from the list and remove.









	   




