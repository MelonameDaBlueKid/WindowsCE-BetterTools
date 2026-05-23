Attribute VB_Name = "RESHelper"
'********************************************************************************
'*
'*  CEPad - Constants and string replace helper function
'*
'*  Copyright (c) 1998 Microsoft Corporation

Option Explicit

'Constants
Const keyOpen = "Open"
Const keySave = "Save"
Const keyExit = "Exit"
Const keyAbout = "AboutNotepad"

Const keySetFont = "SetFont"

'Search String Constants
Const SEARCH_MSG = 1
Const SEARCH_PHRASE = 2
Const MENU_FILE = 3
Const MENU_OPEN = 4
Const MENU_SAVE = 5
Const MENU_ABOUT = 6
Const MENU_EXIT = 7
Const MENU_EDIT = 8
Const MENU_SETFONT = 9

Function ReplaceString(sTarget As String, sSearch As String, sNew As String) As String
  Dim nPos As Integer
  Do
    nPos = InStr(sTarget, sSearch)
    If nPos <> 0 Then
      sTarget = Left(sTarget, nPos - 1) + sNew + Mid(sTarget, nPos + Len(sSearch))
    End If
  Loop While nPos <> 0
  ReplaceString = sTarget
End Function

