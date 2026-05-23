<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: german_resfile - Win32 (WCE x86) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"X86Dbg/hello.res" /i ".." /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "DEBUG" /d "WIN32_PLATFORM_WFSP=100" /d "_X86_" /d "x86" /d "_i386_" /r "C:\stinger\public\sdk\samples\tpc\Win32\muihello\german_resfile\hello.rc"" 
Creating temporary file "C:\DOCUME~1\garrettv\LOCALS~1\Temp\RSP57.tmp" with contents
[
/nologo /W3 /GX- /Zi /Od /D "DEBUG" /D _WIN32_WCE=300 /D "WIN32_PLATFORM_WFSP=100" /D "_i386_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "_USRDLL" /D "GERMAN_RESFILE_EXPORTS" /Fp"X86Dbg/german_resfile.pch" /YX /Fo"X86Dbg/" /Fd"X86Dbg/" /Gs8192 /GF  /c 
"C:\stinger\public\sdk\samples\tpc\Win32\muihello\german_resfile\resfile.cpp"
]
Creating command line "cl.exe @C:\DOCUME~1\garrettv\LOCALS~1\Temp\RSP57.tmp" 
Creating temporary file "C:\DOCUME~1\garrettv\LOCALS~1\Temp\RSP58.tmp" with contents
[
commctrl.lib coredll.lib corelibc.lib   /nologo /base:"0x00100000" /stack:0x10000,0x1000 /entry:"_DllMainCRTStartup" /dll /incremental:yes /pdb:"X86Dbg/muihello.exe.0407.pdb" /debug /nodefaultlib:"OLDNAMES.lib" /nodefaultlib:libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib /out:"X86Dbg/muihello.exe.0407.mui" /implib:"X86Dbg/muihello.exe.0407.lib" /subsystem:windowsce,3.00 /MACHINE:IX86   
.\X86Dbg\resfile.obj
.\X86Dbg\hello.res
]
Creating command line "link.exe @C:\DOCUME~1\garrettv\LOCALS~1\Temp\RSP58.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
resfile.cpp
Linking...
Signing C:\stinger\public\sdk\samples\tpc\Win32\muihello\german_resfile\X86Dbg\muihello.exe.0407.mui
Error: Invalid value for -sha1 option
Usage:  SignCode [options] [FileName]
Options: 
 -spc  <file>       Spc file containing software publishing certificates
 -v    <pvkFile>    Pvk file name containing the private key
 -k    <KeyName>    Key container name
 -n    <name>       Text name representing content of the file to be signed
 -i    <info>       Place to get more info on content (usually a URL)
 -p    <provider>   Name of the cryptographic provider on the system
 -y    <type>       Cryptographic provider type to use
 -ky   <keytype>    Key type
                      <signature|exchange|<integer>>
 -$    <authority>  Signing authority of the certificate
                      <individual|commercial>
                      Default to using certificate's highest capability 
 -a    <algorithm>  Hashing algorithm for signing
                      <md5|sha1>. Default to md5
 -t    <URL>        TimeStamp server's http address
 -tr   <number>     The # of timestamp trial until succeeds. Default to 1
 -tw   <number>     The # of seconds delay between each timestamp. Default to 0
 -j    <dllName>    Name of the dll that provides attributes of the signature
 -jp   <param>      Parameter to be passed to the dll
 -c    <file>       file containing encoded software publishing certificate
 -s    <store>      Cert store containing certs. Default to my store
 -r    <location>   Location of the cert store in the registry
                      <localMachine|currentUser>. Default to currentUser
 -sp   <policy>     Add the certification path (chain) or add the certification
                    path excluding the root certificate (spcstore).
                      <chain|spcstore>. Default to spcstore
 -cn   <name>       The common name of the certificate
 -sha1 <thumbPrint> The sha1 hash of the certificate
 -x                 Do not sign the file.  Only Timestamp the file

Note:   To sign with a SPC file, the required options are -spc and -v if
        your private key is in a PVK file. If your private key is in a 
        registry key container, then -spc and -k are the required options.
Error: Signcode Failed.  Result = 80070057, (-2147024809)




<h3>Results</h3>
muihello.exe.0407.mui - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
