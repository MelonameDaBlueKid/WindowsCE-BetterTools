@echo off

if "%1" == "/?" goto usage
if "%1" == "" goto usage

"C:\Program Files\Windows CE Tools\wce420\SMARTPHONE 2003\Tools\signcode.exe" -spc "C:\Program Files\Windows CE Tools\wce420\SMARTPHONE 2003\Tools\emulcert.cer" -v "C:\Program Files\Windows CE Tools\wce420\SMARTPHONE 2003\Tools\emulcert.pvk" -n "Signed using emulcert.cer" -a sha1 %1
goto end

:usage
echo Usage: "signcab <cab file name>"
echo The certificate used to sign the cab is emulcert.cer.

:end
