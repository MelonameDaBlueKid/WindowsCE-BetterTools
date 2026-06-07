===================================================================
                           MICROSOFT (R) ACTIVESYNC SDK
===================================================================

This directory contains the components necessary to build applications
using the Microsoft ActiveSync SDK.  This document specifically addresses
issues related to building these components with Microsoft Visual Studio 2005.  

The folder includes all the necessary header and library files for building
custom applications, along with the following:

    A sample Stock Portfolio application.
    A debugging and monitoring tool for SSPs


You may copy the entire contents of this folder to any location you like and 
the device-side components of the sample application should build without problems.


==================================================
 I.  BUILDING THE STOCKPOR DEVICE-SIDE COMPONENTS
==================================================

Launch Microsoft Visual Studio 2005 and open the workspace file:

     ".\ACTIVESYNC STOCK PORTFOLIO SAMPLE\Stockpor\StockPor.sln"



==================================================
 II.  AppManager
==================================================

To find documentation on how to use the Desktop ActiveSync AppManager to install 
applications from the desktop to a Windows Mobile-based device, please consult the 
Windows Mobile SDK or the AppInst sample that can be found in the samples folder.