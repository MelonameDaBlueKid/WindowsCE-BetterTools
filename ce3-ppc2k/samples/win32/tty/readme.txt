Description:

This Windows CE application shows how to open, configure, and close a
serial communications port and perform read/write operations for a TTY
terminal emulation application.

Note:

This sample application is not designed for emulation.


Steps for running tty sample application:

1. Compile and download tty.exe to the device. 
2. On the desktop, open a hyper-terminal, choose "Com1" or "Com2" and the baud rate (For example, 9600). 
   If you connected the device with the desktop through seriel connection by using "com1", then choose
   "com2". Otherwise, choose "com1".
3. Connect the device to the desktop through the chosen com port.
4. On the device, run tty.
5. Type letters on the hyper-terminal and you'll see they appear on the tty app window (vise versa).