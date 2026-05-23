helloplug

Sample Smartphone home screen plugin.  See SDK docs on writing plugins.  Note that nothing here is signed.  You will have to add signing of the .dll and .cab file in order to use it on a device.  See the security model documantation in the SDK.

Source Files for the sample plugin:
helloplug.cpp
helloplug.def

Sample home screen layout that uses the sample plugin:
Common\Test.home.xml

Setup .inf file:
setup\helloplug.inf

Example of running CabwizSP:
setup\makecab.bat

