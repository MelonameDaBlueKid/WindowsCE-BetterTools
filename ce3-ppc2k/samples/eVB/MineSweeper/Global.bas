Attribute VB_Name = "Global"
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
'ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
'THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'PARTICULAR PURPOSE.

'Copyright  2000  Microsoft Corporation.  All Rights Reserved

Option Explicit

Public gameValue(15, 15)
Public gameState(15, 15)

Public button
Public gameStatus
Public allowQuestion

Public rowIndexExposed, colIndexExposed
Public flagCount, elapsedTime

Public Function AppPath()
    'a wrapper for App.Path
    Dim path
    
    path = App.path
    If path = "\" Then 'This is the root directory
        AppPath = "\"
    Else                'This is directory other than root.
        AppPath = path & "\"
    End If

End Function



Public Sub InitializeGame()

    Dim remainMines, rowIndex, colIndex, i, j
    remainMines = MAX_MINE
    
    ResetGame
    Randomize
    
    While (remainMines > 0)
    
        rowIndex = Int((MAX_SIZE * Rnd) + 1)
        colIndex = Int((MAX_SIZE * Rnd) + 1)

        If (gameValue(rowIndex, colIndex) <> MINE) Then
        
            gameValue(rowIndex, colIndex) = MINE
            
            For i = rowIndex - 1 To rowIndex + 1
            
                For j = colIndex - 1 To colIndex + 1
                
                    If (gameValue(i, j) <> MINE) Then
                        gameValue(i, j) = gameValue(i, j) + 1
                    End If
                    
                Next
            Next
            
            remainMines = remainMines - 1
        
        End If
        
    Wend
    
End Sub


Private Sub ResetGame()

    Dim i, j
    
    rowIndexExposed = 0
    colIndexExposed = 0
    
    flagCount = MAX_MINE
    elapsedTime = 0
        
    button = LEFT_BUTTON
    gameStatus = GAME_INPLAY
    allowQuestion = True
    
    For i = 0 To MAX_SIZE + 1
    
        For j = 0 To MAX_SIZE + 1
            gameState(i, j) = UNEXPOSED
            gameValue(i, j) = BLANK
        Next
        
    Next
    
End Sub


Public Function IsOutOfBound(rowIndex, colIndex)
    If (rowIndex < 1) Or (rowIndex > MAX_SIZE) Then
        IsOutOfBound = True
        Exit Function
    End If

    If (colIndex < 1) Or (colIndex > MAX_SIZE) Then
        IsOutOfBound = True
        Exit Function
    End If
    
    IsOutOfBound = False
End Function


Public Function GetGameStatus()
    Dim i, j
    Dim cellExposedCount
    
    cellExposedCount = 0
    
    For i = 1 To MAX_SIZE
        For j = 1 To MAX_SIZE
            If gameState(i, j) = EXPOSED Then cellExposedCount = cellExposedCount + 1
        Next
    Next

    If (cellExposedCount = (MAX_SIZE * MAX_SIZE) - MAX_MINE) Then gameStatus = GAME_WIN

    GetGameStatus = gameStatus
End Function


Public Sub UpdateBestRecord(objFile)
    Dim strName, strTime, strDate

    objFile.Open AppPath & BESTRECORD_TXT, fsModeInput
    
    strTime = objFile.LineInputString
    objFile.Close
    
    'Old record is broken
    If CInt(elapsedTime) < CInt(strTime) Then
        strName = Trim(InputBox("Enter player name", "Best Player"))
        If Len(strName) <> 0 Then
            objFile.Open AppPath & BESTRECORD_TXT, fsModeOutput
            objFile.LinePrint CStr(elapsedTime) & Chr(10)
            objFile.LinePrint CStr(strName) & Chr(10)
            objFile.LinePrint CStr(Date) & Chr(10)
            objFile.Close
        End If
    End If
    
End Sub


Function StrLeft(myString, length)
    StrLeft = Left(myString, length)
End Function


