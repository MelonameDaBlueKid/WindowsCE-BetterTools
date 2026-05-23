Application Installation Sample App
===================================

Files
-----
build.bat     - calls CabWiz to create the CAB files
register.bat  - calls CEAppMgr to register the app

common\*.*    - sample shared files
ppc201_mips\*.*	- sample binaries for Palm-size PC (Windows CE 2.01) mips
ppc201_sh3\*.* 	- sample binaries for Palm-size PC (Windows CE 2.01) SH3
ppc211_mips\*.*	- sample binaries for Palm-size PC (Windows CE 2.11) mips
ppc211_sh3\*.* 	- sample binaries for Palm-size PC (Windows CE 2.11) SH3
ppc30_mips\*.*	- sample binaries for Pocket PC (Windows CE 3.0) mips
ppc30_sh3\*.* 	- sample binaries for Pocket PC (Windows CE 3.0) SH3

cabfiles\*.*  - a copy of the CabWiz-generated CAB files

code\bin\*.*      - final binaries for SH3 and MIPS R3000
code\blkjack\*.*  - code used for "blkjack.exe"
code\setupdll\*.* - code used for the CESetupDLL "Blackjack Setup.dll"
code\selfreg\*.*  - code used for the self-registering "SelfRegister.dll"

Notes
-----
- This sample is not intended for emulation.

- You will need to modify the pathnames in the .BAT files appropriately.

- You run "build.bat" to create the CAB files, and then "register.bat"
to register the sample app with CEAppMgr.  If you cannot create the CAB
files, you can use the CABs found in the "cabfiles" subdirectory.

- This only works with Active Sync 3.0 and above. It doesn't work with previous version of active Sync.

