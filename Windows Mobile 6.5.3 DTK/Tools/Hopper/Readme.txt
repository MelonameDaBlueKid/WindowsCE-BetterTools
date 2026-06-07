Hopper
======

Summary

    This document provides how-to information for ISV’s to run the Hopper test tool more 
    effectively. The intended audience for this document is Windows Mobile OEMs and ISVs
    trying to use Hopper to create more robust and stable devices.


Introduction

    Hopper is a software test tool that simulates input stress on Windows Mobile based 
    devices. Hopper will stress all applications made available through the menu system 
    by rapidly sending keystrokes and screen taps in a random fashion. By sending a large
    number of user inputs very rapidly, Hopper can quickly isolate troublesome scenarios
    and find bugs in your applications. 

    Hopper for ISV’s is just like Hopper for OEM’s, the only difference being the addition
    of a "focus app" customized to keep the intended application in the foreground. ISV’s
    are generally not concerned with other applications installed on the device, so 
    keeping Hopper focused on your application is critical. When your application is in 
    the foreground, Hopper will test only it and not the rest of the system. The "focus 
    app" is needed to bring your application back to foreground if Hopper tries to 
    navigate away. 

    It is very important to begin Hopper testing early in your development cycle - 
    application defects found early in the development cycle are easier to fix and 
    provide a stable base to build the rest of your application. Sometimes, bugs found by
    Hopper are very difficult to find and fix, but their value should not be 
    underestimated: Hopper is good. Hopper will help you find system and application 
    scenarios you may not have thought of. 

    The power of Hopper lies in its ability to very rapidly send random inputs to the 
    system. This ability is also what makes Hopper debugging challenging since it is 
    often difficult to find simple user reproductions. 


The focus application

    The tool needed to keep Hopper focused on your application, FocusApp, will actually
     need to be finished by you and deployed to the device before running Hopper. The 
    included sample is based on keeping Media Player in the foreground - since you won’t 
    be testing Media Player, you will need to customize this code to keep your 
    application as the foreground window. The intent of this application is to keep 
    focus on your app and reduce the amount of "wandering" that Hopper does. Hopper was 
    actually designed to test the entire system so don’t be surprised if you see Hopper 
    off in other applications.

    You are free to compile the sample and run it with Hopper to see how Media Player is
     stressed, again - its just code. By including the source to this tool, we have 
    enabled the ISV’s to customize the tool as needed. You will definitely need to change
     the g_pszAppName to represent the name of your application, but please feel free to
     customize to suit your needs. Have two or even three executables you want tested at
     the same time? No problem, just change the focus app to switch between the 
    application names. Want a more exclusive Hopper run (where Hopper never leaves your 
    application)? No problem, just reduce the SLEEP_TIMEOUT variable to bring up your 
    application more often.

    Again, the creation and customization of the focusApp.exe is left to the ISV.


How to run Hopper

    Hopper is a single executable file that will need to be copied from the 
    <sdk_root>\tools\Hopper directory to the root folder of your device. Please also 
    copy your customized focusApp.exe binary to the device.

    1. Launch file explorer on the device
    2. Navigate to the root folder
    3. Launch your focusApp.exe first
    4. Dismiss your app or BACK key to file explorer
    5. Launch Hopper

    That is all that is required, give Hopper a few seconds to begin clicking and soon 
    your application will come back into focus. There will be a Hopper.log written 
    under \testlog that represents a periodic system snapshot and may provide useful 
    in debugging.


Additional Resources

    A blogsite dedicated to solving Hopper problems can be found at: 
    http://blogs.msdn.com/hoppeRx/. 
