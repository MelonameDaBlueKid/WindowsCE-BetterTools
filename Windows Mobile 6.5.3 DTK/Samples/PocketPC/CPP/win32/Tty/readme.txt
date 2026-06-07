Code Sample Name: TTY

Feature Area: Communications

Description: 
    This sample shows how to open, configure, and close a serial communications 
    port and perform read/write operations for a TTY terminal emulation 
    application.
     
Relevant APIs: 
    Serial communications
    
Usage:
    1. Load the project from Visual Studio 2005, and build and deploy normally.
    2. On the desktop, open a hyper-terminal, choose "Com1" or "Com2" and the 
       baud rate (For example, 9600). 
       If you connected the device with the desktop through serial connection by 
       using "com1", then choose "com2". Otherwise, choose "com1".
    3. Connect the device to the desktop through the chosen com port.
    4. On the device, run tty.
    5. Type letters on the hyper-terminal and you'll see they appear on the tty 
       app window (and vice versa).

Assumptions: 
    The device must have a COM port and it should be connected through the COM 
    port to the desktop.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **
