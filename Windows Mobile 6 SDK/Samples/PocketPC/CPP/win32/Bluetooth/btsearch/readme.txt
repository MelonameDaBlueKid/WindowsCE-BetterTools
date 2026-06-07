Code Sample Name: BtSearch

Feature Area: Communications

Description: 

    This sample provides an implementation of simple Bluetooth device discovery 
    via the Winsock 2 API. It provides a listbox control which, when searching 
    is complete, lists the discovered Bluetooth devices. Only names of the devices 
    are displayed, but the addresses of the devices are also retrieved, and can 
    be used to query the devices for more information (not implemented)

Relevant APIs: 
    Bluetooth
    Device discovery
    Winsock
    WSALookupServiceBegin
    WSALookupServiceNext
    WSALookupServiceEnd

Usage:
   Load the project from Visual Studio 2005, and build and deploy normally.

Assumptions: 
    There are bluetooth devices to discover.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK
    Activesync 4.5.

** For more information about this code sample, 
please see the Windows Mobile SDK help system. **

