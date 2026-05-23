VBCEComm ReadMe
===============
This sample is a communications application that demonstrates the use of the Comm control, including opening and closing a communications port and sending and receiving data. 

Press the COMM Start button to initiate a communications link.  This will open a Connection Settings dialog that will allow you to specify the communication settings.  The COMM End button will terminate the link.  The Send Text button will send the text entered into the Write Text field. Incoming text is displayed in the Read Text field. Error messages are reported in the Error text box. The fields on the right side of the interface report the status of the connection. 

To Install and Run the Sample
=============================
This sample runs without further modification.

To allow the Comm control to access the com port on the desktop when running on the emulator choose the custom install option and confirm that the DDK gets installed during the SDK setup. After rebooting, go into the control panel and select devices.  In the devices dialog, stop the serial device and start the wceemuld device.

Additional Notes
================
Because the sample uses the same serial port for communications as it does a serial connection the mobile device must be disconnected after launching the application.  

This sample was tested on a remote device with both the VBTerm Visual Basic sample running on the desktop and the VBCEComm sample running in emulation. The VBTerm.exe application is included in the sample folder.

For information on the Comm control, see the Visual Basic for Windows CE online documentation.
