Code Sample Name: PhoneFinder

Feature Area: Managed Windows Mobile APIs

Description: 
	PhoneFinder is an app that can help you find your phone if you ever lose 
	it.  When you run the app, you have the option of setting a PIN and 
	enabling or disabling PhoneFinder.  

	To activate PhoneFinder, send a text message from any cell phone to your
	phone.  Enter ONLY the PIN in the body of the text message.  If enabled, 
	your phone will wake up and start playing a sound.  While playing the 
	sound, it will also display your owner information so that if someone else 
	finds your phone, they know how to contact you.  

	SMS interception is used to raise an event when your PIN is sent to the 
	phone via a text message and the State and Notification Broker is used to 
	retrieve the owner information if it exists. 

	To play the sound, the sample uses PInvoke to call the native API, 
	PlaySound.  PlaySound will play the sound even if your phone is set to 
	Silent, making it very useful if you lose your phone while set to silent.

Usage: 
	Build the app and run it, or optionally install the cab file on your 
	device to deploy it.

Relevant APIs/Associated Help Topics: 	
	Managed Message Interception
	Managed State and Notification Broker
	PlaySound

Assumptions: Your device can receive text messages

Note: If you have not installed the SDKSampleUnprivDeveloper certificate, you will
need to do that so that your dll and cab projects are signed correctly.  

	To install the certificate from the windows desktop:
	1. Click Start
	2. Click Run
	3. Type in the path to SDKSampleUnprivDeveloper.pfx.  (This file will be where 
	   you installed the Smartphone SDK under the Tools directory)
	4. Click OK
	   (The Certificate Import Wizard should appear)
	5. Click Next
	   (The path to the certificate should be filled in for the File name)
	6. Click Next
	7. Click Next (you do not need a password)
	8. Click Next (you want the default options here: Automatically select the 
	   certificate store based on the type of certificate)
	9. Click Finish

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Standard SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 
