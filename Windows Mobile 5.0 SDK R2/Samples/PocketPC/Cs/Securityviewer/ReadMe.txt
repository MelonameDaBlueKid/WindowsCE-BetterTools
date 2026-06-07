Code Sample Name: SecurityViewer

Feature Area: Security

Description: 
	SecurityViewer is an application that displays all of the security policies
	and all of the certificates installed on a device.  It also displays which 
	of the standard Security Configurations the device is in.
	
Usage: 

    This sample works for both Windows Mobile 5.0 SmartPhone SDK and Windows Mobile 5.0 Pocket PC SDK.
    If you need to pick a specific configuration:
        1. Right click on the project.
        2. Click on "Change Target Platform"
        3. Choose the platform you decide to target and click OK.

    Load the project from Visual Studio 2005, and build and deploy normally.

    Notes
    This application must run as Trusted, which means it must be signed with a 
    security certificate that is in the privileged certificate store on the device.
    See "Windows Mobile Security and Software Development" in the SDK documentation
    for details on how to install the SDK certificates onto the device, and how to 
    use the privileged SDK certificate to sign this application.
	

Relevant APIs/Associated Help Topics: 
	Microsoft.WindowsMobile.Configuration
	
Assumptions: The SDK certificates have been installed on the device.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK or
    Windows Mobile 5.0 Smartphone SDK,
    ActiveSync 4.0.


** For more information about this code sample, please see the Windows Mobile SDK help system. **

