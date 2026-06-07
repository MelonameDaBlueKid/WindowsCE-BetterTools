____________________________________________________

Read me for ActiveSync Monitor & Proxy Debugging Tool
____________________________________________________

Note: This tool is unsupported by Microsoft, and is supplied 'as is'.

PURPOSE:
=========
This tool allows you to monitor all the COM calls that occur between one or more ActiveSync Service Providers(SSPs) and the ActiveSync Manager.

SYSTEM REQUIREMENTS:
========================
* Microsoft Windows® 95, Windows® 98, Windows NT® 4.00(x86), Windows® 2000, or Windows® XP
* Microsoft ActiveSync 2.2 or higher

WHAT'S IN THIS DIRECTORY:
=========================
This directory contains the following files,

SyncMon.exe: Viewer application that displays the COM calls that occur between SSPs and ActiveSync manager.
SyncProxy.dll: Proxy SSP dynamic link library, that sends call data information to SyncMon.exe.
Readme.txt:    This file

INSTALLATION:
=============
Copy the SyncMon.exe & SyncProxy.dll files to the same directory.

USAGE:
=======
Start up SyncMon.exe and get to the options dialog(tools->options menu). The options dialog will display the list of currently installed Sync Service providers. From the list of providers, check the provider(s) that you want to monitor. Close the ActiveSync window and disconnect/re-connect the device. When ActiveSync starts synchronizing the provider(s) that you registered for, the calls will be displayed in the list view of the SyncMon application. To unregister a provider that you had previously registered for, get to the options dialog, uncheck the provider from the list, shut down ActiveSync and disconnect/re-connect the device for the changes to take effect.

The icon displayed next to each call denotes whether the call was successful or not(indicated by a green check or a red cross). Note: It is normal for certain sync calls to fail and then be called again, for example, when sync manager calls a provider's IReplStore:GetStoreInfo() method, the provider will return E_OUTOFMEMORY the first time around, and succeed the next time. Please refer to the ActiveSync documentation for more details.

The frame window status pane displays the total number of calls currrently in the list, and also the total time it took for all the calls listed to complete. The time displayed is not the elapsed time, instead it is simply the total of the "call time" column.