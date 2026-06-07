The .cpf files in this directory can be used to set the RAPI Security Policy 
of a device.  Each .cpf file corresponds to a different RAPI security policy.

These .cpf files are signed with the privileged SDK certificate 
(SdkSamplePrivDeveloper.cer) which means they are guaranteed to work on any 
device where the SDK certificates have been installed.  But they cannot 
change the Security Policy of a device which the OEM or operator has not 
opened up for development.

To install a .cpf file, on Pocket PC, use ActiveSync to copy it to the device,
then click on it in File Explorer. On Smartphone, use ActiveSync to copy it to
\Windows\Start Menu\Accessories, then on the device, navigate to 
Start\More\Accessories, and click on the file. You will receive a Text Message 
in the Messaging application telling you whether the installation succeeded or 
failed.

Note, if you apply a .cpf file from the Tools\SecurityConfiguration directory, 
it will set the RAPI security policy to whatever the default is for that 
Security Configuration.  So the RAPI .cpf files should be applied last.

For reference, the XML files used to create the .cpf files are also included.  
The .cpf files were created with the following batch file:

copy %1.xml _setup.xml
makeCab _setup.xml %1.cpf
del _setup.xml
CabSigner.exe %1.cpf %1.cpf -spc SDKSamplePrivDeveloper.cer -v SDKSamplePrivDeveloper.pvk -n "Signed using SdkSamplePrivDeveloper.cer" -a sha1 -exesign -spc SDKSamplePrivDeveloper.spc -v SDKSamplePrivDeveloper.pvk -n "Privileged Trust" -a sha1