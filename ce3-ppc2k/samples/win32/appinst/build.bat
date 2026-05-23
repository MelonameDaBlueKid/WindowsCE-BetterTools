@echo off
REM
REM build.bat creates the CAB files
REM

REM
REM You Must modify the following directories to point to the correct locations.
REM

set fileBlkjack="%WPCEmulDir%\..\samples\win32\appinst\blkjack.inf"
set fileCabwiz="%WPCEmulDir%\..\Support\appinst\bin\cabwiz.exe"

if not exist %fileBlkjack% goto Usage
if not exist %fileCabwiz% goto Usage

%fileCabwiz% %fileBlkjack% /err blkjack.err /cpu ppc201_sh3 ppc201_mips ppc211_sh3 ppc211_mips ppc30_sh3 ppc30_mips
goto Exit

:Usage
@echo ---
@echo Edit this batch file to point to the correct directories
@echo    fileBlkjack = %fileBlkjack%
@echo    fileCabwiz  = %fileCabwiz%
@echo       (these files are included in the Windows CE SDK)
@echo ---

:Exit
