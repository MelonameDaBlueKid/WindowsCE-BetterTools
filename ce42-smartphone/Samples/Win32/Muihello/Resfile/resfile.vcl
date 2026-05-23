<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: resfile - Win32 (WCE x86) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"X86Dbg/hello.res" /i ".." /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "DEBUG" /d "WIN32_PLATFORM_WFSP=100" /d "_X86_" /d "x86" /d "_i386_" /r "D:\md03\public\sdk\samples\tpc\Win32\muihello\resfile\hello.rc"" 
Creating temporary file "d:\tmp\RSP7E1.tmp" with contents
[
/nologo /W3 /Zi /Od /I ".." /D "DEBUG" /D _WIN32_WCE=300 /D "WIN32_PLATFORM_WFSP=100" /D "_i386_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "_USRDLL" /D "RESFILE_EXPORTS" /Fp"X86Dbg/resfile.pch" /YX /Fo"X86Dbg/" /Fd"X86Dbg/" /Gs8192 /GF /c 
"D:\md03\public\sdk\samples\tpc\Win32\muihello\resfile\resfile.cpp"
]
Creating command line "cl.exe @d:\tmp\RSP7E1.tmp" 
Creating temporary file "d:\tmp\RSP7E2.tmp" with contents
[
corelibc.lib commctrl.lib coredll.lib /nologo /base:"0x00100000" /stack:0x10000,0x1000 /entry:"_DllMainCRTStartup" /dll /incremental:yes /pdb:"X86Dbg/muihello.exe.0409.pdb" /debug /nodefaultlib:"OLDNAMES.lib" /nodefaultlib:libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib /out:"X86Dbg\muihello.exe.0409.mui" /implib:"X86Dbg/muihello.exe.0409.lib" /subsystem:windowsce,3.00 /MACHINE:IX86 
.\X86Dbg\resfile.obj
.\X86Dbg\hello.res
]
Creating command line "link.exe @d:\tmp\RSP7E2.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
resfile.cpp
Linking...
Signing D:\md03\public\sdk\samples\tpc\Win32\muihello\resfile\X86Dbg\muihello.exe.0409.mui
Warning: This file is signed, but not timestamped.
Succeeded




<h3>Results</h3>
muihello.exe.0409.mui - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
