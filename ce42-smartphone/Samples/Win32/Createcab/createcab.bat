@echo off

@REM You will likely have to modify the location of CabwizSP.

if "%1" == "/?" goto usage
if "%1" == "" goto usage

if "%2" == "sp" goto spcab
"C:\Program Files\Windows CE Tools\wce420\POCKET PC 2003\Tools\Cabwiz.exe" createcab.inf /cpu %1
goto changecabname

:spcab
"C:\Program Files\Windows CE Tools\wce420\SMARTPHONE 2003\tools\CabwizSP.exe" createcab.inf /cpu %1

:changecabname
if not "%3" == "" move createcab.%1.cab %3.cab
goto end

:usage
echo Usage: "createcab [x86|ARMV4] [sp|ppc] [name for cab]"

:end
