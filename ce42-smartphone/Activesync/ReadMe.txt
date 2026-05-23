===================================================================
                           MICROSOFT (R) ACTIVESYNC SDK
===================================================================

This directory contains the components necessary to build applications
using the Microsoft ActiveSync SDK.  This document specifically addresses
issues related to building these components with Microsoft eMbedded Visual
C++.  

The folder includes all the necessary header and library files for building
custom applications, along with the following:

    A sample Stock Portfolio application.
    An ActiveSync Service Provider Wizard.
    A debugging and monitoring tool for SSPs
    A WinCE sample cab application that can register with AcitveSync



You may copy the entire contents of this folder to any location you like and the device-side components of the sample application should build without problems.


==================================================
 I.  BUILDING THE STOCKPOR DEVICE-SIDE COMPONENTS
==================================================

1.  Launch eMbedded Visual C++ 4.0 and open the workspace file:

     ".\ACTIVESYNC STOCK PORTFOLIO SAMPLE\Stockpor\StockPor.vcw"

2.  Press {F7} to build.


==================================================
 II.  USING THE SSP WIZARD
==================================================

This is supported on Visual C++ 6 only.

See the readme file located in the "ACTIVESYNC WIZARD" directory for instructions
on using the wizard.

The readme for the wizard is located at:

    ".\ACTIVESYNC WIZARD\readme.txt"
