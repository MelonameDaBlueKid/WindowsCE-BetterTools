WSock ReadMe
============
This sample is a one-form application that demonstrates the use of the Winsock control.  It includes a desktop Visual Basic 6.0 desktop application that communicates with the Window CE application through TCP, UDP and IRDA protocols.

Begin this sample application by starting both the desktop application and the Windows CE application. Start one of the applications as a server using one of the three protocols (TCP, UDP, or IRDA). Once one of the applications has started as a server, connect the second application to the server.  When connected, you can send data between the two applications using the text boxes and send buttons.

Both applications have similar interfaces.  
- Select the type of protocol that will be used with the radio buttons on the right side of the form.  
- The Server Name and Port Number fields contain information about the connection.  
- The Messages text box contains messages concerning the Winsock connection.  
- The Send button sends the text in the Data to Send text box.  
- The Connect to Server, Start as Server and the Disconnect buttons begin or terminate the connection.  
- The Status button displays information about the current connection.  
- The string button ($) buffers a text string in the Data to Send text box.  
- The exclamation button (!) reports on the current error object.  
- The X button clears the Messages text box.
- The clear button above each of the data text boxes clears the text box.

To Install and Run the Sample
=============================
1. Compile and the run the desktop application Wsock_vb6.vbp.  The desktop application will communicate with the Windows CE application.  
2. Run the Wsock_HP.vbp (or Wsock_HPCPro.vbp) application on a remote device or emulator.
3. Start one of the two applications as a server.
4. On the server application, click status and note the values of LocalHostName and LocalPort.
5. Enter the values from step 4 into the Server Name and Port Number fields on the second application and click the 'Connect to server' button.

When the connection has been made between the two applications, enter data in the 'Data to Send' text box in either application and click the 'Send' button.

Additional Notes
================
This sample will run in the Windows CE emulator.

See further documentation on connecting a Windows CE device and using the Winsock Control in the Visual Basic for Windows CE online documentation. Information about creating applications that use TCP, UDP and IRDA protocols can be found in the MSDN library.

