Code Sample Name: GetDeviceID

Feature Area: System Management

Description: Demonstrate calling the GetDeviceUniqueID API. 

GetDeviceUniqueID protects the privacy of a device. Multiple applications 
need to use a device's unique identifier to communicate with servers. 
To protect a device's privacy, multiple servers should not be able to 
correlate data from the same device. GetDeviceUniqueID does not use any 
additional information other than the data that is provided by the 
application, so any application that passes in the same application 
data buffer will obtain the same hash. This API can be called be any
application regardless of the trust level of the application.

This sample will call GetDeviceUniqueID two times using different 
application data to show that different values are returned for 
different application data.

Usage: No setup required -- just run the application

Relevant APIs/Associated Help Topics: GetDeviceUniqueID

Assumptions: none

Requirements: Visual Studio 2005, Windows Mobile 5.0 Pocket PC SDK


** For more information about this code sample, please see the Windows Mobile SDK help system. **
