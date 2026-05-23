Instructions for creating and signing a cab:
===========================================

1. Create a working directory (e.g., createcab).

2. Create a subdirectory whose name is the processor type that the installed binaries are designed to run on.  (e.g., createcab\x86)

3. Put into that subdirectory all the modules that are to be installed for that processor type.

4. Create an information (.inf) file and put it in the working directory.  The name of the .inf file will also be the name of the resultant cab.  (E.g., foo.inf will result in foo.cab.)  For more information on creating a .inf file, see the "Creating an Information File" section in the SDK help.

5. Type "cabwiz <.inf file> /cpu <cpu type>".  (E.g., "cabwiz foo.inf /cpu x86")  For more information on cabwiz, just type "cabwiz".  

NOTE:  PocketPC and Smartphone use different cabwiz's.  PocketPC uses cabwiz, while Smartphone uses cabwizsp.  Both tools can be found in their respective SDK's Tools directory (e.g., "C:\Program Files\Windows CE Tools\wce420\POCKET PC 2003\Tools").

6. What should result is a file ending with .x86.cab (or whatever other processor type).  (E.g., foo.x86.cab or foo.ARMV4.cab)  Optionally, sign the cab with signcode.exe and a certificate's private key.  One cert you can use is the Emulcert.cer and Emulcert.pvk in the smartphone SDK's Tools directory.  Alternatively, you can create your own certificate with which to sign the cab; see the createcert SDK sample on how to create a new certificate.  For example, to sign a cab, enter the following:

signcode.exe -spc emulcert.cer -v emulcert.pvk -n "Signed using emulcert.cer" -a sha1 foo.x86.cab

(Signcode.exe can be found in the smartphone SDK's Tools directory.)


Using CreateCab Sample:
======================

1. Change directory into the one where createcab.inf and createcab.bat reside.  Modify the paths to cabwiz and cabwizsp in createcab.bat to its location on your machine.

2. Enter "createcab.bat x86 sp cfgclient" on the cmd prompt.  

3. The resulting cab (cfgclient.cab) should be in the directory.  (Note that the resultant cab would have been createcab.x86.cab, but createcab.bat renames the cab to cfgclient.cab, as specified on the cmd line.)

Createcab.bat does not sign the cab for you.


