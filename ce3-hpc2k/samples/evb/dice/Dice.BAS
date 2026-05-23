Attribute VB_Name = "modDice"
'********************************************************************************
'*
'*  Dice - It emulates (to borrow a term) the rules of Yahtzee
'*
'*  Copyright (c) 1998 Microsoft Corporation

Dim GetValue

'Public NumPlayers
Const SND_SYNC = &H0
Const SND_ASYNC = &H1
Const SND_NODEFAULT = &H2
Const SND_LOOP = &H8
Const SND_NOSTOP = &H10

Public Declare Function sndPlaySound Lib "coredll.dll" Alias "sndPlaySoundW" (ByVal lpszSoundName As String, ByVal uFlags As Long) As Long

Function ChooseBitmap()
    Dim Die
    Randomize
    Die = Int((6) * Rnd + 1)
    GetValue = Die
    Select Case Die
        Case 1
            ChooseBitmap = App.Path & "1_Dice.bmp"
        Case 2
            ChooseBitmap = App.Path & "2_Dice.bmp"
        Case 3
            ChooseBitmap = App.Path & "3_Dice.bmp"
        Case 4
            ChooseBitmap = App.Path & "4_Dice.bmp"
        Case 5
            ChooseBitmap = App.Path & "5_Dice.bmp"
        Case 6
            ChooseBitmap = App.Path & "6_Dice.bmp"
    End Select
End Function
Sub PlayWaveFile(WavFile)
    Dim ret
    Dim flags
    flags = SND_ASYNC Or SND_NODEFAULT
    ret = sndPlaySound(WavFile, flags)
End Sub



    

