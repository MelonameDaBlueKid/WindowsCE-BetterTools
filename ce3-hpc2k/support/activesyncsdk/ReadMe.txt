===================================================================
                           MICROSOFT (R) ACTIVESYNC SDK
===================================================================

This directory contains the components necessary to build applications
using the Microsoft ActiveSync SDK.  This document specifically addresses
issues related to building these components with Microsoft eMbedded Visual
C++.  

For general ActiveSync SDK documentation see:

     ".\ACTIVESYNC PROGRAMMER'S GUIDE\ActiveSync Programmer's Guide.doc"


The folder includes all the necessary header and library files for building
custom applications, along with the following:

    A sample Stock Portfolio application.
    An ActiveSync Service Provider Wizard.


The sample program has both desktop and device components, but

     THE DESKTOP COMPONENTS WILL NOT BUILD UNDER EMBEDDED VISUAL C++.

You must have a version of desktop Visual C++ in order to build the desktop applications.

You may copy the entire contents of this folder to any location you like and the device-side components of the sample application should build without problems.


==================================================
 I.  BUILDING THE STOCKPOR DEVICE-SIDE COMPONENTS
==================================================

1.  Launch eMbedded Visual C++ and open the workspace file:

     ".\ACTIVESYNC STOCK PORTFOLIO SAMPLE\Stockpor\StockPor.dsw"


    eMbedded Visual C++ will need to create .vsw and .vcp files for the .dsw and .dsp
    files in the workspace.

    You will not be able to open the desktop-side projects.

    The workspace will open with only the three device-side projects loaded.


2.  Press {F7} to build.


==================================================
 II.  USING THE SSP WIZARD
==================================================

See the readme file located in the "ACTIVESYNC WIZARD" directory for instructions
on using the wizard.

The readme for the wizard is located at:

    ".\ACTIVESYNC WIZARD\readme.txt"
