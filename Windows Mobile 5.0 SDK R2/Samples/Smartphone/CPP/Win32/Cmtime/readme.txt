Code Sample Name: CMTime

Feature Area: Connection Manager

Description: 

    The CMTime sample demonstrates how to use connection manager by using it to 
    establish a connection. It connects to a time server and synchronizes the 
    phone with the current time.

    The sample consists of two solutions:

    - CMTime -
    This is the Smartphone solution.
    
    - TimeServer -
    This is a Win32 console app that mimics a time server for use with the 
    CMTime device sample. When you run TimeServer.exe the command window 
    will indicate activity when an application connects to get the time. 

    
Usage: 

    Build and deploy normally using Visual Studio 2005.

    If you want to use the sample to connect to a time server on the Internet, 
    you can set the IP address for that server in g_in_addr. You can substitute 
    the IP address of any time server that supports Time Protocol (RFC-868). 
    Note that using a time server on the Internet requires that your computer be 
    able to access port 37. Depending on your network and proxy server 
    configuration, you may need to ask your network administrator or help desk 
    what you need to do to access traffic on port 37. Generally, this will 
    require you to install or configure a proxy client on your desktop computer. 
    If your network is not allowing port 37 traffic through to your computer, 
    you will see the message "...Finding Connection..." in the CMTime application 
    window for about one minute followed by the message "Error getting time!"

Relevant APIs: 
    ConnMgrReleaseConnection
    ConnMgrEnumDestinations
    ConnMgrEstablishConnection
    TCP sockets

Assumptions: None.

Requirements: 
    Visual Studio 2005
    Windows Mobile 5.0 Smartphone SDK,
    ActiveSync 4.0.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **
   

