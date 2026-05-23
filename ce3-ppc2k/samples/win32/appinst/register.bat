@echo off
REM
REM register.bat registers the Blackjack sample app with CEAppMgr.exe
REM

REM
REM You must modify the following directories to point to the correct locations
REM

set fileBlkjack="%WPCEmulDir%\..\samples\win32\appinst\blkjack.ini"
set fileCEAppMgr="C:\Program Files\Microsoft ActiveSync\ceappmgr.exe"

if not exist %fileBlkjack% goto Usage
if not exist %fileCEAppMgr% goto Usage

%fileCEAppMgr% %fileBlkjack%
goto Exit

:Usage
@echo ---
@echo Edit this batch file to point to the correct directories
@echo    fileBlkjack  = %fileBlkjack%
@echo    fileCEAppMgr = %fileCEAppMgr%
@echo       (this file is installed by Windows CE Services)
@echo ---

:Exit
