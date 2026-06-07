Code Sample Name: FileDRM

Feature Area: File Based DRM

Description: Demonstrate calling the FileDrm APIs. 

This sample demonstrates using the FileDrm APIs. These APIs allow applications to
use DRM protected content with minimal changes. The APIs also work with non-protected
content as well.

This sample will display DRM protected JPEG images.

The basic rules for using DRM content are:

1. Call FileDrmVerifyRights before attempting to open the content to ensure that you
   will be able to use the content.
2. Use FileDrmCreateFile instead of CreateFile to open tne content.
3. Once the content has been "used" call FileDrmCommitRights.

The routine CImageView::OpenImageFile demonstrates the first two steps.
The routine CImageView::Draw demonstrates the third step. Note that 
FileDrmCommitRights is only called after the image is successfully displayed.
This is important for content where the number of times that the content can be
used is restricted. This routine also demonstrates how to handle content that may
have restrictions on how long it can be used.

Usage: You must have a phone designed to work with DRM content. Once you have 
the phone you should download at least one DRM protected JPEG image to the phone.

Relevant APIs/Associated Help Topics: FileDrmIsDRM, FileDrmShowLicenseInfo, FileDrmVerifyRights,
FileDrmCreateFile, FileDrmGetMetric, FileDrmCommitRights

Assumptions: none

Requirements: 
	Visual Studio 2005, 
	Windows Mobile 5.0 Pocket PC SDK or 
	Windows Mobile 5.0 Smartphone SDK


** For more information about this code sample, please see the Windows Mobile SDK help system. **
