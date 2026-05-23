' Smartphone SDK specific configuration

Dim platman
Dim platform
Dim platformID
Dim InstDir
Dim InstallState
Dim propInfo

binfile1 = "SP_2003_WWE_VIRTUAL_RADIO.bin"
binfile2 = "SP_2003_WWE.bin"

Const HKEY_CLASSES_ROOT 	= &H80000000
Const HKEY_CURRENT_USER 	= &H80000001
Const HKEY_LOCAL_MACHINE  	= &H80000002
Const HKEY_USERS 		= &H80000003
Const HKEY_CURRENT_CONFIG 	= &H80000005
Const HKEY_DYN_DATA 	 	= &H80000006

Const REG_SZ 			= 1
Const REG_EXPAND_SZ		= 2
Const REG_BINARY		= 3
Const REG_DWORD			= 4
Const REG_MULTI_SZ		= 7



set args = wscript.Arguments

If args.count <> 2 Then
	WScript.echo("Usage: install_script <Install Dir> <State>")
	Wscript.quit(1)
End If

InstDir = args(0)
InstallState = args(1)

' Trim trailing backslash as the rest of the script assumes there isn't one.
If Right(InstDir, 1) = "\" Then
    InstDir = Left(InstDir, Len(InstDir) - 1)
End If

On Error Resume Next

set WshShell = WScript.CreateObject("WScript.Shell")

set FSO = CreateObject("Scripting.FileSystemObject")

' Platform guid
platformID = "{2ABBB7CA-3274-4C34-9A26-97F9CC832257}"

' Get path to emulator
PBEmulDir = WshShell.RegRead("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows CE Tools\Platform Manager\Setup\Platman Install Dir")
PBEmulDir = PBEmulDir & "bin"

set WshEnv = WshShell.Environment("USER")
TempDir = WshEnv("TEMP")

If TempDir = "" Then
    TempDir = InstDir
End If

' Get proper App Data Dir. 
AppDataDir = WshShell.RegRead("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders\Common AppData")

' The VS .Net Addon will be placed here
VSAddOnDir = AppDataDir & "\microsoft\visualstudio\devices\addons"

' Check for VS .Net 7.1
VSProdDir = WshShell.RegRead("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\7.1\InstalledProducts\Smart Device Extensions\VS7InstallDir")


If (InstDir <> "") and (InstallState = 0) Then

    ' Handle Installation

    set platman = CreateObject("PlatformManager.PlatformManager.1")
    set platform = platman.GetPlatform(platformID)

    ' set the new startup server for the emulator platform
    set EnumDevices = platform.EnumDevices

    ' set the default startup server to the proper emulator startup server
    For index = 1 to EnumDevices.Count
        set device = EnumDevices.Item(index)
        If device.Name = "SMARTPHONE 2003 Emulator" Then
            device.StartupServer = "{3F1E2DE3-78A1-4B0E-BDEB-F7088940C1A2}"
        End If
    Next

    FSO.DeleteFile InstDir & "\Emulation\nk.cem"

    set property = platform.GetProperty("{3F1E2DE3-78A1-4B0E-BDEB-F7088940C1A2}")
    property.AddPropInfo "Ethernet", 1, "1"
    property.AddPropInfo "Memory", 1, "48"
    property.AddPropInfo "Path", 1, InstDir & "\Emulation\" & binfile1
    property.AddPropInfo "Ports", 1, "1"
    property.AddPropInfo "Skins", 1, InstDir & "\Emulation"
'    property.AddPropInfo "Video", 1, "176x220x16"
    property.AddPropInfo "Video", 1, ""
    property.AddPropInfo "ImageName", 1, "Smartphone 2003 (Virtual Radio)"

    EmulImage2 = "{5930001A-151F-478C-9A20-29085853CD9C}"

    set property2 = property.AddProperty("", EmulImage2)
    property2.AddPropInfo "Ethernet", 1, "1"
    property2.AddPropInfo "Memory", 1, "48"
    property2.AddPropInfo "Path", 1, InstDir & "\Emulation\" & binfile2
    property2.AddPropInfo "Ports", 1, "1"
    property2.AddPropInfo "Skins", 1, InstDir & "\Emulation"
    property2.AddPropInfo "Video", 1, ""
    property2.AddPropInfo "ImageName", 1, "Smartphone 2003 (Radio Required)"

    ' Set some Smartfon specific Properties
    set property = platform.GetProperty("{2ABBB7CA-3274-4C34-9A26-97F9CC832257}")

    ' Delete roller's info and then use what we really want
    property.DeletePropInfo("CEPlatform")
    property.AddPropInfo "CEPlatform", 3, "WIN32_PLATFORM_WFSP=200"    

    property.AddPropInfo "Platform Designers", 3, "Menubar Editor"

    property.AddPropInfo "Platform Wizards Directory", 3, InstDir+"\wizards"
    property.AddPropInfo "Remote App Directory", 3, "\Storage\Application Data\Volatile\"
    property.AddPropInfo "Remote Dbg Directory", 3, "\Storage\Windows\"
    property.AddPropInfo "Security Support", 3, "1"

    ' Indicate MFC and ATL support
    property.AddPropInfo "ATLCE Support", 3, "1"

    ' set proper include, src and lib paths
    includeDirx86 = InstDir & "\Include\emulator;" & InstDir & "\atl\include"
    libDirx86 = InstDir & "\lib\emulator;" & InstDir & "\atl\lib\x86"

    includeDirARMV4 = InstDir & "\Include\ARMV4;" & InstDir & "\atl\include"
    libDirARMV4 = InstDir & "\lib\ARMV4;" & InstDir & "\atl\lib\ARMV4"

    ' src dirs is same for both CPUs
    srcDir = InstDir & "\atl\src;" & InstDir & "\atl\include"

    ' ARMV4 CPU
    set propertyCPU = property.GetProperty("{D6518FFB-710F-11D3-99F2-00105A0DF099}")
    propertyCPU.DeletePropInfo("Include Dirs")
    propertyCPU.DeletePropInfo("Lib Dirs")
    propertyCPU.DeletePropInfo("Src Dirs")
    propertyCPU.AddPropInfo "Include Dirs", 3, includeDirARMV4
    propertyCPU.AddPropInfo "Lib Dirs", 3, libDirARMV4
    propertyCPU.AddPropInfo "Src Dirs", 3, srcDir

    ' x86 Emulator CPU
    set propertyCPU = property.GetProperty("{32E52003-403E-442D-BE48-DE10F8C6131D}")
    propertyCPU.DeletePropInfo("Include Dirs")
    propertyCPU.DeletePropInfo("Lib Dirs")
    propertyCPU.DeletePropInfo("Src Dirs")
    propertyCPU.AddPropInfo "Include Dirs", 3, includeDirx86
    propertyCPU.AddPropInfo "Lib Dirs", 3, libDirx86
    propertyCPU.AddPropInfo "Src Dirs", 3, srcDir


    ' Add install dir path so evc can find us
    set property = platform.AddProperty("{C5C00C80-30C2-11D3-99DD-00105A0DF099}")
    property.AddPropInfo "InstallDir", 3, InstDir

    ' Copy platman/remote tools device packages and sign them for the Emulator.
    WshShell.Run """" & InstDir & "\Tools\spdps.exe" & """ /emulonly", 1, 1

    ' Add some useful shortcuts

    WinDir = WShShell.ExpandEnvironmentStrings("%Windir%") 

    ProgramsDir = WshShell.SpecialFolders("AllUsersPrograms")

    SDKShortcuts = ProgramsDir + "\Microsoft Smartphone 2003 SDK"

    set FSO = CreateObject("Scripting.FileSystemObject")
    FSO.CreateFolder(SDKShortcuts)


    set ShellLink = WshShell.CreateShortCut(SDKShortcuts + "\Smartphone 2003 SDK.lnk")
    ShellLink.TargetPath = "%COMSPEC%"
    ShellLink.WindowStyle = 1
    ShellLink.IconLocation = "cmd.exe, 0"
    ShellLink.Description = "Smartphone 2003 SDK Tools Link"
    ShellLink.WorkingDirectory = InstDir & "\Tools"
    ShellLink.Save

    If FSO.FileExists(PBEmulDir & "\PBEmulator.exe") Then
        If FSO.FileExists(InstDir & "\Emulation\emul.cmd") = FALSE Then
            set emulFile = FSO.OpenTextFile(InstDir & "\Emulation\emul.cmd", 2, True)
            emulFile.WriteLine("start """" """ & PBEmulDir & "\PBEmulator.exe"" /MemorySize 48 /Fastbackground /Skin """ & InstDir & "\Emulation\smartphone_emulator_skin.xml"" /CEImage """ & InstDir & "\Emulation\" & binfile1 & """ /VMName ""Smartphone 2003 - Smartphone 2003 Emulator"" /HostKey 165")
            emulFile.Close
        End If

        If FSO.FileExists(SDKShortcuts & "\Smartphone 2003 Emulator.lnk") = FALSE Then
            set ShellLink = WshShell.CreateShortCut(SDKShortcuts + "\Smartphone 2003 Emulator.lnk")
            ShellLink.TargetPath = InstDir & "\Emulation\emul.cmd"
            ShellLink.WindowStyle = 1
            ShellLink.IconLocation = PBEmulDir & "\PBEmulator.exe, 0"
            ShellLink.Description = "Smartphone 2003 Emulator Link"
            ShellLink.WorkingDirectory = PBEmulDir
            ShellLink.Arguments = ""
            ShellLink.Save
        End If
    End IF

    If FSO.FileExists(SDKShortcuts & "\Smartphone 2003 Help.lnk") = FALSE Then
        set ShellLink = WshShell.CreateShortCut(SDKShortcuts + "\Smartphone 2003 Help.lnk")
        ShellLink.TargetPath = InstDir + "\Help\{2ABBB7CA-3274-4C34-9A26-97F9CC832257}.chm"
        ShellLink.WindowStyle = 1
        ShellLink.IconLocation = "winhelp.exe, 0"
        ShellLink.Description = "Smartphone 2003 SDK Help Link"
        ShellLink.WorkingDirectory = InstDir + "\Help"
        ShellLink.Save
    End If

    If FSO.FileExists(SDKShortcuts & "\Smartphone 2003 Readme.lnk") = FALSE Then
        set ShellLink = WshShell.CreateShortCut(SDKShortcuts + "\Smartphone 2003 Readme.lnk")
        ShellLink.TargetPath = InstDir + "\readme.htm"
        ShellLink.WindowStyle = 1
        ShellLink.IconLocation = "notepad.exe, 0"
        ShellLink.Description = "Smartphone 2003 SDK Readme Link"
        ShellLink.WorkingDirectory = InstDir
        ShellLink.Save
    End If

    ' Replace the roller generated chm with one that has a better TOC
    FSO.DeleteFile InstDir & "\Help\{2ABBB7CA-3274-4C34-9A26-97F9CC832257}.chm"
    FSO.MoveFile InstDir & "\Help\sdkhelp.chm", InstDir & "\Help\{2ABBB7CA-3274-4C34-9A26-97F9CC832257}.chm"

    WshShell.RegWrite "HKCU\Software\Microsoft\Windows CE Services\SerialBaudRate",57600,"REG_DWORD"
    WshShell.RegWrite "HKCU\Software\Microsoft\Windows CE Services\SerialPort","COM1","REG_SZ"
  
    If VSProdDir <> "" Then

        EmulDir = InstDir & "\Emulation\"
        ToolsDir = InstDir & "\Tools\"

        ' Prepare XSL addon 
        set vsParamFile = FSO.OpenTextFile(InstDir & "\Install_files\spsettings.txt", 2, True)
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_EMULATOR_BIN_PATH=" & EmulDir & binfile2)
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_EMULATOR_SKIN_PATH=" & EmulDir & "smartphone_emulator_skin.xml")
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_VIRTUAL_RADIO_EMULATOR_BIN_PATH=" & EmulDir & binfile1)
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_VIRTUAL_RADIO_EMULATOR_SKIN_PATH=" & EmulDir & "smartphone_emulator_skin.xml")
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_EMULATOR_SCREEN_WIDTH=176")
	' Height is really 220 but Visual Studio only supports multiples of 8
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_EMULATOR_SCREEN_HEIGHT=216")
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_EMULATOR_COLOR_DEPTH=16")
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_EMULATOR_MEMORY=32")
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_SIGNTOOL_PATH=" & ToolsDir & "signcode.exe")
        vsParamFile.WriteLine("MDPG_SETTING::SMARTPHONE2003_SIGNTOOL_ARGUMENTS= -spc """ & ToolsDir & "testcert_unprivileged.cer"" -v """ & ToolsDir & "testcert_unprivileged.pvk"" -n ""UnPrivileged Trust"" -a sha1 ")
        vsParamFile.WriteLine("MDPG_SETTING::WINDIR=" & WinDir)
        vsParamFile.Close

        ' Update the addon xsl
        WshShell.Run "cscript.exe """ & InstDir & "\install_files\update_xsl.vbs"" """ & VSAddOnDir & "\Microsoft.Smartphone2003.1.0.xsl"" """ & VSAddOnDir & "\Microsoft.Smartphone2003.1.0.xsl"" """& InstDir & "\install_files\spsettings.txt""" , 1, True

    End If

End If

If InstallState = 1 Then
    ' Handle Uninstall 

    If VSProdDir <> "" Then
        FSO.DeleteFile InstDir & "\Install_files\spsettings.txt"
    End If

    ProgramsDir = WshShell.SpecialFolders("AllUsersPrograms")
    SDKShortcuts = ProgramsDir + "\Microsoft Smartphone 2003 SDK"

    If (FSO.FolderExists(SDKShortcuts)) Then
        ' Delete SDK installed files
        FSO.DeleteFile SDKShortcuts & "\Smartphone 2003 SDK.lnk"
        FSO.DeleteFile SDKShortcuts & "\Smartphone 2003 Emulator.lnk"
        FSO.DeleteFile SDKShortcuts & "\Smartphone 2003 Help.lnk"
        FSO.DeleteFile SDKShortcuts & "\Smartphone 2003 Readme.lnk"

        ' Only delete the folder if it is empty
	set SDKFolder = FSO.GetFolder(SDKShortcuts)
	set FC1 = SDKFolder.Files
        set FC2 = SDKFolder.SubFolders
	If FC1.Count = 0 And FC2.Count = 0 Then
            FSO.DeleteFolder(SDKShortcuts)
        End If
    End If

    FSO.DeleteFile InstDir & "\Emulation\emul.cmd"

    ' Remove packages and reg info that spds.exe generated

    Set objRegistry = GetObject("winmgmts:root\default:StdRegProv")

    Function EnumKeys(strRoot, strPath)
      Dim Keys
      call objRegistry.EnumKey(strRoot, strPath, Keys)
      EnumKeys = Keys
    End Function

    Function EnumValues(strRoot, strPath)
      call objRegistry.EnumValues(strRoot, strPath, Values, Types)
      EnumValues = Values
    End Function 

    Function GetStringValue(hDefKey, sSubKeyName, sValueName)
      call objRegistry.GetStringValue(hDefKey, sSubKeyName, sValueName, sValue)
      GetStringValue = sValue
    End Function
    
    Function IsInList(FileNames, strFileName)
      For Each FileName in FileNames
        If StrComp(FileName, strFileName, 1) = 0 Then
          IsInList = True
          Exit Function
        End If
      Next
      IsInList = False
    End Function

    Function AddToList(FileNames, strFileName)
      If IsInList(FileNames, strFileName) = False Then
        ReDim Preserve FileNames (UBound(FileNames)+1)
        FileNames(UBound(FileNames)) = strFileName
      End If
    End Function

    Dim FileList
    FileList = Array()

    path = "SOFTWARE\Microsoft\Windows CE Tools\SP2003DPS"
    Keys = EnumKeys(HKEY_LOCAL_MACHINE, path)
    For Each Key in Keys
  
      SubKeys = EnumKeys(HKEY_LOCAL_MACHINE, path & "\" & Key)
      For Each SubKey in SubKeys
  
        Values = EnumValues(HKEY_LOCAL_MACHINE, path & "\" & Key & "\" & SubKey)
        For Each Value in Values
          call AddToList(FileList, Value)
        Next
	call objRegistry.DeleteKey(HKEY_LOCAL_MACHINE, path & "\" & Key & "\" & SubKey)	
      Next 

      call objRegistry.DeleteKey(HKEY_LOCAL_MACHINE, path & "\" & Key)	

    Next

    ' Delete the folders containing the signed device side packages.
    ' installer doesn't nuke these because they are generated after the install

    Dim PackageArray(6)
    PackageArray(0) = "\target\wce400\armv4"
    PackageArray(1) = "\target\wce410\armv4"
    PackageArray(2) = "\target\wce420\armv4"
    PackageArray(3) = "\target\wce400\x86"
    PackageArray(4) = "\target\wce410\x86"
    PackageArray(5) = "\target\wce420\x86"

    Dim PackageVersions(3)
    PackageVersions(0) = "\target\wce400"
    PackageVersions(1) = "\target\wce410"
    PackageVersions(2) = "\target\wce420"

    ' Delete the signed package files
    For Each item in FileList
        For Each package in PackageArray
            FSO.DeleteFile InstDir & package & "\" & item
        Next
    Next

    ' Delete the folders containing the signed packages. Only delete
    ' them if they are empty to avoid deleting any user data
    For Each package in PackageArray
        set PackageFolder = FSO.GetFolder(InstDir & package)
	set FC1 = PackageFolder.Files
	set FC2 = PackageFolder.SubFolders
        If FC1.Count = 0 And FC2.Count = 0 Then
            FSO.DeleteFolder(InstDir & package)
	End If
    Next

    For Each package in PackageVersions
        set PackageFolder = FSO.GetFolder(InstDir & package)
	set FC1 = PackageFolder.Files
	set FC2 = PackageFolder.SubFolders
        If FC1.Count = 0 And FC2.Count = 0 Then
            FSO.DeleteFolder(InstDir & package)
	End If
    Next

    ' Delete the key
    WshShell.RegDelete "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows CE Tools\SP2003DPS\"
     
End If

