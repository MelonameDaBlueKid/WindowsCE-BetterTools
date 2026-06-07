Code Sample Name: CECamera

Feature Area: Camera

Description: 

    This sample demonstrates how to take pictures and videos using the CameraCaptureDialog 
    managed API.

    If a default filename is used:
       - if a still picture is taken, the ".jpg" extension is appended to the default filename. 
          (Otherwise the CameraCaptureDialog would throw an InvalidArgumentException).

       - if a video is recorded, null is passed to the CameraCaptureDialog as the default filename. 
         The filename returned is then renamed to match the user entered filename while keeping the
	 extension returned.

Usage: 
    
    Load the project from Visual Studio 2005, and build and deploy normally.

    Specify the options in the dialog, then press "Start" to launch Camera for taking picture or video.

    Note:
    This sample works for both Windows Mobile 5.0 SmartPhone SDK and Windows Mobile 5.0 Pocket PC SDK.
    If you need to pick a specific configuration:
        1. Right click on the project.
        2. Click on "Change Target Platform"
        3. Choose the platform you decide to target and click OK.

Relevant APIs/Associated Help Topics: 
    
    Microsoft.WindowsMobile.Forms.CameraCaptureDialog

Assumptions: 
    You already have a PocketPC or Smartphone with Camera.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK or
    Windows Mobile 5.0 Smartphone SDK,
    ActiveSync 4.0.


** For more information about this code sample, please see the Windows Mobile SDK help system. **