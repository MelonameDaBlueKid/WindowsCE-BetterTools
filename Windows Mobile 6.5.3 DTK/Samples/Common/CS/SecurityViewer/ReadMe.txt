Code Sample Name: SecurityViewer

Feature Area: Security

Description: 
	SecurityViewer is an application that displays all of the security policies
	and all of the certificates installed on a device.  It also displays which 
	of the standard Security Configurations the device is in.
	
Usage: 

    This sample works for both Windows Mobile 6 Standard SDK and Windows Mobile 6 Professional SDK.
    If you need to pick a specific configuration:
        1. Right click on the project.
        2. Click on "Change Target Platform"
        3. Choose the platform you decide to target and click OK.

    Load the project from Visual Studio 2005, and build and deploy normally.

    Notes
    This application must run as Trusted, which means it must be signed with a 
    security certificate that is in the privileged certificate store on the device.

    To install the certificate from the windows desktop:
    1. Click Start
    2. Click Run
    3. Type in the path to SDKSamplePrivDeveloper.pfx.  (This file will be where 
       you installed the Windows Mobile SDK under the 
       "\Tools\Security\SDK Development Certificates" directory)
    4. Click OK
       (The Certificate Import Wizard should appear)
    5. Click Next
       (The path to the certificate should be filled in for the File name)
    6. Click Next
    7. Click Next (you do not need a password)
    8. Click Next (you want the default options here: Automatically select the 
       certificate store based on the type of certificate)
    9. Click Finish
	

Relevant APIs/Associated Help Topics: 
	Microsoft.WindowsMobile.Configuration
	
Assumptions: The SDK certificates have been installed on the device.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.


** For more information about this code sample, please see the Windows Mobile SDK help system. **

