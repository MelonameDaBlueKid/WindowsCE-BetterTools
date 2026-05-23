
const DEBUG_MODE = FALSE

const SETTING_PREFIX  = "[#"
const SETTING_POSTFIX = "#]"

Dim ARRAY_MDPG_SETTINGS(), ARRAY_MDPG_VALUES()


Sub Dbg(strMsg)
  If (DEBUG_MODE = True) Then
    WScript.Echo(strMsg)
  End If
End Sub


Sub DisplayErr(strMSg)
   WScript.Echo(" *** ERR: " + strMsg)
   WScript.Echo(" *** ERR: (" + CStr(Err.number) + ") " + Err.Description)
End Sub



Function LoadReplacementStringsFromFile(strfileName)
  Const ForReading = 1, ForWriting = 2
  Dim fso, f, fLine

  Set fso = CreateObject("Scripting.FileSystemObject")  
  Set f = fso.OpenTextFile(strFileName, ForReading, false)
  If (Err.number <> 0) Then 
    DisplayErr("Unable to open specified file: " + fileName + ".")
    Exit Function
  End If

  Dim Count
  Count = 0
  Do While f.AtEndOfStream <> True
    fLine = f.ReadLine
    If (Err.number <> 0) Then 
      DisplayErr("Unable to read specified file: " + fileName + ".")
      Exit Function
    End If

    If ((fLine <> "")) Then
      Dim i, strSetting, strValue
      Count = Count + 1
      ReDim Preserve ARRAY_MDPG_SETTINGS(Count)
      ReDim Preserve ARRAY_MDPG_VALUES(Count)
      
      i = InStr(1, fLine, "=", 1) 
      If (i > 0) Then
        strSetting = Trim(Left(fLine, i-1))
        strValue   = Right(fLine, Len(fLine)-i)
        
        ARRAY_MDPG_SETTINGS(Count-1) = strSetting
        ARRAY_MDPG_VALUES(Count-1)   = strValue
      Else
        DisplayErr("Malformed setting found: " + fLine + ".")
        Exit Function
      End If
    End If
  Loop
  
  f.Close
End Function


Function GetReplacementString(strMDPGSetting)
   For i = 0 to UBound(ARRAY_MDPG_SETTINGS)
      If (StrComp(strMDPGSetting, ARRAY_MDPG_SETTINGS(i), 1) = 0) Then
         GetReplacementString = ARRAY_MDPG_VALUES(i)
         Exit Function
      End If
   Next
   
   GetReplacementString = ""
End Function


Function UpdateSettings(strVSDXslFileName, strOutputFileName)
   'On Error Resume Next
   
   Const ForReading = 1, ForWriting = 2
   Dim fso, VSDXslFile, OutputFile, strOutFileText
   
   Set fso = CreateObject("Scripting.FileSystemObject")
   If (Err.number <> 0) Then 
      DisplayErr("Unable to obtain FileSystemObject")
      Return False
   End If
   
   Dbg("Opening file [" + strVSDXslFileName + "]...")
   Set VSDXslFile = fso.OpenTextFile(strVSDXslFileName, ForReading, False)
   If (Err.number <> 0) Then 
      DisplayErr "Unable to open specified file [" + strVSDXslFileName + "]."
      Return False
   End If



   Dim strLine, strMDPGSetting, intStartIndex, intEndIndex
   Do While VSDXslFile.AtEndOfStream <> True
      strLine = VSDXslFile.ReadLine
      
      intStartIndex = InStr(1, strLine, SETTING_PREFIX, 1)
      If (Err.number <> 0) Then 
         DisplayErr "Error processing XSL file."
         Return False
      End If
      
      If (intStartIndex > 0) Then
         intEndIndex = InStr(1, strLine, SETTING_POSTFIX, 1)
         If (intEndIndex > 0) Then
           strMDPGSetting = Mid(strLine, intStartIndex+Len(SETTING_PREFIX), intEndIndex-(intStartIndex+Len(SETTING_PREFIX)))   
           strLine = Replace(strLine, Mid(strLine, intStartIndex, intEndIndex-intStartIndex+Len(SETTING_POSTFIX)), GetReplacementString(strMDPGSetting))
         End If
      End If
      
      strOutFileText = strOutFileText + strLine + vbNewLine
   Loop
   VSDXslFile.Close

   Dbg("Creating file [" + strOutputFileName + "]...")
   Set OutputFile = fso.CreateTextFile(strOutputFileName, True)
   If (Err.number <> 0) Then 
      DisplayErr "Unable to create the specified file [" + strOutputFileName + "]."
      Return False
   End If
   
   OutputFile.Write(strOutFileText)
   OutputFile.Close
   Dbg("Done.")
End Function


Sub Main
   'Arguments:	<input XSL file>
   '			<output XSL file>
   '			<settings file>
   
   'On Error Resume Next
   Err.number=0
   Err.Description=""
   Set objArgs = WScript.Arguments
   If (objArgs.Count <> 3) Then
      WScript.Echo ""
      WScript.Echo "Usage: Update_XSL [input XSL file] [output XSL file] [settings file]"
   Else
      Call LoadReplacementStringsFromFile(objArgs(2))
      Call UpdateSettings(WScript.Arguments(0), WScript.Arguments(1))
   End If
End Sub

Main