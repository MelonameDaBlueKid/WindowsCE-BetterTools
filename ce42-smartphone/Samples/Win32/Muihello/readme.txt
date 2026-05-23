The MUIHello sample is a MUI version of the hello sample.  This document explains the three files that are built as part of this sample.

app: This directory builds muihello.exe.  Note that hello.cpp is identical to the version of hello.cpp found in the hello sample
resfile: This direcotry builds a resource-only DLL called muihello.exe.0409.mui.  This is where the OS will pull the resources used by muihello.exe if the device language is set to US English
german_resfile: This directory builds a resource-only DLL called muihello.exe.0407.mui.  This is where the OS will pull the resources used by muihello.exe if the device language is set to German.  Note that the strings are not actually in German, put are the English strings followed by "(Ger)"

To build this sample, build all three projects in the workspace and run muihello.exe.  Because muihello.exe loads resources from the .mui files, you'll need to be sure that those files have been built and copied to the target platform before muihello.exe will properly run.  By switching languages, note how the OS automatically loads strings from the appropriate .mui file.
