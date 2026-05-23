@echo off
if not "%_preWceEmulPath%"=="" goto set
set _preWceEmulPath=%path%
set _preWceEmulInclude=%include%
set _preWceEmulLib=%Lib%
:set
set path=%WPCEmulDir%\Palm300\windows;%_preWceEmulPath%
set include=%WPCEmulDir%\..\include;%WPCEmulDir%\..\mfc\include;%WPCEmulDir%\..\atl\include;%_preWceEmulInclude%
set lib=%WPCEmulDir%\..\lib\x86em;%WPCEmulDir%\..\mfc\lib\x86em;%WPCEmulDir%\..\atl\lib\x86em;%_preWceEmulLib%
