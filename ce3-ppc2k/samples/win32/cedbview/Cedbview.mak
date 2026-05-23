# Microsoft Developer Studio Generated NMAKE File, Based on dbview.dsp
!IF "$(CFG)" == ""
CFG=dbview - Win32 (WCE MIPS) Debug
!MESSAGE No configuration specified. Defaulting to dbview - Win32 (WCE MIPS) Debug.
!ENDIF 

!IF "$(CESubsystem)" == ""
CESubsystem=windowsce,2.0
!MESSAGE Variable CESubsystem not specified. Defaulting to windowsce,2.0
!ENDIF 

!IF "$(CEVersion)" == ""
CEVersion=200
!MESSAGE Variable CEVersion not specified. Defaulting to 200
!ENDIF 

!IF "$(CEConfigName)" == ""
CEConfigName=H/PC Ver. 2.00
!MESSAGE Variable CEConfigName not specified.  Defaulting to H/PC Ver. 2.00
!ENDIF 

!IF $(CEVersion) < 201
CECrt=L
CECrtDebug=Ld
CECrtMT=T
CECrtMTDebug=Td
CENoDefaultLib=corelibc.lib
CEx86Corelibc= 
!ELSE 
CECrt=C
CECrtDebug=C
CECrtMT=C
CECrtMTDebug=C
CENoDefaultLib=libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib
CEx86Corelibc=corelibc.lib
!ENDIF 

!IF "$(CFG)" != "dbview - Win32 (WCE MIPS) Release" && "$(CFG)" != "dbview - Win32 (WCE MIPS) Debug" && "$(CFG)" != "dbview - Win32 (WCE SH3) Release" && "$(CFG)" != "dbview - Win32 (WCE SH3) Debug" && "$(CFG)" != "dbview - Win32 (WCE x86) Release" && "$(CFG)" != "dbview - Win32 (WCE x86) Debug" && "$(CFG)" != "dbview - Win32 (WCE x86em) Release" && "$(CFG)" != "dbview - Win32 (WCE x86em) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dbview.mak" CFG="dbview - Win32 (WCE MIPS) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbview - Win32 (WCE MIPS) Release" (based on "Win32 (WCE MIPS) Application")
!MESSAGE "dbview - Win32 (WCE MIPS) Debug" (based on "Win32 (WCE MIPS) Application")
!MESSAGE "dbview - Win32 (WCE SH3) Release" (based on "Win32 (WCE SH3) Application")
!MESSAGE "dbview - Win32 (WCE SH3) Debug" (based on "Win32 (WCE SH3) Application")
!MESSAGE "dbview - Win32 (WCE x86) Release" (based on "Win32 (WCE x86) Application")
!MESSAGE "dbview - Win32 (WCE x86) Debug" (based on "Win32 (WCE x86) Application")
!MESSAGE "dbview - Win32 (WCE x86em) Release" (based on "Win32 (WCE x86em) Application")
!MESSAGE "dbview - Win32 (WCE x86em) Debug" (based on "Win32 (WCE x86em) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"

OUTDIR=.\WCEMIPSRel
INTDIR=.\WCEMIPSRel
# Begin Custom Macros
OutDir=.\WCEMIPSRel
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=clmips.exe
CPP_PROJ=/nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /Fp"$(INTDIR)\dbview.pch" /YX /Fo"$(INTDIR)\\" /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\dbview.res" /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG" 
MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=commctrl.lib coredll.lib aygshell.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /incremental:no /pdb:"$(OUTDIR)\dbview.pdb" /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /subsystem:$(CESubsystem) /STACK:65536,4096 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"

OUTDIR=.\WCEMIPSDbg
INTDIR=.\WCEMIPSDbg
# Begin Custom Macros
OutDir=.\WCEMIPSDbg
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"
	-@erase "$(OUTDIR)\dbview.ilk"
	-@erase "$(OUTDIR)\dbview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=clmips.exe
CPP_PROJ=/nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /Fp"$(INTDIR)\dbview.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\dbview.res" /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" 
MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=commctrl.lib coredll.lib aygshell.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /incremental:yes /pdb:"$(OUTDIR)\dbview.pdb" /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /subsystem:$(CESubsystem) /STACK:65536,4096 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"

OUTDIR=.\WCESH3Rel
INTDIR=.\WCESH3Rel
# Begin Custom Macros
OutDir=.\WCESH3Rel
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=shcl.exe
CPP_PROJ=/nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /Fp"$(INTDIR)\dbview.pch" /YX /Fo"$(INTDIR)\\" /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\dbview.res" /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG" 
MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=commctrl.lib coredll.lib aygshell.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /incremental:no /pdb:"$(OUTDIR)\dbview.pdb" /machine:SH3 /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /subsystem:$(CESubsystem) /STACK:65536,4096 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"

OUTDIR=.\WCESH3Dbg
INTDIR=.\WCESH3Dbg
# Begin Custom Macros
OutDir=.\WCESH3Dbg
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"
	-@erase "$(OUTDIR)\dbview.ilk"
	-@erase "$(OUTDIR)\dbview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=shcl.exe
CPP_PROJ=/nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /Fp"$(INTDIR)\dbview.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\dbview.res" /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" 
MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=commctrl.lib coredll.lib aygshell.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /incremental:yes /pdb:"$(OUTDIR)\dbview.pdb" /debug /machine:SH3 /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /subsystem:$(CESubsystem) /STACK:65536,4096 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"

OUTDIR=.\WCEX86Rel
INTDIR=.\WCEX86Rel
# Begin Custom Macros
OutDir=.\WCEX86Rel
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O2 /D "x86" /D "_i386_" /D "_x86_" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "NDEBUG" /D "i_386_" /D "_MBCS" /Fo"$(INTDIR)\\" /Gs8192 /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\dbview.res" /d "x86" /d "_i386_" /d "_x86_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "NDEBUG" 
MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(CEx86Corelibc) commctrl.lib coredll.lib aygshell.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /incremental:no /pdb:"$(OUTDIR)\dbview.pdb" /machine:IX86 /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /subsystem:$(CESubsystem) /STACK:65536,4096 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"

OUTDIR=.\WCEX86Dbg
INTDIR=.\WCEX86Dbg
# Begin Custom Macros
OutDir=.\WCEX86Dbg
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"
	-@erase "$(OUTDIR)\dbview.ilk"
	-@erase "$(OUTDIR)\dbview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Zi /Od /D "x86" /D "_i386_" /D "_x86_" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "DEBUG" /D "i_386_" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Gs8192 /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\dbview.res" /d "x86" /d "_i386_" /d "_x86_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "DEBUG" 
MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(CEx86Corelibc) commctrl.lib coredll.lib aygshell.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /incremental:yes /pdb:"$(OUTDIR)\dbview.pdb" /debug /machine:IX86 /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /subsystem:$(CESubsystem) /STACK:65536,4096 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"

OUTDIR=.\WCEx86emRel
INTDIR=.\WCEx86emRel
# Begin Custom Macros
OutDir=.\WCEx86emRel
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O2 /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "NDEBUG" /D "x86" /D "i486" /D "_x86_" /D "_MBCS" /Fp"$(INTDIR)\dbview.pch" /YX /Fo"$(INTDIR)\\" /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dbview.res" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "NDEBUG" 
MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(CEx86Corelibc) commctrl.lib coredll.lib aygshell.lib /nologo /stack:0x10000,0x1000 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\dbview.pdb" /machine:I386 /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /windowsce:emulation 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"

OUTDIR=.\WCEx86emDbg
INTDIR=.\WCEx86emDbg
# Begin Custom Macros
OutDir=.\WCEx86emDbg
# End Custom Macros

ALL : "$(OUTDIR)\dbview.exe"


CLEAN :
	-@erase "$(INTDIR)\dbfunc.obj"
	-@erase "$(INTDIR)\dbview.res"
	-@erase "$(INTDIR)\enumdb.obj"
	-@erase "$(INTDIR)\index.obj"
	-@erase "$(INTDIR)\initproc.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\seek.obj"
	-@erase "$(INTDIR)\treeview.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wndproc.obj"
	-@erase "$(OUTDIR)\dbview.exe"
	-@erase "$(OUTDIR)\dbview.ilk"
	-@erase "$(OUTDIR)\dbview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /Od /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "_DEBUG" /D "x86" /D "i486" /D "_x86_" /D "_MBCS" /Fp"$(INTDIR)\dbview.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dbview.res" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "_DEBUG" /d "x86" /d "i486" /d "_x86_" 
MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dbview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(CEx86Corelibc) commctrl.lib coredll.lib aygshell.lib /nologo /stack:0x10000,0x1000 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\dbview.pdb" /debug /machine:I386 /nodefaultlib:"$(CENoDefaultLib)" /out:"$(OUTDIR)\dbview.exe" /windowsce:emulation 
LINK32_OBJS= \
	"$(INTDIR)\dbfunc.obj" \
	"$(INTDIR)\enumdb.obj" \
	"$(INTDIR)\index.obj" \
	"$(INTDIR)\initproc.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\seek.obj" \
	"$(INTDIR)\treeview.obj" \
	"$(INTDIR)\wndproc.obj" \
	"$(INTDIR)\dbview.res"

"$(OUTDIR)\dbview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("dbview.dep")
!INCLUDE "dbview.dep"
!ELSE 
!MESSAGE Warning: cannot find "dbview.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dbview - Win32 (WCE MIPS) Release" || "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug" || "$(CFG)" == "dbview - Win32 (WCE SH3) Release" || "$(CFG)" == "dbview - Win32 (WCE SH3) Debug" || "$(CFG)" == "dbview - Win32 (WCE x86) Release" || "$(CFG)" == "dbview - Win32 (WCE x86) Debug" || "$(CFG)" == "dbview - Win32 (WCE x86em) Release" || "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"
SOURCE=.\dbfunc.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\dbfunc.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dbview.rc

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\dbview.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\enumdb.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\enumdb.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\index.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\index.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\initproc.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\initproc.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\main.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\memory.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\seek.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\seek.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\treeview.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\treeview.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\wndproc.c

!IF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Release"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE MIPS) Debug"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Release"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE SH3) Debug"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Release"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86) Debug"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Release"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dbview - Win32 (WCE x86em) Debug"


"$(INTDIR)\wndproc.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

